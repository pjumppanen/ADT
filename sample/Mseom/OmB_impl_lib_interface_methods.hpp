
SEXP D_OperatingModelBase::_get_aR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)aR, "aR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_aR(SEXP arg_aR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)aR, "aR", arg_aR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_aR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)aR, "aR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_aR(SEXP arg_aR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)aR, "aR", arg_aR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_B0(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)B0, "B0", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_B0(SEXP arg_B0, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)B0, "B0", arg_B0, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_B0(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)B0, "B0", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_B0(SEXP arg_B0, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)B0, "B0", arg_B0, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_bR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)bR, "bR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_bR(SEXP arg_bR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)bR, "bR", arg_bR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_bR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)bR, "bR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_bR(SEXP arg_bR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)bR, "bR", arg_bR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_EforYear(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)EforYear, "EforYear", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_EforYear(SEXP arg_EforYear, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)EforYear, "EforYear", arg_EforYear, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_EforYear(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)EforYear, "EforYear", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_EforYear(SEXP arg_EforYear, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)EforYear, "EforYear", arg_EforYear, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_eforyearb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)eforyearb2_par, "eforyearb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_eforyearb2_par(SEXP arg_eforyearb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)eforyearb2_par, "eforyearb2_par", arg_eforyearb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_eforyearb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)eforyearb2_par, "eforyearb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_eforyearb2_par(SEXP arg_eforyearb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)eforyearb2_par, "eforyearb2_par", arg_eforyearb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_eforyeard1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)eforyeard1_par, "eforyeard1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_eforyeard1_par(SEXP arg_eforyeard1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)eforyeard1_par, "eforyeard1_par", arg_eforyeard1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_eforyeard1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)eforyeard1_par, "eforyeard1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_eforyeard1_par(SEXP arg_eforyeard1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)eforyeard1_par, "eforyeard1_par", arg_eforyeard1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_FM(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)FM, "FM", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_FM(SEXP arg_FM, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)FM, "FM", arg_FM, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_FM(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)FM, "FM", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_FM(SEXP arg_FM, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)FM, "FM", arg_FM, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_fmb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)fmb2_par, "fmb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_fmb2_par(SEXP arg_fmb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)fmb2_par, "fmb2_par", arg_fmb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_fmb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)fmb2_par, "fmb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_fmb2_par(SEXP arg_fmb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)fmb2_par, "fmb2_par", arg_fmb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_fmd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)fmd1_par, "fmd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_fmd1_par(SEXP arg_fmd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)fmd1_par, "fmd1_par", arg_fmd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_fmd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)fmd1_par, "fmd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_fmd1_par(SEXP arg_fmd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)fmd1_par, "fmd1_par", arg_fmd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_internal_initialiseParameters(SEXP M, SEXP R0, SEXP mat, SEXP Idist, SEXP Wt_age, SEXP h, bool bTranslate)
{
  ARRAY_3D arg_M;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Wt_age;
  ARRAY_2D arg_h;
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  if (bTranslate)
  {
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
  }
  else
  {
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  initialiseParameters(arg_M, arg_R0, arg_mat, arg_Idist, arg_Wt_age, arg_h);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_initialiseParameters(SEXP M, SEXP R0, SEXP mat, SEXP Idist, SEXP Wt_age, SEXP h)
{
  return (R_internal_initialiseParameters(M, R0, mat, Idist, Wt_age, h, true));
}

SEXP D_OperatingModelBase::R_nt_initialiseParameters(SEXP M, SEXP R0, SEXP mat, SEXP Idist, SEXP Wt_age, SEXP h)
{
  return (R_internal_initialiseParameters(M, R0, mat, Idist, Wt_age, h, false));
}

SEXP D_OperatingModelBase::_get_MovN(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)MovN, "MovN", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_MovN(SEXP arg_MovN, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)MovN, "MovN", arg_MovN, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_MovN(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)MovN, "MovN", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_MovN(SEXP arg_MovN, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)MovN, "MovN", arg_MovN, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_movnb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)movnb2_par, "movnb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_movnb2_par(SEXP arg_movnb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)movnb2_par, "movnb2_par", arg_movnb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_movnb2_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)movnb2_par, "movnb2_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_movnb2_par(SEXP arg_movnb2_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)movnb2_par, "movnb2_par", arg_movnb2_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_movnd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)movnd1_par, "movnd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_movnd1_par(SEXP arg_movnd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)movnd1_par, "movnd1_par", arg_movnd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_movnd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)movnd1_par, "movnd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_movnd1_par(SEXP arg_movnd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)movnd1_par, "movnd1_par", arg_movnd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_MSY_Recdevs(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)MSY_Recdevs, "MSY_Recdevs", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_MSY_Recdevs(SEXP arg_MSY_Recdevs, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)MSY_Recdevs, "MSY_Recdevs", arg_MSY_Recdevs, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_MSY_Recdevs(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)MSY_Recdevs, "MSY_Recdevs", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_MSY_Recdevs(SEXP arg_MSY_Recdevs, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)MSY_Recdevs, "MSY_Recdevs", arg_MSY_Recdevs, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_MSY_RecSpatialDevs(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)MSY_RecSpatialDevs, "MSY_RecSpatialDevs", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_MSY_RecSpatialDevs(SEXP arg_MSY_RecSpatialDevs, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)MSY_RecSpatialDevs, "MSY_RecSpatialDevs", arg_MSY_RecSpatialDevs, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_MSY_RecSpatialDevs(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)MSY_RecSpatialDevs, "MSY_RecSpatialDevs", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_MSY_RecSpatialDevs(SEXP arg_MSY_RecSpatialDevs, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)MSY_RecSpatialDevs, "MSY_RecSpatialDevs", arg_MSY_RecSpatialDevs, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_internal_MSYrefs(SEXP par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP sim_idx, bool bTranslate)
{
  double arg_par;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_2D arg_SSBA;
  int arg_ntargets;
  ARRAY_1I arg_targpop;
  int arg_run_years;
  ARRAY_1D arg_MSY;
  ARRAY_1D arg_BMSY;
  ARRAY_1D arg_SSBMSY;
  ARRAY_1D arg_SSBMSY_B0;
  int arg_sim_idx;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("ntargets", "INTSXP", INTSXP, ntargets, __FILE__, __LINE__);
  
  R_CheckArgument("targpop", "INTSXP", INTSXP, targpop, __FILE__, __LINE__, 1, 1, INTEGER(ntargets)[0]);
  
  R_CheckArgument("run_years", "INTSXP", INTSXP, run_years, __FILE__, __LINE__);
  
  R_CheckArgument("MSY", "REALSXP", REALSXP, MSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("BMSY", "REALSXP", REALSXP, BMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY", "REALSXP", REALSXP, SSBMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY_B0", "REALSXP", REALSXP, SSBMSY_B0, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = REAL(par)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0]);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(targpop), (char*)arg_targpop);
    
    arg_run_years = INTEGER(run_years)[0];
    arg_MSY = 0;
    
    Plan_16.create(MemAllocator, arg_MSY);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(MSY), (char*)arg_MSY);
    
    arg_BMSY = 0;
    
    Plan_16.create(MemAllocator, arg_BMSY);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(BMSY), (char*)arg_BMSY);
    
    arg_SSBMSY = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBMSY), (char*)arg_SSBMSY);
    
    arg_SSBMSY_B0 = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY_B0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBMSY_B0), (char*)arg_SSBMSY_B0);
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  else
  {
    arg_par = REAL(par)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0], (void*)INTEGER(targpop));
    
    arg_run_years = INTEGER(run_years)[0];
    arg_MSY = 0;
    
    Plan_16.create(MemAllocator, arg_MSY, (void*)REAL(MSY));
    
    arg_BMSY = 0;
    
    Plan_16.create(MemAllocator, arg_BMSY, (void*)REAL(BMSY));
    
    arg_SSBMSY = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY, (void*)REAL(SSBMSY));
    
    arg_SSBMSY_B0 = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY_B0, (void*)REAL(SSBMSY_B0));
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  MSYrefs(arg_par, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_ntargets, arg_targpop, arg_run_years, arg_MSY, arg_BMSY, arg_SSBMSY, arg_SSBMSY_B0, arg_sim_idx);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_MSY, (char*)REAL(MSY));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_BMSY, (char*)REAL(BMSY));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBMSY, (char*)REAL(SSBMSY));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBMSY_B0, (char*)REAL(SSBMSY_B0));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  AdtArrayPlan::destroy(MemAllocator, arg_targpop);
  AdtArrayPlan::destroy(MemAllocator, arg_MSY);
  AdtArrayPlan::destroy(MemAllocator, arg_BMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY_B0);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_MSYrefs(SEXP par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP sim_idx)
{
  return (R_internal_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx, true));
}

