// -----------------------------------------------------------------------
// RAccess
// -----------------------------------------------------------------------
// Wrapper unit to help access the .Call support api in the R dynamic
// library. This unit assumes that the R library is linked to the project
// using this unit.
// -----------------------------------------------------------------------
unit Raccess;

interface

  uses
    Useful;

  const
    {$ifdef win32}
      R_Lib = 'R.dll';
    {$else}
      R_Lib = 'libR.so';
    {$endif}

    type_adt_tag_name = 'ADT_TYPE_TAG';

  type
{$IFDEF FPC}
{$PACKRECORDS C}
{$ENDIF}
    R_len_t         = longint;
    Rboolean        = longint;
    SEXP            = pointer;

    R_CFinalizer_t  = procedure(P1: SEXP);cdecl;

    Rcomplex        = record
                        r : double;
                        i : double;
                      end;

    PPointer        = ^Pointer;
    PChar           = ^char;
    PRboolean       = ^longint;
    PInteger        = ^longint;
    PDouble         = ^double;
    PRcomplex       = ^Rcomplex;

    CallMethodDef = packed record
      cmdName     : pchar;
      cmdFunc     : Pointer;
      cmdNumArgs  : integer;
    end;

    PCallMethodDef  = ^CallMethodDef;

  var
    type_adt_tag : SEXP = nil;

  procedure R_INIT_TYPE();
  procedure R_CHECK_POINTER(rInstance:SEXP);
  function Rf_asLogical(x:SEXP):longint;cdecl;external R_Lib;
  function Rf_asInteger(x:SEXP):longint;cdecl;external R_Lib;
  function Rf_asReal(x:SEXP):double;cdecl;external R_Lib;
  function Rf_alloc3DArray(_para1:SEXPTYPE; _para2:longint; _para3:longint; _para4:longint):SEXP;cdecl;external R_Lib;
  function Rf_allocArray(_para1:SEXPTYPE; _para2:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_allocMatrix(_para1:SEXPTYPE; _para2:longint; _para3:longint):SEXP;cdecl;external R_Lib;
  function Rf_allocList(_para1:longint):SEXP;cdecl;external R_Lib;
  function Rf_allocVector(_para1:SEXPTYPE; _para2:R_len_t):SEXP;cdecl;external R_Lib;
  function Rf_isFree(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isOrdered(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isUnordered(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isUnsorted(_para1:SEXP; _para2:Rboolean):Rboolean;cdecl;external R_Lib;
  function Rf_ncols(_para1:SEXP):longint;cdecl;external R_Lib;
  function Rf_nrows(_para1:SEXP):longint;cdecl;external R_Lib;
  procedure Rf_PrintValue(_para1:SEXP);cdecl;external R_Lib;
  function Rf_protect(_para1:SEXP):SEXP;cdecl;external R_Lib;
  procedure Rf_unprotect(_para1:longint);cdecl;external R_Lib;
  procedure Rf_unprotect_ptr(_para1:SEXP);cdecl;external R_Lib;
  function Rf_isArray(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isInteger(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isList(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isMatrix(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isNewList(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isLogical(s:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isNull(s:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isNumber(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isNumeric(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isReal(s:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isComplex(s:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isPairList(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isPrimitive(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isVector(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isVectorAtomic(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isVectorList(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_isVectorizable(_para1:SEXP):Rboolean;cdecl;external R_Lib;
  function Rf_length(_para1:SEXP):R_len_t;cdecl;external R_Lib;
  function Rf_listAppend(_para1:SEXP; _para2:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_ScalarComplex(_para1:Rcomplex):SEXP;cdecl;external R_Lib;
  function Rf_ScalarInteger(_para1:longint):SEXP;cdecl;external R_Lib;
  function Rf_ScalarLogical(_para1:longint):SEXP;cdecl;external R_Lib;
  function Rf_ScalarReal(_para1:double):SEXP;cdecl;external R_Lib;
  procedure Rf_error(const s:PChar);cdecl;external R_Lib;varargs;
  procedure Rf_warning(const s:PChar);cdecl;external R_Lib;varargs;

  function Rf_mkChar(const s:PChar):SEXP;cdecl;external R_Lib;
  function Rf_mkCharLen(const s:PChar; n:longint):SEXP;cdecl;external R_Lib;
  function Rf_install(const s:PChar):SEXP;cdecl;external R_Lib;

  function R_MakeExternalPtr(p:Pointer; tag:SEXP; prot:SEXP):SEXP;cdecl;external R_Lib;
  function R_ExternalPtrAddr(s:SEXP):Pointer;cdecl;external R_Lib;
  function R_ExternalPtrTag(s:SEXP):SEXP;cdecl;external R_Lib;
  function R_ExternalPtrProtected(s:SEXP):SEXP;cdecl;external R_Lib;
  procedure R_ClearExternalPtr(s:SEXP);cdecl;external R_Lib;
  procedure R_SetExternalPtrAddr(s:SEXP; p:Pointer);cdecl;external R_Lib;
  procedure R_SetExternalPtrTag(s:SEXP; tag:SEXP);cdecl;external R_Lib;
  procedure R_SetExternalPtrProtected(s:SEXP; p:SEXP);cdecl;external R_Lib;

  procedure R_RegisterFinalizer(s:SEXP; fun:SEXP);cdecl;external R_Lib;
  procedure R_RegisterCFinalizer(s:SEXP; fun:R_CFinalizer_t);cdecl;external R_Lib;
  procedure R_RegisterFinalizerEx(s:SEXP; fun:SEXP; onexit:Rboolean);cdecl;external R_Lib;
  procedure R_RegisterCFinalizerEx(s:SEXP; fun:R_CFinalizer_t; onexit:Rboolean);cdecl;external R_Lib;

  function R_registerRoutines(VAR Dll_info : Pointer;
                              cRoutines: Pointer;
                              callRoutines: PCallMethodDef;
                              fortranRoutines: Pointer;
                              externalRoutines: Pointer):integer; cdecl;external R_Lib;

  function R_DATAPTR(x:SEXP):Pointer;
  function R_CHAR(x:SEXP):PChar;
  function R_LOGICAL(x:SEXP):PRboolean;
  function R_INTEGER(x:SEXP):PInteger;
  function R_REAL(x:SEXP):PDouble;
  function R_COMPLEX(x:SEXP):PRcomplex;

  function p2a(x:SEXP): ARRAY_1D; overload;

implementation

  // ---------------------------------------------------------------------

  procedure R_INIT_TYPE();

  begin
    if (type_adt_tag = nil) then
    begin
      type_adt_tag := Rf_install(type_adt_tag_name);
    end;
  end;

  // ---------------------------------------------------------------------

  procedure R_CHECK_POINTER(rInstance:SEXP);

  begin
    if (R_ExternalPtrTag(rInstance) <> type_adt_tag) then
    begin
      Rf_error('ERROR: rInstance must be a ' + type_adt_tag_name);
    end;
  end;


  // ---------------------------------------------------------------------
  // Header in C for R looks like:
  //
  //  struct VECTOR_SEXPREC
  //  {
  //    unsigned int;
  //    void*;
  //    void*;
  //    void*;
  //    int;
  //    int;
  //  };
  //
  // Therefore:
  //   on 32 bit platforms we have 6 * 4 bytes = 24 byte header
  //
  //   on 64 bit windows pointers are 8 bytes but the rest remain as is
  //   giving 3 * 4 + 3 * 8 bytes = 36. However we need to align on 8
  //   byte boundaries so that equates to 40 bytes.
  //
  //   on 64 bit linux we have 6 * 8 = 48 byte header

  function R_DATAPTR(x:SEXP):Pointer;

  begin
  {$IFDEF CPU32}
    R_DATAPTR := Pointer(PtrUInt(x) + 24);
  {$ELSE}
    {$IFDEF CPU64}
      {$IFDEF WINDOWS}
    R_DATAPTR := Pointer(PtrUInt(x) + 40);
      {$ELSE}
    R_DATAPTR := Pointer(PtrUInt(x) + 48);
      {$ENDIF}
    {$ELSE}
      {$ERROR Un-supported target!}
    R_DATAPTR := 0;
    {$ENDIF}
  {$ENDIF}
  end;

  // ---------------------------------------------------------------------

  function R_CHAR(x:SEXP):PChar;

  begin
    R_CHAR := PChar(R_DATAPTR(x));
  end;

  // ---------------------------------------------------------------------

  function R_LOGICAL(x:SEXP):PRboolean;

  begin
    R_LOGICAL := PRboolean(R_DATAPTR(x));
  end;

  // ---------------------------------------------------------------------

  function R_INTEGER(x:SEXP):PInteger;

  begin
    R_INTEGER := PInteger(R_DATAPTR(x));
  end;

  // ---------------------------------------------------------------------

  function R_REAL(x:SEXP):PDouble;

  begin
    R_REAL := PDouble(R_DATAPTR(x));
  end;

  // ---------------------------------------------------------------------

  function R_COMPLEX(x:SEXP):PRcomplex;

  begin
    R_COMPLEX := PRcomplex(R_DATAPTR(x));
  end;

  // ---------------------------------------------------------------------


  function p2a(x:SEXP): ARRAY_1D; overload;

  begin
    p2a := ARRAY_1D(R_DATAPTR(x));
  end;

end.
