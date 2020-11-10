//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <Windows.Devices.I2c/win_dev_i2c_native_target.h>

//////////
// I2C1 //
//////////

// pin configuration for I2C1
// port for SCL pin is: GPIOB
// port for SDA pin is: GPIOB
// SCL pin: is GPIOB_6
// SDA pin: is GPIOB_9
// GPIO alternate pin function is 4 (see alternate function mapping table in device datasheet)
I2C_CONFIG_PINS(1, GPIOB, GPIOB, 6, 9, 4)

//////////
// I2C3 //
//////////

// pin configuration for I2C3
// port for SCL pin is: GPIOA
// port for SDA pin is: GPIOC
// SCL pin: is GPIOA_8
// SDA pin: is GPIOC_9
// GPIO alternate pin function is 4 (see alternate function mapping table in device datasheet)
I2C_CONFIG_PINS(3, GPIOA, GPIOC, 8, 9, 4)
