# Copyright (C) 1996 Her Majesty the Queen in Right of Canada.
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


# Common macros and symbols used by all platforms
#
#
#
# !!! IMPORTANT !!!
#
# $TARGET and $TOPDIR must be defined in the environment
#
#	- $TARGET is the platform on which you compile;
#	  it could be 'solaris' or 'win32'
#	- $TOPDIR is the root directory of OGDI source files
#
#


#
# Default definitions
#

ifndef CFG
CFG = release
endif

ifndef TARGET
TARGET = $(shell uname)
endif

#
# Standard location of external components (not maintained
# by LAS)
#


#
# Standard location of compiled component libraries
#

BINDIR		= $(TOPDIR)/bin/$(TARGET)
LIBDIR		= $(TOPDIR)/lib/$(TARGET)

#
# A location named $(LINKDIR) will be defined in the system
# specific configuration files.  Under win32 this will point 
# to the location of the export libs $(LIBDIR), but under
# Unix it is the location of the shared objects $(BINDIR).
#

#
# Standard location of software components.
#

CURRENT_DIR	= ./
VPF_DIR		= $(topdir)/vpflib

#
# Standard location of include files.
#

CURRENT_INCLUDE	= $(patsubst %,$(INCL_SW)%,$(subst :, ,$(VPATH)))
GENERAL_INCLUDE = $(INCL_SW)$(TOPDIR)/include/$(TARGET)


OGDI_INCLUDE	= $(INCL_SW)$(TOPDIR)/ogdi/include
VRF_INCLUDE	= $(INCL_SW)$(TOPDIR)/ogdi/driver/vrf
PROJ_INCLUDE	= $(INCL_SW)$(TOPDIR)/proj
VPF_INCLUDE	= $(INCL_SW)$(TOPDIR)/vpflib/include $(INCL_SW)$(TOPDIR)/vpflib
ZLIB_INCLUDE	= $(INCL_SW)$(TOPDIR)/external/zlib
GLUTIL_INCLUDE	= $(INCL_SW)$(TOPDIR)/ogdi/glutil

#
# Dynamic libraries (shared objects)
#

ODBCEXT_LINKLIB	= $(LINK_SW)$(LINKDIR)$(LIB_SW)odbcext$(LIB_SUFFIX)
OGDI_LINKLIB	= $(LINK_SW)$(LINKDIR)$(LIB_SW)ogdi$(LIB_SUFFIX)
ZLIB_LINKLIB	= $(LINK_SW)$(LINKDIR)$(LIB_SW)zlib$(LIB_SUFFIX)

#
# Static libraries (archives)
#

PROJ_STATICLIB		= $(LINK_SW)$(LIBDIR)/static$(LIB_SW)proj$(LIB_SUFFIX)
VPF_STATICLIB		= $(LINK_SW)$(LIBDIR)/static$(LIB_SW)vpf$(LIB_SUFFIX)
REMOTE_STATICLIB	= $(LINK_SW)$(LIBDIR)/static$(LIB_SW)remote$(LIB_SUFFIX)
GLUTIL_STATICLIB =	$(LINK_SW)$(LIBDIR)/static$(LIB_SW)glutil$(LIB_SUFFIX)


#
# Library aggregations
#

 
#
# Location of resulting object files
#

OBJDIR		=OBJ.$(TARGET)
DEPENDFILE	= depend.d
OBJECTS		= $(SOURCES:.c=.$(OBJ_EXT))

#
# When compiling in the OBJ.$(TARGET) directory, search for
# the source code files in the parent directory.
#

VPATH		= ..

#
# Standard target names.  Do not redefine them if they have
# already been set in the enclosing makefile.
#

ifndef ARCGEN
ARCHGEN = $(TOPDIR)/lib/$(TARGET)/static/$(LIB_PREFIX)$(TOBEGEN).$(ARCH_EXT)
endif
ifndef DYNAGEN
DYNAGEN = $(TOPDIR)/bin/$(TARGET)/$(LIB_PREFIX)$(TOBEGEN).$(SHLIB_EXT)
endif
ifndef PROGGEN
PROGGEN = $(TOPDIR)/bin/$(TARGET)/$(TOBEGEN)$(APP_EXT)
endif

STANDARD_TARGETS	= clean

#
# Default target to be used if no others are specified.
# This implies that all makefiles that include this configuration
# must provide an 'all' target.
#

all:

#
# Include the platform specific configuration
#

include $(TOPDIR)/config/$(TARGET).mak


#
# Standard targets provided for all sub-makefiles
#

#
# Create a platform-specific object directory
#

MKOBJECTDIR:
	$(MKINSTALLDIR) $(OBJDIR)

#
# Build the dependency file using 'makedepend'
#

$(DEPENDFILE): $(SOURCES)
	touch depend.tmp
	makedepend -f depend.tmp -- $(subst /I,-I,$(subst /D,-D,$(SYSTEM_INCLUDE) $(CFLAGS))) -- $^
	sed  -e 's?^\.\./??g' -e 's?:/?:\\?g' depend.tmp > $@
#
# Clean all possible junk
#

default-clean:
	-$(RMALL) $(OBJDIR) $(TOPDIR)/lib/$(TARGET)/static/$(LIB_PREFIX)$(TOBEGEN).* $(OBJDIR) $(TOPDIR)/lib/$(TARGET)/$(LIB_PREFIX)$(TOBEGEN).* $(TOPDIR)/bin/$(TARGET)/$(LIB_PREFIX)$(TOBEGEN).* $(PROGGEN)

#
# Include the auto-generated dependency rules.  Only include
# this file if executing from within the OBJ.$(TARGET) directory.
#

# ifeq ($(PASS),depend)
# include $(DEPENDFILE)
# endif

#
# End of the common configuration
#




