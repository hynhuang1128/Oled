/*==========
 * INCLUDES
 ===========*/
#include "hw_pesk.h"
   
/*===================
 * EXTERNAL VARIBLES
 ====================*/
extern peskCommand_t peskCommand;

/*=================
 * GLOBAL FUNCTIONS
 ==================*/

/*
 *
 * @ function name	        - hw_keyInit 
 * 
 * @ brief			- Key initialize
 *
 * @ date			- 2017.5.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void hw_keyInit(void)
{
  HW_KEY_INIT();
}

/*
 *
 * @ function name	        - hw_cmdCall 
 * 
 * @ brief			- Key command process
 *
 * @ date			- 2017.5.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void hw_cmdCall(void)
{
  uint8 cmd = 0;
  switch(peskCommand.input)
  {
    case KEY_IDLE:
      cmd = CMD_STOP;
      break;
    
    case KEY_UP:
      cmd = CMD_UP;
      break;
    
    case KEY_DOWN:
      cmd = CMD_DOWN;
      break;
    
    case KEY_SET1:
      cmd = CMD_SET1;
      break;
    
    case KEY_SET2:
      cmd = CMD_SET2;
      break;
    
    case KEY_SET3:
      cmd = CMD_SET3;
      break;
    
    case KEY_SET4:
      cmd = CMD_SET4;
      break;
    
    case KEY_SETTING:
      cmd = CMD_SETTING;
      break;
     
    default:
      cmd = CMD_STOP;
      // Should not get here !
      break;
  }
  P0 = cmd;
}

/*
 *
 * @ function name	        - hw_keyPoll 
 * 
 * @ brief			- Key poll process
 *
 * @ date			- 2017.5.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void hw_keyPoll(void)
{
  volatile uint8 key = KEY_IDLE;
  static uint8 previous = KEY_IDLE;
  static uint8 debounceTime;
  key = P0 & 0xf0;
  if(key != previous)
  {
    previous = key;
  }
  else
  {
    if(++debounceTime >= DEBOUNCING_TIME / PERIOD_KEY_POLL - 1)
    {
      debounceTime = 0;
      peskCommand.input = key;
    }
  }
  hw_cmdCall();
  
#if (defined DEBUG) && (defined DEBUG_KEY)
  uint8 buf[5];
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = peskCommand.input / 16 % 16 + 0x30;
  buf[2] = (buf[2] > 9) ? (buf[2]) : buf[2];
  buf[3] = peskCommand.input % 16 + 0x30;
  buf[3] = (buf[3] > 9) ? (buf[3]) : buf[3];
  buf[4] = '\0';
  LCD_pTinyStr(0, 2, buf);
#endif
}