## STM32F429I-DISCOVERY board (hardware revision B01)

[Product page](https://www.st.com/en/evaluation-tools/32f429idiscovery.html)

> [!IMPORTANT]
> This firmware is meant **only** for the older STM32F429I-DISCOVERY boards (MB1075) with hardware revision **B01** (and C01/D01), where the ST-LINK doesn't provide a Virtual COM port.
> The hardware revision is printed on the sticker at the bottom of the board.

Some basic information abstracted from ST:

- STM32F429ZIT6 microcontroller featuring 32-bit ARM®Cortex®-M4 with FPU core, 2-Mbyte Flash memory, 256-kbyte RAM in an LQFP144 package
- On-board ST-LINK/V2
- 2.4" QVGA TFT LCD
- 64-Mbit SDRAM
- L3GD20 ST MEMS motion sensor, 3-axis digital output gyroscope
- Six LEDs, two push-buttons (user and reset)
- USB OTG with micro-AB connector

## Flashing and debugging

This board has one mini USB connector exposing the embedded ST-Link interface that is used for flashing the nanoFramework firmware and for performing debugging on the nanoCLR code.
The second USB connector (a micro USB one, CN6) is used to connect the device with Visual Studio (USB CDC virtual COM port) allowing to deploy and debug your C# managed applications.

## Configuration of Chibios, HAL and MCU

For a successful build the following changes are required:

In _halconf.h_ (in both nanoBooter and nanoCLR folders), when compared with a default file:

- HAL_USE_SERIAL_USB to TRUE
- HAL_USE_USB to TRUE

In _mcuconf.h_ (in both nanoBooter and nanoCLR folders), when compared with a default file:

- STM32_USB_USE_OTG2 to TRUE

In _chconf.h_ (_**only**_ for nanoCLR folder), when compared with a default file:

- set the CORTEX_VTOR_INIT with the appropriate address of the vector table for nanoCLR

## Floating point

The current build is set to add support for single-precision floating point.
Meaning that `System.Math` API supports only the `float` overloads. The `double` ones will throw a `NotImplementedException`.

## Firmware images (ready to deploy)

[![Latest Version @ Cloudsmith](https://api-prd.cloudsmith.io/v1/badges/version/net-nanoframework/nanoframework-images-community-targets/raw/ST_STM32F429I_DISCOVERY_B01/latest/x/?render=true)](https://cloudsmith.io/~net-nanoframework/repos/nanoframework-images-community-targets/packages/detail/raw/ST_STM32F429I_DISCOVERY_B01/latest/)

## Managed helpers

Checkout the [C# managed helpers](https://github.com/nanoframework/nf-interpreter/tree/main/targets/ChibiOS/ST_STM32F429I_DISCOVERY/managed_helpers) available for this board.
