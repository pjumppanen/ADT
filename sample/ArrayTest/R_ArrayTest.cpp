//  ----------------------------------------------------------------------------
//  ADT generated file implementing class R_ArrayTest
//  ----------------------------------------------------------------------------

#include "ArrayTest.hpp"




#include "R_ArrayTest.hpp"



// ----------------------------------------------------------------------------

R_ArrayTest::R_ArrayTest(int arg_ix, int arg_iy, const ARRAY_1I arg_A1_I, const ARRAY_1D arg_A1_D, const ARRAY_1I arg_A2_IA, const ARRAY_1I arg_A2_IB)
 : ArrayTest(arg_ix,arg_iy,arg_A1_I,arg_A1_D,arg_A2_IA,arg_A2_IB)
{
  createStack(i4stack_2_1);
  i4stack_2_1i = 0;
  createStack(i4stack_1_2);
  i4stack_1_2i = 0;
  createStack(i4stack_1_3);
  i4stack_1_3i = 0;
  createStack(i4stack_1_4);
  i4stack_1_4i = 0;
  createStack(bstack_1_5);
  bstack_1_5i = 0;
}
;

// ----------------------------------------------------------------------------

R_ArrayTest::R_ArrayTest(const R_ArrayTest& rCopy)
 : ArrayTest(rCopy)
{
  createStack(i4stack_2_1);
  i4stack_2_1i = 0;
  createStack(i4stack_1_2);
  i4stack_1_2i = 0;
  createStack(i4stack_1_3);
  i4stack_1_3i = 0;
  createStack(i4stack_1_4);
  i4stack_1_4i = 0;
  createStack(bstack_1_5);
  bstack_1_5i = 0;
}
;

// ----------------------------------------------------------------------------

R_ArrayTest::~R_ArrayTest()
{
  destroy(i4stack_2_1);
  destroy(i4stack_1_2);
  destroy(i4stack_1_3);
  destroy(i4stack_1_4);
  destroy(bstack_1_5);
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__sum in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__sum
//    with respect to varying inputs: x
//    RW status of diff variables: x:out arraytest__sum:in-killed
void R_ArrayTest::SUM_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb1_x/* ix */, double& sumb1_x)
{
  double dsumb1_x;
  dsumb1_x = sumb1_x;
  GLOBAL_SUM_BX(X,xb1_x,1,ix,dsumb1_x);
}

// ----------------------------------------------------------------------------

