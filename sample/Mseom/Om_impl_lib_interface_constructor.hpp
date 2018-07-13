
EXPORT void Om_destroy_handler(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_OperatingModelBase);
  
  D_OperatingModelMin* pContext = (D_OperatingModelMin*)R_ExternalPtrAddr(rInstance);
  
  if (pContext != 0)
  {
    delete pContext;
  }
  
  R_ClearExternalPtr(rInstance);
}

EXPORT SEXP Om_destroy(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  Om_destroy_handler(rInstance);
  
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = 0;
  UNPROTECT(1);
  
  return(Result);
}

EXPORT SEXP Om_create(SEXP args)
{
  SEXP Result = {0};
  D_OperatingModelMin* pContext = 0;
  
  SEXP arg_nsim;
  SEXP arg_npop;
  SEXP arg_nages;
  SEXP arg_nsubyears;
  SEXP arg_nareas;
  SEXP arg_nfleets;
  SEXP arg_Recsubyr;
  
  args = CDR(args); arg_nsim = CAR(args);
  args = CDR(args); arg_npop = CAR(args);
  args = CDR(args); arg_nages = CAR(args);
  args = CDR(args); arg_nsubyears = CAR(args);
  args = CDR(args); arg_nareas = CAR(args);
  args = CDR(args); arg_nfleets = CAR(args);
  args = CDR(args); arg_Recsubyr = CAR(args);
  
  R_CheckArgument("arg_nsim", "INTSXP", INTSXP, arg_nsim, __FILE__, __LINE__);
  
  R_CheckArgument("arg_npop", "INTSXP", INTSXP, arg_npop, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nages", "INTSXP", INTSXP, arg_nages, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nsubyears", "INTSXP", INTSXP, arg_nsubyears, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nareas", "INTSXP", INTSXP, arg_nareas, __FILE__, __LINE__);
  
  R_CheckArgument("arg_nfleets", "INTSXP", INTSXP, arg_nfleets, __FILE__, __LINE__);
  
  R_CheckArgument("arg_Recsubyr", "INTSXP", INTSXP, arg_Recsubyr, __FILE__, __LINE__, 1, 1, INTEGER(arg_nsubyears)[0]);
  
  pContext = new D_OperatingModelMin(
      INTEGER(arg_nsim)[0], 
      INTEGER(arg_npop)[0], 
      INTEGER(arg_nages)[0], 
      INTEGER(arg_nsubyears)[0], 
      INTEGER(arg_nareas)[0], 
      INTEGER(arg_nfleets)[0], 
      INTEGER(arg_Recsubyr));
  
  if (pContext != 0)
  {
    MAKE_R_EXTERNAL_PTR(Result, pContext, Om_destroy_handler, D_OperatingModelBase);
  }
  else
  {
    Rf_error("ERROR: Om_create() failed");
    
    SEXP Result = allocVector(INTSXP, 1);
    
    PROTECT(Result);
    INTEGER(Result)[0] = 0;
    UNPROTECT(1);
  }
  
  return Result;
}
