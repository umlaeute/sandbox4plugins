AC_PREREQ([2.60])
AC_INIT([cpp-plugins], [0.1], [zmoelnig@iem.at], [cpp-plugin], [https://github.com/umlaeute/cpp-plugin/])
AM_INIT_AUTOMAKE([1.10 foreign])
AC_CONFIG_MACRO_DIR([m4])

IEM_OPERATING_SYSTEM

#AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL


AC_LANG(C++)

AC_SEARCH_LIBS([dlopen], [dl])


AC_CONFIG_FILES([Makefile plugins/Makefile old/Makefile])
AC_OUTPUT
