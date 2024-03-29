//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "target_nf_dev_onewire_config.h"
#include <nf_dev_onewire_target.h>

///////////
// UART1 //
///////////

// pin configuration for UART1
// port for TX pin is: GPIOA_9
// port for RX pin is: GPIOB_7
// GPIO alternate pin function is 7 (see "Table 9. Alternate function mapping" in STM32F401RE datasheet)
UART_CONFIG_PINS(1, GPIOA, 9, 7)

// buffers
// buffers that are R/W by DMA are recommended to be aligned with 32 bytes cache page size boundary
// because of issues with cache coherency and DMA (this is particularly important with Cortex-M7 because of cache)
#if defined(__GNUC__)
__attribute__((aligned(32)))
#endif
uint8_t Uart1_TxBuffer[UART1_TX_SIZE];

#if defined(__GNUC__)
__attribute__((aligned(32)))
#endif
uint8_t Uart1_RxBuffer[UART1_RX_SIZE];
