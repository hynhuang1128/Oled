#ifndef _API_MENU_H
#define _API_MENU_H

/*==========
 * INCLUDES
 ===========*/
#include "hw_pesk.h"
#include "hw_type.h"
#include "main.h"

/*========
 * MACROS
 =========*/

/* main menu index */
#define MENU_INDEX_TOGGLEUNIT           0
#define MENU_INDEX_SETMIN               1
#define MENU_INDEX_SETMAX               2
#define MENU_INDEX_CLRLIMIT             3
   
/* status hint sign */
#define STATUS_HINT_SUCCESS             0
#define STATUS_HINT_FAIL                1
#define STATUS_HINT_CLEARING            2
#define STATUS_HINT_SETTING             3
   
/* toggle unit sub menu index */
#define MENU_INDEX_TOGGLEUNIT_EXEC      0
   
/* menu end item macro */
#define MENU_ITEM_END \
  { \
    -1, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
  }
   
/*===========
 * CONSTANT
 ============*/

/* menu total count */
#define MENU_TOTAL_COUNT                5
   
/* menu level */
#define MENU_LEVEL_MAIN                 0
#define MENU_LEVEL_SUB0                 1
#define MENU_LEVEL_SUB1                 2

/* menu events */
#define MENU_NONE_EVENT                 0
#define MENU_UP_EVENT                   1
#define MENU_DOWN_EVENT                 2
#define MENU_ENTER_EVENT                3
#define MENU_EXIT_EVENT                 4

/* menu operation current status */
#define MENU_TASK_STOP                  0
#define MENU_TASK_PROCESSING            1
#define MENU_TASK_DONE                  2
#define MENU_TASK_START                 3
#define MENU_TASK_INIT                  4

/* menu display blackout related */
#define MENU_BLACK_OUT_MAX_TIME         50
#define MENU_BLACK_OUT_STOP             0
#define MENU_BLACK_OUT_START            1            
#define MENU_TIME_MAX                   50

/*==========
 * TYPEDEFS
 ===========*/

typedef void (*eventHandler_t)( void );

typedef struct menuItems
{
  int8 level;
  eventHandler_t initial;
  eventHandler_t start;
  eventHandler_t processing;
  eventHandler_t done;
  struct menuItems *parent;
  struct menuItems *child;
} menuItem_t;

typedef struct menuInfos
{
  bool active;
  uint8 currentIndex;
  uint8 currentLevel;
  uint8 indexCount;
  eventHandler_t executing;
} menuInfo_t;

typedef struct menuEvent
{
  uint32 eventId;
  uint8 status;
} menuEvent_t;

typedef struct timeOut
{
  uint8 state;
  uint16 value;
} menuTimeout_t;

/*======================
 * VARIBLES DECLARATION
 =======================*/

static menuItem_t mainMenuItems[];

static menuItem_t subMenuToggleItems[];

extern menuInfo_t menuInfo;

extern bool isInit;
/*=============
 * DECLARATION
 ==============*/

/* menu level change function */
   
void menuLevelAscend( void );

void menuLevelDescend( void );
   
/* menu event process */

void menu_eventProcess( void );

/* menu operation related */

void menuInit( void );

static void menuProcessDown( void );

static void menuProcessUp( void );

static void menuProcessEnter( void );

static void menuProcessExit( void );

/* modify status api */

void menu_setStatus( uint8 status );

void menu_setTask( uint8 taskIndex );

void menu_clrTask( void );

/*=================
 * EXTERN FUNCTION
 ==================*/

/* clear limit related */

void startClearLimit( void );
 
void doneClearLimit( void );
 
void processingClearLimit( void );
 
void initClearLimit( void );

/* set max related */

void startSetMax( void );
 
void doneSetMax( void );
 
void processingSetMax( void );
 
void initSetMax( void );

/* set min related */

void startSetMin( void );
 
void doneSetMin( void );
 
void processingSetMin( void );
 
void initSetMin( void );

/* toggle unit related */

void startToggleUnit( void );
 
void doneToggleUnit( void );
 
void processingToggleUnit( void );
 
void initToggleUnit( void );

/* blackout timer start */

void timerCountStart( void );

/* blackout timer stop */

void timerCountStop( void );

#endif