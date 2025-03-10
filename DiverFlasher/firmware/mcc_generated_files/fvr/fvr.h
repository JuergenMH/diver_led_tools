/**
 * FVR Generated Driver API Header File.
 * 
 * @file fvr.h
 * 
 * @defgroup fvr FVR
 * 
 * @brief This file contains the API prototypes for the FVR module.
 *
 * @version FVR Driver Version 2.0.1
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef FVR_H
#define FVR_H


/**
  Section: Included Files
*/
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: FVR APIs
*/


/**
 * @ingroup fvr
 * @brief Initializes the FVR module. This is called only once before calling other FVR APIs.
 * @param None.
 * @return None.
 */
 void FVR_Initialize(void);

/**
 * @ingroup fvr
 * @brief Checks if the FVR output is ready.
 * @pre Initialize the FVR before calling this function.
 * @param None.
 * @retval True - FVR module is ready for use.
 * @retval False - FVR module is not ready for use.
 */
bool FVR_IsOutputReady(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // FVR_H
/**
 End of File
*/
