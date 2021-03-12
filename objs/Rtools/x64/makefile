# GNU makefile to make ADLib, ADLibErr and ADLibR static libraries for libtools environments
CC=gcc
CXX=g++
FC=gfortran
R_INCLUDE_PATH=../../../src/RMath/include
SRC_PATH=../../../src/ADLib
COMMONFLAGS=-O2\
-DNDEBUG\
-fPIC\
-I$(R_INCLUDE_PATH)
CFLAGS=$(COMMONFLAGS)
CXXFLAGS=$(COMMONFLAGS)
FFLAGS=$(COMMONFLAGS)
ADLib_objects=adtarrays.o adtdiff.o adtmaths.o adtparallel.o adtstack.o adtthreads.o
ADLibErr_objects=adterror.o
ADLibR_objects=adtR.o ts_optim.o

Libs : libADLib.a libADLibErr.a libADLibR.a 

libADLib.a : $(ADLib_objects)
	ar rcs libADLib.a $(ADLib_objects)

libADLibErr.a : $(ADLibErr_objects)
	ar rcs libADLibErr.a $(ADLibErr_objects)

libADLibR.a : $(ADLibR_objects)
	ar rcs libADLibR.a $(ADLibR_objects)

adtarrays.o : $(SRC_PATH)/adtarrays.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtarrays.cpp

adtdiff.o : $(SRC_PATH)/adtdiff.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtdiff.cpp

adtmaths.o : $(SRC_PATH)/adtmaths.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtmaths.cpp

adtparallel.o : $(SRC_PATH)/adtparallel.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtparallel.cpp

adtstack.o : $(SRC_PATH)/adtstack.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtstack.cpp

adtthreads.o : $(SRC_PATH)/adtthreads.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adtthreads.cpp

adterror.o : $(SRC_PATH)/adterror.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/adterror.cpp

adtR.o : $(SRC_PATH)/adtR.cpp
	$(CXX) -c -DRMATH_DLL $(CXXFLAGS) $(SRC_PATH)/adtR.cpp

ts_optim.o : $(SRC_PATH)/ts_optim.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC_PATH)/ts_optim.cpp


clean : 
	rm libADLib.a libADLibErr.a libADLibR.a $(ADLib_objects) $(ADLibErr_objects) $(ADLibR_objects)