SEXP D_OperatingModelBase::R_nt_MSYrefs(SEXP par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP sim_idx)
{
  return (R_internal_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx, false));
}

SEXP D_OperatingModelBase::R_internal_MSYrefs_objective(SEXP par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, bool bTranslate)
{
  double arg_par;
  int arg_nReport;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_2D arg_SSBA;
  int arg_ntargets;
  ARRAY_1I arg_targpop;
  int arg_run_years;
  int arg_sim_idx;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__);
  
  R_CheckArgument("nReport", "INTSXP", INTSXP, nReport, __FILE__, __LINE__);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("ntargets", "INTSXP", INTSXP, ntargets, __FILE__, __LINE__);
  
  R_CheckArgument("targpop", "INTSXP", INTSXP, targpop, __FILE__, __LINE__, 1, 1, INTEGER(ntargets)[0]);
  
  R_CheckArgument("run_years", "INTSXP", INTSXP, run_years, __FILE__, __LINE__);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = REAL(par)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0]);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(targpop), (char*)arg_targpop);
    
    arg_run_years = INTEGER(run_years)[0];
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  else
  {
    arg_par = REAL(par)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0], (void*)INTEGER(targpop));
    
    arg_run_years = INTEGER(run_years)[0];
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = MSYrefs_objective(arg_par, arg_nReport, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_ntargets, arg_targpop, arg_run_years, arg_sim_idx);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  AdtArrayPlan::destroy(MemAllocator, arg_targpop);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_MSYrefs_objective(SEXP par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx)
{
  return (R_internal_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx, true));
}

