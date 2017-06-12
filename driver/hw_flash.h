#ifndef _HW_FLASH_H
#define _HW_FLASH_H

/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"
#include "hw_dma.h"

/*========
 * MACROS
 =========*/
// Flash is partitioned into 8 banks of 32 KB or 16 pages.
#define FLASH_PAGE_PER_BANK        16

// Flash is constructed of 128 pages of 2 KB.
#define FLASH_PAGE_PHYS            2048

// SNV can use a larger logical page size to accomodate more or bigger items or extend lifetime.
#define FLASH_PAGE_SIZE            FLASH_PAGE_PHYS
#define FLASH_WORD_SIZE            4

// CODE banks get mapped into the XDATA range 8000-FFFF.
#define FLASH_PAGE_MAP             0x8000

/* Critical Vdd Monitoring to prevent flash damage. */

// Vdd/3 / Internal Reference X ENOB --> (Vdd / 3) / 1.15 X 127
#define VDD_2_0  74   // 2.0 V required to safely read/write internal flash.
#define VDD_2_7  100  // 2.7 V required for the Numonyx device.

#define VDD_MIN_RUN      VDD_2_0
#define VDD_MIN_FLASH   (VDD_2_0 + 4)  // 5% margin over minimum to survive a page erase and compaction.
#define VDD_MIN_XNV     (VDD_2_7 + 5)  // 5% margin over minimum to survive a page erase and compaction.

#define NV_DMA_CH                  0

#define TEST_FLASH_ADDR            (uint16)(128 * FLASH_PAGE_PHYS / FLASH_WORD_SIZE)
#define TEST_FLASH_PAGE_SIZE       (FLASH_PAGE_PHYS / FLASH_WORD_SIZE)
   
/*======================
 * FUNCTION DECLARATION
 =======================*/
   
void hw_flashRead(uint8 pg, uint16 offset, uint8 *buf, uint16 cnt);
void hw_flashWrite(uint16 addr, uint8 *buf, uint16 cnt);
void hw_flashErase(uint8 pg);

#endif