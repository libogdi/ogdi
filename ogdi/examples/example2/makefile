TOBEGEN	= example2
TARGETGEN=$(PROGGEN)

SOURCES = example2.c 

INCLUDES = $(CURRENT_INCLUDE) $(GENERAL_INCLUDE) $(OGDI_INCLUDE) $(ZLIB_INCLUDE)

CFLAGS 	= $(INCLUDES) $(COMMON_CFLAGS)

LINK_LIBS= $(OGDI_LINKLIB) $(ZLIB_LINKLIB) \
	   -L/usr/lib/x86_64-linux-gnu -lexpat


include $(TOPDIR)/config/common.mak


all: MKOBJECTDIR
	$(MAKE) --directory $(OBJDIR) -f ../makefile PASS='depend' $(TARGETGEN)
	$(COPY_LOCAL)

clean: default-clean
