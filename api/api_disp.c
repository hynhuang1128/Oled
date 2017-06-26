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
extern special_t specialMode;
extern unit_t unitType;

/*===================
 * INTERNAL VARIBLES
 ====================*/

/*===================
 * INTERNAL FUNCTIONS
 ====================*/

/* display the number */
static void displayNum( void )
{
  uint8 num_index = 0;
  uint16 displayHeight = 0;
  
  if (unitType == METRIC)
  {
    displayHeight = peskData.currentHeight;
  }
  else
  {
    displayHeight = (uint16)((uint32)peskData.currentHeight * 100 / 254);
  }
  
  image_t scene1_num0 =
  {
    DIS_SCENE1_NUM0_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM0_X_BEGIN + DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_Y_BEGIN + DIS_SCENE1_NUM_HEIGHT,
    numberLarge[6],
  };
  
  image_t scene1_num1 =
  {
    DIS_SCENE1_NUM1_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM1_X_BEGIN + DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_Y_BEGIN + DIS_SCENE1_NUM_HEIGHT,
    numberLarge[2],
  };
  
  image_t scene1_num2 =
  {
    DIS_SCENE1_NUM2_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM2_X_BEGIN + DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_Y_BEGIN + DIS_SCENE1_NUM_HEIGHT,
    numberLarge[3],
  };
  
  image_t scene1_dot =
  {
    DIS_SCENE1_DOT_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_DOT_X_BEGIN + DIS_SCENE1_DOT_X_WIDTH,
    DIS_SCENE1_NUM_Y_BEGIN + DIS_SCENE1_NUM_HEIGHT,
    largeDot,
  };
  
  image_t scene1_null =
  {
    DIS_SCENE1_NULL_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NULL_X_BEGIN + DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_Y_BEGIN + DIS_SCENE1_NUM_HEIGHT,
    numberLarge[10],
  };
  
  if(peskData.status == NORMAL)
  {
    if(displayHeight >= 1000)
    {
      /* put the num image into the buffer */
      num_index = displayHeight / 1000 % 10;
      scene1_num0.BMP = numberLarge[num_index];
      num_index = displayHeight / 100 % 10;
      scene1_num1.BMP = numberLarge[num_index];
      num_index = displayHeight / 10 % 10;
      scene1_num2.BMP = numberLarge[num_index];
      
      /* modify the postion of the 3rd num */
      scene1_num2.x0 = DIS_SCENE1_NUM2_X_BEGIN;
      scene1_num2.x1 = DIS_SCENE1_NUM2_X_BEGIN + DIS_SCENE1_NUM_WIDTH;
      
      /* erase the unneccessary display */
      LCD_pDraw(&scene1_null);
    }
    else
    {
      /* put the num image into the buffer */
      num_index = displayHeight / 100 % 10;
      scene1_num0.BMP = numberLarge[num_index];
      num_index = displayHeight / 10 % 10;
      scene1_num1.BMP = numberLarge[num_index];
      num_index = displayHeight % 10;
      scene1_num2.BMP = numberLarge[num_index];
      
      /* modify the postion of the 3rd num */
      scene1_num2.x0 = DIS_SCENE1_NUM2D_X_BEGIN;
      scene1_num2.x1 = DIS_SCENE1_NUM2D_X_BEGIN + DIS_SCENE1_NUM_WIDTH;
      
      /* print the dot on the sight */
      LCD_pDraw(&scene1_dot);
    }
    LCD_pDraw(&scene1_num0);
    LCD_pDraw(&scene1_num1);
    LCD_pDraw(&scene1_num2);
  }
}

/* display the unit */
static void displayUnit( void )
{
  image_t scene1_unit =
  {
    DIS_SCENE1_UNIT_X_BEGIN,
    DIS_SCENE1_UNIT_Y_BEGIN,
    DIS_SCENE1_UNIT_X_BEGIN + DIS_SCENE1_UNIT_WIDTH,
    DIS_SCENE1_UNIT_Y_BEGIN + DIS_SCENE1_UNIT_HEIGHT,
    unitCm,
  };
  
  LCD_pDraw(&scene1_unit);
}

/* display the unit */
static void displaySplit( void )
{
  image_t scene1_split =
  {
    DIS_SCENE1_SPLIT_X_BEGIN,
    DIS_SCENE1_SPLIT_Y_BEGIN,
    DIS_SCENE1_SPLIT_X_BEGIN + DIS_SCENE1_SPLIT_WIDTH,
    DIS_SCENE1_SPLIT_Y_BEGIN + DIS_SCENE1_SPLIT_HEIGHT,
    splitThin,
  };
  
  LCD_pDraw(&scene1_split);
}

