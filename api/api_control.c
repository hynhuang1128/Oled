/*==========
 * INCLUDES
 ===========*/
#include "api_control.h"
#include "api_menu.h"

/*=================
 * EXTERN VARIBLES
 ==================*/

extern rtc_t lastingTime;
extern rtc_t realTimer;
extern uint16 sys_event;
extern displayEvent_t currentStaticDisplay;

/*=================
 * PUBLIC VARIBLES
 ==================*/

unit_t unitType = METRIC;
uint8 settingStatus;
  
/*===================
 * INTERNAL VARIBLES
 ====================*/

static uint16 pressingTime;
   
static bool enableEventListener = true;
   
static uint8 statusCurrent;
  
static internalTimer_t internalTimer =
{
  INTERNAL_TIMER_STOP,
  0,
};

static uint16 eventInternal = EVENT_KEY_NO_EVT;

static internalEventHandler_t eventProcessFuncArray[] = 
{
  upPressed_processEvent,
  downPressed_processEvent,
  setPressed_processEvent,
  settingPressed_processEvent,
  upReleased_processEvent,
  downReleased_processEvent,
  setReleased_processEvent,
  settingReleased_processEvent,
  // TODO finish the processing event
  toggleUnit_precessEvent,
  setMinLimit_processEvent,
  setMaxLimit_processEvent,
  clearLimit_processEvent,
  motorMove_processEvent,
};

static uint8 taskCnt = sizeof(eventProcessFuncArray) / sizeof(eventProcessFuncArray[0]);
  
/*===================
 * EXTERNAL VARIBLES
 ====================*/

extern peskCommand_t peskCommand;
extern peskData_t peskData;

/*====================
 * INTERNAL FUNCTIONS
 ====================*/

/*--------------------
 * SET STATIC DISPLAY
 ---------------------*/
void setStaticDisplay(void)
{
  switch(peskData.status)
  {
    case NORMAL:
      setDisplayEvent(HEIGHT_DISPLAY_EVT);
      break;
      
    case ERROR:
      setDisplayEvent(H01_DISPLAY_EVT);
      break;
      
    case SAVE:
      setDisplayEvent(SAVE_DISPLAY_EVT);
      break;
      
    case RST:
      setDisplayEvent(RST_DISPLAY_EVT);
      break;
      
    default:
      // do nothing
      break;
  }
}

/*---------------
 * TIMER RELATED
 ----------------*/
/* start timer */
static void startTimer(internalTimer_t *t)
{
  t->state = INTERNAL_TIMER_START;
  t->timerValue = 0;
}

/* stop timer */
static void stopTimer(internalTimer_t *t)
{
  t->state = INTERNAL_TIMER_STOP;
  t->timerValue = 0;
}

/* internal timer update (period : 100ms) */
static void internalTimer_update( void )
{
  static uint8 timerCount;
  
  if (INTERNAL_TIMER_START == internalTimer.state)
  {
    if (timerCount < (INTERNAL_TIMER_INTERVAL / PERIOD_KEY_POLL))
    {
      timerCount++;
    }
    else
    {
      internalTimer.timerValue++;
      timerCount = 0;
    }
    
    if (internalTimer.timerValue > INTERNAL_TIMER_TIMEOUT)
    {
      if (currentStaticDisplay == HEIGHT_DISPLAY_EVT)
      {
        if (!menuInfo.active)
        {
          setDisplayEvent(HALT_DISPLAY_EVT);
        }
      }
      stopTimer(&internalTimer);
    }
  }
  else
  {
    timerCount = 0;
  }
}

/*-----------------
 * LOGIC FUNCTIONS
 ------------------*/

/* instant command */
static void instantCmd(uint8 cmd)
{
  P0 = cmd;
}

/*-------------------
 * key event handler
 --------------------*/

/* toggle unit */
static void toggleUnit_precessEvent( void )
{
  if (METRIC == unitType)
  {
    unitType = IMPERIAL;
  }
  else
  {
    unitType = METRIC;
  }
  
  api_clrInternalEvent();
}

/* pressed keyup event */
static void upPressed_processEvent(void)
{
  if (!menuInfo.active)
  {
    if (DONE == setOutput(0, CMD_UP))
    {
      api_clrInternalEvent();
    }
  }
  else
  {
    menu_setTask(MENU_UP_EVENT);
    api_clrInternalEvent();
  }
}

