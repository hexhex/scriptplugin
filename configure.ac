
AC_PREREQ(2.59)

AC_INIT([dlvhex-scriptplugin],[0.0.1],[anton_korosec@hotmail.com])

AC_CONFIG_SRCDIR([src/scriptplugin.cpp])

# AC_CONFIG_HEADER([src/config.h])
AM_CONFIG_HEADER([src/config.h])

MAJOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/"`
MINOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/"`
MICRO=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/"`

AC_DEFINE_UNQUOTED([SCRIPTPLUGIN_MAJOR], [$MAJOR], [Major version number of the script-plugin])
AC_DEFINE_UNQUOTED([SCRIPTPLUGIN_MINOR], [$MINOR], [Minor version number of the script-plugin])
AC_DEFINE_UNQUOTED([SCRIPTPLUGIN_MICRO], [$MICRO], [Micro version number of the script-plugin])


AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL

#
# check for other libraries here
#

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 1.1])

#
# where the plugin will be installed by default.
# running configure will take sysplugindir from dlvhex.pc,
# running configure --enable-userinstall will take homeplugindir.
#

AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/`pkg-config dlvhex --variable=userplugindir`],
             [plugindir=`pkg-config dlvhex --variable=sysplugindir`]
             )
AC_SUBST([plugindir])

#
# all needed makefiles
#
AC_CONFIG_FILES([
           Makefile 
           src/Makefile
])

AC_OUTPUT