static void displayControl( void )
{
  uint8 pBuf[6] = { '0', '0', ':', '0', '0', '\0' };
  
  static image_t scene1_control =
  {
    DIS_SCENE1_CTRL_X_BEGIN,
    DIS_SCENE1_CTRL_Y_BEGIN,
    DIS_SCENE1_CTRL_X_BEGIN + DIS_SCENE1_LAST_WIDTH,
    DIS_SCENE1_CTRL_Y_BEGIN + DIS_SCENE1_CTRL_HEIGHT,
    0,
  };
  
  static image_t scene1_arrow =
  {
    DIS_SCENE1_ARROW_X_BEGIN,
    DIS_SCENE1_ARROW_Y_BEGIN,
    DIS_SCENE1_ARROW_X_BEGIN + DIS_SCENE1_ARROW_WIDTH,
    DIS_SCENE1_ARROW_Y_BEGIN + DIS_SCENE1_ARROW_HEIGHT,
    0,
  };
  
  switch(peskCommand.input)
  {
    case KEY_IDLE:
      
      break;
    
    case KEY_UP:
      
      break;
    
    case KEY_DOWN:
      
      break;
    
    case KEY_SET1:
      
      break;
    
    case KEY_SET2:
      
      break;
    
    case KEY_SET3:
      
      break;
    
    case KEY_SETTING:
      
      break;
     
    default:
      
      // Should not get here !
      break;
  }
  
  if (UP == peskData.moveDir)
  {
    if (KEY_SET_MASK != (peskCommand.input & ~KEY_SET_MASK))
    {
      scene1_control.BMP = risingUp;
      scene1_control.x1 = DIS_SCENE1_CTRL_X_BEGIN + DIS_SCENE1_UP_WIDTH;
    }
    else
    {
      
    }
    scene1_arrow.BMP = up;
  }
  else if (DOWN == peskData.moveDir)
  {
    if (KEY_SET_MASK != (peskCommand.input & ~KEY_SET_MASK))
    {
      scene1_control.x1 = DIS_SCENE1_CTRL_X_BEGIN + DIS_SCENE1_DOWN_WIDTH;
      scene1_control.BMP = goingDown;
    }
    else
    {
      
    }
    scene1_arrow.BMP = down;
  }
  else
  {
    scene1_control.x1 = DIS_SCENE1_CTRL_X_BEGIN + DIS_SCENE1_LAST_WIDTH;
    scene1_control.BMP = lasting;
    scene1_arrow.BMP = null;
    
    pBuf[0] = (lastingTime.minutes / 10) % 10 + 0x30;
    pBuf[1] = lastingTime.minutes % 10 + 0x30;
    pBuf[3] = (lastingTime.seconds / 10) % 10 + 0x30;
    pBuf[4] = lastingTime.seconds % 10 + 0x30;
    
    LCD_pNormalStr(55, 6, pBuf);
  }
  
  LCD_pDraw(&scene1_control);
  LCD_pDraw(&scene1_arrow);
}

/*========
 * SCENE1
 =========*/
void displayScene_1( void )
{
  displayNum();
  displayUnit();
  displaySplit();
  displayControl();
  
  /*
  uint8 buf[7];
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char(peskCommand.output & 0x0f);
  buf[3] = num2Char((peskCommand.output >> 4) & 0x0f);
  buf[4] = '\0';
  LCD_pNormalStr(0, 4, buf);
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char((uint8)(peskData.info >> 12) & 0x0f);
  buf[3] = num2Char((uint8)(peskData.info >> 8) & 0x0f);
  buf[4] = num2Char((uint8)(peskData.info >> 4) & 0x0f);
  buf[5] = num2Char((uint8)(peskData.info) & 0x0f);
  buf[6] = '\0';
  LCD_pNormalStr(0, 6, buf);
  */
}

/*========
 * SCENE2
 =========*/
void displayScene_2( void )
{
  switch (peskData.info)
  {
    case 0x0000:
      LCD_pNormalStr(0, 2, "SAVE?       ");
      break;
      
    case 0x0100:
      LCD_pNormalStr(0, 2, "SAVE - 3    ");
      break;
      
    case 0x0200:
      LCD_pNormalStr(0, 2, "SAVE - 2    ");
      break;
      
    case 0x0800:
      LCD_pNormalStr(0, 2, "SAVE - 1    ");
      break;
      
    default:
      // do nothing!
      break;
  }
  /*
  uint8 buf[7];
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char(peskCommand.output & 0x0f);
  buf[3] = num2Char((peskCommand.output >> 4) & 0x0f);
  buf[4] = '\0';
  LCD_pNormalStr(0, 4, buf);
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char((uint8)(peskData.info >> 12) & 0x0f);
  buf[3] = num2Char((uint8)(peskData.info >> 8) & 0x0f);
  buf[4] = num2Char((uint8)(peskData.info >> 4) & 0x0f);
  buf[5] = num2Char((uint8)(peskData.info) & 0x0f);
  buf[6] = '\0';
  LCD_pNormalStr(0, 6, buf);
  */
}

