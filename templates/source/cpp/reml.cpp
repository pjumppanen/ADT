
// ----------------------------------------------------------------------------

double $(classname)::dlognorm(const double x, const double mean, const double sigma)
{
  double dValue;

  dValue = -log(sigma) - 0.5 * log(2 * 3.14159265358979323846) - 0.5 * pow((x - mean) / sigma, 2.0);

  return (dValue);
}

// ----------------------------------------------------------------------------

void $(classname)::choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pL/* nSize, nSize */, const int nSize)
{
  //--------------------------------------------------------------------------
  // A is symetric positive definite matrix in lower triangular form
  // L is the cholesky decomposition in lower triangular form
  //--------------------------------------------------------------------------
  double sum;
  int    ci, cj, ck;

  for (ci = 1 ; ci <= nSize ; ci++)
  {
    sum = pA[ci][ci];

    for (cj = 1 ; cj <= ci - 1 ; cj++)
    {
      sum = sum - pL[ci][cj] * pL[ci][cj];
    }

#ifndef AD
    assert(sum > 0.0);
#endif    
    pL[ci][ci] = sqrt(sum);

    for (cj = ci + 1 ; cj <= nSize ; cj++)
    {
      sum = pA[cj][ci];
      
      for (ck = 1 ; ck <= ci - 1 ; ck++)
      {
        sum = sum - pL[ci][ck] * pL[cj][ck];
      }

      pL[cj][ci] = sum / pL[ci][ci];
    }
  }
}

// ----------------------------------------------------------------------------

double $(classname)::logDeterminantFromChol(const ARRAY_2D pL/* nSize, nSize */, const int nSize)
{
  //--------------------------------------------------------------------------
  // pL is the cholesky decomposition of A in lower triangular form
  //--------------------------------------------------------------------------
  double dLogDet;
  int    ci;

  dLogDet = 0.0;

  for (ci = 1 ; ci <= nSize ; ci++)
  {
    dLogDet += log(pL[ci][ci]);
  }

  dLogDet *= 2.0;

  return (dLogDet);
}

// ----------------------------------------------------------------------------

void $(classname)::matrixInverseFromChol(const ARRAY_2D pL/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize)
{
  //--------------------------------------------------------------------------
  // pL is the cholesky decomposition of A in lower triangular form
  // pInv is the resulting lower triangular inverse matrix
  //--------------------------------------------------------------------------
  int     cc;
  int     cr;
  int     cq;
  double  b;

  for (cc = nSize ; cc >= 1 ; cc--)
  {
    for (cr = cc ; cr >= 1 ; cr--)
    {
      b = 0.0;

      if (cr == cc)
      {
        b = (1.0 / pL[cr][cr]);
      }

      if (cr < nSize)
      {
        for (cq = 1 + cr ; cq <= nSize ; cq++)
        {
          if (cc <= cq)
          {
            b = b - pInv[cq][cc] * pL[cq][cr];
          }
          else
          {
            b = b - pInv[cc][cq] * pL[cq][cr];
          }
        }
      }

      pInv[cc][cr] = b * (1.0 / pL[cr][cr]);
      pInv[cr][cc] = pInv[cc][cr];
    }
  }
}

// ----------------------------------------------------------------------------

#include <R_ext/Applic.h>

#define USE_SCILABOPTIM
#ifdef USE_SCILABOPTIM

  #include <ScilabOptim.h>

#endif


#ifndef AD  

// ----------------------------------------------------------------------------

void $(classname)::inner_simfn(int* indic, int* n, double* re, double* f, double* gr, int* izs, float* rzs, double* dzs)
{
  $(classname)::SolveContext* Context = ($(classname)::SolveContext*)izs;

  Context->nFnCalls++;
  Context->nGradCalls++;

  //re - 1 and gr - 1 because we are using 1 based arrays
  f[0] = Context->pThis->innerObjective(n[0], re - 1);
  Context->pThis->innerGradient(n[0], re, gr - 1);
}
            
// ----------------------------------------------------------------------------

double $(classname)::inner_optimfn(int n, double* re, void* pContext)
{
  $(classname)::SolveContext* Context = ($(classname)::SolveContext*)pContext;

  Context->nFnCalls++;

  //re - 1 because we are using 1 based arrays
  return (Context->pThis->innerObjective(n, re - 1));
}

// ----------------------------------------------------------------------------

void $(classname)::inner_optimgr(int n, double* re, double* gr, void* pContext)
{
  $(classname)::SolveContext* Context = ($(classname)::SolveContext*)pContext;

  Context->nGradCalls++;

  //re - 1 and gr - 1 because we are using 1 based arrays
  Context->pThis->innerGradient(n, re - 1, gr - 1);
}

#endif //AD

// ----------------------------------------------------------------------------

#ifndef AD  
void $(classname)::solveInner(ARRAY_1D reHat/* NR */, const ARRAY_1D par/* NP */)
{
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
#ifdef USE_SCILABOPTIM
    $(classname)::SolveContext Context;

    Context.nFnCalls   = 0;
    Context.nGradCalls = 0;
    Context.pThis      = this;

    for (cn = 1 ; cn <= NR ; cn++)
    {
      ReRun[cn]  = reHat[cn];
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

    $(classname)::inner_simfn(&indic, &NR, ReRun + 1, &f, GradRun + 1, izs, rzs, dzs);

    F77_NAME(n1qn1)($(classname)::inner_simfn, 
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
      reHat[cn] = ReRun[cn];
    }
#else    
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

    $(classname)::SolveContext Context;

    Context.nFnCalls   = 0;
    Context.nGradCalls = 0;
    Context.pThis      = this;

    for (cn = 1 ; cn <= NR ; cn++)
    {
      ReRun[cn]  = reHat[cn];
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
              $(classname)::inner_optimfn,
              $(classname)::inner_optimgr,
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
        reHat[cn] = ReRun[cn];
      }
    }

    Rprintf("Status:%d, value:%f, fn count:%d, gr count:%d\n", status, val, fncount, grcount);
#endif //USE_SCILABOPTIM
  }
  else
  {
    Rprintf("No change.\n");
  }
  
  Dirty = false;
}

#endif //AD 

// ----------------------------------------------------------------------------

double $(classname)::logDetHessianRE(const ARRAY_1D re/* NR */, const ARRAY_1D par/* NP */, const ARRAY_2D pHessian/* NR,NR */, ARRAY_2D pCholesky/* NR,NR */)
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

