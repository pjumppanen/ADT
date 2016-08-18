
SEXP D_OperatingModelMin::R_internal_beginProjection(SEXP pPar, bool bTranslate)
{
  ARRAY_1D arg_pPar;
  
  R_CheckArgument("pPar", "REALSXP", REALSXP, pPar, __FILE__, __LINE__, 1, 1, nfleets);
  
  if (bTranslate)
  {
    arg_pPar = 0;
    
    Plan_17.create(MemAllocator, arg_pPar);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(pPar), (char*)arg_pPar);
    
  }
  else
  {
    arg_pPar = 0;
    
    Plan_17.create(MemAllocator, arg_pPar, (void*)REAL(pPar));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  beginProjection(arg_pPar);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_pPar);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelMin::R_beginProjection(SEXP pPar)
{
  return (R_internal_beginProjection(pPar, true));
}

SEXP D_OperatingModelMin::R_nt_beginProjection(SEXP pPar)
{
  return (R_internal_beginProjection(pPar, false));
}

SEXP D_OperatingModelMin::_get_cd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)cd1_par, "cd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_cd1_par(SEXP arg_cd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)cd1_par, "cd1_par", arg_cd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_cd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)cd1_par, "cd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_cd1_par(SEXP arg_cd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)cd1_par, "cd1_par", arg_cd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::R_internal_findMSYref(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, SEXP nSim_Idx, bool bTranslate)
{
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
  ARRAY_1D arg_MinPar;
  ARRAY_1D arg_MSY;
  ARRAY_1D arg_BMSY;
  ARRAY_1D arg_SSBMSY;
  ARRAY_1D arg_SSBMSY_B0;
  int arg_maxit;
  int arg_nSim_Idx;
  
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
  
  R_CheckArgument("MinPar", "REALSXP", REALSXP, MinPar, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("MSY", "REALSXP", REALSXP, MSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("BMSY", "REALSXP", REALSXP, BMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY", "REALSXP", REALSXP, SSBMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY_B0", "REALSXP", REALSXP, SSBMSY_B0, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("maxit", "INTSXP", INTSXP, maxit, __FILE__, __LINE__);
  
  R_CheckArgument("nSim_Idx", "INTSXP", INTSXP, nSim_Idx, __FILE__, __LINE__);
  
  if (bTranslate)
  {
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
    arg_MinPar = 0;
    
    Plan_16.create(MemAllocator, arg_MinPar);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(MinPar), (char*)arg_MinPar);
    
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
    
    arg_maxit = INTEGER(maxit)[0];
    arg_nSim_Idx = INTEGER(nSim_Idx)[0];
  }
  else
  {
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
    arg_MinPar = 0;
    
    Plan_16.create(MemAllocator, arg_MinPar, (void*)REAL(MinPar));
    
    arg_MSY = 0;
    
    Plan_16.create(MemAllocator, arg_MSY, (void*)REAL(MSY));
    
    arg_BMSY = 0;
    
    Plan_16.create(MemAllocator, arg_BMSY, (void*)REAL(BMSY));
    
    arg_SSBMSY = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY, (void*)REAL(SSBMSY));
    
    arg_SSBMSY_B0 = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY_B0, (void*)REAL(SSBMSY_B0));
    
    arg_maxit = INTEGER(maxit)[0];
    arg_nSim_Idx = INTEGER(nSim_Idx)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  findMSYref(arg_nReport, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_ntargets, arg_targpop, arg_run_years, arg_MinPar, arg_MSY, arg_BMSY, arg_SSBMSY, arg_SSBMSY_B0, arg_maxit, arg_nSim_Idx);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_MinPar, (char*)REAL(MinPar));
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
  AdtArrayPlan::destroy(MemAllocator, arg_MinPar);
  AdtArrayPlan::destroy(MemAllocator, arg_MSY);
  AdtArrayPlan::destroy(MemAllocator, arg_BMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY_B0);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelMin::R_findMSYref(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, SEXP nSim_Idx)
{
  return (R_internal_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx, true));
}

SEXP D_OperatingModelMin::R_nt_findMSYref(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, SEXP nSim_Idx)
{
  return (R_internal_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx, false));
}

