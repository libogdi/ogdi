/*
**		Functions external to the Panoramic library
*/
#ifndef PANX_H
#define PANX_H

/*
**	AD930531: Anyone who writes an import library needs to know the maximum
**	allowable priority level.
*/
#define PAN_MAX_PRIORITY		32000

/*
**	The return values from the reading functions
*/
#define PROCESS_ERROR		0
#define PROCESS_OK			1
#define PROCESS_KBHIT		2
#define PROCESS_DEMOFILE	3
#define PROCESS_DONE		4

/************************************************************************
** Begin raster-specific defines
************************************************************************/

/************************************************************************
** End raster-specific defines
************************************************************************/

/************************************************************************
** Begin vector-specific defines
************************************************************************/
#define PAN_SETHANDLE	0x0001
#define PAN_PUSHBLOCK	0x0002
#define PAN_POPBLOCK	0x0004
/*	Resource Info Structure Data Types */
enum	{
	RI_TEXTFONT,
	RI_TEXTFONT_RSC_FILE,
	RI_LINESTYLE,
	RI_LINESTYLE_RSC_FILE,
	RI_SHAPE,
	RI_SHAPE_RSC_FILE,
	RI_VECTOR_EXTERNAL_REFERENCE,
	RI_RASTER_EXTERNAL_REFERENCE,
	LAST
};

#define	PAN_THICKPOLY_FIXEDWIDTH	0x0001		// Thickness should remain constant when zoom changes.
#define	PAN_THICKPOLY_PIXELWIDTH	0x0002		// Thickness is given in pixels.
#define	PAN_THICKPOLY_CAPROUND		0x0004		// Round cap.
#define	PAN_THICKPOLY_CAPSQUARE		0x0008		// Square cap.
#define	PAN_THICKPOLY_CAPFLAT		0x0010		// Flat cap.
#define	PAN_THICKPOLY_JOINBEVEL		0x0020		// Bevel joints.
#define	PAN_THICKPOLY_JOINMITER		0x0040		// Miter joints.
#define	PAN_THICKPOLY_JOINROUND		0x0080		// Round joints.



// Clip region flags
#define	PAN_CLIPRGN_WINDING		0x80000000L		// Winding Poly region.  Alternate by default.

#define	PAN_CLIPRGN_NONE 		0x00000001L		// Unselect any selected clip rgn.
#define	PAN_CLIPRGN_SET			0x00000002L		// Set given clip region.
	
#define	PAN_CLIPRGN_AND			0x00000004L		// Combine with exiting clip rgn using the given operator.
#define	PAN_CLIPRGN_DIFF		0x00000008L
#define	PAN_CLIPRGN_OR			0x00000010L
#define	PAN_CLIPRGN_XOR			0x00000020L

// Vector font types.
#define	PAN_FONTTYPE_TYPE1			0x00000001L		// Type1 font.

// Vector font flags.
#define	PAN_FONTFLAG_DELETEFILE		0x00000001L		// Delete font file when done using it.
													

/************************************************************************
** End vector-specific defines
************************************************************************/

/************************************************************************
** Begin AB/SS/AR-specific defines
************************************************************************/
typedef struct {
	unsigned char	iAlign; 				// PAN_ALIGN_{LEFT|RIGHT|CENTER}
	unsigned int	iWidth; 				// in characters
	char			szTitle[STRLEN80 + 1];
} PAN_Column;
/*
** Structures used to describe Spreadsheet cell data
*/
#define PAN_SSFLOAT 					1
#define PAN_SSINT						2
#define PAN_SSSTRING					3

/*
**	Format definitions:
**	Don't change the values for the following flags because
**	they have correspondent  flags in the Table code (toolbox.h)
*/
#define PAN_SSFORMAT_FIXED				0
#define PAN_SSFORMAT_SCIENTIFIC 		1
#define PAN_SSFORMAT_CURRENCY			2
#define PAN_SSFORMAT_COMMA				3
#define PAN_SSFORMAT_PERCENT			4
#define PAN_SSFORMAT_SPECIAL			7

#define PAN_SSSPECIAL_PLUSMINUS 		0
#define PAN_SSSPECIAL_GENERAL			1
#define PAN_SSSPECIAL_DDMMMYY			2
#define PAN_SSSPECIAL_DDMMM 			3
#define PAN_SSSPECIAL_MMMYY 			4
#define PAN_SSSPECIAL_TEXT				5
#define PAN_SSSPECIAL_HIDDEN			6
#define PAN_SSSPECIAL_HHMMSS			7
#define PAN_SSSPECIAL_HHMM				8
#define PAN_SSSPECIAL_DATEINT1			9
#define PAN_SSSPECIAL_DATEINT2			10
#define PAN_SSSPECIAL_TIMEINT1			11
#define PAN_SSSPECIAL_TIMEINT2			12
#define PAN_SSSPECIAL_LABEL 			13
#define PAN_SSSPECIAL_AUTOMATIC 		14
#define PAN_SSSPECIAL_DEFAULT			15

#define PAN_SSFRMTFLG_REV				64				// Color cell contents if negative.
#define PAN_SSFRMTFLG_PAREN 		   128				// Put output in parentheses.
#define PAN_SSFRMTFLG_HILITE		   256				// Hilight cell contents.

// Border flags:
#define PAN_SSBORDER_NONE				0
#define PAN_SSBORDER_LEFT				1
#define PAN_SSBORDER_RIGHT				2
#define PAN_SSBORDER_TOP				4
#define PAN_SSBORDER_BOTTOM 			8
#define PAN_SSBORDER_OUTLINE	   		16

