/*
** PAN.H
**
** Copyright (c) 1993 Cimmetry Systems Inc., All Rights Reserved.
**
** This file should be included in all C.S.I. source files.
*/

#ifndef _PAN_H
#define _PAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>

#if	!defined(__GNUC__)
#pragma	pack(1)
#endif

#include "avdefs.h"
#include "avtypes.h"
#include "pafs.h"

/*
 *	Supporting use of shared MFC DLL under Win32.
 */
#if TARGET == WIN32S
# if	defined(CSIDLL) && (CSIDLL == 1)
#  define	PAN_MANAGE_MFCSTATE	AFX_MANAGE_STATE(AfxGetStaticModuleState());
# else
#  define	PAN_MANAGE_MFCSTATE	AFX_MANAGE_STATE(AfxGetAppModuleState());
# endif
#else
# define	PAN_MANAGE_MFCSTATE	/**/
#endif

#if	!defined(__GNUC__)
#pragma	pack()
#endif

#endif	/* _PAN_H */
