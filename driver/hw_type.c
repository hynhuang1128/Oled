/*==========
 * INCLUDES
 ===========*/
#include "hw_type.h"
   
#ifdef DEBUG
#include "hw_oled.h"
#endif

/*=======
 * UTILS
 ========*/
uint8 num2Char(uint8 x)
{
  uint8 ret = 0;
  switch(x)
  {
    case 0x00:
      ret = '0';
      break;
      
    case 0x01:
      ret = '1';
      break;
      
    case 0x02:
      ret = '2';
      break;
      
    case 0x03:
      ret = '3';
      break;
      
    case 0x04:
      ret = '4';
      break;
      
    case 0x05:
      ret = '5';
      break;
      
    case 0x06:
      ret = '6';
      break;
      
    case 0x07:
      ret = '7';
      break;
      
    case 0x08:
      ret = '8';
      break;
      
    case 0x09:
      ret = '9';
      break;
      
    case 0x0a:
      ret = 'a';
      break;
      
    case 0x0b:
      ret = 'b';
      break;
      
    case 0x0c:
      ret = 'c';
      break;
      
    case 0x0d:
      ret = 'd';
      break;
      
    case 0x0e:
      ret = 'e';
      break;
      
    case 0x0f:
      ret = 'f';
      break;
      
    default:
      break;
  }
  return ret;
}

#ifdef DEBUG
void printDebugMsg(uint32 msg, uint8 pos)
{
  uint8 buf[11];
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char((uint8)(msg >> 28) & 0x0f);
  buf[3] = num2Char((uint8)(msg >> 24) & 0x0f);
  buf[4] = num2Char((uint8)(msg >> 20) & 0x0f);
  buf[5] = num2Char((uint8)(msg >> 16) & 0x0f);
  buf[6] = num2Char((uint8)(msg >> 12) & 0x0f);
  buf[7] = num2Char((uint8)(msg >> 8) & 0x0f);
  buf[8] = num2Char((uint8)(msg >> 4) & 0x0f);
  buf[9] = num2Char((uint8)(msg) & 0x0f);
  buf[10] = '\0';
  
  LCD_pNormalStr(0, pos, buf);
}
#endif 