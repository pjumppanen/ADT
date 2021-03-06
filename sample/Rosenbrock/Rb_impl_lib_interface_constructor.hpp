
EXPORT void Rb_destroy_handler(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  if (pContext != 0)
  {
    delete pContext;
  }
  
  R_ClearExternalPtr(rInstance);
}

EXPORT SEXP Rb_destroy(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  Rb_destroy_handler(rInstance);
  
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = 0;
  UNPROTECT(1);
  
  return(Result);
}

EXPORT SEXP Rb_create(SEXP args)
{
  SEXP Result = {0};
  D_MinRosenbrock* pContext = 0;
  
  SEXP arg_N;
  
  args = CDR(args); arg_N = CAR(args);
  
  R_CheckArgument("arg_N", "INTSXP", INTSXP, arg_N, __FILE__, __LINE__);
  
  pContext = new D_MinRosenbrock(
      INTEGER(arg_N)[0]);
  
  if (pContext != 0)
  {
    MAKE_R_EXTERNAL_PTR(Result, pContext, Rb_destroy_handler, D_MinRosenbrock);
  }
  else
  {
    Rf_error("ERROR: Rb_create() failed");
    
    SEXP Result = allocVector(INTSXP, 1);
    
    PROTECT(Result);
    INTEGER(Result)[0] = 0;
    UNPROTECT(1);
  }
  
  return Result;
}
