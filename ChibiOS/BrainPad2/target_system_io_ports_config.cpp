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
// port: GPIOB
// TX pin: is GPIOA_9
// RX pin: is GPIOA_10
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F401xx datasheet)
UART_CONFIG_PINS(1, GPIOA, GPIOA, 9, 10, 7)

// initialization for UART1
UART_INIT(1)

// un-initialization for UART1
UART_UNINIT(1)

///////////
// UART2 //
///////////

// pin configuration for UART2
// port: GPIOA
// TX pin: is GPIOA_2
// RX pin: is GPIOA_3
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F411xC and STM32F411xE datasheet)
UART_CONFIG_PINS(2, GPIOA, GPIOA, 2, 3, 7)

// initialization for UART2
UART_INIT(2)

// un-initialization for UART2
UART_UNINIT(2)
