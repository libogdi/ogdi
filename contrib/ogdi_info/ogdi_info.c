/******************************************************************************
 * $Id$
 *
 * Project:  OGDI Contributed Clients
 * Purpose:  Simple console query program for testing OGDI.
 * Author:   Frank Warmerdam <warmerdam@pobox.com>
 *
 ******************************************************************************
 * Copyright (c) 2000, Frank Warmerdam <warmerdam@pobox.com>
 *
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of the author not be used 
 * in advertising or publicity pertaining to distribution of the software 
 * without specific, written prior permission.   The author makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 ******************************************************************************
 *
 * $Log$
 * Revision 1.4  2001-04-09 16:06:53  warmerda
 * added -no-proj support
 *
 * Revision 1.3  2001/02/19 04:46:13  warmerda
 * use projUV, not UV
 *
 * Revision 1.2  2000/11/23 19:10:36  warmerda
 * added copyright header
 *
 */

#include "ecs.h"
#include "projects.h"

static int	ClientID = -1;
static int      bNoDict = FALSE;
static int      bNoProj = FALSE;
static int      nSampleFrequency = 1;

/************************************************************************/
/*                              DecToDMS()                              */
/************************************************************************/

const char * DecToDMS( double dfAngle )

{
    static char	szDMS1[128];
    static char	szDMS2[128];
    static int	nRotator = 1;
    int		nDeg, nMin;
    double	dfRemainder;
    

    nDeg = (int) dfAngle;

    dfRemainder = (fabs(dfAngle) - fabs(nDeg));

    nMin = (int) floor(dfRemainder*60.0);
    dfRemainder = dfRemainder - nMin / 60.0;

    if( nRotator == 1 )
    {
        nRotator = 2;
        sprintf( szDMS1, "%4dd%2d'%7.4f\"", nDeg, nMin, dfRemainder*3600.0 );
        return( szDMS1 );
    }
    else
    {
        nRotator = 1;
        sprintf( szDMS2, "%4dd%2d'%7.4f\"", nDeg, nMin, dfRemainder*3600.0 );
        return( szDMS2 );
    }
}

/************************************************************************/
/*                          DumpRasterObject()                          */
/************************************************************************/

static void DumpRasterObject( ecs_Result * result, ecs_Family featureType )

{
    int		i, xsize;

    xsize = ECSOBJECT(result).geom.ecs_Geometry_u.matrix.x.x_len;

    printf("Object ID:%s (%d pixels)\n",ECSOBJECTID(result), xsize);

    for( i = 0; i < xsize; i += nSampleFrequency )
    {
        if( nSampleFrequency != 1 )
            printf( "%d:", i );

        if( featureType == Matrix )
        {
            printf( "%d ", ECSRASTER(result)[i] );
        }
    }

    printf( "\n" );
}

/************************************************************************/
/*                          DumpVectorObject()                          */
/************************************************************************/

static void DumpVectorObject( ecs_Result * result, ecs_Family featureType )

{
    printf("Object ID:%s\n",ECSOBJECTID(result));
    printf("Object Attributes:%s\n",ECSOBJECTATTR(result));
        
    if( featureType == Text ) {
        printf( "%d: (%f , %f) Text=%s\n", 0, 
                ECSGEOM(result).text.c.x,
                ECSGEOM(result).text.c.y,
                ECSGEOM(result).text.desc );
    }
    else if( featureType == Point ) {
        printf( "%d: (%f , %f)\n", 0, 
                ECSGEOM(result).point.c.x,
                ECSGEOM(result).point.c.y );
    }
    else if( featureType == Line ) {
        int		i;
            
        for( i=0; 
             i < (int) ECSGEOM(result).line.c.c_len; 
             i += nSampleFrequency ) {
            printf("%d: (%f , %f)\n", i,
                   ECSGEOM(result).line.c.c_val[i].x,
                   ECSGEOM(result).line.c.c_val[i].y );
        }
    }
    else if( featureType == Area ) {
        int		i, iRing;

        for( iRing=0;
             iRing < (int) ECSGEOM(result).area.ring.ring_len;
             iRing++ ) {
            ecs_FeatureRing	*ring;
                
            printf( "Ring %d\n", iRing );

            ring = ECSGEOM(result).area.ring.ring_val + iRing;

            for( i=0; i < (int) ring->c.c_len; i += nSampleFrequency ) {
                printf("%d: (%f , %f)\n", i,
                       ring->c.c_val[i].x,
                       ring->c.c_val[i].y );
            }
            printf( "\n" );
        }
    }
    printf( "\n" );
}