SEXP D_OperatingModelBase::R_nt_MSYrefs_objective(SEXP par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx)
{
  return (R_internal_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx, false));
}

SEXP D_OperatingModelBase::R_internal_MSYREFS_OBJECTIVE_DPAR(SEXP par, SEXP pard1_par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, SEXP MSYrefs_objective, bool bTranslate)
{
  double arg_par;
  double arg_pard1_par;
  int arg_nReport;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_nd1_par;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_nbefored1_par;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_6D arg_cd1_par;
  ARRAY_2D arg_SSBA;
  int arg_ntargets;
  ARRAY_1I arg_targpop;
  int arg_run_years;
  int arg_sim_idx;
  double arg_MSYrefs_objective;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__);
  
  R_CheckArgument("pard1_par", "REALSXP", REALSXP, pard1_par, __FILE__, __LINE__);
  
  R_CheckArgument("nReport", "INTSXP", INTSXP, nReport, __FILE__, __LINE__);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("nd1_par", "REALSXP", REALSXP, nd1_par, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("nbefored1_par", "REALSXP", REALSXP, nbefored1_par, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("cd1_par", "REALSXP", REALSXP, cd1_par, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("ntargets", "INTSXP", INTSXP, ntargets, __FILE__, __LINE__);
  
  R_CheckArgument("targpop", "INTSXP", INTSXP, targpop, __FILE__, __LINE__, 1, 1, INTEGER(ntargets)[0]);
  
  R_CheckArgument("run_years", "INTSXP", INTSXP, run_years, __FILE__, __LINE__);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  R_CheckArgument("MSYrefs_objective", "REALSXP", REALSXP, MSYrefs_objective, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = REAL(par)[0];
    arg_pard1_par = REAL(pard1_par)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_nd1_par = 0;
    
    Plan_13.create(MemAllocator, arg_nd1_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(nd1_par), (char*)arg_nd1_par);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_nbefored1_par = 0;
    
    Plan_13.create(MemAllocator, arg_nbefored1_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(nbefored1_par), (char*)arg_nbefored1_par);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_cd1_par = 0;
    
    Plan_15.create(MemAllocator, arg_cd1_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(cd1_par), (char*)arg_cd1_par);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0]);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(targpop), (char*)arg_targpop);
    
    arg_run_years = INTEGER(run_years)[0];
    arg_sim_idx = INTEGER(sim_idx)[0];
    arg_MSYrefs_objective = REAL(MSYrefs_objective)[0];
  }
  else
  {
    arg_par = REAL(par)[0];
    arg_pard1_par = REAL(pard1_par)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_nd1_par = 0;
    
    Plan_13.create(MemAllocator, arg_nd1_par, (void*)REAL(nd1_par));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_nbefored1_par = 0;
    
    Plan_13.create(MemAllocator, arg_nbefored1_par, (void*)REAL(nbefored1_par));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_cd1_par = 0;
    
    Plan_15.create(MemAllocator, arg_cd1_par, (void*)REAL(cd1_par));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_ntargets = INTEGER(ntargets)[0];
    arg_targpop = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_targpop, 1, INTEGER(ntargets)[0], (void*)INTEGER(targpop));
    
    arg_run_years = INTEGER(run_years)[0];
    arg_sim_idx = INTEGER(sim_idx)[0];
    arg_MSYrefs_objective = REAL(MSYrefs_objective)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = MSYREFS_OBJECTIVE_DPAR(arg_par, arg_pard1_par, arg_nReport, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_SRrel, arg_N, arg_nd1_par, arg_NBefore, arg_nbefored1_par, arg_SSN, arg_C, arg_cd1_par, arg_SSBA, arg_ntargets, arg_targpop, arg_run_years, arg_sim_idx, arg_MSYrefs_objective);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_nd1_par, (char*)REAL(nd1_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_nbefored1_par, (char*)REAL(nbefored1_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_cd1_par, (char*)REAL(cd1_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
    REAL(MSYrefs_objective)[0] = arg_MSYrefs_objective;
  }
  else
  {
    REAL(MSYrefs_objective)[0] = arg_MSYrefs_objective;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_nd1_par);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_nbefored1_par);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_cd1_par);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  AdtArrayPlan::destroy(MemAllocator, arg_targpop);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_MSYREFS_OBJECTIVE_DPAR(SEXP par, SEXP pard1_par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, SEXP MSYrefs_objective)
{
  return (R_internal_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective, true));
}

SEXP D_OperatingModelBase::R_nt_MSYREFS_OBJECTIVE_DPAR(SEXP par, SEXP pard1_par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, SEXP MSYrefs_objective)
{
  return (R_internal_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective, false));
}

SEXP D_OperatingModelBase::_get_nages() const
{
  return (R_Scalar(nages));
}

