
SEXP DR_MinRosenbrock::R_internal_hessian(SEXP pX, SEXP pHessian, bool bTranslate)
{
  ARRAY_1D arg_pX;
  ARRAY_2D arg_pHessian;
  
  R_CheckArgument("pX", "REALSXP", REALSXP, pX, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("pHessian", "REALSXP", REALSXP, pHessian, __FILE__, __LINE__, 2, 1, N, 1, N);
  
  if (bTranslate)
  {
    arg_pX = 0;
    
    Plan_1.create(MemAllocator, arg_pX);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(pX), (char*)arg_pX);
    
    arg_pHessian = 0;
    
    Plan_2.create(MemAllocator, arg_pHessian);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(pHessian), (char*)arg_pHessian);
    
  }
  else
  {
    arg_pX = 0;
    
    Plan_1.create(MemAllocator, arg_pX, (void*)REAL(pX));
    
    arg_pHessian = 0;
    
    Plan_2.create(MemAllocator, arg_pHessian, (void*)REAL(pHessian));
    
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  hessian(arg_pX, arg_pHessian);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_pX, (char*)REAL(pX));
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_pHessian, (char*)REAL(pHessian));
  }
  else
  {
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_pX);
  AdtArrayPlan::destroy(MemAllocator, arg_pHessian);
  UNPROTECT(1);
  
  return (Result);
}

SEXP DR_MinRosenbrock::R_hessian(SEXP pX, SEXP pHessian)
{
  return (R_internal_hessian(pX, pHessian, true));
}

SEXP DR_MinRosenbrock::R_nt_hessian(SEXP pX, SEXP pHessian)
{
  return (R_internal_hessian(pX, pHessian, false));
}

SEXP DR_MinRosenbrock::_get_lxb1_x(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)lxb1_x, "lxb1_x", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_set_lxb1_x(SEXP arg_lxb1_x, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)lxb1_x, "lxb1_x", arg_lxb1_x, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_get_nt_lxb1_x(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)lxb1_x, "lxb1_x", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_set_nt_lxb1_x(SEXP arg_lxb1_x, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)lxb1_x, "lxb1_x", arg_lxb1_x, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_get_lxd2_x(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)lxd2_x, "lxd2_x", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_set_lxd2_x(SEXP arg_lxd2_x, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)lxd2_x, "lxd2_x", arg_lxd2_x, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_get_nt_lxd2_x(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)lxd2_x, "lxd2_x", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::_set_nt_lxd2_x(SEXP arg_lxd2_x, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)lxd2_x, "lxd2_x", arg_lxd2_x, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP DR_MinRosenbrock::R_internal_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status, bool bTranslate)
{
  ARRAY_1D arg_pS;
  ARRAY_1D arg_pR;
  int arg_maxit;
  int arg_fncount;
  int arg_grcount;
  int arg_status;
  
  R_CheckArgument("pS", "REALSXP", REALSXP, pS, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("pR", "REALSXP", REALSXP, pR, __FILE__, __LINE__, 1, 1, N);
  
  R_CheckArgument("maxit", "INTSXP", INTSXP, maxit, __FILE__, __LINE__);
  
  R_CheckArgument("fncount", "INTSXP", INTSXP, fncount, __FILE__, __LINE__);
  
  R_CheckArgument("grcount", "INTSXP", INTSXP, grcount, __FILE__, __LINE__);
  
  R_CheckArgument("status", "INTSXP", INTSXP, status, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_pS = 0;
    
    Plan_1.create(MemAllocator, arg_pS);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(pS), (char*)arg_pS);
    
    arg_pR = 0;
    
    Plan_1.create(MemAllocator, arg_pR);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(pR), (char*)arg_pR);
    
    arg_maxit = INTEGER(maxit)[0];
    arg_fncount = INTEGER(fncount)[0];
    arg_grcount = INTEGER(grcount)[0];
    arg_status = INTEGER(status)[0];
  }
  else
  {
    arg_pS = 0;
    
    Plan_1.create(MemAllocator, arg_pS, (void*)REAL(pS));
    
    arg_pR = 0;
    
    Plan_1.create(MemAllocator, arg_pR, (void*)REAL(pR));
    
    arg_maxit = INTEGER(maxit)[0];
    arg_fncount = INTEGER(fncount)[0];
    arg_grcount = INTEGER(grcount)[0];
    arg_status = INTEGER(status)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  minimise(arg_pS, arg_pR, arg_maxit, arg_fncount, arg_grcount, arg_status);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_pR, (char*)REAL(pR));
    INTEGER(fncount)[0] = arg_fncount;
    INTEGER(grcount)[0] = arg_grcount;
    INTEGER(status)[0] = arg_status;
  }
  else
  {
    INTEGER(fncount)[0] = arg_fncount;
    INTEGER(grcount)[0] = arg_grcount;
    INTEGER(status)[0] = arg_status;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_pS);
  AdtArrayPlan::destroy(MemAllocator, arg_pR);
  UNPROTECT(1);
  
  return (Result);
}

SEXP DR_MinRosenbrock::R_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status)
{
  return (R_internal_minimise(pS, pR, maxit, fncount, grcount, status, true));
}

SEXP DR_MinRosenbrock::R_nt_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status)
{
  return (R_internal_minimise(pS, pR, maxit, fncount, grcount, status, false));
}
