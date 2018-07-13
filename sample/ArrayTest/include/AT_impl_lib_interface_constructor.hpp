
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

EXPORT SEXP AT_destroy(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  AT_destroy_handler(rInstance);
  
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = 0;
  UNPROTECT(1);
  
  return(Result);
}

EXPORT SEXP AT_create(SEXP args)
{
  SEXP Result = {0};
  R_ArrayTest* pContext = 0;
  
  SEXP arg_ix;
  SEXP arg_iy;
  SEXP arg_A1_I;
  SEXP arg_A1_D;
  SEXP arg_A2_IA;
  SEXP arg_A2_IB;
  SEXP arg_A2_DA;
  SEXP arg_A2_LB;
  SEXP arg_A2_C;
  SEXP arg_A2_UC;
  SEXP arg_A2_B;
  SEXP arg_SingularBool;
  SEXP arg_SingularLongbool;
  
  args = CDR(args); arg_ix = CAR(args);
  args = CDR(args); arg_iy = CAR(args);
  args = CDR(args); arg_A1_I = CAR(args);
  args = CDR(args); arg_A1_D = CAR(args);
  args = CDR(args); arg_A2_IA = CAR(args);
  args = CDR(args); arg_A2_IB = CAR(args);
  args = CDR(args); arg_A2_DA = CAR(args);
  args = CDR(args); arg_A2_LB = CAR(args);
  args = CDR(args); arg_A2_C = CAR(args);
  args = CDR(args); arg_A2_UC = CAR(args);
  args = CDR(args); arg_A2_B = CAR(args);
  args = CDR(args); arg_SingularBool = CAR(args);
  args = CDR(args); arg_SingularLongbool = CAR(args);
  
  R_CheckArgument("arg_ix", "INTSXP", INTSXP, arg_ix, __FILE__, __LINE__);
  
  R_CheckArgument("arg_iy", "INTSXP", INTSXP, arg_iy, __FILE__, __LINE__);
  
  R_CheckArgument("arg_A1_I", "INTSXP", INTSXP, arg_A1_I, __FILE__, __LINE__, 1, 1, 1 + INTEGER(arg_ix)[0]);
  
  R_CheckArgument("arg_A1_D", "REALSXP", REALSXP, arg_A1_D, __FILE__, __LINE__, 1, 1, INTEGER(arg_ix)[0]);
  
  R_CheckArgument("arg_A2_IA", "INTSXP", INTSXP, arg_A2_IA, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_A2_IB", "INTSXP", INTSXP, arg_A2_IB, __FILE__, __LINE__, 2,  -1, INTEGER(arg_iy)[0], 1, 1 + INTEGER(arg_ix)[0]);
  
  R_CheckArgument("arg_A2_DA", "REALSXP", REALSXP, arg_A2_DA, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0], 1, n_sex);
  
  R_CheckArgument("arg_A2_LB", "LGLSXP", LGLSXP, arg_A2_LB, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_A2_C", "RAWSXP", RAWSXP, arg_A2_C, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_A2_UC", "RAWSXP", RAWSXP, arg_A2_UC, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_A2_B", "RAWSXP", RAWSXP, arg_A2_B, __FILE__, __LINE__, 2, 1, 1 + INTEGER(arg_ix)[0],  -1, INTEGER(arg_iy)[0]);
  
  R_CheckArgument("arg_SingularBool", "RAWSXP", RAWSXP, arg_SingularBool, __FILE__, __LINE__);
  
  R_CheckArgument("arg_SingularLongbool", "LGLSXP", LGLSXP, arg_SingularLongbool, __FILE__, __LINE__);
  
  pContext = new R_ArrayTest(
      INTEGER(arg_ix)[0], 
      INTEGER(arg_iy)[0], 
      INTEGER(arg_A1_I), 
      REAL(arg_A1_D), 
      INTEGER(arg_A2_IA), 
      INTEGER(arg_A2_IB), 
      REAL(arg_A2_DA), 
      LONGBOOL(arg_A2_LB), 
      RAWCHAR(arg_A2_C), 
      RAW(arg_A2_UC), 
      RAWBOOL(arg_A2_B), 
      RAWBOOL(arg_SingularBool)[0], 
      LONGBOOL(arg_SingularLongbool)[0]);
  
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
