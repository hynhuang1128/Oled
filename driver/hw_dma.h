#ifndef _HW_DMA_H
#define _HW_DMA_H

/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"

/*========
 * MACROS
 =========*/

/* Set dma address desc */
#define DMA_SET_ADDR_DESC( a )                  \
do                                              \
{                                               \
  DMA0CFGH = (uint8)( (uint16)(a) >> 8 );       \
  DMA0CFGL = (uint8)( (uint16)(a) & 0xFF );     \
} while(0)

/* Arm the dma channel */
#define DMA_ARM_CH( ch )           DMAARM = (0x01 << (ch))

/* Dma operations */
#define DMA_ABORT_CH( ch )         DMAARM = (0x80 | (0x01 << (ch)))
#define DMA_MAN_TRIGGER( ch )      DMAREQ = (0x01 << (ch))
#define DMA_START_CH( ch )         DMA_MAN_TRIGGER( (ch) )

/* Clear the dma irq flag */
#define DMA_CLEAR_IRQ( ch )        DMAIRQ &= ~( 1 << (ch) )

/* Check the dma irq flag */
#define DMA_CHECK_IRQ( ch )       (DMAIRQ & ( 1 << (ch) ))

/* Macro for quickly setting the source address of a DMA structure */
#define DMA_SET_SOURCE( pDesc, src )                    \
do                                                      \
{                                                       \
  pDesc->srcAddrH = (uint8)((uint16)(src) >> 8);        \
  pDesc->srcAddrL = (uint8)((uint16)(src) & 0xFF);      \
} while(0)
    
/* Macro for quickly setting the destination address of a DMA structure */
#define DMA_SET_DEST( pDesc, dst )                      \
do                                                      \
{                                                       \
  pDesc->dstAddrH = (uint8)((uint16)(dst) >> 8);        \
  pDesc->dstAddrL = (uint8)((uint16)(dst) & 0xFF);      \
} while(0)

/* Macro for quickly setting the number of bytes to be transferred by the DMA,
   max length is 0x1FFF. */
#define DMA_SET_LEN( pDesc, len )                       \
do                                                      \
{                                                       \
  pDesc->xferLenL = (uint8)(uint16)(len);               \
  pDesc->xferLenV &= ~DMA_LEN_H;                        \
  pDesc->xferLenV |= (uint8)((uint16)(len) >> 8);       \
} while(0)

/* DMA get parameters */
#define DMA_GET_LEN( pDesc )                            \
  (((uint16)(pDesc->xferLenV & DMA_LEN_H) << 8) | pDesc->xferLenL)

#define HAL_DMA_GET_TRIG_MODE( pDesc ) ((pDesc->ctrlA >> 5) & 0x3)
    
/* DMA set parameters */
#define DMA_SET_VLEN( pDesc, vMode )                    \
do                                                      \
{                                                       \
  pDesc->xferLenV &= ~DMA_LEN_V;                        \
  pDesc->xferLenV |= (vMode << 5);                      \
} while(0)

#define DMA_SET_WORD_SIZE( pDesc, xSz )                 \
do                                                      \
{                                                       \
  pDesc->ctrlA &= ~DMA_WORD_SIZE;                       \
  pDesc->ctrlA |= (xSz << 7);                           \
} while(0)

#define DMA_SET_TRIG_MODE( pDesc, tMode )               \
do                                                      \
{                                                       \
  pDesc->ctrlA &= ~DMA_TRIG_MODE;                       \
  pDesc->ctrlA |= (tMode << 5);                         \
} while(0)

#define DMA_SET_TRIG_SRC( pDesc, tSrc )                 \
do                                                      \
{                                                       \
  pDesc->ctrlA &= ~DMA_TRIG_SRC;                        \
  pDesc->ctrlA |= tSrc;                                 \
} while(0)
   
#define DMA_SET_SRC_INC( pDesc, srcInc )                \
do                                                      \
{                                                       \
  pDesc->ctrlB &= ~DMA_SRC_INC;                         \
  pDesc->ctrlB |= (srcInc << 6);                        \
} while(0)

