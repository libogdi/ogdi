/******************************************************************************
 *
 * Component: OGDI Core C API
 * Purpose: Low level XML Parsing functions for XML Capabilities documents.
 * 
 ******************************************************************************
 * Copyright (C) 2001 Information Interoperability Institute (3i)
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of 3i not be used 
 * in advertising or publicity pertaining to distribution of the software 
 * without specific, written prior permission.  3i makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 ******************************************************************************
 *
 * $Log$
 * Revision 1.1  2001-04-12 05:30:31  warmerda
 * New
 *
 */

#include <stdarg.h>
#include "ecs.h"

#ifndef EXPAT_DISABLED

#include "expat.h"

ECS_CVSID("$Id$");

#define STACK_MAX   100

/*
 * NOTE: The following uses the Expat XML parsing library found in
 *       devdir/external/expat.  More information on Expat can be found at:
 *
 *   http://expat.sourceforge.net/
 *   http://www.xml.com/pub/a/1999/09/expat/index.html
 */

/* -------------------------------------------------------------------- */
/*      The capParseInfo structure is used to keep state information    */
/*      through the parsing process of a capabilities document.         */
/* -------------------------------------------------------------------- */
typedef struct {
    ecs_Client	*cln;

    char        *error;

    char	*version;

    char	**extensions;

    int		element_depth;
    char	*element_stack[STACK_MAX];

    int		layer_count;
    ecs_LayerCapabilities **layers;
    
    ecs_LayerCapabilities *cur_layer;

    char	cdata[5000];

} capParseInfo;

/************************************************************************/
/*                            recordError()                             */
/************************************************************************/

static void recordError( capParseInfo *pi, const char *fmt, ... )

{
    char    buffer[10000];
    va_list args;

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);

    pi->error = strdup(buffer);
}

/************************************************************************/
/*                        startElementHandler()                         */
/************************************************************************/

static void startElementHandler( void *cbData, const char *element, 
                                 const char **attr )

{
    capParseInfo	*pi = (capParseInfo *) cbData;
    int			i;

    if( pi->error != NULL )
        return;

/* -------------------------------------------------------------------- */
/*      Clear the current cdata we are collecting.                      */
/* -------------------------------------------------------------------- */
    pi->cdata[0] = '\0';

/* -------------------------------------------------------------------- */
/*      Push this element onto our stack so we have a sense of context. */
/* -------------------------------------------------------------------- */
    if( pi->element_depth == STACK_MAX )
    {
        recordError( pi, "Element stack max (%d) exceeded with element <%s>.", 
                     STACK_MAX, element );
        return;
    }
    else
    {
        pi->element_stack[pi->element_depth] = strdup(element);
        pi->element_depth++;
    }

/* -------------------------------------------------------------------- */
/*      If we encounter a <FeatureType> element, create a new layer     */
/*      object and initialize it.                                       */
/* -------------------------------------------------------------------- */
    if( strcmp(element,"FeatureType") == 0 )
    {
        pi->layers = (ecs_LayerCapabilities **) 
            realloc(pi->layers, sizeof(void*) * (1 + ++pi->layer_count));
        if( pi->layers == NULL )
        {
            pi->layers = 0;
            recordError( pi, "out of memory" );
            return;
        }

        pi->layers[pi->layer_count-1] = 
            (ecs_LayerCapabilities *) calloc(1,sizeof(ecs_LayerCapabilities));
        pi->layers[pi->layer_count] = NULL;

        /* eventually we need to capture the "parents" at this point */

        pi->cur_layer = pi->layers[pi->layer_count-1];
    }

/* -------------------------------------------------------------------- */
/*      We can handle LatLongBoundingBox immediately since all the      */
/*      information is passed as attributes.                            */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"LongLatBoundingBox") == 0 
             && pi->cur_layer != NULL )
    {
        int	minx_set = 0, maxx_set = 0, miny_set = 0, maxy_set = 0;
        
        for( i = 0; attr != NULL && attr[i] != NULL; i += 2 )
        {
            if( strcmp(attr[i],"minx") == 0 )
            {
                pi->cur_layer->ll_west = atof(attr[i+1]);
                minx_set = 1;
            }
            else if( strcmp(attr[i],"maxx") == 0 )
            {
                pi->cur_layer->ll_east = atof(attr[i+1]);
                maxx_set = 1;
            }
            else if( strcmp(attr[i],"miny") == 0 )
            {
                pi->cur_layer->ll_south = atof(attr[i+1]);
                miny_set = 1;
            }
            else if( strcmp(attr[i],"maxy") == 0 )
            {
                pi->cur_layer->ll_north = atof(attr[i+1]);
                maxy_set = 1;
            }
            else
            {
                /* we deliberately don't warn about unexpected attributes */
            }
        }

        if( !minx_set || !maxx_set || !miny_set || !maxy_set )
        {
            recordError( pi, "One of minx, miny, maxx, or maxy not set for LatLongBoundingBox." );
            return;
        }
        
        pi->cur_layer->ll_bounds_set = TRUE;
    }

