![GHI FEZ CERB40](https://github.com/nanoframework/nf-Community-Targets/blob/master/resources/cerb40.jpg)

## Board introduction ##

The board here used is a GHI Fez Cerb40 based upon an STM32F405RGT6 supporting a 1MB Flash and up to 192KB RAM in a LQFP64 package. On this board the LSE is soldered in case you have a board without the LSE please make sure you have it configured correctly in both the mcuconf.h files for nanoBooter as well as nanoCLR. 

The available pins have been set as can be read in the board.h file and it is there where you can set the pin usage for your required use. Visiting the official site [here](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-high-performance-mcus/stm32f4-series/stm32f405-415/stm32f405rg.html) and per datasheet looking at Table 9. Alternate function mapping you will find possible alternative uses of the various pins. In its initial release the following pin configuration and usage has been verified. Looking at the board from the above (MCU visible) and with the USB connector at the top we have pin 1 on the left hand side.

| Pin | MCU | Usage | Comment |
|:-|---|---|---|
| 01 | VCC | 3.3V | |
| 02 | GND | | |
| 03 | PA8 | | |
| 04 | PA13 | | |
| 05 | PA7 | SPI1 MISO | |
| 06 | PA6 | SPI1 MOSI | |
| 07 | PC10 | | |
| 08 | PA14 | | |
| 09 | PC11 | | |
| 10 | PB4 | | |
| 11 | PB9 | I2C1 SDA | Confirmed and working |
| 12 | PB3 | | |
| 13 | PD2 | | |
| 14 | PC12 | | |
| 15 | VBAT | | |
| 16 | PB8 | I2C1 SCL | Confirmed and working |
| 17 | LODR | | |
| 18 | PB7 | UART1 RX | |
| 19 | PB6 | UART1 TX | |
| 20 | PB5 | GPIO, PWM | GPIO confirmed, PWM not done yet |
| 21 | Reset | | Confirmed |
| 22 | PC0 | | |
| 23 | PC1 | | |
| 24 | PC2 | | |
| 25 | PC3 | | |
| 26 | PA0 | UART2 CTS | |
| 27 | PA1 | UART2 RTS | |
| 28 | PA2 | UART2 TX | |
| 29 | PA3 | UART2 RX | |
| 30 | PA4 | | |
| 31 | PA5 | SPI1 SCK | |
| 32 | PB10 | I2C2 SCL | Confirmed and working |
| 33 | PB11 | I2C2 SDA | Confirmed and working |
| 34 | PB14 | | |
| 35 | PB15 | | |
| 36 | PC6 | | |
| 37 | PC7 | | |
| 38 | PC8 | | |
| 39 | PC9 | | |
| 40 | USB | | |

For more information on the board specifics you can have a look at the [GHI Electronics Cerb40 page](http://old.ghielectronics.com/catalog/product/353)

**NOTE: this configuration was successfully tested in a GHI_FEZ_CERB40_NF board using the Serial over USB connection on USB port 1 that creates a virtual COM port.**
