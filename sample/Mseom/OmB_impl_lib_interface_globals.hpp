IMPL_TYPE_TAG(D_OperatingModelBase)


EXPORT SEXP OmB_get_aR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_aR(sArgList));
}

EXPORT SEXP OmB_set_aR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_aR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_aR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_aR(arg_aR, sArgList));
}


EXPORT SEXP OmB_get_nt_aR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_aR(sArgList));
}

EXPORT SEXP OmB_set_nt_aR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_aR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_aR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_aR(arg_aR, sArgList));
}


EXPORT SEXP OmB_get_B0(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_B0(sArgList));
}

EXPORT SEXP OmB_set_B0(SEXP args)
{
  SEXP rInstance;
  SEXP arg_B0;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_B0 = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_B0(arg_B0, sArgList));
}


EXPORT SEXP OmB_get_nt_B0(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_B0(sArgList));
}

EXPORT SEXP OmB_set_nt_B0(SEXP args)
{
  SEXP rInstance;
  SEXP arg_B0;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_B0 = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_B0(arg_B0, sArgList));
}


EXPORT SEXP OmB_get_bR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_bR(sArgList));
}

EXPORT SEXP OmB_set_bR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_bR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_bR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_bR(arg_bR, sArgList));
}


EXPORT SEXP OmB_get_nt_bR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_bR(sArgList));
}

EXPORT SEXP OmB_set_nt_bR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_bR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_bR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_bR(arg_bR, sArgList));
}


EXPORT SEXP OmB_get_EforYear(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_EforYear(sArgList));
}

EXPORT SEXP OmB_set_EforYear(SEXP args)
{
  SEXP rInstance;
  SEXP arg_EforYear;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_EforYear = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_EforYear(arg_EforYear, sArgList));
}


EXPORT SEXP OmB_get_nt_EforYear(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_EforYear(sArgList));
}

EXPORT SEXP OmB_set_nt_EforYear(SEXP args)
{
  SEXP rInstance;
  SEXP arg_EforYear;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_EforYear = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_EforYear(arg_EforYear, sArgList));
}


EXPORT SEXP OmB_get_eforyearb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_eforyearb2_par(sArgList));
}

EXPORT SEXP OmB_set_eforyearb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_eforyearb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_eforyearb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_eforyearb2_par(arg_eforyearb2_par, sArgList));
}


EXPORT SEXP OmB_get_nt_eforyearb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_eforyearb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_eforyearb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_eforyearb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_eforyearb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_eforyearb2_par(arg_eforyearb2_par, sArgList));
}


EXPORT SEXP OmB_get_eforyeard1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_eforyeard1_par(sArgList));
}

EXPORT SEXP OmB_set_eforyeard1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_eforyeard1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_eforyeard1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_eforyeard1_par(arg_eforyeard1_par, sArgList));
}


EXPORT SEXP OmB_get_nt_eforyeard1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_eforyeard1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_eforyeard1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_eforyeard1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_eforyeard1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_eforyeard1_par(arg_eforyeard1_par, sArgList));
}


EXPORT SEXP OmB_get_FM(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_FM(sArgList));
}

EXPORT SEXP OmB_set_FM(SEXP args)
{
  SEXP rInstance;
  SEXP arg_FM;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_FM = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_FM(arg_FM, sArgList));
}


EXPORT SEXP OmB_get_nt_FM(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_FM(sArgList));
}

EXPORT SEXP OmB_set_nt_FM(SEXP args)
{
  SEXP rInstance;
  SEXP arg_FM;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_FM = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_FM(arg_FM, sArgList));
}


EXPORT SEXP OmB_get_fmb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_fmb2_par(sArgList));
}

EXPORT SEXP OmB_set_fmb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_fmb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_fmb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_fmb2_par(arg_fmb2_par, sArgList));
}


EXPORT SEXP OmB_get_nt_fmb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_fmb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_fmb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_fmb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_fmb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_fmb2_par(arg_fmb2_par, sArgList));
}


EXPORT SEXP OmB_get_fmd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_fmd1_par(sArgList));
}

EXPORT SEXP OmB_set_fmd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_fmd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_fmd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_fmd1_par(arg_fmd1_par, sArgList));
}


EXPORT SEXP OmB_get_nt_fmd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_fmd1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_fmd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_fmd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_fmd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_fmd1_par(arg_fmd1_par, sArgList));
}


