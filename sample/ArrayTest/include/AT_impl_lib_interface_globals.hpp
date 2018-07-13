IMPL_TYPE_TAG(R_ArrayTest)


EXPORT SEXP AT_get_A1_D(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A1_D(sArgList));
}

EXPORT SEXP AT_set_A1_D(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A1_D;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A1_D = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A1_D(arg_A1_D, sArgList));
}


EXPORT SEXP AT_get_nt_A1_D(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A1_D(sArgList));
}

EXPORT SEXP AT_set_nt_A1_D(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A1_D;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A1_D = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A1_D(arg_A1_D, sArgList));
}


EXPORT SEXP AT_get_A1_I(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A1_I(sArgList));
}

EXPORT SEXP AT_set_A1_I(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A1_I;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A1_I = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A1_I(arg_A1_I, sArgList));
}


EXPORT SEXP AT_get_nt_A1_I(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A1_I(sArgList));
}

EXPORT SEXP AT_set_nt_A1_I(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A1_I;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A1_I = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A1_I(arg_A1_I, sArgList));
}


EXPORT SEXP AT_get_A2_B(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_B(sArgList));
}

EXPORT SEXP AT_set_A2_B(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_B;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_B = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_B(arg_A2_B, sArgList));
}


EXPORT SEXP AT_get_nt_A2_B(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_B(sArgList));
}

EXPORT SEXP AT_set_nt_A2_B(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_B;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_B = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_B(arg_A2_B, sArgList));
}


EXPORT SEXP AT_get_A2_C(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_C(sArgList));
}

EXPORT SEXP AT_set_A2_C(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_C;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_C = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_C(arg_A2_C, sArgList));
}


EXPORT SEXP AT_get_nt_A2_C(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_C(sArgList));
}

EXPORT SEXP AT_set_nt_A2_C(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_C;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_C = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_C(arg_A2_C, sArgList));
}


EXPORT SEXP AT_get_A2_DA(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_DA(sArgList));
}

EXPORT SEXP AT_set_A2_DA(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_DA;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_DA = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_DA(arg_A2_DA, sArgList));
}


EXPORT SEXP AT_get_nt_A2_DA(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_DA(sArgList));
}

EXPORT SEXP AT_set_nt_A2_DA(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_DA;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_DA = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_DA(arg_A2_DA, sArgList));
}


EXPORT SEXP AT_get_A2_IA(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_IA(sArgList));
}

EXPORT SEXP AT_set_A2_IA(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_IA;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_IA = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_IA(arg_A2_IA, sArgList));
}


EXPORT SEXP AT_get_nt_A2_IA(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_IA(sArgList));
}

EXPORT SEXP AT_set_nt_A2_IA(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_IA;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_IA = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_IA(arg_A2_IA, sArgList));
}


EXPORT SEXP AT_get_A2_IB(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_IB(sArgList));
}

EXPORT SEXP AT_set_A2_IB(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_IB;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_IB = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_IB(arg_A2_IB, sArgList));
}


EXPORT SEXP AT_get_nt_A2_IB(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_IB(sArgList));
}

EXPORT SEXP AT_set_nt_A2_IB(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_IB;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_IB = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_IB(arg_A2_IB, sArgList));
}


EXPORT SEXP AT_get_A2_LB(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_LB(sArgList));
}

EXPORT SEXP AT_set_A2_LB(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_LB;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_LB = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_LB(arg_A2_LB, sArgList));
}


EXPORT SEXP AT_get_nt_A2_LB(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_LB(sArgList));
}

EXPORT SEXP AT_set_nt_A2_LB(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_LB;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_LB = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_LB(arg_A2_LB, sArgList));
}


EXPORT SEXP AT_get_A2_UC(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_A2_UC(sArgList));
}

EXPORT SEXP AT_set_A2_UC(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_UC;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_UC = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_A2_UC(arg_A2_UC, sArgList));
}


EXPORT SEXP AT_get_nt_A2_UC(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_A2_UC(sArgList));
}

EXPORT SEXP AT_set_nt_A2_UC(SEXP args)
{
  SEXP rInstance;
  SEXP arg_A2_UC;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_A2_UC = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_A2_UC(arg_A2_UC, sArgList));
}


