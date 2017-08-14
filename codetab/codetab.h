#ifndef _CODETAB_H
#define _CODETAB_H

/* display the normal number */

extern __code const unsigned char F6x8[][6];

extern __code const unsigned char F8X16[];

/*-----------------------------
  display initialization scene 
 ------------------------------*/

/* logo display position coordinate */
#define DIS_SCENEHALT_LOGO_X_BEGIN                              8
#define DIS_SCENEHALT_LOGO_Y_BEGIN                              1
#define DIS_SCENEHALT_LOGO_WIDTH                                112
#define DIS_SCENEHALT_LOGO_HEIGHT                               4

extern __code const unsigned char logoDisp[];
/*---------------------
  display first scene 
 ----------------------*/

/* arrow position coordinate */
#define DIS_SCENE1_ARROW_X_BEGIN                107
#define DIS_SCENE1_ARROW_Y_BEGIN                1
#define DIS_SCENE1_ARROW_WIDTH                  13
#define DIS_SCENE1_ARROW_HEIGHT                 1

/* up sign */
extern __code const unsigned char up[];

/* down sign */
extern __code const unsigned char down[];

/* null */
extern __code const unsigned char null[];


/* unit position coordinate */
#define DIS_SCENE1_UNIT_X_BEGIN                 103
#define DIS_SCENE1_UNIT_Y_BEGIN                 3
#define DIS_SCENE1_UNIT_WIDTH                   18
#define DIS_SCENE1_UNIT_HEIGHT                  2

#define DIS_HALT_UNIT_X_BEGIN                   39
#define DIS_HALT_UNIT_Y_BEGIN                   6
#define DIS_HALT_UNIT_WIDTH                     18
#define DIS_HALT_UNIT_HEIGHT                    2

/* cm unit sign */
extern __code const unsigned char unitCm[];

/* inch unit sign */
extern __code const unsigned char unitInch[];


/* dot position coordinate */
#define DIS_SCENE1_DOT_X_BEGIN                  48
#define DIS_SCENE1_DOT_X_WIDTH                  11
#define DIS_SCENE1_NULL_X_BEGIN                 69

/* height value dot */
extern __code const unsigned char largeDot[];
   

/* control position coordinate */
#define DIS_SCENE1_CTRL_X_BEGIN                 8
#define DIS_SCENE1_CTRL_Y_BEGIN                 6
#define DIS_SCENE1_UP_WIDTH                     112
#define DIS_SCENE1_LAST_WIDTH                   47
#define DIS_SCENE1_DOWN_WIDTH                   112
#define DIS_SCENE1_CTRL_HEIGHT                  2

/* raising up text hint */
extern __code const unsigned char risingUp[];

/* going down text hint */
extern __code const unsigned char goingDown[];

/* lasting time text hint */
extern __code const unsigned char lasting[];


/* number position coordinate */
#define DIS_SCENE1_NUM_Y_BEGIN                  1
#define DIS_SCENE1_NUM0_X_BEGIN                 7
#define DIS_SCENE1_NUM1_X_BEGIN                 28
#define DIS_SCENE1_NUM2_X_BEGIN                 48
#define DIS_SCENE1_NUM2D_X_BEGIN                59
#define DIS_SCENE1_NUM_WIDTH                    20
#define DIS_SCENE1_NUM_HEIGHT                   4

/* height value number display */
extern __code const unsigned char numberLarge[][80];

/*------------------ 
  universal display 
 -------------------*/

/* warning sign position coordinate */
#define DIS_WARNING_SIGN_X_BEGIN                107
#define DIS_WARNING_SIGN_Y_BEGIN                1
#define DIS_WARNING_SIGN_WIDTH                  13
#define DIS_WARNING_SIGN_HEIGHT                 2

/* universal display warning sign */
extern __code const unsigned char warningSignCode[];


/* split line position coordinate */
#define DIS_SCENE1_SPLIT_X_BEGIN                6
#define DIS_SCENE1_SPLIT_Y_BEGIN                5
#define DIS_SCENE1_SPLIT_WIDTH                  116
#define DIS_SCENE1_SPLIT_HEIGHT                 1

