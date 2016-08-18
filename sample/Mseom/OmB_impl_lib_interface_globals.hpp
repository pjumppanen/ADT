IMPL_TYPE_TAG(D_OperatingModelBase)


EXPORT SEXP OmB_get_aR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_aR(sArgList));
}

EXPORT SEXP OmB_set_aR(SEXP rInstance, SEXP arg_aR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_aR(arg_aR, sArgList));
}

EXPORT SEXP OmB_get_nt_aR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_aR(sArgList));
}

EXPORT SEXP OmB_set_nt_aR(SEXP rInstance, SEXP arg_aR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_aR(arg_aR, sArgList));
}

EXPORT SEXP OmB_get_B0(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_B0(sArgList));
}

EXPORT SEXP OmB_set_B0(SEXP rInstance, SEXP arg_B0, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_B0(arg_B0, sArgList));
}

EXPORT SEXP OmB_get_nt_B0(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_B0(sArgList));
}

EXPORT SEXP OmB_set_nt_B0(SEXP rInstance, SEXP arg_B0, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_B0(arg_B0, sArgList));
}

EXPORT SEXP OmB_get_bR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_bR(sArgList));
}

EXPORT SEXP OmB_set_bR(SEXP rInstance, SEXP arg_bR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_bR(arg_bR, sArgList));
}

EXPORT SEXP OmB_get_nt_bR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_bR(sArgList));
}

EXPORT SEXP OmB_set_nt_bR(SEXP rInstance, SEXP arg_bR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_bR(arg_bR, sArgList));
}

EXPORT SEXP OmB_get_EforYear(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_EforYear(sArgList));
}

EXPORT SEXP OmB_set_EforYear(SEXP rInstance, SEXP arg_EforYear, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_EforYear(arg_EforYear, sArgList));
}

EXPORT SEXP OmB_get_nt_EforYear(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_EforYear(sArgList));
}

EXPORT SEXP OmB_set_nt_EforYear(SEXP rInstance, SEXP arg_EforYear, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_EforYear(arg_EforYear, sArgList));
}

EXPORT SEXP OmB_get_eforyearb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_eforyearb2_par(sArgList));
}

EXPORT SEXP OmB_set_eforyearb2_par(SEXP rInstance, SEXP arg_eforyearb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_eforyearb2_par(arg_eforyearb2_par, sArgList));
}

EXPORT SEXP OmB_get_nt_eforyearb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_eforyearb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_eforyearb2_par(SEXP rInstance, SEXP arg_eforyearb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_eforyearb2_par(arg_eforyearb2_par, sArgList));
}

EXPORT SEXP OmB_get_eforyeard1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_eforyeard1_par(sArgList));
}

EXPORT SEXP OmB_set_eforyeard1_par(SEXP rInstance, SEXP arg_eforyeard1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_eforyeard1_par(arg_eforyeard1_par, sArgList));
}

EXPORT SEXP OmB_get_nt_eforyeard1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_eforyeard1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_eforyeard1_par(SEXP rInstance, SEXP arg_eforyeard1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_eforyeard1_par(arg_eforyeard1_par, sArgList));
}

EXPORT SEXP OmB_get_FM(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_FM(sArgList));
}

EXPORT SEXP OmB_set_FM(SEXP rInstance, SEXP arg_FM, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_FM(arg_FM, sArgList));
}

EXPORT SEXP OmB_get_nt_FM(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_FM(sArgList));
}

EXPORT SEXP OmB_set_nt_FM(SEXP rInstance, SEXP arg_FM, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_FM(arg_FM, sArgList));
}

EXPORT SEXP OmB_get_fmb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_fmb2_par(sArgList));
}

EXPORT SEXP OmB_set_fmb2_par(SEXP rInstance, SEXP arg_fmb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_fmb2_par(arg_fmb2_par, sArgList));
}

EXPORT SEXP OmB_get_nt_fmb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_fmb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_fmb2_par(SEXP rInstance, SEXP arg_fmb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_fmb2_par(arg_fmb2_par, sArgList));
}

