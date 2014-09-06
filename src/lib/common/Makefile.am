AM_CFLAGS = $(GLIB_CFLAGS) $(SSL_CFLAGS)
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libcommon.a

libcommon_a_SOURCES = \
	registry.h \
	files.c \
	info.c
