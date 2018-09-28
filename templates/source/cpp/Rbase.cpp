// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------


#include "R$(filename).hpp"


// ----------------------------------------------------------------------------

R$(classname)::R$(classname)(
#include "include/R$(short-classname)_constructor_args.hpp"
)
 : D$(classname)(
#include "include/R$(short-classname)_constructor_call_args.hpp"
)
{
  #include "include/R$(short-classname)_constructor_locals.hpp"
  #include "include/R$(short-classname)_constructor_scalars_phase_1.hpp"
  #include "include/R$(short-classname)_constructor_arrays_phase_1.hpp"
  #include "include/R$(short-classname)_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

R$(classname)::~R$(classname)()
{

}
