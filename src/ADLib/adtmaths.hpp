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
//    adtmaths.hpp
//
//  Purpose:
//    This file includes declarations of useful mathematic functions ported
//    from Mark Bravingtons Delphi code.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTMATHS_HPP__
#define __ADTMATHS_HPP__


#ifndef AD

#ifdef _MSC_VER
  #ifndef __STDC__
    #define __STDC__ 1
  #endif

  #ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
  #endif

  #ifndef _USE_MATH_DEFINES
    // Needed under VC to include BSD math defines such as M_PI
    #define _USE_MATH_DEFINES
  #endif
#endif

// Define C++ standard thread local storage keyword. Different implementations
// on VC and GCC
#ifdef __GNUC__
  #define mthread_local  __thread
#endif //__GNUC__

#ifdef _MSC_VER
  #define mthread_local  __declspec(thread)
#endif

extern "C"
{
  // MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
  // MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
  // MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
  // MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
  // MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
  // MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
  // MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
  // MSVC++ 7.0  _MSC_VER == 1300
  // MSVC++ 6.0  _MSC_VER == 1200
  // MSVC++ 5.0  _MSC_VER == 1100
  #ifdef _MSC_VER

    #if _MSC_VER >= 1700

      double __ieee754_lgamma_r(double,int*);
      double __ieee754_gamma_r(double,int*);
      double __ieee754_gamma(double);
      int    __ieee754_rem_pio2(double,double*);

      #define lgamma_r  __ieee754_lgamma_r
      #define gamma_r   __ieee754_gamma_r
      #define gamma     __ieee754_gamma
      #define rem_pio2  __ieee754_rem_pio2

    #elif _MSC_VER >= 1400

      double __ieee754_acosh(double);
      double __ieee754_atanh(double);
      double __ieee754_asinh(double);
      double __ieee754_lgamma_r(double,int*);
      double __ieee754_gamma_r(double,int*);
      double __ieee754_lgamma(double);
      double __ieee754_gamma(double);
      double __ieee754_hypot(double,double);
      double __ieee754_remainder(double,double);
      int    __ieee754_rem_pio2(double,double*);

      #ifdef _SCALB_INT

      double __ieee754_scalb(double,int);

      #else

      double __ieee754_scalb(double,double);

      #endif

      #define acosh     __ieee754_acosh
      #define atanh     __ieee754_atanh
      #define asinh     __ieee754_asinh
      #define lgamma_r  __ieee754_lgamma_r
      #define gamma_r   __ieee754_gamma_r
      #define lgamma    __ieee754_lgamma
      #define gamma     __ieee754_gamma
      #define hypot     __ieee754_hypot
      #define remainder __ieee754_remainder
      #define rem_pio2  __ieee754_rem_pio2
      #define scalb     __ieee754_scalb

      #define __ADD_MISSING__

    #else

      double __ieee754_acosh(double);
      double __ieee754_cosh(double);
      double __ieee754_atanh(double);
      double __ieee754_tanh(double);
      double __ieee754_asinh(double);
      double __ieee754_sinh(double);
      double __ieee754_lgamma_r(double,int*);
      double __ieee754_gamma_r(double,int*);
      double __ieee754_lgamma(double);
      double __ieee754_gamma(double);
      double __ieee754_hypot(double,double);
      double __ieee754_remainder(double,double);
      int    __ieee754_rem_pio2(double,double*);

      #ifdef _SCALB_INT

      double __ieee754_scalb(double,int);

      #else

      double __ieee754_scalb(double,double);

      #endif

      #define acosh     __ieee754_acosh
      #define cosh      __ieee754_cosh
      #define atanh     __ieee754_atanh
      #define tanh      __ieee754_tanh
      #define asinh     __ieee754_asinh
      #define sinh      __ieee754_sinh
      #define lgamma_r  __ieee754_lgamma_r
      #define gamma_r   __ieee754_gamma_r
      #define lgamma    __ieee754_lgamma
      #define gamma     __ieee754_gamma
      #define hypot     __ieee754_hypot
      #define remainder __ieee754_remainder
      #define rem_pio2  __ieee754_rem_pio2
      #define scalb     __ieee754_scalb

      #define __ADD_MISSING__

    #endif

  #endif // _MSC_VER

  void Rf_error(const char *, ...);
  void Rf_warning(const char *, ...);
}

