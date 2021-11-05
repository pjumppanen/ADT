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

double REDev::simpleLogLikelihood(const ARRAY_1D x/*N1*/, 
                                  const ARRAY_1D u/*N3*/,
                                  const ARRAY_1D beta/*N2*/,
                                  const double logsdu,
                                  const double logsd0)
{
  int    cn;
  int    cr;
  int    cc;
  double likelihood;
  double v;

  likelihood = 0.0;

  // Distribution of random effect (u):
  for (cn = 1 ; cn <= N3 ; cn++)
  {
    likelihood = likelihood - dlognorm(u[cn], 0.0, exp(logsdu));
  }

  // Distribution of obs given random effects (x|u):
  for (cr = 1 ; cr <= N1 ; cr++)
  {
    v = 0.0;

    for (cc = 1 ; cc <= N2 ; cc++)
    {
      v = v + A[cc][cr] * beta[cc]; 
    }

    for (cc = 1 ; cc <= N3 ; cc++)
    {
      v = v + B[cc][cr] * u[cc]; 
    }

    likelihood = likelihood - dlognorm(x[cr], v, exp(logsd0));
  }

  return likelihood;
}

// ----------------------------------------------------------------------------

double REDev::thetalogLikelihood(const ARRAY_1D u/*NP*/,
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

  for (cn = 2 ; cn <= NP ; cn++)
  {
    mean = u[cn - 1] + r0 * (1.0 - pow(exp(u[cn - 1]) / K, theta));

    ll -= dlognorm(u[cn], mean, sqrt(Q));
  }

  for(cn = 1 ; cn <= NP ; cn++)
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

void REDev::choleskyDecomposition(const ARRAY_2D pA/* NR,NR */, ARRAY_2D pL/* NR,NR */)
{
  //--------------------------------------------------------------------------
  // A is symetric positive definite matrix in lower triangular form
  // L is the cholesky decomposition in lower triangular form
  //--------------------------------------------------------------------------
  double sum;
  int    ci, cj, ck;

  for (ci = 1 ; ci <= NR ; ci++)
  {
    sum = pA[ci][ci];
    cj  = 1;

    while (cj <= ci - 1)
    {
      sum = sum - pA[ci][cj] * pA[ci][cj];

      cj++;
    }

    pL[ci][ci] = sqrt(sum);

    cj = ci + 1;

    while (cj <= NR)
    {
      sum = pA[cj][ci];
      ck  = 1;

      while (ck <= ci - 1)
      {
        sum = sum - pA[ci][ck] * pA[cj][ck];
      }

      pL[cj][ci] = sum / pA[ci][ci];

      cj++;
    }
  }
}

// ----------------------------------------------------------------------------

double REDev::logDeterminant(const ARRAY_2D pA/* NR,NR */, ARRAY_2D pL/* NR,NR */)
{
  //--------------------------------------------------------------------------
  // A is symetric positive definite matrix in lower triangular form
  //--------------------------------------------------------------------------
  double dLogDet;
  int    ci;

  choleskyDecomposition(pA, pL);

  dLogDet = 0.0;

  for (ci = 1 ; ci <= NR ; ci++)
  {
    dLogDet += log(pL[ci][ci]);
  }

  return (dLogDet);
}
