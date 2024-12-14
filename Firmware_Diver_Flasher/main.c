// ----------------------------------------------------------------------------
//  Projectinfos
// ----------------------------------------------------------------------------
//  Name:    "Diver_Marker" and "PCB_Flasher"
//  Details: The Diver_marker" is a small device with driven by a small AAA Lithium battery
//           It is carried by the diver and genereates light signals with two different colours to mark the diver in low light / bad visibility conditions.
//           The PCB_Flasher is a little bit bigger and driven by an 18650 Lithium accumulator. With two 3W LEDs it generates high power flashes
//           Usage is to mark input / output on night dives or dives with bad visibility
//
//  This code covers both applications. The final machine code is selected by #define command at the beginning of the project
//
//  Main Source File for LED Flasher
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

// debug switch: fasten up timout for debugging if defined
//#define FAST_MODE

#define LED1_ON             LED_1_SetHigh()
#define LED1_OFF            LED_1_SetLow()
#define LED2_ON             LED_2_SetHigh()
#define LED2_OFF            LED_2_SetLow()
#define LED3_ON             LED_3_SetHigh()
#define LED3_OFF            LED_3_SetLow();
#define ALL_LEDS_ON         LED_1_SetHigh(); LED_2_SetHigh(); LED_3_SetHigh();

// Blink parameters in ms
#define LED_ON_TIME         (60u)
#define LED_OFF_TIME        (2850u)

// System active time before sleep in minutes

#ifdef FAST_MODE
  #define A_MINUTE          (15000u)
  #define DRY_OFF_TIME      (1u)      // short timeouts for sw development 
  #define WET_OFF_TIME      (3u)      // 15 seconds and 45 seconds
#else
  #define A_MINUTE          (60000u)
  #define DRY_OFF_TIME      (5u)      // normal timing     
  #define WET_OFF_TIME      (75u)
#endif

// Helper macros for easy acces in SW
#define OFF_TIME_REACHED      (u16_Timeout  == u16_MinutesElapsed) 
#define MAIN_FSM_IN_WAIT      (MainFSM_Wait == ms_MainFSM)
#define WATER_DETECTED        (FALSE        == WAKE_INPUT_PORT)

// ----------------------------------------------------------------------------
// Module global variables (scope = main)
// ----------------------------------------------------------------------------
volatile  u8  u1_TimerIsrOcured   = 0;
static    u16 u16_MinutesElapsed  = 0;
static    u8  u1_InWater          = FALSE;
static    u16 u16_Timeout         = 0;

typedef enum 
{
  MainFSM_Init, // temp state after power on
  MainFSM_Led1, // LED 1 is powered
  MainFSM_Led2, // ditto LED 2
  MainFSM_Led3, // ditto LED 3
  MainFSM_Wait, // pause before fire LED 1 again
} MainFSM_t;
static MainFSM_t ms_MainFSM = MainFSM_Init;

// Software timer variables
#define SW_TIMER_CNT            (2u)
static u16                      u16_SwTimer[SW_TIMER_CNT];

// Software time access macros
#define LOAD_MAIN_FSM_TIMER(x)  u16_SwTimer[0]=x
#define MAIN_FSM_TIMER_ELAPSED  (0 == u16_SwTimer[0])

#define LOAD_MINUTE_TIMER(x)    u16_SwTimer[1]=x
#define MINUTE_TIMER_ELAPSED    (0 == u16_SwTimer[1])

// ----------------------------------------------------------------------------
// Declaration of all functions of main
// ----------------------------------------------------------------------------

static void PrepareSleep(void);
static void PrepareRun(void);
static void MySwTimer(void);
static void MainFSM(void);
static void HandleSleep(void);

// ----------------------------------------------------------------------------
// Definition of all fucntions of main
// ----------------------------------------------------------------------------

static void PrepareSleep(void)
{
  TMR0_StopTimer();   // disable timer to avoid wakeup by timer interrupt
  GIE    = 0;         // real interrupt is not necessary for wakeup
  IOCAF  = 0;         // clear all interrupt change flags from port RA
  IOCAN0 = 1;         // enable wakeup by falling edge on RA0
  IOCIE  = 1;         // enable IO change interrupt module
}

static void PrepareRun(void)
{
  IOCAN0 = 0;         // disable interrupt by falling edge on RA0
  IOCIE  = 0;         // disable interrupt module
  IOCAF  = 0;         // clear all interrupt change flags from port RA
  GIE    = 1;         // enable interrupt system again
  
  TMR0_StartTimer();  // enable timer again for basic functionality
  
  u16_MinutesElapsed = 0;       // Reset minute counter 
  ms_MainFSM = MainFSM_Init;    // Reset main FSM
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
static void MainFSM(void)
{
  switch (ms_MainFSM)
  {
    default: 
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
      
    case MainFSM_Init: 
      LED1_ON;
      LOAD_MAIN_FSM_TIMER(LED_ON_TIME);
      ms_MainFSM = MainFSM_Led1;
      break;
    
    case MainFSM_Led1: 
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        LED1_OFF;
        LED2_ON;
        LOAD_MAIN_FSM_TIMER(LED_ON_TIME);
        ms_MainFSM = MainFSM_Led2;
      }
      break;
    
    case MainFSM_Led2: 
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        LED2_OFF;
        LED3_ON;
        LOAD_MAIN_FSM_TIMER(LED_ON_TIME);
        ms_MainFSM = MainFSM_Led3;
      }
      break;
    
    case MainFSM_Led3: 
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        LED3_OFF;
        LOAD_MAIN_FSM_TIMER(LED_OFF_TIME);
        ms_MainFSM = MainFSM_Wait;
      }
      break;
    
    case MainFSM_Wait:
      if(MAIN_FSM_TIMER_ELAPSED)
      {
        ms_MainFSM = MainFSM_Init;
      }
      break;
  }
}

// ----------------------------------------------------------------------------
static void HandleSleep(void)
{
  if (MINUTE_TIMER_ELAPSED  &&      // SW timer counts down from 65000 ms
      MAIN_FSM_IN_WAIT)
  {
    LOAD_MINUTE_TIMER(A_MINUTE);    // Reload for the next minute
    u16_MinutesElapsed++;           // one more minute has elapsed
    
    if (WATER_DETECTED)             // decision depending on current state
    {
      u16_Timeout = WET_OFF_TIME;   // use this timeout if wet ...
      if (FALSE == u1_InWater)      // Edge dry => wet?
      {
        u16_MinutesElapsed = 0;     // yes, rest counter 
      }
    } 
    else
    {
      u16_Timeout = DRY_OFF_TIME;   // use this timeout if dry ...
      if (FALSE != u1_InWater)      // Edge wet => dry?
      {
        u16_MinutesElapsed = 0;     // yes, rest counter 
      }     
    }
    u1_InWater = WATER_DETECTED;    // store current value for edge detection

    if(OFF_TIME_REACHED)            // Time to switch off reached?
    {    
      PrepareSleep();               // enable wakeup on falling edge of RA0     
      SLEEP();                      // stop the system exactly here 
      NOP();                        // proposed to do that after sleep ..
      PrepareRun();                 // set back to normal mode
    }
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
  
  while (TRUE)
  {
    if(FALSE != u1_TimerIsrOcured)        // timer interrupt occurred?
    {
      //LED_3_Toggle();                   // enable to measure ISR freq.
      u1_TimerIsrOcured = FALSE;          // clear local flag from ISR
      MySwTimer();                        // handle all software timers
      MainFSM();                          // perform main function in FSM
      HandleSleep();                      // check and handle system sleep 
    }
  }
}

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------
