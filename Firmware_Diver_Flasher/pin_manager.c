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
    TRISA   = 0x01;     // set port complete to output but RA0 (wakeup) 
    ANSELA  = 0x0;      // no analog inputs used
    WPUA    = 0x01;     // internal weak pull on RA0 input
    ODCONA  = 0x00;     // no poen drain function
    SLRCONA = 0x37;     // slow rate for all port bits reduced
    INLVLA  = 0x3F;     // Input treshold control to standard values
}
  
// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------