// Border styles:
#define PAN_SSBORDERSTYLE_NONE			0
#define PAN_SSBORDERSTYLE_SOLID 		1
#define PAN_SSBORDERSTYLE_DASH			2
#define PAN_SSBORDERSTYLE_DOT			4
#define PAN_SSBORDERSTYLE_DASHDOT		8
#define PAN_SSBORDERSTYLE_DASHDOTDOT	16
#define PAN_SSBORDERSTYLE_BLANK 		32

/*
** Properties:
**	lpPropVal points to BOOL variable:
*/
#define PAN_PROP_OVERFLOW				1		// Allow cell overflow.
#define PAN_PROP_RESIZE 				2		// Allow column/row resize.
#define PAN_PROP_MULTIBLK				3		// Allow multi-block selections.
#define PAN_PROP_GRID					4		// Show grid.
#define PAN_PROP_CHEADERS				5		// Display column headers.
#define PAN_PROP_RHEADERS				6		// Display row headers.

// lpPropVal points to COLORREF
#define PAN_PROP_GCOLOR 				10		// Grid colour.

// lpPropVal points to WORD
#define PAN_PROP_GTYPE					11		// Grid style.

// lpPropVal points to array of two COLORREFS: background, foreground.
#define PAN_PROP_GREY					12		// Grey color.

// lpPropVal points to array of four COLORREFS:
//  shadow, shadow text, shadow dark, shadow light.
#define PAN_PROP_SHADOW 				13		// Shadow color.

// Used only with PANX_GetSSProps.
// need to specified col, row and lpPropVal must be a pointer to a double
#define PAN_SSCOLWIDTH					14
#define PAN_SSROWHEIGHT 				15
#define PAN_SSDEFAULTFONT				16

// Used only with PANX_SetSSProps
// num is either column or row number
typedef struct {
	long	num;
	double	value;
} PAN_RowColAttrib, *PPAN_RowColAttrib, FAR *LPPAN_RowColAttrib;


typedef struct {
	int 	type;

	int		formatFam;
	int		subFormat;
	int 	cCenteredCells;	  //Centered across this # of cells
	int 	formatDigs;
	int 	formatFlgs;
	LPCSTR	formatUStr;

	int 	brdrFlgs;
	int 	brdrStyle;
	COLORREF		brdrColor;
	COLORREF		bkColor;
	COLORREF		fgColor;
} PAN_CellAttrib, *PPAN_CellAttrib, FAR *LPPAN_CellAttrib;

typedef struct {
	int 	type;
	union {
		int 	intVal;
		double	dbleVal;
		LPSTR	strVal;
	} value;
} PAN_CellContents, *PPAN_CellContents, FAR *LPPAN_CellContents;
/************************************************************************
** End DB/SS/AR-specific defines
************************************************************************/

/************************************************************************
** Begin document-specific defines
************************************************************************/
/***********************************************************************
** BEGIN Document Format Constants
************************************************************************/
/* text attributes */
#define PAN_ATTR_NORMAL 			0x00000000
#define PAN_ATTR_BOLD				0x00000001
#define PAN_ATTR_ITALIC 			0x00000002
#define PAN_ATTR_UNDERLINE			0x00000004
#define PAN_ATTR_STRIKEOUT			0x00000008
#define PAN_ATTR_SUBSCRIPT			0x00000010
#define PAN_ATTR_SUPERSCRIPT		0x00000020
#define PAN_ATTR_WORD_UNDERLINE 	0x00000040
#define PAN_ATTR_DOUBLE_UNDERLINE	0x00000080
#define PAN_ATTR_SMALL_CAPS 		0x00000100
#define PAN_ATTR_CAPS				0x00000200
#define PAN_ATTR_OUTLINE			0x00000400
#define PAN_ATTR_SHADOW 			0x00000800
#define PAN_ATTR_ALL_LOWERCASE		0x00001000
#define PAN_ATTR_INITIAL_CAPS		0x00002000
#define PAN_ATTR_DOT_UNDERLINE		0x00004000
#define PAN_ATTR_SERIFS 			0x00008000
#define PAN_ATTR_VARIABLE_PITCH 	0x00010000
#define	PAN_ATTR_NOADJUSTAVGWIDTH	0x00020000		// Do not adjust font avg width to
													// equal height.		
#define PAN_ATTR_CHARHEIGHT		 	0x00040000		// Indicates that the height passed is
													// the character height and not the cell height.

#define PAN_ATTR_UNDERLINES 	(PAN_ATTR_UNDERLINE | \
								PAN_ATTR_WORD_UNDERLINE | \
								PAN_ATTR_DOUBLE_UNDERLINE | \
								PAN_ATTR_DOT_UNDERLINE)
/* tab stop types */
#define PAN_TAB_LDR_NO_LEADER		0
#define PAN_TAB_LDR_DOTTED			1
#define PAN_TAB_LDR_HYPHENATED		2
#define PAN_TAB_LDR_UNDERLINE		3
#define PAN_TAB_LDR_THICK_LINE		4
#define PAN_TAB_LDR_EQUAL_SIGN		5

#define PAN_TAB_LEFT				1
#define PAN_TAB_RIGHT				2
#define PAN_TAB_CENTER				3
#define PAN_TAB_DECIMAL 			4
#define PAN_TAB_BAR 				5

/* Table alignment values */

#define PAN_TBL_ALIGN_LEFT			0
#define PAN_TBL_ALIGN_RIGHT 		1
#define PAN_TBL_ALIGN_CENTER		2

/* Section break codes */

#define PAN_BRK_NONE				0
#define PAN_BRK_NEW_COLUMN			1
#define PAN_BRK_NEW_PAGE			2
#define PAN_BRK_EVEN_PAGE			3
#define PAN_BRK_ODD_PAGE			4

