
#include <CPU_Gpio.h>

#if defined(__nuttx__)
#include <nuttx/config.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <nuttx/ioexpander/gpio.h>
#endif

#define GPIO_MAX_PIN        30
#define TOTAL_GPIO_PORTS    1

static GpioPinDriveMode pinDirStored[GPIO_MAX_PIN];

#if defined(__nuttx__)

static int openGpioCharDev(GPIO_PIN Pin)
{
    // strlen /dev/gpout100 = 13
    // I think 20 is a good size
    char devpath[20];
    int fd;
    int ret;

    if (pinDirStored[Pin] == GpioPinDriveMode_Output)
        sprintf(devpath, "/dev/gpout%d", Pin);
    else
        sprintf(devpath, "/dev/gpin%d", Pin);

    fd = open(devpath, O_RDWR);

    if (fd < 0)
    {
      int errcode = errno;
      fprintf(stderr, "ERROR: Failed to open %s: %d\n", devpath, errcode);
      exit(EXIT_FAILURE);
    }

    return fd;
}

static gpio_pintype_e getGpioCharDevType(int fd)
{
    enum gpio_pintype_e pintype;
    int ret;

    ret = ioctl(fd, GPIOC_PINTYPE, (unsigned long)((uintptr_t)&pintype));
    if (ret < 0)
    {
      int errcode = errno;
      fprintf(stderr, "ERROR: Failed to read pintype %d\n", errcode);
      close(fd);
      exit(EXIT_FAILURE);
    }

    return pintype;
}

static bool getGpioCharDevInValue(int fd)
{
    bool invalue;
    int ret;

    ret = ioctl(fd, GPIOC_READ, (unsigned long)((uintptr_t)&invalue));
    if (ret < 0)
    {
        int errcode = errno;
        fprintf(stderr, "ERROR: Failed to read value %d\n", errcode);
        close(fd);
        exit(EXIT_FAILURE);
    }

    return invalue;
}

static void setGpioCharDevOutValue(int fd, bool outvalue)
{
    int ret;

    ret = ioctl(fd, GPIOC_WRITE, (unsigned long)outvalue);
    if (ret < 0)
    {
        int errcode = errno;
        fprintf(stderr,
                "ERROR: Failed to write value %u err %d\n",
                (unsigned int)outvalue, errcode);
        close(fd);
        exit(EXIT_FAILURE);
    }
}

#endif

bool CPU_GPIO_Initialize()
{
    // for nuttx it's not needed for now because this is handled by char dev
    // TODO: Nuttx generic char device

    return true;
}

bool CPU_GPIO_Uninitialize()
{
    // for nuttx it's not needed for now because this is handled by char dev
    // TODO: Nuttx generc char device

    return true;
}

void CPU_GPIO_DisablePin(GPIO_PIN Pin, GpioPinDriveMode driveMode,
    uint32_t alternateFunction)
{
    GLOBAL_LOCK();
    CPU_GPIO_SetDriveMode(Pin, driveMode);

    // TODO
    // set PIN to alternateFunction

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
#if defined(__nuttx__)
    int fd;
    enum gpio_pintype_e pintype;
    bool invalue;

    fd = openGpioCharDev(Pin);
    //pintype = getGpioCharDevType(fd);
    invalue = getGpioCharDevInValue(fd);
    close(fd);

    return invalue == 1 ? GpioPinValue_High : GpioPinValue_Low;
#else
    printf("CPU_GPIO_GetPinState :: %d\n", Pin);
    return GpioPinValue_Low;
#endif
}

void CPU_GPIO_SetPinState(GPIO_PIN Pin, GpioPinValue PinState)
{
#if defined(__nuttx__)
    int fd;
    enum gpio_pintype_e pintype;
    bool invalue;

    fd = openGpioCharDev(Pin);
    pintype = getGpioCharDevType(fd);
    
    if (pintype == GPIO_OUTPUT_PIN)
    {
        switch (PinState)
        {
        case GpioPinValue_High:
            setGpioCharDevOutValue(fd, true);
            break;
        case GpioPinValue_Low:
            setGpioCharDevOutValue(fd, false);
            break;
        default:
            break;
        }
    }

    close(fd);

    // TODO error?
#else
    printf("CPU_GPIO_SetPinState :: %d to val=%d\n", Pin, PinState);
#endif
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
    // TODO
    return IsValidGpioPin(Pin);
}

bool CPU_GPIO_ReservePin(GPIO_PIN Pin, bool fReserve)
{
    // TODO
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

#if defined(__linux__)
    printf("Setting pin::%d to driveMode::%d\n", pinNumber, driveMode);
    printf("Checking pinDriveMode %d\n", pinDirStored[pinNumber]);
#endif

        return true;
    }

    // TODO
    // this appears to be not possible today on Nuttx, it's predefined on driver
    return false;
}

bool CPU_GPIO_DriveModeSupported(GPIO_PIN pinNumber, GpioPinDriveMode driveMode)
{
#if defined(__nuttx__)
    int fd;
    enum gpio_pintype_e pintype;

    fd = openGpioCharDev(pinNumber);
    pintype = getGpioCharDevType(fd);
    close(fd);

    switch (pintype)
    {
    case GPIO_INPUT_PIN:
        return driveMode == GpioPinDriveMode_Input;
        break;
    case GPIO_INPUT_PIN_PULLUP:
        return driveMode == GpioPinDriveMode_InputPullUp;
        break;
    case GPIO_INPUT_PIN_PULLDOWN:
        return driveMode == GpioPinDriveMode_InputPullDown;
        break;
    case GPIO_OUTPUT_PIN:
    case GPIO_OUTPUT_PIN_OPENDRAIN:
        return driveMode == GpioPinDriveMode_Output;
        break;
    default:
        break;
    }

    return false;
#else
    // playground all possible
    return true;
#endif
}
