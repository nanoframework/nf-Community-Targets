//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <sys_dev_adc_native_target.h>

const NF_PAL_ADC_PORT_PIN_CHANNEL AdcPortPinConfig[] = {
    
    // ADC1
    {1, GPIOA, 3, ADC_CHANNEL_IN3},
    {1, GPIOC, 0, ADC_CHANNEL_IN10},
    {1, GPIOC, 3, ADC_CHANNEL_IN13},
    {1, GPIOC, 1, ADC_CHANNEL_IN11},
    {1, GPIOC, 4, ADC_CHANNEL_IN14},
    {1, GPIOC, 5, ADC_CHANNEL_IN15},
    
    // these are the internal sources, available only at ADC1
    {1, NULL, 0, ADC_CHANNEL_SENSOR},
    {1, NULL, 0, ADC_CHANNEL_VREFINT},
    {1, NULL, 0, ADC_CHANNEL_VBAT},
};

const int AdcChannelCount = ARRAYSIZE(AdcPortPinConfig);
