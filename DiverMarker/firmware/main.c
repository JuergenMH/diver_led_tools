#include "mcc_generated_files/system/system.h"

// Some defines to make code more readable -------------------------------------

#define OffTime               2000u
#define WaitBetween           300u
#define MinOnCycles           5u                  // setup time

#define LoadBlinkTimer(T_u16) {SwTimer1_u16=T_u16;}
#define BlinkTimerElapsed     0==SwTimer1_u16

#define ReedIsOff             (0 != ReedIn_GetValue())
#define MinOnCyclesActive     (0 != MinOnCycles_u08) 
#define MinOnCyclesElapsed    (0 == MinOnCycles_u08)

// module globale variables and flags ------------------------------------------

static const uint8_t GreenTimes[3] = {0, 10, 80};
static const uint8_t RedTimes[3]   = {0, 10, 80};

static uint8_t  TimerFlag_u08 = 0;                // 1 = timer isr occured
static uint8_t  MinOnCycles_u08 = MinOnCycles+1;  // +1 because of -- first
static uint16_t SwTimer1_u16 = 0;                 // two SW timer vars
static uint16_t SwTimer2_u16 = 0;

static uint8_t  GreenOnTime_u08;
static uint8_t  RedOnTime_u08;

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
  Power_Init,
  Power_Low,
  Power_High
} PowerFSM_t;
static PowerFSM_t PowerFSM = Power_Init;

// Coding area from here -------------------------------------------------------
void MyTmr0(void)
{
  TimerFlag_u08 = 1;
}

// -----------------------------------------------------------------------------
void PerformSWTimer(void)
{
  if (0 != SwTimer1_u16) SwTimer1_u16--;  
  if (0 != SwTimer2_u16) SwTimer2_u16--;  
}

// -----------------------------------------------------------------------------

static void HandlePowerOff()
{
  if (ReedIsOff && MinOnCyclesElapsed)   
  {                               
    // prepare sleep
    TMR0_Stop();                  // disable timer (avoid wakeup by timer Int)
    GIE    = 0;                   // real interrupt is not necessary for wakeup
    PORTA;                        // dummy read before clear flags
    IOCAF  = 0;                   // clear interrupt change flags from port RA
    IOCAN2 = 1;                   // enable wakeup by falling edge on RA2
    IOCIE  = 1;                   // enable IO change interrupt module
    SLEEP();                      // stop the system exactly here 
    NOP();                        // proposed to do that after sleep ..
    
    // restart the system    
    IOCAN2 = 0;                   // disable interrupt by falling edge on RA2
    IOCIE  = 0;                   // disable IO interrupt module
    IOCAF  = 0;                   // clear interrupt change flags from port RA
    GIE    = 1;                   // enable interrupt system again
    TMR0_Start();                 // enable timer again for basic functionality
    MinOnCycles_u08 = MinOnCycles;
  }
}

// -----------------------------------------------------------------------------
void PerformBlinkFSM(void)
{
  switch (BlinkFSM) 
  {
    case Blink_Init:
      if (MinOnCyclesActive)              // count the cycles
        MinOnCycles_u08--;                // to ensure a minimum on time
      LoadBlinkTimer(OffTime);            // cycle starts with the off time  
      BlinkFSM = Blink_WaitOffTime;       // go to the wait state "off"
      break;
    
    case Blink_WaitOffTime:               // Cycle part 1: All LEDs are off
      HandlePowerOff();                   // user power off request?
      if (BlinkTimerElapsed)
      {
        GreenOn_SetHigh();                // timer elapsed; next state is green
        LoadBlinkTimer(GreenOnTime_u08);
        BlinkFSM = Blink_GreenIsOn;
      }
      break;
    
    case Blink_GreenIsOn:                 // Cycle part 2: green is on
      if (BlinkTimerElapsed)
      {
        GreenOn_SetLow();                 // time elapsed; next state = wait again
        LoadBlinkTimer(WaitBetween);        
        BlinkFSM = Blink_WaitBetweenGreenAndRed;
      }
      break;
    
    case Blink_WaitBetweenGreenAndRed:    // Cycle part 3 = all off again
      if (BlinkTimerElapsed)
      {
        RedOn_SetHigh();                  // timer elapsed; next state is Red
        LoadBlinkTimer(RedOnTime_u08);        
        BlinkFSM = Blink_RedIsOn;
      }
      break;
      
    case Blink_RedIsOn:                   // Cycle part 4: Red is on
      if (BlinkTimerElapsed)
      {
        RedOn_SetLow();                   // timer elapsed; restart the cycle
        BlinkFSM = Blink_Init;
      }
      break;
    
    default: 
      BlinkFSM =  Blink_Init;    
  }        
}

// -----------------------------------------------------------------------------
void PerformPowerFSM(void)
{
  switch (PowerFSM) 
  {
    case Power_Init:
      PowerFSM = Power_Low;
      break;
    
    case Power_Low:
    if (MinOnCyclesActive && ReedIsOff)     // and user power request?
      {
        MinOnCycles_u08 = MinOnCycles;      // restart the min cycle
        PowerFSM = Power_High;              // and now in high state
      }         
      break;
   
    case Power_High:
      // currently is the high state the final state;
      PowerFSM = Power_High;            // and now in high state
      break;
    
    default:
      PowerFSM = Power_Init;
  }
  GreenOnTime_u08 = GreenTimes[PowerFSM];   // Load times for LEDs 
  RedOnTime_u08   = RedTimes[PowerFSM];     //according FSM State
}

// -----------------------------------------------------------------------------
int main(void)
{
   SYSTEM_Initialize();
    TMR0_OverflowCallbackRegister(MyTmr0);  // hook to own function for timer 0   
    INTERRUPT_GlobalInterruptEnable();      // Enable the Global Interrupts     
    INTERRUPT_PeripheralInterruptEnable();  // Enable the Peripheral Interrupts  
    TMR0_Start();                           // Start the 40uS background timer

    while(1)
    {
      if (0 != TimerFlag_u08)               // one ms elapsed?
      {    
        TimerFlag_u08 = 0;                  // yes, reset the flag
        PerformSWTimer();                   // call the software timer module
        PerformPowerFSM();                  // call the power control FSM
        PerformBlinkFSM();                  // call the blink generator
      }
    }    
}
// End of code area ------------------------------------------------------------

