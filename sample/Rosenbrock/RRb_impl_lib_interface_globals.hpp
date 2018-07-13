IMPL_TYPE_TAG(DR_MinRosenbrock)


EXPORT SEXP RRb_R_hessian(SEXP args)
{
  SEXP rInstance;
  SEXP pX;
  SEXP pHessian;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pX = CAR(args);
  args = CDR(args); pHessian = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_hessian(pX, pHessian);
  
  return (Result);
}

EXPORT SEXP RRb_R_nt_hessian(SEXP args)
{
  SEXP rInstance;
  SEXP pX;
  SEXP pHessian;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pX = CAR(args);
  args = CDR(args); pHessian = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_hessian(pX, pHessian);
  
  return (Result);
}

EXPORT SEXP RRb_get_lxb1_x(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_lxb1_x(sArgList));
}

EXPORT SEXP RRb_set_lxb1_x(SEXP args)
{
  SEXP rInstance;
  SEXP arg_lxb1_x;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_lxb1_x = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_lxb1_x(arg_lxb1_x, sArgList));
}


EXPORT SEXP RRb_get_nt_lxb1_x(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_lxb1_x(sArgList));
}

EXPORT SEXP RRb_set_nt_lxb1_x(SEXP args)
{
  SEXP rInstance;
  SEXP arg_lxb1_x;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_lxb1_x = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_lxb1_x(arg_lxb1_x, sArgList));
}


EXPORT SEXP RRb_get_lxd2_x(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_lxd2_x(sArgList));
}

EXPORT SEXP RRb_set_lxd2_x(SEXP args)
{
  SEXP rInstance;
  SEXP arg_lxd2_x;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_lxd2_x = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_lxd2_x(arg_lxd2_x, sArgList));
}


EXPORT SEXP RRb_get_nt_lxd2_x(SEXP args)
{
  SEXP rInstance;
  SEXP sArgList;
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_nt_lxd2_x(sArgList));
}

EXPORT SEXP RRb_set_nt_lxd2_x(SEXP args)
{
  SEXP rInstance;
  SEXP arg_lxd2_x;
  SEXP sArgList;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_lxd2_x = CAR(args);
  args = CDR(args); sArgList = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_nt_lxd2_x(arg_lxd2_x, sArgList));
}


EXPORT SEXP RRb_R_minimise(SEXP args)
{
  SEXP rInstance;
  SEXP pS;
  SEXP pR;
  SEXP maxit;
  SEXP fncount;
  SEXP grcount;
  SEXP status;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pS = CAR(args);
  args = CDR(args); pR = CAR(args);
  args = CDR(args); maxit = CAR(args);
  args = CDR(args); fncount = CAR(args);
  args = CDR(args); grcount = CAR(args);
  args = CDR(args); status = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_minimise(pS, pR, maxit, fncount, grcount, status);
  
  return (Result);
}

EXPORT SEXP RRb_R_nt_minimise(SEXP args)
{
  SEXP rInstance;
  SEXP pS;
  SEXP pR;
  SEXP maxit;
  SEXP fncount;
  SEXP grcount;
  SEXP status;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); pS = CAR(args);
  args = CDR(args); pR = CAR(args);
  args = CDR(args); maxit = CAR(args);
  args = CDR(args); fncount = CAR(args);
  args = CDR(args); grcount = CAR(args);
  args = CDR(args); status = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  DR_MinRosenbrock* pContext = (DR_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_minimise(pS, pR, maxit, fncount, grcount, status);
  
  return (Result);
}
