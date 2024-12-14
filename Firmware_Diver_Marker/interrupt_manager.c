// ----------------------------------------------------------------------------
//  Interrupt manager for LED Flasher
//
//  File Name:  interrupt_manager.c
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

#include <xc.h>
#include "interrupt_manager.h"

// ----------------------------------------------------------------------------
// module global variables and defines (scope = interrupt_manager.c)
// ----------------------------------------------------------------------------

extern void TMR0_ISR(void);

// ----------------------------------------------------------------------------
// Definition of all fucntions of interrupt_manager.c
// ----------------------------------------------------------------------------
void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------