/* -------------------------------------------------------------------- */
/*      We can handle SRSBoundingBox immediately since all the          */
/*      information is passed as attributes.                            */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"SRSBoundingBox") == 0 
             && pi->cur_layer != NULL )
    {
        int	minx_set = 0, maxx_set = 0, miny_set = 0, maxy_set = 0;
        int	x_res_set = 0, y_res_set = 0;
        
        for( i = 0; attr != NULL && attr[i] != NULL; i += 2 )
        {
            if( strcmp(attr[i],"minx") == 0 )
            {
                pi->cur_layer->srs_west = atof(attr[i+1]);
                minx_set = 1;
            }
            else if( strcmp(attr[i],"maxx") == 0 )
            {
                pi->cur_layer->srs_east = atof(attr[i+1]);
                maxx_set = 1;
            }
            else if( strcmp(attr[i],"miny") == 0 )
            {
                pi->cur_layer->srs_south = atof(attr[i+1]);
                miny_set = 1;
            }
            else if( strcmp(attr[i],"maxy") == 0 )
            {
                pi->cur_layer->srs_north = atof(attr[i+1]);
                maxy_set = 1;
            }
            else if( strcmp(attr[i],"y_res") == 0 )
            {
                pi->cur_layer->srs_nsres = atof(attr[i+1]);
                y_res_set = 1;
            }
            else if( strcmp(attr[i],"x_res") == 0 )
            {
                pi->cur_layer->srs_ewres = atof(attr[i+1]);
                x_res_set = 1;
            }
            else
            {
                /* we deliberately don't warn about unexpected attributes */
            }
        }

        if( !minx_set || !maxx_set || !miny_set || !maxy_set 
            || !x_res_set || !y_res_set )
        {
            recordError( pi, "One of x_res, y_res, minx, miny, maxx, or maxy not set for SRSBoundingBox" );
            return;
        }
    }
}

/************************************************************************/
/*                         endElementHandler()                          */
/************************************************************************/

static void endElementHandler( void *cbData, const char *element )

{
    capParseInfo	*pi = (capParseInfo *) cbData;

    if( pi->error != NULL )
        return;

/* -------------------------------------------------------------------- */
/*      On the end of a layer definition we check that we have          */
/*      required fields.                                                */
/* -------------------------------------------------------------------- */
    if( strcmp( element, "FeatureType" ) == 0 && pi->cur_layer != NULL )
    {
        if( pi->cur_layer->name == NULL )
        {
            recordError( pi, "Didn't get a <Name> for a layer." );
            return;
        }
        else if( pi->cur_layer->srs_ewres == 0.0 )
        {
            recordError( pi, "Didn't get valid SRSBoundingBox for layer %s.", 
                         pi->cur_layer->name );
        }

        pi->cur_layer = NULL;
    }

/* -------------------------------------------------------------------- */
/*      If we are processing a layer and encounter a name, apply to     */
/*      the layer.                                                      */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"Name") == 0 && pi->cur_layer != NULL )
    {
        pi->cur_layer->name = strdup(pi->cdata);
    }

/* -------------------------------------------------------------------- */
/*      If we are processing a layer and encounter a title, apply to    */
/*      the layer.                                                      */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"Title") == 0 && pi->cur_layer != NULL )
    {
        pi->cur_layer->title = strdup(pi->cdata);
    }

/* -------------------------------------------------------------------- */
/*      If we are processing a layer and encounter an SRS, apply to     */
/*      the layer.                                                      */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"SRS") == 0 && pi->cur_layer != NULL )
    {
        if( strncmp(pi->cdata,"PROJ4:",6) == 0 )
            pi->cur_layer->srs = strdup(pi->cdata+6);
        else
            pi->cur_layer->srs = strdup(pi->cdata);
    }