SEXP D_OperatingModelBase::_set_nages(SEXP arg_nages)
{
  R_CheckArgument("arg_nages", "INTSXP", INTSXP, arg_nages, __FILE__, __LINE__);
  
  nages = INTEGER(arg_nages)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::_get_nareas() const
{
  return (R_Scalar(nareas));
}

SEXP D_OperatingModelBase::_set_nareas(SEXP arg_nareas)
{
  R_CheckArgument("arg_nareas", "INTSXP", INTSXP, arg_nareas, __FILE__, __LINE__);
  
  nareas = INTEGER(arg_nareas)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::R_internal_nextYear(SEXP N, SEXP NBefore, bool bTranslate)
{
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  if (bTranslate)
  {
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
  }
  else
  {
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  nextYear(arg_N, arg_NBefore);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_nextYear(SEXP N, SEXP NBefore)
{
  return (R_internal_nextYear(N, NBefore, true));
}

SEXP D_OperatingModelBase::R_nt_nextYear(SEXP N, SEXP NBefore)
{
  return (R_internal_nextYear(N, NBefore, false));
}

SEXP D_OperatingModelBase::_get_nfleets() const
{
  return (R_Scalar(nfleets));
}

SEXP D_OperatingModelBase::_set_nfleets(SEXP arg_nfleets)
{
  R_CheckArgument("arg_nfleets", "INTSXP", INTSXP, arg_nfleets, __FILE__, __LINE__);
  
  nfleets = INTEGER(arg_nfleets)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::_get_npop() const
{
  return (R_Scalar(npop));
}

SEXP D_OperatingModelBase::_set_npop(SEXP arg_npop)
{
  R_CheckArgument("arg_npop", "INTSXP", INTSXP, arg_npop, __FILE__, __LINE__);
  
  npop = INTEGER(arg_npop)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::_get_nsim() const
{
  return (R_Scalar(nsim));
}

SEXP D_OperatingModelBase::_set_nsim(SEXP arg_nsim)
{
  R_CheckArgument("arg_nsim", "INTSXP", INTSXP, arg_nsim, __FILE__, __LINE__);
  
  nsim = INTEGER(arg_nsim)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::_get_nsubyears() const
{
  return (R_Scalar(nsubyears));
}

SEXP D_OperatingModelBase::_set_nsubyears(SEXP arg_nsubyears)
{
  R_CheckArgument("arg_nsubyears", "INTSXP", INTSXP, arg_nsubyears, __FILE__, __LINE__);
  
  nsubyears = INTEGER(arg_nsubyears)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::R_internal_popdyn_projection_objective(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx, bool bTranslate)
{
  ARRAY_1D arg_par;
  int arg_npar;
  int arg_nfixed;
  ARRAY_1D arg_TAC;
  ARRAY_1D arg_TAE;
  ARRAY_1I arg_FbyPar;
  ARRAY_1I arg_FbyFixed;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_Wt_age_mid;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_3D arg_Recdevs;
  ARRAY_3D arg_RecSpatialDevs;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_2D arg_SSBA;
  int arg_sim_idx;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("npar", "INTSXP", INTSXP, npar, __FILE__, __LINE__);
  
  R_CheckArgument("nfixed", "INTSXP", INTSXP, nfixed, __FILE__, __LINE__);
  
  R_CheckArgument("TAC", "REALSXP", REALSXP, TAC, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("TAE", "REALSXP", REALSXP, TAE, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("FbyPar", "INTSXP", INTSXP, FbyPar, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("FbyFixed", "INTSXP", INTSXP, FbyFixed, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age_mid", "REALSXP", REALSXP, Wt_age_mid, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdevs", "REALSXP", REALSXP, Recdevs, __FILE__, __LINE__, 3, 1, SpawnPerYr, 1, npop, 1, nsim);
  
  R_CheckArgument("RecSpatialDevs", "REALSXP", REALSXP, RecSpatialDevs, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(par), (char*)arg_par);
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAC), (char*)arg_TAC);
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAE), (char*)arg_TAE);
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyPar), (char*)arg_FbyPar);
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyFixed), (char*)arg_FbyFixed);
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_Wt_age_mid = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age_mid);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age_mid), (char*)arg_Wt_age_mid);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdevs), (char*)arg_Recdevs);
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(RecSpatialDevs), (char*)arg_RecSpatialDevs);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  else
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1, (void*)REAL(par));
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1, (void*)REAL(TAC));
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1, (void*)REAL(TAE));
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1, (void*)INTEGER(FbyPar));
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1, (void*)INTEGER(FbyFixed));
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_Wt_age_mid = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age_mid, (void*)REAL(Wt_age_mid));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs, (void*)REAL(Recdevs));
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs, (void*)REAL(RecSpatialDevs));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = popdyn_projection_objective(arg_par, arg_npar, arg_nfixed, arg_TAC, arg_TAE, arg_FbyPar, arg_FbyFixed, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_Wt_age_mid, arg_sel, arg_mov, arg_h, arg_Recdist, arg_Recdevs, arg_RecSpatialDevs, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_sim_idx);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_par);
  AdtArrayPlan::destroy(MemAllocator, arg_TAC);
  AdtArrayPlan::destroy(MemAllocator, arg_TAE);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyPar);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyFixed);
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age_mid);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdevs);
  AdtArrayPlan::destroy(MemAllocator, arg_RecSpatialDevs);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_popdyn_projection_objective(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  return (R_internal_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx, true));
}

