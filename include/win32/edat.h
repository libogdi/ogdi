/*
** EDAT.H (v 2.0)
**
** Copyright (c) 1995 Cimmetry Systems Inc., All Rights Reserved.
**
** EDAT definitions.
*/

#ifndef	__EDA_H__
#define	__EDA_H__

#ifndef RC_INVOKED
#include "pan.h"
#pragma	pack(1)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/*
**	API DEFINITIONS
*/

//	Some constants
#define	CE_MAX_NAME			257
#define	CE_HANDLE_NULL		0
#define	CE_MAX_MLINE		16

#define	CE_OPEN_RDONLY		0x01
#define	CE_OPEN_RDWR		0x02
#define	CE_OPEN_CREAT		0x04

//	Different file types supported
#define	CE_TYPE_UNKNOWN		0x00
#define	CE_TYPE_DWG			0x01
#define	CE_TYPE_DXF			0x02
#define	CE_TYPE_DGN			0x03
#define	CE_TYPE_CEL			0x04
#define	CE_TYPE_PRT			0x05

/* TABLE FLAGS */

//	Common table flags (except view table)
#define	TF_TBL_DEPENDENT	0x10
#define	TF_TBL_RESOLVED		0x20
#define	TF_TBL_USED			0x40
#define	TF_TBL_DELETED		0x80

//	Layer table flags
#define	TF_LAYER_FROZEN		0x01	// Frozen.
#define	TF_LAYER_FROZENNEW	0x02	// Frozen in new viewport.
#define	TF_LAYER_LOCKED		0x04	// Locked.

// Style table flags
#define	TF_STYLE_SHAPE		0x01	// Shape file instead of font file.
#define	TF_STYLE_VERTICAL	0x04	// Vertically oriented.

//	View table flags (for DGN)	
#define	TF_VIEW_OFF			0x01	// View is off.
#define	TF_VIEW_SYMB		0x02	// Level symbology is on.
#define	TF_VIEW_CONST		0x04	// Construction class is drawn. 
#define	TF_VIEW_DIM			0x08	// Dimension elements are displayed.
#define	TF_VIEW_FILL		0x10	// Area fill is on.
#define	TF_VIEW_BG			0x20	// Background is on.
#define	TF_VIEW_REFBD		0x40	// Ref boundaries is on.
#define	TF_VIEW_LNWT		0x80	// Line weight is on.

//	Mlinestyle table flags
#define	TF_ML_FILL			0x01	// Fill is on.
#define	TF_ML_MITER			0x02	// Display joint.
			
#define	TF_ML_CAP_LINE		0x01	// Display line.
#define	TF_ML_CAP_INNER		0x02	// Draw iner arc.
#define	TF_ML_CAP_OUTER		0x04	// Draw outer arc.
			
// Group table flag
#define	TF_GRP_SELECT		0x01	// Selectability on.

/* ENTITY FLAGS */

//	Common element header flags
#define	EF_EHDR_DELETED		0x01	// Entity is deleted.
#define	EF_EHDR_COMPLEX		0x02	// Entity is complex.
#define	EF_EHDR_XDATA		0x04	// Extended data present.
#define	EF_EHDR_MODIFIED	0x08	// Entity is modified.
#define	EF_EHDR_NEW			0x10	// Entity is new.

//	Entity flags : Block (also applied to block table)
#define	EF_BLK_UNNAMED		0x01
#define	EF_BLK_HASATTRIBS	0x02
#define	EF_BLK_ISXREF		0x04
#define	EF_BLK_ISRASXREF	0x08
#define	EF_BLK_ISDEPEND		0x10
#define	EF_BLK_RESOLVED		0x20
#define	EF_BLK_USED			0x40

//	Entity flags : Text-Related
#define EF_JUSTX_LEFT		0
#define EF_JUSTX_CENTER		1
#define EF_JUSTX_RIGHT		2
#define EF_JUSTX_ALIGNED	3
#define EF_JUSTX_MIDDLE		4
#define EF_JUSTX_FIT		5

#define EF_JUSTY_BASELINE	0
#define EF_JUSTY_BOTTOM		1
#define EF_JUSTY_MIDDLE		2
#define EF_JUSTY_TOP		3

#define EF_GEN_MIRRORX		0x02
#define EF_GEN_MIRRORY		0x04

//	Entity flags : Attribute
#define EF_ATT_INVISIBLE	0x01
#define EF_ATT_CONSTANT		0x02
#define EF_ATT_VERIFY		0x04
#define EF_ATT_PRESET		0x08

#define EF_ATYPE_CHAR		0
#define EF_ATYPE_LONG		1
#define EF_ATYPE_DOUB		2

//	Entity flags : Polyline
#define	EF_PLINE_CLOSEDM	0x01
#define	EF_PLINE_CURVEFIT	0x02
#define	EF_PLINE_SPLINEFIT	0x04
#define	EF_PLINE_3D			0x08
#define	EF_PLINE_MESH		0x10
#define	EF_PLINE_CLOSEDN	0x20
#define	EF_PLINE_FACE		0x40

//	Entity flags : Polyline-types
#define	EF_PTYPE_NORMAL		0
#define	EF_PTYPE_QUAD		5
#define	EF_PTYPE_BSPLINE	6
#define	EF_PTYPE_BEZIER		8

//	Entity flags : Vertex
#define	EF_VER_EXTRA		0x01
#define	EF_VER_CURVEFIT		0x02
#define	EF_VER_SPLINE		0x08
#define	EF_VER_FRAME		0x10
#define	EF_VER_3DPLINE		0x20
#define	EF_VER_3DPMESH		0x40	
#define	EF_VER_3DPFACE		0x80	

//	Entity flags : Face-visibility
#define	EF_FACE_HIDEE1		0x01
#define	EF_FACE_HIDEE2		0x02
#define	EF_FACE_HIDEE3		0x04
#define	EF_FACE_HIDEE4		0x08

// Entity flags : Dimension
#define EF_DIMTYPE_NORMAL	0
#define EF_DIMTYPE_ALIGNED	1
#define EF_DIMTYPE_ANGULAR	2
#define EF_DIMTYPE_DIAMETER	3
#define EF_DIMTYPE_RADIUS	4
#define EF_DIMTYPE_ANG3PT	5
#define EF_DIMTYPE_YORDIN	6
#define EF_DIMTYPE_XORDIN	7

// Entity flags : Mtext
#define EF_ATTCH_TL		1		// Top    Left.
#define EF_ATTCH_TC		2		// Top    Center
#define EF_ATTCH_TR		3		// Top    Right
#define EF_ATTCH_ML		4		// Middle Left.
#define EF_ATTCH_MC		5		// Middle Center
#define EF_ATTCH_MR		6		// Middle Right
#define EF_ATTCH_BL		7		// Bottom Left.
#define EF_ATTCH_BC		8		// Bottom Center
#define EF_ATTCH_BR		9		// Bottom Right

#define EF_DRW_L2R		1		// Left to Right.
#define EF_DRW_R2L		2		// Right to Left.
#define EF_DRW_T2B		3		// Top to Bottom.
#define EF_DRW_B2T		4		// Bottom to Top.

