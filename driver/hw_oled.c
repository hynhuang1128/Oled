/*==========
 * INCLUDES
 ===========*/
#include "hw_oled.h"
#include "codetab.h"

/*===================
 * INTERNAL FUNCTIONS
 ====================*/
static void delayMs(uint32 ms)
{
  uint32 a = 0;
  while(ms)
  {
    a = DELAY_PARAM;
    while(a--);
    ms--;
  }
  return;
}

static void writeData(uint8 dat)
{
  uint8 temp = 0;
  LCD_DC = 1;
  for (int i = 0; i < 8; i++)
  {
    LCD_SCL = 0;
    temp = dat & 0x80;
    if (temp == 0)
    {
      LCD_SDA = 0;
    }
    else
    {
      LCD_SDA = 1;
    }
    LCD_SCL = 1;             
    dat <<= 1;    
  }
}

static void writeCmd(uint8 cmd)
{ 
  uint8 temp = 0;
  LCD_DC = 0;
  for (int i = 0; i < 8; i++)
  { 
    LCD_SCL = 0; 
    
    temp = cmd & 0x80;
    if (temp == 0)
    {
      LCD_SDA = 0;
    }
    else
    {
      LCD_SDA = 1;
    }
    LCD_SCL = 1;
    cmd <<= 1;        
  }     
}

/*=================
 * GLOBAL FUNCTIONS
 ==================*/

/*
 *
 * @ function name	        - LCD_setPos 
 * 
 * @ brief			- Set the course coordinate 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x             uint8
 *                                              indicates x coordinate
 *
 * @ param                      - y             uint8
 *                                              indicates y coordinate
 *
 * @ return			- none	
 *
 */
void LCD_setPos(uint8 x, uint8 y) 
{ 
  writeCmd(0xb0 + y);
  writeCmd((( x & 0xf0 ) >> 4) | 0x10);
  writeCmd(( x & 0x0f ) | 0x01); 
}

/*
 *
 * @ function name	        - LCD_fill 
 * 
 * @ brief			- Fill the LCD 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x             uint8
 *                                              bmp_dat fill with data
 *
 * @ return			- none	
 *
 */
void LCD_fill(uint8 bmp_dat) 
{
  for (uint8 y = 0; y < Y_WIDTH; y++)
  {
    writeCmd(0xb0 + y);
    writeCmd(0x01);
    writeCmd(0x10);
    for (uint8 x = 0; x < X_WIDTH; x++)
    {
      writeData(bmp_dat);
    }
  }
}

/*
 *
 * @ function name	        - LCD_clr 
 * 
 * @ brief			- Clear the LCD 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void LCD_clr(void)
{  
  for (int y = 0; y < 8; y++)
  {
    writeCmd(0xb0 + y);
    writeCmd(0x01);
    writeCmd(0x10); 
    for (int x = 0; x < X_WIDTH; x++)
    {
      writeData(0);
    }
  }
}

/*
 *
 * @ function name	        - LCD_init 
 * 
 * @ brief			- Initialize the LCD 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- none
 *
 * @ return			- none	
 *
 */
void LCD_init(void)     
{  
  LCD_INIT_PORT();
  
  LCD_CS = 0;
  LCD_SCL = 1;
  LCD_RST = 0;
  delayMs(50);
  LCD_RST = 1;
  
  writeCmd(0xae);       //--turn off oled panel
  writeCmd(0x00);       //---set low column address
  writeCmd(0x10);       //---set high column address
  writeCmd(0x40);       //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  writeCmd(0x81);       //--set contrast control register
  writeCmd(0xcf);       // Set SEG Output Current Brightness
  writeCmd(0xa0);       //--Set SEG/Column Mapping     0xa0 : y-axis reversed 0xa1 : normal
  writeCmd(0xc0);       // Set COM/Row Scan Direction   0xc0 : x-axis reversed 0xc8 : normal
  writeCmd(0xa6);       //--set normal display
  writeCmd(0xa8);       //--set multiplex ratio(1 to 64)
  writeCmd(0x3f);       //--1/64 duty
  writeCmd(0xd3);       //-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
  writeCmd(0x00);       //-not offset
  writeCmd(0xd5);       //--set display clock divide ratio/oscillator frequency
  writeCmd(0x80);       //--set divide ratio, Set Clock as 100 Frames/Sec
  writeCmd(0xd9);       //--set pre-charge period
  writeCmd(0xf1);       // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  writeCmd(0xda);       //--set com pins hardware configuration
  writeCmd(0x12);
  writeCmd(0xdb);       //--set vcomh
  writeCmd(0x40);       // Set VCOM Deselect Level
  writeCmd(0x20);       //-Set Page Addressing Mode (0x00/0x01/0x02)
  writeCmd(0x02);       
  writeCmd(0x8d);       //--set Charge Pump enable/disable
  writeCmd(0x14);       //--set(0x10) disable
  writeCmd(0xa4);       // Disable Entire Display On (0xa4/0xa5)
  writeCmd(0xa6);       // Disable Inverse Display On (0xa6/a7) 
  writeCmd(0xaf);       //--turn on oled panel
  
  LCD_fill(0xff);       // Clear The LCD
  LCD_setPos(0, 0);     // Set The Course
}

