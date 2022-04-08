// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements the full random effects fitting process.
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "R_REDevB.hpp"
#include <R_ext/Applic.h>


// ----------------------------------------------------------------------------
// R_MinRosenbrock method implementations
// ----------------------------------------------------------------------------
R_REDevB::R_REDevB(
#include "Dc_constructor_args.hpp"
)
 : DR_REDevA(
#include "Dc_constructor_call_args.hpp"
   )
{
  #include "Dc_constructor_locals.hpp"
  #include "Dc_constructor_scalars_phase_1.hpp"
  #include "Dc_constructor_arrays_phase_1.hpp"
  #include "Dc_array_plans_init.hpp"

#ifndef AD
  MultithreadedCount = 0;
#endif  
}

// ----------------------------------------------------------------------------

R_REDevB::R_REDevB(const R_REDevB& rCopy)
 : DR_REDevA(rCopy)
#include "Dc_array_plans_copy.hpp"
{

}

// ----------------------------------------------------------------------------

R_REDevB::~R_REDevB()
{
  if (IsShallowCopy)
  {
    destroy(Dir);
  }
}

// ----------------------------------------------------------------------------

#ifndef AD
AdtArrays* R_REDevB::createShallowCopy() const
{
  return (new R_REDevB(*this));
}
#endif //AD

// ----------------------------------------------------------------------------

#ifndef AD
void R_REDevB::hessianRow(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* Context     = (ParallelForContext*)pContext;
  R_REDevB*           pThis       = (R_REDevB*)shallowCopy(nThreadIdx);
  double              diffreb1_re = 1.0;

  pThis->Dir[nIdx] = 1.0;

  // Hessian matrix is symmetric and we construct the matrix row by row by
  // taking the tangent derivative of the adjoint derivative in each basis
  // direction. The hessian result goes into an ARRAY_2D but we pass the
  // n'th column to be filled by indexing the array.
  pThis->DIFFRE_BRE(Context->Re, 
                    Context->Result[nIdx], 
                    Context->Par, 
                    pThis->Dir, 
                    diffreb1_re);
    
  pThis->Dir[nIdx] = 0.0;
}

// ----------------------------------------------------------------------------

void R_REDevB::covarRE_ParRow(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* Context       = (ParallelForContext*)pContext;
  R_REDevB*           pThis         = (R_REDevB*)shallowCopy(nThreadIdx);
  double              diffreb2_par  = 1.0;

  Context->Dir[nIdx] = 1.0;

  // Hessian matrix is symmetric and we construct the matrix row by row by
  // taking the tangent derivative of the adjoint derivative in each basis
  // direction. The hessian result goes into an ARRAY_2D but we pass the
  // n'th column to be filled by indexing the array.
  pThis->DIFFRE_BPAR(Context->Re, 
                     Context->Par, 
                     Context->Result[nIdx], 
                     pThis->Dir, 
                     diffreb2_par);

  Context->Dir[nIdx] = 0.0;

}

// ----------------------------------------------------------------------------

void R_REDevB::beginMultithreaded(int nThreads)
{
  if (MultithreadedCount == 0)
  {
    createThreadPool(nThreads);
    allocateShallowCopies(this);
  }

  MultithreadedCount++;
}

// ----------------------------------------------------------------------------

void R_REDevB::endMultithreaded()
{
  MultithreadedCount--;

  if (MultithreadedCount == 0)
  {
    freeShallowCopies();
    closeThreadPool();
  }
}

#endif

// ----------------------------------------------------------------------------

