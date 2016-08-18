UNIT D_Tuseful_obj_unit;
INTERFACE
USES
  Useful,
  Math,
  Maths32,
tuseful_obj_unit;
TYPE
  D_Tuseful_obj=CLASS( Tuseful_obj)
    {$IFNDEF AD}
    FUNCTION logdet_and_chol(
        CONST ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
        CONST nchol: INTEGER):
      DOUBLE; OVERRIDE;
    FUNCTION logdet_and_chol_neg(
        CONST neg_ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
        CONST nchol: INTEGER):
      DOUBLE; OVERRIDE;
    PROCEDURE backsolve_chol(
        CONST rchol{nchol,nchol}: ARRAY_2D;
        CONST target{nchol}, sol{nchol}: ARRAY_1D;
        CONST nchol: INTEGER); OVERRIDE;
    FUNCTION quadform(
        CONST xqf{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER):
      DOUBLE; OVERRIDE;
    {$ENDIF}{AD}
    PROCEDURE quadform_b(
        CONST xqf{nqf}, xqf_b{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER;
        VAR   xqf_wt: DOUBLE); OVERRIDE;
    FUNCTION quadform_d(
        CONST xqf{nqf}, xqf_dir{nqf}: ARRAY_1D;
        CONST hqf{nqf,nqf}: ARRAY_2D;
        CONST nqf: INTEGER;
        VAR   hxh: DOUBLE):
      DOUBLE; OVERRIDE;
  END;
IMPLEMENTATION

{$IFNDEF AD}
FUNCTION D_Tuseful_obj. logdet_and_chol(
  CONST ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
  CONST nchol: INTEGER):
DOUBLE;
VAR
  i, j, k: INTEGER;
  _h, s: DOUBLE;
  ain__i{nchol}, rchol__i{nchol}, rchol__k{nchol}: ARRAY_1D;
BEGIN
  RESULT:= 0;
  FOR i:=1 TO nchol DO BEGIN
    ain__i:= ain[i];
    rchol__i:= rchol[i];
    _h:= ain__i[i];
    FOR j:=1 TO i-1 DO BEGIN
      DECR( _h, SQR( rchol__i[j]));
    END;
    {$IFNDEF AD}
    IF _h<=0 THEN BEGIN
      RESULT:= QNAN;
      rchol[1][1]:= QNAN;
EXIT;
    END;
    {$ENDIF}{AD}
    _h:= sqrt(_h);
    INCR( RESULT, LN( _h)); 
    _h:= 1/_h;
    rchol__i[i]:= _h;
    FOR k:=i+1 TO nchol DO BEGIN
      rchol__k:= rchol[k];
      s:= 0;
      FOR j:=1 TO i-1 DO BEGIN
        INCR( s, rchol__i[j]*rchol__k[j]);
      END;
      s:= (ain__i[k]-s)*_h;
      rchol__k[i]:= s;
    END;
  END;
  
  RESULT:= 2*RESULT;
END;

FUNCTION D_Tuseful_obj. logdet_and_chol_neg(
  CONST neg_ain{nchol,nchol}, rchol{nchol,nchol}: ARRAY_2D;
  CONST nchol: INTEGER):
DOUBLE;
VAR
  i, j, k: INTEGER;
  _h, s: DOUBLE;
  neg_ain__i{nchol}, rchol__i{nchol}, rchol__k{nchol}: ARRAY_1D;
BEGIN
  RESULT:= 0;
  FOR i:=1 TO nchol DO BEGIN
    neg_ain__i:= neg_ain[i];
    rchol__i:= rchol[i];
    _h:= -neg_ain__i[i];
    FOR j:=1 TO i-1 DO BEGIN
      DECR( _h, SQR( rchol__i[j]));
    END;
    {$IFNDEF AD}
    IF _h<=0 THEN BEGIN
      RESULT:= QNAN;
      rchol[1][1]:= QNAN;
EXIT;
    END;
    {$ENDIF}{AD}
    INCR( RESULT, LN( _h)); 
    _h:= 1/sqrt(_h);
    rchol__i[i]:= _h;
    FOR k:=i+1 TO nchol DO BEGIN
      rchol__k:= rchol[k];
      s:= -neg_ain__i[k];
      FOR j:=1 TO i-1 DO BEGIN
        DECR( s, rchol__i[j]*rchol__k[j]);
      END;
      rchol__k[i]:= s*_h;
    END;
  END;
  
END;

PROCEDURE D_Tuseful_obj. backsolve_chol(
    CONST rchol{nchol,nchol}: ARRAY_2D;
    CONST target{nchol}, sol{nchol}: ARRAY_1D;
    CONST nchol: INTEGER);
VAR
  i, k: INTEGER;
  sum: DOUBLE;
  rchol__i{nchol}: ARRAY_1D;
BEGIN
  FOR i:= 1 TO nchol DO BEGIN
    rchol__i:= rchol[i];
    sum:= target[ i];
    FOR k:= i-1  DOWNTO 1 DO BEGIN
      DECR( sum, rchol__i[ k] * sol[ k]);
    END;
    sol[ i]:= sum * rchol__i[ i];
  END;
  FOR i:= nchol DOWNTO 1 DO BEGIN
    rchol__i:= rchol[i];
    sum:= sol[ i];
    FOR k:= i+1 TO nchol DO BEGIN
      DECR( sum, rchol[k][i]*sol[k]);
    END;
    sol[ i]:= sum * rchol__i[i];
  END;
END;

FUNCTION D_Tuseful_obj. quadform(
    CONST xqf{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER):
  DOUBLE;
VAR
  i, j: INTEGER;
  sumbo: DOUBLE;
  HQF__I{nqf}: ARRAY_1D;
BEGIN
  RESULT:= 0;
  FOR i:= 1 TO nqf DO BEGIN
    hqf__i:= hqf[i];
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf__i[j]*xqf[j]);
    END;
    INCR( RESULT, xqf[i]*sumbo);
  END;
END;
{$ENDIF}{AD}

PROCEDURE D_Tuseful_obj. quadform_b(
    CONST xqf{nqf}, xqf_b{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER;
    VAR   xqf_wt: DOUBLE);
VAR
  i, j: INTEGER;
  sumbo: DOUBLE;
  HQF__I{nqf}: ARRAY_1D;
BEGIN
  FOR i:= 1 TO nqf DO BEGIN
    hqf__i:= hqf[i];
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf__i[j]*xqf[j]);
    END;
    xqf_b[ i]:= 2*xqf_wt*sumbo;
  END;
END;

FUNCTION D_Tuseful_obj. quadform_d(
    CONST xqf{nqf}, xqf_dir{nqf}: ARRAY_1D;
    CONST hqf{nqf,nqf}: ARRAY_2D;
    CONST nqf: INTEGER;
    VAR   hxh: DOUBLE):
  DOUBLE;
VAR
  i, j: INTEGER;  
  sumbo: DOUBLE;
  HQF__I{nqf}: ARRAY_1D;
BEGIN
  hxh:= 0;
  RESULT:= 0;
  FOR i:= 1 TO nqf DO BEGIN
    hqf__i:= hqf[i];
    sumbo:= 0;
    FOR j:= 1 TO nqf DO BEGIN
      INCR( sumbo, hqf__i[j]*xqf[j]);
    END;
    INCR( hxh, sumbo*xqf[i]);
    INCR( RESULT, 2*xqf_dir[i]*sumbo);
  END;
END;
END.
