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
   
/*=================
 * GLOBAL VARIBLES
 ==================*/

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
  if ( (data[0] == 0x01) && (data[1] == 0x01) && (data[2] == 0x01) || 
       (data[0] == 0x01) && (data[1] == 0x01) && (data[2] == 0x00) && (data[3] != 0x00) )
  {
    // keep the information unchanged
  }
  else if (data[0] == 0x01)
  {
    peskData.status = data[1];
    peskData.info_L = data[3];
    peskData.info_H = data[2];
  }
  else
  {
    // do nothing
  }
  
  static int16 heightDiffer;
  static int16 previousHeight;
  static uint32 delayCount;
  static uint32 idleTimerStart;
  
  static bool firstTimeIdle;
  
  /* validate the height informations */
  if (NORMAL == peskData.status)
  {
    peskData.height = peskData.info;
    if (peskData.height != previousHeight)
    {
      heightDiffer = ((int16)peskData.height - previousHeight);
      if (ABS(heightDiffer) < HEIGHTDIFFER_MAX
          && previousHeight != 0)
      {
        peskData.currentHeight = peskData.height;
      }
      else if (0 == previousHeight)
      {
        peskData.currentHeight = peskData.height;
      }
      else
      {
        // do nothing
      }
      previousHeight = peskData.height;
    }
  }
  else if (ERROR == peskData.status)
  {
    // TODO
  }
  else if (RST == peskData.status)
  {
    // TODO
  }
  else if (SAVE == peskData.status)
  {
    // TODO
  }
  else
  {
    // do nothing
  }
  
  /* filter the direction informations */
  if (delayCount > STATUS_DELAY_COUNT(100) && NORMAL == peskData.status)
  {
    if (peskData.currentHeight != peskData.previousHeight)
    {
      if (peskData.currentHeight > peskData.previousHeight)
      {
        peskData.moveDir = UP;
      }
      else if (peskData.currentHeight < peskData.previousHeight)
      {
        peskData.moveDir = DOWN;
      }
      peskData.previousHeight = peskData.currentHeight; 
      firstTimeIdle = true;
    }
    else
    {
      if (firstTimeIdle)
      {
        peskData.moveDir = IDLE;
        firstTimeIdle = false;
        idleTimerStart = realTimer.realSecs;
        lastingTime.realSecs = 0;
      }
      else
      {
        peskData.moveDir = IDLE;
        lastingTime.realSecs = realTimer.realSecs - idleTimerStart;
      }
    }
    delayCount = 0;
  }
  
  /* get the lasting time */
  lastingTime = hw_timerConvert(lastingTime.realSecs);
  
  delayCount++;
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
  
  /* Image initialize */
  image_t logo =
  {
    IMAGE_X_BEGIN,
    IMAGE_Y_BEGIN,
    IMAGE_X_END,
    IMAGE_Y_END,
    logoDisp,
  };
  
  /* LCD initialize */
  LCD_init();
  LCD_fill(FULL);
  LCD_clr();
  LCD_pDraw(&logo);
  
  /* Timer 3 initialize */
  hw_timer3Cfg();
  
  /* Uart 0 initialize */
  hw_uartInit(uart0Config);
  
  /* delay for 500 ms */
  hw_delayMs(1500);
  LCD_clr();
}

/*==========
 *   LOOP
 ===========*/
void loop(void)
{
  /* Uart data receiving process poll */
  performPeriodic(PERIOD_UART0_POLL, hw_uartPoll);
  
  /* Key press process poll */
  performPeriodic(PERIOD_KEY_POLL, api_keyPoll);
  
  /* Display process poll */
  performPeriodic(PERIOD_DISPLAY, displayScene);
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
