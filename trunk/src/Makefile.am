AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexscript.la

libdlvhexscript_la_SOURCES = ScriptPlugin.cpp \
                             ScriptAtom.cpp \
                             ScriptConverter.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
        $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexscript_la_LDFLAGS = -avoid-version -module

