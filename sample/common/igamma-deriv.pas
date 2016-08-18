TYPE
  DAR6 = ARRAY[ 1..6] OF DOUBLE;
{
   Algorithm as 187  appl. statist. (1982) vol.31, no.3

   Computes derivatives of the incomplete gamma integral for positive
   parameters, x, p, using a series expansion if p > x or x <= 1, and
   a continued fraction expansion otherwise.

   calculation of d(4) in line 60 corrected 5 october 1993.

   N.B. the user must input values of the incomplete gamma, digamma
        and trigamma functions.  these can be obtained using as 239
        (or 32), as 103 and as 121 respectively.
}

PROCEDURE digami(
      d: PDOUBLE_ARRAY;
      x, p, gplog, gp1log, psip, psip1, psidp, psidp1: DOUBLE;
  VAR ifault: LONGINT);

VAR
  pn, dp, dpp: DAR6;
  pm1, c, s, cp, f, dfp, dfpp, xlog, cpp, csp, dsp, dspp, a, an, cpc, b, term, s0, tmaxp: DOUBLE;
  i, i2: INTEGER;

CONST
  e = 1e-6;
  oflo = 1e30;
  tmax = 100;
  vsmall = 1e-30;

BEGIN
  ifault:= 0;

  IF isNAN( gplog) THEN
    gplog:= gammln( p);
  IF isNAN( psip) THEN
    psip:= psi( p);
  IF isNAN( psidp) THEN
    psidp:= psi_dash( p);

  // The "1" versions are of p+1, cheaply calculated from the "no-1" versions    
  IF isNAN( gp1log) THEN
    gp1log:= LN( p)+gplog;
  IF isNAN( psip1) THEN
    psip1:= 1/p + psip;
  IF isNAN( psidp1) THEN
    psidp1:= -1/SQR( p) + psidp;

  //  derivatives with respect to x
  pm1:= p-1;
  xlog:= LN(x);
  d[1]:= exp(-gplog + pm1*xlog - x);
  d[2]:= d[1] * (pm1/x - 1);
  d[5]:= d[1] * (xlog - psip);

  // derivatives with respect to p

  IF (x<=1) OR (x<p) THEN
  BEGIN
    // Series expansion
    f:= exp(p*xlog - gp1log - x);
    dfp:= f * (xlog - psip1);
    dfpp:= dfp*dfp/f - f*psidp1;

    tmaxp:= tmax + p;
    c:= 1;
    s:= 1;
    cp:= 0;
    cpp:= 0;
    dsp:= 0;
    dspp:= 0;
    a:= p;
    REPEAT
      a:= a + 1;
      cpc:= cp / c;
      cp:= cpc - 1/a;
      cpp:= cpp/c - SQR( cpc) + 1/SQR(a);
      c:= c*x/a;
      cp:= cp*c;
      cpp:= cpp*c + cp*cp/c;
      s:= s + c;
      dsp:= dsp + cp;
      dspp:= dspp + cpp;
      IF a>tmaxp THEN
      BEGIN
        ifault:= 1;
EXIT;
      END;
    UNTIL NOT (c>e*s);

    // SUCCESS
    d[6]:= s*f;
    d[3]:= s*dfp + f*dsp;
    d[4]:= s*dfpp + 2*dfp*dsp + f*dspp;
  END
  ELSE BEGIN
    // Continued fraction expansion
    f:= exp(p*xlog - gplog - x);
    dfp:= f * (xlog - psip);
    dfpp:= dfp*dfp/f - f*psidp;

    a:= pm1;
    b:= x + 1 - a;
    term:= 0;
    pn[1]:= 1;
    pn[2]:= x;
    pn[3]:= x + 1;
    pn[4]:= x * b;
    s0:= pn[3] / pn[4];

    FOR i:= 1 TO 4 DO
    BEGIN
      dp[ i]:= 0; dpp[ i]:= 0;
    END;
    dp[4]:= -x;

    REPEAT
      a:= a - 1;
      b:= b + 2;
      term:= term + 1;
      an:= a*term;
      pn[5]:= b*pn[3] + an*pn[1];
      pn[6]:= b*pn[4] + an*pn[2];
      dp[5]:= b*dp[3] - pn[3] + an*dp[1] + pn[1]*term;
      dp[6]:= b*dp[4] - pn[4] + an*dp[2] + pn[2]*term;
      dpp[5]:= b*dpp[3] + an*dpp[1] + 2*(term*dp[1] - dp[3]);
      dpp[6]:= b*dpp[4] + an*dpp[2] + 2*(term*dp[2] - dp[4]);

      IF NOT (abs(pn[6])<vsmall) THEN
      BEGIN
        s:= pn[5] / pn[6];
        c:= abs(s - s0);
        IF NOT (c*p>e) THEN
        BEGIN
          IF c<e*s THEN
      BREAK;
        END;

        s0:= s;
      END;

      FOR i:= 1 TO 4 DO
      BEGIN
        i2:= i + 2;
        dp[i]:= dp[i2];
        dpp[i]:= dpp[i2];
        pn[i]:= pn[i2];
      END;

      IF term > tmax THEN
      BEGIN
        ifault:= 1;
