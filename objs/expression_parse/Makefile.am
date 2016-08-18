noinst_LIBRARIES = libexpression_y.a libexpression_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libexpression_y_a_SOURCES = ../../src/expression_y.y
libexpression_l_a_SOURCES = ../../src/expression_l.l

clean-local:
	-rm -f expression_l.c expression_y.c expression_y.h
