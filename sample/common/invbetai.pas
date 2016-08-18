FUNCTION inv_betai_starting_value( a, b, p, ln_beta: SINGLE):
         SINGLE;
VAR r, y, t,
    s, h, w, temp: SINGLE;
BEGIN
  r:= SQRT( -2*LN( p));
  y:= r - (2.30753+0.27061*r) / (1 + r*(0.99229*0.04481*r));
  IF (a<=1) OR (b<=1) THEN
  BEGIN
    r:= b+b;
    t:= 1/(9*b);
    t:= r * ipwr( 1 - t + y * SQRT( t), 3);
    IF t>0 THEN
    BEGIN
      t:= (4*a + r - 2) / t;
      IF t>1 THEN
        temp:= 1-2/(1+t)
      ELSE
        temp:= EXP( (LN( a*p) + ln_beta) / a);
    END
    ELSE
      temp:= 1 - EXP( (LN( b*(1-p)) + ln_beta) / b);
  END
  ELSE
  BEGIN
    r:= ( SQR( y) - 3) / 6;
    s:= 1 / (a+a-1); t:= 1 / (b+b-1);
    h:= 2 / (s+t);
    w:= y * SQRT( h+r) / h - (t-s) * (r + 5/6 - 2 / (3*h));
    temp:= a / ( a + b * EXP( w+w));
  END;

  inv_betai_starting_value:= temp;
END;

{****************************************************************************}

FUNCTION inv_betai_primitive( a, b, p,
                              ln_beta: EXTENDED):
         EXTENDED;

CONST acu = 1e-14;

VAR sufficiently_accurate,
    plausible_new_est,
    swapping: BOOLEAN;
    tx, temp,
    g, r,
    t, y,
    sq, adj,
    old_y, prev: DOUBLE;

BEGIN
  inv_betai_primitive:= QNAN;
  IF (a<0) OR (b<0)
  OR ((a=0) AND (b=0))
  OR (p<0) OR (p>1)
  OR ( (p*(1-p)=0) AND (a*b=0)) THEN
    EXIT;

  inv_betai_primitive:= p;
  IF (p=0) OR (p=1) THEN
    EXIT;

  inv_betai_primitive:= ORD( b=0);
  IF (a=0) OR (b=0) THEN
    EXIT;

{* Reverse if necessary *}

  swapping:= p>0.5;
  IF swapping THEN
  BEGIN
    p:= 1-p;
    temp:= a;
    a:= b;
    b:= temp;
  END;

{* Initial approximation: *}

  temp:= inv_betai_starting_value( a, b, p, ln_beta);

{* Solve for x by modified NR, calling BETAI *}

  r:= 1 - a;
  t:= 1 - b;
  y:= 0;
  sq:= 1;
  prev:= 1;

  temp:= Math. MAX( 1e-4, temp);
  temp:= Math. MIN( 1-1e-4, temp);
  tx:= temp;

  REPEAT
    old_y:= y;
    temp:= tx;

    y:= betai_known_beta( a, b, temp, ln_beta);
    y:= (y-p) * EXP( ln_beta + r*LN( temp) + t*LN( 1-temp));
    IF y*old_y<=0 THEN
      prev:= sq;

    g:= 1;

    sufficiently_accurate:= (prev<=acu) OR (SQR(y)<=acu);
{*  But we still want to do at least one pass of the following: *}

    REPEAT
      adj:= g*y;
      sq:= SQR( adj);
      g:= (1/3) * g; {* ready for next time *}

      plausible_new_est:= FALSE;
      IF sq<prev THEN
      BEGIN
        tx:= temp - adj;
        IF (tx>=0) AND (tx<=1) THEN
        BEGIN
          plausible_new_est:= sufficiently_accurate
                           OR ((tx<>0) AND (tx<>1));

          IF NOT plausible_new_est THEN
          BEGIN
            plausible_new_est:= (tx=temp);
            IF plausible_new_est THEN
              sufficiently_accurate:= TRUE;
          END;
        END;
      END;

    UNTIL plausible_new_est;
  UNTIL sufficiently_accurate;

  IF swapping THEN
    inv_betai_primitive:= 1-temp
  ELSE
    inv_betai_primitive:= temp;
END;

