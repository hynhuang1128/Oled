/*===========================================
 *
 * name			- projectHandset
 * 
 * projectname		- ´øÆÁÊÖ¿Ø°å
 *
 * date			- 2017.5.26
 *
 * author		- Eric Huang
 *
 * email                - eric.huang@9-a-m.com
 *
 ============================================*/
   
/*==========
 * INCLUDES
 ===========*/
#include "main.h"
   
/*===================
 * EXTERNAL VARIBLES
 ====================*/

extern rtc_t realTimer;

extern unit_t unitType;

/*=================
 * GLOBAL VARIBLES
 ==================*/

/* System event poll */
uint16 sys_event;

/* Lasting time */
rtc_t lastingTime;
   
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
  0,
  0,
  0,
  NORMAL,
  0,
  IDLE,
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

static bool performInitTask(uint32 time, periodCBack_t cb)
{
  static bool finished;
  static uint8 tempTime;
  
  if (finished) return finished;
  
  if (!(periodicTimer.timerCount % INIT_TIME_ELEMENT))
  {
    tempTime++;
  }
  
  if (tempTime >= time)
  {
    finished = true;
  }
  else
  {
    cb();
  }
  
  return finished;
}

static void performPeriodic(uint32 time, periodCBack_t cb)
{
  static bool involked;
  if (!(periodicTimer.timerCount % time))
  {
    if (!involked)
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

/*=========
 *  SETUP
 ==========*/
void setup(void)
{
  /* Key process initialize */
  hw_keyInit();
  
  /* Clock initialize */
  hw_clockInit();
  
  /* Dma initialize */
  dmaInit();
  
  /* LCD initialize */
  LCD_init();
  LCD_fill(FULL);
  LCD_clr();
  
  /* Timer 3 initialize */
  hw_timer3Cfg();
  
  /* Uart 0 initialize */
  hw_uartInit(uart0Config);
  
  /* Clear the display */
  LCD_clr();
  
  /* Read the unit information */
  if (!api_nv_read(UNIT_NV_ID, &unitType, UNIT_NV_ID_LEN))
  {
    unitType = METRIC;
  }
  
}

/*==========
 *   LOOP
 ===========*/
void loop(void)
{
  /* Device initialize */
  isInit = performInitTask(8, displayInitScene);
  
  /* Uart data receiving process poll */
  performPeriodic(PERIOD_UART0_POLL, hw_uartPoll);
  
  /* Key press process poll */
  performPeriodic(PERIOD_KEY_POLL, api_keyPoll);
  
  /* Display process poll */
  performPeriodic(PERIOD_DISPLAY, displayScene);
  
  /* data handler */
  performPeriodic(PERIOD_DATAHANDLER, api_dataHandler);
  
  /* direction and idle time estimate */
  performPeriodic(PERIOD_GETDIR, api_getDirection);
  
  /* menu operation process poll */
  performPeriodic(PERIOD_MENU_POLL, menu_eventProcess);
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
