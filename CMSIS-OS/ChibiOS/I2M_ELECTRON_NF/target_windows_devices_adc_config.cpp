//
// Copyright (c) 2018 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//
 
#include "win_dev_adc_native.h"

//////////
// ADC1 //
//////////

const NF_PAL_ADC_PORT_PIN_CHANNEL Adc1PortPinConfig[] = {
    {GPIOA, 4, ADC_CHANNEL_IN4},
    {GPIOA, 5, ADC_CHANNEL_IN5},
    {NULL, NULL, ADC_CHANNEL_SENSOR},
    {NULL, NULL, ADC_CHANNEL_VREFINT},
    {NULL, NULL, ADC_CHANNEL_VBAT},
};

const int Adc1ChannelCount = ARRAYSIZE(Adc1PortPinConfig);
