noinst_LIBRARIES = libblackbox_y.a libblackbox_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libblackbox_y_a_SOURCES = ../../src/black_box_y.y
libblackbox_l_a_SOURCES = ../../src/black_box_l.l

clean-local:
	-rm -f ../../src/blackbox_l.c ../../src/black_box_y.c ../../src/black_box_y.h
