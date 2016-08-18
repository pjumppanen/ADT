FUNCTION ppchi2( p, v, g: DOUBLE): DOUBLE;

CONST e = 0.5e-6;
      aa = 0.6931471805;
      inv_420 = 1/420;
      inv_2520 = 1/2520;
      inv_5040 = 1/5040;

TYPE I=INTEGER;

CONST
  _420:I=420;   _210:I=210;   _140:I=140;   _105:I=105;   _84:I=84;
  _70:I=70;     _60:I=60;     _2520:I=2520; _735:I=735;   _966:I=966;
  _1141:I=1141; _1278:I=1278; _462:I=462;   _707:I=707;   _932:I=932;
  _5040:I=5040; _252:I=252;   _672:I=672;   _1182:I=1182; _294:I=294;
  _889:I=889;   _1740:I=1740; _264:I=264;   _175:I=175;   _606:I=606;
  _120:I=120;   _346:I=346;   _127:I=127;

  half: SINGLE = 0.5;

VAR xx, chi2,
    t, q,
    a, c,
    p1, p2: DOUBLE;
    { b, s1, s2, s3,
    s4, s5, s6 : DOUBLE;}

BEGIN
//  ppchi2:= -1; Failsafe default NOT USED
  xx:= 0.5*v;
  c:= xx-1;

  IF v < -1.24*LN( p) THEN
  BEGIN
{* Starting approximation for small Xý *}

    chi2:= pwr( p * xx * EXP( g + xx*aa), 1/xx);
    IF chi2 < e THEN
    BEGIN
      ppchi2:= chi2;
EXIT;
    END;
  END
  ELSE
  IF v <= 0.32 THEN
  BEGIN
    chi2:= 0.4;
    a:= LN(1-p);
    REPEAT
      q:= chi2;
      p1:= 1 + chi2 * (4.67+chi2);
      p2:= chi2 * ( 6.73 + chi2 * ( 6.66+chi2));
      t:= 6.73 + chi2 * ( 13.32 + 3*chi2);
      t:= -0.5 + ( 4.67 + 2*chi2) / p1 - t / p2;
      chi2:= chi2 - ( 1- EXP( a + g + 0.5*chi2 + c*aa) * p2/p1) / t;
    UNTIL ABS( q/chi2 - 1) <= 0.01;
  END
  ELSE
  BEGIN
    chi2:= Normal( p);

{* Now use Wilson-Hilferty approximation for starting value *}

    p1:= 0.222222 / v;
    chi2:= chi2 * SQRT( p1) + 1-p1;
    chi2:= v * chi2 * SQR( chi2);

{* If p -> 1 ... *}

    IF chi2 > 2.2 * v + 6 THEN
      chi2:= -2 * ( LN( 1-p) - c * LN( 0.5*chi2) + g);
  END;

{* We damn well should have a starting value by now! *}
(* This bit replaced mostly by machine code:
  REPEAT
    q:= chi2;
    p1:= 0.5 * chi2;
    p2:= p - GammP_GLN( xx, p1, g, TRUE);
    t:= p2 * EXP( xx * aa + g + p1 - c * LN( chi2));
    b:= t / chi2;
    a:= 0.5 * t - b * c;
{* Now a 7-term Taylor series *}

    s1:= inv_420 *  ( 210 + a*( 140 + a*( 105 + a*( 84 + a*( 70 + 60*a)))));
    s2:= inv_2520 * ( 420 + a*( 735 + a*( 966 + a*( 1141 + 1278*a))));
    s3:= inv_2520 * ( 210 + a*( 462 + a*( 707 + 932*a)));
    s4:= inv_5040 * ( 252 + a*( 672 + 1182*a) + c*( 294 + a*( 889 + 1740*a)));
    s5:= inv_2520 * ( 84 + 264*a + c*( 175 + 606*a));
    s6:= inv_5040 * ( 120 + c*( 346 + 127*c));
    chi2:= chi2 + t*( 1 + 0.5*t*s1 - b*c*( s1-b*( s2-b*( s3-b*( s4-b*( s5-b*s6))))));
  UNTIL ABS( q/chi2 - 1) < e;
*)

  REPEAT
{* These bits are tedious because of the function calls *}
//    q:= chi2;
    p1:= 0.5 * chi2;
    p2:= p - GammP_GLN( xx, p1, g, TRUE);
    t:= p2 * EXP( xx * aa + g + p1 - c * LN( chi2));

    ASM
{* First load c then t then b *}

      fld c;                 { c }
      fld t;                 { t c }
      fld chi2;                { chi2 t c }
      fdivr st, st( 1);      { b=t/chi2 t c }
      fld st;                { b b t c }
      fmul st, st( 3);       { bc b t c }
      fld st(2);             { t bc b t c }
      fmul half;             { 0.5*t bc b t c }
      fsubrp st(1),st;       { a=0.5*t-bc b t c } {* Hopefully! *}

