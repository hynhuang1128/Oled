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

/*========
 * SCENE3
 =========*/

void displayScene_3( void )
{
  if (ERROR == peskData.status)
  {
    LCD_pNormalStr(0, 2, "PESK IN ERROR");
    switch (peskData.info)
    {
      case 0x0100:
        LCD_pNormalStr(0, 4, "E01");
        break;
        
      case 0x0200:
        LCD_pNormalStr(0, 4, "E02");
        break;
        
      case 0x0400:
        LCD_pNormalStr(0, 4, "E03");
        break;
        
      case 0x4000:
        LCD_pNormalStr(0, 4, "E07");
        break;
        
      case 0x8000:
        LCD_pNormalStr(0, 4, "E08");
        break;
        
      case 0x0001:
        LCD_pNormalStr(0, 4, "E09");
        break;
        
      case 0x0010:
        LCD_pNormalStr(0, 4, "H01");
        break;
    }
  }
  else
  {
    LCD_pNormalStr(0, 2, "PESK IN RESET");
  }
}
