
#include <CPU_Gpio.h>

__nfweak bool CPU_GPIO_Initialize()
{
    return false;
}

__nfweak bool CPU_GPIO_Uninitialize()
{
    return false;
}

__nfweak void CPU_GPIO_DisablePin(GPIO_PIN Pin, GpioPinDriveMode driveMode,
    uint32_t alternateFunction)
{}

__nfweak bool CPU_GPIO_EnableOutputPin(GPIO_PIN Pin, GpioPinValue InitialState,
    GpioPinDriveMode driveMode)
{
    return false;
}

__nfweak bool CPU_GPIO_EnableInputPin(
    GPIO_PIN pinNumber,
    CLR_UINT64 debounceTimeMilliseconds,
    GPIO_INTERRUPT_SERVICE_ROUTINE pin_ISR,
    void *isr_Param,
    GPIO_INT_EDGE intEdge,
    GpioPinDriveMode driveMode)
{
    return false;
}

__nfweak GpioPinValue CPU_GPIO_GetPinState(GPIO_PIN Pin)
{
    return GpioPinValue_Low;
}

__nfweak void CPU_GPIO_SetPinState(GPIO_PIN Pin, GpioPinValue PinState)
{}

__nfweak void CPU_GPIO_TogglePinState(GPIO_PIN pinNumber)
{}

__nfweak bool IsValidGpioPin(GPIO_PIN pinNumber)
{
    return false;
}

__nfweak bool CPU_GPIO_PinIsBusy(GPIO_PIN Pin)
{
    return false;
}

__nfweak bool CPU_GPIO_ReservePin(GPIO_PIN Pin, bool fReserve)
{
    return false;
}

__nfweak int32_t CPU_GPIO_GetPinCount()
{
    return 0;
}

__nfweak uint32_t CPU_GPIO_GetPinDebounce(GPIO_PIN Pin)
{
    return 0;
}

__nfweak bool CPU_GPIO_SetPinDebounce(GPIO_PIN pinNumber, CLR_UINT64 debounceTimeMilliseconds)
{
    return false;
}

__nfweak bool CPU_GPIO_SetDriveMode(GPIO_PIN pinNumber, GpioPinDriveMode driveMode)
{
    return false;
}

__nfweak bool CPU_GPIO_DriveModeSupported(GPIO_PIN pinNumber, GpioPinDriveMode driveMode)
{
    return false;
}
