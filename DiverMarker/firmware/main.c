#include "mcc_generated_files/system/system.h"

// remove remark sign to active one of the checks defined below
//#define CheckTimerISR
//#define CheckTimerMain

// Some defines to make code more readable -------------------------------------

#define OffTime             2000u
#define GreenOnTime         40u
#define BlueOnTime          80u
#define WaitBetween         100u
#define MinOnCycles         3u                  // min on cycle count to avoid flicker

#define LoadMainTimer(T_u16) {SwTimer1_u16=T_u16;}
#define MainTimerElapsed     0==SwTimer1_u16

#define ReedIsOff            0!=ReedIn_GetValue()

// module globale variables and flags ------------------------------------------

static uint8_t  TimerFlag_u08 = 0;              // 1 = timer isr occured
static uint8_t  MinOnCycles_u08 = MinOnCycles;  // min cnt of cycles after PO
static uint16_t SwTimer1_u16 = 0;               // two SW timer vars
static uint16_t SwTimer2_u16 = 0;

typedef enum 
{
  Main_Init,
  Main_WaitOffTime,
  Main_GreenIsOn,
  Main_WaitBetweenGreenAndBlue,
  Main_BlueIsOn
} MainFSM_t;
static MainFSM_t MainFSM = Main_Init;

// Coding area from here -------------------------------------------------------
void MyTmr0(void)
{
  TimerFlag_u08 = 1;
  #ifdef CheckTimerISR 
    DebugOut_Toggle(); 
  #endif
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
  if ((ReedIsOff) &&              // user switch off request?  
     (0 == MinOnCycles_u08))      // and minimum on cycles zero 
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
void PerformMainFSM(void)
{
  switch (MainFSM) 
  {
    case Main_Init:
      if (0!= MinOnCycles_u08)          // count the cycles
        MinOnCycles_u08--;              // to ensure a minimum on time
      LoadMainTimer(OffTime);           // cycle starts with the off time  
      MainFSM = Main_WaitOffTime;       // go to the wait state "off"
      break;
    
    case Main_WaitOffTime:              // Cycle part 1: All LEDs are off
      HandlePowerOff();                 // user power off request?
      if (MainTimerElapsed)
      {
        GreenOn_SetHigh();              // timer elapsed; next state is green
        LoadMainTimer(GreenOnTime);
        MainFSM = Main_GreenIsOn;
      }
      break;
    
    case Main_GreenIsOn:                // Cycle part 2: green is on
      if (MainTimerElapsed)
      {
        GreenOn_SetLow();               // time elapsed; next state = wait again
        LoadMainTimer(WaitBetween);        
        MainFSM = Main_WaitBetweenGreenAndBlue;
      }
      break;
    
    case Main_WaitBetweenGreenAndBlue:  // Cycle part 3 = all off again
      if (MainTimerElapsed)
      {
        BlueOn_SetHigh();               // timer elapsed; next state is blue
        LoadMainTimer(BlueOnTime);        
        MainFSM = Main_BlueIsOn;
      }
      break;
      
    case Main_BlueIsOn:                 // Cycle part 4: Blue is on
      if (MainTimerElapsed)
      {
        BlueOn_SetLow();                // timer elapsed; restart the cycle
        MainFSM = Main_Init;
      }
      break;
    
    default: MainFSM =  Main_Init;    
  }        
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
      if (0 != TimerFlag_u08)
      {    
        #ifdef CheckTimerMain 
          DebugOut_Toggle(); 
        #endif
        TimerFlag_u08 = 0;
        PerformSWTimer();
        PerformMainFSM();  
      }
    }    
}
// End of code area ------------------------------------------------------------

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    
    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
