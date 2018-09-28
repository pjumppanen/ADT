// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------

#ifndef __$(filename)_HPP__
#define __$(filename)_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------

class $(classname) : public AdtArrays
{
protected:
  /* AD_LIBNAME $(libname) */
  /* AD_ALIAS $(short-classname)=D$(classname) */
  /* AUTOINIT */
  /* AUTODEC */

#include "include/$(short-classname)_array_plans.hpp"

public:
  $(classname)(
#include "include/$(short-classname)_constructor_args.hpp"
  );

  virtual ~$(classname)();

};


#endif  //__$(filename)_HPP__
