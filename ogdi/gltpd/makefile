#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
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

