<img src="https://github.com/nanoframework/nf-Community-Targets/blob/master/CMSIS-OS/ChibiOS/I2M_ELECTRON_NF/resources/IngenuityMicro_Logo.svg?sanitize=true">

## Another community board ##

The board used in this community contribution is a STM32F411CEU6 based board from IngenuityMicro called Electron. The board has only 12 pins of which 3 are already used for 3.3V, 5V and GND, leaving use of only 9 pins.

These pins can be used for:

- 1 x TX/RX (Serial is not tested yet (January 3rd, 2018))
- 4 x PWM
- 4 X ADC (ADC is not tested yet (January 3rd, 2018))
- 1 x I2C
- 1 x SPI

In addition, the board has two on-board LEDs connected to PA1 and PA8 and are tested for use as GPIO, PWM.

Further information can be found on http://www.ingenuitymicro.com/products/electron/ where various firmware, board layout and schema can be found.