#ifdef __ADD_MISSING__

  extern "C"
  {
    // We need to declare these because VC++ has no such functions in math.h
    // Linux platforms provide this in the system fdlibm library.
    double expm1(double);
    double log1p(double);
  	int    isnan(double);
  	int    finite(double);
  }

  #ifdef __cplusplus
  inline int isinf(double x)
  {
    return (!isnan(x) && !finite(x));
  }
  #endif

#endif


#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdexcept>
#include <map>
#include <list>
#include <algorithm>
#include <string>

#include <Rmath.h>
#include <stdio.h>

#if defined(_MSC_VER)

#define snprintf _snprintf

#endif

#define log_error       Rf_error
#define log_warning     Rf_warning


// ----------------------------------------------------------------------------
// error and warning handlers safe to use in parallelFor() context
// ----------------------------------------------------------------------------
void ts_error(const char* pFormat, ...);
void ts_warning(const char* pFormat, ...);
void ts_printf(const char* pFormat, ...);


// ----------------------------------------------------------------------------

typedef std::basic_string<char> adtstring;

//  ---------------------------------------------------------------------------
//  List of adtstring objects
//  ---------------------------------------------------------------------------
typedef std::list<adtstring>                  adtstringList;
typedef std::list<adtstring>::iterator        adtstringListIter;
typedef std::list<adtstring>::const_iterator  adtstringListConstIter;


// ----------------------------------------------------------------------------

extern const double&  INF;
extern const double&  MINF;
extern const double&  QNaN;
extern const double&  nearly_one;
extern const double   sqrt_two_pi;
extern const double   inv_sqrt_two_pi;

// ----------------------------------------------------------------------------

template<typename T, typename IX>
  const T min(const T* pArray, const IX i1, const IX i2)
  {
    T _Min = pArray[i1];

    assert(i1 < i2);

    for (IX cn = i1 ; cn < i2 ; cn++)
    {
      _Min = _Min > pArray[cn] ? pArray[cn] : _Min;
    }

    return _Min;
  }

// ----------------------------------------------------------------------------

template<typename T, typename IX>
  const T max(const T* pArray, const IX i1, const IX i2)
  {
    T _Max = pArray[i1];

    assert(i1 < i2);

    for (IX cn = i1 ; cn < i2 ; cn++)
    {
      _Max = _Max < pArray[cn] ? pArray[cn] : _Max;
    }

    return _Max;
  }

using std::max;
using std::min;

#endif // AD

//  ----------------------------------------------------------------------------

double  sqr(const double x);
double  inv(const double x);
int     trunc_to_int(const double x);
int     round_to_int(const double x);
double  frac(const double x);
double  pwr(const double x, const double& y);
#ifndef AD
double  pwr(const double x, const int& y);
double  pwr(const double x, const unsigned int& y);
double  pwr(const double x, const long& y);
double  pwr(const double x, const unsigned long& y);
double  pwr(const double x, const short& y);
double  pwr(const double x, const unsigned short& y);
double  pwr(const double x, const char& y);
double  pwr(const double x, const unsigned char& y);
#endif //AD
double  logit(const double x);
double  inv_logit(const double x);
double  scal_logit(const double x);
double  scal_inv_logit(const double x);
double  dinv_logit(const double x);
double  LIL(const double x);
double  rel_delta(const double a, const double b);

// ----------------------------------------------------------------------------

double  exp_cached(const double x);
double  inv_cached(const double x);
double  inv_logit_cached(const double x);

// ----------------------------------------------------------------------------

inline double sign(double x)
{
  if (x == 0)
  {
    return 0.0;
  }
  else
  {
    return ((x < 0) ? -1.0 : 1.0);
  }
}

// ----------------------------------------------------------------------------

inline double sqr(const double x)
{
  return (x * x);
}

// ----------------------------------------------------------------------------

inline double inv(const double x)
{
  return (1.0 / x);
}

// ----------------------------------------------------------------------------

inline double frac(const double x)
{
  return (x - floor(x));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const double& y)
{
  return (R_pow(x, y));
}

// ----------------------------------------------------------------------------
#ifndef AD
inline double pwr(const double x, const int& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const unsigned int& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const long& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const unsigned long& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const short& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const unsigned short& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const char& y)
{
  return (R_pow_di(x, y));
}

// ----------------------------------------------------------------------------

inline double pwr(const double x, const unsigned char& y)
{
  return (R_pow_di(x, y));
}
#endif //AD

#endif //__ADTMATHS_HPP__
