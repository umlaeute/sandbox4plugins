AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I$(top_srcdir)/m4

bin_PROGRAMS = pluginhost legacyhost
pluginhost_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
pluginhost_CPPFLAGS = -DINTERNAL -I$(top_srcdir)/include
pluginhost_LDFLAGS  = -export-dynamic

legacyhost_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
legacyhost_CPPFLAGS = -DPLUGINHOST_LEGACY -DINTERNAL -I$(top_srcdir)/legacy -I$(top_srcdir)/include
legacyhost_LDFLAGS  = -export-dynamic
