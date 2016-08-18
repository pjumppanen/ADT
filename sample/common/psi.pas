CONST lower_psi_limit: SINGLE = 1e-5;
      upper_psi_limit: SINGLE = 8.5;
      half:            SINGLE = 0.5;
      inv_12:          SINGLE = 1/12;
      inv_120:         SINGLE = 1/120;
      inv_252:         SINGLE = 1/252;

{****************************************************************************}

FUNCTION LN_minus_psi_of_big( x: DOUBLE):
DOUBLE;
VAR
  inv_x, inv_x2: DOUBLE;
BEGIN
  inv_x:= 1/x;
  inv_x2:= SQR( inv_x);
  LN_minus_psi_of_big:=
    half*inv_x + inv_x2*(inv_12 - inv_x2 * (inv_120 - inv_252*inv_x2));
END;

{****************************************************************************}

FUNCTION psi( x: DOUBLE):
         DOUBLE;
VAR subtract: DOUBLE;
//    comp_result: WORD;
BEGIN
  IF x < lower_psi_limit THEN
    psi:= -Euler_gamma-1/x
  ELSE
  BEGIN
    subtract:= 0;
    WHILE x < upper_psi_limit DO
    BEGIN
      subtract:= subtract + 1/x;
      x:= x+1;
    END;

    psi:= LN( x) - ln_minus_psi_of_big( x) - subtract;
  END;
END;

{****************************************************************************}

FUNCTION LN_minus_psi( x: DOUBLE):
         DOUBLE;
BEGIN
  IF x < upper_psi_limit THEN
    LN_minus_psi:= LN( x) - psi( x)
  ELSE
    LN_minus_psi:= LN_minus_psi_of_big( x);
END;

{****************************************************************************}

FUNCTION psi_dash( x: DOUBLE):
         DOUBLE;

CONST n_terms = 5;
      cft: ARRAY[ 1..n_terms] OF DOUBLE
         = ( 1, 0.166666666667, -0.0333333333333, 2.3809523810e-2, -0.0333333333333);

VAR k, klim: INTEGER;
    poly,
    x_power,
    sum: DOUBLE;

BEGIN
  IF x<lower_psi_limit THEN
  BEGIN
    psi_dash:= 1/SQR(x);
EXIT;
  END;

  sum:= 0;
  IF x<upper_psi_limit THEN
  BEGIN
    klim:= TRUNC(upper_psi_limit-x);
    FOR k:= 0 TO klim DO
       sum:= sum + 1 / SQR( k + x);
    x:= x+klim+1;
  END;

  x_power:= 1 / x;
  x:= SQR( x_power);
  sum:= sum + 0.5*x;

  poly:= cft[ n_terms];
  FOR k:= n_terms-1 DOWNTO 1 DO
    poly:= poly * x + cft[ k];

  psi_dash:= sum + x_power * poly;
END;

{****************************************************************************}

FUNCTION dnpsi( n: INTEGER; x: DOUBLE):
         DOUBLE;

{*******************************}

  FUNCTION dninvxpwr( xpwr, dn: INTEGER; x: DOUBLE):
           DOUBLE;
  VAR mul: DOUBLE;
      i:   INTEGER;
  BEGIN
    mul:= ipwr( x, -xpwr-dn);
    FOR i:= 1 TO dn DO
      mul:= -mul * (xpwr+i-1);
    dninvxpwr:= mul;
  END;

{*******************************}

CONST n_terms = 5;
      cft: ARRAY[ 1..n_terms] OF DOUBLE
         = ( 1, 1/6, -1/30, 1/42, -1/30);

VAR k, klim: INTEGER;
    sum: DOUBLE;

BEGIN
  dnpsi:= QNAN; {* in case of trouble *}
  IF n<1 THEN
  BEGIN
    CASE n OF
      0:  dnpsi:= psi( x);
      1:  dnpsi:= psi_dash( x);
    END;

    EXIT;
  END;

  IF x<lower_psi_limit THEN
  BEGIN
    sum:= ipwr( -x, -(n+1));
    FOR k:= 2 TO n DO
      sum:= sum * k;
    dnpsi:= sum;
EXIT;
  END;

  sum:= 0;
  IF x < upper_psi_limit THEN
  BEGIN
    klim:= TRUNC(upper_psi_limit-x);
    FOR k:= 0 TO klim DO
       sum:= sum + ipwr( k+x, -n-1);
    sum:= sum * dninvxpwr( 2, n-1, 1);
    x:= x+klim+1;
  END;

  sum:= sum - dninvxpwr( 1, n, x) / 2;

  FOR k:= 1 TO n_terms DO
    sum:= sum + cft[ k] * dninvxpwr( 2*k-1, n-1, x);

  dnpsi:= sum;
END;

