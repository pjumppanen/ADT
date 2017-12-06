
Procedure AT_destroy_handler(rInstance : SEXP); cdecl;
begin
  R_CHECK_POINTER(rInstance);
  
  if (R_ExternalPtrAddr(rInstance) <> Null) then
  begin
    R_ArrayTest(R_ExternalPtrAddr(rInstance)).Destroy;
  end;
  
  R_ClearExternalPtr(rInstance);
end;

Function AT_destroy(rInstance : SEXP) : SEXP; cdecl;
begin
  AT_destroy_handler(rInstance);
  
  AT_destroy := rInstance;
end;

function AT_create(
    arg_ix, 
    arg_iy, 
    arg_A1_I, 
    arg_A1_D, 
    arg_A2_IA, 
    arg_A2_IB : SEXP) : SEXP; cdecl;

var
  Context : R_ArrayTest;

begin
  if (Rf_isInteger(arg_ix) = 0) then
  begin
    Rf_error('ERROR: arg_ix must be of type INTSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  if (Rf_isInteger(arg_iy) = 0) then
  begin
    Rf_error('ERROR: arg_iy must be of type INTSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  if (Rf_isInteger(arg_A1_I) = 0) then
  begin
    Rf_error('ERROR: arg_A1_I must be of type INTSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  if (Rf_isReal(arg_A1_D) = 0) then
  begin
    Rf_error('ERROR: arg_A1_D must be of type REALSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  if (Rf_isInteger(arg_A2_IA) = 0) then
  begin
    Rf_error('ERROR: arg_A2_IA must be of type INTSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  if (Rf_isInteger(arg_A2_IB) = 0) then
  begin
    Rf_error('ERROR: arg_A2_IB must be of type INTSXP. See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});
  end;
  
  Context := R_ArrayTest.create(
      R_INTEGER(arg_ix)^, 
      R_INTEGER(arg_iy)^, 
      R_INTEGER(arg_A1_I), 
      R_REAL(arg_A1_D), 
      R_INTEGER(arg_A2_IA), 
      R_INTEGER(arg_A2_IB));
  
  R_INIT_TYPE();
  
  Result := R_MakeExternalPtr(Pointer(Context), type_adt_tag, Rf_mkChar('TUsefulClass'));
  
  Rf_protect(Result);
  R_RegisterCFinalizer(Result, AT_destroy_handler);
  Rf_unprotect(1);
end;
