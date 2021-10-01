// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------

#ifndef __REDEV_HPP__
#define __REDEV_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------

class REDev : public AdtArrays
{
protected:
  /* AD_LIBNAME REDev */
  /* AD_ALIAS Rd=D_REDev */
  /* AUTOINIT */
  int     N;

#include "Rd_array_plans.hpp"

private:
  double  rosenbrock(const ARRAY_1D X/*N*/);
  
public:
  REDev(
#include "Rd_constructor_args.hpp"
  );

  double  logLikelihood(const ARRAY_1D X/*N*/);
};

#endif  //__REDEV_HPP__