/* pressed keydown event */
static void downPressed_processEvent(void)
{
  if (!menuInfo.active)
  {
    if (DONE == setOutput(0, CMD_DOWN))
    {
      api_clrInternalEvent();
    }
  }
  else
  {
    menu_setTask(MENU_DOWN_EVENT);
    api_clrInternalEvent();
  }
}

/* pressed keyset event */
static void setPressed_processEvent(void)
{ 
  if (!menuInfo.active)
  {
    setOutput(0, CMD_STOP);
    setOutput(2, peskCommand.output);
    if (DONE == setOutput(4, CMD_STOP))
    {
      api_clrInternalEvent();
    }
  }
  else
  {
    menu_setTask(MENU_EXIT_EVENT);
    api_clrInternalEvent();
  }
}

/* pressed keysetting event */
static void settingPressed_processEvent(void)
{
  if (!menuInfo.active)
  {
    setOutput(0, CMD_SETTING);
    setOutput(2, CMD_STOP);
  
    pressingTime++;
  
    if (pressingTime > 80)
    {
      menuInit();
      api_clrInternalEvent();
      pressingTime = 0;
    }
  }
  else
  {
    menu_setTask(MENU_ENTER_EVENT);
    api_clrInternalEvent();
  }
}

/* released keyup event */
static void upReleased_processEvent(void)
{
  if (DONE == setOutput(0, CMD_STOP))
  {
    api_clrInternalEvent();
  }
}

/* released keydown event */
static void downReleased_processEvent(void)
{
  if (DONE == setOutput(0, CMD_STOP))
  {
    api_clrInternalEvent();
  }
}

/* motor move event */
static void motorMove_processEvent(void)
{
  static uint8 actionCount = 0;
  
  if(actionCount < MOTOR_ACTION_TIME(3))
  {
    actionCount++;
  }
  else
  {
    actionCount = 0;
    MOTOR_OSCILLATOR = 0;
    api_clrInternalEvent();
    return;
  }
  
  if (actionCount % MOTOR_INTERVAL == MOTOR_ON_TIME)
  {
    MOTOR_OSCILLATOR = 1;
  }
  else if (actionCount % MOTOR_INTERVAL == MOTOR_OFF_TIME)
  {
    MOTOR_OSCILLATOR = 0;
  }
}

/* released keyset event */
static void setReleased_processEvent(void)
{
  if (!menuInfo.active)
  {
    if (internalTimer.timerValue == 1)
    {
      instantCmd(CMD_STOP);
    }
    else if (internalTimer.timerValue == 9)
    {
      if (peskData.moveDir != IDLE)
      {
        instantCmd(peskCommand.output);
      }
      else
      {
        instantCmd(CMD_STOP);
      }
    }
    else if (internalTimer.timerValue == 13)
    {
      instantCmd(CMD_STOP);
      api_clrInternalEvent();
    }
    else if (internalTimer.timerValue > 13)
    {
      api_clrInternalEvent();
    }
  }
  else
  {
    menu_setTask(MENU_EXIT_EVENT);
    api_clrInternalEvent();
  }
}

/* released keysetting event */
static void settingReleased_processEvent(void)
{
  instantCmd(CMD_STOP);
  api_clrInternalEvent();
}

/* set mininum height limit event */
static void setMinLimit_processEvent(void)
{
  static int operationCount;
  
  enableEventListener = false;
  
  /* emit menu event */
  menu_setStatus(MENU_TASK_PROCESSING);
  settingStatus = STATUS_HINT_SETTING;
  
  setOutput(LIMIT_OPERATION_TIME_STEP0, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP1, CMD_UP);
  setOutput(LIMIT_OPERATION_TIME_STEP2, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP3, CMD_DOWN);
  setOutput(LIMIT_OPERATION_TIME_STEP4, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP5, CMD_SETTING);
  setOutput(LIMIT_OPERATION_TIME_STEP6, CMD_STOP);
  setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP7), CMD_SETTING);
  if (DONE == setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP8), CMD_STOP))
  {
    operationCount++;
  }
  
  if ( (peskData.info == MIN_SUCCESS_SIGN) &&
       (peskData.status == NORMAL) )
  {
    operationCount = 0;
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_SUCCESS;
  }
  else if (operationCount > LIMIT_MAXMIN_TIMEOUT_COUNT)
  {
    operationCount = 0;
    startTimer(&internalTimer);
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_FAIL;
  }
  else
  {
    settingStatus = STATUS_HINT_SETTING;
  }
}

