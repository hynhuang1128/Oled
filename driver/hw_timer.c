/*==========
 * INCLUDES
 ===========*/
#include "hw_timer.h"

/*===================
 * EXTERNAL VARIBLES
 ====================*/
extern periodic_t periodicTimer;
extern uartTimer_t uartTimeout;
rtc_t realTimer =
{
  0,
  0,
  0,
  0,
};

/*===================
 * INTERNAL FUNCTION
 ====================*/
static void timerUpdate()
{
  realTimer.realSecs++;
  
  realTimer.seconds = realTimer.realSecs % 60;
  realTimer.minutes = (realTimer.realSecs / 60) % 60;
  realTimer.hours = (realTimer.realSecs / 3600) % 60;
}

/*===========================
 * INTERRUPT SERVICE ROUTINE
 ============================*/
#pragma vector = T3_VECTOR
__interrupt void T3_ISR(void)
{ 
  IRCON =0;
  T3CC0 = RELOAD_TIMER;
  
  /* Uart time out */
  uartTimeout.timeoutCount++;
  if(uartTimeout.timeoutCount >= uartTimeout.timeoutValue)
  {
    uartTimeout.timeoutCount = 0;
    uartTimeout.timedout = true;
  }
  
  /* Periodic timer */
  periodicTimer.timerCount++;
  if(periodicTimer.timerCount > periodicTimer.timerMax)
  {
    periodicTimer.timerCount = 1;
    timerUpdate();
  }
}

/*=================
 * GLOBAL FUNCTION
 ==================*/
   
/*
 *
 * @ function name	        - hw_timerConvert 
 * 
 * @ brief			- timer format transfer
 *
 * @ date			- 2017.6.20
 *
 * @ author			- Eric Huang
 *
 * @ param			- secs               
 *
 * @ return			- real time counter format data	
 *
 */  
rtc_t hw_timerConvert( uint32 secs )
{
  rtc_t t;
  t.realSecs = secs;
  t.seconds = secs % 60;
  t.minutes = (secs / 60) % 60;
  t.hours = (secs / 3600) % 60;
  if (secs > 86398)
  {
    t.seconds = 59;
    t.minutes = 59;
    t.hours = 23;
  }
  return t;
}
   
/*
 *
 * @ function name	        - hw_delayMs 
 * 
 * @ brief			- Delay ms function 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- msec           n milliseconds to delay    
 *
 * @ return			- none	
 *
 */   
void hw_delayMs(uint32 msec)
{    
  for (int i = 0; i < msec; i++)
  {
    for (int j = 0; j < DELAY_ARGUMENTS; j++);
  }
}

/*
 *
 * @ function name	        - hw_clockInit 
 * 
 * @ brief			- 32MHz clock initialization 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- none    
 *
 * @ return			- none	
 *
 */
void hw_clockInit(void)
{
  CLKCONCMD &= ~0x40;
  while(CLKCONSTA & 0x40);
  CLKCONCMD &= ~0x47;
}

/*
 *
 * @ function name	        - hw_timer3Cfg 
 * 
 * @ brief			- Timer 3 configuration 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- none    
 *
 * @ return			- none	
 *
 */
void hw_timer3Cfg(void)
{
  T3CCTL0 |= 0x04;
  T3CC0 = RELOAD_TIMER;
  T3CTL |= 0x08;
  ENABLE_TIMER3_INT();
  T3CTL |= 0xC2;
  T3CTL &= ~0x04;
  T3CTL |= 0x10;
  ENABLE_ALL_INTERRUPTS();
}