#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher07], [0.0.1], [s02240464@gse.cs.msu.ru])
AC_CONFIG_SRCDIR([src/rhasher.c])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([librhash is needed])])
AC_CHECK_LIB([readline],[readline])

# Checks for header files.
AC_CHECK_HEADERS([strings.h])
AC_CHECK_HEADERS([rhash.h])
AC_CHECK_HEADERS([readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strerror strncasecmp])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable using readline]),
    AC_DEFINE(LREADLINE_ENABLE,[],[Using readline enabled])
)

AC_ARG_WITH([readline], [AS_HELP_STRING([--without-readline], [disable support for readline])], [with_readline=no], [with_readline=yes])

LIBREADLINE=
          AS_IF([test "x$with_readline" != xno],
            [AC_CHECK_LIB([readline], [main],
              [AC_SUBST([LIBREADLINE], ["-lreadline"])
               AC_DEFINE([HAVE_LIBREADLINE], [1],
                         [Define if you have libreadline])
              ],
              [AC_MSG_FAILURE(
                 [readline test failed (--without-readline to disable)])],
              [])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
