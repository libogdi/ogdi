#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

TOBEGEN	= ecs_tcl
TARGETGEN=$(DYNAGEN)

SOURCES = ecs_tcl.c

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE) $(TCL_INCLUDE) $(OGDI_INCLUDE) $(PROJ_INCLUDE)
CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

LINK_LIBS= $(OGDI_LINKLIB) $(TCL_LINKLIB) $(MATH_LINKLIB)

include $(TOPDIR)/config/common.mak

all:  MKOBJECTDIR
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)



