AUTOMAKE_OPTIONS = foreign

plugin_LTLIBRARIES = libdlvhexscript.la

libdlvhexscript_la_SOURCES = scriptplugin.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(DLVHEX_CFLAGS)

libdlvhexscript_la_LDFLAGS = -avoid-version -module

