//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "target_system_io_ports_config.h"
#include <sys_io_ser_native_target.h>

///////////
// UART6 //
///////////

// pin configuration for UART6
// port: GPIOA
// TX pin: is GPIOA_11
// RX pin: is GPIOA_12
// GPIO alternate pin function is 8 (see "Table 9. Alternate function mapping" in STM32F401xC and STM32F401xE datasheet)
UART_CONFIG_PINS(6, GPIOA, GPIOA, 11, 12, 8)

// initialization for UART6
UART_INIT(6)

// un-initialization for UART6
UART_UNINIT(6)