{* We do s6 then s5, etc., accumulating the nested product for chi2 *}

      fild _127;             { 127 a b t c }
      fmul st,st(4);         { 127c a b t c }
      fiadd _346;            { 346+127c a b t c }
      fmul st,st(4);         { c*(346+127c) a b t c }
      fiadd _120;            { 120+c*(346+127c) a b t c }
      fidiv _5040;           { s6=(1/5040)*120+c*(346+127c) a b t c }
      fmul st, st( 2);       { b*s6 a b t c }

{* Now do s5 *}

      fild _606;             { 606 b*s6 a b t c }
      fmul st, st( 2);       { 606a b*s6 a b t c }
      fiadd _175;            { 175+606a b*s6 a b t c }
      fmul st, st( 5);       { c*(175+606a) b*s6 a b t c }
      fild _264;             { 264 c*(175+606a) b*s6 a b t c } {* 7 on stack *}
      fmul st, st( 3);       { 264a c*(175+606a) b*s6 a b t c }
      faddp st(1),st;        { 264a+c*(175+606a) b*s6 a b t c }
      fiadd _84;             { 84+264a+c*(175+606a) b*s6 a b t c }
      fidiv _2520;           { s5 b*s6 a b t c }
      fsubrp st(1),st;       { nest=s5-b*s6 a b t c }
      fmul st, st( 2);       { nest=b*nest a b t c }

{* Now do s4 *}

      fild _1740;           { 1740 nest a b t c }
      fmul st, st( 2);      { 1740a nest a b t c }
      fiadd _889;           { 889+1740a nest a b t c }
      fmul st, st( 2);      { a*(889+1740a) nest a b t c }
      fiadd _294;           { 294+a*(889+1740a) nest a b t c }
      fmul st, st( 5);      { c*(294+a*(889+1740a)) nest a b t c }
      fild _1182;           { 1182 c*(294+a*(889+1740a)) nest a b t c }
      fmul st, st( 3);      { 1182a c*(294+a*(889+1740a)) nest a b t c }
      fiadd _672;           { 672+1182a c*(294+a*(889+1740a)) nest a b t c }
      fmul st, st( 3);      { a*(672+1182a) c*(294+a*(889+1740a)) nest a b t c }
      faddp st( 1), st;     { a*(672+1182a)+c*(294+a*(889+1740a)) nest a b t c }
      fiadd _252;           { 252+a*(672+1182a)+c*(294+a*(889+1740a)) nest a b t c }
      fidiv _5040;          { s4=(1/5040)*(252+a*(672+1182a)+c*(294+a*(889+1740a))) nest a b t c }
      fsubrp st( 1), st;    { s4-nest a b t c }
      fmul st, st( 2);      { nest=b*(s4-nest) a b t c }

