DECL_TYPE_TAG(D_MinRosenbrock)

EXPORT SEXP Rb_get_N(SEXP rInstance);
EXPORT SEXP Rb_set_N(SEXP rInstance, SEXP arg_N);
EXPORT SEXP Rb_R_rosenbrock(SEXP rInstance, SEXP X);
EXPORT SEXP Rb_R_nt_rosenbrock(SEXP rInstance, SEXP X);
EXPORT SEXP Rb_R_ROSENBROCK_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP rosenbrockb1_x);
EXPORT SEXP Rb_R_nt_ROSENBROCK_BX(SEXP rInstance, SEXP X, SEXP xb1_x, SEXP rosenbrockb1_x);
EXPORT SEXP Rb_R_ROSENBROCK_BX_DX(SEXP rInstance, SEXP X, SEXP xd2_x, SEXP xb1_x, SEXP xb1_xd2_x, SEXP rosenbrockb1_x);
EXPORT SEXP Rb_R_nt_ROSENBROCK_BX_DX(SEXP rInstance, SEXP X, SEXP xd2_x, SEXP xb1_x, SEXP xb1_xd2_x, SEXP rosenbrockb1_x);
