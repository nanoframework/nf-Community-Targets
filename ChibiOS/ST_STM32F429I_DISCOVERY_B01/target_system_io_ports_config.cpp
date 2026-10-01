//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "target_system_io_ports_config.h"
#include <sys_io_ser_native_target.h>

///////////
// UART1 //
///////////

// pin configuration for UART1
// port for TX pin is: GPIOA
// port for RX pin is: GPIOA
// TX pin: is GPIOA_9
// RX pin: is GPIOA_10
// GPIO alternate pin function is 7 (see "Table 12. STM32F427xx and STM32F429xx alternate function mapping" in
// STM32F427xx and STM32F429xx datasheet)
UART_CONFIG_PINS(1, GPIOA, GPIOA, 9, 10, 7)

// initialization for UART1
UART_INIT(1)

// un-initialization for UART1
UART_UNINIT(1)

///////////
// UART5 //
///////////

// pin configuration for UART5
// port for TX pin is: GPIOC
// port for RX pin is: GPIOD
// TX pin: is GPIOC_12
// RX pin: is GPIOD_2
// GPIO alternate pin function is 8 (see "Table 12. STM32F427xx and STM32F429xx alternate function mapping" in
// STM32F427xx and STM32F429xx datasheet)
// (USART3 default pins PD8/PD9 are used by the FMC SDRAM)
UART_CONFIG_PINS(5, GPIOC, GPIOD, 12, 2, 8)

// initialization for UART5
UART_INIT(5)

// un-initialization for UART5
UART_UNINIT(5)
