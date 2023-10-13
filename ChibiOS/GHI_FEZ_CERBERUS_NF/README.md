![GHI FEZ CERBERUS](https://github.com/nanoteer/boards/blob/master/GHI_FEZ_CERBERUS_NF/resources/cerberus.jpg)

-----

## Board introduction ##

The board here used is a GHI Fez Cerberus based upon an STM32F405RGT6.  

The code is a fork from the GHI_FEZ_CERB40 [initial port](https://github.com/nanoframework/nf-Community-Targets/tree/master/ChibiOS/GHI_FEZ_CERB40_NF)  

The available pins have been set as can be read in the board.h file and it is there where you can set the pin usage for your required use. Visiting the official site [here](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-high-performance-mcus/stm32f4-series/stm32f405-415/stm32f405rg.html) and per datasheet looking at Table 9. Alternate function mapping you will find possible alternative uses of the various pins. In its initial release the following pin configuration and usage has been verified. Looking at the board from the above (MCU visible) and with the USB connector at the top we have pin 1 on the left hand side.

For more information on the board specifics you can have a look at the [GHI Electronics Cerberus schema](https://github.com/nanoframework/nf-Community-Targets/tree/master/ChibiOS/GHI_FEZ_CERBERUS_NF/resources/cerberus.pdf)

**NOTE: this configuration was successfully tested in a GHI_FEZ_CERBERUS_NF board using the USB Client SP on socket 8.**
