// ----------------------------------------------------------------------------
//  Projectinfos
// ----------------------------------------------------------------------------
//  Name:     "Diver_Flasher"
//  Details:  With two 3W LEDs it generates high power flashes
//            Usage is to mark input / output on night dives or dives with bad 
//            visibility
//            The flasher is driven by an 18650 Lithium accumulator
//            
//            Output 5V_EN is used to switch on the 5V boost regulator
//            Output FLASH_ON is used to switch on both power LEDS
//            Input REED is used to switch the unit on / off
//
//            Operation modes
//            Reed activated:  System is in sleep mode
//            Reed activated:  System stays active in flash mode
//                             until auto power off timeout occurs
// ----------------------------------------------------------------------------
//  Main Source File for Diver Flasher
//
//  File Name:   	main.c
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

//#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "globaldef.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "mcc.h"
#include "tmr0.h"

// ----------------------------------------------------------------------------
// Hardware access macros and other definitions
// ----------------------------------------------------------------------------

//#define FAST_MODE                         // enable switch for debugging
#ifdef FAST_MODE
  #define OFF_TIME              (1u)        // short time for SW debug/test
#else
  #define OFF_TIME              (90u)       // normal auto power off time
#endif

// HW input & output access macros
#define REED_IS_OFF             (FALSE != WAKE_INPUT_GetValue())
#define FLASH_ON                LED_Flash_SetHigh()
#define FLASH_OFF               LED_Flash_SetLow()
#define BOOST_ON                EN_5V_SetHigh()
#define BOOST_OFF               EN_5V_SetLow()

// All basic timing parameters
#define A_MINUTE                (60000u)  // ms tics per minute
#define MIN_ON_TIME             (5000u)   // minimum on time to avoid flicker
#define CYCLE_TIME              (2000u)   // complete cycle time 2 seconds
#define BOOST_TIME              (10u)     // time to load 5V capacitor
#define FLASH_TIME              (50u)     // flash time in ms
#define WAIT_TIME               (CYCLE_TIME-BOOST_TIME-FLASH_TIME)

// Generic helper macros for easy access in SW
#define TIMER_ISR_OCCURED       (FALSE != u1_TimerIsrOcured)
#define OFF_TIME_REACHED        (OFF_TIME == u16_MinutesElapsed) 
#define MAIN_FSM_IN_WAIT        (MainFSM_Wait == ms_MainFSM)

// Macros related to SW timer
#define SW_TIMER_CNT            (3u)      // counter
#define LOAD_MAIN_FSM_TIMER(x)  u16_SwTimer[0]=x
#define MAIN_FSM_TIMER_ELAPSED  (0 == u16_SwTimer[0])
#define LOAD_MINUTE_TIMER(x)    u16_SwTimer[1]=x
#define MINUTE_TIMER_ELAPSED    (0 == u16_SwTimer[1])
#define LOAD_MIN_ON_TIMER(x)    u16_SwTimer[2]=x
#define MIN_ON_TIMER_ELAPSED    (0 == u16_SwTimer[2])

// ----------------------------------------------------------------------------
// Variable definition (all module global but ISR flag 
// ----------------------------------------------------------------------------
typedef enum 
{
  MainFSM_Init,     // temp state after power on
  MainFSM_Boost,    // boost regulator is switchend on, 5V cap charging
  MainFSM_Flash,    // boost + LEDs are on 
  MainFSM_Wait      // all off, wait before cycle restarts
} MainFSM_t;
static MainFSM_t ms_MainFSM = MainFSM_Init;

volatile  u8  u1_TimerIsrOcured   = 0;    // flag set by timer ISR
static    u16 u16_MinutesElapsed  = 0;    // minute counter for auto power off
static    u16 u16_SwTimer[SW_TIMER_CNT];  // all SW counters

// ----------------------------------------------------------------------------
// Declaration of all functions of main
// ----------------------------------------------------------------------------
static void PrepareSleep(void);
static void PrepareRun(void);
static void MySwTimer(void);
static void MainFSM(void);
static void HandleSleep(void);

