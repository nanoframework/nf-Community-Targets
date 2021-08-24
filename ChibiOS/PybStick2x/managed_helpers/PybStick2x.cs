using System;
using System.Device.Spi;
using System.IO.Ports;
using Windows.Devices.Pwm;

namespace nanoFramework.Targets.PybStick
{
    /// <summary>
    /// This extension class will help opening the right pins
    /// </summary>
    public static class Board
    {
        /// <summary>
        /// Creates a default SPI Device on SPI1 with Chip Select A4.
        /// </summary>
        /// <returns>A SPI Device</returns>
        public static SpiDevice CreateSpi() => CreateSpi(PinNumber('A', 4));

        /// <summary>
        /// Creates a default SPI Device on SPI1 with a custom Chip Select
        /// </summary>
        /// <param name="chipSelect"></param>
        /// <returns>A SPI Device</returns>
        public static SpiDevice CreateSpi(int chipSelect) => SpiDevice.Create(new SpiConnectionSettings(1, chipSelect));

        /// <summary>
        /// Create a Serial Port
        /// </summary>
        /// <returns>A Serial Port</returns>
        public static SerialPort CreateSerial() => new SerialPort("COM2");

        /// <summary>
        /// Create a PWM Pin
        /// </summary>
        /// <param name="pin">The pin number</param>
        /// <param name="frequency">The desired frequency</param>
        /// <returns>A PWM pin</returns>
        public static PwmPin CreatePwm(int pin, double frequency)
        {
            string tim;
            if (pin == PinNumber('A', 0) || pin == PinNumber('A', 2) || pin == PinNumber('A', 3))
            {
                tim = "TIM5";
            }
            else if (pin == PinNumber('B', 0) || pin == PinNumber('B', 1) || pin == PinNumber('B', 4)
                || pin == PinNumber('B', 5) || pin == PinNumber('B', 7))
            {
                tim = "TIM3";
            }
            else if (pin == PinNumber('B', 9) || pin == PinNumber('B', 8) || pin == PinNumber('B', 6))
            {
                tim = "TIM4";
            }
            else if (pin == PinNumber('B', 3) || pin == PinNumber('B', 10) || pin == PinNumber('A', 5)
                || pin == PinNumber('A', 15))
            {
                // In theory tim = "TIM2"; but TIM2 is not activated
                throw new ApplicationException("Can't use TIM2");
            }
            else if (pin == PinNumber('A', 10))
            {
                tim = "TIM1";
            }
            else
            {
                throw new ArgumentException();
            }

            PwmController pwmController = PwmController.FromId(tim);
            pwmController.SetDesiredFrequency(frequency);
            return pwmController.OpenPin(pin);
        }

        /// <summary>
        /// Gets the pin number based on port and pin. Example A5
        /// </summary>
        /// <param name="port">The port</param>
        /// <param name="pin">The port pin</param>
        /// <returns>The pin number</returns>
        public static int PinNumber(char port, byte pin)
        {
            if (port < 'A' || port > 'J')
                throw new ArgumentException();

            return ((port - 'A') * 16) + pin;
        }

        /// <summary>
        /// Get the pin number for the board pin. Example: S5 will be 5
        /// </summary>
        /// <param name="num">The board pin number</param>
        /// <returns>The pin number</returns>
        public static int PinFromBoardNumber(int num)
        {
            switch (num)
            {
                case 3:
                    return PinNumber('B', 9);
                case 5:
                    return PinNumber('B', 8);
                case 7:
                    return PinNumber('B', 6);
                case 8:
                    return PinNumber('A', 2);
                case 10:
                    return PinNumber('A', 3);
                case 11:
                    return PinNumber('B', 3);
                case 12:
                    return PinNumber('A', 0);
                case 13:
                    return PinNumber('B', 10);
                case 15:
                    return PinNumber('B', 12);
                case 16:
                    return PinNumber('B', 13);
                case 18:
                    return PinNumber('B', 14);
                case 19:
                    return PinNumber('A', 7);
                case 21:
                    return PinNumber('B', 4);
                case 22:
                    return PinNumber('A', 10);
                case 23:
                    return PinNumber('A', 5);
                case 24:
                    return PinNumber('A', 15);
                case 26:
                    return PinNumber('A', 4);
                default:
                    throw new ArgumentException();
            }
        }

        /// <summary>
        /// Gets the pin number from the board pin. Example S 5, L 2 (Led 2), B 1 (button 1), P 2 (Led 4)
        /// </summary>
        /// <param name="port">The port</param>
        /// <param name="num">The port number</param>
        /// <returns></returns>
        public static int PinFromBoard(char port, int num)
        {
            if (port == 'S')
            {
                return PinFromBoardNumber(num);
            }

            if (port == 'B')
            {
                if (num == 1)
                {
                    return PinNumber('C', 13);
                }
                else if (num == 2)
                {
                    return PinNumber('B', 6);
                }
                else
                {
                    throw new ArgumentException();
                }
            }

            if (port == 'L')
            {
                switch (num)
                {
                    case 1:
                        return PinNumber('A', 13);
                    case 2:
                        return PinNumber('A', 14);
                    case 3:
                        return PinNumber('B', 0);
                    case 4:
                        return PinNumber('B', 1);
                    default:
                        break;
                }
            }

            if (port == 'P')
            {
                switch (num)
                {
                    case 5:
                        return PinNumber('A', 13);
                    case 4:
                        return PinNumber('A', 14);
                    case 3:
                        return PinNumber('B', 0);
                    case 2:
                        return PinNumber('B', 1);
                    default:
                        break;
                }
            }

            throw new ArgumentException();
        }

    }
}
