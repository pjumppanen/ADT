
function AT_get_A1_D(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_A1_D(sArgList);
end;

function AT_set_A1_D(rInstance, arg_A1_D : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_A1_D(arg_A1_D, sArgList);
end;

function AT_get_nt_A1_D(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_nt_A1_D(sArgList);
end;

function AT_set_nt_A1_D(rInstance, arg_A1_D : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_nt_A1_D(arg_A1_D, sArgList);
end;

function AT_get_A1_I(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_A1_I(sArgList);
end;

function AT_set_A1_I(rInstance, arg_A1_I : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_A1_I(arg_A1_I, sArgList);
end;

function AT_get_nt_A1_I(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_nt_A1_I(sArgList);
end;

function AT_set_nt_A1_I(rInstance, arg_A1_I : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_nt_A1_I(arg_A1_I, sArgList);
end;

function AT_get_A2_IA(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_A2_IA(sArgList);
end;

function AT_set_A2_IA(rInstance, arg_A2_IA : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_A2_IA(arg_A2_IA, sArgList);
end;

function AT_get_nt_A2_IA(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_nt_A2_IA(sArgList);
end;

function AT_set_nt_A2_IA(rInstance, arg_A2_IA : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_nt_A2_IA(arg_A2_IA, sArgList);
end;

function AT_get_A2_IB(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_A2_IB(sArgList);
end;

function AT_set_A2_IB(rInstance, arg_A2_IB : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_A2_IB(arg_A2_IB, sArgList);
end;

function AT_get_nt_A2_IB(rInstance : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_nt_A2_IB(sArgList);
end;

function AT_set_nt_A2_IB(rInstance, arg_A2_IB : SEXP; sArgList : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_nt_A2_IB(arg_A2_IB, sArgList);
end;
function AT_R_boundsCheckTest(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_boundsCheckTest(X);
end;

function AT_R_nt_boundsCheckTest(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_boundsCheckTest(X);
end;

function AT_R_GLOBAL_SUM_BX(rInstance : SEXP; x : SEXP; xb1_x : SEXP; nbase : SEXP; ncount : SEXP; global_sumb1_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_GLOBAL_SUM_BX(x, xb1_x, nbase, ncount, global_sumb1_x);
end;

function AT_R_nt_GLOBAL_SUM_BX(rInstance : SEXP; x : SEXP; xb1_x : SEXP; nbase : SEXP; ncount : SEXP; global_sumb1_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_GLOBAL_SUM_BX(x, xb1_x, nbase, ncount, global_sumb1_x);
end;

function AT_R_IFTEST_BX(rInstance : SEXP; x : SEXP; xb5_x : SEXP; iftestb5_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_IFTEST_BX(x, xb5_x, iftestb5_x);
end;

function AT_R_nt_IFTEST_BX(rInstance : SEXP; x : SEXP; xb5_x : SEXP; iftestb5_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_IFTEST_BX(x, xb5_x, iftestb5_x);
end;


function AT_get_ix(rInstance : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_ix();
end;

function AT_set_ix(rInstance, arg_ix : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_ix(arg_ix);
end;

function AT_get_iy(rInstance : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._get_iy();
end;

function AT_set_iy(rInstance, arg_iy : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance))._set_iy(arg_iy);
end;
function AT_R_POLYB_BX(rInstance : SEXP; x : SEXP; xb3_x : SEXP; polybb3_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_POLYB_BX(x, xb3_x, polybb3_x);
end;

function AT_R_nt_POLYB_BX(rInstance : SEXP; x : SEXP; xb3_x : SEXP; polybb3_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_POLYB_BX(x, xb3_x, polybb3_x);
end;

function AT_R_POLYB_BX0(rInstance : SEXP; x : SEXP; xb5_x : SEXP; polybb5_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_POLYB_BX0(x, xb5_x, polybb5_x);
end;

function AT_R_nt_POLYB_BX0(rInstance : SEXP; x : SEXP; xb5_x : SEXP; polybb5_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_POLYB_BX0(x, xb5_x, polybb5_x);
end;

function AT_R_polySumA(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_polySumA(X);
end;

function AT_R_nt_polySumA(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_polySumA(X);
end;

function AT_R_POLYSUMA_BX(rInstance : SEXP; x : SEXP; xb2_x : SEXP; polysumab2_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_POLYSUMA_BX(x, xb2_x, polysumab2_x);
end;

function AT_R_nt_POLYSUMA_BX(rInstance : SEXP; x : SEXP; xb2_x : SEXP; polysumab2_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_POLYSUMA_BX(x, xb2_x, polysumab2_x);
end;

function AT_R_polySumB(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_polySumB(X);
end;

function AT_R_nt_polySumB(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_polySumB(X);
end;

function AT_R_POLYSUMB_BX(rInstance : SEXP; x : SEXP; xb3_x : SEXP; polysumbb3_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_POLYSUMB_BX(x, xb3_x, polysumbb3_x);
end;

function AT_R_nt_POLYSUMB_BX(rInstance : SEXP; x : SEXP; xb3_x : SEXP; polysumbb3_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_POLYSUMB_BX(x, xb3_x, polysumbb3_x);
end;

function AT_R_polySumC(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_polySumC(X);
end;

function AT_R_nt_polySumC(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_polySumC(X);
end;

function AT_R_POLYSUMC_BX(rInstance : SEXP; x : SEXP; xb4_x : SEXP; polysumcb4_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_POLYSUMC_BX(x, xb4_x, polysumcb4_x);
end;

function AT_R_nt_POLYSUMC_BX(rInstance : SEXP; x : SEXP; xb4_x : SEXP; polysumcb4_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_POLYSUMC_BX(x, xb4_x, polysumcb4_x);
end;

function AT_R_sum(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_sum(X);
end;

function AT_R_nt_sum(rInstance : SEXP; X : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_sum(X);
end;

function AT_R_SUM_BX(rInstance : SEXP; x : SEXP; xb1_x : SEXP; sumb1_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_SUM_BX(x, xb1_x, sumb1_x);
end;

function AT_R_nt_SUM_BX(rInstance : SEXP; x : SEXP; xb1_x : SEXP; sumb1_x : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_SUM_BX(x, xb1_x, sumb1_x);
end;

function AT_R_sumA1_D(rInstance : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_sumA1_D();
end;

function AT_R_nt_sumA1_D(rInstance : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_sumA1_D();
end;

function AT_R_test_one_if(rInstance : SEXP; v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_test_one_if(v);
end;

function AT_R_nt_test_one_if(rInstance : SEXP; v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_test_one_if(v);
end;

function AT_R_TEST_ONE_IF_BV(rInstance : SEXP; v : SEXP; vb7_v : SEXP; test_one_ifb7_v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v);
end;

function AT_R_nt_TEST_ONE_IF_BV(rInstance : SEXP; v : SEXP; vb7_v : SEXP; test_one_ifb7_v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v);
end;

function AT_R_TEST_ONE_IF_DV(rInstance : SEXP; v : SEXP; vd6_v : SEXP; test_one_if : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_TEST_ONE_IF_DV(v, vd6_v, test_one_if);
end;

function AT_R_nt_TEST_ONE_IF_DV(rInstance : SEXP; v : SEXP; vd6_v : SEXP; test_one_if : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_TEST_ONE_IF_DV(v, vd6_v, test_one_if);
end;

function AT_R_test_one_if_internal(rInstance : SEXP; v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_test_one_if_internal(v);
end;

function AT_R_nt_test_one_if_internal(rInstance : SEXP; v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_test_one_if_internal(v);
end;

function AT_R_TEST_ONE_IF_INTERNAL_BV(rInstance : SEXP; v : SEXP; vb9_v : SEXP; test_one_if_internalb9_v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v);
end;

function AT_R_nt_TEST_ONE_IF_INTERNAL_BV(rInstance : SEXP; v : SEXP; vb9_v : SEXP; test_one_if_internalb9_v : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v);
end;

function AT_R_TEST_ONE_IF_INTERNAL_DV(rInstance : SEXP; v : SEXP; vd8_v : SEXP; test_one_if_internal : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal);
end;

function AT_R_nt_TEST_ONE_IF_INTERNAL_DV(rInstance : SEXP; v : SEXP; vd8_v : SEXP; test_one_if_internal : SEXP) : SEXP; cdecl;

begin
  R_CHECK_POINTER(rInstance);
  
  Result := R_ArrayTest(R_ExternalPtrAddr(rInstance)).R_nt_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal);
end;

