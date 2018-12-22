//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.Community
{
    public static class ST_NUCLEO144_F412ZG_NF
    {
        public enum OnBoardLeds
        {
            /// <summary>
            /// Output pin connected to the on-board green user LED
            /// </summary>
            public const int GreenLed = PB0;

            /// <summary>
            /// Output pin connected to the on-board blue user LED
            /// </summary>
            public const int BlueLed = PB7;

            /// <summary>
            /// Output pin connected to the on-board red user LED
            /// </summary>
            public const int RedLed = PB14;
        }

    	public static class Gpio
        {
            /// <summary>
            /// 
            /// </summary>
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

            /// <summary>
            /// 
            /// </summary>
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
            public const int PB13 = 29;
            public const int PB14 = 30;
            public const int PB15 = 31;

            /// <summary>
            /// 
            /// </summary>
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

        /// <summary>
        /// Enumeration of ADC channels available on board ST_NUCLEO144_F412ZG_NF
        /// </summary>
        public static class AdcChannels
        {
            /// <summary>
            /// Channel 0, exposed on CN9 Pin 1, connected to PA3 (ADC1 - IN3)
            /// </summary>
            public const int Channel_0 = 0;

            /// <summary>
            /// Channel 1, exposed on CN9 Pin 3, connected to PC0 (ADC1 - IN10)
            /// </summary>
            public const int Channel_1 = 1;

            /// <summary>
            /// Channel 2, exposed on CN9 Pin 5, connected to PC3 (ADC1 - IN13)
            /// </summary>
            public const int Channel_2 = 2;

            /// <summary>
            /// Channel 3, exposed on CN9 Pin 7, connected to PC1 (ADC1 - IN11)
            /// </summary>
            public const int Channel_3 = 3;

            /// <summary>
            /// Channel 4, exposed on CN9 Pin 9, connected to PC4 (ADC1 - IN14)
            /// </summary>
            public const int Channel_4 = 4;

            /// <summary>
            /// Channel 5, exposed on CN9 Pin 11, connected to PC5 (ADC1 - IN15)
            /// </summary>
            public const int Channel_5 = 5;

            /// <summary>
            /// Channel 6, internal temperature sensor, connected to ADC1
            /// </summary>
            public const int Channel_TemperatureSensor = 6;

            /// <summary>
            /// Channel 7, internal voltage reference, connected to ADC1
            /// </summary>
            public const int Channel_VrefIn = 7;

            /// <summary>
            /// Channel 8, connected to VBatt pin, ADC1
            /// </summary>
            public const int Channel_Vbatt = 8;
        }

    }
}
