/******************************************************************************
 *
 * Component: OGDI VRF Driver
 * Purpose: Implementation of vrf Server getObject* functions
 * 
 ******************************************************************************
 * Copyright (C) 1995 Logiciels et Applications Scientifiques (L.A.S.) Inc
 * Permission to use, copy, modify and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies, that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of L.A.S. Inc not be used 
 * in advertising or publicity pertaining to distribution of the software 
 * without specific, written prior permission. L.A.S. Inc. makes no
 * representations about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 ******************************************************************************
 *
 * $Log$
 * Revision 1.5  2001-06-13 17:33:59  warmerda
 * upgraded source headers
 *
 */


#include "ecs.h"
#include "vrf.h"

vpf_projection_type NOPROJ = {DDS, 0.0, 0.0, 0.0, 0.0, 0, 0.0, 0.0,
                              NULL, NULL, "Decimal Degrees     "};


/*********************************************************************
  vrf_get_line_feature

  Fill the ecs_Result with the vrf information directly extract
  from the table. 

  IN
     ecs_Server *s: ecs_Server structure
     ecs_Layer *layer: Layer information structure
     int prim_id: Primitive ID

  OUT
     return int: Error code. True if the function execute correctly,
     false else.
  
  ********************************************************************/

int vrf_get_line_feature (s, layer, prim_id)
     ecs_Server *s;
     ecs_Layer *layer;
     int prim_id;
{
  int32 pos, count;
  row_type row;
  int i;
  coordinate_type *ptr1;
  tri_coordinate_type *ptr2;
  double_coordinate_type *ptr3;
  double_tri_coordinate_type *ptr4;
  register LayerPrivateData *lpriv = (LayerPrivateData *) layer->priv;

  /* 
     -----------------------------------------------------------

     Check the tables to see if they are open

     -----------------------------------------------------------
     */  

  if (!vrf_checkLayerTables(s,layer)) {
    return FALSE;
  }

  /* 
     -----------------------------------------------------------

     Extract table informations from the ecs_Server structure "s".

     -----------------------------------------------------------
     */  

  row = read_row (prim_id, lpriv->l.line.edgeTable);
  if (row == NULL) {
    ecs_SetError(&(s->result), 1,"Unable to extract the edge");
    return FALSE;
  }
  pos = table_pos ("COORDINATES", lpriv->l.line.edgeTable);

  
  /* 
     -----------------------------------------------------------

     Get the coordinates in the table 

     -----------------------------------------------------------
     */

  switch (lpriv->l.line.edgeTable.header[pos].type) {
  case 'C': 
    ptr1 = get_table_element (pos, row, lpriv->l.line.edgeTable, NULL, &count);
    break;
  case 'Z':
    ptr2 = get_table_element (pos, row, lpriv->l.line.edgeTable, NULL, &count);
    break;
  case 'B':
    ptr3 = get_table_element (pos, row, lpriv->l.line.edgeTable, NULL, &count);
    break;
  case 'Y':
    ptr4 = get_table_element (pos, row, lpriv->l.line.edgeTable, NULL, &count);
    break;
  default:
    ecs_SetError(&(s->result), 2, "Undefined VRF table type");
  }

  free_row(row,lpriv->l.line.edgeTable);

  /* 
     -----------------------------------------------------------

     Initialize line structure 

     -----------------------------------------------------------
     */

  if (!ecs_SetGeomLine(&(s->result), count))
    return FALSE; 

  /* 
     -----------------------------------------------------------

     Fill the table line structure and free the old structure ptr

     -----------------------------------------------------------
     */

  switch (lpriv->l.line.edgeTable.header[pos].type) {
  case 'C': 
    {
      if ((count == 1) && (ptr1 == (coordinate_type*)NULL)) {
	ecs_SetError(&(s->result), 2, "Only one coordinate found for a line");
      } else {
	for (i=0; i<count; i++) {
         ECS_SETGEOMLINECOORD((&(s->result)),i,
			       ((double) ptr1[i].x),
			       ((double) ptr1[i].y))
	}
	if (ptr1)
	  xvt_free ((char*)ptr1);
	break;
      }
    }
  case 'Z':
    {
      if ((count == 1) && (ptr2 == (tri_coordinate_type*)NULL)) {
	ecs_SetError(&(s->result), 2, "Only one coordinate found for a line");
      } else {
	for (i=0; i<count; i++) {
	  ECS_SETGEOMLINECOORD((&(s->result)),i,((double) ptr2[i].x),((double) ptr2[i].y))
	}
	if (ptr2)
	  xvt_free ((char*)ptr2);
	break;
      }
    }
  case 'B':
    {
      if ((count == 1) && (ptr3 == (double_coordinate_type*)NULL)) {
	ecs_SetError(&(s->result), 2, "Only one coordinate found for a line");
      } else {
	for (i=0; i<count; i++) {
	  ECS_SETGEOMLINECOORD((&(s->result)),i,((double) ptr3[i].x),((double) ptr3[i].y))
	}
      }
      if (ptr3)
	xvt_free ((char*)ptr3);
      break;
    }
  case 'Y':
    {
      if ((count == 1) && (ptr4 == (double_tri_coordinate_type*)NULL)) {
	ecs_SetError(&(s->result), 2, "Only one coordinate found for a line");
      } else {
	for (i=0; i<count; i++) {
	  ECS_SETGEOMLINECOORD((&(s->result)),i,((double) ptr4[i].x),((double) ptr4[i].y))
	}
      }
      if (ptr4)
	xvt_free ((char*)ptr4);
      break;
    }    
  default:
    break;
  } /* switch type */
  return TRUE;
}

