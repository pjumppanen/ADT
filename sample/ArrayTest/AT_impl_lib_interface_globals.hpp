IMPL_TYPE_TAG(R_ArrayTest)


EXPORT SEXP AT_get_A1_D(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A1_D(sArgList));
}

EXPORT SEXP AT_set_A1_D(SEXP rInstance, SEXP arg_A1_D, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A1_D(arg_A1_D, sArgList));
}

EXPORT SEXP AT_get_nt_A1_D(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A1_D(sArgList));
}

EXPORT SEXP AT_set_nt_A1_D(SEXP rInstance, SEXP arg_A1_D, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A1_D(arg_A1_D, sArgList));
}

EXPORT SEXP AT_get_A1_I(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A1_I(sArgList));
}

EXPORT SEXP AT_set_A1_I(SEXP rInstance, SEXP arg_A1_I, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A1_I(arg_A1_I, sArgList));
}

EXPORT SEXP AT_get_nt_A1_I(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A1_I(sArgList));
}

EXPORT SEXP AT_set_nt_A1_I(SEXP rInstance, SEXP arg_A1_I, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A1_I(arg_A1_I, sArgList));
}

EXPORT SEXP AT_get_A2_IA(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_IA(sArgList));
}

EXPORT SEXP AT_set_A2_IA(SEXP rInstance, SEXP arg_A2_IA, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_IA(arg_A2_IA, sArgList));
}

EXPORT SEXP AT_get_nt_A2_IA(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_IA(sArgList));
}

EXPORT SEXP AT_set_nt_A2_IA(SEXP rInstance, SEXP arg_A2_IA, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_IA(arg_A2_IA, sArgList));
}

EXPORT SEXP AT_get_A2_IB(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_IB(sArgList));
}

EXPORT SEXP AT_set_A2_IB(SEXP rInstance, SEXP arg_A2_IB, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_IB(arg_A2_IB, sArgList));
}

EXPORT SEXP AT_get_nt_A2_IB(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_IB(sArgList));
}

EXPORT SEXP AT_set_nt_A2_IB(SEXP rInstance, SEXP arg_A2_IB, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_IB(arg_A2_IB, sArgList));
}

EXPORT SEXP AT_R_boundsCheckTest(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_boundsCheckTest(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_boundsCheckTest(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_boundsCheckTest(X);
  
  return (Result);
}

EXPORT SEXP AT_R_GLOBAL_SUM_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP nBase, SEXP nCount, SEXP global_sumb1_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_GLOBAL_SUM_BX(X, xb1_x, nBase, nCount, global_sumb1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_GLOBAL_SUM_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP nBase, SEXP nCount, SEXP global_sumb1_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_GLOBAL_SUM_BX(X, xb1_x, nBase, nCount, global_sumb1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_IFTEST_BX(SEXP rInstance, SEXP X, SEXP xb5_x, SEXP iftestb5_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_IFTEST_BX(X, xb5_x, iftestb5_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_IFTEST_BX(SEXP rInstance, SEXP X, SEXP xb5_x, SEXP iftestb5_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_IFTEST_BX(X, xb5_x, iftestb5_x);
  
  return (Result);
}

EXPORT SEXP AT_get_ix(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_ix());
}

EXPORT SEXP AT_set_ix(SEXP rInstance, SEXP arg_ix)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_ix(arg_ix));
}

EXPORT SEXP AT_get_iy(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_iy());
}

EXPORT SEXP AT_set_iy(SEXP rInstance, SEXP arg_iy)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_iy(arg_iy));
}

EXPORT SEXP AT_R_POLYB_BX(SEXP rInstance, SEXP X, SEXP xb3_x, SEXP polybb3_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYB_BX(X, xb3_x, polybb3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYB_BX(SEXP rInstance, SEXP X, SEXP xb3_x, SEXP polybb3_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYB_BX(X, xb3_x, polybb3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYB_BX0(SEXP rInstance, SEXP X, SEXP xb5_x, SEXP polybb5_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYB_BX0(X, xb5_x, polybb5_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYB_BX0(SEXP rInstance, SEXP X, SEXP xb5_x, SEXP polybb5_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYB_BX0(X, xb5_x, polybb5_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumA(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumA(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumA(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumA(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMA_BX(SEXP rInstance, SEXP X, SEXP xb2_x, SEXP polysumab2_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMA_BX(X, xb2_x, polysumab2_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMA_BX(SEXP rInstance, SEXP X, SEXP xb2_x, SEXP polysumab2_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMA_BX(X, xb2_x, polysumab2_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumB(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumB(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumB(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumB(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMB_BX(SEXP rInstance, SEXP X, SEXP xb3_x, SEXP polysumbb3_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMB_BX(X, xb3_x, polysumbb3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMB_BX(SEXP rInstance, SEXP X, SEXP xb3_x, SEXP polysumbb3_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMB_BX(X, xb3_x, polysumbb3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumC(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumC(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumC(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumC(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMC_BX(SEXP rInstance, SEXP X, SEXP xb4_x, SEXP polysumcb4_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMC_BX(X, xb4_x, polysumcb4_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMC_BX(SEXP rInstance, SEXP X, SEXP xb4_x, SEXP polysumcb4_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMC_BX(X, xb4_x, polysumcb4_x);
  
  return (Result);
}

EXPORT SEXP AT_R_sum(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_sum(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_sum(SEXP rInstance, SEXP X)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_sum(X);
  
  return (Result);
}

EXPORT SEXP AT_R_SUM_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP sumb1_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_SUM_BX(X, xb1_x, sumb1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_SUM_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP sumb1_x)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_SUM_BX(X, xb1_x, sumb1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_sumA1_B(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_sumA1_B();
  
  return (Result);
}

EXPORT SEXP AT_R_nt_sumA1_B(SEXP rInstance)
{
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_sumA1_B();
  
  return (Result);
}
