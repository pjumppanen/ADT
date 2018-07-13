IMPL_TYPE_TAG(D_MinRosenbrock)


EXPORT SEXP Rb_get_N(SEXP args)
{
  SEXP rInstance;
  args = CDR(args); rInstance = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_get_N());
}

EXPORT SEXP Rb_set_N(SEXP args)
{
  SEXP rInstance;
  SEXP arg_N;
  
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); arg_N = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  return (pContext->_set_N(arg_N));
}


EXPORT SEXP Rb_R_rosenbrock(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_rosenbrock(X);
  
  return (Result);
}

EXPORT SEXP Rb_R_nt_rosenbrock(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_rosenbrock(X);
  
  return (Result);
}

EXPORT SEXP Rb_R_ROSENBROCK_BX(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  SEXP xb1_x;
  SEXP rosenbrockb1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); rosenbrockb1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_ROSENBROCK_BX(X, xb1_x, rosenbrockb1_x);
  
  return (Result);
}

EXPORT SEXP Rb_R_nt_ROSENBROCK_BX(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  SEXP xb1_x;
  SEXP rosenbrockb1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); rosenbrockb1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_ROSENBROCK_BX(X, xb1_x, rosenbrockb1_x);
  
  return (Result);
}

EXPORT SEXP Rb_R_ROSENBROCK_BX_DX(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  SEXP xd2_x;
  SEXP xb1_x;
  SEXP xb1_xd2_x;
  SEXP rosenbrockb1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  args = CDR(args); xd2_x = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); xb1_xd2_x = CAR(args);
  args = CDR(args); rosenbrockb1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_ROSENBROCK_BX_DX(X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x);
  
  return (Result);
}

EXPORT SEXP Rb_R_nt_ROSENBROCK_BX_DX(SEXP args)
{
  SEXP rInstance;
  SEXP X;
  SEXP xd2_x;
  SEXP xb1_x;
  SEXP xb1_xd2_x;
  SEXP rosenbrockb1_x;
  
  args = CDR(args); rInstance = CAR(args);
  args = CDR(args); X = CAR(args);
  args = CDR(args); xd2_x = CAR(args);
  args = CDR(args); xb1_x = CAR(args);
  args = CDR(args); xb1_xd2_x = CAR(args);
  args = CDR(args); rosenbrockb1_x = CAR(args);
  
  ASSERT_TYPE_TAG(rInstance, D_MinRosenbrock);
  
  D_MinRosenbrock* pContext = (D_MinRosenbrock*)R_ExternalPtrAddr(rInstance);
  
  SEXP Result = pContext->R_nt_ROSENBROCK_BX_DX(X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x);
  
  return (Result);
}