/*
 *
 * @ function name	        - LCD_pTinyStr 
 * 
 * @ brief			- Print the 6x8 characters' string 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x             uint8
 *                                              the x coordinate
 *
 * @ param			- y             uint8
 *                                              the y coordinate
 *
 * @ param			- ch            uint8 *
 *                                              the string pointer
 *
 * @ return			- none	
 *
 */
void LCD_pTinyStr(uint8 x, uint8 y, uint8 *ch)
{
  uint8 c = 0;
  uint8 j = 0;      
  while (ch[j] != '\0')
  {    
    c = ch[j] - 32;
    if (x > 126)
    {
      x = 0;
      y++;
    }
    LCD_setPos(x, y);    
    for (int i = 0; i < 6; i++)
    {     
      writeData( F6x8[c][i] );
    }  
    x += 6;
    j++;
  }
}

/*
 *
 * @ function name	        - LCD_pNormalStr 
 * 
 * @ brief			- Print the 16x8 characters' string 
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x             uint8
 *                                              the x coordinate
 *
 * @ param			- y             uint8
 *                                              the y coordinate
 *
 * @ param			- ch            uint8 *
 *                                              the string pointer
 *
 * @ return			- none	
 *
 */
void LCD_pNormalStr(uint8 x, uint8 y, uint8 *ch)
{
  uint8 c = 0;
  uint8 j = 0;
  while (ch[j] != '\0')
  {    
    c = ch[j] - 32;
    if (x > 120)
    {
      x = 0;
      y++;
    }
    LCD_setPos(x, y);    
    for (int i = 0; i < 8; i++)
    {     
      writeData( F8X16[c * 16 + i] );
    }
    LCD_setPos(x, y + 1);
    for (int i = 0; i < 8; i++)
    {     
      writeData( F8X16[c * 16 + i + 8] );
    }
    x += 8;
    j++;
  }
}

/*
 *
 * @ function name	        - LCD_pDraw 
 * 
 * @ brief			- Draw my favorite picture :)
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x0            uint8
 *                                              the start x coordinate
 *
 * @ param			- y0            uint8
 *                                              the start y coordinate
 *
 * @ param			- x1            uint8
 *                                              the end x coordinate
 *
 * @ param			- y1            uint8
 *                                              the end y coordinate
 *
 * @ param			- BMP           uint8 
 *                                              the picture
 *
 * @ return			- none	
 *
 */
void LCD_pDraw(image_t* image)
{     
  uint32 j = 0;
  
  for (uint8 y = image->y0; y < (image->y0 + image->height); y++)
  {
    LCD_setPos(image->x0, y);
    for (uint8 x = image->x0; x < (image->x0 + image->width); x++)
    {
      writeData(image->BMP[j++]);            
    }
  }
} 

/*
 *
 * @ function name	        - LCD_pDrawDynamic
 * 
 * @ brief			- Draw my favorite dynamic picture :)
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x0            uint8
 *                                              the start x coordinate
 *
 * @ param			- y0            uint8
 *                                              the start y coordinate
 *
 * @ param			- x1            uint8
 *                                              the end x coordinate
 *
 * @ param			- y1            uint8
 *                                              the end y coordinate
 *
 * @ param			- BMP           uint8 
 *                                              the picture
 *
 * @ return			- none	
 *
 */
void LCD_pDrawDynamic(imageDynamic_t* image)
{     
  uint32 j = 0;
  
  for (uint8 y = image->y0; y < (image->y0 + image->height); y++)
  {
    LCD_setPos(image->x0, y);
    for (uint8 x = image->x0; x < (image->x0 + image->width); x++)
    {
      writeData(image->BMP[j++]);            
    }
  }
} 

/*
 *
 * @ function name	        - LCD_clrArea
 * 
 * @ brief			- Clear the specific area
 *
 * @ date			- 2017.5.26
 *
 * @ author			- Eric Huang
 *
 * @ param			- x0            uint8
 *                                              the start x coordinate
 *
 * @ param			- y0            uint8
 *                                              the start y coordinate
 *
 * @ param			- width         uint8
 *                                              the end x coordinate
 *
 * @ param			- height        uint8
 *                                              the end y coordinate
 *
 * @ return			- none	
 *
 */
void LCD_clrArea(image_t* clr)
{     
  for (uint8 y = clr->y0; y < (clr->y0 + clr->height); y++)
  {
    LCD_setPos(clr->x0, y);
    for (uint8 x = clr->x0; x < (clr->x0 + clr->width); x++)
    {
      writeData(0x00);
    }
  }
} 
