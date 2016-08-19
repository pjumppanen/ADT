AC_INIT([adt], [1.0], [bug-automake@gnu.org])
AM_PROG_AR
LT_INIT

CXXFLAGS=""
CFLAGS=""
R_INCLUDE=""

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_PROG_LEX
AC_PROG_YACC
AC_PROG_CXX
AC_LANG([C++])


AC_ARG_ENABLE([debug],
              [AS_HELP_STRING([--enable-debug=(no/yes)],[turn on debugging (default=no)])],
              [enable_debug=$enableval],
              [enable_debug=no])

AC_MSG_NOTICE([checking whether to enable debugging... $enable_debug])

if test "x$enable_debug" = "xyes"; then
  CXXFLAGS="$CXXFLAGS -g -DDEBUG"
  CFLAGS="$CFLAGS -g -DDEBUG"
else
  CXXFLAGS="$CXXFLAGS -O2"
  CFLAGS="$CFLAGS -O2"
  AH_BOTTOM([#define NDEBUG])
fi


AC_ARG_WITH([r-include-path],
            [AS_HELP_STRING([--with-r-include-path],[location of R includes (defaults to /usr/share/R/include)])],
            [R_INCLUDE="$withval"],
            [R_INCLUDE="/usr/share/R/include"])


AC_ARG_WITH([r-lib-path],
            [AS_HELP_STRING([--with-r-lib-path],[location of R libs (defaults to /usr/lib/R/lib)])],
            [R_LIB="$withval"],
            [R_LIB="/usr/lib/R/lib"])


AC_ARG_ENABLE([standalone],
              [AS_HELP_STRING([--enable-standalone=(no/yes)],[use standalone R libs (default=no)])],
              [enable_standalone=$enableval],
              [enable_standalone=no])

AC_MSG_NOTICE([checking whether to use standalone R libs... $enable_standalone])

if test "x$enable_standalone" = "xyes"; then
  CFLAGS="$CFLAGS -D MATHLIB_STANDALONE -I ../../src/RMath/include/"
  CXXFLAGS="$CXXFLAGS -D MATHLIB_STANDALONE -I ../../src/RMath/include/"
else
  CFLAGS="$CFLAGS -I \"$R_INCLUDE\""
  CXXFLAGS="$CXXFLAGS -I \"$R_INCLUDE\""

  AC_CHECK_FILE([$R_INCLUDE/R.h],
                [],
                [AC_MSG_ERROR([Cannot find R.h. Make sure the R_HOME environment variable is set])])
fi


AC_ARG_ENABLE([tapenade],
              [AS_HELP_STRING([--enable-tapenade=(no/yes)],[do you have tapenade (default=yes)])],
              [enable_tapenade=$enableval],
              [enable_tapenade=yes])

AC_MSG_NOTICE([checking whether we are using tapenade... $enable_tapenade])

AM_CONDITIONAL([WITH_TAPENADE], test "x$enable_tapenade" = "xyes")


CFLAGS="$CFLAGS"
CXXFLAGS="$CXXFLAGS"
LDFLAGS="$LDFLAGS"

AC_SUBST(R_INCLUDE)
AC_SUBST(R_LIB)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
objs/ADLib/Makefile
objs/ADLibTest/Makefile
objs/make_parse/Makefile
objs/fortran_parse/Makefile
objs/delphi_parse/Makefile
objs/cpp_parse/Makefile
objs/java_parse/Makefile
objs/expression_parse/Makefile
objs/blackbox_parse/Makefile
objs/Makefile
objs/sample/ArrayTest/Makefile
objs/sample/Rosenbrock/Makefile
objs/sample/Mseom/Makefile
])

AC_CHECK_FUNCS(stricmp)
AC_CHECK_FUNCS(strcasecmp)

AC_OUTPUT