/* set maxinum height limit event */
static void setMaxLimit_processEvent(void)
{
  static int operationCount;
  enableEventListener = false;
  
  /* emit menu event */
  menu_setStatus(MENU_TASK_PROCESSING);
  settingStatus = STATUS_HINT_SETTING;
  
  setOutput(LIMIT_OPERATION_TIME_STEP0, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP1, CMD_DOWN);
  setOutput(LIMIT_OPERATION_TIME_STEP2, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP3, CMD_UP);
  setOutput(LIMIT_OPERATION_TIME_STEP4, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP5, CMD_SETTING);
  setOutput(LIMIT_OPERATION_TIME_STEP6, CMD_STOP);
  setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP7), CMD_SETTING);
  if (DONE == setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP8), CMD_STOP))
  {
    operationCount++;
  }
  
  if ( (peskData.info == MAX_SUCCESS_SIGN) &&
       (peskData.status == NORMAL) )
  {
    operationCount = 0;
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_SUCCESS;
  }
  else if (operationCount > LIMIT_MAXMIN_TIMEOUT_COUNT)
  {
    operationCount = 0;
    startTimer(&internalTimer);
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_FAIL;
  }
  else
  {
    // do nothing
  }
}

/* clear height limit event */
static void clearLimit_processEvent(void)
{
  static int operationCount;
  enableEventListener = false;
 
  /* emit menu event */
  menu_setStatus(MENU_TASK_PROCESSING);
  settingStatus = STATUS_HINT_CLEARING;
  
  setOutput(LIMIT_OPERATION_TIME_STEP0, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP1, CMD_DOWN);
  setOutput(LIMIT_OPERATION_TIME_STEP2, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP3, CMD_UP);
  setOutput(LIMIT_OPERATION_TIME_STEP4, CMD_STOP);
  setOutput(LIMIT_OPERATION_TIME_STEP5, CMD_SETTING);
  setOutput(LIMIT_OPERATION_TIME_STEP6, CMD_STOP);
  setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP7), CMD_SETTING);
  if (DONE == setOutput((operationCount * LIMIT_OPERATION_TIME_INTERVAL + LIMIT_OPERATION_TIME_STEP8), CMD_STOP))
  {
    operationCount++;
  }
  
  if ( (peskData.info == CANCEL_SUCCESS_SIGN) &&
       (peskData.status == NORMAL) )
  {
    operationCount = 0;
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_SUCCESS;
  }
  else if (operationCount > LIMIT_CANCEL_TIMEOUT_COUNT)
  {
    operationCount = 0;
    startTimer(&internalTimer);
    enableEventListener = true;
    api_clrInternalEvent();
    
    /* emit menu event */
    menu_setStatus(MENU_TASK_DONE);
    settingStatus = STATUS_HINT_FAIL;
  }
  else
  {
    // do nothing
  }
}

/* handle the key press logic functions */
static void keyLogic( void )
{
  static uint8 previousPressed = KEY_IDLE;
  
  if (!enableEventListener) return;
  
  // while initialize is complete
  if (!isInit)
  {
    return;
  }
  
  // key change event trigger
  if (previousPressed != peskCommand.input)
  {
    /* if key change event has been triggered restart the internal timer */
    startTimer(&internalTimer);
    
    if (KEY_IDLE == previousPressed)
    {
      /* get the current key pressed state */
      switch (peskCommand.input)
      {
        case KEY_UP:
          api_setInternalEvent(EVENT_KEY_UP_ONPRESS);
          break;
          
        case KEY_DOWN:
          api_setInternalEvent(EVENT_KEY_DOWN_ONPRESS);
          break;
          
        case KEY_SET1:
          peskCommand.output = CMD_SET1;
          api_setInternalEvent(EVENT_KEY_SET_ONPRESS);
          break;
          
        case KEY_SET2:
          peskCommand.output = CMD_SET2;
          api_setInternalEvent(EVENT_KEY_SET_ONPRESS);
          break;
          
        case KEY_SET3:
          peskCommand.output = CMD_SET3;
          api_setInternalEvent(EVENT_KEY_SET_ONPRESS);
          break;
          
        case KEY_SETTING:
          api_setInternalEvent(EVENT_KEY_SETTING_ONPRESS);
          break;
          
        default :
          // should never get here !
          break;
      }
    }
    else if (KEY_IDLE == peskCommand.input)
    {
      /* get the current key released state */
      switch (previousPressed)
      {
        case KEY_UP:
          api_setInternalEvent(EVENT_KEY_UP_ONRELEASE);
          break;
          
        case KEY_DOWN:
          api_setInternalEvent(EVENT_KEY_DOWN_ONRELEASE);
          break;
          
        case KEY_SET1:
          peskCommand.output = CMD_SET1;
          api_setInternalEvent(EVENT_KEY_SET_ONRELEASE);
          break;
          
        case KEY_SET2:
          peskCommand.output = CMD_SET2;
          api_setInternalEvent(EVENT_KEY_SET_ONRELEASE);
          break;
          
        case KEY_SET3:
          peskCommand.output = CMD_SET3;
          api_setInternalEvent(EVENT_KEY_SET_ONRELEASE);
          break;
          
        case KEY_SETTING:
          api_setInternalEvent(EVENT_KEY_SETTING_ONRELEASE);
          break;
          
        default :
          // should never get here!
          break;
      }
    }
    else
    {
      if ( previousPressed == KEY_SET1 ||
           previousPressed == KEY_SET2 ||
           previousPressed == KEY_SET3 )
      {
        api_setInternalEvent(EVENT_KEY_SET_ONRELEASE);
      }
      else
      {
        api_setInternalEvent(EVENT_KEY_UP_ONRELEASE);
      }
    }
    
    previousPressed = peskCommand.input;
  }
  
}

