// ----------------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
// bananna function generalised to N dimensions.
// ----------------------------------------------------------------------------

#ifndef __ROSENBROCK_HPP__
#define __ROSENBROCK_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------

class MinRosenbrock : public AdtArrays
{
protected:
  /* AD_LIBNAME Rosenbrock */
  /* AD_ALIAS Rb=D_MinRosenbrock */
  /* AUTOINIT */
  int     N;

#include "Rb_array_plans.hpp"

public:
  MinRosenbrock(
#include "Rb_constructor_args.hpp"
  );

  double  rosenbrock(const ARRAY_1D X/*N*/);
};

#endif  //__ROSENBROCK_HPP__