/* universal split */
extern __code const unsigned char splitThin[];

/*-------------------- 
  display second scene 
 ---------------------*/

/* save code position coordinate */
#define DIS_SCENE2_CODE_X_BEGIN                 8
#define DIS_SCENE2_CODE_Y_BEGIN                 1
#define DIS_SCENE2_CODE_WIDTH                   91
#define DIS_SCENE2_CODE_HEIGHT                  3

/* height storage saving text hint */
extern __code const unsigned char saveHint[];


/* press hint position coordinate */
#define DIS_SCENE2_PRESS_X_BEGIN                8
#define DIS_SCENE2_PRESS_Y_BEGIN                6
#define DIS_SCENE2_PRESS_WIDTH                  33
#define DIS_SCENE2_PRESS_HEIGHT                 2

/* height storage text hint */
extern __code const unsigned char savePressHint[];


/* success hint position coordinate */
#define DIS_SCENE2_SUCCESS_X_BEGIN              8
#define DIS_SCENE2_SUCCESS_Y_BEGIN              6
#define DIS_SCENE2_SUCCESS_WIDTH                48
#define DIS_SCENE2_SUCCESS_HEIGHT               2

extern __code const unsigned char saveSuccessHint[];


/* save sign position coordinate */
#define DIS_SCENE2_SAVE_X_BEGIN                 62
#define DIS_SCENE2_SAVE_Y_BEGIN                 6
#define DIS_SCENE2_SAVE_WIDTH                   13
#define DIS_SCENE2_SAVE_HEIGHT                  2

/* save sign combo position offset */
#define DIS_SCENE2_SAVECOMBO_X_BEGIN            47
#define DIS_SCENE2_SAVE_OFFSET                  19

/* height storage save sign 1 */
extern __code const unsigned char save1[];

/* height storage save sign 2 */
extern __code const unsigned char save2[];

/* height storage save sign 3 */
extern __code const unsigned char save3[];

/* save sign position coordinate */
#define DIS_SCENE2_GOINGTO_X_BEGIN              8
#define DIS_SCENE2_GOINGTO_Y_BEGIN              6
#define DIS_SCENE2_GOINGTO_WIDTH                47
#define DIS_SCENE2_GOINGTO_HEIGHT               2

/* save sign position offset */
#define DIS_SCENE2_GONINGSIGN_X_BEGIN           61

/* save display going to text hint */
extern __code const unsigned char goingTo[];

/*-------------------- 
  display thrid scene 
 ---------------------*/

/* error qrcode position coordinate */
#define DIS_SCENE3_QRCODE_X_BEGIN               0
#define DIS_SCENE3_QRCODE_Y_BEGIN               0
#define DIS_SCENE3_QRCODE_WIDTH                 64
#define DIS_SCENE3_QRCODE_HEIGHT                8

/* error code figure size */
#define QRCODE_SIZE                             512

/* error QR code */
extern __code const unsigned char errorQRCode[];


/* error qrcode position coordinate */
#define DIS_SCENE3_ERRORCODE_X_BEGIN            101
#define DIS_SCENE3_ERRORCODE_Y_BEGIN            3
#define DIS_SCENE3_ERRORCODE_WIDTH              22
#define DIS_SCENE3_ERRORCODE_HEIGHT             2

/* error code text size */
#define SCENE3_ERRORCODE_SIZE                   44

/* error code */
extern __code const unsigned char errorCode[];


/* error scan text and figure position coordinate */
#define DIS_SCENE3_SCAN_X_BEGIN                 64
#define DIS_SCENE3_SCAN_Y_BEGIN                 5
#define DIS_SCENE3_SCAN_WIDTH                   58
#define DIS_SCENE3_SCAN_HEIGHT                  3

/* error scan text and figure hint */
extern __code const unsigned char errorScan[];

/*------------------ 
  display 4th scene 
 -------------------*/

/* rst text hint position coordinate */
#define DIS_SCENE4_RSTHINT_X_BEGIN              29
#define DIS_SCENE4_RSTHINT_Y_BEGIN              2
#define DIS_SCENE4_RSTHINT_WIDTH                42
#define DIS_SCENE4_RSTHINT_HEIGHT               3

