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
// port for TX pin is: GPIOD
// port for RX pin is: GPIOD
// TX pin: is GPIOD_5
// RX pin: is GPIOD_6
// GPIO alternate pin function is 7 (see "Table for alternate function mapping" in STM32 datasheet)
UART_CONFIG_PINS(2, GPIOD, GPIOD, 5, 6, 7)

// initialization for UART2
UART_INIT(2)

// un-initialization for UART2
UART_UNINIT(2)

///////////
// UART3 //
///////////

// pin configuration for UART3
// port for TX pin is: GPIOC
// port for RX pin is: GPIOC
// TX pin: is GPIOC_6
// RX pin: is GPIOC_7
// GPIO alternate pin function is 7 (see "Table for alternate function mapping" in STM32 datasheet)
UART_CONFIG_PINS(3, GPIOC, GPIOC, 6, 7, 7)

// initialization for UART3
UART_INIT(3)

// un-initialization for UART3
UART_UNINIT(3)

///////////
// UART6 //
///////////

// pin configuration for UART6
// port for TX pin is: GPIOD
// port for RX pin is: GPIOD
// TX pin: is GPIOD_8
// RX pin: is GPIOD_9
// GPIO alternate pin function is 7 (see "Table for alternate function mapping" in STM32 datasheet)
UART_CONFIG_PINS(6, GPIOD, GPIOD, 8, 9, 7)

// initialization for UART6
UART_INIT(6)

// un-initialization for UART6
UART_UNINIT(6)
