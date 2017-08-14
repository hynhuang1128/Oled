/*==========
 * INCLUDES
 ===========*/
#include "api_disp.h"
#include "api_menu.h"
#include "hw_oled.h"

/*===================
 * INTERNAL VARIBLES
 ===================*/
displayEventHandler_t menuStatusDisplay[] =
{
  displaySuccess,
  displayFail,
  displayClearing,
  displaySetting,
};

/*===================
 * EXTERNAL VARIBLES
 ===================*/

extern uint8 settingStatus;

/*====================
 * INTERNAL FUNCTIONS
 ====================*/

/* universal sign */
 
static void displayDashSign( void )
{
  image_t menuDashSign =
  {
    DIS_MENU_DASH_SIGN_X_BEGIN,
    DIS_MENU_DASH_SIGN_Y_BEGIN,
    DIS_MENU_DASH_SIGN_WIDTH,
    DIS_MENU_DASH_SIGN_HEIGHT,
    menuSignDash,
  };
 
  LCD_pDraw(&menuDashSign);
}   

static void displayNumTotal( void )
{
  image_t menuNumTotal =
  {
    DIS_MENU_NUM_TOTAL_X_BEGIN,
    DIS_MENU_NUM_TOTAL_Y_BEGIN,
    DIS_MENU_NUM_TOTAL_WIDTH,
    DIS_MENU_NUM_TOTAL_HEIGHT,
    menuNumbers + MENU_NUM_INDEX_SIZE * menuInfo.indexCount,
  };
 
  LCD_pDraw(&menuNumTotal);
}  

static void displayMenuSplit( void )
{
  image_t menuSplitDisp =
  {
    DIS_MENU_SPLIT_LINE_X_BEGIN,
    DIS_MENU_SPLIT_LINE_Y_BEGIN,
    DIS_MENU_SPLIT_LINE_WIDTH,  
    DIS_MENU_SPLIT_LINE_HEIGHT, 
    menuSplit,
  };
  
  LCD_pDraw(&menuSplitDisp);
}

static void displayPressHint( void )
{
  image_t menuPressHintDisp =
  {
    DIS_MENU_PRESSHINT_X_BEGIN,
    DIS_MENU_PRESSHINT_Y_BEGIN,
    DIS_MENU_PRESSHINT_WIDTH,
    DIS_MENU_PRESSHINT_HEIGHT, 
    menuPressHint,
  };
  
  LCD_pDraw(&menuPressHintDisp);
}

/* main menu display process */
static void displayMainHint( void )
{
  switch (menuInfo.currentIndex)
  {
    case MENU_INDEX_TOGGLEUNIT:
      displayToggle();
      break;
      
    case MENU_INDEX_SETMIN:
      displaySetMin();
      break;
      
    case MENU_INDEX_SETMAX:
      displaySetMax();
      break;
      
    case MENU_INDEX_CLRLIMIT:
      displayClrLimit();
      break;
      
    default:
      // do nothing
      break;
  }
}

/*==================
 * GLOBAL FUNCTIONS
 ===================*/

void menuDisplay_static( void )
{
  LCD_clr();
  displayNumTotal();
  displayDashSign();
  displayMainHint();
  displayPressHint();
  displayMenuSplit();
}

void statusDisplay_static( void )
{
  LCD_clr();
  //menuStatusDisplay[settingStatus]();
}

void displayMainMenuInfo( void )
{
  displayNumTotal();
  displayDashSign();
  displayMainHint();
}

void sub0Display_static( void )
{
  ToggleUnitDetailsStatic();
}

void displaySub0( void )
{
  ToggleUnitDetails();
}

void displayStatusCode( void )
{
  menuStatusDisplay[settingStatus]();
}