/*===========================================
 *
 * name			- projectHandset
 * 
 * projectname		- ´øÆÁÊÖ¿Ø°å
 *
 * date			- 2017.5.26
 *
 * author			- Eric Huang
 *
 * email                   - eric.huang@9-a-m.com
 *
 ============================================*/
   
/*==========
 * INCLUDES
 ===========*/
#include "main.h"
   
/*=================
 * GLOBAL VARIBLES
 ==================*/

/* Uart data 0 */
uartData_t uartData0 =
{
  { 0, 0, 0, 0 },
  0,
  0,
  false,
};

/* Uart data 1 */
uartData_t uartData1 =
{
  { 0, 0, 0, 0 },
  0,
  0,
  false,
};
   
/* Periodic timer */
periodic_t periodicTimer =
{
  0,
  PERIODIC_TIMER_MAX,
};

/* Uart time out */
uartTimer_t uartTimeout =
{
  0,
  UART0_TIMEOUT,
  false,
};

/* Uart 0 config */
uartConfig_t uart0Config =
{
  BAUD_9600,
  0,
  cb_dataHandler,
};

/* Pesk data */
peskData_t peskData =
{
  0,
  NORMAL,
  0,
};

/* Pesk commands */
peskCommand_t peskCommand =
{
  KEY_IDLE,
  CMD_STOP,
};

/*===================
 * INTERNAL FUNCTION
 ====================*/
static void performPeriodic(uint32 time, periodCBack_t cb)
{
  static bool involked;
  if( !(periodicTimer.timerCount % time) )
  {
    if(!involked)
    {
      cb();
      involked = true;
    }
  }
  else
  {
    involked = false;
  }
}

/*===========
 * CALLBACKS
 ============*/
void cb_dataHandler(uint8 port, uint8 *data)
{
  // TODO complete the data callback function
  peskData.status = data[1];
  peskData.info_L = data[3];
  peskData.info_H = data[2];
  
#if (defined DEBUG) && (defined DEBUG_STATUS)
  switch(peskData.status)
  {
    case NORMAL:
      LCD_pNormalStr(0, 0, "pesk in normal");
      break;
      
    case ERROR:
      LCD_pTinyStr(0, 0, "PESK IN ERROR ");
      break;
      
    case RST:
      LCD_pTinyStr(0, 0, "PESK IN RESET ");
      break;
      
    case SAVE:
      LCD_pTinyStr(0, 0, "PESK IN SAVE  ");
      break;
      
    default:
      
      break;
  }
#endif
  
  if(NORMAL == peskData.status)
  {
    peskData.height = peskData.info;
#if (defined DEBUG) && (defined DEBUG_STATUS)
    uint8 buf[5];
    buf[3] = peskData.height % 10 + 0x30;
    buf[2] = peskData.height / 10 % 10 + 0x30;
    buf[1] = peskData.height / 100 % 10 + 0x30;
    buf[0] = peskData.height / 1000 % 10 + 0x30;
    buf[4] = '\0';
    LCD_pTinyStr(0, 1, buf);
#endif
  }
  
}

/*=========
 *  SETUP
 ==========*/
void setup(void)
{
  /* Key process initialize */
  hw_keyInit();
  
  /* Image initialize */
  image_t qrcode =
  {
    QRCODE_X_BEGIN,
    QRCODE_Y_BEGIN,
    QRCODE_X_END,
    QRCODE_Y_END,
    QRCode,
  };
  
  /* LCD initialize */
  LCD_init();
  LCD_fill(FULL);
  LCD_clr();
  //LCD_pDraw(&qrcode);
  
  /* Clock initialize */
  hw_clockInit();
  
  /* Timer 3 initialize */
  hw_timer3Cfg();
  
  /* Uart 0 initialize */
  hw_uartInit(uart0Config);
  
}

/*==========
 *   LOOP
 ===========*/
void loop(void)
{
  /* Uart data receiving process poll */
  performPeriodic(PERIOD_UART0_POLL, hw_uartPoll);
  
  /* Key press process poll */
  performPeriodic(PERIOD_KEY_POLL, hw_keyPoll);
  
  /* Key command process poll */
  performPeriodic(PERIOD_CMD_POLL, hw_cmdCall);
}

/*==========
 *   MAIN
 ===========*/
void main()
{
  /* setup for the program */
  setup();
  
  /* doing the loop */
  while(1)
  {
    loop();
  }
}
