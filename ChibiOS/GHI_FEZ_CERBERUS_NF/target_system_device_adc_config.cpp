//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <sys_dev_adc_native_target.h>


const NF_PAL_ADC_PORT_PIN_CHANNEL AdcPortPinConfig[] = {

    // ADC2
    {1, GPIOA, 6, ADC_CHANNEL_IN6},
    {1, GPIOA, 2, ADC_CHANNEL_IN2},
    {1, GPIOA, 3, ADC_CHANNEL_IN3},

    // ADC2
    {2, GPIOC, 0, ADC_CHANNEL_IN10},
    {2, GPIOC, 1, ADC_CHANNEL_IN11},
    {2, GPIOA, 4, ADC_CHANNEL_IN4},

    // ADC3
    {3, GPIOC, 2, ADC_CHANNEL_IN12},
    {3, GPIOC, 3, ADC_CHANNEL_IN13},
    {3, GPIOA, 5, ADC_CHANNEL_IN5},

    // these are the internal sources, available only at ADC1
    {1, NULL, 0, ADC_CHANNEL_SENSOR},
    {1, NULL, 0, ADC_CHANNEL_VREFINT},
    {1, NULL, 0, ADC_CHANNEL_VBAT},
};

const int AdcChannelCount = ARRAYSIZE(AdcPortPinConfig);
