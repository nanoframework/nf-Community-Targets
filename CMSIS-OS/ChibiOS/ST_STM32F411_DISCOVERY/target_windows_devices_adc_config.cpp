//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <win_dev_adc_native_target.h>

const NF_PAL_ADC_PORT_PIN_CHANNEL AdcPortPinConfig[] = {
    
    // ADC1
    {1, GPIOA, 1, ADC_CHANNEL_IN1},
    {1, GPIOB, 0, ADC_CHANNEL_IN8},
    {1, GPIOB, 1, ADC_CHANNEL_IN9},
    {1, GPIOC, 1, ADC_CHANNEL_IN11},
    {1, GPIOC, 2, ADC_CHANNEL_IN12},

    // these are the internal sources, available only at ADC1
    {1, NULL, 0, ADC_CHANNEL_SENSOR},
    {1, NULL, 0, ADC_CHANNEL_VREFINT},
    {1, NULL, 0, ADC_CHANNEL_VBAT},
};

const int AdcChannelCount = ARRAYSIZE(AdcPortPinConfig);
