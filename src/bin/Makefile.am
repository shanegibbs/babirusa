AM_CFLAGS = $(GLIB_CFLAGS) -I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/berkeley_registry
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

bin_PROGRAMS = babirusa

babirusa_CPPFLAGS = -I$(top_srcdir)/src/lib/common
babirusa_SOURCES = babirusa.c
babirusa_LDADD = $(AM_LDFLAGS)
babirusa_LDADD += libbabirusa_bin.a
babirusa_LDADD += $(top_builddir)/src/lib/common/libcommon.a
babirusa_LDADD += $(top_builddir)/src/lib/libbackup.a
babirusa_LDADD += $(top_builddir)/src/lib/berkeley_registry/libbabirusa-berkeley-registry.a
babirusa_LDADD += $(GLIB_LIBS)
babirusa_LDADD += $(GOBJECT_LIBS)

noinst_LIBRARIES = libbabirusa_bin.a
libbabirusa_bin_a_SOURCES = options.c log.c


TESTS=$(check_PROGRAMS)
check_PROGRAMS=options_test

options_test_SOURCES = options_test.c
options_test_LDADD = libbabirusa_bin.a
options_test_LDADD += $(GLIB_LIBS)
