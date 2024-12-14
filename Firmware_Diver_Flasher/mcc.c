// ----------------------------------------------------------------------------
//  Controller configuration for LED Flasher
//
//  File Name:  mcc.c
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "mcc.h"

// ----------------------------------------------------------------------------
// module global variables and defines (scope = mcc.c)
// ----------------------------------------------------------------------------

// CONFIG1
#pragma config FEXTOSC = OFF      // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF     // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = OFF        // Clock Switch Enable bit->Writing to NOSC and NDIV is NOT allowed
#pragma config FCMEN = OFF        // Fail-Safe Clock Monitor Enable bit->FSCM timer disabled

// CONFIG2
#pragma config MCLRE = ON         // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF        // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF      // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF        // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO          // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF          // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON       // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON        // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_31 // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF         // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7  // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC        // WDT input clock selector->Software Control

// CONFIG4
#pragma config BBSIZE = BB512     // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF         // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF        // SAF Enable bit->SAF disabled
#pragma config WRTAPP = OFF       // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF         // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF         // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTSAF = OFF       // Storage Area Flash Write Protection bit->SAF not write protected
#pragma config LVP = ON           // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF           // UserNVM Program memory code protection bit->UserNVM code protection disabled

// ----------------------------------------------------------------------------
// Declaration of all fucntions of interrupt_manager.c
// ----------------------------------------------------------------------------
void PMD_Initialize(void);
void OSCILLATOR_Initialize(void);

// ----------------------------------------------------------------------------
// Definition of all fucntions of interrupt_manager.c
// ----------------------------------------------------------------------------
void PMD_Initialize(void)
{
  PMD0 = 0x00;  // CLKRMD CLKR enabled; SYSCMD SYSCLK enabled; FVRMD FVR enabled; IOCMD IOC enabled; NVMMD NVM enabled;     
  PMD1 = 0x00;  // TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR2MD TMR2 enabled; NCOMD DDS(NCO) enabled;     
  PMD2 = 0x00;  // ZCDMD ZCD enabled; CMP1MD CMP1 enabled; ADCMD ADC enabled; DAC1MD DAC1 enabled;     
  PMD3 = 0x00;  // CCP2MD CCP2 enabled; CCP1MD CCP1 enabled; PWM4MD PWM4 enabled; PWM3MD PWM3 enabled; PWM6MD PWM6 enabled; PWM5MD PWM5 enabled;     
  PMD4 = 0x00;  // CWG1MD CWG1 enabled; MSSP1MD MSSP1 enabled; UART1MD EUSART enabled;    
  PMD5 = 0x00;  // CLC3MD CLC3 enabled; CLC4MD CLC4 enabled; CLC1MD CLC1 enabled; CLC2MD CLC2 enabled; 
}

// ----------------------------------------------------------------------------
void OSCILLATOR_Initialize(void)
{
  OSCCON1 = 0x62; // NOSC HFINTOSC; NDIV 4; 
  OSCCON3 = 0x00; // CSWHOLD may proceed;    
  OSCEN   = 0x00; // MFOEN disabled; LFOEN disabled; ADOEN disabled; EXTOEN disabled; HFOEN disabled;     
  OSCFRQ  = 0x02; // HFFRQ 4_MHz;      
  OSCSTAT = 0x00; // MFOR not ready;    
  OSCTUNE = 0x00; // HFTUN 0; 
}

// ----------------------------------------------------------------------------
void SYSTEM_Initialize(void)
{
  CPUDOZE = 0x00; // ensure IDLEN is set to zero to enable real sleep
  
  PMD_Initialize();
  OSCILLATOR_Initialize();
}

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------