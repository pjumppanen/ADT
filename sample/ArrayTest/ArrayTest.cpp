// ----------------------------------------------------------------------------
// Test code for ADT Arrays.
// ----------------------------------------------------------------------------


#include "ArrayTest.hpp"


// ----------------------------------------------------------------------------

double global_sum(const ARRAY_1D X/*1:ix*/, int nBase, int nCount)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  for (cn = nBase ; cn < nBase + nCount ; cn++)
  {
    dSum += X[cn];
  }

  return (dSum);
}

// ----------------------------------------------------------------------------

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
#include "AT_constructor_args.hpp"
)
 : AdtArrays()
{
  #include "AT_constructor_locals.hpp"
  #include "AT_constructor_scalars_phase_1.hpp"
  #include "AT_constructor_arrays_phase_1.hpp"
  #include "AT_constructor_scalars_phase_2.hpp"
  #include "AT_constructor_arrays_phase_2.hpp"
  #include "AT_array_plans_init.hpp"
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

double ArrayTest::polySumA(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

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

double ArrayTest::boundsCheckTest(const ARRAY_1D X/*1:ix*/)
{
  int     cn;
  double  dSum;

  dSum = 0.0;

  // Make indexing step over the line on purpose. Bounds error!
  for (cn = 1 ; cn <= ix + 5 ; cn++)
  {
    dSum += X[cn];
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
