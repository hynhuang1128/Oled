/*==========
 * INCLUDES
 ===========*/
#include "api_control.h"

/*=================
 * PUBLIC VARIBLES
 ==================*/
special_t specialMode = 
{
  SPECIAL_NONE,
  NULL,
};

unit_t unitType = METRIC;
  
/*===================
 * INTERNAL VARIBLES
 ====================*/
   
static struct internalTimerSet
  {
    internalTimer_t setting;
    internalTimer_t set;
    internalTimer_t setStop;
    internalTimer_t maxHeight;
    internalTimer_t minHeight;
    internalTimer_t unitTimeout;
  } timerSet = 
  {
    {TIMER_STOP_FLAG, 0},
    {TIMER_STOP_FLAG, 0},
    {TIMER_STOP_FLAG, 0},
    {TIMER_STOP_FLAG, 0},
    {TIMER_STOP_FLAG, 0},
    {TIMER_STOP_FLAG, 0},
  };   

/*===================
 * EXTERNAL VARIBLES
 ====================*/

extern peskCommand_t peskCommand;
extern peskData_t peskData;

/*====================
 * INTERNAL FUNCTIONS
 ====================*/

/*---------------
 * TIMER RELATED
 ----------------*/
/* start timer */
static void startTimer(internalTimer_t *t)
{
  t->flag = TIMER_START_FLAG;
  t->timerValue = 0;
}

/* stop timer */
static void stopTimer(internalTimer_t *t)
{
  t->flag = TIMER_STOP_FLAG;
  t->timerValue = 0;
}

/* pause timer 
static void pauseTimer(internalTimer_t *t)
{
  t->flag = TIMER_STOP_FLAG;
} */

/* resume timer 
static void resumeTimer(internalTimer_t *t)
{
  t->flag = TIMER_START_FLAG;
} */

/* internal timer update */
static void internalTimer_update( void )
{
  if (TIMER_START_FLAG == timerSet.setting.flag)
  {
    timerSet.setting.timerValue++;
  }
  else
  {
    // do nothing
  }
  
  if (TIMER_START_FLAG == timerSet.set.flag)
  {
    timerSet.set.timerValue++;
  }
  else
  {
    // do nothing
  }
  
  if (TIMER_START_FLAG == timerSet.maxHeight.flag)
  {
    timerSet.maxHeight.timerValue++;
  }
  else
  {
    // do nothing
  }
  
  if (TIMER_START_FLAG == timerSet.minHeight.flag)
  {
    timerSet.minHeight.timerValue++;
  }
  else
  {
    // do nothing
  }
  
  if (TIMER_START_FLAG == timerSet.setStop.flag)
  {
    timerSet.setStop.timerValue++;
  }
  else
  {
    // do nothing
  }
  
  if (TIMER_START_FLAG == timerSet.unitTimeout.flag)
  {
    timerSet.unitTimeout.timerValue++;
  }
  else
  {
    // do nothing
  }
}

/*-----------------
 * LOGIC FUNCTIONS
 ------------------*/

/* alter unit */
static void alterUnitLogic( void )
{
  if (METRIC == unitType)
  {
    unitType = IMPERIAL;
  }
  else
  {
    unitType = METRIC;
  }
  
  specialMode.mode = SPECIAL_TOGGLE_UNIT;
  specialMode.status = NULL;
}

/* instant command */
static void instantCmd(uint8 cmd)
{
  peskCommand.output = cmd;
}

/* logic for set buttons pressed */
static void key_setStopLogic( uint8 cmd )
{
  if ( timerSet.setStop.timerValue > CONTROL_DELAY_COUNT(STOP_SET_SETTING_TIME) )
  {
    if ( IDLE != peskData.moveDir )
    {
      if ( TIMER_START_FLAG == timerSet.setStop.flag &&
           timerSet.setStop.timerValue < CONTROL_DELAY_COUNT(STOP_SET_STOP_TIME) )
      {
        instantCmd(CMD_STOP);
      }
      else if ( TIMER_START_FLAG == timerSet.setStop.flag &&
                timerSet.setStop.timerValue < CONTROL_DELAY_COUNT(STOP_SET_MOVING_TIME) )
      {
        instantCmd(cmd);
      }
      else
      {
        stopTimer(&(timerSet.set));
        instantCmd(CMD_STOP);
      }
    }
    else
    {
      instantCmd(CMD_STOP);
    }
  }
}