/*********************************************************************
  vrf_get_line_mbr

  Get the related mbr of a primitive line

  IN
     ecs_Server *s: ecs_Server structure
     ecs_Layer *layer: Layer information structure
     int prim_id: Primitive ID

  OUT
     return int: Error code. True if the function execute correctly,
     false else.
     double *xmin, *xmax, *ymin, *ymax: Returned bounding box
  
  ********************************************************************/

int vrf_get_line_mbr (layer, prim_id, xmin, ymin, xmax, ymax)
     ecs_Layer *layer;
     int32 prim_id;
     double *xmin;
     double *ymin;
     double *xmax;
     double *ymax;
{
  int32 count;
  register LayerPrivateData *lpriv = (LayerPrivateData *) layer->priv;
  float temp;
  row_type row;

  if (lpriv->l.line.mbrTable.fp == NULL) {
    return FALSE;
  }

  row = read_row (prim_id, lpriv->l.line.mbrTable);

  get_table_element (table_pos("XMIN",lpriv->l.line.mbrTable), row, lpriv->l.line.mbrTable, &temp, &count);
  *xmin = (double) temp;
  get_table_element (table_pos("XMAX",lpriv->l.line.mbrTable), row, lpriv->l.line.mbrTable, &temp, &count);
  *xmax = (double) temp;
  get_table_element (table_pos("YMIN",lpriv->l.line.mbrTable), row, lpriv->l.line.mbrTable, &temp, &count);
  *ymin = (double) temp;
  get_table_element (table_pos("YMAX",lpriv->l.line.mbrTable), row, lpriv->l.line.mbrTable, &temp, &count);
  *ymax = (double) temp;

  free_row(row,lpriv->l.line.mbrTable);

  return TRUE;
}

/*********************************************************************
  GET_TEXT_FEATURE                                                   
  ********************************************************************/

int vrf_get_text_feature (s, layer, prim_id)
     ecs_Server *s;
     ecs_Layer *layer;
     int prim_id;
{
  row_type row;			/* Row type in the text primitive table  */
  vpf_table_type table;         /* VRF table type format		 */
  int32 pos; 		       	/* Position in the text primitive table  */
  int32 count;		       	/* Number of caracters that were read    */
  double x,y;		       	/* coordinates of the text 	      	 */
  int code;		        /* success or failure of the operation   */
  LayerPrivateData *PrivData;   /* Private information on the layer      */
  char * desc;
  
  /* 
     -----------------------------------------------------------

     Check the tables to see if they are open

     -----------------------------------------------------------
     */  

  if (!vrf_checkLayerTables(s,layer)) {
    return FALSE;
  }

  PrivData = (LayerPrivateData *) layer->priv; /* casting the private data for a VPF Point layer from */
  table = PrivData->l.text.textTable;	       /* our interest here is the primitive table 	      */
  row = read_row (prim_id, table);	       /* Read the prim_id row from the text primitive table */

  pos = table_pos ("STRING", table);	       /* find the position in the primitive table */
  desc = (char *) get_table_element (pos, row, table, NULL, &count); /* get the text string   */
  
  pos = table_pos ("SHAPE_LINE", table);
  /* get the text coordinate, code will receive the result of th 0 = problem, 1 = success */
  if ((code = vrf_get_xy (table, row, pos, &x, &y)) == TRUE) {
    code = ecs_SetGeomText(&(s->result),x,y,desc); 
  } else {
    ecs_SetError(&(s->result), 1, "Unable to get coordinates");    
  }

  free_row(row,PrivData->l.text.textTable);  
  xvt_free(desc);
  /* here all the information needed is known in result (ecs_Result) that is in s (ecs_Server) */
  return code;

}

