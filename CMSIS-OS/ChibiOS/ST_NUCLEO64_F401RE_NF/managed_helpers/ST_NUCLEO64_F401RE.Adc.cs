//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.ST_NUCLEO64_F401RE
{
    /// <summary>
    /// Enumeration of ADC channels available on ST_NUCLEO64_F401RE
    /// </summary>
    public static class AdcChannels
    {
        /// <summary>
        /// Channel 0, exposed as A0, connected to pin 1 on CN8 = PA0 (ADC1 - IN0)
        /// </summary>
        public const int Channel_0 = 0;

        /// <summary>
        /// Channel 1, exposed as A1, connected to pin 2 on CN8 = PA1 (ADC1 - IN1)
        /// </summary>
        public const int Channel_1 = 1;

        /// <summary>
        /// Channel 2, exposed as A2, connected to pin 3 on CN8 = PA4 (ADC1 - IN4)
        /// </summary>
        public const int Channel_2 = 2;

        /// <summary>
        /// Channel 3, exposed as A3, connected to pin 4 on CN8 = PB0 (ADC1 - IN8)
        /// </summary>
        public const int Channel_3 = 3;

        /// <summary>
        /// Channel 4, exposed as A4, connected to pin 5 on CN8 = PC1 (ADC1 - IN11)
        /// </summary>
        public const int Channel_4 = 4;

        /// <summary>
        /// Channel 5, exposed on A5, connected to pin 6 on CN8 = PC0 (ADC1 - IN10)
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
