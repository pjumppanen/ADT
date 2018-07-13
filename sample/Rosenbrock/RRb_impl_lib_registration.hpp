static const R_CallMethodDef extMethods[] = 
{
  {"_Rb.destroy", (DL_FUNC)&Rb_destroy, 1},
  {"_Rb.create", (DL_FUNC)&Rb_create, 1},
  {"_Rb.get.N", (DL_FUNC)&Rb_get_N, 1},
  {"_Rb.set.N", (DL_FUNC)&Rb_set_N, 2},
  {"_Rb.rosenbrock", (DL_FUNC)&Rb_R_rosenbrock, 2},
  {"_Rb.nt.rosenbrock", (DL_FUNC)&Rb_R_nt_rosenbrock, 2},
  {"_Rb.ROSENBROCK_BX", (DL_FUNC)&Rb_R_ROSENBROCK_BX, 4},
  {"_Rb.nt.ROSENBROCK_BX", (DL_FUNC)&Rb_R_nt_ROSENBROCK_BX, 4},
  {"_Rb.ROSENBROCK_BX_DX", (DL_FUNC)&Rb_R_ROSENBROCK_BX_DX, 6},
  {"_Rb.nt.ROSENBROCK_BX_DX", (DL_FUNC)&Rb_R_nt_ROSENBROCK_BX_DX, 6},
  {"_RRb.destroy", (DL_FUNC)&RRb_destroy, 1},
  {"_RRb.create", (DL_FUNC)&RRb_create, 1},
  {"_RRb.hessian", (DL_FUNC)&RRb_R_hessian, 3},
  {"_RRb.nt.hessian", (DL_FUNC)&RRb_R_nt_hessian, 3},
  {"_RRb.get.lxb1_x", (DL_FUNC)&RRb_get_lxb1_x, 2},
  {"_RRb.set.lxb1_x", (DL_FUNC)&RRb_set_lxb1_x, 3},
  {"_RRb.get.nt.lxb1_x", (DL_FUNC)&RRb_get_nt_lxb1_x, 2},
  {"_RRb.set.nt.lxb1_x", (DL_FUNC)&RRb_set_nt_lxb1_x, 3},
  {"_RRb.get.lxd2_x", (DL_FUNC)&RRb_get_lxd2_x, 2},
  {"_RRb.set.lxd2_x", (DL_FUNC)&RRb_set_lxd2_x, 3},
  {"_RRb.get.nt.lxd2_x", (DL_FUNC)&RRb_get_nt_lxd2_x, 2},
  {"_RRb.set.nt.lxd2_x", (DL_FUNC)&RRb_set_nt_lxd2_x, 3},
  {"_RRb.minimise", (DL_FUNC)&RRb_R_minimise, 7},
  {"_RRb.nt.minimise", (DL_FUNC)&RRb_R_nt_minimise, 7},
  0
};


EXPORT void R_init_Rosenbrock(DllInfo* pInfo)
{
  R_SetArrayClass(ArrayClass_Oarray);
  R_registerRoutines(pInfo, 0, 0, 0, extMethods);
}


EXPORT void R_init_libRosenbrock(DllInfo* pInfo)
{
  R_SetArrayClass(ArrayClass_Oarray);
  R_registerRoutines(pInfo, 0, 0, 0, extMethods);
}


