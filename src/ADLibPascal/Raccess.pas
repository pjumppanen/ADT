// -----------------------------------------------------------------------
// Raccess
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
// -----------------------------------------------------------------------
// Wrapper unit to help access the .Call support api in the R dynamic
// library. This unit assumes that the R library is linked to the project
// using this unit.
// -----------------------------------------------------------------------
{$mode objfpc}{$H+}
unit Raccess;

interface

  uses
    Math;

  const
    {$ifdef win32}
      R_Lib = 'R.dll';
    {$else}
      R_Lib = 'libR.so';
    {$endif}

    type_adt_tag_name = 'ADT_TYPE_TAG';

    M_E             = 2.718281828459045235360287471353; //e
    M_LOG2E         = 1.442695040888963407359924681002; // log2(e)
    M_LOG10E        = 0.434294481903251827651128918917; // log10(e)
    M_LN2           = 0.693147180559945309417232121458; // ln(2)
    M_LN10          = 2.302585092994045684017991454684; // ln(10)
    M_PI            = 3.141592653589793238462643383280; // pi
    M_2PI           = 6.283185307179586476925286766559; // 2*pi
    M_PI_2          = 1.570796326794896619231321691640; // pi/2
    M_PI_4          = 0.785398163397448309615660845820; // pi/4
    M_1_PI          = 0.318309886183790671537767526745; // 1/pi
    M_2_PI		      = 0.636619772367581343075535053490; // 2/pi
    M_2_SQRTPI      = 1.128379167095512573896158903122; // 2/sqrt(pi)
    M_SQRT2         = 1.414213562373095048801688724210; // sqrt(2)
    M_SQRT1_2       = 0.707106781186547524400844362105; // 1/sqrt(2)
    M_SQRT_3        = 1.732050807568877293527446341506; // sqrt(3)
    M_SQRT_32       = 5.656854249492380195206754896838; // sqrt(32)
    M_LOG10_2       = 0.301029995663981195213738894724; // log10(2)
    M_SQRT_PI       = 1.772453850905516027298167483341; // sqrt(pi)
    M_1_SQRT_2PI    = 0.398942280401432677939946059934; // 1/sqrt(2pi)
    M_SQRT_2dPI     = 0.797884560802865355879892119869; // sqrt(2/pi)
    M_LN_SQRT_PI    = 0.572364942924700087071713675677; // log(sqrt(pi))
    M_LN_SQRT_2PI   = 0.918938533204672741780329736406; // log(sqrt(2*pi))
    M_LN_SQRT_PId2  = 0.225791352644727432363097614947; // log(sqrt(pi/2))
    INF             = Infinity;
    MINF            = NegInfinity;
    QNaN            = NaN;

  type
    // -----------------------------------------------------------------------
    //  enum SEXPTYPE
    // -----------------------------------------------------------------------
    SEXPTYPE  = (NILSXP	    = 0,	  // nil = NULL
                 SYMSXP	    = 1,	  // symbols
                 LISTSXP	  = 2,	  // lists of dotted pairs
                 CLOSXP	    = 3,	  // closures
                 ENVSXP	    = 4,	  // environments
                 PROMSXP	  = 5,	  // promises: [un]evaluated closure arguments
                 LANGSXP	  = 6,	  // language constructs (special lists)
                 SPECIALSXP	= 7,	  // special forms
                 BUILTINSXP	= 8,	  // builtin non-special forms
                 CHARSXP	  = 9,	  // "scalar" string type (internal only)
                 LGLSXP	    = 10,	  // logical vectors
                 INTSXP	    = 13,	  // integer vectors
                 REALSXP	  = 14,	  // real variables
                 CPLXSXP	  = 15,	  // complex variables
                 STRSXP	    = 16,	  // string vectors
                 DOTSXP	    = 17,	  // dot-dot-dot object
                 ANYSXP	    = 18,	  // make "any" args work
                 VECSXP	    = 19,	  // generic vectors
                 EXPRSXP	  = 20,	  // expressions vectors
                 BCODESXP	  = 21,	  // byte code
                 EXTPTRSXP	= 22,	  // external pointer
                 WEAKREFSXP	= 23,	  // weak reference
                 RAWSXP	    = 24,	  // raw bytes
                 S4SXP	    = 25,	  // S4 non-vector
                 NEWSXP     = 30,   // fresh node creaed in new page
                 FREESXP    = 31,   // node released by GC
                 FUNSXP	    = 99);	// Closure or Builtin

