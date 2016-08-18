
EXPORT void RRb_destroy_handler(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  if (pContext != 0)
  {
    delete pContext;
  }
  
  R_ClearExternalPtr(rInstance);
}

EXPORT SEXP RRb_destroy(SEXP rInstance)
{
  RRb_destroy_handler(rInstance);
  
  return (rInstance);
}

EXPORT SEXP RRb_create(
    SEXP arg_N)
{
  SEXP Result = {0};
  DR_MinRosenbrock* pContext = 0;
  
  R_CheckArgument("arg_N", "INTSXP", INTSXP, arg_N, __FILE__, __LINE__);
  
  pContext = new DR_MinRosenbrock(
      INTEGER(arg_N)[0]);
  
  if (pContext != 0)
  {
    MAKE_R_EXTERNAL_PTR(Result, pContext, RRb_destroy_handler, D_MinRosenbrock);
  }
  else
  {
    Rf_error("ERROR: RRb_create() failed");
    
    SEXP Result = allocVector(INTSXP, 1);
    
    PROTECT(Result);
    INTEGER(Result)[0] = 0;
    UNPROTECT(1);
  }
  
  return Result;
}
