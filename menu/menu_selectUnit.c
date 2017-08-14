/*==========
 * INCLUDES
 ===========*/

#include "api_menu.h"
#include "api_disp.h"
#include "api_control.h"

/*==================
 * GLOBAL VARIBLES
 ==================*/

/*===================
 * EXTERNAL VARIBLES
 ===================*/

/*===================
 * INTERNAL VARIBLES
 ====================*/

/*====================
 * INTERNAL FUNCTIONS
 =====================*/

/*===================
 * PUBLIC FUNCTIONS
 ===================*/
   
void startSelectUnit( void )
{
  
}
 
void doneSelectUnit( void )
{
  
}
 
void processingSelectUnit( void )
{
  
}
 
void initSelectUnit( void )
{
  // TODO display the current menu item interface
  setDisplayEvent(MENU_INFO_CHANGE_EVT);
  menu_setStatus(MENU_TASK_STOP);
}