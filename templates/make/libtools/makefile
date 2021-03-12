# $(libname) GNU makefile
CC=$(toolset-path)/gcc
CXX=$(toolset-path)/g++
FC=$(toolset-path)/gfortran
ifeq ($(DEBUG), 1)
  CodeGenFlags=-O0 -g -DDEBUG -D_DEBUG
else
  CodeGenFlags=-O2 -DNDEBUG
endif
COMMONFLAGS=$(CodeGenFlags) \
-I$(R_INCLUDE_PATH) \
-I./src \
-I./src/include \
-I$(adt-path)/include \
-I$(adt-path)/include/RMath
CFLAGS=$(COMMONFLAGS)
CXXFLAGS=$(COMMONFLAGS)
FFLAGS=$(COMMONFLAGS)
LDFLAGS=-shared
LDLIBS=-L$(AD_LIB) -lADLib.a -lADLibR.a -L$(R_LIB) -lR -lblas -lpthread
objects=D$(filename).o R$(filename).o RI$(filename).o $(filename).o $(filename)_registration.o

# Note - the whitespace on lines 25,28,31,34,37,40,43,46, and 49 must be a tab character
$(libname).$(lib-extension) : $(objects)
	$(CXX) -o $(libname).$(lib-extension) $(LDFLAGS) $(objects) $(LDLIBS)

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
	./src/run_mk $(filename).mk

src/RI$(filename).cpp : src/$(filename).mk
	./src/run_mk $(filename).mk

clean : 
	rm $(libname).$(lib-extension) $(objects) \
src/D$(filename).?pp src/RI$(filename).?pp src/$(filename)_reg_*.hpp src/$(filename).dch \
src/include/$(short-classname)_array_plans.hpp src/include/$(short-classname)_array_plans_copy.hpp src/include/$(short-classname)_array_plans_init.hpp \
src/include/$(short-classname)_constructor_args.hpp src/include/$(short-classname)_constructor_arrays_phase_*.hpp \
src/include/$(short-classname)_constructor_call_args.hpp src/include/$(short-classname)_constructor_locals.hpp \
src/include/$(short-classname)_constructor_scalars_phase_*.hpp src/include/$(short-classname)_decl_lib_interface_constructor.hpp \
src/include/$(short-classname)_decl_lib_interface_globals.hpp src/include/$(short-classname)_decl_lib_interface_methods.hpp \
src/include/$(short-classname)_impl_lib_interface_constructor.hpp src/include/$(short-classname)_impl_lib_interface_globals.hpp \
src/include/$(short-classname)_impl_lib_interface_methods.hpp src/include/$(short-classname)_impl_lib_registration.hpp \
src/include/R$(short-classname)_array_plans.hpp src/include/R$(short-classname)_array_plans_copy.hpp src/include/R$(short-classname)_array_plans_init.hpp \
src/include/R$(short-classname)_constructor_args.hpp src/include/R$(short-classname)_constructor_arrays_phase_*.hpp \
src/include/R$(short-classname)_constructor_call_args.hpp src/include/R$(short-classname)_constructor_locals.hpp \
src/include/R$(short-classname)_constructor_scalars_phase_*.hpp src/include/R$(short-classname)_decl_lib_interface_constructor.hpp \
src/include/R$(short-classname)_decl_lib_interface_globals.hpp src/include/R$(short-classname)_decl_lib_interface_methods.hpp \
src/include/R$(short-classname)_impl_lib_interface_constructor.hpp src/include/R$(short-classname)_impl_lib_interface_globals.hpp \
src/include/R$(short-classname)_impl_lib_interface_methods.hpp src/include/R$(short-classname)_impl_lib_registration.hpp \
src/R$(short-classname)_R_interface.r src/$(short-classname)_R_interface.r
