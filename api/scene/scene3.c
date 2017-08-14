/*==========
 * INCLUDES
 ===========*/
#include "api_disp.h"
#include "hw_oled.h"

/*===================
 * EXTERNAL VARIBLES
 ===================*/
extern peskData_t peskData;
extern uint16 sys_evt;
extern peskCommand_t peskCommand;
extern rtc_t realTimer;
extern rtc_t lastingTime;
extern unit_t unitType;

/*====================
 * INTERNAL FUNCTIONS
 ====================*/

static void displayQRCode( uint8 index )
{
  image_t scene3_QRCode =
  {
    DIS_SCENE3_QRCODE_X_BEGIN,
    DIS_SCENE3_QRCODE_Y_BEGIN,
    DIS_SCENE3_QRCODE_WIDTH,
    DIS_SCENE3_QRCODE_HEIGHT,
    errorQRCode + index * QRCODE_SIZE,
  };
  
  LCD_pDraw(&scene3_QRCode);
}

static void displayScan( void )
{
  image_t scene3_scan =
  {
    DIS_SCENE3_SCAN_X_BEGIN,
    DIS_SCENE3_SCAN_Y_BEGIN,
    DIS_SCENE3_SCAN_WIDTH,
    DIS_SCENE3_SCAN_HEIGHT,
    errorScan,
  };
  
  LCD_pDraw(&scene3_scan);
}

static void displayError( uint8 index )
{
  image_t scene3_error =
  {
    DIS_SCENE3_ERRORCODE_X_BEGIN,
    DIS_SCENE3_ERRORCODE_Y_BEGIN,
    DIS_SCENE3_ERRORCODE_WIDTH,
    DIS_SCENE3_ERRORCODE_HEIGHT,
    errorCode + index * SCENE3_ERRORCODE_SIZE,
  };
  
  LCD_pDraw(&scene3_error);
}
                                     
/*========
 * SCENE3
 =========*/

void displayWarningSign( void )
{
  image_t warningSign =
  {
    DIS_WARNING_SIGN_X_BEGIN,
    DIS_WARNING_SIGN_Y_BEGIN,
    DIS_WARNING_SIGN_WIDTH,
    DIS_WARNING_SIGN_HEIGHT,
    warningSignCode,
  };
  
  LCD_pDraw(&warningSign);
}
   
void errorDisplay_static( void )
{
  LCD_clr();
  displayWarningSign();
  displayScan();
}

void displayErrorCode( void )
{
  if (ERROR == peskData.status)
  {
    switch (peskData.code)
    {
      case 0x0100:
        displayQRCode(0);
        displayError(0);
        break;
        
      case 0x0200:
        displayQRCode(0);
        displayError(1);
        break;
        
      case 0x0400:
        displayQRCode(0);
        displayError(2);
        break;
        
      case 0x0800:
        displayQRCode(0);
        displayError(3);
        break;
        
      case 0x1000:
        displayQRCode(0);
        displayError(4);
        break;
        
      case 0x2000:
        displayQRCode(0);
        displayError(5);
        break;
      
      case 0x4000:
        displayQRCode(0);
        displayError(6);
        break;
        
      case 0x8000:
        displayQRCode(0);
        displayError(7);
        break;
        
      case 0x0001:
        displayQRCode(0);
        displayError(8);
        break;
        
      case 0x0002:
        displayQRCode(0);
        displayError(9);
        break;
        
      case 0x0004:
        displayQRCode(0);
        displayError(10);
        break;
        
      case 0x0008:
        displayQRCode(0);
        displayError(11);
        break;
        
      default:
        // do nothing
        break;
    }
  }
}