#define DMA_SET_DST_INC( pDesc, dstInc )                \
do                                                      \
{                                                       \
  pDesc->ctrlB &= ~DMA_DST_INC;                         \
  pDesc->ctrlB |= (dstInc << 4);                        \
} while(0)

#define DMA_SET_IRQ( pDesc, enable )                    \
do                                                      \
{                                                       \
  pDesc->ctrlB &= ~DMA_IRQ_MASK;                        \
  pDesc->ctrlB |= (enable << 3);                        \
} while(0)

#define DMA_SET_M8( pDesc, m8 )                         \
do                                                      \
{                                                       \
  pDesc->ctrlB &= ~DMA_M8;                              \
  pDesc->ctrlB |= (m8 << 2);                            \
} while(0)

#define DMA_SET_PRIORITY( pDesc, pri )                  \
do                                                      \
{                                                       \
  pDesc->ctrlB &= ~DMA_PRIORITY;                        \
  pDesc->ctrlB |= pri;                                  \
} while(0)

/*==========
 * CONSTANT
 ===========*/

// Use LEN for transfer count
#define DMA_VLEN_USE_LEN            0x00
// Transfer the first byte + the number of bytes indicated by the first byte
#define DMA_VLEN_1_P_VALOFFIRST     0x01
// Transfer the number of bytes indicated by the first byte (starting with the first byte)
#define DMA_VLEN_VALOFFIRST         0x02
// Transfer the first byte + the number of bytes indicated by the first byte + 1 more byte
#define DMA_VLEN_1_P_VALOFFIRST_P_1 0x03
// Transfer the first byte + the number of bytes indicated by the first byte + 2 more bytes
#define DMA_VLEN_1_P_VALOFFIRST_P_2 0x04

#define DMA_WORDSIZE_BYTE           0x00 /* Transfer a byte at a time. */
#define DMA_WORDSIZE_WORD           0x01 /* Transfer a 16-bit word at a time. */

#define DMA_TMODE_SINGLE            0x00 /* Transfer a single byte/word after each DMA trigger. */
#define DMA_TMODE_BLOCK             0x01 /* Transfer block of data (length len) after each DMA trigger. */
#define DMA_TMODE_SINGLE_REPEATED   0x02 /* Transfer single byte/word (after len transfers, rearm DMA). */
#define DMA_TMODE_BLOCK_REPEATED    0x03 /* Transfer block of data (after len transfers, rearm DMA). */

#define DMA_TRIG_NONE           0   /* No trigger, setting DMAREQ.DMAREQx bit starts transfer. */
#define DMA_TRIG_PREV           1   /* DMA channel is triggered by completion of previous channel. */
#define DMA_TRIG_T1_CH0         2   /* Timer 1, compare, channel 0. */
#define DMA_TRIG_T1_CH1         3   /* Timer 1, compare, channel 1. */
#define DMA_TRIG_T1_CH2         4   /* Timer 1, compare, channel 2. */
#define DMA_TRIG_T2_COMP        5   /* Timer 2, compare. */
#define DMA_TRIG_T2_OVFL        6   /* Timer 2, overflow. */
#define DMA_TRIG_T3_CH0         7   /* Timer 3, compare, channel 0. */
#define DMA_TRIG_T3_CH1         8   /* Timer 3, compare, channel 1. */
#define DMA_TRIG_T4_CH0         9   /* Timer 4, compare, channel 0. */
#define DMA_TRIG_T4_CH1        10   /* Timer 4, compare, channel 1. */
#define DMA_TRIG_ST            11   /* Sleep Timer compare. */
#define DMA_TRIG_IOC_0         12   /* Port 0 I/O pin input transition. */
#define DMA_TRIG_IOC_1         13   /* Port 1 I/O pin input transition. */
#define DMA_TRIG_URX0          14   /* USART0 RX complete. */
#define DMA_TRIG_UTX0          15   /* USART0 TX complete. */
#define DMA_TRIG_URX1          16   /* USART1 RX complete. */
#define DMA_TRIG_UTX1          17   /* USART1 TX complete. */
#define DMA_TRIG_FLASH         18   /* Flash data write complete. */
#define DMA_TRIG_RADIO         19   /* RF packet byte received/transmit. */
#define DMA_TRIG_ADC_CHALL     20   /* ADC end of a conversion in a sequence, sample ready. */
#define DMA_TRIG_ADC_CH0       21   /* ADC end of conversion channel 0 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH1       22   /* ADC end of conversion channel 1 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH2       23   /* ADC end of conversion channel 2 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH3       24   /* ADC end of conversion channel 3 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH4       25   /* ADC end of conversion channel 4 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH5       26   /* ADC end of conversion channel 5 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH6       27   /* ADC end of conversion channel 6 in sequence, sample ready. */
#define DMA_TRIG_ADC_CH7       28   /* ADC end of conversion channel 7 in sequence, sample ready. */
#define DMA_TRIG_ENC_DW        29   /* AES encryption processor requests download input data. */
#define DMA_TRIG_ENC_UP        30   /* AES encryption processor requests upload output data. */

