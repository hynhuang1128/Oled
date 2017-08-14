#ifndef _API_CONTROL_H
#define _API_CONTROL_H

/*==========
 * INCLUDES
 ===========*/
#include "hw_pesk.h"
#include "hw_type.h"
#include "main.h"

/*==========
 * TYPEDEFS
 ===========*/

typedef struct _internalTimer
{
  uint8 state;
  uint32 timerValue;
} internalTimer_t;

typedef struct _special
{
  uint8 mode;
  uint8 status;
} special_t;

typedef uint8 fStatus;

typedef void (*internalEventHandler_t)( void );

/*============
 * ENUM TYPES
 =============*/

typedef enum unitTypes
{
  IMPERIAL,
  METRIC,
} unit_t;

/*==========
 * CONSTANT
 ===========*/
   
/* internal timer flag */
#define INTERNAL_TIMER_START            0x01
#define INTERNAL_TIMER_STOP             0x02
#define INTERNAL_TIMER_PAUSE            0x03

/* limit setting related macros */
#define LIMIT_OPERATION_TIME_STEP0      0
#define LIMIT_OPERATION_TIME_STEP1      2
#define LIMIT_OPERATION_TIME_STEP2      7
#define LIMIT_OPERATION_TIME_STEP3      12
#define LIMIT_OPERATION_TIME_STEP4      17
#define LIMIT_OPERATION_TIME_STEP5      21
#define LIMIT_OPERATION_TIME_STEP6      71
#define LIMIT_OPERATION_TIME_STEP7      73
#define LIMIT_OPERATION_TIME_STEP8      76
#define LIMIT_OPERATION_TIME_INTERVAL   3
#define LIMIT_CANCEL_TIMEOUT_COUNT      9
#define LIMIT_MAXMIN_TIMEOUT_COUNT      5
   
/* setting signs */
#define MAX_SUCCESS_SIGN                9999
#define MIN_SUCCESS_SIGN                0000
#define CANCEL_SUCCESS_SIGN             5555

/* unit alter time out */
#define UNIT_TIMEOUT                    1500

/* set button released delay time */
#define STOP_SET_SETTING_TIME           800
#define STOP_SET_STOP_TIME              1200
#define STOP_SET_MOVING_TIME            1400

/* internal timer interval */
#define INTERNAL_TIMER_INTERVAL         100
   
/* internal timer timeout */
#define INTERNAL_TIMER_TIMEOUT          200    // 1200 * 0.1 = 120(sec) = 2(min)
#define USER_REMINDING_TIME             60
   
/* internal events */
// button press event
#define EVENT_KEY_UP_ONPRESS            0x0001
#define EVENT_KEY_DOWN_ONPRESS          0x0002
#define EVENT_KEY_SET_ONPRESS           0x0004
#define EVENT_KEY_SETTING_ONPRESS       0x0008
// button release event
#define EVENT_KEY_UP_ONRELEASE          0x0010
#define EVENT_KEY_DOWN_ONRELEASE        0x0020
#define EVENT_KEY_SET_ONRELEASE         0x0040
#define EVENT_KEY_SETTING_ONRELEASE     0x0080
// menu emit event
#define EVENT_TOGGLE_UNIT               0x0100
#define EVENT_SET_MIN_LIMIT             0x0200
#define EVENT_SET_MAX_LIMIT             0x0400
#define EVENT_CLEAR_LIMIT               0x0800
// motor action event
#define EVENT_MOTOR_MOVE                0x1000
// no event has been triggered
#define EVENT_KEY_NO_EVT                0x0000

/* port output lasting time */
#define PORT_OUTPUT_LASTING_TIME        1       // 1 * 0.1 = 0.1(sec) = 100ms

/* status stablization counts */
#define STAUTS_STABLE_COUNT_MAX         5

/* vibaration interval */
#define MOTOR_INTERVAL                  8
#define MOTOR_ON_TIME                   0
#define MOTOR_OFF_TIME                  6

/*========
 * MACROS
 =========*/
   
#define DONE            0x01
#define PROCESSING      0x00

#define MOTOR_OSCILLATOR                P2_0
#define MOTOR_ACTION_TIME(x)            ((x) * PERIOD_KEY_POLL)
   
/*=============
 * DECLARATION
 ==============*/

/*********************
 * public declaration
 *********************/
void api_setInternalEvent(uint16 event);

void api_clrInternalEvent();

void api_keyPoll( void );

void api_dataHandler( void );

void api_getDirection( void );

void cb_dataHandler(uint8 port, uint8 *data);

void api_resetTimer( void );

void setStaticDisplay( void );

/***********************
 * internal declaration
 ***********************/
   
static void toggleUnit_precessEvent(void);

static void upPressed_processEvent(void);

static void downPressed_processEvent(void);

static void setPressed_processEvent(void);

static void settingPressed_processEvent(void);

static void upReleased_processEvent(void);

static void downReleased_processEvent(void);

static void setReleased_processEvent(void);

static void settingReleased_processEvent(void);

static void setMinLimit_processEvent(void);

static void setMaxLimit_processEvent(void);

static void clearLimit_processEvent(void);

static void motorMove_processEvent(void);

static fStatus setOutput(uint32 time, uint8 outputData);

#endif