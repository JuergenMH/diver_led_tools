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
#define WAKE_INPUT_TRIS                 TRISAbits.TRISA0
#define WAKE_INPUT_LAT                  LATAbits.LATA0
#define WAKE_INPUT_PORT                 PORTAbits.RA0
#define WAKE_INPUT_WPU                  WPUAbits.WPUA0
#define WAKE_INPUT_OD                   ODCONAbits.ODCA0
#define WAKE_INPUT_ANS                  ANSELAbits.ANSA0
#define WAKE_INPUT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define WAKE_INPUT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define WAKE_INPUT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define WAKE_INPUT_GetValue()           PORTAbits.RA0
#define WAKE_INPUT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define WAKE_INPUT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define WAKE_INPUT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define WAKE_INPUT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define WAKE_INPUT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define WAKE_INPUT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define WAKE_INPUT_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define WAKE_INPUT_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DEBUG_OUT aliases
#define DEBUT_OUT_TRIS                 TRISAbits.TRISA1
#define DEBUT_OUT_LAT                  LATAbits.LATA1
#define DEBUT_OUT_PORT                 PORTAbits.RA1
#define DEBUT_OUT_WPU                  WPUAbits.WPUA1
#define DEBUT_OUT_OD                   ODCONAbits.ODCA1
#define DEBUT_OUT_ANS                  ANSELAbits.ANSA1
#define DEBUT_OUT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DEBUT_OUT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DEBUT_OUT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DEBUT_OUT_GetValue()           PORTAbits.RA1
#define DEBUT_OUT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DEBUT_OUT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DEBUT_OUT_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define DEBUT_OUT_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define DEBUT_OUT_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define DEBUT_OUT_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define DEBUT_OUT_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DEBUT_OUT_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set LED_1 aliases
#define LED_1_TRIS                 TRISAbits.TRISA2
#define LED_1_LAT                  LATAbits.LATA2
#define LED_1_PORT                 PORTAbits.RA2
#define LED_1_WPU                  WPUAbits.WPUA2
#define LED_1_OD                   ODCONAbits.ODCA2
#define LED_1_ANS                  ANSELAbits.ANSA2
#define LED_1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_1_GetValue()           PORTAbits.RA2
#define LED_1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_1_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED_1_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED_1_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LED_1_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LED_1_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED_1_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED_2 aliases
#define LED_2_TRIS                 TRISAbits.TRISA4
#define LED_2_LAT                  LATAbits.LATA4
#define LED_2_PORT                 PORTAbits.RA4
#define LED_2_WPU                  WPUAbits.WPUA4
#define LED_2_OD                   ODCONAbits.ODCA4
#define LED_2_ANS                  ANSELAbits.ANSA4
#define LED_2_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED_2_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED_2_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED_2_GetValue()           PORTAbits.RA4
#define LED_2_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED_2_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LED_2_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define LED_2_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define LED_2_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define LED_2_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define LED_2_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define LED_2_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set LED_3 aliases
#define LED_3_TRIS                 TRISAbits.TRISA5
#define LED_3_LAT                  LATAbits.LATA5
#define LED_3_PORT                 PORTAbits.RA5
#define LED_3_WPU                  WPUAbits.WPUA5
#define LED_3_OD                   ODCONAbits.ODCA5
#define LED_3_ANS                  ANSELAbits.ANSA5
#define LED_3_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_3_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_3_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_3_GetValue()           PORTAbits.RA5
#define LED_3_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_3_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_3_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_3_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_3_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_3_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_3_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_3_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

void PIN_MANAGER_Initialize (void);

// ----------------------------------------------------------------------------
// End of File
// ----------------------------------------------------------------------------