# $(libname) GNU makefile
CC=gcc
CXX=g++
FC=gfortran
COMMONFLAGS=-O0\
-g\
-DDEBUG\
-D_DEBUG\
-I$(R_INCLUDE_PATH)\
-I./include\
-I$(adt-path)/include\
-I$(adt-path)/include/RMath
CFLAGS=$(COMMONFLAGS)
CXXFLAGS=$(COMMONFLAGS)
FFLAGS=$(COMMONFLAGS)
LDFLAGS=-shared
LDLIBS=-L$(AD_LIB) -lADLib -lADLibR -L$(R_LIB) -lR -lblas -lpthread
objects=$(filename).o D$(filename).o R$(filename).o RI$(filename).o $(filename)_registration.o

$(libname).dll : $(objects)
	$(CXX) -o $(libname).dll $(LDFLAGS) $(objects) $(LDLIBS)

$(filename).o : src/$(filename).cpp
	$(CXX) -c $(CXXFLAGS) src/$(filename).cpp

D$(filename).o : src/D$(filename).cpp
	$(CXX) -c $(CXXFLAGS) src/D$(filename).cpp

R$(filename).o : src/R$(filename).cpp
	$(CXX) -c $(CXXFLAGS) src/R$(filename).cpp

RI$(filename).o : src/RI$(filename).cpp
	$(CXX) -c $(CXXFLAGS) src/RI$(filename).cpp

$(filename)_registration.o : src/$(filename)_registration.cpp
	$(CXX) -c $(CXXFLAGS) src/$(filename)_registration.cpp

src/D$(filename).cpp : src/$(filename).mk
	run_mk $(filename).mk

src/RI$(filename).cpp : src/$(filename).mk
	run_mk $(filename).mk

clean : 
	rm $(libname).dll $(objects) && \
rm -f src/D$(filename).cpp src/RI$(filename).cpp src/$(filename)_reg_*.hpp sr/$(filename).dch && \
rm -f src/include/$(short-classname)_array_plans.hpp src/include/$(short-classname)_array_plans_copy.hpp src/include/$(short-classname)_array_plans_init.hpp && \
rm -f src/include/$(short-classname)_constructor_args.hpp src/include/$(short-classname)_constructor_arrays_phase_*.hpp && \
rm -f src/include/$(short-classname)_constructor_call_args.hpp src/include/$(short-classname)_constructor_locals.hpp && \
rm -f src/include/$(short-classname)_constructor_scalars_phase_*.hpp src/include/$(short-classname)_decl_lib_interface_constructor.hpp && \
rm -f src/include/$(short-classname)_decl_lib_interface_globals.hpp src/include/$(short-classname)_decl_lib_interface_methods.hpp && \
rm -f src/include/$(short-classname)_impl_lib_interface_constructor.hpp src/include/$(short-classname)_impl_lib_interface_globals.hpp && \
rm -f src/include/$(short-classname)_impl_lib_interface_methods.hpp src/include/$(short-classname)_impl_lib_registration.hpp && \
rm -f src/include/R$(short-classname)_array_plans.hpp src/include/R$(short-classname)_array_plans_copy.hpp src/include/R$(short-classname)_array_plans_init.hpp && \
rm -f src/include/R$(short-classname)_constructor_args.hpp src/include/R$(short-classname)_constructor_arrays_phase_*.hpp && \
rm -f src/include/R$(short-classname)_constructor_call_args.hpp src/include/R$(short-classname)_constructor_locals.hpp && \
rm -f src/include/R$(short-classname)_constructor_scalars_phase_*.hpp src/include/R$(short-classname)_decl_lib_interface_constructor.hpp && \
rm -f src/include/R$(short-classname)_decl_lib_interface_globals.hpp src/include/R$(short-classname)_decl_lib_interface_methods.hpp && \
rm -f src/include/R$(short-classname)_impl_lib_interface_constructor.hpp src/include/R$(short-classname)_impl_lib_interface_globals.hpp && \
rm -f src/include/R$(short-classname)_impl_lib_interface_methods.hpp src/include/R$(short-classname)_impl_lib_registration.hpp
