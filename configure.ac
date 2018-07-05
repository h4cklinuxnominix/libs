#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hack-linux-no-minix_memory], [0.1], [gigoga367@gmail.com])
#AC_CONFIG_SRCDIR([test/changemem.cpp])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_FILES([Makefile build_mem/Makefile build_dl/Makefile])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_HEADERS([linux/user.h])
AC_CHECK_LIB([dl],[dlsym],[],[CFLAGS+=" -DWITHOUT_DL "])
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
LT_INIT
#AC_CHECK_PROGS([PSTRACE],[strace],:)
#if "$PSTRACE"==:;then

#fi

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_OUTPUT
