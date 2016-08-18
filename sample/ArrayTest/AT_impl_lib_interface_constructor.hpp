
EXPORT void AT_destroy_handler(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  if (pContext != 0)
  {
    delete pContext;
  }
  
  R_ClearExternalPtr(rInstance);
}

EXPORT SEXP AT_destroy(SEXP rInstance)
{
  AT_destroy_handler(rInstance);
  
  return (rInstance);
}

EXPORT SEXP AT_create(
    SEXP arg_ix, 
    SEXP arg_iy, 
    SEXP arg_A1_I, 
    SEXP arg_A1_D, 
    SEXP arg_A2_IA, 
    SEXP arg_A2_IB)
{
  SEXP Result = {0};
  R_ArrayTest* pContext = 0;
  
  R_CheckArgument("arg_ix", "INTSXP", INTSXP, arg_ix, __FILE__, __LINE__);
  
  R_CheckArgument("arg_iy", "INTSXP", INTSXP, arg_iy, __FILE__, __LINE__);
  
  R_CheckArgument("arg_A1_I", "INTSXP", INTSXP, arg_A1_I, __FILE__, __LINE__, 1, 1, 1 + INTEGER(arg_ix)[0]);
  
  R_CheckArgument("arg_A1_D", "REALSXP", REALSXP, arg_A1_D, __FILE__, __LINE__, 1, 1, INTEGER(arg_ix)[0]);
  
  R_CheckArgument("arg_A2_IA", "INTSXP", INTSXP, arg_A2_IA, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_A2_IB", "INTSXP", INTSXP, arg_A2_IB, __FILE__, __LINE__, 2,  -1, INTEGER(arg_iy)[0], 1, 1 + INTEGER(arg_ix)[0]);
  
  pContext = new R_ArrayTest(
      INTEGER(arg_ix)[0], 
      INTEGER(arg_iy)[0], 
      INTEGER(arg_A1_I), 
      REAL(arg_A1_D), 
      INTEGER(arg_A2_IA), 
      INTEGER(arg_A2_IB));
  
  if (pContext != 0)
  {
    MAKE_R_EXTERNAL_PTR(Result, pContext, AT_destroy_handler, R_ArrayTest);
  }
  else
  {
    Rf_error("ERROR: AT_create() failed");
    
    SEXP Result = allocVector(INTSXP, 1);
    
    PROTECT(Result);
    INTEGER(Result)[0] = 0;
    UNPROTECT(1);
  }
  
  return Result;
}