SEXP D_OperatingModelBase::R_nt_popdyn_projection_objective(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  return (R_internal_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx, false));
}

SEXP D_OperatingModelBase::R_internal_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP sim_idx, SEXP popdyn_projection_objectiveb2_par, bool bTranslate)
{
  ARRAY_1D arg_par;
  ARRAY_1D arg_parb2_par;
  int arg_npar;
  int arg_nfixed;
  ARRAY_1D arg_TAC;
  ARRAY_1D arg_TAE;
  ARRAY_1I arg_FbyPar;
  ARRAY_1I arg_FbyFixed;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_Wt_age_mid;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_3D arg_Recdevs;
  ARRAY_3D arg_RecSpatialDevs;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_nb2_par;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_nbeforeb2_par;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_6D arg_cb2_par;
  ARRAY_2D arg_SSBA;
  int arg_sim_idx;
  double arg_popdyn_projection_objectiveb2_par;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("parb2_par", "REALSXP", REALSXP, parb2_par, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("npar", "INTSXP", INTSXP, npar, __FILE__, __LINE__);
  
  R_CheckArgument("nfixed", "INTSXP", INTSXP, nfixed, __FILE__, __LINE__);
  
  R_CheckArgument("TAC", "REALSXP", REALSXP, TAC, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("TAE", "REALSXP", REALSXP, TAE, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("FbyPar", "INTSXP", INTSXP, FbyPar, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("FbyFixed", "INTSXP", INTSXP, FbyFixed, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age_mid", "REALSXP", REALSXP, Wt_age_mid, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdevs", "REALSXP", REALSXP, Recdevs, __FILE__, __LINE__, 3, 1, SpawnPerYr, 1, npop, 1, nsim);
  
  R_CheckArgument("RecSpatialDevs", "REALSXP", REALSXP, RecSpatialDevs, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("nb2_par", "REALSXP", REALSXP, nb2_par, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("nbeforeb2_par", "REALSXP", REALSXP, nbeforeb2_par, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("cb2_par", "REALSXP", REALSXP, cb2_par, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  R_CheckArgument("popdyn_projection_objectiveb2_par", "REALSXP", REALSXP, popdyn_projection_objectiveb2_par, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(par), (char*)arg_par);
    
    arg_parb2_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_parb2_par, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(parb2_par), (char*)arg_parb2_par);
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAC), (char*)arg_TAC);
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAE), (char*)arg_TAE);
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyPar), (char*)arg_FbyPar);
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyFixed), (char*)arg_FbyFixed);
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_Wt_age_mid = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age_mid);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age_mid), (char*)arg_Wt_age_mid);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdevs), (char*)arg_Recdevs);
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(RecSpatialDevs), (char*)arg_RecSpatialDevs);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_nb2_par = 0;
    
    Plan_13.create(MemAllocator, arg_nb2_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(nb2_par), (char*)arg_nb2_par);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_nbeforeb2_par = 0;
    
    Plan_13.create(MemAllocator, arg_nbeforeb2_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(nbeforeb2_par), (char*)arg_nbeforeb2_par);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_cb2_par = 0;
    
    Plan_15.create(MemAllocator, arg_cb2_par);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(cb2_par), (char*)arg_cb2_par);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_sim_idx = INTEGER(sim_idx)[0];
    arg_popdyn_projection_objectiveb2_par = REAL(popdyn_projection_objectiveb2_par)[0];
  }
  else
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1, (void*)REAL(par));
    
    arg_parb2_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_parb2_par, 0, INTEGER(npar)[0] - 1, (void*)REAL(parb2_par));
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1, (void*)REAL(TAC));
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1, (void*)REAL(TAE));
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1, (void*)INTEGER(FbyPar));
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1, (void*)INTEGER(FbyFixed));
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_Wt_age_mid = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age_mid, (void*)REAL(Wt_age_mid));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs, (void*)REAL(Recdevs));
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs, (void*)REAL(RecSpatialDevs));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_nb2_par = 0;
    
    Plan_13.create(MemAllocator, arg_nb2_par, (void*)REAL(nb2_par));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_nbeforeb2_par = 0;
    
    Plan_13.create(MemAllocator, arg_nbeforeb2_par, (void*)REAL(nbeforeb2_par));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_cb2_par = 0;
    
    Plan_15.create(MemAllocator, arg_cb2_par, (void*)REAL(cb2_par));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_sim_idx = INTEGER(sim_idx)[0];
    arg_popdyn_projection_objectiveb2_par = REAL(popdyn_projection_objectiveb2_par)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POPDYN_PROJECTION_OBJECTIVE_BPAR(arg_par, arg_parb2_par, arg_npar, arg_nfixed, arg_TAC, arg_TAE, arg_FbyPar, arg_FbyFixed, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_Wt_age_mid, arg_sel, arg_mov, arg_h, arg_Recdist, arg_Recdevs, arg_RecSpatialDevs, arg_SRrel, arg_N, arg_nb2_par, arg_NBefore, arg_nbeforeb2_par, arg_SSN, arg_C, arg_cb2_par, arg_SSBA, arg_sim_idx, arg_popdyn_projection_objectiveb2_par);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_parb2_par, (char*)REAL(parb2_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_nb2_par, (char*)REAL(nb2_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_nbeforeb2_par, (char*)REAL(nbeforeb2_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_cb2_par, (char*)REAL(cb2_par));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
    REAL(popdyn_projection_objectiveb2_par)[0] = arg_popdyn_projection_objectiveb2_par;
  }
  else
  {
    REAL(popdyn_projection_objectiveb2_par)[0] = arg_popdyn_projection_objectiveb2_par;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_par);
  AdtArrayPlan::destroy(MemAllocator, arg_parb2_par);
  AdtArrayPlan::destroy(MemAllocator, arg_TAC);
  AdtArrayPlan::destroy(MemAllocator, arg_TAE);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyPar);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyFixed);
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age_mid);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdevs);
  AdtArrayPlan::destroy(MemAllocator, arg_RecSpatialDevs);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_nb2_par);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_nbeforeb2_par);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_cb2_par);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP sim_idx, SEXP popdyn_projection_objectiveb2_par)
{
  return (R_internal_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par, true));
}

