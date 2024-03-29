//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

///////////
// UART1 //
///////////

// enable USART1
#define NF_SERIAL_COMM_STM32_UART_USE_USART1    FALSE

// buffers size
// tx buffer size: 256 bytes
#define UART1_TX_SIZE  256
// rx buffer size: 256 bytes
#define UART1_RX_SIZE  256


///////////
// UART2 //
///////////

// enable USART2
#define NF_SERIAL_COMM_STM32_UART_USE_USART2    TRUE

// buffers size
// tx buffer size: 1024 bytes
#define UART2_TX_SIZE  1024
// rx buffer size: 1024 bytes
#define UART2_RX_SIZE  1024

///////////
// UART3 //
///////////

// enable USART3
#define NF_SERIAL_COMM_STM32_UART_USE_USART3    TRUE

// buffers size
// tx buffer size: 1024 bytes
#define UART3_TX_SIZE  1024
// rx buffer size: 1024 bytes
#define UART3_RX_SIZE  1024
