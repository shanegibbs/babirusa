if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/bin -I$(top_srcdir)/src/lib -Wall -O3
endif

AM_CFLAGS += $(GLIB_CFLAGS)

bin_PROGRAMS = babirusa

babirusa_SOURCES = babirusa.c options.c
babirusa_LDADD = $(top_builddir)/src/lib/libbabirusa.a $(AM_LDFLAGS)
babirusa_LDADD += $(GLIB_LIBS)

