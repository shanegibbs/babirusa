SUBDIRS=common berkeley_registry

AM_CFLAGS = $(GLIB_CFLAGS) $(SSL_CFLAGS)
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libbackup.a

libbackup_a_CPPFLAGS = -I$(top_srcdir)/src/lib/common
libbackup_a_SOURCES = backup.c
