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
// UART6 //
///////////

// pin configuration for UART6
// port for TX pin is: GPIOG
// port for RX pin is: GPIOG
// TX pin: is GPIOG_14
// RX pin: is GPIOG_9
// GPIO alternate pin function is 8 (see "Table 12. STM32F427xx and STM32F429xx alternate function mapping" in
// STM32F427xx and STM32F429xx datasheet)
UART_CONFIG_PINS(6, GPIOG, GPIOG, 14, 9, 8)

// initialization for UART6
UART_INIT(6)

// un-initialization for UART6
UART_UNINIT(6)
