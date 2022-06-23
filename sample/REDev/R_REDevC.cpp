// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements the full random effects fitting process.
// ----------------------------------------------------------------------------


#include "R_REDevC.hpp"
#include <R_ext/Applic.h>


// ----------------------------------------------------------------------------
// R_MinRosenbrock method implementations
// ----------------------------------------------------------------------------
R_REDevC::R_REDevC(
#include "Dd_constructor_args.hpp"
)
 : DR_REDevB(
#include "Dd_constructor_call_args.hpp"
   )
{
  #include "Dd_constructor_locals.hpp"
  #include "Dd_constructor_scalars_phase_1.hpp"
  #include "Dd_constructor_arrays_phase_1.hpp"
  #include "Dd_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

R_REDevC::R_REDevC(const R_REDevC& rCopy)
 : DR_REDevB(rCopy)
#include "Dd_array_plans_copy.hpp"
{

}

// ----------------------------------------------------------------------------

R_REDevC::~R_REDevC()
{
  if (IsShallowCopy)
  {

  }
}

// ----------------------------------------------------------------------------

void R_REDevC::gradientLaplacePar(const ARRAY_1D re/* NR */, 
                                  const ARRAY_1D par/* NP */,
                                  ARRAY_1D pGrad/* NP */)
{
  int     cc;
  int     cr;
  double  dSum;
  double  rev;

  rev = 1.0;

  LAPLACE_BREPAR(re, LaplaceGradRE, par, LaplaceGradPar, rev);

  // We assume here that Cholesky is calculated already from above.
  matrixInverseFromChol(Cholesky, InvHessian, NR);

  for (cc = 1 ; cc <= NR ; cc++)
  {
    dSum = 0.0;

    for (cr = 1 ; cr <= NR ; cr++)
    {
      dSum += LaplaceGradRE[cr] * InvHessian[cc][cr];
    }

    TempRow[cc] = dSum;
  }


  for (cc = 1 ; cc <= NP ; cc++)
  {
    dSum = 0.0;

    for (cr = 1 ; cr <= NR ; cr++)
    {
      dSum += TempRow[cr] * ReParXCovar[cr][cc];
    }

    pGrad[cc] = LaplaceGradPar[cc] - dSum;
  }
}

// ----------------------------------------------------------------------------

void R_REDevC::solveAndGradientLaplacePar(const ARRAY_1D par/* NP */,
                                          ARRAY_1D pGrad/* NP */)
{
  solveInner(par);
  gradientLaplacePar(ReHat, par, pGrad);
}                                          
