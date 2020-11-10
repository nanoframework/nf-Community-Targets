//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <win_dev_adc_native_target.h>


const NF_PAL_ADC_PORT_PIN_CHANNEL AdcPortPinConfig[] = {

    // ADC2
    {2, GPIOC, 0, ADC_CHANNEL_IN10},
    {2, GPIOC, 1, ADC_CHANNEL_IN11},

    // ADC3
    {3, GPIOC, 2, ADC_CHANNEL_IN12},
    {3, GPIOC, 3, ADC_CHANNEL_IN13},

    // these are the internal sources, available only at ADC1
    {1, NULL, 0, ADC_CHANNEL_SENSOR},
    {1, NULL, 0, ADC_CHANNEL_VREFINT},
    {1, NULL, 0, ADC_CHANNEL_VBAT},
};

const int AdcChannelCount = ARRAYSIZE(AdcPortPinConfig);
