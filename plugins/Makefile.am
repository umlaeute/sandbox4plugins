AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS   =
AM_CXXFLAGS =
#AM_LIBADD   = -L$(top_builddir)
AM_LDFLAGS  = -module -avoid-version -shared

if WINDOWS
AM_LDFLAGS += -no-undefined
endif

pkglib_LTLIBRARIES= simple.la

### SOURCES
simple_la_SOURCES= simple.cc simple.hh

