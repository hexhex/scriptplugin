AC_PREREQ([2.61])
AC_INIT([dlvhex-scriptplugin],[2.0.0],[dlvhex-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR([src/ScriptPlugin.cpp])
AC_CONFIG_HEADERS([src/config.h])

# for documentation of the versioning scheme see
# https://sourceforge.net/apps/trac/dlvhex/wiki/LibraryVersions
DLVHEX_DEFINE_VERSION([SCRIPTPLUGIN],[$PACKAGE_VERSION])
DLVHEX_DEFINE_VERSION([DLVHEX_ABI],[7.0.0])

AM_INIT_AUTOMAKE

AC_CANONICAL_HOST

# by default we look into /opt/local and /sw for include files (macports vs. fink)
case $host_os in
     darwin*|macosx*)
        CPPFLAGS="$CPPFLAGS -I/opt/local/include -I/sw/include"
     ;;
esac


# Checks for programs.
AC_PROG_CXX
AC_LANG([C++])

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC # we don't need a static lbrary
AC_PROG_LIBTOOL

#
# check for other libraries here
#

# check for dlvhex, sets various variables
DLVHEX_REQUIRE([2.0.0])

# checking for boost libs
BOOST_REQUIRE([1.41.0])
BOOST_SMART_PTR
BOOST_STRING_ALGO
BOOST_TOKENIZER

# where the plugin will be installed by default.
# running configure will take sysplugindir from dlvhex.pc,
# running configure --enable-userinstall will take homeplugindir.
AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/$DLVHEX_USERPLUGINDIR],
             [plugindir=$DLVHEX_SYSPLUGINDIR]
             )
AC_SUBST([plugindir])
if test "x$plugindir" == "x"; then
	AC_MSG_ERROR([Cannot determine nonempty value for plugindir!])
fi

#
# doxygen stuff
#
# these are the defaults, can be overridden by --enable-doxygen-...
DX_HTML_FEATURE([ON])
DX_CHM_FEATURE([OFF])
DX_CHI_FEATURE([OFF])
DX_MAN_FEATURE([OFF])
DX_RTF_FEATURE([OFF])
DX_XML_FEATURE([OFF])
DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([dlvhex-scriptplugin], [doxygen.cfg], [doc])

#
# check for python, perl, and bash (we need their paths)
#
AC_PATH_PROG(PYTHON,[python], [AC_MSG_ERROR([Cannot find python!])])
AC_PATH_PROG(PERL,[perl], [AC_MSG_ERROR([Cannot find perl!])])
AC_PATH_PROG(BASH,[bash], [AC_MSG_ERROR([Cannot find bash!])])

#
# all needed makefiles
#
AC_CONFIG_FILES([
  Makefile 
  src/Makefile
  include/Makefile
  examples/Makefile
  examples/tests/scriptplugin.test
  examples/example1/script.pl
  examples/example1/script.py
  examples/example1/script.sh
  examples/example2/int.py
  examples/example2/int.sh
  examples/example3/conv1.py
  examples/example3/ls.hex
  examples/example4/conv2.sh
  examples/example7/rename.py
  examples/example10/scripterror.sh
  examples/example12/converter.sh
  testsuite/Makefile
],
[
  chmod a+x examples/example1/script.pl
  chmod a+x examples/example1/script.py
  chmod a+x examples/example1/script.sh
  chmod a+x examples/example2/int.py
  chmod a+x examples/example2/int.sh
  chmod a+x examples/example3/conv1.py
  chmod a+x examples/example4/conv2.sh
  chmod a+x examples/example7/rename.py
  chmod a+x examples/example10/scripterror.sh
  chmod a+x examples/example12/converter.sh
])

AC_OUTPUT

dnl output configuration
cat <<EOF
 
$PACKAGE_TARNAME $PACKAGE_VERSION configuration:

 - Compiler settings
 CC: $CC
 CXX: $CXX
 CFLAGS: $CFLAGS
 CPPFLAGS: $CPPFLAGS
 CXXFLAGS: $CXXFLAGS
 LDFLAGS: $LDFLAGS

 - from pkg-config
 DLVHEX_CFLAGS: $DLVHEX_CFLAGS
 DLVHEX_LIBS: $DLVHEX_LIBS
 DLVHEX_BINDIR: $DLVHEX_BINDIR
 
 - Path settings
 prefix: $prefix
 plugindir: $plugindir
 python: $PYTHON
 perl: $PERL
 bash: $BASH
EOF
