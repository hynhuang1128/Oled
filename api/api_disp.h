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
   
/*------------------ 
  universal display 
 -------------------*/
#define CLR_BOTTOM_X_BEGIN                      8
#define CLR_BOTTOM_Y_BEGIN                      6
#define CLR_BOTTOM_WIDTH                        112
#define CLR_BOTTOM_HEIGHT                       2
   
/*-------------------- 
  display first scene 
 ---------------------*/
   
/* going to figure0 display clear */
#define CLR_GONING0_X_BEGIN                     55
#define CLR_GONING0_Y_BEGIN                     6
#define CLR_GONING0_WIDTH                       6
#define CLR_GONING0_HEIGHT                      2
   
/* going to figure1 display clear */
#define CLR_GONING1_X_BEGIN                     73
#define CLR_GONING1_Y_BEGIN                     6
#define CLR_GONING1_WIDTH                       46
#define CLR_GONING1_HEIGHT                      2
   
/*-------------------- 
  display second scene 
 ---------------------*/

/*-------------------- 
  display third scene 
 ---------------------*/

/*------------------- 
  display menu scene 
 --------------------*/
   
#define MENU_NUM_INDEX_SIZE                     16
   
/*===========
 * CONSTANT
 ============*/

/* NO DISPLAY EVENT */
#define NO_DISPLAY_EVENT                        0x00000000
   
/* PRIMARY DISPLAY EVENT MASK */
#define STATIC_DISPLAY_MASK                     0x00000fff
#define DYNAMIC_DISPLAY_OFFSET                  12
   
/* STATIC DISPLAY EVENT */
#define HEIGHT_DISPLAY_EVT                      0x00000001
#define SAVE_DISPLAY_EVT                        0x00000002
#define ERROR_DISPLAY_EVT                       0x00000004
#define RST_DISPLAY_EVT                         0x00000008
#define MENU_DISPLAY_EVT                        0x00000010
#define STATUS_DISPLAY_EVT                      0x00000020
#define SUB0_DISPLAY_EVT                        0x00000040
#define HALT_DISPLAY_EVT                        0x00000080
#define H01_DISPLAY_EVT                         0x00000100
   
/* DYNAMIC DISPLAY EVENT */
#define HEIGHT_VALUE_CHANGE_EVT                 0x00001000
#define PESK_STATE_CHANGE_EVT                   0x00002000
// TODO
#define SAVE_CODE_CHANGE_EVT                    0x00008000
#define ERROR_CODE_CHANGE_EVT                   0x00010000
#define HALT_INFO_CHANGE_EVT                    0x00020000
#define MENU_INFO_CHANGE_EVT                    0x00040000
#define STATUS_INFO_CHANGE_EVT                  0x00080000
#define MENU_SUB0_DISPLAY_EVT                   0x00100000

/* DISPLAY EVENT ALL */
#define MENU_DISPLAY_FULL_EVT                   0xffffffff
   
/* PROGRESS BAR */
#define HALT_PROGRESS_BAR_LENGTH                116
#define HALT_PROGRESS_BAR_ELEMENT               0x30
/*==========
 * TYPEDEFS
 ===========*/

typedef uint32 displayEvent_t;

typedef void (*displayEventHandler_t)( void );

/*=============
 * DECLARATION
 ==============*/

/* event setting process */
void setDisplayEvent( displayEvent_t event );
void clearDisplayEvent( displayEvent_t event );

/* display callback functions */
void displayScene( void );
   
/* UNIVERSAL */
void displayWarningSign( void );
void displaySplit( void );

/* SCENE INIT */
void displayInitScene( void );

/* SCENE1 */
void normalDisplay_static( void );
void displayNum( void );
void displayUnit( void );
void displayControl( void );

/* SCENE2 */
void saveDisplay_static( void );
void displaySaveCode( void );

/* SCENE3 */
void errorDisplay_static( void );
void displayErrorCode( void );

/* SCENE4 */
void rstDisplay_static( void );
void h01Display_static( void );
/* SCENEHALT */
void haltDisplay_static( void );
void displayHaltInfo( void );

/* SCENE_MENU */
void menuDisplay_static( void );
void displayMainMenuInfo( void );
void statusDisplay_static( void );
void displayStatusCode( void );

void displayToggle( void );
void displaySetMin( void );
void displaySetMax( void );
void displayClrLimit( void );

/* SCENE SUB0 MENU */
void sub0Display_static( void );
void displaySub0( void );
void ToggleUnitDetailsStatic( void );
void ToggleUnitDetails( void );

/* menu status display callbacks */
void displaySuccess( void );
void displayClearing( void );
void displaySetting( void );
void displayFail( void );

#endif