/* rst status text hint */
extern __code const unsigned char resetHint[];


/* rst sign position coordinate */
#define DIS_SCENE4_RSTSIGN_X_BEGIN              8
#define DIS_SCENE4_RSTSIGN_Y_BEGIN              1
#define DIS_SCENE4_RSTSIGN_WIDTH                17
#define DIS_SCENE4_RSTSIGN_HEIGHT               2

/* rst sign display */
extern __code const unsigned char resetSign[];


/* rst text hint position coordinate */
#define DIS_SCENE4_RSTTEXT_X_BEGIN              98
#define DIS_SCENE4_RSTTEXT_Y_BEGIN              3
#define DIS_SCENE4_RSTTEXT_WIDTH                22
#define DIS_SCENE4_RSTTEXT_HEIGHT               2

/* rst text */
extern __code const unsigned char resetText[];


/* rst operation hint position coordinate */
#define DIS_SCENE4_RSTOPER_X_BEGIN              8
#define DIS_SCENE4_RSTOPER_Y_BEGIN              6
#define DIS_SCENE4_RSTOPER_WIDTH                92
#define DIS_SCENE4_RSTOPER_HEIGHT               2

/* reset operation instructions */
extern __code const unsigned char resetOperation[];


/* h01 operation hint position coordinate */
#define DIS_SCENE4_H01HINT_X_BEGIN              23
#define DIS_SCENE4_H01HINT_Y_BEGIN              2
#define DIS_SCENE4_H01HINT_WIDTH                69
#define DIS_SCENE4_H01HINT_HEIGHT               3

/* h01 status text hint */
extern __code const unsigned char h01Hint[];


/* h01 sign position coordinate */
#define DIS_SCENE4_H01SIGN_X_BEGIN              8
#define DIS_SCENE4_H01SIGN_Y_BEGIN              1
#define DIS_SCENE4_H01SIGN_WIDTH                20
#define DIS_SCENE4_H01SIGN_HEIGHT               3

/* h01 sign display */
extern __code const unsigned char h01Sign[];


/* h01 text hint position coordinate */
#define DIS_SCENE4_H01TEXT_X_BEGIN              100
#define DIS_SCENE4_H01TEXT_Y_BEGIN              3
#define DIS_SCENE4_H01TEXT_WIDTH                22
#define DIS_SCENE4_H01TEXT_HEIGHT               2

/* h01 text */
extern __code const unsigned char h01Text[];


/* h01 operation hint position coordinate */
#define DIS_SCENE4_H01OPER_X_BEGIN              8
#define DIS_SCENE4_H01OPER_Y_BEGIN              6
#define DIS_SCENE4_H01OPER_WIDTH                92
#define DIS_SCENE4_H01OPER_HEIGHT               2

/* h01 operation instructions */
extern __code const unsigned char h01Operation[];

/*--------------------
  menu related scenes 
 ---------------------*/

/* top index sign display position coordinate */
#define DIS_MENU_NUM_INDEX_X_BEGIN              52
#define DIS_MENU_NUM_INDEX_Y_BEGIN              0
#define DIS_MENU_NUM_INDEX_WIDTH                8
#define DIS_MENU_NUM_INDEX_HEIGHT               2

/* top index sign display position coordinate */
#define DIS_MENU_NUM_TOTAL_X_BEGIN              68
#define DIS_MENU_NUM_TOTAL_Y_BEGIN              0
#define DIS_MENU_NUM_TOTAL_WIDTH                8
#define DIS_MENU_NUM_TOTAL_HEIGHT               2

/* menu number */
extern __code const unsigned char menuNumbers[];



/* menu clear hint display position coordinate */
#define DIS_MENU_TEXT_HINT_X_BEGIN              8
#define DIS_MENU_TEXT_HINT_Y_BEGIN              2
#define DIS_MENU_TEXT_HINT_WIDTH                116
#define DIS_MENU_TEXT_HINT_HEIGHT               3

/* menu clear hint */
extern __code const unsigned char menuClearHint[];

/* menu set max */
extern __code const unsigned char menuSetMaxHint[];

