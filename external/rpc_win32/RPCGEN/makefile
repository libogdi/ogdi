#
#  Zlib compression library makefile
#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

#
# The names of the targets to build
#
TOBEGEN		= rpcgen
TARGETGEN	= $(PROGGEN)

#
# Source files
#
SOURCES = rpc_main.c rpc_hout.c rpc_cout.c rpc_parse.c rpc_scan.c \
	rpc_util.c rpc_svcout.c rpc_clntout.c rpc_tblout.c rpc_sample.c

#
# Compilation flags
#
INCLUDES = $(CURRENT_INCLUDE) $(OGDI_INCLUDE) $(PROJ_INCLUDE)\
	   $(ZLIB_INCLUDE) $(GENERAL_INCLUDE) $(TCLTK_INCLUDE)
CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS) $(FLAGS_X86DEF)
LINK_LIBS= $(WIN_LINKLIB) $(RPC_LINKLIB)

#
# Include the common configuration
#
include $(TOPDIR)/config/common.mak

#
# Primary target
#
all: MKOBJECTDIR
	@echo "making $(TARGETGEN)"
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)
