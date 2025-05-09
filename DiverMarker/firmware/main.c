#include "mcc_generated_files/system/system.h"

// remove remark sign to active one of the checks defined below
//#define CheckTimerISR
//#define CheckTimerMain

// module globale variables and flags ------------------------------------------

static unsigned char TimerFlag_u08 = 0;
static unsigned int SwTimer1_u16 = 0;
static unsigned int SwTimer2_u16 = 0;

typedef enum 
{
  Main_Init,
  Main_WaitOffTime,
  Main_GreenIsOn,
  Main_WaitBetweenGreenAndBlue,
  Main_BlueIsOn
} MainFSM_t;

static MainFSM_t MainFSM = Main_Init;

// Some defines to make code more readable -------------------------------------

#define OffTime             2000u
#define GreenOnTime         40u
#define BlueOnTime          80u
#define WaitBetween         100u

#define LoadMainTimer(Time_u16) { SwTimer1_u16 = Time_u16; }
#define MainTimerElapsed        0 == SwTimer1_u16

// Coding area from here -------------------------------------------------------

void MyTmr0(void)
{
  TimerFlag_u08 = 1;
  #ifdef CheckTimerISR 
    DebugOut_Toggle(); 
  #endif
}

void PerformSWTimer(void)
{
  if (0 != SwTimer1_u16) SwTimer1_u16--;  
  if (0 != SwTimer2_u16) SwTimer2_u16--;  
}

void PerformMainFSM(void)
{
  switch (MainFSM) 
  {
    case Main_Init:
      LoadMainTimer(OffTime);
      MainFSM = Main_WaitOffTime;
      break;
    
    case Main_WaitOffTime:  
      if (MainTimerElapsed)
      {
        GreenOn_SetHigh();
        LoadMainTimer(GreenOnTime);
        MainFSM = Main_GreenIsOn;
      }
      break;
    
    case Main_GreenIsOn:
      if (MainTimerElapsed)
      {
        GreenOn_SetLow();
        LoadMainTimer(WaitBetween);        
        MainFSM = Main_WaitBetweenGreenAndBlue;
      }
      break;
    
    case Main_WaitBetweenGreenAndBlue:
      if (MainTimerElapsed)
      {
        BlueOn_SetHigh();
        LoadMainTimer(BlueOnTime);        
        MainFSM = Main_BlueIsOn;
      }
      break;
      
    case Main_BlueIsOn:
      if (MainTimerElapsed)
      {
        BlueOn_SetLow();
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
