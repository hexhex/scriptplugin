EXTRA_DIST = ls.hex \
		 lsdir/file1 \
		 lsdir/file2 \
		 lsdir/file3 \
	     example1/script.hex \
	     example1/script.pl \
	     example1/script.py \
	     example1/script.sh \
	     example2/int.hex \
	     example2/int.py \
	     example2/int.sh \
	     example3/conv1.py \
	     example4/conv2.hex \
	     example4/conv2.sh \
	     example5/family.hex \
	     example5/family.py \
	     example5/family.txt \
	     example6/day_of_week.hex \
	     example6/day_of_week.py \
	     example7/input.hex \
	     example7/rename.py \
	     example8/query.hex \
	     example8/query.py \
	     tests/dlvhextests.test \
	     tests/example1.out \
	     tests/example2.out \
	     tests/example3.out \
	     tests/example4.out \
	     tests/example5.out \
	     tests/example6.out \
	     tests/example7.out \
	     tests/example8.out \
		 ../testsuite/run-dlvhex-tests.sh \
		 ../testsuite/answerset_compare.py
		 
# run the test script
TESTS = $(top_srcdir)/testsuite/run-dlvhex-tests.sh

# some variables for the test-script
TESTS_ENVIRONMENT = \
	TOP_SRCDIR=$(top_srcdir) \
	DLVHEX="$(DLVHEX_BINDIR)/dlvhex -s --plugindir=$(top_builddir)/src --verbose=255" \
	EXAMPLESDIR=$(top_srcdir)/examples \
	TESTDIR=$(top_srcdir)/examples/tests 


