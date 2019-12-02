//
// Copyright (c) 2019 The nanoFramework project contributors
// Copyright (c) 2015-2018, Texas Instruments Incorporated. All rights reserved.
// See LICENSE file in the project root for full license information.
//


/////////////////////////////////////////////////////////////////////////////////////
// Project configuration for CC13xx device                                         //
// This file is used to configure Boot ROM, start-up code, and SW radio behaviour. //
/////////////////////////////////////////////////////////////////////////////////////

// Following the recomendations in the original ccfg file and SDK files, 
// all the changes are to be made here before including the original ccfg.c file

#include <ti/devices/DeviceFamily.h>

// Force VDDR voltage to the factory HH setting (FCFG1..VDDR_TRIM_HH)
#define CCFG_FORCE_VDDR_HH                           0x1        

#include DeviceFamily_constructPath(startup_files/ccfg.c)
