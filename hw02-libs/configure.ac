AC_PREREQ([2.72])
AC_INIT([weather], [0.0.1], [semenchuksu@yandex.ru])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_LIB([curl], [main])
AC_CHECK_LIB([json-c], [main])

AC_PROG_CC
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
