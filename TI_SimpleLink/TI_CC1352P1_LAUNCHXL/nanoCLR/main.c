//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <stdint.h>
#include <nanoCLR_Application.h>
#include <nanoHAL_v2.h>

// RTOS header files
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

// clang-format off
#include DeviceFamily_constructPath(inc/hw_prcm.h)
#include DeviceFamily_constructPath(driverlib/sys_ctrl.h)
// clang-format on

// need this until fix in TI SDK is implemented
extern void PIN_init_nano();

//////////////////////////////

// Stack size in bytes
#define THREADSTACKSIZE 2048

Task_Handle receiverHandle;
Task_Handle clrHandle;

CLR_SETTINGS clrSettings;

// this define has to match the one in cpu_gpio.cpp
#define GPIO_MAX_PINS 16

extern void ReceiverThread(UArg arg0, UArg arg1);
extern void CLRStartupThread(UArg arg0, UArg arg1);

int main(void)
{
    Task_Params taskParams;

    // get and store reset reason
    // must be called before PIN_init()
    WakeupReasonStore = SysCtrlResetSourceGet();

    // hack required to be able to config wakeup from deep sleep
    // bug introduced in SDK 5.30.01.01.
    PIN_init_nano();

    // Call board init functions
    // Board_init();
    
    ADC_init();
    ConfigUART();

    // setup Task thread
    Task_Params_init(&taskParams);
    taskParams.stackSize = THREADSTACKSIZE;
    taskParams.priority = 4;

    // create Receiver
    Task_construct(&receiverTask, ReceiverThread, &taskParams, Error_IGNORE);

    // CLR settings to launch CLR thread
    (void)memset(&clrSettings, 0, sizeof(CLR_SETTINGS));

    clrSettings.MaxContextSwitches = 50;
    clrSettings.WaitForDebugger = false;
    clrSettings.EnterDebuggerLoopAfterExit = true;

    // setup CLR task
    taskParams.arg0 = (UArg)&clrSettings;
    taskParams.stackSize = 2 * THREADSTACKSIZE;
    taskParams.priority = 4;

    Task_construct(&clrTask, CLRStartupThread, &taskParams, Error_IGNORE);
    
    BIOS_start();

    return (0);
}

///////////////////////////////////////////////////////////////////////
// need this dummy implementation here (started with SDK 4.20.01.04) //
///////////////////////////////////////////////////////////////////////
void __attribute__((naked)) _exit(int code)
{
    (void)code;

    for (;;)
        ;
}
