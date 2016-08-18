//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    adtdiff.cpp
//
//  Purpose:
//    This file includes implementations of classes for use in Auto-differentiation
//    code implemented in C++. This is a functional equivalent of the TUseful
//    delphi unit code for delphi applications.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtdiff.hpp"


const int AdtDiff::n_laugamp        = 100; // gives at least 15 digits of accuracy
const int AdtDiff::n_gamlanc        = 9;
const double AdtDiff::gamlanc_cof[] = {1.000000000000000174663,
                                       5716.400188274341379136,
                                       -14815.30426768413909044,
                                       14291.49277657478554025,
                                       -6348.160217641458813289,
                                       1301.608286058321874105,
                                       -108.1767053514369634679,
                                       2.605696505611755827729,
                                       -0.7423452510201416151527e-2,
                                       0.5384136432509564062961e-7,
                                       -0.4023533141268236372067e-8};


//  ----------------------------------------------------------------------------

AdtDiff::AdtDiff()
 : AdtArrays()
{
  ncheb       = 0;
  incheb      = 0;
  sqrt_two_pi = sqrt(2 * M_PI);
  cheb_x      = 0;
  cheb_wt     = 0;

#ifndef AD
  // 257 in next line because nbig<=256 & ibig[nbig+1]:= j
  AdtArrayPlan  A1(1, 257);

  A1.create(MemAllocator, ismall);
  A1.create(MemAllocator, ibig);
  A1.create(MemAllocator, exp_shift);

  AdtArrayPlan  A2(1, 256);

  A2.create(MemAllocator, compli);
  A2.create(MemAllocator, acc_cval);
#endif
}

//  ----------------------------------------------------------------------------

AdtDiff::~AdtDiff()
{

}

//  ----------------------------------------------------------------------------

#ifndef AD

// Macro to access the exponent of a IEEE double
#define EXP_OF_DOUBLE(num)  ((short*)(&num))[3]

