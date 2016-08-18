unit useful;

{$IFDEF FPC}
  {$MODE DELPHI}
{$ENDIF}

interface

TYPE
  PQWORD = ^Int64;
  PPOINTER = ^POINTER;
  PZPOINTER_ARRAY = ^ZPOINTER_ARRAY;
  ZPOINTER_ARRAY = ARRAY[ 0..99] OF PZPOINTER_ARRAY;
  ARRAY_1P = PZPOINTER_ARRAY;

  PARRAY_1P = ^ARRAY_1P;

  LONGINT_ARRAY = ARRAY[1..99] OF LONGINT;
  PLONGINT_ARRAY = ^LONGINT_ARRAY;
  ZLONGINT_array = ARRAY[ 0..99] OF LONGINT;
  PZLONGINT_array = ^ZLONGINT_array;

  SHORTINT_ARRAY = ARRAY[1..99] OF SHORTINT;
  PSHORTINT_ARRAY = ^SHORTINT_ARRAY;
  ZSHORTINT_array = ARRAY[ 0..99] OF SHORTINT;
  PZSHORTINT_array = ^ZSHORTINT_array;

  BOOLEAN_ARRAY = ARRAY[ 1..99] OF LONGBOOL;
  PBOOLEAN_ARRAY = ^BOOLEAN_ARRAY;
  ZBOOLEAN_ARRAY = ARRAY[ 0..99] OF LONGBOOL;
  PZBOOLEAN_ARRAY = ^ZBOOLEAN_ARRAY;

  SINGLE_ARRAY = ARRAY[ 1..99] OF SINGLE;
  PSINGLE_ARRAY = ^SINGLE_array;
  ZSINGLE_ARRAY = ARRAY[ 0..99] OF SINGLE;
  PZSINGLE_ARRAY = ^ZSINGLE_array;

  STRING_ARRAY = ARRAY[ 1..99] OF STRING;
  PSTRING_ARRAY = ^STRING_array;
  ZSTRING_ARRAY = ARRAY[ 0..99] OF STRING;
  PZSTRING_ARRAY = ^ZSTRING_array;

  BYTE_ARRAY = ARRAY[1..99] OF BYTE;
  PBYTE_ARRAY = ^BYTE_ARRAY;
  ZBYTE_ARRAY = ARRAY[ 0..99] OF BYTE;
  PZBYTE_ARRAY = ^ZBYTE_array;

  // The preferred way of adding dimensions is:
  ARRAY_1L = PZLONGINT_ARRAY;
    ZAR_ARRAY_1L = ARRAY[ 0..99] OF ARRAY_1L;
  ARRAY_2L = ^ZAR_ARRAY_1L;
    ZAR_ARRAY_2L = ARRAY[ 0..99] OF ARRAY_2L;
  ARRAY_3L = ^ZAR_ARRAY_2L;
    ZAR_ARRAY_3L = ARRAY[ 0..99] OF ARRAY_3L;
  ARRAY_4L = ^ZAR_ARRAY_3L;

  ARRAY_1B = PZBOOLEAN_ARRAY;
    ZAR_ARRAY_1B = ARRAY[ 0..99] OF ARRAY_1B;
  ARRAY_2B = ^ZAR_ARRAY_1B;
    ZAR_ARRAY_2B = ARRAY[ 0..99] OF ARRAY_2B;
  ARRAY_3B = ^ZAR_ARRAY_2B;

  ARRAY_1SHINT = PZSHORTINT_ARRAY;
    ZAR_ARRAY_1SHINT = ARRAY[ 0..99] OF ARRAY_1SHINT;
  ARRAY_2SHINT = ^ZAR_ARRAY_1SHINT;

  ARRAY_1S = PZSINGLE_ARRAY;
    ZAR_ARRAY_1S = ARRAY[ 0..99] OF ARRAY_1S;
  ARRAY_2S = ^ZAR_ARRAY_1S;
    ZAR_ARRAY_2S = ARRAY[ 0..99] OF ARRAY_2S;
  ARRAY_3S = ^ZAR_ARRAY_2S;
    ZAR_ARRAY_3S = ARRAY[ 0..99] OF ARRAY_3S;
  ARRAY_4S = ^ZAR_ARRAY_3S;
    ZAR_ARRAY_4S = ARRAY[ 0..99] OF ARRAY_4S;
  ARRAY_5S = ^ZAR_ARRAY_4S;

  ARRAY_1STR = PZSTRING_ARRAY;
    ZAR_ARRAY_1STR = ARRAY[ 0..99] OF ARRAY_1STR;
  ARRAY_2STR = ^ZAR_ARRAY_1STR;
    ZAR_ARRAY_2STR = ARRAY[ 0..99] OF ARRAY_2STR;
  ARRAY_3STR = ^ZAR_ARRAY_2STR;

  ARRAY_1BYTE = PZBYTE_ARRAY;
    ZAR_ARRAY_1BYTE = ARRAY[ 0..99] OF ARRAY_1BYTE;
  ARRAY_2BYTE = ^ZAR_ARRAY_1BYTE;
    ZAR_ARRAY_2BYTE = ARRAY[ 0..99] OF ARRAY_2BYTE;
  ARRAY_3BYTE = ^ZAR_ARRAY_2BYTE;

  ZQWORD_ARRAY = ARRAY[ 0..99] OF Int64;
  PZQWORD_ARRAY = ^ZQWORD_array;

  ARRAY_1Q = PZQWORD_ARRAY;
    ZAR_ARRAY_1Q = ARRAY[ 0..99] OF ARRAY_1Q;
  ARRAY_2Q = ^ZAR_ARRAY_1Q;
    ZAR_ARRAY_2Q = ARRAY[ 0..99] OF ARRAY_2Q;
  ARRAY_3Q = ^ZAR_ARRAY_2Q;

  DOUBLE_ARRAY = ARRAY[1..99] OF DOUBLE;
  PDOUBLE_ARRAY = ^DOUBLE_ARRAY;
  ZDOUBLE_ARRAY = ARRAY[ 0..99] OF DOUBLE;
  PZDOUBLE_ARRAY = ^ZDOUBLE_ARRAY;
  AR_PZDOUBLE_ARRAY = ARRAY[ 0..99] OF PZDOUBLE_ARRAY;
  PAR_PZDOUBLE_ARRAY = ^AR_PZDOUBLE_ARRAY;

  ARRAY_1D = PZDOUBLE_ARRAY;
  ARRAY_2D = PAR_PZDOUBLE_ARRAY;
    AR_PAR_PZDOUBLE_ARRAY = ARRAY[ 0..99] OF PAR_PZDOUBLE_ARRAY;
    PAR_PAR_PZDOUBLE_ARRAY = ^AR_PAR_PZDOUBLE_ARRAY;
  ARRAY_3D = PAR_PAR_PZDOUBLE_ARRAY;
    ZAR_PARRAY_3D = ARRAY[ 0..99] OF ARRAY_3D;
  ARRAY_4D = ^ZAR_PARRAY_3D;
    ZAR_PARRAY_4D = ARRAY[ 0..99] OF ARRAY_4D;
  ARRAY_5D = ^ZAR_PARRAY_4D;

  ppalloc_record = ^palloc_record;
  palloc_record = ^alloc_record;
  alloc_record =
    RECORD
      nb: INTEGER;
      where, nominal: POINTER;
      nd, size_of_el: INTEGER; // for arrays only
      dims, first_el: PLONGINT_ARRAY; // ditto
      objptr: TObject;
      next: palloc_record;
    END;

  Teasy_alloc_object=
  CLASS( TObject)
      alloc_list: palloc_record;
      alloc_record_size: WORD;
      DSS, def_stacksize: INTEGER;
      CONSTRUCTOR create;
      FUNCTION alloc(
          n_bytes: INTEGER):
        POINTER; OVERLOAD;
      FUNCTION alloc(
          n_els, size_of_el, first_el: INTEGER):
        POINTER; OVERLOAD;
      FUNCTION alloc(
          variables: ARRAY OF PPOINTER;
          n_els, size_of_el, first_el: INTEGER):
        POINTER; OVERLOAD;
      FUNCTION alloc( obj: POINTER): POINTER; OVERLOAD;
      FUNCTION alloc_array(
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
      FUNCTION alloc_array(
           _nd: INTEGER;
           _dims, _first_el: PLONGINT_ARRAY;
           _size_of_el: INTEGER):
         POINTER; OVERLOAD;
      FUNCTION alloc_array(
           existing_array: POINTER;
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
      FUNCTION alloc_array(
           existing_array: POINTER;
           nd: INTEGER;
           dims, first_el: PLONGINT_ARRAY;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
      FUNCTION find_array_specs(
           CONST existing_array: POINTER):
         palloc_record;
      PROCEDURE alloc_same_shape(
           variables: ARRAY OF PARRAY_1P;
           CONST existing_array: POINTER);
      PROCEDURE alloc_same_shape2(
           variables: ARRAY OF PARRAY_1P;
           VAR existing_firstel);
      PROCEDURE alloc_same_shape_guts(
           variables: ARRAY OF PARRAY_1P;
           CONST ar: ppalloc_record);
      FUNCTION alloc_arrays(
           variables: ARRAY OF PPOINTER;
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER):
        POINTER; OVERLOAD;
      FUNCTION alloc_arrays(
           variables: ARRAY OF PPOINTER;
           nd: INTEGER;
           dims, first_el: PLONGINT_ARRAY;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
       FUNCTION alloc_stack(
           CONST stack_size, size_of_el: INTEGER):
         POINTER;
       PROCEDURE alloc_stacks(
           CONST variables: ARRAY OF PPOINTER;
           CONST  stack_size, size_of_el: INTEGER);
       FUNCTION enum(
           variables: ARRAY OF PLONGINT):
         INTEGER;
       FUNCTION card(
           stuff: ARRAY OF CONST):
         INTEGER;
       FUNCTION realloc(
           ar, target: POINTER):
         POINTER; OVERLOAD;
       PROCEDURE ensure_enough_stack(
           VAR stack: ARRAY_1L;
           CONST needed: INTEGER); OVERLOAD;
       PROCEDURE ensure_enough_stack(
           VAR stack: ARRAY_1D;
           CONST needed: INTEGER); OVERLOAD;
       PROCEDURE ensure_enough_stack(
           VAR stack: ARRAY_1B;
           CONST needed: INTEGER); OVERLOAD;
       PROCEDURE double_stack_length(
           VAR stack: ARRAY_1L); OVERLOAD;
       PROCEDURE double_stack_length(
           VAR stack: ARRAY_1D); OVERLOAD;
       PROCEDURE double_stack_length(
           VAR stack: ARRAY_1B); OVERLOAD;
       FUNCTION realloc(
           ar: POINTER;
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER; target: POINTER):
         POINTER; OVERLOAD;
       FUNCTION realloc(
           ar: POINTER;
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
       FUNCTION realloc_arrays(
           variables: ARRAY OF PPOINTER;
           dims, first_el: ARRAY OF INTEGER;
           size_of_el: INTEGER):
         POINTER; OVERLOAD;
       PROCEDURE init(
         CONST ar: ARRAY_1L;
         CONST val: INTEGER); OVERLOAD;
       PROCEDURE init(
         CONST ar: ARRAY_2L;
         CONST val: INTEGER); OVERLOAD;
       PROCEDURE init(
         CONST ar: ARRAY_1D;
         CONST val: DOUBLE); OVERLOAD;
       PROCEDURE init(
         CONST ar: ARRAY_2D;
         CONST val: DOUBLE); OVERLOAD;
       PROCEDURE init(
         CONST ar: ARRAY_3D;
         CONST val: DOUBLE); OVERLOAD;
       FUNCTION stget(
           VAR stack: ARRAY_1D;
           CONST stacki: INTEGER):
         DOUBLE; OVERLOAD; // INLINE;
       FUNCTION stget(
           VAR stack: ARRAY_1L;
           CONST stacki: INTEGER):
         LONGINT; OVERLOAD; // INLINE;
       FUNCTION stget(
           VAR stack: ARRAY_1B;
           CONST stacki: INTEGER):
         BOOLEAN; OVERLOAD; // INLINE;
       PROCEDURE stget2(
           VAR   x: DOUBLE;
           VAR stack: ARRAY_1D;
           CONST stacki: INTEGER); OVERLOAD; INLINE;
       PROCEDURE stset(
           VAR stack: ARRAY_1D;
           CONST stacki: INTEGER;
           CONST val: DOUBLE); OVERLOAD; // INLINE;
       PROCEDURE stset(
           VAR stack: ARRAY_1L;
           CONST stacki: INTEGER;
           CONST val: LONGINT); OVERLOAD; // INLINE;
       PROCEDURE stset(
           VAR stack: ARRAY_1B;
           CONST stacki: INTEGER;
           CONST val: LONGBOOL); OVERLOAD; // INLINE;
       PROCEDURE dealloc(
           variables: ARRAY OF PPOINTER); OVERLOAD;
       PROCEDURE dealloc(
           p: POINTER); OVERLOAD;
       DESTRUCTOR Destroy; OVERRIDE;
     END;

FUNCTION add_to(
    VAR i: INTEGER;
        v: INTEGER):INTEGER; INLINE;

FUNCTION add_one_to(
    VAR i: INTEGER):
  INTEGER; INLINE;

FUNCTION sub_one_from(
    VAR i: INTEGER):
  INTEGER; INLINE;

FUNCTION ifelse(
  CONST condition: BOOLEAN;
  CONST t, f: INTEGER): INTEGER; OVERLOAD;

FUNCTION ifelse(
  CONST condition: BOOLEAN;
  CONST t, f: DOUBLE): DOUBLE; OVERLOAD;

PROCEDURE zero(
  VAR ar_el: LONGINT;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero(
  VAR ar_el: DOUBLE;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero(
  VAR ar_el: BOOLEAN;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero1(
  VAR ar : ARRAY_1L;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero1(
  VAR ar : ARRAY_1S;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero1(
  VAR ar : ARRAY_1D;
  CONST n: INTEGER); OVERLOAD; INLINE;

PROCEDURE zero1(
  VAR ar : ARRAY_1B;
  CONST n: INTEGER); OVERLOAD; INLINE;

// Multi-dimensional & explicit:
PROCEDURE dzero(
  CONST ar;
  CONST _nd: INTEGER;
  CONST _starts, _dims: PLONGINT_ARRAY); OVERLOAD;

PROCEDURE zero(
  CONST ar: ARRAY_1D;
  CONST starts, dims: ARRAY OF INTEGER); OVERLOAD;

PROCEDURE zero(
  CONST ar: ARRAY_2D;
  CONST starts, dims: ARRAY OF INTEGER); OVERLOAD;

PROCEDURE zero(
  CONST ar: ARRAY_3D;
  CONST starts, dims: ARRAY OF INTEGER); OVERLOAD;

PROCEDURE dzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER); OVERLOAD;

PROCEDURE lzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER); OVERLOAD;

PROCEDURE bzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER); OVERLOAD;

PROCEDURE negate(
  VAR ar_el: DOUBLE;
  CONST n: INTEGER); OVERLOAD;

PROCEDURE negate(
  VAR ar_el: LONGINT;
  CONST n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : LONGBOOL;
  n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : DOUBLE;
  n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : SINGLE;
  n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : POINTER;
  n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : LONGINT;
  n: INTEGER); OVERLOAD;

PROCEDURE XCOPY(
  VAR source, dest : BYTE;
  n: INTEGER); OVERLOAD;

PROCEDURE set_values(
      p: POINTER;
  CONST vals: ARRAY OF DOUBLE);

FUNCTION check_equal(
  CONST a, b;
        n_bytes: INTEGER):
  BOOLEAN;

PROCEDURE p2a(p: pdouble_array; OUT result:ARRAY_1D); OVERLOAD;

FUNCTION p2a(p: pdouble_array): ARRAY_1D; OVERLOAD;

FUNCTION p2a(p: psingle_array): ARRAY_1S; OVERLOAD;

FUNCTION p2a(p: plongint_array): ARRAY_1L; OVERLOAD;

FUNCTION p2a(p: pboolean_array): ARRAY_1B; OVERLOAD;

FUNCTION p2a(p: pbyte_array): ARRAY_1BYTE; OVERLOAD;

FUNCTION p2a(p: pshortint_array): ARRAY_1SHINT; OVERLOAD;

FUNCTION a2p( VAR d: DOUBLE): PDOUBLE_ARRAY; OVERLOAD;

FUNCTION a2p( VAR d: LONGINT): PLONGINT_ARRAY; OVERLOAD;

{$IFNDEF NO_R_FPU_CW}
TYPE
  TRwin_fpset_proctype = PROCEDURE(); CDECL;

VAR
  Rwin_fpset: TRwin_fpset_proctype;
{$ENDIF}

VAR
  badptr: POINTER = {$IFDEF CPU32} pointer( $FEFEFEFE); {$ELSE}
                    {$IFDEF CPU64} pointer( $FEFEFEFEFEFEFEFE); {$ENDIF}
                    {$ENDIF}

CONST
  def_def_stacksize = 1;

{************************************************************}
{************************************************************}

IMPLEMENTATION
{$UNDEF NEED_RLOADER}
{$IFNDEF NO_R_FPU_CW}
  {$DEFINE NEED_RLOADER}
{$ENDIF}
{$IFDEF RMEM}
  {$DEFINE NEED_RLOADER}
{$ENDIF}
USES 
  {$IFNDEF FPC}
    FastCode, FastMove,
  {$ENDIF} 
  SysUtils
  {$IFDEF NEED_RLOADER},
  Rloader
  {$ENDIF}
  ;

{$IFDEF RMEM}
TYPE
  TR_Calloc_proctype = FUNCTION (n,size:integer): POINTER; cdecl;
  TR_Realloc_proctype = FUNCTION( p: POINTER; n,size:integer): POINTER; cdecl;
  TR_Free_proctype = PROCEDURE ( p: POINTER); cdecl;

VAR
  R_Calloc: TR_Calloc_proctype;
  R_Realloc: TR_Realloc_proctype;
  R_Free: TR_Free_proctype;

FUNCTION Rgetmem(
      size: INTEGER):
POINTER;
BEGIN
  RESULT:= R_Calloc( size, 1);
END;

FUNCTION RFreeMem(
      p: POINTER):
INTEGER;
BEGIN
  R_Free( p);
  RESULT:= 0;
END;

FUNCTION RreallocMem(
      p: POINTER;
      size: INTEGER):
POINTER;
BEGIN
  RESULT:= R_realloc( p, size, 1);
END;
{$ENDIF}

{$POINTERMATH ON}
PROCEDURE p2a(p: pdouble_array; OUT result:ARRAY_1D);
BEGIN
  result:= ARRAY_1D(p-1); // LONGINT( p) - SizeOf( p[1]));
END;

FUNCTION p2a(p: pdouble_array): ARRAY_1D; INLINE;
BEGIN
  result:= ARRAY_1D(p-1);
END;

FUNCTION p2a(p: psingle_array): ARRAY_1S; INLINE;
BEGIN
  result:= ARRAY_1S(p-1);
END;


FUNCTION p2a(p: plongint_array): ARRAY_1L; INLINE;
BEGIN
  result:= ARRAY_1L(p-1);
END;

FUNCTION p2a(p: pboolean_array): ARRAY_1B; INLINE;
BEGIN
  result:= ARRAY_1B( p-1);
END;

FUNCTION p2a(p: pbyte_array): ARRAY_1BYTE; INLINE;
BEGIN
  result:= ARRAY_1BYTE(p-1);
END;

FUNCTION p2a(p: pshortint_array): ARRAY_1SHINT; INLINE;
BEGIN
  result:= ARRAY_1SHINT(p-1);
END;

FUNCTION a2p( VAR d: DOUBLE): PDOUBLE_ARRAY; INLINE;
BEGIN
  result:= PDOUBLE_ARRAY( @d)+1;
  // LONGINT( RESULT):= LONGINT( @d) + SizeOf( d);
END;

FUNCTION a2p( VAR d: LONGINT): PLONGINT_ARRAY; INLINE;
BEGIN
  result:= PLONGINT_ARRAY( @d)+1;
  // LONGINT( RESULT):= LONGINT( @d) + SizeOf( d);
END;
{$POINTERMATH OFF}

{***********************************************}

FUNCTION add_to(VAR i: INTEGER; v: INTEGER):INTEGER; INLINE;
BEGIN
  i:= i + v;
  RESULT:= i;
END;

FUNCTION add_one_to(
    VAR i: INTEGER):
  INTEGER; INLINE;
BEGIN
  INC( i);
  RESULT:= i;
END;

FUNCTION sub_one_from(
    VAR i: INTEGER):
  INTEGER; INLINE;
BEGIN
  DEC( i);
  RESULT:= i;
END;

FUNCTION ifelse(
  CONST condition: BOOLEAN;
  CONST t, f: INTEGER): INTEGER;
BEGIN
  IF condition THEN RESULT:= t ELSE RESULT:= f;
END;

FUNCTION ifelse(
  CONST condition: BOOLEAN;
  CONST t, f: DOUBLE): DOUBLE;
BEGIN
  IF condition THEN RESULT:= t ELSE result:= f;
END;

PROCEDURE zero(
  VAR ar_el: LONGINT;
  CONST n: INTEGER);
BEGIN
  FillChar( ar_el, n*SizeOf( ar_el), 0);
END;

PROCEDURE zero(
  VAR ar_el: DOUBLE;
  CONST n: INTEGER);
BEGIN
  FillChar( ar_el, n*SizeOf( ar_el), 0);
END;

PROCEDURE zero(
  VAR ar_el: BOOLEAN;
  CONST n: INTEGER);
BEGIN
  FillChar( ar_el, n*SizeOf( ar_el), 0);
END;

PROCEDURE Teasy_alloc_object. init(
  CONST ar: ARRAY_2L;
  CONST val: INTEGER);
VAR
  pa:   palloc_record;
  id, id1, dimprod: INTEGER;
  temp: INTEGER;
BEGIN
  pa:= find_array_specs( ar);
  WITH pa^ DO BEGIN
    IF nd=2 THEN BEGIN // direct fill
      dimprod:= dims[ 1];
      FOR id:= 2 TO nd DO BEGIN
        dimprod:= dimprod * dims[ id];
      END;
      temp:= val;
      FillDword( ARRAY_2L( nominal)[ first_el[1]][ first_el[2]],
          dimprod, temp);
    END ELSE BEGIN // nd=1; hard-code rather than fancy variable-depth loop
      FOR id1:= first_el[1] TO first_el[1]+dims[1]-1 DO BEGIN
        init( ARRAY_2L( nominal)[ id1], val);
      END;
    END;
  END;
END;

PROCEDURE Teasy_alloc_object. init(
  CONST ar: ARRAY_1L;
  CONST val: INTEGER);
VAR
  pa:   palloc_record;
  temp: INTEGER;
BEGIN
  pa:= find_array_specs( ar);
  WITH pa^ DO BEGIN
    temp:= val;
    FillDWord( ARRAY_1L( nominal)[ first_el[1]], dims[1], temp);
  end;
END;

PROCEDURE Teasy_alloc_object. init(
  CONST ar: ARRAY_3D;
  CONST val: DOUBLE);
VAR
  pa:   palloc_record;
  id, id1, id2, dimprod: INTEGER;
  temp: QWORD;
BEGIN
  pa:= find_array_specs( ar);
  WITH pa^ DO BEGIN
    IF nd=3 THEN BEGIN // direct fill
      dimprod:= dims[ 1];
      FOR id:= 2 TO nd DO BEGIN
        dimprod:= dimprod * dims[ id];
      END;
      temp:= QWORD( val);
      FillQWord( ARRAY_3D( nominal)[ first_el[1]][ first_el[2]][first_el[3]],
          dimprod, temp);
    END ELSE IF nd=2 THEN BEGIN // nd=1; hard-code rather than fancy variable-depth loop
      FOR id1:= first_el[1] TO first_el[1]+dims[1]-1 DO BEGIN
        FOR id2:= first_el[2] TO first_el[2]+dims[2]-1 DO BEGIN
          init( ARRAY_3D( nominal)[ id1][ id2], val);
        END;
      END;
    END ELSE BEGIN // nd=1
      FOR id1:= first_el[1] TO first_el[1]+dims[1]-1 DO BEGIN
        init( ARRAY_3D( nominal)[ id1], val);
      end;
    end;
  END;
END;

PROCEDURE Teasy_alloc_object. init(
  CONST ar: ARRAY_2D;
  CONST val: DOUBLE);
VAR
  pa:   palloc_record;
  id, id1, dimprod: INTEGER;
  temp: QWORD;
BEGIN
  pa:= find_array_specs( ar);
  WITH pa^ DO BEGIN
    IF nd=2 THEN BEGIN // direct fill
      dimprod:= dims[ 1];
      FOR id:= 2 TO nd DO BEGIN
        dimprod:= dimprod * dims[ id];
      END;
      temp:= QWORD( val);
      FillQWord( ARRAY_2D( nominal)[ first_el[1]][ first_el[2]], dimprod, temp);
    END ELSE BEGIN // nd=1; hard-code rather than fancy variable-depth loop
      FOR id1:= 1 TO dims[1] DO BEGIN
        init( ARRAY_2D( nominal)[ first_el[1]+id1-dims[1]], val);
      END;
    END;
  END;
END;

PROCEDURE Teasy_alloc_object. init(
  CONST ar: ARRAY_1D;
  CONST val: DOUBLE);
VAR
  pa:   palloc_record;
  temp: QWORD;
BEGIN
  pa:= find_array_specs( ar);
  temp:= QWORD( val);
  WITH pa^ DO BEGIN
    FillQWord( ARRAY_1D( nominal)[ first_el[1]],
        dims[1], temp);
  end;
END;


PROCEDURE zero1(
  VAR ar : ARRAY_1L;
  CONST n: INTEGER);
BEGIN
  FillChar( ar[1], n*SizeOf(ar[1]), 0);
END;

PROCEDURE zero1(
  VAR ar : ARRAY_1S;
  CONST n: INTEGER);
BEGIN
  FillChar( ar[1], n*SizeOf(ar[1]), 0);
END;

PROCEDURE zero1(
  VAR ar : ARRAY_1D;
  CONST n: INTEGER);
BEGIN
  FillChar( ar[1], n*SizeOf(ar[1]), 0);
END;

PROCEDURE zero1(
  VAR ar : ARRAY_1B;
  CONST n: INTEGER);
BEGIN
  FillChar( ar[1], n*SizeOf(ar[1]), 0);
END;

PROCEDURE dzero(
  CONST ar;
  CONST _nd: INTEGER;
  CONST _starts, _dims: PLONGINT_ARRAY);
VAR
  i: INTEGER;
BEGIN
  IF _nd=1 THEN BEGIN
    zero( ARRAY_1D( ar)[_starts[1]], _dims[1]);
  END ELSE BEGIN
    FOR i:= 1 TO _dims[1] DO BEGIN
      dzero( ARRAY_1P( ar)[ _starts[1]-1+i], _nd-1,
          PLONGINT_ARRAY( @_starts[2]), PLONGINT_ARRAY( @_dims[2]));
    END;
  END;
END;

PROCEDURE zero(
  CONST ar: ARRAY_1D;
  CONST starts, dims: ARRAY OF INTEGER);
BEGIN
  zero( ar[starts[0]], dims[0]);
END;

PROCEDURE zero(
  CONST ar: ARRAY_2D;
  CONST starts, dims: ARRAY OF INTEGER);
BEGIN
  dzero( ar, 1+HIGH( starts), @starts[0], @dims[0]);
END;

PROCEDURE zero(
  CONST ar: ARRAY_3D;
  CONST starts, dims: ARRAY OF INTEGER);
BEGIN
  dzero( ar, 1+HIGH( starts), @starts[0], @dims[0]);
END;


// Should write a hash-table alternative that looks up the array's own size

PROCEDURE dzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER);
VAR
  i, j: INTEGER;
  p: ARRAY_1P;
BEGIN
  FOR i:= LOW( ars) TO HIGH( ars) DO BEGIN
    p:= ars[ i];
    FOR j:= LOW( offset) TO HIGH( offset)-1 DO
      p:= p[ offset[ j]];
    FillChar( ARRAY_1D( p)[ offset[ HIGH( offset)]], n*SizeOf( DOUBLE), 0);
  END;
END;

PROCEDURE lzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER);
VAR
  i, j: INTEGER;
  p: ARRAY_1P;
BEGIN
  FOR i:= LOW( ars) TO HIGH( ars) DO BEGIN
    p:= ars[ i];
    FOR j:= LOW( offset) TO HIGH( offset) DO
      p:= p[ j];
    FillChar( ARRAY_1L( p)[ offset[HIGH( offset)]], n*SizeOf( LONGINT), 0);
  END;
END;

PROCEDURE bzero(
  CONST ars: ARRAY OF POINTER;
  CONST offset: ARRAY OF INTEGER;
  CONST n: INTEGER);
VAR
  i, j: INTEGER;
  p: ARRAY_1P;
BEGIN
  FOR i:= LOW( ars) TO HIGH( ars) DO BEGIN
    p:= ars[ i];
    FOR j:= LOW( offset) TO HIGH( offset) DO
      p:= p[ j];
    FillChar( ARRAY_1B( p)[ offset[ HIGH( offset)]], n*SizeOf( BOOLEAN), 0);
  END;
END;

PROCEDURE negate(
  VAR ar_el: DOUBLE;
  CONST n: INTEGER);
VAR
  i: INTEGER;
  ar: ARRAY_1D;
BEGIN
  ar:= @ar_el;
  FOR i:= 0 TO n-1 DO
    ar[ i]:= -ar[ i];
END;

PROCEDURE negate(
  VAR ar_el: LONGINT;
  CONST n: INTEGER);
VAR
  i: INTEGER;
  ar: ARRAY_1L;
BEGIN
  ar:= @ar_el;
  FOR i:= 0 TO n-1 DO
    ar[ i]:= -ar[ i];
END;

PROCEDURE XCOPY(
  VAR source, dest: LONGBOOL;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE XCOPY(
  VAR source, dest: DOUBLE;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE XCOPY(
  VAR source, dest: SINGLE;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE XCOPY(
  VAR source, dest: POINTER;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE XCOPY(
  VAR source, dest : LONGINT;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE XCOPY(
  VAR source, dest : BYTE;
  n: INTEGER);
BEGIN
  MOVE( source, dest, n * SizeOf( dest));
END;

PROCEDURE set_values(
      p: POINTER;
  CONST vals: ARRAY OF DOUBLE);
VAR
  i: INTEGER;
BEGIN
  FOR i:= 0 TO HIGH( vals) DO
    PZDOUBLE_ARRAY( p)[ i]:= vals[ i];
END;

FUNCTION check_equal(
  CONST a, b;
        n_bytes: INTEGER):
  BOOLEAN;
VAR
  i: INTEGER;
TYPE
  LWORD_ARRAY = ARRAY[ 1..1] OF LONGWORD;
  BYTE_ARRAY = ARRAY[ 1..1] OF BYTE;
BEGIN
  RESULT:= FALSE;
  FOR i:= 1 TO n_bytes DIV 4 DO
    IF LWORD_ARRAY( a)[ i] <> LWORD_ARRAY( b)[ i] THEN
EXIT;

  FOR i:= n_bytes - 4*(n_bytes DIV 4) TO n_bytes DO
    IF BYTE_ARRAY( a)[ i] <> BYTE_ARRAY( b)[ i] THEN
EXIT;

  RESULT:= TRUE;
END;

CONSTRUCTOR Teasy_alloc_object. create;
BEGIN
  INHERITED;
  alloc_record_size:= SizeOf( alloc_record);
  def_stacksize:= def_def_stacksize;
  DSS:= def_stacksize;
END;

FUNCTION Teasy_alloc_object. alloc( n_bytes: INTEGER): POINTER;
VAR at: POINTER;
    ar, allocation_record: palloc_record;
    clash: BOOLEAN;
BEGIN
  // Paranoia: check no clash with existing nominals
  REPEAT
    GetMem( at, n_bytes);
    clash:= FALSE;
    ar:= alloc_list;
    WHILE NOT clash AND (ar<>NIL) DO BEGIN
      clash:= ar^. nominal = at;
      ar:= ar^. next;
    END;

    IF clash THEN BEGIN
      FreeMem( at, n_bytes);
      // Grab some memory with a dummy alloc_record
      GetMem( allocation_record, alloc_record_size);
      FillChar( allocation_record^, SizeOf( allocation_record^), 0);
      WITH allocation_record^ DO BEGIN
        next:= alloc_list; // all other fields empty
      END;
      alloc_list:= allocation_record;
    END;
  UNTIL NOT clash;

  FillChar( PPOINTER( at)^, n_bytes, 0);
  GetMem( allocation_record, alloc_record_size);
  FillChar( allocation_record^, SizeOf( allocation_record^), 0);
  WITH allocation_record^ DO
  BEGIN
    next:= alloc_list;
    nb:= n_bytes;
    where:= at;
    nominal:= at;
    objptr:= NIL;
  END;
  alloc_list:= allocation_record;
  alloc:= at;
END;

FUNCTION Teasy_alloc_object. alloc_stack(
    CONST stack_size, size_of_el: INTEGER):
  POINTER;
BEGIN
  RESULT:= alloc_array( [stack_size+1], [0], size_of_el);
  PLONGINT( RESULT)^:= stack_size;
END;

PROCEDURE Teasy_alloc_object. alloc_stacks(
    CONST variables: ARRAY OF PPOINTER;
    CONST  stack_size, size_of_el: INTEGER);
VAR
  i: INTEGER;
BEGIN
  FOR i:= LOW( variables) TO HIGH( variables) DO
    variables[ i]^:= alloc_stack( stack_size, size_of_el);
END;

PROCEDURE Teasy_alloc_object. ensure_enough_stack(
  VAR stack: ARRAY_1D;
  CONST needed: INTEGER);
VAR
  new_stack: ARRAY_1D;
  old_n_stack, n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( @stack[ 0])^;
  IF needed>n_stack THEN BEGIN
    old_n_stack:= n_stack;
    REPEAT
      n_stack:= n_stack+n_stack+1;
    UNTIL n_stack >= needed;

    // elt 0 reserved for size-- needed only by set_stack_size
    new_stack:= alloc_array( [n_stack+1], [0], SizeOf( stack[ 1]));
    XCOPY(stack[1], new_stack[1], old_n_stack);
    dealloc( stack);
    stack:= new_stack;
    PLONGINT( new_stack)^:= n_stack;
  END;
END;

PROCEDURE Teasy_alloc_object. ensure_enough_stack(
  VAR stack: ARRAY_1L;
  CONST needed: INTEGER);
VAR
  new_stack: ARRAY_1L;
  old_n_stack, n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( @stack[ 0])^;
  IF needed>n_stack THEN BEGIN
    old_n_stack:= n_stack;
    REPEAT
      n_stack:= n_stack+n_stack+1;
    UNTIL n_stack >= needed;

    // elt 0 reserved for size-- needed only by set_stack_size
    new_stack:= alloc_array( [n_stack+1], [0], SizeOf( stack[ 1]));
    XCOPY( stack[1], new_stack[1], old_n_stack);
    dealloc( stack);
    stack:= new_stack;
    PLONGINT( new_stack)^:= n_stack;
  END;
END;

PROCEDURE Teasy_alloc_object. ensure_enough_stack(
  VAR stack: ARRAY_1B;
  CONST needed: INTEGER);
VAR
  new_stack: ARRAY_1B;
  old_n_stack, n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( @stack[ 0])^;
  IF needed>n_stack THEN BEGIN
    old_n_stack:= n_stack;
    REPEAT
      n_stack:= n_stack+n_stack+1;
    UNTIL n_stack >= needed;

    // elt 0 reserved for size-- needed only by set_stack_size
    new_stack:= alloc_array( [n_stack+1], [0], SizeOf( stack[ 1]));
    XCOPY( stack[1], new_stack[1], old_n_stack);
    dealloc( stack);
    stack:= new_stack;
    PLONGINT( new_stack)^:= n_stack;
  END;
END;

PROCEDURE Teasy_alloc_object. double_stack_length(
  VAR stack: ARRAY_1D);
VAR
  new_stack: ARRAY_1D;
  n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( stack)^;
  new_stack:= alloc_array( [n_stack*2+2], [0], SizeOf( stack[ 1]));
  XCOPY( stack[1], new_stack[1], n_stack);
  dealloc( stack);
  stack:= new_stack;
  PLONGINT( new_stack)^:= n_stack*2+1;
END;
{dont $DEFINE TYPE_D}
{dont $DEFINE double_stack_length}
{dont $INCLUDE USEFULINC.PAS}

PROCEDURE Teasy_alloc_object. double_stack_length(
  VAR stack: ARRAY_1L);
VAR
  new_stack: ARRAY_1L;
  n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( stack)^;
  new_stack:= alloc_array( [n_stack*2+2], [0], SizeOf( stack[ 1]));
  XCOPY( stack[1], new_stack[1], n_stack);
  dealloc( stack);
  stack:= new_stack;
  PLONGINT( new_stack)^:= n_stack*2+1;
END;

{dont $DEFINE TYPE_L}
{dont $DEFINE double_stack_length}
{dont $INCLUDE USEFULINC.PAS}

PROCEDURE Teasy_alloc_object. double_stack_length(
  VAR stack: ARRAY_1B);
VAR
  new_stack: ARRAY_1B;
  n_stack: INTEGER;
BEGIN
  n_stack:= PLONGINT( stack)^;
  new_stack:= alloc_array( [n_stack*2+2], [0], SizeOf( stack[ 1]));
  XCOPY( stack[1], new_stack[1], n_stack);
  dealloc( stack);
  stack:= new_stack;
  PLONGINT( new_stack)^:= n_stack*2+1;
END;
{dont $DEFINE TYPE_B}
{dont $DEFINE double_stack_length}
{dont $INCLUDE USEFULINC.PAS}

FUNCTION Teasy_alloc_object. stget(
    VAR stack: ARRAY_1D;
    CONST stacki: INTEGER):
  DOUBLE;
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  RESULT:= stack[ stacki];
END;

FUNCTION Teasy_alloc_object. stget(
    VAR stack: ARRAY_1L;
    CONST stacki: INTEGER):
  LONGINT;
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  RESULT:= stack[ stacki];
END;

FUNCTION Teasy_alloc_object. stget(
    VAR stack: ARRAY_1B;
    CONST stacki: INTEGER):
  BOOLEAN;
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  RESULT:= stack[ stacki];
END;

// Because an uninitialized real migbt be pushed (at the start) or popped (at...
// ... the end) of a AD'd procedure, avoid fld/fst
PROCEDURE Teasy_alloc_object. stget2(
     VAR   x: DOUBLE;
     VAR stack: ARRAY_1D;
     CONST stacki: INTEGER);
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  PQWORD( @x)^:= ARRAY_1Q(stack)[ stacki];
END;

PROCEDURE Teasy_alloc_object. stset(
    VAR stack: ARRAY_1D;
    CONST stacki: INTEGER;
    CONST val: DOUBLE);
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  ARRAY_1Q( stack)[ stacki]:= PQWORD( @val)^;
END;

PROCEDURE Teasy_alloc_object. stset(
    VAR stack: ARRAY_1L;
    CONST stacki: INTEGER;
    CONST val: LONGINT);
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  stack[ stacki]:= val;
END;

PROCEDURE Teasy_alloc_object. stset(
    VAR stack: ARRAY_1B;
    CONST stacki: INTEGER;
    CONST val: LONGBOOL);
BEGIN
  IF PLONGINT( stack)^<stacki THEN
    ensure_enough_stack( stack, stacki);
  stack[ stacki]:= val;
END;

FUNCTION Teasy_alloc_object. alloc( n_els, size_of_el, first_el: INTEGER):
  POINTER;
VAR at: ^BYTE;
BEGIN
  at:= alloc( n_els * size_of_el);
  DEC( at, first_el * size_of_el);
  alloc_list^. nominal:= at;
  RESULT:= at;
END;

FUNCTION Teasy_alloc_object. alloc(
      variables: ARRAY OF PPOINTER;
      n_els, size_of_el, first_el: INTEGER):
  POINTER;
VAR
  i: INTEGER;
BEGIN
  variables[ 0]^:= alloc( (HIGH( variables)+1) * n_els, size_of_el, first_el);
  FOR i:= 1 TO HIGH( variables) DO
    variables[ i]^:= POINTER( LONGINT( variables[i-1]^) + n_els * size_of_el);
  RESULT:= variables[ 0]^;
END;

FUNCTION Teasy_alloc_object. alloc( obj: POINTER): POINTER;
BEGIN
  alloc( 0); { create new record }
  alloc_list^. nominal:= obj;
  alloc_list^. objptr:= obj;
  RESULT:= obj;
END;


FUNCTION Teasy_alloc_object. alloc_array(
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER):
  POINTER;
BEGIN
  IF HIGH( dims) <> HIGH( first_el) THEN
RAISE Exception. Create( 'Inconsistent dimensions in "alloc_array"');
  RESULT:= alloc_array( HIGH( dims) + 1, @dims[ 0], @first_el[ 0], size_of_el);
END;

FUNCTION sizeof_array(
      nd: INTEGER;
      dims: PLONGINT_ARRAY;
      size_of_el: INTEGER):
  INTEGER;
VAR
  d, bytes_required: INTEGER;
BEGIN
  bytes_required:= dims[ nd] * size_of_el;
  FOR d:= nd-1 DOWNTO 1 DO
  BEGIN
    INC( bytes_required, SizeOf( POINTER));
    bytes_required:= bytes_required * dims[ d];
  END;
  RESULT:= bytes_required;
END;

FUNCTION setup_array_at(
      mat: PLONGINT_ARRAY;
      nd: INTEGER;
      dims, first_el: PLONGINT_ARRAY;
      size_of_el: INTEGER):
  POINTER;
VAR
  idx: LONGINT;
  dec_offset, inc_by, dimprod, d, i, pindex: INTEGER;
BEGIN
  RESULT:= mat;
  IF nd=1 THEN
    i:= size_of_el
  ELSE
    i:= SizeOf( POINTER);
  DEC( LONGINT( RESULT), first_el[ 1] * i);

  pindex:= 1;
  idx:= LONGINT( @mat[ dims[ 1] + 1]);
  dimprod:= 1;

  FOR d:= 1 TO nd-1 DO
  BEGIN
    IF d<nd-1 THEN
      i:= SizeOf( POINTER)
    ELSE
      i:= size_of_el;
    inc_by:= dims[ d+1] * i;
    dec_offset:= first_el[ d+1] * i;
    dimprod:= dimprod * dims[ d];
    FOR i:= 1 TO dimprod DO
    BEGIN
      mat[ pindex]:= idx - dec_offset;
      INC( idx, inc_by);
      INC( pindex);
    END;
  END;
END;

FUNCTION Teasy_alloc_object. alloc_array(
      _nd: INTEGER;
      _dims, _first_el: PLONGINT_ARRAY;
      _size_of_el: INTEGER):
  POINTER;

VAR
  mat: PLONGINT_ARRAY;
  bytes_required: INTEGER;
BEGIN
  RESULT:= NIL;
  IF _nd<1 THEN
EXIT;

  bytes_required:= sizeof_array( _nd, _dims, _size_of_el);
  IF bytes_required=0 THEN
    bytes_required:= 8; // new: force some allocation!
  mat:= alloc( bytes_required);
  RESULT:= setup_array_at( mat, _nd, _dims, _first_el, _size_of_el);
  WITH alloc_list^ DO BEGIN
    nd:= _nd;
    size_of_el:= _size_of_el;
    GetMem( dims, 2 * nd * SizeOf( INTEGER));
    first_el:= @dims[ nd+1];
    XCOPY( _dims[1], dims[1], nd);
    XCOPY( _first_el[1], first_el[1], nd);
    nominal:= RESULT;
  END;
END;

FUNCTION Teasy_alloc_object. alloc_array(
      existing_array: POINTER;
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER):
  POINTER;
BEGIN
  IF HIGH( dims) <> HIGH( first_el) THEN
RAISE Exception. Create( 'Inconsistent dimensions in "alloc_array"');
  RESULT:= alloc_array( existing_array, HIGH( dims) + 1, @dims[ 0], @first_el[ 0], size_of_el);
END;

FUNCTION Teasy_alloc_object. alloc_array(
      existing_array: POINTER;
      nd: INTEGER;
      dims, first_el: PLONGINT_ARRAY;
      size_of_el: INTEGER):
  POINTER;

  VAR
    mat: PLONGINT_ARRAY;
    idx: LONGINT;
    pointers_required, dec_offset, inc_by, dimprod, d, i, pindex: INTEGER;

BEGIN
  RESULT:= NIL;
  IF nd<1 THEN
EXIT;
  IF nd=1 THEN
  BEGIN
    RESULT:= POINTER( LONGINT( existing_array) - first_el[ 1] * size_of_el);
EXIT;
  END;

  pointers_required:= 0;
  FOR d:= nd-1 DOWNTO 1 DO
  BEGIN
    INC( pointers_required);
    pointers_required:= pointers_required * dims[ d];
  END;

  RESULT:= alloc( pointers_required, SizeOf( POINTER), first_el[ 1]); // avoids problems with dealloc & nominal
  mat:= POINTER( LONGINT( RESULT) + first_el[ 1] * SizeOf( POINTER)); // altered 27/2/2002

  pindex:= 1;
  idx:= LONGINT( @mat[ dims[ 1] + 1]);
  dimprod:= 1;

  FOR d:= 1 TO nd-1 DO
  BEGIN
    IF d<nd-1 THEN
      i:= SizeOf( POINTER)
    ELSE
    BEGIN
      i:= size_of_el;
      idx:= LONGINT( existing_array);
    END;

    inc_by:= dims[ d+1] * i;
    dec_offset:= first_el[ d+1] * i;
    dimprod:= dimprod * dims[ d];
    FOR i:= 1 TO dimprod DO
    BEGIN
      mat[ pindex]:= idx - dec_offset;
      INC( idx, inc_by);
      INC( pindex);
    END;
  END;
END;

FUNCTION Teasy_alloc_object. alloc_arrays( variables: ARRAY OF PPOINTER;
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER): POINTER;
VAR
  i: INTEGER;
BEGIN
  IF HIGH( dims) <> HIGH( first_el) THEN
RAISE Exception. Create( 'Inconsistent dimensions in "alloc_array"');
  // nd:= HIGH( dims) - LOW( dims) + 1;
  // New:
  FOR i:= 0 TO HIGH( variables) DO
    variables[ i]^:= alloc_array( dims, first_el, size_of_el);
  RESULT:= variables[0]^;
  // Old method: a single allocation
  // Won't work with alloc_same_shape
  // RESULT:= alloc_arrays( variables, nd, @dims[ 0], @first_el[ 0], size_of_el);
END;

FUNCTION Teasy_alloc_object. alloc_arrays( variables: ARRAY OF PPOINTER;
      nd: INTEGER;
      dims, first_el: PLONGINT_ARRAY;
      size_of_el: INTEGER): POINTER;
VAR
  idx, i, bytes_per_array: INTEGER;
BEGIN
  bytes_per_array:= sizeof_array( nd, dims, size_of_el);
  POINTER( idx):= alloc( (HIGH( variables)+1) * bytes_per_array);
  FOR i:= 0 TO HIGH( variables) DO
    variables[ i]^:= setup_array_at( POINTER( idx + i*bytes_per_array), nd, dims, first_el, size_of_el);
  RESULT:= POINTER( idx);
  alloc_list^. nominal:= variables[0]^; // so that dealloc works if called on first in list
END;

FUNCTION next_multindex(
  CONST n_els: INTEGER;
  CONST current, minel, maxel: PLONGINT_ARRAY):
BOOLEAN;
VAR
  maxch, i: INTEGER;
  hit_max: BOOLEAN;
BEGIN
  RESULT:= FALSE; // signals all done
  IF n_els < 1 THEN
EXIT;

  hit_max:= FALSE;
  FOR maxch:= n_els DOWNTO 1 DO
  BEGIN
    hit_max:= current[ maxch]<maxel[ maxch];
    IF hit_max THEN
  BREAK;
  END;

  IF NOT hit_max THEN
EXIT;

  INC( current[ maxch]);
  FOR i:= maxch+1 TO n_els DO
    current[ i]:= minel[ i];

  RESULT:= TRUE; // OK
END;

PROCEDURE Teasy_alloc_object. alloc_same_shape2(
   variables: ARRAY OF PARRAY_1P;
   VAR existing_firstel);
VAR
  ar: ppalloc_record;
  i: INTEGER;
BEGIN
  ar:= @alloc_list;

  WHILE (ar^^. where <> @existing_firstel) AND (ar^^. next <> NIL) DO
    ar:= @ar^^. next;

  IF ar^^. where <> @existing_firstel THEN BEGIN
    FOR i:= 0 TO HIGH( variables) DO
      variables[ i]^:= NIL;
EXIT;
    // RAISE EAccessViolation. CreateFmt( 'Can''t find existing_array for alloc_same_shape', []);
  END;

  alloc_same_shape_guts( variables, ar);
END;

FUNCTION Teasy_alloc_object. find_array_specs(
  CONST existing_array: POINTER):
palloc_record;
VAR
  ar: ppalloc_record;
BEGIN
  ar:= @alloc_list;

  WHILE (ar^^. nominal <> existing_array) AND (ar^^. next <> NIL) DO
    ar:= @ar^^. next;

  IF ar^^. nominal <> existing_array THEN BEGIN
    RESULT:= NIL;
EXIT;
    // RAISE EAccessViolation. CreateFmt( 'Can''t find existing_array for alloc_same_shape', []);
  END;
  RESULT:= ar^;
END;



PROCEDURE Teasy_alloc_object. alloc_same_shape(
      variables: ARRAY OF PARRAY_1P;
  CONST existing_array: POINTER);
VAR
  ar: ppalloc_record;
  i: INTEGER;
BEGIN
  ar:= @alloc_list;

  WHILE (ar^^. nominal <> existing_array) AND (ar^^. next <> NIL) DO
    ar:= @ar^^. next;

  IF ar^^. nominal <> existing_array THEN BEGIN
    FOR i:= 0 TO HIGH( variables) DO
      variables[ i]^:= NIL;
EXIT;
    // RAISE EAccessViolation. CreateFmt( 'Can''t find existing_array for alloc_same_shape', []);
  END;

  alloc_same_shape_guts( variables, ar);
END;

PROCEDURE Teasy_alloc_object. alloc_same_shape_guts(
      variables: ARRAY OF PARRAY_1P;
  CONST ar: ppalloc_record);
VAR
  ar1: ppalloc_record;
  i, idim: INTEGER;
  slice1, slice2: ARRAY_1P;
  index, minel, maxel: PLONGINT_ARRAY;
  subvar: ARRAY OF PARRAY_1P;
BEGIN
  IF ar^^. nd=0 THEN
RAISE EAccessViolation. CreateFmt( 'No dim info for alloc_same_shape', []);

  WITH ar^^ DO BEGIN
    FOR i:= 0 TO HIGH( variables) DO
      variables[ i]^:= alloc_array( nd, dims, first_el, size_of_el);

    // If final elts aren't pointers, then no sub-allocs by defn
    IF size_of_el <> SizeOf( POINTER) THEN
EXIT;

    // now try to find the allocation
    slice1:= ARRAY_1P( nominal);
    FOR idim:= 1 TO nd-1 DO
      slice1:= slice1[ first_el[ idim]];
    slice2:= slice1[ first_el[ nd]]; // LONGINT( slice1) + first_el[nd]*size_of_el
    ar1:= @alloc_list;
    // Used to have "nominal" instead of "where" in next 2 instances thereof
    WHILE (ar1^^. where <> slice2) AND (ar1^^. next <> NIL) DO
      ar1:= @ar1^^. next;
    IF ar1^^. where <>slice2 THEN // no sub-allocs
EXIT;

    SetLength( subvar, HIGH( variables)+1);
    GetMem( index, 3*nd*SizeOf( INTEGER));
    minel:= @index[ nd+1];
    maxel:= @minel[ nd+1];
    FOR idim:= 1 TO nd DO BEGIN
      minel[ idim]:= first_el[ idim];
      index[ idim]:= first_el[ idim];
      maxel[ idim]:= dims[ idim] - first_el[ idim] + 1;
    END;

    REPEAT
      slice2:= slice1;
      FOR idim:= 1 TO nd DO
        slice2:= slice2[ index[ idim]];
      // setup slice1 and subvar using index
      // Construct array of things to alloc
      FOR i:= 0 TO HIGH( variables) DO BEGIN
        subvar[ i]:= variables[ i];
        FOR idim:= 1 TO nd DO
          subvar[ i]:= @( variables[ i]^[ index[ idim]]);
      END;
      alloc_same_shape( subvar, slice2);
    UNTIL NOT next_multindex( nd, index, minel, maxel);

    Finalize( subvar);
  END;
END;

FUNCTION Teasy_alloc_object. enum(
    variables: ARRAY OF PLONGINT):
  INTEGER;
VAR
  i: INTEGER;
BEGIN
  FOR i:= 0 TO HIGH( variables) DO
    variables[ i]^:= i+1;
  RESULT:= HIGH( variables)+1;
END;

FUNCTION Teasy_alloc_object. card(
    stuff: ARRAY OF CONST):
  INTEGER;
BEGIN
  RESULT:= High(stuff)+1;
END;

FUNCTION Teasy_alloc_object. realloc(
      ar: POINTER;
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER):
  POINTER;
BEGIN
  IF ar<>NIL THEN
    dealloc( ar);
  RESULT:= alloc_array( dims, first_el, size_of_el)
END;

FUNCTION Teasy_alloc_object. realloc(
      ar: POINTER;
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER;
      target: POINTER):
  POINTER;
VAR
  i, inc_by: INTEGER;
  p: ARRAY_1P;
BEGIN
  IF ar=NIL THEN
    RESULT:= alloc_array( target, dims, first_el, size_of_el)
  ELSE
  BEGIN
    IF HIGH( dims) <> HIGH( first_el) THEN
RAISE Exception. Create( 'Inconsistent dimensions in "alloc_array"');
    RESULT:= ar;
    p:= ar;
    FOR i:= LOW( first_el) TO HIGH( first_el)-2 DO
      p:= p[ first_el[ i]];
    IF LONGINT( p[ first_el[ HIGH( first_el)-1]]) + first_el[ HIGH( first_el)]*size_of_el <> LONGINT( target) THEN
    BEGIN
      p:= @p[ first_el[ HIGH( first_el)-1]-1];
      inc_by:= dims[ HIGH( dims)] * size_of_el;
      LONGINT( target):= LONGINT( target) - first_el[ HIGH( first_el)] * size_of_el;
      FOR i:= 1 TO dims[ HIGH( first_el)-1] DO
      BEGIN
        p[ i]:= target;
        INC( LONGINT( target), inc_by);
      END;
    END;
  END;
END;

FUNCTION Teasy_alloc_object. realloc(
      ar, target: POINTER):
  POINTER;
BEGIN
  IF ar<>NIL THEN
    dealloc( ar);
  RESULT:= alloc( target);
END;

FUNCTION Teasy_alloc_object. realloc_arrays(
      variables: ARRAY OF PPOINTER;
      dims, first_el: ARRAY OF INTEGER;
      size_of_el: INTEGER):
POINTER;
BEGIN
  dealloc( variables);
  RESULT:= alloc_arrays( variables, dims, first_el, size_of_el);
END;

PROCEDURE Teasy_alloc_object. dealloc( variables: ARRAY OF PPOINTER);
VAR
  i: INTEGER;
BEGIN
  FOR i:= 0 TO HIGH( variables) DO
    IF variables[i]^<>NIL THEN
      dealloc( variables[i]^);
END;

PROCEDURE Teasy_alloc_object. dealloc( p: POINTER);
VAR
  save: palloc_record;
  ar:   ^palloc_record;
BEGIN
  IF p=NIL THEN
EXIT;

  ar:= @alloc_list;

  WHILE (ar^^. nominal <> p) AND (ar^^. next <> NIL) DO
    ar:= @ar^^. next;

  IF ar^^. nominal <> p THEN
RAISE EAccessViolation. CreateFmt( 'Attempt to dealloc failed', []);

  WITH ar^^ DO
  BEGIN
    save:= next;
    IF objptr=NIL THEN
      FreeMem( where, nb)
    ELSE
      objptr. destroy;
    IF dims<>NIL THEN
      FreeMem( dims, 2*nd*SizeOf( INTEGER));
  END;
  FreeMem( ar^, alloc_record_size);
  ar^:= save;
END;

DESTRUCTOR Teasy_alloc_object. Destroy;
VAR temp: POINTER;
BEGIN
  WHILE alloc_list<>NIL DO
  BEGIN
    temp:= alloc_list. next;
    WITH alloc_list^ DO
    BEGIN
      IF nb>0 THEN
        FreeMem( where, nb)
      ELSE
        objptr. Free;
      IF dims<>NIL THEN
        FreeMem( dims, 2*nd*SizeOf( INTEGER));
    END;
    FreeMem( alloc_list, alloc_record_size);
    alloc_list:= temp;
  END;
  INHERITED destroy;
END;

{$IFDEF RMEM}
VAR
  mem_manage: TMemoryManager;
{$ENDIF}

INITIALIZATION
{$IFDEF RMEM}
  load_R_routines( [@@R_Calloc, @@R_Realloc, @@R_Free],
      ['R_chk_alloc', 'R_chk_realloc', 'R_chk_free']);

  WITH mem_manage DO BEGIN
    GetMem:= RGetMem;
    FreeMem:= RFreemem;
    ReallocMem:= RReallocmem;
  END;
  // SetMemoryManage( mem_manage);
{$ENDIF}
{$IFNDEF WINDOWS}
  {$DEFINE NO_R_FPU_CW}
{$ENDIF}
{$IFNDEF NO_R_FPU_CW} // so default is: use R's version
  load_R_routines( [@@Rwin_fpset], ['Rwin_fpset']);
  Rwin_fpset();
{$ENDIF}

END.
