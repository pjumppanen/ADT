// ----------------------------------------------------------------------------
// Test code for ADT Arrays.
// ----------------------------------------------------------------------------

#ifndef __ARRAYTEST_HPP__
#define __ARRAYTEST_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"

// ----------------------------------------------------------------------------

// Test global constants
extern const int male;
extern const int female;
extern const int n_sex;

// ----------------------------------------------------------------------------

class ArrayTest : public AdtArrays
{
protected:
  /* AD_LIBNAME ArrayTest */
  /* AD_ALIAS AT=R_ArrayTest */
  /* AUTOINIT 1 */
  int       ix;
  int       iy;

  // Test 1D arrays
  ARRAY_1I  A1_I /*1:1+ix*/;
  ARRAY_1D  A1_D /*1:ix*/;
  ARRAY_2I  A2_IA /*1+ix,-1:iy*/;
  ARRAY_2I  A2_IB /*-1:iy,1+ix*/;
  ARRAY_2D  A2_DA /*1+ix,1:n_sex*/;

  // Test longbool arrays
  ARRAY_2LB A2_LB /*1+ix,-1:iy*/;

  // Test Raw array types
  ARRAY_2C  A2_C /*1+ix,-1:iy*/;
  ARRAY_2UC A2_UC /*1+ix,-1:iy*/;
  ARRAY_2B  A2_B /*1+ix,-1:iy*/;

  // Bool and longbool singulars
  bool      SingularBool;
  longbool  SingularLongbool;

  /* AUTODEC 2 */
  ARRAY_3D  A3_DA /*-1:iy,1+ix,A2_IA[<2>,<1>]+A2_IB[<1>,<2>]*/;
  ARRAY_3D  A3_DB /*-1:iy,1+ix,A2_IA[<-1>,<-2>]*/;
  ARRAY_3D  A3_DC /*-1:iy,1+ix,A1_I[<-1>]*/;
  ARRAY_3D  A3_DD /*1+ix,-1:iy,A1_I[<-2>]*/;

  /* AUTODEC NO_INTERFACE */
  ARRAY_1B  A1_B /*1:ix*/;
  ARRAY_1C  A1_C /*1:ix*/;
  ARRAY_1L  A1_L /*1:ix*/;
  ARRAY_1F  A1_F /*1:ix*/;
  ARRAY_1UC A1_UC/*1:ix*/;
  ARRAY_1UI A1_UI/*1:ix*/;
  ARRAY_1UL A1_UL/*1:ix*/;
  ARRAY_1US A1_US/*1:ix*/;

  // Check for null sized arrays
  ARRAY_1D  N1_D /*1:0*/;
  int       nbdirsmax;

#include "include/AT_array_plans.hpp"

protected:
  // D/D(x) (4 * x) - 5;
  double polyA(double x);
  double polyB(double x);

#ifndef AD
  // This function is used to test stand-alone black box definitions so we
  // don't want it to be included in any AD processing.
  double polyC(double x);
#endif

  int    t_one_if(bool bTrue);
  double ifTest(double x);

public:
  ArrayTest(
#include "include/AT_constructor_args.hpp"
  );

  // Function to test the interface generation on functions with no args
  double sumA1_D();

  double sum(const ARRAY_1D X/*1:ix*/);
  double polySumA(const ARRAY_1D X/*1:ix*/);
  double polySumB(const ARRAY_1D X/*1:ix*/);
  double polySumC(const ARRAY_1D X/*1:ix*/);
  double polySum3D(const ARRAY_1D X/*1:1+ix*/);
  virtual double boundsCheckTest(const ARRAY_1D X/*1:ix*/);
  double test_one_if(double v);
  double test_one_if_internal(double v);

  bool     isNegative(double dValue);
  longbool isPositive(double dValue);

  // Functions to test DIFF and GRAD wrappers
  void     trigA(double& rOut, const ARRAY_1D x/* 1:ix */, const ARRAY_1D y/* 1:ix */);
  double   trigB(const ARRAY_1D x/* 1:ix */, const ARRAY_1D y/* 1:ix */);
};


#endif  //__ARRAYTEST_HPP__
