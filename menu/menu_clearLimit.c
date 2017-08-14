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
   
/*===================
 * INTERNAL VARIBLES
 ====================*/

/*====================
 * INTERNAL FUNCTIONS
 =====================*/

static void displayTextHint( void )
{
  image_t menuClear =
  {
    DIS_MENU_TEXT_HINT_X_BEGIN,
    DIS_MENU_TEXT_HINT_Y_BEGIN,
    DIS_MENU_TEXT_HINT_WIDTH,
    DIS_MENU_TEXT_HINT_HEIGHT,
    menuClearHint,
  };
  
  LCD_pDraw(&menuClear);
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
    menuSignUp,
  };
  
  image_t menuArrowDownDisp =
  {
    DIS_MENU_DOWN_SIGN_X_BEGIN,
    DIS_MENU_DOWN_SIGN_Y_BEGIN,
    DIS_MENU_DOWN_SIGN_WIDTH,   
    DIS_MENU_DOWN_SIGN_HEIGHT,
    menuSignNull,
  };
  
  LCD_pDraw(&menuArrowUpDisp);
  LCD_pDraw(&menuArrowDownDisp);
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/

/* clear limit display */
void displayClrLimit( void )
{
  displayArrows();
  displayTextHint();
  displayNumIndex();
}
 
void startClearLimit( void )
{
  api_setInternalEvent(EVENT_CLEAR_LIMIT);
  setDisplayEvent(STATUS_DISPLAY_EVT);
}
 
void doneClearLimit( void )
{
  static uint16 time;
  
  timerCountStop();
  
  // TODO
  if (time < MENU_TIME_MAX)
  {
    time++;
  }
  
  if (time == 1)
  {
    setDisplayEvent(STATUS_INFO_CHANGE_EVT);
  }
  else if (time == 25)
  {
    menuLevelAscend();
    menu_setStatus(MENU_TASK_STOP);
    time = 0;
  }
}
 
void processingClearLimit( void )
{
  timerCountStop();
  setDisplayEvent(STATUS_INFO_CHANGE_EVT);
}
 
void initClearLimit( void )
{
  // TODO display the current menu item interface
  setDisplayEvent(MENU_INFO_CHANGE_EVT);
  menu_setStatus(MENU_TASK_STOP);
}