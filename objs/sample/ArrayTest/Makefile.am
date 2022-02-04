if WITH_TAPENADE
AM_CPPFLAGS = -I../../../src/ADLib

lib_LTLIBRARIES = libArrayTest.la

libArrayTest_la_LDFLAGS = -no-undefined

libArrayTest_la_SOURCES = ../../../sample/ArrayTest/ArrayTest.cpp ../../../sample/ArrayTest/R_ArrayTest.cpp ../../../sample/ArrayTest/ArrayTest_registration.cpp
libArrayTest_la_LIBADD = -L../../ADLib -lADLib -lADLibR -L$(R_LIB) -lR -lblas -lpthread

BUILT_SOURCES = ../../../sample/ArrayTest/R_ArrayTest.cpp

../../../sample/ArrayTest/R_ArrayTest.cpp : ../../../sample/ArrayTest/ArrayTest.mk
	../../../sample/ArrayTest/run_mk ArrayTest.mk

clean-local:
	-rm -f ../../../sample/ArrayTest/R_ArrayTest.cpp ../../../sample/ArrayTest/include/AT_*.hpp ../../../sample/ArrayTest/ArrayTest.dch
endif
