AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib/common

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libdbreg.a
libdbreg_a_SOURCES = dbreg.c

TESTS=$(check_PROGRAMS)
check_PROGRAMS=dbreg_test

dbreg_test_SOURCES = dbreg_test.c
dbreg_test_LDADD = libdbreg.a
dbreg_test_LDADD += $(top_builddir)/src/lib/common/libcommon.a
