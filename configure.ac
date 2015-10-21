#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([SOSpin], [1.0.0], [sospin@hepforge.org])
# For using custom m4 macros.
AC_CONFIG_MACRO_DIR([m4])

# Auxiliary scripts such as install-sh and depcomp should be in following directory.
AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([src/son.cpp])
AC_CONFIG_HEADERS([config.h])

# Initialize Automake.
# There are useful options.
#   -Werror: Report warnings as errors.
#   foreign: ignores some GNU Coding Standards.
#   subdirs-objects: Create objects in sub-direcotories
#AM_INIT_AUTOMAKE([-Werror foreign subdir-objects])
AM_INIT_AUTOMAKE([subdir-objects])
AM_MAINTAINER_MODE([disable])


# Checks for programs.
# store current user given compiler flags to avoid default setup via AC_PROG_CXX
OLD_CXXFLAGS=$CXXFLAGS
# check for C++ preprocessor and compiler and the library compiler
# (might change the compiler flags)
AC_PROG_CXXCPP
AC_PROG_CXX
AC_PROG_RANLIB
# reset compiler flags to initial flags
CXXFLAGS=$OLD_CXXFLAGS

AS_IF([test "x$CXXFLAGS" = "x"],
      CXXFLAGS=-O3)

AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

#check for form installation
FORM_DIR=$PATH_TO_FORM
AC_ARG_WITH([form], [AC_HELP_STRING([--with-form=PATH], [FORM directory])], [
    FORM_DIR="${withval}"
#   AC_MSG_RESULT([form path "${withval}"])
  ],[
  ])
#check if form exist in FORM_DIR
AC_CHECK_PROG(FORM_DIR_CHECK,    form,    "yes",    "no", $FORM_DIR)
if test "$FORM_DIR_CHECK"   == "no"; then 
#uncomment and comment next lines to stop with error if form not found
#if form not found here, then the user must use PATH_TO_FORM env
#  AC_MSG_ERROR(form NOT found in $FORM_DIR)
  AC_MSG_RESULT(form NOT found in $FORM_DIR)
else
  AC_MSG_RESULT(form found in $FORM_DIR)
  FORM_DIR_IS_SET='-DFORMDIR=$(FORM_DIR)'
fi
AC_SUBST(FORM_DIR)
AC_SUBST(FORM_DIR_IS_SET)


# * Check for Doxygen.
# DX_???_FEATURE(ON|OFF) - control the default setting fo a Doxygen feature.
DX_DOXYGEN_FEATURE(ON)
DX_HTML_FEATURE(ON)
DX_MAN_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
# DX_INIT_DOXYGEN(PROJECT, [CONFIG-FILE], [OUTPUT-DOC-DIR])
DX_INIT_DOXYGEN($PACKAGE_NAME, [Doxyfile], [doc])


# Checks for libraries.
# FIXME: Replace `main' with a function in `-lSospin':
AC_CHECK_LIB([sospin], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h mach/mach.h stdlib.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday sqrt])



AC_CONFIG_FILES([Makefile src/Makefile examples/Makefile Doxyfile])
AC_OUTPUT


AC_MSG_RESULT([
Configure Information:
  C++ Compiler      :   $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS

  Linker            :   $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS

  Form              :    $(if test "x$FORM_DIR_IS_SET" = "x"; then echo no; else echo yes; fi)
    path            :    $(if test "x$FORM_DIR_IS_SET" != "x"; then echo $FORM_DIR; else echo set PATH_TO_FORM env; fi)
    path            :    or put the FORM binary file "form" in the same project folder

Supported Build Features:
  Documents             :   $(if test "x$DX_FLAG_doc" = "x1"; then echo yes; else echo no; fi)
    html                :   $(if test "x$DX_FLAG_html" = "x1"; then echo yes; else echo no; fi)
    man                 :   $(if test "x$DX_FLAG_man" = "x1"; then echo yes; else echo no; fi)
    pdf                 :   $(if test "x$DX_FLAG_pdf" = "x1"; then echo yes; else echo no; fi)
    ps                  :   $(if test "x$DX_FLAG_ps" = "x1"; then echo yes; else echo no; fi)
])
