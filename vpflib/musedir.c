/*
 * MUSEDIR.C- a set of directory and file utilities implemented over XVT
 * functions. These functions could also be implemented over a specific
 * operating system to wean from XVT.
 * 
 * This file contains the following functions: dir_create dir_current dir_pop
 * dir_push dir_restore dir_save file_open file_spec_to_string muse_access
 * muse_filelength muse_check_path
 */


#ifndef INCL_XVTH
#include "xvt.h"
#endif

#ifdef unix
/* #include "direct.h" */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "machine.h"

#include "musedir.h"
#ifndef TRUE
#define TRUE 1
#endif

#ifdef _MSDOS
#include "io.h"
#endif

#ifdef _WINDOWS
#include <stdio.h>
#include <io.h>
#endif

#include <ctype.h>


/**************************************************************************/
/* FILE_OPEN                                                              */
/**************************************************************************/



#if XVT_CC_PROTO
FILE           *
muse_file_open(char *path, char *mode)
#else
FILE           *
muse_file_open(path, mode)
    char           *path;
    char           *mode;
#endif

{
    FILE           *file;
    char            pathext[SZ_FNAME];
    char            lobuf[SZ_FNAME];
    char            upbuf[SZ_FNAME];
    int             i, len;
    BOOLEAN         DOT_FOUND = 0;
    int32            lenup;
    char            *s;

    strcpy(pathext, path);
    muse_check_path(pathext);

#ifdef _WINDOWS
    file = fopen(pathext, mode);
    return (file);
#endif				

#ifdef unix
    memset(lobuf, (char) NULL, SZ_FNAME);
    memset(upbuf, (char) NULL, SZ_FNAME);
    len = strlen(pathext);
    strcpy(upbuf, pathext);
    strcpy(lobuf, pathext);

    for (i = len-1; i >= 0; i--)
    {
	if (pathext[i] == '.')
	{
	    DOT_FOUND = TRUE;
	}
        if (pathext[i] == (int) FILE_SEP) 
            break;
    }
#if 0
    for (i = len - 1; (i >= 0 && pathext[i] != (int) FILE_SEP); i--)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }
#endif
    s = strchr(&pathext[1],'/');
    if (s != (char *)NULL)
      lenup = strlen(s);
    else
      lenup = len;
    for (i = len - lenup; i < len; i++)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }

    if ((file = fopen(pathext, mode)) == (FILE *) NULL)
    {

	if (!DOT_FOUND)
	    strcat(pathext, ".");
	if ((file = fopen(pathext, mode)) == (FILE *) NULL)
	{
	    strcat(pathext, ";1");
	    file = fopen(pathext, mode);
	}
    }
    if (file == (FILE *) NULL)
    {
	if ((file = fopen(lobuf, mode)) == (FILE *) NULL)
	{

	    if (!DOT_FOUND)
		strcat(lobuf, ".");
	    if ((file = fopen(lobuf, mode)) == (FILE *) NULL)
	    {
		strcat(lobuf, ";1");
		file = fopen(lobuf, mode);
	    }
	}
    }
    if (file == (FILE *) NULL)
    {
	if ((file = fopen(upbuf, mode)) == (FILE *) NULL)
	{

	    if (!DOT_FOUND)
		strcat(upbuf, ".");
	    if ((file = fopen(upbuf, mode)) == (FILE *) NULL)
	    {
		strcat(upbuf, ";1");
		file = fopen(upbuf, mode);
	    }
	}
    }

    return (file);
#endif

/*
#ifdef _MAC
    if ((file = fopen(pathext, mode)) == (FILE *) NULL)
    {

	if (strchr(pathext, '.') == NULL)
	    strcat(pathext, ".");
	strcat(pathext, ";1");
	file = fopen(pathext, mode);
    }
    return (file);
#endif				
*/
}



/**************************************************************************/
/* FIL_OPEN                                                              */
/**************************************************************************/

