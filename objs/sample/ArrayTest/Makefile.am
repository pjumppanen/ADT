AM_CPPFLAGS = -I../../../src/ADLib

lib_LTLIBRARIES = libArrayTest.la

libArrayTest_la_LDFLAGS = -no-undefined

libArrayTest_la_SOURCES = ../../../sample/ArrayTest/ArrayTest.cpp ../../../sample/ArrayTest/R_ArrayTest.cpp ../../../sample/ArrayTest/ArrayTest_registration.cpp
libArrayTest_la_LIBADD = ../../../src/ADLib/adtR.lo ../../../src/ADLib/ts_optim.lo ../../../src/ADLib/adtmaths.lo ../../../src/ADLib/adtarrays.lo ../../../src/ADLib/adtdiff.lo ../../../src/ADLib/adtstack.lo ../../../src/ADLib/adtthreads.lo ../../../src/ADLib/adtparallel.lo -L$(R_LIB) -lR -lblas -lpthread

BUILT_SOURCES = ../../../sample/ArrayTest/R_ArrayTest.cpp

../../../sample/ArrayTest/R_ArrayTest.cpp : ../../../sample/ArrayTest/ArrayTest.mk
	../../../sample/ArrayTest/run_mk ArrayTest.mk

clean-local:
	-rm -f ../../../sample/ArrayTest/R_ArrayTest.cpp ../../../sample/ArrayTest/AT_*.hpp ../../../sample/ArrayTest/ArrayTest.dch