SEXP D_OperatingModelBase::R_nt_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP sim_idx, SEXP popdyn_projection_objectiveb2_par)
{
  return (R_internal_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par, false));
}

SEXP D_OperatingModelBase::_get_Recsubyr(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)Recsubyr, "Recsubyr", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_Recsubyr(SEXP arg_Recsubyr, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)Recsubyr, "Recsubyr", arg_Recsubyr, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_Recsubyr(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)Recsubyr, "Recsubyr", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_Recsubyr(SEXP arg_Recsubyr, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)Recsubyr, "Recsubyr", arg_Recsubyr, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_internal_runHistoric(SEXP totF, SEXP qy, SEXP ECurrent, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, bool bTranslate)
{
  double arg_totF;
  ARRAY_2D arg_qy;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_3D arg_Recdevs;
  ARRAY_3D arg_RecSpatialDevs;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_2D arg_SSBA;
  
  R_CheckArgument("totF", "REALSXP", REALSXP, totF, __FILE__, __LINE__);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdevs", "REALSXP", REALSXP, Recdevs, __FILE__, __LINE__, 3, 1, SpawnPerYr, 1, npop, 1, nsim);
  
  R_CheckArgument("RecSpatialDevs", "REALSXP", REALSXP, RecSpatialDevs, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  if (bTranslate)
  {
    arg_totF = REAL(totF)[0];
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdevs), (char*)arg_Recdevs);
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(RecSpatialDevs), (char*)arg_RecSpatialDevs);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
  }
  else
  {
    arg_totF = REAL(totF)[0];
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs, (void*)REAL(Recdevs));
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs, (void*)REAL(RecSpatialDevs));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  runHistoric(arg_totF, arg_qy, arg_ECurrent, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_Recdevs, arg_RecSpatialDevs, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdevs);
  AdtArrayPlan::destroy(MemAllocator, arg_RecSpatialDevs);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_runHistoric(SEXP totF, SEXP qy, SEXP ECurrent, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA)
{
  return (R_internal_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, true));
}

SEXP D_OperatingModelBase::R_nt_runHistoric(SEXP totF, SEXP qy, SEXP ECurrent, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA)
{
  return (R_internal_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, false));
}