/************************************************************************/
/*                             CheckError()                             */
/************************************************************************/

static int CheckError( ecs_Result * result )

{
    if( ECSERROR( result ) ) {
        printf( "ECSERROR: %s\n", result->message );
        return TRUE;
    }
    else
        return FALSE;
}

/************************************************************************/
/*                             AccessURL()                              */
/************************************************************************/

static int AccessURL( char * url, ecs_Region * region )

{
    ecs_Result *result;
    PJ	       *proj_defn = NULL;
    projUV     proj_pnt;

/* -------------------------------------------------------------------- */
/*      Close old client if there is one active.                        */
/* -------------------------------------------------------------------- */
    if( ClientID != -1 ) {
        result = cln_DestroyClient(ClientID);
        if( CheckError( result ) )
            return( FALSE );
        ClientID = -1;
    }
            
/* -------------------------------------------------------------------- */
/*      Open new URL/client.                                            */
/* -------------------------------------------------------------------- */
    result = cln_CreateClient(&ClientID,url);
    if( CheckError( result ) )
        return( FALSE );

/* -------------------------------------------------------------------- */
/*      Print the projection.                                           */
/* -------------------------------------------------------------------- */
    result = cln_GetServerProjection( ClientID );
    if( CheckError( result ) )
        return( FALSE );

    printf( "Projection = `%s'\n", ECSTEXT(result) );

#ifndef _WINDOWS    
    if( !bNoProj )
        proj_defn = cln_ProjInit( ECSTEXT(result) );
#endif
    
/* -------------------------------------------------------------------- */
/*      print the global bounds.                                        */
/* -------------------------------------------------------------------- */
    result = cln_GetGlobalBound(ClientID);
    if( CheckError( result ) )
        return( FALSE );

    printf( "Global Bounds\n" );
    printf( "north = %f\n", ECSREGION(result).north );
    printf( "south = %f\n", ECSREGION(result).south );
    printf( "east = %f\n", ECSREGION(result).east );
    printf( "west = %f\n", ECSREGION(result).west );
    printf( "ns_res = %f\n", ECSREGION(result).ns_res );
    printf( "ew_res = %f\n", ECSREGION(result).ew_res );

    *region = ECSREGION(result);

/* -------------------------------------------------------------------- */
/*	Print the corner coordinates in lat/long.			*/
/* -------------------------------------------------------------------- */
#ifndef _WINDOWS    
    if( proj_defn != NULL ) {
        printf( "Lat/Long Corners\n" );
        
        proj_pnt.v = region->north;
        proj_pnt.u = region->west;
        proj_pnt = pj_inv(proj_pnt, proj_defn);
        printf( "Upper Left:  (%s,%s) (%g,%g)\n",
                DecToDMS(proj_pnt.u/DEG_TO_RAD),
                DecToDMS(proj_pnt.v/DEG_TO_RAD),
                proj_pnt.u/DEG_TO_RAD, proj_pnt.v/DEG_TO_RAD );
        
        proj_pnt.v = region->north;
        proj_pnt.u = region->east;
        proj_pnt = pj_inv(proj_pnt, proj_defn);
        printf( "Upper Right: (%s,%s) (%g,%g)\n",
                DecToDMS(proj_pnt.u/DEG_TO_RAD),
                DecToDMS(proj_pnt.v/DEG_TO_RAD),
                proj_pnt.u/DEG_TO_RAD, proj_pnt.v/DEG_TO_RAD );
        
        proj_pnt.v = region->south;
        proj_pnt.u = region->west;
        proj_pnt = pj_inv(proj_pnt, proj_defn);
        printf( "Lower Left:  (%s,%s) (%g,%g)\n",
                DecToDMS(proj_pnt.u/DEG_TO_RAD),
                DecToDMS(proj_pnt.v/DEG_TO_RAD),
                proj_pnt.u/DEG_TO_RAD, proj_pnt.v/DEG_TO_RAD );
        
        proj_pnt.v = region->south;
        proj_pnt.u = region->east;
        proj_pnt = pj_inv(proj_pnt, proj_defn);
        printf( "Lower Right: (%s,%s) (%g,%g)\n",
                DecToDMS(proj_pnt.u/DEG_TO_RAD),
                DecToDMS(proj_pnt.v/DEG_TO_RAD),
                proj_pnt.u/DEG_TO_RAD, proj_pnt.v/DEG_TO_RAD );
    }
#endif
    
/* -------------------------------------------------------------------- */
/*      Print the Dictionary (update).                                  */
/* -------------------------------------------------------------------- */
    result = cln_UpdateDictionary( ClientID, "" );
    if( CheckError( result ) )
        return( FALSE );

    if( !bNoDict )
        printf( "UpdateDictionary = \n%s\n", ECSTEXT(result) );
  
    return( TRUE );
}

