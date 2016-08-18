//  ----------------------------------------------------------------------------
//  ADT generated file implementing class D_MinRosenbrock
//  ----------------------------------------------------------------------------

#include "Rosenbrock.hpp"




#include "d_Rosenbrock.hpp"



// ----------------------------------------------------------------------------

D_MinRosenbrock::D_MinRosenbrock(int arg_N)
 : MinRosenbrock(arg_N)
{
  createStack(i4stack_1_1);
  i4stack_1_1i = 0;
  createStack(r8stack_1_1);
  r8stack_1_1i = 0;
  createStack(r8stack_1_1d2_x);
}
;

// ----------------------------------------------------------------------------

D_MinRosenbrock::D_MinRosenbrock(const D_MinRosenbrock& rCopy)
 : MinRosenbrock(rCopy)
{
  createStack(i4stack_1_1);
  i4stack_1_1i = 0;
  createStack(r8stack_1_1);
  r8stack_1_1i = 0;
  createStack(r8stack_1_1d2_x);
}
;

// ----------------------------------------------------------------------------

D_MinRosenbrock::~D_MinRosenbrock()
{
  destroy(i4stack_1_1);
  destroy(r8stack_1_1);
  destroy(r8stack_1_1d2_x);
}

// ----------------------------------------------------------------------------

