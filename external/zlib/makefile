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
TOBEGEN		= zlib
TARGETGEN	= $(ARCHGEN)

#
# Source files
#
SOURCES =   adler32.c \
            compress.c \
            crc32.c \
            deflate.c \
            gzio.c \
            infblock.c \
            infcodes.c \
            inffast.c \
            inflate.c \
            inftrees.c \
            infutil.c \
            trees.c \
            uncompr.c \
            zutil.c

#
# Include the common configuration
#
include $(TOPDIR)/config/common.mak

#
# Compilation flags
#
INCLUDES = $(CURRENT_INCLUDE)
CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

#
# Primary target
#
all: MKOBJECTDIR
	@echo "making $(TARGETGEN)"
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(DYNAGEN)

