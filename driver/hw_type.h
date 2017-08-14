#ifndef _HW_TYPE_H
#define _HW_TYPE_H

/*========
 * MACROS
 =========*/

#define ABS(x)                          ( (x) > 0 ? (x) : -(x) )

#define DISABLE_ALL_INTERRUPTS()       (EA = 0)
#define ENABLE_ALL_INTERRUPTS()        (EA = 1)
#define NULL                           0
   
/*=============
 * TYPE DEFINES
 ==============*/

typedef enum
{
  FAILED,
  SUCCESS,
} bStatus;
   
/* common type defines */
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed long int32;
typedef signed short int16;
typedef signed char int8;
typedef enum bStatus
{
  false,
  true,
} bool;

/*=======
 * UTILS
 ========*/

uint8 num2Char(uint8 x);

void printDebugMsg(uint32 msg, uint8 pos);
#endif