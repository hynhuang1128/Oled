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
extern displayEvent_t currentStaticDisplay;

/*===================
 * INTERNAL FUNCTIONS
 ====================*/

/*========
 * SCENE1
 =========*/
 
/*
 *
 * @ function name	        - normalDisplay_static 
 * 
 * @ brief			- display the normal situation's background
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void normalDisplay_static( void )
{
  LCD_clr();
  displaySplit();
  displayNum();
  displayUnit();
  displayControl();
}

/*
 *
 * @ function name	        - displayNum 
 * 
 * @ brief			- display the normal situation's height value
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void displayNum( void )
{
  uint8 num_index = 0;
  uint16 displayHeight = 0;
  
  if (currentStaticDisplay != HEIGHT_DISPLAY_EVT) return;
  
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
    DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_HEIGHT,
    numberLarge[6],
  };
  
  image_t scene1_num1 =
  {
    DIS_SCENE1_NUM1_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_HEIGHT,
    numberLarge[2],
  };
  
  image_t scene1_num2 =
  {
    DIS_SCENE1_NUM2_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_HEIGHT,
    numberLarge[3],
  };
  
  image_t scene1_dot =
  {
    DIS_SCENE1_DOT_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_DOT_X_WIDTH,
    DIS_SCENE1_NUM_HEIGHT,
    largeDot,
  };
  
  image_t scene1_null =
  {
    DIS_SCENE1_NULL_X_BEGIN,
    DIS_SCENE1_NUM_Y_BEGIN,
    DIS_SCENE1_NUM_WIDTH,
    DIS_SCENE1_NUM_HEIGHT,
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
      scene1_num2.width = DIS_SCENE1_NUM_WIDTH;
      
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
      scene1_num2.width = DIS_SCENE1_NUM_WIDTH;
      
      /* print the dot on the sight */
      LCD_pDraw(&scene1_dot);
    }
    LCD_pDraw(&scene1_num0);
    LCD_pDraw(&scene1_num1);
    LCD_pDraw(&scene1_num2);
  }
}

/*
 *
 * @ function name	        - displayUnit 
 * 
 * @ brief			- display the normal situation's unit
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void displayUnit( void )
{
  image_t scene1_unit =
  {
    DIS_SCENE1_UNIT_X_BEGIN,
    DIS_SCENE1_UNIT_Y_BEGIN,
    DIS_SCENE1_UNIT_WIDTH,
    DIS_SCENE1_UNIT_HEIGHT,
    NULL,
  };
  
  if (unitType == METRIC)
  {
    scene1_unit.BMP = unitCm;
  }
  else
  {
    scene1_unit.BMP = unitInch;
  }
  
  LCD_pDraw(&scene1_unit);
}

/*
 *
 * @ function name	        - displaySplit 
 * 
 * @ brief			- display the normal situation's split line
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void displaySplit( void )
{
  image_t scene1_split =
  {
    DIS_SCENE1_SPLIT_X_BEGIN,
    DIS_SCENE1_SPLIT_Y_BEGIN,
    DIS_SCENE1_SPLIT_WIDTH,
    DIS_SCENE1_SPLIT_HEIGHT,
    splitThin,
  };
  
  LCD_pDraw(&scene1_split);
}

/*
 *
 * @ function name	        - displayControl 
 * 
 * @ brief			- display the normal situation's lasting time and arrow
 *
 * @ date			- 2017.7.27
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none
 *
 */
void displayControl( void )
{
  uint8 pBuf[6] = { '0', '0', ':', '0', '0', '\0' };
  
  image_t scene1_control =
  {
    DIS_SCENE1_CTRL_X_BEGIN,
    DIS_SCENE1_CTRL_Y_BEGIN,
    DIS_SCENE1_LAST_WIDTH,
    DIS_SCENE1_CTRL_HEIGHT,
    0,
  };
  
  image_t scene1_arrow =
  {
    DIS_SCENE1_ARROW_X_BEGIN,
    DIS_SCENE1_ARROW_Y_BEGIN,
    DIS_SCENE1_ARROW_WIDTH,
    DIS_SCENE1_ARROW_HEIGHT,
    NULL,
  };
  
  image_t scene1_goingTo =
  {
    DIS_SCENE2_GOINGTO_X_BEGIN,
    DIS_SCENE2_GOINGTO_Y_BEGIN,
    DIS_SCENE2_GOINGTO_WIDTH,
    DIS_SCENE2_GOINGTO_HEIGHT,
    goingTo,
  };
  
  image_t clrArea0 = 
  {
    CLR_GONING0_X_BEGIN,
    CLR_GONING0_Y_BEGIN,    
    CLR_GONING0_WIDTH,    
    CLR_GONING0_HEIGHT,      
    NULL,
  };
  
  image_t clrArea1 = 
  {
    CLR_GONING1_X_BEGIN,
    CLR_GONING1_Y_BEGIN,    
    CLR_GONING1_WIDTH,    
    CLR_GONING1_HEIGHT,      
    NULL,
  };
  
  image_t scene1_saveSign =
  {
    DIS_SCENE2_GONINGSIGN_X_BEGIN,
    DIS_SCENE2_SAVE_Y_BEGIN,
    DIS_SCENE2_SAVE_WIDTH,
    DIS_SCENE2_SAVE_HEIGHT,
    NULL,
  };
  
  if (UP == peskData.moveDir)
  {
    if (peskCommand.input == KEY_SET3)
    {
      scene1_saveSign.BMP = save1;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else if (peskCommand.input == KEY_SET2)
    {
      scene1_saveSign.BMP = save2;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else if (peskCommand.input == KEY_SET1)
    {
      scene1_saveSign.BMP = save3;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else
    {
      scene1_control.BMP = risingUp;
      scene1_control.width = DIS_SCENE1_UP_WIDTH;
      LCD_pDraw(&scene1_control);
    }
    scene1_arrow.BMP = up;
  }
  else if (DOWN == peskData.moveDir)
  {
    if (peskCommand.input == KEY_SET3)
    {
      scene1_saveSign.BMP = save1;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else if (peskCommand.input == KEY_SET2)
    {
      scene1_saveSign.BMP = save2;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else if (peskCommand.input == KEY_SET1)
    {
      scene1_saveSign.BMP = save3;
      LCD_clrArea(&clrArea0);
      LCD_clrArea(&clrArea1);
      LCD_pDraw(&scene1_goingTo);
      LCD_pDraw(&scene1_saveSign);
    }
    else
    {
      scene1_control.BMP = goingDown;
      scene1_control.width = DIS_SCENE1_DOWN_WIDTH;
      LCD_pDraw(&scene1_control);
    }
    scene1_arrow.BMP = down;
  }
  else
  {
    scene1_control.width = DIS_SCENE1_LAST_WIDTH;
    scene1_control.BMP = lasting;
    scene1_arrow.BMP = null;
    
    pBuf[0] = (lastingTime.minutes / 10) % 10 + 0x30;
    pBuf[1] = lastingTime.minutes % 10 + 0x30;
    pBuf[3] = (lastingTime.seconds / 10) % 10 + 0x30;
    pBuf[4] = lastingTime.seconds % 10 + 0x30;
    
    LCD_pNormalStr(55, 6, pBuf);
    LCD_pDraw(&scene1_control);
  }
  
  LCD_pDraw(&scene1_arrow);
}