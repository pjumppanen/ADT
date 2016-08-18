VAR private_Poisson_block: Poisson_block;

{****************************************************************************}

FUNCTION TAN( theta: DOUBLE):
         DOUBLE;
ASSEMBLER;
ASM
  fld theta;
  fptan;
  fcomp st(0); {* Pop top of stack, which contains 1 after fptan *}
  fwait;
END;


{****************************************************************************}

PROCEDURE set_Poisson_block( VAR p: Poisson_block;
                                 lambda: DOUBLE);
BEGIN
  p. xm:= lambda;
  WITH p DO
  IF xm < 12 THEN
    glg:= EXP( -xm)
  ELSE
  BEGIN
    glsq := sqrt(2.0*xm);
    glalxm := ln(xm);
    glg := xm*glalxm-gammln(xm+1.0)
  END;
END;

{****************************************************************************}


FUNCTION Poisson( VAR p: Poisson_block):
         LONGINT;

VAR em,t,y: DOUBLE;
    iem: LONGINT;

BEGIN
WITH p DO
  IF (xm < 12.0) THEN
  BEGIN
   iem := -1;
   t := 1.0;
   REPEAT
      INC( iem);
      t := t*random;
   UNTIL (t <= glg)
  END
  ELSE
  REPEAT
    REPEAT
      y:= TAN( pi * random);
      em := glsq * y + xm;
    UNTIL (em >= 0) AND (em < $7FFFFFFF); {* To avoid overflow *}

    iem := trunc(em);
    t:= iem*glalxm-gammln(iem+1)-glg;

{* Check whether this value is grossly unlikely *}
    IF t > -11000 THEN
      t := 0.9*(1+sqr(y))*exp(t)
    ELSE
      t := 0;
  UNTIL (random < t);

  Poisson := iem;
END;

{****************************************************************************}

FUNCTION Poi_rnd( lambda: DOUBLE):
         LONGINT;
BEGIN
  IF private_Poisson_block. xm <> lambda THEN
    set_Poisson_block( private_Poisson_block, lambda);
  Poi_rnd:= Poisson( private_Poisson_block);
END;