/*********************************************************************
  GET_POINT_FEATURE
  Derived from draw_point_row  [vpfdraw.c]                       
  ********************************************************************/

int vrf_get_point_feature (s, layer, prim_id)
     ecs_Server *s;
     ecs_Layer *layer;
     int prim_id;
{
  row_type row;			/* Row type in the point primitive table */
  vpf_table_type table;         /* VRF table type format		 */
  int32 pos; 		        /* Position in the point primitive table */
  double x,y;			/* Coordinates of the point 		 */
  int code;			/* Success or failure of the operation   */
  LayerPrivateData *PrivData;   /* Private information on the layer      */

  /* 
     -----------------------------------------------------------

     Check the tables to see if they are open

     -----------------------------------------------------------
     */  

  if (!vrf_checkLayerTables(s,layer)) {
    return FALSE;
  }
  
  PrivData = (LayerPrivateData *) layer->priv; /* casting the private data for a VPF Point layer from */
  table = PrivData->l.point.primTable;	       /* our interest here is the primitive table 	      */
  row = read_row (prim_id, table);	       /* Read the prim_id row from the point primitive table */
  pos = table_pos ("COORDINATE", table);       /* find the position in the primitive table */
  /* get the point coordinate, code will receive the result of th 0 = problem, 1 = success */
  if ((code = vrf_get_xy (table, row, pos, &x, &y)) == TRUE) {
    code = ecs_SetGeomPoint(&(s->result),x,y); 
  } else {
    ecs_SetError(&(s->result), 1, "Unable to get coordinates");
  }
  free_row(row,PrivData->l.point.primTable);  
  /* here all the information needed is known in result (ecs_Result) that is in s (ecs_Server) */
  return code;
}

/*********************************************************************
  GET_AREA_FEATURE                                                  
  Derived from outline_face  [vpfdraw.c]                          
  ********************************************************************/

