 // Diver flasher main module
// ----------------------------------------------------------------------------
#include "mcc_generated_files/system/system.h"

// ----------------------------------------------------------------------------
// debug definitions
// ----------------------------------------------------------------------------
// if enable the ISR will switch on/off the debug output while active
//#define MeasureTmr0

// ----------------------------------------------------------------------------
// module globale defines, typedefs and variables
// ----------------------------------------------------------------------------

// other macros to make code more readable
#define TicsPerMs     25u               // 25 * 40탎 = 1ms
#define LEDOntTime    50u               // LED on for 50ms
#define LEDOffTime    950u              // while developement LED period = 1s
#define TargetCurrent 730               // .. a little bit below 750mA
#define T2PRLoadInit  160u              // controle value start up value (20탎)
#define T2PRLoadMin   80u               // 80 is about 10탎
#define T2PRLoadMax   240u              // 240 is about 30탎

// type definitions 
typedef enum 
{
  Init,
  Idle,
  PulseOn,
  PulseOff        
} MainFSM_t;

// Variables
static int16_t    ActualCurrent_s16;    // current measured in mA
static int16_t    DeviationCurrent_s16; // Deviation = Current - Target
static uint8_t    T2PRLoad_u8;           // calculated reload value for pulse
static uint8_t    MsTimerOccured_u8;    // flag 1ms timer
static uint8_t    MsTimer_u8;           // helper counter for 1m timer
static uint8_t    BoosterActive_u8;     // control pulse output on/off
static uint16_t   SWTimerPeriod_u16;    // SW timer to control the LED period
static MainFSM_t  MainFSM = Init;       // the main FSM for behaviour control

// ----------------------------------------------------------------------------
// Timer callback area
// ----------------------------------------------------------------------------
// Main40탎 timeout => handle the switch output
static void MyTmr0(void)
{
  #ifdef MeasureTmr0
    Debug_SetHigh();
  #endif  
    
  // Basic pulse functionality only if enabled by the main function
  if (0 != BoosterActive_u8)
  {
    // Measure current and calculate a new pulse width
    // VREF=1,024V, Shunt=1Ohm => 10 bit result ist mA
    ActualCurrent_s16 = (int16_t) ADC_GetConversionResult();
    ADC_StartConversion();                    // start next AD
    
    // generate new control value, based on deviation current - target
    if (0 < ActualCurrent_s16-TargetCurrent)  // acutal current too high?
    {                                         // yes, current ist too high
      if (T2PRLoadMin <= T2PRLoad_u8)         // check pulse minimum  
        T2PRLoad_u8--;                        // reduce pulse witdth
    }
    else                                      // current too low       
    {  
      if (T2PRLoadMax >= T2PRLoad_u8)         // check pulse maximum
        T2PRLoad_u8++;                        // increment pulse width
    }  
    // Start a new output pulse 
    Switch_SetHigh();                         // start the pulse
    T2PR = T2PRLoad_u8;                       // load HW timer with period
    TMR2_Start();                             // and prepare pulse stop
  }
  
  // handle the 1m time for the scheduler in main
  if (0 == MsTimer_u8)
  {
    MsTimer_u8 = TicsPerMs; // Reload timer for one ms tic
    MsTimerOccured_u8 = 1;  // and set the flag for the main function
  }
  MsTimer_u8--;
  
  #ifdef MeasureTmr0
    Debug_SetLow();
  #endif 
}

// Pulse timer timeout => switch off the pulse
static void MyTmr2()
{
  Switch_SetLow();    
}

// ----------------------------------------------------------------------------
// other module functions
// ----------------------------------------------------------------------------
static void StartStopBooster(uint8_t Control_u8)
{
  INTERRUPT_GlobalInterruptDisable();   // Make the function atomic
  BoosterActive_u8 = Control_u8;        // set variable to control ISR
  T2PRLoad_u8 = T2PRLoadInit;           // load start value for pulse timer
  INTERRUPT_GlobalInterruptEnable();    // enable the global interrupts again
}

static void DoSWTimer()
{
  if (0!=SWTimerPeriod_u16) SWTimerPeriod_u16--;
}

static void DoMainFSM()
{
  switch(MainFSM)
  {
    case Init:
      MainFSM = Idle;
      break;
      
    case Idle:
      StartStopBooster(1);
      SWTimerPeriod_u16= LEDOntTime;
      MainFSM = PulseOn;
      break;
      
    case PulseOn:                   // LED is in ON state
      if (0 == SWTimerPeriod_u16)   // on timer elapsed?
      {                             // yes, switch to off period
        StartStopBooster(0);
        SWTimerPeriod_u16= LEDOffTime;
        MainFSM = PulseOff;        
      }
      break;
      
    case PulseOff:                  // LED is in OFF state
      if (0 == SWTimerPeriod_u16)   // off timer elapsed?
      {                             // yes, switch to on period
        StartStopBooster(1);
        SWTimerPeriod_u16= LEDOntTime;
        MainFSM = PulseOn;        
      }
      break;
  }
}

// ----------------------------------------------------------------------------
// last: the main function
// ----------------------------------------------------------------------------
int main(void)
{
    SYSTEM_Initialize();
    TMR0_OverflowCallbackRegister(MyTmr0);  // hook to own function for timer 0
    TMR2_OverflowCallbackRegister(MyTmr2);  // dito for timer 2   
    ADC_SelectChannel(Current);             // current input as AD channel
    FVRCON = 0xC1;                          // enable ADC setting for FVR
    INTERRUPT_GlobalInterruptEnable();      // Enable the Global Interrupts     
    INTERRUPT_PeripheralInterruptEnable();  // Enable the Peripheral Interrupts  
    StartStopBooster(0);                    // Switch booster off
    TMR0_Start();                           // Start the 40uS background timer
 
    while(1)                                // Background loop
    {
      if (0 != MsTimerOccured_u8)           // one ms event occured?
      {
        MsTimerOccured_u8 = 0;              // yes, clear the event
        DoSWTimer();                        // handle all SW timer
        DoMainFSM();                        // visible behaviour in this FSM
      }
    }    
}

// ----------------------------------------------------------------------------
// end of module
// ----------------------------------------------------------------------------
