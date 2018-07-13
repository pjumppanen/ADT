IMPL_TYPE_TAG(D_OperatingModelMin)


EXPORT SEXP Om_R_beginProjection(SEXP args)
{
  SEXP rInstance;
  SEXP pPar;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pPar = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_beginProjection(pPar);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_beginProjection(SEXP args)
{
  SEXP rInstance;
  SEXP pPar;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pPar = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_beginProjection(pPar);
  
  return (Result);
}

EXPORT SEXP Om_get_cd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_cd1_par(sArgList));
}

EXPORT SEXP Om_set_cd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_cd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_cd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_cd1_par(arg_cd1_par, sArgList));
}


EXPORT SEXP Om_get_nt_cd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_cd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_cd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_cd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_cd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_cd1_par(arg_cd1_par, sArgList));
}


EXPORT SEXP Om_R_findMSYref(SEXP args)
{
  SEXP rInstance;
  SEXP nReport;
  SEXP ECurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP MinPar;
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP maxit;
  SEXP nSim_Idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); MinPar = CAR(args);
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); maxit = CAR(args);
  args = CDR(args); nSim_Idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_findMSYref(SEXP args)
{
  SEXP rInstance;
  SEXP nReport;
  SEXP ECurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP MinPar;
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP maxit;
  SEXP nSim_Idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); MinPar = CAR(args);
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); maxit = CAR(args);
  args = CDR(args); nSim_Idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx);
  
  return (Result);
}

EXPORT SEXP Om_R_findMSYrefs(SEXP args)
{
  SEXP rInstance;
  SEXP nReport;
  SEXP ECurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP MinPar;
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP maxit;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); MinPar = CAR(args);
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); maxit = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_findMSYrefs(SEXP args)
{
  SEXP rInstance;
  SEXP nReport;
  SEXP ECurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP MinPar;
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP maxit;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); MinPar = CAR(args);
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); maxit = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit);
  
  return (Result);
}

EXPORT SEXP Om_get_last_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_last_par(sArgList));
}

EXPORT SEXP Om_set_last_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_last_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_last_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_last_par(arg_last_par, sArgList));
}


EXPORT SEXP Om_get_nt_last_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_last_par(sArgList));
}

EXPORT SEXP Om_set_nt_last_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_last_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_last_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_last_par(arg_last_par, sArgList));
}


EXPORT SEXP Om_get_nbefored1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nbefored1_par(sArgList));
}

EXPORT SEXP Om_set_nbefored1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nbefored1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nbefored1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nbefored1_par(arg_nbefored1_par, sArgList));
}


EXPORT SEXP Om_get_nt_nbefored1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_nbefored1_par(sArgList));
}

EXPORT SEXP Om_set_nt_nbefored1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nbefored1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nbefored1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_nbefored1_par(arg_nbefored1_par, sArgList));
}


EXPORT SEXP Om_get_nd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nd1_par(sArgList));
}

EXPORT SEXP Om_set_nd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nd1_par(arg_nd1_par, sArgList));
}


EXPORT SEXP Om_get_nt_nd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_nd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_nd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_nd1_par(arg_nd1_par, sArgList));
}


EXPORT SEXP Om_R_projection(SEXP args)
{
  SEXP rInstance;
  SEXP nProjectionYear;
  SEXP nReport;
  SEXP dEffortCeiling;
  SEXP TAC;
  SEXP TAEbyF;
  SEXP TACEError;
  SEXP ECurrent;
  SEXP CMCurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP Wt_age_mid;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP maxit;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nProjectionYear = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); dEffortCeiling = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAEbyF = CAR(args);
  args = CDR(args); TACEError = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); CMCurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); Wt_age_mid = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); maxit = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_projection(SEXP args)
{
  SEXP rInstance;
  SEXP nProjectionYear;
  SEXP nReport;
  SEXP dEffortCeiling;
  SEXP TAC;
  SEXP TAEbyF;
  SEXP TACEError;
  SEXP ECurrent;
  SEXP CMCurrent;
  SEXP qy;
  SEXP R0;
  SEXP M;
  SEXP mat;
  SEXP Idist;
  SEXP Len_age;
  SEXP Wt_age;
  SEXP Wt_age_mid;
  SEXP sel;
  SEXP mov;
  SEXP h;
  SEXP Recdist;
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP maxit;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); nProjectionYear = CAR(args);
  args = CDR(args); nReport = CAR(args);
  args = CDR(args); dEffortCeiling = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAEbyF = CAR(args);
  args = CDR(args); TACEError = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
  args = CDR(args); CMCurrent = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Len_age = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); Wt_age_mid = CAR(args);
  args = CDR(args); sel = CAR(args);
  args = CDR(args); mov = CAR(args);
  args = CDR(args); h = CAR(args);
  args = CDR(args); Recdist = CAR(args);
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); maxit = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit);
  
  return (Result);
}

EXPORT SEXP Om_get_ssnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_ssnd1_par(sArgList));
}

EXPORT SEXP Om_set_ssnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_ssnd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_ssnd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_ssnd1_par(arg_ssnd1_par, sArgList));
}


EXPORT SEXP Om_get_nt_ssnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_ssnd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_ssnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_ssnd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_ssnd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_ssnd1_par(arg_ssnd1_par, sArgList));
}


EXPORT SEXP Om_get_TACbyF(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_TACbyF(sArgList));
}

EXPORT SEXP Om_set_TACbyF(SEXP args)
{
  SEXP rInstance;
  SEXP arg_TACbyF;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_TACbyF = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_TACbyF(arg_TACbyF, sArgList));
}


EXPORT SEXP Om_get_nt_TACbyF(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_TACbyF(sArgList));
}

EXPORT SEXP Om_set_nt_TACbyF(SEXP args)
{
  SEXP rInstance;
  SEXP arg_TACbyF;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_TACbyF = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_TACbyF(arg_TACbyF, sArgList));
}