EXIT;
      END;

      IF abs(pn[5])<oflo THEN
    CONTINUE;

      FOR i:= 1 TO 4 DO
      BEGIN
        dp[i]:= dp[i] / oflo;
        dpp[i]:= dpp[i] / oflo;
        pn[i]:= pn[i] / oflo;
      END;
    UNTIL FALSE;

    d[6]:= 1 - f*s;
    dsp:= (dp[5] - s*dp[6]) / pn[6];
    dspp:= (dpp[5] - s*dpp[6] - 2*dsp*dp[6]) / pn[6];
    d[3]:= -f*dsp - s*dfp;
    d[4]:= -f*dspp - 2*dsp*dfp - s*dfpp;
  END;
END;



(*
      SUBROUTINE DIGAMI(D, X, P, GPLOG, GP1LOG, PSIP, PSIP1, PSIDP,
     *     PSIDP1, IFAULT)
C
C     ALGORITHM AS 187  APPL. STATIST. (1982) VOL.31, NO.3
C
C     Computes derivatives of the incomplete gamma integral for positive
C     parameters, X, P, using a series expansion if P > X or X <= 1, and
C     a continued fraction expansion otherwise.
C
C     Calculation of D(4) in line 60 corrected 5 October 1993.
C
C     N.B. The user must input values of the incomplete gamma, digamma
C          and trigamma functions.  These can be obtained using AS 239
C          (or 32), AS 103 and AS 121 respectively.
C
      REAL PN(6), D(6), DP(6), DPP(6), ZERO, ONE, TWO
      DATA E, OFLO, TMAX, VSMALL/1.E-6, 1.E30, 100.0, 1.E-30/
      DATA ZERO/0.0/, ONE/1.0/, TWO/2.0/
C
      IFAULT = 0
C
C     Derivatives with respect to X
C
      PM1 = P - ONE
      XLOG = LOG(X)
      D(1) = EXP(-GPLOG + PM1*XLOG - X)
      D(2) = D(1) * (PM1/X - ONE)
      D(5) = D(1) * (XLOG - PSIP)
C
C     Derivatives with respect to P
C
      IF (X .GT. ONE .AND. X .GE. P) GO TO 30
C
C     Series expansion
C
      F = EXP(P*XLOG - GP1LOG - X)
      DFP = F * (XLOG - PSIP1)
      DFPP = DFP*DFP/F - F*PSIDP1
C
      TMAXP = TMAX + P
      C = ONE
      S = ONE
      CP = ZERO
      CPP = ZERO
      DSP = ZERO
      DSPP = ZERO
      A = P
    1 A = A + ONE
      CPC = CP / C
      CP = CPC - ONE/A
      CPP = CPP/C - CPC*CPC + ONE/A**2
      C = C*X/A
      CP = CP*C
      CPP = CPP*C + CP*CP/C
      S = S + C
      DSP = DSP + CP
      DSPP = DSPP + CPP
      IF (A .GT. TMAXP) GO TO 1001
      IF (C .GT. E*S) GO TO 1
      D(6) = S*F
      D(3) = S*DFP + F*DSP
      D(4) = S*DFPP + TWO*DFP*DSP + F*DSPP
      RETURN
C
C     Continued fraction expansion
C
   30 F = EXP(P*XLOG - GPLOG - X)
      DFP = F * (XLOG - PSIP)
      DFPP = DFP*DFP/F - F*PSIDP
C
      A = PM1
      B = X + ONE - A
      TERM = ZERO
      PN(1) = ONE
      PN(2) = X
      PN(3) = X + ONE
      PN(4) = X * B
      S0 = PN(3) / PN(4)
      DO 31 I = 1, 4
	DP(I) = ZERO
	DPP(I) = ZERO
   31 CONTINUE
      DP(4) = -X
C
   32 A = A - ONE
      B = B + TWO
      TERM = TERM + ONE
      AN = A*TERM
      PN(5) = B*PN(3) + AN*PN(1)
      PN(6) = B*PN(4) + AN*PN(2)
      DP(5) = B*DP(3) - PN(3) + AN*DP(1) + PN(1)*TERM
      DP(6) = B*DP(4) - PN(4) + AN*DP(2) + PN(2)*TERM
      DPP(5) = B*DPP(3) + AN*DPP(1) + TWO*(TERM*DP(1) - DP(3))
      DPP(6) = B*DPP(4) + AN*DPP(2) + TWO*(TERM*DP(2) - DP(4))
C
      IF (ABS(PN(6)) .LT. VSMALL) GO TO 35
      S = PN(5) / PN(6)
      C = ABS(S - S0)
      IF (C*P .GT. E) GO TO 34
      IF (C .LE. E*S) GO TO 42
C
   34 S0 = S
   35 DO 36 I = 1, 4
        I2 = I + 2
        DP(I) = DP(I2)
        DPP(I) = DPP(I2)
        PN(I) = PN(I2)
   36 CONTINUE
C
      IF (TERM .GT. TMAX) GO TO 1001
      IF (ABS(PN(5)) .LT. OFLO) GO TO 32
      DO 41 I = 1, 4
	DP(I) = DP(I) / OFLO
	DPP(I) = DPP(I) / OFLO
	PN(I) = PN(I) / OFLO
   41 CONTINUE
      GO TO 32
C
   42 D(6) = ONE - F*S
      DSP = (DP(5) - S*DP(6)) / PN(6)
      DSPP = (DPP(5) - S*DPP(6) - TWO*DSP*DP(6)) / PN(6)
      D(3) = -F*DSP - S*DFP
      D(4) = -F*DSPP - TWO*DSP*DFP - S*DFPP
      RETURN
C
C     Set fault indicator
C
 1001 IFAULT = 1
      RETURN
      END


*)
