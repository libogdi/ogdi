/*
 * vrf.c --
 *
 * Implementation of vrf Server open, close and rewind functions
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
#include "vrf.h"

/*
 *  --------------------------------------------------------------------------
 *  _openAreaLayer: 
 *   
 *      open an initialize a new vrf area vector layer
 *  --------------------------------------------------------------------------
 */

void
_openAreaLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;
}

void
_closeAreaLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;


}

void
_rewindAreaLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
}

/*
 *  --------------------------------------------------------------------------
 *  _openLineLayer: 
 *   
 *      open an initialize a new vrf line vector layer
 *  --------------------------------------------------------------------------
 */

void
_openLineLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
}

void
_closeLineLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;


}

void
_rewindLineLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
}


/*
 *  --------------------------------------------------------------------------
 *  _openPointLayer: 
 *   
 *      open an initialize a new vrf sites layer
 *  --------------------------------------------------------------------------
 */

void
_openPointLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;
}


void
_closePointLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;

}

void
_rewindPointLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{

}


/*
 *  --------------------------------------------------------------------------
 *  _openTextLayer: 
 *   
 *      open an initialize a new vrf paint/label layer
 *  --------------------------------------------------------------------------
 */

void
_openTextLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;
}


void
_closeTextLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{
	register LayerPrivateData *lpriv = (LayerPrivateData *) l->priv;


}


void
_rewindTextLayer(s,l)
	ecs_Server *s;
	ecs_Layer *l;
{

}






