//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <hal.h>
#include <cmsis_os.h>

#include <usbcfg.h>
#include <targetHAL.h>
#include <WireProtocol_ReceiverThread.h>
#include <LaunchCLR.h>

// For printf experiment only 
//#include <chprintf.h>
//#include <chstreams.h>
//#include <string.h>
//#include <stdio.h>

void BlinkerThread(void const * argument)
{
  (void)argument;

  // loop until thread receives a request to terminate
  while (!chThdShouldTerminateX()) {

      //palSetPad(GPIOD, GPIOD_LED3);
      //osDelay(250);

      //palClearPad(GPIOD, GPIOD_LED3);
      //palSetPad(GPIOD, GPIOD_LED5);
      //osDelay(250);

      //palClearPad(GPIOD, GPIOD_LED5);
      //palSetPad(GPIOD, GPIOD_LED6);
      //osDelay(250);

      //palClearPad(GPIOD, GPIOD_LED6);
      palSetPad(GPIOA, GPIOA_LED_GREEN);
      osDelay(250);
      
      palClearPad(GPIOA, GPIOA_LED_GREEN);
      osDelay(250);
  }
  
  // nothing to deinitialize or cleanup, so it's safe to return
}
osThreadDef(BlinkerThread, osPriorityNormal, 128);

// need to declare the Receiver thread here
osThreadDef(ReceiverThread, osPriorityNormal, 1024);

//  Application entry point.
int main(void) {

  osThreadId blinkerThreadId;
  osThreadId receiverThreadId;

  // HAL initialization, this also initializes the configured device drivers
  // and performs the board-specific initializations.
  halInit();

  //chSysInit();

  sdStart(&SD6, NULL);

  palSetPadMode(GPIOC, 6, PAL_MODE_ALTERNATE(8));
  palSetPadMode(GPIOC, 7, PAL_MODE_ALTERNATE(8));

  //chprintf((BaseSequentialStream*)&SD6, "\r\nPeter was here !!!!!\r\n\n");
  //chprintf((BaseSequentialStream*)&SD6, "The color   . . . . %s\r\n", "orange");
  //chprintf((BaseSequentialStream*)&SD6, "First number  . . . %d\r\n", 12345);
  //chprintf((BaseSequentialStream*)&SD6, "Second number . . . %04d\r\n", 25);
  //chprintf((BaseSequentialStream*)&SD6, "Third number  . . . %i\r\n", 1234);
  //chprintf((BaseSequentialStream*)&SD6, "Float number  . . . %3.2f\r\n", 3.14159);
  //chprintf((BaseSequentialStream*)&SD6, "Hexadecimal . . . . %x\r\n", 255);
  //chprintf((BaseSequentialStream*)&SD6, "Octal . . . . . . . %o\r\n", 255);
  //chprintf((BaseSequentialStream*)&SD6, "Unsigned value  . . %u\r\n", 150);

  char data[100];
  float myFloat = 3.14159;

  //sprintf(data, "Float : %f", myFloat);
  streamWrite(&SD6, (uint8_t *) data, strlen(data));
  
  // The kernel is initialized but not started yet, this means that
  // main() is executing with absolute priority but interrupts are already enabled.
  osKernelInitialize();

  //  Initializes a serial-over-USB CDC driver.
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  // Activates the USB driver and then the USB bus pull-up on D+.
  // Note, a delay is inserted in order to not have to disconnect the cable after a reset.
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  // Creates the blinker thread, it does not start immediately.
  blinkerThreadId = osThreadCreate(osThread(BlinkerThread), NULL);

  // create the receiver thread
  receiverThreadId = osThreadCreate(osThread(ReceiverThread), NULL);

  // start kernel, after this the main() thread has priority osPriorityNormal by default
  osKernelStart();

  // Some feedback
  // debug_printf("Booter started, press button ...");

  //  Normal main() thread
  while (true) {

    // check for button pressed
    if (!palReadPad(GPIOC, GPIOC_BUTTON))
    {
      // Some feedback
      // debug_printf("Button pressed ...");
      
      // Start the shutdown sequence

      // terminate threads
      osThreadTerminate(receiverThreadId);
      osThreadTerminate(blinkerThreadId);
      
      // stop the serial-over-USB CDC driver
      sduStop(&SDU1);
      
      // launch nanoCLR
      LaunchCLR(0x08008000);
    }
    
    osDelay(500);
  }
}
