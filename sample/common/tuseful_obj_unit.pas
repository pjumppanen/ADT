unit tuseful_obj_unit;
interface

USES
  Useful,
  Math,
  Maths32;

TYPE
  Tuseful_obj = CLASS( Teasy_alloc_object)
    ncheb: INTEGER;
    incheb: DOUBLE; // inverse
    cheb_x{ncheb}, cheb_wt{ncheb}: ARRAY_1D;

    n_nueven, dummy_nueven: INTEGER; // for t-distro with odd df, precomputed stuff
    nueven{n_nueven}, nterms_nueven{n_nueven}: ARRAY_1L;
    ratto_nueven{n_nueven}, dt_ratto_nueven{n_nueven}: ARRAY_1D;
    cft_nueven{n_nueven,dummy_nueven}: ARRAY_2D;

    {$IFNDEF AD}
    ismall{257}, ibig{257}, expo_shift{256}: ARRAY_1L;
    compl{256}, acc_cval{256}: ARRAY_1D;
    {$ELSE}{AD}
    n_gamlanc, n_laugamp: INTEGER;
    gamlanc_cof{-1:n_gamlanc}: ARRAY_1D;
    sqrt_two_pi: DOUBLE;
    {$ENDIF}{AD}
    CONSTRUCTOR create();
    {$IFNDEF AD}
    PROCEDURE set_n_nueven(
        CONST _n_nueven: INTEGER);
    PROCEDURE set_nueveni(
        CONST nu, i_nueven: INTEGER);
    FUNCTION pt_nueveni(
        CONST x: DOUBLE;
        CONST i_nueven: INTEGER):
      DOUBLE;
    {$ENDIF}{AD}
    FUNCTION dt_nueveni(
        CONST x: DOUBLE;
        CONST i_nueven: INTEGER):
      DOUBLE;
    FUNCTION mean_t_nueveni_trunclt(
        CONST x, pt: DOUBLE;
        CONST i_nueven: INTEGER):
      DOUBLE;
    FUNCTION sum_log1m(
        CONST xpos{count}: ARRAY_1D;
        CONST first, count: INTEGER):
      DOUBLE;
    {D; sum_log1m; sum_log1m; xpos; dsum_log1m}
    {D; dsum_log1m; dsum_log1m; xpos; ddsum_log1m}
    {D; ddsum_log1m; ddsum_log1m; xpos; dddsum_log1m}
    FUNCTION dsum_log1m(
        CONST xpos{count}, xposdir1{count}: ARRAY_1D;
        CONST first, count: INTEGER;
        VAR   sum_log1m_result: DOUBLE):
      DOUBLE;
    FUNCTION ddsum_log1m(
        CONST xpos{count}, xposdir1{count}, xposdir2{count}: ARRAY_1D;
        CONST first, count: INTEGER;
        VAR   sum_log1m_result, dsum_log1m_result: DOUBLE):
      DOUBLE;
    FUNCTION dddsum_log1m(
        CONST xpos{count}, xposdir1{count}, xposdir2{count}, xposdir3{count}: ARRAY_1D;
        CONST first, count: INTEGER;
        VAR   sum_log1m_result, dsum_log1m_result, ddsum_log1m_result: DOUBLE):
      DOUBLE;
    FUNCTION logdet_and_chol(
        CONST ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
        CONST nchol: INTEGER):
      DOUBLE; VIRTUAL;
    FUNCTION logdet_and_chol_neg(
        CONST neg_ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
        CONST nchol: INTEGER):
      DOUBLE; VIRTUAL;
    PROCEDURE backsolve_chol(
        CONST rchol{nchol,nchol}: ARRAY_2D;
        CONST target{nchol}, sol{nchol}: ARRAY_1D;
        CONST nchol: INTEGER); VIRTUAL;
    FUNCTION quadform(
        CONST xqf{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER):
      DOUBLE; VIRTUAL;
    PROCEDURE to_binc(
        CONST pars{d1,d2}: ARRAY_2D;
        CONST d1, d2: INTEGER);
    PROCEDURE from_binc(
        CONST pars{d1,d2}: ARRAY_2D;
        CONST d1, d2: INTEGER);
    PROCEDURE to_binc_x11(
        CONST pars{d1}: ARRAY_1D;
        CONST start, d1, d2: INTEGER);
        //ADSPLIT to_binc_x11_2
    PROCEDURE to_binc_x11_2(
        CONST pars{nnnn, d1}: ARRAY_2D;
        CONST nnnn, iiii, start, d1, d2: INTEGER); // ugly AD-related fudge
//    PROCEDURE to_binc_x11_3(
//        CONST pars{dprod}: ARRAY_1D;
//        CONST d1, d2, dprod: INTEGER); // dprod=d1*d2-1
    PROCEDURE from_binc_x11(
        CONST pars{d1}: ARRAY_1D;
        CONST start, d1, d2: INTEGER);
    PROCEDURE to_binc1(
        CONST pars{d1}: ARRAY_1D;
        CONST start, d1, d2: INTEGER);
    PROCEDURE to_binc12(
        CONST pars{nnnn, d1}: ARRAY_2D;
        CONST nnnn, iiii, start, d1, d2: INTEGER); // ugly AD-related fudge
    PROCEDURE from_binc1(
        CONST pars{d1}: ARRAY_1D;
        CONST start, d1, d2: INTEGER);
    {B; quadform; quadform; xqf; quadform_b}
    {D; quadform; quadform; xqf; quadform_d}
    {D; quadform_b; xqf_b; xqf; quadform_b_d}
    PROCEDURE quadform_b(
        CONST xqf{nqf}, xqf_b{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER;
        VAR   xqf_wt: DOUBLE); VIRTUAL;
    FUNCTION quadform_d(
        CONST xqf{nqf}, xqf_dir{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER;
        VAR   hxh: DOUBLE):
      DOUBLE; VIRTUAL;
    PROCEDURE quadform_b_d(
        CONST xqf{nqf}, xqf_dir{nqf}, xqf_b{nqf}, xqf_bd{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER;
        VAR   xqf_wt: DOUBLE); VIRTUAL;
    FUNCTION asymp(
        CONST _x, _thresh: DOUBLE):
      DOUBLE;
    FUNCTION nearlymin(
        CONST _a, _b: DOUBLE):
      DOUBLE;
    FUNCTION nearlymax(
        CONST _a, _b: DOUBLE):
      DOUBLE;
    FUNCTION laugamp(
        CONST _y, _p, _lgamma_p: DOUBLE;
        CONST _calc_lgamma_p: BOOLEAN):
      DOUBLE;
    FUNCTION lgamma(
        CONST _x: DOUBLE):
      DOUBLE;

    {$IFNDEF AD}
    // should make tridag AD-able...
    PROCEDURE tridag(
      CONST
        n: INTEGER;
      CONST
      a{n}, b{n}, c{n}, r{nn}, u{n}, gam{n}: ARRAY_1D); VIRTUAL;

    PROCEDURE prepare_for_chint(
        CONST _ncheb: INTEGER);
    {$ENDIF}{AD}
  END;

  // Stuff for lgamma & gammln
{$IFNDEF AD}
CONST
  n_laugamp=100; // gives at least 15 digits of accuracy
  n_gamlanc = 9;
  gamlanc_cof: ARRAY[ -1..n_gamlanc] OF DOUBLE = (
    1.000000000000000174663,
    5716.400188274341379136,
    -14815.30426768413909044,
    14291.49277657478554025,
    -6348.160217641458813289,
    1301.608286058321874105,
    -108.1767053514369634679,
    2.605696505611755827729,
    -0.7423452510201416151527e-2,
    0.5384136432509564062961e-7,
    -0.4023533141268236372067e-8);
{$ENDIF}{AD}

implementation

CONSTRUCTOR Tuseful_obj. create();
BEGIN
  INHERITED;
  ncheb:= 0;
  // n_nuodd:= 0;
  n_nueven:= 1;
  alloc_arrays( [@nueven, @nterms_nueven], [1], [1], SizeOf( nueven[1]));
  alloc_arrays( [@ratto_nueven, @dt_ratto_nueven], [1], [1], SizeOf( ratto_nueven[1]));
  alloc_arrays( [@cft_nueven], [1], [1], SizeOf( cft_nueven[1])); // outer of ragged only
  nueven[ 1]:= -1; // Gaussian; no need for cfts

  // 257 in next line because nbig<=256 & ibig[nbig+1]:= j
  {$IFNDEF AD}
  alloc_arrays( [@ismall, @ibig, @expo_shift], [257], [1], SizeOf( LONGINT));
  alloc_arrays( [@compl, @acc_cval], [256], [1], SizeOf( DOUBLE));
  {$ENDIF}{AD}
END;

{$IFNDEF AD}
// This should be AD-able when I get round to it...
PROCEDURE Tuseful_obj. tridag(
  CONST
    n: INTEGER;
  CONST
    a{n}, b{n}, c{n}, r{n}, u{n}, gam{n}: ARRAY_1D);
VAR
  bet, ibet: DOUBLE;
  j: INTEGER;
BEGIN
  // Mostly from Numerical Recipes, recoded into Pascal:
  bet:= b[1];
  ibet:= 1/bet;
  u[1]:= r[1] * ibet;
  FOR j:= 2 TO n DO BEGIN
    gam[j]:= c[j-1] * ibet;
    bet:= b[j] - a[j]*gam[j];
    {IF bet=0 STOP...}
    ibet:= 1/bet;
    u[j]:= (r[j]-a[j]*u[j-1]) * ibet;
  END;

  FOR j:= n-1 DOWNTO 1 DO BEGIN
    DECR( u[j], gam[j+1] * u[j+1]);
  END;
END;

TYPE
  ftar = ARRAY[ FALSE..TRUE] OF DOUBLE;
  QWORD_AR = ARRAY[0..3] OF WORD;

{$POINTERMATH ON}
FUNCTION Tuseful_obj. sum_log1m(
    CONST xpos{count}: ARRAY_1D;
    CONST first, count: INTEGER):
  DOUBLE;
CONST
  scale2: ftar = (1,2);
  scale3: ftar = (0,1);
  LN2: DOUBLE = 0.69314718055994529;
VAR
  nbig, nsmall, j, odd, expo, expotot, this_expo_shift, new_expo,
    leftover, iloop: INTEGER;
  big: BOOLEAN;
  eps, this_x, compx, prod: DOUBLE;
  txpos: ARRAY_1D;
BEGIN
  RESULT:= 0;
  txpos:= @xpos[first-1];
  FOR iloop:= 1 TO (count SHR 8) DO BEGIN
    zero( expo_shift[1], 256);
    zero( ismall[1], 256);
    zero( ibig[1], 256);

    nbig:= 0;
    nsmall:= 0;
    FOR j:= 1 TO 256 DO BEGIN
      big:= txpos[j]>0.5;
      compl[ j]:= 1-txpos[ j];
      ibig[ nbig+1]:= j;
      ismall[ nsmall+1]:= j;
      nbig += BYTE( big);
      nsmall += BYTE( NOT big);
    END;

    expotot:= 0;
    IF nsmall>0 THEN BEGIN
      eps:= 0;
      FOR j:= 1 TO nsmall DO BEGIN
        this_x:= txpos[ ismall[ j]];
        eps += this_x-eps*this_x;
        big:= eps>0.5;
        eps:= scale2[big]*eps-scale3[big];
        expotot += BYTE( big);  // should be DECR-- sorted out below
      END;
      RESULT += log1p( -eps);
    END;

    IF nbig>0 THEN BEGIN
      expotot:= (-expotot) SHL 4;
      odd:= $10;
      prod:= 1;
      // ?Should break this into blocks to prevent underflow (and reduce mispreds)
      // Be sure to load each double completely to avoid misaligned cache splits
      // ... (ie not just high-order)
      // ... necessary because the ibig indexing.
      FOR j:= 1 TO nbig DO BEGIN
        compx:= compl[ ibig[ j]];
        expo:= QWORD_AR( compx)[3];
        new_expo:= $3FF0-odd;
        QWORD_AR( compx)[3]:= new_expo OR (expo AND $F); // keep mantissa bitss
        compl[ ibig[ j]]:= compx;
        this_expo_shift:= (expo AND $7FF0) - new_expo;
        expo_shift[ ibig[ j]]:= this_expo_shift;
        expotot += this_expo_shift;
        prod:= prod*compx;
        odd:= $10-odd;
      END;
      RESULT += LN( prod);
      expotot:= (-expotot) SHR 4;
    END;

    RESULT -= expotot * LN2;
    txpos += 256;
    // LONGINT( txpos):= LONGINT( txpos) + 256*SizeOf( txpos[1]);
  END;

  leftover:= count AND $FF;
  IF leftover>0 THEN BEGIN
    zero( expo_shift[1], leftover);
    zero( ismall[1], leftover);
    zero( ibig[1], leftover);

    nbig:= 0;
    nsmall:= 0;
    FOR j:= 1 TO leftover DO BEGIN
      big:= txpos[j]>0.5;
      compl[ j]:= 1-txpos[ j];
      ibig[ nbig+1]:= j;
      ismall[ nsmall+1]:= j;
      INCR( nbig, BYTE( big));
      INCR( nsmall, BYTE( NOT big));
    END;

    expotot:= 0;
    IF nsmall>0 THEN BEGIN
      eps:= 0;
      FOR j:= 1 TO nsmall DO BEGIN
        this_x:= txpos[ ismall[ j]];
        INCR( eps, this_x-eps*this_x);
        big:= eps>0.5;
        eps:= scale2[big]*eps-scale3[big];
        INCR( expotot, BYTE( big));  // should be DECR-- sorted out below
      END;
      INCR( RESULT, log1p( -eps));
    END;

    IF nbig>0 THEN BEGIN
      odd:= $10;
      prod:= 1;
      expotot:= (-expotot) SHL 4;
      // ?Should break this into blocks to prevent underflow (and reduce mispreds)
      // Be sure to load each double completely to avoid misaligned cache splits (ie not just high-order)
      // ... necessary because the ibig indexing.
      FOR j:= 1 TO nbig DO BEGIN
        compx:= compl[ ibig[ j]];
        expo:= QWORD_AR( compx)[3];
        new_expo:= $3FF0-odd;
        QWORD_AR( compx)[3]:= new_expo OR (expo AND $F); // keep mantissa bitss
        compl[ ibig[ j]]:= compx;
        this_expo_shift:= (expo AND $7FF0) - new_expo;
        expo_shift[ ibig[ j]]:= this_expo_shift;
        INCR( expotot, this_expo_shift);
        prod:= prod*compx;
        odd:= $10-odd;
      END;
      INCR( RESULT, LN( prod));
      expotot:= (-expotot) SHR 4;
    END;

    DECR( RESULT, expotot * LN2);
  END;
END;

FUNCTION Tuseful_obj. dsum_log1m(
    CONST xpos{count}, xposdir1{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  a, b, cval, zstar: DOUBLE;
  j, leftover, iloop: INTEGER;
  txpos, txposdir1: ARRAY_1D;
BEGIN
  // compl and expo_shift already contain 1-x in the form z, log_2(k)
  RESULT:= 0;
  sum_log1m_result:= 0;
  txpos:= @xpos[ first-1];
  txposdir1:= @xposdir1[ first-1];
  FOR iloop:= 1 TO (count SHR 8) DO BEGIN
    INCR( sum_log1m_result, sum_log1m( txpos, 1, 256));

    a:= 0;
    b:= 1;
    FOR j:= 1 TO 256 DO BEGIN
      cval:= txposdir1[ j];
      // cval:= cval * 2^(-expo_shift[ j]);
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3] - expo_shift[ j];
      zstar:= compl[ j];
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
    txposdir1 += 256;
    txpos += 256;
  END;

  leftover:= count AND $FF;
  IF leftover>0 THEN BEGIN
    INCR( sum_log1m_result, sum_log1m( txpos, 1, leftover));

    a:= 0;
    b:= 1;
    FOR j:= 1 TO leftover DO BEGIN
      cval:= txposdir1[ j];
      // cval:= cval * 2^(-expo_shift[ j]);
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3] - expo_shift[ j];
      zstar:= compl[ j];
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
  END;
END;

FUNCTION Tuseful_obj. ddsum_log1m(
    CONST xpos{count}, xposdir1{count}, xposdir2{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result, dsum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  a, b, cval, zstar, tsum_log1m_result: DOUBLE;
  j, leftover, iloop: INTEGER;
  txpos, txposdir1, txposdir2: ARRAY_1D;
BEGIN
  RESULT:= 0;
  sum_log1m_result:= 0;
  tsum_log1m_result:= 0;
  dsum_log1m_result:= 0;
  txpos:= @xpos[ first-1];
  txposdir1:= @xposdir1[ first-1];
  txposdir2:= @xposdir2[ first-1];
  FOR iloop:= 1 TO (count SHR 8) DO BEGIN
    INCR( dsum_log1m_result, dsum_log1m( txpos, txposdir1,
        1, 256, tsum_log1m_result));
    INCR( sum_log1m_result, tsum_log1m_result);

    a:= 0;
    b:= 1;
    FOR j:= 1 TO 256 DO BEGIN
      cval:= txposdir1[ j];
      cval:= cval * txposdir2[ j];
      acc_cval[ j]:= cval;
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3] - 2*expo_shift[ j];
      zstar:= compl[ j];
      zstar:= zstar*zstar;
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
    txpos += 256;
    txposdir1 += 256;
    txposdir2 += 256;
  END;

  leftover:= count AND $FF;
  IF leftover>0 THEN BEGIN
    INCR( dsum_log1m_result, dsum_log1m( txpos, txposdir1,
        1, leftover, tsum_log1m_result));
    INCR( sum_log1m_result, tsum_log1m_result);

    a:= 0;
    b:= 1;
    FOR j:= 1 TO leftover DO BEGIN
      cval:= txposdir1[ j];
      cval:= cval * txposdir2[ j];
      acc_cval[ j]:= cval;
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3] - 2*expo_shift[ j];
      zstar:= compl[ j];
      zstar:= zstar*zstar;
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
  END;
END;

FUNCTION Tuseful_obj. dddsum_log1m(
    CONST xpos{count}, xposdir1{count}, xposdir2{count}, xposdir3{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result, dsum_log1m_result, ddsum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  a, b, cval, zstar, tsum_log1m_result, tdsum_log1m_result: DOUBLE;
  j, leftover, iloop: INTEGER;
  txpos, txposdir1, txposdir2, txposdir3: ARRAY_1D;
BEGIN
  RESULT:= 0;
  tsum_log1m_result:= 0;
  tdsum_log1m_result:= 0;
  sum_log1m_result:= 0;
  dsum_log1m_result:= 0;
  ddsum_log1m_result:= 0;
  txpos:= @xpos[first-1];
  txposdir1:= @xposdir1[ first-1];
  txposdir2:= @xposdir2[ first-1];
  txposdir3:= @xposdir3[ first-1];
  FOR iloop:= 1 TO (count SHR 8) DO BEGIN
    INCR( ddsum_log1m_result, ddsum_log1m( txpos, txposdir1, txposdir2,
        1, 256, tsum_log1m_result, tdsum_log1m_result));
    INCR( sum_log1m_result, tsum_log1m_result);
    INCR( dsum_log1m_result, tdsum_log1m_result);

    a:= 0;
    b:= 1;
    FOR j:= 1 TO 256 DO BEGIN
      cval:= acc_cval[ j];
      cval:= cval * txposdir3[ j];
      acc_cval[ j]:= cval;
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3]- 3*expo_shift[ j]+$10;
      zstar:= compl[ j];
      zstar:= zstar*zstar*zstar;
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
    txpos += 256;
    txposdir1 += 256;
    txposdir2 += 256;
    txposdir3 += 256;
  END;

  leftover:= count AND $FF;
  IF leftover>0 THEN BEGIN
    INCR( ddsum_log1m_result, ddsum_log1m( txpos, txposdir1, txposdir2,
        1, leftover, tsum_log1m_result, tdsum_log1m_result));
    INCR( sum_log1m_result, tsum_log1m_result);
    INCR( dsum_log1m_result, tdsum_log1m_result);

    a:= 0;
    b:= 1;
    FOR j:= 1 TO leftover DO BEGIN
      cval:= acc_cval[ j];
      cval:= cval * txposdir3[ j];
      acc_cval[ j]:= cval;
      QWORD_AR( cval)[3]:= QWORD_AR( cval)[3]- 3*expo_shift[ j]+$10;
      zstar:= compl[ j];
      zstar:= zstar*zstar*zstar;
      a:= a*zstar + b*cval;
      b:= b*zstar;
    END;

    DECR( RESULT, a/b);
  END;
END;
{$POINTERMATH OFF}

{$ELSE}{AD}
// SLOW VERSIONS-- must fix 'make' to remove forward derivs of these
// These are never actually called-- only used as templates by AD
FUNCTION Tuseful_obj. sum_log1m(
    CONST xpos{count}: ARRAY_1D;
    CONST first, count: INTEGER):
  DOUBLE;
VAR
  ixpos: INTEGER;
BEGIN
  RESULT:= 0;
  FOR ixpos:= first TO count DO BEGIN
    INCR( RESULT, log1p( -xpos[ ixpos]));
  END;
END;

FUNCTION Tuseful_obj. dsum_log1m(
    CONST xpos{count}, xposdir1{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  ixpos: INTEGER;
BEGIN
  sum_log1m_result:= 0;
  RESULT:= 0;
  FOR ixpos:= first TO count DO BEGIN
    INCR( sum_log1m_result, log1p( -xpos[ ixpos]));
    DECR( RESULT, xposdir1[ ixpos] / (1-xpos[ ixpos]));
  END;
END;

FUNCTION Tuseful_obj. ddsum_log1m(
    CONST xpos{count}, xposdir1{count}, xposdir2{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result, dsum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  ixpos: INTEGER;
  invo, invo1: DOUBLE;
BEGIN
  sum_log1m_result:= 0;
  dsum_log1m_result:= 0;
  RESULT:= 0;
  FOR ixpos:= first TO count DO BEGIN
    INCR( sum_log1m_result, log1p( -xpos[ ixpos]));
    invo:= 1 / (1-xpos[ ixpos]);
    invo1:= xposdir1[ ixpos] * invo;
    DECR( dsum_log1m_result,  invo1);
    DECR( RESULT, xposdir2[ ixpos] * invo * invo1);
  END;
END;

FUNCTION Tuseful_obj. dddsum_log1m(
    CONST xpos{count}, xposdir1{count}, xposdir2{count}, xposdir3{count}: ARRAY_1D;
    CONST first, count: INTEGER;
    VAR   sum_log1m_result, dsum_log1m_result, ddsum_log1m_result: DOUBLE):
  DOUBLE;
VAR
  ixpos: INTEGER;
  invo, invo1: DOUBLE;
BEGIN
  sum_log1m_result:= 0;
  dsum_log1m_result:= 0;
  ddsum_log1m_result:= 0;
  RESULT:= 0;
  FOR ixpos:= first TO count DO BEGIN
    INCR( sum_log1m_result, log1p( -xpos[ ixpos]));
    invo:= 1 / (1-xpos[ ixpos]);
    invo1:= xposdir1[ ixpos] * invo;
    DECR( dsum_log1m_result, invo1);
    invo1:= xposdir2[ ixpos] * invo * invo1;
    DECR( ddsum_log1m_result, invo1);
    DECR( RESULT, 2*xposdir3[ixpos]*invo1*invo);
  END;
END;
{$ENDIF}{AD}

{$IFNDEF AD}
PROCEDURE Tuseful_obj. set_n_nueven(
    CONST _n_nueven: INTEGER);
VAR
  old_n, i: INTEGER;
BEGIN
  old_n:= n_nueven;
  n_nueven:= _n_nueven;
  realloc_arrays( [@nueven, @nterms_nueven], [n_nueven], [1], SizeOf( nueven[1]));
  realloc_arrays( [@ratto_nueven, @dt_ratto_nueven], [n_nueven], [1], SizeOf( ratto_nueven[1]));
  IF old_n>1 THEN BEGIN // manually remove old cft vecs, except #1 which is always Normal with no cft
    FOR i:= 2 TO old_n DO BEGIN
      dealloc( cft_nueven[ i]);
    END;
  END;
  realloc_arrays( [@cft_nueven], [n_nueven], [1], SizeOf( cft_nueven[1])); // outer of ragged
  nueven[ 1]:= -1;
END;

PROCEDURE Tuseful_obj. set_nueveni(
    CONST nu, i_nueven: INTEGER);
VAR
  p, q, mulgor, this_ratto: DOUBLE;
  r, n: INTEGER;
BEGIN
  nueven[ i_nueven]:= nu;
  IF nu>0 THEN BEGIN
    n:= nu DIV 2 - 1;
    nterms_nueven[ i_nueven]:= n;
    alloc_arrays( [@cft_nueven[ i_nueven]], [n+1], [0], SizeOf( cft_nueven[1][1]));
    mulgor:= 1;
    p:= 1;
    q:= 0.5;
    FOR r:= 1 TO n DO BEGIN
      mulgor *= (p+q+n-r) / (p+n-r);
    END;

    cft_nueven[ i_nueven][ 0]:= 0.5 * mulgor; // Pt = 0.5 * I_x
    this_ratto:= -0.5 * SQRT( nu) / (nu-1);
    FOR r:= 1 TO n DO BEGIN
      cft_nueven[ i_nueven][ r]:= -cft_nueven[ i_nueven][r-1] * ((q+r-1)/(p+q-1+r)) * ((n+1-r)/r);
      this_ratto *= (r+0.5)/r;
    END;
    ratto_nueven[ i_nueven]:= this_ratto;
    dt_ratto_nueven[ i_nueven]:= - this_ratto * (nu-1) / nu;
  END;
END;

FUNCTION Tuseful_obj. pt_nueveni(
    CONST x: DOUBLE;
    CONST i_nueven: INTEGER):
  DOUBLE;
VAR
  nu, r: INTEGER;
  tt, comp_tt, term, sum: DOUBLE;
BEGIN
  nu:= nueven[ i_nueven];
  IF nu<=0 THEN BEGIN
    RESULT:= pnorm( x);
  END ELSE BEGIN
    tt:= nu /(nu+SQR(x));
    comp_tt:= 1-tt;
    term:= SQRT( comp_tt);
    sum:= 0;
    FOR r:= 0 TO nterms_nueven[ i_nueven] DO BEGIN
      sum += cft_nueven[ i_nueven][ r] * (1-term);
      term *= comp_tt;
    END;
    RESULT:= 0.5 + sign(x) * (0.5-sum);
  END;
END;
{$ENDIF}{AD}

FUNCTION Tuseful_obj. dt_nueveni(
    CONST x: DOUBLE;
    CONST i_nueven: INTEGER):
  DOUBLE;
VAR
  nu: INTEGER;
  tt: DOUBLE;
BEGIN
  nu:= nueven[ i_nueven];
  IF nu<=0 THEN BEGIN
    RESULT:= dnorm( x);
  END ELSE BEGIN
    tt:= nu /(nu+SQR(x));
    tt:= ipwr( tt, 1+nterms_nueven[ i_nueven]) * SQRT( tt);
    RESULT:= dt_ratto_nueven[ i_nueven] * tt;
  END;
END;

FUNCTION Tuseful_obj. mean_t_nueveni_trunclt(
    CONST x, pt: DOUBLE;
    CONST i_nueven: INTEGER):
  DOUBLE;
VAR
  nu: INTEGER;
  tt, mulbo: DOUBLE;
BEGIN
  nu:= nueven[ i_nueven];
  IF nu<=0 THEN BEGIN
    RESULT:= -dnorm( x) / pt;
  END ELSE BEGIN
    tt:= nu/(nu + sqr(x));
    mulbo:= sqrt( tt) * ipwr( tt, nterms_nueven[ i_nueven]);
    RESULT:= ratto_nueven[ i_nueven] * mulbo / pt;
  END;
END;

FUNCTION Tuseful_obj. logdet_and_chol(
  CONST ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
  CONST nchol: INTEGER):
DOUBLE;
VAR
  i, j, k: INTEGER;
  _h, s: DOUBLE;
// Based on Spelucci routine, but transposed
// Differs in that diag is replaced with INVERSE to speed up backsub
// Fastest version would store diagonal & use sum_log
BEGIN
  RESULT:= 0;
  FOR i:=1 TO nchol DO BEGIN
    _h:= ain[i][i];
    FOR j:=1 TO i-1 DO BEGIN
      DECR( _h, SQR( rchol[i][j]));
    END;

    {$IFNDEF AD}
    IF _h<=0 THEN BEGIN
      RESULT:= QNAN;
      rchol[1][1]:= QNAN;
EXIT;
    END;
    {$ENDIF}{AD}

    _h:= sqrt(_h);
    INCR( RESULT, LN( _h)); // efficiency??
    _h:= 1/_h;
    rchol[i][i]:= _h;
    FOR k:=i+1 TO nchol DO BEGIN
      s:= 0;
      FOR j:=1 TO i-1 DO BEGIN
        INCR( s, rchol[i][j]*rchol[k][j]);
      END;
      s:= (ain[i][k]-s)*_h;
      rchol[k][i]:= s;
    END;
  END;

  // RESULT:= -sum_log( diag_wkspace[1], n);
  RESULT:= 2*RESULT;
END;

FUNCTION Tuseful_obj. logdet_and_chol_neg(
  CONST neg_ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
  CONST nchol: INTEGER):
DOUBLE;
VAR
  i, j, k: INTEGER;
  _h, s: DOUBLE;
// Based on Spelucci routine, but transposed
// Differs in that diag is replaced with INVERSE to speed up backsub
// Fastest version would store diagonal & use sum_log
BEGIN
  RESULT:= 0;
  FOR i:=1 TO nchol DO BEGIN
    _h:= -neg_ain[i][i];
    FOR j:=1 TO i-1 DO BEGIN
      DECR( _h, SQR( rchol[i][j]));
    END;

    {$IFNDEF AD}
    IF _h<=0 THEN BEGIN
      RESULT:= QNAN;
      rchol[1][1]:= QNAN;
EXIT;
    END;
    {$ENDIF}{AD}

    INCR( RESULT, LN( _h)); // efficiency??
    _h:= 1/sqrt(_h);
    rchol[i][i]:= _h;
    FOR k:=i+1 TO nchol DO BEGIN
      s:= -neg_ain[i][k];
      FOR j:=1 TO i-1 DO BEGIN
        DECR( s, rchol[i][j]*rchol[k][j]);
      END;
      rchol[k][i]:= s*_h;
    END;
  END;
  // RESULT:= -sum_log( diag_wkspace[1], n);
END;

PROCEDURE Tuseful_obj. backsolve_chol(
    CONST rchol{nchol,nchol}: ARRAY_2D;
    CONST target{nchol}, sol{nchol}: ARRAY_1D;
    CONST nchol: INTEGER);
VAR
  i, k: INTEGER;
  sum: DOUBLE;
BEGIN
  FOR i:= 1 TO nchol DO BEGIN
    sum:= target[ i];
    FOR k:= i-1  DOWNTO 1 DO BEGIN
      DECR( sum, rchol[i][ k] * sol[ k]);
    END;
    sol[ i]:= sum * rchol[i][ i];
  END;

  FOR i:= nchol DOWNTO 1 DO BEGIN
    sum:= sol[ i];
    FOR k:= i+1 TO nchol DO BEGIN
      DECR( sum, rchol[k][i]*sol[k]);
    END;
    sol[ i]:= sum * rchol[i][i];
  END;
END;

//-----------------------------------------------------------------------------

PROCEDURE Tuseful_obj. to_binc(
    CONST pars{d1,d2}: ARRAY_2D;
    CONST d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_end, id_end1, id_end2: INTEGER;
  w: DOUBLE;
BEGIN
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  // Diagonal:
  FOR id:= 2 TO dd DO BEGIN
    pars[id][id]:= pars[id-1][id-1] + log1p( EXP( pars[id][id]));
  END;

  IF d1>d2 THEN BEGIN
    FOR i1:= d2+1 TO d1 DO BEGIN
      pars[i1][d2]:= pars[i1-1][d2] + log1p( EXP( pars[i1][d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d1+1 TO d2 DO BEGIN
      pars[d1][i2]:= pars[d1][i2-1] + log1p( EXP( pars[d1][i2]));
    END;
  END;

  FOR i1:= 2 TO d1 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      w:= inv_logit( pars[i1+id-1][id]);
      pars[i1+id-1][id]:= pars[i1+id-2][id] * (1-w) + w * pars[i1+id-1][id+1];
    END;
  END;

  FOR i2:= 2 TO d2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      w:= inv_logit( pars[id][i2+id-1]);
      pars[id][i2+id-1]:= pars[id][i2+id-2] * (1-w) + w * pars[id+1][i2+id-1];
    END;
  END;

END;

//-----------------------------------------------------------------------------

PROCEDURE Tuseful_obj. from_binc(
    CONST pars{d1,d2}: ARRAY_2D;
    CONST d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_end, id_end1, id_end2: INTEGER;
  iw, temp: DOUBLE;
BEGIN
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  // Reverse the sequence

  FOR i2:= d2 DOWNTO 2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= id_end DOWNTO 1 DO BEGIN
      //w:= inv_logit( pars[id][i2+id-1]);
      //pars[id][i2+id-1]:= pars[id][i2+id-2] * (1-w) + w * pars[id+1][i2+id-1];

      temp:= pars[id][i2+id-2];
      iw:= (pars[id][i2+id-1] - temp) / ( pars[id+1][i2+id-1] - temp);
      pars[id][i2+id-1]:= logit( iw);
    END;
  END;

  FOR i1:= d1 DOWNTO 2 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= id_end DOWNTO 1 DO BEGIN
      // w:= inv_logit( pars[i1+id-1][id]);
      // pars[i1+id-1][id]:= pars[i1+id-2][id] * (1-w) + w * pars[i1+id-1][id+1];
      temp:= pars[i1+id-2][id];
      iw:= (pars[i1+id-1][id] - temp) / ( pars[i1+id-1][id+1] - temp);
      pars[i1+id-1][id]:= logit( iw);
    END;
  END;


  IF d1>d2 THEN BEGIN
    FOR i1:= d1 DOWNTO d2+1 DO BEGIN
      // pars[i1][d2]:= pars[i1-1][d2] + LN1p( EXP( pars[i1][d2]));
      pars[i1][d2]:= LN( expm1( pars[i1][d2] - pars[i1-1][d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d2 DOWNTO d1+1 DO BEGIN
      // pars[d1][i2]:= pars[d1][i2-1] + LN1p( EXP( pars[d1][i2]));
      pars[d1][i2]:= LN( expm1( pars[d1][i2] - pars[d1][i2-1]));
    END;
  END;

  // Diagonal:
  FOR id:= dd DOWNTO 2 DO BEGIN
    // pars[id][id]:= pars[id-1][id-1] + log1p( EXP( pars[id][id]));
    pars[id][id]:= LN( expm1( pars[id][id]-pars[id-1][id-1]));
  END;
END;

//-----------------------------------------------------------------------------

PROCEDURE Tuseful_obj. to_binc_x11(
    CONST pars{d1}: ARRAY_1D;
    CONST start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_start, id_end, id_end1, id_end2: INTEGER;
  w: DOUBLE;
BEGIN
  // Like Binc, but x11 is ignored altogether
  // vectorized array starts with [1,2] in position 1
  // Starts going up diag at x22, and x21 and x12 have only single constraints
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  // Diagonal:
  FOR id:= 3 TO dd DO BEGIN
    pars[start-2+d2*(id-1)+id]:= pars[start-2+d2*(id-1-1)+id-1] + log1p( EXP( pars[start-2+d2*(id-1)+id]));
  END;

  IF d1>d2 THEN BEGIN
    FOR i1:= d2+1 TO d1 DO BEGIN
      pars[start-2+d2*(i1-1)+d2]:= pars[start-2+d2*(i1-1-1)+d2] + log1p( EXP( pars[start-2+d2*(i1-1)+d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d1+1 TO d2 DO BEGIN
      pars[start-2+d2*(d1-1)+i2]:= pars[start-2+d2*(d1-1)+i2-1] + log1p( EXP( pars[start-2+d2*(d1-1)+i2]));
    END;
  END;

  pars[start-2+d2*(2-1)+1]:= pars[start-2+d2*(2-1)+2] - log1p( EXP( pars[start-2+d2*(2-1)+1]));
  pars[start-2+d2*(1-1)+2]:= pars[start-2+d2*(2-1)+2] - log1p( EXP( pars[start-2+d2*(1-1)+2]));

  FOR i1:= 2 TO d1 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    IF i1>2 THEN BEGIN
      id_start:= 1;
    END ELSE BEGIN
      id_start:= 2;
    END;

    FOR id:= id_start TO id_end DO BEGIN
      w:= inv_logit( pars[start-2+d2*(i1+id-1-1)+id]);
      pars[start-2+d2*(i1+id-1-1)+id]:= pars[start-2+d2*(i1+id-2-1)+id] * (1-w) + w * pars[start-2+d2*(i1+id-1-1)+id+1];
    END;
  END;

  FOR i2:= 2 TO d2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    IF i2>2 THEN BEGIN
      id_start:= 1;
    END ELSE BEGIN
      id_start:= 2;
    END;

    FOR id:= id_start TO id_end DO BEGIN
      w:= inv_logit( pars[start-2+d2*(id-1)+i2+id-1]);
      pars[start-2+d2*(id-1)+i2+id-1]:= pars[start-2+d2*(id-1)+i2+id-2] * (1-w) + w * pars[start-2+d2*(id+1-1)+i2+id-1];
    END;
  END;

END;

//---------------------------------------------------------------------------

// current limitations of my AD force this workaround:

PROCEDURE tuseful_obj. to_binc_x11_2(
    CONST pars{nnnn, d1}: ARRAY_2D;
    CONST nnnn, iiii, start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, istart, id_end, id_end1, id_end2: INTEGER;
  w, lower: DOUBLE;
BEGIN
  // pars[start] is elt[1,2] of matrix-- [1,1] doesn't exist
  dd:= 0;
  IF d1=1 THEN BEGIN
   dd:= d2;
  END ELSE IF d2=1 THEN BEGIN
    dd:= d1;
  END;

  IF dd<>0 THEN BEGIN
    pars[iiii][start]:= log1p( EXP( pars[iiii][start]));
    FOR id:= 3 TO dd DO BEGIN
      pars[iiii][start-2+id]:= pars[iiii][start-3+id] + log1p( EXP( pars[iiii][start-2+id]));
    END;
  END ELSE BEGIN
    IF d1>d2 THEN BEGIN
      dd:= d2;
    END ELSE BEGIN
      dd:= d1;
    END;

    // Diagonal: hardwiring p(1,1)=0
    pars[iiii][start-2+(2-1)*d2+2]:= log1p( EXP( pars[iiii][start-2+(2-1)*d2+2]));
    FOR id:= 3 TO dd DO BEGIN
      pars[iiii][start-2+(id-1)*d2+id]:= pars[iiii][start-2+(id-1-1)*d2+id-1] + log1p( EXP( pars[iiii][start-2+(id-1)*d2+id]));
    END;

    IF d1>d2 THEN BEGIN
      istart:= d2+1;
      IF d2=1 THEN BEGIN
        pars[iiii][start-2+(istart-1)*d2+d2]:= log1p( EXP( pars[iiii][start-2+(istart-1)*d2+d2]));
        istart:= istart+1;
      END;

      FOR i1:= istart TO d1 DO BEGIN
        pars[iiii][start-2+(i1-1)*d2+d2]:= pars[iiii][start-2+(i1-1-1)*d2+d2] + log1p( EXP( pars[iiii][start-2+(i1-1)*d2+d2]));
      END;
    END ELSE IF d1<d2 THEN BEGIN
      istart:= d1+1;
      IF d1=1 THEN BEGIN
        pars[iiii][start-2+(d1-1)*d2+istart]:= log1p( EXP( pars[iiii][start-2+(d1-1)*d2+istart]));
        istart:= istart+1;
      END;

      FOR i2:= istart TO d2 DO BEGIN
        pars[iiii][start-2+(d1-1)*d2+i2]:= pars[iiii][start-2+(d1-1)*d2+i2-1] + log1p( EXP( pars[iiii][start-2+(d1-1)*d2+i2]));
      END;
    END;

    FOR i1:= 2 TO d1 DO BEGIN
      id_end1:= d2-1;
      id_end2:= 1+d1-i1;
      IF id_end1>id_end2 THEN BEGIN
        id_end:= id_end2;
      END ELSE BEGIN
        id_end:= id_end1;
      END;

      FOR id:= 1 TO id_end DO BEGIN
        IF (i1>2) OR (id>1) THEN BEGIN
          lower:= pars[iiii][start-2+(i1+id-2-1)*d2+id];
        END ELSE BEGIN
          lower:= 0;
        END;
        w:= inv_logit( pars[iiii][start-2+(i1+id-1-1)*d2+id]);
        pars[iiii][start-2+(i1+id-1-1)*d2+id]:= lower * (1-w) + w * pars[iiii][start-2+(i1+id-1-1)*d2+id+1];
      END;
    END;

    FOR i2:= 2 TO d2 DO BEGIN
      id_end1:= d1-1;
      id_end2:= 1+d2-i2;
      IF id_end1>id_end2 THEN BEGIN
        id_end:= id_end2;
      END ELSE BEGIN
        id_end:= id_end1;
      END;

      FOR id:= 1 TO id_end DO BEGIN
        IF (i2>2) OR (id>1) THEN BEGIN
          lower:= pars[iiii][start-2+(id-1)*d2+i2+id-2];
        END ELSE BEGIN
          lower:= 0;
        END;

        w:= inv_logit( pars[iiii][start-2+(id-1)*d2+i2+id-1]);
        pars[iiii][start-2+(id-1)*d2+i2+id-1]:=  lower * (1-w) + w * pars[iiii][start-2+(id+1-1)*d2+i2+id-1];
      END;
    END;
  END;
END;


//-----------------------------------------------------------------------------


PROCEDURE Tuseful_obj. from_binc_x11(
    CONST pars{d1}: ARRAY_1D;
    CONST start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, istart, id_end, id_end1, id_end2: INTEGER;
  lower: DOUBLE;
BEGIN
  dd:= 0;
  IF d1=1 THEN BEGIN
   dd:= d2;
  END ELSE IF d2=1 THEN BEGIN
    dd:= d1;
  END;

  IF dd<>0 THEN BEGIN
    FOR id:= dd DOWNTO 3 DO BEGIN
      pars[start-2+id]:= LN( expm1( pars[start-2+id] - pars[start-3+id]));
    END;
    pars[start]:= LN( expm1( pars[start]));
  END ELSE BEGIN
    IF d1>d2 THEN BEGIN
      dd:= d2;
    END ELSE BEGIN
      dd:= d1;
    END;

    // Reverse the sequence

    FOR i2:= d2 DOWNTO 2 DO BEGIN
      id_end1:= d1-1;
      id_end2:= 1+d2-i2;
      IF id_end1>id_end2 THEN BEGIN
        id_end:= id_end2;
      END ELSE BEGIN
        id_end:= id_end1;
      END;

      FOR id:= id_end DOWNTO 1 DO BEGIN
        IF (i2>2) OR (id>1) THEN BEGIN
          lower:= pars[start-2+(id-1)*d2+i2+id-2];
        END ELSE BEGIN
          lower:= 0;
        END;

        // w:= inv_logit( pars[iiii][start-2+(id-1)*d2+i2+id-1]);
        // pars[iiii][start-2+(id-1)*d2+i2+id-1]:=  lower * (1-w) + w * pars[iiii][start-2+(id-1+1)*d2+i2+id-1];
        pars[start-2+(id-1)*d2+i2+id-1]:= logit( (pars[start-2+(id-1)*d2+i2+id-1] - lower) /
            (pars[start-2+(id-1+1)*d2+i2+id-1] - lower));
      END;
    END;

    FOR i1:= d1 DOWNTO 2 DO BEGIN
      id_end1:= d2-1;
      id_end2:= 1+d1-i1;
      IF id_end1>id_end2 THEN BEGIN
        id_end:= id_end2;
      END ELSE BEGIN
        id_end:= id_end1;
      END;

      FOR id:= id_end DOWNTO 1 DO BEGIN
        IF (i1>2) OR (id>1) THEN BEGIN
          lower:= pars[start-2+(i1+id-2-1)*d2+id];
        END ELSE BEGIN
          lower:= 0;
        END;

        // w:= inv_logit( pars[start-2+(i1+id-1-1)*d2+id]);
        // pars[start-2+(i1+id-1-1)*d2+id]:= lower * (1-w) + w * pars[iiii][start-2+(i1+id-1-1)*d2+id+1];
        pars[start-2+d2*(i1+id-1-1)+id]:= logit( (pars[start-2+d2*(i1+id-1-1)+id] - lower) /
            (pars[start-2+d2*(i1+id-1-1)+id+1] - lower));
      END;
    END;

    IF d1>d2 THEN BEGIN
      istart:= d2+1;
      IF d2=1 THEN BEGIN
        istart:= istart+1;
      END;

      FOR i1:= d1 DOWNTO istart DO BEGIN
        // pars[start-2+d2*(i1-1)+d2]:= pars[start-2+d2*(i1-1-1)+d2] + LN1p( EXP( pars[start-2+d2*(i1-1)+d2]));
        pars[start-2+d2*(i1-1)+d2]:= LN( expm1( pars[start-2+d2*(i1-1)+d2] - pars[start-2+d2*(i1-1-1)+d2]));
      END;

      IF d2=1 THEN BEGIN
        pars[start-2+d2*(istart-2)+d2]:= LN( expm1( pars[start-2+(istart-2)*d2+d2]));
      END;
    END ELSE IF d1<d2 THEN BEGIN
      istart:= d1+1;
      IF d1=1 THEN BEGIN
        istart:= istart+1;
      END;

      FOR i2:= d2 DOWNTO istart DO BEGIN
        // pars[start-2+d2*(d1-1)+i2]:= pars[start-2+d2*(d1-1)+i2-1] + LN1p( EXP( pars[start-2+d2*(d1-1)+i2]));
        pars[start-2+d2*(d1-1)+i2]:= LN( expm1( pars[start-2+d2*(d1-1)+i2] - pars[start-2+d2*(d1-1)+i2-1]));
      END;

      IF d1=1 THEN BEGIN
        pars[start-2+(d1-1)*d2+istart-1]:= LN( expm1( pars[start-2+(d1-1)*d2+istart-1]));
      END;
    END;

    // Diagonal:
    FOR id:= dd DOWNTO 3 DO BEGIN
      // pars[start-2+d2*(id-1)+id]:= pars[start-2+d2*(id-1-1)+id-1] + log1p( EXP( pars[start-2+d2*(id-1)+id]));
      pars[start-2+d2*(id-1)+id]:= LN( expm1( pars[start-2+d2*(id-1)+id]-pars[start-2+d2*(id-1-1)+id-1]));
    END;
    pars[start-2+(2-1)*d2+2]:= LN( expm1( pars[start-2+(2-1)*d2+2]));
  END;
END;

//-----------------------------------------------------------------------------


PROCEDURE tuseful_obj. to_binc1(
    CONST pars{d1}: ARRAY_1D;
    CONST start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_end, id_end1, id_end2: INTEGER;
  w, lower: DOUBLE;
BEGIN
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  // Diagonal: hardwiring p(1,1)=0
  pars[start-1+(2-1)*d2+2]:= log1p( EXP( pars[start-1+(2-1)*d2+2]));
  FOR id:= 3 TO dd DO BEGIN
    pars[start-1+(id-1)*d2+id]:= pars[start-1+(id-1-1)*d2+id-1] + log1p( EXP( pars[start-1+(id-1)*d2+id]));
  END;

  IF d1>d2 THEN BEGIN
    FOR i1:= d2+1 TO d1 DO BEGIN
      pars[start-1+(i1-1)*d2+d2]:= pars[start-1+(i1-1-1)*d2+d2] + log1p( EXP( pars[start-1+(i1-1)*d2+d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d1+1 TO d2 DO BEGIN
      pars[start-1+(d1-1)*d2+i2]:= pars[start-1+(d1-1)*d2+i2-1] + log1p( EXP( pars[start-1+(d1-1)*d2+i2]));
    END;
  END;

  FOR i1:= 2 TO d1 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      IF (i1>2) OR (id>1) THEN BEGIN
        lower:= pars[start-1+(i1+id-2-1)*d2+id];
      END ELSE BEGIN
        lower:= 0;
      END;
      w:= inv_logit( pars[start-1+(i1+id-1-1)*d2+id]);
      pars[start-1+(i1+id-1-1)*d2+id]:= lower * (1-w) + w * pars[start-1+(i1+id-1-1)*d2+id+1];
    END;
  END;

  FOR i2:= 2 TO d2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      IF (i2>2) OR (id>1) THEN BEGIN
        lower:= pars[start-1+(id-1)*d2+i2+id-2];
      END ELSE BEGIN
        lower:= 0;
      END;

      w:= inv_logit( pars[start-1+(id-1)*d2+i2+id-1]);
      pars[start-1+(id-1)*d2+i2+id-1]:=  lower * (1-w) + w * pars[start-1+(id+1-1)*d2+i2+id-1];
    END;
  END;

END;

/////////////////////////////////

PROCEDURE tuseful_obj. to_binc12(
    CONST pars{nnnn, d1}: ARRAY_2D;
    CONST nnnn, iiii, start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_end, id_end1, id_end2: INTEGER;
  w, lower: DOUBLE;
BEGIN
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  // Diagonal: hardwiring p(1,1)=0
  pars[iiii][start-1+(2-1)*d2+2]:= log1p( EXP( pars[iiii][start-1+(2-1)*d2+2]));
  FOR id:= 3 TO dd DO BEGIN
    pars[iiii][start-1+(id-1)*d2+id]:= pars[iiii][start-1+(id-1-1)*d2+id-1] + log1p( EXP( pars[iiii][start-1+(id-1)*d2+id]));
  END;

  IF d1>d2 THEN BEGIN
    FOR i1:= d2+1 TO d1 DO BEGIN
      pars[iiii][start-1+(i1-1)*d2+d2]:= pars[iiii][start-1+(i1-1-1)*d2+d2] + log1p( EXP( pars[iiii][start-1+(i1-1)*d2+d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d1+1 TO d2 DO BEGIN
      pars[iiii][start-1+(d1-1)*d2+i2]:= pars[iiii][start-1+(d1-1)*d2+i2-1] + log1p( EXP( pars[iiii][start-1+(d1-1)*d2+i2]));
    END;
  END;

  FOR i1:= 2 TO d1 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      IF (i1>2) OR (id>1) THEN BEGIN
        lower:= pars[iiii][start-1+(i1+id-2-1)*d2+id];
      END ELSE BEGIN
        lower:= 0;
      END;
      w:= inv_logit( pars[iiii][start-1+(i1+id-1-1)*d2+id]);
      pars[iiii][start-1+(i1+id-1-1)*d2+id]:= lower * (1-w) + w * pars[iiii][start-1+(i1+id-1-1)*d2+id+1];
    END;
  END;

  FOR i2:= 2 TO d2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= 1 TO id_end DO BEGIN
      IF (i2>2) OR (id>1) THEN BEGIN
        lower:= pars[iiii][start-1+(id-1)*d2+i2+id-2];
      END ELSE BEGIN
        lower:= 0;
      END;

      w:= inv_logit( pars[iiii][start-1+(id-1)*d2+i2+id-1]);
      pars[iiii][start-1+(id-1)*d2+i2+id-1]:=  lower * (1-w) + w * pars[iiii][start-1+(id+1-1)*d2+i2+id-1];
    END;
  END;

END;


//-----------------------------------------------------------------------------

PROCEDURE tuseful_obj. from_binc1(
    CONST pars{d1}: ARRAY_1D;
    CONST start, d1, d2: INTEGER);
VAR
  dd, id, i1, i2, id_end, id_end1, id_end2: INTEGER;
  iw, lower: DOUBLE;
BEGIN
  IF d1>d2 THEN BEGIN
    dd:= d2;
  END ELSE BEGIN
    dd:= d1;
  END;

  FOR i2:= d2 DOWNTO 2 DO BEGIN
    id_end1:= d1-1;
    id_end2:= 1+d2-i2;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= id_end DOWNTO 1 DO BEGIN
      //w:= inv_logit( pars[start-1+(id-1)*d2+i2+id-1]);
      //pars[start-1+(id-1)*d2+i2+id-1]:= pars[start-1+(id-1)*d2+i2+id-2] * (1-w) + w * pars[start-1+(id+1-1)*d2+i2+id-1];

      IF (id>1) OR (i2>2) THEN BEGIN
        lower:= pars[start-1+(id-1)*d2+i2+id-2];
      END ELSE BEGIN
        lower:= 0;
      END;
      iw:= (pars[start-1+(id-1)*d2+i2+id-1] - lower) / ( pars[start-1+(id+1-1)*d2+i2+id-1] - lower);
      pars[start-1+(id-1)*d2+i2+id-1]:= logit( iw);
    END;
  END;

  FOR i1:= d1 DOWNTO 2 DO BEGIN
    id_end1:= d2-1;
    id_end2:= 1+d1-i1;
    IF id_end1>id_end2 THEN BEGIN
      id_end:= id_end2;
    END ELSE BEGIN
      id_end:= id_end1;
    END;

    FOR id:= id_end DOWNTO 1 DO BEGIN
      // w:= inv_logit( pars[start-1+(i1+id-1-1)*d2+id]);
      // pars[start-1+(i1+id-1-1)*d2+id]:= pars[start-1+(i1+id-2-1)*d2+id] * (1-w) + w * pars[start-1+(i1+id-1-1)*d2+id+1];
      IF (id>1) OR (i1>2) THEN BEGIN
        lower:= pars[start-1+(i1+id-2-1)*d2+id];
      END ELSE BEGIN
        lower:= 0;
      END;

      iw:= (pars[start-1+(i1+id-1-1)*d2+id] - lower) / ( pars[start-1+(i1+id-1-1)*d2+id+1] - lower);
      pars[start-1+(i1+id-1-1)*d2+id]:= logit( iw);
    END;
  END;


  IF d1>d2 THEN BEGIN
    FOR i1:= d1 DOWNTO d2+1 DO BEGIN
      // pars[start-1+(i1-1)*d2+d2]:= pars[start-1+(i1-1-1)*d2+d2] + LN1p( EXP( pars[start-1+(i1-1)*d2+d2]));
      pars[start-1+(i1-1)*d2+d2]:= LN( expm1( pars[start-1+(i1-1)*d2+d2] - pars[start-1+(i1-1-1)*d2+d2]));
    END;
  END ELSE IF d1<d2 THEN BEGIN
    FOR i2:= d2 DOWNTO d1+1 DO BEGIN
      // pars[start-1+(d1-1)*d2+i2]:= pars[start-1+(d1-1)*d2+i2-1] + LN1p( EXP( pars[start-1+(d1-1)*d2+i2]));
      pars[start-1+(d1-1)*d2+i2]:= LN( expm1( pars[start-1+(d1-1)*d2+i2] - pars[start-1+(d1-1)*d2+i2-1]));
    END;
  END;

  // Diagonal:
  FOR id:= dd DOWNTO 3 DO BEGIN
    // pars[start-1+(id-1)*d2+id]:= pars[start-1+(id-1-1)*d2+id-1] + log1p( EXP( pars[start-1+(id-1)*d2+id]));
    pars[start-1+(id-1)*d2+id]:= LN( expm1( pars[start-1+(id-1)*d2+id]-pars[start-1+(id-1-1)*d2+id-1]));
  END;

  // p(1,1) is hardwired to 0 so...
  pars[start-1+(2-1)*d2+2]:= LN( expm1( pars[start-1+(2-1)*d2+2]));
END;

//-----------------------------------------------------------------------------

FUNCTION Tuseful_obj. quadform(
    CONST xqf{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER):
  DOUBLE;
VAR
  i, j: INTEGER;
  sumbo: DOUBLE;
BEGIN
  RESULT:= 0;
  FOR i:= 1 TO nqf DO BEGIN
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf[i][j]*xqf[j]);
    END;
    INCR( RESULT, xqf[i]*sumbo);
  END;
END;

PROCEDURE Tuseful_obj. quadform_b(
    CONST xqf{nqf}, xqf_b{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER;
    VAR   xqf_wt: DOUBLE);
VAR
  i, j: INTEGER;
  sumbo: DOUBLE;
BEGIN
  FOR i:= 1 TO nqf DO BEGIN
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf[i][j]*xqf[j]);
    END;
    xqf_b[ i]:= 2*xqf_wt*sumbo;
  END;
END;

FUNCTION Tuseful_obj. quadform_d(
    CONST xqf{nqf}, xqf_dir{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER;
    VAR   hxh: DOUBLE):
  DOUBLE;
VAR
  i, j: INTEGER;  
  sumbo: DOUBLE;
BEGIN
  hxh:= 0;
  RESULT:= 0;
  FOR i:= 1 TO nqf DO BEGIN
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf[i][j]*xqf[j]);
    END;
    INCR( hxh, sumbo*xqf[i]);
    INCR( RESULT, 2*xqf_dir[i]*sumbo);
  END;
END;

PROCEDURE Tuseful_obj. quadform_b_d(
    CONST xqf{nqf}, xqf_dir{nqf}, xqf_b{nqf}, xqf_bd{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER;
    VAR   xqf_wt: DOUBLE);
BEGIN
  quadform_b( xqf_dir, xqf_bd, hqf, nqf, xqf_wt);
  quadform_b( xqf, xqf_b, hqf, nqf, xqf_wt);
END;

//-------------------------------------------------------------------------------------------------------------------

FUNCTION Tuseful_obj. asymp(
    CONST _x, _thresh: DOUBLE):
  DOUBLE;  //OUTPUT: x if x<thresh, otherwise something below the asymptote 3*thresh
VAR
  _w1, _w2, _w4, _w8, _w16, _w32, _w64, _w: DOUBLE;
BEGIN
  {$IFNDEF AD}
  IF IsInfinite( _x) THEN BEGIN
    RESULT:= 3*_thresh;
EXIT;
  END;
  {$ENDIF}{AD}

  _w1:= 8*_x / (15*_thresh+_x);
  _w2:= _w1*_w1;
  _w4:= _w2*_w2;
  _w8:= _w4*_w4;
  _w16:= _w8*_w8;
  _w32:= _w16*_w16;
  _w64:= _w32*_w32;
  _w:= _w64 / (1+_w64);
  RESULT:= _x*(1-_w) + _w*3*_thresh;
END;

//-------------------------------------------------------------------------------------------------------------------

// Code below slight mod of Paul Godfrey's implementation of Lanczos approx to gamma
// Diffrentiable!

FUNCTION Tuseful_obj. lgamma(
    CONST _x: DOUBLE):
  DOUBLE;
VAR
  _s, _ss: DOUBLE;
  _k: INTEGER;
BEGIN
  // t=z+g;
  _s:=0;
  FOR _k:= n_gamlanc DOWNTO 0 DO BEGIN
    INCR( _s, gamlanc_cof[_k]/(_x+_k));
  END;
  INCR( _s, gamlanc_cof[-1]);
  _ss:= _x+n_gamlanc-0.5;
  RESULT:= LN( _s * sqrt_two_pi) + (_x-0.5)*LN(_ss)-_ss;
END;

//-------------------------------------------------------------------------------------------------------------------

FUNCTION Tuseful_obj. nearlymin(
    CONST _a, _b: DOUBLE):
  DOUBLE;
  // AD-_able version of min: generalized mean with p = -16.
  // _a & _b>0. Can't exceed min( _a, _b) _by more than 5%
VAR
  _bb, _b2, _b4, _b8, _b16, m: DOUBLE;
BEGIN
  _bb:= _b/_a;

  _b2:= _bb*_bb;
  _b4:= _b2*_b2;
  _b8:= _b4*_b4;
  _b16:= _b8*_b8;

  m:= 0.5*_b16 / (1+_b16);

  RESULT:= _a*SQRT( SQRT( SQRT( SQRT( m))));
END;

//-------------------------------------------------------------------------------------------------------------------

FUNCTION Tuseful_obj. nearlymax(
    CONST _a, _b: DOUBLE):
  DOUBLE;
  // AD-_able version of max: generalized mean with p = +16.
  // _a & _b>0. Can't fall _below max( _a, _b) _by more than 5%
VAR
  _bb, _b2, _b4, _b8, _b16, m: DOUBLE;
BEGIN
  _bb:= _a/_b;

  _b2:= _bb*_bb;
  _b4:= _b2*_b2;
  _b8:= _b4*_b4;
  _b16:= _b8*_b8;

  m:= 0.5*_b16 / (1+_b16);

  RESULT:= 1/(_a*SQRT( SQRT( SQRT( SQRT( m)))));
END;

//-------------------------------------------------------------------------------------------------------------------


FUNCTION Tuseful_obj. laugamp(
    CONST _y, _p, _lgamma_p: DOUBLE;
    CONST _calc_lgamma_p: BOOLEAN):
  DOUBLE;
//OUTPUT: gammp( _y, _p)-- only checked for 0.5<=_p<=1. Fully differentiable.
// if div_lgamma is FALSE, result is NOT divided by lgamma( _p)
VAR
  _yy, _f, _cc, _a, _lgamma_p_int, twelve: DOUBLE;
  _i: INTEGER;
BEGIN
  {$IFNDEF AD}
  IF IsInfinite( _y) THEN BEGIN
    RESULT:= 1;
EXIT;
  END;
  {$ENDIF}{AD}
  twelve:= 12;
  _yy:= asymp( _y, twelve); // guaranteed to give 1 for _y>36, this range of _p, so

   IF _calc_lgamma_p THEN BEGIN
    _lgamma_p_int:= gammln( _p);
  END ELSE BEGIN
    _lgamma_p_int:= _lgamma_p;
  END;

  _f:= EXP( _p * LN(_yy) - _lgamma_p_int - _yy); // still need div by _p
  // if (_f .eq. 0.0) return -- omit since won't crash and IF is bad for AD
  _cc:= 1;
  RESULT:= 1;
  _a:= _p;
  FOR _i:= 1 TO n_laugamp DO BEGIN
    INCR( _a);
    _cc:= _cc * _yy / _a;
    INCR( RESULT, _cc);
  END;
  RESULT:= RESULT * _f / _p;
END;

//  -expm1(-(s^b)) + s * exp( lgamma( 1-1/b)) * pgamma( s^b, shape=1-1/b, lower.tail=FALSE)

//-------------------------------------------------------------------------------------------------------------------C

{$IFNDEF AD}
PROCEDURE Tuseful_obj. prepare_for_chint(
    CONST _ncheb: INTEGER);
VAR
  _i, _j, _uid, _ncheb2: INTEGER;
  _sum: DOUBLE;
  _dotto, _coseq: ARRAY_1D;
  _idx: ARRAY_1L;
BEGIN
  IF _ncheb=ncheb THEN BEGIN
EXIT;
  END;

  IF _ncheb>0 THEN BEGIN
    dealloc( [@cheb_x, @cheb_wt]);
  END;

  ncheb:= _ncheb;
  incheb:= 1/ncheb;
  _ncheb2:= ncheb DIV 2;
  alloc_arrays( [@_dotto], [_ncheb2], [1], SizeOf( _dotto[1]));
  alloc_arrays( [@_coseq], [ncheb+1], [0], SizeOf( _coseq[1]));
  alloc_arrays( [@_idx], [_ncheb2], [1], SizeOf( _idx[1]));
  alloc_arrays( [@cheb_x, @cheb_wt], [ncheb], [1], SizeOf( cheb_x[1]));

  _dotto[1]:= 2;
  _idx[1]:= 0;
  FOR _i:= 1 TO _ncheb2-1 DO BEGIN
    _dotto[ _i+1]:= 2/(2*_i+1) - 2/(2*_i-1);
    _idx[ _i+1]:= _i;
  END;

  FOR _i:= 1 TO ncheb DO BEGIN
    cheb_x[ _i]:= COS( pi*(_i-0.5)/ncheb);
  END;

  // Could do these with recurrence relation
  FOR _i:= 0 TO _ncheb2-1 DO BEGIN
    _coseq[ _i]:= cos( _i*pi/ncheb);
    _coseq[ ncheb-_i]:= -_coseq[ _i];
  END;
  _coseq[ _ncheb2]:= 0;

  FOR _i:= 1 TO _ncheb2 DO BEGIN
    _sum:= 0;
    FOR _j:= 1 TO _ncheb2 DO BEGIN
      _uid:= _idx[ _j];
      IF _uid>=ncheb THEN BEGIN
        _uid:= 2*ncheb - _uid;
      END;

      INCR( _sum, _dotto[ _j] * _coseq[ _uid]);
      INCR( _idx[_j], 2*(_j-1));
      IF _idx[_j]>=2*ncheb THEN BEGIN
        DECR( _idx[_j], 2*ncheb);
      END;
    END;

    cheb_wt[ _i]:= _sum*incheb;
    cheb_wt[ ncheb+1-_i]:= cheb_wt[_i];
  END;

  dealloc( [@_dotto, @_idx, @_coseq]);
END;
{$ENDIF}{AD}


end.

