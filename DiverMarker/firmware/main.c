/* -----------------------------------------------------------------------------
 *
 * Firmware for DiverMarker
 * Autor: Jürgen Eggeling
 * First version 05.2025
 * 
 * Functional description (basic functions):
 * -----------------------------------------
 * The system is activated from sleep by a falling edge of RA.2
 * On RA.2 there is a reed contact active low; activated by the user
 * 
 * While the reed contact is acitvated the system performs these actions:
 * 
 * 1. Wait for a specific time
 * 2. Switch the green LED on for a specific time
 * 3. Wait again a short time (with no LED activated)
 * 4. Switch the red LED on for a specific time
 * 5. Restart the cycle (goto 1)
 * 
 * If the user removes the magnet (RA.2 goes high) the system will enter 
 * sleep mode gain. This is applicable after the minimum blink cycle count
 * Refer next chapter for details.
 * 
 * Functional descriptin (extended functions):
 * -------------------------------------------
 * 
 * Minimum blink cycle count:
 * If the system is activated one there is a minimum blink count in place
 * This helps to avoid flicker and is the base for the power control
 * 
 * Power control of the LEDs:
 * If the minimum blink count is not reached a reed high => low => high
 * cycle increments the power state from Min => Medium => High
 * The power state controls a PWM to modulate the LED intensity.
 *  
 * -------------------------------------------------------------------------- */
#include "mcc_generated_files/system/system.h"

// -----------------------------------------------------------------------------
// Some defines to make code more readable 
// -----------------------------------------------------------------------------
#define FirstOffTime          500u                // for faster user feed back
#define NormalOffTime         2000u               // pause time blink cycle
#define WaitBetween           300u                // between green and red
#define MinOnCycles           5u                  // min cycle count limit
#define GreenOnTime           50u                 // time LED is on
#define RedOnTime             50u                 // dito

#define LoadBlinkTimer(T_u16) {SwTimer_u16=T_u16;}
#define BlinkTimerElapsed     0==SwTimer_u16

#define ReedIsOff             (0 != ReedIn_GetValue())
#define ReedIsOn              (0 == ReedIn_GetValue())
#define MinOnCyclesActive     (0 != MinOnCycles_u08) 
#define MinOnCyclesElapsed    (0 == MinOnCycles_u08)

// -----------------------------------------------------------------------------
// module globale variables and flags 
// -----------------------------------------------------------------------------
static uint8_t  TimerFlag_u08     = 0;              // 1 = timer isr occured
static uint8_t  GreenIsOnFlag_u08 = 0;              // signal for ISR to control
static uint8_t  RedIsOnFlag_u08   = 0;              // physical outputs in PWM
static uint8_t  MinOnCycles_u08   = MinOnCycles+1;  // +1 because of -- first
static uint8_t  WaitReedOnFlag_u8 = 0;              // Edge power mid => high
static uint16_t SwTimer_u16       = 0;              // only one SW timer var
static uint16_t OffTime_u16       = FirstOffTime;   // pause time is variable  

typedef enum 
{
  Blink_Init,
  Blink_WaitOffTime,
  Blink_GreenIsOn,
  Blink_WaitBetweenGreenAndRed,
  Blink_RedIsOn
} BlinkFSM_t;
static BlinkFSM_t BlinkFSM = Blink_Init;

typedef enum 
{
  Power_Low,
  Power_Medium,
  Power_High
} PowerFSM_t;
static PowerFSM_t PowerFSM = Power_Low;

// Coding area from here -------------------------------------------------------

// -----------------------------------------------------------------------------
// The timer 0 interrupt service routine iperforms two tasks:
// - Set the flag for the main routine to handle all functions necessary 
// -----------------------------------------------------------------------------
void MyTmr0(void)
{  
  TimerFlag_u08 = 1;                      // flag set for main() 
}

