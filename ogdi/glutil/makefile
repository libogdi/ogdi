#
#  Grassland utility functions
#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

TOBEGEN	= glutil
TARGETGEN=$(ARCHGEN)

SOURCES	= getglenv.c iofile.c dirent.c

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE)

CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

include $(TOPDIR)/config/common.mak

all: MKOBJECTDIR 
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)