// Entity flags : Spline
#define EF_SPLINE_CLOSED	0x01	// Closed spline.
#define EF_SPLINE_PERIODIC	0x02	// Periodical spline.
#define EF_SPLINE_RATIONAL	0x04	// Rational spline.
#define EF_SPLINE_PLANAR	0x08	// Planar spline.
#define EF_SPLINE_LINEAR	0x10	// Linear spline.
#define EF_SPLINE_FIT		0x20	// Fit spline.

// Entity flags : MLine
#define EF_MLJUST_TOP		0	// Top justification.
#define EF_MLJUST_ZERO		1	// Zerojustification.
#define EF_MLJUST_BOTTOM	2	// Bottom justification.

// Entity flags : Leader path type
#define	EF_PATH_ST			0	// Straight line segment.
#define	EF_PATH_SP			1	// Spline.

// Entity flags : Spline surface
#define	EF_SPLSURF_CLOSEDU	0x01	// Closed in u-dir.
#define	EF_SPLSURF_CLOSEDV	0x02	// Closed in v-dir.
#define	EF_SPLSURF_RATIONAL	0x04	// Rational.

// Entity flags : Cone
#define	EF_CTYPE_GEN		0		// General.
#define	EF_CTYPE_RCYL		1		// Right cylinder.
#define	EF_CTYPE_CYL		2		// Cylinder.
#define	EF_CTYPE_RCONE		3		// Right cone.
#define	EF_CTYPE_CONE		4		// Cone.
#define	EF_CTYPE_RTCONE		5		// Right truncated cone.
#define	EF_CTYPE_TCONE		6		// Truncated cone.

// Entity flags : Vertices
#define	EF_VTYPE_UNKNOWN	0		// Unknown.
#define	EF_VTYPE_LINESTR	1		// Line string.
#define	EF_VTYPE_SHAPE		2		// Shape.
#define	EF_VTYPE_CURVE		3		// Curve.

// Entity flags : CmplxHdr (complex header)
#define	EF_HTYPE_UNKNOWN	0		// Unknown.
#define	EF_HTYPE_CCHAIN		1		// Complex chain.
#define	EF_HTYPE_CSHAPE		2		// Complex shape.
#define	EF_HTYPE_SURFACE	3		// 3D surface.
#define	EF_HTYPE_SOLID		4		// 3D solid.

// Entity flags : Cell Library Header
#define	EF_CLTYPE_GRAPHIC	0		// Graphic cell.
#define	EF_CLTYPE_COMMAND	1		// Command menu cell.
#define	EF_CLTYPE_CURSOR	2		// Cursor button menu cell.
#define	EF_CLTYPE_FUNCTION	3		// Function key menu cell.
#define	EF_CLTYPE_MATRIX	4		// Matrix menu cell.
#define	EF_CLTYPE_TUTORIAL	5		// Tutorial cell.
#define	EF_CLTYPE_VOICE		6		// Voice menu cell.

//Entity flags: lwpolyline
#define EF_LWPLINE_CONSTWIDTH 		0x0004        //All vertices have the same with (constant width)
#define EF_LWPLINE_BULGE	 		0x0010		//Bulges are present.                              
#define	EF_LWPLINE_VARIABLEWIDTH	0x0020		//Each vetex has its own start width and end width.

// Entity linetype and color
#define	CE_BYLAYER			-1
#define CE_BYBLOCK			-2
#define CE_UNDEFINED		-32768

// Drawing spaces.
#define CE_SPACE_MODEL		-1
#define CE_SPACE_PAPER		-2

// Preview image type.
#define	CE_PV_BMP			2
#define	CE_PV_WMF			3

/*
**	API STRUCTURES
*/

typedef int			Bool;


typedef	DWORD		CE_HANDLE, *PCE_HANDLE,
					__near *NPCE_HANDLE, __far *LPCE_HANDLE;

typedef	DWORD		CE_ENTPOS, *PCE_ENTPOS,
					__near *NPCE_ENTPOS, __far *LPCE_ENTPOS;

typedef COLORREF	*PCOLORREF,
					__near *NPCOLORREF,	__far *LPCOLORREF;

typedef	double		edatDouble, *PDOUBLE,
					__near *NPDOUBLE, __far *LPDOUBLE;

typedef	struct {
	DWORD		low;
	DWORD		high;
}	CE_ENTHANDLE, *PCE_ENTHANDLE,
	__near *NPCE_ENTHANDLE, __far *LPCE_ENTHANDLE;

typedef	struct {
	edatDouble		x, y, z;
}	Dpoint3, DPOINT3, *PDPOINT3,
	__near *NPDPOINT3, __far *LPDPOINT3;

typedef	struct {
	edatDouble		x, y;
}	Dpoint2, DPOINT2, *PDPOINT2,
	__near *NPDPOINT2, __far *LPDPOINT2;

//	TABLES
typedef enum {
	CE_TBL_Unknown = 0,
	CE_TBL_Appid,   //1
	CE_TBL_Block,   //2
	CE_TBL_Dimstyle,//3
	CE_TBL_Group,   //4
	CE_TBL_Layer,   //5
	CE_TBL_Ltype,   //6
	CE_TBL_MLStyle, //7
	CE_TBL_Style,   //8
	CE_TBL_UCS,     //9
	CE_TBL_View,    //10
	CE_TBL_Vport,   //11
	CE_TBL_Image,   //12	//Added on 10/02/97
	CE_TBL_LAST,    //13
} TableType;

typedef struct {
	unsigned short	DB_ID;
	DWORD			TableIndex;
	DWORD			MS_LINK;
} DATABASE;

typedef struct {
	char		szName[CE_MAX_NAME];
	DWORD		dwFlags;
}	CE_APPID, *PCE_APPID,
	__near *NPCE_APPID, __far *LPCE_APPID;

typedef struct {
	char		szName[CE_MAX_NAME];
	char		szXRefName[CE_MAX_NAME];
	DWORD		dwFlags;
	DWORD		offset;	     //offset into the block section
}	CE_BLOCK, *PCE_BLOCK,
	__near *NPCE_BLOCK, __far *LPCE_BLOCK;

typedef struct {
	char		szName[CE_MAX_NAME];
	DWORD		dwFlags;
}	CE_DIMSTYLE, *PCE_DIMSTYLE,
	__near *NPCE_DIMSTYLE, __far *LPCE_DIMSTYLE;

typedef struct {
	char		szName[CE_MAX_NAME];
	COLORREF	rgbColor;
	int			nColor;
	int			nLtype;
	edatDouble		width;
	DWORD		dwFlags;	
}	CE_LAYER, *PCE_LAYER,
	__near *NPCE_LAYER, __far *LPCE_LAYER;

typedef struct {
	char		szName[CE_MAX_NAME];
	char		szDescription[CE_MAX_NAME];
	DWORD		dwFlags;
}	CE_LTYPE, *PCE_LTYPE,
	__near *NPCE_LTYPE, __far *LPCE_LTYPE;

