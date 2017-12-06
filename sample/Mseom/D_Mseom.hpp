//  ----------------------------------------------------------------------------
//  ADT generated header defining class D_OperatingModelBase
//  ----------------------------------------------------------------------------


#ifndef __D_OperatingModelBase_HPP
#define __D_OperatingModelBase_HPP


#include "Mseom.hpp"


class D_OperatingModelBase  : public OperatingModelBase
{
protected: 
  
  ARRAY_2D fmd1_par/* nfleets,nsim */;
  ARRAY_2D movnd1_par/* nareas,nsim */;
  ARRAY_4D eforyeard1_par/* nfleets,nareas,nsubyears,nsim */;
  ARRAY_2D fmb2_par/* nfleets,nsim */;
  ARRAY_2D movnb2_par/* nareas,nsim */;
  ARRAY_4D eforyearb2_par/* nfleets,nareas,nsubyears,nsim */;
  ARRAY_1I i4stack_1_2/* dim_stack */;
  int i4stack_1_2i;
  ARRAY_1D r4stack_1_2/* dim_stack */;
  int r4stack_1_2i;
  ARRAY_1I i4stack_2_2/* dim_stack */;
  int i4stack_2_2i;
  ARRAY_1I i4stack_3_2/* dim_stack */;
  int i4stack_3_2i;
  ARRAY_1D r4stack_3_2/* dim_stack */;
  int r4stack_3_2i;
  ARRAY_1I bstack_3_2/* dim_stack */;
  int bstack_3_2i;
public: 
  
  #include "OmB_decl_lib_interface_methods.hpp"
  D_OperatingModelBase(int arg_nsim, int arg_npop, int arg_nages, int arg_nsubyears, int arg_nareas, int arg_nfleets, const ARRAY_1I arg_Recsubyr);
  D_OperatingModelBase(const D_OperatingModelBase& rCopy);
  virtual ~D_OperatingModelBase();
  //   Differentiation of operatingmodelbase__msyrefs_objective in forward (tangent) mode:
  //    variations   of useful results: operatingmodelbase__msyrefs_objective
  //    with respect to varying inputs: par
  //    RW status of diff variables: movn:(loc) fm:(loc) eforyear:(loc)
  //                 nbefore:(loc) n:(loc) operatingmodelbase__msyrefs_objective:out
  //                 par:in c:(loc)
  double MSYREFS_OBJECTIVE_DPAR(double par, double pard1_par, int nReport, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int ntargets, const ARRAY_1I targpop/* ntargets */, int run_years, int sim_idx, double& MSYrefs_objective);
  //   Differentiation of operatingmodelbase__popdyn_msy_par in forward (tangent) mode:
  //    variations   of useful results: c
  //    with respect to varying inputs: par
  void POPDYN_MSY_PAR_DPAR(double par, double pard1_par, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int run_years, int sim_idx);
  //   Differentiation of operatingmodelbase__popdyn_next_year in forward (tangent) mode:
  //    variations   of useful results: nbefore n
  //    with respect to varying inputs: nbefore n
  void POPDYN_NEXT_YEAR_DPAR(ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, int sim_idx);
  //   Differentiation of operatingmodelbase__popdyn_year in forward (tangent) mode:
  //    variations   of useful results: movn fm nbefore n c
  //    with respect to varying inputs: movn fm nbefore n eannual c
  void POPDYN_YEAR_DPAR(const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_4D Eannual/* nfleets,nareas,nsubyears,nsim */, const ARRAY_4D eannuald1_par/* nfleets,nareas,nsubyears,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx);
  //   Differentiation of operatingmodelbase__popdyn_projection_objective in reverse (adjoint) mode:
  //    gradient     of useful results: operatingmodelbase__popdyn_projection_objective
  //    with respect to varying inputs: par
  //    RW status of diff variables: movn:(loc) fm:(loc) eforyear:(loc)
  //                 nbefore:(loc) n:(loc) operatingmodelbase__popdyn_projection_objective:in-killed
  //                 par:out c:(loc)
  void POPDYN_PROJECTION_OBJECTIVE_BPAR(const ARRAY_1D par/* 0:npar - 1 */, ARRAY_1D parb2_par/* 0:npar - 1 */, int npar, int nfixed, const ARRAY_1D TAC/* 0:npar - 1 */, const ARRAY_1D TAE/* 0:nfixed - 1 */, const ARRAY_1I FbyPar/* 0:npar - 1 */, const ARRAY_1I FbyFixed/* 0:nfixed - 1 */, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D Wt_age_mid/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int sim_idx, double& popdyn_projection_objectiveb2_par);
  //   Differentiation of operatingmodelbase__popdyn_projection_par in reverse (adjoint) mode:
  //    gradient     of useful results: c
  //    with respect to varying inputs: par
  void POPDYN_PROJECTION_PAR_BPAR(const ARRAY_1D par/* 0:npar - 1 */, ARRAY_1D parb2_par/* 0:npar - 1 */, int npar, int nfixed, const ARRAY_1D TAE/* 0:nfixed - 1 */, const ARRAY_1I FbyPar/* 0:npar - 1 */, const ARRAY_1I FbyFixed/* 0:nfixed - 1 */, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx);
  //   Differentiation of operatingmodelbase__popdyn_year in reverse (adjoint) mode:
  //    gradient     of useful results: c
  //    with respect to varying inputs: eannual
  void POPDYN_YEAR_BPAR(const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_4D Eannual/* nfleets,nareas,nsubyears,nsim */, ARRAY_4D eannualb2_par/* nfleets,nareas,nsubyears,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx);
  
};

#include "OmB_decl_lib_interface_globals.hpp"
#include "OmB_decl_lib_interface_constructor.hpp"


#endif //__D_OperatingModelBase_HPP

