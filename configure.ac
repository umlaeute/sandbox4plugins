AC_PREREQ([2.60])
AC_INIT([cpp-plugins], [0.1], [zmoelnig@iem.at], [cpp-plugin], [https://github.com/umlaeute/cpp-plugin/])
AM_INIT_AUTOMAKE([1.10 foreign])
AC_CONFIG_MACRO_DIR([m4])

IEM_OPERATING_SYSTEM

#AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_SUBST([HOST_CPPFLAGS])
AC_SUBST([HOST_CFLAGS])
AC_SUBST([HOST_CXXFLAGS])
AC_SUBST([HOST_LDFLAGS])
HOST_CPPFLAGS="-DINTERNAL"
HOST_CFLAGS=""
HOST_CXXFLAGS=""
HOST_LDFLAGS="-export-dynamic"


AC_LANG(C++)

AC_SEARCH_LIBS([dlopen], [dl])


AC_CONFIG_FILES([Makefile host/Makefile plugins/Makefile legacy/Makefile])




if test "x${WINDOWS}" = "xyes"; then
  HOST_CFLAGS="${HOST_CFLAGS} -mms-bitfields"
  HOST_CXXFLAGS="${HOST_CXXFLAGS} -mms-bitfields"
  HOST_LDFLAGS="${HOST_LDFLAGS} -mms-bitfields"
  HOST_LDFLAGS="${HOST_LDFLAGS} -static-libgcc"
  HOST_LDFLAGS="${HOST_LDFLAGS} -static-libstdc++"
fi



AC_OUTPUT
