noinst_LIBRARIES = libcpp_y.a libcpp_l.a

AM_CPPFLAGS = -I../../src

AM_YFLAGS = -d

libcpp_y_a_SOURCES = ../../src/cpp_y.y
libcpp_l_a_SOURCES = ../../src/cpp_l.l

clean-local:
	-rm -f cpp_l.c cpp_y.c cpp_y.h
