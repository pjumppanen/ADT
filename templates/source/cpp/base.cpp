// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------


#include "$(filename).hpp"
#include <R.h>


// ----------------------------------------------------------------------------


$(classname)::$(classname)(
#include "include/$(short-classname)_constructor_args.hpp"
)
 : AdtArrays()
{
  #include "include/$(short-classname)_constructor_locals.hpp"
  #include "include/$(short-classname)_constructor_scalars_phase_1.hpp"
  #include "include/$(short-classname)_constructor_arrays_phase_1.hpp"
  #include "include/$(short-classname)_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

$(classname)::~$(classname)()
{

}
