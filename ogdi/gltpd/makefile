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

TOBEGEN	= gltpd
TARGETGEN=$(PROGGEN)

SOURCES = asyncsvr.c ecs_sif.c ecs_svc.c

INCLUDES = $(CURRENT_INCLUDE) $(OGDI_INCLUDE) $(PROJ_INCLUDE)\
	   $(ZLIB_INCLUDE) $(GENERAL_INCLUDE)

CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS) $(FLAGS_X86DEF)

LINK_LIBS= $(OGDI_LINKLIB) $(ZLIB_LINKLIB) $(RPC_LINKLIB) \
           $(PROJ_STATICLIB) $(MATH_LINKLIB) \
	   $(LIBC_LINKLIB) $(UCB_STATICLIB) $(DL_LINKLIB) \
	   $(WIN_LINKLIB) $(X11_LINKLIB) $(LXLIB_LINKLIB) \
	   $(TK_LINKLIB) $(TCL_LINKLIB) 

include $(TOPDIR)/config/common.mak

all: MKOBJECTDIR ecs_svc.c
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)

ecs_svc.c: ../include/ecs.x
ifneq ($(TARGET),win32)
	-$(RM) -f ecs.x
	$(FILECOPY) ../include/ecs.x ecs.x
	$(RM) -f $(OBJDIR)/ecs_svc.c.raw
	rpcgen -K 120 -I -b -C -s tcp -o $(OBJDIR)/ecs_svc.c.raw ecs.x
	perl ../scripts/svc_clean.pl \
		-o ecs_svc.c $(OBJDIR)/ecs_svc.c.raw
	$(RM) -f ecs.x
endif

