#ifndef AVDEFS_H
#define AVDEFS_H

/*
**	Miscellaneous defines  and	Compiler dependencies.
**	-------------------------------------------------
*/

/*
**	The different TARGETS that we support
*/
#include "target.h"


#if !defined(TARGET) || TARGET==1
# define TARGET 	WIN16
# pragma	message("Setting target to WIN16")
#endif

#if !defined(MACHINE) || MACHINE==1
# define MACHINE	M_PC
#endif


/*
**	The different LANGUAGES that we support
*/
#define English 	0
#define French		1
#define German		2


/***************************************************************************
**	DOS Real Mode
****************************************************************************/
#if TARGET == DOS86
# define PCALLBACK		/**/
# define CCALLBACK		/**/
# define PCALLBACKFN	/**/
# define CCALLBACKFN	/**/
# define LittleEndian	1
# define INTBITS 		16
# define INTBITS_M1		15
#endif	/* DOS86 */

/***************************************************************************
**	DOS Protected Mode
****************************************************************************/
#if TARGET == DOS386
# define LittleEndian	1
# define INTBITS 		32
# define INTBITS_M1		31
# define huge			/**/
# define _huge			/**/
# define __huge			/**/
# define far			/**/
# define _far			/**/
# define __far			/**/
# define _near			/**/
# define __near 		/**/
# define _cdecl 		/**/
# define _pascal		/**/
# define __pascal		/**/
# define _loadds		/**/
# define __loadds		/**/
# define _export		/**/
# define __export		/**/
# define __inline		/**/
# define WINAPI 		FAR PASCAL
# define CALLBACK		/**/
# define PCALLBACK		/**/
# define CCALLBACK		/**/
# define PCALLBACKFN	/**/
# define CCALLBACKFN	/**/
typedef char *			_LPSTR;
# define LPSTR			_LPSTR
# define LPCSTR 		LPSTR
typedef unsigned int	UINT;
# define LPARAM 		DWORD
# define WPARAM 		WORD
# define HGLOBAL		GLOBALHANDLE
# define HFILE			int
# define HFILE_ERROR	-1
# define hmemcpy		memcpy
# define _fcalloc		calloc
# define _ffree 		free
# define _fmalloc		malloc
# define _fmemcmp		memcmp
# define _fmemcpy		memcpy
# define _fmemset		memset
# define _frealloc		realloc
# define _fstrcat		strcat
# define _fstrchr		strchr
# define _fstrcmp		strcmp
# define _fstrcpy		strcpy
# define _fstrdup		_strdup
# define _fstricmp		_stricmp
# define _fstrlen		strlen
# define _fstrncat		strncat
# define _fstrncmp		strncmp
# define _fstrncpy		strncpy
# define _fstrnicmp 	_strnicmp
# define _fstrrchr		strrchr
# define _fstrstr		strstr
# define _fstrtok		strtok
# define _fstrupr		_strupr
# define __HIGHC__		1
# define MSDOS			1
# define P386			1
extern	char			_pgmptr[];
#endif	/* DOS386 */

/***************************************************************************
**	UNIX
****************************************************************************/
#if TARGET == UNIX
# define BigEndian		1
# define INTBITS 		32
# define INTBITS_M1		31
# define huge			/**/
# define _huge			/**/
# define __huge			/**/
# define far			/**/
# define _far			/**/
# define __far			/**/
# define _near			/**/
# define __near 		/**/
# define _cdecl 		/**/
# define _pascal		/**/
# define __pascal		/**/
# define _loadds		/**/
# define __loadds		/**/
# define _export		/**/
# define __export		/**/
# define __inline		/**/
# define CALLBACK		/**/
# define PCALLBACK		/**/
# define CCALLBACK		/**/
# define PCALLBACKFN	/**/
# define CCALLBACKFN	/**/
typedef char *			_LPSTR;
# define LPSTR			_LPSTR
# define LPCSTR 		LPSTR
# define hmemcpy		memcpy
# define _fcalloc		calloc
# define _ffree 		free
# define _fmalloc		malloc
# define _fmemcmp		memcmp
# define _fmemcpy		memcpy
# define _fmemset		memset
# define _frealloc		realloc
# define _fstrcat		strcat
# define _fstrchr		strchr
# define _fstrcmp		strcmp
# define _fstrcpy		strcpy
# define _fstrdup		strdup
# define _fstricmp		stricmp
# define _fstrlen		strlen
# define _fstrncat		strncat
# define _fstrncmp		strncmp
# define _fstrncpy		strncpy
# define _fstrnicmp 	strnicmp
# define _fstrrchr		strrchr
# define _fstrstr		strstr
# define _fstrtok		strtok
# define _fstrupr		strupr
# define _MAX_DRIVE 	512
# define _MAX_DIR		512
# define _MAX_PATH		512
# define _MAX_FNAME 	512
# define _MAX_EXT		512
# define MulDiv(x,y,z)	(((x) * (y)) / (z))
extern	char			_pgmptr[];
#endif	/* UNIX */


