/*==========
 * INCLUDES
 ===========*/

#include "api_menu.h"

/*==================
 * GLOBAL VARIBLES
 ==================*/

menuInfo_t menuInfo;

menuEvent_t menuEvent =
{
  MENU_NONE_EVENT,
  MENU_TASK_STOP,
};

eventHandler_t taskArray[] =
{
  menu_clrTask,
  menuProcessUp,
  menuProcessDown,
  menuProcessEnter,
  menuProcessExit,
};

menuItem_t mainMenuItems[] =
{
  /* menu_toggleUnit */
  {
    MENU_LEVEL_MAIN,
    initToggleUnit,
    startToggleUnit,
    processingToggleUnit,
    doneToggleUnit,
    NULL,
    NULL,
  },
  
  /* menu_setMin */
  {
    MENU_LEVEL_MAIN,
    initSetMin,
    startSetMin,
    processingSetMin,
    doneSetMin,
    NULL,
    NULL,
  },
  
  /* menu_setMax */
  {
    MENU_LEVEL_MAIN,
    initSetMax,
    startSetMax,
    processingSetMax,
    doneSetMax,
    NULL,
    NULL,
  },
  
  /* menu_clrLimit */
  {
    MENU_LEVEL_MAIN,
    initClearLimit,
    startClearLimit,
    processingClearLimit,
    doneClearLimit,
    NULL,
    NULL,
  },
  
  MENU_ITEM_END,
};

menuItem_t subMenuToggleItems[] =
{
  /* subMenu_toggleUnit */
  {
    MENU_LEVEL_SUB0,
    0,
    0,
    0,
    0,
    mainMenuItems,
    NULL,
  },
  
  MENU_ITEM_END,
};

bool isInit;

/*===================
 * EXTERNAL VARIBLES
 ===================*/



/*===================
 * INTERNAL VARIBLES
 ====================*/

static menuItem_t *currentMenuItem;

static menuEvent_t menuEvent;

static menuTimeout_t timeout;

/*====================
 * INTERNAL FUNCTIONS
 =====================*/

/* internal menu status modify function */
static void menu_internalSetStatus( uint8 status )
{
  menuEvent.status = status;
}

/* get current level's menu items count */
static uint32 getItemSum(menuItem_t *menu)
{
  uint32 ret = 0;
  
  while( menu->level != -1 )
  {
    menu++;
    ret++;
  }
  
  return ret;
}

/* timeout to exit menu display */
static void timerCount( void )
{
  if (timeout.state == MENU_BLACK_OUT_START)
  {
    if (timeout.value < MENU_BLACK_OUT_MAX_TIME)
    {
      timeout.value++;
    }
    else
    {
      menu_setTask(MENU_EXIT_EVENT);
      timeout.value = 0;
    }
  }
  else
  {
    timeout.value = 0;
  }
}

/*==================
 * GLOBAL FUNCTIONS
 ===================*/

void menuInit( void )
{
  menuInfo.active = true;
  currentMenuItem = mainMenuItems;
  menuInfo.currentLevel = MENU_LEVEL_MAIN;
  menuInfo.currentIndex = MENU_INDEX_TOGGLEUNIT;
  menuInfo.indexCount = getItemSum(currentMenuItem);
  setDisplayEvent(MENU_DISPLAY_EVT);
}

/*
 *
 * @ function name	        - menu_eventProcess 
 * 
 * @ brief			- the menu events process task
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void menu_eventProcess( void )
{
  if (!menuInfo.active)
  {
    return;
  }
  else
  {
    if (timeout.state != MENU_BLACK_OUT_START)
    {
      timerCountStart();
    }
    
    timerCount();
  }
  
  if (menuEvent.status != MENU_TASK_STOP)
  {
    switch (menuEvent.status)
    {
      case MENU_TASK_INIT:
        currentMenuItem[menuInfo.currentIndex].initial();
        break;
        
      case MENU_TASK_PROCESSING:
        currentMenuItem[menuInfo.currentIndex].processing();
        break;
        
      case MENU_TASK_DONE:
        currentMenuItem[menuInfo.currentIndex].done();
        break;
        
      case MENU_TASK_START:
        timerCountStart();
        currentMenuItem[menuInfo.currentIndex].start();
        break;
        
      default:
        // should not get here!
        break;
    }
  }
  else
  {
    taskArray[menuEvent.eventId]();
    return;
  }
  
  if (menuEvent.eventId != MENU_NONE_EVENT)
  {
    menu_clrTask();
  }
  
}

/*
 *
 * @ function name	        - menu_setTask 
 * 
 * @ brief			- api for other layers to set event
 *
 * @ date			- 2017.8.8
 *
 * @ author			- Eric Huang
 *
 * @ param			- taskIndex             the task ready to set
 *
 * @ return			- none
 *
 */