int vrf_get_area_feature (s, layer, prim_id)
     ecs_Server *s;
     ecs_Layer *layer;
     int prim_id;
{                                    
  int32 n=0;
  int code,i,j,k,qty;
  face_rec_type face_rec;
  ring_rec_type ring_rec;
  vpf_table_type facetable, ringtable, edgetable;
  AREA_FEATURE area;
  double x,y;
  int firstlength;
    
  /* 
     -----------------------------------------------------------

     Check the tables to see if they are open

     -----------------------------------------------------------
     */  

  if (!vrf_checkLayerTables(s,layer)) {
    return FALSE;
  }

  facetable = ((LayerPrivateData *) layer->priv)->l.area.faceTable;
  ringtable = ((LayerPrivateData *) layer->priv)->l.area.ringTable;
  edgetable = ((LayerPrivateData *) layer->priv)->l.area.edgeTable;
  face_rec = read_face (prim_id, facetable);
  ring_rec = read_ring (face_rec.ring, ringtable);
  
  /* 
     Allocate space to store addresses of all the ring structures 
     */
  area.rings = (RING**)xvt_zmalloc (MAXRINGS * sizeof (RING*));
  if (area.rings == NULL) {
    ecs_SetError(&(s->result), 2, "No enough memory");
    return FALSE;
  }

  /* 
     Get the outer ring coords 
     */
  area.rings[n] = (RING*)xvt_zmalloc (sizeof (RING));
  if (area.rings[n] == NULL) {
    ecs_SetError(&(s->result), 2, "No enough memory");
    xvt_free ((char*)area.rings);
    return FALSE;
  }
  
  area.rings[n]->id = n+1;

  if (!vrf_get_ring_coords (s,area.rings[n], prim_id, ring_rec.edge, edgetable)) {
    xvt_free((char*)area.rings[0]);
    xvt_free ((char*)area.rings);
    return FALSE;
  }
  firstlength = area.rings[n]->nr_segs;
  n++;
  
  /* 
     Get the coords for any inner rings that exist 
     */
  while (ring_rec.face == prim_id) {
    ring_rec = read_next_ring (ringtable);
    
    if (feof (ringtable.fp))
      break;

    /*
      The Browse Case: It is possible the last island cover the same
      region than the first one.
      */
    if (n>=2 && ring_rec.face != prim_id && area.rings[n-1]->nr_segs == firstlength) {
      n--;
      break;
    }

    if (ring_rec.face == prim_id) {
      area.rings[n] = (RING*)xvt_zmalloc (sizeof (RING));
      if (area.rings[n] == NULL) {
	for(i=0;i<n-1;i++) {
	  for(j=0;j<area.rings[i]->nr_segs;j++) {
	    xvt_free((char*) area.rings[i]->segs[j]->coords);
	    xvt_free((char*) area.rings[i]->segs[j]);
	  }
	  xvt_free((char*)area.rings[i]->segs);
	  xvt_free((char*)area.rings[i]);
	}
	xvt_free ((char*)area.rings);
	ecs_SetError(&(s->result), 2, "No enough memory");
	return FALSE;
      }
        
      area.rings[n]->id = n+1;
      
      if (!vrf_get_ring_coords (s,area.rings[n], prim_id, ring_rec.edge, edgetable)) {
	for(i=0;i<n-1;i++) {
	  for(j=0;j<area.rings[i]->nr_segs;j++) {
	    xvt_free((char*) area.rings[i]->segs[j]->coords);
	    xvt_free((char*) area.rings[i]->segs[j]);
	  }
	  xvt_free((char*)area.rings[i]->segs);
	  xvt_free((char*)area.rings[i]);
	}
	xvt_free ((char*)area.rings);
	ecs_SetError(&(s->result), 2, "No enough memory");
	return FALSE;
      }

      n++;                        
    }
  }
  area.nr_rings = n;
  
  /* 
     Extract all coordinates from area and put them in a ecs_Area 
     */

  code = TRUE;
  if ((code = ecs_SetGeomArea(&(s->result), area.nr_rings))) {
    for(i=0;i<area.nr_rings;i++) {

      if (!code)
	break;

      /*
	For all the ring segments, calculate the total number of points
	*/

      qty = 0;
      for(j=0;j<area.rings[i]->nr_segs;j++)
	qty += area.rings[i]->segs[j]->nr_coords;
      
      /*
	Initialise the ring and add all the coordinates
	*/

      if( (code = ecs_SetGeomAreaRing(&(s->result), i, qty, 0.0, 0.0)) ) { 
	qty = 0;
	for(j=0;j<area.rings[i]->nr_segs;j++) {
	  for(k=0; k<area.rings[i]->segs[j]->nr_coords;k++) {
	    x = (double) area.rings[i]->segs[j]->coords[k].x;
	    y = (double) area.rings[i]->segs[j]->coords[k].y;
	    ECS_SETGEOMAREACOORD((&(s->result)), i, qty, x, y);
	    qty++;
	  }
	}
      }
    }
  }
    
  for(i=0;i < area.nr_rings;i++) {
    for(j=0;j<area.rings[i]->nr_segs;j++) {
      xvt_free((char*) area.rings[i]->segs[j]->coords);
      xvt_free((char*) area.rings[i]->segs[j]);
    }
    xvt_free((char*)area.rings[i]->segs);
    xvt_free((char*)area.rings[i]);
  }
  xvt_free ((char*)area.rings);
  
  return code;
} 
   
/*********************************************************************
  GET_RING_COORDS                                                   
  Derived from outline_face_ring  [vpfdraw.c]                   
  ********************************************************************/

