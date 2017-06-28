#ifndef _API_DISP_H
#define _API_DISP_H

/*==========
 * INCLUDES
 ===========*/
#include "hw_oled.h"
#include "hw_type.h"
#include "codetab.h"
#include "main.h"

/*========
 * MACROS
 =========*/
   
/*-------------------- 
  display first scene 
 ---------------------*/
   
/* number position coordinate */
#define DIS_SCENE1_NUM_Y_BEGIN                  1
#define DIS_SCENE1_NUM0_X_BEGIN                 7
#define DIS_SCENE1_NUM1_X_BEGIN                 28
#define DIS_SCENE1_NUM2_X_BEGIN                 48
#define DIS_SCENE1_NUM2D_X_BEGIN                59
#define DIS_SCENE1_NUM_WIDTH                    20
#define DIS_SCENE1_NUM_HEIGHT                   4

/* dot position coordinate */
#define DIS_SCENE1_DOT_X_BEGIN                  48
#define DIS_SCENE1_DOT_X_WIDTH                  11
#define DIS_SCENE1_NULL_X_BEGIN                 69
   
/* arrow position coordinate */
#define DIS_SCENE1_ARROW_X_BEGIN                107
#define DIS_SCENE1_ARROW_Y_BEGIN                1
#define DIS_SCENE1_ARROW_WIDTH                  13
#define DIS_SCENE1_ARROW_HEIGHT                 1
   
/* unit position coordinate */
#define DIS_SCENE1_UNIT_X_BEGIN                 103
#define DIS_SCENE1_UNIT_Y_BEGIN                 3
#define DIS_SCENE1_UNIT_WIDTH                   18
#define DIS_SCENE1_UNIT_HEIGHT                  2

/* split line position coordinate */
#define DIS_SCENE1_SPLIT_X_BEGIN                0
#define DIS_SCENE1_SPLIT_Y_BEGIN                5
#define DIS_SCENE1_SPLIT_WIDTH                  128
#define DIS_SCENE1_SPLIT_HEIGHT                 1
   
/* control position coordinate */
#define DIS_SCENE1_CTRL_X_BEGIN                 8
#define DIS_SCENE1_CTRL_Y_BEGIN                 6
#define DIS_SCENE1_UP_WIDTH                     112
#define DIS_SCENE1_LAST_WIDTH                   47
#define DIS_SCENE1_DOWN_WIDTH                   112
#define DIS_SCENE1_CTRL_HEIGHT                  2


   
/*===========
 * CONSTANT
 ============*/
   
#define DIS_SCENE_0                             0x00
#define DIS_SCENE_1                             0x01
#define DIS_SCENE_2                             0x02
#define DIS_SCENE_3                             0x03
   
#define FIRST_DISPLAY_SCENE1                    0x01
#define FIRST_DISPLAY_SCENE2                    0x02
#define FIRST_DISPLAY_SCENE3                    0x04
#define FIRST_DISPLAY_SCENE4                    0x08
   
/*=============
 * DECLARATION
 ==============*/
   
void displayScene( void );
void displayScene_1( void );
void displayScene_2( void );
void displayScene_3( void );
void displayScene_4( void );

#endif