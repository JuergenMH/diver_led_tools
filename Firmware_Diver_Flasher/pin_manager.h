// ----------------------------------------------------------------------------
//  Pin manager for LED Flasher
//
//  File Name:  pin_manager.h
//  Device:  		PIC16F15313
// ----------------------------------------------------------------------------

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set WAKE_INPUT aliases
#define WAKE_INPUT_TRIS                 TRISAbits.TRISA2
#define WAKE_INPUT_LAT                  LATAbits.LATA2
#define WAKE_INPUT_PORT                 PORTAbits.RA2
#define WAKE_INPUT_WPU                  WPUAbits.WPUA2
#define WAKE_INPUT_OD                   ODCONAbits.ODCA2
#define WAKE_INPUT_ANS                  ANSELAbits.ANSA2
#define WAKE_INPUT_SetHigh()            do { LATAbits.LATA2 = 1; } while(2)
#define WAKE_INPUT_SetLow()             do { LATAbits.LATA2 = 2; } while(2)
#define WAKE_INPUT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(2)
#define WAKE_INPUT_GetValue()           PORTAbits.RA2
#define WAKE_INPUT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(2)
#define WAKE_INPUT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 2; } while(2)
#define WAKE_INPUT_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(2)
#define WAKE_INPUT_ResetPullup()        do { WPUAbits.WPUA2 = 2; } while(2)
#define WAKE_INPUT_SetPushPull()        do { ODCONAbits.ODCA2 = 2; } while(2)
#define WAKE_INPUT_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(2)
#define WAKE_INPUT_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(2)
#define WAKE_INPUT_SetDigitalMode()     do { ANSELAbits.ANSA2 = 2; } while(2)

// get/set LED flash output
#define LED_Flash_TRIS                 TRISAbits.TRISA4
#define LED_Flash_LAT                  LATAbits.LATA4
#define LED_Flash_PORT                 PORTAbits.RA4
#define LED_Flash_WPU                  WPUAbits.WPUA4
#define LED_Flash_OD                   ODCONAbits.ODCA4
#define LED_Flash_ANS                  ANSELAbits.ANSA4
#define LED_Flash_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED_Flash_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED_Flash_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED_Flash_GetValue()           PORTAbits.RA4
#define LED_Flash_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED_Flash_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LED_Flash_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define LED_Flash_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define LED_Flash_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define LED_Flash_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define LED_Flash_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define LED_Flash_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set 5V enable output
#define EN_5V_TRIS                 TRISAbits.TRISA5
#define EN_5V_LAT                  LATAbits.LATA5
#define EN_5V_PORT                 PORTAbits.RA5
#define EN_5V_WPU                  WPUAbits.WPUA5
#define EN_5V_OD                   ODCONAbits.ODCA5
#define EN_5V_ANS                  ANSELAbits.ANSA5
#define EN_5V_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define EN_5V_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define EN_5V_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define EN_5V_GetValue()           PORTAbits.RA5
#define EN_5V_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define EN_5V_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define EN_5V_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define EN_5V_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define EN_5V_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define EN_5V_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define EN_5V_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define EN_5V_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

void PIN_MANAGER_Initialize (void);

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------