int vrf_get_ring_coords (s,ring, face_id, start_edge, edgetable)
     ecs_Server *s;
     RING *ring;
     int32 face_id, start_edge;
     vpf_table_type edgetable;
{
  edge_rec_type edge_rec;
  int32 next_edge, prevnode, i, n=0;
  boolean done=FALSE;
  vpf_projection_type proj;
  double_coordinate_type  dcoord;
  SEGMENT **temp;
  long eqlface1=0L, eqlface2=0L;
  long eqlnpts;
  long eqlleft_edge=0L, eqlright_edge=0L;
  long maxsegs;
  char buffer[120];

  maxsegs = MAXSEGS;
  proj = NOPROJ;
  
  edge_rec = read_edge (start_edge, edgetable, proj.inverse_proj);
  if (edge_rec.npts == 0) {
    sprintf(buffer,"Unable to read the edge %d in the face %d",
            (int) start_edge, (int) face_id);
    ecs_SetError(&(s->result), 1,buffer);
    return FALSE;
  }
  edge_rec.dir = '+';
  prevnode = edge_rec.start_node;
  
  if (edge_rec.start_node == edge_rec.end_node)
    done = TRUE;
  next_edge = vrf_next_face_edge (&edge_rec, &prevnode, face_id);
  if ((edge_rec.right_face == face_id) && (edge_rec.left_face == face_id))
    {
      eqlface1 = 1L;
      eqlnpts = edge_rec.npts;
      eqlleft_edge = edge_rec.left_edge;
      eqlright_edge = edge_rec.right_edge;
    }
  else
    eqlface1 = 0L;
   
  /* Allocate plenty of space for array of segment addresses */
  ring->segs = (SEGMENT**)xvt_zmalloc (maxsegs * sizeof (SEGMENT*));

  /* Load the first segment of the ring */
  ring->segs[n] = (SEGMENT*)xvt_zmalloc (sizeof (SEGMENT));
  ring->segs[n]->nr_coords = edge_rec.npts;
  ring->segs[n]->id = n+1;

  /* Allocate space for the coordinates of the first segment */
  ring->segs[n]->coords = (COORDINATE*)xvt_zmalloc ((size_t)ring->segs[n]->nr_coords * sizeof (COORDINATE));
                                                
  /* If the direction is - load in reverse order */
  if (edge_rec.dir == '-')
    {
      for (i=(edge_rec.npts-1); i>=0; i--)
	{
	  dcoord = next_edge_coordinate (&edge_rec);
	  ring->segs[n]->coords[i].x = (float)dcoord.x;
	  ring->segs[n]->coords[i].y = (float)dcoord.y;
	}
      } else {
	for (i=0; i<edge_rec.npts; i++) {
	  dcoord = next_edge_coordinate (&edge_rec);
	  ring->segs[n]->coords[i].x = (float)dcoord.x;
	  ring->segs[n]->coords[i].y = (float)dcoord.y;
	}
    }

  n++;
  if (edge_rec.coords)
    xvt_free ((char*)edge_rec.coords);

  while (!done)
    {
      if (next_edge < 0)
	{
	  done = TRUE;
	}

      if (next_edge == 0)
	{
	  done = TRUE;
	}

      if (next_edge == start_edge && !eqlface1)
	{
	  done = TRUE;
	  continue;
	}

      if (next_edge == start_edge && eqlface1 &&
	  eqlleft_edge == 0L && eqlright_edge == 0L)
	{
	  done = TRUE;
	}

      if (!done)
	{
	  edge_rec = read_edge( next_edge, edgetable, (int)proj.inverse_proj);
	  if (edge_rec.npts == 0) {
	    sprintf(buffer,"Unable to read the edge %d in the face %d",
		    (int) next_edge, (int) face_id);
	    ecs_SetError(&(s->result), 1,buffer);
	    return FALSE;
	  }

	  next_edge = vrf_next_face_edge( &edge_rec, &prevnode, face_id );
	  if ((edge_rec.right_face == face_id) && (edge_rec.left_face ==face_id))
            eqlface2 = 1L;
	  else
            eqlface2 = 0L;
 
	  /* Allocate space for the next segment */
	  if (eqlface1 && edge_rec.id == eqlleft_edge)
            eqlleft_edge = 0L;
	  if (eqlface1 && edge_rec.id == eqlright_edge)
            eqlright_edge = 0L;
	  ring->segs[n] = (SEGMENT*)xvt_zmalloc (sizeof (SEGMENT));
	  ring->segs[n]->nr_coords = edge_rec.npts;
	  ring->segs[n]->id = n+1;
         
	  /* Allocate space for the segment coordinates */
	  ring->segs[n]->coords = (COORDINATE*)xvt_zmalloc ((size_t)ring->segs[n]->nr_coords * sizeof (COORDINATE));

	  /* If the direction is - load in reverse order */
	  if (edge_rec.dir == '-')
            {
	      for (i=(edge_rec.npts-1); i>=0; i--)
		{
		  dcoord = next_edge_coordinate (&edge_rec);
		  ring->segs[n]->coords[i].x = (float)dcoord.x;
		  ring->segs[n]->coords[i].y = (float)dcoord.y;
		}
            }
	  else
            {
	      for (i=0; i<edge_rec.npts; i++)
		{
		  dcoord = next_edge_coordinate (&edge_rec);
		  ring->segs[n]->coords[i].x = (float)dcoord.x;
		  ring->segs[n]->coords[i].y = (float)dcoord.y;
		}
            }
	  n++;
	  if (edge_rec.coords)
            xvt_free ((char*)edge_rec.coords);

	} /* if (!done) */
    } /* while */              
  ring->nr_segs = n;

  /* Realloc the segs array to free unused memory */
  temp = (SEGMENT**)xvt_zmalloc (ring->nr_segs * sizeof (SEGMENT*));
  memcpy ((char*)temp, (char*)ring->segs, (ring->nr_segs * sizeof (SEGMENT*)));
  xvt_free ((char*)ring->segs);
  ring->segs = temp;

  return TRUE;
} 

