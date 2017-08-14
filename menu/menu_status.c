/*==========
 * INCLUDES
 ===========*/

#include "api_menu.h"

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

static void dispAnimation( void )
{
  static uint16 tick;
  static uint8 tock;
  
  image_t dot[3] = 
  {
    {
      DIS_PROCESS_ANIM_X0_BEGIN,
      DIS_PROCESS_ANIM_Y_BEGIN, 
      DIS_PROCESS_ANIM_WIDTH,    
      DIS_PROCESS_ANIM_HEIGHT,   
      processingAnimation,
    },
    
    {
      DIS_PROCESS_ANIM_X1_BEGIN,
      DIS_PROCESS_ANIM_Y_BEGIN,
      DIS_PROCESS_ANIM_WIDTH,
      DIS_PROCESS_ANIM_HEIGHT,
      processingAnimation,
    },
    
    {
      DIS_PROCESS_ANIM_X2_BEGIN,
      DIS_PROCESS_ANIM_Y_BEGIN,
      DIS_PROCESS_ANIM_WIDTH,
      DIS_PROCESS_ANIM_HEIGHT,
      processingAnimation,
    },
  };
  
  if (tick < 1)
  {
    tick++;
  }
  else
  {
    tock++;
    tick = 0;
  }
  
  if (tock == 1)
  {
    dot[0].BMP = processingAnimation + 16;
  }
  else if (tock == 2)
  {
    dot[0].BMP = processingAnimation + 32;
    dot[1].BMP = processingAnimation + 16;
  }
  else if (tock == 3)
  {
    dot[0].BMP = processingAnimation + 16;
    dot[1].BMP = processingAnimation + 32;
    dot[2].BMP = processingAnimation + 16;
  }
  else if (tock == 4)
  {
    dot[0].BMP = processingAnimation;
    dot[1].BMP = processingAnimation + 16;
    dot[2].BMP = processingAnimation + 32;
  }
  else if (tock == 5)
  {
    dot[0].BMP = processingAnimation;
    dot[1].BMP = processingAnimation;
    dot[2].BMP = processingAnimation + 16;
    tock = 0;
  }
  
  for (int i = 0; i < 3; i++)
  {
    LCD_pDraw(dot+i);
  }
}
   
static void dispSuccess( void )
{
  image_t clearWaitingSign =
  {
    DIS_PROCESS_ANIM_X0_BEGIN,
    DIS_PROCESS_ANIM_Y_BEGIN,
    DIS_PROCESS_ANIM_CLEAR_WIDTH,    
    DIS_PROCESS_ANIM_HEIGHT,
    NULL,
  };
  
  image_t displaySuccessHint =
  {
    DIS_MENU_STATUS_X_BEGIN,
    DIS_MENU_STATUS_Y_BEGIN,
    DIS_MENU_STATUS_WIDTH,  
    DIS_MENU_STATUS_HEIGHT, 
    menuSuccessStatus,
  };
  
  LCD_pDraw(&displaySuccessHint);
  LCD_clrArea(&clearWaitingSign);
}

static void dispFail( void )
{
  image_t clearWaitingSign =
  {
    DIS_PROCESS_ANIM_X0_BEGIN,
    DIS_PROCESS_ANIM_Y_BEGIN,
    DIS_PROCESS_ANIM_CLEAR_WIDTH,    
    DIS_PROCESS_ANIM_HEIGHT,
    NULL,
  };
  
  image_t displayFailHint =
  {
    DIS_MENU_STATUS_X_BEGIN,
    DIS_MENU_STATUS_Y_BEGIN,
    DIS_MENU_STATUS_WIDTH,  
    DIS_MENU_STATUS_HEIGHT, 
    menuFailedStatus,
  };
  
  LCD_pDraw(&displayFailHint);
  LCD_clrArea(&clearWaitingSign);
}

static void dispSetting( void )
{
  image_t displaySettingHint =
  {
    DIS_MENU_STATUS_X_BEGIN,
    DIS_MENU_STATUS_Y_BEGIN,
    DIS_MENU_STATUS_WIDTH,  
    DIS_MENU_STATUS_HEIGHT, 
    menuSettingStatus,
  };
  
  LCD_pDraw(&displaySettingHint);
}

static void dispClearing( void )
{
  image_t displayClearingHint =
  {
    DIS_MENU_STATUS_X_BEGIN,
    DIS_MENU_STATUS_Y_BEGIN,
    DIS_MENU_STATUS_WIDTH,  
    DIS_MENU_STATUS_HEIGHT, 
    menuClearingStatus,
  };
  
  LCD_pDraw(&displayClearingHint);
}
   
/*===================
 * PUBLIC FUNCTIONS
 ===================*/
   
/* status hint display */
void displaySuccess( void )
{
  dispSuccess();
}

void displayClearing( void )
{
  dispAnimation();
  dispClearing();
}

void displaySetting( void )
{
  dispAnimation();
  dispSetting();
}

void displayFail( void )
{
  dispFail();
}

