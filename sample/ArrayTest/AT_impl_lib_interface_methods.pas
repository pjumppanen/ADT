
function R_ArrayTest._get_A1_D(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, false, pchar(A1_D), 'A1_D', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_A1_D(arg_A1_D : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, false, pchar(A1_D), 'A1_D', arg_A1_D, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_nt_A1_D(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, true, pchar(A1_D), 'A1_D', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_nt_A1_D(arg_A1_D : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, true, pchar(A1_D), 'A1_D', arg_A1_D, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_A1_I(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, false, pchar(A1_I), 'A1_I', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_A1_I(arg_A1_I : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, false, pchar(A1_I), 'A1_I', arg_A1_I, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_nt_A1_I(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, true, pchar(A1_I), 'A1_I', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_nt_A1_I(arg_A1_I : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, true, pchar(A1_I), 'A1_I', arg_A1_I, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_A2_IA(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, false, pchar(A2_IA), 'A2_IA', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_A2_IA(arg_A2_IA : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, false, pchar(A2_IA), 'A2_IA', arg_A2_IA, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_nt_A2_IA(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, true, pchar(A2_IA), 'A2_IA', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_nt_A2_IA(arg_A2_IA : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, true, pchar(A2_IA), 'A2_IA', arg_A2_IA, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_A2_IB(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, false, pchar(A2_IB), 'A2_IB', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_A2_IB(arg_A2_IB : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, false, pchar(A2_IB), 'A2_IB', arg_A2_IB, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._get_nt_A2_IB(sArgList : SEXP) : SEXP;

begin
  Result := R_ImplGetter(_MemAllocator, true, pchar(A2_IB), 'A2_IB', sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest._set_nt_A2_IB(arg_A2_IB : SEXP; sArgList : SEXP) : SEXP;

begin
  Result := R_ImplSetter(_MemAllocator, true, pchar(A2_IB), 'A2_IB', arg_A2_IB, sArgList, {$I %FILE%}, {$I %LINE%});
end;

function R_ArrayTest.R_internal_boundsCheckTest(X : SEXP; bTranslate : boolean) : SEXP;

var
  arg_X : ARRAY_1D;
  
begin
  R_CheckArgument('X', 'REALSXP', REALSXP, X, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  if bTranslate then
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(X)), pchar(arg_X));
    
  end
  else
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X, pointer(R_REAL(X)));
    
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := boundsCheckTest(arg_X);
  
  
  AdtArrayPlan_destroy(_MemAllocator, arg_X);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_boundsCheckTest(X : SEXP) : SEXP;

begin
  Result := R_internal_boundsCheckTest(X, true);
end;

function R_ArrayTest.R_nt_boundsCheckTest(X : SEXP) : SEXP;

begin
  Result := R_internal_boundsCheckTest(X, false);
end;

function R_ArrayTest.R_internal_GLOBAL_SUM_BX(x : SEXP; xb1_x : SEXP; nbase : SEXP; ncount : SEXP; global_sumb1_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : ARRAY_1D;
  arg_xb1_x : ARRAY_1D;
  arg_nbase : longint;
  arg_ncount : longint;
  arg_global_sumb1_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('xb1_x', 'REALSXP', REALSXP, xb1_x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('nbase', 'INTSXP', INTSXP, nbase, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('ncount', 'INTSXP', INTSXP, ncount, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('global_sumb1_x', 'REALSXP', REALSXP, global_sumb1_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(x)), pchar(arg_x));
    
    arg_xb1_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(xb1_x)), pchar(arg_xb1_x));
    
    arg_nbase := R_INTEGER(nbase)^;
    arg_ncount := R_INTEGER(ncount)^;
    arg_global_sumb1_x := R_REAL(global_sumb1_x)^;
  end
  else
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x, pointer(R_REAL(x)));
    
    arg_xb1_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb1_x, pointer(R_REAL(xb1_x)));
    
    arg_nbase := R_INTEGER(nbase)^;
    arg_ncount := R_INTEGER(ncount)^;
    arg_global_sumb1_x := R_REAL(global_sumb1_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  GLOBAL_SUM_BX(arg_x, arg_xb1_x, arg_nbase, arg_ncount, arg_global_sumb1_x);
  
  if bTranslate then
  begin
    AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_xb1_x), pchar(R_REAL(xb1_x)));
    R_REAL(global_sumb1_x)^ := arg_global_sumb1_x;
  end
  else
  begin
    R_REAL(global_sumb1_x)^ := arg_global_sumb1_x;
  end;
  
  AdtArrayPlan_destroy(_MemAllocator, arg_x);
  AdtArrayPlan_destroy(_MemAllocator, arg_xb1_x);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_GLOBAL_SUM_BX(x : SEXP; xb1_x : SEXP; nbase : SEXP; ncount : SEXP; global_sumb1_x : SEXP) : SEXP;

begin
  Result := R_internal_GLOBAL_SUM_BX(x, xb1_x, nbase, ncount, global_sumb1_x, true);
end;

function R_ArrayTest.R_nt_GLOBAL_SUM_BX(x : SEXP; xb1_x : SEXP; nbase : SEXP; ncount : SEXP; global_sumb1_x : SEXP) : SEXP;

begin
  Result := R_internal_GLOBAL_SUM_BX(x, xb1_x, nbase, ncount, global_sumb1_x, false);
end;

function R_ArrayTest.R_internal_IFTEST_BX(x : SEXP; xb5_x : SEXP; iftestb5_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : double;
  arg_xb5_x : double;
  arg_iftestb5_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('xb5_x', 'REALSXP', REALSXP, xb5_x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('iftestb5_x', 'REALSXP', REALSXP, iftestb5_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := R_REAL(x)^;
    arg_xb5_x := R_REAL(xb5_x)^;
    arg_iftestb5_x := R_REAL(iftestb5_x)^;
  end
  else
  begin
    arg_x := R_REAL(x)^;
    arg_xb5_x := R_REAL(xb5_x)^;
    arg_iftestb5_x := R_REAL(iftestb5_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  IFTEST_BX(arg_x, arg_xb5_x, arg_iftestb5_x);
  
  if bTranslate then
  begin
    R_REAL(xb5_x)^ := arg_xb5_x;
    R_REAL(iftestb5_x)^ := arg_iftestb5_x;
  end
  else
  begin
    R_REAL(xb5_x)^ := arg_xb5_x;
    R_REAL(iftestb5_x)^ := arg_iftestb5_x;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_IFTEST_BX(x : SEXP; xb5_x : SEXP; iftestb5_x : SEXP) : SEXP;

begin
  Result := R_internal_IFTEST_BX(x, xb5_x, iftestb5_x, true);
end;

function R_ArrayTest.R_nt_IFTEST_BX(x : SEXP; xb5_x : SEXP; iftestb5_x : SEXP) : SEXP;

begin
  Result := R_internal_IFTEST_BX(x, xb5_x, iftestb5_x, false);
end;

function R_ArrayTest._get_ix() : SEXP;

begin
  Result := R_Scalar(ix);
end;

function R_ArrayTest._set_ix(arg_ix : SEXP) : SEXP;

begin
  R_CheckArgument('arg_ix', 'INTSXP', INTSXP, arg_ix, {$I %FILE%}, {$I %LINE%});
  
  ix := R_INTEGER(arg_ix)^;
  Result := R_Empty();
end;

function R_ArrayTest._get_iy() : SEXP;

begin
  Result := R_Scalar(iy);
end;

function R_ArrayTest._set_iy(arg_iy : SEXP) : SEXP;

begin
  R_CheckArgument('arg_iy', 'INTSXP', INTSXP, arg_iy, {$I %FILE%}, {$I %LINE%});
  
  iy := R_INTEGER(arg_iy)^;
  Result := R_Empty();
end;

function R_ArrayTest.R_internal_POLYB_BX(x : SEXP; xb3_x : SEXP; polybb3_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : double;
  arg_xb3_x : double;
  arg_polybb3_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('xb3_x', 'REALSXP', REALSXP, xb3_x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('polybb3_x', 'REALSXP', REALSXP, polybb3_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := R_REAL(x)^;
    arg_xb3_x := R_REAL(xb3_x)^;
    arg_polybb3_x := R_REAL(polybb3_x)^;
  end
  else
  begin
    arg_x := R_REAL(x)^;
    arg_xb3_x := R_REAL(xb3_x)^;
    arg_polybb3_x := R_REAL(polybb3_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  POLYB_BX(arg_x, arg_xb3_x, arg_polybb3_x);
  
  if bTranslate then
  begin
    R_REAL(xb3_x)^ := arg_xb3_x;
    R_REAL(polybb3_x)^ := arg_polybb3_x;
  end
  else
  begin
    R_REAL(xb3_x)^ := arg_xb3_x;
    R_REAL(polybb3_x)^ := arg_polybb3_x;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_POLYB_BX(x : SEXP; xb3_x : SEXP; polybb3_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYB_BX(x, xb3_x, polybb3_x, true);
end;

function R_ArrayTest.R_nt_POLYB_BX(x : SEXP; xb3_x : SEXP; polybb3_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYB_BX(x, xb3_x, polybb3_x, false);
end;

function R_ArrayTest.R_internal_POLYB_BX0(x : SEXP; xb5_x : SEXP; polybb5_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : double;
  arg_xb5_x : double;
  arg_polybb5_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('xb5_x', 'REALSXP', REALSXP, xb5_x, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('polybb5_x', 'REALSXP', REALSXP, polybb5_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := R_REAL(x)^;
    arg_xb5_x := R_REAL(xb5_x)^;
    arg_polybb5_x := R_REAL(polybb5_x)^;
  end
  else
  begin
    arg_x := R_REAL(x)^;
    arg_xb5_x := R_REAL(xb5_x)^;
    arg_polybb5_x := R_REAL(polybb5_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  POLYB_BX0(arg_x, arg_xb5_x, arg_polybb5_x);
  
  if bTranslate then
  begin
    R_REAL(xb5_x)^ := arg_xb5_x;
    R_REAL(polybb5_x)^ := arg_polybb5_x;
  end
  else
  begin
    R_REAL(xb5_x)^ := arg_xb5_x;
    R_REAL(polybb5_x)^ := arg_polybb5_x;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_POLYB_BX0(x : SEXP; xb5_x : SEXP; polybb5_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYB_BX0(x, xb5_x, polybb5_x, true);
end;

function R_ArrayTest.R_nt_POLYB_BX0(x : SEXP; xb5_x : SEXP; polybb5_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYB_BX0(x, xb5_x, polybb5_x, false);
end;

function R_ArrayTest.R_internal_polySumA(X : SEXP; bTranslate : boolean) : SEXP;

var
  arg_X : ARRAY_1D;
  
begin
  R_CheckArgument('X', 'REALSXP', REALSXP, X, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  if bTranslate then
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(X)), pchar(arg_X));
    
  end
  else
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X, pointer(R_REAL(X)));
    
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := polySumA(arg_X);
  
  
  AdtArrayPlan_destroy(_MemAllocator, arg_X);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_polySumA(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumA(X, true);
end;

function R_ArrayTest.R_nt_polySumA(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumA(X, false);
end;

function R_ArrayTest.R_internal_POLYSUMA_BX(x : SEXP; xb2_x : SEXP; polysumab2_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : ARRAY_1D;
  arg_xb2_x : ARRAY_1D;
  arg_polysumab2_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('xb2_x', 'REALSXP', REALSXP, xb2_x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('polysumab2_x', 'REALSXP', REALSXP, polysumab2_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(x)), pchar(arg_x));
    
    arg_xb2_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb2_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(xb2_x)), pchar(arg_xb2_x));
    
    arg_polysumab2_x := R_REAL(polysumab2_x)^;
  end
  else
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x, pointer(R_REAL(x)));
    
    arg_xb2_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb2_x, pointer(R_REAL(xb2_x)));
    
    arg_polysumab2_x := R_REAL(polysumab2_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  POLYSUMA_BX(arg_x, arg_xb2_x, arg_polysumab2_x);
  
  if bTranslate then
  begin
    AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_xb2_x), pchar(R_REAL(xb2_x)));
    R_REAL(polysumab2_x)^ := arg_polysumab2_x;
  end
  else
  begin
    R_REAL(polysumab2_x)^ := arg_polysumab2_x;
  end;
  
  AdtArrayPlan_destroy(_MemAllocator, arg_x);
  AdtArrayPlan_destroy(_MemAllocator, arg_xb2_x);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_POLYSUMA_BX(x : SEXP; xb2_x : SEXP; polysumab2_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMA_BX(x, xb2_x, polysumab2_x, true);
end;

function R_ArrayTest.R_nt_POLYSUMA_BX(x : SEXP; xb2_x : SEXP; polysumab2_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMA_BX(x, xb2_x, polysumab2_x, false);
end;

function R_ArrayTest.R_internal_polySumB(X : SEXP; bTranslate : boolean) : SEXP;

var
  arg_X : ARRAY_1D;
  
begin
  R_CheckArgument('X', 'REALSXP', REALSXP, X, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  if bTranslate then
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(X)), pchar(arg_X));
    
  end
  else
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X, pointer(R_REAL(X)));
    
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := polySumB(arg_X);
  
  
  AdtArrayPlan_destroy(_MemAllocator, arg_X);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_polySumB(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumB(X, true);
end;

function R_ArrayTest.R_nt_polySumB(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumB(X, false);
end;

function R_ArrayTest.R_internal_POLYSUMB_BX(x : SEXP; xb3_x : SEXP; polysumbb3_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : ARRAY_1D;
  arg_xb3_x : ARRAY_1D;
  arg_polysumbb3_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('xb3_x', 'REALSXP', REALSXP, xb3_x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('polysumbb3_x', 'REALSXP', REALSXP, polysumbb3_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(x)), pchar(arg_x));
    
    arg_xb3_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb3_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(xb3_x)), pchar(arg_xb3_x));
    
    arg_polysumbb3_x := R_REAL(polysumbb3_x)^;
  end
  else
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x, pointer(R_REAL(x)));
    
    arg_xb3_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb3_x, pointer(R_REAL(xb3_x)));
    
    arg_polysumbb3_x := R_REAL(polysumbb3_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  POLYSUMB_BX(arg_x, arg_xb3_x, arg_polysumbb3_x);
  
  if bTranslate then
  begin
    AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_xb3_x), pchar(R_REAL(xb3_x)));
    R_REAL(polysumbb3_x)^ := arg_polysumbb3_x;
  end
  else
  begin
    R_REAL(polysumbb3_x)^ := arg_polysumbb3_x;
  end;
  
  AdtArrayPlan_destroy(_MemAllocator, arg_x);
  AdtArrayPlan_destroy(_MemAllocator, arg_xb3_x);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_POLYSUMB_BX(x : SEXP; xb3_x : SEXP; polysumbb3_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMB_BX(x, xb3_x, polysumbb3_x, true);
end;

function R_ArrayTest.R_nt_POLYSUMB_BX(x : SEXP; xb3_x : SEXP; polysumbb3_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMB_BX(x, xb3_x, polysumbb3_x, false);
end;

function R_ArrayTest.R_internal_polySumC(X : SEXP; bTranslate : boolean) : SEXP;

var
  arg_X : ARRAY_1D;
  
begin
  R_CheckArgument('X', 'REALSXP', REALSXP, X, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  if bTranslate then
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(X)), pchar(arg_X));
    
  end
  else
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X, pointer(R_REAL(X)));
    
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := polySumC(arg_X);
  
  
  AdtArrayPlan_destroy(_MemAllocator, arg_X);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_polySumC(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumC(X, true);
end;

function R_ArrayTest.R_nt_polySumC(X : SEXP) : SEXP;

begin
  Result := R_internal_polySumC(X, false);
end;

function R_ArrayTest.R_internal_POLYSUMC_BX(x : SEXP; xb4_x : SEXP; polysumcb4_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : ARRAY_1D;
  arg_xb4_x : ARRAY_1D;
  arg_polysumcb4_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('xb4_x', 'REALSXP', REALSXP, xb4_x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('polysumcb4_x', 'REALSXP', REALSXP, polysumcb4_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(x)), pchar(arg_x));
    
    arg_xb4_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb4_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(xb4_x)), pchar(arg_xb4_x));
    
    arg_polysumcb4_x := R_REAL(polysumcb4_x)^;
  end
  else
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x, pointer(R_REAL(x)));
    
    arg_xb4_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb4_x, pointer(R_REAL(xb4_x)));
    
    arg_polysumcb4_x := R_REAL(polysumcb4_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  POLYSUMC_BX(arg_x, arg_xb4_x, arg_polysumcb4_x);
  
  if bTranslate then
  begin
    AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_xb4_x), pchar(R_REAL(xb4_x)));
    R_REAL(polysumcb4_x)^ := arg_polysumcb4_x;
  end
  else
  begin
    R_REAL(polysumcb4_x)^ := arg_polysumcb4_x;
  end;
  
  AdtArrayPlan_destroy(_MemAllocator, arg_x);
  AdtArrayPlan_destroy(_MemAllocator, arg_xb4_x);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_POLYSUMC_BX(x : SEXP; xb4_x : SEXP; polysumcb4_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMC_BX(x, xb4_x, polysumcb4_x, true);
end;

function R_ArrayTest.R_nt_POLYSUMC_BX(x : SEXP; xb4_x : SEXP; polysumcb4_x : SEXP) : SEXP;

begin
  Result := R_internal_POLYSUMC_BX(x, xb4_x, polysumcb4_x, false);
end;

function R_ArrayTest.R_internal_sum(X : SEXP; bTranslate : boolean) : SEXP;

var
  arg_X : ARRAY_1D;
  
begin
  R_CheckArgument('X', 'REALSXP', REALSXP, X, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  if bTranslate then
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(X)), pchar(arg_X));
    
  end
  else
  begin
    arg_X := nil;
    
    Plan_1.create(_MemAllocator, arg_X, pointer(R_REAL(X)));
    
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := sum(arg_X);
  
  
  AdtArrayPlan_destroy(_MemAllocator, arg_X);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_sum(X : SEXP) : SEXP;

begin
  Result := R_internal_sum(X, true);
end;

function R_ArrayTest.R_nt_sum(X : SEXP) : SEXP;

begin
  Result := R_internal_sum(X, false);
end;

function R_ArrayTest.R_internal_SUM_BX(x : SEXP; xb1_x : SEXP; sumb1_x : SEXP; bTranslate : boolean) : SEXP;

var
  arg_x : ARRAY_1D;
  arg_xb1_x : ARRAY_1D;
  arg_sumb1_x : double;
  
begin
  R_CheckArgument('x', 'REALSXP', REALSXP, x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('xb1_x', 'REALSXP', REALSXP, xb1_x, {$I %FILE%}, {$I %LINE%}, 1, [1, ix]);
  
  R_CheckArgument('sumb1_x', 'REALSXP', REALSXP, sumb1_x, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(x)), pchar(arg_x));
    
    arg_xb1_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb1_x);
    
    AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_REAL(xb1_x)), pchar(arg_xb1_x));
    
    arg_sumb1_x := R_REAL(sumb1_x)^;
  end
  else
  begin
    arg_x := nil;
    
    Plan_1.create(_MemAllocator, arg_x, pointer(R_REAL(x)));
    
    arg_xb1_x := nil;
    
    Plan_1.create(_MemAllocator, arg_xb1_x, pointer(R_REAL(xb1_x)));
    
    arg_sumb1_x := R_REAL(sumb1_x)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  SUM_BX(arg_x, arg_xb1_x, arg_sumb1_x);
  
  if bTranslate then
  begin
    AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_xb1_x), pchar(R_REAL(xb1_x)));
    R_REAL(sumb1_x)^ := arg_sumb1_x;
  end
  else
  begin
    R_REAL(sumb1_x)^ := arg_sumb1_x;
  end;
  
  AdtArrayPlan_destroy(_MemAllocator, arg_x);
  AdtArrayPlan_destroy(_MemAllocator, arg_xb1_x);
  Rf_unprotect(1);
end;

function R_ArrayTest.R_SUM_BX(x : SEXP; xb1_x : SEXP; sumb1_x : SEXP) : SEXP;

begin
  Result := R_internal_SUM_BX(x, xb1_x, sumb1_x, true);
end;

function R_ArrayTest.R_nt_SUM_BX(x : SEXP; xb1_x : SEXP; sumb1_x : SEXP) : SEXP;

begin
  Result := R_internal_SUM_BX(x, xb1_x, sumb1_x, false);
end;

function R_ArrayTest.R_internal_sumA1_D(bTranslate : boolean) : SEXP;
begin
  if bTranslate then
  begin
  end
  else
  begin
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := sumA1_D();
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_sumA1_D() : SEXP;

begin
  Result := R_internal_sumA1_D(true);
end;

function R_ArrayTest.R_nt_sumA1_D() : SEXP;

begin
  Result := R_internal_sumA1_D(false);
end;

function R_ArrayTest.R_internal_test_one_if(v : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := test_one_if(arg_v);
  
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_test_one_if(v : SEXP) : SEXP;

begin
  Result := R_internal_test_one_if(v, true);
end;

function R_ArrayTest.R_nt_test_one_if(v : SEXP) : SEXP;

begin
  Result := R_internal_test_one_if(v, false);
end;

function R_ArrayTest.R_internal_TEST_ONE_IF_BV(v : SEXP; vb7_v : SEXP; test_one_ifb7_v : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  arg_vb7_v : double;
  arg_test_one_ifb7_v : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('vb7_v', 'REALSXP', REALSXP, vb7_v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('test_one_ifb7_v', 'REALSXP', REALSXP, test_one_ifb7_v, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
    arg_vb7_v := R_REAL(vb7_v)^;
    arg_test_one_ifb7_v := R_REAL(test_one_ifb7_v)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
    arg_vb7_v := R_REAL(vb7_v)^;
    arg_test_one_ifb7_v := R_REAL(test_one_ifb7_v)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  TEST_ONE_IF_BV(arg_v, arg_vb7_v, arg_test_one_ifb7_v);
  
  if bTranslate then
  begin
    R_REAL(vb7_v)^ := arg_vb7_v;
    R_REAL(test_one_ifb7_v)^ := arg_test_one_ifb7_v;
  end
  else
  begin
    R_REAL(vb7_v)^ := arg_vb7_v;
    R_REAL(test_one_ifb7_v)^ := arg_test_one_ifb7_v;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_TEST_ONE_IF_BV(v : SEXP; vb7_v : SEXP; test_one_ifb7_v : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v, true);
end;

function R_ArrayTest.R_nt_TEST_ONE_IF_BV(v : SEXP; vb7_v : SEXP; test_one_ifb7_v : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_BV(v, vb7_v, test_one_ifb7_v, false);
end;

function R_ArrayTest.R_internal_TEST_ONE_IF_DV(v : SEXP; vd6_v : SEXP; test_one_if : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  arg_vd6_v : double;
  arg_test_one_if : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('vd6_v', 'REALSXP', REALSXP, vd6_v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('test_one_if', 'REALSXP', REALSXP, test_one_if, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
    arg_vd6_v := R_REAL(vd6_v)^;
    arg_test_one_if := R_REAL(test_one_if)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
    arg_vd6_v := R_REAL(vd6_v)^;
    arg_test_one_if := R_REAL(test_one_if)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := TEST_ONE_IF_DV(arg_v, arg_vd6_v, arg_test_one_if);
  
  if bTranslate then
  begin
    R_REAL(test_one_if)^ := arg_test_one_if;
  end
  else
  begin
    R_REAL(test_one_if)^ := arg_test_one_if;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_TEST_ONE_IF_DV(v : SEXP; vd6_v : SEXP; test_one_if : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_DV(v, vd6_v, test_one_if, true);
end;

function R_ArrayTest.R_nt_TEST_ONE_IF_DV(v : SEXP; vd6_v : SEXP; test_one_if : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_DV(v, vd6_v, test_one_if, false);
end;

function R_ArrayTest.R_internal_test_one_if_internal(v : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := test_one_if_internal(arg_v);
  
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_test_one_if_internal(v : SEXP) : SEXP;

begin
  Result := R_internal_test_one_if_internal(v, true);
end;

function R_ArrayTest.R_nt_test_one_if_internal(v : SEXP) : SEXP;

begin
  Result := R_internal_test_one_if_internal(v, false);
end;

function R_ArrayTest.R_internal_TEST_ONE_IF_INTERNAL_BV(v : SEXP; vb9_v : SEXP; test_one_if_internalb9_v : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  arg_vb9_v : double;
  arg_test_one_if_internalb9_v : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('vb9_v', 'REALSXP', REALSXP, vb9_v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('test_one_if_internalb9_v', 'REALSXP', REALSXP, test_one_if_internalb9_v, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
    arg_vb9_v := R_REAL(vb9_v)^;
    arg_test_one_if_internalb9_v := R_REAL(test_one_if_internalb9_v)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
    arg_vb9_v := R_REAL(vb9_v)^;
    arg_test_one_if_internalb9_v := R_REAL(test_one_if_internalb9_v)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := 0.0;
  TEST_ONE_IF_INTERNAL_BV(arg_v, arg_vb9_v, arg_test_one_if_internalb9_v);
  
  if bTranslate then
  begin
    R_REAL(vb9_v)^ := arg_vb9_v;
    R_REAL(test_one_if_internalb9_v)^ := arg_test_one_if_internalb9_v;
  end
  else
  begin
    R_REAL(vb9_v)^ := arg_vb9_v;
    R_REAL(test_one_if_internalb9_v)^ := arg_test_one_if_internalb9_v;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_TEST_ONE_IF_INTERNAL_BV(v : SEXP; vb9_v : SEXP; test_one_if_internalb9_v : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v, true);
end;

function R_ArrayTest.R_nt_TEST_ONE_IF_INTERNAL_BV(v : SEXP; vb9_v : SEXP; test_one_if_internalb9_v : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_INTERNAL_BV(v, vb9_v, test_one_if_internalb9_v, false);
end;

function R_ArrayTest.R_internal_TEST_ONE_IF_INTERNAL_DV(v : SEXP; vd8_v : SEXP; test_one_if_internal : SEXP; bTranslate : boolean) : SEXP;

var
  arg_v : double;
  arg_vd8_v : double;
  arg_test_one_if_internal : double;
  
begin
  R_CheckArgument('v', 'REALSXP', REALSXP, v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('vd8_v', 'REALSXP', REALSXP, vd8_v, {$I %FILE%}, {$I %LINE%});
  
  R_CheckArgument('test_one_if_internal', 'REALSXP', REALSXP, test_one_if_internal, {$I %FILE%}, {$I %LINE%});
  
  if bTranslate then
  begin
    arg_v := R_REAL(v)^;
    arg_vd8_v := R_REAL(vd8_v)^;
    arg_test_one_if_internal := R_REAL(test_one_if_internal)^;
  end
  else
  begin
    arg_v := R_REAL(v)^;
    arg_vd8_v := R_REAL(vd8_v)^;
    arg_test_one_if_internal := R_REAL(test_one_if_internal)^;
  end;
  
  Result := Rf_allocVector(REALSXP, 1);
  
  Rf_protect(Result);
  R_REAL(Result)^ := TEST_ONE_IF_INTERNAL_DV(arg_v, arg_vd8_v, arg_test_one_if_internal);
  
  if bTranslate then
  begin
    R_REAL(test_one_if_internal)^ := arg_test_one_if_internal;
  end
  else
  begin
    R_REAL(test_one_if_internal)^ := arg_test_one_if_internal;
  end;
  
  Rf_unprotect(1);
end;

function R_ArrayTest.R_TEST_ONE_IF_INTERNAL_DV(v : SEXP; vd8_v : SEXP; test_one_if_internal : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal, true);
end;

function R_ArrayTest.R_nt_TEST_ONE_IF_INTERNAL_DV(v : SEXP; vd8_v : SEXP; test_one_if_internal : SEXP) : SEXP;

begin
  Result := R_internal_TEST_ONE_IF_INTERNAL_DV(v, vd8_v, test_one_if_internal, false);
end;
