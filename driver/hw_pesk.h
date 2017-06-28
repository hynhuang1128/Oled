#ifndef _HW_PESK_H
#define _HW_PESK_H

/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"
#include "main.h"
#include "codetab.h"
   
/*==========
 *  MACROS
 ===========*/
/* Pesk status macros */
#define NORMAL                          0x01
#define ERROR                           0x02
#define RST                             0x04
#define SAVE                            0x06
      
/* Handset status */
#define KEY_IDLE                        0x3f
#define KEY_UP                          0x3d
#define KEY_DOWN                        0x3e
#define KEY_SETTING                     0x37
#define KEY_SET1                        0x3b
#define KEY_SET2                        0x1f
#define KEY_SET3                        0x2f
#define KEY_SETTING_AND_UP              0x36
#define KEY_SETTING_AND_DOWN            0x35
   
/* Handset Commands */
#define CMD_UP                          0x40
#define CMD_DOWN                        0x80
#define CMD_STOP                        0x00
#define CMD_SET1                        0xc0
#define CMD_SET2                        0x20
#define CMD_SET3                        0xa0
#define CMD_SETTING                     0x10

/* Handset memory bits mask */
#define KEY_SET_MASK                    0x38
   
/* Debounce time */
#define DEBOUNCING_TIME                 50
   
/* Key initialize */
#define HW_KEY_INIT() \
do \
{ \
  P0 = 0x0b; \
  P0SEL &= 0x1d; \
  P0DIR |= 0xf4; \
  P1 = 0xe0; \
  P1SEL &= 0x1f; \
  P1DIR &= 0x1f; \
} while(0)

/* Shift port */
#define SHIFT_PORT_KEY() \
do \
{ \
  P0DIR |= 0xf4; \
  P1DIR &= 0x1f; \
} while(0)

/*===========
 * ENUM TYPES
 ============*/
typedef enum userPosture
{
  SIT,
  STAND,
} posture_t;

typedef enum moveDir
{
  UP,
  DOWN,
  IDLE,
} moveDir_t;

/*=============
 * TYPE DEFINES
 ==============*/
typedef struct peskData
{
  uint16 height;
  uint16 currentHeight;
  uint16 previousHeight;
  uint8 status;
  union
  {
    uint16 info;
    struct
    {
      uint8 info_L;
      uint8 info_H;
    };
  };
  moveDir_t moveDir;
} peskData_t;

typedef struct timeStruct
{
  union
  {
    uint32 timeValue;
    struct
    {
      uint8 time0;
      uint8 time1;
      uint8 time2;
      uint8 time3;
    };
  };
  uint8 hr;
  uint8 min;
  uint8 sec;
} timeData_t;

typedef struct userData
{
  timeData_t lastingTime;
  posture_t posture;
} userData_t;

typedef struct peskCommand
{
  uint8 input;
  uint8 output;
} peskCommand_t;

/*====================
 * FUNCTION DECLATION
 =====================*/
void hw_keyInit(void);
void hw_keyPoll(void);
void hw_cmdCall(void);

#endif