//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include "win_dev_serial_native.h"

///////////
// UART1 //
///////////

// pin configuration for UART1
// port: GPIOB
// TX pin: is GPIOB_6
// RX pin: is GPIOB_7
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F405xG datasheet)
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
UART_INIT(1, UART1_TX_SIZE, UART1_RX_SIZE)

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
UART_INIT(2, UART2_TX_SIZE, UART2_RX_SIZE)

// un-initialization for UART2
UART_UNINIT(2)

