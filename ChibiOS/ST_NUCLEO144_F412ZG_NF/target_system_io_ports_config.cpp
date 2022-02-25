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
// GPIO alternate pin function is 7 (see "Table 10. STM32F412xE/G alternate function mapping" in datasheet)
UART_CONFIG_PINS(2, GPIOD, GPIOD, 5, 6, 7)

// initialization for UART2
UART_INIT(2)

// un-initialization for UART2
UART_UNINIT(2)