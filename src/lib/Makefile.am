SUBDIRS=common dbreg

AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib/common

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libbackup.a

libbackup_a_SOURCES = backup.c
