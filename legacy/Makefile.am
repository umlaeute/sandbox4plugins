AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir)/include
AM_CFLAGS   =
AM_CXXFLAGS =
#AM_LIBADD   = -L$(top_builddir)
AM_LDFLAGS  = -module -avoid-version -shared

if WINDOWS
AM_LDFLAGS += -no-undefined
endif

pkglib_LTLIBRARIES= pluginC.la pluginCC.la

### SOURCES
pluginC_la_SOURCES= pluginC.c
pluginCC_la_SOURCES= pluginCC.cc