/************************************************************************/
/*                              IdSearch()                              */
/************************************************************************/

static void IdSearch( char * layer, ecs_Family featureType,
                      const char * id )

{
    ecs_LayerSelection selectionLayer;
    ecs_Result *result;
    
/* -------------------------------------------------------------------- */
/*      Define the layer to select.                                     */
/* -------------------------------------------------------------------- */
    selectionLayer.Select = (char *) layer;
    selectionLayer.F = featureType;
    
    result = cln_SelectLayer(ClientID,&selectionLayer);
    
    if( CheckError( result ) )
        return;

/* -------------------------------------------------------------------- */
/*      Search for the coordinate.                                      */
/* -------------------------------------------------------------------- */
    result = cln_GetObject( ClientID, (char *) id );
    if( CheckError( result ) )
        return;

    if( featureType == Matrix || featureType == Image )
    {
        DumpRasterObject( result, featureType );
    }
    else
    {
        DumpVectorObject( result, featureType );
    }
}

/************************************************************************/
/*                            CoordSearch()                             */
/************************************************************************/

static void CoordSearch( char * layer, ecs_Family featureType,
                         double x, double y )

{
    ecs_LayerSelection selectionLayer;
    ecs_Result *result;
    ecs_Coordinate	coord;
    
/* -------------------------------------------------------------------- */
/*      Define the layer to select.                                     */
/* -------------------------------------------------------------------- */
    selectionLayer.Select = (char *) layer;
    selectionLayer.F = featureType;
    
    result = cln_SelectLayer(ClientID,&selectionLayer);
    
    if( CheckError( result ) )
        return;

/* -------------------------------------------------------------------- */
/*      Search for the coordinate.                                      */
/* -------------------------------------------------------------------- */
    coord.x = x;
    coord.y = y;
    result = cln_GetObjectIdFromCoord( ClientID, &coord );
    if( CheckError( result ) )
        return;

    printf( "cln_GetObjectIdFromCoord(%f,%f) = `%s'\n",
            x, y, ECSTEXT(result) );
}

/************************************************************************/
/*                              DumpDict()                              */
/************************************************************************/

static void DumpDict( const char * pszDictName )

{
    ecs_Result *result;

    printf( "Dumping Dictionary `%s':\n", pszDictName );
    
    result = cln_UpdateDictionary( ClientID, (char *) pszDictName );
    if( CheckError( result ) )
        return;

    printf( "UpdateDictionary = \n%s\n", ECSTEXT(result) );
}

/************************************************************************/
/*                             DumpLayer()                              */
/************************************************************************/

static void DumpLayer( const char * options, ecs_Region * region,
                       char * layer, ecs_Family featureType )

