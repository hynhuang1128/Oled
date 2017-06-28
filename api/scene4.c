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
 * SCENE4
 =========*/
void displayScene_4( void )
{
  static uint16 unitToggle_lastingTime;
  
  switch (specialMode.mode)
  {
    case SPECIAL_SETTING_CANCEL:
      if (SETTING_CANCEL_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "CANCEL SUCCESS");
      }
      else if (SETTING_CANCEL_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "CANCEL PROCESS");
      }
      else
      {
        LCD_pNormalStr(0, 2, "CANCEL FAILED");
      }
      break;
      
    case SPECIAL_SETTING_MAX:
      if (SETTING_MAX_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MAX SUCCESS   ");
      }
      else if (SETTING_MAX_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MAX PROCESS   ");
      }
      else
      {
        LCD_pNormalStr(0, 2, "MAX FAILED    ");
      }
      break;
      
    case SPECIAL_SETTING_MIN:
      if (SETTING_MIN_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MIN SUCCESS   ");
      }
      else if (SETTING_MIN_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MIN PROCESS   ");
      }
      else
      {
        LCD_pNormalStr(0, 2, "MIN FAILED    ");
      }
      break;
      
    case SPECIAL_TOGGLE_UNIT:
      if (unitToggle_lastingTime < 14)
      {
        LCD_pNormalStr(0, 2, "TOGGLE UNIT OK");
        unitToggle_lastingTime++;
      }
      else
      {
        unitToggle_lastingTime = 0;
        specialMode.mode = SPECIAL_NONE;
        specialMode.status = NULL;
      }
      break;
      
    default:
      // do nothing
      break;
  }
  
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
}
