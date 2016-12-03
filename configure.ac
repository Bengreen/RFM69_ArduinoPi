#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])


AC_INIT([RFM_ArduinoPi], [0.1.0])
AC_CONFIG_SRCDIR([bentemp/hello.cpp])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([bentemp/hello.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lwiringPi':
AC_CHECK_LIB([wiringPi], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h sys/time.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday select])

# AC_CONFIG_FILES([])
AC_OUTPUT(Makefile bentemp/Makefile)
