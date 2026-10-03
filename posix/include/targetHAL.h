//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _TARGET_HAL_H_
#define _TARGET_HAL_H_

#include "basetsd.h"

#if defined(__linux__) || defined(__nuttx__)
#define __cdecl __attribute__((__cdecl__))
#endif

// #include <nanoHAL_Power.h>

// set min possible number of sockets
#define PLATFORM_DEPENDENT__SOCKETS_MAX_COUNT 1

#if defined(__linux__) || defined(__nuttx__)
#define NANOCLR_STOP() {\
    printf("NANOCLR_STOP");\
    exit(-24);\
}
#endif

#if !defined(BUILD_RTM)

inline void __cdecl HARD_Breakpoint()
{
    // TODO: port to linux
    // if (::IsDebuggerPresent())
    // {
    //     ::DebugBreak();
    // }
}

#define HARD_BREAKPOINT() HARD_Breakpoint()

inline bool Target_ConfigUpdateRequiresErase()
{
    return true;
}

#endif // !defined(BUILD_RTM)

inline bool Target_HasNanoBooter()
{
    return false;
};

inline bool Target_IFUCapable()
{
    return false;
};

inline bool Target_HasProprietaryBooter()
{
    return false;
};

inline uint32_t GetPlatformCapabilities()
{
    return 0;
};

inline uint32_t GetTargetCapabilities()
{
    return 0;
};

inline bool RequestToLaunchProprietaryBootloader()
{
    return false;
};

inline bool RequestToLaunchNanoBooter()
{
    return false;
};

inline uint32_t CPU_TicksPerSecond()
{
    return 100000000;
}

inline uint64_t CPU_MicrosecondsToTicks(UINT64 uSec)
{
    return uSec * 10;
}

inline uint64_t CPU_MillisecondsToTicks(UINT64 uSec)
{
    return uSec * 10 * 1000;
}

#endif //_TARGET_HAL_H_