SEXP D_OperatingModelMin::R_internal_findMSYrefs(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, bool bTranslate)
{
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
  ARRAY_1D arg_MinPar;
  ARRAY_1D arg_MSY;
  ARRAY_1D arg_BMSY;
  ARRAY_1D arg_SSBMSY;
  ARRAY_1D arg_SSBMSY_B0;
  int arg_maxit;
  
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
  
  R_CheckArgument("MinPar", "REALSXP", REALSXP, MinPar, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("MSY", "REALSXP", REALSXP, MSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("BMSY", "REALSXP", REALSXP, BMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY", "REALSXP", REALSXP, SSBMSY, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("SSBMSY_B0", "REALSXP", REALSXP, SSBMSY_B0, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("maxit", "INTSXP", INTSXP, maxit, __FILE__, __LINE__);
  
  if (bTranslate)
  {
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
    arg_MinPar = 0;
    
    Plan_16.create(MemAllocator, arg_MinPar);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(MinPar), (char*)arg_MinPar);
    
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
    
    arg_maxit = INTEGER(maxit)[0];
  }
  else
  {
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
    arg_MinPar = 0;
    
    Plan_16.create(MemAllocator, arg_MinPar, (void*)REAL(MinPar));
    
    arg_MSY = 0;
    
    Plan_16.create(MemAllocator, arg_MSY, (void*)REAL(MSY));
    
    arg_BMSY = 0;
    
    Plan_16.create(MemAllocator, arg_BMSY, (void*)REAL(BMSY));
    
    arg_SSBMSY = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY, (void*)REAL(SSBMSY));
    
    arg_SSBMSY_B0 = 0;
    
    Plan_16.create(MemAllocator, arg_SSBMSY_B0, (void*)REAL(SSBMSY_B0));
    
    arg_maxit = INTEGER(maxit)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  findMSYrefs(arg_nReport, arg_ECurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_sel, arg_mov, arg_h, arg_Recdist, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_ntargets, arg_targpop, arg_run_years, arg_MinPar, arg_MSY, arg_BMSY, arg_SSBMSY, arg_SSBMSY_B0, arg_maxit);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_N, (char*)REAL(N));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_NBefore, (char*)REAL(NBefore));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSN, (char*)REAL(SSN));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_C, (char*)REAL(C));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_SSBA, (char*)REAL(SSBA));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_MinPar, (char*)REAL(MinPar));
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
  AdtArrayPlan::destroy(MemAllocator, arg_MinPar);
  AdtArrayPlan::destroy(MemAllocator, arg_MSY);
  AdtArrayPlan::destroy(MemAllocator, arg_BMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY);
  AdtArrayPlan::destroy(MemAllocator, arg_SSBMSY_B0);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_OperatingModelMin::R_findMSYrefs(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit)
{
  return (R_internal_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, true));
}

SEXP D_OperatingModelMin::R_nt_findMSYrefs(SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit)
{
  return (R_internal_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, false));
}

