#ifndef _MACHINE_
#define _MACHINE_ 1

#ifndef INCL_XVTH
#include "xvt.h"
#endif

#define LEAST_SIGNIFICANT 0
#define MOST_SIGNIFICANT  1

typedef struct
{
    long            machine;
    long            input;
    long            output;
} xBYTE_ORDER;

#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define MACHINE_BYTE_ORDER LEAST_SIGNIFICANT
#elif __BYTE_ORDER == __BIG_ENDIAN
#define MACHINE_BYTE_ORDER MOST_SIGNIFICANT
#endif

#ifdef _WINDOWS
#  define DOS 1
#else  /* Not _WINDOWS */
#  define strcmpi(s1,s2) strcasecmp(s1,s2)
#  define stricmp(s1,s2) strcasecmp(s1,s2)
#  define strnicmp(s1,s2, len) strncasecmp(s1,s2, len)
#endif /* endif _WINDOWS */

#ifndef __INT32DEF__
#define __INT32DEF__
#ifdef _MSC_VER
typedef signed int int32;
typedef unsigned int uint32;
#elif defined(_ALPHA)
typedef int32_t int32;
typedef uint32_t uint32;
#else
typedef int32_t int32;
typedef uint32_t uint32;
#endif
#endif

#endif /* endif _MACHINE */



