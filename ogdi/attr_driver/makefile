#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

include $(TOPDIR)/config/common.mak
# SHELL	= /usr/bin/bash
#
# Sub-directories that need to be built
#
ifeq ($(TARGET),win32)
subdirs	= odbc
else
subdirs = 
endif

#
# Default target to build everything in all sub-directories
#
all: $(subdirs)

#
# Target to allow individual sub-directories to be built 
# (e.g.  make odbc)
#
.PHONY: $(subdirs)
$(subdirs): 
	cd $@; $(MAKE)

#
# Pass specialized targets into the sub-directories
#
.PHONY: $(STANDARD_TARGETS)
$(STANDARD_TARGETS):
	@for i in  null $(subdirs); do \
	  if test $$i != null ; then \
	    $(MAKE) --directory $$i $@; \
	  fi \
	done