EXPORT SEXP OmB_get_fmd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_fmd1_par(sArgList));
}

EXPORT SEXP OmB_set_fmd1_par(SEXP rInstance, SEXP arg_fmd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_fmd1_par(arg_fmd1_par, sArgList));
}

EXPORT SEXP OmB_get_nt_fmd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_fmd1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_fmd1_par(SEXP rInstance, SEXP arg_fmd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_fmd1_par(arg_fmd1_par, sArgList));
}

EXPORT SEXP OmB_R_initialiseParameters(SEXP rInstance, SEXP M, SEXP R0, SEXP mat, SEXP Idist, SEXP Wt_age, SEXP h)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_initialiseParameters(M, R0, mat, Idist, Wt_age, h);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_initialiseParameters(SEXP rInstance, SEXP M, SEXP R0, SEXP mat, SEXP Idist, SEXP Wt_age, SEXP h)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_initialiseParameters(M, R0, mat, Idist, Wt_age, h);
  
  return (Result);
}

EXPORT SEXP OmB_get_MovN(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MovN(sArgList));
}

EXPORT SEXP OmB_set_MovN(SEXP rInstance, SEXP arg_MovN, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MovN(arg_MovN, sArgList));
}

EXPORT SEXP OmB_get_nt_MovN(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MovN(sArgList));
}

EXPORT SEXP OmB_set_nt_MovN(SEXP rInstance, SEXP arg_MovN, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MovN(arg_MovN, sArgList));
}

EXPORT SEXP OmB_get_movnb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_movnb2_par(sArgList));
}

EXPORT SEXP OmB_set_movnb2_par(SEXP rInstance, SEXP arg_movnb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_movnb2_par(arg_movnb2_par, sArgList));
}

EXPORT SEXP OmB_get_nt_movnb2_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_movnb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_movnb2_par(SEXP rInstance, SEXP arg_movnb2_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_movnb2_par(arg_movnb2_par, sArgList));
}

EXPORT SEXP OmB_get_movnd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_movnd1_par(sArgList));
}

EXPORT SEXP OmB_set_movnd1_par(SEXP rInstance, SEXP arg_movnd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_movnd1_par(arg_movnd1_par, sArgList));
}

EXPORT SEXP OmB_get_nt_movnd1_par(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_movnd1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_movnd1_par(SEXP rInstance, SEXP arg_movnd1_par, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_movnd1_par(arg_movnd1_par, sArgList));
}

EXPORT SEXP OmB_get_MSY_Recdevs(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MSY_Recdevs(sArgList));
}

EXPORT SEXP OmB_set_MSY_Recdevs(SEXP rInstance, SEXP arg_MSY_Recdevs, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MSY_Recdevs(arg_MSY_Recdevs, sArgList));
}

EXPORT SEXP OmB_get_nt_MSY_Recdevs(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MSY_Recdevs(sArgList));
}

EXPORT SEXP OmB_set_nt_MSY_Recdevs(SEXP rInstance, SEXP arg_MSY_Recdevs, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MSY_Recdevs(arg_MSY_Recdevs, sArgList));
}

EXPORT SEXP OmB_get_MSY_RecSpatialDevs(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MSY_RecSpatialDevs(sArgList));
}

EXPORT SEXP OmB_set_MSY_RecSpatialDevs(SEXP rInstance, SEXP arg_MSY_RecSpatialDevs, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MSY_RecSpatialDevs(arg_MSY_RecSpatialDevs, sArgList));
}

EXPORT SEXP OmB_get_nt_MSY_RecSpatialDevs(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MSY_RecSpatialDevs(sArgList));
}

EXPORT SEXP OmB_set_nt_MSY_RecSpatialDevs(SEXP rInstance, SEXP arg_MSY_RecSpatialDevs, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MSY_RecSpatialDevs(arg_MSY_RecSpatialDevs, sArgList));
}

