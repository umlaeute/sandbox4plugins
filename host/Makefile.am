AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I$(top_srcdir)/m4

bin_PROGRAMS = pluginhost legacyhost

pluginhost_CPPFLAGS = @HOST_CPPFLAGS@ 
pluginhost_CFLAGS   = @HOST_CFLAGS@
pluginhost_CXXFLAGS = @HOST_CXXFLAGS@
pluginhost_LDFLAGS  = @HOST_LDFLAGS@

legacyhost_CPPFLAGS = @HOST_CPPFLAGS@
legacyhost_CFLAGS   = @HOST_CFLAGS@
legacyhost_CXXFLAGS = @HOST_CXXFLAGS@
legacyhost_LDFLAGS  = @HOST_LDFLAGS@

pluginhost_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
pluginhost_CPPFLAGS += -I$(top_srcdir)/include
pluginhost_LDFLAGS  += -Wl,--out-implib,pluginhost.lib

legacyhost_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
legacyhost_CPPFLAGS += -DPLUGINHOST_LEGACY -I$(top_srcdir)/legacy -I$(top_srcdir)/include
legacyhost_LDFLAGS  += -Wl,--out-implib,legacyhost.lib

