//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.Community.GHI_FEZ_CERB40_NF
{
    /// <summary>
    /// Enumeration of ADC channels available in the community board GHI_FEZ_CERB40_NF
    /// </summary>
    public static class AdcChannels
    {
        /// <summary>
        /// Channel 0, exposed on PC0, connected to PC0 (ADC2 - IN10)
        /// </summary>
        public const int Channel_0 = 0;

        /// <summary>
        /// Channel 1, exposed on PA1, connected to PA1 (ADC2 - IN11)
        /// </summary>
        public const int Channel_1 = 1;

        /// <summary>
        /// Channel 2, exposed on PA4, connected to PA4 (ADC3 - IN12)
        /// </summary>
        public const int Channel_2 = 2;

        /// <summary>
        /// Channel 3, exposed on PC3, connected to PC3 (ADC3 - IN13)
        /// </summary>
        public const int Channel_3 = 3;

        /// <summary>
        /// Channel 4, internal temperature sensor, connected to ADC1
        /// </summary>
        public const int Channel_TemperatureSensor = 4;

        /// <summary>
        /// Channel 5, internal voltage reference, connected to ADC1
        /// </summary>
        public const int Channel_VrefIn = 5;

        /// <summary>
        /// Channel 6, connected to VBatt pin, ADC1
        /// </summary>
        public const int Channel_Vbatt = 6;
    }
}