void R_REDevB::hessianRE(const ARRAY_1D re/* NR */, 
                         const ARRAY_1D par/* NP */, 
                         ARRAY_2D pHessian/* NR,NR */)
{
  int     cn;
  int     cm;
  double  diffreb1_re;
  
  diffreb1_re = 1.0;

  for (cn = 1 ; cn <= NR ; cn++)
  {
    Dir[cn] = 0.0;
  }
  
#ifdef AD
  for (cn = 1 ; cn <= NR ; cn++)
  {
    Dir[cn] = 1.0;

    // Hessian matrix is symmetric and we construct the matrix row by row by
    // taking the tangent derivative of the adjoint derivative in each basis
    // direction. The hessian result goes into an ARRAY_2D but we pass the
    // n'th column to be filled by indexing the array.
    DIFFRE_BRE(re, 
               TempRow,
               par, 
               Dir, 
               diffreb1_re);
  
    for (cm = 1 ; cm <= NR ; cm++)
    {
      pHessian[cn][cm] = TempRow[cm];
    }

    Dir[cn] = 0.0;
  }
#else
  bool    bMultithreaded = (MultithreadedCount > 0);
  
  if (bMultithreaded)
  {
    ParallelForContext  Context(this, 
                                par,
                                re,
                                Dir,
                                pHessian);

    parallelFor((void*)&Context, R_REDevB::hessianRow, 1, NR);
  }
  else
  {
    for (cn = 1 ; cn <= NR ; cn++)
    {
      Dir[cn] = 1.0;

      // Hessian matrix is symmetric and we construct the matrix row by row by
      // taking the tangent derivative of the adjoint derivative in each basis
      // direction. The hessian result goes into an ARRAY_2D but we pass the
      // n'th column to be filled by indexing the array.
      DIFFRE_BRE(re, 
                 pHessian[cn], 
                 par, 
                 Dir, 
                 diffreb1_re);
    
      Dir[cn] = 0.0;
    }
  }
#endif
}

// ----------------------------------------------------------------------------

void R_REDevB::covarRE_Par(const ARRAY_1D re/* NR */, 
                           const ARRAY_1D par/* NP */, 
                           ARRAY_2D pReParXCovar/* NR,NP */)
{
  int     cn;
  int     cm;
  double  diffreb2_par;
  
  diffreb2_par = 1.0;

  for (cn = 1 ; cn <= NR ; cn++)
  {
    Dir[cn] = 0.0;
  }
  
#ifdef AD
  for (cn = 1 ; cn <= NR ; cn++)
  {
    Dir[cn] = 1.0;

    // Hessian matrix is symmetric and we construct the matrix row by row by
    // taking the tangent derivative of the adjoint derivative in each basis
    // direction. The hessian result goes into an ARRAY_2D but we pass the
    // n'th column to be filled by indexing the array.
    DIFFRE_BPAR(re, 
                par, 
                TempRow, 
                Dir, 
                diffreb2_par);
  
    for (cm = 1 ; cm <= NR ; cm++)
    {
      pReParXCovar[cn][cm] = TempRow[cm];
    }

    Dir[cn] = 0.0;
  }
#else
  bool    bMultithreaded = (MultithreadedCount > 0);
  
  if (bMultithreaded)
  {
    ParallelForContext  Context(this, 
                                par,
                                re,
                                Dir,
                                pReParXCovar);

    parallelFor((void*)&Context, R_REDevB::covarRE_ParRow, 1, NR);
  }
  else
  {
    for (cn = 1 ; cn <= NR ; cn++)
    {
      Dir[cn] = 1.0;

      // Hessian matrix is symmetric and we construct the matrix row by row by
      // taking the tangent derivative of the adjoint derivative in each basis
      // direction. The hessian result goes into an ARRAY_2D but we pass the
      // n'th column to be filled by indexing the array.
      DIFFRE_BPAR(re, 
                  par, 
                  pReParXCovar[cn], 
                  Dir, 
                  diffreb2_par);
    
      Dir[cn] = 0.0;
    }
  }
#endif
}

// ----------------------------------------------------------------------------

double R_REDevB::logDetHessianRE(const ARRAY_1D re/* NR */, 
                                 const ARRAY_1D par/* NP */,
                                 const ARRAY_2D pHessian/* NR,NR */,
                                 ARRAY_2D pCholesky/* NR,NR */)
{
  double logdet;

  choleskyDecomposition(pHessian, pCholesky, NR);
  logdet = logDeterminantFromChol(pCholesky, NR);

  return (logdet);
}

// ----------------------------------------------------------------------------

double R_REDevB::laplace(const ARRAY_1D re/* NR */, 
                         const ARRAY_1D par/* NP */, 
                         ARRAY_2D pHessian/* NR,NR */, 
                         ARRAY_2D pCholesky/* NR,NR */)
{
  double h;

  hessianRE(re, par, pHessian);
  h = ((-NR * log(2 * M_PI) + logDetHessianRE(re, par, pHessian, pCholesky)) * 0.5) + logLikelihood(re, par);

  return (h);
}

