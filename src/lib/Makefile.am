SUBDIRS=berkeley_registry

if DEBUG
  AM_CFLAGS =-I$(top_srcdir)/src/lib -Wall -Werror -g -O0 -rdynamic
else
  AM_CFLAGS =-I$(top_srcdir)/src/lib -O3 -DG_DISABLE_ASSERT
endif

AM_CFLAGS += $(GLIB_CFLAGS)
AM_CFLAGS += $(SSL_CFLAGS)
AM_CPPFLAGS = -DG_LOG_DOMAIN=\"Babirusa\"

noinst_LIBRARIES = libbabirusa.a

libbabirusa_a_SOURCES = \
	$(libbabirusa_a_HEADERS) \
	backup.c \
	files.c \
	info.c
