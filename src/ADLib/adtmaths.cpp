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
//    adtmaths.cpp
//
//  Purpose:
//    This file includes implementations of useful mathematic functions ported
//    from Mark Bravingtons Delphi code.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include <stdarg.h>
#include "adtmaths.hpp"
#include "adtparallel.hpp"


struct InitDouble
{
  char  Bytes[8];
};

// ----------------------------------------------------------------------------

const InitDouble  InfinityData      = {'\x7f', '\xf0', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'};
const InitDouble  MinusInfinityData = {'\xff', '\xf0', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00'};
const InitDouble  NearlyOneData     = {'\x3f', '\xef', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff'};
const InitDouble  QNaNData          = {'\xff', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff'};
const double&     INF               = *((double*)&InfinityData);
const double&     MINF              = *((double*)&MinusInfinityData);
const double&     nearly_one        = *((double*)&NearlyOneData);
const double&     QNaN              = *((double*)&QNaNData);
const double      inv_sqrt_two_pi   = 0.3989422804014326779399461;
const double      sqrt_two_pi       = 2.506628274631000502415765;

// ----------------------------------------------------------------------------

mthread_local double  last_exp_x              = 0.0;
mthread_local double  last_exp_result         = 1.0;
mthread_local double  last_inv_x              = 1.0;
mthread_local double  last_inv_result         = 1.0;
mthread_local double  last_inv_logit_x        = 0.0;
mthread_local double  last_inv_logit_result   = 0.5;

// ----------------------------------------------------------------------------

void ts_error(const char* pFormat, ...)
{
  // format error, print to StdErrString
  char sBuffer[4096] = {0};

  va_list args;
  va_start(args, pFormat);
  vsnprintf(sBuffer, sizeof(sBuffer) - 1, pFormat, args);
  va_end(args);

  if (AdtThread::isMainThread())
  {
    // Not multithreaded so use R error function
    Rf_error(sBuffer);
  }
  else
  {
    std::string Msg(sBuffer);

    Msg += "\n";

    // In thread so throw an exception
    throw(Msg);
  }
}

// ----------------------------------------------------------------------------

void ts_warning(const char* pFormat, ...)
{
  // format warning and print to StdOutString
  char sBuffer[4096] = {0};

  va_list args;
  va_start(args, pFormat);
  vsnprintf(sBuffer, sizeof(sBuffer) - 1, pFormat, args);
  va_end(args);

  if (AdtThread::isMainThread())
  {
    AdtParallelStdOutCallback pCallback = getStdOutCallback();

    if (pCallback != 0)
    {
      std::string Msg(sBuffer);

      pCallback(Msg);
    }
    else
    {
      Rf_warning(sBuffer);
    }
  }
  else
  {
    std::string Msg(sBuffer);

    Msg += "\n";

    writeToStdOutString(Msg.c_str());
  }
}

// ----------------------------------------------------------------------------

void ts_printf(const char* pFormat, ...)
{
  // format warning and print to StdOutString
  char sBuffer[4096] = {0};

  va_list args;
  va_start(args, pFormat);
  vsnprintf(sBuffer, sizeof(sBuffer) - 1, pFormat, args);
  va_end(args);

  if (AdtThread::isMainThread())
  {
    AdtParallelStdOutCallback pCallback = getStdOutCallback();

    if (pCallback != 0)
    {
      std::string Msg(sBuffer);

      pCallback(Msg);
    }
    else
    {
      Rprintf(sBuffer);
    }
  }
  else
  {
    writeToStdOutString(sBuffer);
  }
}

// ----------------------------------------------------------------------------

int trunc_to_int(const double x)
{
  #if defined(__GNUG__)

  int i = lrint(floor(x));

  #else

  int i = (int)floor(x);

  #endif

  return (i);
}

// ----------------------------------------------------------------------------

int round_to_int(const double x)
{
  #if defined(__GNUG__)

  int i = lrint(x);

  #else

  int i = (int)(x + 0.5);

  #endif

  return (i);
}

// ----------------------------------------------------------------------------

double logit(const double x)
{
  return ((x == 0) ? MINF : ((x == 1) ? INF : log(x / (1.0 - x))));
}

// ----------------------------------------------------------------------------

double inv_logit(const double x)
{
  // roughly log( double_neg_eps), but this is exact
  return ((x < -36.7363124075975981959901) ? 1.0 : 1.0 / (1.0 + exp(-x)));
}

// ----------------------------------------------------------------------------

double scal_logit(const double x)
{
  return (logit(0.5 + (255.0 / 256.0) * (x - 0.5)));
}

// ----------------------------------------------------------------------------

double scal_inv_logit(const double x)
{
  return ((1.0 + 255.0 * inv_logit(x)) / 256.0);
}

// ----------------------------------------------------------------------------

double dinv_logit(const double x)
{
  if (x > 88.0)
  {
    return (0.0);
  }
  else
  {
    double y = 1.0 / ( 1.0 + exp(x));

    return (y * (1.0 - y));
  }
}

// ----------------------------------------------------------------------------

double LIL(const double x)
{
  return ((x<0) ? x - log1p(exp(x))
                :-log1p(exp(-x)));
}

// ----------------------------------------------------------------------------

double exp_cached(const double x)
{
  if (x == last_exp_x)
  {
    return (last_exp_result);
  }
  else
  {
    last_exp_result = exp(x);
    last_exp_x      = x;

    return (last_exp_result);
  }
}

// ----------------------------------------------------------------------------

double inv_cached(const double x)
{
  if (x == last_inv_x)
  {
    return (last_inv_result);
  }
  else
  {
    last_inv_result = 1.0 / x;
    last_inv_x      = x;

    return (last_inv_result);
  }
}

// ----------------------------------------------------------------------------

double inv_logit_cached(const double x)
{
  if (x == last_inv_logit_x)
  {
    return (last_inv_logit_result);
  }
  else
  {
    last_inv_logit_result = inv_logit(x);
    last_inv_logit_x      = x;

    return (last_inv_logit_result);
  }
}

// ----------------------------------------------------------------------------

double rel_delta(const double a, const double b)
{
  if (a == b)
  {
    return (0.0);
  }
  else
  {
    double dMaxAbs = max(fabs(a), fabs(b));

    return ((dMaxAbs > 0) && (dMaxAbs < INF) ? fabs(a - b) / dMaxAbs
                                             : ((dMaxAbs == 0) ? INF
                                                               : sign(a - b)));
  }
}
