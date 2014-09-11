#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/index.html

AC_PREREQ([2.69])
AC_INIT([babirusa], [0.1], [shane@gibbsdevops.com])
AC_CONFIG_SRCDIR([src/bin/babirusa.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Remember externally set CFLAGS
EXTERNAL_CFLAGS="$CFLAGS"

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_CPP
AC_PROG_RANLIB

# Reset the externally set CFLAGS after calling AC_PROG*
CFLAGS="$EXTERNAL_CFLAGS"

# Use the C language and compiler for the following checks
AC_LANG([C])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

# Checks for standard header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])

# Check for math
AC_CHECK_HEADERS([math.h], [], [
  AC_MSG_ERROR([Error, math.h is missing])
])
AC_SEARCH_LIBS([pow], [m], [], [
  AC_MSG_ERROR([unable to find the pow() function])
])

# Checks for glib
PKG_CHECK_MODULES([GLIB], [glib-2.0], [], [
  AC_MSG_ERROR([unable to find glib-2.0])
])

# Checks for gobject
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0], [], [
  AC_MSG_FAILURE([no gobject-2.0 libs found])
])

# Checks for berkeley db
AC_SEARCH_LIBS([db_create], [db-5.3 db], [], [
  AC_MSG_ERROR([unable to find the db_create() function])
])
AC_CHECK_HEADER([db.h], [], [
  AC_MSG_ERROR([Error, db.h is missing])
])

AC_SUBST([BAB_CFLAGS], ["-DG_LOG_DOMAIN=\\\"Babirusa\\\" -O3 -DG_DISABLE_ASSERT"])
AC_SUBST([BAB_DEBUG_CFLAGS], ["-DG_LOG_DOMAIN=\\\"Babirusa\\\" -Wall -Werror -g -O0"])

# debug flag
AC_ARG_ENABLE([debug],
[  --enable-debug    Turn on debugging],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

#AC_MSG_ERROR([wtf DEBUG])

# Make AC_OUTPUT create each file by copying an input file (by default
# file.in), substituting the output variable values
AC_CONFIG_FILES([
                 Makefile
                 src/lib/common/Makefile
                 src/lib/dbreg/Makefile
                 src/lib/Makefile
                 src/bin/Makefile
                 ])

# Generate config.status and launch it. Call this macro once, at the
# end of configure.ac
AC_OUTPUT
