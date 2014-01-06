AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

SUBDIRS=plugins

bin_PROGRAMS = host
host_SOURCES = main.cc \
	dylib.cc \
	exception.cc \
	pluginfactory.cc plugin.cc
host_CPPFLAGS = -DINTERN