#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

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

# Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0], [have_libglib=yes], [have_libglib=no])
AM_CONDITIONAL([GLIB],  [test "$have_libglib" = "yes"])

if test "x$have_libglib" = xno ; then
  AC_MSG_FAILURE([no glib-2.0 found. You probably need to install libglib2.0-dev])
fi

# Check for openssl
PKG_CHECK_MODULES([SSL], [openssl], [have_libssl=yes], [have_libssl=no])
AM_CONDITIONAL([SSL],  [test "$have_libssl" = "yes"])

if test "x$have_libgssl" = xno ; then
  AC_MSG_FAILURE([no openssl found. You probably need to install openssl and libssl-dev])
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([openssl/md5.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile src/lib/Makefile src/bin/Makefile])
AC_OUTPUT

# debug flag
AC_ARG_ENABLE(debug,
  AS_HELP_STRING(
    [--enable-debug],
    [enable debugging, default: no]),
    [case "${enableval}" in
      yes) debug=true ;;
      no)  debug=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
    esac],
    [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG,
    AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
    AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))

