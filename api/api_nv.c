/*==========
 * INCLUDES
 ===========*/
#include "api_nv.h"
#include "hw_oled.h"

/*===================
 * INTERNAL VARIBLES
 ====================*/
static bool failFlag;

/*===================
 * INTERNAL FUNCTIONS
 ====================*/

/* to erase the flash page */
static bStatus nv_erase(uint8 pg)
{
  uint16 offset;
  uint8 tmp;
  
  if (failFlag)
  {
    return FAILED;
  }
  hw_flashErase(pg);
  
  for (offset = 0; offset < FLASH_PAGE_SIZE; offset++)
  {
    hw_flashRead(pg, offset, &tmp, 1);
    if (tmp != NV_STORAGE_NULL)
    {
      hw_flashErase(pg);
    }
  }
  return SUCCESS;
}

/*==================
 * PUBLIC FUNCTIONS
 ===================*/

/******************************************************************************
 * @fn      api_nv_init
 *
 * @brief   non-volatile storage initialize
 *
 * @param       none
 *
 * @return      bStatus type -  whether the operation is success or not
 *****************************************************************************/
bStatus api_nv_init(void)
{
  
  return SUCCESS;
}

/******************************************************************************
 * @fn      api_nv_write
 *
 * @brief   non-volatile storage write command
 *
 * @param       id  -           uint8 type, the identifier of the destinate address
 * @param       srcData -       uint8 array type, the data prepared to write into the storage
 * @param       len -           uint8 type, the data length
 *
 * @return      bStatus type -  whether the operation is success or not
 *****************************************************************************/
bStatus api_nv_write(uint8 id, uint8 *srcData, uint8 len)
{
  nvData_t nvData[NV_DATA_COUNT];
  uint32 temp;
  
  // TODO fail detection
  
  for (int i = 0; i < NV_DATA_COUNT; i++)
  {
    hw_flashRead(NV_START_PG, i * FLASH_WORD_SIZE, (uint8 *)&nvData[i].word, sizeof(nvData_t));
  }
  
  if(nv_erase(NV_START_PG))
  {
    LCD_pTinyStr(0, 1, "erase complete!");
  }
  else
  {
    LCD_pTinyStr(0, 1, "erase failed!");
  }
  
  for (int i = id; i < id + len; i++)
  {
    nvData[i].hdr = i;
    nvData[i].data = *(srcData + i);
    nvData[i].sum = (uint16)i + (uint16)(*(srcData + i));
  }
  
  hw_flashWrite(NV_START_ADDR, (uint8 *)nvData->sData, sizeof(nvData_t) * NV_DATA_COUNT);
  
  /* verify the written data */
  for (int i = 0; i < NV_DATA_COUNT; i++)
  {
    hw_flashRead(NV_START_PG, i * FLASH_WORD_SIZE, (uint8 *)&temp, sizeof(nvData_t));
    
    if(temp != nvData[i].word)
    {
  
  // test
  {
    uint8 buf[9];
    buf[7] = ((uint8)(temp) & 0x0f) + 0x30;
    buf[6] = ((uint8)(temp >> 4) & 0x0f) + 0x30;
    buf[5] = ((uint8)(temp >> 8) & 0x0f) + 0x30;
    buf[4] = ((uint8)(temp >> 12) & 0x0f) + 0x30;
    buf[3] = ((uint8)(temp >> 16) & 0x0f) + 0x30;
    buf[2] = ((uint8)(temp >> 20) & 0x0f) + 0x30;
    buf[1] = ((uint8)(temp >> 24) & 0x0f) + 0x30;
    buf[0] = ((uint8)(temp >> 28) & 0x0f) + 0x30;
    buf[8] = '\0';
    LCD_pTinyStr(0, 6, buf);
  }
  //
      return FAILED;
    }
  }

  return SUCCESS;
}

/******************************************************************************
 * @fn      api_nv_read
 *
 * @brief   non-volatile storage read command
 *
 * @param       id  -           uint8 type, the identifier you need to read from the destinate address
 * @param       srcData -       uint8 array type, the data prepared to read from the storage
 * @param       len -           uint8 type, the data length
 *
 * @return      bStatus type -  whether the operation is success or not
 *****************************************************************************/
bStatus api_nv_read(uint8 id, uint8 *destData, uint8 len)
{
  nvData_t nvData[NV_DATA_COUNT];
  
  for(int i = id; i < id + len; i++)
  {
    hw_flashRead(NV_START_PG, i * FLASH_WORD_SIZE, (uint8 *)&nvData[i].word, sizeof(nvData_t));
  
    if( nvData[i].data + nvData[i].hdr != nvData[i].sum )
    {
      return FAILED;
    }
    
    if( nvData[i].hdr == NV_STORAGE_NULL )
    {
      return FAILED;
    }
    
    *(destData + i - id) = nvData[i].data;
  }
  
  return SUCCESS;
}