/*********************************************************************
  NEXT_FACE_EDGE                                                   
  Derived from next_face_edge   [vpfdraw.c]                     
  ********************************************************************/
int32 vrf_next_face_edge (edge_rec, prevnode, face_id)
     edge_rec_type *edge_rec;
     int32 *prevnode, face_id;
{
  int32 next;

  if ((edge_rec->right_face == face_id) && 
      (edge_rec->left_face == face_id)) {
    /* 
       Dangle - go the opposite dir to continue aint32 the boundary 
       */
    if (*prevnode == edge_rec->start_node) {
      edge_rec->dir = '+';
      next = edge_rec->right_edge;
      *prevnode = edge_rec->end_node;
    } else if (*prevnode == edge_rec->end_node) {
      edge_rec->dir = '-';
      next = edge_rec->left_edge;
      *prevnode = edge_rec->start_node;
    } else {
      next = -1;
    }
  } else if (edge_rec->right_face == face_id) {
    /* 
       The face is on the right - take the right forward edge 
       */
    next = edge_rec->right_edge;
    edge_rec->dir = '+';
    *prevnode = edge_rec->end_node;
  } else if (edge_rec->left_face == face_id) {
    /* 
       The face is on the left - take the left forward edge 
       */
    next = edge_rec->left_edge;
    edge_rec->dir = '-';
    *prevnode = edge_rec->start_node;
  }
  else
    next = -1;
  
  return next;
}  

/*********************************************************************
  vrf_get_area_mbr

  Get the related mbr of a primitive face

  IN
     ecs_Server *s: ecs_Server structure
     ecs_Layer *layer: Layer information structure
     int prim_id: Primitive ID

  OUT
     return int: Error code. True if the function execute correctly,
     false else.
     double *xmin, *xmax, *ymin, *ymax: Returned bounding box
  
  ********************************************************************/

int vrf_get_area_mbr (layer, prim_id, xmin, ymin, xmax, ymax)
     ecs_Layer *layer;
     int32 prim_id;
     double *xmin;
     double *ymin;
     double *xmax;
     double *ymax;
{
  int32 count;
  register LayerPrivateData *lpriv = (LayerPrivateData *) layer->priv;
  float temp;
  row_type row;

  if (lpriv->l.area.mbrTable.fp == NULL) {
    return FALSE;
  }

  row = read_row (prim_id, lpriv->l.area.mbrTable);

  get_table_element (table_pos("XMIN",lpriv->l.area.mbrTable), row, lpriv->l.area.mbrTable, &temp, &count);
  *xmin = (double) temp;
  get_table_element (table_pos("XMAX",lpriv->l.area.mbrTable), row, lpriv->l.area.mbrTable, &temp, &count);
  *xmax = (double) temp;
  get_table_element (table_pos("YMIN",lpriv->l.area.mbrTable), row, lpriv->l.area.mbrTable, &temp, &count);
  *ymin = (double) temp;
  get_table_element (table_pos("YMAX",lpriv->l.area.mbrTable), row, lpriv->l.area.mbrTable, &temp, &count);
  *ymax = (double) temp;

  free_row(row,lpriv->l.area.mbrTable);

  return TRUE;
}


