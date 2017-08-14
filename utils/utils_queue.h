/*==========
 * INCLUDES
 ===========*/
#include "hw_type.h"
#include "main.h"

/*==========
 *  MACROS
 ===========*/


/*===========
 * CONSTANT
 ============*/

#define FIFO_MAX_COUNT          15

/*=============
 * TYPE DEFINES
 ==============*/

typedef struct _queue
{
  uint8 head;
  uint8 tail;
  uint8 data[FIFO_MAX_COUNT];
  uint8 dataCount;
} queue_t;

/*======================
 * FUNCTION DECLARATION
 =======================*/

void util_queueInit(queue_t *fifo);

bool util_queueEmpty(queue_t *fifo);

bool util_queueFull(queue_t *fifo);

bool util_enQueue(queue_t *fifo, uint8 elem);

bool util_deQueue(queue_t *fifo, uint8 *elem);