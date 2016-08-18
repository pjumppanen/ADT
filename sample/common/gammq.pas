FUNCTION gammq_GLN( a,x, gln: DOUBLE;
                    gln_known: BOOLEAN): DOUBLE;
CONST ninth = 1/9;
VAR argument,
   gamser: DOUBLE;

BEGIN
   IF a>200 THEN
   BEGIN
{* Use Normal approximation given in Abramowitz & Stegun; we will split
   up the calculation to avoid stack overflows *}

     argument:= PWR(x/a,1/3)-1+ninth/a;
     argument:= argument / SQRT( ninth/a);
     GammQ_GLN:= 1-cum_normal_prob(argument);
   END
   ELSE
   IF (x < a+1) THEN
   BEGIN
     gser(a,x,gamser,gln,gln_known);
     gammq_GLN:= 1-gamser;
   END
   ELSE
   BEGIN
     gcf(a,x,gamser,gln,gln_known);
     gammq_GLN:= gamser;
   END
END;

{****************************************************************************}

FUNCTION GammQ( a, x: DOUBLE): DOUBLE;
BEGIN
  GammQ:= GammQ_GLN( a, x, 0, FALSE);
END;