EXPORT SEXP AT_R_boundsCheckTest(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_boundsCheckTest(x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_boundsCheckTest(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_boundsCheckTest(x);
  
  return (Result);
}

EXPORT SEXP AT_R_IFTEST_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb6_x;
  SEXP iftestb6_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb6_x = CAR(args);
  args = CDR(args); iftestb6_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_IFTEST_BX(x, xb6_x, iftestb6_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_IFTEST_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb6_x;
  SEXP iftestb6_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb6_x = CAR(args);
  args = CDR(args); iftestb6_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_IFTEST_BX(x, xb6_x, iftestb6_x);
  
  return (Result);
}

EXPORT SEXP AT_R_isNegative(SEXP args)
{
  SEXP rInstance;
  SEXP dValue;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); dValue = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_isNegative(dValue);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_isNegative(SEXP args)
{
  SEXP rInstance;
  SEXP dValue;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); dValue = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_isNegative(dValue);
  
  return (Result);
}

EXPORT SEXP AT_R_isPositive(SEXP args)
{
  SEXP rInstance;
  SEXP dValue;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); dValue = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_isPositive(dValue);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_isPositive(SEXP args)
{
  SEXP rInstance;
  SEXP dValue;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); dValue = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_isPositive(dValue);
  
  return (Result);
}

EXPORT SEXP AT_get_ix(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_ix());
}

EXPORT SEXP AT_set_ix(SEXP args)
{
  SEXP rInstance;
  SEXP arg_ix;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_ix = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_ix(arg_ix));
}


EXPORT SEXP AT_get_iy(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_iy());
}

EXPORT SEXP AT_set_iy(SEXP args)
{
  SEXP rInstance;
  SEXP arg_iy;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_iy = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_iy(arg_iy));
}


