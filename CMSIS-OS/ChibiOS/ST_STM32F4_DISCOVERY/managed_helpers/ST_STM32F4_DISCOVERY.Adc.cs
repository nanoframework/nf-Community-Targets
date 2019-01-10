//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.ST_STM32F4_DISCOVERY
{
    /// <summary>
    /// Enumeration of ADC channels available on ST_STM32F4_DISCOVERY
    /// </summary>
    public static class AdcChannels
    {
        /// <summary>
        /// Channel 0, connected to PC1 (ADC1 - IN11)
        /// </summary>
        public const int Channel_0 = 0;

        /// <summary>
        /// Channel 1, connected to PC2 (ADC1 - IN12)
        /// </summary>
        public const int Channel_1 = 1;

        /// <summary>
        /// Channel 2, connected to PA6 (ADC2 - IN6)
        /// </summary>
        public const int Channel_2 = 2;

        /// <summary>
        /// Channel 3, connected to PA7 (ADC2 - IN7)
        /// </summary>
        public const int Channel_3 = 3;

        /// <summary>
        /// Channel 4, connected to PB0 (ADC2 - IN8)
        /// </summary>
        public const int Channel_4 = 4;

        /// <summary>
        /// Channel 5, internal temperature sensor, connected to ADC1
        /// </summary>
        public const int Channel_TemperatureSensor = 5;

        /// <summary>
        /// Channel 6, internal voltage reference, connected to ADC1
        /// </summary>
        public const int Channel_VrefIn = 6;

        /// <summary>
        /// Channel 7, connected to VBatt pin, ADC1
        /// </summary>
        public const int Channel_Vbatt = 7;
    }
}
