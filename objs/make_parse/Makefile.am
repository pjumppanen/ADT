noinst_LIBRARIES = libmake_y.a libmake_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libmake_y_a_SOURCES = ../../src/make_y.y
libmake_l_a_SOURCES = ../../src/make_l.l

clean-local:
	-rm -f ../../src/make_l.c ../../src/make_y.c ../../src/make_y.h
