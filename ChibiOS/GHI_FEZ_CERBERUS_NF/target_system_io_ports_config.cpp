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
// TX pin: is GPIOB_6
// RX pin: is GPIOB_7
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F405xx/STM32F407xx datasheet)
UART_CONFIG_PINS(1, GPIOB, GPIOB, 6, 7, 7)

// buffers size
// tx buffer size: 256 bytes
#define UART1_TX_SIZE  256
// rx buffer size: 256 bytes
#define UART1_RX_SIZE  256

// buffers
// buffers that are R/W by DMA are recommended to be aligned with 32 bytes cache page size boundary
// because of issues with cache coherency and DMA (this is particularly important with Cortex-M7 because of cache)
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart1_TxBuffer[UART1_TX_SIZE];
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart1_RxBuffer[UART1_RX_SIZE];

// initialization for UART1
//UART_INIT(1, UART1_TX_SIZE, UART1_RX_SIZE)

// un-initialization for UART1
//UART_UNINIT(1)

///////////
// UART2 //
///////////

// pin configuration for UART2
// port: GPIOA
// TX pin: is GPIOA_2
// RX pin: is GPIOA_3
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F405xx/STM32F407xx datasheet)
UART_CONFIG_PINS(2, GPIOA, GPIOA, 2, 3, 7)

// buffers size
// tx buffer size: 1024 bytes
#define UART2_TX_SIZE  1024
// rx buffer size: 1024 bytes
#define UART2_RX_SIZE  1024

// buffers
// buffers that are R/W by DMA are recommended to be aligned with 32 bytes cache page size boundary
// because of issues with cache coherency and DMA (this is particularly important with Cortex-M7 because of cache)
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart2_TxBuffer[UART2_TX_SIZE];
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart2_RxBuffer[UART2_RX_SIZE];

// initialization for UART2
UART_INIT(2)

// un-initialization for UART2
UART_UNINIT(2)

///////////
// UART3 //
///////////

// pin configuration for UART3
// port: GPIOB
// TX pin: is GPIOB_10
// RX pin: is GPIOB_11
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F405xx/STM32F407xx datasheet)
UART_CONFIG_PINS(3, GPIOB, GPIOB, 10, 11, 7)

// buffers size
// tx buffer size: 1024 bytes
#define UART3_TX_SIZE  1024
// rx buffer size: 1024 bytes
#define UART3_RX_SIZE  1024

// buffers
// buffers that are R/W by DMA are recommended to be aligned with 32 bytes cache page size boundary
// because of issues with cache coherency and DMA (this is particularly important with Cortex-M7 because of cache)
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart3_TxBuffer[UART3_TX_SIZE];
#if defined(__GNUC__)
__attribute__((aligned (32)))
#endif
uint8_t Uart3_RxBuffer[UART3_RX_SIZE];

// initialization for UART3
UART_INIT(3)

// un-initialization for UART3
UART_UNINIT(3)
