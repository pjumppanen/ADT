IMPL_TYPE_TAG(D_OperatingModelMin)


EXPORT SEXP Om_R_beginProjection(SEXP rInstance, SEXP pPar)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_beginProjection(pPar);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_beginProjection(SEXP rInstance, SEXP pPar)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_beginProjection(pPar);
  
  return (Result);
}

EXPORT SEXP Om_get_cd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_cd1_par(sArgList));
}

EXPORT SEXP Om_set_cd1_par(SEXP rInstance, SEXP arg_cd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_cd1_par(arg_cd1_par, sArgList));
}

EXPORT SEXP Om_get_nt_cd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_cd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_cd1_par(SEXP rInstance, SEXP arg_cd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_cd1_par(arg_cd1_par, sArgList));
}

EXPORT SEXP Om_R_findMSYref(SEXP rInstance, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, SEXP nSim_Idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_findMSYref(SEXP rInstance, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit, SEXP nSim_Idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_findMSYref(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit, nSim_Idx);
  
  return (Result);
}

EXPORT SEXP Om_R_findMSYrefs(SEXP rInstance, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_findMSYrefs(SEXP rInstance, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MinPar, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP maxit)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_findMSYrefs(nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MinPar, MSY, BMSY, SSBMSY, SSBMSY_B0, maxit);
  
  return (Result);
}

EXPORT SEXP Om_get_last_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_last_par(sArgList));
}

EXPORT SEXP Om_set_last_par(SEXP rInstance, SEXP arg_last_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_last_par(arg_last_par, sArgList));
}

EXPORT SEXP Om_get_nt_last_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_last_par(sArgList));
}

EXPORT SEXP Om_set_nt_last_par(SEXP rInstance, SEXP arg_last_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_last_par(arg_last_par, sArgList));
}

EXPORT SEXP Om_get_nbefored1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nbefored1_par(sArgList));
}

EXPORT SEXP Om_set_nbefored1_par(SEXP rInstance, SEXP arg_nbefored1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nbefored1_par(arg_nbefored1_par, sArgList));
}

EXPORT SEXP Om_get_nt_nbefored1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_nbefored1_par(sArgList));
}

EXPORT SEXP Om_set_nt_nbefored1_par(SEXP rInstance, SEXP arg_nbefored1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_nbefored1_par(arg_nbefored1_par, sArgList));
}

EXPORT SEXP Om_get_nd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nd1_par(sArgList));
}

EXPORT SEXP Om_set_nd1_par(SEXP rInstance, SEXP arg_nd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nd1_par(arg_nd1_par, sArgList));
}

EXPORT SEXP Om_get_nt_nd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_nd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_nd1_par(SEXP rInstance, SEXP arg_nd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_nd1_par(arg_nd1_par, sArgList));
}

EXPORT SEXP Om_R_projection(SEXP rInstance, SEXP nProjectionYear, SEXP nReport, SEXP dEffortCeiling, SEXP TAC, SEXP TAEbyF, SEXP TACEError, SEXP ECurrent, SEXP CMCurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP maxit)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit);
  
  return (Result);
}

EXPORT SEXP Om_R_nt_projection(SEXP rInstance, SEXP nProjectionYear, SEXP nReport, SEXP dEffortCeiling, SEXP TAC, SEXP TAEbyF, SEXP TACEError, SEXP ECurrent, SEXP CMCurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP maxit)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_projection(nProjectionYear, nReport, dEffortCeiling, TAC, TAEbyF, TACEError, ECurrent, CMCurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, maxit);
  
  return (Result);
}

EXPORT SEXP Om_get_ssnd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_ssnd1_par(sArgList));
}

EXPORT SEXP Om_set_ssnd1_par(SEXP rInstance, SEXP arg_ssnd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_ssnd1_par(arg_ssnd1_par, sArgList));
}

EXPORT SEXP Om_get_nt_ssnd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_ssnd1_par(sArgList));
}

EXPORT SEXP Om_set_nt_ssnd1_par(SEXP rInstance, SEXP arg_ssnd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_ssnd1_par(arg_ssnd1_par, sArgList));
}

EXPORT SEXP Om_get_TACbyF(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_TACbyF(sArgList));
}

EXPORT SEXP Om_set_TACbyF(SEXP rInstance, SEXP arg_TACbyF, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_TACbyF(arg_TACbyF, sArgList));
}

EXPORT SEXP Om_get_nt_TACbyF(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_TACbyF(sArgList));
}

EXPORT SEXP Om_set_nt_TACbyF(SEXP rInstance, SEXP arg_TACbyF, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_TACbyF(arg_TACbyF, sArgList));
}