/* set port output at specific time */
static fStatus setOutput(uint32 time, uint8 outputData)
{
  if (internalTimer.timerValue == time)
  {
    instantCmd(outputData);
    return DONE;
  }
  else if (internalTimer.timerValue > time)
  {
    return DONE;
  }
  else
  {
    return PROCESSING;
  }
}

/* handle for the key state change events */
static void keyEventHandler( void )
{
  uint8 taskNum = 0;
  
  while (taskNum < taskCnt)
  {
    if ( (eventInternal >> taskNum) & 0x0001 ) break;
    taskNum++;
  }
  
  if (taskNum < taskCnt)
  {
    eventProcessFuncArray[taskNum]();
  }
}

/*===========
 * CALLBACKS
 ============*/

/*
 *
 * @ function name	        - api_getDirection
 * 
 * @ brief			- get the current direction
 *
 * @ date			- 2017.7.31
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void api_getDirection( void )
{
  DISABLE_ALL_INTERRUPTS();
  
  /* direction acquire temp varibles */
  static uint32 idleTimerStart;
  static bool firstTimeIdle;
  
  /* idle time start event */
  static uint32 previousLastingTime;
  
  /* filter the direction informations */
  if (NORMAL == statusCurrent)
  {
    if (peskData.currentHeight != peskData.previousHeight)
    {
      if (peskData.currentHeight > peskData.previousHeight)
      {
        peskData.moveDir = UP;
      }
      else if (peskData.currentHeight < peskData.previousHeight)
      {
        peskData.moveDir = DOWN;
      }
      /* if move direction changed from "idle" */
      if (!menuInfo.active)
      {
        setDisplayEvent(PESK_STATE_CHANGE_EVT);
      }
        
      if (currentStaticDisplay == HALT_DISPLAY_EVT)
      {
        if (!menuInfo.active)
        {
          setDisplayEvent(HEIGHT_DISPLAY_EVT);
        }
      }
      
      peskData.previousHeight = peskData.currentHeight; 
      firstTimeIdle = true;
    }
    else
    {
      peskData.moveDir = IDLE;
      if (firstTimeIdle)
      {
        firstTimeIdle = false;
        // if the current display mode is in menu disply mode the idleTimerStart value won't change!
        idleTimerStart = realTimer.realSecs;
        lastingTime.realSecs = 0;
      }
      else
      {
        lastingTime.realSecs = realTimer.realSecs - idleTimerStart;
        
        if (previousLastingTime != lastingTime.realSecs)
        {
          previousLastingTime = lastingTime.realSecs;
          
          /* is the current display mode is in normal display mode 
            and the lasting time is changed, emit a lasting time changing event. */
          if (currentStaticDisplay == HEIGHT_DISPLAY_EVT)
          {
            if (!menuInfo.active)
            {
              setDisplayEvent(PESK_STATE_CHANGE_EVT);
            }
          }
          else if (currentStaticDisplay == HALT_DISPLAY_EVT)
          {
            if (!menuInfo.active)
            {
              setDisplayEvent(HALT_INFO_CHANGE_EVT);
            }
          }
          
        }
      }
    }
  }
  
  /* get the lasting time */
  lastingTime = hw_timerConvert(lastingTime.realSecs);
  
  ENABLE_ALL_INTERRUPTS();
}

