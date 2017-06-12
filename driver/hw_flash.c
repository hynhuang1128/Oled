/*==========
 * INCLUDES
 ===========*/
#include "hw_flash.h"

/*=================
 * GLOBAL FUNCTIONS
 ==================*/

/**************************************************************************************************
 * @fn          hw_flashRead
 *
 * @brief       This function reads 'cnt' bytes from the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number.
 * @param       offset - A valid offset into the page.
 * @param       buf - A valid buffer space at least as big as the 'cnt' parameter.
 * @param       cnt - A valid number of bytes to read.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void hw_flashRead(uint8 pg, uint16 offset, uint8 *buf, uint16 cnt)
{
  // Calculate the offset into the containing flash bank as it gets mapped into XDATA.
  uint8 *ptr = (uint8 *)(offset + FLASH_PAGE_MAP) +
               ((pg % FLASH_PAGE_PER_BANK) * FLASH_PAGE_SIZE);
  uint8 memctr = MEMCTR;  // Save to restore.

  pg /= FLASH_PAGE_PER_BANK;  // Calculate the flash bank from the flash page.

  // Calculate and map the containing flash bank into XDATA.
  MEMCTR = (MEMCTR & 0xF8) | pg;

  while (cnt--)
  {
    *buf++ = *ptr++;
  }

  MEMCTR = memctr;
}
   
/**************************************************************************************************
 * @fn          hw_flashWrite
 *
 * @brief       This function writes 'cnt' bytes to the internal flash.
 *
 * input parameters
 *
 * @param       addr - Valid HAL flash write address: actual addr / 4 and quad-aligned.
 * @param       buf - Valid buffer space at least as big as 'cnt' X 4.
 * @param       cnt - Number of 4-byte blocks to write.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void hw_flashWrite(uint16 addr, uint8 *buf, uint16 cnt)
{
  DMADesc_t *ch = &dmaCh0;

  DMA_SET_SOURCE(ch, buf);
  DMA_SET_DEST(ch, &FWDATA);
  DMA_SET_VLEN(ch, DMA_VLEN_USE_LEN);
  DMA_SET_LEN(ch, (cnt * FLASH_WORD_SIZE));
  DMA_SET_WORD_SIZE(ch, DMA_WORDSIZE_BYTE);
  DMA_SET_TRIG_MODE(ch, DMA_TMODE_SINGLE);
  DMA_SET_TRIG_SRC(ch, DMA_TRIG_FLASH);
  DMA_SET_SRC_INC(ch, DMA_SRCINC_1);
  DMA_SET_DST_INC(ch, DMA_DSTINC_0);
  // The DMA is to be polled and shall not issue an IRQ upon completion.
  DMA_SET_IRQ(ch, DMA_IRQMASK_DISABLE);
  DMA_SET_M8( ch, DMA_M8_USE_8_BITS);
  DMA_SET_PRIORITY(ch, DMA_PRI_HIGH);
  DMA_CLEAR_IRQ(NV_DMA_CH);
  DMA_ARM_CH(NV_DMA_CH);

  FADDRL = (uint8)addr;
  FADDRH = (uint8)(addr >> 8);
  FCTL |= 0x02;         // Trigger the DMA writes.
  while (FCTL & 0x80);  // Wait until writing is done.
}

/**************************************************************************************************
 * @fn          hw_flashErase
 *
 * @brief       This function erases the specified page of the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number to erase.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void hw_flashErase(uint8 pg)
{
  FADDRH = pg * (FLASH_PAGE_SIZE / FLASH_WORD_SIZE / 256);
  FCTL |= 0x01;
}