typedef struct {
	char		szName[CE_MAX_NAME];			// Style name.
	char		szFontFilename[CE_MAX_NAME];	// Font or shape file name.
	edatChar		szBFontFilename[CE_MAX_NAME];   // Big font file name.
	DWORD		dwFlags;
	WORD		wGen;							// See EF_GEN_XXX.		
	edatDouble		wfactor;
	edatDouble		height;
	edatDouble		oblique;
}	CE_STYLE, *PCE_STYLE,
	__near *NPCE_STYLE, __far *LPCE_STYLE;

typedef struct {
	char		szName[CE_MAX_NAME];
	Dpoint3		origin;
	Dpoint3		Xaxis;
	Dpoint3		Yaxis;
	DWORD		dwFlags;
}	CE_UCS, *PCE_UCS,
	__near *NPCE_UCS, __far *LPCE_UCS;

typedef struct {
	char		szName[CE_MAX_NAME];		// Style name.
	char	 	szDescription[CE_MAX_NAME];	// Description.
	DWORD		dwFlags;			// Dxf 70 (see TF_ML_XXX).			
	DWORD		stCap;				// Dxf 71 (see TF_ML_CAP_XXX).			
	DWORD		endCap;				// Dxf 72 (see TF_ML_CAP_XXX).			
	edatDouble		stAng;				// Start angle.
	edatDouble		endAng;				// End angle.
	int			nLine;				// No. of lines.
	edatDouble		lineOffset[CE_MAX_MLINE];	// Array of line offset.
	int			lineColor[CE_MAX_MLINE];	// Array of line color.
	int			lineLtype[CE_MAX_MLINE];	// Array of line ltype.			
	edatDouble		lineWidth[CE_MAX_MLINE];	// Array of line weight.			
	int			stColor;			// Color of st. cap.
	int			stLtype;			// Line type of st. cap.			
	edatDouble		stWidth;			// Line weight of st. cap.			
	int			endColor;			// Color of end cap.
	int			endLtype;			// Line type of end cap.			
	edatDouble		endWidth;			// Line weight of end cap.			
	int			nColor;				// Fill color.
}	CE_MLSTYLE, *PCE_MLSTYLE,
	__near *NPCE_MLSTYLE, __far *LPCE_MLSTYLE;

typedef	struct {
	char		szName[CE_MAX_NAME];
	DWORD		dwFlags;				
	Dpoint3		pViewMin;		// Viewed area: min. (VCS)
	Dpoint3		pViewMax;		// Viewed area: max. (VCS)
	Hmatrix		transmatrix;	// View transformation matrix.
	edatDouble		FrontClip;		// Front clipping plane.
	edatDouble		BackClip;		// Back clipping plane.
	edatDouble	    LensLength;		// Lens length.
	WORD		viewmode;		// ACAD "viewmode" system variable.
	int			nLayers;		// Size of "layerstate" buffer.
	LPBYTE		layerstate;		// 0 := off,	1 := on
	Dpoint2		viewcenter;		//Used to solve for viewtarget point (in writing mode)
} 	CE_VIEW, *PCE_VIEW,
	__near *NPCE_VIEW, __far *LPCE_VIEW;

typedef struct {
	char		mode;		// 0 (off), 1 (on).
	char		style;		// 0 (stabdard), 1 (isometric).
	edatInt			isopair;	// 0 (left), 1 (top), or 2 (right).
	edatDouble		basex;		// center point (2D).
	edatDouble		basey;
	edatDouble		unitx;		// spacing in x & y.
	edatDouble 		unity;
	edatDouble		angle;		// snap rotation angle.
}	SNAPINFO;

typedef struct {
	char		mode;		// 0 (off), 1 (on).
	edatDouble		unitx;		// spacing in x & y.
	edatDouble 		unity;
}	GRIDINFO;

typedef struct {
	char		fast;		// 0 (off), 1 (on).
	edatInt			circle;		// circle zoom percent.
}	ZOOMINFO;

typedef	struct {
	char		szName[CE_MAX_NAME];
	DWORD		dwFlags;				
	Dpoint3		pBoxMin;		// Lower-left corner of the view box.
	Dpoint3		pBoxMax;		// Upper-right corner of the view box.
	Dpoint3		pViewMin;		// Viewed area: min. (VCS)
	Dpoint3		pViewMax;		// Viewed area: max. (VCS)	
	Dpoint3		viewDir;		// View direction.
	Dpoint3		viewTarget;		// View direction.
	edatDouble		twist;			// Twist angle.
	edatDouble		frontClip;		// Front clipping plane.
	edatDouble		backClip;		// Back clipping plane.
	edatDouble	    lenslength;		// Lens length.
	WORD		viewmode;		// ACAD "viewmode" system variable.
	edatChar	ucsicon;		// 1 -- on; 2 -- float at origin.
	SNAPINFO	snap;			
	GRIDINFO	grid;
	ZOOMINFO	zoom;
	int			nLayers;		// Size of "layerstate" buffer.
	LPBYTE		layerstate;		// 0 := off,	1 := on    
	Dpoint2		vportcenter;		//Used to solve for vportaspect (in writing mode)	
} 	CE_VPORT, *PCE_VPORT,
	__near *NPCE_VPORT, __far *LPCE_VPORT;
	
typedef struct {
	char		szName[CE_MAX_NAME]; 		// Group name.
	char		szPath[CE_MAX_NAME];	// Group description.
	DWORD		dwFlags;					// See TF_GRP_XXX.
	edatDouble		width;
	edatDouble		height;
	edatDouble		Xscale;
	edatDouble		Yscale;
}	CE_IMAGEREF, *PCE_IMAGEREF,
	__near *NPCE_IMAGEREF, __far *LPCE_IMAGEREF;

typedef struct {
	char		szName[CE_MAX_NAME]; 		// Group name.
	char		szDescription[CE_MAX_NAME];	// Group description.
	DWORD		dwFlags;					// See TF_GRP_XXX.
	int			nEntities;					// No. of entities in this group.
	LPCE_ENTHANDLE	lpHandles;				// List of entities' handle.	
}	CE_GROUP, *PCE_GROUP,
	__near *NPCE_GROUP, __far *LPCE_GROUP;
typedef	struct {
	int				index;  	    // I.D. of the record in the table
	DWORD			recordsize;		//size of each record in the table
	CE_ENTPOS		dwPos;      	//position of the table in the original file if not new entry
	CE_ENTPOS		dwNewPos;   	//position of the table record in the working file 
	Bool			fModified;		//flag for modified records.
	Bool			fNew;			//flag for new records
//	CE_ENTPOS		New_Pos;	//the new position of the block record in the drawing dwg file

} RECORDINFO, *PRECORDINFO,
__near *NPRECORDINFO, __far *LPRECORDINFO;

typedef struct {
	TableType		type; 
	RECORDINFO		RecordInfo;
	union {
		CE_APPID		appid;
		CE_BLOCK		block;
		CE_DIMSTYLE		dimstyle;
		CE_GROUP		group;
		CE_LAYER		layer;
		CE_LTYPE		ltype;
		CE_MLSTYLE		mlstyle; 
		CE_STYLE		style; 
		CE_UCS			ucs;
		CE_VIEW			view;
		CE_VPORT		vport;
		CE_IMAGEREF		image;
		char			filler[1024];
	} u;
}	CE_TABLEENTRY, *PCE_TABLEENTRY,
	__near *NPCE_TABLEENTRY, __huge *LPCE_TABLEENTRY;

