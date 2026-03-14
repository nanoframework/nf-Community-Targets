//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "include/stdafx.h"


void HAL_Time_Sleep_MicroSeconds(unsigned int uSec)
{
    // UNDONE: FIXME: return EmulatorNative::GetITimeDriver()->Sleep_MicroSeconds( uSec );
}

void HAL_Time_Sleep_MicroSeconds_InterruptEnabled(unsigned int uSec)
{
    // UNDONE: FIXME: return EmulatorNative::GetITimeDriver()->Sleep_MicroSecondsInterruptsEnabled( uSec );
}

uint64_t HAL_Time_CurrentSysTicks()
{
    // TODO: port to linux
    struct timespec ts;
    uint64_t tick = 0u;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // each 100 nanoseconds one tick
    tick = ((ts.tv_sec * (uint64_t)1000000000) + ts.tv_nsec) / (uint64_t)100;
    return tick;
}

// Converts CMSIS sysTicks to .NET ticks (100 nanoseconds)
uint64_t HAL_Time_SysTicksToTime(uint64_t sysTicks)
{
    // TODO: port to linux
    _ASSERTE(sysTicks < 0x8000000000000000);

    return sysTicks;
}

uint64_t HAL_Time_CurrentDateTime(bool datePartOnly)
{
    // TODO: port to linux
    return 0;
}

bool HAL_Time_TimeSpanToStringEx(const int64_t &ticks, char *&buf, size_t &len)
{
    // TODO: port to linux
    return 0;
}

bool DateTimeToString(const uint64_t &time, char *&buf, size_t &len)
{
    // TODO: port to linux
    CLR_SafeSprintf(buf, len, "%4d/%02d/%02d %02d:%02d:%02d.%03d", 0, 0, 0, 0, 0, 0, 0);

    return len != 0;
}

char *DateTimeToString(const uint64_t &time)
{
    static char rgBuffer[128];
    char *szBuffer = rgBuffer;
    size_t iBuffer = sizeof(rgBuffer) / sizeof(char);

    DateTimeToString(time, szBuffer, iBuffer);

    return rgBuffer;
}

const char *HAL_Time_CurrentDateTimeToString()
{
    return DateTimeToString(HAL_Time_CurrentDateTime(false));
}