SEXP D_OperatingModelBase::R_internal_runProjection(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx, bool bTranslate)
{
  ARRAY_1D arg_par;
  int arg_npar;
  int arg_nfixed;
  ARRAY_1D arg_TAC;
  ARRAY_1D arg_TAE;
  ARRAY_1I arg_FbyPar;
  ARRAY_1I arg_FbyFixed;
  ARRAY_4D arg_ECurrent;
  ARRAY_2D arg_qy;
  ARRAY_2D arg_R0;
  ARRAY_3D arg_M;
  ARRAY_3D arg_mat;
  ARRAY_4D arg_Idist;
  ARRAY_3D arg_Len_age;
  ARRAY_3D arg_Wt_age;
  ARRAY_3D arg_sel;
  ARRAY_6D arg_mov;
  ARRAY_2D arg_h;
  ARRAY_3D arg_Recdist;
  ARRAY_3D arg_Recdevs;
  ARRAY_3D arg_RecSpatialDevs;
  ARRAY_1I arg_SRrel;
  ARRAY_5D arg_N;
  ARRAY_5D arg_NBefore;
  ARRAY_5D arg_SSN;
  ARRAY_6D arg_C;
  ARRAY_2D arg_SSBA;
  int arg_sim_idx;
  
  R_CheckArgument("par", "REALSXP", REALSXP, par, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("npar", "INTSXP", INTSXP, npar, __FILE__, __LINE__);
  
  R_CheckArgument("nfixed", "INTSXP", INTSXP, nfixed, __FILE__, __LINE__);
  
  R_CheckArgument("TAC", "REALSXP", REALSXP, TAC, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("TAE", "REALSXP", REALSXP, TAE, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("FbyPar", "INTSXP", INTSXP, FbyPar, __FILE__, __LINE__, 1, 0, INTEGER(npar)[0] - 1);
  
  R_CheckArgument("FbyFixed", "INTSXP", INTSXP, FbyFixed, __FILE__, __LINE__, 1, 0, INTEGER(nfixed)[0] - 1);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("qy", "REALSXP", REALSXP, qy, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("R0", "REALSXP", REALSXP, R0, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("M", "REALSXP", REALSXP, M, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("mat", "REALSXP", REALSXP, mat, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Idist", "REALSXP", REALSXP, Idist, __FILE__, __LINE__, 4, 1, nareas, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Len_age", "REALSXP", REALSXP, Len_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("Wt_age", "REALSXP", REALSXP, Wt_age, __FILE__, __LINE__, 3, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("sel", "REALSXP", REALSXP, sel, __FILE__, __LINE__, 3, 1, nages, 1, nfleets, 1, nsim);
  
  R_CheckArgument("mov", "REALSXP", REALSXP, mov, __FILE__, __LINE__, 6, 1, nareas, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("h", "REALSXP", REALSXP, h, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdist", "REALSXP", REALSXP, Recdist, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("Recdevs", "REALSXP", REALSXP, Recdevs, __FILE__, __LINE__, 3, 1, SpawnPerYr, 1, npop, 1, nsim);
  
  R_CheckArgument("RecSpatialDevs", "REALSXP", REALSXP, RecSpatialDevs, __FILE__, __LINE__, 3, 1, nareas, 1, npop, 1, nsim);
  
  R_CheckArgument("SRrel", "INTSXP", INTSXP, SRrel, __FILE__, __LINE__, 1, 1, npop);
  
  R_CheckArgument("N", "REALSXP", REALSXP, N, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("NBefore", "REALSXP", REALSXP, NBefore, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears + 1, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSN", "REALSXP", REALSXP, SSN, __FILE__, __LINE__, 5, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("C", "REALSXP", REALSXP, C, __FILE__, __LINE__, 6, 1, nfleets, 1, nareas, 1, nsubyears, 1, nages, 1, npop, 1, nsim);
  
  R_CheckArgument("SSBA", "REALSXP", REALSXP, SSBA, __FILE__, __LINE__, 2, 1, npop, 1, nsim);
  
  R_CheckArgument("sim_idx", "INTSXP", INTSXP, sim_idx, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(par), (char*)arg_par);
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAC), (char*)arg_TAC);
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAE), (char*)arg_TAE);
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyPar), (char*)arg_FbyPar);
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(FbyFixed), (char*)arg_FbyFixed);
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(qy), (char*)arg_qy);
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(R0), (char*)arg_R0);
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(M), (char*)arg_M);
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mat), (char*)arg_mat);
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Idist), (char*)arg_Idist);
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Len_age), (char*)arg_Len_age);
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Wt_age), (char*)arg_Wt_age);
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(sel), (char*)arg_sel);
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(mov), (char*)arg_mov);
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(h), (char*)arg_h);
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdist), (char*)arg_Recdist);
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(Recdevs), (char*)arg_Recdevs);
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(RecSpatialDevs), (char*)arg_RecSpatialDevs);
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)INTEGER(SRrel), (char*)arg_SRrel);
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(N), (char*)arg_N);
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(NBefore), (char*)arg_NBefore);
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSN), (char*)arg_SSN);
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(C), (char*)arg_C);
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(SSBA), (char*)arg_SSBA);
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  else
  {
    arg_par = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_par, 0, INTEGER(npar)[0] - 1, (void*)REAL(par));
    
    arg_npar = INTEGER(npar)[0];
    arg_nfixed = INTEGER(nfixed)[0];
    arg_TAC = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAC, 0, INTEGER(npar)[0] - 1, (void*)REAL(TAC));
    
    arg_TAE = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_TAE, 0, INTEGER(nfixed)[0] - 1, (void*)REAL(TAE));
    
    arg_FbyPar = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyPar, 0, INTEGER(npar)[0] - 1, (void*)INTEGER(FbyPar));
    
    arg_FbyFixed = 0;
    
    AdtArrayPlan::create(MemAllocator, arg_FbyFixed, 0, INTEGER(nfixed)[0] - 1, (void*)INTEGER(FbyFixed));
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_qy = 0;
    
    Plan_4.create(MemAllocator, arg_qy, (void*)REAL(qy));
    
    arg_R0 = 0;
    
    Plan_3.create(MemAllocator, arg_R0, (void*)REAL(R0));
    
    arg_M = 0;
    
    Plan_2.create(MemAllocator, arg_M, (void*)REAL(M));
    
    arg_mat = 0;
    
    Plan_2.create(MemAllocator, arg_mat, (void*)REAL(mat));
    
    arg_Idist = 0;
    
    Plan_9.create(MemAllocator, arg_Idist, (void*)REAL(Idist));
    
    arg_Len_age = 0;
    
    Plan_2.create(MemAllocator, arg_Len_age, (void*)REAL(Len_age));
    
    arg_Wt_age = 0;
    
    Plan_2.create(MemAllocator, arg_Wt_age, (void*)REAL(Wt_age));
    
    arg_sel = 0;
    
    Plan_10.create(MemAllocator, arg_sel, (void*)REAL(sel));
    
    arg_mov = 0;
    
    Plan_11.create(MemAllocator, arg_mov, (void*)REAL(mov));
    
    arg_h = 0;
    
    Plan_3.create(MemAllocator, arg_h, (void*)REAL(h));
    
    arg_Recdist = 0;
    
    Plan_6.create(MemAllocator, arg_Recdist, (void*)REAL(Recdist));
    
    arg_Recdevs = 0;
    
    Plan_8.create(MemAllocator, arg_Recdevs, (void*)REAL(Recdevs));
    
    arg_RecSpatialDevs = 0;
    
    Plan_6.create(MemAllocator, arg_RecSpatialDevs, (void*)REAL(RecSpatialDevs));
    
    arg_SRrel = 0;
    
    Plan_12.create(MemAllocator, arg_SRrel, (void*)INTEGER(SRrel));
    
    arg_N = 0;
    
    Plan_13.create(MemAllocator, arg_N, (void*)REAL(N));
    
    arg_NBefore = 0;
    
    Plan_13.create(MemAllocator, arg_NBefore, (void*)REAL(NBefore));
    
    arg_SSN = 0;
    
    Plan_14.create(MemAllocator, arg_SSN, (void*)REAL(SSN));
    
    arg_C = 0;
    
    Plan_15.create(MemAllocator, arg_C, (void*)REAL(C));
    
    arg_SSBA = 0;
    
    Plan_3.create(MemAllocator, arg_SSBA, (void*)REAL(SSBA));
    
    arg_sim_idx = INTEGER(sim_idx)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  runProjection(arg_par, arg_npar, arg_nfixed, arg_TAC, arg_TAE, arg_FbyPar, arg_FbyFixed, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_Recdevs, arg_RecSpatialDevs, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_sim_idx);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_par);
  AdtArrayPlan::destroy(MemAllocator, arg_TAC);
  AdtArrayPlan::destroy(MemAllocator, arg_TAE);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyPar);
  AdtArrayPlan::destroy(MemAllocator, arg_FbyFixed);
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_qy);
  AdtArrayPlan::destroy(MemAllocator, arg_R0);
  AdtArrayPlan::destroy(MemAllocator, arg_M);
  AdtArrayPlan::destroy(MemAllocator, arg_mat);
  AdtArrayPlan::destroy(MemAllocator, arg_Idist);
  AdtArrayPlan::destroy(MemAllocator, arg_Len_age);
  AdtArrayPlan::destroy(MemAllocator, arg_Wt_age);
  AdtArrayPlan::destroy(MemAllocator, arg_sel);
  AdtArrayPlan::destroy(MemAllocator, arg_mov);
  AdtArrayPlan::destroy(MemAllocator, arg_h);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdist);
  AdtArrayPlan::destroy(MemAllocator, arg_Recdevs);
  AdtArrayPlan::destroy(MemAllocator, arg_RecSpatialDevs);
  AdtArrayPlan::destroy(MemAllocator, arg_SRrel);
  AdtArrayPlan::destroy(MemAllocator, arg_N);
  AdtArrayPlan::destroy(MemAllocator, arg_NBefore);
  AdtArrayPlan::destroy(MemAllocator, arg_SSN);
  AdtArrayPlan::destroy(MemAllocator, arg_C);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBA);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelBase::R_runProjection(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  return (R_internal_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx, true));
}

