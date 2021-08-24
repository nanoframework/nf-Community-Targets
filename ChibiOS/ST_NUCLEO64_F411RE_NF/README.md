# ST Nucleo 64 F411RE NF

The board used in this community contribution is the NUCLEO64_F411RE board from ST. The board can be purchased from various sources and should be about 20 euros. Further information on the Nucleo64 boards can be found in the user manual UM1724 on the ST side (www.st.com). The board used here is of revision c as can be found on the board's lower backside sticker. The board MB1136 C-02 is configured to use ST-LINK MCO as clock input for HSE so we have an HSE of 8 MHz. Plus X2 is mounted we do have an LSE as well. This is reflected in the mcuconf.h in both nanoBooter and nanoCLR paths. If it is chosen to activate LSE as this is a more accurate clock for RTC then board.h file needs to be adjusted accordingly to use 32768 frequency for LSE.

Serial port 2 (USART2) is used to communicate thru the ST-Link connector, so only one Mini-USB cable is used to start the nanoFramework adventure.

The nanoFramework firmware can be flashed using the nanoFramework Firmware Flasher (nanoff) in the package manager console. If you are not familiar with nanoff look on https://github.com/nanoframework/nanoFirmwareFlasher for more info. 

The firmware can still be flashed using the STM32 ST-LINK Utility if you prefer. The device should be visible in the Printf via SWO viewer function in the ST-LINK utility. Please set the frequency to match to what has been set in mcuconf.h (here 96000000) and the Stimulus port to 0 and than hit start. If the board doesn't show then a reset (Black button on board) could be of help or a power cycle by disconnecting, connecting the Mini-USB cable and try ST-LINK Utility again.

In Visual Studio and with nanoFramework extension being installed, open the Device Explorer window and the board should be visible. Select the board and press the Device Capability button. The board specifics should be visible in the output window. 

Now you can start your adventure in the nanoFramework world and use one of the samples and adjust to the board specific features. Try to make a sample of yourself and publish it on f.e. www.hackster.io to show your achievement.

For your convenience listed below are the features currently set and on what pins they can be found to help you out for an easy start. 

Arduino header pins:
====================
 * D0, D1 can not be used as serial connection is used for nanoFramework communication. Plus the required solder bridges are not fitted by default.

 * D2 - D10 can be used for an intermix of GPIO and PWM
 * D11 - D13 are setup and configured for SPI1 however the on board LED (LD2) is connected to D13 as well and might be of influence. In that case solder bridge SB21 needs to be removed. 
 * D14 = I2C1 SDA
 * D15 = I2C1 SCL
 * A0 = ADC1 Channel 1
 * A1 = ADC1 Channel 2
 * A2 = ADC1 Channel 3
 * A3 = ADC1 Channel 4
 * A4 = ADC1 Channel 5
 * A5 = ADC1 Channel 6


Connector CN7:
==============
 * 1 = SPI3 SCK
 * 2 = SPI3 MISO
 * 3 = SPI3 MOSI
 * 17 = USART1 TX
 * 21 = USART1 RX


Connector CN10:
===============
 * 12 = USART6 RX
 * 14 = USART6 TX
 * 26 = SPI2 MOSI
 * 28 = SPI2 MISO
 * 30 = SPI2 SCK

**NOTE: This configuration was successfully tested on a NUCLEO64_F411RE board.**

## Managed helpers

Checkout the [C# managed helpers](https://github.com/nanoframework/nf-Community-Targets/tree/main/ChibiOS/ST_NUCLEO64_F411RE_NF/managed_helpers) available for this board.
