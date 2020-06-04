//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <sys_dev_dac_native_target.h>

const NF_PAL_DAC_PORT_PIN_CHANNEL DacPortPinConfig[] = {

    // NO DAC support on the STM32F411xE MCU
    ,

};

const int DacChannelCount = ARRAYSIZE(DacPortPinConfig);
