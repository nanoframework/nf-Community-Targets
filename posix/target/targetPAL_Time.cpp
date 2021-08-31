//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "include/stdafx.h"
#include "TimerManager.h"

#ifdef __cplusplus
extern "C" {
#endif

void TimerCallback()
{
    GLOBAL_LOCK();
    HAL_COMPLETION::DequeueAndExec();
}

void Time_SetCompare(uint64_t CompareValue)
{
    static std::unique_ptr<TimerManager> pCompletionsTimer;

    // convert to milliseconds for OS timer
    auto compareMs = CompareValue / (CPU_TicksPerSecond() * (uint64_t)1000);
    ASSERT(compareMs < UINT32_MAX);

    if (compareMs == 0)
    {
        TimerCallback();
    }
    else
    {
        pCompletionsTimer = std::make_unique<TimerManager>(compareMs, TimerCallback);
    }
}

#ifdef __cplusplus
}
#endif
