
SEXP R_ArrayTest::_get_A1_D(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)A1_D, "A1_D", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_A1_D(SEXP arg_A1_D, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)A1_D, "A1_D", arg_A1_D, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_nt_A1_D(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)A1_D, "A1_D", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_nt_A1_D(SEXP arg_A1_D, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)A1_D, "A1_D", arg_A1_D, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_A1_I(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)A1_I, "A1_I", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_A1_I(SEXP arg_A1_I, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)A1_I, "A1_I", arg_A1_I, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_nt_A1_I(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)A1_I, "A1_I", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_nt_A1_I(SEXP arg_A1_I, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)A1_I, "A1_I", arg_A1_I, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_A2_IA(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)A2_IA, "A2_IA", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_A2_IA(SEXP arg_A2_IA, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)A2_IA, "A2_IA", arg_A2_IA, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_nt_A2_IA(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)A2_IA, "A2_IA", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_nt_A2_IA(SEXP arg_A2_IA, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)A2_IA, "A2_IA", arg_A2_IA, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_A2_IB(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, false, (char*)A2_IB, "A2_IB", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_A2_IB(SEXP arg_A2_IB, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, false, (char*)A2_IB, "A2_IB", arg_A2_IB, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_get_nt_A2_IB(SEXP sArgList) const
{
  SEXP Result = R_ImplGetter(MemAllocator, true, (char*)A2_IB, "A2_IB", sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::_set_nt_A2_IB(SEXP arg_A2_IB, SEXP sArgList)
{
  SEXP Result = R_ImplSetter(MemAllocator, true, (char*)A2_IB, "A2_IB", arg_A2_IB, sArgList, __FILE__, __LINE__);
  
  return (Result);
}

SEXP R_ArrayTest::R_internal_boundsCheckTest(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
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
  REAL(Result)[0] = boundsCheckTest(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_boundsCheckTest(SEXP X)
{
  return (R_internal_boundsCheckTest(X, true));
}

SEXP R_ArrayTest::R_nt_boundsCheckTest(SEXP X)
{
  return (R_internal_boundsCheckTest(X, false));
}

SEXP R_ArrayTest::R_internal_GLOBAL_SUM_BX(SEXP X, SEXP xb1_x, SEXP nBase, SEXP nCount, SEXP global_sumb1_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb1_x;
  int arg_nBase;
  int arg_nCount;
  double arg_global_sumb1_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("xb1_x", "REALSXP", REALSXP, xb1_x, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("nBase", "INTSXP", INTSXP, nBase, __FILE__, __LINE__);
  
  R_CheckArgument("nCount", "INTSXP", INTSXP, nCount, __FILE__, __LINE__);
  
  R_CheckArgument("global_sumb1_x", "REALSXP", REALSXP, global_sumb1_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb1_x), (char*)arg_xb1_x);
    
    arg_nBase = INTEGER(nBase)[0];
    arg_nCount = INTEGER(nCount)[0];
    arg_global_sumb1_x = REAL(global_sumb1_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x, (void*)REAL(xb1_x));
    
    arg_nBase = INTEGER(nBase)[0];
    arg_nCount = INTEGER(nCount)[0];
    arg_global_sumb1_x = REAL(global_sumb1_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  GLOBAL_SUM_BX(arg_X, arg_xb1_x, arg_nBase, arg_nCount, arg_global_sumb1_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb1_x, (char*)REAL(xb1_x));
    REAL(global_sumb1_x)[0] = arg_global_sumb1_x;
  }
  else
  {
    REAL(global_sumb1_x)[0] = arg_global_sumb1_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb1_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_GLOBAL_SUM_BX(SEXP X, SEXP xb1_x, SEXP nBase, SEXP nCount, SEXP global_sumb1_x)
{
  return (R_internal_GLOBAL_SUM_BX(X, xb1_x, nBase, nCount, global_sumb1_x, true));
}

SEXP R_ArrayTest::R_nt_GLOBAL_SUM_BX(SEXP X, SEXP xb1_x, SEXP nBase, SEXP nCount, SEXP global_sumb1_x)
{
  return (R_internal_GLOBAL_SUM_BX(X, xb1_x, nBase, nCount, global_sumb1_x, false));
}

SEXP R_ArrayTest::R_internal_IFTEST_BX(SEXP X, SEXP xb5_x, SEXP iftestb5_x, bool bTranslate)
{
  double arg_X;
  double arg_xb5_x;
  double arg_iftestb5_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__);
  
  R_CheckArgument("xb5_x", "REALSXP", REALSXP, xb5_x, __FILE__, __LINE__);
  
  R_CheckArgument("iftestb5_x", "REALSXP", REALSXP, iftestb5_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = REAL(X)[0];
    arg_xb5_x = REAL(xb5_x)[0];
    arg_iftestb5_x = REAL(iftestb5_x)[0];
  }
  else
  {
    arg_X = REAL(X)[0];
    arg_xb5_x = REAL(xb5_x)[0];
    arg_iftestb5_x = REAL(iftestb5_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  IFTEST_BX(arg_X, arg_xb5_x, arg_iftestb5_x);
  
  if (bTranslate)
  {
    REAL(xb5_x)[0] = arg_xb5_x;
    REAL(iftestb5_x)[0] = arg_iftestb5_x;
  }
  else
  {
    REAL(xb5_x)[0] = arg_xb5_x;
    REAL(iftestb5_x)[0] = arg_iftestb5_x;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_IFTEST_BX(SEXP X, SEXP xb5_x, SEXP iftestb5_x)
{
  return (R_internal_IFTEST_BX(X, xb5_x, iftestb5_x, true));
}

SEXP R_ArrayTest::R_nt_IFTEST_BX(SEXP X, SEXP xb5_x, SEXP iftestb5_x)
{
  return (R_internal_IFTEST_BX(X, xb5_x, iftestb5_x, false));
}

SEXP R_ArrayTest::_get_ix() const
{
  return (R_Scalar(ix));
}

SEXP R_ArrayTest::_set_ix(SEXP arg_ix)
{
  R_CheckArgument("arg_ix", "INTSXP", INTSXP, arg_ix, __FILE__, __LINE__);
  
  ix = INTEGER(arg_ix)[0];
  
  return (R_Empty());
}

SEXP R_ArrayTest::_get_iy() const
{
  return (R_Scalar(iy));
}

SEXP R_ArrayTest::_set_iy(SEXP arg_iy)
{
  R_CheckArgument("arg_iy", "INTSXP", INTSXP, arg_iy, __FILE__, __LINE__);
  
  iy = INTEGER(arg_iy)[0];
  
  return (R_Empty());
}

SEXP R_ArrayTest::R_internal_POLYB_BX(SEXP X, SEXP xb3_x, SEXP polybb3_x, bool bTranslate)
{
  double arg_X;
  double arg_xb3_x;
  double arg_polybb3_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__);
  
  R_CheckArgument("xb3_x", "REALSXP", REALSXP, xb3_x, __FILE__, __LINE__);
  
  R_CheckArgument("polybb3_x", "REALSXP", REALSXP, polybb3_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = REAL(X)[0];
    arg_xb3_x = REAL(xb3_x)[0];
    arg_polybb3_x = REAL(polybb3_x)[0];
  }
  else
  {
    arg_X = REAL(X)[0];
    arg_xb3_x = REAL(xb3_x)[0];
    arg_polybb3_x = REAL(polybb3_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POLYB_BX(arg_X, arg_xb3_x, arg_polybb3_x);
  
  if (bTranslate)
  {
    REAL(xb3_x)[0] = arg_xb3_x;
    REAL(polybb3_x)[0] = arg_polybb3_x;
  }
  else
  {
    REAL(xb3_x)[0] = arg_xb3_x;
    REAL(polybb3_x)[0] = arg_polybb3_x;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_POLYB_BX(SEXP X, SEXP xb3_x, SEXP polybb3_x)
{
  return (R_internal_POLYB_BX(X, xb3_x, polybb3_x, true));
}

SEXP R_ArrayTest::R_nt_POLYB_BX(SEXP X, SEXP xb3_x, SEXP polybb3_x)
{
  return (R_internal_POLYB_BX(X, xb3_x, polybb3_x, false));
}

SEXP R_ArrayTest::R_internal_POLYB_BX0(SEXP X, SEXP xb5_x, SEXP polybb5_x, bool bTranslate)
{
  double arg_X;
  double arg_xb5_x;
  double arg_polybb5_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__);
  
  R_CheckArgument("xb5_x", "REALSXP", REALSXP, xb5_x, __FILE__, __LINE__);
  
  R_CheckArgument("polybb5_x", "REALSXP", REALSXP, polybb5_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = REAL(X)[0];
    arg_xb5_x = REAL(xb5_x)[0];
    arg_polybb5_x = REAL(polybb5_x)[0];
  }
  else
  {
    arg_X = REAL(X)[0];
    arg_xb5_x = REAL(xb5_x)[0];
    arg_polybb5_x = REAL(polybb5_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POLYB_BX0(arg_X, arg_xb5_x, arg_polybb5_x);
  
  if (bTranslate)
  {
    REAL(xb5_x)[0] = arg_xb5_x;
    REAL(polybb5_x)[0] = arg_polybb5_x;
  }
  else
  {
    REAL(xb5_x)[0] = arg_xb5_x;
    REAL(polybb5_x)[0] = arg_polybb5_x;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_POLYB_BX0(SEXP X, SEXP xb5_x, SEXP polybb5_x)
{
  return (R_internal_POLYB_BX0(X, xb5_x, polybb5_x, true));
}

SEXP R_ArrayTest::R_nt_POLYB_BX0(SEXP X, SEXP xb5_x, SEXP polybb5_x)
{
  return (R_internal_POLYB_BX0(X, xb5_x, polybb5_x, false));
}

SEXP R_ArrayTest::R_internal_polySumA(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
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
  REAL(Result)[0] = polySumA(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_polySumA(SEXP X)
{
  return (R_internal_polySumA(X, true));
}

SEXP R_ArrayTest::R_nt_polySumA(SEXP X)
{
  return (R_internal_polySumA(X, false));
}

SEXP R_ArrayTest::R_internal_POLYSUMA_BX(SEXP X, SEXP xb2_x, SEXP polysumab2_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb2_x;
  double arg_polysumab2_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("xb2_x", "REALSXP", REALSXP, xb2_x, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("polysumab2_x", "REALSXP", REALSXP, polysumab2_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb2_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb2_x), (char*)arg_xb2_x);
    
    arg_polysumab2_x = REAL(polysumab2_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb2_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb2_x, (void*)REAL(xb2_x));
    
    arg_polysumab2_x = REAL(polysumab2_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POLYSUMA_BX(arg_X, arg_xb2_x, arg_polysumab2_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb2_x, (char*)REAL(xb2_x));
    REAL(polysumab2_x)[0] = arg_polysumab2_x;
  }
  else
  {
    REAL(polysumab2_x)[0] = arg_polysumab2_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb2_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_POLYSUMA_BX(SEXP X, SEXP xb2_x, SEXP polysumab2_x)
{
  return (R_internal_POLYSUMA_BX(X, xb2_x, polysumab2_x, true));
}

SEXP R_ArrayTest::R_nt_POLYSUMA_BX(SEXP X, SEXP xb2_x, SEXP polysumab2_x)
{
  return (R_internal_POLYSUMA_BX(X, xb2_x, polysumab2_x, false));
}

SEXP R_ArrayTest::R_internal_polySumB(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
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
  REAL(Result)[0] = polySumB(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_polySumB(SEXP X)
{
  return (R_internal_polySumB(X, true));
}

SEXP R_ArrayTest::R_nt_polySumB(SEXP X)
{
  return (R_internal_polySumB(X, false));
}

SEXP R_ArrayTest::R_internal_POLYSUMB_BX(SEXP X, SEXP xb3_x, SEXP polysumbb3_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb3_x;
  double arg_polysumbb3_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("xb3_x", "REALSXP", REALSXP, xb3_x, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("polysumbb3_x", "REALSXP", REALSXP, polysumbb3_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb3_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb3_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb3_x), (char*)arg_xb3_x);
    
    arg_polysumbb3_x = REAL(polysumbb3_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb3_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb3_x, (void*)REAL(xb3_x));
    
    arg_polysumbb3_x = REAL(polysumbb3_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POLYSUMB_BX(arg_X, arg_xb3_x, arg_polysumbb3_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb3_x, (char*)REAL(xb3_x));
    REAL(polysumbb3_x)[0] = arg_polysumbb3_x;
  }
  else
  {
    REAL(polysumbb3_x)[0] = arg_polysumbb3_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb3_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_POLYSUMB_BX(SEXP X, SEXP xb3_x, SEXP polysumbb3_x)
{
  return (R_internal_POLYSUMB_BX(X, xb3_x, polysumbb3_x, true));
}

SEXP R_ArrayTest::R_nt_POLYSUMB_BX(SEXP X, SEXP xb3_x, SEXP polysumbb3_x)
{
  return (R_internal_POLYSUMB_BX(X, xb3_x, polysumbb3_x, false));
}

SEXP R_ArrayTest::R_internal_polySumC(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
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
  REAL(Result)[0] = polySumC(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_polySumC(SEXP X)
{
  return (R_internal_polySumC(X, true));
}

SEXP R_ArrayTest::R_nt_polySumC(SEXP X)
{
  return (R_internal_polySumC(X, false));
}

SEXP R_ArrayTest::R_internal_POLYSUMC_BX(SEXP X, SEXP xb4_x, SEXP polysumcb4_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb4_x;
  double arg_polysumcb4_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("xb4_x", "REALSXP", REALSXP, xb4_x, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("polysumcb4_x", "REALSXP", REALSXP, polysumcb4_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb4_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb4_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb4_x), (char*)arg_xb4_x);
    
    arg_polysumcb4_x = REAL(polysumcb4_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb4_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb4_x, (void*)REAL(xb4_x));
    
    arg_polysumcb4_x = REAL(polysumcb4_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  POLYSUMC_BX(arg_X, arg_xb4_x, arg_polysumcb4_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb4_x, (char*)REAL(xb4_x));
    REAL(polysumcb4_x)[0] = arg_polysumcb4_x;
  }
  else
  {
    REAL(polysumcb4_x)[0] = arg_polysumcb4_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb4_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_POLYSUMC_BX(SEXP X, SEXP xb4_x, SEXP polysumcb4_x)
{
  return (R_internal_POLYSUMC_BX(X, xb4_x, polysumcb4_x, true));
}

SEXP R_ArrayTest::R_nt_POLYSUMC_BX(SEXP X, SEXP xb4_x, SEXP polysumcb4_x)
{
  return (R_internal_POLYSUMC_BX(X, xb4_x, polysumcb4_x, false));
}

SEXP R_ArrayTest::R_internal_sum(SEXP X, bool bTranslate)
{
  ARRAY_1D arg_X;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
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
  REAL(Result)[0] = sum(arg_X);
  
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_sum(SEXP X)
{
  return (R_internal_sum(X, true));
}

SEXP R_ArrayTest::R_nt_sum(SEXP X)
{
  return (R_internal_sum(X, false));
}

SEXP R_ArrayTest::R_internal_SUM_BX(SEXP X, SEXP xb1_x, SEXP sumb1_x, bool bTranslate)
{
  ARRAY_1D arg_X;
  ARRAY_1D arg_xb1_x;
  double arg_sumb1_x;
  
  R_CheckArgument("X", "REALSXP", REALSXP, X, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("xb1_x", "REALSXP", REALSXP, xb1_x, __FILE__, __LINE__, 1, 1, ix);
  
  R_CheckArgument("sumb1_x", "REALSXP", REALSXP, sumb1_x, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(X), (char*)arg_X);
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)REAL(xb1_x), (char*)arg_xb1_x);
    
    arg_sumb1_x = REAL(sumb1_x)[0];
  }
  else
  {
    arg_X = 0;
    
    Plan_1.create(MemAllocator, arg_X, (void*)REAL(X));
    
    arg_xb1_x = 0;
    
    Plan_1.create(MemAllocator, arg_xb1_x, (void*)REAL(xb1_x));
    
    arg_sumb1_x = REAL(sumb1_x)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  SUM_BX(arg_X, arg_xb1_x, arg_sumb1_x);
  
  if (bTranslate)
  {
    AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_xb1_x, (char*)REAL(xb1_x));
    REAL(sumb1_x)[0] = arg_sumb1_x;
  }
  else
  {
    REAL(sumb1_x)[0] = arg_sumb1_x;
  }
  
  AdtArrayPlan::destroy(MemAllocator, arg_X);
  AdtArrayPlan::destroy(MemAllocator, arg_xb1_x);
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_SUM_BX(SEXP X, SEXP xb1_x, SEXP sumb1_x)
{
  return (R_internal_SUM_BX(X, xb1_x, sumb1_x, true));
}

SEXP R_ArrayTest::R_nt_SUM_BX(SEXP X, SEXP xb1_x, SEXP sumb1_x)
{
  return (R_internal_SUM_BX(X, xb1_x, sumb1_x, false));
}

SEXP R_ArrayTest::R_internal_sumA1_D(bool bTranslate)
{
  if (bTranslate)
  {
  }
  else
  {
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = sumA1_D();
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_sumA1_D()
{
  return (R_internal_sumA1_D(true));
}

SEXP R_ArrayTest::R_nt_sumA1_D()
{
  return (R_internal_sumA1_D(false));
}

SEXP R_ArrayTest::R_internal_test_one_if(SEXP v, bool bTranslate)
{
  double arg_v;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = test_one_if(arg_v);
  
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_test_one_if(SEXP v)
{
  return (R_internal_test_one_if(v, true));
}

SEXP R_ArrayTest::R_nt_test_one_if(SEXP v)
{
  return (R_internal_test_one_if(v, false));
}

SEXP R_ArrayTest::R_internal_TEST_ONE_IF_BV(SEXP v, SEXP vb7_v, SEXP test_one_ifb7_v, bool bTranslate)
{
  double arg_v;
  double arg_vb7_v;
  double arg_test_one_ifb7_v;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  R_CheckArgument("vb7_v", "REALSXP", REALSXP, vb7_v, __FILE__, __LINE__);
  
  R_CheckArgument("test_one_ifb7_v", "REALSXP", REALSXP, test_one_ifb7_v, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
    arg_vb7_v = REAL(vb7_v)[0];
    arg_test_one_ifb7_v = REAL(test_one_ifb7_v)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
    arg_vb7_v = REAL(vb7_v)[0];
    arg_test_one_ifb7_v = REAL(test_one_ifb7_v)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  TEST_ONE_IF_BV(arg_v, arg_vb7_v, arg_test_one_ifb7_v);
  
  if (bTranslate)
  {
    REAL(vb7_v)[0] = arg_vb7_v;
    REAL(test_one_ifb7_v)[0] = arg_test_one_ifb7_v;
  }
  else
  {
    REAL(vb7_v)[0] = arg_vb7_v;
    REAL(test_one_ifb7_v)[0] = arg_test_one_ifb7_v;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_TEST_ONE_IF_BV(SEXP v, SEXP vb7_v, SEXP test_one_ifb7_v)
{
  return (R_internal_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v, true));
}

SEXP R_ArrayTest::R_nt_TEST_ONE_IF_BV(SEXP v, SEXP vb7_v, SEXP test_one_ifb7_v)
{
  return (R_internal_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v, false));
}

SEXP R_ArrayTest::R_internal_TEST_ONE_IF_DV(SEXP v, SEXP vd6_v, SEXP test_one_if, bool bTranslate)
{
  double arg_v;
  double arg_vd6_v;
  double arg_test_one_if;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  R_CheckArgument("vd6_v", "REALSXP", REALSXP, vd6_v, __FILE__, __LINE__);
  
  R_CheckArgument("test_one_if", "REALSXP", REALSXP, test_one_if, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
    arg_vd6_v = REAL(vd6_v)[0];
    arg_test_one_if = REAL(test_one_if)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
    arg_vd6_v = REAL(vd6_v)[0];
    arg_test_one_if = REAL(test_one_if)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = TEST_ONE_IF_DV(arg_v, arg_vd6_v, arg_test_one_if);
  
  if (bTranslate)
  {
    REAL(test_one_if)[0] = arg_test_one_if;
  }
  else
  {
    REAL(test_one_if)[0] = arg_test_one_if;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_TEST_ONE_IF_DV(SEXP v, SEXP vd6_v, SEXP test_one_if)
{
  return (R_internal_TEST_ONE_IF_DV(v, vd6_v, test_one_if, true));
}

SEXP R_ArrayTest::R_nt_TEST_ONE_IF_DV(SEXP v, SEXP vd6_v, SEXP test_one_if)
{
  return (R_internal_TEST_ONE_IF_DV(v, vd6_v, test_one_if, false));
}

SEXP R_ArrayTest::R_internal_test_one_if_internal(SEXP v, bool bTranslate)
{
  double arg_v;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = test_one_if_internal(arg_v);
  
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_test_one_if_internal(SEXP v)
{
  return (R_internal_test_one_if_internal(v, true));
}

SEXP R_ArrayTest::R_nt_test_one_if_internal(SEXP v)
{
  return (R_internal_test_one_if_internal(v, false));
}

SEXP R_ArrayTest::R_internal_TEST_ONE_IF_INTERNAL_BV(SEXP v, SEXP vb9_v, SEXP test_one_if_internalb9_v, bool bTranslate)
{
  double arg_v;
  double arg_vb9_v;
  double arg_test_one_if_internalb9_v;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  R_CheckArgument("vb9_v", "REALSXP", REALSXP, vb9_v, __FILE__, __LINE__);
  
  R_CheckArgument("test_one_if_internalb9_v", "REALSXP", REALSXP, test_one_if_internalb9_v, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
    arg_vb9_v = REAL(vb9_v)[0];
    arg_test_one_if_internalb9_v = REAL(test_one_if_internalb9_v)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
    arg_vb9_v = REAL(vb9_v)[0];
    arg_test_one_if_internalb9_v = REAL(test_one_if_internalb9_v)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = 0.0;
  TEST_ONE_IF_INTERNAL_BV(arg_v, arg_vb9_v, arg_test_one_if_internalb9_v);
  
  if (bTranslate)
  {
    REAL(vb9_v)[0] = arg_vb9_v;
    REAL(test_one_if_internalb9_v)[0] = arg_test_one_if_internalb9_v;
  }
  else
  {
    REAL(vb9_v)[0] = arg_vb9_v;
    REAL(test_one_if_internalb9_v)[0] = arg_test_one_if_internalb9_v;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_TEST_ONE_IF_INTERNAL_BV(SEXP v, SEXP vb9_v, SEXP test_one_if_internalb9_v)
{
  return (R_internal_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v, true));
}

SEXP R_ArrayTest::R_nt_TEST_ONE_IF_INTERNAL_BV(SEXP v, SEXP vb9_v, SEXP test_one_if_internalb9_v)
{
  return (R_internal_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v, false));
}

SEXP R_ArrayTest::R_internal_TEST_ONE_IF_INTERNAL_DV(SEXP v, SEXP vd8_v, SEXP test_one_if_internal, bool bTranslate)
{
  double arg_v;
  double arg_vd8_v;
  double arg_test_one_if_internal;
  
  R_CheckArgument("v", "REALSXP", REALSXP, v, __FILE__, __LINE__);
  
  R_CheckArgument("vd8_v", "REALSXP", REALSXP, vd8_v, __FILE__, __LINE__);
  
  R_CheckArgument("test_one_if_internal", "REALSXP", REALSXP, test_one_if_internal, __FILE__, __LINE__);
  
  if (bTranslate)
  {
    arg_v = REAL(v)[0];
    arg_vd8_v = REAL(vd8_v)[0];
    arg_test_one_if_internal = REAL(test_one_if_internal)[0];
  }
  else
  {
    arg_v = REAL(v)[0];
    arg_vd8_v = REAL(vd8_v)[0];
    arg_test_one_if_internal = REAL(test_one_if_internal)[0];
  }
  
  SEXP Result = Rf_allocVector(REALSXP, 1);
  
  PROTECT(Result);
  REAL(Result)[0] = TEST_ONE_IF_INTERNAL_DV(arg_v, arg_vd8_v, arg_test_one_if_internal);
  
  if (bTranslate)
  {
    REAL(test_one_if_internal)[0] = arg_test_one_if_internal;
  }
  else
  {
    REAL(test_one_if_internal)[0] = arg_test_one_if_internal;
  }
  
  UNPROTECT(1);
  
  return (Result);
}

SEXP R_ArrayTest::R_TEST_ONE_IF_INTERNAL_DV(SEXP v, SEXP vd8_v, SEXP test_one_if_internal)
{
  return (R_internal_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal, true));
}

SEXP R_ArrayTest::R_nt_TEST_ONE_IF_INTERNAL_DV(SEXP v, SEXP vd8_v, SEXP test_one_if_internal)
{
  return (R_internal_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal, false));
}