//	ENTITIES

typedef enum {
	CE_ENT_Unknown = 0,
	CE_ENT_Line,			//	1
	CE_ENT_Point,           //	2
	CE_ENT_Ellipse,         //	3
	CE_ENT_Shape,           //	4
	CE_ENT_Text,            //	5
	CE_ENT_Arc,             //	6
	CE_ENT_Trace,           //	7
	CE_ENT_Solid,           //	8
	CE_ENT_Block,           //	9
	CE_ENT_EndBlock,        //	10
	CE_ENT_Insert,          //	11
	CE_ENT_Attdef,          //	12
	CE_ENT_Attrib,          //	13
	CE_ENT_Seqend,          //	14
	CE_ENT_Polyline,        //	15
	CE_ENT_Vertex,          //	16
	CE_ENT_Face3d,          //	17
	CE_ENT_Dimension,       // 	18
	CE_ENT_Viewport,        //  19
	CE_ENT_MText,           //	20
	CE_ENT_3DSolid,         //	21
	CE_ENT_Body,            //	22
	CE_ENT_Region,          //	23
	CE_ENT_Spline,          //	24
	CE_ENT_Ray,             //	25
	CE_ENT_XLine,           //	26
	CE_ENT_MLine,           //	27
	CE_ENT_Tolerance,       //	28
	CE_ENT_Leader,          //	29
	CE_ENT_OLEFrame,        //  30
	CE_ENT_CmplxHdr,        //	31
	CE_ENT_Vertices,        //	32
	CE_ENT_AttdefSet,       //	33
	CE_ENT_Cone,            //	34
	CE_ENT_SplineSurf,      //	35
	CE_ENT_RasterData,      //	36
	CE_ENT_CelLibHdr,       //	37
	CE_ENT_GDE,             //	38
	CE_ENT_MSE,             //	39
//ZZZ
	CE_ENT_LWPolyline, 	//dwg14   //	40
	CE_ENT_Image,       //dwg14   //	41
	CE_ENT_Hatch,       //dwg14   //	42
/***** Non-graphical entities in ACAD R13, named but not supported *****/

	CE_ENT_Dictionary,
	CE_ENT_BlockHdr,
	CE_ENT_BlockRec,
	CE_ENT_LayerTblHdr,
	CE_ENT_LayerTbl,
	CE_ENT_StyleTblHdr,
	CE_ENT_StyleTbl,
	CE_ENT_LtypeTblHdr,
	CE_ENT_LtypeTbl,
	CE_ENT_ViewTblHdr,
	CE_ENT_ViewTbl,
	CE_ENT_UCSTblHdr,
	CE_ENT_UCSTbl,
	CE_ENT_VportTblHdr,
	CE_ENT_VportTbl,
	CE_ENT_AppIDTblHdr,
	CE_ENT_AppIDTbl,
	CE_ENT_DStyleTblHdr,
	CE_ENT_DStyleTbl,
	CE_ENT_ViewportHdr70,
	CE_ENT_ViewportHdr71,
	CE_ENT_Group,
	CE_ENT_ImageRef,
	CE_ENT_MLStyle,
	
/******* Entity of type 18 in ACAD R12 ******/
	CE_ENT_Eighteen,
	
	CE_ENT_LAST,
} EntityType;

typedef	struct {
	EntityType		type;
	DWORD			dwFlags;	// See EF_EHDR_XXX.
	int				nColor;
	int				nLayer;
	int				nLtype;
	edatDouble			ltscale;
	edatDouble			zthickness;
	edatDouble			width;
	Dpoint3			extrusion;
	edatDouble			twist;
	CE_ENTHANDLE	handle;
	int				pspace;
	DATABASE		databaselink[16];
	DWORD			dwReserved[16];
}	CE_ENTHDR, *PCE_ENTHDR,
	__near *NPCE_ENTHDR, __far *LPCE_ENTHDR;

typedef	struct {
	Dpoint3			p0;
} 	CE_ENT_POINT, *PCE_ENT_POINT,
	__near *NPCE_ENT_POINT, __far *LPCE_ENT_POINT;

typedef	struct {
	Dpoint3			p0;
	Dpoint3			p1;
} 	CE_ENT_LINE, *PCE_ENT_LINE,
	__near *NPCE_ENT_LINE, __far *LPCE_ENT_LINE;

typedef	struct {
	Dpoint3			centre;
	edatDouble			radiusX;
	edatDouble			radiusY;
	edatDouble			stAng;
	edatDouble			endAng;
} 	CE_ENT_ARC, *PCE_ENT_ARC,
	__near *NPCE_ENT_ARC, __far *LPCE_ENT_ARC;

typedef	struct {
	Dpoint3			centre;
	edatDouble			radiusX;
	edatDouble			radiusY;
} 	CE_ENT_ELLIPSE, *PCE_ENT_ELLIPSE,
	__near *NPCE_ENT_ELLIPSE, __far *LPCE_ENT_ELLIPSE;

typedef	struct {
	Dpoint3			p0;
	Dpoint3			p1;
	Dpoint3			p2;
	Dpoint3			p3;
} 	CE_ENT_TRACE, *PCE_ENT_TRACE,
	__near *NPCE_ENT_TRACE, __far *LPCE_ENT_TRACE;

typedef	struct {
	Dpoint3			p0;
	Dpoint3			p1;
	Dpoint3			p2;
	Dpoint3			p3;
} 	CE_ENT_SOLID, *PCE_ENT_SOLID,
	__near *NPCE_ENT_SOLID, __far *LPCE_ENT_SOLID;

typedef	struct {
	Dpoint3			p0;			// Insertion point.
	char			szName[CE_MAX_NAME];
	char			szAltName[CE_MAX_NAME];
	char			szXRefName[CE_MAX_NAME];
	DWORD			dwFlags;	// See: EF_BLK_XXX
	CE_ENTPOS		dwEndPos;	// Block ending position (for DGN).
} 	CE_ENT_STARTBLOCK, *PCE_ENT_STARTBLOCK,
	__near *NPCE_ENT_STARTBLOCK, __far *LPCE_ENT_STARTBLOCK;

typedef	struct {
	Dpoint3				p0;			// Insertion point
	int					nID;		// Block id
	Dpoint3				scale;		// x/y/z scaling
	int					nCol;		// Multiple-insertion
	int					nRow;		// Repitition.
	Dpoint3				spacing;	// Multiple-insertion spacing.
	Bool				fAttrib;	// Attributes follow.
	Bool				fBlock;		// Start block information included.
	CE_ENT_STARTBLOCK	sblock;	// Block entity information.
} 	CE_ENT_INSERT, *PCE_ENT_INSERT,
	__near *NPCE_ENT_INSERT, __far *LPCE_ENT_INSERT;

