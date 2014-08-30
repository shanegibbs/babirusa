SUBDIRS=berkeley_registry

AM_CFLAGS = -I$(top_srcdir)/src/lib $(GLIB_CFLAGS) $(SSL_CFLAGS)
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libbabirusa.a

libbabirusa_a_SOURCES = \
	$(libbabirusa_a_HEADERS) \
	backup.c \
	files.c \
	info.c
