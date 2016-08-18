PROCEDURE gcf(a,x: DOUBLE; VAR gammcf,gln: DOUBLE;
              gln_known: BOOLEAN);
(* LABEL 1; *)
CONST
   itmax=100;
   eps: SINGLE = 3.0e-7;
VAR
   comp_result: WORD;
   n: integer;
   //gold,
   g: DOUBLE;

(* Used by non-machine code version:
   fac,b1,b0,anf,ana,a1,a0: DOUBLE; *)

BEGIN
   IF NOT gln_known THEN
     gln:= gammln(a);
(* Non-machine code version:
   gold:= 0;
   a0:= 1;
   a1:= x;
   b0:= 0;
   b1:= 1;
   fac:= 1;
   FOR n:= 1 to itmax DO BEGIN
      ana:= n-a;
      a0:= (a1+a0*ana)*fac;
      b0:= (b1+b0*ana)*fac;
      anf:= n*fac;
      a1:= x*a0+anf*a1;
      b1:= x*b0+anf*b1;
      IF (a1 <> 0) THEN BEGIN
         fac:= 1/a1;
         g:= b1*fac;
         IF (abs((g-gold)/g) < eps) THEN GOTO 1;
         gold:= g
      END
   END;
   pause( 'GCF - a too large, itmax too small');
1:
*)

(* Machine code replacement: *)

  n:= 1;
  g:= 0;

  ASM
    mov ecx, itmax;

{* Initialize *}

    fld1;                         { fac=1 }
    fld st;                       { b1=1 fac }
    fld x;                        { a1 b1 fac }
    fldz;                         { b0=0 a1 b1 fac }
    fld st(2);                    { a0=1 b0 a1 b1 fac; called "terms" }

@1:
{* Update terms *}
    fild n;                       { n terms }
    fsub a;                       { ana=n-a terms }
    fld st;                       { ana ana terms }
    fmul st,st(2);                { ana*a0 ana terms }
    fadd st,st(4);                { a1+ana*a0 ana terms }
    fmul st,st(6);                { a0'=fac*(a1+ana*a0) ana terms }
    fstp st(2);                   { ana terms (with a0') }

    fmul st,st(2);                { ana*b0 terms }
    fadd st,st(4);                { b1+ana*b0 terms }
    fmul st,st(5);                { b0'=fac*(b1+ana*b0) terms }
    fstp st(2);                   { terms (with b0') }

    fild n;                       { n terms }
    fmul st,st(5);                { anf=n*fac terms }
    fld st;                       { anf anf terms }
    fmul st,st(4);                { anf*a1 anf terms }
    fld x;                        { x anf*a1 anf terms } {* 8 on stack *}
    fmul st,st(3);                { x*a0 anf*a1 anf terms }
    faddp st(1), st;              { a1'=x*a0+anf*a1 anf terms }
    fstp st(4);                   { anf terms (with a1') }

    fmul st,st(4);                { anf*b1 terms }
    fld x;                        { x anf*b1 terms }
    fmul st,st(3);                { x*b0 anf*b1 terms }
    faddp st(1), st;              { b1'=x*b0+anf*b1 terms }
    fstp st(4);                   { terms }

  {* Now, if a1<>0, we must renormalize the terms & do the test *}

    fld st(2);                    { a1 terms }
    ftst;                         { a1 terms }
    fstsw comp_result;
    fwait;
    mov ax, comp_result;
    sahf;
    jz @2;

  {* Renormalize... *}

    fld1;                         { 1 a1 terms }
    fdivrp st(1), st;             { fac=1/a1 terms }
    fst st(5);                    { fac terms (with new fac) }
    fmul st,st(4);                { g=b1*fac terms }
    fld st;                       { g g terms }
    fsub g;                       { g-gold g terms } {* NB gold stored in g *}
    fdiv st, st( 1);              { (g-gold)/g g terms }
    fabs;                         { |(g-gold)/g| g terms }
    fcomp eps;                    { g terms }
    fstsw comp_result;            { g terms }
    fwait;
    fst g;                        { g terms } {* g left on stack for comp. with a1=0 case *}
    fwait;
    mov ax, comp_result;
    sahf;
    jb @3;

  @2:
    fcomp st(0);                  { terms }
    fwait;
    inc n;

{$DEFINE LOOP_OK}
{$IFOPT E+}
  {$UNDEF LOOP_OK}
{$ENDIF}
{$IFOPT G-}
  {$UNDEF LOOP_OK}
{$ENDIF}
{$IFDEF VER70}
  {$UNDEF LOOP_OK}
{$ENDIF}

{$IFDEF LOOP_OK}
    loop @1;
{$ELSE} {* @1 isn't within range of the loop *}
    dec ecx;
    jecxz @4;
    jmp @1;
{$ENDIF}

  @4:
    fld st(2);                    { a1 terms }

  @3:
    fcomp st(0);                  { a0 b0 a1 b1 fac }
    fcomp st(0);                  { b0 a1 b1 fac }
    fcomp st(0);                  { a1 b1 fac }
    fcomp st(0);                  { b1 fac }
    fcomp st(0);                  { fac }
    fcomp st(0);                  { }
    fwait;
    mov comp_result, cx;          { something terms } {* whether from convergence or boredom *}
  END;

  IF comp_result=0 THEN
    pause( 'GCF - a too large, itmax too small');

  gammcf:= exp(-x+a*ln(x)-gln)*g;
END;

