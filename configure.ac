#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT(cpm, 1.0, joagomez.dev@gmail.com)
AC_CONFIG_SRCDIR([src/cpm.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE( [-Wall -Werror foreign] )

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getcwd mkdir realpath])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
