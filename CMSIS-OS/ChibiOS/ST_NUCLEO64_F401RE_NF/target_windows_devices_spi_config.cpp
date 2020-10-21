//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "win_dev_spi_native_target.h"

//////////
// SPI2 //
//////////

// pin configuration for SPI2
// port for SCK pin is: SPI2_SCLK
// port for MISO pin is: SPI2_MISO
// port for MOSI pin is: SPI2_MOSI

// GPIO alternate pin function is 5 (see alternate function mapping table in device datasheet)
SPI_CONFIG_PINS(2, GPIOB, 13, GPIOB, 14, GPIOB, 15, 5)

//////////
// SPI3 //
//////////

// pin configuration for SPI3
// port for SCK pin is: SPI3_SCLK
// port for MISO pin is: SPI3_MISO
// port for MOSI pin is: SPI3_MOSI

// GPIO alternate pin function is 5 (see alternate function mapping table in device datasheet)
SPI_CONFIG_PINS(3, GPIOC, 10, GPIOC, 11, GPIOC, 12, 5)