#define DMA_SRCINC_0         0x00 /* Increment source pointer by 0 bytes/words after each transfer. */
#define DMA_SRCINC_1         0x01 /* Increment source pointer by 1 bytes/words after each transfer. */
#define DMA_SRCINC_2         0x02 /* Increment source pointer by 2 bytes/words after each transfer. */
#define DMA_SRCINC_M1        0x03 /* Decrement source pointer by 1 bytes/words after each transfer. */

#define DMA_DSTINC_0         0x00 /* Increment destination pointer by 0 bytes/words after each transfer. */
#define DMA_DSTINC_1         0x01 /* Increment destination pointer by 1 bytes/words after each transfer. */
#define DMA_DSTINC_2         0x02 /* Increment destination pointer by 2 bytes/words after each transfer. */
#define DMA_DSTINC_M1        0x03 /* Decrement destination pointer by 1 bytes/words after each transfer. */

#define DMA_IRQMASK_DISABLE  0x00 /* Disable interrupt generation. */
#define DMA_IRQMASK_ENABLE   0x01 /* Enable interrupt generation upon DMA channel done. */

#define DMA_M8_USE_8_BITS    0x00 /* Use all 8 bits for transfer count. */
#define DMA_M8_USE_7_BITS    0x01 /* Use 7 LSB for transfer count. */

#define DMA_PRI_LOW          0x00 /* Low, CPU has priority. */
#define DMA_PRI_GUARANTEED   0x01 /* Guaranteed, DMA at least every second try. */
#define DMA_PRI_HIGH         0x02 /* High, DMA has priority. */
#define DMA_PRI_ABSOLUTE     0x03 /* Highest, DMA has priority. Reserved for DMA port access.. */

#define DMA_MAX_ARM_CLOCKS   45   // Maximum number of clocks required if arming all 5 at once.

// Bit fields of the 'lenModeH'
#define DMA_LEN_V     0xE0
#define DMA_LEN_H     0x1F

// Bit fields of the 'ctrlA'
#define DMA_WORD_SIZE 0x80
#define DMA_TRIG_MODE 0x60
#define DMA_TRIG_SRC  0x1F

// Bit fields of the 'ctrlB'
#define DMA_SRC_INC   0xC0
#define DMA_DST_INC   0x30
#define DMA_IRQ_MASK  0x08
#define DMA_M8        0x04
#define DMA_PRIORITY  0x03

/*==========
 * TYPEDEFS
 ===========*/

typedef struct {
  uint8 srcAddrH;
  uint8 srcAddrL;
  uint8 dstAddrH;
  uint8 dstAddrL;
  uint8 xferLenV;
  uint8 xferLenL;
  uint8 ctrlA;
  uint8 ctrlB;
} DMADesc_t;

/*=================
 * EXTERN VARIBLES
 ==================*/

extern DMADesc_t dmaCh0;

/*=================
 * PUBLIC FUNCTION
 ==================*/

void dmaInit(void);
#endif