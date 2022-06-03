//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "target_system_io_ports_config.h"
#include <sys_io_ser_native_target.h>

///////////
// UART2 //
///////////

// pin configuration for UART2
// port for TX pin is: GPIOA
// port for RX pin is: GPIOA
// TX pin: is GPIOA_2
// RX pin: is GPIOA_3
// GPIO alternate pin function is 7 (see "Table 9. STM32F405xx and STM32F407xx alternate function mapping" in
// STM32F405xx/STM32F407xx datasheet)
UART_CONFIG_PINS(2, GPIOA, GPIOA, 2, 3, 7)

// initialization for UART2
UART_INIT(2)

// un-initialization for UART2
UART_UNINIT(2)

///////////
// UART3 //
///////////

// pin configuration for UART3
// port for TX pin is: GPIOD
// port for RX pin is: GPIOD
// TX pin: is GPIOD_8
// RX pin: is GPIOD_9
// GPIO alternate pin function is 7 (see "Table 9. STM32F405xx and STM32F407xx alternate function mapping" in
// STM32F405xx/STM32F407xx datasheet)
UART_CONFIG_PINS(3, GPIOD, GPIOD, 8, 9, 7)

UART_INIT(3)

// un-initialization for UART3
UART_UNINIT(3)
