AM_CPPFLAGS = -I../../../src/ADLib

lib_LTLIBRARIES = libMseom.la

libMseom_la_LDFLAGS = -no-undefined

libMseom_la_SOURCES = ../../../sample/Mseom/Mseom.cpp ../../../sample/Mseom/MseomMin.cpp = ../../../sample/Mseom/D_Mseom.cpp ../../../sample/Mseom/D_MseomMin.cpp ../../../sample/Mseom/Mseom_registration.cpp
libMseom_la_LIBADD = ../../../src/ADLib/adtR.lo ../../../src/ADLib/ts_optim.lo ../../../src/ADLib/adtmaths.lo ../../../src/ADLib/adtarrays.lo ../../../src/ADLib/adtdiff.lo ../../../src/ADLib/adtstack.lo ../../../src/ADLib/adtthreads.lo ../../../src/ADLib/adtparallel.lo -L$(R_LIB) -lR -lblas -lpthread

BUILT_SOURCES = ../../../sample/Mseom/D_Mseom.cpp ../../../sample/Mseom/D_MseomMin.cpp

../../../sample/Mseom/D_Mseom.cpp : ../../../sample/Mseom/Mseom.mk
	../../../sample/Mseom/run_mk Mseom.mk

../../../sample/Mseom/D_MseomMin.cpp : ../../../sample/Mseom/Mseom.mk
	../../../sample/Mseom/run_mk Mseom.mk

clean-local:
	-rm -f ../../../sample/Mseom/D_Mseom.cpp ../../../sample/Mseom/D_MseomMin.cpp ../../../sample/Mseom/Om_*.hpp ../../../sample/Mseom/OmB_*.hpp ../../../sample/Mseom/Mseom.dch
