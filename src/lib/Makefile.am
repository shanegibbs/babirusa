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

TESTS=$(check_PROGRAMS)
check_PROGRAMS=backup_test

backup_test_SOURCES = backup_test.c
backup_test_LDADD = libbackup.a
backup_test_LDADD += $(top_builddir)/src/lib/common/libcommon.a
