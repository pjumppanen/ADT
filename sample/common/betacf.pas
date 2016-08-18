FUNCTION betacf(a,b,x: EXTENDED): EXTENDED;
LABEL 1;
CONST
   itmax=100;
   eps=3.0e-7;
VAR
   tm,qap,qam,qab,d: EXTENDED;
   bz,bpp,bp,bm,az,app: EXTENDED;
   am,aold,ap: EXTENDED;
   m: integer;
BEGIN
   am:= 1;
   bm:= 1;
   az:= 1;
   qab:= a+b;
   qap:= a+1;
   qam:= a-1;
   bz:= 1-qab*x/qap;
   FOR m:= 1 to itmax DO BEGIN
      tm:= m+m;
      d:= m*(b-m)*x/((qam+tm)*(a+tm));
      ap:= az+d*am;
      bp:= bz+d*bm;
      d:= -(a+m)*(qab+m)*x/((a+tm)*(qap+tm));
      app:= ap+d*az;
      bpp:= bp+d*bz;
      aold:= az;
      am:= ap/bpp;
      bm:= bp/bpp;
      az:= app/bpp;
      bz:= 1;
      IF ABS( aold/az-1) < eps THEN GOTO 1
   END;
   pause( 'BETACF- a or b too big, or itmax too small');
1:   betacf:= az
END;
