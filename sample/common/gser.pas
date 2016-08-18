PROCEDURE gser(a, x: DOUBLE; VAR gamser,gln: DOUBLE;
               gln_known: BOOLEAN);
LABEL 1;
CONST
   itmax=100;
   eps: SINGLE = 3.0e-7;
VAR
   comp_result1: LONGINT;
   comp_result2: WORD;
   sum:         DOUBLE;

(* Extra variables used by non-machine code version...
   n: integer;
   del,ap: DOUBLE;
*)

BEGIN
   IF NOT gln_known THEN
     gln:= gammln(a);

   IF (x <= 0) THEN
   BEGIN
      IF (x < 0) THEN
         pause( 'GSER - x less than 0');
      gamser:= 0;
   END
   ELSE
   BEGIN
(* This code is the original non-assembler version...
     ap:= a;
     sum:= 1/a;
     del:= sum;
     FOR n:= 1 to itmax DO BEGIN
        ap:= ap+1;
        del:= del*x/ap;
        sum:= sum+del;
        IF (abs(del) < abs(sum)*eps) THEN GOTO 1
     END;
     pause( 'GSER - a too large, itmax too small');
1:
*)

{* Machine code replacement: *}
     ASM
       mov ecx, itmax;
       fld a;                { a }
       fld1;                 { 1 a }
       fdiv st, st(1);       { 1/a a } {* Check syntax! *}
       fld st;               { 1/a 1/a a }
       fxch st(2);           { a 1/a 1/a = ap del sum }

     @1:
       fld1;                 { 1 ap del sum }
       faddp;                { 1+ap=ap' del sum }
       fxch st(1);           { del ap' sum }
       fdiv st, st(1);       { del/ap' ap' sum }
       fmul x;               { del*x/ap'=del' ap' sum }
       fadd st(2), st;       { del' ap' sum' }
       fld st;               { del' del' ap' sum' }
       fdiv st, st(3);       { del/sum del ap sum }
       fabs;                 { |del/sum| del ap sum }
       fcomp eps;            { del ap sum }
       fstsw comp_result2;    { del ap sum }
       fxch st(1);           { ap del sum; ready for next loop }
       fwait;
       mov ax, comp_result2;
       sahf;
       jb @2;                {* if |del/sum| < eps then stop *}
       loop @1;

     @2:                     { ap del sum }
       fcomp st(0);          { del sum }
       fcomp st(0);          { sum }
       fstp sum;             { }
       fwait;
       mov comp_result1, ecx;  { if cx is 0, then we're out of range }
     END;

     IF comp_result1=0 THEN
       pause( 'GSER - a too large, itmax too small');

     gamser:= sum*exp(-x+a*ln(x)-gln)
   END
END;


