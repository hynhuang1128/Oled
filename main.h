#ifndef _MAIN_H
#define _MAIN_H
  
/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_oled.h"
#include "hw_timer.h"
#include "hw_uart.h"
#include "hw_pesk.h"
#include "hw_flash.h"
#include "api_nv.h"
#include "api_disp.h"
#include "api_control.h"
#include "api_menu.h"
   
/*==========
 *  MACROS
 ===========*/

/* QRcode image coordinate */
#define IMAGE_X_BEGIN           8
#define IMAGE_Y_BEGIN           2
#define IMAGE_WIDTH             116
#define IMAGE_HEIGHT            4
   
/* poll time period(ms) */
#define PERIOD_UART0_POLL       11
#define PERIOD_DISPLAY          79
#define PERIOD_KEY_POLL         25
#define PERIOD_DATAHANDLER      31
#define PERIOD_GETDIR           91
#define PERIOD_MENU_POLL        100
#define INIT_TIME_ELEMENT       50
   
/* Cache Prefetch Control */
#define PREFETCH_ENABLE()       \
do                              \
{                               \
  FCTL = 0x08;                  \
} while(0)

#define PREFETCH_DISABLE()      \
do                              \
{                               \
  FCTL = 0x04;                  \
} while(0)

/* Set event macros */
#define SET_EVENT_ACTIVE(x)     (sys_event |= (x))

/*===========
 * CONSTANTS
 ============*/
#define HEIGHTDIFFER_MAX        5
#define STATUS_DELAY_COUNT(x)   ((x) / PERIOD_UART0_POLL)
#define CONTROL_DELAY_COUNT(x)  ((x) / PERIOD_KEY_POLL)

/* event id */
#define SYS_KEY_CHANGE_EVT              0x0001
#define SYS_DISP_CHANGE_EVT             0x0002
#define SYS_DISP_EVT                    0x0004
#define SYS_CMD_EVT                     0x0008

/* unit non-volatile storage */
#define UNIT_NV_ID                      0x0000
#define UNIT_NV_ID_LEN                  1
   
/*=============
 * TYPE DEFINES
 ==============*/
typedef void (*periodCBack_t) (void);

/*=================
 *   DECLARATION
 ==================*/
void cb_dataHandler(uint8 port, uint8 *data);


#endif