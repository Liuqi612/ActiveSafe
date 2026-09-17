

#pragma once

#include <cstdint>

typedef signed char schar;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef signed int char32;

#undef GG_LONGLONG
#undef GG_ULONGLONG
#undef GG_LL_FORMAT

#define GG_LONGLONG(x) x##LL
#define GG_ULONGLONG(x) x##ULL
#define GG_LL_FORMAT "ll"
#define GG_LL_FORMAT_W L"ll"