{
    int nObjectCount = 0, i;
    ecs_Result *result;
    ecs_Region selectionRegion;
    ecs_LayerSelection selectionLayer;
    ecs_ObjAttributeFormat *oaf;

    (void) options;

/* -------------------------------------------------------------------- */
/*      Select a region ... this should be overridable from the         */
/*      command line.                                                   */
/* -------------------------------------------------------------------- */
    if( region != NULL ) {
        selectionRegion = *region;
        result = cln_SelectRegion(ClientID,&selectionRegion);
        if( CheckError( result ) )
            return;
    }

/* -------------------------------------------------------------------- */
/*      Define the layer to select.                                     */
/* -------------------------------------------------------------------- */
    selectionLayer.Select = (char *) layer;
    selectionLayer.F = featureType;
    
    result = cln_SelectLayer(ClientID,&selectionLayer);
    
    if( CheckError( result ) )
        return;

/* -------------------------------------------------------------------- */
/*      Dump the attribute definitions.                                 */
/* -------------------------------------------------------------------- */
    if( featureType != Matrix && featureType != Image ) {
        int	nSampleCounter = 0;

        result = cln_GetAttributesFormat( ClientID );
        if( CheckError( result ) )
            return;
        
        oaf = &(ECSRESULT(result).oaf);
        for( i = 0; i < (int) oaf->oa.oa_len; i++ )
        {
            printf( "Field %d: %s ", i, oaf->oa.oa_val[i].name );
            
            if( oaf->oa.oa_val[i].type == Char )
                printf( " (Char)" );
            else if( oaf->oa.oa_val[i].type == Varchar )
                printf( " (Varchar)" );
            else if( oaf->oa.oa_val[i].type == Longvarchar )
                printf( " (Longvarchar)" );
            else if( oaf->oa.oa_val[i].type == Decimal )
                printf( " (Decimal)" );
            else if( oaf->oa.oa_val[i].type == Numeric )
                printf( " (Numeric)" );
            else if( oaf->oa.oa_val[i].type == Smallint )
                printf( " (Smallint)" );
            else if( oaf->oa.oa_val[i].type == Integer )
                printf( " (Integer)" );
            else if( oaf->oa.oa_val[i].type == Real )
                printf( " (Real)" );
            else if( oaf->oa.oa_val[i].type == Float )
                printf( " (Float)" );
            else if( oaf->oa.oa_val[i].type == Double )
                printf( " (Double)" );
            else
                printf( " (unknown)" );
            
            printf( " %d.%d",
                    oaf->oa.oa_val[i].lenght,
                    oaf->oa.oa_val[i].precision );
            
            if( oaf->oa.oa_val[i].nullable )
                printf( " nullable" );
            printf( "\n" );
        }

/* -------------------------------------------------------------------- */
/*      Process all shapes.                                             */
/* -------------------------------------------------------------------- */
        result = cln_GetNextObject(ClientID);
        while (ECSSUCCESS(result)) {

            if( ++nSampleCounter >= nSampleFrequency )
            {
                DumpVectorObject( result, featureType );
                nSampleCounter = 0;
            }
            
            nObjectCount++;
            result = cln_GetNextObject(ClientID);
        }
    }

/* -------------------------------------------------------------------- */
/*      Report on matrix information.                                   */
/* -------------------------------------------------------------------- */
    if( featureType == Matrix || featureType == Image ) {
        int		i;
        int             nSampleCounter = 0;
        
        printf( "RasterInfo:\n" );

        result = cln_GetRasterInfo( ClientID );
        if( CheckError( result ) )
            return;

        printf( "mincat = %ld\n", ECSRASTERINFO(result).mincat );
        printf( "maxcat = %ld\n", ECSRASTERINFO(result).maxcat );
        
        printf( "width = %d", ECSRASTERINFO(result).width );
        if( featureType == Image )
        {
            if( ECSRASTERINFO(result).width == 1 )
                printf( " (RGB)" );
            else if( ECSRASTERINFO(result).width == 2 )
                printf( " (8U)" );
            else if( ECSRASTERINFO(result).width == 3 )
                printf( " (16U)" );
            else if( ECSRASTERINFO(result).width == 4 )
                printf( " (16S)" );
            else if( ECSRASTERINFO(result).width == 5 )
                printf( " (32S)" );
            else
                printf( " (unknown data type)") ;

        }
        printf( "\nheight = %d\n", ECSRASTERINFO(result).height );
        
        printf( "cat_len = %d\n", ECSRASTERINFO(result).cat.cat_len );

        for( i = 0; i < (int) ECSRASTERINFO(result).cat.cat_len; i++ ) {
            printf( "%d: no=%ld, rgb=%d,%d,%d  %s\n",
                    i,
                    ECSRASTERINFO(result).cat.cat_val[i].no_cat,
                    ECSRASTERINFO(result).cat.cat_val[i].r,
                    ECSRASTERINFO(result).cat.cat_val[i].g,
                    ECSRASTERINFO(result).cat.cat_val[i].b,
                    ECSRASTERINFO(result).cat.cat_val[i].label );
        }
/* -------------------------------------------------------------------- */
/*      Process all lines.                                              */
/* -------------------------------------------------------------------- */
        result = cln_GetNextObject(ClientID);
        while (ECSSUCCESS(result)) {

            if( ++nSampleCounter >= nSampleFrequency )
            {
                DumpRasterObject( result, featureType );
                nSampleCounter = 0;
            }

            nObjectCount++;
            result = cln_GetNextObject(ClientID);
        }
    }
  
/* -------------------------------------------------------------------- */
/*      Release the layer, and client and cleanup.                      */
/* -------------------------------------------------------------------- */
/*    result = cln_ReleaseLayer(ClientID,&selectionLayer); */

    printf( "Object Count = %d\n", nObjectCount );
}

