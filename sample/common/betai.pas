VAR ln_beta_for_betai: SINGLE;

FUNCTION betai(a,b,x: DOUBLE): DOUBLE;
CONST max_n = 30;
      min_par = 5;
      one_third = 0.3333333333333;
      one_ninth = 0.1111111111111;

VAR w1, w2: DOUBLE;

BEGIN
   IF x * ( 1 - x) = 0 THEN
   BEGIN
     betai:= x;
     EXIT;
   END;

   IF ( a + b - 1 > max_n)
   AND ( a > min_par)
   AND ( b > min_par)
   THEN
   BEGIN
     IF ( a + b - 1) * ( 1 - x) < 0.8 THEN
       betai:= gammq( b, (( a + b - 1) * ( 3 - x) - ( b - 1)) * ( 1 - x) * 0.5)
     ELSE
     BEGIN
       w1:= EXP( one_third * LN( b * x));
       w2:= EXP( one_third * LN( a * ( 1 - x)));
       betai:=
         cum_normal_prob( 3 * ( w1 * ( 1 - one_ninth / b)
                              - w2 * ( 1 - one_ninth / a))
                            / SQRT( SQR( w1) / b + SQR( w2) / a));
     END;
   END
   ELSE
   BEGIN
     IF isNAN( ln_beta_for_betai) THEN
       ln_beta_for_betai:= ln_beta_fn( a, b);

      IF x < (a+1) / (a+b+2) THEN
        betai := exp( -ln_beta_for_betai + a*ln(x) + b*ln(1-x))
                * betacf(a,b,x) / a
      ELSE
        betai := 1-exp( -ln_beta_for_betai + a*ln(x) + b*ln(1-x))
                    * betacf(b,a,1-x) / b;
   END;

   ln_beta_for_betai:= QNAN;
END;
{****************************************************************************}

FUNCTION betai_known_beta( a, b, p, ln_beta: DOUBLE):
         DOUBLE;
BEGIN
  ln_beta_for_betai:= ln_beta;
  betai_known_beta:= betai( a, b, p);
END;

