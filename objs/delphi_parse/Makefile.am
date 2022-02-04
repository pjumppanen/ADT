noinst_LIBRARIES = libdelphi_y.a libdelphi_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d
AM_LFLAGS = -i

libdelphi_y_a_SOURCES = ../../src/delphi_y.y
libdelphi_l_a_SOURCES = ../../src/delphi_l.l

clean-local:
	-rm -f ../../src/delphi_l.c ../../src/delphi_y.c ../../src/delphi_y.h