EXPORT SEXP OmB_R_initialiseParameters(SEXP args)
{
  SEXP rInstance;
  SEXP M;
  SEXP R0;
  SEXP mat;
  SEXP Idist;
  SEXP Wt_age;
  SEXP h;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); h = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_initialiseParameters(M, R0, mat, Idist, Wt_age, h);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_initialiseParameters(SEXP args)
{
  SEXP rInstance;
  SEXP M;
  SEXP R0;
  SEXP mat;
  SEXP Idist;
  SEXP Wt_age;
  SEXP h;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); M = CAR(args);
  args = CDR(args); R0 = CAR(args);
  args = CDR(args); mat = CAR(args);
  args = CDR(args); Idist = CAR(args);
  args = CDR(args); Wt_age = CAR(args);
  args = CDR(args); h = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_initialiseParameters(M, R0, mat, Idist, Wt_age, h);
  
  return (Result);
}

EXPORT SEXP OmB_get_MovN(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MovN(sArgList));
}

EXPORT SEXP OmB_set_MovN(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MovN;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MovN = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MovN(arg_MovN, sArgList));
}


EXPORT SEXP OmB_get_nt_MovN(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MovN(sArgList));
}

EXPORT SEXP OmB_set_nt_MovN(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MovN;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MovN = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MovN(arg_MovN, sArgList));
}


EXPORT SEXP OmB_get_movnb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_movnb2_par(sArgList));
}

EXPORT SEXP OmB_set_movnb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_movnb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_movnb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_movnb2_par(arg_movnb2_par, sArgList));
}


EXPORT SEXP OmB_get_nt_movnb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_movnb2_par(sArgList));
}

EXPORT SEXP OmB_set_nt_movnb2_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_movnb2_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_movnb2_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_movnb2_par(arg_movnb2_par, sArgList));
}


EXPORT SEXP OmB_get_movnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_movnd1_par(sArgList));
}

EXPORT SEXP OmB_set_movnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_movnd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_movnd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_movnd1_par(arg_movnd1_par, sArgList));
}


EXPORT SEXP OmB_get_nt_movnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_movnd1_par(sArgList));
}

EXPORT SEXP OmB_set_nt_movnd1_par(SEXP args)
{
  SEXP rInstance;
  SEXP arg_movnd1_par;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_movnd1_par = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_movnd1_par(arg_movnd1_par, sArgList));
}


EXPORT SEXP OmB_get_MSY_Recdevs(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MSY_Recdevs(sArgList));
}

EXPORT SEXP OmB_set_MSY_Recdevs(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MSY_Recdevs;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MSY_Recdevs = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MSY_Recdevs(arg_MSY_Recdevs, sArgList));
}


EXPORT SEXP OmB_get_nt_MSY_Recdevs(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MSY_Recdevs(sArgList));
}

EXPORT SEXP OmB_set_nt_MSY_Recdevs(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MSY_Recdevs;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MSY_Recdevs = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MSY_Recdevs(arg_MSY_Recdevs, sArgList));
}


EXPORT SEXP OmB_get_MSY_RecSpatialDevs(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_MSY_RecSpatialDevs(sArgList));
}

EXPORT SEXP OmB_set_MSY_RecSpatialDevs(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MSY_RecSpatialDevs;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MSY_RecSpatialDevs = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_MSY_RecSpatialDevs(arg_MSY_RecSpatialDevs, sArgList));
}


EXPORT SEXP OmB_get_nt_MSY_RecSpatialDevs(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_MSY_RecSpatialDevs(sArgList));
}

EXPORT SEXP OmB_set_nt_MSY_RecSpatialDevs(SEXP args)
{
  SEXP rInstance;
  SEXP arg_MSY_RecSpatialDevs;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_MSY_RecSpatialDevs = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_MSY_RecSpatialDevs(arg_MSY_RecSpatialDevs, sArgList));
}


