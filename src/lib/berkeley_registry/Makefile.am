AM_CFLAGS = $(GLIB_CFLAGS) -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/berkeley_registry
if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libbabirusa-berkeley-registry.a

libbabirusa_berkeley_registry_a_SOURCES = \
	$(libbabirusa_berkeley_registry_a_HEADERS) \
	berkeley_registry.c

TESTS=$(check_PROGRAMS)
check_PROGRAMS=berkeley_registry_test

berkeley_registry_test_SOURCES = berkeley_registry_test.c
berkeley_registry_test_LDADD = libbabirusa-berkeley-registry.a
berkeley_registry_test_LDADD += $(GLIB_LIBS)
