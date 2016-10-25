# $(libname) configure script
AC_INIT([adt], [1.0], [bug-automake@gnu.org])
AM_PROG_AR
LT_INIT

CXXFLAGS=""
CFLAGS=""
R_INCLUDE=""

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
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


CFLAGS="$CFLAGS -I \"$R_INCLUDE\""
CXXFLAGS="$CXXFLAGS -I \"$R_INCLUDE\""

AC_CHECK_FILE([$R_INCLUDE/R.h],
              [],
              [AC_MSG_ERROR([Cannot find R.h. Make sure the R_HOME environment variable is set])])


CFLAGS="$CFLAGS"
CXXFLAGS="$CXXFLAGS"
LDFLAGS="$LDFLAGS"

AC_SUBST(R_INCLUDE)
AC_SUBST(R_LIB)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
])

AC_CHECK_FUNCS(stricmp)
AC_CHECK_FUNCS(strcasecmp)

AC_OUTPUT
