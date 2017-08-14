/*==========
 * INCLUDES
 ===========*/
#include "api_disp.h"
#include "hw_oled.h"

/*===================
 * EXTERNAL VARIBLES
 ===================*/
extern peskData_t peskData;
extern uint16 sys_evt;
extern peskCommand_t peskCommand;
extern rtc_t realTimer;
extern rtc_t lastingTime;
extern unit_t unitType;

/*====================
 * INTERNAL FUNCTIONS
 ====================*/
   
static void displaySaveHint( void )
{
  image_t scene2_saveHint =
  {
    DIS_SCENE2_CODE_X_BEGIN,
    DIS_SCENE2_CODE_Y_BEGIN,
    DIS_SCENE2_CODE_WIDTH,
    DIS_SCENE2_CODE_HEIGHT,
    saveHint,
  };
  
  LCD_pDraw(&scene2_saveHint);
}

static void displayPressHint( void )
{
  image_t scene2_pressHint =
  {
    DIS_SCENE2_PRESS_X_BEGIN,
    DIS_SCENE2_PRESS_Y_BEGIN,
    DIS_SCENE2_PRESS_WIDTH,
    DIS_SCENE2_PRESS_HEIGHT,
    savePressHint,
  };
  
  LCD_pDraw(&scene2_pressHint);
}

static void displaySuccessHint( void )
{
  image_t scene2_successHint =
  {
    DIS_SCENE2_SUCCESS_X_BEGIN,
    DIS_SCENE2_SUCCESS_Y_BEGIN,
    DIS_SCENE2_SUCCESS_WIDTH,
    DIS_SCENE2_SUCCESS_HEIGHT,
    saveSuccessHint,
  };
  
  LCD_pDraw(&scene2_successHint);
}

static void displaySave1( void )
{
  image_t scene2_save1 =
  {
    DIS_SCENE2_SAVE_X_BEGIN,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save1,
  };
  
  LCD_pDraw(&scene2_save1);
}

static void displaySave2( void )
{
  image_t scene2_save2 =
  {
    DIS_SCENE2_SAVE_X_BEGIN,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save2,
  };
  
  LCD_pDraw(&scene2_save2);
}

static void displaySave3( void )
{
  image_t scene2_save3 =
  {
    DIS_SCENE2_SAVE_X_BEGIN,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save3,
  };
  
  LCD_pDraw(&scene2_save3);
}

static void displayPressSave( void )
{
  image_t scene2_saveCombo1 =
  {
    DIS_SCENE2_SAVECOMBO_X_BEGIN,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save1,
  };
  
  image_t scene2_saveCombo2 =
  {
    DIS_SCENE2_SAVECOMBO_X_BEGIN + DIS_SCENE2_SAVE_OFFSET,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save2,
  };
  
  image_t scene2_saveCombo3 =
  {
    DIS_SCENE2_SAVECOMBO_X_BEGIN + 2 * DIS_SCENE2_SAVE_OFFSET,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    save3,
  };
  
  LCD_pDraw(&scene2_saveCombo1);
  LCD_pDraw(&scene2_saveCombo2);
  LCD_pDraw(&scene2_saveCombo3);
}

/*========
 * SCENE2
 =========*/

void saveDisplay_static( void )
{
  LCD_clr();
  displaySplit();
  displaySaveHint();
  displayPressHint();
  displayPressSave();
}

void displaySaveCode( void )
{
  image_t clrArea0 = 
  {
    CLR_BOTTOM_X_BEGIN,
    CLR_BOTTOM_Y_BEGIN,    
    CLR_BOTTOM_WIDTH,    
    CLR_BOTTOM_HEIGHT,      
    NULL,
  };
  
  switch (peskData.code)
  {
    case 0x0000:
      LCD_clrArea(&clrArea0);
      displayPressHint();
      displayPressSave();
      break;
      
    case 0x0100:
      LCD_clrArea(&clrArea0);
      displaySuccessHint();
      displaySave3();
      break;
      
    case 0x0200:
      LCD_clrArea(&clrArea0);
      displaySuccessHint();
      displaySave2();
      break;
      
    case 0x0800:
      LCD_clrArea(&clrArea0);
      displaySuccessHint();
      displaySave1();
      break;
      
    default:
      // do nothing!
      break;
  }
}