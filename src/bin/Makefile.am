AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/bin
AM_CFLAGS += -I$(top_srcdir)/src/lib/common
AM_CFLAGS += -I$(top_srcdir)/src/lib/dbreg
AM_CFLAGS += -I$(top_srcdir)/src/lib

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

bin_PROGRAMS = babirusa

babirusa_SOURCES = babirusa.c
babirusa_LDADD = libbabirusa_bin.a
babirusa_LDADD += $(top_builddir)/src/lib/libbackup.a
babirusa_LDADD += $(top_builddir)/src/lib/dbreg/libdbreg.a
babirusa_LDADD += $(top_builddir)/src/lib/common/libcommon.a

noinst_LIBRARIES = libbabirusa_bin.a
libbabirusa_bin_a_SOURCES = options.c log.c

TESTS=$(check_PROGRAMS)
check_PROGRAMS=options_test

options_test_SOURCES = options_test.c
options_test_LDADD = libbabirusa_bin.a
