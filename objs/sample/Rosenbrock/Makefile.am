AM_CPPFLAGS = -I../../../src/ADLib

lib_LTLIBRARIES = libRosenbrock.la

libRosenbrock_la_LDFLAGS = -no-undefined

libRosenbrock_la_SOURCES = ../../../sample/Rosenbrock/Rosenbrock.cpp ../../../sample/Rosenbrock/d_Rosenbrock.cpp ../../../sample/Rosenbrock/R_Rosenbrock.cpp ../../../sample/Rosenbrock/dR_Rosenbrock.cpp ../../../sample/Rosenbrock/registration.cpp
libRosenbrock_la_LIBADD = -L../../ADLib -lADLib -lADLibR -L$(R_LIB) -lR -lblas -lpthread

if WITH_TAPENADE
BUILT_SOURCES = ../../../sample/Rosenbrock/d_Rosenbrock.cpp ../../../sample/Rosenbrock/dR_Rosenbrock.cpp

../../../sample/Rosenbrock/d_Rosenbrock.cpp : ../../../sample/Rosenbrock/Rosenbrock.mk
	../../../sample/Rosenbrock/run_mk Rosenbrock.mk

../../../sample/Rosenbrock/dR_Rosenbrock.cpp : ../../../sample/Rosenbrock/Rosenbrock.mk
	../../../sample/Rosenbrock/run_mk Rosenbrock.mk

clean-local:
	-rm -f ../../../sample/Rosenbrock/d_Rosenbrock.cpp ../../../sample/Rosenbrock/dR_Rosenbrock.cpp ../../../sample/Rosenbrock/Rb_*.hpp ../../../sample/Rosenbrock/RRb_*.hpp ../../../sample/Rosenbrock/Rosenbrock.dch
endif
