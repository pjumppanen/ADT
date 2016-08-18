lib_LTLIBRARIES = libADLib.la libADLibR.la libADLibErr.la

AM_CPPFLAGS = -I../../src/ADLib

libADLib_la_LDFLAGS = -no-undefined

libADLib_la_SOURCES = ../../src/ADLib/adtmaths.cpp ../../src/ADLib/adtarrays.cpp ../../src/ADLib/adtdiff.cpp ../../src/ADLib/adtstack.cpp ../../src/ADLib/adtthreads.cpp ../../src/ADLib/adtparallel.cpp
libADLib_la_include_HEADERS = ../../src/ADLib/adtmaths.hpp ../../src/ADLib/adtarrays.hpp ../../src/ADLib/adtdiff.hpp ../../src/ADLib/adtstack.hpp ../../src/ADLib/adtthreads.hpp ../../src/ADLib/adtparallel.hpp
libADLib_la_includedir = $(includedir)
libADLib_la_LIBADD = -L$(R_LIB) -lR -lblas -lpthread

libADLibR_la_LDFLAGS = -no-undefined

libADLibR_la_SOURCES = ../../src/ADLib/adtR.cpp ../../src/ADLib/ts_optim.cpp
libADLibR_la_include_HEADERS = ../../src/ADLib/adtR.hpp ../../src/ADLib/ts_lbfgsb.cpp
libADLibR_la_includedir = $(includedir)
libADLibR_la_LIBADD = libADLib.la -L$(R_LIB) -lR -lblas -lpthread

libADLibErr_la_LDFLAGS = -no-undefined

libADLibErr_la_SOURCES = ../../src/ADLib/adterror.cpp
libADLibErr_la_includedir = $(includedir)