/* -------------------------------------------------------------------- */
/*      If we are processing a layer and encounter a family, add to     */
/*      the layer.                                                      */
/* -------------------------------------------------------------------- */
    else if( strcmp(element,"Family") == 0 && pi->cur_layer != NULL )
    {
        if( strcmp(pi->cdata,"Matrix") == 0 )
            pi->cur_layer->families[Matrix] = 1;
        else if( strcmp(pi->cdata,"Image") == 0 )
            pi->cur_layer->families[Image] = 1;
        else if( strcmp(pi->cdata,"Area") == 0 )
            pi->cur_layer->families[Area] = 1;
        else if( strcmp(pi->cdata,"Line") == 0 )
            pi->cur_layer->families[Line] = 1;
        else if( strcmp(pi->cdata,"Point") == 0 )
            pi->cur_layer->families[Point] = 1;
        else if( strcmp(pi->cdata,"Text") == 0 )
            pi->cur_layer->families[Text] = 1;
        else if( strcmp(pi->cdata,"Edge") == 0 )
            pi->cur_layer->families[Edge] = 1;
        else if( strcmp(pi->cdata,"Face") == 0 )
            pi->cur_layer->families[Face] = 1;
        else if( strcmp(pi->cdata,"Node") == 0 )
            pi->cur_layer->families[Node] = 1;
        else if( strcmp(pi->cdata,"Ring") == 0 )
            pi->cur_layer->families[Ring] = 1;
    }

/* -------------------------------------------------------------------- */
/*      Pop the element off the stack.                                  */
/* -------------------------------------------------------------------- */
    if( pi->element_depth > 0 
        && strcmp(element,pi->element_stack[pi->element_depth-1]) == 0 )
    {
        pi->element_depth--;
        free( pi->element_stack[pi->element_depth] );
    }
    else
    {
        recordError( pi, "endElement(): unbalanced tag %s\n", element );
        return;
    }
}

/************************************************************************/
/*                          charDataHandler()                           */
/************************************************************************/

static void charDataHandler( void *cbData, const char *text, int len )

{
    capParseInfo	*pi = (capParseInfo *) cbData;

    if( pi->error != NULL )
        return;

    if( strlen(pi->cdata) + len < sizeof(pi->cdata)-1 )
    {
        int	cdata_len = strlen(pi->cdata);
        
        strncpy( pi->cdata + cdata_len, text, len );
        pi->cdata[cdata_len + len] = '\0';
    }
    else
    {
        recordError( pi, "CDATA buffer overrun in charDataHandler()." );
        return;
    }
}
#endif /* ndef EXPAT_DISABLED */

/************************************************************************/
/*                       _ecs_ParseCapabilities()                       */
/************************************************************************/

ecs_LayerCapabilities **
_ecs_ParseCapabilities( ecs_Client *cln, const char *cap_doc )

{
#ifdef EXPAT_DISABLED
    fprintf( stderr, 
             "Expat not configured, capabilities parsing disabled.\n" );

    return NULL;
#else
    capParseInfo	pi;
    XML_Parser		parser;
    
    memset( &pi, 0, sizeof(pi) );

    pi.cln = cln;
    pi.layers = (ecs_LayerCapabilities **) calloc(1,sizeof(void*));

/* -------------------------------------------------------------------- */
/*      Setup parser.                                                   */
/* -------------------------------------------------------------------- */
    parser = XML_ParserCreate(NULL);
    
    XML_SetUserData( parser, &pi );
    XML_SetElementHandler(parser, startElementHandler, endElementHandler);
    XML_SetCharacterDataHandler(parser, charDataHandler);

/* -------------------------------------------------------------------- */
/*      Parse whole document.                                           */
/* -------------------------------------------------------------------- */
    XML_Parse( parser, cap_doc, strlen(cap_doc), TRUE );

/* -------------------------------------------------------------------- */
/*      Cleanup                                                         */
/* -------------------------------------------------------------------- */
    XML_ParserFree( parser );

/* -------------------------------------------------------------------- */
/*      Report error.  This will need to be substantially improved.     */
/* -------------------------------------------------------------------- */
    if( pi.error != NULL )
    {
        fprintf( stderr, "_ecs_ParseCapabilities Error:\n%s", pi.error );
        free( pi.error );
    }

    return pi.layers;
#endif
}