EXPORT SEXP AT_R_polySum3D(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySum3D(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySum3D(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySum3D(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUM3D_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb1_x;
  SEXP polysum3db1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); polysum3db1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUM3D_BX(x, xb1_x, polysum3db1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUM3D_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb1_x;
  SEXP polysum3db1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); polysum3db1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUM3D_BX(x, xb1_x, polysum3db1_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumA(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumA(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumA(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumA(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMA_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb3_x;
  SEXP polysumab3_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb3_x = CAR(args);
  args = CDR(args); polysumab3_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMA_BX(x, xb3_x, polysumab3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMA_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb3_x;
  SEXP polysumab3_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb3_x = CAR(args);
  args = CDR(args); polysumab3_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMA_BX(x, xb3_x, polysumab3_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumB(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumB(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumB(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumB(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMB_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb4_x;
  SEXP polysumbb4_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb4_x = CAR(args);
  args = CDR(args); polysumbb4_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMB_BX(x, xb4_x, polysumbb4_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMB_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb4_x;
  SEXP polysumbb4_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb4_x = CAR(args);
  args = CDR(args); polysumbb4_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMB_BX(x, xb4_x, polysumbb4_x);
  
  return (Result);
}

EXPORT SEXP AT_R_polySumC(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_polySumC(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_polySumC(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_polySumC(X);
  
  return (Result);
}

EXPORT SEXP AT_R_POLYSUMC_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb5_x;
  SEXP polysumcb5_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb5_x = CAR(args);
  args = CDR(args); polysumcb5_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_POLYSUMC_BX(x, xb5_x, polysumcb5_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_POLYSUMC_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb5_x;
  SEXP polysumcb5_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb5_x = CAR(args);
  args = CDR(args); polysumcb5_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_POLYSUMC_BX(x, xb5_x, polysumcb5_x);
  
  return (Result);
}

EXPORT SEXP AT_get_SingularBool(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SingularBool());
}

EXPORT SEXP AT_set_SingularBool(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SingularBool;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SingularBool = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SingularBool(arg_SingularBool));
}


EXPORT SEXP AT_get_SingularLongbool(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_SingularLongbool());
}

EXPORT SEXP AT_set_SingularLongbool(SEXP args)
{
  SEXP rInstance;
  SEXP arg_SingularLongbool;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_SingularLongbool = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_SingularLongbool(arg_SingularLongbool));
}


EXPORT SEXP AT_R_sum(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_sum(X);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_sum(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_sum(X);
  
  return (Result);
}

EXPORT SEXP AT_R_SUM_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb2_x;
  SEXP sumb2_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb2_x = CAR(args);
  args = CDR(args); sumb2_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_SUM_BX(x, xb2_x, sumb2_x);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_SUM_BX(SEXP args)
{
  SEXP rInstance;
  SEXP x;
  SEXP xb2_x;
  SEXP sumb2_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); x = CAR(args);
  args = CDR(args); xb2_x = CAR(args);
  args = CDR(args); sumb2_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_SUM_BX(x, xb2_x, sumb2_x);
  
  return (Result);
}

EXPORT SEXP AT_R_sumA1_D(SEXP args)
{
  SEXP rInstance;
  
  
  args = CDR(args); rInstance = CAR(args);
  
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_sumA1_D();
  
  return (Result);
}

EXPORT SEXP AT_R_nt_sumA1_D(SEXP args)
{
  SEXP rInstance;
  
  
  args = CDR(args); rInstance = CAR(args);
  
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_sumA1_D();
  
  return (Result);
}

EXPORT SEXP AT_R_test_one_if(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_test_one_if(v);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_test_one_if(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_test_one_if(v);
  
  return (Result);
}

EXPORT SEXP AT_R_TEST_ONE_IF_BV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vb8_v;
  SEXP test_one_ifb8_v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vb8_v = CAR(args);
  args = CDR(args); test_one_ifb8_v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_TEST_ONE_IF_BV(v, vb8_v, test_one_ifb8_v);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_TEST_ONE_IF_BV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vb8_v;
  SEXP test_one_ifb8_v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vb8_v = CAR(args);
  args = CDR(args); test_one_ifb8_v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_TEST_ONE_IF_BV(v, vb8_v, test_one_ifb8_v);
  
  return (Result);
}

EXPORT SEXP AT_R_TEST_ONE_IF_DV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vd7_v;
  SEXP test_one_if;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vd7_v = CAR(args);
  args = CDR(args); test_one_if = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_TEST_ONE_IF_DV(v, vd7_v, test_one_if);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_TEST_ONE_IF_DV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vd7_v;
  SEXP test_one_if;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vd7_v = CAR(args);
  args = CDR(args); test_one_if = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_TEST_ONE_IF_DV(v, vd7_v, test_one_if);
  
  return (Result);
}

EXPORT SEXP AT_R_test_one_if_internal(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_test_one_if_internal(v);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_test_one_if_internal(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_test_one_if_internal(v);
  
  return (Result);
}

EXPORT SEXP AT_R_TEST_ONE_IF_INTERNAL_BV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vb10_v;
  SEXP test_one_if_internalb10_v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vb10_v = CAR(args);
  args = CDR(args); test_one_if_internalb10_v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_TEST_ONE_IF_INTERNAL_BV(v, vb10_v, test_one_if_internalb10_v);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_TEST_ONE_IF_INTERNAL_BV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vb10_v;
  SEXP test_one_if_internalb10_v;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vb10_v = CAR(args);
  args = CDR(args); test_one_if_internalb10_v = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_TEST_ONE_IF_INTERNAL_BV(v, vb10_v, test_one_if_internalb10_v);
  
  return (Result);
}

EXPORT SEXP AT_R_TEST_ONE_IF_INTERNAL_DV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vd9_v;
  SEXP test_one_if_internal;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vd9_v = CAR(args);
  args = CDR(args); test_one_if_internal = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_TEST_ONE_IF_INTERNAL_DV(v, vd9_v, test_one_if_internal);
  
  return (Result);
}

EXPORT SEXP AT_R_nt_TEST_ONE_IF_INTERNAL_DV(SEXP args)
{
  SEXP rInstance;
  SEXP v;
  SEXP vd9_v;
  SEXP test_one_if_internal;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); v = CAR(args);
  args = CDR(args); vd9_v = CAR(args);
  args = CDR(args); test_one_if_internal = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, R_ArrayTest);
  
  R_ArrayTest* pContext = (R_ArrayTest*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_TEST_ONE_IF_INTERNAL_DV(v, vd9_v, test_one_if_internal);
  
  return (Result);
}

EXPORT SEXP AT_get_female()
{
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = female;
  UNPROTECT(1);
  
  return(Result);
}


EXPORT SEXP AT_get_male()
{
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = male;
  UNPROTECT(1);
  
  return(Result);
}


EXPORT SEXP AT_get_n_sex()
{
  SEXP Result = allocVector(INTSXP, 1);
  
  PROTECT(Result);
  INTEGER(Result)[0] = n_sex;
  UNPROTECT(1);
  
  return(Result);
}

