// ----------------------------------------------------------------------------
//  Pin manager for LED Flasher
//
//  File Name:  pin_manager.c
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA    = 0x00;     // init port A output latch to zero
    TRISA   = 0x04;     // set port complete to output but RA2 (reed, wakeup) 
    ANSELA  = 0x0;      // no analog inputs used
    WPUA    = 0x04;     // internal weak pull on RA2 input
    ODCONA  = 0x00;     // no open drain function
    SLRCONA = 0x37;     // slow rate for all port bits reduced
    INLVLA  = 0x3F;     // Input treshold control to standard values
}
  
// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------