VAR private_binomial_block: binomial_block;

FUNCTION Binomial( VAR BB: Binomial_block):
         LONGINT;
          {*(pp: real; n: LONGINT; VAR idum: integer): real;*}
LABEL 1;
VAR
   em, y:  DOUBLE;
   bnl, j: LONGINT;

BEGIN
WITH BB DO
BEGIN
  CASE distribution OF

  small_n:
    BEGIN
      bnl:= 0;
      FOR j:= 1 to n DO
      IF random < p THEN
        INC( bnl);
    END;

  small_mean:
    BEGIN
      y:= 1.0;
      bnl:= -1;

      WHILE ( y >= g)
      AND ( bnl < n) DO
      BEGIN
        y:= y * random;
        INC( bnl);
      END;
    END;

  ELSE
    REPEAT
      REPEAT
        y:= TAN( pi * random);
        em:= sq * y + am;
      UNTIL (em >= 0)
      AND (em < n+1);

      bnl:= TRUNC( em);

      y:= 1.2 * sq * (1+sqr(y))
        * EXP( oldg - gammln( SUCC( bnl))
             - gammln( SUCC( n - bnl))
             + bnl * plog
             + ( n - bnl) * pclog);
    UNTIL random <= y;
  END;

  IF swapping_prob THEN
    Binomial:= n - bnl
  ELSE
    Binomial:= bnl;
END;
END;

{****************************************************************************}

PROCEDURE set_binomial_block( VAR bb: Binomial_block;
                                  nn: LONGINT;
                                  pp: DOUBLE);
BEGIN
WITH bb DO
BEGIN
  n:= nn;
  swapping_prob:= pp > 0.5;
  IF swapping_prob THEN
    p:= 1 - pp
  ELSE
    p:= pp;
  am:= n*p;

  IF n < 25 THEN
    distribution:= small_n
  ELSE
  IF am < 1 THEN
  BEGIN
    distribution:= small_mean;
    g:= exp(-am);
  END
  ELSE
  BEGIN
    distribution:= large_mean;
    pc:= 1 - p;
    plog:= ln(p);
    pclog:= ln(pc);
    sq:= sqrt(2.0*am*pc);
    oldg:= gammln(n+1.0);
  END;
END;
END;

{****************************************************************************}

FUNCTION Bin_rnd( n: LONGINT;
                  p: DOUBLE):
         LONGINT;
BEGIN
  set_binomial_block( private_binomial_block, n, p);
  Bin_rnd:= Binomial( private_binomial_block);
END;