/* menu set min */
extern __code const unsigned char menuSetMinHint[];

/* menu set min */
extern __code const unsigned char menuToggleUnitHint[];


/* menu up sign display position coordinate */
#define DIS_MENU_UP_SIGN_X_BEGIN                38
#define DIS_MENU_UP_SIGN_Y_BEGIN                0
#define DIS_MENU_UP_SIGN_WIDTH                  9
#define DIS_MENU_UP_SIGN_HEIGHT                 2

/* menu up sign */
extern __code const unsigned char menuSignUp[];


/* menu up sign display position coordinate */
#define DIS_MENU_DOWN_SIGN_X_BEGIN              80
#define DIS_MENU_DOWN_SIGN_Y_BEGIN              0
#define DIS_MENU_DOWN_SIGN_WIDTH                9
#define DIS_MENU_DOWN_SIGN_HEIGHT               2

/* menu down sign */
extern __code const unsigned char menuSignDown[];

/* menu null sign */
extern __code const unsigned char menuSignNull[];

/* menu up sign display position coordinate */
#define DIS_MENU_DASH_SIGN_X_BEGIN              60
#define DIS_MENU_DASH_SIGN_Y_BEGIN              0
#define DIS_MENU_DASH_SIGN_WIDTH                6
#define DIS_MENU_DASH_SIGN_HEIGHT               2

/* menu dash sign */
extern __code const unsigned char menuSignDash[];


/* menu up sign display position coordinate */
#define DIS_MENU_PRESSHINT_X_BEGIN              8
#define DIS_MENU_PRESSHINT_Y_BEGIN              6
#define DIS_MENU_PRESSHINT_WIDTH                68
#define DIS_MENU_PRESSHINT_HEIGHT               2

/* menu press hint */
extern __code const unsigned char menuPressHint[];



/* menu unit clear area */
#define DIS_MENU_UNIT_CLEAR_X_BEGIN             0
#define DIS_MENU_UNIT_CLEAR_Y_BEGIN             0
#define DIS_MENU_UNIT_CLEAR_WIDTH               128
#define DIS_MENU_UNIT_CLEAR_HEIGHT              5
/* menu up sign display position coordinate */
#define DIS_MENU_UNIT_X_BEGIN                   29
#define DIS_MENU_UNIT_Y_BEGIN                   2
#define DIS_MENU_UNIT_WIDTH                     70
#define DIS_MENU_UNIT_HEIGHT                    3

/* menu unit cm selected */
extern __code const unsigned char menuUnitCm[];


/* menu unit inch selected */
extern __code const unsigned char menuUnitInch[];


/* menu up sign display position coordinate */
#define DIS_MENU_SPLIT_LINE_X_BEGIN             6
#define DIS_MENU_SPLIT_LINE_Y_BEGIN             5
#define DIS_MENU_SPLIT_LINE_WIDTH               116
#define DIS_MENU_SPLIT_LINE_HEIGHT              1

/* menu split line */
extern __code const unsigned char menuSplit[];


/* menu status display position coordinate */
#define DIS_MENU_STATUS_X_BEGIN                 32
#define DIS_MENU_STATUS_Y_BEGIN                 3
#define DIS_MENU_STATUS_WIDTH                   64
#define DIS_MENU_STATUS_HEIGHT                  2

/* menu status */
extern __code const unsigned char menuSuccessStatus[];
extern __code const unsigned char menuFailedStatus[];
extern __code const unsigned char menuSettingStatus[];
extern __code const unsigned char menuClearingStatus[];


/* processing animation position coordinate */
#define DIS_PROCESS_ANIM_X0_BEGIN               46
#define DIS_PROCESS_ANIM_X1_BEGIN               58
#define DIS_PROCESS_ANIM_X2_BEGIN               70
#define DIS_PROCESS_ANIM_Y_BEGIN                5
#define DIS_PROCESS_ANIM_WIDTH                  8
#define DIS_PROCESS_ANIM_HEIGHT                 2
/* clear */
#define DIS_PROCESS_ANIM_CLEAR_WIDTH            36 

/* processing animation */
extern __code const unsigned char processingAnimation[];

#endif