/****************************************************************************

  vrf_get_xy

  Extract from the database the point contain at the "pos" column of
  the table "table" at the row "row". If the structure found is a list
  of coordinate, only the first one will be returned.

  IN
     vpf_table_type table :   Table of primitives (already open)
     row_type       row   :   Table row in "table"
     long           pos   :   Column position in "table" for "COORDINATE"

  OUT
     double *x,*y         :   Point extract from structure
     return int           :   This flag indicate the success or the failure
                              of the function.

  ***************************************************************************/

int vrf_get_xy (table, row, pos, x, y)
     vpf_table_type table;
     row_type       row;
     int32           pos;
     double         *x;
     double         *y;
{
  int32 count;
  coordinate_type temp1, *ptr1;
  tri_coordinate_type temp2, *ptr2;
  double_coordinate_type temp3, *ptr3;
  double_tri_coordinate_type temp4, *ptr4;

  switch (table.header[pos].type) {
  case 'C': 
    {
      ptr1 = get_table_element (pos, row, table, &temp1, &count);
      
      if ((count == 1) && (ptr1 == (coordinate_type*)NULL)) {
	*x = (double) temp1.x;
	*y = (double) temp1.y;
      } else {
	*x = (double) ptr1->x;
	*y = (double) ptr1->y;
	if (ptr1)
	  free(ptr1);
      }
      break;
    }
  case 'Z':
    {
      ptr2 = get_table_element (pos, row, table, &temp2, &count);
      if ((count == 1) && (ptr2 == (tri_coordinate_type*)NULL)) {
	*x = temp2.x;
	*y = temp2.y;
      } else {
	*x = (double) ptr2[0].x;
	*y = (double) ptr2[0].y;
	if (ptr2)
	  xvt_free ((char*)ptr2);
      }
      break;
    }
  case 'B':
    {
      ptr3 = get_table_element (pos, row, table, &temp3, &count);
      if ((count == 1) && (ptr3 == (double_coordinate_type*)NULL)) {
	*x = (double) temp3.x;
	*y = (double) temp3.y;
      } else {
	*x = (double) ptr3[0].x;
	*y = (double) ptr3[0].y;
	if (ptr3)
	  xvt_free ((char*)ptr3);
      }
      break;
    }
  case 'Y':
    {
      ptr4 = get_table_element (pos, row, table, &temp4, &count);
      if ((count == 1) && (ptr4 == (double_tri_coordinate_type*)NULL)) {
	*x = (double) temp4.x;
	*y = (double) temp4.y;
      } else {
	*x = (double) ptr4[0].x;
	*y = (double) ptr4[0].y;
	if (ptr4)
	  xvt_free ((char*)ptr4);
      }    
      break;
    }
  default:
    break;
  } /* switch type */
  return TRUE;
}



/****************************************************************************

  vrf_get_ObjAttributes

  Get the attributes from the feature table and generate a string with
  it.

  IN
     vpf_table_type table :   Table of primitives (already open)
     int32 row_pos         :   Row position in table

  OUT
     return char *: The returned string. If NULL, the operation
     was unsuccessul.

  ***************************************************************************/

