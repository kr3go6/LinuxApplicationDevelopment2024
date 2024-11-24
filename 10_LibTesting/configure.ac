#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([libbuf], [0.0.1], [s02240464@gse.cs.msu.ru])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/libbuf.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])

# Checks for programs.
AC_PROG_CC

# Joint pkgconfig library/include tests
PKG_CHECK_MODULES([CHECK],[check])

# Enabe/disable things
AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
              [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_OUTPUT
