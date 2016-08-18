//  ----------------------------------------------------------------------------
//  ADT generated header defining class R_ArrayTest
//  ----------------------------------------------------------------------------


#ifndef __R_ArrayTest_HPP
#define __R_ArrayTest_HPP


#include "ArrayTest.hpp"


class R_ArrayTest  : public ArrayTest
{
protected: 
  
  ARRAY_1I i4stack_2_1/* dim_stack */;
  int i4stack_2_1i;
  ARRAY_1I i4stack_1_2/* dim_stack */;
  int i4stack_1_2i;
  ARRAY_1I i4stack_1_3/* dim_stack */;
  int i4stack_1_3i;
  ARRAY_1I i4stack_1_4/* dim_stack */;
  int i4stack_1_4i;
  ARRAY_1I bstack_1_5/* dim_stack */;
  int bstack_1_5i;
public: 
  
  #include "AT_decl_lib_interface_methods.hpp"
  R_ArrayTest(int arg_ix, int arg_iy, const ARRAY_1I arg_A1_I, const ARRAY_1D arg_A1_D, const ARRAY_1I arg_A2_IA, const ARRAY_1I arg_A2_IB);
  R_ArrayTest(const R_ArrayTest& rCopy);
  virtual ~R_ArrayTest();
  //   Differentiation of arraytest__sum in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__sum
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out arraytest__sum:in-killed
  void SUM_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb1_x/* ix */, double& sumb1_x);
  //   Differentiation of global_sum in reverse (adjoint) mode:
  //    gradient     of useful results: global_sum
  //    with respect to varying inputs: x
  void GLOBAL_SUM_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb1_x/* ix */, int nBase, int nCount, double& global_sumb1_x);
  //   Differentiation of arraytest__polysuma in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__polysuma
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out arraytest__polysuma:in-killed
  void POLYSUMA_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb2_x/* ix */, double& polysumab2_x);
  //   Differentiation of arraytest__polysumb in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__polysumb
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out arraytest__polysumb:in-killed
  void POLYSUMB_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb3_x/* ix */, double& polysumbb3_x);
  //   Differentiation of arraytest__polyb in reverse (adjoint) mode:
  //    gradient     of useful results: x arraytest__polyb
  //    with respect to varying inputs: x
  void POLYB_BX(double X, double& xb3_x, double& polybb3_x);
  //   Differentiation of arraytest__polysumc in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__polysumc
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out arraytest__polysumc:in-killed
  void POLYSUMC_BX(const ARRAY_1D X/* ix */, ARRAY_1D xb4_x/* ix */, double& polysumcb4_x);
  //   Differentiation of arraytest__iftest in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__iftest
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out arraytest__iftest:in-killed
  //  ----------------------------------------------------------------------------
  void IFTEST_BX(double X, double& xb5_x, double& iftestb5_x);
  //   Differentiation of arraytest__polyb in reverse (adjoint) mode:
  //    gradient     of useful results: arraytest__polyb
  //    with respect to varying inputs: x
  void POLYB_BX0(double X, double& xb5_x, double& polybb5_x);
  
};

#include "AT_decl_lib_interface_globals.hpp"
#include "AT_decl_lib_interface_constructor.hpp"


#endif //__R_ArrayTest_HPP

