#ifndef _HW_TYPE_H
#define _HW_TYPE_H

/*========
 * MACROS
 =========*/
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
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;
typedef enum bStatus
{
  false,
  true,
} bool;

#endif