/* logic for setting the min limit */
static void key_minLogic( void )
{
  static uint32 timerTemp;
  
  // TODO time out handle
  if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
       timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(300) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
            timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(2000) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
            timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(2500) )
  {
    specialMode.mode = SPECIAL_SETTING_MIN;
    specialMode.status = SETTING_MIN_PROCESS;
    instantCmd(CMD_DOWN);
  }
  else if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
            timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(3000) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
            timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(7700) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.minHeight.flag &&
            timerSet.minHeight.timerValue < CONTROL_DELAY_COUNT(8000) )
  {
    instantCmd(CMD_STOP);
  }
  else
  {
    if (peskData.info != MIN_SUCCESS_SIGN || NORMAL != peskData.status )
    {
      if (0 == (timerSet.minHeight.timerValue % CONTROL_DELAY_COUNT(1000)))
      {
        instantCmd(CMD_SETTING);
      }
      else if (0 == (timerSet.minHeight.timerValue % CONTROL_DELAY_COUNT(2025)))
      {
        instantCmd(CMD_STOP);
      }
    }
    else
    {
      specialMode.status = SETTING_MAX_SUCCESS;
      timerTemp = timerSet.minHeight.timerValue;
    }
    
    if ( specialMode.status == SETTING_MAX_SUCCESS && 
         timerSet.minHeight.timerValue > (timerTemp + CONTROL_DELAY_COUNT(2000)) )
    {
      stopTimer(&(timerSet.minHeight));
      instantCmd(CMD_STOP);
      specialMode.mode = SPECIAL_NONE;
      specialMode.status = NULL;
    }
  }
}

/* logic for setting the max limit */
static void key_maxLogic( void )
{
  static uint32 timerTemp;
  
  // TODO time out handle
  if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
       timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(300) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
            timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(2000) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
            timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(2500) )
  {
    specialMode.mode = SPECIAL_SETTING_MAX;
    specialMode.status = SETTING_MAX_PROCESS;
    instantCmd(CMD_UP);
  }
  else if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
            timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(3000) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
            timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(7700) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.maxHeight.flag &&
            timerSet.maxHeight.timerValue < CONTROL_DELAY_COUNT(8000) )
  {
    instantCmd(CMD_STOP);
  }
  else
  {
    if (peskData.info != MAX_SUCCESS_SIGN)
    {
      if (0 == (timerSet.maxHeight.timerValue % CONTROL_DELAY_COUNT(1000)))
      {
        instantCmd(CMD_SETTING);
      }
      else if (0 == (timerSet.maxHeight.timerValue % CONTROL_DELAY_COUNT(2025)))
      {
        instantCmd(CMD_STOP);
      }
    }
    else
    {
      specialMode.status = SETTING_MAX_SUCCESS;
      timerTemp = timerSet.maxHeight.timerValue;
    }
    
    if ( specialMode.status == SETTING_MAX_SUCCESS && 
         timerSet.maxHeight.timerValue > (timerTemp + CONTROL_DELAY_COUNT(2000)) )
    {
      stopTimer(&(timerSet.maxHeight));
      instantCmd(CMD_STOP);
      specialMode.mode = SPECIAL_NONE;
      specialMode.status = NULL;
    }
  }
}

/* logic for setting button pressed */
static void key_settingLogic( void )
{
  static uint32 timerTemp;
  
  if ( TIMER_START_FLAG == timerSet.setting.flag &&
       timerSet.setting.timerValue < CONTROL_DELAY_COUNT(300) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(2000) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(2300) )
  {
    specialMode.mode = SPECIAL_SETTING_CANCEL;
    specialMode.status = SETTING_CANCEL_PROCESS;
    instantCmd(CMD_UP);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(3300) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(3600) )
  {
    instantCmd(CMD_DOWN);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(3900) )
  {
    instantCmd(CMD_STOP);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(7900) )
  {
    instantCmd(CMD_SETTING);
  }
  else if ( TIMER_START_FLAG == timerSet.setting.flag &&
            timerSet.setting.timerValue < CONTROL_DELAY_COUNT(8000) )
  {
    instantCmd(CMD_STOP);
  }
  else
  {
    // TODO time out handle
    if (peskData.info != CANCEL_SUCCESS_SIGN)
    {
      if (0 == (timerSet.setting.timerValue % CONTROL_DELAY_COUNT(1000)))
      {
        instantCmd(CMD_SETTING);
      }
      else if (0 == (timerSet.setting.timerValue % CONTROL_DELAY_COUNT(2025)))
      {
        instantCmd(CMD_STOP);
      }
    }
    else
    {
      specialMode.status = SETTING_CANCEL_SUCCESS;
      timerTemp = timerSet.setting.timerValue;
    }
    
    if ( specialMode.status == SETTING_CANCEL_SUCCESS && 
         timerSet.setting.timerValue > (timerTemp + CONTROL_DELAY_COUNT(2000)) )
    {
      stopTimer(&(timerSet.setting));
      instantCmd(CMD_STOP);
      specialMode.mode = SPECIAL_NONE;
      specialMode.status = NULL;
    }
  }
}

// parameter is memeory height instruments
static void key_setStartLogic( uint8 cmd )
{
  if ( TIMER_START_FLAG == timerSet.set.flag &&
       timerSet.set.timerValue < CONTROL_DELAY_COUNT(300) )
  {
    instantCmd(cmd);
  }
  else
  {
    stopTimer(&(timerSet.setStop));
    instantCmd(CMD_STOP);
  }
}

