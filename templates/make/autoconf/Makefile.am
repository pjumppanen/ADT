# $(libname) makefile
dist_doc_DATA = INSTALL README ChangeLog

lib_LTLIBRARIES = lib$(libname).la

lib$(libname)_la_LDFLAGS = -no-undefined

lib$(libname)_la_SOURCES = src/$(filename).cpp src/D$(filename).cpp src/R$(filename).cpp src/RI$(filename).cpp src/$(filename)_registration.cpp
lib$(libname)_la_LIBADD = -L$(libdir) -lADLib -lADLibR -L$(R_LIB) -lR -lblas -lpthread

BUILT_SOURCES = src/D$(filename).cpp src/RI$(filename).cpp

src/D$(filename).cpp : src/$(filename).mk
	src/run_mk $(filename).mk

src/RI$(filename).cpp : src/$(filename).mk
	src/run_mk $(filename).mk

clean-local:
	-rm -f src/D$(filename).cpp src/RI$(filename).cpp src/$(filename)_reg_*.hpp src/$(filename).dch && \
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
