/*
 * adrg.h --
 *
 * Data structure definition for ADRG server
 *
 * Copyright (C) 1995 Her Majesty the Queen in Right of Canada.
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Her Majesty the Queen
 * in Right  of Canada not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  Her Majesty the Queen in Right of Canada makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 */

#include "ecs.h"
#include <sys/stat.h>
#ifdef _WINDOWS
#include <direct.h>
#include "compat/dirent.h"
#include <io.h>

#else
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif
#include <fcntl.h>

#define MAXADRGTILES 26

#ifndef max
#define max(x,y) ((x > y) ? x : y)
#endif

typedef struct {
  int isActive;
  unsigned char data[49152];
} tile_mem;

/* private data general to all Grass layer */

typedef struct {
  char imgname[10];      /* IMG name */
  char imgfilename[14]; /* IMG file name */
  int zonenumber;       /* ARC zone number */
  int rows;             /* Number of rows */
  int columns;          /* Number of columns */
  int rowtiles;         /* Number of 128x128 tiles in a row */
  int coltiles;         /* Number of 128x128 tiles in a column */
  ecs_Region region;    /* Bounding rectangle of the matrix */
  int *tilelist;        /* Tile list of all the tiles positions.
			   This list is (rowtiles*coltiles) long. */
  FILE *imgfile;        /* IMG file itself */
  int ARV,BRV;
  double LSO,PSO;
  int firstposition;    /* First pixel position in file */
  tile_mem *buffertile; /* buffer table */
  int firsttile;        /* Position of the first tile in the buffer table */
} LayerPrivateData;

typedef struct {
  char *genfilename;
  char *imgdir;
  LayerPrivateData overview;
} ServerPrivateData;

/* layer oriented method definition */

void		_openRasterLayer _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer));
void		_closeRasterLayer _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer));
void		_rewindRasterLayer _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer));
void		_getNextObjectRaster _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer));
void		_getObjectRaster _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer, char *objectId));
void		_getObjectIdRaster _ANSI_ARGS_((ecs_Server *s,ecs_Layer *layer, ecs_Coordinate *coord));
int             _calcPosValue _ANSI_ARGS_((ecs_Server *s,ecs_Layer *l,int i,int j,int UseOverview));
void            _LoadADRGTiles _ANSI_ARGS_((ecs_Server *s,ecs_Layer *l,int *UseOverview));

/* layer oriented method are keeped into a single data structure to simplify the code */

typedef void layerfunc();
typedef void layerobfunc();
typedef void layercoordfunc();


typedef struct {
  layerfunc	*open;
  layerfunc	*close;
  layerfunc	*rewind;
  layerfunc	*getNextObject;
  layerobfunc	*getObject;
  layercoordfunc	*getObjectIdFromCoord;	
} LayerMethod;

void _calPosWithCoord _ANSI_ARGS_((ecs_Server *s,ecs_Layer *l,double pos_x,double pos_y,int *i,int *j,int UseOverview));

int	_IsOutsideRegion _ANSI_ARGS_((double n, double s, double e,double w, ecs_Region *x));
void	_releaseAllLayers _ANSI_ARGS_((ecs_Server *s));

int _read_adrg _ANSI_ARGS_((ecs_Server *s,ecs_Layer *l));
int _read_overview _ANSI_ARGS_((ecs_Server *s));
char *subfield _ANSI_ARGS_((char *buffer, int index, int length));
double parse_coord_x _ANSI_ARGS_((char *buffer));
double parse_coord_y _ANSI_ARGS_((char *buffer));
int _verifyLocation _ANSI_ARGS_((ecs_Server *s));
int _initRegionWithDefault _ANSI_ARGS_((ecs_Server *s));
char *loc_strupr _ANSI_ARGS_((char *string));
char *loc_strlwr _ANSI_ARGS_((char *string));

