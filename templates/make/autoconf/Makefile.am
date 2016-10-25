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
	rm -f $(short-classname)_array_plans.hpp $(short-classname)_array_plans_copy.hpp $(short-classname)_array_plans_init.hpp $(short-classname)_constructor_args.hpp && \
	rm -f $(short-classname)_constructor_arrays_phase_*.hpp $(short-classname)_constructor_call_args.hpp $(short-classname)_constructor_locals.hpp && \
	rm -f $(short-classname)_constructor_scalars_phase_*.hpp $(short-classname)_decl_lib_interface_constructor.hpp $(short-classname)_decl_lib_interface_globals.hpp && \
	rm -f $(short-classname)_decl_lib_interface_methods.hpp $(short-classname)_impl_lib_interface_constructor.hpp $(short-classname)_impl_lib_interface_globals.hpp && \
	rm -f $(short-classname)_impl_lib_interface_methods.hpp $(short-classname)_impl_lib_registration.hpp R$(short-classname)_array_plans.hpp && \
	rm -f R$(short-classname)_array_plans_copy.hpp R$(short-classname)_array_plans_init.hpp R$(short-classname)_constructor_args.hpp && \
	rm -f R$(short-classname)_constructor_arrays_phase_*.hpp R$(short-classname)_constructor_call_args.hpp R$(short-classname)_constructor_locals.hpp && \
	rm -f R$(short-classname)_constructor_scalars_phase_*.hpp R$(short-classname)_decl_lib_interface_constructor.hpp R$(short-classname)_decl_lib_interface_globals.hpp && \
	rm -f R$(short-classname)_decl_lib_interface_methods.hpp R$(short-classname)_impl_lib_interface_constructor.hpp R$(short-classname)_impl_lib_interface_globals.hpp && \
	rm -f R$(short-classname)_impl_lib_interface_methods.hpp R$(short-classname)_impl_lib_registration.hpp