EXPORT SEXP OmB_R_MSYrefs(SEXP args)
{
  SEXP rInstance;
  SEXP par;
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
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
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
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYrefs(SEXP args)
{
  SEXP rInstance;
  SEXP par;
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
  SEXP MSY;
  SEXP BMSY;
  SEXP SSBMSY;
  SEXP SSBMSY_B0;
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
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
  args = CDR(args); MSY = CAR(args);
  args = CDR(args); BMSY = CAR(args);
  args = CDR(args); SSBMSY = CAR(args);
  args = CDR(args); SSBMSY_B0 = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYrefs(par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_MSYrefs_objective(SEXP args)
{
  SEXP rInstance;
  SEXP par;
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
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
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
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYrefs_objective(SEXP args)
{
  SEXP rInstance;
  SEXP par;
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
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
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
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYrefs_objective(par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_MSYREFS_OBJECTIVE_DPAR(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP pard1_par;
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
  SEXP nd1_par;
  SEXP NBefore;
  SEXP nbefored1_par;
  SEXP SSN;
  SEXP C;
  SEXP cd1_par;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP sim_idx;
  SEXP MSYrefs_objective;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); pard1_par = CAR(args);
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
  args = CDR(args); nd1_par = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); nbefored1_par = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); cd1_par = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  args = CDR(args); MSYrefs_objective = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_MSYREFS_OBJECTIVE_DPAR(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP pard1_par;
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
  SEXP nd1_par;
  SEXP NBefore;
  SEXP nbefored1_par;
  SEXP SSN;
  SEXP C;
  SEXP cd1_par;
  SEXP SSBA;
  SEXP ntargets;
  SEXP targpop;
  SEXP run_years;
  SEXP sim_idx;
  SEXP MSYrefs_objective;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); pard1_par = CAR(args);
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
  args = CDR(args); nd1_par = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); nbefored1_par = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); cd1_par = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); ntargets = CAR(args);
  args = CDR(args); targpop = CAR(args);
  args = CDR(args); run_years = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  args = CDR(args); MSYrefs_objective = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_MSYREFS_OBJECTIVE_DPAR(par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective);
  
  return (Result);
}

EXPORT SEXP OmB_get_nages(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nages());
}

EXPORT SEXP OmB_set_nages(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nages;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nages = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nages(arg_nages));
}


EXPORT SEXP OmB_get_nareas(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nareas());
}

EXPORT SEXP OmB_set_nareas(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nareas;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nareas = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nareas(arg_nareas));
}


EXPORT SEXP OmB_R_nextYear(SEXP args)
{
  SEXP rInstance;
  SEXP N;
  SEXP NBefore;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nextYear(N, NBefore);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_nextYear(SEXP args)
{
  SEXP rInstance;
  SEXP N;
  SEXP NBefore;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_nextYear(N, NBefore);
  
  return (Result);
}

EXPORT SEXP OmB_get_nfleets(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nfleets());
}

EXPORT SEXP OmB_set_nfleets(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nfleets;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nfleets = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nfleets(arg_nfleets));
}


EXPORT SEXP OmB_get_npop(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_npop());
}

EXPORT SEXP OmB_set_npop(SEXP args)
{
  SEXP rInstance;
  SEXP arg_npop;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_npop = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_npop(arg_npop));
}


EXPORT SEXP OmB_get_nsim(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nsim());
}

EXPORT SEXP OmB_set_nsim(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nsim;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nsim = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nsim(arg_nsim));
}


EXPORT SEXP OmB_get_nsubyears(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nsubyears());
}

EXPORT SEXP OmB_set_nsubyears(SEXP args)
{
  SEXP rInstance;
  SEXP arg_nsubyears;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_nsubyears = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nsubyears(arg_nsubyears));
}


EXPORT SEXP OmB_R_popdyn_projection_objective(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
  SEXP ECurrent;
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
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_popdyn_projection_objective(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
  SEXP ECurrent;
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
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_popdyn_projection_objective(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP parb2_par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
  SEXP ECurrent;
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
  SEXP nb2_par;
  SEXP NBefore;
  SEXP nbeforeb2_par;
  SEXP SSN;
  SEXP C;
  SEXP cb2_par;
  SEXP SSBA;
  SEXP sim_idx;
  SEXP popdyn_projection_objectiveb2_par;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); parb2_par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); nb2_par = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); nbeforeb2_par = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); cb2_par = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  args = CDR(args); popdyn_projection_objectiveb2_par = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_POPDYN_PROJECTION_OBJECTIVE_BPAR(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP parb2_par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
  SEXP ECurrent;
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
  SEXP nb2_par;
  SEXP NBefore;
  SEXP nbeforeb2_par;
  SEXP SSN;
  SEXP C;
  SEXP cb2_par;
  SEXP SSBA;
  SEXP sim_idx;
  SEXP popdyn_projection_objectiveb2_par;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); parb2_par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); nb2_par = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); nbeforeb2_par = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); cb2_par = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  args = CDR(args); popdyn_projection_objectiveb2_par = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POPDYN_PROJECTION_OBJECTIVE_BPAR(par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par);
  
  return (Result);
}

