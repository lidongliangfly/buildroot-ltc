#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([d304bt], [1.0.0], [bug@infotm.com])
AC_CONFIG_SRCDIR([app_qiwo_main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.0.0 foreign no-define])
#AC_CONFIG_MACRO_DIR([m4])


LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC
# Checks for programs.
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

PKG_CHECK_MODULES(EVENT,event == 1.0.0)
PKG_CHECK_MODULES(LIBSYSTEM,qlibsys == 1.0.0)

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h malloc.h stddef.h stdlib.h string.h sys/mount.h sys/statfs.h sys/vfs.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([clock_gettime gettimeofday memset strerror strrchr strstr])

AC_OUTPUT(Makefile)
