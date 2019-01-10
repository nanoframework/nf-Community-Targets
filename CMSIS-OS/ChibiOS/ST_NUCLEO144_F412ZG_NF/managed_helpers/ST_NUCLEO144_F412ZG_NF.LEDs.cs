//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

namespace nanoFramework.Targets.Community.ST_NUCLEO144_F412ZG_NF
{
    public enum OnBoardLeds
    {
        /// <summary>
        /// Output pin connected to the on-board green user LED
        /// </summary>
        GreenLed = Gpio.PB0,

        /// <summary>
        /// Output pin connected to the on-board blue user LED
        /// </summary>
        BlueLed = Gpio.PB7,

        /// <summary>
        /// Output pin connected to the on-board red user LED
        /// </summary>
        RedLed = Gpio.PB14
    }
}
