CONST
   old_cof: ARRAY [1..6] OF DOUBLE = ( 76.18009173, -86.50532033, 24.01409822,
                                -1.231739516, 0.120858003e-2, -0.536382e-5);

   stp = 2.50662827465;
   LN_stp: DOUBLE = 0.918938533212252;
   four_half: DOUBLE = 4.5;
   neg_half: DOUBLE = -0.5;
{$IFOPT G-}
   LN2: DOUBLE = 0.69314718055994531;
{$ENDIF}

FUNCTION ASM_gammln_big( xx: DOUBLE): DOUBLE;
ASSEMBLER;
ASM
{* Code for this function duplicates that given below *}
  push edi; // MUST PRESERVE EDI IN DELPHI 3+!

{* Set up tmp *}
  fld xx;                      { x }
  fld st;                      { x, x }
  fadd four_half;              { 4.5+x, x }
  fld st(1);                   { x, x+4.5, x }
  fadd neg_half;               { x-0.5, x, x+4.5, x }
  fld st(1);                   { x+4.5, x-0.5, x+4.5 x }
  fyl2x;                       { (x-0.5)*LOG2(x+4.5), x+4.5, x }
{* For some reason, Turbo thinks "fldln2" is a 286/287 instruction (it isn't).
   The following bit of code copes *}
{$IFOPT G+}
  fldln2;                      { LN( 2), (x-0.5)*LOG2(x+4.5), x+4.5, x }
{$ELSE}
  fld LN2;                     { LN( 2), (x-0.5)*LOG2(x+4.5), x+4.5, x }
{$ENDIF}
  fmulp st( 1), st;            { (x-0.5)*LN(x+4.5), x+4.5, x }
  fsubrp st( 1), st;           { (x-0.5)*LN(x+4.5)-(x+4.5), x }
  fxch st( 1);                 { x, (x-0.5)*LN(x+4.5) - (x+4.5) }

{* Load running total *}
  fld1;                        { 1, x, (x-0.5)*LN(x+4.5) - (x+4.5) }
  fxch st(1);                  { x, 1, (x-0.5)*LN(x+4.5) - (x+4.5) }
  mov ecx, 6;
  mov edi, offset old_cof;
  fwait;

@1:
  fld st;                      { x, x, 1, temp }
  fdivr double ptr [edi];    { c/x, x, 1, temp }
  faddp st(2), st;             { x, total, temp }
  fld1;                        { 1, x, total, temp }
  faddp st(1), st;             { x+1, total, temp }
  fwait;
  add edi, 8;
  loop @1;

  fcomp st(0);                 { total temp }

{$IFOPT G+}
  fldln2;                      { LN( 2), total, temp }
{$ELSE}
  fld LN2;                     { LN( 2), total, temp }
{$ENDIF}

  fxch st(1);                  { total, LN( 2), temp }
  fyl2x;                       { LN( total), temp }
  fadd LN_stp;                 { LN( stp*total), temp }
  fadd;                        { LN( stp * total) + temp }
  fwait;
  pop edi;
END;

(* This one isn't used; use the machine code instead...
FUNCTION gammln_for_big(xx: DOUBLE): DOUBLE;



VAR
   x,tmp,ser: DOUBLE;
   j: integer;

BEGIN
   x := xx-1;
   tmp := x+5.5;
   tmp := (x+0.5)*ln(tmp)-tmp;
   ser := 1;
   FOR j := 1 to 6 DO
      ser := ser+cof[j]/( x + j);
   gammln_for_big := tmp+ln(stp*ser);
END;
*)

{****************************************************************************}

FUNCTION gammln( x: DOUBLE):
         DOUBLE;

VAR z: DOUBLE;

BEGIN
  IF x >= 1 THEN
   gammln:= ASM_gammln_big( x)
  ELSE
  BEGIN
    z:= 1 - x;
    x:= SIN( pi * z);
    x:= pi * z / x;
    x:= LN( x);
    x:= x - ASM_gammln_big( 1+z);
    gammln:= x;
{    gammln:= LN( pi * z / SIN( pi * z)) - ASM_gammln_big( 1 + z);}
  END;
END;
