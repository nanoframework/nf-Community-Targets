//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <hal.h>
#include <hal_nf_community.h>
#include <cmsis_os.h>

#include <usbcfg.h>
#include <targetHAL.h>
#include <WireProtocol_ReceiverThread.h>
#include <nanoPAL_BlockStorage.h>
#include <LaunchCLR.h>

// need to declare the Receiver thread here
osThreadDef(ReceiverThread, osPriorityHigh, 2048, "ReceiverThread");

//  Application entry point.
int main(void)
{
    // HAL initialization, this also initializes the configured device drivers
    // and performs the board-specific initializations.
    halInit();

    // init boot clipboard
    InitBootClipboard();

    // check if there is a request to remain on nanoBooter
    if (!IsToRemainInBooter())
    {
        // check for valid CLR image at address contiguous to nanoBooter
        // this target DOES NOT have configuration block, so we need to use the __nanoImage_end__ address here
        if (CheckValidCLRImage((uint32_t)&__nanoImage_end__))
        {
            // there seems to be a valid CLR image
            // launch nanoCLR
            LaunchCLR((uint32_t)&__nanoImage_end__);
        }
    }

    // The kernel is initialized but not started yet, this means that
    // main() is executing with absolute priority but interrupts are already enabled.
    osKernelInitialize();

#if (HAL_NF_USE_STM32_CRC == TRUE)
    // startup crc
    crcStart(NULL);
#endif

    //  Initializes a serial-over-USB CDC driver.
    sduObjectInit(&SERIAL_DRIVER);
    sduStart(&SERIAL_DRIVER, &serusbcfg);

    // Activates the USB driver and then the USB bus pull-up on D+.
    // Note, a delay is inserted in order to not have to disconnect the cable after a reset.
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(100);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    // create the receiver thread
    osThreadCreate(osThread(ReceiverThread), NULL);

    // start kernel, after this main() will behave like a thread with priority osPriorityNormal
    osKernelStart();

    // initialize block storage list and devices
    // in CLR this is called in nanoHAL_Initialize()
    // for nanoBooter we have to init it in order to provide the flash map for Monitor_FlashSectorMap command
    BlockStorageList_Initialize();
    BlockStorage_AddDevices();

    // report successfull nanoBooter execution
    ReportSuccessfullNanoBooter();

    //  Normal main() thread
    while (true)
    {
        palSetPad(GPIOE, GPIOE_LED1);
        osDelay(500);
        palClearPad(GPIOE, GPIOE_LED1);
        osDelay(500);
    }
}
