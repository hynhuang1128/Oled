/*==========
 * INCLUDES
 ===========*/
#include "hw_uart.h"

/*===================
 * EXTERNAL VARIBLES
 ====================*/
extern uartData_t uartData0;
extern uartData_t uartData1;
extern uartTimer_t uartTimeout;
extern uartConfig_t uart0Config;
extern uint16 sys_evt;

/*===================
 * INTERNAL FUNCTIONS
 ====================*/
static void setBaud(uint8 port, uint8 value)
{
  if(0 == port)
  {
    U0BAUD = value;
  }
  else
  {
    U1BAUD = value;
  }
}

static void setGCR(uint8 port, uint8 value)
{
  if(0 == port)
  {
    U0GCR |= value;
  }
  else
  {
    U1GCR |= value;
  }
}

static void setPort(uint8 port)
{
  if(port == 0)
  {
    PERCFG |= 0x01; // UART0 alter to the second peripheral port
    P1SEL |= 0x10; // UART0 port configure
    P2DIR &= ~0xC0;
  }
  else
  {
    PERCFG |= 0x01; // UART1 alter to the second peripheral port
    P1SEL |= 0xc0; // UART1 port configure
  }
}

static void setReceiver(uint8 port)
{
  if(port == 0)
  {
    U0CSR |= 0x40;
  }
  else
  {
    U1CSR |= 0x40;
  }
}

/*===========================
 * INTERRUPT SERVICE ROUTINE
 ============================*/
#pragma vector = URX0_VECTOR 
__interrupt void UART0_ISR(void) 
{
  URX0IF = 0;
  *(uartData0.recvBuf + uartData0.recvCount) = U0DBUF;
  uartData0.recvCount++;
  if(uartData0.recvCount >= UART0_RX_SIZE)
  {
    uartData0.recvComplete = true;
    uartData0.recvCount = 0;
    DISABLE_RECEIVE_INT(0);
  }
}

#pragma vector = URX1_VECTOR 
__interrupt void UART1_ISR(void) 
{ 
  URX1IF = 0;
  *(uartData1.recvBuf + uartData1.recvCount) = U1DBUF;
  uartData1.recvCount++;
  if(uartData1.recvCount >= UART1_RX_SIZE)
  {
    uartData1.recvComplete = true;
    uartData1.recvCount = 0;
    DISABLE_RECEIVE_INT(1);
  }                        
}

/*=================
 * GLOBAL FUNCTIONS
 ==================*/

/*
 *
 * @ function name	        - hw_uartInit 
 * 
 * @ brief			- UART initialization 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- cfg           uart configurations parameters    
 *
 * @ return			- none	
 *
 */
void hw_uartInit(uartConfig_t cfg)
{
  DISABLE_ALL_INTERRUPTS();
  
  /* Set both port to uart mode */
  U0CSR |= 0x80;
  U1CSR |= 0x80;
    
  /* Port configuration */
  setPort(cfg.port);
  
  /* Baudrate configure */
  if (cfg.baudRate == BAUD_57600 ||
      cfg.baudRate == BAUD_115200)
  {
    setBaud(cfg.port, 216);
  }
  else
  {
    setBaud(cfg.port, 59);
  }
  
  switch(cfg.baudRate)
  {
    case BAUD_9600:
      setGCR(cfg.port, 8);
      break;
      
    case BAUD_19200:
      setGCR(cfg.port, 9);
      break;
      
    case BAUD_38400:
      
    case BAUD_57600:
      setGCR(cfg.port, 10);
      break;
      
    default:
      setGCR(cfg.port, 11);
      break;
  }
  
  /* Enable receiving process */
  setReceiver(cfg.port);
  if(cfg.port == 0)
  {
    ENABLE_RECEIVE_INT(0);
  }
  else
  {
    ENABLE_RECEIVE_INT(1);
  }
  
  ENABLE_ALL_INTERRUPTS();
}

/*
 *
 * @ function name	        - hw_uartPoll 
 * 
 * @ brief			- UART poll 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- port           uart the port to poll    
 *
 * @ return			- none	
 *
 */
void hw_uartPoll(void)
{
  uint8 port = 0;
  uartData_t uartData;
  uartData = port ? uartData1 : uartData0;
  // TODO if the port 1 is defined, prepare the data buffer
  uint8 dataBuf[UART0_RX_SIZE];
  
  if(uartTimeout.timedout)
  {
    hw_uartClearBuf(port);
    uartTimeout.timedout = false;
    uartTimeout.timeoutCount = 0;
  }
  
  if(uartData.recvComplete)
  {
    for(int i = 0; i < UART0_RX_SIZE; i++)
    {
      dataBuf[i] = uartData.recvBuf[i];
    }
    uart0Config.cbs(port, dataBuf);
  }
  port ? ENABLE_RECEIVE_INT(1) : ENABLE_RECEIVE_INT(0);
}

/*
 *
 * @ function name	        - hw_uartClearBuf 
 * 
 * @ brief			- UART clear the buffer 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- port           uart the port to execute    
 *
 * @ return			- none	
 *
 */
void hw_uartClearBuf(uint8 port)
{
  uartData_t *uartData;
  uartData = port ? &uartData1 : &uartData0;
  uartData->recvCount = 0;
  uartData->recvComplete = false;
}