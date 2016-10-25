// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------

#ifndef __R$(filename)_HPP__
#define __R$(filename)_HPP__


#include "D$(filename).hpp"


// ----------------------------------------------------------------------------

class R$(classname) : public D$(classname)
{
protected:
  /* AD_LIBNAME $(libname) */
  /* AD_ALIAS R$(short-classname)=RI$(classname), D$(classname) */
  /* AUTOINIT */
  /* AUTODEC */

#include "R$(short-classname)_array_plans.hpp"

public:
  R$(classname)(
#include "R$(short-classname)_constructor_args.hpp"
  );

  virtual ~R$(classname)();

};


#endif  //__R$(filename)_HPP__