void menu_setTask( uint8 taskIndex )
{
  if (!menuEvent.eventId)
  {
    menuEvent.eventId = taskIndex;
  }
  else
  {
    return;
  }
}

/*
 *
 * @ function name	        - menu_clrTask 
 * 
 * @ brief			- api for other layers to clear event
 *
 * @ date			- 2017.8.8
 *
 * @ author			- Eric Huang
 *
 * @ param			- taskIndex             the task ready to clear
 *
 * @ return			- none
 *
 */
void menu_clrTask( void )
{
  menuEvent.eventId = 0;
}

/*
 *
 * @ function name	        - menu_setStatus 
 * 
 * @ brief			- api for other layers to modify the current menu status
 *
 * @ date			- 2017.8.8
 *
 * @ author			- Eric Huang
 *
 * @ param			- status        the new status
 *
 * @ return			- none
 *
 */
void menu_setStatus( uint8 status )
{
  menuEvent.status = status;
}

/*
 *
 * @ function name	        - menuProcessDown 
 * 
 * @ brief			- api for down key pressed when the menu status is stop
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
static void menuProcessDown( void )
{
  if (menuInfo.currentIndex == menuInfo.indexCount - 1)
  {
    menu_internalSetStatus(MENU_TASK_INIT);
    return;
  }
  
  menuInfo.currentIndex++;
  
  menu_internalSetStatus(MENU_TASK_INIT);
  
  timerCountStart();
}

/*
 *
 * @ function name	        - menuProcessUp 
 * 
 * @ brief			- api for up key pressed when the menu status is stop
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
static void menuProcessUp( void )
{
  if (menuInfo.currentIndex == 0)
  {
    menu_internalSetStatus(MENU_TASK_INIT);
    return;
  }
  
  menuInfo.currentIndex--;
  
  menu_internalSetStatus(MENU_TASK_INIT);
  
  timerCountStart();
}

/*
 *
 * @ function name	        - menuProcessEnter 
 * 
 * @ brief			- api for enter key pressed when the menu status is stop
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
static void menuProcessEnter( void )
{
  menu_internalSetStatus(MENU_TASK_START);
  
  timerCountStart();
}

/*
 *
 * @ function name	        - menuProcessExit 
 * 
 * @ brief			- api for exit key pressed when the menu status is stop
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
static void menuProcessExit( void )
{
  timerCountStop();
  
  menuLevelDescend();
}

/*
 *
 * @ function name	        - menuLevelAscend 
 * 
 * @ brief			- api for menu level ascend
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void menuLevelAscend( void )
{
  if (currentMenuItem->child != NULL)
  {
    currentMenuItem = currentMenuItem->child;
    menuInfo.currentIndex = 0;
  }
  else
  {
    menuInfo.active = false;
    setStaticDisplay();
    return;
  }
  
  menuInfo.currentLevel++;
  
  menuInfo.indexCount = getItemSum(currentMenuItem);
}

/*
 *
 * @ function name	        - menuLevelDescend 
 * 
 * @ brief			- api for menu level descend
 *
 * @ date			- 2017.8.9
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void menuLevelDescend( void )
{
  if (currentMenuItem->parent != NULL)
  {
    currentMenuItem = currentMenuItem->parent;
    menuInfo.currentIndex = 0;
  }
  else
  {
    menuInfo.active = false;
    setStaticDisplay();
    menu_clrTask();
    return;
  }
  
  menuInfo.currentLevel--;
  
  menuInfo.indexCount = getItemSum(currentMenuItem);
}

/* blackout timer start */
void timerCountStart( void )
{
  timeout.value = 0;
  timeout.state = MENU_BLACK_OUT_START;
}

/* blackout timer stop */
void timerCountStop( void )
{
  timeout.value = 0;
  timeout.state = MENU_BLACK_OUT_STOP;
}