/************************************************************************/
/*                               Usage()                                */
/************************************************************************/

static void Usage()

{
    printf("Usage: ogdi_info [-no-dict] [-no-proj]\n"
           "                 -u url -l layername -f family\n" );
    printf("                 [-r north south east west] -dl \n" );
    printf("                 [-cs easting northing] \n" );
    printf("                 [-id object_id] [-sf sample_frequency] \n" );
    exit( 1 );
}

/************************************************************************/
/*                                main()                                */
/************************************************************************/

int main( int argc, char ** argv )
{
    ecs_Family	featureType = Point;
    char *layer = "label";
    static ecs_Region	reg;
    ecs_Region  *region = NULL;
    ecs_Result *result;
    int		i;

/* -------------------------------------------------------------------- */
/*      Handle commandline arguments.                                   */
/* -------------------------------------------------------------------- */
    for( i = 1; i < argc; i++ ) {

        if( strcmp(argv[i],"-dl") == 0 ) {
            DumpLayer( "", region, layer, featureType );
        }
        else if( strcmp(argv[i], "-no-proj") == 0 ) {
            bNoProj = TRUE;
        }
        else if( strcmp(argv[i], "-no-dict") == 0 ) {
            bNoDict = TRUE;
        }
        else if( strcmp(argv[i], "-dict") == 0 ) {
            DumpDict( argv[++i] );
        }
        else if( i == argc - 1 ) {
            /* skip ... the rest require arguments.  */
            Usage();
        }
        else if( strcmp(argv[i],"-u") == 0 ) {
            AccessURL( argv[++i], &reg );
            region = &reg;
        }
        else if( strcmp(argv[i], "-l") == 0 ) {
            layer = argv[++i];
        }
        else if( strcmp(argv[i], "-sf") == 0 ) {
            nSampleFrequency = atoi(argv[++i]);
        }
        else if( strcmp(argv[i], "-f") == 0 ) {
            if( strcmp(argv[i+1],"Point") == 0 )
                featureType = Point;
            else if( strcmp(argv[i+1],"Line") == 0 )
                featureType = Line;
            else if( strcmp(argv[i+1],"Area") == 0 )
                featureType = Area;
            else if( strcmp(argv[i+1],"Text") == 0 )
                featureType = Text;
            else if( strcmp(argv[i+1],"Matrix") == 0 )
                featureType = Matrix;
            else if( strcmp(argv[i+1],"Image") == 0 )
                featureType = Image;
            i++;
        }
        else if( strcmp(argv[i], "-r") == 0 && i < argc - 4 ) {

            region = &reg;
            reg.north = atof(argv[++i]);
            reg.south = atof(argv[++i]);
            reg.east = atof(argv[++i]);
            reg.west = atof(argv[++i]);
        }
        else if( strcmp(argv[i], "-cs") == 0 && i < argc - 2 ) {
            CoordSearch( layer, featureType,
                         atof(argv[i+1]), atof(argv[i+2]) );

            i += 2;
        }
        else if( strcmp(argv[i], "-id") == 0 && i < argc - 1 ) {
            IdSearch( layer, featureType, argv[i+1] );
            i += 1;
        }
        else
            Usage();
    }

/* -------------------------------------------------------------------- */
/*      Close old client if there is one active.                        */
/* -------------------------------------------------------------------- */
    if( ClientID != -1 ) {
        result = cln_DestroyClient(ClientID);
        if( CheckError( result ) )
            return( FALSE );
        ClientID = -1;
    }

    return 0;
}