/***************************************************************************
**	Windows 3.x
****************************************************************************/
#if TARGET == WIN16
# define	_Windows
// Define the PCALLBACK attribute(Pascal style exported function)
# define PCALLBACK	_far _pascal __export _loadds
# define PCALLBACKFN	_far _pascal __export
// Define the CCALLBACK attribute("C" convention exported function)
# define CCALLBACK		_far _cdecl __export _loadds
# define CCALLBACKFN	_far _cdecl __export
# define LittleEndian	1
# define INTBITS 		16
# define INTBITS_M1		15
#endif	/* WIN16 */

/***************************************************************************
**	WIN32S / NT API
****************************************************************************/
#if TARGET == WIN32S
# define LittleEndian	1
# define INTBITS 		32
# define INTBITS_M1		31
# define PCALLBACK		CALLBACK
# define CCALLBACK		CALLBACK
# define PCALLBACKFN	CALLBACK
# define CCALLBACKFN	CALLBACK
# define _near			/**/
# define __near 		/**/
# define _far			/**/
# define __far			/**/
# define _huge			/**/
# define __huge			/**/
# define huge			/**/
# define _loadds		/**/
# define __loadds		/**/
# define _export		/**/
# define __export		/**/
# define _pascal		/**/
# define __pascal		/**/
# define READ			_O_RDONLY
# define WRITE			_O_WRONLY
# define _fcalloc		calloc
# define _fmemset		memset
# define _fmemcpy		memcpy
# define _fmalloc		malloc
# define _frealloc		realloc
# define _fmemcmp		memcmp
# define _ffree 		free
# define _fstrcat		strcat
# define _fstrdup		_strdup
# define _fstrncat		strncat
# define _fstrchr		strchr
# define _fstrrchr		strrchr
# define _fstrcmp		strcmp
# define _fstricmp		_stricmp
# define _fstrncmp		strncmp
# define _fstrcpy		strcpy
# define _fstrncpy		strncpy
# define _fstrnicmp 	_strnicmp
# define _fstrlen		strlen
# define _fstrstr		strstr
# define _fstrtok		strtok
# define _fstrupr		_strupr
# define _halloc(n, x)	malloc((n) * (x))
# define _hfree			free
# define hmemcpy		MoveMemory
# define LockData(x)	/**/
# define UnlockData(x)	/**/
# define _Windows		/**/
# define WIN32			1
#endif	/* WIN32S */


/*
**	Create a valid IEEE double and floating point values
*/
#if TARGET == UNIX
#define FixFloat(x) {;}
#define FixDouble(x) {;}
#else
#define FixFloat(x) {									\
		float	F = (float)0.0; 						\
		_xdr_ieee_to_float(&F, (Long _far *) &(x)); 	\
		_xdr_float_to_ieee(&F, (Long _far *) &(x)); 	\
		}
#define FixDouble(x)	{								\
		double	D = 0.0;								\
		_xdr_ieee_to_double(&D, (Long _far *) &(x));	\
		_xdr_double_to_ieee(&D, (Long _far *) &(x));	\
		}
#endif

/*
**	Useful typedefs.
*/
#define Public		/**/
#define Private 	static

/*
**	Some defines
*/
#define 	False		 0
#define 	True		 1
#define 	Maybe		-1
#define 	DontCare	-2
#define 	Fifteen 	15

#define 	STRLEN80		80
#define 	STRLEN240		240
#define		PAN_MAX_PATH	320


#define 	STRLEN_DRIVE	_MAX_DRIVE
#define 	STRLEN_DIR		_MAX_DIR
#if 	defined(UNIX)
# define	STRLEN_FNAME	512
# define	STRLEN_EXT		512
#else
# define	STRLEN_FNAME	_MAX_FNAME
# define	STRLEN_EXT		_MAX_EXT
#endif
#define 	STRLEN_NAME		_MAX_PATH


