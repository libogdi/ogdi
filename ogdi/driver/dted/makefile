#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

TOBEGEN	= dted
TARGETGEN=$(DYNAGEN)

SOURCES = dted.c utils.c object.c

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE) $(OGDI_INCLUDE) $(PROJ_INCLUDE)
CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

LINK_LIBS= $(OGDI_LINKLIB)  $(GLUTIL_STATICLIB) 

include $(TOPDIR)/config/common.mak

all:  MKOBJECTDIR datadict.h
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)



