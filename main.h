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
#define IMAGE_Y_BEGIN           0
#define IMAGE_X_END             128
#define IMAGE_Y_END             8
   
/* poll time period(ms) */
#define PERIOD_UART0_POLL       10
#define PERIOD_DISPLAY          25
#define PERIOD_KEY_POLL         25
#define PERIOD_CMD_POLL         25
   
/*=============
 * TYPE DEFINES
 ==============*/
typedef void (*periodCBack_t) (void);

/*=================
 *   DECLARATION
 ==================*/
void cb_dataHandler(uint8 port, uint8 *data);


#endif