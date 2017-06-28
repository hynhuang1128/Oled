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
extern special_t specialMode;
extern unit_t unitType;

/*===================
 * INTERNAL VARIBLES
 ====================*/


/*===================
 * PUBLIC FUNCTIONS
 ===================*/
// TODO nothing has been done yet
void displayScene( void )
{
  static uint8 firstDisp;
  
  /* shift the port to the lcd function */
  SHIFT_PORT_LCD();
  LCD_CS = 0;
  
  if (NORMAL == peskData.status && SPECIAL_NONE == specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE1)
    {
      displayScene_1();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE1;
    }
  }
  else if (SAVE == peskData.status && SPECIAL_NONE == specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE2)
    {
      displayScene_2();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE2;
    }
  }
  else if ( (ERROR == peskData.status ||
             RST == peskData.status)  &&
             SPECIAL_NONE == specialMode.mode )
  {
    if (firstDisp & FIRST_DISPLAY_SCENE3)
    {
      displayScene_3();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE3;
    }
  }
  else if (SPECIAL_NONE != specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE4)
    {
      displayScene_4();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE4;
    }
  }
  else
  {
    // TODO
  }
  
  /* reset the port prepare to receive the key press event */
  CLOSE_PORT_LCD();
}