{* Now do s3 *}

      fild _932;            { 932 nest a b t c }
      fmul st, st( 2);      { 932a nest a b t c }
      fiadd _707;           { 707+932a nest a b t c }
      fmul st, st( 2);      { a*(707+932a) nest a b t c }
      fiadd _462;           { 462+a*(707+932a) nest a b t c }
      fmul st, st( 2);      { a*(462+a*(707+932a)) nest a b t c }
      fiadd _210;           { 210+a*(462+a*(707+932a)) nest a b t c }
      fidiv _2520;          { s3=(1/2520)*(210+a*(462+a*(707+932a))) nest a b t c }
      fsubrp st( 1), st;    { s3-nest a b t c }
      fmul st, st( 2);      { nest=b*(s3-nest) a b t c }

{* Now do s2 *}

      fild _1278;           { 1278 nest a b t c }
      fmul st, st( 2);      { 1278a nest a b t c }
      fiadd _1141;          { 1141+1278a nest a b t c }
      fmul st, st( 2);      { a*(1141+1278a) nest a b t c }
      fiadd _966;           { 966+a*(1141+1278a) nest a b t c }
      fmul st, st( 2);      { a*(966+a*(1141+1278a)) nest a b t c }
      fiadd _735;           { 735+a*(966+a*(1141+1278a)) nest a b t c }
      fmul st, st( 2);      { a*(735+a*(966+a*(1141+1278a))) nest a b t c }
      fiadd _420;           { 420+a*(735+a*(966+a*(1141+1278a))) nest a b t c }
      fidiv _2520;          { s2 nest a b t c }
      fsubrp st( 1), st;    { s2-nest a b t c }
      fmul st, st( 2);      { nest=b*(s2-nest) a b t c }

{* And s1... *}

      fild _60;             { 60 nest a b t c }
      fmul st, st( 2);      { 60a nest a b t c }
      fiadd _70;            { 70+60a nest a b t c }
      fmul st, st( 2);      { a*(70+60a) nest a b t c }
      fiadd _84;            { 84+a*(70+60a) nest a b t c }
      fmul st, st( 2);      { a*(84+a*(70+60a)) nest a b t c }
      fiadd _105;           { 105+a*(84+a*(70+60a)) nest a b t c }
      fmul st, st( 2);      { a*(105+a*(84+a*(70+60a))) nest a b t c }
      fiadd _140;           { 140+a*(105+a*(84+a*(70+60a))) nest a b t c }
      fmul st, st( 2);      { a*(140+a*(105+a*(84+a*(70+60a)))) nest a b t c }
      fiadd _210;           { 210+a*(140+a*(105+a*(84+a*(70+60a)))) nest a b t c }
      fidiv _420;           { s1 nest a b t c }

{* Now do the final chi2 calculation *}

      fxch st( 2);          { a nest s1 b t c }
      fcomp st( 0);         { nest s1 b t c }
      fsubr st, st( 1);     { s1-nest s1 b t c }
      fmul st, st( 2);      { b*(s1-nest) s1 b t c }
      fmulp st(4), st;      { s1 b t b*c*(s1-nest) }
      fmul st, st( 2);      { s1*t b t b*c*(s1-nest) }
      fmul half;            { 0.5*s1*t b t b*c*(s1-nest) }
      fsubrp st( 3), st;    { b t 0.5*s1*t-b*c*(s1-nest) }
      fcomp st( 0);         { t nest }
      fld1;                 { 1 t nest }
      faddp st( 2), st;     { t 1+nest }
      fmulp st( 1), st;     { t*(1+nest) }
      fld chi2;             { chi2 t }  {* Can't add directly because chi2 is DOUBLE *}
      faddp st( 1), st;     { chi2'=chi2+t }
      fstp chi2;            { }
      fwait;
    END;
  UNTIL TRUE; (* ABS( q/chi2 - 1) < e; however, this wastes 1 iteration,
                 and for e=0.5e-6, only 1 iteration is needed *)

  ppchi2:= chi2;
END;

{****************************************************************************}

FUNCTION inv_GammP( alpha, p: DOUBLE): DOUBLE;
BEGIN
  inv_GammP:= 0.5*ppchi2( p, 2*alpha, gammln( alpha));
END;

