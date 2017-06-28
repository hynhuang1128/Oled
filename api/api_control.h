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
  uint8 flag;
  uint32 timerValue;
} internalTimer_t;
   
typedef struct _special
{
  uint8 mode;
  uint8 status;
} special_t;

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
#define TIMER_START_FLAG        0x01
#define TIMER_STOP_FLAG         0x02
#define TIMER_PAUSE_FLAG        0x03

/* special mode */
#define SPECIAL_NONE            0x00
#define SPECIAL_SETTING_MAX     0x01
#define SPECIAL_SETTING_MIN     0x02
#define SPECIAL_SETTING_CANCEL  0x03
#define SPECIAL_TOGGLE_UNIT     0x04

/* special status */
#define SETTING_CANCEL_FAILED   0x00
#define SETTING_CANCEL_PROCESS  0x01
#define SETTING_CANCEL_SUCCESS  0x02
   
#define SETTING_MAX_FAILED      0x00
#define SETTING_MAX_PROCESS     0x01
#define SETTING_MAX_SUCCESS     0x02
   
#define SETTING_MIN_FAILED      0x00
#define SETTING_MIN_PROCESS     0x01
#define SETTING_MIN_SUCCESS     0x02
   
/* setting signs */
#define MAX_SUCCESS_SIGN        9999
#define MIN_SUCCESS_SIGN        0000
#define CANCEL_SUCCESS_SIGN     5555

/* unit alter time out */
#define UNIT_TIMEOUT            1500

/* set button released delay time */
#define STOP_SET_SETTING_TIME   800
#define STOP_SET_STOP_TIME      1200
#define STOP_SET_MOVING_TIME    1400

/*=============
 * DECLARATION
 ==============*/
void api_keyPoll( void );
   
#endif