typedef	struct {
	char			dummy;
} 	CE_ENT_ENDBLOCK, *PCE_ENT_ENDBLOCK,
	__near *NPCE_ENT_ENDBLOCK, __far *LPCE_ENT_ENDBLOCK;


typedef	struct {
	WORD			wFlags;		// See: EF_ATT_XXX
	WORD			wType;		// See: EF_ATYPE_XXX
	Dpoint3			p0;			// Insertion point
	Dpoint3			p1;			// Alignment point
	char			szSet[CE_MAX_NAME];
	char			szTag[CE_MAX_NAME];
	union {
		char		szVal[CE_MAX_NAME];
		long		lVal;
		edatDouble		dVal;
	} val;
	int				nLength;
	int				nFont;		// Font-Style
	edatDouble			height;		// Font-height
	edatDouble			wfactor;	// Width factor (def=1.0)
	edatDouble			oblique;	// Obliquing angle.
	WORD			wJustX;		// See: EF_JUSTX_XXX
	WORD			wJustY;		// See: EF_JUSTY_XXX
	WORD			wGen;		// See: EF_GEN_XXX
} 	CE_ENT_ATTRIB, *PCE_ENT_ATTRIB,
	__near *NPCE_ENT_ATTRIB, __far *LPCE_ENT_ATTRIB;

typedef	struct {
	WORD			wFlags;		// See: EF_ATT_XXX
	WORD			wType;		// See: EF_ATYPE_XXX
	Dpoint3			p0;			// Insertion point
	Dpoint3			p1;			// Alignment point
	char			szPrompt[CE_MAX_NAME];
	char			szTag[CE_MAX_NAME];
	union {
		char		szVal[CE_MAX_NAME];
		long		lVal;
		edatDouble		dVal;
	} val;
	int				nLength;
	int				nFont; 		// Font-Style
	edatDouble			height; 	// Font-height
	edatDouble			wfactor; 	// Width factor (def=1.0)
	edatDouble			oblique; 	// Obliquing angle.
	WORD			wJustX; 	// See: EF_JUSTX_XXX
	WORD			wJustY;		// See: EF_JUSTY_XXX
	WORD			wGen;		// See: EF_GEN_XXX
} 	CE_ENT_ATTDEF, *PCE_ENT_ATTDEF,
	__near *NPCE_ENT_ATTDEF, __far *LPCE_ENT_ATTDEF;

typedef	struct {
	DWORD			dwFlags;	// See: EF_PLINE_XXX
	DWORD			dwType;		// See: EF_PTYPE_XXX
	Dpoint3			p0;			// Insertion point
	edatDouble			stWidth;	// Starting width
	edatDouble			endWidth;	// Ending width
	int				nMeshM;		// Mesh count
	int				nMeshN;		// Mesh count
	int				nSurfM;		// Surface count
	int				nSurfN;		// Surface count
 } 	CE_ENT_PLINE, *PCE_ENT_PLINE,
	__near *NPCE_ENT_PLINE, __far *LPCE_ENT_PLINE;

typedef	struct {
	DWORD			dwFlags;	// See: EF_VER_XXX
	Dpoint3			p0;
	edatDouble			stWidth;
	edatDouble			endWidth;
	edatDouble			bulge;
	edatDouble			tangent;
	int				IdxFace[4];	// Vertex Indexes (face of the mesh).
 } 	CE_ENT_VERTEX, *PCE_ENT_VERTEX,
	__near *NPCE_ENT_VERTEX, __far *LPCE_ENT_VERTEX;

typedef	struct {
	char			dummy;
 } 	CE_ENT_SEQEND, *PCE_ENT_SEQEND,
	__near *NPCE_ENT_SEQEND, __far *LPCE_ENT_SEQEND;

//zzz
typedef	struct {
	DWORD			dwFlags;	// See: EF_PLINE_XXX    (1== closed; 128 == plinegen)
	int				flag;		//flag to see if the lwpolyline has constant width or not...                                                                                  
	edatDouble			ConstWidth;	// constant with for all the verteces.
	int				numVertices;                                                            
	PAN_Point		*vertex;     //vertex coordinates.                 
	edatDouble			*stWidth;	// Starting width for each vertex if variable width
	edatDouble			*endWidth;	// Ending width  for each vertex if variable width
	edatDouble			*bulge;		//Bulge for each vertex.
 } 	CE_ENT_LWPOLYLINE, *PCE_ENT_LWPPLYLINE,
	__near *NPCE_ENT_LWPOLYLINE, __far *LPCE_ENT_LWPOLYLINE;

typedef struct {
	PAN_Point	insertpt;	//Insertion point of the image.
	edatDouble		width;
	edatDouble		height;
	int			brightness;
	int			contrast;
	int			fade;
	char		imagepath[CE_MAX_NAME];
} CE_ENT_IMAGE, *PCE_ENT_IMAGE,
	__near *NPCE_ENT_IMAGE, __far *LPCE_ENT_IMAGE;

typedef struct {
	char		HatchName[CE_MAX_NAME];
} CE_ENT_HATCH, *PCE_ENT_HATCH,
	__near *NPCE_ENT_HATCH, __far *LPCE_ENT_HATCH;

typedef	struct {
	WORD			wFlags;	// See: EF_FACE_XXX
	Dpoint3			p0;		// 4 points defining
	Dpoint3			p1;		// the face.
	Dpoint3			p2;
	Dpoint3			p3;
 } 	CE_ENT_FACE, *PCE_ENT_FACE,
	__near *NPCE_ENT_FACE, __far *LPCE_ENT_FACE;

typedef	struct {
	Dpoint3			p0;		// Insertion point
	Dpoint3			p1;		// Alignment point
	char			szText[CE_MAX_NAME];
	int				nFont;
	edatDouble			height;
	edatDouble			wfactor;
	edatDouble			oblique;
	WORD			wJustX;
	WORD			wJustY;
	WORD			wGenflags;
 } 	CE_ENT_TEXT, *PCE_ENT_TEXT,
	__near *NPCE_ENT_TEXT, __far *LPCE_ENT_TEXT;

typedef	struct {
	Dpoint3			p0;			// Insertion point.
	int				nFont;		// No. of the style. (rel. to the style table)
	int				nShape;     // No. of the shape. (rel. to the shape file)
	char			szName[CE_MAX_NAME];// Name of the shape.
	edatDouble			height;
	edatDouble			wfactor;
	edatDouble			oblique;
 } 	CE_ENT_SHAPE, *PCE_ENT_SHAPE,
	__near *NPCE_ENT_SHAPE, __far *LPCE_ENT_SHAPE;

