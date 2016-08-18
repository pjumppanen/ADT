
SEXP D_MinRosenbrock::_get_N() const
{
  return (R_Scalar(N));
}

SEXP D_MinRosenbrock::_set_N(SEXP arg_N)
{
  R_CheckArgument("arg_N", "INTSXP", INTSXP, arg_N, __FILE__, __LINE__);
  
  N = INTEGER(arg_N)[0];
  
  return (R_Empty());
}

SEXP D_MinRosenbrock::R_internal_rosenbrock(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, N);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = rosenbrock(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_MinRosenbrock::R_rosenbrock(SEXP X)
{
  return (R_internal_rosenbrock(X, true));
}

SEXP D_MinRosenbrock::R_nt_rosenbrock(SEXP X)
{
  return (R_internal_rosenbrock(X, false));
}

SEXP D_MinRosenbrock::R_internal_ROSENBROCK_BX(SEXP X, SEXP xb1_x, SEXP rosenbrockb1_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb1_x;
  double arg_rosenbrockb1_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("xb1_x", "REALSXP", REALSXP, xb1_x, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("rosenbrockb1_x", "REALSXP", REALSXP, rosenbrockb1_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb1_x), (char*)arg_xb1_x);
    
    arg_rosenbrockb1_x = REAL(rosenbrockb1_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x, (void*)REAL(xb1_x));
    
    arg_rosenbrockb1_x = REAL(rosenbrockb1_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  ROSENBROCK_BX(arg_X, arg_xb1_x, arg_rosenbrockb1_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb1_x, (char*)REAL(xb1_x));
    REAL(rosenbrockb1_x)[0] = arg_rosenbrockb1_x;
  }
  else
  {
    REAL(rosenbrockb1_x)[0] = arg_rosenbrockb1_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb1_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_MinRosenbrock::R_ROSENBROCK_BX(SEXP X, SEXP xb1_x, SEXP rosenbrockb1_x)
{
  return (R_internal_ROSENBROCK_BX(X, xb1_x, rosenbrockb1_x, true));
}

SEXP D_MinRosenbrock::R_nt_ROSENBROCK_BX(SEXP X, SEXP xb1_x, SEXP rosenbrockb1_x)
{
  return (R_internal_ROSENBROCK_BX(X, xb1_x, rosenbrockb1_x, false));
}

SEXP D_MinRosenbrock::R_internal_ROSENBROCK_BX_DX(SEXP X, SEXP xd2_x, SEXP xb1_x, SEXP xb1_xd2_x, SEXP rosenbrockb1_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xd2_x;
  ARRAY_1D arg_xb1_x;
  ARRAY_1D arg_xb1_xd2_x;
  double arg_rosenbrockb1_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("xd2_x", "REALSXP", REALSXP, xd2_x, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("xb1_x", "REALSXP", REALSXP, xb1_x, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("xb1_xd2_x", "REALSXP", REALSXP, xb1_xd2_x, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("rosenbrockb1_x", "REALSXP", REALSXP, rosenbrockb1_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xd2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xd2_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xd2_x), (char*)arg_xd2_x);
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb1_x), (char*)arg_xb1_x);
    
    arg_xb1_xd2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_xd2_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb1_xd2_x), (char*)arg_xb1_xd2_x);
    
    arg_rosenbrockb1_x = REAL(rosenbrockb1_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xd2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xd2_x, (void*)REAL(xd2_x));
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x, (void*)REAL(xb1_x));
    
    arg_xb1_xd2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_xd2_x, (void*)REAL(xb1_xd2_x));
    
    arg_rosenbrockb1_x = REAL(rosenbrockb1_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  ROSENBROCK_BX_DX(arg_X, arg_xd2_x, arg_xb1_x, arg_xb1_xd2_x, arg_rosenbrockb1_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb1_x, (char*)REAL(xb1_x));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb1_xd2_x, (char*)REAL(xb1_xd2_x));
    REAL(rosenbrockb1_x)[0] = arg_rosenbrockb1_x;
  }
  else
  {
    REAL(rosenbrockb1_x)[0] = arg_rosenbrockb1_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xd2_x);
  AdtArrayPlan::destroy(MemAllocator, arg_xb1_x);
  AdtArrayPlan::destroy(MemAllocator, arg_xb1_xd2_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP D_MinRosenbrock::R_ROSENBROCK_BX_DX(SEXP X, SEXP xd2_x, SEXP xb1_x, SEXP xb1_xd2_x, SEXP rosenbrockb1_x)
{
  return (R_internal_ROSENBROCK_BX_DX(X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x, true));
}

SEXP D_MinRosenbrock::R_nt_ROSENBROCK_BX_DX(SEXP X, SEXP xd2_x, SEXP xb1_x, SEXP xb1_xd2_x, SEXP rosenbrockb1_x)
{
  return (R_internal_ROSENBROCK_BX_DX(X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x, false));
}
