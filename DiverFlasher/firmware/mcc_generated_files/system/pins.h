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

// get/set IO_RA0 aliases
#define IO_RA0_TRIS                 TRISAbits.TRISA0
#define IO_RA0_LAT                  LATAbits.LATA0
#define IO_RA0_PORT                 PORTAbits.RA0
#define IO_RA0_WPU                  WPUAbits.WPUA0
#define IO_RA0_OD                   ODCONAbits.ODCA0
#define IO_RA0_ANS                  ANSELAbits.ANSA0
#define IO_RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_RA0_GetValue()           PORTAbits.RA0
#define IO_RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_RA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_RA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_RA0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_RA0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_RA0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define IO_RA0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define Debug_TRIS                 TRISAbits.TRISA1
#define Debug_LAT                  LATAbits.LATA1
#define Debug_PORT                 PORTAbits.RA1
#define Debug_WPU                  WPUAbits.WPUA1
#define Debug_OD                   ODCONAbits.ODCA1
#define Debug_ANS                  ANSELAbits.ANSA1
#define Debug_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Debug_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Debug_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Debug_GetValue()           PORTAbits.RA1
#define Debug_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Debug_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Debug_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Debug_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Debug_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Debug_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Debug_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define Debug_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define Reed_TRIS                 TRISAbits.TRISA2
#define Reed_LAT                  LATAbits.LATA2
#define Reed_PORT                 PORTAbits.RA2
#define Reed_WPU                  WPUAbits.WPUA2
#define Reed_OD                   ODCONAbits.ODCA2
#define Reed_ANS                  ANSELAbits.ANSA2
#define Reed_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Reed_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Reed_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Reed_GetValue()           PORTAbits.RA2
#define Reed_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Reed_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Reed_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Reed_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Reed_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define Reed_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define Reed_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Reed_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define Current_TRIS                 TRISAbits.TRISA4
#define Current_LAT                  LATAbits.LATA4
#define Current_PORT                 PORTAbits.RA4
#define Current_WPU                  WPUAbits.WPUA4
#define Current_OD                   ODCONAbits.ODCA4
#define Current_ANS                  ANSELAbits.ANSA4
#define Current_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Current_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Current_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Current_GetValue()           PORTAbits.RA4
#define Current_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Current_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Current_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Current_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Current_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define Current_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define Current_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Current_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define Switch_TRIS                 TRISAbits.TRISA5
#define Switch_LAT                  LATAbits.LATA5
#define Switch_PORT                 PORTAbits.RA5
#define Switch_WPU                  WPUAbits.WPUA5
#define Switch_OD                   ODCONAbits.ODCA5
#define Switch_ANS                  ANSELAbits.ANSA5
#define Switch_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Switch_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Switch_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Switch_GetValue()           PORTAbits.RA5
#define Switch_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Switch_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Switch_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define Switch_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define Switch_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define Switch_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define Switch_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define Switch_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
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