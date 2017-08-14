/*==========
 * INCLUDES
 ===========*/
#include "utils_queue.h"

/*===================
 * PUBLIC FUNCTIONS
 ===================*/

/*
 *
 * @ function name	        - util_queueInit 
 * 
 * @ brief			- fifo initialize
 *
 * @ date			- 2017.7.17
 *
 * @ author			- Eric Huang
 *
 * @ param			- fifo type data
 *
 * @ return			- none
 *
 */
void util_queueInit(queue_t *fifo)
{
  fifo->head = 0;
  fifo->tail = FIFO_MAX_COUNT - 1;

  for(int i = 0; i < FIFO_MAX_COUNT; i++)
  {
    fifo->data[i] = 0;
  }

  fifo->dataCount = 0;
}

/*
 *
 * @ function name	        - util_queueEmpty 
 * 
 * @ brief			- whether the current fifo is empty
 *
 * @ date			- 2017.7.18
 *
 * @ author			- Eric Huang
 *
 * @ param			- fifo type data
 *
 * @ return			- true, otherwise false
 *
 */
bool util_queueEmpty(queue_t *fifo)
{
  if (fifo->dataCount == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 *
 * @ function name	        - util_queueFull 
 * 
 * @ brief			- whether the current fifo is full
 *
 * @ date			- 2017.7.18
 *
 * @ author			- Eric Huang
 *
 * @ param			- fifo type data
 *
 * @ return			- true, otherwise false
 *
 */
bool util_queueFull(queue_t *fifo)
{
  if (fifo->dataCount >= FIFO_MAX_COUNT)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 *
 * @ function name	        - util_enQueue 
 * 
 * @ brief			- if the fifo is not full, enqueue a new data
 *
 * @ date			- 2017.7.18
 *
 * @ author			- Eric Huang
 *
 * @ param			- fifo type data
 *                              - the new data
 *
 * @ return			- true, otherwise false
 *
 */
bool util_enQueue(queue_t *fifo, uint8 elem)
{
  if (!util_queueFull(fifo))
  {
    fifo->tail++;
    fifo->tail = fifo->tail % FIFO_MAX_COUNT;
    fifo->data[fifo->tail] = elem;
    fifo->dataCount++;
    return true;
  }
  else
  {
    return false;
  }
}

/*
 *
 * @ function name	        - util_deQueue 
 * 
 * @ brief			- if the fifo is not empty, dequeue an existed data
 *
 * @ date			- 2017.7.18
 *
 * @ author			- Eric Huang
 *
 * @ param			- fifo type data
 *                              - the pointer of dequeue data
 *
 * @ return			- true, otherwise false
 *
 */
bool util_deQueue(queue_t *fifo, uint8 *elem)
{
  if (!util_queueEmpty(fifo))
  {
    *elem = fifo->data[fifo->head];
    fifo->head++;
    fifo->head = fifo->head % FIFO_MAX_COUNT;
    fifo->dataCount--;
    return true;
  }
  else
  {
    return false;
  }
}