typedef	struct {
	int				nBlock;	// Block no.
	Dpoint3			p0;		// Insertion point.
	Dpoint3			pMid;	// Text mid point.
	Dpoint3			pClone;	// Clone insertion point.
	Dpoint3			pDef1;	// Grp 13-33.
	Dpoint3			pDef2;	// Grp 14-34.
	Dpoint3			pDef3;	// Grp 15-35.
	Dpoint3			pDef4;	// Grp 16-36.
	Dpoint3			scale;	//Group 41-43.
	WORD			wType;	// See: EF_DIMTYPE_XXX
	char			szText[CE_MAX_NAME];
	int				nFont;
	edatDouble			height;
	edatDouble			wfactor;
	edatDouble			rot;
	edatDouble			oblique;  
	edatDouble			leaderlen; //Leader length for radius and diameter dimension (Group 40)
	WORD			wJustX;		
	WORD			wJustY;		
	WORD			wGenflags;		
} 	CE_ENT_DIMENSION, *PCE_ENT_DIMENSION,
	__near *NPCE_ENT_DIMENSION, __far *LPCE_ENT_DIMENSION;

typedef	struct {
	Dpoint3			p0;			// Placement : min (papersapce)
	Dpoint3			p1;			// Placement : max (paperspace)
	int				nID;    	// Viewport ID.
	int				nStatus;   	// Viewport status.
	char			szName[CE_MAX_NAME]; 
	Dpoint3			pViewMin;	// Viewed area: min. (VCS)
	Dpoint3			pViewMax;	// Viewed area: max. (VCS)
	Dpoint3			viewTarget;	// View target point.
	edatDouble			frontClip;	// Front clipping plane.
	edatDouble			backClip;	// Back clipping plane.
	edatDouble	    	lenslength;	// Lens length.         
	edatDouble			vportwidth;
	edatDouble			vportheight;
	WORD			viewmode;	// ACAD "viewmode" system variable.
	edatChar		ucsicon;	// 1 -- on; 2 -- float at origin.
	SNAPINFO		snap;		// Snap characteristics.			
	GRIDINFO		grid;		// Grid characteristics.
	ZOOMINFO		zoom;		// Zoom characteristics.
	int				nLayers;	// Size of "layerstate" buffer.
	LPBYTE			layerstate;	// 0 := off,	1 := on
} 	CE_ENT_VIEWPORT, *PCE_ENT_VIEWPORT,
	__near *NPCE_ENT_VIEWPORT, __far *LPCE_ENT_VIEWPORT;

typedef	struct {
	Dpoint3			p0;			// Insertion point.
	int				nFont;		// Text style no.
	edatDouble			height;		// Font height.
	edatDouble			wfactor;	// Font width factor.
	edatDouble			width;		// Reference rectangle width.
	LPBYTE			lpText;		// The text string.
	WORD			wAttach;	// See EF_ATTCH_XX.		
	WORD			wDraw;		// See EF_DRW_XXX.		
} 	CE_ENT_MTEXT, *PCE_ENT_MTEXT,
	__near *NPCE_ENT_MTEXT, __far *LPCE_ENT_MTEXT;

typedef	struct {
	Dpoint3			p0;			// Base point.
	Dpoint3			p1;			// Direction.
} 	CE_ENT_RAY, *PCE_ENT_RAY,
	__near *NPCE_ENT_RAY, __far *LPCE_ENT_RAY;

typedef	struct {
	Dpoint3			p0;			// Base point.
	Dpoint3			p1;			// Direction.
} 	CE_ENT_XLINE, *PCE_ENT_XLINE,
	__near *NPCE_ENT_XLINE, __far *LPCE_ENT_XLINE;

typedef	struct {
	int				degree;			// Degree of the spline.		
	WORD			wFlags;			// See EF_SPLINE_XXX.		
	int				nKnot;			// No. of knots.
	int				nCont;			// No. of control points.
	int				nFit;			// No. of fit points.
	edatDouble			tlrFit;			// Fit tolerance.
	edatDouble			tlrCont;		// Control point tolerance.
	edatDouble			tlrFitSpline;	// Fit tolerance for the fit spline.
	Dpoint3			stTang;			// Start tangent.
	Dpoint3			endTang;		// End tangent.
	LPDOUBLE		lpKnots;		// Pointer to knot values.
	LPDOUBLE		lpContWts;		// Pointer to wt. of control pts.
	LPDPOINT3		lpConts;		// Pointer to control pts.
	LPDPOINT3		lpFits;			// Pointer to fit pts.
} 	CE_ENT_SPLINE, *PCE_ENT_SPLINE,
	__near *NPCE_ENT_SPLINE, __far *LPCE_ENT_SPLINE;

typedef	struct {
	char			dummy;
} 	CE_ENT_ACIS, *PCE_ENT_ACIS,
	__near *NPCE_ENT_ACIS, __far *LPCE_ENT_ACIS;

typedef	struct {
	WORD			wJust;			// See EF_MLJUST_XXX.		
	Bool			fClosed;		// 1 for CLOSED.
	int				nStyle;			// Ref. to mlinestyle table.
	edatDouble			scale;			// Scale factor.
	int				nVertex;		// No. of vertices.
	LPDPOINT3		lpVertices;		// Pointer to vertex cordinates.
} 	CE_ENT_MLINE, *PCE_ENT_MLINE,
	__near *NPCE_ENT_MLINE, __far *LPCE_ENT_MLINE;

typedef	struct {
	Dpoint3			p0;				// Insertion point.
	char			szText[CE_MAX_NAME];			
	int				nDim;			// Ref. to dimstyle table.
} 	CE_ENT_TOLERANCE, *PCE_ENT_TOLERANCE,
	__near *NPCE_ENT_TOLERANCE, __far *LPCE_ENT_TOLERANCE;

typedef	struct {
	int				nDim;			// Ref. to dimstyle table.
	WORD			wType;			// EF_PATH_XXX.
	int				nVertex;		// No. of vertices.
	LPDPOINT3		lpVertices;		// Pointer to vertex cordinates.
} 	CE_ENT_LEADER, *PCE_ENT_LEADER,
	__near *NPCE_ENT_LEADER, __far *LPCE_ENT_LEADER;

typedef	struct {
	Dpoint3			p0;				// Bounding box min.
	Dpoint3			p1;				// Bounding box max.
} 	CE_ENT_OLEFRAME, *PCE_ENT_OLEFRAME,
	__near *NPCE_ENT_OLEFRAME, __far *LPCE_ENT_OLEFRAME;


// Some entity types for MicroStation.

typedef	struct {
	WORD			wType;			// See EF_VTYPE_XXX.				
	Bool			fClosed;		// 0 -- opened; 1 -- closed.
	int				nVertex;		// Limited to 101 vertices.
	LPDPOINT3		lpVertices;		// Pointer to vertex cordinates.
} 	CE_ENT_VERTICES, *PCE_ENT_VERTICES,
	__near *NPCE_ENT_VERTICES, __far *LPCE_ENT_VERTICES;

typedef	struct {
	char	szName[CE_MAX_NAME];	// Name of the set.
	int		nAttdef;				// No. of attdefs in the set.
	LPCE_ENT_ATTDEF	lpAttdefs;		// Pointer to attdefs.
} 	CE_ENT_ATTDEFSET, *PCE_ENT_ATTDEFSET,
	__near *NPCE_ENT_ATTDEFSET, __far *LPCE_ENT_ATTDEFSET;


