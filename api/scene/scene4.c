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

/* RST relevant */

static void displayRstHint( void )
{
  image_t scene4_RstHint =
  {
    DIS_SCENE4_RSTHINT_X_BEGIN,
    DIS_SCENE4_RSTHINT_Y_BEGIN,
    DIS_SCENE4_RSTHINT_WIDTH,
    DIS_SCENE4_RSTHINT_HEIGHT,
    resetHint,
  };
  
  LCD_pDraw(&scene4_RstHint);
}

static void displayRstSign( void )
{
  image_t scene4_RstSign =
  {
    DIS_SCENE4_RSTSIGN_X_BEGIN,
    DIS_SCENE4_RSTSIGN_Y_BEGIN,
    DIS_SCENE4_RSTSIGN_WIDTH,
    DIS_SCENE4_RSTSIGN_HEIGHT,
    resetSign,
  };
  
  LCD_pDraw(&scene4_RstSign);
}

static void displayRstText( void )
{
  image_t scene4_RstText =
  {
    DIS_SCENE4_RSTTEXT_X_BEGIN,
    DIS_SCENE4_RSTTEXT_Y_BEGIN,
    DIS_SCENE4_RSTTEXT_WIDTH,
    DIS_SCENE4_RSTTEXT_HEIGHT,
    resetText,
  };
  
  LCD_pDraw(&scene4_RstText);
}

static void displayRstOper( void )
{
  image_t scene4_RstOper =
  {
    DIS_SCENE4_RSTOPER_X_BEGIN,
    DIS_SCENE4_RSTOPER_Y_BEGIN,
    DIS_SCENE4_RSTOPER_WIDTH,
    DIS_SCENE4_RSTOPER_HEIGHT,
    resetOperation,
  };
  
  LCD_pDraw(&scene4_RstOper);
}

/* H01 relevant */

static void displayH01Hint( void )
{
  image_t scene4_H01Hint =
  {
    DIS_SCENE4_H01HINT_X_BEGIN,
    DIS_SCENE4_H01HINT_Y_BEGIN,
    DIS_SCENE4_H01HINT_WIDTH,
    DIS_SCENE4_H01HINT_HEIGHT,
    h01Hint,
  };
  
  LCD_pDraw(&scene4_H01Hint);
}

static void displayH01Sign( void )
{
  image_t scene4_H01Sign =
  {
    DIS_SCENE4_H01SIGN_X_BEGIN,
    DIS_SCENE4_H01SIGN_Y_BEGIN,
    DIS_SCENE4_H01SIGN_WIDTH,
    DIS_SCENE4_H01SIGN_HEIGHT,
    h01Sign,
  };
  
  LCD_pDraw(&scene4_H01Sign);
}

static void displayH01Text( void )
{
  image_t scene4_H01Text =
  {
    DIS_SCENE4_H01TEXT_X_BEGIN,
    DIS_SCENE4_H01TEXT_Y_BEGIN,
    DIS_SCENE4_H01TEXT_WIDTH,
    DIS_SCENE4_H01TEXT_HEIGHT,
    h01Text,
  };
  
  LCD_pDraw(&scene4_H01Text);
}

static void displayH01Oper( void )
{
  image_t scene4_H01Oper =
  {
    DIS_SCENE4_H01OPER_X_BEGIN,
    DIS_SCENE4_H01OPER_Y_BEGIN,
    DIS_SCENE4_H01OPER_WIDTH,
    DIS_SCENE4_H01OPER_HEIGHT,
    h01Operation,
  };
  
  LCD_pDraw(&scene4_H01Oper);
}


/*========
 * SCENE4
 =========*/

void rstDisplay_static( void )
{
  LCD_clr();
  displayRstSign();
  displayRstHint();
  displayWarningSign();
  displayRstText();
  displaySplit();
  displayRstOper();
}

void h01Display_static( void )
{
  LCD_clr();
  displayH01Sign();
  displayH01Hint();
  displayWarningSign();
  displayH01Text();
  displaySplit();
  displayH01Oper();
}