// -----------------------------------------------------------------------------
// The Perform_LedPWM is in charge to generate PWM signals for the LEDs
// The function is coupled to the state of the Power FSM!
// There are also two helper functions here to make code more readble
// -----------------------------------------------------------------------------
void SetActiveLedsOn(void)                  // helper function for PerformSwPWM
{
  if (GreenIsOnFlag_u08) GreenOn_SetHigh(); // green on only if active
  if (RedIsOnFlag_u08) RedOn_SetHigh();     // red dito
}

void SetLedsOff(void)                       // helper function for PerformSwPWM
{
  GreenOn_SetLow();                         // first green
  RedOn_SetLow();                           // then red
}

void Perform_LedPWM(void)
{
  static uint8_t PWMCnt = 0;                // helper to generate PWM

  if (!GreenIsOnFlag_u08) GreenOn_SetLow(); // switch off all inactive LEDs
  if (!RedIsOnFlag_u08)   RedOn_SetLow();   //   first green, then red
  switch (PowerFSM)                         // perform software PWM for LEDs
  {
    case Power_Low:                         // @Low: Leds active if PWMCnt = 0
      if (0==PWMCnt) SetActiveLedsOn();     // check for counter content = 0
      else SetLedsOff(); 
      break;
      
    case Power_Medium:                      // @Medium: Leds active if PWMCnt = 0
      if (2>PWMCnt) SetActiveLedsOn();      // check for counter content = 1 or 2
      else SetLedsOff(); 
      break;
      
    case Power_High:                        // @High: Leds active all the time 
      SetActiveLedsOn();                    // no check for counter content = 1 or 2
      break;
  }
  PWMCnt++;                                 // increment counter for PWM generation
  if (3 == PWMCnt) PWMCnt = 0;              // count runs from 0 to 2 only  
}

// -----------------------------------------------------------------------------
// The function HandlePowerOff switches off the product if:
// - the minimium cycle count is elapsed AND 
// - the reed contact is inactive
// -----------------------------------------------------------------------------
static void HandlePowerOff()      // Power off if requested by the user
{
  if (ReedIsOff && MinOnCyclesElapsed)   
  {                               
    // power off request valid => prepare sleep
    TMR0_Stop();                  // disable timer (avoid wakeup by timer Int)
    GIE    = 0;                   // real interrupt is not necessary for wakeup
    PORTA;                        // dummy read before clear flags
    IOCAF  = 0;                   // clear interrupt change flags from port RA
    IOCAN2 = 1;                   // enable wakeup by falling edge on RA2
    IOCIE  = 1;                   // enable IO change interrupt module
    SLEEP();                      // stop the system exactly here 
    NOP();                        // proposed to do that after sleep ..
    
    // reed wake up occured => restart the system    
    IOCAN2 = 0;                   // disable interrupt by falling edge on RA2
    IOCIE  = 0;                   // disable IO interrupt module
    IOCAF  = 0;                   // clear interrupt change flags from port RA
    GIE    = 1;                   // enable interrupt system again
    TMR0_Start();                 // enable timer again for basic functionality
    
    // Releoad some variables necessary for restart
    MinOnCycles_u08   = MinOnCycles;  // restart to enable power control 
    WaitReedOnFlag_u8 = 0;            // clear the flag for edge detection   
    OffTime_u16       = FirstOffTime; // restart with short off period
    PowerFSM          = Power_Low;    // restart in power low mode
  }
}