/* Constants used to describe border */
#define PAN_BRD_NO_BORDER		0
#define PAN_BRD_SINGLE_LINE 	1
#define PAN_BRD_THICK_LINE		2	// Cannot be defined as SINGLE + big width
#define PAN_BRD_DOUBLE_LINE 	3
#define PAN_BRD_DASH_LINE		4
#define PAN_BRD_DOTTED_LINE 	5
#define PAN_BRD_DASHDOT_LINE	6
#define PAN_BRD_HAIR_LINE		7	// Cannot be defined as SINGLE + zero width


/* APO constants */
#define PAN_RELPOS_HORZ_COLUMN	0
#define PAN_RELPOS_HORZ_MARGIN	1
#define PAN_RELPOS_HORZ_PAGE	2
#define PAN_RELPOS_VERT_MARGIN	0
#define PAN_RELPOS_VERT_PAGE	1
#define PAN_RELPOS_VERT_PARA	2

#define PAN_POS_CURRENT 		 -1
#define PAN_POSX_LEFT			  0
#define PAN_POSX_CENTER 		 -4
#define PAN_POSX_RIGHT			 -8
#define PAN_POSX_INSIDE 		-12
#define PAN_POSX_OUTSIDE		-16
#define PAN_POSY_UNCONSTRAINED	0
#define PAN_POSY_TOP			-4
#define PAN_POSY_CENTER 		-8
#define PAN_POSY_BOTTOM 		-12

#define PAN_WR_NOWRAP			1
#define PAN_WR_AROUND			2
#define PAN_WR_SIDEBYSIDE		3
#define PAN_WR_OVERLAP			4
#define	PAN_WR_LEFT				5
#define	PAN_WR_RIGHT			6
#define	PAN_WR_EITHER			7
#define	PAN_WR_WIDER			8

// Table breaking flags.
#define	PAN_TABLEBREAK_NONE			0
#define	PAN_TABLEBREAK_SPLIT		1
#define PAN_TABLEBREAK_EXPANDROW	2

#define PAN_TR_TRANSPARENT		0
#define PAN_TR_OPAQUE			1
#define PAN_TR_UNDERLIE 		2

/* Cell contents flags */
#define PAN_TBL_CELL_TEXT		0
#define PAN_TBL_CELL_IMAGE		1

/* Shading patterns */
#define PAN_PAT_NUMERICAL		 0
#define PAN_PAT_HORIZ			 1
#define PAN_PAT_VERT			 2
#define PAN_PAT_FDIAG			 3
#define PAN_PAT_BDIAG			 4
#define PAN_PAT_CROSS			 5
#define PAN_PAT_DCROSS			 6
#define PAN_PAT_DKHORIZ 		 7
#define PAN_PAT_DKVERT			 8
#define PAN_PAT_DKFDIAG 		 9
#define PAN_PAT_DKBDIAG 		10
#define PAN_PAT_DKCROSS 		11
#define PAN_PAT_DKDCROSS		12

/* embedded text codes */
#define	PAN_CHAR_FLUSH_RIGHT		0x03
#define PAN_CHAR_BACK_TAB			0x08
#define PAN_CHAR_TAB				0x09
#define PAN_CHAR_END_OF_PAR 		0x0A
#define PAN_CHAR_FORCED_LINE_BREAK	0x0B
#define PAN_CHAR_END_OF_PAGE		0x0C
#define PAN_CHAR_COLUMN_BREAK		0x0E
#define PAN_CHAR_SECTION_MARK		0x0F
#define PAN_CHAR_HYPHEN_USER		0x1E
#define PAN_CHAR_HYPHEN_KEYBOARD	0x1F

/* special characters */
#define	PAN_SCHAR_SOFT_COLUMN_BREAK	0x01
#define	PAN_SCHAR_SOFT_PAGE_BREAK	0x02
#define	PAN_SCHAR_SECTION_BREAK		0x03
#define	PAN_SCHAR_PAGE_ESC			0x04

/* paragraph alignment */
#define PAN_ALIGN_LEFT			0
#define PAN_ALIGN_RIGHT 		1
#define PAN_ALIGN_CENTER		2
#define PAN_ALIGN_JUSTIFY		3

// RR: 10/14/94 (used with spreadsheet cells)
#define PAN_ALIGN_TOP					8
#define PAN_ALIGN_BOTTOM				4
#define PAN_ALIGN_VCENTER				16
#define PAN_ALIGN_WRAP					32	// wrap cell contents

/* misc... */
#define PAN_ABS_SPACING_BIT 			0x8000	// At least line spacing in twips.	
#define PAN_EXACT_SPACING_BIT			0x4000	// Exactly line spacing in twips.

/* Predefined border length types */
#define PAN_BL_MARGINS			1
#define PAN_BL_TEXT 			2
#define PAN_BL_CUSTOM			3

/* Shadow existence and/or direction */
#define PAN_SHADOW_NONE 		 0
#define PAN_SHADOW_ALL			 1
#define PAN_SHADOW_LEFT 		 2
#define PAN_SHADOW_ABOVE		 3
#define PAN_SHADOW_RIGHT		 4
#define PAN_SHADOW_BELOW		 5
#define PAN_SHADOW_LA			 6
#define PAN_SHADOW_LR			 7
#define PAN_SHADOW_LB			 8
#define PAN_SHADOW_AR			 9
#define PAN_SHADOW_AB			10
#define PAN_SHADOW_RB			11
#define PAN_SHADOW_LAR			12
#define PAN_SHADOW_LAB			13
#define PAN_SHADOW_LRB			14
#define PAN_SHADOW_ARB			15

/* The start page to which the header and footer will be applied */
#define	PAN_FIRST_PAGE			-1
#define	PAN_CURRENT_PAGE		0
#define	PAN_NEXT_PAGE			-2


/***********************************************************************
** END Document Format Constants
************************************************************************/

/*
**  A tab-position definition
*/
typedef struct {
	BYTE	bTabType;
	WORD	wTabPos;
} PAN_TAB, FAR *LPPAN_TAB;