/*========
 * SCENE3
 =========*/
void displayScene_3( void )
{
  if (ERROR == peskData.status)
  {
    LCD_pNormalStr(0, 2, "PESK IN ERROR");
    switch (peskData.info)
    {
      case 0x0100:
        LCD_pNormalStr(0, 4, "E01");
        break;
        
      case 0x0200:
        LCD_pNormalStr(0, 4, "E02");
        break;
        
      case 0x0400:
        LCD_pNormalStr(0, 4, "E03");
        break;
        
      case 0x4000:
        LCD_pNormalStr(0, 4, "E07");
        break;
        
      case 0x8000:
        LCD_pNormalStr(0, 4, "E08");
        break;
        
      case 0x0001:
        LCD_pNormalStr(0, 4, "E09");
        break;
        
      case 0x0010:
        LCD_pNormalStr(0, 4, "H01");
        break;
    }
  }
  else
  {
    LCD_pNormalStr(0, 2, "PESK IN RESET");
  }
}

/*========
 * SCENE4
 =========*/
void displayScene_4( void )
{
  switch (specialMode.mode)
  {
    case SPECIAL_SETTING_CANCEL:
      if (SETTING_CANCEL_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "CANCEL SUCCESS");
      }
      else if (SETTING_CANCEL_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "CANCEL PROCESS");
      }
      else
      {
        LCD_pNormalStr(0, 2, "CANCEL FAILED");
      }
      break;
      
    case SPECIAL_SETTING_MAX:
      if (SETTING_MAX_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MAX SUCCESS   ");
      }
      else if (SETTING_MAX_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MAX PROCESS   ");
      }
      else
      {
        LCD_pNormalStr(0, 2, "MAX FAILED    ");
      }
      break;
      
    case SPECIAL_SETTING_MIN:
      if (SETTING_MIN_SUCCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MIN SUCCESS   ");
      }
      else if (SETTING_MIN_PROCESS == specialMode.status)
      {
        LCD_pNormalStr(0, 2, "MIN PROCESS   ");
      }
      else
      {
        LCD_pNormalStr(0, 2, "MIN FAILED    ");
      }
      break;
      
    default:
      // do nothing
      break;
  }
  
  uint8 buf[7];
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char(peskCommand.output & 0x0f);
  buf[3] = num2Char((peskCommand.output >> 4) & 0x0f);
  buf[4] = '\0';
  LCD_pNormalStr(0, 4, buf);
  
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = num2Char((uint8)(peskData.info >> 12) & 0x0f);
  buf[3] = num2Char((uint8)(peskData.info >> 8) & 0x0f);
  buf[4] = num2Char((uint8)(peskData.info >> 4) & 0x0f);
  buf[5] = num2Char((uint8)(peskData.info) & 0x0f);
  buf[6] = '\0';
  LCD_pNormalStr(0, 6, buf);
}

/*===================
 * PUBLIC FUNCTIONS
 ===================*/
// TODO nothing has been done yet
void displayScene( void )
{
  static uint8 firstDisp;
  
  /* shift the port to the lcd function */
  SHIFT_PORT_LCD();
  LCD_CS = 0;
  
  if (NORMAL == peskData.status && SPECIAL_NONE == specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE1)
    {
      displayScene_1();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE1;
    }
  }
  else if (SAVE == peskData.status && SPECIAL_NONE == specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE2)
    {
      displayScene_2();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE2;
    }
  }
  else if ( (ERROR == peskData.status ||
             RST == peskData.status)  &&
             SPECIAL_NONE == specialMode.mode )
  {
    if (firstDisp & FIRST_DISPLAY_SCENE3)
    {
      displayScene_3();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE3;
    }
  }
  else if (SPECIAL_NONE != specialMode.mode)
  {
    if (firstDisp & FIRST_DISPLAY_SCENE4)
    {
      displayScene_4();
    }
    else
    {
      LCD_clr();
      firstDisp = FIRST_DISPLAY_SCENE4;
    }
  }
  else
  {
    // TODO
  }
  
  /* reset the port prepare to receive the key press event */
  CLOSE_PORT_LCD();
}