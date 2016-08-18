noinst_LIBRARIES = libfortran_y.a libfortran_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libfortran_y_a_SOURCES = ../../src/fortran_y.y
libfortran_l_a_SOURCES = ../../src/fortran_l.l

clean-local:
	-rm -f fortran_l.c fortran_y.c fortran_y.h
