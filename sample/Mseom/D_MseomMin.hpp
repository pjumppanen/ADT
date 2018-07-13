//  ----------------------------------------------------------------------------
//  ADT generated header defining class D_OperatingModelMin
//  ----------------------------------------------------------------------------


#ifndef __D_OperatingModelMin_HPP
#define __D_OperatingModelMin_HPP


#include "MseomMin.hpp"


class D_OperatingModelMin  : public OperatingModelMin
{
public: 
  
  #include "Om_decl_lib_interface_methods.hpp"
  D_OperatingModelMin(int arg_nsim, int arg_npop, int arg_nages, int arg_nsubyears, int arg_nareas, int arg_nfleets, const ARRAY_1I arg_Recsubyr);
  D_OperatingModelMin(const D_OperatingModelMin& rCopy);
  virtual ~D_OperatingModelMin();
  
};


#include "Om_decl_lib_interface_globals.hpp"
#include "Om_decl_lib_interface_constructor.hpp"


#endif //__D_OperatingModelMin_HPP

