//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
using System;
using Windows.Devices.Gpio;

namespace STM32F4.Pins
{
    public static class Pinouts
    {
        static int PinNumber(char port, byte pin)
        {
            if (port < 'A' || port > 'J')
                throw new ArgumentException();

            return ((port - 'A') * 16) + pin;
        }
    }

    public static class BrainPad2
    {
      
        public static void AllLedOff()
        {
            GpioPin l1 = GpioController.GetDefault().OpenPin(41);
            GpioPin l2 = GpioController.GetDefault().OpenPin(38);
            GpioPin l3 = GpioController.GetDefault().OpenPin(40);

            l1.SetDriveMode(GpioPinDriveMode.Output);
            l2.SetDriveMode(GpioPinDriveMode.Output);
            l3.SetDriveMode(GpioPinDriveMode.Output);

            l1.Write(GpioPinValue.Low);
            l2.Write(GpioPinValue.Low);
            l3.Write(GpioPinValue.Low);

            l1.Dispose();
            l2.Dispose();
            l3.Dispose();
        }

        /// <summary>
        /// Enumeration of ADC channels available on ST_NUCLEO64_F411RE_NF
        /// </summary>
        public static class AdcChannels
        {
            /// <summary>
            /// Channel 0, exposed on PA4, connected to PA4 (ADC1 - IN4) //to be modified to PB0
            /// </summary>
            public const int Channel_0 = 0;

            /// <summary>
            /// Channel 1, exposed on PA5, connected to PA5 (ADC1 - IN5)
            /// </summary>
            public const int Channel_1 = 1;

            /// <summary>
            /// Channel 2, internal temperature sensor, connected to ADC1
            /// </summary>
            public const int Channel_TemperatureSensor = 2;

            /// <summary>
            /// Channel 3, internal voltage reference, connected to ADC1
            /// </summary>
            public const int Channel_VrefIn = 3;

            /// <summary>
            /// Channel 4, connected to VBatt pin, ADC1
            /// </summary>
            public const int Channel_Vbatt = 4;
        }

        /// <summary>
        ///  GPIO class represent mapped info and values on 
        /// </summary>

        public static class Gpio
        {
            public const int PA0 = 0;
            public const int PA1 = 1; 
            public const int PA2 = 2; 
            public const int PA3 = 3; 
            public const int PA4 = 4; 
            public const int PA5 = 5; 
            public const int PA6 = 6; 
            public const int PA7 = 7; 
            public const int PA8 = 8; 
            public const int PA9 = 9; 
            public const int PA10 = 10; 
            public const int PA11 = 11;
            public const int PA12 = 12;
            public const int PA13 = 13;
            public const int PA14 = 14;
            public const int PA15 = 15;

            public const int PB0 = 16;  
            public const int PB1 = 17;
            public const int PB2 = 18;
            public const int PB3 = 19;  
            public const int PB4 = 20;  
            public const int PB5 = 21;  
            public const int PB6 = 22;
            public const int PB7 = 23;
            public const int PB8 = 24;  
            public const int PB9 = 25;  
            public const int PB10 = 26;  
            public const int PB11 = 27;
            public const int PB12 = 28;
            public const int PB13 = 28;
            public const int PB14 = 30;
            public const int PB15 = 31;

            public const int PC0 = 32;  
            public const int PC1 = 33;  
            public const int PC2 = 34;
            public const int PC3 = 35;
            public const int PC4 = 36;
            public const int PC5 = 37;
            public const int PC6 = 38;
            public const int PC7 = 39;  
            public const int PC8 = 40;
            public const int PC9 = 41;
            public const int PC10 = 42;
            public const int PC11 = 43;
            public const int PC12 = 44;
            public const int PC13 = 45; 
            public const int PC14 = 46;
            public const int PC15 = 47;

        }

    
        public static class SpiDevice
        {
            public static class SpiDevices
            {
                public const string Name = "SPI1";
                public const int MOSI = Gpio.PB5;
                public const int MISO = Gpio.PB4;
                public const int SCK = Gpio.PB3;
            }
        }

        public static class Buttons
        {
            public static int ButtonUp = Gpio.PA5;
            public static int ButtonLeft = Gpio.PA15;
            public static int ButtonRight = Gpio.PC13;
            public static int ButtonDown = Gpio.PB10;
        }

        public static class Accelearator
        {
            public static string Name = "I2C1";
            public static int SCL = Gpio.PB6;
            public static int SDA = Gpio.PB7;
            public static int SlaveAddress = 2;
        }

        public static class Buzzer
        {
            public static int Pin = Gpio.PB8;
        }

        public static class Light
        {
            public static int Red = Gpio.PC9;    //41
            public static int Blue = Gpio.PC6;   //38
            public static int Greeen = Gpio.PC8; //40
        }


        public static class TemperatureSensor
        {
            public static int Pin = Gpio.PB0;
        }

        public static class LightMeterSensor
        {
            public static int Pin = Gpio.PB1;
        }



        public static class OledDisplay
        {
            public static string Device = "I2C1";
            public static int Width = 128;
            public static int Height = 64;
            public static int SlaveAddress = 0x3C;
        }

        public class I2CDevices
        {
            struct I2C1
            {
                public const string Name = "I2C1";
                public const int SCL = Gpio.PB6;
                public const int SDA = Gpio.PB7;
            }
        }

        public class ComDevices
        {
            struct COM1
            {
                public const string Name = "COM1";
                public const int Tx = Gpio.PA9;
                public const int Rx = Gpio.PA10;
            }

            struct COM2
            {
                public const string Name = "COM2";
                public const int Tx = Gpio.PA2;
                public const int Rx = Gpio.PA3;
            }
        }

        
    }
}