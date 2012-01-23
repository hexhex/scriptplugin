EXTRA_DIST = \
  run-dlvhex-tests.sh \
  answerset_compare.py

# run the test script
TESTS = run-dlvhex-tests.sh

# some variables for the test-script
TESTS_ENVIRONMENT = \
	TOP_SRCDIR=$(top_srcdir) \
	DLVHEX="$(DLVHEX_BINDIR)/dlvhex2 -s --plugindir=!$(top_builddir)/src " \
	EXAMPLESDIR=$(top_srcdir)/examples \
	TESTS=$(top_builddir)/examples/tests/scriptplugin.test \
	OUTDIR=$(top_srcdir)/examples/tests