/*
** Text element information
*/
typedef struct {
	POINT		Page;	// page size
	POINT		Off;	// page offsets
	RECT		Marg;	// page margins
} TxSize;

/*
** General shading structure
*/
typedef struct {
	int		iPercentage;	// In hundredths of a percent !
	int		iPattern;
	DWORD	rgbForeColor;
	DWORD	rgbBackColor;
} PAN_Shading, FAR *LPPAN_Shading;

/* Universal structure for a border segment around text units */
typedef struct tagBORDER {
	BYTE	brdStyle;		// No border, single-line, double-line, thick, dotted ...
	int 	brdLineWidth;	// Width of a single line of the border.
	int 	dxpSpace;		// Width of space to maintain between border and text within border.
							//		(Must be 0 when used to describe table cell border.)
	int 	brdType;		// One of predefined types of border length
	int 	brdLength;		// Length of border line if brdType = PAN_BL_CUSTOM
	DWORD	rgbColor;		// Border color
} PAN_Border, FAR * LPPAN_Border;

/* A structure for lines and shadows around text units */
typedef struct	{
	PAN_Border	leftBord;	// Border to be used to the left of an object
	PAN_Border	topBord;	// Border to be used above an object
	PAN_Border	rightBord;	// Border to be used to the right of an object
	PAN_Border	bottomBord; // Border to be used below an object
	PAN_Shading intShade;	// Shading to be used in the interior of borders
	int 		iRadius;	// Curvature of border corners in percent
							// 0% - square corners, 100% - all-curved frame
	int 		shadDir;	// Existence and/or direction of a shadow for the border
	int 		shadDepth;	// Depth of border shadow in TWIPS. If 0, no shadow.
	DWORD		rgbShadColor;// Color to be used to paint border shadow
} PAN_Edge, FAR * LPPAN_Edge;

/*
** Absolutely-positioned object
*/
typedef struct	{
	int 	iPage;			// Page no. or 0 if unknown
	BYTE	pcHorz; 		// 0 - relative to column, 1 - margin, 2 - page
	BYTE	pcVert; 		// 0 - relative to margin, 1 - page, 2 - to text (where non_APO
							//				 would have been placed)
	int 	dxaAbs; 		// Positive - horiz. dist. from reference frame,
							//				 0 - positioned at the left,
							//				-4 - centered horizontally,
							//				-8 - adjusted right,
							// -12 - placed immediately inside RF,
							// -16	- placed immediately outside of RF
	int 	dyaAbs; 		// Positive - vert. dist. from reference frame,
							//				 0 - y-position is unconstrained,
							//				-4 - on top of RF,
							//				-8 - centered vertically,
							// -12 - at bottom of RF,
	int 	dxaFromText;	// Horiz.dist. between APP and any non-AP text
	int 	dyaFromText;	// Vertical.dist. between APP and any non-AP text
	int 	dxaWidth;		// When !=0, margin & column settings have no effect
	int		wHeightAbs; 	// Sign bit = 0 -> exact, 1 -> at least
	BYTE	Wrap;			// Wrap code
	BYTE	Transparency;	// Transparency code
	PAN_Edge	bordFrame;	// Borders and shadows associated with an APO
} PAN_APO, FAR *LPPAN_APO;


////////////////////////////////////////////////////////////////////////////////////
//	Some type definitions for the drawing objects
////////////////////////////////////////////////////////////////////////////////////

/* Constants to describe a linestyle */
#define	PAN_LINESTYLE_SOLID			0
#define	PAN_LINESTYLE_DASHED		1
#define	PAN_LINESTYLE_DOTTED		2
#define	PAN_LINESTYLE_DASHDOT		3
#define	PAN_LINESTYLE_DASHDOTDOT	4
#define	PAN_LINESTYLE_HOLLOW		5

// Drawing object types.
typedef enum {
	PAN_DO_LINE = 1,
	PAN_DO_RECTANGLE,
	PAN_DO_ARC,
	PAN_DO_ELLIPSE,
	PAN_DO_POLYLINE,
	PAN_DO_TEXTBOX
} PAN_DrawingObjType ;

typedef struct {
	POINT		start;
	POINT		end;
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow
	WORD		eppStart;	// Start endpoint properties.
	WORD		eppEnd;		// End endpoint properties.
							// (& 0x0003) : 0 - none; 1 - hollow; 2 - filled
							// (& 0x000c) : weight
							// (& 0x0030) : length		
}	PAN_LINE, FAR *LPPAN_LINE;

typedef struct {
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow
	BYTE		fLeft;		// True when endpoint is to the left of the start point.
	BYTE		fUp;		// True when endpoint is above the start point.
}	PAN_ARC, FAR *LPPAN_ARC;

typedef struct {
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow
}	PAN_ELLIPSE, FAR *LPPAN_ELLIPSE;

typedef struct {
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow
}	PAN_RECTANGLE, FAR *LPPAN_RECTANGLE;

typedef struct {
	int			nPts;	
	POINT FAR	*lpPoints;
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow
	WORD		eppStart;	// Start endpoint properties.
	WORD		eppEnd;		// End endpoint properties.
							// (& 0x0003) : 0 - none; 1 - hollow; 2 - filled
							// (& 0x000c) : weight
							// (& 0x0030) : length		
}	PAN_POLYLINE, FAR *LPPAN_POLYLINE;

typedef struct {
	COLORREF	color;
	int			weight;
	int			style;		// 0 - solid; 1 - dashed; 2 - dotted; 3 - dash dot;
							// 4 - dash dot dot; 5 - hollow

	BOOL		fOpen;		// TRUE to open text box for input, FALSE to close it.
}	PAN_TEXTBOX, FAR *LPPAN_TEXTBOX;

