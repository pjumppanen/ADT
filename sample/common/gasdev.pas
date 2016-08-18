VAR
   gliset: integer;
   glgset: DOUBLE;

FUNCTION Norm_rnd: DOUBLE;
VAR
   fac,r,v1,v2: DOUBLE;
BEGIN
   IF  (gliset = 0)  THEN BEGIN
      REPEAT
         v1 := 2.0*random-1.0;
         v2 := 2.0*random-1.0;
         r := sqr(v1)+sqr(v2);
      UNTIL (r < 1.0);
      fac := sqrt(-2.0*ln(r)/r);
      glgset := v1*fac;
      Norm_rnd:= v2*fac;
      gliset := 1
   END ELSE BEGIN
      Norm_rnd:= glgset;
      gliset := 0
   END
END;