EXPORT SEXP OmB_get_Recsubyr(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_Recsubyr(sArgList));
}

EXPORT SEXP OmB_set_Recsubyr(SEXP args)
{
  SEXP rInstance;
  SEXP arg_Recsubyr;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_Recsubyr = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_Recsubyr(arg_Recsubyr, sArgList));
}


EXPORT SEXP OmB_get_nt_Recsubyr(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_Recsubyr(sArgList));
}

EXPORT SEXP OmB_set_nt_Recsubyr(SEXP args)
{
  SEXP rInstance;
  SEXP arg_Recsubyr;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_Recsubyr = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_Recsubyr(arg_Recsubyr, sArgList));
}


EXPORT SEXP OmB_R_runHistoric(SEXP args)
{
  SEXP rInstance;
  SEXP totF;
  SEXP qy;
  SEXP ECurrent;
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
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); totF = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_runHistoric(SEXP args)
{
  SEXP rInstance;
  SEXP totF;
  SEXP qy;
  SEXP ECurrent;
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
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); totF = CAR(args);
  args = CDR(args); qy = CAR(args);
  args = CDR(args); ECurrent = CAR(args);
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
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_runHistoric(totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA);
  
  return (Result);
}

EXPORT SEXP OmB_R_runProjection(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
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
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
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
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_R_nt_runProjection(SEXP args)
{
  SEXP rInstance;
  SEXP par;
  SEXP npar;
  SEXP nfixed;
  SEXP TAC;
  SEXP TAE;
  SEXP FbyPar;
  SEXP FbyFixed;
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
  SEXP Recdevs;
  SEXP RecSpatialDevs;
  SEXP SRrel;
  SEXP N;
  SEXP NBefore;
  SEXP SSN;
  SEXP C;
  SEXP SSBA;
  SEXP sim_idx;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); par = CAR(args);
  args = CDR(args); npar = CAR(args);
  args = CDR(args); nfixed = CAR(args);
  args = CDR(args); TAC = CAR(args);
  args = CDR(args); TAE = CAR(args);
  args = CDR(args); FbyPar = CAR(args);
  args = CDR(args); FbyFixed = CAR(args);
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
  args = CDR(args); Recdevs = CAR(args);
  args = CDR(args); RecSpatialDevs = CAR(args);
  args = CDR(args); SRrel = CAR(args);
  args = CDR(args); N = CAR(args);
  args = CDR(args); NBefore = CAR(args);
  args = CDR(args); SSN = CAR(args);
  args = CDR(args); C = CAR(args);
  args = CDR(args); SSBA = CAR(args);
  args = CDR(args); sim_idx = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_runProjection(par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx);
  
  return (Result);
}

EXPORT SEXP OmB_get_SpawnPerYr(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SpawnPerYr());
}

EXPORT SEXP OmB_set_SpawnPerYr(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SpawnPerYr;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SpawnPerYr = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SpawnPerYr(arg_SpawnPerYr));
}


EXPORT SEXP OmB_get_SSB0(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SSB0(sArgList));
}

EXPORT SEXP OmB_set_SSB0(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SSB0;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SSB0 = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SSB0(arg_SSB0, sArgList));
}


EXPORT SEXP OmB_get_nt_SSB0(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_SSB0(sArgList));
}

EXPORT SEXP OmB_set_nt_SSB0(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SSB0;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SSB0 = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_SSB0(arg_SSB0, sArgList));
}


EXPORT SEXP OmB_get_SSBpR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SSBpR(sArgList));
}

EXPORT SEXP OmB_set_SSBpR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SSBpR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SSBpR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SSBpR(arg_SSBpR, sArgList));
}


EXPORT SEXP OmB_get_nt_SSBpR(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_SSBpR(sArgList));
}

EXPORT SEXP OmB_set_nt_SSBpR(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SSBpR;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SSBpR = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_SSBpR(arg_SSBpR, sArgList));
}


EXPORT SEXP OmB_get_surv(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_surv(sArgList));
}

EXPORT SEXP OmB_set_surv(SEXP args)
{
  SEXP rInstance;
  SEXP arg_surv;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_surv = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_surv(arg_surv, sArgList));
}


EXPORT SEXP OmB_get_nt_surv(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_surv(sArgList));
}

EXPORT SEXP OmB_set_nt_surv(SEXP args)
{
  SEXP rInstance;
  SEXP arg_surv;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_surv = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_surv(arg_surv, sArgList));
}