//   Differentiation of global_sum in reverse (adjoint) mode:
//    gradient     of useful results: global_sum
//    with respect to varying inputs: x
void R_ArrayTest::GLOBAL_SUM_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb1_x/* ix */, int nBase, int nCount, double& global_sumb1_x)
{
  int ad_count;
  int cn;
  double dsumb1_x;
  int i;
  int ix_0___;
  cn = nBase;
  ad_count = 0;
  
  while ((cn < nBase + nCount))
  {
    i4stack_2_1i = i4stack_2_1i + 1;
    
    if (i4stack_2_1i > stackSizeInt(i4stack_2_1))
    {
      growStack(i4stack_2_1,i4stack_2_1i);
    }
    
    i4stack_2_1[i4stack_2_1i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_2_1i = i4stack_2_1i + 1;
  
  if (i4stack_2_1i > stackSizeInt(i4stack_2_1))
  {
    growStack(i4stack_2_1,i4stack_2_1i);
  }
  
  i4stack_2_1[i4stack_2_1i] = ad_count;
  dsumb1_x = global_sumb1_x;
  
  for (ix_0___ = 1;ix_0___ <= ix; ++ix_0___)
  {
    xb1_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_2_1[i4stack_2_1i];
  i4stack_2_1i = i4stack_2_1i - 1;
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_2_1[i4stack_2_1i];
    i4stack_2_1i = i4stack_2_1i - 1;
    xb1_x[cn] = xb1_x[cn] + dsumb1_x;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__polysuma in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__polysuma
//    with respect to varying inputs: x
//    RW status of diff variables: x:out arraytest__polysuma:in-killed
void R_ArrayTest::POLYSUMA_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb2_x/* ix */, double& polysumab2_x)
{
  int ad_count;
  int cn;
  double dsumb2_x;
  int i;
  int ix_0___;
  double result1b2_x;
  cn = 1;
  ad_count = 0;
  
  while ((cn <= ix))
  {
    i4stack_1_2i = i4stack_1_2i + 1;
    
    if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
    {
      growStack(i4stack_1_2,i4stack_1_2i);
    }
    
    i4stack_1_2[i4stack_1_2i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_1_2i = i4stack_1_2i + 1;
  
  if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
  {
    growStack(i4stack_1_2,i4stack_1_2i);
  }
  
  i4stack_1_2[i4stack_1_2i] = ad_count;
  dsumb2_x = polysumab2_x;
  
  for (ix_0___ = 1;ix_0___ <= ix; ++ix_0___)
  {
    xb2_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_1_2[i4stack_1_2i];
  i4stack_1_2i = i4stack_1_2i - 1;
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_1_2[i4stack_1_2i];
    i4stack_1_2i = i4stack_1_2i - 1;
    result1b2_x = dsumb2_x;
    xb2_x[cn] = xb2_x[cn] + (4 * X[cn] - 5) * result1b2_x;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__polysumb in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__polysumb
//    with respect to varying inputs: x
//    RW status of diff variables: x:out arraytest__polysumb:in-killed
void R_ArrayTest::POLYSUMB_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb3_x/* ix */, double& polysumbb3_x)
{
  int ad_count;
  int cn;
  double dsumb3_x;
  int i;
  int ix_0___;
  double result1b3_x;
  cn = 1;
  ad_count = 0;
  
  while ((cn <= ix))
  {
    i4stack_1_3i = i4stack_1_3i + 1;
    
    if (i4stack_1_3i > stackSizeInt(i4stack_1_3))
    {
      growStack(i4stack_1_3,i4stack_1_3i);
    }
    
    i4stack_1_3[i4stack_1_3i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_1_3i = i4stack_1_3i + 1;
  
  if (i4stack_1_3i > stackSizeInt(i4stack_1_3))
  {
    growStack(i4stack_1_3,i4stack_1_3i);
  }
  
  i4stack_1_3[i4stack_1_3i] = ad_count;
  dsumb3_x = polysumbb3_x;
  
  for (ix_0___ = 1;ix_0___ <= ix; ++ix_0___)
  {
    xb3_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_1_3[i4stack_1_3i];
  i4stack_1_3i = i4stack_1_3i - 1;
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_1_3[i4stack_1_3i];
    i4stack_1_3i = i4stack_1_3i - 1;
    result1b3_x = dsumb3_x;
    POLYB_BX(X[cn],xb3_x[cn],result1b3_x);
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__polyb in reverse (adjoint) mode:
//    gradient     of useful results: x arraytest__polyb
//    with respect to varying inputs: x
void R_ArrayTest::POLYB_BX(double X, double& xb3_x, double& polybb3_x)
{
  double dresultb3_x;
  dresultb3_x = polybb3_x;
  xb3_x = xb3_x + (pow(2,2) * X - 5) * dresultb3_x;
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__polysumc in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__polysumc
//    with respect to varying inputs: x
//    RW status of diff variables: x:out arraytest__polysumc:in-killed
void R_ArrayTest::POLYSUMC_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb4_x/* ix */, double& polysumcb4_x)
{
  int ad_count;
  int cn;
  double dsumb4_x;
  int i;
  int ix_0___;
  double result1b4_x;
  cn = 1;
  ad_count = 0;
  
  while ((cn <= ix))
  {
    i4stack_1_4i = i4stack_1_4i + 1;
    
    if (i4stack_1_4i > stackSizeInt(i4stack_1_4))
    {
      growStack(i4stack_1_4,i4stack_1_4i);
    }
    
    i4stack_1_4[i4stack_1_4i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_1_4i = i4stack_1_4i + 1;
  
  if (i4stack_1_4i > stackSizeInt(i4stack_1_4))
  {
    growStack(i4stack_1_4,i4stack_1_4i);
  }
  
  i4stack_1_4[i4stack_1_4i] = ad_count;
  dsumb4_x = polysumcb4_x;
  
  for (ix_0___ = 1;ix_0___ <= ix; ++ix_0___)
  {
    xb4_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_1_4[i4stack_1_4i];
  i4stack_1_4i = i4stack_1_4i - 1;
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_1_4[i4stack_1_4i];
    i4stack_1_4i = i4stack_1_4i - 1;
    result1b4_x = dsumb4_x;
    xb4_x[cn] = xb4_x[cn] + (4 * X[cn] - 5) * result1b4_x;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__iftest in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__iftest
//    with respect to varying inputs: x
//    RW status of diff variables: x:out arraytest__iftest:in-killed
//  ----------------------------------------------------------------------------
void R_ArrayTest::IFTEST_BX(double X, double& xb5_x, double& iftestb5_x)
{
  int branch;
  double dValue;
  double dvalueb5_x;
  branch = 0;
  dValue = polyB(X);
  
  if ((dValue > 0.0))
  {
    dValue = dValue * 2.0;
    bstack_1_5i = bstack_1_5i + 1;
    
    if (bstack_1_5i > stackSizeInt(bstack_1_5))
    {
      growStack(bstack_1_5,bstack_1_5i);
    }
    
    bstack_1_5[bstack_1_5i] = 0;
  }
  else
  {
    bstack_1_5i = bstack_1_5i + 1;
    
    if (bstack_1_5i > stackSizeInt(bstack_1_5))
    {
      growStack(bstack_1_5,bstack_1_5i);
    }
    
    bstack_1_5[bstack_1_5i] = 1;
  }
  
  if (true)
  {
    if ((dValue > 1.0))
    {
      bstack_1_5i = bstack_1_5i + 1;
      
      if (bstack_1_5i > stackSizeInt(bstack_1_5))
      {
        growStack(bstack_1_5,bstack_1_5i);
      }
      
      bstack_1_5[bstack_1_5i] = 0;
    }
    else
    {
      bstack_1_5i = bstack_1_5i + 1;
      
      if (bstack_1_5i > stackSizeInt(bstack_1_5))
      {
        growStack(bstack_1_5,bstack_1_5i);
      }
      
      bstack_1_5[bstack_1_5i] = 1;
    }
  }
  else
  {
    bstack_1_5i = bstack_1_5i + 1;
    
    if (bstack_1_5i > stackSizeInt(bstack_1_5))
    {
      growStack(bstack_1_5,bstack_1_5i);
    }
    
    bstack_1_5[bstack_1_5i] = 2;
  }
  
  dvalueb5_x = iftestb5_x;
  branch = bstack_1_5[bstack_1_5i];
  bstack_1_5i = bstack_1_5i - 1;
  
  if ((branch == 0))
  {
    dvalueb5_x = 1.5 * dvalueb5_x;
  }
  
  branch = bstack_1_5[bstack_1_5i];
  bstack_1_5i = bstack_1_5i - 1;
  
  if ((branch == 0))
  {
    dvalueb5_x = 2.0 * dvalueb5_x;
  }
  
  POLYB_BX0(X,xb5_x,dvalueb5_x);
}

// ----------------------------------------------------------------------------

//   Differentiation of arraytest__polyb in reverse (adjoint) mode:
//    gradient     of useful results: arraytest__polyb
//    with respect to varying inputs: x
void R_ArrayTest::POLYB_BX0(double X, double& xb5_x, double& polybb5_x)
{
  double dresultb5_x;
  dresultb5_x = polybb5_x;
  xb5_x = (pow(2,2) * X - 5) * dresultb5_x;
}

#include "AT_impl_lib_interface_methods.hpp"
#include "AT_impl_lib_interface_globals.hpp"
#include "AT_impl_lib_interface_constructor.hpp"


