#ifndef	AVTYPES_H
#define	AVTYPES_H

/*
**  The different types that are used throughout the C.S.I. code
*/

/*
**	Machine-independent types
*/
typedef	double			edatDouble;		// Guaranteed to be 8 bytes, IEEE - signed
typedef	float			edatFloat;		// Guaranteed to be 4 bytes, IEEE - signed
typedef	long			edatLong;		// Guaranteed to be 4 bytes - signed
typedef	short			edatInt;		// Guaranteed to be 2 bytes - signed
typedef	unsigned char	edatChar;		// Guaranteed to be 1 8bit byte - unsigned

#define	DoubleSize		8
#define	FloatSize		4
#define	LongSize		4
#define	IntSize			2
#define	CharSize		1

/*
**	Simple types
*/
typedef	signed char		Schar;
typedef	unsigned char	Uchar;

#ifndef	Bool
typedef	int				Bool;
#endif	/* Bool */

#ifndef	MAINWIN
typedef	UINT _far		*LPUINT;
#endif
typedef	double			edatReal;
typedef	unsigned long	ULong;

typedef int				PANFILE;		// Type for the handle to a PANIO file
typedef	int				STREAMID;		// OLE stream identifier

/*
**  Function pointers
*/
typedef	void	(* VoidFn)();
typedef	int		(* IntFn)();
typedef	Bool	(* BoolFn)();

typedef	void	(_far _pascal * FVoidFn)();
typedef	int		(_far _pascal * FIntFn)();
typedef	Bool	(_far _pascal * FBoolFn)();

/*
**  A point
*/
typedef struct tagPAN_Point {
	edatReal	x;
	edatReal	y;
	edatReal	z;
} PAN_Point, PANPOINT, *PPANPOINT, _far *LPPANPOINT;

typedef struct {
	edatReal	x;
	edatReal	y;
} PHYSPOINT, FAR *LPPHYSPOINT;

/*
**  A rectangle
*/
typedef struct tagPAN_Rect {
	PAN_Point		   min;
	PAN_Point		   max;
} PAN_Rect, PANRECT, *PPANRECT, _far *LPPANRECT,
  PAN_RectangleRange;

typedef struct {
	edatReal	left;
	edatReal	top;
	edatReal	right;
	edatReal	bottom;
} PHYSRECT, FAR *LPPHYSRECT;

/*
** Thick Poly vertex.
*/
typedef struct {
	edatReal	sw;
	edatReal	ew;
	edatReal	bulge;
} PAN_TVertex, *PPANTVERTEX, _far *LPPANTVERTEX;

/*
**  Long coordinate point
*/
typedef	struct lpoint {
	long	x, y;
} LPOINT,   _far *LPLPOINT,
  LONGPOINT, FAR *LPLONGPOINT;
typedef	const LPOINT	_far *LPCLPOINT;

/*
**  Long coordinate size
*/
typedef	struct lsize {
	long	cx, cy;
} LSIZE, _far *LPLSIZE;
typedef	const LSIZE		_far *LPCLSIZE;

/*
**  Long coordinate rectangle
*/
typedef	struct lrect {
	long	left, top;
	long	right, bottom;
} LRECT,   _far *LPLRECT,
  LONGRECT, FAR *LPLONGRECT;
typedef	const LRECT		_far *LPCLRECT;

/*
**  Homegenous matrix transformation
*/
#define		HMATRIX_UNIT		0x00000001
#define		HMATRIX_2D			0x00000002
#define		HMATRIX_SCALEONLY	0x00000004
typedef	struct hmatrix {
	edatReal	m[4][4];
	long	flags;
} Hmatrix, *PHmatrix, _far *LPHmatrix;

/*
**  An entity-handle
*/
typedef struct {
	DWORD	low;
	DWORD	high;
} PAN_Handle, PANHANDLE, *PPANHANDLE, _far *LPPANHANDLE;

/*
**	Structure used to describe Resource Info 
*/
typedef struct {
	UINT resourceType;   			/* Text font, Linestyle, shape, or external reference file */
	char	szResourceID[_MAX_PATH];/* Name of resource ID (Logical Name) */
	UINT cbResourceID;	 			/* number of characters in the name of resource ID*/
	char szResource[_MAX_PATH];    	/* Name of resource (File Name) */
	UINT cbResource;	 			/* Number of characters in the name of resource */
	BOOL fOK;			 			/* Located / missing flag */
#if	TARGET == WIN16
	char	pad[1024-528];			/* pad to a power of two */
#endif
}	PAN_RESOURCEINFO, *PPAN_RESOURCEINFO,
	_far *LPPAN_RESOURCEINFO, _huge *HPPAN_RESOURCEINFO;

