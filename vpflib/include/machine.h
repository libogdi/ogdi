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

#ifdef _WINDOWS
#define DOS 1
#define MACHINE_BYTE_ORDER LEAST_SIGNIFICANT
#else  /* Not _WINDOWS */
#ifdef _LINUX
#define UNIX 1
#define MACHINE_BYTE_ORDER LEAST_SIGNIFICANT
#define strcmpi(s1,s2) strcasecmp(s1,s2)
#define stricmp(s1,s2) strcasecmp(s1,s2)
#define strnicmp(s1,s2, len) strncasecmp(s1,s2, len)
#else /* Not _LINUX */
#ifdef _ALPHA
#define UNIX 1
#define MACHINE_BYTE_ORDER LEAST_SIGNIFICANT
#define strcmpi(s1,s2) strcasecmp(s1,s2)
#define stricmp(s1,s2) strcasecmp(s1,s2)
#define strnicmp(s1,s2, len) strncasecmp(s1,s2, len)
#else /* Not _ALPHA */
#ifdef _SOLARIS
#define UNIX 1
#define MACHINE_BYTE_ORDER MOST_SIGNIFICANT
#define strcmpi(s1,s2) strcasecmp(s1,s2)
#define stricmp(s1,s2) strcasecmp(s1,s2)
#define strnicmp(s1,s2, len) strncasecmp(s1,s2, len)
#else /* Not _SOLARIS */
#if 0
#if XVT_OS == XVT_OS_WIN
#define DOS 1
#define MACHINE_BYTE_ORDER LEAST_SIGNIFICANT
#endif /* not 0 */
#endif /* XVT_OS == XVT_OS_WIN */
#if XVT_OS_ISUNIX == TRUE
#define UNIX 1
#define MACHINE_BYTE_ORDER MOST_SIGNIFICANT
#define strcmpi(s1,s2) strcasecmp(s1,s2)
#define stricmp(s1,s2) strcasecmp(s1,s2)
#define strnicmp(s1,s2, len) strncasecmp(s1,s2, len)
#endif /* endif XVT_OS_ISUNIX == TRUE */
#if XVT_OS == XVT_OS_MAC
#define MAC 1
#define MACHINE_BYTE_ORDER MOST_SIGNIFICANT
#endif /* endif XVT_OS == XVT_OS_MAC */
#endif /* endif _SOLARIS */
#endif /* endif _ALPHA */
#endif /* endif _LINUX */
#endif /* endif _WINDOWS */

#ifndef __INT32DEF__
#define __INT32DEF__
#ifdef _ALPHA
typedef int int32;
typedef unsigned int uint32;
#else
typedef long int32;
typedef unsigned long uint32;
#endif
#endif

#endif /* endif _MACHINE */



