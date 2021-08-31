
#include <CPU_Gpio.h>

#if defined(__linux__) && defined(__gpio)

bool CPU_GPIO_Initialize()
{
    // for now supporting only bank 0
    _chip = gpiod_chip_open_by_number(0);

    if (_chip == NULL)
        return false;

    return true;
}

bool CPU_GPIO_Uninitialize()
{
    // no need to unitialize
    return true;
}

void CPU_GPIO_DisablePin(GPIO_PIN Pin, GpioPinDriveMode driveMode,
    uint32_t alternateFunction)
{
    GLOBAL_LOCK();
    CPU_GPIO_SetDriveMode(Pin, driveMode);

    // disable line
    gpiod_line_release(pinLineStored[Pin]);

    GLOBAL_UNLOCK();

    CPU_GPIO_ReservePin(Pin, false);
}

bool CPU_GPIO_EnableOutputPin(GPIO_PIN Pin, GpioPinValue InitialState,
    GpioPinDriveMode driveMode)
{
    // check not an output drive mode
    if (driveMode < (int)GpioPinDriveMode_Output)
        return false;

    if (CPU_GPIO_SetDriveMode(Pin, driveMode) == false)
        return false;

    CPU_GPIO_SetPinState(Pin, InitialState);

    return true;
}

bool CPU_GPIO_EnableInputPin(
    GPIO_PIN pinNumber,
    CLR_UINT64 debounceTimeMilliseconds,
    GPIO_INTERRUPT_SERVICE_ROUTINE pin_ISR,
    void *isr_Param,
    GPIO_INT_EDGE intEdge,
    GpioPinDriveMode driveMode)
{
    // Check Input drive mode
    if (driveMode >= (int)GpioPinDriveMode_Output)
    {
        return false;
    }

    if (pin_ISR != NULL) {
        switch (intEdge)
        {
            case GPIO_INT_EDGE_LOW:
            case GPIO_INT_LEVEL_LOW:
            case GPIO_INT_EDGE_HIGH:
            case GPIO_INT_LEVEL_HIGH:
            case GPIO_INT_EDGE_BOTH:
                // TODO: IRQ callback not implemented
                return false;
                break;

            default:
                break;
        }
    }

    if (!CPU_GPIO_SetDriveMode(pinNumber, driveMode))
    {
        return false;
    }

    // not implemented :: debounce time
    // TODO
    return true;
}

GpioPinValue CPU_GPIO_GetPinState(GPIO_PIN Pin)
{
    if (pinDirStored[Pin] == GpioPinDriveMode_Output)
        return pinLineValue[Pin];
    
    int val = gpiod_line_get_value(pinLineStored[Pin]);
    return val == 1 ? GpioPinValue_High : GpioPinValue_Low;
}

void CPU_GPIO_SetPinState(GPIO_PIN Pin, GpioPinValue PinState)
{
    pinLineValue[Pin] = PinState;
    int val = gpiod_line_set_value(pinLineStored[Pin], PinState);
}

void CPU_GPIO_TogglePinState(GPIO_PIN pinNumber)
{
    GpioPinValue value = CPU_GPIO_GetPinState(pinNumber);

    switch (value)
    {
    case GpioPinValue_High:
        CPU_GPIO_SetPinState(pinNumber, GpioPinValue_Low);
        break;
    case GpioPinValue_Low:
        CPU_GPIO_SetPinState(pinNumber, GpioPinValue_High);
        break;
    default:
        break;
    }
}

bool IsValidGpioPin(GPIO_PIN pinNumber)
{
    return (pinNumber <= GPIO_MAX_PIN);
}

bool CPU_GPIO_PinIsBusy(GPIO_PIN Pin)
{
    return gpiod_line_is_free(pinLineStored[Pin]);
}

bool CPU_GPIO_ReservePin(GPIO_PIN Pin, bool fReserve)
{
    pinLineStored[Pin] = gpiod_chip_get_line(_chip, Pin);

    if (pinLineStored[Pin] == NULL)
        return false;
    
    return true;
}

int32_t CPU_GPIO_GetPinCount()
{
    return GPIO_MAX_PIN;
}

uint32_t CPU_GPIO_GetPinDebounce(GPIO_PIN Pin)
{
    // TODO
    return 0;
}

bool CPU_GPIO_SetPinDebounce(GPIO_PIN pinNumber, CLR_UINT64 debounceTimeMilliseconds)
{
    // TODO
    return true;
}

bool CPU_GPIO_SetDriveMode(GPIO_PIN pinNumber, GpioPinDriveMode driveMode)
{
    if (CPU_GPIO_DriveModeSupported(pinNumber, driveMode)) {
        pinDirStored[pinNumber] = driveMode;

        switch (driveMode)
        {
        case GpioPinDriveMode_Output:
            gpiod_line_request_output(pinLineStored[pinNumber],
                                      "nanoFramework", 0);
            break;
        case GpioPinDriveMode_Input:
            gpiod_line_request_input(pinLineStored[pinNumber],
                                     "nanoFramework");
            break;
        default:
            return false;
            break;
        }

        return true;
    }

    // TODO: complete GpioPinDriveMode support
    return false;
}

bool CPU_GPIO_DriveModeSupported(GPIO_PIN pinNumber, GpioPinDriveMode driveMode)
{
    // TODO
    return true;
}

#endif
