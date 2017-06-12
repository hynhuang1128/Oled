/*==========
 * INCLUDES
 ===========*/

#include "hw_dma.h"

/*=================
 * GLOBAL VARIBLES
 ==================*/

DMADesc_t dmaCh0;

/*=================
 * PUBLIC FUNCTIONS
 ==================*/

/******************************************************************************
 * @fn      HalDMAInit
 *
 * @brief   DMA Interrupt Service Routine
 *
 * @param   None
 *
 * @return  None
 *****************************************************************************/
void dmaInit( void )
{
  DMA_SET_ADDR_DESC( &dmaCh0 );
}