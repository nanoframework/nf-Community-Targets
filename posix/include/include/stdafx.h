// TODO: port to linux

#pragma once

#if defined(__linux__) || defined(__nuttx__)
#define __cdecl __attribute__((__cdecl__))
#endif

typedef const char * LPCSTR;

#include <stdio.h>
//#include <crtdefs.h>

#define _CRTIMP

//#define _strninc(_pc,_sz) (((_pc)+(_sz)))
//  _CRTIMP size_t __cdecl __strncnt(const char *_Str,size_t _Cnt);

#include <mutex>

// TODO: reference additional headers your program requires here

#include <nanoCLR_Runtime.h>
#include <nanoCLR_Hardware.h>
#include <nanoCLR_Application.h>
#include <base64.h>
#include <sys_dev_gpio_native.h>

#include "targetHAL.h"
#include "nanoCLR_ParseOptions.h"
#include "basetsd.h"
#include "utils.h"

// LINUX
#include <sys/mman.h>
#include <memory>
#include <condition_variable>