EXPORT SEXP OmB_R_MSYrefs(SEXP rInstance, SEXP par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYrefs(SEXP rInstance, SEXP par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP MSY, SEXP BMSY, SEXP SSBMSY, SEXP SSBMSY_B0, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_MSYrefs_objective(SEXP rInstance, SEXP par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYrefs_objective(SEXP rInstance, SEXP par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_MSYREFS_OBJECTIVE_DPAR(SEXP rInstance, SEXP par, SEXP pard1_par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, SEXP MSYrefs_objective)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYREFS_OBJECTIVE_DPAR(SEXP rInstance, SEXP par, SEXP pard1_par, SEXP nReport, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP ntargets, SEXP targpop, SEXP run_years, SEXP sim_idx, SEXP MSYrefs_objective)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective);
  
  return (Result);
}

EXPORT SEXP OmB_get_nages(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nages());
}

EXPORT SEXP OmB_set_nages(SEXP rInstance, SEXP arg_nages)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nages(arg_nages));
}

EXPORT SEXP OmB_get_nareas(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nareas());
}

EXPORT SEXP OmB_set_nareas(SEXP rInstance, SEXP arg_nareas)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nareas(arg_nareas));
}

EXPORT SEXP OmB_R_nextYear(SEXP rInstance, SEXP N, SEXP NBefore)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nextYear(N, NBefore);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_nextYear(SEXP rInstance, SEXP N, SEXP NBefore)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_nextYear(N, NBefore);
  
  return (Result);
}

EXPORT SEXP OmB_get_nfleets(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nfleets());
}

EXPORT SEXP OmB_set_nfleets(SEXP rInstance, SEXP arg_nfleets)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nfleets(arg_nfleets));
}

EXPORT SEXP OmB_get_npop(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_npop());
}

EXPORT SEXP OmB_set_npop(SEXP rInstance, SEXP arg_npop)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_npop(arg_npop));
}

EXPORT SEXP OmB_get_nsim(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nsim());
}

EXPORT SEXP OmB_set_nsim(SEXP rInstance, SEXP arg_nsim)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nsim(arg_nsim));
}

EXPORT SEXP OmB_get_nsubyears(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nsubyears());
}

EXPORT SEXP OmB_set_nsubyears(SEXP rInstance, SEXP arg_nsubyears)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nsubyears(arg_nsubyears));
}

