#
#  Grassland utility functions
#
# Copyright (C) 1997 Her Majesty the Queen in Right of Canada.
# Permission to use, copy, modify and distribute this software and
# its documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies, that
# both the copyright notice and this permission notice appear in
# supporting documentation, and that the name of Her Majesty the Queen
# in Right  of Canada not be used in advertising or publicity pertaining
# to distribution of the software without specific, written prior
# permission.  Her Majesty the Queen in Right of Canada makes no
# representations about the suitability of this software for any purpose.
# It is provided "as is" without express or implied warranty.
#

TOBEGEN	= glutil
TARGETGEN=$(ARCHGEN)

SOURCES	= getglenv.c iofile.c dirent.c

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE)

CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

include $(TOPDIR)/config/common.mak

all: MKOBJECTDIR 
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)


