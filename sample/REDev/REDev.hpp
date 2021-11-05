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
  ARRAY_2D  A/*N2,N1*/;
  ARRAY_2D  B/*N3,N1*/;
  int       N1;
  int       N2;
  int       N3;

  ARRAY_1D  y/* N */;
  int       N;
  int       NR; // total number of random effects
  int       NP; // total number of parameters

  /* AUTODEC */
  ARRAY_1D  par_u/* NP */;
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

  double    simpleLogLikelihood(const ARRAY_1D x/*N1*/, 
                                const ARRAY_1D u/*N3*/,
                                const ARRAY_1D beta/*N2*/,
                                const double logsdu,
                                const double logsd0);

public:
  REDev(
#include "Rd_constructor_args.hpp"
  );

  double    logLikelihood(const ARRAY_1D re/* NR */, const ARRAY_1D par/* NP */); // note that NR is N and NP is 5 in this case 

  void      choleskyDecomposition(const ARRAY_2D pA/* NR,NR */, ARRAY_2D pL/* NR,NR */);
  double    logDeterminant(const ARRAY_2D pA/* NR,NR */, ARRAY_2D pL/* NR,NR */);
};

#endif  //__REDEV_HPP__