/*
** Drawing Objects
*/
typedef struct	{
	int 	iPage;			// Page no. or 0 if unknown
	BYTE	pcHorz; 		// 0 - relative to column, 1 - margin, 2 - page
	BYTE	pcVert; 		// 0 - relative to margin, 1 - page, 2 - to text (where non_APO
							//				 would have been placed)
	int 	dxaAbs; 		// Positive - horiz. dist. from reference frame,
							//				 0 - positioned at the left,
							//				-4 - centered horizontally,
							//				-8 - adjusted right,
							// -12 - placed immediately inside RF,
							// -16	- placed immediately outside of RF
	int 	dyaAbs; 		// Positive - vert. dist. from reference frame,
							//				 0 - y-position is unconstrained,
							//				-4 - on top of RF,
							//				-8 - centered vertically,
							// -12 - at bottom of RF,
	int 	dxaWidth;
	int		dyaHeight;
	int		dzaHeight;		// z-order or height (0x1000 to 0x3000)
							// Value less than 0x2000 means transparent.

	PAN_Shading	shading;

	PAN_DrawingObjType	type;

	union {
		PAN_LINE		line;
		PAN_RECTANGLE	rectangle;
		PAN_ARC			arc;
		PAN_ELLIPSE		ellipse;
		PAN_POLYLINE	polyline;
		PAN_TEXTBOX		textbox;
	} u;	
} PAN_DrawingObj, FAR *LPPAN_DrawingObj;

////////////////////////////////////////////////////////////////////////////////////
// End of the type definitions for the drawing objects
////////////////////////////////////////////////////////////////////////////////////

/*
** Element type
*/
typedef enum {
	PAN_DOC_ETYPE_TEXT = 1,
	PAN_DOC_ETYPE_FRAME,
	PAN_DOC_ETYPE_TABLE,
	PAN_DOC_ETYPE_GRAPHIC,
	PAN_DOC_ETYPE_UNKNOWN
} PAN_DocElemType ;

/*
** Flow identifier
*/
typedef enum {
	PAN_DOC_FLOW_MAIN		= 1,
	PAN_DOC_FLOW_HEADALL ,
	PAN_DOC_FLOW_HEADEVEN,
	PAN_DOC_FLOW_HEADODD,
	PAN_DOC_FLOW_HEADFIRST,
	PAN_DOC_FLOW_FOOTALL,
	PAN_DOC_FLOW_FOOTEVEN,
	PAN_DOC_FLOW_FOOTODD,
	PAN_DOC_FLOW_FOOTFIRST,
	PAN_DOC_FLOW_PAGENUM,
	PAN_DOC_FLOW_USER		= 128
} FlowID;

/*
** Specific area on a page template
*/
typedef struct {
	PANRECT 		prBoundary;
	PAN_DocElemType	type;
	FlowID			flowId;
	WORD			wWrap;
	WORD			wRelHorzPos;
	WORD			wRelVertPos;
} PAN_Element, *PPAN_Element, FAR *LPPAN_Element;

/*
** Line items in documents
*/
typedef struct {
	PAN_Point		from;
	PAN_Point		to;
	PAN_Border FAR	*lpRuleStyle;
} PAN_Rule, *PPAN_Rule, FAR *LPPAN_Rule;

/*
** Structure used to describe Overlay/OLE objects
*/
#define SPECIAL_OBJECT			-2
#define OVERLAY_OBJECT			-1
#define OLE_OBJECT_STATIC		 0
#define OLE_OBJECT_LINKED		 1
#define OLE_OBJECT_EMBEDDED 	 2

#define OBJECTFLAG_EXTRACT			0x0001
#define OBJECTFLAG_DELETE			0x0002
#define OBJECTFLAG_TRANSPARENT		0x0004
#define OBJECTFLAG_INSERTIONPOINT	0x0008
#define OBJECTFLAG_NOVIEWPORTS		0x0010

typedef struct {
	char	ObjectID[16];
	int 	ObjectType;
	char	filename[PAN_MAX_PATH];
	WORD	flags;			// special flags

	LPSTR	lpszHeader; 	// pointer to file prefix
	LONG	cbHeader;		// size of the file prefix

	LONG	zOrder; 		// NOT used!!!

	LONG	ObjectOffset;	// starting of data in the file
	LONG	ObjectSize; 	// size of data to extract

	PANRECT source; 		// for images: current view extents.
	PAN_Border _far		*borders;
	PAN_Shading _far	*shading;
	WORD				wRotate;
	WORD				wFlip;
} PAN_OBJECT, *PPAN_OBJECT, FAR *LPPAN_OBJECT;

/*
** Document Table.
*/
typedef struct tagTABLE {
	int 	nRows;			// number of rows, or 0 if not known
	WORD	wBreakMode;		// How to break table if it intersects another
							// rigid element.
} PAN_Table, FAR *LPPAN_Table;

/*
** Document Table Row.
*/
typedef struct tagROW {
	LONG	idRow;			// identifies row for the core to reference in future
	int 	xTable; 		// set to -1 to use default
	int 	yTable; 		// set to -1 to use default
	int 	yaHeight;		// row height at least, exactly, or variable
	BYTE	jc; 			// justification of a row within page column
	int 	nCells; 		// number of cells, or 0 if not known
} PAN_Row, FAR *LPPAN_Row;

