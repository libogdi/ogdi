/*
 * vrf.c --
 *
 * Implementation of vrf Server open, close and rewind functions
 *
 * Copyright (c) 1995 Logiciels et Applications Scientifiques (L.A.S.) Inc.
 * Il est strictement interdit de publier ou de devoiler le contenu de ce
 * programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
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






