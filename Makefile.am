AUTOMAKE_OPTIONS = gnu 1.10

ACLOCAL_AMFLAGS = -I m4

# setup doxygen for automake use
include doxygen.am

html-local: doc/dlvhex-scriptplugin.tag
	make doxygen-doc

install-html-local:
	install -d $(DESTDIR)/$(docdir)
	cp -rv $(top_builddir)/doc/html $(DESTDIR)/$(docdir)

uninstall-local:
	test -d $(DESTDIR)/$(docdir)/html || exit 0; \
	cd $(DESTDIR)/$(docdir) && rm -rf html


SUBDIRS = \
	src \
	include \
	examples \
  testsuite

EXTRA_DIST = \
    doxygen.am \
    doxygen.cfg

MOSTLYCLEANFILES = $(DX_CLEANFILES)

