/*==========
 * INCLUDES
 ===========*/
#include "hw_type.h"

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