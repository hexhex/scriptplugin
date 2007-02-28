#!/bin/sh

echo "libtoolize..."
libtoolize --force \
    || { echo "libtoolize failed"; exit 1; }

echo "aclocal..."
# use this if you have additional files in the m4 directory:
#aclocal -I m4
aclocal \
    || { echo "aclocal failed"; exit 1; }

echo "autoheader..."
autoheader --warnings=all \
    || { echo "autoheader failed"; exit 1; }

echo "automake..."
automake --foreign --add-missing \
    || { echo "automake failed"; exit 1; }

echo "autoconf..."
autoconf --warnings=all \
    || { echo "autoconf failed"; exit 1; }
