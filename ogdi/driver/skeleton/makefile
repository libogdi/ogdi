#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

TOBEGEN	= skeleton
TARGETGEN=$(DYNAGEN)

SOURCES = skeleton.c open.c object.c utils.c 

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE) $(OGDI_INCLUDE) $(GLUTIL_INCLUDE) $(PROJ_INCLUDE)

CFLAGS 	= $(INCLUDES) $(MACHINE) $(COMMON_CFLAGS)

LINK_LIBS= $(OGDI_LINKLIB) $(GLUTIL_STATICLIB)

include $(TOPDIR)/config/common.mak

all:  MKOBJECTDIR datadict.h
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)
