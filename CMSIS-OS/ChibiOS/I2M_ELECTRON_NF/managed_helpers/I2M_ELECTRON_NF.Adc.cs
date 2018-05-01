//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.Community.I2M_ELECTRON_NF
{
    /// <summary>
    /// Enumeration of ADC channels available in the community board I2M_ELECTRON_NF
    /// </summary>
    public static class AdcChannels
    {
        /// <summary>
        /// Channel 0, exposed on PA4, connected to PA4 (ADC1 - IN4)
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
}