typedef	struct {
	Bool			fSurf;			// 0 -- solid, 1 -- surface.
	WORD			wType;			// See EF_CTYPE_XXX.
	edatDouble			radius1;		// Radius of first circle.
	edatDouble			radius2;		// Radius of second circle.
	DPOINT3			centre1;		// Center of first circle.
	DPOINT3			centre2;		// Center of second circle.
} 	CE_ENT_CONE, *PCE_ENT_CONE,
	__near *NPCE_ENT_CONE, __far *LPCE_ENT_CONE;

typedef	struct {
	int				degreeU;		// Degree in the u direction.
	int				degreeV;		// Degree in the u direction.
	WORD			wFlags;			// EF_SPLSURF_XXX.
	int				nKnotU;			// Knots in u-direction.
	int				nKnotV;			// Knots in v-direction.
	int				nContU;			// Poles in u-dir.
	int				nContV;			// Poles in v-dir.
	LPDOUBLE		lpKnotsU;		// Pointer to knots in u-dir.
	LPDOUBLE		lpKnotsV;		// Pointer to knots in v-dir.
	LPDOUBLE		lpContWts;		// Pointer to wts. (stored by row)
	LPDPOINT3		lpConts;		// Pointer to poles. (stored by row)
} 	CE_ENT_SPLINESURF, *PCE_ENT_SPLINESURF,
	__near *NPCE_ENT_SPLINESURF, __far *LPCE_ENT_SPLINESURF;

typedef	struct {
	WORD			wType;			// See EF_HTYPE_XXX.
	int				nEntity;		// No. of cmplx. entities follow.
	WORD			wReserved[4];	// See note below.		
} 	CE_ENT_CMPLXHDR, *PCE_ENT_CMPLXHDR,
	__near *NPCE_ENT_CMPLXHDR, __far *LPCE_ENT_CMPLXHDR;

/****************************************************
	Note : wReserved[] for CE_ENT_CMPLXHDR.
		For surface and solid header :
			wReserved[0] -- Type of creation.
				(Refer to the Appendix of the Development
				and Support	Guide from MicroStation)
			wReserved[1] -- No. of boundary elms.
****************************************************/

typedef	struct {
	char			dummy;
} 	CE_ENT_RASTERDATA, *PCE_ENT_RASTERDATA,
	__near *NPCE_ENT_RASTERDATA, __far *LPCE_ENT_RASTERDATA;

typedef	struct {
	char			szName[CE_MAX_NAME];
	WORD			wType;			// See EF_CLTYPE_XXX.
	DWORD			dwEndPos;		// Ending position.
} 	CE_ENT_CELLIBHDR, *PCE_ENT_CELLIBHDR,
	__near *NPCE_ENT_CELLIBHDR, __far *LPCE_ENT_CELLIBHDR;

typedef	struct {
	char			dummy;
} 	CE_ENT_NONGRPHC, *PCE_ENT_NONGRPHC,
	__near *NPCE_ENT_NONGRPHC, __far *LPCE_ENT_NONGRPHC;

typedef struct {
	CE_HANDLE		hCE;	// The handle of the file in which the entity situated.
	CE_ENTPOS		dwPos;	// The postion of the entity in the file.
	EntityType		type;
	CE_ENTHDR		ehdr;
	union {
		CE_ENT_POINT		point;
		CE_ENT_LINE			line;
		CE_ENT_ARC			arc;
		CE_ENT_TRACE		trace;
		CE_ENT_SOLID		solid;
		CE_ENT_INSERT		insert;
		CE_ENT_STARTBLOCK	sblock;
		CE_ENT_ENDBLOCK		eblock;
		CE_ENT_ATTDEF		attdef;
		CE_ENT_ATTRIB		attrib;
		CE_ENT_PLINE		pline;
		CE_ENT_VERTEX		vertex;
		CE_ENT_SEQEND		seqend;
		CE_ENT_FACE			face;
		CE_ENT_TEXT			text;
		CE_ENT_SHAPE		shape;
		CE_ENT_DIMENSION	dimension;
		CE_ENT_VIEWPORT		viewport;
		CE_ENT_ELLIPSE		ellipse;
		CE_ENT_MTEXT		mtext;
		CE_ENT_RAY			ray;
		CE_ENT_XLINE		xline;
		CE_ENT_SPLINE		spline;
		CE_ENT_ACIS			solid3d;
		CE_ENT_ACIS			body;
		CE_ENT_ACIS			region;
		CE_ENT_MLINE		mline;
		CE_ENT_TOLERANCE	tolerance;
		CE_ENT_LEADER		leader;
		CE_ENT_OLEFRAME		oleframe;
		CE_ENT_LWPOLYLINE	lwpolyline;
		CE_ENT_IMAGE		image;
		CE_ENT_HATCH		hatch;
		// Entities for MicroStation only.
		CE_ENT_CMPLXHDR		cmplxhdr;
		CE_ENT_VERTICES		vertices;
		CE_ENT_ATTDEFSET	attdefset;
		CE_ENT_CONE			cone;
		CE_ENT_SPLINESURF	splinesurf;
		CE_ENT_RASTERDATA	rasterdata;
		CE_ENT_CELLIBHDR	cellibhdr;
		CE_ENT_NONGRPHC		gde;	// Group data element.
		CE_ENT_NONGRPHC		mse;	// MicroStation element.
		char			filler[1024];
	} u;
}	CE_ENTITY, *PCE_ENTITY,
	__near *NPCE_ENTITY, __far *LPCE_ENTITY;

// Entity filtering
typedef	Bool (PCALLBACK *CE_FilterFunc)(LPCE_ENTHDR);


/*
**  API FUNCTIONS
*/
// Initialisation and Termination of the EDAT library
Public	Bool		PCALLBACK
CE_LoadLibrary(LPCSTR szSerialNumber, LPCSTR szIniFile, DWORD dwReserved);

Public	Bool		PCALLBACK
CE_UnloadLibrary(void);


// General Functions
Public	DWORD		PCALLBACK
CE_Identify(LPCSTR szFilename);

Public	CE_HANDLE	PCALLBACK
CE_Open(LPCSTR szFilename, DWORD dwFlags);

Public	Bool		PCALLBACK
CE_Close(CE_HANDLE hCE);

Public	Bool		PCALLBACK
CE_Update(CE_HANDLE hCE);

Public	Bool		PCALLBACK
CE_GetFilename(CE_HANDLE hCE, LPSTR szFilename);

// Hearder Access Function
Public	Bool		PCALLBACK
CE_GetHeaderVar(CE_HANDLE hCE, LPCSTR szVAR, LPVOID lpVAR);

Public	Bool		PCALLBACK
CE_SetHeaderVar(CE_HANDLE hCE, LPCSTR szVAR, LPVOID lpVAR);

// Table Access Functions
Public	int			PCALLBACK
CE_GetNumTableEntries(CE_HANDLE hCE, TableType tType);

