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
   
/*==========
 *  MACROS
 ===========*/
/* QRcode image coordinate */
#define QRCODE_X_BEGIN          0
#define QRCODE_Y_BEGIN          0
#define QRCODE_X_END            64
#define QRCODE_Y_END            8

/* QRcode image coordinate */
#define IMAGE_X_BEGIN           0
#define IMAGE_Y_BEGIN           2
#define IMAGE_X_END             128
#define IMAGE_Y_END             6
   
/* poll time period(ms) */
#define PERIOD_UART0_POLL       11
#define PERIOD_DISPLAY          109
#define PERIOD_KEY_POLL         25
   
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

/*===========
 * CONSTANTS
 ============*/
#define HEIGHTDIFFER_MAX        5
#define STATUS_DELAY_COUNT(x)   ((x) / PERIOD_UART0_POLL)
#define CONTROL_DELAY_COUNT(x)  ((x) / PERIOD_KEY_POLL)

/* event id */
#define SYS_UART_EVT                    0x0001  
#define SYS_KEY_EVT                     0x0002
#define SYS_DISP_EVT                    0x0004
#define SYS_CMD_EVT                     0x0008

/*=============
 * TYPE DEFINES
 ==============*/
typedef void (*periodCBack_t) (void);

/*=================
 *   DECLARATION
 ==================*/
void cb_dataHandler(uint8 port, uint8 *data);


#endif