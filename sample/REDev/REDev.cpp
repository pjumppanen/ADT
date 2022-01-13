// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------


#include "REDev.hpp"


// ----------------------------------------------------------------------------

REDev::REDev(
#include "Rd_constructor_args.hpp"
)
{
  #include "Rd_constructor_locals.hpp"
  #include "Rd_constructor_scalars_phase_1.hpp"
  #include "Rd_constructor_arrays_phase_1.hpp"
  #include "Rd_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

double REDev::dlognorm(const double x, 
                       const double mean,
                       const double sigma)
{
  double dValue;

  dValue = -log(sigma) - 0.5 * log(2 * M_PI) - 0.5 * pow((x - mean) / sigma, 2.0);

  return (dValue);
}

// ----------------------------------------------------------------------------

double REDev::thetalogLikelihood(const ARRAY_1D u/*N*/,
                                 const double logr0,
                                 const double logtheta,
                                 const double logK,
                                 const double logQ,
                                 const double logR)
{
  double mean;
  double r0;
  double theta;
  double K;
  double Q;
  double R;
  double ll;
  int    cn;

  r0    = exp(logr0);
  theta = exp(logtheta);
  K     = exp(logK);
  Q     = exp(logQ);
  R     = exp(logR);
  ll    = 0.0;

  for (cn = 2 ; cn <= N ; cn++)
  {
    mean = u[cn - 1] + r0 * (1.0 - pow(exp(u[cn - 1]) / K, theta));

    ll -= dlognorm(u[cn], mean, sqrt(Q));
  }

  for(cn = 1 ; cn <= N ; cn++)
  {
    ll -= dlognorm(y[cn], u[cn], sqrt(R));
  }

  return (ll);
}

// ----------------------------------------------------------------------------

double REDev::logLikelihood(const ARRAY_1D re/* NR */, const ARRAY_1D par/* NP */)
{
  // Decode parameters                                  
  double dLikelihood;
  int    cn;
  int    cm;

  // Copy over random effects
  cm = 1;

  for (cn = 0 ; cn < NR ; cn++)
  {
    par_u[cm] = re[cm];

    cm++;
  }

  // Copy over parameters
  cm = 1;

  par_logr0 = par[cm];
  cm++;

  par_logtheta = par[cm];
  cm++;

  par_logK = par[cm];
  cm++;

  par_logQ = par[cm];
  cm++;

  par_logR = par[cm];
  cm++;

  // Call likelihood function
  dLikelihood = thetalogLikelihood(par_u,
                                   par_logr0,
                                   par_logtheta,
                                   par_logK,
                                   par_logQ,
                                   par_logR);

  return (dLikelihood);
}

// ----------------------------------------------------------------------------

void REDev::choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pL/* nSize, nSize */, const int nSize)
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
    cj  = 1;

    while (cj <= ci - 1)
    {
      sum = sum - pL[ci][cj] * pL[ci][cj];

      cj++;
    }

    pL[ci][ci] = sqrt(sum);

    cj = ci + 1;

    while (cj <= nSize)
    {
      sum = pA[cj][ci];
      ck  = 1;

      while (ck <= ci - 1)
      {
        sum = sum - pL[ci][ck] * pL[cj][ck];

        ck++;
      }

      pL[cj][ci] = sum / pL[ci][ci];

      cj++;
    }
  }
}

// ----------------------------------------------------------------------------

double REDev::logDeterminantFromChol(const ARRAY_2D pL/* nSize, nSize */, const int nSize)
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

void REDev::matrixInverseFromChol(const ARRAY_2D pL/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize)
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
          b = b - pInv[cq][cc] * pL[cq][cr];
        }
      }

      pInv[cc][cr] = b * (1.0 / pL[cr][cr]);
    }
  }
}
