// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------


#include "REDev.hpp"


// ----------------------------------------------------------------------------

REDev::REDev(
#include "Rd_constructor_args.hpp"
)
{
  #include "Rd_constructor_locals.hpp"
  #include "Rd_constructor_scalars_phase_1.hpp"
  #include "Rd_constructor_arrays_phase_1.hpp"
  #include "Rd_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

double REDev::rosenbrock(const ARRAY_1D X/*N*/)
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

// ----------------------------------------------------------------------------

double REDev::logLikelihood(const ARRAY_1D X/*N*/)
{
  double dLikelihood;

  dLikelihood = rosenbrock(X);

  return (dLikelihood);
}