char *vrf_get_ObjAttributes(table, row_pos)
     vpf_table_type table;
     int32 row_pos;
{
  int i;
  char buffer[255];
  row_type row;
  static char *returnString = NULL;
  int32 lenght;
  char temp1, *ptr1;
  float temp2;
  double temp3;
  short int temp4;
  int temp5;
  date_type temp6;
  long count;

  row = read_row(row_pos,table);

  if (returnString != NULL) {
    free(returnString);
    returnString = NULL;
  }

  lenght = 1;
  returnString = (char *) malloc(lenght);
  strcpy(returnString,"");

  for(i = 0; i < table.nfields; ++i) {
    switch(table.header[i].type) {
    case 'T':
      ptr1 = get_table_element (i, row, table, &temp1, &count);
      if ((count == 1) && (ptr1 == (char *) NULL)) {
	lenght += 6;
	returnString = (char *) realloc(returnString,lenght);
	if (returnString == NULL) {
	  free_row(row,table);
	  return NULL;
	}
	sprintf(buffer,"%c",temp1);
	strcat(returnString,"{ ");
	strcat(returnString,buffer);
	strcat(returnString," } ");
      } else {
	lenght += count + 6;
	returnString = (char *) realloc(returnString,lenght);
	if (returnString == NULL) {
	  free_row(row,table);
	  free(ptr1);
	  return NULL;
	}
	strcat(returnString,"{ ");
	strcat(returnString,ptr1);
	strcat(returnString," } ");
	free(ptr1);
      }    
      break;
      /*added 5-28-97 case "D"  */
    case 'D':  /* Date */
      ptr1 = get_table_element (i, row, table, &temp6, &count);
      if ((count == 1) && (ptr1 == (char *) NULL)) {
	lenght += 5 + sizeof(date_type);  /*Changed from += 6 to += 5 + sizeof(date_type)*/
	returnString = (char *) realloc(returnString,lenght);
	if (returnString == NULL) {
	  free_row(row,table);
	  return NULL;
	}
	sprintf(buffer,"%20s",temp6);	/*dap Changed %c to %20s*/
	strcat(returnString,"{ ");
	strcat(returnString,buffer);
	strcat(returnString," } ");
      } else {
	/* Changed from += count + 6 to += 5 + (count * sizeof(date_type))*/	
	lenght += 5 + (count * sizeof(date_type));  
	returnString = (char *) realloc(returnString,lenght);
	if (returnString == NULL) {
	  free_row(row,table);
	  free(ptr1);
	  return NULL;
	}
	strcat(returnString,"{ ");
	strcat(returnString,ptr1);
	strcat(returnString," } ");
	free(ptr1);
      }    
      break;
   case 'F':
      get_table_element (i, row, table, &temp2, &count);
      sprintf(buffer,"%f",temp2);
      lenght += strlen(buffer) + 2;
      returnString = (char *) realloc(returnString,lenght);
      if (returnString == NULL) {
	free_row(row,table);
	return NULL;
      }
      strcat(returnString,buffer);
      strcat(returnString," ");
      break;
    case 'R':
      get_table_element (i, row, table, &temp3, &count);
      sprintf(buffer,"%f",temp3);
      lenght += strlen(buffer) + 2;
      returnString = (char *) realloc(returnString,lenght);
      if (returnString == NULL) {
	free_row(row,table);
	return NULL;
      }
      strcat(returnString,buffer);
      strcat(returnString," ");
      break;
    case 'S':
      get_table_element (i, row, table, &temp4, &count);
      sprintf(buffer,"%d",temp4);
      lenght += strlen(buffer) + 2;
      returnString = (char *) realloc(returnString,lenght);
      if (returnString == NULL) {
	free_row(row,table);
	return NULL;
      }
      strcat(returnString,buffer);
      strcat(returnString," ");
      break;
    case 'I':
      get_table_element (i, row, table, &temp5, &count);
      sprintf(buffer,"%d",temp5);
      lenght += strlen(buffer) + 2;
      returnString = (char *) realloc(returnString,lenght);
      if (returnString == NULL) {
	free_row(row,table);
	return NULL;
      }
      strcat(returnString,buffer);
      strcat(returnString," ");
      break;
    }
  }

  free_row(row,table);
  return returnString;
}

int vrf_checkLayerTables(s,l)
     ecs_Server *s;
     ecs_Layer *l;
{
  register LayerPrivateData *lpriv;

  lpriv = (LayerPrivateData *) l->priv;
  switch(l->sel.F) {
  case Area:
    if (lpriv->l.area.faceTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table fac not open");
      return FALSE;
    }
    if (lpriv->l.area.mbrTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table mbr not open");
      return FALSE;
    }
    if (lpriv->l.area.ringTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table rng not open");
      return FALSE;
    }
    if (lpriv->l.area.edgeTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table edg not open");
      return FALSE;
    }

    break;
  case Line:
    if (lpriv->l.line.mbrTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table mbr not open");
      return FALSE;
    }
    if (lpriv->l.line.edgeTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table edg not open");
      return FALSE;
    }
    break;
  case Point:
    if (lpriv->l.point.primTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table end or cnd not open");
      return FALSE;
    }
    break;
  case Text:
    if (lpriv->l.text.textTable.fp == NULL) {
      ecs_SetError(&(s->result), 1, "VRF table txt not open");
      return FALSE;
    }
    break;
  default:
    return FALSE;
  }

  return TRUE;
}


