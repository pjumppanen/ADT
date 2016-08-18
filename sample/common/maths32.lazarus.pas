UNIT Maths32;
{$WARNINGS OFF}
{$HINTS OFF}
{$REALCOMPATIBILITY ON}
{$F+}

INTERFACE

USES useful;

VAR g2: single;
CONST Euler_gamma: DOUBLE = 0.577215664901532860606512;
      inv_sqrt_two_pi: DOUBLE = 0.3989422804014326779399461;
      sqrt_two_pi: DOUBLE = 2.506628274631000502415765;
      hex_nearly_one: LONGWORD = $3F7FFFFF;
      infinity_data: LONGWORD = $7F800000;
      qnan_data: LONGWORD = $FFFFFFFF;
      inv_256 = 1/256;

VAR infinity: SINGLE ABSOLUTE infinity_data;
    qnan: SINGLE ABSOLUTE qnan_data;
    pausing: BOOLEAN;
    nearly_one: SINGLE ABSOLUTE hex_nearly_one;
    double_eps: DOUBLE;

TYPE PLONGINT = ^LONGINT;
     PDOUBLE = ^DOUBLE;
     PSINGLE = ^SINGLE;

PROCEDURE reset_80x87;

PROCEDURE DECR(
  VAR x: INTEGER;
  CONST by: INTEGER = 1); OVERLOAD; INLINE;

PROCEDURE DECR(
  VAR x: DOUBLE;
  CONST by: DOUBLE = 1); OVERLOAD; INLINE;

PROCEDURE INCR(
  VAR x: INTEGER;
  CONST by: INTEGER = 1); OVERLOAD; INLINE;

PROCEDURE INCR(
  VAR x: DOUBLE;
  CONST by: DOUBLE = 1); OVERLOAD; INLINE;

FUNCTION MAX( x: DOUBLE; y: DOUBLE):
  DOUBLE; OVERLOAD; INLINE;

FUNCTION MAX( x: INTEGER; y: INTEGER):
  INTEGER; OVERLOAD; INLINE;

FUNCTION MAX( x: ARRAY OF DOUBLE):
  DOUBLE; OVERLOAD;

FUNCTION MIN( x: DOUBLE; y: DOUBLE):
  DOUBLE; OVERLOAD; INLINE;

FUNCTION MIN( x: INTEGER; y: INTEGER):
  INTEGER; OVERLOAD; INLINE;

FUNCTION MIN( x: ARRAY OF DOUBLE):
  DOUBLE; OVERLOAD;

FUNCTION LMAX ( l1, l2: LONGINT): LONGINT;

FUNCTION LMIN ( l1, l2: LONGINT): LONGINT;

PROCEDURE min_and_max( VAR old_min, old_max: DOUBLE;
                           new_val: DOUBLE);

FUNCTION is_finite( CONST x: DOUBLE): BOOLEAN;

FUNCTION TRUNC( x: DOUBLE): LONGINT; { replaces system version }

FUNCTION sign(x: DOUBLE): DOUBLE; OVERLOAD; INLINE;

FUNCTION sign( apply_to, apply_from: DOUBLE): DOUBLE; OVERLOAD; INLINE;

FUNCTION sgn( x: DOUBLE): INTEGER; INLINE;

FUNCTION pwr( CONST x, y: DOUBLE): DOUBLE; OVERLOAD; INLINE;

FUNCTION pwr( CONST x: DOUBLE; CONST y: INTEGER): DOUBLE; OVERLOAD; INLINE;

FUNCTION ipwr( CONST x: DOUBLE; CONST e: INTEGER): DOUBLE; INLINE;

FUNCTION PosIntPower( CONST x: DOUBLE; CONST n: INTEGER): DOUBLE; // call ipwr instead!

FUNCTION rel_delta( CONST a, b: DOUBLE):
         DOUBLE;

TYPE quad_root_type = ( big_root, small_root);
     QUADRATIC =
       OBJECT
         a, b, c: DOUBLE;
         is_complex: BOOLEAN;
         root:    ARRAY[ quad_root_type] OF DOUBLE;
         CONSTRUCTOR init( aa, bb, cc: DOUBLE);
         FUNCTION at( x: DOUBLE): DOUBLE;
       END;
CONST  real_part = big_root;
       im_part = small_root;

VAR Aitken_ext: DOUBLE;

FUNCTION Aitken_OK( x1, x2, x3: DOUBLE): BOOLEAN;

FUNCTION EXP(
    CONST x: DOUBLE):
  DOUBLE; INLINE;

FUNCTION log1p( CONST x: DOUBLE): DOUBLE;

FUNCTION expm1( CONST x: DOUBLE): DOUBLE;

FUNCTION logit( CONST x: DOUBLE): DOUBLE;

FUNCTION inv_logit( CONST x: DOUBLE): DOUBLE;

FUNCTION scal_logit( CONST x: DOUBLE): DOUBLE;

FUNCTION scal_inv_logit( CONST x: DOUBLE): DOUBLE;

FUNCTION dinv_logit( CONST x: DOUBLE): DOUBLE;

FUNCTION plogit( CONST x_minus_m: DOUBLE): DOUBLE;

FUNCTION LIL( CONST x: DOUBLE): DOUBLE; // log inv logit

FUNCTION inv( CONST x: DOUBLE): DOUBLE; INLINE;

FUNCTION EXP_( CONST x: DOUBLE): DOUBLE; INLINE;

FUNCTION INV_( CONST x: DOUBLE): DOUBLE; INLINE;

FUNCTION inv_logit_( CONST x: DOUBLE): DOUBLE; INLINE;

FUNCTION plogis( CONST x: DOUBLE): DOUBLE; INLINE;

FUNCTION BetaI( a, b, x: DOUBLE):
         DOUBLE;

FUNCTION betai_known_beta( a, b, p, ln_beta: DOUBLE):
         DOUBLE;

FUNCTION inv_Betai( a, b, p: DOUBLE):
         DOUBLE;

FUNCTION psi( x: DOUBLE):
         DOUBLE;

FUNCTION psi_dash( x: DOUBLE):
         DOUBLE;

FUNCTION dnpsi( n: INTEGER; x: DOUBLE):
         DOUBLE;

FUNCTION LN_minus_psi( x: DOUBLE):
         DOUBLE;

FUNCTION gammln( x: DOUBLE):
         DOUBLE;

FUNCTION delta_gammln( v: SINGLE;
                       extra: LONGINT;
                   VAR gammln_v,
                       temp: DOUBLE): DOUBLE;

FUNCTION ln_beta_fn( a,b: DOUBLE):
         DOUBLE;

FUNCTION bessi0( x: DOUBLE):
         DOUBLE;

FUNCTION ppchi2( p, v, g: DOUBLE): DOUBLE; { p=prob; v=DoF; g=gammln( DoF/2) if provided }

FUNCTION GammP( a, x: DOUBLE):
         DOUBLE;

FUNCTION gammq( a, x: DOUBLE):
         DOUBLE;

FUNCTION GammQ_GLN( a,x, gln: DOUBLE;
                    gln_known: BOOLEAN): DOUBLE;