/*

#if XVT_CC_PROTO
int
fil_open(char *path, int mode)
#else
int
fil_open(path, mode)
    char           *path;
    int             mode;
#endif

{
    int             file;
    char            pathext[SZ_FNAME];
    char            lobuf[SZ_FNAME];
    char            upbuf[SZ_FNAME];
    int             i, len;
    BOOLEAN         DOT_FOUND = 0;
    int32            lenup;
    char            *s;

    strcpy(pathext, path);

#ifdef _WINDOWS
    file = open(pathext, mode);
    return (file);
#endif				

#ifdef unix
    memset(lobuf, (char) NULL, SZ_FNAME);
    memset(upbuf, (char) NULL, SZ_FNAME);
    len = strlen(pathext);
    strcpy(upbuf, pathext);
    strcpy(lobuf, pathext);

    for (i = len-1; i >= 0; i--)
    {
	if (pathext[i] == '.')
	{
	    DOT_FOUND = TRUE;
	}
        if (pathext[i] == (int) FILE_SEP) 
            break;
    }
#if 0
    for (i = len - 1; (i >= 0 && pathext[i] != (int) FILE_SEP); i--)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }
#endif
    s = strchr(&pathext[1],'/');
    if (s != (char *)NULL)
      lenup = strlen(s);
    else
      lenup = len;
    for (i = len - lenup; i < len; i++)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }

    if ((file = open(pathext, mode)) < 0)
    {

	if (!DOT_FOUND)
	    strcat(pathext, ".");
	if ((file = open(pathext, mode)) < 0)
	{
	    strcat(pathext, ";1");
	    file = open(pathext, mode);
	}
    }
    if (file < 0)
    {
	if ((file = open(lobuf, mode)) < 0)
	{

	    if (!DOT_FOUND)
		strcat(lobuf, ".");
	    if ((file = open(lobuf, mode)) < 0)
	    {
		strcat(lobuf, ";1");
		file = open(lobuf, mode);
	    }
	}
    }
    if (file < 0)
    {
	if ((file = open(upbuf, mode)) < 0)
	{

	    if (!DOT_FOUND)
		strcat(upbuf, ".");
	    if ((file = open(upbuf, mode)) < 0)
	    {
		strcat(upbuf, ";1");
		file = open(upbuf, mode);
	    }
	}
    }
    return (file);
#endif				

}

*/

/**************************************************************************/
/* MUSE_ACCESS                                                            */
/**************************************************************************/



#if XVT_CC_PROTO
int
muse_access(char *path, int amode)
#else
int
muse_access(path, amode)
    char           *path;
    int             amode;
#endif

{

    char            pathext[SZ_FNAME];
    int             acc;
    char            lobuf[SZ_FNAME];
    char            upbuf[SZ_FNAME];
    int             i, len;
    BOOLEAN         DOT_FOUND = 0;
    int32            lenup;
    char            *s;

    strcpy(pathext, path);

#ifdef _WINDOWS
    acc = _access(pathext, amode);
    return (acc);
#endif

#ifdef unix
    memset(lobuf, (char) NULL, SZ_FNAME);
    memset(upbuf, (char) NULL, SZ_FNAME);
    len = strlen(pathext);
    strcpy(upbuf, pathext);
    strcpy(lobuf, pathext);

    for (i = len-1; i >= 0; i--)
    {
	if (pathext[i] == '.')
	{
	    DOT_FOUND = TRUE;
	}
        if (pathext[i] == (int) FILE_SEP) 
            break;
    }
#if 0
    for (i = len - 1; (i >= 0 && pathext[i] != (int) FILE_SEP); i--)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }
#endif
    s = strchr(&pathext[1],'/');
    if (s != (char *)NULL)
      lenup = strlen(s);
    else
      lenup = len;
    for (i = len - lenup; i < len; i++)
    {
	upbuf[i] = toupper(pathext[i]);
	lobuf[i] = tolower(pathext[i]);
    }

    if ((acc = access(pathext, amode)) == -1)
    {

	if (!DOT_FOUND)
	    strcat(pathext, ".");
	if ((acc = access(pathext, amode)) == -1)
	{
	    strcat(pathext, ";1");
	    acc = access(pathext, amode);
	}
    }
    if (acc == -1)
    {
	if ((acc = access(lobuf, amode)) == -1)
	{

	    if (!DOT_FOUND)
		strcat(lobuf, ".");
	    if ((acc = access(lobuf, amode)) == -1)
	    {
		strcat(lobuf, ";1");
		acc = access(lobuf, amode);
	    }
	}
    }
    if (acc == -1)
    {
	if ((acc = access(upbuf, amode)) == -1)
	{

	    if (!DOT_FOUND)
		strcat(upbuf, ".");
	    if ((acc = access(upbuf, amode)) == -1)
	    {
		strcat(upbuf, ";1");
		acc = access(upbuf, amode);
	    }
	}
    }
    return (acc);
#endif				

}



/**************************************************************************/
/* MUSE_FILELENGTH                                                        */
/**************************************************************************/



#if XVT_CC_PROTO
int32
muse_filelength(char *path)
#else
int32
muse_filelength(path)
    char           *path;
#endif

{

#ifdef unix
    struct stat buf;
#endif 

    FILE           *file;
    int32            length;

    length = 0;
    file = muse_file_open(path, "rb");
    if (file != NULL) {
#ifdef _WINDOWS
      length = _filelength(fileno(file));
#else 
      if (fstat(fileno(file),&buf) == 0) {
	length = (int32) buf.st_size;
      } else {
	length = 0;
      }
#endif
      fclose(file);
    }
    return (length);
}



/************************************************************************/
/* MUSE_CHECK_PATH                                                      */
/************************************************************************/

void
muse_check_path(path)
    char *path;
{
    int32            i, length;

    length = strlen(path);

    for (i = 0; i < length; i++)
	if (path[i] == '\\')
	    path[i] = FILE_SEP;
    return;
}

