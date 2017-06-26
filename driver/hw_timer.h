#ifndef _HW_TIMER_H
#define _HW_TIMER_H
   
/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"
#include "hw_uart.h"

/*==========
 *  MACROS
 ===========*/
/* Delay arguments */
#define DELAY_ARGUMENTS         1070

/* Periodic timer max */
#define PERIODIC_TIMER_MAX      1000

/* Timer 3 interrupt enable */
#define ENABLE_TIMER3_INT()     (T3IE = 1)
#define DISABLE_TIMER3_INT()    (T3IE = 0)
   
/* Timer 3 */
#define RELOAD_TIMER            0xf9   
   
/*=============
 * TYPE DEFINES
 ==============*/
typedef struct periodic
{
  uint32 timerCount;
  uint32 timerMax;
} periodic_t;

typedef struct uartTimeout
{
  uint32 timeoutCount;
  uint32 timeoutValue;
  bool timedout;
} uartTimer_t;

typedef struct rtc
{
  uint32 realSecs;
  uint32 seconds;
  uint32 minutes;
  uint32 hours;
} rtc_t;
/*====================
 * FUNCTION DECLATION
 =====================*/
void hw_delayMs(uint32 msec);
void hw_clockInit(void);
void hw_timer3Cfg(void);
rtc_t hw_timerConvert(uint32 secs);

#endif