double AdtDiff::sum_log1m(const ARRAY_1D xpos /*count*/,
                          const int first,
                          const int count)
{
  const double scale2[2]  = {1,2};
  const double scale3[2]  = {0,1};
  const double LN2        = 0.69314718055994529;

  int nbig, nsmall, j, odd, expo, expotot, this_exp_shift, new_expo, leftover, iloop;
  bool big;
  double eps, this_x, compx, prod;
  ARRAY_1D txpos;
  double FRESULT;

  FRESULT = 0;
  txpos   = &xpos[first-1];

  for (iloop = 1 ; iloop <= (count >> 8) ; iloop++)
  {
    zero(exp_shift[1], 256);
    zero(ismall[1], 256);
    zero(ibig[1], 256);

    nbig    = 0;
    nsmall  = 0;

    for (j = 1 ; j <= 256 ; j++)
    {
      big                 = (txpos[j] > 0.5);
      compli[j]           = 1 - txpos[j];
      ibig[nbig + 1]      = j;
      ismall[nsmall + 1]  = j;
      nbig               += (big) ? 1 : 0;
      nsmall             += (!big) ? 1 : 0;
    }

    expotot = 0;

    if (nsmall > 0)
    {
      eps = 0;

      for (j = 1 ; j <= nsmall ; j++)
      {
        this_x   = txpos[ismall[j]];
        eps     += this_x - eps * this_x;
        big      = (eps > 0.5);
        eps      = scale2[big] * eps - scale3[big];
        expotot += (big) ? 1 : 0;  // should be DECR-- sorted out below
      }

      FRESULT += log1p(-eps);
    }

    if (nbig > 0)
    {
      expotot = (-expotot) << 4;
      odd     = 0x10;
      prod    = 1;

      // ?Should break this into blocks to prevent underflow (and reduce mispreds)
      // Be sure to load each double completely to avoid misaligned cache splits
      // ... (ie not just high-order)
      // ... necessary because the ibig indexing.
      for (j = 1 ; j <= nbig ; j++)
      {
        compx                 = compli[ibig[j]];
        expo                  = EXP_OF_DOUBLE(compx);
        new_expo              = 0x3FF0 - odd;
        EXP_OF_DOUBLE(compx)  = new_expo | (expo & 0x0F); // keep mantissa bitss
        compli[ibig[j]]       = compx;
        this_exp_shift        = (expo & 0x7FF0) - new_expo;
        exp_shift[ibig[j]]    = this_exp_shift;
        expotot              += this_exp_shift;
        prod                  = prod * compx;
        odd                   = 0x10 - odd;
      }

      FRESULT += log(prod);
      expotot = (-expotot) >> 4;
    }

    FRESULT -= expotot * LN2;
    txpos   = &txpos[256];
  };

  leftover = count & 0xFF;

  if (leftover > 0)
  {
    zero(exp_shift[1], leftover);
    zero(ismall[1], leftover);
    zero(ibig[1], leftover);

    nbig    = 0;
    nsmall  = 0;

    for (j = 1 ; j <= leftover ; j++)
    {
      big                 = (txpos[j] > 0.5);
      compli[j]           = 1 - txpos[j];
      ibig[nbig + 1]      = j;
      ismall[nsmall + 1]  = j;
      nbig               += (big) ? 1 : 0;
      nsmall             += (!big) ? 1 : 0;
    }

    expotot = 0;

    if (nsmall > 0)
    {
      eps = 0;

      for (j = 1 ; j <= nsmall ; j++)
      {
        this_x    = txpos[ismall[j]];
        eps      += this_x - eps * this_x;
        big       = (eps > 0.5);
        eps       = scale2[big] * eps - scale3[big];
        expotot  += (big)? 1 : 0;  // should be DECR-- sorted out below
      }

      FRESULT += log1p(-eps);
    }

    if (nbig > 0)
    {
      odd     = 0x10;
      prod    = 1;
      expotot = (-expotot) << 4;

      // ?Should break this into blocks to prevent underflow (and reduce mispreds)
      // Be sure to load each double completely to avoid misaligned cache splits (ie not just high-order)
      // ... necessary because the ibig indexing.
      for (j = 1 ; j <= nbig ; j++)
      {
        compx                 = compli[ibig[j]];
        expo                  = EXP_OF_DOUBLE(compx);
        new_expo              = 0x3FF0 - odd;
        EXP_OF_DOUBLE(compx)  = new_expo | (expo & 0x0F); // keep mantissa bitss
        compli[ibig[j]]       = compx;
        this_exp_shift        = (expo & 0x7FF0) - new_expo;
        exp_shift[ibig[j]]    = this_exp_shift;
        expotot              += this_exp_shift;
        prod                  = prod * compx;
        odd                   = 0x10 - odd;
      }

      FRESULT += log(prod);
      expotot = (-expotot) >> 4;
    };

    FRESULT -= expotot * LN2;
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::dsum_log1m(const ARRAY_1D xpos /*count*/,
                           const ARRAY_1D xposdir1/*count*/,
                           const int first,
                           const int count,
                           double& sum_log1m_result)
{
  double    a, b, cval, zstar;
  int       j, leftover, iloop;
  ARRAY_1D  txpos, txposdir1;
  double    FRESULT;

  FRESULT = 0;

  // compli and exp_shift already contain 1-x in the form z, log_2(k)
  sum_log1m_result = 0;

  txpos     = &xpos[first - 1];
  txposdir1 = &xposdir1[first - 1];

  for (iloop = 1 ; iloop <= (count >> 8) ; iloop++)
  {
    sum_log1m_result += sum_log1m(txpos, 1, 256);

    a = 0;
    b = 1;

    for (j = 1 ; j <= 256 ; j++)
    {
      cval                = txposdir1[j];
      // cval = cval * 2^(-exp_shift[ j]);
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - exp_shift[j]);
      zstar               = compli[j];
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    };

    FRESULT -= a / b;

    txposdir1 = &txposdir1[256];
    txpos     = &txpos[256];
  }

  leftover = count & 0xFF;

  if (leftover > 0)
  {
    sum_log1m_result += sum_log1m(txpos, 1, leftover);

    a = 0;
    b = 1;

    for (j = 1 ; j <= leftover ; j++)
    {
      cval                = txposdir1[j];
      // cval= cval * 2^(-exp_shift[ j]);
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - exp_shift[j]);
      zstar               = compli[j];
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    }

    FRESULT -= a / b;
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::ddsum_log1m(const ARRAY_1D xpos/*count*/,
                            const ARRAY_1D xposdir1/*count*/,
                            const ARRAY_1D xposdir2/*count*/,
                            const int first,
                            const int count,
                            double& sum_log1m_result,
                            double& dsum_log1m_result)
{
  double    a, b, cval, zstar, tsum_log1m_result;
  int       j, leftover, iloop;
  ARRAY_1D  txpos, txposdir1, txposdir2;
  double    FRESULT = 0;

  sum_log1m_result  = 0;
  tsum_log1m_result = 0;
  dsum_log1m_result = 0;

  txpos     = &xpos[first-1];
  txposdir1 = &xposdir1[first-1];
  txposdir2 = &xposdir2[first-1];

  for (iloop = 1 ; iloop <= (count >> 8) ; iloop++)
  {
    dsum_log1m_result += dsum_log1m(txpos, txposdir1, 1, 256, tsum_log1m_result);
    sum_log1m_result  += tsum_log1m_result;

    a = 0;
    b = 1;

    for (j = 1 ; j <= 256 ; j++)
    {
      cval                = txposdir1[j];
      cval                = cval * txposdir2[j];
      acc_cval[j]         = cval;
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - 2 * exp_shift[j]);
      zstar               = compli[j];
      zstar               = zstar * zstar;
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    }

    FRESULT -= a / b;

    txpos     = &txpos[256];
    txposdir1 = &txposdir1[256];
    txposdir2 = &txposdir2[256];
  }

  leftover = count & 0xFF;

  if (leftover > 0)
  {
    dsum_log1m_result += dsum_log1m(txpos, txposdir1, 1, leftover, tsum_log1m_result);
    sum_log1m_result  += tsum_log1m_result;

    a = 0;
    b = 1;

    for (j = 1 ; j <= leftover ; j++)
    {
      cval                = txposdir1[j];
      cval                = cval * txposdir2[j];
      acc_cval[j]         = cval;
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - 2 * exp_shift[j]);
      zstar               = compli[j];
      zstar               = zstar * zstar;
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    }

    FRESULT -= a / b;
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::dddsum_log1m(const ARRAY_1D xpos/*count*/,
                             const ARRAY_1D xposdir1/*count*/,
                             const ARRAY_1D xposdir2/*count*/,
                             const ARRAY_1D xposdir3/*count*/,
                             const int first,
                             const int count,
                             double& sum_log1m_result,
                             double& dsum_log1m_result,
                             double& ddsum_log1m_result)
{
  double    a, b, cval, zstar, tsum_log1m_result, tdsum_log1m_result;
  int       j, leftover, iloop;
  ARRAY_1D  txpos, txposdir1, txposdir2, txposdir3;
  double    FRESULT;

  FRESULT             = 0;
  tsum_log1m_result   = 0;
  tdsum_log1m_result  = 0;
  sum_log1m_result    = 0;
  dsum_log1m_result   = 0;
  ddsum_log1m_result  = 0;

  txpos     = &xpos[first - 1];
  txposdir1 = &xposdir1[first - 1];
  txposdir2 = &xposdir2[first - 1];
  txposdir3 = &xposdir3[first - 1];

  for (iloop = 1 ; iloop <= (count >> 8) ; iloop++)
  {
    ddsum_log1m_result  += ddsum_log1m(txpos, txposdir1, txposdir2, 1, 256, tsum_log1m_result, tdsum_log1m_result);
    sum_log1m_result    += tsum_log1m_result;
    dsum_log1m_result   += tdsum_log1m_result;

    a = 0;
    b = 1;

    for (j = 1 ; j <= 256 ; j++)
    {
      cval                = acc_cval[j];
      cval                = cval * txposdir3[j];
      acc_cval[j]         = cval;
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - 3 * exp_shift[j] + 0x10);
      zstar               = compli[j];
      zstar               = zstar * zstar * zstar;
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    }

    FRESULT -= a / b;

    txpos     = &txpos[256];
    txposdir1 = &txposdir1[256];
    txposdir2 = &txposdir2[256];
    txposdir3 = &txposdir3[256];
  }

  leftover = count & 0xFF;

  if (leftover > 0)
  {
    ddsum_log1m_result  += ddsum_log1m(txpos, txposdir1, txposdir2, 1, leftover, tsum_log1m_result, tdsum_log1m_result);
    sum_log1m_result    += tsum_log1m_result;
    dsum_log1m_result   += tdsum_log1m_result;

    a = 0;
    b = 1;

    for (j = 1 ; j <= leftover ; j++)
    {
      cval                = acc_cval[j];
      cval                = cval * txposdir3[j];
      acc_cval[j]         = cval;
      EXP_OF_DOUBLE(cval) = (short)(EXP_OF_DOUBLE(cval) - 3 * exp_shift[j] + 0x10);
      zstar               = compli[j];
      zstar               = zstar * zstar * zstar;
      a                   = a * zstar + b * cval;
      b                   = b * zstar;
    }

    FRESULT -= a / b;
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

#else

// SLOW VERSIONS-- must fix 'make' to remove forward derivs of these
// These are never actually called-- only used as templates by AD
double AdtDiff::sum_log1m(const ARRAY_1D xpos/*count*/,
                          const int first,
                          const int count)
{
  int     ixpos;
  double  FRESULT;

  FRESULT = 0;

  for (ixpos = 0 ; ixpos < count ; ixpos++)
  {
    FRESULT += log1p(-xpos[first + ixpos]);
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::dsum_log1m(const ARRAY_1D xpos/*count*/,
                           const ARRAY_1D xposdir1/*count*/,
                           const int first,
                           const int count,
                           double& sum_log1m_result)
{
  int     ixpos;
  double  FRESULT;

  FRESULT           = 0;
  sum_log1m_result  = 0;

  for (ixpos = 0 ; ixpos < count ; ixpos++)
  {
    sum_log1m_result += log1p(-xpos[first + ixpos]);
    FRESULT           -= xposdir1[first + ixpos] / (1 - xpos[first + ixpos]);
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::ddsum_log1m(const ARRAY_1D xpos/*count*/,
                            const ARRAY_1D xposdir1/*count*/,
                            const ARRAY_1D xposdir2/*count*/,
                            const int first,
                            const int count,
                            double& sum_log1m_result,
                            double& dsum_log1m_result)
{
  int     ixpos;
  double  invo, invo1;
  double  FRESULT;

  FRESULT           = 0;
  sum_log1m_result  = 0;
  dsum_log1m_result = 0;

  for (ixpos = 0 ; ixpos < count ; ixpos++)
  {
    sum_log1m_result  += log1p(-xpos[first + ixpos]);
    invo               = 1.0 / (1.0 - xpos[first + ixpos]);
    invo1              = xposdir1[first + ixpos] * invo;
    dsum_log1m_result -= invo1;
    FRESULT            -= xposdir2[first + ixpos] * invo * invo1;
  }

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::dddsum_log1m(const ARRAY_1D xpos/*count*/,
                             const ARRAY_1D xposdir1/*count*/,
                             const ARRAY_1D xposdir2/*count*/,
                             const ARRAY_1D xposdir3/*count*/,
                             const int first,
                             const int count,
                             double& sum_log1m_result,
                             double& dsum_log1m_result,
                             double& ddsum_log1m_result)
{
  int     ixpos;
  double  invo, invo1;
  double  FRESULT;

  FRESULT             = 0;
  sum_log1m_result    = 0;
  dsum_log1m_result   = 0;
  ddsum_log1m_result  = 0;

  for (ixpos = 0 ; ixpos < count ; ixpos++)
  {
    sum_log1m_result   += log1p(-xpos[first + ixpos]);
    invo                = 1.0 / (1.0 - xpos[first + ixpos]);
    invo1               = xposdir1[first + ixpos] * invo;
    dsum_log1m_result  -= invo1;
    invo1               = xposdir2[first + ixpos] * invo * invo1;
    ddsum_log1m_result -= invo1;
    FRESULT             -= 2 * xposdir3[first + ixpos] * invo1 * invo;
  }

  return (FRESULT);
}

#endif

//  ----------------------------------------------------------------------------

double AdtDiff::logdet_and_chol(const ARRAY_2D ain/*nchol,nchol*/,
                                const ARRAY_2D rchol/*nchol,nchol*/,
                                const int nchol)
{
  int     i, j, k;
  double  _h, s;
  double  FRESULT;

  FRESULT = 0;

  // Based on Spelucci routine, but transposed
  // Differs in that diag is replaced with INVERSE to speed up backsub
  // Fastest version would store diagonal & use sum_log
  for (i = 1 ; i <= nchol ; i++)
  {
    _h = ain[i][i];

    for (j = 1 ; j <= i-1 ; j++)
    {
      _h -= rchol[i][j] * rchol[i][j];
    }

#ifndef AD
    if (_h <= 0)
    {
      FRESULT      = QNaN;
      rchol[1][1] = QNaN;

      return (FRESULT);
    }
#endif //AD

    _h          = sqrt(_h);
    FRESULT     += log(_h); // efficiency??
    _h          = 1.0 / _h;
    rchol[i][i] = _h;

    for (k = i + 1 ; k <= nchol ; k++)
    {
      s = 0;

      for (j = 1 ; j <= i - 1 ; j++)
      {
        s += rchol[i][j] * rchol[k][j];
      }

      s           = (ain[i][k] - s) * _h;
      rchol[k][i] = s;
    }
  }

  // FRESULT:= -sum_log( diag_wkspace[1], n);
  FRESULT = 2 * FRESULT;

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

double AdtDiff::logdet_and_chol_neg(const ARRAY_2D neg_ain/*nchol,nchol*/,
                                    const ARRAY_2D rchol/*nchol,nchol*/,
                                    const int nchol)
{
  int     i, j, k;
  double  _h, s;
  double  FRESULT;

  FRESULT = 0;

// Based on Spelucci routine, but transposed
// Differs in that diag is replaced with INVERSE to speed up backsub
// Fastest version would store diagonal & use sum_log
  for (i = 1 ; i <= nchol ; i++)
  {
    _h = -neg_ain[i][i];

    for (j = 1 ; j <= i-1 ; j++)
    {
      _h -= rchol[i][j] * rchol[i][j];
    }

#ifndef AD
    if (_h <= 0)
    {
      FRESULT      = QNaN;
      rchol[1][1] = QNaN;

      return (FRESULT);
    }
#endif //AD

    FRESULT     += log(_h); // efficiency??
    _h          = 1.0 / sqrt(_h);
    rchol[i][i] = _h;

    for (k =i + 1 ; k <= nchol ; k++)
    {
      s = -neg_ain[i][k];

      for (j = 1 ; j <= i - 1 ; j++)
      {
        s -= rchol[i][j] * rchol[k][j];
      }

      rchol[k][i] = s * _h;
    }
  }
  // FRESULT:= -sum_log( diag_wkspace[1], n);

  return (FRESULT);
}

//  ----------------------------------------------------------------------------

void AdtDiff::backsolve_chol(const ARRAY_2D rchol/*nchol,nchol*/,
                             const ARRAY_1D target/*nchol*/,
                             ARRAY_1D sol/*nchol*/,
                             const int nchol)
{
  int     i, k;
  double  sum;

  for (i = 1 ; i <= nchol ; i++)
  {
    sum = target[i];

    for (k = i - 1 ; k >= 1 ; k--)
    {
      sum -= rchol[i][k] * sol[k];
    }

    sol[i] = sum * rchol[i][i];
  }

  for (i = nchol ; i >= 1 ; i--)
  {
    sum = sol[i];

    for (k = i + 1 ; k <= nchol ; k++)
    {
      sum -= rchol[k][i] * sol[k];
    }

    sol[i] = sum * rchol[i][i];
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::to_binc(const ARRAY_2D pars/*d1,d2*/,
                      const int d1,
                      const int d2)
{
  int     dd, id, i1, i2, id_end, id_end1, id_end2;
  double  w;

  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  // Diagonal:
  for (id = 2 ; id <= dd ; id++)
  {
    pars[id][id] = pars[id - 1][id - 1] + log1p(exp(pars[id][id]));
  }

  if (d1 > d2)
  {
    for (i1 = d2 + 1 ; i1 <= d1 ; i1++)
    {
      pars[i1][d2] = pars[i1 - 1][d2] + log1p(exp(pars[i1][d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d1 + 1 ; i2 <= d2 ; i2++)
    {
      pars[d1][i2] = pars[d1][i2 - 1] + log1p(exp(pars[d1][i2]));
    }
  }

  for (i1 = 2 ; i1 <= d1 ; i1++)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1 ; id <= id_end ; id++)
    {
      w                     = inv_logit(pars[i1 + id - 1][id]);
      pars[i1 + id - 1][id] = pars[i1 + id - 2][id] * (1 - w) + w * pars[i1 + id - 1][id + 1];
    }
  }

  for (i2 = 2 ; i2 <= d2 ; i2++)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1 ; id <= id_end ; id++)
    {
      w                     = inv_logit(pars[id][i2 + id - 1]);
      pars[id][i2 + id - 1] = pars[id][i2 + id - 2] * (1 - w) + w * pars[id + 1][i2 + id - 1];
    }
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::from_binc(const ARRAY_2D pars/*d1,d2*/,
                        const int d1,
                        const int d2)
{
  int     dd, id, i1, i2, id_end, id_end1, id_end2;
  double  iw, temp;

  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  // Reverse the sequence
  for (i2 = d2 ; i2 >= 2 ; i2--)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = id_end ; id >= 1 ; id--)
    {
      //w:= inv_logit( pars[id][i2+id-1]);
      //pars[id][i2+id-1]:= pars[id][i2+id-2] * (1-w) + w * pars[id+1][i2+id-1];
      temp                  = pars[id][i2 + id - 2];
      iw                    = (pars[id][i2 + id - 1] - temp) / ( pars[id + 1][i2 + id - 1] - temp);
      pars[id][i2 + id - 1] = logit( iw);
    }
  }

  for (i1 = d1 ; i1 >= 2 ; i1--)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = id_end ; id >= 1 ; id--)
    {
      // w:= inv_logit( pars[i1+id-1][id]);
      // pars[i1+id-1][id]:= pars[i1+id-2][id] * (1-w) + w * pars[i1+id-1][id+1];
      temp                  = pars[i1 + id - 2][id];
      iw                    = (pars[i1 + id - 1][id] - temp) / ( pars[i1 + id - 1][id + 1] - temp);
      pars[i1 + id - 1][id] = logit(iw);
    }
  }

  if (d1 > d2)
  {
    for (i1 = d1 ; i1 >= d2 + 1 ; i1--)
    {
      // pars[i1][d2]:= pars[i1-1][d2] + LN1p( EXP( pars[i1][d2]));
      pars[i1][d2] = log(expm1(pars[i1][d2] - pars[i1 - 1][d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d2 ; i2 >= d1 + 1 ; i2--)
    {
      // pars[d1][i2]:= pars[d1][i2-1] + LN1p( EXP( pars[d1][i2]));
      pars[d1][i2] = log(expm1(pars[d1][i2] - pars[d1][i2 - 1]));
    }
  }

  // Diagonal:
  for (id = dd ; id >= 2 ; id--)
  {
    // pars[id][id]:= pars[id-1][id-1] + log1p( EXP( pars[id][id]));
    pars[id][id] = log(expm1(pars[id][id] - pars[id - 1][id - 1]));
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::to_binc_x11(const ARRAY_1D pars/*d1*/,
                          const int start,
                          const int d1,
                          const int d2)
{
  int     dd, id, i1, i2, id_start, id_end, id_end1, id_end2;
  double  w;

  // Like Binc, but x11 is ignored altogether
  // vectorized array starts with [1,2] in position 1
  // Starts going up diag at x22, and x21 and x12 have only single constraints
  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  // Diagonal:
  for (id = 3 ; id <= dd ; id++)
  {
    pars[start -2 + d2 * (id - 1) + id] = pars[start - 2 + d2 * (id - 1 - 1) + id - 1] + log1p(exp(pars[start - 2 + d2 * (id - 1) + id]));
  }

  if (d1 > d2)
  {
    for (i1 = d2 + 1 ; i1 <= d1 ; i1++)
    {
      pars[start - 2 + d2 * (i1 - 1) + d2] = pars[start - 2 + d2 * (i1 - 1 - 1) + d2] + log1p(exp(pars[start - 2 + d2 * (i1 - 1) + d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d1 + 1 ; i2 <= d2 ; i2++)
    {
      pars[start - 2 + d2 * (d1 - 1) + i2] = pars[start - 2 + d2 * (d1 - 1) + i2 - 1] + log1p(exp(pars[start - 2 + d2 * (d1 - 1) + i2]));
    }
  }

  pars[start - 2 + d2 * (2 - 1) + 1] = pars[start - 2 + d2 * (2 - 1) + 2] - log1p(exp(pars[start - 2 + d2 * (2 - 1) + 1]));
  pars[start - 2 + d2 * (1 - 1) + 2] = pars[start - 2 + d2 * (2 - 1) + 2] - log1p(exp(pars[start - 2 + d2 * (1 - 1) + 2]));

  for (i1 = 2 ; i1 <= d1 ; i1++)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    if (i1 > 2)
    {
      id_start = 1;
    }
    else
    {
      id_start = 2;
    }

    for (id = id_start ; id <= id_end ; id++)
    {
      w                                             = inv_logit(pars[start - 2 + d2 * (i1 + id - 1 - 1) + id]);
      pars[start - 2 + d2 * (i1 + id - 1 - 1) + id] = pars[start - 2 + d2 * (i1 + id - 2 - 1) + id] * (1 - w) + w * pars[start - 2 + d2 * (i1 + id - 1 - 1) + id + 1];
    }
  }

  for (i2 = 2 ; i2 <= d2 ; i2++)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    if (i2 > 2)
    {
      id_start = 1;
    }
    else
    {
      id_start = 2;
    }

    for (id = id_start ; id <= id_end ; id++)
    {
      w                                             = inv_logit(pars[start - 2 + d2 * (id - 1) + i2 + id - 1]);
      pars[start - 2 + d2 * (id - 1) + i2 + id - 1] = pars[start - 2 + d2 * (id - 1) + i2 + id - 2] * (1 - w) + w * pars[start - 2 + d2 * (id + 1 - 1) + i2 + id - 1];
    }
  }
}

//---------------------------------------------------------------------------

// current limitations of my AD force this workaround:

void AdtDiff::to_binc_x11_2(const ARRAY_2D pars/*nnnn, d1*/,
                            const int nnnn,
                            const int iiii,
                            const int start,
                            const int d1,
                            const int d2)
{
  int     dd, id, i1, i2, istart, id_end, id_end1, id_end2;
  double  w, lower;

  // pars[start] is elt[1,2] of matrix-- [1,1] doesn't exist
  dd = 0;

  if (d1 == 1)
  {
    dd = d2;
  }
  else if (d2 == 1)
  {
    dd = d1;
  }

  if (dd != 0)
  {
    pars[iiii][start] = log1p(exp(pars[iiii][start]));

    for (id = 3 ; id <= dd ; id++)
    {
      pars[iiii][start - 2 + id] = pars[iiii][start - 3 + id] + log1p(exp(pars[iiii][start - 2 + id]));
    }
  }
  else
  {
    if (d1 > d2)
    {
      dd = d2;
    }
    else
    {
      dd = d1;
    }

    // Diagonal: hardwiring p(1,1)=0
    pars[iiii][start - 2 + (2 - 1) * d2 + 2] = log1p(exp(pars[iiii][start - 2 + (2 - 1) * d2 + 2]));

    for (id = 3 ; id <= dd ; id++)
    {
      pars[iiii][start - 2 + (id - 1) * d2 + id]= pars[iiii][start - 2 + (id - 1 - 1) * d2 + id - 1] + log1p(exp(pars[iiii][start - 2 + (id - 1) * d2 + id]));
    }

    if (d1 > d2)
    {
      istart = d2 + 1;

      if (d2 == 1)
      {
        pars[iiii][start - 2 + (istart - 1) * d2 + d2]  = log1p(exp(pars[iiii][start - 2 + (istart - 1) * d2 + d2]));
        istart                                          = istart + 1;
      }

      for (i1 = istart ; i1 <= d1 ; i1++)
      {
        pars[iiii][start - 2 + (i1 - 1) * d2 + d2] = pars[iiii][start - 2 + (i1 - 1 - 1) * d2 + d2] + log1p(exp(pars[iiii][start - 2 + (i1 - 1) * d2 + d2]));
      }
    }
    else if (d1 < d2)
    {
      istart = d1 + 1;

      if (d1 == 1)
      {
        pars[iiii][start - 2 + (d1 - 1) * d2 + istart]  = log1p(exp(pars[iiii][start - 2 + (d1 - 1) * d2 + istart]));
        istart                                          = istart + 1;
      }

      for (i2 = istart ; i2 <= d2 ; i2++)
      {
        pars[iiii][start - 2 + (d1 - 1) * d2 + i2] = pars[iiii][start - 2 + (d1 - 1) * d2 + i2 - 1] + log1p(exp(pars[iiii][start - 2 + (d1 - 1) * d2 + i2]));
      }
    }

    for (i1 = 2 ; i1 <= d1 ; i1++)
    {
      id_end1 = d2 - 1;
      id_end2 = 1 + d1 - i1;

      if (id_end1 > id_end2)
      {
        id_end = id_end2;
      }
      else
      {
        id_end = id_end1;
      }

      for (id = 1 ; id <= id_end ; id++)
      {
        if ((i1 > 2) || (id > 1))
        {
          lower = pars[iiii][start - 2 + (i1 + id - 2 - 1) * d2 + id];
        }
        else
        {
          lower = 0;
        }

        w                                                   = inv_logit(pars[iiii][start - 2 + (i1 + id - 1 - 1) * d2 + id]);
        pars[iiii][start - 2 + (i1 + id - 1 - 1) * d2 + id] = lower * (1 - w) + w * pars[iiii][start - 2 + (i1 + id - 1 - 1) * d2 + id + 1];
      }
    }

    for (i2 = 2 ; i2 <= d2 ; i2++)
    {
      id_end1 = d1 - 1;
      id_end2 = 1 + d2 - i2;

      if (id_end1 > id_end2)
      {
        id_end = id_end2;
      }
      else
      {
        id_end = id_end1;
      }

      for (id = 1 ; id <= id_end ; id++)
      {
        if ((i2 > 2) || (id > 1))
        {
          lower = pars[iiii][start - 2 + (id - 1) * d2 + i2 + id - 2];
        }
        else
        {
          lower = 0;
        }

        w                                                   = inv_logit(pars[iiii][start - 2 + (id - 1) * d2 + i2 + id - 1]);
        pars[iiii][start - 2 + (id - 1) * d2 + i2 + id - 1] = lower * (1 - w) + w * pars[iiii][start - 2 + (id + 1 - 1) * d2 + i2 + id - 1];
      }
    }
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::from_binc_x11(const ARRAY_1D pars/*d1*/,
                            const int start,
                            const int d1,
                            const int d2)
{
  int     dd, id, i1, i2, istart, id_end, id_end1, id_end2;
  double  lower;

  dd = 0;

  if (d1 == 1)
  {
    dd = d2;
  }
  else if (d2 == 1)
  {
    dd = d1;
  }

  if (dd != 0)
  {
    for (id = dd ; id >= 3 ; id--)
    {
      pars[start - 2 + id] = log(expm1(pars[start - 2 + id] - pars[start - 3 + id]));
    }

    pars[start] = log(expm1(pars[start]));

  }
  else
  {
    if (d1 > d2)
    {
      dd = d2;
    }
    else
    {
      dd = d1;
    }

    // Reverse the sequence

    for (i2 = d2 ; i2 >= 2 ; i2--)
    {
      id_end1 = d1 - 1;
      id_end2 = 1 + d2 - i2;

      if (id_end1 > id_end2)
      {
        id_end = id_end2;
      }
      else
      {
        id_end = id_end1;
      }

      for (id = id_end ; id >= 1 ; id--)
      {
        if ((i2 > 2) || (id > 1))
        {
          lower = pars[start - 2 + (id - 1) * d2 + i2 + id - 2];
        }
        else
        {
          lower = 0;
        }

        // w:= inv_logit( pars[iiii][start-2+(id-1)*d2+i2+id-1]);
        // pars[iiii][start-2+(id-1)*d2+i2+id-1]:=  lower * (1-w) + w * pars[iiii][start-2+(id-1+1)*d2+i2+id-1];
        pars[start - 2 + (id - 1) * d2 + i2 + id - 1] = logit((pars[start - 2 + (id - 1) * d2 + i2 + id - 1] - lower)
                                                      / (pars[start - 2 + (id - 1 + 1) * d2 + i2 + id - 1] - lower));
      }
    }

    for (i1 = d1 ; i1 >= 2 ; i1--)
    {
      id_end1 = d2 - 1;
      id_end2 = 1 + d1 - i1;

      if (id_end1 > id_end2)
      {
        id_end = id_end2;
      }
      else
      {
        id_end = id_end1;
      }

      for (id = id_end ; id >= 1 ; id--)
      {
        if ((i1 > 2) || (id > 1))
        {
          lower = pars[start - 2 + (i1 + id - 2 - 1) * d2 + id];
        }
        else
        {
          lower = 0;
        }

        // w:= inv_logit( pars[start-2+(i1+id-1-1)*d2+id]);
        // pars[start-2+(i1+id-1-1)*d2+id]:= lower * (1-w) + w * pars[iiii][start-2+(i1+id-1-1)*d2+id+1];
        pars[start - 2 + d2 * (i1 + id - 1 - 1) + id] = logit((pars[start - 2 + d2 * (i1 + id - 1 - 1) + id] - lower)
                                                      / (pars[start - 2 + d2 * (i1 + id - 1 - 1) + id + 1] - lower));
      }
    }

    if (d1 > d2)
    {
      istart = d2 + 1;

      if (d2 == 1)
      {
        istart = istart + 1;
      }

      for (i1 = d1 ; i1 >= istart ; i1--)
      {
        // pars[start-2+d2*(i1-1)+d2]:= pars[start-2+d2*(i1-1-1)+d2] + LN1p( EXP( pars[start-2+d2*(i1-1)+d2]));
        pars[start - 2 + d2 * (i1 - 1) + d2] = log(expm1(pars[start - 2 + d2 * (i1 - 1) + d2] - pars[start - 2 + d2 * (i1 - 1 - 1) + d2]));
      }

      if (d2 == 1)
      {
        pars[start - 2 + d2 * (istart - 2) + d2] = log(expm1(pars[start - 2 + (istart - 2) * d2 + d2]));
      }
    }
    else if (d1 < d2)
    {
      istart = d1 + 1;

      if (d1 == 1)
      {
        istart = istart + 1;
      }

      for (i2 = d2 ; i2 >= istart ; i2--)
      {
        // pars[start-2+d2*(d1-1)+i2]:= pars[start-2+d2*(d1-1)+i2-1] + LN1p( EXP( pars[start-2+d2*(d1-1)+i2]));
        pars[start - 2 + d2 * (d1 - 1) + i2] = log(expm1(pars[start - 2 + d2 * (d1 - 1) + i2] - pars[start - 2 + d2 * (d1 - 1) + i2 - 1]));
      }

      if (d1 == 1)
      {
        pars[start - 2 + (d1 - 1) * d2 + istart - 1] = log(expm1(pars[start - 2 + (d1 - 1) * d2 + istart - 1]));
      }
    }

    // Diagonal:
    for (id = dd ; id >= 3 ; id--)
    {
      // pars[start-2+d2*(id-1)+id]:= pars[start-2+d2*(id-1-1)+id-1] + log1p( EXP( pars[start-2+d2*(id-1)+id]));
      pars[start - 2 + d2 * (id - 1) + id] = log(expm1(pars[start - 2 + d2 * (id - 1) + id] - pars[start - 2 + d2 * (id - 1 - 1) + id - 1]));
    }

    pars[start - 2 + (2 - 1) * d2 + 2] = log(expm1(pars[start - 2 + (2 - 1) * d2 + 2]));
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::to_binc1(const ARRAY_1D pars/*d1*/,
                       const int start,
                       const int d1,
                       const int d2)
{
  int     dd, id, i1, i2, id_end, id_end1, id_end2;
  double  w, lower;

  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  // Diagonal: hardwiring p(1,1)=0
  pars[start - 1 + (2 - 1) * d2 + 2] = log1p(exp(pars[start - 1 + (2 - 1) * d2 + 2]));

  for (id = 3 ; id <= dd ; id++)
  {
    pars[start - 1 + (id - 1) * d2 + id] = pars[start - 1 + (id - 1 - 1) * d2 + id - 1] + log1p(exp(pars[start - 1 + (id - 1) * d2 + id]));
  }

  if (d1 > d2)
  {
    for (i1 = d2 + 1 ; i1 <= d1 ; i1++)
    {
      pars[start - 1 + (i1 - 1) * d2 + d2] = pars[start - 1 + (i1 - 1 - 1) * d2 + d2] + log1p(exp(pars[start - 1 + (i1 - 1) * d2 + d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d1 + 1 ; i2 <= d2 ; i2++)
    {
      pars[start - 1 + (d1 - 1) * d2 + i2] = pars[start - 1 + (d1 - 1) * d2 + i2 - 1] + log1p(exp(pars[start - 1 + (d1 - 1) * d2 + i2]));
    }
  }

  for (i1 = 2 ; i1 <= d1 ; i1++)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1 ; id <= id_end ; id++)
    {
      if ((i1 > 2) || (id > 1))
      {
        lower = pars[start - 1 + (i1 + id - 2 - 1) * d2 + id];
      }
      else
      {
        lower = 0;
      }

      w                                             = inv_logit(pars[start - 1 + (i1 + id - 1 - 1) * d2 + id]);
      pars[start - 1 + (i1 + id - 1 - 1) * d2 + id] = lower * (1 - w) + w * pars[start - 1 + (i1 + id - 1 - 1) * d2 + id + 1];
    }
  }

  for (i2 = 2 ; i2 <= d2 ; i2++)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1 ; id <= id_end ; id++)
    {
      if ((i2 > 2) || (id > 1))
      {
        lower = pars[start - 1 + (id - 1) * d2 + i2 + id - 2];
      }
      else
      {
        lower = 0;
      }

      w                                             = inv_logit(pars[start - 1 + (id - 1) * d2 + i2 + id - 1]);
      pars[start - 1 + (id - 1) * d2 + i2 + id - 1] = lower * (1 - w) + w * pars[start - 1 + (id + 1 - 1) * d2 + i2 + id - 1];
    }
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::to_binc12(const ARRAY_2D pars/*nnnn, d1*/,
                        const int nnnn,
                        const int iiii,
                        const int start,
                        const int d1,
                        const int d2)
{
  int     dd, id, i1, i2, id_end, id_end1, id_end2;
  double  w, lower;

  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  // Diagonal: hardwiring p(1,1)=0
  pars[iiii][start - 1 + (2 - 1) * d2 + 2] = log1p(exp(pars[iiii][start - 1 + (2 - 1) * d2 + 2]));

  for (id = 3 ; id <= dd ; id++)
  {
    pars[iiii][start - 1 + (id - 1) * d2 + id] = pars[iiii][start - 1 + (id - 1 - 1) * d2 + id - 1] + log1p(exp(pars[iiii][start - 1 + (id - 1) * d2 + id]));
  }

  if (d1 > d2)
  {
    for (i1 = d2 + 1 ; i1 <= d1 ; i1++)
    {
      pars[iiii][start - 1 + (i1 - 1) * d2 + d2] = pars[iiii][start - 1 + (i1 - 1 - 1) * d2 + d2] + log1p(exp(pars[iiii][start - 1 + (i1 - 1) * d2 + d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d1 + 1 ; i2 <= d2 ; i2++)
    {
      pars[iiii][start - 1 + (d1 - 1) * d2 + i2] = pars[iiii][start - 1 + (d1 - 1) * d2 + i2 - 1] + log1p(exp(pars[iiii][start - 1 + (d1 - 1) * d2 + i2]));
    }
  }

  for (i1 = 2 ; i1 < d1 ; i1++)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1 ; id <= id_end ; id++)
    {
      if ((i1 > 2) || (id > 1))
      {
        lower = pars[iiii][start - 1 + (i1 + id - 2 - 1) * d2 + id];
      }
      else
      {
        lower = 0;
      }

      w                                                   = inv_logit(pars[iiii][start - 1 + (i1 + id - 1 - 1) * d2 + id]);
      pars[iiii][start - 1 + (i1 + id - 1 - 1) * d2 + id] = lower * (1 - w) + w * pars[iiii][start - 1 + (i1 + id - 1 - 1) * d2 + id + 1];
    }
  }

  for (i2 = 2 ; i2 <= d2 ; i2++)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = 1; id <= id_end ; id++)
    {
      if ((i2 > 2) || (id > 1))
      {
        lower = pars[iiii][start - 1 + (id - 1) * d2 + i2 + id - 2];
      }
      else
      {
        lower = 0;
      }

      w                                                   = inv_logit(pars[iiii][start - 1 + (id - 1) * d2 + i2 + id - 1]);
      pars[iiii][start - 1 + (id - 1) * d2 + i2 + id - 1] = lower * (1 - w) + w * pars[iiii][start - 1 + (id + 1 - 1) * d2 + i2 + id - 1];
    }
  }
}

//-----------------------------------------------------------------------------

void AdtDiff::from_binc1(const ARRAY_1D pars/*d1*/,
                         const int start,
                         const int d1,
                         const int d2)
{
  int     dd, id, i1, i2, id_end, id_end1, id_end2;
  double  iw, lower;

  if (d1 > d2)
  {
    dd = d2;
  }
  else
  {
    dd = d1;
  }

  for (i2 = d2 ; i2 >= 2 ; i2--)
  {
    id_end1 = d1 - 1;
    id_end2 = 1 + d2 - i2;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = id_end ; id >= 1 ; id--)
    {
      //w:= inv_logit( pars[start-1+(id-1)*d2+i2+id-1]);
      //pars[start-1+(id-1)*d2+i2+id-1]:= pars[start-1+(id-1)*d2+i2+id-2] * (1-w) + w * pars[start-1+(id+1-1)*d2+i2+id-1];

      if ((id > 1) || (i2 > 2))
      {
        lower = pars[start - 1 + (id - 1) * d2 + i2 + id - 2];
      }
      else
      {
        lower = 0;
      }

      iw                                            = (pars[start - 1 + (id - 1) * d2 + i2 + id - 1] - lower) / (pars[start - 1 + (id + 1 - 1) * d2 + i2 + id - 1] - lower);
      pars[start - 1 + (id - 1) * d2 + i2 + id - 1] = logit(iw);
    }
  }

  for (i1 = d1 ; i1 >= 2 ; i1--)
  {
    id_end1 = d2 - 1;
    id_end2 = 1 + d1 - i1;

    if (id_end1 > id_end2)
    {
      id_end = id_end2;
    }
    else
    {
      id_end = id_end1;
    }

    for (id = id_end ; id >= 1 ; id--)
    {
      // w:= inv_logit( pars[start-1+(i1+id-1-1)*d2+id]);
      // pars[start-1+(i1+id-1-1)*d2+id]:= pars[start-1+(i1+id-2-1)*d2+id] * (1-w) + w * pars[start-1+(i1+id-1-1)*d2+id+1];
      if ((id > 1) || (i1 > 2))
      {
        lower = pars[start - 1 + (i1 + id - 2 - 1) * d2 + id];
      }
      else
      {
        lower = 0;
      }

      iw                                            = (pars[start - 1 + (i1 + id - 1 - 1) * d2 + id] - lower) / ( pars[start - 1 + (i1 + id - 1 - 1) * d2 + id + 1] - lower);
      pars[start - 1 + (i1 + id - 1 - 1) * d2 + id] = logit(iw);
    }
  }

  if (d1 > d2)
  {
    for (i1 = d1 ; i1 >= d2 + 1 ; i1--)
    {
      // pars[start-1+(i1-1)*d2+d2]:= pars[start-1+(i1-1-1)*d2+d2] + LN1p( EXP( pars[start-1+(i1-1)*d2+d2]));
      pars[start - 1 + (i1 - 1) * d2 + d2] = log(expm1(pars[start - 1 + (i1 - 1) * d2 + d2] - pars[start - 1 + (i1 - 1 - 1) * d2 + d2]));
    }
  }
  else if (d1 < d2)
  {
    for (i2 = d2 ; i2 >= d1+1 ; i2--)
    {
      // pars[start-1+(d1-1)*d2+i2]:= pars[start-1+(d1-1)*d2+i2-1] + LN1p( EXP( pars[start-1+(d1-1)*d2+i2]));
      pars[start - 1 + (d1 - 1) * d2 + i2] = log(expm1(pars[start - 1 + (d1 - 1) * d2 + i2] - pars[start - 1 + (d1 - 1) * d2 + i2 - 1]));
    }
  }

  // Diagonal:
  for (id = dd ; id >= 3 ; id--)
  {
    // pars[start-1+(id-1)*d2+id]:= pars[start-1+(id-1-1)*d2+id-1] + log1p( EXP( pars[start-1+(id-1)*d2+id]));
    pars[start - 1 + (id - 1) * d2 + id] = log(expm1(pars[start - 1 + (id - 1) * d2 + id] - pars[start - 1 + (id - 1 - 1) * d2 + id - 1]));
  }

  // p(1,1) is hardwired to 0 so...
  pars[start - 1 + (2 - 1) * d2 + 2] = log(expm1(pars[start - 1 + (2 - 1) * d2 + 2]));
}

//-----------------------------------------------------------------------------

double AdtDiff::quadform(const ARRAY_1D xqf/*nqf*/,
                         const ARRAY_2D hqf/*nqf,nqf*/,
                         const int nqf)
{
  int     i, j;
  double  sumbo;
  double  FRESULT;

  FRESULT = 0;

  for (i = 1 ; i <= nqf ; i++)
  {
    sumbo = 0;

    for (j = 1 ; j <= nqf ; j++)
    {
      sumbo += hqf[i][j] * xqf[j];
    }

    FRESULT += xqf[i] * sumbo;
  }

  return (FRESULT);
}

//-----------------------------------------------------------------------------

void AdtDiff::quadform_b(const ARRAY_1D xqf/*nqf*/,
                         ARRAY_1D xqf_b/*nqf*/,
                         const ARRAY_2D hqf/*nqf,nqf*/,
                         const int nqf,
                         double& xqf_wt)
{
  int     i, j;
  double  sumbo;

  for (i = 1 ; i <= nqf ; i++)
  {
    sumbo = 0;

    for (j = 1 ; j <= nqf ; j++)
    {
      sumbo += hqf[i][j] * xqf[j];
    }

    xqf_b[i] = 2 * xqf_wt * sumbo;
  }
}

//-----------------------------------------------------------------------------

double AdtDiff::quadform_d(const ARRAY_1D xqf/*nqf*/,
                           const ARRAY_1D xqf_dir/*nqf*/,
                           const ARRAY_2D hqf/*nqf,nqf*/,
                           const int nqf,
                           double& hxh)
{
  int     i, j;
  double  sumbo;
  double  FRESULT;

  FRESULT = 0;
  hxh = 0;

  for (i = 1 ; i <= nqf ; i++)
  {
    sumbo = 0;

    for (j = 1 ; j <= nqf ; j++)
    {
      sumbo += hqf[i][j] * xqf[j];
    }

    hxh     += sumbo * xqf[i];
    FRESULT  += 2 * xqf_dir[i] * sumbo;
  }

  return (FRESULT);
}

//-----------------------------------------------------------------------------

void AdtDiff::quadform_b_d(const ARRAY_1D xqf/*nqf*/,
                           const ARRAY_1D xqf_dir/*nqf*/,
                           ARRAY_1D xqf_b/*nqf*/,
                           ARRAY_1D xqf_bd/*nqf*/,
                           const ARRAY_2D hqf/*nqf,nqf*/,
                           const int nqf,
                           double& xqf_wt)
{
  quadform_b(xqf_dir, xqf_bd, hqf, nqf, xqf_wt);
  quadform_b(xqf, xqf_b, hqf, nqf, xqf_wt);
}

//-----------------------------------------------------------------------------

double AdtDiff::asymp(const double _x,
                      const double _thresh)
{
  //OUTPUT: x if x<thresh, otherwise something below the asymptote 3*thresh
  double  v1, v2, v4, v8, v16, v32, v64, v;
  double  FRESULT;

  FRESULT = 0;

#ifndef AD
  if (isinf(_x))
  {
    FRESULT = 3*_thresh;

    return (FRESULT);
  }
#endif //AD

  v1     = 8 * _x / (15 * _thresh + _x);
  v2     = v1 * v1;
  v4     = v2 * v2;
  v8     = v4 * v4;
  v16    = v8 * v8;
  v32    = v16 * v16;
  v64    = v32 * v32;
  v      = v64 / (1 + v64);
  FRESULT = _x * (1 - v) + v * 3 * _thresh;

  return (FRESULT);
}

//-----------------------------------------------------------------------------

// Code below slight mod of Paul Godfrey's implementation of Lanczos approx to gamma
// Diffrentiable!

double AdtDiff::lgamma2(const double _x)
{
  int     _k;
  double  _s, _ss;
  double  FRESULT;

  // t=z+g;
  _s = 0;

  for (_k = n_gamlanc ; _k >= 0 ; _k--)
  {
    _s += gamlanc_cof[_k + 1] / (_x +_k);
  }

  _s     += gamlanc_cof[0];
  _ss     = _x + n_gamlanc - 0.5;
  FRESULT  = log(_s * sqrt_two_pi) + (_x - 0.5) * log(_ss) - _ss;

  return (FRESULT);
}

//-----------------------------------------------------------------------------

double AdtDiff::nearlymin(const double _a,
                          const double _b)
{
  // AD-_able version of min: generalized mean with p = -16.
  // _a & _b>0. Can't exceed min( _a, _b) _by more than 5%
  double  _bb, _b2, _b4, _b8, _b16, m;
  double  FRESULT;

  _bb     = _b / _a;
  _b2     = _bb * _bb;
  _b4     = _b2 * _b2;
  _b8     = _b4 * _b4;
  _b16    = _b8 * _b8;
  m       = 0.5 * _b16 / (1 + _b16);
  FRESULT  = _a * sqrt(sqrt(sqrt(sqrt(m))));

  return (FRESULT);
}

//-----------------------------------------------------------------------------

double AdtDiff::nearlymax(const double _a,
                          const double _b)
{
  // AD-_able version of max: generalized mean with p = +16.
  // _a & _b>0. Can't fall _below max( _a, _b) _by more than 5%
  double  _bb, _b2, _b4, _b8, _b16, m;
  double  FRESULT;

  _bb     = _a / _b;
  _b2     = _bb * _bb;
  _b4     = _b2 * _b2;
  _b8     = _b4 * _b4;
  _b16    = _b8 * _b8;
  m       = 0.5 * _b16 / (1 + _b16);
  FRESULT  = 1.0 / (_a * sqrt(sqrt(sqrt(sqrt(m)))));

  return (FRESULT);
}

//-----------------------------------------------------------------------------

double AdtDiff::laugamp(const double _y,
                        const double _p,
                        const double _lgamma_p,
                        const bool _calc_lgamma_p)
{
//OUTPUT: gammp( _y, _p)-- only checked for 0.5<=_p<=1. Fully differentiable.
// if div_lgamma is FALSE, FRESULT is NOT divided by lgamma( _p)
  int     _i;
  double  _yy, _f, _cc, _a, _lgamma_p_int, twelve;
  double  FRESULT;

#ifndef AD
  if (isinf(_y))
  {
    FRESULT = 1;

    return (FRESULT);
  }
#endif //AD

  twelve  = 12;
  _yy     = asymp(_y, twelve); // guaranteed to give 1 for _y>36, this range of _p, so

  if (_calc_lgamma_p)
  {
    _lgamma_p_int = lgamma(_p);
  }
  else
  {
    _lgamma_p_int = _lgamma_p;
  }

  _f      = exp(_p * log(_yy) - _lgamma_p_int - _yy); // still need div by _p
  // if (_f .eq. 0.0) return -- omit since won't crash and IF is bad for AD
  _cc     = 1;
  FRESULT  = 1;
  _a      = _p;

  for (_i = 1 ; _i <= n_laugamp ; _i++)
  {
    _a++;
    _cc     = _cc * _yy / _a;
    FRESULT += _cc;
  }

  FRESULT *= _f / _p;

  return (FRESULT);
}

//  -expm1(-(s^b)) + s * exp( lgamma( 1-1/b)) * pgamma( s^b, shape=1-1/b, lower.tail=FALSE)

//-----------------------------------------------------------------------------

#ifndef AD

void AdtDiff::prepare_for_chint(const int _ncheb)
{
  int       _i, _j, _uid, _ncheb2;
  double    _sum;
  ARRAY_1D  _dotto, _coseq;
  ARRAY_1L  _idx;

  if (_ncheb == ncheb)
  {
    return;
  }

  if (_ncheb > 0)
  {
    destroy(cheb_x);
    destroy(cheb_wt);
  }

  ncheb   = _ncheb;
  incheb  = 1.0 / ncheb;
  _ncheb2 = ncheb / 2;

  AdtArrayPlan  A1(1, _ncheb2);
  AdtArrayPlan  A2(0, ncheb + 1);
  AdtArrayPlan  A3(1, ncheb);

  A1.create(MemAllocator, _dotto);
  A1.create(MemAllocator, _idx);
  A2.create(MemAllocator, _coseq);
  A3.create(MemAllocator, cheb_x);
  A3.create(MemAllocator, cheb_wt);

  _dotto[1] = 2;
  _idx[1]   = 0;

  for (_i = 1 ; _i<= _ncheb2 - 1 ; _i++)
  {
    _dotto[_i + 1] = 2.0 / (2 *_i + 1) - 2 / (2 * _i - 1);
    _idx[_i + 1]   = _i;
  }

  for (_i = 1 ; _i <= ncheb ; _i++)
  {
    cheb_x[_i] = cos(M_PI * (_i - 0.5) / ncheb);
  }

  // Could do these with recurrence relation
  for (_i = 0 ; _i <= _ncheb2 - 1 ; _i++)
  {
    _coseq[_i]         = cos(_i * M_PI / ncheb);
    _coseq[ncheb - _i] = -_coseq[_i];
  }

  _coseq[_ncheb2] = 0;

  for (_i = 1 ; _i <= _ncheb2 ; _i++)
  {
    _sum = 0;

    for (_j = 1 ; _j <= _ncheb2 ; _j++)
    {
      _uid = _idx[_j];

      if (_uid >= ncheb)
      {
        _uid = 2 * ncheb - _uid;
      }

      _sum      += _dotto[_j] * _coseq[_uid];
      _idx[_j]  += 2 * (_j - 1);

      if (_idx[_j] >= 2 * ncheb)
      {
        _idx[_j] -= 2 * ncheb;
      }
    }

    cheb_wt[_i]             = _sum  * incheb;
    cheb_wt[ncheb + 1 - _i] = cheb_wt[_i];
  }

  destroy(_dotto);
  destroy(_idx);
  destroy(_coseq);
}

#endif //AD
