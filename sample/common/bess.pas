FUNCTION bessi0( x: DOUBLE):
         DOUBLE;
CONST p1=1; p2=3.5156229; p3=3.0899424; p4=1.2067492; p5=0.2659732;
      p6=0.0360768; p7=0.0045813;
      q1=0.39894228; q2=0.01328592; q3=0.00225319; q4=-0.00157565;
      q5=0.00916281; q6=-0.02057706; q7=0.02635537; q8=-0.01647633;
      q9=0.00392377;
VAR y, ax: DOUBLE;
BEGIN
  IF isNAN( x) THEN
    bessi0:= QNAN
  ELSE
  IF ABS( x) < 3.75 THEN
  BEGIN
    y:= sqr( x/3.75);
    bessi0:= p1+y*(p2+y*(p3+y*(p4+y*(p5+y*(p6+y*p7)))));
  END
  ELSE
  IF ABS( x)=Infinity THEN
    bessi0:= Infinity
  ELSE
  BEGIN
    ax:= ABS( x);
    y:= 3.75/ax;
    bessi0:= (exp(ax)/sqrt( ax)) *
        (q1+y*(q2+y*(q3+y*(q4+y*(q5+y*(q6+y*(q7+y*(q8+y*q9))))))));
  END;
END;