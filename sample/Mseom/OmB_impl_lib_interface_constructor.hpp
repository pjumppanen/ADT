
EXPORT void OmB_destroy_handler(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelBase* pContext = (D_OperatingModelBase*)R_ExternalPtrAddr(rInstance);
  
  if (pContext != 0)
  {
    delete pContext;
  }
  
  R_ClearExternalPtr(rInstance);
}

EXPORT SEXP OmB_destroy(SEXP rInstance)
{
  OmB_destroy_handler(rInstance);
  
  return (rInstance);
}

EXPORT SEXP OmB_create(
    SEXP arg_nsim, 
    SEXP arg_npop, 
    SEXP arg_nages, 
    SEXP arg_nsubyears, 
    SEXP arg_nareas, 
    SEXP arg_nfleets, 
    SEXP arg_Recsubyr)
{
  SEXP Result = {0};
  D_OperatingModelBase* pContext = 0;
  
  R_CheckArgument("arg_nsim", "INTSXP", INTSXP, arg_nsim, __FILE__, __LINE__);
  
  R_CheckArgument("arg_npop", "INTSXP", INTSXP, arg_npop, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nages", "INTSXP", INTSXP, arg_nages, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nsubyears", "INTSXP", INTSXP, arg_nsubyears, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nareas", "INTSXP", INTSXP, arg_nareas, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nfleets", "INTSXP", INTSXP, arg_nfleets, __FILE__, __LINE__);
  
  R_CheckArgument("arg_Recsubyr", "INTSXP", INTSXP, arg_Recsubyr, __FILE__, __LINE__, 1, 1, INTEGER(arg_nsubyears)[0]);
  
  pContext = new D_OperatingModelBase(
      INTEGER(arg_nsim)[0], 
      INTEGER(arg_npop)[0], 
      INTEGER(arg_nages)[0], 
      INTEGER(arg_nsubyears)[0], 
      INTEGER(arg_nareas)[0], 
      INTEGER(arg_nfleets)[0], 
      INTEGER(arg_Recsubyr));
  
  if (pContext != 0)
  {
    MAKE_R_EXTERNAL_PTR(Result, pContext, OmB_destroy_handler, D_OperatingModelBase);
  }
  else
  {
    Rf_error("ERROR: OmB_create() failed");
    
    SEXP Result = allocVector(INTSXP, 1);
    
    PROTECT(Result);
    INTEGER(Result)[0] = 0;
    UNPROTECT(1);
  }
  
  return Result;
}
