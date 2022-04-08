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
  ARRAY_2D      Hessianb1_re/* NR,NR */;
  ARRAY_2D      Choleskyb1_re/* NR,NR */;
  ARRAY_1D      TempRow2/* NR */;
  
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
                          ARRAY_2D pHessian/* NR,NR */, 
                          ARRAY_2D pCholesky/* NR,NR */,
                          ARRAY_2D pInvHessian/* NR,NR */, 
                          ARRAY_1D pLaplaceGradRE/* NR */, 
                          ARRAY_1D pLaplaceGradPar/* NP */, 
                          ARRAY_2D pObjReParXCovar/* NR,NP */,
                          ARRAY_1D pGrad/* NP */);
};


#endif  //__R_REDEVC_HPP__
