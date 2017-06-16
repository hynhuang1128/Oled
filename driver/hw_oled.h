#ifndef _HW_OLED_H
#define _HW_OLED_H

/*==========
 * INCLUDES
 ===========*/
#include <ioCC2541.h>
#include "hw_type.h"
#include "codetab.h"

/*========
 * MACROS
 =========*/
/* delay marco */
#define DELAY_PARAM     1800

/* port definitions */
#define LCD_SCL         P1_5
#define LCD_SDA         P1_6
#define LCD_RST         P1_7
#define LCD_DC          P1_2

/* port initialize definitions */
// set P1.2 P1.5 P1.6 P1.7 to GPIO
// set P1.2 P1.5 P1.6 P1.7 output
#define LCD_INIT_PORT()                 \
do                                      \
{                                       \
  P1SEL &= 0x1b;                        \
  P1DIR |= 0xe4;                        \
} while(0)

/* OLED definitions */
#define X_LEVEL_L       0x00
#define X_LEVEL_H       0x10
#define X_LEVEL         ( ( X_LEVEL_H & 0x0F ) * 16 + X_LEVEL_L )
#define MAX_COLUMN      128
#define MAX_ROW         64
#define BRIGHTNESS      0xCF
#define X_WIDTH         128
#define Y_WIDTH         64
#define FULL            0xFF
#define CLEAR           0x00

/*=============
 * TYPE DEFINES
 ==============*/
typedef struct imageInfo
{
  uint8 x0;
  uint8 y0;
  uint8 x1;
  uint8 y1;
  uint8 *BMP;
} image_t;

/*======================
 * FUNCTION DECLARATION
 =======================*/
void LCD_setPos(uint8 x, uint8 y);
void LCD_fill(uint8 bmp_dat);
void LCD_clr(void);
void LCD_init(void);
void LCD_pTinyStr(uint8 x, uint8 y, uint8 *ch);
void LCD_pNormalStr(uint8 x, uint8 y, uint8 *ch);
void LCD_pDraw(image_t* image);

#endif