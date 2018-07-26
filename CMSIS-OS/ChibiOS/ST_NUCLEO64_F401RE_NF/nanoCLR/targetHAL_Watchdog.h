//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _TARGETHAL_WATCHDOG_H_
#define _TARGETHAL_WATCHDOG_H_ 1

    #if (STM32_LSI_ENABLED == FALSE)
        #error "LSI clock must be enabled for independent watchdog (IWDG) to work"
    #endif

    #if(HAL_USE_WDG == TRUE)

        #define IWATCHDOG_CLK_TYPICAL           32768   //should it be here or in the mcuconf.h

        #define MIN_TIMEOUT_SUPPORTED_MILLIS    1
        #define MAX_TIMEOUT_SUPPORTED_MILLIS    32768

    #endif
#endif