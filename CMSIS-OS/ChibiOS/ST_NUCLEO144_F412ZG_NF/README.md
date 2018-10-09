## ST of the shelve board ##

The board used in this community contribution is the NUCLEO144_F412ZG board from ST. The board can be purchased from various sources and should be about 20 euros. Further information on the Nucleo144 boards can be found in the user manuals UM1727 or UM1974 on the ST side (www.st.com). 

Some basic information abstracted from ST:

• STM32F412ZGT6 100MHz Cortex-M4F core microcontroller with 1MB Flash memory, 256KB SRAM
• Adaptive real-time accelerator (ART Accelerator™) allowing 0-wait state execution from Flash memory
• Full access to all GPIO with ST Zio connector (Arduino Uno v3 connectivity support)
• ST morpho extension pin headers for access to all GPIO
• ST-LINK/V2-1 debugger/programmer with SWD connector
• Up to 17 serial communication interfaces: USART, IrDA, I²C, SPI, LIN, CAN, USB, I²S, SDIO
• Flexible board power supply
• USB OTG or FS Device with micro-AB connector
• True random number generator
• CRC calculation unit
• RTC with subsecond accuracy and hardware calendar
• 96-bit unique ID
• 3 x LEDs: Power LED, USB communication, User LED
• User and Reset pushbuttons
• 32.768 KHz crystal oscillator

Since the board has two MicroUSB connectors so you can use one for flashing the nanoFramework firmware and use for debugging purposes on the ST Link side and the other for a connection that can be used against VS to be recognized as a nanoFramework device to run your C# managed application.


