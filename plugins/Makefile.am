AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS   =
AM_CXXFLAGS =
AM_LDFLAGS  = -module -avoid-version -shared

if WINDOWS
AM_LDFLAGS += -no-undefined
AM_LDFLAGS += -Xlinker "$(top_builddir)/host/pluginhost.lib"
endif

pkglib_LTLIBRARIES= pluginC_0.la pluginCC_1.la pluginC_1.la pluginCC_2.la

### SOURCES
pluginC_0_la_SOURCES  = pluginC_0.c

pluginCC_1_la_SOURCES = pluginCC_1.cc

pluginC_1_la_SOURCES  = pluginC_1.c

pluginCC_2_la_SOURCES = pluginCC_2.cc
