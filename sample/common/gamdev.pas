FUNCTION gamdev( ia: WORD):
         EXTENDED;
VAR
   am,e,s,v1,v2,x,y: EXTENDED;
   j: integer;
BEGIN
   IF (ia < 6) THEN BEGIN
      x := 1.0;
      FOR j := 1 to ia DO x := x*random;
      x := -ln(x);
   END ELSE BEGIN
      REPEAT
         REPEAT
            REPEAT
               v1 := 2.0*random-1.0;
               v2 := 2.0*random-1.0;
            UNTIL ((sqr(v1)+sqr(v2)) <= 1.0);
            y := v2/v1;
            am := ia-1;
            s := sqrt(2.0*am+1.0);
            x := s*y+am;
         UNTIL (x > 0.0);
{
         e := (1.0+sqr(y))*exp(am*ln(x/am)-s*y);
      UNTIL (random <= e)
}
         e:= LN(1+SQR(y)) + am*LN(x/am) - s*y;
      UNTIL LN( random) <= e;
   END;
   gamdev := x
END;
