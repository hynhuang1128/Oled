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
 * SCENE2
 =========*/

void displayScene_2( void )
{
  switch (peskData.info)
  {
    case 0x0000:
      LCD_pNormalStr(0, 2, "SAVE?       ");
      break;
      
    case 0x0100:
      LCD_pNormalStr(0, 2, "SAVE - 3    ");
      break;
      
    case 0x0200:
      LCD_pNormalStr(0, 2, "SAVE - 2    ");
      break;
      
    case 0x0800:
      LCD_pNormalStr(0, 2, "SAVE - 1    ");
      break;
      
    default:
      // do nothing!
      break;
  }
  /*
  uint8 buf[7];
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char(peskCommand.output & 0x0f);
  buf[3] = num2Char((peskCommand.output >> 4) & 0x0f);
  buf[4] = '\0';
  LCD_pNormalStr(0, 4, buf);
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char((uint8)(peskData.info >> 12) & 0x0f);
  buf[3] = num2Char((uint8)(peskData.info >> 8) & 0x0f);
  buf[4] = num2Char((uint8)(peskData.info >> 4) & 0x0f);
  buf[5] = num2Char((uint8)(peskData.info) & 0x0f);
  buf[6] = '\0';
  LCD_pNormalStr(0, 6, buf);
  */
}
