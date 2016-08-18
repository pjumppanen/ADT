IMPL_TYPE_TAG(DR_MinRosenbrock)


EXPORT SEXP RRb_R_hessian(SEXP rInstance, SEXP pX, SEXP pHessian)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_hessian(pX, pHessian);
  
  return (Result);
}

EXPORT SEXP RRb_R_nt_hessian(SEXP rInstance, SEXP pX, SEXP pHessian)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_hessian(pX, pHessian);
  
  return (Result);
}

EXPORT SEXP RRb_get_lxb1_x(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_lxb1_x(sArgList));
}

EXPORT SEXP RRb_set_lxb1_x(SEXP rInstance, SEXP arg_lxb1_x, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_lxb1_x(arg_lxb1_x, sArgList));
}

EXPORT SEXP RRb_get_nt_lxb1_x(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_lxb1_x(sArgList));
}

EXPORT SEXP RRb_set_nt_lxb1_x(SEXP rInstance, SEXP arg_lxb1_x, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_lxb1_x(arg_lxb1_x, sArgList));
}

EXPORT SEXP RRb_get_lxd2_x(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_lxd2_x(sArgList));
}

EXPORT SEXP RRb_set_lxd2_x(SEXP rInstance, SEXP arg_lxd2_x, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_lxd2_x(arg_lxd2_x, sArgList));
}

EXPORT SEXP RRb_get_nt_lxd2_x(SEXP rInstance, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_lxd2_x(sArgList));
}

EXPORT SEXP RRb_set_nt_lxd2_x(SEXP rInstance, SEXP arg_lxd2_x, SEXP sArgList)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_lxd2_x(arg_lxd2_x, sArgList));
}

EXPORT SEXP RRb_R_minimise(SEXP rInstance, SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_minimise(pS, pR, maxit, fncount, grcount, status);
  
  return (Result);
}

EXPORT SEXP RRb_R_nt_minimise(SEXP rInstance, SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status)
{
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_minimise(pS, pR, maxit, fncount, grcount, status);
  
  return (Result);
}
