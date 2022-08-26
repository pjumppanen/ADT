// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements the full random effects fitting process.
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "R_REDevB.hpp"
#include <R_ext/Applic.h>
#include "ScilabOptim.h"


// ----------------------------------------------------------------------------
// R_REDevB method implementations
// ----------------------------------------------------------------------------
#ifndef AD  
void R_REDevB::inner_simfn(int* indic, int* n, double* x, double* f, double* g, int* izs, float* rzs, double* dzs)
{
  R_REDevB::SolveContext* Context = (R_REDevB::SolveContext*)izs;

  Context->nFnCalls++;
  Context->nGradCalls++;

  f[0] = Context->pThis->innerObjective(n[0], x);
  Context->pThis->innerGradient(n[0], x, g);
}
            
// ----------------------------------------------------------------------------

double R_REDevB::inner_optimfn(int n, double* par, void* pContext)
{
  R_REDevB::SolveContext* Context = (R_REDevB::SolveContext*)pContext;

  Context->nFnCalls++;

  return (Context->pThis->innerObjective(n, par));
}

// ----------------------------------------------------------------------------

void R_REDevB::inner_optimgr(int n, double* par, double* gr, void* pContext)
{
  R_REDevB::SolveContext* Context = (R_REDevB::SolveContext*)pContext;

  Context->nGradCalls++;

  Context->pThis->innerGradient(n, par, gr);
}

// ----------------------------------------------------------------------------

double R_REDevB::innerObjective(int n, double* par)
{
  return (logLikelihood(par - 1, Par)); //par - 1 because we are using 1 based arrays
}

// ----------------------------------------------------------------------------

void R_REDevB::innerGradient(int n, double* par, double* gr)
{
  gradientRE(par - 1, Par, gr - 1); //par - 1, gr - 1 because we are using 1 based arrays
}

#endif //AD

// ----------------------------------------------------------------------------

void R_REDevB::solveInner(const ARRAY_1D par/* NP */)
{
#ifndef AD  
  int   cn;
  int   cm;
  bool  bChanged = Dirty;

  for (cn = 1 ; cn <= NP ; cn++)
  {
    // As Par gets used and set in other parts of the code
    // it's value isn't a reliable check for whether the random
    // effects fit has been carried out or not. Thus we have 
    // a second array, CheckPar, whose only purpose is to cache 
    // the last fit parameters so we can tell if it needs fitting
    // or not.
    bChanged      = bChanged || (CheckPar[cn] != par[cn]);
    Par[cn]       = par[cn];
    CheckPar[cn]  = par[cn];
  }

  if (bChanged)
  {
    if (1)
    {
      R_REDevB::SolveContext Context;

      Context.nFnCalls   = 0;
      Context.nGradCalls = 0;
      Context.pThis      = this;

      for (cn = 1 ; cn <= NR ; cn++)
      {
        ReRun[cn]  = ReHat[cn];
        var[cn]    = 1.0;
      }

      if (!Dirty)
      {
        int cz = 0;

        // Initialise hessian for minimiser based on last result
        for (cn = 1 ; cn <= NR ; cn++)
        {
          for (cm = cn ; cm <= NR ; cm++)
          {
            zm[cz] = Hessian[cn][cm];

            cz++;
          }
        }
      }

      double    f       = 0.0;
      double    eps     = 1.0e-8;
      int       mode    = Dirty ? 1 : 2;
      int       niter   = 200;
      int       nsim    = 200;
      int       iprint  = 3;
      int       lp      = 0;
      int       indic   = 0;
      int*      izs     = (int*)&Context; // use it as the context pointer
      float*    rzs     = 0;              // unused
      double*   dzs     = 0;              // unused

      R_REDevB::inner_simfn(&indic, &NR, ReRun + 1, &f, GradRun + 1, izs, rzs, dzs);

      F77_NAME(n1qn1)(R_REDevB::inner_simfn, 
                      &NR, 
                      ReRun + 1,
                      &f,
                      GradRun + 1,
                      var + 1,
                      &eps,
                      &mode,
                      &niter,
                      &nsim,
                      &iprint,
                      &lp,
                      zm,
                      izs,
                      rzs,
                      dzs);

      for (cn = 1 ; cn <= NR ; cn++)
      {
        ReHat[cn] = ReRun[cn];
      }
    }
    else
    {
    char    msg[256]  = {0};
    int     trace     = 6; // Don't print minimsation messages
    int     nREPORT   = 100000;
    int     mask      = 1;
    double  val       = 0.0;
    double  factr     = 1.0e+8; // The iteration will stop when
                                //
                                //   (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= factr*epsmch
                                //
                                // where epsmch is the machine precision, which is
                                // automatically generated by the code.
    double  pgtol     = 1.0e-6; // The iteration will stop when
                                //
                                //   max{|proj g_i | i = 1, ..., n} <= pgtol
                                //
                                // where pg_i is the ith component of the projected gradient.
//    int     m         = 8;      // m is the maximum number of variable metric corrections allowed in the limited memory matrix. What does that mean?
    int     m         = NP;      // m is the maximum number of variable metric corrections allowed in the limited memory matrix. What does that mean?
    int     fncount   = 0;
    int     grcount   = 0;
    int     status    = 0;
    int     maxit     = 1000;

    R_REDevB::SolveContext Context;

    Context.nFnCalls   = 0;
    Context.nGradCalls = 0;
    Context.pThis      = this;

    for (cn = 1 ; cn <= NR ; cn++)
    {
      ReRun[cn]  = ReHat[cn];
      plower[cn] = 0.0;
      pupper[cn] = 0.0;
      pnbd[cn]   = 0; // Bound type 0 if x(i) is unbounded,
                      //            1 if x(i) has only a lower bound,
                      //            2 if x(i) has both lower and upper bounds, and
                      //            3 if x(i) has only an upper bound.
    }

    ts_lbfgsb(NR,
              m,
              ReRun + 1,
              plower + 1,
              pupper + 1,
              pnbd + 1,
              &val,
              R_REDevB::inner_optimfn,
              R_REDevB::inner_optimgr,
              &status,
              (void*)&Context,
              factr,
              pgtol,
              &fncount,
              &grcount,
              maxit,
              msg,
              trace,
              nREPORT);

    if (status == 0)
    {
      for (cn = 1 ; cn <= NR ; cn++)
      {
        ReHat[cn] = ReRun[cn];
      }
    }

    Rprintf("Status:%d, value:%f, fn count:%d, gr count:%d\n", status, val, fncount, grcount);
    }
  }
  else
  {
    Rprintf("No change.\n");
  }
  
  Dirty = false;
#endif //AD
}

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
  Dirty = true;
}