SEXP D_OperatingModelBase::R_nt_runProjection(SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  return (R_internal_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx, false));
}

SEXP D_OperatingModelBase::_get_SpawnPerYr() const
{
  return (R_Scalar(SpawnPerYr));
}

SEXP D_OperatingModelBase::_set_SpawnPerYr(SEXP arg_SpawnPerYr)
{
  R_CheckArgument("arg_SpawnPerYr", "INTSXP", INTSXP, arg_SpawnPerYr, __FILE__, __LINE__);
  
  SpawnPerYr = INTEGER(arg_SpawnPerYr)[0];
  
  return (R_Empty());
}

SEXP D_OperatingModelBase::_get_SSB0(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)SSB0, "SSB0", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_SSB0(SEXP arg_SSB0, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)SSB0, "SSB0", arg_SSB0, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_SSB0(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)SSB0, "SSB0", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_SSB0(SEXP arg_SSB0, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)SSB0, "SSB0", arg_SSB0, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_SSBpR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)SSBpR, "SSBpR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_SSBpR(SEXP arg_SSBpR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)SSBpR, "SSBpR", arg_SSBpR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_SSBpR(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)SSBpR, "SSBpR", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_SSBpR(SEXP arg_SSBpR, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)SSBpR, "SSBpR", arg_SSBpR, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_surv(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)surv, "surv", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_surv(SEXP arg_surv, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)surv, "surv", arg_surv, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_get_nt_surv(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)surv, "surv", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelBase::_set_nt_surv(SEXP arg_surv, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)surv, "surv", arg_surv, sArgList, __FILE__, __LINE__);
  
  return (Result);
}
