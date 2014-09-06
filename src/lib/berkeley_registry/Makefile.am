AM_CFLAGS = $(GLIB_CFLAGS) -I$(top_srcdir)/src/lib/common
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libdbreg.a

libdbreg_a_SOURCES = berkeley_registry.c

# tests

TESTS=$(check_PROGRAMS)
check_PROGRAMS=berkeley_registry_test

berkeley_registry_test_SOURCES = berkeley_registry_test.c
berkeley_registry_test_LDADD = libdbreg.a
berkeley_registry_test_LDADD += $(GLIB_LIBS)
berkeley_registry_test_LDADD += $(top_builddir)/src/lib/common/libcommon.a
