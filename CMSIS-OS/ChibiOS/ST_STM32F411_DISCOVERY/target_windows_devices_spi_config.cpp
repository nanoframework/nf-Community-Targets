//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "win_dev_spi_native_target.h"

//////////
// SPI1 //
//////////

// pin configuration for SPI1
// port for SCK pin is: SPI1_SCLK
// port for MISO pin is: SPI1_MISO
// port for MOSI pin is: SPI1_MOSI

// GPIO alternate pin function is 5 (see alternate function mapping table in device datasheet)
SPI_CONFIG_PINS(1, GPIOA, 5, GPIOA, 6, GPIOA, 7, 5)

//////////
// SPI2 //
//////////

// pin configuration for SPI2
// port for SCK pin is: SPI2_SCLK
// port for MISO pin is: SPI2_MISO
// port for MOSI pin is: SPI2_MOSI

// GPIO alternate pin function is 5 (see alternate function mapping table in device datasheet)
SPI_CONFIG_PINS(2, GPIOB, 13, GPIOB, 14, GPIOB, 15, 5)
