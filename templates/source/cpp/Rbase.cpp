// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------


#include "R$(filename).hpp"


// ----------------------------------------------------------------------------

R$(classname)::R$(classname)(
#include "R$(short-classname)_constructor_args.hpp"
)
 : D$(classname)(
#include "R$(short-classname)_constructor_call_args.hpp"
)
{
  #include "R$(short-classname)_constructor_locals.hpp"
  #include "R$(short-classname)_constructor_scalars_phase_1.hpp"
  #include "R$(short-classname)_constructor_arrays_phase_1.hpp"
  #include "R$(short-classname)_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

R$(classname)::~R$(classname)()
{

}
