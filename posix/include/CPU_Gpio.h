//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//


#ifndef _CPU_GPIO_H_
#define _CPU_GPIO_H_

#include "include/stdafx.h"

#if defined(BOARD_WSL)

#define NF_POSIX_GPIO
// multi bank, each have 36
#define GPIO_MAX_PIN        36
#define TOTAL_GPIO_PORTS    36

#endif // BOARD_WSL

#if defined(BOARD_PI_ZERO)

#define NF_POSIX_GPIO
// 1 bank
#define GPIO_MAX_PIN        27
#define TOTAL_GPIO_PORTS    27

#endif // BOARD_PI_ZERO

#if defined(BOARD_JH7100)

#define NF_POSIX_GPIO
// TODO: 1 bank?
#define GPIO_MAX_PIN        48
#define TOTAL_GPIO_PORTS    48

#endif // BOARD_JH7100


#if defined(BOARD_PI_PICO)
// 5 gpios seted as gpin in Nuttx
#define __gpio
#define GPIO_MAX_PIN        30
#define TOTAL_GPIO_PORTS    5
#endif

#if defined(BOARD_PI_ZERO) || defined(BOARD_WSL)
#define __gpio
#include <gpiod.h>

struct gpiod_chip *_chip;

// 9 usable gpios
#define GPIO_MAX_PIN        40
#define TOTAL_GPIO_PORTS    9

static gpiod_line* pinLineStored[GPIO_MAX_PIN];
static GpioPinValue pinLineValue[GPIO_MAX_PIN];
#endif

#if defined(__nuttx__) && defined(__gpio)
static int ioctrlFdReference[GPIO_MAX_PIN];
static GpioPinValue pinLineValue[GPIO_MAX_PIN];
#endif


#if defined(__gpio)
static GpioPinDriveMode pinDirStored[GPIO_MAX_PIN];
#endif

#endif  //_CPU_GPIO_H_