/*
 *
 * @ function name	        - api_dataHandler 
 * 
 * @ brief			- data handler
 *
 * @ date			- 2017.7.31
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void api_dataHandler( void )
{
  /* status acquire temp varibles */
  static uint8 statusStableCount;
  static uint16 previousCode;
  uint8 statusPreviousTemp;
  static uint8 statusPrevious;
  
  /* height acquire temp varibles */
  static int16 heightDiffer;
  static int16 previousHeight;
  
  /* status stablization process */
  if (statusPrevious != peskData.status)
  {
    if (statusStableCount < STAUTS_STABLE_COUNT_MAX)
    {
      statusStableCount++;
    }
    else
    {
      // set a event that the pesk status has changed!
      statusCurrent = peskData.status;
      statusPreviousTemp = statusPrevious;
      statusPrevious = statusCurrent;
      statusStableCount = 0;
      /* if the current display is not in menu mode */
      if (!menuInfo.active)
      {
        setStaticDisplay();
      }
    }
  }
  else
  {
    statusStableCount = 0;
  }
  
  /* validate the height informations */
  if (NORMAL == statusCurrent)
  {
    if ( (peskData.info != CANCEL_SUCCESS_SIGN) &&
         (peskData.info != MAX_SUCCESS_SIGN) &&
         (peskData.info != MIN_SUCCESS_SIGN) )
    {
      peskData.height = peskData.info;
    }
    
    if (peskData.height != previousHeight)
    {
      heightDiffer = ((int16)peskData.height - previousHeight);
      if (ABS(heightDiffer) < HEIGHTDIFFER_MAX
          && previousHeight != 0)
      {
        peskData.currentHeight = peskData.height;
        
        /* set the height value change event */
        if (!menuInfo.active)
        {
          setDisplayEvent(HEIGHT_VALUE_CHANGE_EVT);
        }
      }
      else if (0 == previousHeight || RST == statusPreviousTemp)
      {
        peskData.currentHeight = peskData.height;
        
        /* set the height value change event */
        if (!menuInfo.active)
        {
          setDisplayEvent(HEIGHT_VALUE_CHANGE_EVT);
        }
      }
      else
      {
        // do nothing
      }
      previousHeight = peskData.height;
    }
  }
  else if (ERROR == statusCurrent)
  {
    peskData.code = peskData.info;
    if (peskData.code != previousCode)
    {
      if (!menuInfo.active)
      {
        if (peskData.code == 0x0010)
        {
          // TODO H01 display
        }
        else
        {
          setDisplayEvent(ERROR_DISPLAY_EVT);
          setDisplayEvent(ERROR_CODE_CHANGE_EVT);
        }
      }
      previousCode = peskData.code;
    }
  }
  else if (RST == statusCurrent)
  {
    // do nothing
  }
  else if (SAVE == statusCurrent)
  {
    if (SAVE == peskData.status)
    {
      peskData.code = peskData.info;
    }
    if (peskData.code != previousCode)
    {
      if (!menuInfo.active)
      {
        setDisplayEvent(SAVE_CODE_CHANGE_EVT);
      }
      previousCode = peskData.code;
    }
  }
  else
  {
    // do nothing
  }
}

/*
 *
 * @ function name	        - cb_dataHandler 
 * 
 * @ brief			- uart data receiving handler
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
void cb_dataHandler(uint8 port, uint8 *data)
{
  if ( (data[0] == 0x01) && (data[1] == 0x01) && (data[2] == 0x01) || 
       (data[0] == 0x01) && (data[1] == 0x01) && (data[2] == 0x00) && (data[3] != 0x00) )
  {
    // keep the information unchanged
  }
  else if (data[0] == 0x01)
  {
    peskData.status = data[1];
    peskData.info_L = data[3];
    peskData.info_H = data[2];
  }
  else
  {
    // do nothing
  }
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/

void api_setInternalEvent(uint16 event)
{
  if (enableEventListener)
  {
    eventInternal = event;
  }
}

void api_clrInternalEvent()
{
  eventInternal = EVENT_KEY_NO_EVT;
}

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
  /* set the port to receive key command */
  SHIFT_PORT_KEY();
  
  /* key press features timer update */
  internalTimer_update();
  
  /* get the current port status */
  hw_keyPoll();
  
  /* get the key event */
  keyLogic();
  
  /* handle the key event */
  keyEventHandler();
}

void api_resetTimer( void )
{
  startTimer(&internalTimer);
}