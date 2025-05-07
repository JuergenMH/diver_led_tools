#include "mcc_generated_files/system/system.h"

// module globale variables and flags ------------------------------------------

static unsigned char TimerFlag_u08 = 0;

// Coding area from here -------------------------------------------------------

void MyTmr0(void)
{
  TimerFlag_u08 = 1;
  DebugOut_Toggle();
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
        TimerFlag_u08 = 0;
      }
    }    
}
// End of code area ------------------------------------------------------------

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    
    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