/*
**	Structure used to describe an External Reference Setting
*/
typedef struct {
	LONG		id; 				// Unique identifier
	char		name[_MAX_PATH];	// Logical Name of xref
	char		fname[_MAX_PATH];	// Full filename of xref
	BOOL		bState; 			// ON or OFF
} PAN_XREF, *PPAN_XREF, FAR *LPPAN_XREF;

/*
**	Structure used to describe a layer.
*/
typedef struct {
	LONG		id; 			// Unique identifier
	char		name[STRLEN80]; // Name of layer
	COLORREF	color;			// RGB value of the layer
	BOOL		bState; 		// ON or OFF
	BOOL		fThawed;		// Frozen or Thawed
	char		pad[36];		// Pad to 128 bytes so that structure
								// does not straddle 64K boundary
								// (problem for DOS86 + WIN16)
} PAN_LAYER, *PPAN_LAYER, FAR *LPPAN_LAYER;

/*
**	Structure used to describe a block.
*/
typedef struct {
	LONG		id; 			// unique identifier
	char		name[STRLEN80]; // name of block
	char		pad[44];		// Pad to 128 bytes so that structure
								// does not straddle 64K boundary
								// (problem for DOS86 + WIN16)
} PAN_BLOCK, *PPAN_BLOCK, FAR *LPPAN_BLOCK;

/*
**	Structure used to describe a saved view.
*/
typedef struct {
	LONG		id; 			// unique identifier
	char		name[STRLEN80]; // name of view
	PAN_Point	vmin, vmax; 	// Window coordinates;
	Hmatrix 	view;			// transformation matrix
} PAN_VIEW, *PPAN_VIEW, FAR *LPPAN_VIEW;

/*
**	Structure used to describe a vector font.
*/
#define	PAN_MAXFONT_NAME		256
#define	PAN_MAXFONT_CHARWIDTHS	256
typedef	struct {
	DWORD 	dwType;									// Font type:  PAN_FONTTYPE_XXX
	DWORD	dwFlags;								// Font flags:  one or more PAN_FONTFLAG_XXX
	edatReal	Size;									// Font size.
	BOOL	fHmValid;								// Does hm contain a valid matrix.
	Hmatrix hm;										// Transformation matrix.
	edatReal	CharWidths[PAN_MAXFONT_CHARWIDTHS+1];	// Buffer of character widths
	char	szName[PAN_MAXFONT_NAME+1];				// Font name.
	char	szFileName[_MAX_PATH+1];				// File name containing the font definition.
} PAN_FONT, *PPAN_FONT, FAR *LPPAN_FONT;

typedef	struct PAN_BOOKMARK
{
	LONG	ID;					// Any app-defined ID
	int		level;				// 0:=root level
	int		fState;				// 0:=closed, 1:=opened, 2:=leaf
	char	name[_MAX_PATH];	// Descriptive name
	char	target[1024];		// Target destination.
}	PAN_BOOKMARK, *PPAN_BOOKMARK,
	_far *LPPAN_BOOKMARK, huge *HPPAN_BOOKMARK;

typedef	struct PAN_LINK
{
	DWORD			dwLinkFlag;
	int				nPageIndex;
	PANRECT			LinkRange;		
	PAN_BOOKMARK	LinkData;
}	PAN_LINK, *PPAN_LINK,
	_far *LPPAN_LINK, huge *HPPAN_LINK;


/************************************************************************
**	Declare the basic Document types ************************************
*************************************************************************/
typedef enum {
	PAN_UnknownFile,
	PAN_RasterFile,
	PAN_VectorFile,
	PAN_DatabaseFile,
	PAN_SpreadsheetFile,
	PAN_DocumentFile,
	PAN_ArchiveFile
} PAN_FileType;

/************************************************************************
**	A Colour Map ********************************************************
*************************************************************************/
typedef struct	{
	int 	ncolours;
#	define	MAXCMAP 256
	BYTE	r[MAXCMAP], g[MAXCMAP], b[MAXCMAP];
} PAN_Cmap, PANCMAP, *PPANCMAP, _far *LPPANCMAP;


#endif	/* AVTYPES_H */
