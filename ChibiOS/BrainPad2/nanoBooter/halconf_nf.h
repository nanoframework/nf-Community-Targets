//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef HALCONF_NF_H
#define HALCONF_NF_H

// enables STM32 Flash driver
#if !defined(HAL_NF_USE_STM32_FLASH) 
#define HAL_NF_USE_STM32_FLASH         TRUE
#endif

#if !defined(HAL_NF_USE_STM32_RNG)
#define HAL_NF_USE_STM32_RNG           FALSE
#endif

#endif // HALCONF_NF_H