/*
** Document Table Cell.
*/
typedef struct tagCELL {
	LONG	idCell; 		// Identifies cell for the core to reference in future
	BOOL	fNewCall;		// True by default
	int 	fType;			// type of data which cell contains
	int 	xRow;			// set to -1 to use default
	int 	yRow;			// set to -1 to use default
	int 	xaWidth;		// cell width must be non-zero
	int		yaHeight;		// Default height if cell is empty.
	int 	dxaMarginLeft;	// space between left border & data
	int 	dyaMarginTop;	// space between top border & data
	int 	dxaMarginRight; // space between right border & data
	int 	dyaMarginBottom;// space between bottom border & data
	BOOL	fFirstMerged;	// False by default
	BOOL	fMerged;		// False by default
	BOOL	fVertFirstMerged;// False by default
	BOOL	fVertMerged;	// False by default
	PAN_Edge	bordCell;	// Cell borders and shading
} PAN_Cell, FAR *LPPAN_Cell;
/************************************************************************
** End document-specific defines
************************************************************************/


/************************************************************************
** BEGIN Drawing Hints for PAN_QueryFile()
*************************************************************************/
#define PAN_NoHints 			0x0000

#define PAN_RasterInterlaced	0x0001
#define PAN_RasterBottomUp		0x0002
#define PAN_RasterRuns			0x0004

#define PAN_VectorSupportsEdat	0x0001
#define PAN_VectorWindowsMeta	0x0002
#define PAN_VectorHasPens		0x0010
#define PAN_VectorYOrgBottom	0x0020
#define PAN_VectorXOrgRight 	0x0040
#define PAN_VectorTrueColor 	0x0080
#define PAN_VectorRGBColors 	0x0100
#define PAN_VectorFrozenLayers 	0x0200

#define PAN_ArchiveByRow		0x0001
#define PAN_ArchiveByCol		0x0002
#define PAN_ArchiveByBlock		0x0004

#define PAN_DatabaseByRow		0x0001
#define PAN_DatabaseByCol		0x0002
#define PAN_DatabaseByBlock		0x0004

#define PAN_SpreadsheetByRow	0x0001
#define PAN_SpreadsheetByCol	0x0002
#define PAN_SpreadsheetByBlock	0x0004

#define PAN_MultiPage			0x1000
#define PAN_HighResolution		0x2000

#define	PAN_FLIPNONE			0x0000
#define	PAN_FLIPX				0x0001
#define	PAN_FLIPY				0x0002
#define	PAN_FLIPXY				0x0003

/************************************************************************
** END Drawing Hints for PAN_QueryFile()
*************************************************************************/


