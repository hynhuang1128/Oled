/*==========
 * INCLUDES
 ===========*/

#include "api_disp.h"
#include "hw_oled.h"

/*==================
 * GLOBAL VARIBLES
 ==================*/

displayEvent_t displayEvt;
displayEvent_t currentStaticDisplay;

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

static displayEventHandler_t displayStaticEventArray[] = 
{
  normalDisplay_static,
  saveDisplay_static,
  errorDisplay_static,
  rstDisplay_static,
  menuDisplay_static,
  statusDisplay_static,    
  sub0Display_static,// submenu display
  haltDisplay_static,
  h01Display_static,
};

static displayEventHandler_t displayDynamicEventArray[] = 
{
  displayNum,
  displayControl,
  displayUnit,
  displaySaveCode,
  displayErrorCode,
  displayHaltInfo,
  displayMainMenuInfo,
  displayStatusCode,
  displaySub0,
};

static uint8 staticTaskCnt = sizeof(displayStaticEventArray) / sizeof(displayStaticEventArray[0]);
static uint8 dynamicTaskCnt = sizeof(displayDynamicEventArray) / sizeof(displayDynamicEventArray[0]);

/*====================
 * INTERNAL FUNCTIONS
 =====================*/

static void displayEventHandler( void )
{
  uint8 taskNum = 0;
  uint32 tempEvent = NO_DISPLAY_EVENT;
  
  tempEvent = displayEvt & STATIC_DISPLAY_MASK;
      
  if (tempEvent)
  {
    while (taskNum < staticTaskCnt)
    {
      if ( (tempEvent >> taskNum) & 0x00000001 ) break;
      taskNum++;
    }
    
    if (taskNum < staticTaskCnt)
    {
      /* call the function */
      displayStaticEventArray[taskNum]();
  
      /* clear the event flag */
      clearDisplayEvent(tempEvent);
    }
  }
  
  tempEvent = ((displayEvt & (~STATIC_DISPLAY_MASK)) >> DYNAMIC_DISPLAY_OFFSET);
  
  if (tempEvent)
  {
    taskNum = 0;
    
    while (taskNum < dynamicTaskCnt)
    {
      if ( (tempEvent >> taskNum) & 0x00000001 ) break;
      taskNum++;
    }
    
    if (taskNum < dynamicTaskCnt)
    {
      /* call the function */
      displayDynamicEventArray[taskNum]();
  
      /* clear the event flag */
      clearDisplayEvent(tempEvent << DYNAMIC_DISPLAY_OFFSET);
    }
  }
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/
   
/*
 *
 * @ function name	        - displayScene 
 * 
 * @ brief			- display event poll handler
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void displayScene( void )
{
  /* if initialize haven't complete */
  if (!isInit)
  {
    //clearDisplayEvent(MENU_DISPLAY_FULL_EVT);
    return;
  }
  
  /* shift the port to the lcd function */
  SHIFT_PORT_LCD();
  
  /* event handler */
  displayEventHandler();
  
  /* reset the port prepare to receive the key press event */
  CLOSE_PORT_LCD();
}

/*
 *
 * @ function name	        - setDisplayEvent 
 * 
 * @ brief			- Emit a display event to the handler
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- event         displayEvent_t
 *                                              indicates the emitted event
 *
 * @ return			- none
 *
 */
void setDisplayEvent( displayEvent_t event )
{
  if (event & (~STATIC_DISPLAY_MASK))
  {
    displayEvt &= STATIC_DISPLAY_MASK;
    displayEvt |= event & ~STATIC_DISPLAY_MASK;
  }
  
  if ( (event & (STATIC_DISPLAY_MASK)) &&
       ((event & (STATIC_DISPLAY_MASK)) != currentStaticDisplay) )
  {
    displayEvt &= NO_DISPLAY_EVENT;
    displayEvt |= event & STATIC_DISPLAY_MASK;
    currentStaticDisplay = event & STATIC_DISPLAY_MASK;
  }
}

/*
 *
 * @ function name	        - clearDisplayEvent 
 * 
 * @ brief			- clear a display event
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- event         displayEvent_t
 *                                              indicates the emitted event
 *
 * @ return			- none
 *
 */
void clearDisplayEvent( displayEvent_t event )
{
  displayEvt &= ~event;
}