// ----------------------------------------------------------------------------
// Definition of all functions of main
// ----------------------------------------------------------------------------
static void PerformSleep(void)
{
  // prepare sleep
  TMR0_StopTimer();           // disable timer to avoid wakeup by timer interrupt
  GIE    = 0;                 // real interrupt is not necessary for wakeup
  IOCAF  = 0;                 // clear all interrupt change flags from port RA
  IOCAN2 = 1;                 // enable wakeup by falling edge on RA2
  IOCIE  = 1;                 // enable IO change interrupt module

  SLEEP();                    // stop the system exactly here 
  NOP();                      // proposed to do that after sleep ..

  // restart the system    
  IOCAN2 = 0;                 // disable interrupt by falling edge on RA2
  IOCIE  = 0;                 // disable interrupt module
  IOCAF  = 0;                 // clear all interrupt change flags from port RA
  GIE    = 1;                 // enable interrupt system again
  
  u16_MinutesElapsed = 0;     // reset minute counter 
  ms_MainFSM = MainFSM_Init;  // reset main FSM
  TMR0_StartTimer();          // enable timer again for basic functionality
  LOAD_MIN_ON_TIMER(MIN_ON_TIME);         // reed switch flicker suppression
}

// ----------------------------------------------------------------------------
static void MySwTimer(void)
{
  u8 lu8_i;
  for (lu8_i = 0; lu8_i < SW_TIMER_CNT; lu8_i++)
  {
    if (0 != u16_SwTimer[lu8_i]) 
    {
      u16_SwTimer[lu8_i]--;
    }
  }
}

// ----------------------------------------------------------------------------
static void HandlePowerOff()
{
  // first: check for auto power off
  if (MINUTE_TIMER_ELAPSED)         // auto power off time reached?
  {
    LOAD_MINUTE_TIMER(A_MINUTE);    // Reload for the next minute
    u16_MinutesElapsed++;           // one more minute has elapsed
 
    if(OFF_TIME_REACHED)            // Time to switch off reached?
    {    
      PerformSleep();               // true, enter sleep mode
    }
  }
  // second: check for user power off
  if (REED_IS_OFF &&                // user switch off request?
     MIN_ON_TIMER_ELAPSED)          // and minimum on time elapsed     
  {  
    PerformSleep();                 // true, enter sleep mode
  }
}

// ----------------------------------------------------------------------------
static void MainFSM(void)
{
  switch (ms_MainFSM)
  {
    default:                        // just in case: switch everything off
      BOOST_OFF;                    // and run into the init state
      FLASH_OFF;
      
    case MainFSM_Init:              // cycle start here
      BOOST_ON;                     // we start with the boost time
      LOAD_MAIN_FSM_TIMER(BOOST_TIME);
      ms_MainFSM = MainFSM_Boost;
      break;

    case MainFSM_Boost:             // booster is on, 5V cap charging
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        FLASH_ON;                   // enable flash while boost is still active
        LOAD_MAIN_FSM_TIMER(FLASH_TIME);
        ms_MainFSM = MainFSM_Flash;
      }          
    break;
      
    case MainFSM_Flash:             // LEDS and boost on, wait for timeout
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        FLASH_OFF;
        BOOST_OFF;
        LOAD_MAIN_FSM_TIMER(WAIT_TIME);
        ms_MainFSM = MainFSM_Wait;          
      }
    break;
          
    case MainFSM_Wait:              // all off, pause before cycle restarts   
      HandlePowerOff();             // check for system power off
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        ms_MainFSM = MainFSM_Init;                    
      }
    break;
  }
}

// ----------------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------------
void main(void)
{
  SYSTEM_Initialize();                    // Controller system initialization 
  PIN_MANAGER_Initialize();               // port initialisation
  TMR0_Initialize();                      // timer 0 (system tic 1ms) init
  INTERRUPT_GlobalInterruptEnable();      // time isr is used
  INTERRUPT_PeripheralInterruptEnable();  // both flags to be set for TISR
  LOAD_MINUTE_TIMER(A_MINUTE);            // init SW timer for minute counter  
  LOAD_MIN_ON_TIMER(MIN_ON_TIME);         // reed switch flicker suppression
  
  while (TRUE)
  {
    if(TIMER_ISR_OCCURED)                 // timer interrupt occurred?
    {
      u1_TimerIsrOcured = FALSE;          // clear local flag from ISR
      MySwTimer();                        // handle all software timers
      MainFSM();                          // perform main function in FSM
    }
  }
}

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------