{$IFDEF FPC}
{$PACKRECORDS C}
{$ENDIF}
    R_len_t         = longint;
    Rboolean        = longint;
    SEXP            = pointer;
    PSEXP           = ^SEXP;

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
    PRbyte          = ^byte;

    CallMethodDef = packed record
      cmdName     : pchar;
      cmdFunc     : Pointer;
      cmdNumArgs  : integer;
    end;

    PCallMethodDef  = ^CallMethodDef;

  threadvar
    last_exp_x            : double;
    last_exp_result       : double;
    last_inv_x            : double;
    last_inv_result       : double;
    last_inv_logit_x      : double;
    last_inv_logit_result : double;

  var
    type_adt_tag : SEXP = nil;

  procedure R_INIT_TYPE();
  procedure R_CHECK_POINTER(rInstance:SEXP);

  function R_ATTRIB(x:SEXP):SEXP;cdecl;external R_Lib name 'ATTRIB';
  function R_OBJECT(x:SEXP):longint;cdecl;external R_Lib name 'OBJECT';
  function R_MARK(x:SEXP):longint;cdecl;external R_Lib name 'MARK';
  function R_TYPEOF(x:SEXP):SEXPTYPE;cdecl;external R_Lib name 'TYPEOF';
  function R_NAMED(x:SEXP):longint;cdecl;external R_Lib name 'NAMED';
  procedure R_SET_OBJECT(x:SEXP;v:longint);cdecl;external R_Lib name 'SET_OBJECT';
  procedure R_SET_TYPEOF(x:SEXP;v:longint);cdecl;external R_Lib name 'SET_TYPEOF';
  procedure R_SET_NAMED(x:SEXP;v:longint);cdecl;external R_Lib name 'SET_NAMED';
  procedure R_SET_ATTRIB(x,v:SEXP);cdecl;external R_Lib name 'SET_ATTRIB';
  procedure R_DUPLICATE_ATTRIB(sto,sfrom:SEXP);cdecl;external R_Lib name 'DUPLICATE_ATTRIB';
  function R_IS_S4_OBJECT(x:SEXP):longint;cdecl;external R_Lib name 'IS_S4_OBJECT';
  procedure R_SET_S4_OBJECT(x:SEXP);cdecl;external R_Lib name 'SET_S4_OBJECT';
  procedure R_UNSET_S4_OBJECT(x:SEXP);cdecl;external R_Lib name 'UNSET_S4_OBJECT';
  function R_LENGTH(x:SEXP):longint;cdecl;external R_Lib name 'LENGTH';
  function R_TRUELENGTH(x:SEXP):longint;cdecl;external R_Lib name 'TRUELENGTH';
  procedure R_SETLENGTH(x:SEXP;v:longint);cdecl;external R_Lib name 'SETLENGTH';
  procedure R_SET_TRUELENGTH(x:SEXP;v:longint);cdecl;external R_Lib name 'SET_TRUELENGTH';
  function R_LEVELS(x:SEXP):longint;cdecl;external R_Lib name 'LEVELS';
  function R_SETLEVELS(x:SEXP;v:longint):longint;cdecl;external R_Lib name 'SETLEVELS';
  function R_LOGICAL(x:SEXP):PInteger;cdecl;external R_Lib name 'LOGICAL';
  function R_INTEGER(x:SEXP):PInteger;cdecl;external R_Lib name 'INTEGER';
  function R_RAW(x:SEXP):PRbyte;cdecl;external R_Lib name 'RAW';
  function R_REAL(x:SEXP):PDouble;cdecl;external R_Lib name 'REAL';
  function R_COMPLEX(x:SEXP):PRcomplex;cdecl;external R_Lib name 'COMPLEX';
  function R_STRING_ELT(x:SEXP;i:longint):SEXP;cdecl;external R_Lib name 'STRING_ELT';
  function R_VECTOR_ELT(x:SEXP;i:longint):SEXP;cdecl;external R_Lib name 'VECTOR_ELT';
  procedure R_SET_STRING_ELT(x:SEXP;i:longint;v:SEXP);cdecl;external R_Lib name 'SET_STRING_ELT';
  function R_SET_VECTOR_ELT(x:SEXP;i:longint;v:SEXP):SEXP;cdecl;external R_Lib name 'SET_VECTOR_ELT';
  function R_STRING_PTR(x:SEXP):PSEXP;cdecl;external R_Lib name 'STRING_PTR';
  function R_VECTOR_PTR(x:SEXP):PSEXP;cdecl;external R_Lib name 'VECTOR_PTR';
  function R_TAG(e:SEXP):SEXP;cdecl;external R_Lib name 'TAG';
  function R_CAR(e:SEXP):SEXP;cdecl;external R_Lib name 'CAR';
  function R_CDR(e:SEXP):SEXP;cdecl;external R_Lib name 'CDR';
  function R_CAAR(e:SEXP):SEXP;cdecl;external R_Lib name 'CAAR';
  function R_CDAR(e:SEXP):SEXP;cdecl;external R_Lib name 'CDAR';
  function R_CADR(e:SEXP):SEXP;cdecl;external R_Lib name 'CADR';
  function R_CDDR(e:SEXP):SEXP;cdecl;external R_Lib name 'CDDR';
  function R_CADDR(e:SEXP):SEXP;cdecl;external R_Lib name 'CADDR';
  function R_CADDDR(e:SEXP):SEXP;cdecl;external R_Lib name 'CADDDR';
  function R_CAD4R(e:SEXP):SEXP;cdecl;external R_Lib name 'CAD4R';
  function R_MISSING(x:SEXP):longint;cdecl;external R_Lib name 'MISSING';
  procedure R_SET_MISSING(x:SEXP;v:longint);cdecl;external R_Lib name 'SET_MISSING';
  procedure R_SET_TAG(x,y:SEXP);cdecl;external R_Lib name 'SET_TAG';
  function R_SETCAR(x,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCAR';
  function R_SETCDR(x,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCDR';
  function R_SETCADR(x,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCADR';
  function R_SETCADDR(x,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCADDR';
  function R_SETCADDDR(x,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCADDDR';
  function R_SETCAD4R(e,y:SEXP):SEXP;cdecl;external R_Lib name 'SETCAD4R';

  function Rf_classgets(x:SEXP;y:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_dimgets(x:SEXP;y:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_dimnamesgets(x:SEXP;y:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_duplicate(x:SEXP):SEXP;cdecl;external R_Lib;
  function Rf_setAttrib(x:SEXP;y:SEXP;z:SEXP):SEXP;cdecl;external R_Lib;
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


  //  ----------------------------------------------------------------------------
  //  R math routines plus some others
  //  ----------------------------------------------------------------------------

  function R_pow(x, y : double):double;cdecl;external R_Lib;
  function R_pow_di(x : double; y : longint):double;cdecl;external R_Lib;
  function finite(x : double) : boolean;cdecl;external R_Lib name 'R_finite';

  //  ----------------------------------------------------------------------------

  function expm1(const x : double) : double;
  function log1p(const x : double) : double;
  function isinf(const x : double) : boolean;
  function sign(const x : double) : double;
  function inv(const x : double) : double;
  function trunc_to_int(const x : double) : longint;
  function round_to_int(const x : double) : longint;
  function pwr(const x : double; const y : single) : double ; overload;
  function pwr(const x : double; const y : double) : double ; overload;
  function pwr(const x : double; const y : shortint) : double ; overload;
  function pwr(const x : double; const y : smallint) : double ; overload;
  function pwr(const x : double; const y : longint) : double ; overload;
  function pwr(const x : double; const y : byte) : double ; overload;
  function pwr(const x : double; const y : word) : double ; overload;
  function pwr(const x : double; const y : longword) : double ; overload;
  function logit(const x : double) : double;
  function inv_logit(const x : double) : double;
  function scal_logit(const x : double) : double;
  function scal_inv_logit(const x : double) : double;
  function dinv_logit(const x : double) : double;
  function LIL(const x : double) : double;
  function rel_delta(const a, b : double) : double;

  // ----------------------------------------------------------------------------

  function exp_cached(const x : double) : double;
  function inv_cached(const x : double) : double;
  function inv_logit_cached(const x : double) : double;


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

  // ----------------------------------------------------------------------------

  function expm1(const x : double) : double ; inline;

  begin
    expm1 := exp(x) - 1.0;
  end;

  // ----------------------------------------------------------------------------

  function log1p(const x : double) : double ; inline;

  begin
    log1p := lnxp1(x);
  end;

  // ----------------------------------------------------------------------------

  function isinf(const x : double) : boolean ; inline;

  begin
    isinf := (not isnan(x)) and (not finite(x));
  end;

  // ----------------------------------------------------------------------------

  function sign(const x : double) : double ; inline;

  begin
    if x = 0 then
      sign := 0.0
    else
    begin
      if x < 0 then
        sign := -1.0
      else
        sign := 1.0;
    end;
  end;

  // ----------------------------------------------------------------------------

  function inv(const x : double) : double ; inline;

  begin
    inv := 1.0 / x;
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : single) : double ; overload ; inline;

  var
    dy : double;

  begin
    dy  := double(y);
    pwr := R_pow(x, dy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : double) : double ; overload ; inline;

  begin
    pwr := R_pow(x, y);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : shortint) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : smallint) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : longint) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : byte) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : word) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function pwr(const x : double; const y : longword) : double ; overload ; inline;

  var
    iy : longint;

  begin
    iy  := longint(y);
    pwr := R_pow_di(x, iy);
  end;

  // ----------------------------------------------------------------------------

  function trunc_to_int(const x : double) : longint;

  begin
    trunc_to_int := longint(floor(x));
  end;

  // ----------------------------------------------------------------------------

  function round_to_int(const x : double) : longint;

  begin
    round_to_int := longint(floor(x + 0.5));
  end;

  // ----------------------------------------------------------------------------

  function logit(const x : double) : double;

  begin
    if x = 0 then
      logit := MINF
    else
    begin
      if x = 1 then
        logit := INF
      else
        logit := ln(x / (1.0 - x));
    end;
  end;

  // ----------------------------------------------------------------------------

  function inv_logit(const x : double) : double;

  begin
    // roughly log( double_neg_eps), but this is exact
    if x < -36.7363124075975981959901 then
      inv_logit := 1.0
    else
      inv_logit := 1.0 / (1.0 + exp(-x));
  end;

  // ----------------------------------------------------------------------------

  function scal_logit(const x : double) : double;

  begin
    scal_logit := logit(0.5 + (255.0 / 256.0) * (x - 0.5));
  end;

  // ----------------------------------------------------------------------------

  function scal_inv_logit(const x : double) : double;

  begin
    scal_inv_logit := ((1.0 + 255.0 * inv_logit(x)) / 256.0);
  end;

  // ----------------------------------------------------------------------------

  function dinv_logit(const x : double) : double;

  var
    y : double;

  begin
    if x > 88.0 then
      dinv_logit := 0.0
    else
    begin
      y           := 1.0 / (1.0 + exp(x));
      dinv_logit  := y * (1.0 - y);
    end;
  end;

  // ----------------------------------------------------------------------------

  function LIL(const x : double) : double;

  begin
    if x < 0 then
      LIL := x - log1p(exp(x))
    else
      LIL := -log1p(exp(-x));
  end;

  // ----------------------------------------------------------------------------

  function exp_cached(const x : double) : double;

  begin
    if x = last_exp_x then
      exp_cached      := last_exp_result
    else
    begin
      last_exp_result := exp(x);
      last_exp_x      := x;
      exp_cached      := last_exp_result;
    end;
  end;

  // ----------------------------------------------------------------------------

  function inv_cached(const x : double) : double;

  begin
    if x = last_inv_x then
      inv_cached      := last_inv_result
    else
    begin
      last_inv_result := 1.0 / x;
      last_inv_x      := x;
      inv_cached      := last_inv_result;
    end;
  end;

  // ----------------------------------------------------------------------------

  function inv_logit_cached(const x : double) : double;

  begin
    if x = last_inv_logit_x then
      inv_logit_cached      := last_inv_logit_result
    else
    begin
      last_inv_logit_result := inv_logit(x);
      last_inv_logit_x      := x;
      inv_logit_cached      := last_inv_logit_result;
    end;
  end;

  // ----------------------------------------------------------------------------

  function rel_delta(const a, b : double) : double;

  var
    dMaxAbs : double;

  begin
    if a = b then
      rel_delta := 0.0
    else
    begin
      dMaxAbs := max(abs(a), abs(b));

      if (dMaxAbs > 0) and (dMaxAbs < INF) then
        rel_delta := abs(a - b) / dMaxAbs
      else
      begin
        if dMaxAbs = 0 then
          rel_delta := INF
        else
          rel_delta := sign(a - b);
      end;
    end;
  end;


initialization
  last_exp_x            := 0.0;
  last_exp_result       := 1.0;
  last_inv_x            := 1.0;
  last_inv_result       := 1.0;
  last_inv_logit_x      := 0.0;
  last_inv_logit_result := 0.5;


end.
