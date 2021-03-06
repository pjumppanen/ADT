SEXP R_internal_hessian(SEXP pX, SEXP pHessian, bool bTranslate);
SEXP R_hessian(SEXP pX, SEXP pHessian);
SEXP R_nt_hessian(SEXP pX, SEXP pHessian);
SEXP _get_lxb1_x(SEXP sArgList) const;
SEXP _set_lxb1_x(SEXP arg_lxb1_x, SEXP sArgList);
SEXP _get_nt_lxb1_x(SEXP sArgList) const;
SEXP _set_nt_lxb1_x(SEXP arg_lxb1_x, SEXP sArgList);
SEXP _get_lxd2_x(SEXP sArgList) const;
SEXP _set_lxd2_x(SEXP arg_lxd2_x, SEXP sArgList);
SEXP _get_nt_lxd2_x(SEXP sArgList) const;
SEXP _set_nt_lxd2_x(SEXP arg_lxd2_x, SEXP sArgList);
SEXP R_internal_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status, bool bTranslate);
SEXP R_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status);
SEXP R_nt_minimise(SEXP pS, SEXP pR, SEXP maxit, SEXP fncount, SEXP grcount, SEXP status);