FUNCTION GammP_GLN( a,x, gln: DOUBLE;
                    gln_known: BOOLEAN): DOUBLE;

FUNCTION inv_GammP( alpha, p: DOUBLE): DOUBLE;

PROCEDURE R_dgammp_dalpha(
      a, x, dda, dda2: PDOUBLE_ARRAY;
  VAR n: LONGINT); {$IFDEF R} CDECL {$ELSE} STDCALL {$ENDIF} ;

FUNCTION dgammp_dalpha(
  CONST a, x: DOUBLE;
        lgam_a, psi_a, dpsi_a: DOUBLE):
  DOUBLE;

TYPE pseudo_array = FUNCTION ( n: LONGINT): DOUBLE;

FUNCTION median(x: pseudo_array; n: LONGINT): DOUBLE;

FUNCTION chi_sig( chi_sq: DOUBLE;
                  df:     INTEGER):
         DOUBLE;

FUNCTION Normal( alpha: DOUBLE):
         DOUBLE;

FUNCTION Hermite( n: INTEGER; x: SINGLE): SINGLE;

FUNCTION Student( df: INTEGER;
                  alpha: DOUBLE):
         DOUBLE;

FUNCTION Student_pp( df: INTEGER;
                     pp:  DOUBLE):
         DOUBLE;

FUNCTION inv_NB_rnd( v, p, r: SINGLE): INTEGER;

FUNCTION inv_Poisson_rnd( lambda, r: SINGLE): INTEGER;

FUNCTION inv_Bin_rnd( n: INTEGER; p, r: SINGLE): INTEGER;

FUNCTION cum_normal_prob( x: DOUBLE):
         DOUBLE;

FUNCTION LN_1_minus_Phi( x: DOUBLE):
  DOUBLE;

FUNCTION cum_NB_prob( s: INTEGER; v, p: SINGLE): SINGLE;

FUNCTION cum_Poisson_prob( s: INTEGER; lambda: SINGLE): SINGLE;

FUNCTION cum_Bin_prob( n, r: INTEGER; p: SINGLE): SINGLE;

FUNCTION Norm_rnd: DOUBLE;

FUNCTION Bin_rnd( n: LONGINT;
                  p: DOUBLE):
         LONGINT;

TYPE  Binomial_dsn_type = ( small_n, small_mean, large_mean);
      Binomial_block =
     RECORD
       n: LONGINT;
       p: DOUBLE;
       swapping_prob: BOOLEAN;
       am: DOUBLE;

       CASE distribution: Binomial_dsn_type OF
         small_mean: ( g: DOUBLE);
         large_mean: ( sq, oldg,
                       pc, plog,
                       pclog: DOUBLE);
     END;

PROCEDURE set_binomial_block( VAR bb: Binomial_block;
                                  nn:  LONGINT;
                                  pp:  DOUBLE);

FUNCTION Binomial( VAR bb: Binomial_block):
         LONGINT;

FUNCTION Poi_rnd( lambda: DOUBLE):
         LONGINT;

TYPE Poisson_block =
     RECORD
       xm,
       glsq,
       glalxm,
       glg:    DOUBLE;
     END;

PROCEDURE set_Poisson_block( VAR p: Poisson_block;
                                 lambda: DOUBLE);

FUNCTION Poisson( VAR p: Poisson_block):
         LONGINT;

FUNCTION Gam_rnd( alpha: DOUBLE):
         DOUBLE;

FUNCTION Beta_rnd( a, b: SINGLE): SINGLE;

FUNCTION NB_rnd( n: INTEGER;
                      p: DOUBLE):
         LONGINT;

PROCEDURE solve_tridiag(
  a, b, c, r, u, gam: PDOUBLE_ARRAY;
  n: PLONGINT); {$IFDEF R} CDECL {$ELSE} STDCALL {$ENDIF} ;

FUNCTION select(
  data: PDOUBLE_ARRAY;
  k, n: INTEGER):
  DOUBLE;

PROCEDURE inbeder(
  x,p,q: DOUBLE;
  psi, der : PDOUBLE_ARRAY;
  VAR nappx, ifault: INTEGER;
  VAR errapx: DOUBLE);

VAR
  last_exp_x, last_exp_result,
  last_inv_x, last_inv_result,
  last_inv_logit_x, last_inv_logit_result: DOUBLE;

(****************************************************************************)

IMPLEMENTATION

USES
  {FastCode, FastMove, }SysUtils, Math{, Rloader};

TYPE binomial_block_type =
     RECORD
       oldg,
       en,
       pc,
       plog,
       pclog,
       pold:  DOUBLE;
       nold:  LONGINT;
     END;

     Poisson_block_type =
     RECORD
       xm,
       gloldm,
       glsq,
       glalxm,
       glg:    DOUBLE;
     END;

     r_array = ARRAY[ 1..10000] OF REAL;
     s_array = ARRAY[ 1..15000] OF SINGLE;
     d_array = ARRAY[ 1..8000] OF DOUBLE;
     e_array = ARRAY[ 1..6000] OF EXTENDED;

     extended_words = ARRAY[ 1..5] OF WORD;

VAR convergence_block: RECORD
                         size_of_real: INTEGER;
                         tolerance:    DOUBLE;
                       END;

CONST nt = 11;
      LN_2 = 0.69314718056;
      one_third = 0.333333333333;
      two_thirds = 0.66666666667;
      c: ARRAY [ 2..nt] OF DOUBLE
      = ( 0.644934066823, -0.202056903160, 8.232323371114e-2, -3.69277551434e-2,
          1.734306198445e-2, -8.34927738192e-3, 4.97735619794e-3, -2.00839282608e-3,
          9.94575127818e-4, -4.94188604119e-4);

{****************************************************************************}

FUNCTION random: DOUBLE;
CONST min_rnd = 1e-3;
      rnd_scale = 1-2*min_rnd;
BEGIN
  random:= min_rnd + rnd_scale * system. random;
END;

{****************************************************************************}

PROCEDURE DECR(
  VAR x: INTEGER;
  CONST by: INTEGER = 1); INLINE;
BEGIN
  x:= x-by;
END;

PROCEDURE DECR(
  VAR x: DOUBLE;
  CONST by: DOUBLE = 1); INLINE;
BEGIN
  x:= x-by;
  {FLD x;
  FADD by;
  FSTP x;}
END;

PROCEDURE INCR(
  VAR x: INTEGER;
  CONST by: INTEGER = 1); INLINE;
{ASM
  MOV EAX, [x]
  ADD EAX, [by]
  MOV [x], EAX;}
BEGIN
  x:= x+by;
END;

PROCEDURE INCR(
  VAR x: DOUBLE;
  CONST by: DOUBLE = 1); INLINE;
BEGIN
  x:= x+by;
END;

