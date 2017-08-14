/*==========
 * INCLUDES
 ===========*/
#include "api_disp.h"
#include "hw_oled.h"

/*===================
 * EXTERNAL VARIBLES
 ===================*/

/*====================
 * INTERNAL FUNCTIONS
 ====================*/

static void displayInit( void )
{
  /* Image initialize */
  image_t logo =
  {
    DIS_SCENEHALT_LOGO_X_BEGIN,
    DIS_SCENEHALT_LOGO_Y_BEGIN + 1,
    DIS_SCENEHALT_LOGO_WIDTH,
    DIS_SCENEHALT_LOGO_HEIGHT,
    logoDisp,
  };

  LCD_pDraw(&logo);
}

/*============
 * SCENE INIT
 =============*/

void displayInitScene( void )
{
  displayInit();
}