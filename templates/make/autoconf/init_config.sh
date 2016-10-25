#! /bin/sh
# Shell script for setting up ADT skeleton project
libtoolize
autoreconf
automake --add-missing
autoreconf