FUNCTION inv(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  RESULT:= 1/x;
END;

FUNCTION EXP_(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF x=last_exp_x THEN
    RESULT:= last_exp_result
  ELSE BEGIN
    RESULT:= EXP( x);
    last_exp_x:= x;
    last_exp_result:= RESULT;
  END;
END;

FUNCTION INV_(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF x=last_inv_x THEN
    RESULT:= last_inv_result
  ELSE BEGIN
    RESULT:= 1/x;
    last_inv_x:= x;
    last_inv_result:= RESULT;
  END;
END;

FUNCTION inv_logit_(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF x=last_inv_logit_x THEN
    RESULT:= last_inv_logit_result
  ELSE BEGIN
    RESULT:= inv_logit(x);
    last_inv_logit_x:= x;
    last_inv_logit_result:= RESULT;
  END;
END;

FUNCTION plogis(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF x=last_inv_logit_x THEN
    RESULT:= last_inv_logit_result
  ELSE BEGIN
    RESULT:= inv_logit(x);
    last_inv_logit_x:= x;
    last_inv_logit_result:= RESULT;
  END;
END;


TYPE
  pexpmem_rec=^expmem_rec;
  expmem_rec = RECORD
    x, exp_x: DOUBLE;
    next: pexpmem_rec;
  END;
  dummy_double=RECORD
    d1, d2: LONGWORD;
  END;

CONST
  n_expmem=3;
VAR
  head, orig_head: pexpmem_rec;

FUNCTION EXPmem(
  CONST x: DOUBLE):
DOUBLE; INLINE;
VAR
  old_head: pexpmem_rec;
BEGIN
  old_head:= head;
  REPEAT
    IF (dummy_double( x).d1=dummy_double( head.x).d1) AND
       (dummy_double( x).d2=dummy_double( head.x).d2) THEN BEGIN
      RESULT:= head.exp_x;
EXIT;
    END;
    head:= head.next;
  UNTIL head=old_head;
  head:= head.next; // overwrite next value, presumably oldest
  head.x:= x;
  head.exp_x:= system. EXP( x);
  RESULT:= head.exp_x;
END;

{****************************************************************************}

FUNCTION MAX( x: DOUBLE; y: DOUBLE):
  DOUBLE; OVERLOAD; INLINE;
BEGIN
  if (x > y) then
    RESULT := x
  else
    RESULT := y;
END;

{****************************************************************************}

FUNCTION MAX( x: INTEGER; y: INTEGER):
  INTEGER; OVERLOAD; INLINE;
BEGIN
  if (x > y) then
    RESULT := x
  else
    RESULT := y;
END;

{****************************************************************************}

FUNCTION MAX( x: ARRAY OF DOUBLE):
  DOUBLE; OVERLOAD;
VAR
  i: INTEGER;
BEGIN
  RESULT:= x[ LOW(x)];
  FOR i:= 1+LOW(x) TO HIGH( x) DO
    if (RESULT < x[ i]) then
      RESULT := x[ i];
END;

{****************************************************************************}

FUNCTION MIN( x: DOUBLE; y: DOUBLE):
  DOUBLE; OVERLOAD; INLINE;
BEGIN
  if (x < y) then
    RESULT := x
  else
    RESULT := y;
END;

{****************************************************************************}

FUNCTION MIN( x: INTEGER; y: INTEGER):
  INTEGER; OVERLOAD; INLINE;
BEGIN
  if (x < y) then
    RESULT := x
  else
    RESULT := y;
END;

{****************************************************************************}

FUNCTION MIN( x: ARRAY OF DOUBLE):
  DOUBLE; OVERLOAD;
VAR
  i: INTEGER;
BEGIN
  RESULT:= x[ LOW(x)];
  FOR i:= 1+LOW(x) TO HIGH( x) DO
    if (RESULT > x[ i]) then
      RESULT := x[ i];
END;

{****************************************************************************}

PROCEDURE min_and_max( VAR old_min, old_max: DOUBLE;
                           new_val: DOUBLE);
BEGIN
  IF old_min > new_val THEN
    old_min:= new_val;
  IF old_max < new_val THEN
    old_max:= new_val;
END;

{****************************************************************************}

FUNCTION LMAX ( l1, l2: LONGINT): LONGINT;
BEGIN
IF l1<l2 THEN LMAX:=l2
         ELSE LMAX:=l1;
END;

FUNCTION LMIN ( l1, l2: LONGINT): LONGINT;
BEGIN
IF l1<l2 THEN LMIN:=l1
         ELSE LMIN:=l2;
END;

{****************************************************************************}

FUNCTION is_finite( CONST x: DOUBLE): BOOLEAN;
BEGIN
  RESULT:= (NOT isNaN( x)) AND (NOT isInfinite( x));
END;

{****************************************************************************}

FUNCTION TRUNC( x: DOUBLE): LONGINT;
VAR sign: BOOLEAN;
    tx:    LONGINT;
BEGIN
  sign:= x>0;
  IF NOT sign THEN
    x:= -x;
  ASM
    FLD x;
    FISTP tx;
    FWAIT;
  END;

  IF tx>x THEN
    tx:= tx-1;

  IF NOT sign THEN
    tx:= -tx;
  TRUNC:= tx;
END;

{****************************************************************************}

FUNCTION EXP(
    CONST x: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF isInfinite(x) AND (SIGN(x)=-1) THEN
    RESULT:= 0
  ELSE
    RESULT:= System. EXP( x);
END;

{****************************************************************************}

FUNCTION pwr(
    CONST x, y: DOUBLE):
  DOUBLE; INLINE;
BEGIN
  IF (x=0) AND (y<0) THEN
    RESULT:= Infinity
  ELSE
    Result:= power( x, y);
END;

{****************************************************************************}

FUNCTION pwr(
    CONST x: DOUBLE;
    CONST y: INTEGER):
  DOUBLE; INLINE;
BEGIN
  IF y>0 THEN
    Result:= PosIntPower( x, y)
  ELSE IF y<0 THEN
    RESULT:= PosIntPower( 1/x, -y)
  ELSE IF x<>0 THEN
    RESULT:= 1
  ELSE
    RESULT:= QNAN;
END;

{****************************************************************************}

FUNCTION ipwr(
    CONST x: DOUBLE;
    CONST e: INTEGER):
  DOUBLE; INLINE;
BEGIN
  IF e>0 THEN
    Result:= PosIntPower( x, e)
  ELSE IF e<0 THEN
    RESULT:= PosIntPower( 1/x, -e)
  ELSE IF x<>0 THEN
    RESULT:= 1
  ELSE
    RESULT:= QNAN;
END;

{****************************************************************************}

FUNCTION PosIntPower(
    CONST x: DOUBLE;
    CONST n: INTEGER):
  DOUBLE;
ASM
  // From Agner Fog's Pentium optimization manual
      FLD1 // temporary 1.0
      FLD1 // power init. = 1.0
      FLD [X] // ST(0) = xp, ST(1) = power
      // MOV EAX, [N] // EAX = n-- should be there already
 @@1: FLD ST(0) // load a temporary copy of xp
      SHR EAX, 1 // shift right n
      // macro for FCMOVNC
      // DB $DB
      // FADD ST(0),ST(3)
      FCMOVNB ST(0),ST(3) // replace xp by 1.0 if bit = 0
      FMULP ST(2),ST(0) // power *= (i & 1) ? xp : 1.0
      FMUL ST(0),ST(0) // xp *= xp
      JNZ @@1 // stop when i = 0
      FSTP ST(0) // discard xp
      FSTP ST(1) // result overwrites temporary 1
      // FSTP [POWER] // store result
      // FSTP ST(0) // discard temporary 1.0
END;

{****************************************************************************}

FUNCTION log1p(
  CONST x: DOUBLE): DOUBLE;
VAR
  u: DOUBLE;
BEGIN
  u:= 1+x;
  IF u=1 THEN
    RESULT:= x
  ELSE
    RESULT:= LN( u) * (x/(u-1));
END;

{****************************************************************************}

FUNCTION expm1(
  CONST x: DOUBLE): DOUBLE;
VAR
  y, a: DOUBLE;
BEGIN
  a:= ABS( x);
  IF a<double_eps THEN BEGIN
    RESULT:= x;
EXIT;
  END;

  IF a>0.697 THEN BEGIN
    RESULT:= EXP( x)-1;
EXIT;
  END;

  IF a>1e-8 THEN
    y:= EXP( x)-1
  ELSE
    y:= (x*0.5+1)*x;

  DECR( y, (1+y)*(log1p( y)-x));
  RESULT:= y;
END;

{ from R nmath.h
    double y, a = fabs(x);

    if (a < DBL_EPSILON) return x;
    if (a > 0.697) return exp(x) - 1;  /* negligible cancellation */

    if (a > 1e-8)
	y = exp(x) - 1;
    else /* Taylor expansion, more accurate in this range */
	y = (x / 2 + 1) * x;

    /* Newton step for solving   log(1 + y) = x   for y : */
    /* WARNING: does not work for y ~ -1: bug in 1.5.0 */
    y -= (1 + y) * (log1p (y) - x);
    return y;
}
{****************************************************************************}

FUNCTION rel_delta( CONST a, b: DOUBLE):
         DOUBLE;
VAR temp: DOUBLE;
BEGIN
  rel_delta:= 0;
  IF a=b THEN
EXIT;

  temp:= MAX( ABS( a), ABS( b));
  IF ( temp > 0) AND ( temp < infinity) THEN
    rel_delta:= ABS( a - b) / temp
  ELSE IF temp <> 0 THEN
    rel_delta:= infinity;
END;

{****************************************************************************}

CONSTRUCTOR quadratic. init( aa, bb, cc: DOUBLE);
VAR det, q: DOUBLE;
BEGIN
  a:= aa; b:= bb; c:= cc;

  IF a=0 THEN
  BEGIN
    root[ big_root]:= -c/b;
    root[ small_root]:= -c/b;
    is_complex:= FALSE
  END
  ELSE
  BEGIN
    det:= SQR( b) - 4*a*c;
    is_complex:= det<0;

    IF is_complex THEN
    BEGIN
      root[ real_part]:= -b/(2*a);
      root[ im_part]:= SQRT( ABS( det));
    END
    ELSE
    BEGIN
      IF b>=0 THEN
        q:= -0.5 * ( b + SQRT( det))
      ELSE
        q:= -0.5 * ( b - SQRT( det));

      IF q=0 THEN
{*    This can only happen if b=0 AND det=0; since we have checked
      that a>0, we must have b=c=0, and root=0 *}
      BEGIN
        root[ small_root]:= 0; root[ big_root]:= 0;
      END
      ELSE
      BEGIN
        root[ small_root]:= c / q;
        root[ big_root]:= q / a;
      END;

      IF root[ big_root] < root[ small_root] THEN
      BEGIN
        q:= root[ big_root];
        root[ big_root]:= root[ small_root];
        root[ small_root]:= q;
      END;
    END;
  END;
END;

{****************************************************************************}

FUNCTION quadratic. at( x: DOUBLE): DOUBLE;
BEGIN
  at:= c + x * ( b + x*a);
END;

{****************************************************************************}

FUNCTION convergence( VAR old_vals,
                          new_vals;
                          n: INTEGER): BOOLEAN;

VAR t:    INTEGER;
    max_del: DOUBLE;

    FUNCTION el( VAR vals;
                     i: INTEGER): DOUBLE;
    BEGIN
      CASE convergence_block. size_of_real OF
        {SizeOf( REAL): el:= r_array( vals)[ i];}
        SizeOf( SINGLE): el:= s_array( vals)[ i];
        SizeOf( DOUBLE): el:= d_array( vals)[ i];
        SizeOf( EXTENDED): el:= e_array( vals)[ i];
      ELSE
        el:= QNAN;
      END;
    END;

BEGIN
  max_del:= 0;
  FOR t:= 1 TO nt DO
    max_del:= max( max_del, rel_delta( el( old_vals, t), el( new_vals, t)));

  convergence:= max_del < convergence_block. tolerance;
END;

{****************************************************************************}

FUNCTION Aitken_OK( x1, x2, x3: DOUBLE): BOOLEAN;
VAR r: DOUBLE;
BEGIN
  Aitken_OK:= FALSE;
  IF x2 <> x1 THEN
  BEGIN
    r:= ( x3 - x2) / ( x2 - x1);
    IF ABS( r) < 1 THEN
    BEGIN
      Aitken_ext:= x1 - ( x2 - x1) / ( r - 1);
      Aitken_OK:= TRUE;
    END;
  END;
END;

{****************************************************************************}

FUNCTION sign(x: DOUBLE): DOUBLE; OVERLOAD; INLINE;
BEGIN
  IF (x > 0) THEN
    RESULT := 1
  ELSE IF (x < 0) THEN
    RESULT := -1
  ELSE
    RESULT := 0;
END;

{****************************************************************************}

FUNCTION sign( apply_to, apply_from: DOUBLE): DOUBLE; INLINE;
BEGIN
  IF (apply_from > 0) THEN
    sign := abs( apply_to)
  ELSE
    sign := -abs( apply_to);
END;

{****************************************************************************}

PROCEDURE pause( CONST s: STRING);
BEGIN
  RAISE EMathError.Create( s);
END;

{****************************************************************************}

FUNCTION sgn( x: DOUBLE): INTEGER;
BEGIN
  IF x>0 THEN sgn:=1 ELSE IF x<0 THEN sgn:=-1 ELSE sgn:=0;
END;

{****************************************************************************}

FUNCTION logit(
    CONST x: DOUBLE):
  DOUBLE;
BEGIN
  IF x=0 THEN
    logit:= -1e37
  ELSE
  IF x=1 THEN
    logit:= 1e37
  ELSE
    logit:= LN( x / (1-x));
END;

{****************************************************************************}

FUNCTION inv_logit(
    CONST x: DOUBLE):
  DOUBLE;
BEGIN
  // roughly log( double_neg_eps), but this is exact
  IF x<-36.7363124075975981959901 THEN
    inv_logit:= 1
  ELSE
    inv_logit:= 1 / (1+EXP(-x)); // 1 - 1 / ( 1 + EXP( x));
END;

{****************************************************************************}

FUNCTION scal_logit(
    CONST x: DOUBLE):
  DOUBLE;
BEGIN
  RESULT:= logit( 0.5 + (1-inv_256) * (x-0.5));
END;

{****************************************************************************}

FUNCTION scal_inv_logit(
    CONST x: DOUBLE):
  DOUBLE;
BEGIN
  RESULT:= inv_256 + (1-inv_256) * inv_logit(x);
END;

(****************************************************************************)

FUNCTION dinv_logit(
    CONST x: DOUBLE):
  DOUBLE;
VAR
  xx: DOUBLE;
BEGIN
  IF x>88 THEN
    dinv_logit:= 0
  ELSE
  BEGIN
    xx:= 1 / ( 1 + EXP( x));
    dinv_logit:= xx * (1-xx);
  END;
END;

(****************************************************************************)

FUNCTION plogit(
    CONST x_minus_m: DOUBLE):
  DOUBLE;
BEGIN
  RESULT:= 1 / (1 + exp(-x_minus_m));
END;

(****************************************************************************)

FUNCTION LIL(
    CONST x: DOUBLE):
  DOUBLE;
BEGIN
  IF x<0 THEN
    RESULT:= x - log1p( EXP( x))
  ELSE
    RESULT:= -log1p( EXP( -x));
END;

(****************************************************************************)

{$I GAMMLN.PAS}
{$I GSER.PAS}
{$I GCF.PAS}
{$I GAMMQ.PAS}
{$I ERFCC.PAS}
{$I BETACF.PAS}
{$I BETAI.PAS}
{$I BESS.PAS}
{$I PSI.PAS}
{$I GASDEV.PAS}
{$I BNLDEV.PAS}
{$I GAMDEV.PAS}
{$I POIDEV.PAS}
{$I PPCHI2.PAS}
{$I INVBETAI.PAS}
{$I IBETADRV.PAS}
{$I IGAMMA-DERIV.PAS}

{****************************************************************************}

FUNCTION GammP( a, x: DOUBLE):
         DOUBLE;
BEGIN
  GammP:= 1 - GammQ( a, x);
END;

{****************************************************************************}

FUNCTION GammP_GLN( a,x, gln: DOUBLE;
                    gln_known: BOOLEAN): DOUBLE;
BEGIN
  GammP_GLN:= 1 - GammQ_GLN( a, x, gln, gln_known);
END;

{****************************************************************************}

FUNCTION inv_Betai( a, b, p: DOUBLE):
         DOUBLE;
BEGIN
  inv_betai:= inv_betai_primitive( a, b, p, ln_beta_fn( a, b))
END;

{****************************************************************************}

FUNCTION dgammp_dalpha(
  CONST a, x: DOUBLE;
        lgam_a, psi_a, dpsi_a: DOUBLE):
  DOUBLE;
VAR
  error: INTEGER;
  dres: DAR6;
BEGIN
  digami( @dres[1], x, a, lgam_a, QNAN, psi_a, QNAN, dpsi_a, QNAN, error);
  RESULT:= dres[ 3];
END;


PROCEDURE R_dGammP_dalpha(
      a, x, dda, dda2: PDOUBLE_ARRAY;
  VAR n: LONGINT);
VAR
  i, error: INTEGER;
  dres: DAR6;
  last_a, gplog, psip, psidp: DOUBLE;
BEGIN
  last_a:= -Infinity;
  FOR i:= 1 TO n DO
  BEGIN
    IF last_a <> a[i] THEN
    BEGIN
      gplog:= gammln( a[i]); psip:= psi( a[i]); psidp:= psi_dash( a[i]);
      last_a:= a[ i];
    END;

    digami( @dres[1], x[i], a[i], gplog, QNAN, psip, QNAN, psidp, QNAN, error);
    IF error=0 THEN
    BEGIN
      dda[ i]:= dres[ 3];
      dda2[ i]:= dres[ 4];
    END
    ELSE BEGIN
      dda[ i]:= QNAN;
      dda2[ i]:= QNAN;
    END;
  END;
END;

{****************************************************************************}

FUNCTION delta_gammln( v: SINGLE;
                       extra: LONGINT;
                   VAR gammln_v,
                       temp: DOUBLE): DOUBLE;
CONST delta_gammln_limit = 500;
VAR 
  old_temp: DOUBLE;
  ptemp: ^DOUBLE;

BEGIN
  IF isNAN( temp) THEN
  BEGIN
    delta_gammln:= QNAN;
EXIT;
  END;

  delta_gammln:= 0;
  ptemp:=@temp;
{* Make a decision whether to compute directly on underflow grounds *}

(*  m:= LN( 2*MAX( v, extra));
  IF extra * m > delta_gammln_limit THEN
*)

{* Avoid overflows in temp *}
  old_temp:= temp;
  REPEAT
    IF (extra>delta_gammln_limit)
    OR (ipwr( v+extra, -extra) = 0)
    OR isNAN( temp) THEN
    BEGIN
      temp:= old_temp; {* in case we screwed up last time *}
      IF isNAN( gammln_v) THEN
        gammln_v:= gammln( v);
      delta_gammln:= gammln( v+extra) - gammln_v;
    END
    ELSE
    ASM
      push edi;
      mov edi, ptemp;
      fld qword ptr[ edi];
      fld v;
      mov ecx, DWORD PTR [extra];
      jcxz @2;
      fwait;
    @1:
      fmul st(1), st;
      fld1;
      faddp st(1),st;
      fwait;
      loop @1;

    @2:
      fcomp st(1);
      fstp qword ptr [edi];
      // fstp tbyte ptr [edi];
      fwait;
      pop edi;
    END;
  UNTIL NOT isNAN( temp);
END;

{****************************************************************************}

FUNCTION ln_beta_fn( a,b: DOUBLE):
         DOUBLE;
VAR lb, temp,
    gammln_a: DOUBLE;
    c: INTEGER;
BEGIN
  ln_beta_fn:= QNAN;
  IF a*b<=0 THEN
EXIT;

  IF FRAC( a) + FRAC( b) > 0 THEN
    ln_beta_fn:= gammln( a) + gammln( b) - gammln( a+b)
  ELSE BEGIN
    temp:= 1;
    IF a>b THEN BEGIN
      c:= ROUND( b); b:= a; a:= c;
    END ELSE
      c:= ROUND( a);

    gammln_a:= gammln( c);
    lb:= delta_gammln( b, c, gammln_a, temp);
    IF lb=0 THEN
      ln_beta_fn:= gammln_a - LN( temp)
    ELSE
      ln_beta_fn:= gammln_a - lb;
  END;
END;

{****************************************************************************}

FUNCTION median(x: pseudo_array; n: LONGINT): DOUBLE;
LABEL 1;
CONST
   big=1.0e30;
   afac=1.5;
   amp=1.5;
VAR
   np,nm,j: integer;
   xx,xp,xm,sumx,sum,eps: DOUBLE;
   stemp,dum,ap,am,aa,a: DOUBLE;
BEGIN
   a := 0.5*(x(2)+x(1));
   eps := abs(x(2)-x(1));
   ap := big;
   am := -big;
1:   sum := 0.0; sumx := 0.0; np := 0; nm := 0; xp := big; xm := -big;
   FOR j := 1 to n DO BEGIN
      xx := x(j);
      IF (xx <> a) THEN BEGIN
         IF (xx > a) THEN BEGIN
            np := np+1;
            IF (xx < xp) THEN xp := xx END
         ELSE IF  (xx < a) THEN BEGIN
            nm := nm+1;
            IF (xx > xm) THEN xm := xx
         END;
         dum := 1.0/(eps+abs(xx-a));
         sum := sum+dum;
         sumx := sumx+xx*dum
      END
   END;
   stemp := (sumx/sum)-a;
   IF ((np-nm) >= 2) THEN BEGIN
      am := a;
      IF (stemp < 0.0) THEN aa := xp
      ELSE aa := xp+stemp*amp;
      IF (aa > ap) THEN aa := 0.5*(a+ap);
      eps := afac*abs(aa-a);
      a := aa;
      GOTO 1 END
   ELSE IF ((nm-np) >= 2) THEN BEGIN
      ap := a;
      IF (stemp > 0.0) THEN aa := xm
      ELSE aa := xm+stemp*amp;
      IF (aa < am) THEN aa := 0.5*(a+am);
      eps := afac*abs(aa-a);
      a := aa;
      GOTO 1 END
   ELSE IF (n MOD 2) = 0 THEN BEGIN
      IF (np = nm) THEN median := 0.5*(xp+xm)
      ELSE IF (np > nm) THEN median := 0.5*(a+xp)
      ELSE median := 0.5*(xm+a) END
   ELSE BEGIN
      IF (np = nm) THEN median := a
      ELSE IF (np > nm) THEN median := xp
      ELSE median := xm
   END
END;

{****************************************************************************}

FUNCTION chi_sig( chi_sq: DOUBLE;
                  df:     INTEGER):
         DOUBLE;

BEGIN

  chi_sig:=GammQ( df/2, chi_sq/2);

END;

(****************************************************************************)

FUNCTION LN_1_minus_Phi( x: DOUBLE):
  DOUBLE;
CONST
  SQRT_half = 0.7071067811865;
VAR
  t, z: DOUBLE;
BEGIN
(*  Phi = 1 - erfcc( x * SQRT_half) / 2; *)
  x:= x * SQRT_half;
  IF x<-8 THEN
   RESULT:= 0
  ELSE
  BEGIN
    z := abs(x);
    t := 1/(1+0.5*z);
    RESULT:= -SQR( z) + LN( t/2) -1.26551223+t*(1.00002368+
       t*(0.37409196+t*(0.09678418+t*(-0.18628806+
       t*(0.27886807+t*(-1.13520398+t*(1.48851587+
       t*(-0.82215223+t*0.17087277))))))));
    IF x < 0 THEN
      RESULT:= LN( 1-EXP( RESULT));
  END;
END;

(****************************************************************************)

FUNCTION cum_normal_prob( x: DOUBLE):
         DOUBLE;
CONST sqrt_half =  0.7071067811865;
BEGIN
  cum_normal_prob:= 1 - erfcc( x * SQRT_half) / 2;
END;

{****************************************************************************}

FUNCTION cum_NB_prob( s: INTEGER; v, p: SINGLE): SINGLE;
{* Prob (<s) = prob (<=s-1) *}
BEGIN
  IF s>0 THEN
    cum_NB_prob:= betai( v, s, p)
  ELSE
    cum_NB_prob:= 0;
END;

{****************************************************************************}

FUNCTION cum_Poisson_prob( s: INTEGER; lambda: SINGLE): SINGLE;
BEGIN
  IF s>0 THEN
    cum_Poisson_prob:= GammQ_gln( s, lambda, 0, FALSE)
  ELSE
    cum_Poisson_prob:= 0;
END;

{****************************************************************************}

FUNCTION Normal( alpha: DOUBLE):
         DOUBLE;

CONST c: ARRAY[ 0..2] OF DOUBLE = ( 2.515517, 0.802853, 0.010328);
      d: ARRAY[ 1..3] OF DOUBLE = ( 1.432788, 0.189269, 0.001308);

VAR i: INTEGER;
    num, denom,
    t, t_power: DOUBLE;

BEGIN
IF alpha < 0.5 THEN
  Normal:= - Normal( 1 - alpha)
ELSE
BEGIN
  t:= SQRT( - 2 * LN( 1 - alpha));

  num:= c[ 0];
  denom:= 1; { = d[ 0]}
  t_power:= t;

  FOR i:= 1 TO 2 DO
  BEGIN
    num:= num + t_power * c[ i];
    denom:= denom + t_power * d[ i];
    t_power:= t_power * t;
  END;

  denom:= denom + d[ 3] * t_power;
  Normal:= t - num / denom;
END;
END;

{****************************************************************************}

FUNCTION Hermite( n: INTEGER; x: SINGLE): SINGLE;
VAR h0, h1, h2: DOUBLE;
    i: INTEGER;
BEGIN
  h0:= 1; h1:= x;
  IF n=0 THEN
    h2:= h0
  ELSE
  IF n=1 THEN
    h2:= h1
  ELSE
  FOR i:= 1 TO n-1 DO
  BEGIN
    h2:= x*h1-i*h0;
    h0:= h1;
    h1:= h2;
  END;

  Hermite:= h2;
END;

{****************************************************************************}

FUNCTION Student( df: INTEGER;
                  alpha: DOUBLE):
         DOUBLE;
VAR p: SINGLE;
BEGIN
  p:= 1 - BetaI( 0.5 * df, 0.5, df/(df+SQR(alpha)));
  IF alpha<0 THEN
    Student:= (1-p)/2
  ELSE
    Student:= (1+p)/2;
END;

(****************************************************************************)

FUNCTION Student_pp( df: INTEGER;
                     pp:  DOUBLE):
         DOUBLE;
VAR swap: BOOLEAN;
    x:    DOUBLE;
BEGIN
  swap:= pp>0.5;
  IF swap THEN
    pp:= 1-pp;
  x:= inv_betai( 0.5*df, 0.5, 2*pp);
  x:= sqrt( df/x-df);
  IF NOT swap THEN
    x:= -x;
  Student_pp:= x;
END;

{****************************************************************************}

FUNCTION inv_NB_rnd( v, p, r: SINGLE): INTEGER;
VAR rhat, term: DOUBLE;
    s:          INTEGER;
BEGIN
{* Get a starting value using Gamma approx to NB *}

  s:= TRUNC( inv_gammp( v*(1-p), r) / p);
  rhat:= cum_NB_prob( s, v, p);
  IF rhat > r THEN
    DEC( s);
  term:= EXP( gammln( v+s) - gammln( v) - gammln( s+1))
       * pwr( p, v) * pwr( 1-p, s);

  IF rhat <= r THEN
  WHILE rhat + term < r DO
  BEGIN
    rhat:= rhat + term;
    term:= term * (1-p) * (v+s) / (s+1);
    INC( s);
  END
  ELSE
  WHILE (s>0) AND (rhat-term > r) DO
  BEGIN
    rhat:= rhat - term;
    term:= term * s / ((v+s-1)*(1-p));
    DEC( s);
  END;

  inv_NB_rnd:= s;
END;

{****************************************************************************}

FUNCTION inv_Poisson_rnd( lambda, r: SINGLE): INTEGER;
VAR s: INTEGER;
    term, rhat: DOUBLE;

BEGIN
{* Start by checking that we're not in the zero prob region- this avoids
   numerical problems if lambda is very small *}

  inv_Poisson_rnd:= 0;
  IF r<EXP(-lambda) THEN
    EXIT;

{* Set code for failure *}
  inv_Poisson_rnd:= -1;
  IF r>=1 THEN
    EXIT;

{* Start with Gamma approx, as for inv_NB *}
  rhat:= inv_GammP( lambda, r);
  IF isNAN( rhat) OR (rhat > maxint) THEN
    EXIT;
  s:= TRUNC( rhat);

  rhat:= cum_Poisson_prob( s, lambda);
  IF isNAN( rhat) THEN
    EXIT;

  IF rhat > r THEN
    DEC( s);
  term:= EXP( -lambda - gammln( s+1) + s * LN( lambda)); (* * pwr( lambda, s);*)
  IF isNAN( term) THEN
    EXIT;

  IF rhat <= r THEN
  WHILE rhat + term < r DO
  BEGIN
    rhat:= rhat + term;
    term:= term * lambda / s;
    INC( s);
    IF s<0 THEN
      EXIT;
  END
  ELSE
  WHILE rhat - term > r DO
  BEGIN
    rhat:= rhat - term;
    term:= term * s / lambda;
    DEC( s);
  END;

  inv_Poisson_rnd:= s;
END;

{****************************************************************************}

VAR binomial_term,
    binomial_lb: DOUBLE;

FUNCTION cum_Bin_prob( n, r: INTEGER; p: SINGLE):
         SINGLE;     {* prob of <r out of n @ probability p *}
CONST r_limit = 8;
VAR j: INTEGER;
    sum: DOUBLE;
BEGIN
  cum_Bin_prob:= QNAN;
  binomial_term:= QNAN;
  binomial_lb:= QNAN;
  IF (n<=0) OR (r<0) OR (r>n+1) OR (p<0) OR (p>1) THEN
    EXIT;

  IF r=0 THEN
    cum_Bin_prob:= 0
  ELSE
  IF r>n-r+1 THEN
    cum_bin_prob:= 1 - cum_Bin_prob( n, n-r+1, 1-p)
  ELSE
  IF r<r_limit THEN
  BEGIN
    binomial_term:= ipwr( 1-p, n);
    sum:= binomial_term;
    FOR j:= 1 TO r-1 DO
    BEGIN
      binomial_term:= binomial_term * (n-j+1) * p / ( j * (1-p));
      sum:= sum + binomial_term;
    END;
    cum_Bin_prob:= sum;
  END
  ELSE
  IF p*(1-p)=0 THEN
    cum_bin_prob:= 1-p
  ELSE
  BEGIN
    binomial_LB:= ln_beta_fn( r, n-r+1);
    cum_Bin_prob:= 1-BetaI_known_beta( r, n-r+1, p, binomial_lb);
  END;
END;

{****************************************************************************}

FUNCTION inv_Bin_rnd( n: INTEGER; p, r: SINGLE):
         INTEGER;
VAR guess: INTEGER;
    a,b: SINGLE;
    cp, term: DOUBLE;
BEGIN
  inv_Bin_rnd:= -1;
  IF (p<0) OR (r<0) OR (p>1) OR (r>1) OR (n<0) THEN
  BEGIN
    pause( 'Illegal argument(s) to INV_BIN_RND');
    EXIT;
  END;

  IF (n=0) OR (r<=ipwr(1-p,n)) THEN
    inv_Bin_rnd:= 0
  ELSE
  IF r>=1-ipwr(p,n) THEN
    inv_Bin_rnd:= n
  ELSE
  BEGIN
{* Approximate Binomial distribution by a scaled beta. The full "inv_betai"
   routine is very slow and excessively accurate, so I have just used the
   approximate version *}
    a:= (n-1)*p;
    b:= (n-1)*(1-p);
    g2:= ln_beta_fn( a, b);
    guess:= TRUNC( n * inv_betai_starting_value( a, b, r, g2 (* ln_beta_fn( a, b)*))-0.5);
    G2:= GUESS;
    guess:= LMAX( 1, LMIN( guess, n-1)); {* as extremes have already been ruled out *}
    cp:= cum_Bin_prob( n, guess, p); {* which will set up bin_term or bin_lb *}
    IF isNAN( binomial_term) THEN
    BEGIN
      IF isNAN( binomial_lb) THEN
{*    shouldn't happen *}
        binomial_lb:= EXP( -ln_beta_fn( n-guess+1, guess+1))/(n+1)
      ELSE
        binomial_lb:= EXP( -binomial_lb) / guess;
      term:= ipwr( p, guess) * ipwr( 1-p, n-guess) * binomial_lb;
    END
    ELSE
      term:= (n-guess+1) * p * binomial_term / ((1-p) * guess);

{*  The conditions on "guess" below just guard against rounding error *}

    WHILE (guess>0) AND (cp>r) DO
    BEGIN
      DEC( guess);
      term:= term * (1/p-1) * (guess+1)/(n-guess);
      cp:= cp - term;
    END;

    WHILE (guess<n) AND (cp+term<r) DO
    BEGIN
      cp:= cp + term;
      INC( guess);
      term:= term * p * (n-guess+1) / ((1-p) * guess);
    END;

    inv_Bin_rnd:= guess;
  END;
END;

{****************************************************************************}

FUNCTION Beta_rnd( a, b: SINGLE): SINGLE;
VAR ga, gb: SINGLE;
BEGIN
  ga:= Gam_rnd( a); gb:= Gam_rnd( b);
  Beta_rnd:= ga / (ga+gb);
END;

{****************************************************************************}

FUNCTION GamDevR( alpha: DOUBLE):
         DOUBLE;

{* Returns a Gamma random deviate with alpha < 1 *}

CONST alpha_limit = 0.99;

VAR y: DOUBLE;

BEGIN
  IF alpha > alpha_limit THEN
  BEGIN
    GamDevR:= GamDevR( alpha*0.6) + GamDevR( alpha*0.4);
    EXIT;
  END;

  IF random < GammP( alpha, 1) THEN
  REPEAT {* < 1 *}
    y:= pwr( random, 1/alpha);
  UNTIL random < EXP( -y)
  ELSE
  REPEAT {* > 1 *}
    y:= 1 - LN( 1 - random)
{* strictly, we don't need the "1-" inside "LN", but arises in derivation *}
  UNTIL pwr( random, 1/(alpha-1)) >= y;

  GamDevR:= y;
END;

{****************************************************************************}

FUNCTION Gam_rnd( alpha: DOUBLE):
         DOUBLE;

VAR f: DOUBLE;

BEGIN
  IF alpha>65520 THEN
    Gam_rnd:= alpha + SQRT( alpha) * Norm_rnd
  ELSE
  BEGIN
    f:= FRAC( alpha);
    IF f = 0 THEN
      Gam_rnd:= GamDev( ROUND( alpha))
    ELSE
      Gam_rnd:= GamDev( TRUNC( alpha)) + GamDevR( f);
  END;
END;

(****************************************************************************)
(*
FUNCTION constrained_GamDevR( alpha, gp, a, b, pa, pb: DOUBLE):
         DOUBLE;

{* Returns a Gamma random deviate with alpha < 1, between a & b, where
   pa = GammP( alpha, a), pb = GammP( alpha, b), gp = GammP( alpha, 1) *}

CONST alpha_limit = 0.99;

VAR y: DOUBLE;

{*******************************}

  FUNCTION con_random: DOUBLE;
  BEGIN
    con_random:= lower + ( upper-lower)*random;
  END;

{*******************************}

BEGIN
  IF alpha > alpha_limit THEN
  BEGIN
{* Fuck it- this should be close enough! *}
    constrained_GamDevR:= constrained_GamDev( 1, gp, a, b, pa, pb);
    EXIT;
  END;

  IF b < 1 THEN
  BEGIN
    lt1:= TRUE;
    lower:= a;
    upper:= b;
  END
  ELSE
  IF a > 1 THEN
  BEGIN
    lt1:= FALSE;
    upper:= 1-EXP(1-b);
    lower:= 1-EXP(1-a);
  END
  ELSE
  BEGIN
    lt1:= random < (gp-pa)/(pb-pa);
    IF lt1 THEN
    BEGIN
      lower:= a;
      upper:= 1;
    ELSE
    BEGIN
      lower:= 0;
      upper:= 1-EXP(1-b);
    END;
  END;

  IF lt1 THEN
  REPEAT {* < 1 *}
    y:= pwr( con_random, 1/alpha);
  UNTIL random < EXP( -y)
  ELSE
  REPEAT {* > 1 *}
    y:= 1 - LN( 1 - con_random)
  UNTIL pwr( random, 1/(alpha-1)) >= y;

  constrained_GamDevR:= y;
END;

{****************************************************************************}

FUNCTION constrained_Gam_rnd( alpha, gp, a, b, pa, pb: DOUBLE):
         DOUBLE;

VAR f: DOUBLE;

BEGIN
  f:= FRAC( alpha);
  IF f = 0 THEN
    constrained_Gam_rnd:= constrained_GamDev( ROUND( alpha), gp, a, b, pa, pb)
  ELSE
  BEGIN
    f:= constrained_GamDevR( alpha, gp, 0, b, 0, pb);
    IF f<a THEN
      constrainGam_rnd:= f
      + constrained_GamDev( TRUNC( alpha), gp, a-f, b-f,
                           GammP( alpha, a-f), GammP( alpha, b-f));
END;
*)
(****************************************************************************)

FUNCTION NB_rnd( n: INTEGER;
                      p: DOUBLE):
         LONGINT;
BEGIN
  NB_rnd:= Poi_rnd( Gam_rnd( n) * (1/p - 1));
END;

(****************************************************************************)

PROCEDURE solve_tridiag(
  a, b, c, r, u, gam: PDOUBLE_ARRAY;
  n: PLONGINT);
VAR
  bet: DOUBLE;
  j: LONGINT;
BEGIN
  bet:= b[ 1];
  u[ 1]:= r[ 1] / bet;
  FOR j:= 2 TO n^ DO
  BEGIN
    gam[ j]:= c[ j-1] / bet;
    bet:= b[ j] - a[ j] * gam[ j];
    IF bet=0 THEN
    BEGIN
      u[ 1]:= qNAN;
EXIT;
    END;
    u[ j]:= (r[ j] - a[ j] * u[ j-1]) / bet;
  END;

  FOR j:= n^-1 DOWNTO 1 DO
    u[ j]:= u[ j] - gam[ j+1] * u[ j+1];
END;

(****************************************************************************)

FUNCTION select(
  data: PDOUBLE_ARRAY;
  k, n: INTEGER):
  DOUBLE;

  PROCEDURE swap(
      i, j: INTEGER);
    VAR x: DOUBLE;
  BEGIN
    IF (LMIN( i, j) < 1) OR (LMAX( i, j) > n) THEN
HALT;
    x:= data[ i]; data[ i]:= data[ j]; data[ j]:= x;
  END;

VAR
  i, ir, j, l, mid: INTEGER;
  a: DOUBLE;

BEGIN
  l:= 1;
  ir:= n;
  REPEAT
    IF ir <= l+1 THEN
    BEGIN
      IF (ir = l+1) AND (data[ ir] < data[ l]) THEN
        swap( l, ir);
      select:= data[ k];
  BREAK;
    END
    ELSE BEGIN
      mid:= (l + ir) DIV 2;
      swap( mid, l+1);
      IF data[ l+1] > data[ ir] THEN
        swap( l+1, ir);
      IF data[ l] > data[ ir] THEN
        swap( l, ir);
      IF data[ l+1] > data[ l] THEN
        swap( l, l+1);

      i:= l+1;
      j:= ir;
      a:= data[ l];

      REPEAT
        INC( i);
        IF data[ i]<a THEN
      CONTINUE;

        REPEAT
          DEC( j);
        UNTIL data[ j]<=a;

        IF j<i THEN
      BREAK;

        swap( i, j);
      UNTIL FALSE;

      data[ l]:= data[ j];
      data[ j]:= a;

      IF j>=k THEN
        ir:= j-1;
      IF j<=k THEN
        l:= i;
    END; {* partition > 2 elements *}
  UNTIL FALSE;
END;

(****************************************************************************)

PROCEDURE reset_80x87;
VAR control_word: WORD;
ASM
// DON'T want this to have any effect in R
// Not sure if it's still needed in other applications
{$IFNDEF R}
{* Preserve old crash settings *}
  fstcw control_word;
  fwait;
  finit;
  fwait;
  fldcw control_word;
{$ENDIF}
END;

(****************************************************************************)

function Get8087CW:word;
begin
  asm
    fstcw result
  end;
end;

{****************************************************************************}
{****************************************************************************}

{$WARNINGS ON}
{$HINTS ON}
VAR
  de2: DOUBLE;
  i: INTEGER;
{$IFDEF R}
TYPE
  TRwin_fpset_proctype= procedure; cdecl;

VAR
  Rwin_fpset: TRwin_fpset_proctype;

INITIALIZATION
  load_R_routines( [@@Rwin_fpset], ['Rwin_fpset']);
  Rwin_fpset();
  Set8087CW(Get8087CW);
{$ELSE}
INITIALIZATION
{$ENDIF}

  pausing:= TRUE;
  gliset:= 0;
  ln_beta_for_betai:= QNAN;

  double_eps:= 1;
  REPEAT
    de2:= double_eps/2;
    IF(1-de2) < 1 THEN
      double_eps:= de2
    ELSE
  BREAK;
  UNTIL FALSE;

  WITH convergence_block DO
  BEGIN
    tolerance:= 1e-3;
    size_of_real:= SizeOf( REAL);
  END;

  // Chain of stored results for expmem
  GetMem( head, SizeOf( expmem_rec));
  head. x:= 0;
  head. exp_x:= 1;
  head. next:= head;
  orig_head:= head;

  FOR i:= 1 TO n_expmem DO BEGIN
    GetMem( head. next, SizeOf( expmem_rec));
    head:= head. next;
    head. x:= 0;
    head. exp_x:= 1;
    head. next:= orig_head;
  END;

  last_exp_x:= 0;
  last_exp_result:= 1;

  last_inv_x:= 1;
  last_inv_result:= 1;

  last_inv_logit_x:= 0;
  last_inv_logit_result:= 0.5;
END.
