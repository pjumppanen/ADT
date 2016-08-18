static const R_CallMethodDef callMethods[] = 
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
  0
};


EXPORT void R_init_Rosenbrock(DllInfo* pInfo)
{
  R_registerRoutines(pInfo, 0, callMethods, 0, 0);
}


EXPORT void R_init_libRosenbrock(DllInfo* pInfo)
{
  R_registerRoutines(pInfo, 0, callMethods, 0, 0);
}