//   Differentiation of minrosenbrock__rosenbrock in reverse (adjoint) mode:
//    gradient     of useful results: minrosenbrock__rosenbrock
//    with respect to varying inputs: x
//    RW status of diff variables: x:out minrosenbrock__rosenbrock:in-killed
//  ----------------------------------------------------------------------------
void D_MinRosenbrock::ROSENBROCK_BX(const ARRAY_1D X/* N */, ARRAY_1D xb1_x/* N */, double& rosenbrockb1_x)
{
  int ad_count;
  int cn;
  double dsumb1_x;
  double f1;
  double f1b1_x;
  double f2;
  double f2b1_x;
  int i;
  int ix_0___;
  double p1;
  double p1b1_x;
  double p2;
  double p2b1_x;
  f1 = 0;
  f2 = 0;
  cn = 1;
  ad_count = 0;
  
  while ((cn <= N / 2))
  {
    p1 = X[2 * cn - 1];
    p2 = X[2 * cn];
    r8stack_1_1i = r8stack_1_1i + 1;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1))
    {
      growStack(r8stack_1_1,r8stack_1_1i);
    }
    
    r8stack_1_1[r8stack_1_1i] = f1;
    f1 = p1 * p1 - p2;
    r8stack_1_1i = r8stack_1_1i + 1;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1))
    {
      growStack(r8stack_1_1,r8stack_1_1i);
    }
    
    r8stack_1_1[r8stack_1_1i] = f2;
    f2 = p1 - 1.0;
    i4stack_1_1i = i4stack_1_1i + 1;
    
    if (i4stack_1_1i > stackSizeInt(i4stack_1_1))
    {
      growStack(i4stack_1_1,i4stack_1_1i);
    }
    
    i4stack_1_1[i4stack_1_1i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_1_1i = i4stack_1_1i + 1;
  
  if (i4stack_1_1i > stackSizeInt(i4stack_1_1))
  {
    growStack(i4stack_1_1,i4stack_1_1i);
  }
  
  i4stack_1_1[i4stack_1_1i] = ad_count;
  dsumb1_x = rosenbrockb1_x;
  
  for (ix_0___ = 1;ix_0___ <= N; ++ix_0___)
  {
    xb1_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_1_1[i4stack_1_1i];
  i4stack_1_1i = i4stack_1_1i - 1;
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_1_1[i4stack_1_1i];
    i4stack_1_1i = i4stack_1_1i - 1;
    f1b1_x = dsumb1_x;
    f2b1_x = dsumb1_x;
    p1 = X[2 * cn - 1];
    f2b1_x = 2 * f2 * f2b1_x;
    f2 = r8stack_1_1[r8stack_1_1i];
    r8stack_1_1i = r8stack_1_1i - 1;
    f1b1_x = 100 * 2 * f1 * f1b1_x;
    p1b1_x = 2 * p1 * f1b1_x + f2b1_x;
    f1 = r8stack_1_1[r8stack_1_1i];
    r8stack_1_1i = r8stack_1_1i - 1;
    p2b1_x = -f1b1_x;
    xb1_x[2 * cn] = xb1_x[2 * cn] + p2b1_x;
    xb1_x[2 * cn - 1] = xb1_x[2 * cn - 1] + p1b1_x;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of minrosenbrock__rosenbrock_bx in forward (tangent) mode:
//    variations   of useful results: xb1_x
//    with respect to varying inputs: x
//    RW status of diff variables: r8stack_1_1:(loc) x:in xb1_x:out
//   Differentiation of minrosenbrock__rosenbrock in reverse (adjoint) mode:
//    gradient     of useful results: minrosenbrock__rosenbrock
//    with respect to varying inputs: x
//    RW status of diff variables: x:out minrosenbrock__rosenbrock:in-killed
//  ----------------------------------------------------------------------------
void D_MinRosenbrock::ROSENBROCK_BX_DX(const ARRAY_1D X/* N */, const ARRAY_1D xd2_x/* N */, ARRAY_1D xb1_x/* N */, ARRAY_1D xb1_xd2_x/* N */, double& rosenbrockb1_x)
{
  int ad_count;
  int cn;
  double dsumb1_x;
  double f1;
  double f1b1_x;
  double f1b1_xd2_x;
  double f1d2_x;
  double f2;
  double f2b1_x;
  double f2b1_xd2_x;
  double f2d2_x;
  int i;
  int ix_0___;
  double p1;
  double p1b1_x;
  double p1b1_xd2_x;
  double p1d2_x;
  double p2;
  double p2b1_x;
  double p2b1_xd2_x;
  double p2d2_x;
  f1 = 0;
  f2 = 0;
  cn = 1;
  ad_count = 0;
  
  for (ix_0___ = 1;ix_0___ <= stackSizeInt(r8stack_1_1d2_x); ++ix_0___)
  {
    r8stack_1_1d2_x[ix_0___] = 0.0;
  }
  
  f1d2_x = 0.0;
  f2d2_x = 0.0;
  
  while ((cn <= N / 2))
  {
    p1d2_x = xd2_x[2 * cn - 1];
    p1 = X[2 * cn - 1];
    p2d2_x = xd2_x[2 * cn];
    p2 = X[2 * cn];
    r8stack_1_1i = r8stack_1_1i + 1;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1d2_x))
    {
      growStack(r8stack_1_1d2_x,r8stack_1_1i);
    }
    
    r8stack_1_1d2_x[r8stack_1_1i] = f1d2_x;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1))
    {
      growStack(r8stack_1_1,r8stack_1_1i);
    }
    
    r8stack_1_1[r8stack_1_1i] = f1;
    f1d2_x = p1d2_x * p1 + p1 * p1d2_x - p2d2_x;
    f1 = p1 * p1 - p2;
    r8stack_1_1i = r8stack_1_1i + 1;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1d2_x))
    {
      growStack(r8stack_1_1d2_x,r8stack_1_1i);
    }
    
    r8stack_1_1d2_x[r8stack_1_1i] = f2d2_x;
    
    if (r8stack_1_1i > stackSizeInt(r8stack_1_1))
    {
      growStack(r8stack_1_1,r8stack_1_1i);
    }
    
    r8stack_1_1[r8stack_1_1i] = f2;
    f2d2_x = p1d2_x;
    f2 = p1 - 1.0;
    i4stack_1_1i = i4stack_1_1i + 1;
    
    if (i4stack_1_1i > stackSizeInt(i4stack_1_1))
    {
      growStack(i4stack_1_1,i4stack_1_1i);
    }
    
    i4stack_1_1[i4stack_1_1i] = cn;
    cn = cn + 1;
    ad_count = ad_count + 1;
  }
  
  i4stack_1_1i = i4stack_1_1i + 1;
  
  if (i4stack_1_1i > stackSizeInt(i4stack_1_1))
  {
    growStack(i4stack_1_1,i4stack_1_1i);
  }
  
  i4stack_1_1[i4stack_1_1i] = ad_count;
  dsumb1_x = rosenbrockb1_x;
  
  for (ix_0___ = 1;ix_0___ <= N; ++ix_0___)
  {
    xb1_x[ix_0___] = 0.0;
  }
  
  ad_count = i4stack_1_1[i4stack_1_1i];
  i4stack_1_1i = i4stack_1_1i - 1;
  
  for (ix_0___ = 1;ix_0___ <= N; ++ix_0___)
  {
    xb1_xd2_x[ix_0___] = 0.0;
  }
  
  for (i = 1;i <= ad_count; ++i)
  {
    cn = i4stack_1_1[i4stack_1_1i];
    i4stack_1_1i = i4stack_1_1i - 1;
    f1b1_x = dsumb1_x;
    f2b1_x = dsumb1_x;
    p1d2_x = xd2_x[2 * cn - 1];
    p1 = X[2 * cn - 1];
    f2b1_xd2_x = 2 * f2b1_x * f2d2_x;
    f2b1_x = 2 * f2 * f2b1_x;
    f2d2_x = r8stack_1_1d2_x[r8stack_1_1i];
    f2 = r8stack_1_1[r8stack_1_1i];
    r8stack_1_1i = r8stack_1_1i - 1;
    f1b1_xd2_x = 100 * 2 * f1b1_x * f1d2_x;
    f1b1_x = 100 * 2 * f1 * f1b1_x;
    p1b1_xd2_x = 2 * (p1d2_x * f1b1_x) + 2 * (p1 * f1b1_xd2_x) + f2b1_xd2_x;
    p1b1_x = 2 * p1 * f1b1_x + f2b1_x;
    f1d2_x = r8stack_1_1d2_x[r8stack_1_1i];
    f1 = r8stack_1_1[r8stack_1_1i];
    r8stack_1_1i = r8stack_1_1i - 1;
    p2b1_xd2_x = -f1b1_xd2_x;
    p2b1_x = -f1b1_x;
    xb1_xd2_x[2 * cn] = xb1_xd2_x[2 * cn] + p2b1_xd2_x;
    xb1_x[2 * cn] = xb1_x[2 * cn] + p2b1_x;
    xb1_xd2_x[2 * cn - 1] = xb1_xd2_x[2 * cn - 1] + p1b1_xd2_x;
    xb1_x[2 * cn - 1] = xb1_x[2 * cn - 1] + p1b1_x;
  }
}

#include "Rb_impl_lib_interface_methods.hpp"
#include "Rb_impl_lib_interface_globals.hpp"
#include "Rb_impl_lib_interface_constructor.hpp"