Public	Bool		PCALLBACK
CE_GetTableEntryByIndex(CE_HANDLE hCE, TableType tType,
	int nIndex, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_GetTableEntryByName(CE_HANDLE hCE, TableType tType,
	LPCSTR szName, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_SetTableEntryByIndex(CE_HANDLE hCE, TableType tType,
	int nIndex, CE_TABLEENTRY TEntry);

Public	int			PCALLBACK
CE_NewTableEntry(CE_HANDLE hCE, TableType tType, CE_TABLEENTRY TEntry);

/*
** Table Access Helper Functions provide access to the
** CE_TABLEENTRY structure
*/

// Table Access Helper Fucntions: General
Public	TableType	PCALLBACK
CE_GetTEType(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_GetTEName(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	LPSTR szName);

// Table Access Helper Functions: Layers
Public	Bool		PCALLBACK
CE_GetLayerColor(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView, LPCOLORREF lpRGB, LPINT lpIndex);

Public	Bool		PCALLBACK
CE_GetLayerLinetype(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView, LPINT lpIndex);

Public	Bool		PCALLBACK
CE_IsLayerOn(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView);
	
Public	Bool		PCALLBACK
CE_IsLayerFrozen(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView);

Public	Bool		PCALLBACK
CE_IsLayerLocked(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView);
	
Public	Bool		PCALLBACK
CE_IsLayerFrozenNew(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_IsLayerVisible(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry,
	int nView);
	
// Table Access Helper Functions: Blocks
Public	Bool		PCALLBACK
CE_IsBlockPrivate(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_IsBlockExternal(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_IsBlockDependent(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_IsBlockXDependent(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_IsBlockUsed(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

Public	Bool		PCALLBACK
CE_HasBlockAttributes(CE_HANDLE hCE, LPCE_TABLEENTRY lpTEntry);

// Entities Access Functions
Public	Bool		PCALLBACK
CE_GetFirstEntityPosition(CE_HANDLE hCE, LPCE_ENTPOS lpEntPos);

Public	Bool		PCALLBACK
CE_GetNextEntity(CE_HANDLE hCE, LPCE_ENTITY lpEnt);

Public	Bool		PCALLBACK
CE_GetEntityPosition(CE_HANDLE hCE, LPCE_ENTPOS lpEntPos);

Public	Bool		PCALLBACK
CE_SetEntityPosition(CE_HANDLE hCE, CE_ENTPOS EntPos);

Public	Bool		PCALLBACK
CE_GetEntityByPosition(CE_HANDLE hCE, CE_ENTPOS EntPos, LPCE_ENTITY lpEnt);

Public	Bool		PCALLBACK
CE_GetEntityByHandle(CE_HANDLE hCE, CE_ENTHANDLE hEnt, LPCE_ENTITY lpEnt);

Public	Bool		PCALLBACK
CE_SetEntity(CE_HANDLE hCE, CE_ENTITY Ent);

Public	Bool		PCALLBACK
CE_NewEntity(CE_HANDLE hCE, CE_ENTITY Ent, int nSpace, LPCE_ENTHANDLE lpHandle);

Public	Bool		PCALLBACK
CE_DelEntityByPosition(CE_HANDLE hCE, CE_ENTPOS EntPos);

Public	Bool		PCALLBACK
CE_DelEntityByHandle(CE_HANDLE hCE, CE_ENTHANDLE hEnt);

// Entity Filtering
Public	Bool		PCALLBACK
CE_PushFilter(CE_HANDLE hCE, CE_FilterFunc fnFilter);

Public	Bool		PCALLBACK
CE_PopFilter(CE_HANDLE hCE);

// Extended Data Access
Public	int			PCALLBACK
CE_GetNumExtendedData(CE_HANDLE hCE, LPCE_ENTITY lpEnt);

Public	DWORD		PCALLBACK
CE_GetExtendedDataSize(CE_HANDLE hCE, LPCE_ENTITY lpEnt, int nXData, LPINT lpAppid);

Public	DWORD		PCALLBACK
CE_GetExtendedData(CE_HANDLE hCE, LPCE_ENTITY lpEnt, int nXData, LPINT lpAppid,
		LPBYTE lpData, DWORD dwSize);

Public	Bool		PCALLBACK
CE_SetExtendedData(CE_HANDLE hCE, LPCE_ENTITY lpEnt, int nXData, int Appid,
		LPBYTE lpData, DWORD dwSize);

Public	Bool		PCALLBACK
CE_NewExtendedData(CE_HANDLE hCE, LPCE_ENTITY lpEnt, int Appid, 
		LPBYTE lpData, DWORD dwSize);

// Block Access
Public	Bool		PCALLBACK
CE_FindBlockByIndex(CE_HANDLE hCE, int nBlock);

Public	Bool		PCALLBACK
CE_FindBlockByName(CE_HANDLE hCE, LPCSTR szBlockName);

// Drawing Indexing
Public	Bool		PCALLBACK
CE_IndexDrawing(CE_HANDLE hCE, LPCSTR szIndexFilename);

Public	Bool		PCALLBACK
CE_GetIndexFilename(CE_HANDLE hCE, LPSTR szIndexFilename);

// Sat Files
Public	DWORD		PCALLBACK
CE_ACISOut(CE_HANDLE hCE, CE_ENTHANDLE	hEnt, LPCSTR szSatFilename);

Public	Bool		PCALLBACK
CE_ACISIn(CE_HANDLE hCE, CE_ENTITY Ent, LPCSTR szSatFilename, int nSpace, LPCE_ENTHANDLE lpHandle);

// Attributes Information.
Public	int			PCALLBACK
CE_GetNumAttribsByPosition(CE_HANDLE hCE, CE_ENTPOS EntPos);

Public	int			PCALLBACK
CE_GetNumAttribsByHandle(CE_HANDLE hCE, CE_ENTHANDLE hEnt);

Public	Bool		PCALLBACK
CE_GetAttribByPosition(CE_HANDLE hCE, CE_ENTPOS EntPos, int nIndex, LPCE_ENTITY lpEnt);

Public	Bool		PCALLBACK
CE_GetAttribByHandle(CE_HANDLE hCE, CE_ENTHANDLE hEnt, int nIndex, LPCE_ENTITY lpEnt);

Public	Bool		PCALLBACK
CE_SetAttribByPosition(CE_HANDLE hCE, CE_ENTPOS EntPos, int nIndex, CE_ENTITY Ent);

Public	Bool		PCALLBACK
CE_SetAttribByHandle(CE_HANDLE hCE, CE_ENTHANDLE hEnt, int nIndex, CE_ENTITY Ent);

Public	CE_ENTPOS	PCALLBACK
CE_GetAttribOwnerPosition(CE_HANDLE hCE, LPCE_ENTITY lpEnt);

// Complex Entities.
Public	CE_ENTPOS	PCALLBACK
CE_GetComplexHeaderPosition(CE_HANDLE hCE, LPCE_ENTITY lpEnt);
 
// Preview Image.
Public	HGLOBAL		PCALLBACK
CE_GetPreview(CE_HANDLE hCE, int nType);

// RGB color map.
Public	COLORREF	PCALLBACK
CE_GetColorMap(CE_HANDLE hCE, int nColor);

#ifndef RC_INVOKED
#pragma	pack()
#endif

#ifdef __cplusplus
}
#endif

#endif	/* __EDA_H__ */