// -----------------------------------------------------------------------------
// The blink FSM is in charge to perform all the basic functionality of the
// product; eg. it controls the blinking cycle of the LEDs
// -----------------------------------------------------------------------------
void Perform_BlinkFSM(void)
{
  switch (BlinkFSM) 
  {
    case Blink_Init:
      if (MinOnCyclesActive)              // count the cycles
        MinOnCycles_u08--;                // to ensure a minimum on time
      LoadBlinkTimer(OffTime_u16);        // cycle starts with the off time  
      BlinkFSM = Blink_WaitOffTime;       // go to the wait state "off"
      break;
    
    case Blink_WaitOffTime:               // Cycle part 1: All LEDs are off
      HandlePowerOff();                   // user power off request?
      if (BlinkTimerElapsed)
      {
        GreenIsOnFlag_u08 = 1;            // flag to ISR to power green LED
        LoadBlinkTimer(GreenOnTime);
        BlinkFSM = Blink_GreenIsOn;
      }
      break;
    
    case Blink_GreenIsOn:                 // Cycle part 2: green is on
      if (BlinkTimerElapsed)
      {
        GreenIsOnFlag_u08 = 0;            // flag to ISR to unpower green LED
        LoadBlinkTimer(WaitBetween);        
        BlinkFSM = Blink_WaitBetweenGreenAndRed;
      }
      break;
    
    case Blink_WaitBetweenGreenAndRed:    // Cycle part 3 = all off again
      if (BlinkTimerElapsed)
      {
        RedIsOnFlag_u08 = 1;              // flag to ISR to power red LED
        LoadBlinkTimer(RedOnTime);        
        BlinkFSM = Blink_RedIsOn;
      }
      break;
      
    case Blink_RedIsOn:                   // Cycle part 4: Red is on
      if (BlinkTimerElapsed)
      {
        RedIsOnFlag_u08 = 0;              // flag to ISR to unpower red LED
        BlinkFSM = Blink_Init;
      }
      break;
    
    default: 
      BlinkFSM =  Blink_Init;    
  }    
  OffTime_u16 = NormalOffTime;            // Off time longer after cycle 1...
}

// -----------------------------------------------------------------------------
// The Power FSM is in place to control the power modes requested by the user.
// -----------------------------------------------------------------------------
void Perform_PowerFSM(void)
{
  switch (PowerFSM) 
  {
    case Power_Low:                         // min cycle still active AND
    if (MinOnCyclesActive && ReedIsOff)     // and user power request?
      {
        MinOnCycles_u08   = MinOnCycles;    // restart the min cycle
        WaitReedOnFlag_u8 = 1;              // set flag for next state 
        PowerFSM          = Power_Medium;   // and now in medium state
      }         
      break;

    case Power_Medium:                      // entry from Power_low, reed may still low!
      if (WaitReedOnFlag_u8)                // flag still set?
      {
        if (ReedIsOn)                       // reset flag in case of 
          WaitReedOnFlag_u8 = 0;            // reed is active again
      }
      else                                  // from here "normal" operation
      {
        if (ReedIsOff && MinOnCyclesActive) // request if both are true
          PowerFSM = Power_High;            // and now in high state                   
      }
      break;

    case Power_High:                        // high state = final state;
      PowerFSM = Power_High;                // .. only for debugging
      break;                                // to enable breakpoints
    
    default:
      PowerFSM = Power_Low;
  }
}

// -----------------------------------------------------------------------------
// Classic short main function
// -----------------------------------------------------------------------------
int main(void)
{
  SYSTEM_Initialize();                    // Call mcc generated files once
  TMR0_OverflowCallbackRegister(MyTmr0);  // hook to own function for timer 0   
  INTERRUPT_GlobalInterruptEnable();      // Enable the Global Interrupts     
  INTERRUPT_PeripheralInterruptEnable();  // Enable the Peripheral Interrupts  
  TMR0_Start();                           // Start the 1ms timer
  while(1)                                // endless loop frome here 
  {
    if (0 != TimerFlag_u08)               // one ms elapsed?
    {    
      DebugOut_SetHigh();
      TimerFlag_u08 = 0;                  // yes, reset the flag
      if (0!=SwTimer_u16) SwTimer_u16--;  // currently one timer is enough

      Perform_LedPWM();                   // perform SW PWM for the LEDs
      Perform_PowerFSM();                 // call the power control FSM
      Perform_BlinkFSM();                 // call the blink generator
      DebugOut_SetLow();
    }
  }    
}
// End of code area ------------------------------------------------------------

