// ----------------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
// bananna function generalised to N dimensions with an R dynamic lib interface.
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "R_Rosenbrock.hpp"
#include <R_ext/Applic.h>


// ----------------------------------------------------------------------------
// R_MinRosenbrock method implementations
// ----------------------------------------------------------------------------
R_MinRosenbrock::R_MinRosenbrock(
#include "RRb_constructor_args.hpp"
)
 : D_MinRosenbrock(
#include "RRb_constructor_call_args.hpp"
   )
{
  #include "RRb_constructor_locals.hpp"
  #include "RRb_constructor_scalars_phase_1.hpp"
  #include "RRb_constructor_arrays_phase_1.hpp"
  #include "RRb_array_plans_init.hpp"

#ifndef AD
  Pars = 0;
  Grad = 0;
#endif
}

// ----------------------------------------------------------------------------

void R_MinRosenbrock::hessian(ARRAY_1D pX/*1:N*/, ARRAY_2D pHessian/*1:N,1:N*/)
{
  int     cn;
  double  rosenbrockb1_x;

  rosenbrockb1_x = 1.0;

  for (cn = 1 ; cn <= N ; cn++)
  {
    lxd2_x[cn] = 0.0;
  }

  for (cn = 1 ; cn <= N ; cn++)
  {
    lxd2_x[cn] = 1.0;

    // Hessian matrix is symmetric and we construct the matrix row by row by
    // taking the tangent mode derivative of the gradient in each basis
    // direction. The hessian result goes into an ARRAY_2D but we pass the
    // n'th column to be filled by indexing the array.
    ROSENBROCK_BX_DX(pX, lxd2_x, lxb1_x, pHessian[cn], rosenbrockb1_x);

    lxd2_x[cn] = 0.0;
  }
}

// ----------------------------------------------------------------------------
#ifndef AD
double rb_optimfn(int n, double* par, void* context)
{
  R_MinRosenbrock*  pThis = (R_MinRosenbrock*)context;

  for (int cn = 0 ; cn < n ; cn++)
  {
    pThis->Pars[cn + 1] = par[cn];
  }

  return (pThis->rosenbrock(pThis->Pars));
}

// ----------------------------------------------------------------------------

void rb_optimgr(int n, double* par, double* gr, void* context)
{
  double            rosenbrockb1_x = 1.0;
  R_MinRosenbrock*  pThis          = (R_MinRosenbrock*)context;

  for (int cn = 0 ; cn < n ; cn++)
  {
    pThis->Pars[cn + 1] = par[cn];
  }

  pThis->ROSENBROCK_BX(pThis->Pars, pThis->Grad, rosenbrockb1_x);

  for (int cn = 0 ; cn < n ; cn++)
  {
    gr[cn] = pThis->Grad[cn + 1];
  }
}

// ----------------------------------------------------------------------------
#endif

void R_MinRosenbrock::minimise(const ARRAY_1D pS/*1:N*/, ARRAY_1D pR/*1:N*/, int maxit, int& fncount, int& grcount, int& status)
{
#ifndef AD
  double  val     = 0;
  int     trace   = 0; // Don't print minimsation messages
  double  abstol  = R_NegInf;
  double  reltol  = 1e-10;
  int     nREPORT = 100000;
  int*    mask    = new int[N];

  fncount = 0;
  grcount = 0;
  status  = 0;

  create(Pars, 1, N);
  create(Grad, 1, N);

  for (int cn = 0 ; cn < N ; cn++)
  {
    mask[cn]   = 1;
    pR[cn + 1] = pS[cn + 1];
  }

  ts_vmmin(N,
           &pR[1],
           &val,
           rb_optimfn,
           rb_optimgr,
           maxit,
           trace,
           mask,
           abstol,
           reltol,
           nREPORT,
           (void*)this,
           &fncount,
           &grcount,
           &status);

  delete mask;

  destroy(Pars);
  destroy(Grad);

#endif
}
