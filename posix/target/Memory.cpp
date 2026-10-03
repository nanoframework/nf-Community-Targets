//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#include "include/stdafx.h"

// using namespace Microsoft::SPOT::Emulator;

// TODO: port to linux

// This is good for get virtual memory from Linux

// From minheap.cpp
// static unsigned char *s_Memory_Start = NULL;
// static unsigned int s_Memory_Length = 1024 * 1024 * 10;

// void HeapLocation(unsigned char *&BaseAddress, unsigned int &SizeInBytes)
// {
//     if (!s_Memory_Start)
//     {
//         // TODO: port to linux
//         /*s_Memory_Start =
//             (unsigned char *)::VirtualAlloc(NULL, s_Memory_Length, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);*/
//         s_Memory_Start = 
//             (unsigned char *) mmap(NULL, s_Memory_Length, PROT_READ | PROT_WRITE, MAP_32BIT | MAP_SHARED | MAP_ANON, -1, 0);

//         if (s_Memory_Start)
//         {
//             memset(s_Memory_Start, 0x0, s_Memory_Length);
//         }

//         HalSystemConfig.RAM1.Base = (unsigned int)(size_t)s_Memory_Start;
//         HalSystemConfig.RAM1.Size = (unsigned int)(size_t)s_Memory_Length;
//     }

//     BaseAddress = s_Memory_Start;
//     SizeInBytes = s_Memory_Length;
// }

// TODO: port to nuttx

// this is to simulate the same behavior from nuttx

static unsigned char *s_Memory_Start = NULL;
static unsigned int s_Memory_Length = 64*1024;

#define MANAGED_HEAP_SIZE  (64*1024)
uint32_t managedHeap[MANAGED_HEAP_SIZE/ sizeof(uint32_t)];

void HeapLocation(unsigned char *&BaseAddress, unsigned int &SizeInBytes)
{
    if (!s_Memory_Start)
    {
        // static heap memory
        s_Memory_Start = (unsigned char*)&managedHeap;
        s_Memory_Length =  sizeof(managedHeap);

        HalSystemConfig.RAM1.Base = (unsigned int)(size_t)s_Memory_Start;
        HalSystemConfig.RAM1.Size = (unsigned int)(size_t)s_Memory_Length;
    }

    BaseAddress = s_Memory_Start;
    SizeInBytes = s_Memory_Length;
}
