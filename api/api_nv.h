#ifndef _API_NV_H
#define _API_NV_H

/*==========
 * INCLUDES
 ===========*/
#include "hw_flash.h"
#include "hw_type.h"

/*========
 * MACROS
 =========*/
#define NV_STORAGE_NULL         0xff
   
/*==========
 * CONSTANT
 ===========*/
#define NV_START_PG             0x7f
#define NV_START_ADDR           (0xfe00)
#define NV_END_ADDR             (NV_START_PG * FLASH_PAGE_SIZE / FLASH_WORD_SIZE + FLASH_WORD_COUNT)

   
#define NV_DATA_COUNT           20
   
/*==========
 * TYPEDEFS
 ===========*/
typedef struct _nvData
{
  union
  {
    uint32 word;
    struct
    {
      uint8 hdr;
      uint8 data;
      uint16 sum;
    };
    uint16 sData[2];
  };
} nvData_t;

/*=============
 * DECLARATION
 ==============*/
bStatus api_nv_write(uint8 id, uint8 *srcData, uint8 len);
bStatus api_nv_read(uint8 id, uint8 *destData, uint8 len);

#endif