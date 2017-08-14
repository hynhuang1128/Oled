#ifndef _HW_UART_H
#define _HW_UART_H
/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"
#include "hw_timer.h"
#include "main.h"

/*========
 * MACROS
 =========*/
#define ENABLE_RECEIVE_INT(x)   (URX##x##IE = 1)
#define DISABLE_RECEIVE_INT(x)  (URX##x##IE = 0)
#define UART0_RX_SIZE           4
#define UART1_RX_SIZE           4

#define UART0_TIMEOUT           10

/*===========
 * ENUM TYPES
 ============*/
typedef enum baudRate
{
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200,
} baudType_t;

typedef enum parity
{
  NONE,
  ODD,
  EVEN,
} parity_t;

/*=============
 * TYPE DEFINES
 ==============*/
typedef void (*uartCBack_t) (uint8 port, uint8 *data);

typedef struct uartConfig
{
  baudType_t baudRate;
  uint8 port;
  uartCBack_t cbs;
} uartConfig_t;

typedef struct uartData
{
  uint8 recvBuf[UART0_RX_SIZE];
  uint8 recvCount;
  uint32 recvTimeOut;
  bool recvComplete;
} uartData_t;

/*=================
 * GLOBAL FUNCTIONS
 ==================*/
void hw_uartInit(uartConfig_t cfg);
void hw_uartPoll(void);
void hw_uartClearBuf(uint8 port);

#endif