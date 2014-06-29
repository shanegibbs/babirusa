if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -Werror -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -Werror -O3
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CPPFLAGS = -DG_LOG_DOMAIN=\"Babirusa\"

bin_PROGRAMS = babirusa

babirusa_SOURCES = babirusa.c
babirusa_LDADD = libbabirusa_bin.a
babirusa_LDADD += $(top_builddir)/src/lib/libbabirusa.a $(AM_LDFLAGS)
babirusa_LDADD += $(GLIB_LIBS)

noinst_LIBRARIES = libbabirusa_bin.a

libbabirusa_bin_a_SOURCES = options.c log.c

TESTS=$(check_PROGRAMS)
check_PROGRAMS=options_test

options_test_SOURCES = options_test.c
options_test_LDADD = libbabirusa_bin.a
options_test_LDADD += $(GLIB_LIBS)

