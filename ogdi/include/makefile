#
#  RPCGEN to generate the OGDI header file.
#
#  Copyright (c) 1997 Logiciels et Applications Scientifiques (L.A.S.) Inc.
#  Il est strictement interdit de publier ou de devoiler le contenu de ce
#  programme sans avoir prealablement obtenu la permission de L.A.S. Inc.
#  It is strictly forbidden to publish or divulge the content of
#  these programs without the prior permission of L.A.S. Inc.
#

include $(TOPDIR)/config/common.mak

all: ecs.h

ecs.h: ecs.x
ifneq ($(TARGET),win32)
	-$(RM) -f $@ $@.raw
	rpcgen -h -C -o $@.raw ecs.x
	perl ../scripts/h_clean.pl -o $@ $@.raw
endif

clean:
	@echo Nothing to clean in ogdi/include