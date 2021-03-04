/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */
static u8 Counter=0x00; // counter that sets LATA to one of the light pattern array indexes
u8 au8Pattern[] = {0x01,0x02,0x04,0x08,0x10,0x20}; // light pattern

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    
    T0CON0 = 0x90; // Enable TMR0, set as 16-bit timer, 1:1 postscaler
    T0CON1 = 0x44; // set CLK source to Fosc/4 ,set to ASYNCH mode, set prescaler to 1:8
    TMR0H = 0x00;   
    TMR0L = 0x00;
} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun()
{    
    if(PIR3bits.TMR0IF==1) // if Timer rolls over then light pattern
    {
        LATA = au8Pattern[Counter];
        Counter++;
    }
    if (Counter == 0x06)// if counter reaches end of sequence then reset counter
    {
        Counter = 0x00;
    }
}
   void TimeXus(u16 User_Input){
    
    T0CON0 &= 0X7F; // Disable timer 
    
    u16 timer_end = 0xFFFF - User_Input; // configure timer end to user specfication
    
    TMR0L = (u8) (timer_end & 0x0000); // configure timer start to user input
    TMR0H = (u8) ((timer_end >> 8)&0x0000); // configure timer start to user input
    
    PIR3bits.TMR0IF = 0x00; // alarm restarted
    T0CON0 |= 0X80; // Re-enable Timer
    
}   

 /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