// ----------------------------------------------------------------------------

R_REDevB::R_REDevB(const R_REDevB& rCopy)
 : DR_REDevA(rCopy)
#include "Dc_array_plans_copy.hpp"
{
  Dirty = true;
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

void R_REDevB::hessianAndCovarRow(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* Context         = (ParallelForContext*)pContext;
  R_REDevB*           pThis           = (R_REDevB*)shallowCopy(nThreadIdx);
  double              diffreb2_repar  = 1.0;

  pThis->Dir[nIdx] = 1.0;

      // Hessian matrix is symmetric and we construct the matrix row by row by
      // taking the tangent derivative of the adjoint derivative in each basis
      // direction. The hessian result goes into an ARRAY_2D but we pass the
      // n'th column to be filled by indexing the array.
  pThis->DIFFRE_BREPAR(Context->Re, 
                       Context->Result[nIdx], 
                       Context->Par, 
                       Context->Result2[nIdx], 
                       pThis->Dir, 
                       diffreb2_repar);

  pThis->Dir[nIdx] = 0.0;

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
                                pHessian, 
                                0);

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

void R_REDevB::hessianAndCovarRE(const ARRAY_1D re/* NR */, 
                                 const ARRAY_1D par/* NP */, 
                                 ARRAY_2D pHessian/* NR,NR */,
                                 ARRAY_2D pReParXCovar/* NR,NP */)
{
  int     cn;
  int     cm;
  double  diffreb2_repar;
  
  diffreb2_repar = 1.0;

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
    DIFFRE_BREPAR(re, 
                  TempRow, 
                  par, 
                  TempRow2, 
                  Dir, 
                  diffreb2_repar);
  
    for (cm = 1 ; cm <= NR ; cm++)
    {
      pHessian[cn][cm] = TempRow[cm];
    }

    for (cm = 1 ; cm <= NP ; cm++)
    {
      pReParXCovar[cn][cm] = TempRow2[cm];
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
                                pHessian,
                                pReParXCovar);

    parallelFor((void*)&Context, R_REDevB::hessianAndCovarRow, 1, NR);
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
      DIFFRE_BREPAR(re, 
                    pHessian[cn], 
                    par, 
                    pReParXCovar[cn], 
                    Dir, 
                    diffreb2_repar);
    
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
  int    cn;
  int    cm;

  for (cn = 1 ; cn <= NR ; cn++)
  {
    for (cm = 1 ; cm <= NR ; cm++)
    {
      Cholesky[cn][cm] = 0.0;
    }
  }

  choleskyDecomposition(pHessian, pCholesky, NR);
  logdet = logDeterminantFromChol(pCholesky, NR);

  return (logdet);
}

// ----------------------------------------------------------------------------

double R_REDevB::laplace(const ARRAY_1D re/* NR */, 
                         const ARRAY_1D par/* NP */)
{
  double h;

  hessianAndCovarRE(re, par, Hessian, ReParXCovar);
  h = ((-NR * log(2 * M_PI) + logDetHessianRE(re, par, Hessian, Cholesky)) * 0.5) + logLikelihood(re, par);

  return (h);
}

// ----------------------------------------------------------------------------

double R_REDevB::solveAndLaplace(const ARRAY_1D par/* NP */)
{
  solveInner(par);

  return (laplace(ReHat, par));
}

// ----------------------------------------------------------------------------

void R_REDevB::setInitialRE(const ARRAY_1D re/* NR */)
{
  int   cn;

  for (cn = 1 ; cn <= NR ; cn++)
  {
    ReHat[cn]  = re[cn];
  }

  Dirty = true;
}

