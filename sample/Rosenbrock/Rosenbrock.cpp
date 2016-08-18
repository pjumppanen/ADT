// ----------------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
// bananna function generalised to N dimensions.
// ----------------------------------------------------------------------------


#include "Rosenbrock.hpp"


// ----------------------------------------------------------------------------

MinRosenbrock::MinRosenbrock(
#include "Rb_constructor_args.hpp"
)
{
  #include "Rb_constructor_locals.hpp"
  #include "Rb_constructor_scalars_phase_1.hpp"
  #include "Rb_constructor_arrays_phase_1.hpp"
  #include "Rb_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

double MinRosenbrock::rosenbrock(const ARRAY_1D X/*N*/)
{
  int cn;
  double dSum;
  double p1,p2,f1,f2;

  dSum = 0.0;

  for (cn = 1 ; cn <= N / 2 ; cn++)
  {
    p1 = X[2 * cn - 1];
    p2 = X[2 * cn];
    f1 = (p1 * p1 - p2);
    f1 = 100 * f1 * f1;
    f2 = (p1 - 1.0);
    f2 = f2 * f2;

    dSum += f1 + f2;
  }

  return (dSum);
}
