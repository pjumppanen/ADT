static const R_CallMethodDef callMethods[] = 
{
  {"_AT.destroy", (DL_FUNC)&AT_destroy, 1},
  {"_AT.create", (DL_FUNC)&AT_create, 6},
  {"_AT.get.A1_D", (DL_FUNC)&AT_get_A1_D, 2},
  {"_AT.set.A1_D", (DL_FUNC)&AT_set_A1_D, 3},
  {"_AT.get.nt.A1_D", (DL_FUNC)&AT_get_nt_A1_D, 2},
  {"_AT.set.nt.A1_D", (DL_FUNC)&AT_set_nt_A1_D, 3},
  {"_AT.get.A1_I", (DL_FUNC)&AT_get_A1_I, 2},
  {"_AT.set.A1_I", (DL_FUNC)&AT_set_A1_I, 3},
  {"_AT.get.nt.A1_I", (DL_FUNC)&AT_get_nt_A1_I, 2},
  {"_AT.set.nt.A1_I", (DL_FUNC)&AT_set_nt_A1_I, 3},
  {"_AT.get.A2_IA", (DL_FUNC)&AT_get_A2_IA, 2},
  {"_AT.set.A2_IA", (DL_FUNC)&AT_set_A2_IA, 3},
  {"_AT.get.nt.A2_IA", (DL_FUNC)&AT_get_nt_A2_IA, 2},
  {"_AT.set.nt.A2_IA", (DL_FUNC)&AT_set_nt_A2_IA, 3},
  {"_AT.get.A2_IB", (DL_FUNC)&AT_get_A2_IB, 2},
  {"_AT.set.A2_IB", (DL_FUNC)&AT_set_A2_IB, 3},
  {"_AT.get.nt.A2_IB", (DL_FUNC)&AT_get_nt_A2_IB, 2},
  {"_AT.set.nt.A2_IB", (DL_FUNC)&AT_set_nt_A2_IB, 3},
  {"_AT.boundsCheckTest", (DL_FUNC)&AT_R_boundsCheckTest, 2},
  {"_AT.nt.boundsCheckTest", (DL_FUNC)&AT_R_nt_boundsCheckTest, 2},
  {"_AT.GLOBAL_SUM_BX", (DL_FUNC)&AT_R_GLOBAL_SUM_BX, 6},
  {"_AT.nt.GLOBAL_SUM_BX", (DL_FUNC)&AT_R_nt_GLOBAL_SUM_BX, 6},
  {"_AT.IFTEST_BX", (DL_FUNC)&AT_R_IFTEST_BX, 4},
  {"_AT.nt.IFTEST_BX", (DL_FUNC)&AT_R_nt_IFTEST_BX, 4},
  {"_AT.get.ix", (DL_FUNC)&AT_get_ix, 1},
  {"_AT.set.ix", (DL_FUNC)&AT_set_ix, 2},
  {"_AT.get.iy", (DL_FUNC)&AT_get_iy, 1},
  {"_AT.set.iy", (DL_FUNC)&AT_set_iy, 2},
  {"_AT.POLYB_BX", (DL_FUNC)&AT_R_POLYB_BX, 4},
  {"_AT.nt.POLYB_BX", (DL_FUNC)&AT_R_nt_POLYB_BX, 4},
  {"_AT.POLYB_BX0", (DL_FUNC)&AT_R_POLYB_BX0, 4},
  {"_AT.nt.POLYB_BX0", (DL_FUNC)&AT_R_nt_POLYB_BX0, 4},
  {"_AT.polySumA", (DL_FUNC)&AT_R_polySumA, 2},
  {"_AT.nt.polySumA", (DL_FUNC)&AT_R_nt_polySumA, 2},
  {"_AT.POLYSUMA_BX", (DL_FUNC)&AT_R_POLYSUMA_BX, 4},
  {"_AT.nt.POLYSUMA_BX", (DL_FUNC)&AT_R_nt_POLYSUMA_BX, 4},
  {"_AT.polySumB", (DL_FUNC)&AT_R_polySumB, 2},
  {"_AT.nt.polySumB", (DL_FUNC)&AT_R_nt_polySumB, 2},
  {"_AT.POLYSUMB_BX", (DL_FUNC)&AT_R_POLYSUMB_BX, 4},
  {"_AT.nt.POLYSUMB_BX", (DL_FUNC)&AT_R_nt_POLYSUMB_BX, 4},
  {"_AT.polySumC", (DL_FUNC)&AT_R_polySumC, 2},
  {"_AT.nt.polySumC", (DL_FUNC)&AT_R_nt_polySumC, 2},
  {"_AT.POLYSUMC_BX", (DL_FUNC)&AT_R_POLYSUMC_BX, 4},
  {"_AT.nt.POLYSUMC_BX", (DL_FUNC)&AT_R_nt_POLYSUMC_BX, 4},
  {"_AT.sum", (DL_FUNC)&AT_R_sum, 2},
  {"_AT.nt.sum", (DL_FUNC)&AT_R_nt_sum, 2},
  {"_AT.SUM_BX", (DL_FUNC)&AT_R_SUM_BX, 4},
  {"_AT.nt.SUM_BX", (DL_FUNC)&AT_R_nt_SUM_BX, 4},
  {"_AT.sumA1_D", (DL_FUNC)&AT_R_sumA1_D, 1},
  {"_AT.nt.sumA1_D", (DL_FUNC)&AT_R_nt_sumA1_D, 1},
  {"_AT.test_one_if", (DL_FUNC)&AT_R_test_one_if, 2},
  {"_AT.nt.test_one_if", (DL_FUNC)&AT_R_nt_test_one_if, 2},
  {"_AT.TEST_ONE_IF_BV", (DL_FUNC)&AT_R_TEST_ONE_IF_BV, 4},
  {"_AT.nt.TEST_ONE_IF_BV", (DL_FUNC)&AT_R_nt_TEST_ONE_IF_BV, 4},
  {"_AT.TEST_ONE_IF_DV", (DL_FUNC)&AT_R_TEST_ONE_IF_DV, 4},
  {"_AT.nt.TEST_ONE_IF_DV", (DL_FUNC)&AT_R_nt_TEST_ONE_IF_DV, 4},
  {"_AT.test_one_if_internal", (DL_FUNC)&AT_R_test_one_if_internal, 2},
  {"_AT.nt.test_one_if_internal", (DL_FUNC)&AT_R_nt_test_one_if_internal, 2},
  {"_AT.TEST_ONE_IF_INTERNAL_BV", (DL_FUNC)&AT_R_TEST_ONE_IF_INTERNAL_BV, 4},
  {"_AT.nt.TEST_ONE_IF_INTERNAL_BV", (DL_FUNC)&AT_R_nt_TEST_ONE_IF_INTERNAL_BV, 4},
  {"_AT.TEST_ONE_IF_INTERNAL_DV", (DL_FUNC)&AT_R_TEST_ONE_IF_INTERNAL_DV, 4},
  {"_AT.nt.TEST_ONE_IF_INTERNAL_DV", (DL_FUNC)&AT_R_nt_TEST_ONE_IF_INTERNAL_DV, 4},
  0
};


EXPORT void R_init_ArrayTest(DllInfo* pInfo)
{
  R_SetArrayClass(ArrayClass_Oarray);
  R_registerRoutines(pInfo, 0, callMethods, 0, 0);
}


EXPORT void R_init_libArrayTest(DllInfo* pInfo)
{
  R_SetArrayClass(ArrayClass_Oarray);
  R_registerRoutines(pInfo, 0, callMethods, 0, 0);
}


