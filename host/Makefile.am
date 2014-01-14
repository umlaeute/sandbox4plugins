AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I$(top_srcdir)/m4

bin_PROGRAMS = pluginhost
pluginhost_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
pluginhost_CPPFLAGS = -DINTERNAL
pluginhost_LDFLAGS  = -export-dynamic