/* handle for the key press logic functions */
static void keyLogic( void )
{
  static uint8 previousPressed = KEY_IDLE;
  static uint8 pressedTemp;
  
  /* barrier the handset input while cancelling the limit */
  if (SPECIAL_SETTING_CANCEL == specialMode.mode)
  {
    peskCommand.input = KEY_SETTING;
  }
  else if (SPECIAL_SETTING_MAX == specialMode.mode)
  {
    peskCommand.input = KEY_SETTING_AND_UP;
  }
  else if (SPECIAL_SETTING_MIN == specialMode.mode)
  {
    peskCommand.input = KEY_SETTING_AND_DOWN;
  }
  
  if (previousPressed != peskCommand.input)
  {
    /* start the timer */
    switch (peskCommand.input)
    {
      case KEY_IDLE:
        if (KEY_SET1 == previousPressed)
        {
          startTimer(&(timerSet.setStop));
        }
        else if (KEY_SET2 == previousPressed)
        {
          startTimer(&(timerSet.setStop));
        }
        else if (KEY_SET3 == previousPressed)
        {
          startTimer(&(timerSet.setStop));
        }
        else if (KEY_SETTING == previousPressed)
        {
          instantCmd(CMD_STOP);
        }
        else
        {
          // TODO
        }
        
        break;
        
      case KEY_UP:
        if (KEY_SET1 == previousPressed)
        {
          instantCmd(CMD_SET1);
        }
        else if (KEY_SET2 == previousPressed)
        {
          instantCmd(CMD_SET2);
        }
        else if (KEY_SET3 == previousPressed)
        {
          instantCmd(CMD_SET3);
        }
        break;
        
      case KEY_DOWN:
        if (KEY_SET1 == previousPressed)
        {
          instantCmd(CMD_SET1);
        }
        else if (KEY_SET2 == previousPressed)
        {
          instantCmd(CMD_SET2);
        }
        else if (KEY_SET3 == previousPressed)
        {
          instantCmd(CMD_SET3);
        }
        break;
        
      case KEY_SETTING:
        if (KEY_IDLE == previousPressed)
        {
          startTimer(&(timerSet.setting));
        }
        else if (KEY_SET1 == previousPressed)
        {
          instantCmd(CMD_SET1);
        }
        else if (KEY_SET2 == previousPressed)
        {
          instantCmd(CMD_SET2);
        }
        else if (KEY_SET3 == previousPressed)
        {
          instantCmd(CMD_SET3);
        }
        break;
        
      case KEY_SET1:
        if (KEY_IDLE == previousPressed)
        {
          startTimer(&(timerSet.set));
        }
        break;
        
      case KEY_SET2:
        if (KEY_IDLE == previousPressed)
        {
          startTimer(&(timerSet.set));
        }
        break;
        
      case KEY_SET3:
        if (KEY_IDLE == previousPressed)
        {
          startTimer(&(timerSet.set));
        }
        break;
        
      default:
        if (KEY_SET1 == previousPressed)
        {
          instantCmd(CMD_SET1);
        }
        else if (KEY_SET2 == previousPressed)
        {
          instantCmd(CMD_SET2);
        }
        else if (KEY_SET3 == previousPressed)
        {
          instantCmd(CMD_SET3);
        }
        break;
    }
    
    /* save the previous pressed key */
    pressedTemp = previousPressed;
    previousPressed = peskCommand.input;
  }
  else
  {
    /* started timer continous counting */
    switch (peskCommand.input)
    {
      case KEY_IDLE:
        if (KEY_SETTING == pressedTemp)
        {
          // TODO ?
        }
        else if (KEY_SET1 == pressedTemp)
        {
          key_setStopLogic(CMD_SET1);
        }
        else if (KEY_SET2 == pressedTemp)
        {
          key_setStopLogic(CMD_SET2);
        }
        else if (KEY_SET3 == pressedTemp)
        {
          key_setStopLogic(CMD_SET3);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_UP:
        if (KEY_IDLE == pressedTemp)
        {
          instantCmd(CMD_UP);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_DOWN:
        if (KEY_IDLE == pressedTemp)
        {
          instantCmd(CMD_DOWN);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_SETTING:
        if (KEY_IDLE == pressedTemp)
        {
          key_settingLogic();
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_SET1:
        if (KEY_IDLE == pressedTemp)
        {
          key_setStartLogic(CMD_SET1);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_SET2:
        if (KEY_IDLE == pressedTemp)
        {
          key_setStartLogic(CMD_SET2);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
        
      case KEY_SET3:
        if (KEY_IDLE == pressedTemp)
        {
          key_setStartLogic(CMD_SET3);
        }
        else
        {
          instantCmd(CMD_STOP);
        }
        break;
          
      default:
        // TODO handle the exceptions
        break;
    }  
  }
  
  /* timer update */
  internalTimer_update();
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/
/*
 *
 * @ function name	        - api_keyPoll 
 * 
 * @ brief			- Key press control process
 *
 * @ date			- 2017.6.21
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void api_keyPoll( void )
{
  /* get the current port status */
  hw_keyPoll();
  
  /* handle the key */
  keyLogic();
  
  /* move the pesk */
  hw_cmdCall();
}