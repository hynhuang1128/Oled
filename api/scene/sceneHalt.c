/*==========
 * INCLUDES
 ===========*/

#include "api_disp.h"
#include "hw_oled.h"

/*==================
 * GLOBAL VARIBLES
 ==================*/

static uint8 progressBar[HALT_PROGRESS_BAR_LENGTH];

/*===================
 * EXTERNAL VARIBLES
 ===================*/

extern peskData_t peskData;
extern uint16 sys_evt;
extern peskCommand_t peskCommand;
extern rtc_t realTimer;
extern rtc_t lastingTime;
extern unit_t unitType;

/*===================
 * INTERNAL VARIBLES
 ===================*/

static uint32 haltTimeStart;

/*===================
 * INTERNAL FUNCTIONS
 ====================*/

static void displayLogo( void )
{
  image_t logo =
  {
    DIS_SCENEHALT_LOGO_X_BEGIN,
    DIS_SCENEHALT_LOGO_Y_BEGIN,
    DIS_SCENEHALT_LOGO_WIDTH,
    DIS_SCENEHALT_LOGO_HEIGHT,
    logoDisp,
  };
  
  LCD_pDraw(&logo);
}

static void displayHaltHeight( void )
{
  uint16 height;
  uint8 pBuf[5] = {'0', '0', '.', '0', '\0',};
  
  if (unitType == METRIC)
  {
    height = peskData.currentHeight;
  }
  else
  {
    height = (uint16)((uint32)peskData.currentHeight * 100 / 254);
  }
  
  if (height > 1000)
  {
    pBuf[0] = (height / 1000) % 10 + 0x30;
    pBuf[1] = (height / 100) % 10 + 0x30;
    pBuf[2] = (height / 10) % 10 + 0x30;
    pBuf[3] = '\0';
  }
  else
  {
    pBuf[0] = (height / 100) % 10 + 0x30;
    pBuf[1] = (height / 10) % 10 + 0x30;
    pBuf[2] = '.';
    pBuf[3] = height % 10 + 0x30;
    pBuf[4] = '\0';
  }
  
  LCD_pNormalStr(7, 6, pBuf);
}

static void displayHaltProgress( void )
{
  uint32 progress = 0;
  static int lastProgress;
  
  imageDynamic_t sceneHalt_progress =
  {
    DIS_SCENE1_SPLIT_X_BEGIN,
    DIS_SCENE1_SPLIT_Y_BEGIN,
    DIS_SCENE1_SPLIT_WIDTH,
    DIS_SCENE1_SPLIT_HEIGHT, 
    progressBar,
  };
  
  if (lastingTime.realSecs < USER_REMINDING_TIME)
  {
    progress = ((lastingTime.realSecs - haltTimeStart) * HALT_PROGRESS_BAR_LENGTH) /
               (USER_REMINDING_TIME - haltTimeStart);
    for (int i = lastProgress; i < progress; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
    lastProgress = progress;
  }
  else if (lastingTime.realSecs == USER_REMINDING_TIME)
  {
    api_setInternalEvent(EVENT_MOTOR_MOVE);
    progress = HALT_PROGRESS_BAR_LENGTH;
    for (int i = lastProgress; i < progress; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
    lastProgress = 0;
  }
  else
  {
    for (int i = 0; i < HALT_PROGRESS_BAR_LENGTH; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
    
    lastProgress = 0;
  }
  
  LCD_pDrawDynamic(&sceneHalt_progress);
}

static void displayInitHaltProgress( void )
{
  uint32 progress = 0;
  
  imageDynamic_t sceneHalt_progress =
  {
    DIS_SCENE1_SPLIT_X_BEGIN,
    DIS_SCENE1_SPLIT_Y_BEGIN,
    DIS_SCENE1_SPLIT_WIDTH,
    DIS_SCENE1_SPLIT_HEIGHT, 
    progressBar,
  };
  
  if (lastingTime.realSecs < USER_REMINDING_TIME)
  {
    progress = ((lastingTime.realSecs + 1 - haltTimeStart) * HALT_PROGRESS_BAR_LENGTH) /
               (USER_REMINDING_TIME - haltTimeStart);
    for (int i = 0; i < progress; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
    
    for (int i = progress; i < HALT_PROGRESS_BAR_LENGTH; i++)
    {
      progressBar[i] = 0;
    }
  }
  else if (lastingTime.realSecs == USER_REMINDING_TIME)
  {
    api_setInternalEvent(EVENT_MOTOR_MOVE);
    progress = HALT_PROGRESS_BAR_LENGTH;
    for (int i = 0; i < progress; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
    
    for (int i = progress; i < HALT_PROGRESS_BAR_LENGTH; i++)
    {
      progressBar[i] = 0;
    }
  }
  else
  {
    for (int i = 0; i < HALT_PROGRESS_BAR_LENGTH; i++)
    {
      progressBar[i] = HALT_PROGRESS_BAR_ELEMENT;
    }
  }
  
  LCD_pDrawDynamic(&sceneHalt_progress);
}

static void displayHaltTime( void )
{
  uint8 pBuf[6] = {'0', '0', ':', '0', '0', '\0',};
  
  pBuf[0] = (lastingTime.minutes / 10) % 10 + 0x30;
  pBuf[1] = lastingTime.minutes % 10 + 0x30;
  pBuf[3] = (lastingTime.seconds / 10) % 10 + 0x30;
  pBuf[4] = lastingTime.seconds % 10 + 0x30;
  
  LCD_pNormalStr(82, 6, pBuf);
}

static void displayHaltUnit( void )
{
  image_t sceneHalt_unit =
  {
    DIS_HALT_UNIT_X_BEGIN,
    DIS_HALT_UNIT_Y_BEGIN,
    DIS_HALT_UNIT_WIDTH,
    DIS_HALT_UNIT_HEIGHT,
    NULL,
  };
  
  if (unitType == METRIC)
  {
    sceneHalt_unit.BMP = unitCm;
  }
  else
  {
    sceneHalt_unit.BMP = unitInch;
  }
  
  LCD_pDraw(&sceneHalt_unit);
}

/*==================
 * GLOBAL FUNCTIONS
 ===================*/

void displayHaltInfo( void )
{
  displayHaltUnit();
  displayHaltProgress();
  displayHaltTime();
}

void haltDisplay_static( void )
{
  haltTimeStart = lastingTime.realSecs + 1;
  
  LCD_clr();
  displayLogo();
  displayInitHaltProgress();
  displayHaltHeight();
  displayHaltTime();
  displayHaltUnit();
}