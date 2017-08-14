/*==========
 * INCLUDES
 ===========*/
#include "hw_pesk.h"
   
/*===================
 * EXTERNAL VARIBLES
 ====================*/
extern peskCommand_t peskCommand;
extern uint16 sys_evt;

/*===================
 * INTERNAL FUNCTIONS
 ====================*/

static uint8 getKey( void )
{
  uint8 key = 0;
  key |= (P0 & 0x03);
  key |= ((P0 & 0x08) >> 1);
  key |= ((P1 & 0xe0) >> 2);
  return key;
}

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
  P0 &= 0x0f;
  P0 |= peskCommand.output;
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
  static uint8 key;
  static uint8 debounceTime;
  static uint8 keyPrevious;
  
  key = getKey();
  
  if (key != keyPrevious)
  {
    debounceTime = 0;
    keyPrevious = key;
  }
  else
  {
    debounceTime++;
  }
  
  if (debounceTime >= DEBOUNCING_TIME / PERIOD_KEY_POLL - 1)
  {
    debounceTime = 0;
    peskCommand.input = key;
  }
}