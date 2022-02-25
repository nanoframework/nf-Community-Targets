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
// port: GPIOA, GPIOB
// TX pin: is GPIOA_15
// RX pin: is GPIOB_7
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F411xC and STM32F411xE datasheet)
UART_CONFIG_PINS(1, GPIOA, GPIOB, 15, 7, 7)

// initialization for UART1
UART_INIT(1)

// un-initialization for UART1
UART_UNINIT(1)

///////////
// UART6 //
///////////

// pin configuration for UART6
// port: GPIOA
// TX pin: is GPIOA_11
// RX pin: is GPIOA_12
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F411xC and STM32F411xE datasheet)
UART_CONFIG_PINS(6, GPIOA, GPIOA, 11, 12, 8)

// initialization for UART6
UART_INIT(6)

// un-initialization for UART6
UART_UNINIT(6)
