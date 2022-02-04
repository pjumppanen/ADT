noinst_LIBRARIES = libexpression_y.a libexpression_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libexpression_y_a_SOURCES = ../../src/expression_y.y
libexpression_l_a_SOURCES = ../../src/expression_l.l

clean-local:
	-rm -f ../../src/expression_l.c ../../src/expression_y.c ../../src/expression_y.h
