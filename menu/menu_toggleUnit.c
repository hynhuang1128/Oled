/*==========
 * INCLUDES
 ===========*/

#include "api_menu.h"
#include "api_disp.h"
#include "api_control.h"

/*==================
 * GLOBAL VARIBLES
 ==================*/

/*===================
 * EXTERNAL VARIBLES
 ===================*/

extern unit_t unitType;

extern menuEvent_t menuEvent;

extern uint8 settingStatus;

/*===================
 * INTERNAL VARIBLES
 ====================*/

static unit_t tempUnitType = METRIC;

/*====================
 * INTERNAL FUNCTIONS
 =====================*/

static void displayTextHint( void )
{
  image_t menuToggle =
  {
    DIS_MENU_TEXT_HINT_X_BEGIN,
    DIS_MENU_TEXT_HINT_Y_BEGIN,
    DIS_MENU_TEXT_HINT_WIDTH,
    DIS_MENU_TEXT_HINT_HEIGHT,
    menuToggleUnitHint,
  };
  
  LCD_pDraw(&menuToggle);
}
   
static void displayNumIndex( void )
{
  image_t menuNumIndex =
  {
    DIS_MENU_NUM_INDEX_X_BEGIN,
    DIS_MENU_NUM_INDEX_Y_BEGIN,
    DIS_MENU_NUM_INDEX_WIDTH,
    DIS_MENU_NUM_INDEX_HEIGHT,
    menuNumbers + MENU_NUM_INDEX_SIZE * (menuInfo.currentIndex + 1),
  };
 
  LCD_pDraw(&menuNumIndex);
}

static void displayArrows( void )
{
  image_t menuArrowUpDisp =
  {
    DIS_MENU_UP_SIGN_X_BEGIN,
    DIS_MENU_UP_SIGN_Y_BEGIN,
    DIS_MENU_UP_SIGN_WIDTH,   
    DIS_MENU_UP_SIGN_HEIGHT,
    menuSignNull,
  };
  
  image_t menuArrowDownDisp =
  {
    DIS_MENU_DOWN_SIGN_X_BEGIN,
    DIS_MENU_DOWN_SIGN_Y_BEGIN,
    DIS_MENU_DOWN_SIGN_WIDTH,   
    DIS_MENU_DOWN_SIGN_HEIGHT,
    menuSignDown,
  };
  
  LCD_pDraw(&menuArrowUpDisp);
  LCD_pDraw(&menuArrowDownDisp);
}

static void toggleClearArea( void )
{
  image_t menuToggleClear = 
  {
    DIS_MENU_UNIT_CLEAR_X_BEGIN,
    DIS_MENU_UNIT_CLEAR_Y_BEGIN, 
    DIS_MENU_UNIT_CLEAR_WIDTH,   
    DIS_MENU_UNIT_CLEAR_HEIGHT,  
    NULL,
  };
  
  LCD_clrArea(&menuToggleClear); 
}

static void unitDisplay( unit_t unit )
{
  image_t unitSelectDisp =
  {
    DIS_MENU_UNIT_X_BEGIN,
    DIS_MENU_UNIT_Y_BEGIN,
    DIS_MENU_UNIT_WIDTH,  
    DIS_MENU_UNIT_HEIGHT, 
    NULL,
  };
  
  if (unit == METRIC)
  {
    unitSelectDisp.BMP = menuUnitCm;
  }
  else
  {
    unitSelectDisp.BMP = menuUnitInch;
  }
  
  LCD_pDraw(&unitSelectDisp); 
}

static void unitIncrease( void )
{
  if (tempUnitType == IMPERIAL) return;
  
  tempUnitType = IMPERIAL;
  
  setDisplayEvent(MENU_SUB0_DISPLAY_EVT);
}

static void unitDecrease( void )
{
  if (tempUnitType == METRIC) return;
  
  tempUnitType = METRIC;
  
  setDisplayEvent(MENU_SUB0_DISPLAY_EVT);
}

static void unitModify( void )
{
  unitType = tempUnitType;
  
  api_nv_write(UNIT_NV_ID, &unitType, UNIT_NV_ID_LEN);
  
  menu_setStatus(MENU_TASK_DONE);
  
  settingStatus = STATUS_HINT_SUCCESS;
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/

/* toggle unit display */
void displayToggle( void )
{
  displayArrows();
  displayTextHint();
  displayNumIndex();
}

void ToggleUnitDetails( void )
{
  unitDisplay(tempUnitType);
}

void ToggleUnitDetailsStatic( void )
{
  toggleClearArea();
  unitDisplay(unitType);
}

void startToggleUnit( void )
{
  setDisplayEvent(SUB0_DISPLAY_EVT);
  menu_setStatus(MENU_TASK_PROCESSING);
}

void doneToggleUnit( void )
{
  static uint16 time;
  
  // TODO
  if (time < MENU_TIME_MAX)
  {
    time++;
  }
  
  if (time == 1)
  {
    setDisplayEvent(STATUS_DISPLAY_EVT);
    setDisplayEvent(STATUS_INFO_CHANGE_EVT);
  }
  else if (time == 25)
  {
    menuLevelAscend();
    menu_setStatus(MENU_TASK_STOP);
    time = 0;
  }
}

void processingToggleUnit( void )
{
  switch (menuEvent.eventId)
  {
    case MENU_UP_EVENT:
      timerCountStart();
      unitDecrease();
      break;
      
    case MENU_DOWN_EVENT:
      timerCountStart();
      unitIncrease();
      break;
      
    case MENU_ENTER_EVENT:
      unitModify();
      break;
      
    case MENU_EXIT_EVENT:
      menuLevelAscend();
      menu_setStatus(MENU_TASK_STOP);
      break;
      
    default:
      // do nothing
      break;
  }
}

void initToggleUnit( void )
{
  // TODO display the current menu item interface
  setDisplayEvent(MENU_INFO_CHANGE_EVT);
  menu_setStatus(MENU_TASK_STOP);
}