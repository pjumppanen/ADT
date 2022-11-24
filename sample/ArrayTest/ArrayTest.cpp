// ----------------------------------------------------------------------------
// Test code for ADT Arrays.
// ----------------------------------------------------------------------------


#include "ArrayTest.hpp"


const int male    = 1;
const int female  = 2;
const int n_sex   = 2;

// ----------------------------------------------------------------------------

double global_sum(const ARRAY_1D Y/*nBase:nCount*/, int nBase, int nCount)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  for (cn = nBase ; cn < nBase + nCount ; cn++)
  {
    dSum += Y[cn];
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

// < D/D(x) (4 * x) - 5; >
double ArrayTest::polyA(double x)
{
  double dResult;

  dResult = (2 * x * x) - (5 * x) + 3;

  return (dResult);
}

// ----------------------------------------------------------------------------

double ArrayTest::polyB(double x)
{
  double dResult;

  dResult = (2 * x * x) - (5 * x) + 3;

  return (dResult);
}

// ----------------------------------------------------------------------------

#ifndef AD

// This function is used to test stand-alone black box definitions so we
// don't want it to be included in any AD processing.
double ArrayTest::polyC(double x)
{
  double dResult;

  dResult = (2 * x * x) - (5 * x) + 3;

  return (dResult);
}

#endif

// ----------------------------------------------------------------------------

int ArrayTest::t_one_if(bool bTrue)
{
  int nIndex;

  if (bTrue)
  {
    nIndex = 1;
  }
  else
  {
    nIndex = 0;
  }

  return nIndex;
}

// ----------------------------------------------------------------------------

double ArrayTest::ifTest(double x)
{
  double dValue;

  dValue = polyB(x);

  if (dValue > 0.0)
  {
    dValue *= 2.0;
  }

  if (true)
  {
    if (dValue > 1.0)
    {
      dValue *= 1.5;
    }
  }

  return (dValue);
}

// ----------------------------------------------------------------------------

ArrayTest::ArrayTest(
#include "include/AT_constructor_args.hpp"
)
 : AdtArrays()
{
  #include "include/AT_constructor_locals.hpp"
  #include "include/AT_constructor_scalars_phase_1.hpp"
  #include "include/AT_constructor_arrays_phase_1.hpp"
  #include "include/AT_constructor_scalars_phase_2.hpp"
  #include "include/AT_constructor_arrays_phase_2.hpp"
  #include "include/AT_array_plans_init.hpp"

  nbdirsmax = 10;
}

// ----------------------------------------------------------------------------

double ArrayTest::sumA1_D()
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  for (cn = 1 ; cn <= ix ; cn++)
  {
    dSum += A1_D[cn];
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::sum(const ARRAY_1D X/*1:ix*/)
{
  double dSum;

  dSum = global_sum(X, 1, ix) + X[male] + X[female];

  return dSum;
}

// ----------------------------------------------------------------------------

// Note that putting AD NOCHECKPOINT outside of a function appears to be a
// bad thing to do from a Tapenade perspective and results in no differential
// being created. I don't know if this makes any sense and whether the behaviour
// is errant but Tapenade does not throw any warnings about it. As it breaks
// my test harness I've put "bad" in front of the pragma to ensure it isn't
// used as it will break the test harness.
// $bad AD NOCHECKPOINT
double ArrayTest::polySumA(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  // $AD NOCHECKPOINT
  for (cn = 1 ; cn <= ix ; cn++)
  {
    dSum += polyA(X[cn]);
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::polySumB(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  for (cn = 1 ; cn <= ix ; cn++)
  {
    dSum += polyB(X[cn]);
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::polySumC(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  for (cn = 1 ; cn <= ix ; cn++)
  {
    dSum += polyC(X[cn]);
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::polySum3D(const ARRAY_1D X/*1:1+ix*/)
{
  int     cx;
  int     cy;
  double  dSum;

  dSum = 0.0;

  for (cx = 1 ; cx <= 1 + ix ; cx++)
  {
    for (cy = -1 ; cy <= iy ; cy++)
    {
      dSum += polyC(X[cx] * A3_DD[cx][cy][A1_I[cx]]);
    }
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::boundsCheckTest(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;
  double  dR;

  dSum = 0.0;
  dR   = 0.9;

  // Make indexing step over the line on purpose. Bounds error!
  for (cn = 1 ; cn <= ix + 5 ; cn++)
  {
    dSum += pow(dR, dSum * pow(dR, X[cn]));
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

double ArrayTest::test_one_if(double v)
{
  double dResult;

  dResult = pow((t_one_if(v > 0.0) - t_one_if(v > 30.0)) * v, 5);

  return (dResult);
}

// ----------------------------------------------------------------------------

double ArrayTest::test_one_if_internal(double v)
{
  double dResult;

  dResult = pow((one_if(v > 0.0) - one_if(v > 30.0)) * v, 5);

  return (dResult);
}

// ----------------------------------------------------------------------------

bool ArrayTest::isNegative(double dValue)
{
  bool bResult;

  bResult = (dValue < 0);

  return (bResult);
}

// ----------------------------------------------------------------------------

longbool ArrayTest::isPositive(double dValue)
{
  longbool bResult;

  if (dValue >= 0)
  {
    bResult = 1;
  }
  else
  {
    bResult = 0;
  }

  return (bResult);
}

// ----------------------------------------------------------------------------

void ArrayTest::trigA(double& rOut, const ARRAY_1D x/* 1:ix */, const ARRAY_1D y/* 1:ix */)
{
  int cn;

  rOut = 0.0;

  for (cn = 1 ; cn <= ix ; cn++)
  {
    rOut = rOut + cos(cn * x[cn]) + sin(cn * y[cn]);
  }
}

// ----------------------------------------------------------------------------

double ArrayTest::trigB(const ARRAY_1D x/* 1:ix */, const ARRAY_1D y/* 1:ix */)
{
  int     cn;
  double  rOut;

  rOut = 0.0;

  for (cn = 1 ; cn <= ix ; cn++)
  {
    rOut = rOut + cos(cn * x[cn]) + sin(cn * y[cn]);
  }

  return (rOut);
}

