// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements the full random effects fitting process.
// ----------------------------------------------------------------------------


#ifndef __R_REDEVC_HPP__
#define __R_REDEVC_HPP__


#include "dR_REDevB.hpp"


// ----------------------------------------------------------------------------

class R_REDevC : public DR_REDevB
{
protected:
  /* AD_ALIAS Dd=DR_REDevC, DR_REDevB */
  /* AUTOINIT */
  /* AUTODEC 1 */
  ARRAY_2D      InvHessian/* NR,NR */;
  ARRAY_1D      LaplaceGradRE/* NR */;
  ARRAY_1D      LaplaceGradPar/* NP */;

#include "Dd_array_plans.hpp"

public:
  R_REDevC(
#include "Dd_constructor_args.hpp"
  );

  R_REDevC(const R_REDevC& rCopy);
  virtual ~R_REDevC();

  // Gradient of Laplace approximation of Maximum Likelihood
  void gradientLaplacePar(const ARRAY_1D re/* NR */, 
                          const ARRAY_1D par/* NP */,
                          ARRAY_1D pGrad/* NP */);

  // Gradient of Laplace approximation of Maximum Likelihood
  void solveAndGradientLaplacePar(const ARRAY_1D par/* NP */,
                                  ARRAY_1D pGrad/* NP */);
};


#endif  //__R_REDEVC_HPP__
