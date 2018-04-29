//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include "win_dev_adc_native.h"


const NF_PAL_ADC_PORT_PIN_CHANNEL AdcPortPinConfig[] = {

    // ADC1
    {1, GPIOA, 0, ADC_CHANNEL_IN0},
    {1, GPIOA, 1, ADC_CHANNEL_IN1},
    {1, GPIOA, 4, ADC_CHANNEL_IN4},
    
    // these are the internal sources, available only at ADC1
    {1, NULL, NULL, ADC_CHANNEL_SENSOR},
    {1, NULL, NULL, ADC_CHANNEL_VREFINT},
    {1, NULL, NULL, ADC_CHANNEL_VBAT},
};

const int AdcChannelCount = ARRAYSIZE(AdcPortPinConfig);
