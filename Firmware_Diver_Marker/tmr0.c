// ----------------------------------------------------------------------------
//  Timer0 driver file
//
//  File Name:   	tmr0.c
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

#include <xc.h>
#include "globaldef.h"
#include "tmr0.h"

// ----------------------------------------------------------------------------
// module global variables and defines (scope = tmr0.c)
// ----------------------------------------------------------------------------

extern  u8           u1_TimerIsrOcured;

#define TMR0HValue   (0xFC)

// theoretical value is 0x18, trial and error gives 7B ;-)
//#define TMR0LValue   (0x18)
#define TMR0LValue   (0x7B)

// ----------------------------------------------------------------------------
// Definition of all fucntions of tmr0.c
// ----------------------------------------------------------------------------
void TMR0_Initialize(void)
{  
    T0CON1 = 0x72;              // T0CS HFINTOSC; T0CKPS 1:4; T0ASYNC not synchronised;   
    TMR0H = TMR0HValue;         // TMR0H 252;   
    TMR0L = TMR0LValue;         // TMR0L 24; 
    PIR0bits.TMR0IF = 0;        // Clear Interrupt flag before enabling the interrupt   
    PIE0bits.TMR0IE = 1;        // Enabling TMR0 interrupt.   
    T0CON0 = 0x90;              // T0OUTPS 1:1; T0EN enabled; T016BIT 16-bit; 
}

// ----------------------------------------------------------------------------
void TMR0_ISR(void)
{
    PIR0bits.TMR0IF = 0;        // clear the TMR0 interrupt flag 
    TMR0H = TMR0HValue;         // reload timer
    TMR0L = TMR0LValue;
    
    u1_TimerIsrOcured = TRUE;   // Set flag for main.c
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------
