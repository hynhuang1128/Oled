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
#define KEY_IDLE                        0xf0
#define KEY_UP                          0xd0
#define KEY_DOWN                        0x70
#define KEY_SET1                        0x50
#define KEY_SET2                        0xb0
#define KEY_SET3                        0x30
#define KEY_SET4                        0x90
#define KEY_SETTING                     0xe0

/* Handset Commands */
#define CMD_UP                          0x04
#define CMD_DOWN                        0x08
#define CMD_STOP                        0x00
#define CMD_SET1                        0x0c
#define CMD_SET2                        0x02
#define CMD_SET3                        0x0a
#define CMD_SET4                        0x06
#define CMD_SETTING                     0x01

#define DEBOUNCING_TIME                 100
   
/* Key initialize */
#define HW_KEY_INIT() \
do \
{ \
  P0 = 0x00; \
  P0SEL = 0x00; \
  P0DIR = 0x0f; \
} while(0)

/*===========
 * ENUM TYPES
 ============*/
typedef enum userPosture
{
  SIT,
  STAND,
} posture_t;

/*=============
 * TYPE DEFINES
 ==============*/
typedef struct peskData
{
  uint16 height;
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