#define TooBig				32766
#define ExtremelyVerySmall	1.e-012
#define VerySmall			1.e-04
#define Small				1.e-03
#define Large				1.e06
#define VeryLarge			1.e12

#define Pi					3.14159265358979320
#define PiT2				6.28318530717958600
#define PiB2				1.57079632679489700
#define PiB4				0.78539816339744830
#define PiB5				0.62831853071795860
#define PiB6				0.52359877559829880
#define PiB8				0.39269908169872410
#define PiB10				0.31415926535897930
#define PiB12				0.26179938779914940
#define PiB16				0.19634954084936210
#define PiB36				0.08726646259971647
#define TenDegrees			0.17453292519943290
#define Sqrt2				1.41421356237309500
#define Sqrt2B2 			0.70710678118654760
#define RadToDeg			57.2957795130823200
#define DegToRad			0.01745329251994330
#define RadToDeg256 		40.7436654315252100 /* 256 / (2pi)	*/
#define RadToDeg512 		81.4873308630504200 /* 512 / (2pi)	*/
#define Deg256ToRad 		0.02454369260617026
#define Deg512ToRad 		0.01227184630308513

#define Abs(x)				((x)<0 ? -(x) : (x))
#define Fabs(x) 			((x)<0.? -(x) : (x))
#define Min(a, b)			((a)<(b) ? (a) : (b))
#define Max(a, b)			((a)>(b) ? (a) : (b))
#define Round(x)			((x)>=0  ? (int)((x)+0.5) : (int)((x)-0.5))

/*
**	Memory allocation
*/
#define Nil(x)				((x *) NULL)
#define New(x)				(x *) malloc(sizeof(x))
#define NNew(y, x)			(x *) malloc((size_t)(((size_t)!(y)?1:(y)) * sizeof(x)))
#define Realloc(x, y)		((x) ? realloc(x, y) : malloc(y))
#define Free(x) 			if ((x)!=NULL) {free(x);}
#define PanMalloc(x)		malloc((!(x) ? 1 : (x)))
#define PanFree(x)			if ((x)!=NULL) {free(x);}

#if	TARGET == DOS386
# define FNew(x) 			(x _far *) malloc(sizeof(x))
# define FNNew(y, x) 		(x _far *) malloc((size_t)((!(y)?1:(y)) * sizeof(x)))
# define FFree(x)			if ((x)!=NULL) {free(x);}
# define PanFMalloc(x)		malloc((!(x) ? 1 : (x)))
# define PanFFree(x) 		if ((x)!=NULL) {free(x);}
#else
# define FNew(x) 			(x _far *) _fmalloc(sizeof(x))
# define FNNew(y, x) 		(x _far *) _fmalloc((size_t)((!(y)?1:(y)) * sizeof(x)))
# define FFree(x)			if ((x)!=NULL) {_ffree(x);}
# define PanFMalloc(x)		_fmalloc((!(x) ? 1 : (x)))
# define PanFFree(x) 		if ((x)!=NULL) {_ffree(x);}
#endif	/* TARGET */

#define	pixels2bytes(x)		(((x) & 0x07) ? ((x) >> 3) + 1 : (x) >> 3)
#define	IIndirect(z, y, x)	( *(*((z) + (y)) + (x)) )

#define Sqrt(x) 			((x)>0.0 ? sqrt(x) : 0.0)
#define Sin(x)				PAN_Sin(x)
#define Cos(x)				PAN_Cos(x)
#define Atan2(x, y)			(((x)==0.0&&(y)==0.0) ? 0.0 : atan2(x, y))

/*
**	Convert a double to two longs
*/
#define D2LL(val)	(long) val, (long)((val<0.0? -1 : 1) * ((val - (long) val)*1000.0))

/*
**	Encoding / Decoding functions to read/write serial numbers from the
**	registration file
**	ENCTONUM converts an encoded value (two letters) to a number (0..9)
**	NUMTOENC converts a digit (0..9) two a two-letter ascii encoded value.
*/
#define ENCTONUM2(x)	( 10*((x)[0] - '0' - 32) + ((x)[1] - '0' - 32) )
#define NUMTOENC2(x, y) (x)[0] = (((y) % 100) / 10) + '0' + 32; \
						(x)[1] =  ((y) % 10) + '0' + 32;

#endif	/* AVDEFS_H */
