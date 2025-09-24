
#ifndef _UTILS_H_
#define _UTILS_H_ 1

#include <stdint.h>
#include <string>
#include <cstring>

#include <stdio.h>
#include <execinfo.h>

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef int64_t LONGLONG;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

extern char * utils_charo_char(const char * wchar, size_t len);
extern void print_trace(void);

#endif //_UTILS_H_
