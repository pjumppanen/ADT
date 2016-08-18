// ----------------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
// bananna function generalised to N dimensions with an R dynamic lib interface.
// ----------------------------------------------------------------------------

#ifndef __R_ROSENBROCK_HPP__
#define __R_ROSENBROCK_HPP__


#include "d_Rosenbrock.hpp"


// ----------------------------------------------------------------------------

class R_MinRosenbrock : public D_MinRosenbrock
{
protected:
  /* AD_ALIAS RRb=DR_MinRosenbrock, D_MinRosenbrock */
  /* AUTODEC 1 */
  ARRAY_1D  lxb1_x/*1:N*/;
  ARRAY_1D  lxd2_x/*1:N*/;
#include "RRb_array_plans.hpp"

#ifndef AD
public:
  // Temporary arrays used for calling vmmin() optimiser directly from our code
  ARRAY_1D Pars/*1:N*/;
  ARRAY_1D Grad/*1:N*/;
#endif

public:
  R_MinRosenbrock(
#include "RRb_constructor_args.hpp"
  );

  void      hessian(ARRAY_1D pX/*1:N*/, ARRAY_2D pHessian/*1:N,1:N*/);
  void      minimise(const ARRAY_1D pS/*1:N*/, ARRAY_1D pR/*1:N*/, int maxit, int& fncount, int& grcount, int& status);
};


#endif  //__R_ROSENBROCK_HPP__
