//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _HALCONF_NF_H_
#define _HALCONF_NF_H_ 1

// enables STM32 Flash driver
#if !defined(HAL_NF_USE_STM32_FLASH) 
#define HAL_NF_USE_STM32_FLASH         TRUE
#endif

//  Enables the FSMC subsystem.
#if !defined(HAL_NF_USE_FSMC)
#define HAL_NF_USE_FSMC                FALSE
#endif

// enables STM32 Can driver
#if !defined(HAL_NF_USE_STM32_CAN) 
#define HAL_NF_USE_STM32_CAN           FALSE
#endif

//  STM32F411xx Does not support TRNG
#if !defined(HAL_NF_USE_STM32_RNG)
#define HAL_NF_USE_STM32_RNG           FALSE
#endif

// enables STM32 QSPI driver
#if !defined(HAL_NF_USE_STM32_QSPI)
#define HAL_NF_USE_STM32_QSPI          FALSE
#endif

#endif // _HALCONF_NF_H_