SEXP D_OperatingModelMin::_get_last_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)last_par, "last_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_last_par(SEXP arg_last_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)last_par, "last_par", arg_last_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_last_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)last_par, "last_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_last_par(SEXP arg_last_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)last_par, "last_par", arg_last_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nbefored1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)nbefored1_par, "nbefored1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nbefored1_par(SEXP arg_nbefored1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)nbefored1_par, "nbefored1_par", arg_nbefored1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_nbefored1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)nbefored1_par, "nbefored1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_nbefored1_par(SEXP arg_nbefored1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)nbefored1_par, "nbefored1_par", arg_nbefored1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)nd1_par, "nd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nd1_par(SEXP arg_nd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)nd1_par, "nd1_par", arg_nd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_nd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)nd1_par, "nd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_nd1_par(SEXP arg_nd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)nd1_par, "nd1_par", arg_nd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::R_internal_projection(SEXP nProjectionYear, SEXP nReport, SEXP dEffortCeiling, SEXP TAC, SEXP TAEbyF, SEXP TACEError, SEXP ECurrent, SEXP CMCurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP maxit, bool bTranslate)
{
  int arg_nProjectionYear;
  int arg_nReport;
  double arg_dEffortCeiling;
  ARRAY_1D arg_TAC;
  ARRAY_2D arg_TAEbyF;
  ARRAY_2D arg_TACEError;
  ARRAY_4D arg_ECurrent;
  ARRAY_4D arg_CMCurrent;
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
  int arg_maxit;
  
  R_CheckArgument("nProjectionYear", "INTSXP", INTSXP, nProjectionYear, __FILE__, __LINE__);
  
  R_CheckArgument("nReport", "INTSXP", INTSXP, nReport, __FILE__, __LINE__);
  
  R_CheckArgument("dEffortCeiling", "REALSXP", REALSXP, dEffortCeiling, __FILE__, __LINE__);
  
  R_CheckArgument("TAC", "REALSXP", REALSXP, TAC, __FILE__, __LINE__, 1, 1, nsim);
  
  R_CheckArgument("TAEbyF", "REALSXP", REALSXP, TAEbyF, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("TACEError", "REALSXP", REALSXP, TACEError, __FILE__, __LINE__, 2, 1, nfleets, 1, nsim);
  
  R_CheckArgument("ECurrent", "REALSXP", REALSXP, ECurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
  R_CheckArgument("CMCurrent", "REALSXP", REALSXP, CMCurrent, __FILE__, __LINE__, 4, 1, nfleets, 1, nareas, 1, nsubyears, 1, nsim);
  
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
  
  R_CheckArgument("maxit", "INTSXP", INTSXP, maxit, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_nProjectionYear = INTEGER(nProjectionYear)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_dEffortCeiling = REAL(dEffortCeiling)[0];
    arg_TAC = 0;
    
    Plan_16.create(MemAllocator, arg_TAC);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAC), (char*)arg_TAC);
    
    arg_TAEbyF = 0;
    
    Plan_4.create(MemAllocator, arg_TAEbyF);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TAEbyF), (char*)arg_TAEbyF);
    
    arg_TACEError = 0;
    
    Plan_4.create(MemAllocator, arg_TACEError);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(TACEError), (char*)arg_TACEError);
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(ECurrent), (char*)arg_ECurrent);
    
    arg_CMCurrent = 0;
    
    Plan_1.create(MemAllocator, arg_CMCurrent);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(CMCurrent), (char*)arg_CMCurrent);
    
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
    
    arg_maxit = INTEGER(maxit)[0];
  }
  else
  {
    arg_nProjectionYear = INTEGER(nProjectionYear)[0];
    arg_nReport = INTEGER(nReport)[0];
    arg_dEffortCeiling = REAL(dEffortCeiling)[0];
    arg_TAC = 0;
    
    Plan_16.create(MemAllocator, arg_TAC, (void*)REAL(TAC));
    
    arg_TAEbyF = 0;
    
    Plan_4.create(MemAllocator, arg_TAEbyF, (void*)REAL(TAEbyF));
    
    arg_TACEError = 0;
    
    Plan_4.create(MemAllocator, arg_TACEError, (void*)REAL(TACEError));
    
    arg_ECurrent = 0;
    
    Plan_1.create(MemAllocator, arg_ECurrent, (void*)REAL(ECurrent));
    
    arg_CMCurrent = 0;
    
    Plan_1.create(MemAllocator, arg_CMCurrent, (void*)REAL(CMCurrent));
    
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
    
    arg_maxit = INTEGER(maxit)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  projection(arg_nProjectionYear, arg_nReport, arg_dEffortCeiling, arg_TAC, arg_TAEbyF, arg_TACEError, arg_ECurrent, arg_CMCurrent, arg_qy, arg_R0, arg_M, arg_mat, arg_Idist, arg_Len_age, arg_Wt_age, arg_Wt_age_mid, arg_sel, arg_mov, arg_h, arg_Recdist, arg_Recdevs, arg_RecSpatialDevs, arg_SRrel, arg_N, arg_NBefore, arg_SSN, arg_C, arg_SSBA, arg_maxit);
  
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
  
  AdtArrayPlan::destroy(MemAllocator, arg_TAC);
  AdtArrayPlan::destroy(MemAllocator, arg_TAEbyF);
  AdtArrayPlan::destroy(MemAllocator, arg_TACEError);
  AdtArrayPlan::destroy(MemAllocator, arg_ECurrent);
  AdtArrayPlan::destroy(MemAllocator, arg_CMCurrent);
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

SEXP D_OperatingModelMin::R_projection(SEXP nProjectionYear, SEXP nReport, SEXP dEffortCeiling, SEXP TAC, SEXP TAEbyF, SEXP TACEError, SEXP ECurrent, SEXP CMCurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP maxit)
{
  return (R_internal_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit, true));
}

SEXP D_OperatingModelMin::R_nt_projection(SEXP nProjectionYear, SEXP nReport, SEXP dEffortCeiling, SEXP TAC, SEXP TAEbyF, SEXP TACEError, SEXP ECurrent, SEXP CMCurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP maxit)
{
  return (R_internal_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit, false));
}

SEXP D_OperatingModelMin::_get_ssnd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)ssnd1_par, "ssnd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_ssnd1_par(SEXP arg_ssnd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)ssnd1_par, "ssnd1_par", arg_ssnd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_ssnd1_par(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)ssnd1_par, "ssnd1_par", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_ssnd1_par(SEXP arg_ssnd1_par, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)ssnd1_par, "ssnd1_par", arg_ssnd1_par, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_TACbyF(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)TACbyF, "TACbyF", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_TACbyF(SEXP arg_TACbyF, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)TACbyF, "TACbyF", arg_TACbyF, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_get_nt_TACbyF(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)TACbyF, "TACbyF", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP D_OperatingModelMin::_set_nt_TACbyF(SEXP arg_TACbyF, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)TACbyF, "TACbyF", arg_TACbyF, sArgList, __FILE__, __LINE__);
  
  return (Result);
}