EXPORT SEXP OmB_R_POPDYN_MSY_PAR_DPAR(SEXP rInstance, SEXP par, SEXP pard1_par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP run_years, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_MSY_PAR_DPAR(par, pard1_par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_MSY_PAR_DPAR(SEXP rInstance, SEXP par, SEXP pard1_par, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP run_years, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_MSY_PAR_DPAR(par, pard1_par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_NEXT_YEAR_DPAR(SEXP rInstance, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_NEXT_YEAR_DPAR(N, nd1_par, NBefore, nbefored1_par, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_NEXT_YEAR_DPAR(SEXP rInstance, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_NEXT_YEAR_DPAR(N, nd1_par, NBefore, nbefored1_par, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_popdyn_projection_objective(SEXP rInstance, SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_popdyn_projection_objective(SEXP rInstance, SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP rInstance, SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP sim_idx, SEXP popdyn_projection_objectiveb2_par)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP rInstance, SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP Wt_age_mid, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP sim_idx, SEXP popdyn_projection_objectiveb2_par)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_PROJECTION_PAR_BPAR(SEXP rInstance, SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_PROJECTION_PAR_BPAR(par, parb2_par, npar, nfixed, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_PROJECTION_PAR_BPAR(SEXP rInstance, SEXP par, SEXP parb2_par, SEXP npar, SEXP nfixed, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_PROJECTION_PAR_BPAR(par, parb2_par, npar, nfixed, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_YEAR_BPAR(SEXP rInstance, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP Eannual, SEXP eannualb2_par, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_YEAR_BPAR(qy, R0, M, mat, Len_age, Wt_age, sel, Eannual, eannualb2_par, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_YEAR_BPAR(SEXP rInstance, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP Eannual, SEXP eannualb2_par, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nb2_par, SEXP NBefore, SEXP nbeforeb2_par, SEXP SSN, SEXP C, SEXP cb2_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_YEAR_BPAR(qy, R0, M, mat, Len_age, Wt_age, sel, Eannual, eannualb2_par, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_YEAR_DPAR(SEXP rInstance, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP Eannual, SEXP eannuald1_par, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_YEAR_DPAR(qy, R0, M, mat, Len_age, Wt_age, sel, Eannual, eannuald1_par, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_YEAR_DPAR(SEXP rInstance, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP Eannual, SEXP eannuald1_par, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP nd1_par, SEXP NBefore, SEXP nbefored1_par, SEXP SSN, SEXP C, SEXP cd1_par, SEXP SSBA, SEXP bIgnoreLast, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_YEAR_DPAR(qy, R0, M, mat, Len_age, Wt_age, sel, Eannual, eannuald1_par, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, bIgnoreLast, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_get_Recsubyr(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_Recsubyr(sArgList));
}

EXPORT SEXP OmB_set_Recsubyr(SEXP rInstance, SEXP arg_Recsubyr, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_Recsubyr(arg_Recsubyr, sArgList));
}

EXPORT SEXP OmB_get_nt_Recsubyr(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_Recsubyr(sArgList));
}

EXPORT SEXP OmB_set_nt_Recsubyr(SEXP rInstance, SEXP arg_Recsubyr, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_Recsubyr(arg_Recsubyr, sArgList));
}

EXPORT SEXP OmB_R_runHistoric(SEXP rInstance, SEXP totF, SEXP qy, SEXP ECurrent, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_runHistoric(SEXP rInstance, SEXP totF, SEXP qy, SEXP ECurrent, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA);
  
  return (Result);
}

EXPORT SEXP OmB_R_runProjection(SEXP rInstance, SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_runProjection(SEXP rInstance, SEXP par, SEXP npar, SEXP nfixed, SEXP TAC, SEXP TAE, SEXP FbyPar, SEXP FbyFixed, SEXP ECurrent, SEXP qy, SEXP R0, SEXP M, SEXP mat, SEXP Idist, SEXP Len_age, SEXP Wt_age, SEXP sel, SEXP mov, SEXP h, SEXP Recdist, SEXP Recdevs, SEXP RecSpatialDevs, SEXP SRrel, SEXP N, SEXP NBefore, SEXP SSN, SEXP C, SEXP SSBA, SEXP sim_idx)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_get_SpawnPerYr(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SpawnPerYr());
}

EXPORT SEXP OmB_set_SpawnPerYr(SEXP rInstance, SEXP arg_SpawnPerYr)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SpawnPerYr(arg_SpawnPerYr));
}

EXPORT SEXP OmB_get_SSB0(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SSB0(sArgList));
}

EXPORT SEXP OmB_set_SSB0(SEXP rInstance, SEXP arg_SSB0, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SSB0(arg_SSB0, sArgList));
}

EXPORT SEXP OmB_get_nt_SSB0(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_SSB0(sArgList));
}

EXPORT SEXP OmB_set_nt_SSB0(SEXP rInstance, SEXP arg_SSB0, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_SSB0(arg_SSB0, sArgList));
}

EXPORT SEXP OmB_get_SSBpR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SSBpR(sArgList));
}

EXPORT SEXP OmB_set_SSBpR(SEXP rInstance, SEXP arg_SSBpR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SSBpR(arg_SSBpR, sArgList));
}

EXPORT SEXP OmB_get_nt_SSBpR(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_SSBpR(sArgList));
}

EXPORT SEXP OmB_set_nt_SSBpR(SEXP rInstance, SEXP arg_SSBpR, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_SSBpR(arg_SSBpR, sArgList));
}

EXPORT SEXP OmB_get_surv(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_surv(sArgList));
}

EXPORT SEXP OmB_set_surv(SEXP rInstance, SEXP arg_surv, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_surv(arg_surv, sArgList));
}

EXPORT SEXP OmB_get_nt_surv(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_surv(sArgList));
}

EXPORT SEXP OmB_set_nt_surv(SEXP rInstance, SEXP arg_surv, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_surv(arg_surv, sArgList));
}
