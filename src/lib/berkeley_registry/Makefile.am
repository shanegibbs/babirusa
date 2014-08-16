if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/berkeley_registry -Wall -Werror -g -O0 -rdynamic
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/berkeley_registry -O3 -DG_DISABLE_ASSERT
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CPPFLAGS = -DG_LOG_DOMAIN=\"Babirusa\"

noinst_LIBRARIES = libbabirusa-berkeley-registry.a

libbabirusa_berkeley_registry_a_SOURCES = \
	$(libbabirusa_berkeley_registry_a_HEADERS) \
	berkeley_registry.c

TESTS=$(check_PROGRAMS)
check_PROGRAMS=berkeley_registry_test

berkeley_registry_test_SOURCES = berkeley_registry_test.c
berkeley_registry_test_LDADD = libbabirusa-berkeley-registry.a
berkeley_registry_test_LDADD += $(GLIB_LIBS)
