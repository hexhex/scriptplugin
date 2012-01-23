plugin_LTLIBRARIES = libdlvhexplugin-script.la

libdlvhexplugin_script_la_SOURCES = \
  ScriptPlugin.cpp \
  ScriptAtom.cpp \
  ScriptConverter.cpp \
  ScriptProcess.cpp

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
  $(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_script_la_LDFLAGS = -avoid-version -module

