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
  ARRAY_1D  y/* N */;
  int       N;
  int       NR; // total number of random effects
  int       NP; // total number of parameters

  /* AUTODEC */
  ARRAY_1D  par_u/* N */;
  double    par_logr0;
  double    par_logtheta;
  double    par_logK;
  double    par_logQ;
  double    par_logR;

#include "Rd_array_plans.hpp"

private:
  double    dlognorm(const double x, 
                     const double mean,
                     const double sigma);

  double    thetalogLikelihood(const ARRAY_1D u/* N */,
                               const double logr0,
                               const double logtheta,
                               const double logK,
                               const double logQ,
                               const double logR);

public:
  REDev(
#include "Rd_constructor_args.hpp"
  );

  double    logLikelihood(const ARRAY_1D re/* NR */, const ARRAY_1D par/* NP */); // note that NR is N and NP is 5 in this case 

  void      choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pL/* nSize, nSize */, const int nSize);
  double    logDeterminantFromChol(const ARRAY_2D pL/* nSize, nSize */, const int nSize);
  void      matrixInverseFromChol(const ARRAY_2D pL/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize);
};

#endif  //__REDEV_HPP__
