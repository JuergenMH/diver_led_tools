/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA1 aliases
#define DebugOut_TRIS                 TRISAbits.TRISA1
#define DebugOut_LAT                  LATAbits.LATA1
#define DebugOut_PORT                 PORTAbits.RA1
#define DebugOut_WPU                  WPUAbits.WPUA1
#define DebugOut_OD                   ODCONAbits.ODCA1
#define DebugOut_ANS                  ANSELAbits.ANSA1
#define DebugOut_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DebugOut_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DebugOut_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DebugOut_GetValue()           PORTAbits.RA1
#define DebugOut_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DebugOut_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DebugOut_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define DebugOut_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define DebugOut_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define DebugOut_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define DebugOut_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DebugOut_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define ReedIn_TRIS                 TRISAbits.TRISA2
#define ReedIn_LAT                  LATAbits.LATA2
#define ReedIn_PORT                 PORTAbits.RA2
#define ReedIn_WPU                  WPUAbits.WPUA2
#define ReedIn_OD                   ODCONAbits.ODCA2
#define ReedIn_ANS                  ANSELAbits.ANSA2
#define ReedIn_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ReedIn_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ReedIn_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ReedIn_GetValue()           PORTAbits.RA2
#define ReedIn_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ReedIn_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ReedIn_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ReedIn_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ReedIn_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ReedIn_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ReedIn_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ReedIn_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define GreenOn_TRIS                 TRISAbits.TRISA4
#define GreenOn_LAT                  LATAbits.LATA4
#define GreenOn_PORT                 PORTAbits.RA4
#define GreenOn_WPU                  WPUAbits.WPUA4
#define GreenOn_OD                   ODCONAbits.ODCA4
#define GreenOn_ANS                  ANSELAbits.ANSA4
#define GreenOn_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define GreenOn_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define GreenOn_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define GreenOn_GetValue()           PORTAbits.RA4
#define GreenOn_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define GreenOn_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define GreenOn_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define GreenOn_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define GreenOn_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define GreenOn_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define GreenOn_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define GreenOn_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define BlueOn_TRIS                 TRISAbits.TRISA5
#define BlueOn_LAT                  LATAbits.LATA5
#define BlueOn_PORT                 PORTAbits.RA5
#define BlueOn_WPU                  WPUAbits.WPUA5
#define BlueOn_OD                   ODCONAbits.ODCA5
#define BlueOn_ANS                  ANSELAbits.ANSA5
#define BlueOn_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define BlueOn_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define BlueOn_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define BlueOn_GetValue()           PORTAbits.RA5
#define BlueOn_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define BlueOn_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define BlueOn_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define BlueOn_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define BlueOn_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define BlueOn_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define BlueOn_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define BlueOn_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/