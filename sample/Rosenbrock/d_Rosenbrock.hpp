//  ----------------------------------------------------------------------------
//  ADT generated header defining class D_MinRosenbrock
//  ----------------------------------------------------------------------------


#ifndef __D_MinRosenbrock_HPP
#define __D_MinRosenbrock_HPP


#include "Rosenbrock.hpp"


class D_MinRosenbrock  : public MinRosenbrock
{
protected: 
  
  ARRAY_1I i4stack_1_1/* dim_stack */;
  int i4stack_1_1i;
  ARRAY_1D r8stack_1_1/* dim_stack */;
  int r8stack_1_1i;
  ARRAY_1D r8stack_1_1d2_x/* dim_stack */;
public: 
  
  #include "Rb_decl_lib_interface_methods.hpp"
  D_MinRosenbrock(int arg_N);
  D_MinRosenbrock(const D_MinRosenbrock& rCopy);
  virtual ~D_MinRosenbrock();
  //   Differentiation of minrosenbrock__rosenbrock in reverse (adjoint) mode:
  //    gradient     of useful results: minrosenbrock__rosenbrock
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out minrosenbrock__rosenbrock:in-killed
  //  ----------------------------------------------------------------------------
  void ROSENBROCK_BX(const ARRAY_1D X/* N */, ARRAY_1D xb1_x/* N */, double& rosenbrockb1_x);
  //   Differentiation of minrosenbrock__rosenbrock_bx in forward (tangent) mode:
  //    variations   of useful results: xb1_x
  //    with respect to varying inputs: x
  //    RW status of diff variables: r8stack_1_1:(loc) x:in xb1_x:out
  //   Differentiation of minrosenbrock__rosenbrock in reverse (adjoint) mode:
  //    gradient     of useful results: minrosenbrock__rosenbrock
  //    with respect to varying inputs: x
  //    RW status of diff variables: x:out minrosenbrock__rosenbrock:in-killed
  //  ----------------------------------------------------------------------------
  void ROSENBROCK_BX_DX(const ARRAY_1D X/* N */, const ARRAY_1D xd2_x/* N */, ARRAY_1D xb1_x/* N */, ARRAY_1D xb1_xd2_x/* N */, double& rosenbrockb1_x);
  
};

#include "Rb_decl_lib_interface_globals.hpp"
#include "Rb_decl_lib_interface_constructor.hpp"


#endif //__D_MinRosenbrock_HPP