/*
**	Callback interface as defined in "DESIGN DOCUMENT Version 0.1".
**	When new callbacks need to be added, they should replace
**  the DUMMY placeholders.
*/
typedef struct panx {

	/* Common Functions */
	Bool	(CALLBACK *PANX_NOP)(LONG);
	Bool	(CALLBACK *PANX_SetFileType)(LONG, PAN_FileType, DWORD);
	Bool	(CALLBACK *PANX_SetSubFileType)(LONG, DWORD);
	Bool	(CALLBACK *PANX_SetColAttr)(LONG, PAN_Column _far *, unsigned int);
	Bool	(CALLBACK *PANX_SetColormap)(LONG, WORD, WORD, WORD, BYTE _far *, BYTE _far *, BYTE _far *);
	Bool	(CALLBACK *PANX_GetRange)(LONG, PAN_FileType, LONG _far *, LONG _far *, LONG _far *, LONG _far *);
	Bool	(CALLBACK *PANX_SetExtentsLong)(LONG, LONG, LONG, LONG, LONG);
	Bool	(CALLBACK *PANX_SetExtentsReal)(LONG, edatReal, edatReal, edatReal, edatReal, edatReal, edatReal);
	Bool	(CALLBACK *PANX_GetExtents)(LONG, LPPOINT, LPPOINT, PAN_Point _far *, PAN_Point _far *);
	Bool	(CALLBACK *PANX_SetNumPages)(LONG, int);
	Bool	(CALLBACK *PANX_DUMMY_X02) (void);
	Bool	(CALLBACK *PANX_DUMMY_X03) (void);
	Bool	(CALLBACK *PANX_DUMMY_X04) (void);
	Bool	(CALLBACK *PANX_DUMMY_X05) (void);

	/* Raster Functions */
	Bool	(CALLBACK *PANX_Bitmap)(LONG, LONG, LONG, LONG, BYTE _far *, LONG);
	Bool	(CALLBACK *PANX_DUMMY_RS1) (void);
	Bool	(CALLBACK *PANX_DUMMY_RS2) (void);
	Bool	(CALLBACK *PANX_DUMMY_RS3) (void);
	Bool	(CALLBACK *PANX_DUMMY_RS4) (void);
	Bool	(CALLBACK *PANX_DUMMY_RS5) (void);

	/* Vector Functions */
	Bool	(CALLBACK *PANX_Line)(LONG, PAN_Point _far *, PAN_Point _far *, LONG);
	Bool	(CALLBACK *PANX_Rect)(LONG, PAN_Point _far *, PAN_Point _far *, Bool, LONG, LONG);
	Bool	(CALLBACK *PANX_Poly)(LONG, PAN_Point _far *, int, LONG, LONG);
	Bool	(CALLBACK *PANX_Arc)(LONG, PAN_Point _far *, edatReal, edatReal, edatReal, LONG, LONG);
	Bool	(CALLBACK *PANX_3PtArc)(LONG, PAN_Point _far *, PAN_Point _far *, PAN_Point _far *, LONG, LONG);
	Bool	(CALLBACK *PANX_EllipticArc)(LONG, PAN_Point _far *, edatReal, edatReal, edatReal, edatReal, LONG, LONG, Bool);
	Bool	(CALLBACK *PANX_Ellipse)(LONG, PAN_Point _far *, edatReal, edatReal, LONG, LONG, Bool);
	Bool	(CALLBACK *PANX_VText)(LONG, struct panx _far *, PAN_Point _far *, LPCSTR, edatReal, edatReal, edatReal, edatReal, void _far *,int, LONG);
	Bool	(CALLBACK *PANX_MonoBitmap)(LONG, BYTE _far *, edatReal, edatReal, int, int, int, LONG, LONG, int);
	Bool	(CALLBACK *PANX_TText)(LONG, LPCSTR, PAN_Point _far *, PAN_Point _far *, LPSTR, edatReal, edatReal, edatReal, edatReal, WORD, LONG, LONG, BOOL, BOOL);
	Bool	(CALLBACK *PANX_TTextSize)(LONG, LPCSTR, LPCSTR, edatReal, edatReal, LONG, edatReal _far *, edatReal _far *);
	Bool	(CALLBACK *PANX_SetMetafileBBox)(LONG, LPRECT);
	Bool	(CALLBACK *PANX_SetMetafileObjects)(LONG, UINT);
	Bool	(CALLBACK *PANX_PlayMetafileRecord)(LONG, METARECORD _far *);

	Bool	(CALLBACK *PANX_SetHandle) (LONG, WORD, LPPANHANDLE);
#if CSIVER >= 10200
	Bool	(CALLBACK *PANX_ThickPoly) (LONG, PAN_Point _far *, int, edatReal, edatReal, PAN_TVertex _far *, WORD, LONG, LONG);
#else
	Bool	(CALLBACK *PANX_DUMMY_VC1) (void);
#endif

	Bool	(CALLBACK *PANX_SetClipRegion) (LONG ID, PAN_Point _far *pPoints, int PolyCnt, LPINT pPtCnt, DWORD Flags);
	Bool	(CALLBACK *PANX_SetVFont) (LONG ID, LPPAN_FONT pFont);
	Bool	(CALLBACK *PANX_PText) (LONG ID, PAN_Point _far *pPoint, LPCSTR szText, DWORD dwAlign, edatReal CharSpacing, edatReal WordSpacing, LPHmatrix pMatrix, LONG COLOR, PAN_Point _far *lpEndPt);

	/* XRef callbacks */
	Bool	(CALLBACK *PANX_SetXRefs)(LONG, WORD, LPPAN_XREF);
	Bool	(CALLBACK *PANX_GetXRefs)(LONG, WORD, LPPAN_XREF);

	Bool	(CALLBACK *PANX_ResourceInfo) (LONG ID, UINT resourceType, LPCSTR szResourceID, UINT cbResourceID, LPSTR szResource, UINT cbResource, BOOL fOK);

	/* Document Functions */
	Bool	(CALLBACK *PANX_Text)(LONG ID, LPSTR lpStr);
	Bool	(CALLBACK *PANX_SetFont)(LONG ID, LPLOGFONT lpFont);
	Bool	(CALLBACK *PANX_SetAlignment)(LONG ID, WORD wAlign);
	Bool	(CALLBACK *PANX_SetIndents)(LONG ID, int iLeft, int iRight, int iFirstLine);
	Bool	(CALLBACK *PANX_SetTabs)(LONG ID, LPPAN_TAB lpTabList, int nTabs);
	Bool	(CALLBACK *PANX_SetAttribute)(LONG ID, DWORD dwAttr, DWORD dwColor, int iBlAlign);
	Bool	(CALLBACK *PANX_SetSpacing)(LONG ID, WORD wLine, WORD wParAbove, WORD wParBelow);
	Bool	(CALLBACK *PANX_SetMargins)(LONG ID, WORD wLeft, WORD wTop, WORD wRight, WORD wBottom);
	Bool	(CALLBACK *PANX_SetTable) (LONG ID, PAN_Table far *lpTable);
	Bool	(CALLBACK *PANX_SetTableRow) (LONG ID, PAN_Row far *lpRow);
	Bool	(CALLBACK *PANX_SetTableCell) (LONG ID, PAN_Cell far *lpCell);
	Bool	(CALLBACK *PANX_SetImage)(LONG ID, LPCSTR lpPictureFileName, DWORD fcImage, DWORD cbImage,
				POINT ptCurrDimensions, POINT ptTargetDimensions,
				LPPAN_Edge lpEdge, RECT rcCrop, POINT ptScale, LPSTR lpExt,
				void far * lpStruct);
	Bool	(CALLBACK *PANX_SetColumns)(LONG ID, BYTE bkc, WORD ccolM1, WORD dxaColumns, LPPAN_Border lpBorder);
	Bool	(CALLBACK *PANX_SetParagraphBorder)(LONG ID, LPPAN_Edge lpEdge,
				 LPPAN_Border lpbrdBetween, LPPAN_Border lpbrdBar);
	LONG	(CALLBACK *PANX_DefineAPO) (LONG ID, LPPAN_APO lpAPO);
	Bool	(CALLBACK *PANX_DefineDocument) (LONG ID, int nParam, LPSTR FAR *rgTxtPrm);
	Bool	(CALLBACK *PANX_DefineParagraph) (LONG ID, int nParam, LPSTR FAR *rgTxtPrm);
	Bool	(CALLBACK *PANX_DefineSection) (LONG ID, int nParam, LPSTR FAR *rgTxtPrm);
	Bool	(CALLBACK *PANX_AddElement) (LONG ID, int nPage, PAN_Element FAR *lpNewElement);
	Bool	(CALLBACK *PANX_InitLayout) (LONG ID, int nPage, int xSize, int ySize);
	Bool	(CALLBACK *PANX_SetTextFlow) (LONG ID, int nPage, FlowID newFlow);
	Bool	(CALLBACK *PANX_SetPageLayout) (LONG ID, int nPage, int nLayoutPage);
	Bool	(CALLBACK *PANX_SetRule) (LONG ID, int nPage, PAN_Rule FAR *lpNewRule);

	/* Database Functions */
	Bool	(CALLBACK *PANX_DBaseRecord)(LONG, BYTE _far *, int);
	Bool	(CALLBACK *PANX_DUMMY_DB1) (void);
	Bool	(CALLBACK *PANX_DUMMY_DB2) (void);

	/* Cont' of Document Fucntions */
	Bool	(CALLBACK *PANX_SetColumns1)(LONG ID, BYTE bkc, WORD ccolM1, WORD dxaColumns,
			 LPWORD lpColWidths, LPWORD lpColSpaces, LPPAN_Border lpBorder);
	Bool	(CALLBACK *PANX_SpecialCharacters) (LONG ID, LPSTR lpStr);
	Bool	(CALLBACK *PANX_DrawingObject) (LONG ID, LPPAN_DrawingObj lpDrawObj);

	/* Spreadsheet Functions */
	Bool	(CALLBACK *PANX_SpreadsheetRow)(LONG, BYTE _far *, int);
	Bool	(CALLBACK *PANX_SetCell)(LONG, LONG, LONG, LONG, PAN_CellAttrib FAR*);
	Bool	(CALLBACK *PANX_SetCellContents)(LONG, LONG, LONG, LONG, PAN_CellContents FAR*);
	Bool	(CALLBACK *PANX_SetSSProps)(LONG, LONG, WORD, void FAR*);
	Bool	(CALLBACK *PANX_SetFlow)(LONG, LONG);
	Bool	(CALLBACK *PANX_GetSSProps)(LONG, LONG /* sheet*/, LONG /*col*/, LONG /*row*/, WORD, void FAR*);

	/* Archive */
	Bool	(CALLBACK *PANX_ArchiveFile)(LONG, LPSTR, LPSTR, edatReal, BOOL);
	Bool	(CALLBACK *PANX_SetExtractFunc)(LONG, LONG);
	Bool	(CALLBACK *PANX_DUMMY_AR2) (void);
	Bool	(CALLBACK *PANX_DUMMY_AR3) (void);
	Bool	(CALLBACK *PANX_DUMMY_AR4) (void);
	Bool	(CALLBACK *PANX_DUMMY_AR5) (void);

	/* Layer callbacks */
	Bool	(CALLBACK *PANX_SetLayers)(LONG, WORD, LPPAN_LAYER);
	Bool	(CALLBACK *PANX_GetLayers)(LONG, WORD, LPPAN_LAYER);

	/* Block callbacks */
	Bool	(CALLBACK *PANX_SetBlocks)(LONG, WORD, LPPAN_BLOCK);
	Bool	(CALLBACK *PANX_GetBlock)(LONG,  LPLONG);

	/* View callbacks */
	Bool	(CALLBACK *PANX_SetViews)(LONG, WORD, LPPAN_VIEW);
	Bool	(CALLBACK *PANX_GetView)(LONG,	LPLONG, LPHmatrix);

	/* Option flags */
	int 	(CALLBACK *PANX_GetOptionString)(LONG, LPCSTR /*Section*/, LPSTR /*optionname*/, LPCSTR /*defaultvalue*/,int /* Max Char to be read */, LPSTR /*result*/, LPCSTR /* Ini FileName or Null */);
	int 	(CALLBACK *PANX_GetOptionInt)(LONG, LPCSTR /*Section*/, LPSTR /*optionname*/, int /*defaultvalue*/,LPCSTR /*Ini File Name or Null */);

	/* Support for Overlayed files / OLE objects  */
	Bool	(CALLBACK *PANX_SetInsertionPoint)(LONG, PAN_Point _far * /*offset*/, PAN_Point _far * /*scale*/, PAN_Point _far * /*dpi*/, edatReal /*rotation rad*/, WORD /*flip*/, LONG /*rgbcolour*/);
#if CSIVER >= 10200
	Bool	(CALLBACK *PANX_OverlayImage)(LONG, PANRECT /*placement*/, PAN_OBJECT _far * /*olSpec*/);
#else
	Bool	(CALLBACK *PANX_OverlayFile)(LONG, struct panx _far * /*cbs*/, DWORD dwObjectID, LPSTR /*filename*/, PAN_Point _far * /*point1*/, PAN_Point _far * /*point2*/);
#endif
	Bool	(CALLBACK *PANX_OleObject)(LONG, LPCSTR /*ObjectNum*/, int /*ObjType*/, PANRECT /*Placement*/, LONG /*ObjOffset*/, LONG /*cbObj*/);
	Bool	(CALLBACK *PANX_DUMMY_92) (void);
	Bool	(CALLBACK *PANX_DUMMY_93) (void);

	/* Support for tiled tiff images */
	Bool	(CALLBACK *PANX_SetTileSize)(LONG, LONG, LONG);

	/* Support for setting bookmarks */
	int		(CALLBACK *PANX_SetBookMarks)(LONG ID, int numBookmarks, LPPAN_BOOKMARK pBookMarks);

	/* Support for setting links */
	Bool	(CALLBACK *PANX_SetLink)(LONG ID, LPPAN_LINK pLink);
	Bool	(CALLBACK *PANX_DUMMY_10) (void);
	Bool	(CALLBACK *PANX_DUMMY_09) (void);
	Bool	(CALLBACK *PANX_DUMMY_08) (void);
	Bool	(CALLBACK *PANX_DUMMY_07) (void);
	Bool	(CALLBACK *PANX_DUMMY_06) (void);
	Bool	(CALLBACK *PANX_DUMMY_05) (void);
	Bool	(CALLBACK *PANX_DUMMY_04) (void);
	Bool	(CALLBACK *PANX_DUMMY_03) (void);
	Bool	(CALLBACK *PANX_DUMMY_02) (void);
	Bool	(CALLBACK *PANX_DUMMY_01) (void);
	Bool	(CALLBACK *PANX_DUMMY_00) (void);

} PANX, *PPANX,  FAR *LPPANX;


#endif	/* PANX_H */
