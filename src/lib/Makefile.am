if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -g -O3
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CPPFLAGS = -DG_LOG_DOMAIN=\"Babirusa\"

noinst_LIBRARIES = libbabirusa.a

libbabirusa_a_SOURCES = \
	$(libbabirusa_a_HEADERS) \
	backup.c
