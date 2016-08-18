UNIT domin;
{$WARNINGS OFF}
{$HINTS OFF}
{ Based on Peter Spellucci's DOMIN quasi-Newton code, recast into OOP }
{ Sequence of ops:

  1. Instantiate a Tspelmin_obj specifying the number of parameters
  2. Specify the user functions via manually setting func_global or func_method etc.
  3. Set convergence tolerances in epsx, epsg, epsf; change any defaults
  4. Set starting values in xst (via XCOPY I guess)
  5. Call set_approx_hess to set an approximate Hessian in a
  6. Call prepare_to_minimize
  7. Either call minimize to just do it, or embed calls to do_one_iter in a loop,
     checking whether finished=TRUE afterwards. See DOMIN doc for interpretation of
     exit codes etc.
  7a. Just before step() is called in do_one_iter, the user hook
     call_before_step( SELF) is called.
  8. Can recall if necessary
  9. FREE it.
}


INTERFACE

USES Math, Useful; // for definitions of tfunc_global etc.

TYPE
  Tfunc_global = FUNCTION( CONST p: ARRAY_1D): DOUBLE;
  Tfunc_method = FUNCTION( CONST p: ARRAY_1D): DOUBLE OF OBJECT;
  TDfunc_global = PROCEDURE( CONST p, df: ARRAY_1D);
  TDfunc_method = PROCEDURE( CONST p, df: ARRAY_1D) OF OBJECT;
  TD2func_global = PROCEDURE( CONST p: ARRAY_1D; CONST d2f: ARRAY_2D);
  TD2func_method = PROCEDURE( CONST p: ARRAY_1D; CONST d2f: ARRAY_2D) OF OBJECT;

  Td_func_method = Tdfunc_method; // LHS is preferred spelling

  Tspelmin_obj = CLASS;
  Tspelmin_meth = PROCEDURE( CONST me: Tspelmin_obj) OF OBJECT;
  Tspelmin_new_it_meth = PROCEDURE( CONST me: Tspelmin_obj; CONST _x: ARRAY_1D; VAR _fx: DOUBLE; CONST _gradx, _a: ARRAY_1D) OF OBJECT;

  Tspelmin_obj = CLASS( Teasy_alloc_object)
    // This reproduces the declaration order in domincom
    x, d, gradx, last_eval_x: ARRAY_1D;
    funcval, funmul, fx, xnorm, dnorm, sig: DOUBLE;
    x0, d0, gradx0: ARRAY_1D;
    fx0, x0norm, d0norm, sig0: DOUBLE;
    difx: ARRAY_1D;
    ftest, dirder: DOUBLE;

    stepte,sigsm,sigla,alpha,beta,delta, theta,dskal,deldif: DOUBLE;
    epsx,epsg,epsf: DOUBLE;
    cold: BOOLEAN;
    n,icf,icsf,icgf,iup,inoup,ires,imod: INTEGER;
    a: ARRAY_2D;
    diaga, z, y: ARRAY_1D;
    tracea,traceb, acc8, prev_acc8, acc14: DOUBLE;
    niter, iterma: INTEGER;
    eta, thet2: DOUBLE;
    bfgste: INTEGER;
    xst,
    x1, v, c, // x1: step; v: do_one_iter; c: cholso
    xd, xst1, gradxs, gradx1: ARRAY_1D; // all: initia
    sdiag, rn1, w: ARRAY_1D; // update_Ok

    initialize_from_scratch,
    inside_step: BOOLEAN;
    // fx is output value

    sigmax: DOUBLE;

    f: Tfunc_method;
    gradf: Tdfunc_method;

    call_at_new_it: Tspelmin_new_it_meth;
    call_before_step: Tspelmin_meth;

    finished: BOOLEAN;

    mvb_inv_chol_col, mvb_targ{n}: ARRAY_1D;

    CONSTRUCTOR create( _n: INTEGER); VIRTUAL;
    PROCEDURE set_approx_hess(
      CONST _a, _chol_a: ARRAY_2D;
      CONST mulbo: DOUBLE=-1;
      CONST flip: BOOLEAN=FALSE); OVERLOAD;
    PROCEDURE set_approx_hess( CONST _a: ARRAY_2D); OVERLOAD;
    PROCEDURE set_approx_hess( CONST _a: ARRAY_1D); OVERLOAD;
    PROCEDURE step;
    PROCEDURE prepare_to_minimize;
    PROCEDURE minimize;
    PROCEDURE do_one_iter;
    PROCEDURE testx;
    FUNCTION vecnor( CONST x: ARRAY_1D): DOUBLE;
    FUNCTION skal1( CONST a, b: ARRAY_1D): DOUBLE;
    PROCEDURE numgrd( CONST xl, gradxl: ARRAY_1D);
    PROCEDURE initia;
    PROCEDURE refres( CONST niter1: INTEGER);
    PROCEDURE cholso( CONST a: ARRAY_2D; CONST b, x: ARRAY_1D);
    FUNCTION update_OK( CONST r: ARRAY_2D; CONST z, y: ARRAY_1D): BOOLEAN;

    // These 2 use funmul
    FUNCTION private_f( CONST p: ARRAY_1D): DOUBLE; INLINE;
    PROCEDURE private_gradf( CONST p, df: ARRAY_1D);
  END;

// Not sure why this is outside and cholso is inside...
PROCEDURE chol(
  CONST a: ARRAY_2D;
  CONST n: INTEGER;
  CONST r: ARRAY_2D;
  VAR ifail: INTEGER);

VAR
  epsmac, tolmac: DOUBLE; // set by INITIALIZATION

CONST
  def_sigla = 2048;
  def_beta = 2;
  def_alpha = 0.1;
  def_delta = 0.01;
  def_theta = 0.99;
  def_sigmax = 32; // MVB

IMPLEMENTATION

USES Maths32;

CONSTRUCTOR Tspelmin_obj. create( _n: INTEGER);
BEGIN
  INHERITED create;
  n:= _n;
  alloc_arrays( [@x, @d, @gradx, @last_eval_x, @x0, @d0, @gradx0, @difx, @diaga,
      @z, @y, @xst, @x1, @v, @c, @xd, @xst1, @gradxs, @gradx1, @sdiag, @rn1, @w,
      @mvb_inv_chol_col, @mvb_targ],
      [n], [1], SizeOf( DOUBLE));
  a:= alloc_array( [n,n], [1,1], SizeOf( DOUBLE)); // a[1][1]=0 so triggers initia()

  funmul:= 1;
  initialize_from_scratch:= TRUE;

  // Defaults
  iterma:= LMIN( 30*n, 1000);
  epsx:= power( epsmac, 2/3);
  epsg:= epsx;
  epsf:= epsmac*1000;
  eta:= SQRT( epsmac);
  sigsm:= epsx;

  sigmax:= def_sigmax; // MVB

  deldif:= power(epsmac,1/7)*0.25;

  xst[ 1]:= QNAN; // user must set this

  sigla:= def_sigla;
  beta:= def_beta;
  alpha:= def_alpha;
  delta:= def_delta;
  theta:= def_theta;

  //       icf=0 etc. are automatic
END;

FUNCTION Tspelmin_obj. private_f( CONST p: ARRAY_1D):
  DOUBLE;
BEGIN
  RESULT:= funmul * f( p);
END;

PROCEDURE Tspelmin_obj. private_gradf( CONST p, df: ARRAY_1D);
VAR
  i: INTEGER;
BEGIN
  gradf( p, df);
  IF funmul=-1 THEN
    negate( df[1], n)
  ELSE IF funmul<>1 THEN BEGIN
    FOR i:= 1 TO n DO
      df[i]:= df[i]*funmul;
  END;
END;

// end of domincom

// bfgsminimizer v030392 copyright p. spellucci

//     epsx = required precision  in x (relative)

{      call bfgs(cold)
c start may change control parameters
c param cold for bfgs means fresh start
c     output of short information:
c     it = stepnumber , f = function value, delx = change in x
c     ngrad = norm of gradient, (behaves nonmonotonic) ,
c     n(a)= norm of quasi-newton-matrix, approximately  norm of hessian
c     thet2 Powells parameter, << 1 means that f behaves strongly
c     nonconvex , this reduces the efficiency
c     sig = stepsize  x(new)=x(old)-sig*direction(d),
c     sig << 1 means, that we are far from the asymtotic (fast) phase
c     of the iteration.
c     dskal (scaling of d) . dskal notequal 1 means that correction d is
c     too large. may be due to bad update
c     using the internal scaling of d reduces the possibility of
c     failures due to overflow
c     n(d)=norm of  d, icf+ = number of f-evaluations for stepsize-
c     determination for the current step
c     should be 1 or 2 normally. a large icf+ means that
c     d is "bad" , that is the update is bad or x is far from the solution.
c     restart = 1 means a reinitialization of the quasi-newton-update
c     update = -1 means a suppression of the quasi-newton-update
c     that is f behaves strongly nonconvex
c
c     termination: bfgste = 0 , 1 normal termination
c               =2 directional derivative exremely small
c               as a rule this occurs with badly conditioned cases
c               where the desired accuracy in x and grad f cannot be
c               obtained
c               -2 iterma steps taken without satisfying termination
c               criteria
c               -1 extremely small stepsize after a restart
c               (condition number of hessian > 1/sigsm
c               -3 irrecoverable error in calling f or gradf
c               that is in an extremely small neighborhood of the current
c               x the user supplied function returns with an error
}

{c****************************************************************
c     determination of stepsize by an armijo-like test for
c     descent
c****************************************************************
c copyright = spellucci
      subroutine step
      include 'domincom.inc'
c********************************************************************
c   n = actual dimension
c   x = current point
c   d = current direction
c   gradx = gradient of f at x
c   x,d,gradx = input ( in common )
c   x0,gradx0 etc. information from previous step
c
c   xnorm,dnorm = euclidean length of x and d
c   stepte = 1 in case of success , =-1 otherwise
c   sig = computed stepsize
c   the routine assumes that sig=1 is asymptotically optimal
c   (otherwise one has to change initialization of sig)
c   sigsm = minimal stepsize allowed
c   sigla = maximal stepsize allowed
c   alpha = maximal reduction of stepsize per reduction-step
c   delta = the armijo-parameter
c   beta = max. growth of  xnorm allowed for  sig=1
c   theta = bound for cos(angle(d))
c           we try stepsizes larger than one, if this is exceeded.
c           in that case and d point (almost) in the same direction
c
c*********************************************************************
}

{*********************************************************************}

FUNCTION oor(
  CONST f: DOUBLE):
  BOOLEAN;
BEGIN
  RESULT:= isNaN( f) or isInfinite( f);
END;

{*********************************************************************}

PROCEDURE Tspelmin_obj. step;
VAR
  i: INTEGER;
  t, sigmin, fmin, cosphi, f1: DOUBLE;
  last_eval_here: BOOLEAN;
{***
       sigmin is the current best point, fmin the corrsponding fuction
       value (if we increase sig)
***}
BEGIN
  xnorm:= vecnor(x);
  dnorm:= vecnor(d);
  dskal:= 1;
  cosphi:= skal1(d,d0);
  t:= 1;
  FOR i:= 1 TO n DO
    IF abs(d[i]) > ( abs(x[i]) + 1) * (beta-1) THEN
      t:= min( t, (beta-1)*(abs(x[i])+1)/abs(d[i]));

  IF t<1 THEN
  BEGIN // rescale d
    dnorm:= t*dnorm;
    dirder:= t*dirder;
    cosphi:= cosphi*t;
    dskal:= t;
    FOR i:= 1 TO n DO
      d[i]:= d[i]*t;
  END;

  cosphi:= abs(cosphi)/(dnorm*d0norm);

  // d[] is now set, so...
  IF @call_before_step<>NIL THEN
    call_before_step( SELF);
  inside_step:= TRUE;

  // If f() gives NAN/INF, then reduce stepsize & try again
  last_eval_here:= FALSE;
  sig:= 1;
  REPEAT // 100 continue
    // New x. Check for descent

    // Next wrapping IF by MVB:
    IF sig<sigmax THEN BEGIN
      FOR i:= 1 TO n DO
        x1[i]:= x[i]-sig*d[i];
      last_eval_here:= TRUE;
      f1:= private_f(x1); // sig is also available to nosy user routines
      XCOPY( x1[1], last_eval_x[1], n);
    END;

    // First clause in next IF by MVB
    IF (sig>=sigmax) OR oor(f1) THEN BEGIN
      IF sig > 1 THEN BEGIN // do not further increase of sig
        sig:= sigmin;
        f1:= fmin;
        last_eval_here:= FALSE; // check it
        FOR i:= 1 TO n DO
          x1[i]:= x[i]-sig*d[i];
  BREAK; // goto 200
      END;

      sig:= sig*0.5;
      IF sig>=sigsm THEN
  CONTINUE // goto 100
      ELSE
      BEGIN
        stepte:= -1;
EXIT;
      END;
    END; // if oor
    ftest:= f1;

    // New function value
    IF sig > 1 THEN BEGIN
      IF f1 > fmin THEN BEGIN // f stops decreasing
        sig:= sigmin;
        f1:= fmin;
        last_eval_here:= FALSE; // check it
        FOR i:= 1 TO n DO
          x1[i]:= x[i]-sig*d[i];
  BREAK; // goto 200
      END
      ELSE BEGIN
        IF sig < sigla THEN BEGIN
          fmin:= f1;
          sigmin:= sig;
          sig:= min(sigla,sig+sig);
  CONTINUE // goto 100
        END
        ELSE
  BREAK; // goto 200
      END;
    END;

    IF fx - f1 > sig*delta*dirder THEN BEGIN
      // goldstein-armijo test satisfied
      IF (sig=1) AND (cosphi>=theta) AND (sig0>=1) THEN BEGIN
        // try sig . 1
        fmin:= f1;
        sigmin:= sig;
        IF fx-f1 < sig*dirder THEN
          sig:= min(sigla, max(sig+sig,dirder*SQR(sig)/(2*(f1-fx+sig*dirder))))
        ELSE
          sig:= min(sigla,sig+sig);
  CONTINUE; // goto 100
      END;
  BREAK; // goto 200
    END
    ELSE BEGIN
      sig:= max( alpha*sig,
                 min( dirder*SQR( sig)/(2*(f1-fx+sig*dirder)),
                      0.5*sig));
      IF sig < sigsm THEN BEGIN
        stepte:= -1;
EXIT;
      END
      ELSE
  CONTINUE; // 100

    END;
  UNTIL FALSE;

// 200 continue
// new x accepted

  fx0:= fx;
  fx:= f1;
  stepte:= 1;
  x0norm:= xnorm;
  d0norm:= dnorm;
  sig0:= sig;
  XCOPY( gradx[1], gradx0[1], n);
  XCOPY( x[1], x0[1], n);
  XCOPY( d[1], d0[1], n);
  XCOPY( x1[1], x[1], n);

  FOR i:= 1 TO n DO
    difx[i]:= x[i]-x0[i];

// think I don't need to recall f here? or set up params the same?
  // check it
  IF NOT last_eval_here THEN BEGIN
    last_eval_here:= TRUE;
    FOR i:= 1 TO n DO BEGIN
      IF last_eval_x[ i]<>x[ i] THEN BEGIN
        last_eval_here:= FALSE;
    BREAK;
      END;
    END;

    IF NOT last_eval_here THEN
      private_f( x);
  END;

  IF @gradf<>NIL THEN
    private_gradf(x,gradx)
  ELSE
    numgrd(x,gradx);

  xnorm:= vecnor(x);
  IF oor( gradx[1]) THEN // panic; f can be evaluated, but grad(f) not
    stepte:= -2;
END;

{*******************************************************************
c   scalar product of two vectors or parts of vectors
c*******************************************************************
c copyright:= spellucci
}
//    double precision function skal1(a,b)
FUNCTION Tspelmin_obj. skal1(
  CONST a, b: ARRAY_1D):
DOUBLE;
VAR
  k: INTEGER;
BEGIN
  RESULT:= 0;
  FOR k:= 1 TO n DO
    INCR( RESULT, a[k]*b[k]);
END;

{************************************************************}

PROCEDURE Tspelmin_obj. set_approx_hess(
  CONST _a, _chol_a: ARRAY_2D;
  CONST mulbo: DOUBLE = -1;
  CONST flip: BOOLEAN = FALSE);
VAR
  i: INTEGER;
BEGIN
  tracea:= 0;
  FOR i:= 1 TO n DO BEGIN
    diaga[ i]:= mulbo * _a[i][i];
    XCOPY( _chol_a[i][1], a[i][1], n);
    IF flip THEN BEGIN // diag of chol is stored as 1/itself...
      a[i][i]:= 1/_chol_a[i][i];
    END;
    INCR( tracea, diaga[ i]);
  END;
  // traceb:= SQR( n) / tracea; ? too approx ?
  // must invert
  traceb:= 0;
  FOR i:= 1 TO n DO BEGIN
    zero( mvb_targ[1], n);
    mvb_targ[ i]:= 1;
    cholso( _chol_a, mvb_inv_chol_col, mvb_targ);
    INCR( traceb, mvb_inv_chol_col[ i]);
  END;
END;

{************************************************************}

PROCEDURE Tspelmin_obj. set_approx_hess(
  CONST _a: ARRAY_2D);
VAR
  i: INTEGER;
BEGIN
  FOR i:= 1 TO n DO BEGIN // not just single XCOPY in case of dim mismatch
    XCOPY( _a[i][1], a[i][1], n);
  END;
  tracea:= 0;
  FOR i:= 1 TO n DO BEGIN
    diaga[ i]:= a[i][i];
    INCR( tracea, diaga[ i]);
  END;
  // traceb:= SQR( n) / tracea; ? too approx ?
  // must invert
  traceb:= 0;
  chol( a, n, a, i);
  FOR i:= 1 TO n DO BEGIN
    zero( mvb_targ[1], n);
    mvb_targ[ i]:= 1;
    cholso( a, mvb_inv_chol_col, mvb_targ);
    INCR( traceb, mvb_inv_chol_col[ i]);
  END;
END;

{************************************************************}

PROCEDURE Tspelmin_obj. set_approx_hess(
  CONST _a: ARRAY_1D);
BEGIN
  XCOPY( _a[1], a[1][1], n*n);
  set_approx_hess( a);
END;

{************************************************************}

PROCEDURE Tspelmin_obj. prepare_to_minimize;
VAR
  i: INTEGER;
BEGIN
  icsf:= 0;
  if initialize_from_scratch OR (a[1][1]<=0) then
  BEGIN
    XCOPY( xst[1], x[1], n);
    XCOPY( x[1], x0[1], n);
    FOR i:= 1 TO n DO
      difx[i]:= 1+abs(x[i]); // to avoid termination in testx in step one
    xnorm:= vecnor(x);
    IF a[1][1]<=0 THEN // signal!
      initia(); // initializes the quasi-newton-matrix a
  END;

  sig0:= 0;
  d0norm:= 1; // ?? no stepsize larger than 1 in the first step
  niter:= 0;
  thet2:= 1;
  bfgste:= 0;
  zero( d0[1], n);

  inside_step:= FALSE;

  IF @f=NIL THEN
    fx:= QNAN
  ELSE
    fx:= private_f(x);
  IF oor( fx) THEN
  BEGIN
    bfgste:= -3;
EXIT;
  END;

  IF @gradf<>NIL THEN
    private_gradf(x,gradx)
  ELSE
    numgrd(x,gradx);

  IF oor( gradx[1]) THEN
  BEGIN
    bfgste:= -3;
EXIT;
  END;
END;

{******************************************************}

PROCEDURE Tspelmin_obj. minimize;
BEGIN
  REPEAT
    do_one_iter();
  UNTIL finished;
  funcval:= fx / funmul;
END; // too easy!

{******************************************************
     main iteration loop starts here
******************************************************}

{c copyright = spellucci
      include 'domincom.inc'
      integer cfold,cgfold,icsf,i,j,ifail
      double precision v(nx),s1,s2,s3,s4,s5,difxin,wi,vecnor,
     f     skal1,den1
      double precision dif1,dif2,h
      logical resta,err
}

PROCEDURE Tspelmin_obj. do_one_iter;
VAR
  cfold, cgfold, i, j, ifail: INTEGER;
  s1,s2,s3,s4,s5,difxin,wi,den1,dif1,dif2,h: DOUBLE;
  resta: BOOLEAN;

BEGIN
  // REPEAT // main iteration loop: 100
  finished:= TRUE; // in case of an early bath
  INCR( niter);
  IF ( niter>iterma ) THEN
  BEGIN
    DECR( niter);
    bfgste:= -2;
EXIT;
  END;

  if @call_at_new_it<>NIL THEN
    call_at_new_it( SELF, @x[1], fx, @gradx[1], @a[1]);

  prev_acc8:= acc8;
  acc8:= 0;
  acc14:= 0;

  s1:= diaga[1];
  s2:= a[1][1];
  FOR i:= 2 TO n DO
  BEGIN
    INCR( s1, diaga[i]);
    s2:= MIN( s2,a[i][i]);
  END;

// s1 = spur (a), s2=minimal element on the diagonal of cholesky factor of a
  IF niter > 1 THEN
  BEGIN
      IF ((tracea*epsmac>1) AND (traceb*epsmac>1))
        OR (s1*epsmac > SQR( s2)) OR (prev_acc8 > 1/eta) THEN
      BEGIN
        refres( niter);
      if bfgste=-3 THEN
EXIT;
      resta:= TRUE
    END ELSE
      resta:= FALSE;
  END;

  testx();
  cfold:= icf;
  cgfold:= icgf;
// check accuracy
  IF bfgste=1 THEN
EXIT;

  REPEAT // 200 continue
    cholso(a,gradx,d);
    // d = quasi-newton direction (uphill)
    dnorm:= vecnor(d);
    IF dnorm=0 THEN
    BEGIN
      bfgste:= 0;
EXIT;
    END;

    dirder:= skal1(d,gradx);
    IF delta*dirder <= epsmac*(abs(fx)+1)*100 THEN
    BEGIN
      bfgste:= 2;
EXIT;
    END;

    step();
    inside_step:= FALSE;

    i:= icf-cfold;
    IF @gradf=NIL THEN
      i:= i-6*n*(icgf-cgfold);

    IF stepte <> 1 THEN
    BEGIN
      IF resta then
      BEGIN
        bfgste:= -1;
EXIT;
      END
      ELSE BEGIN
        refres(niter);
        IF bfgste=-3 THEN
EXIT;
        resta:= TRUE;
  CONTINUE; // 200
      END;
    END;
  UNTIL TRUE;

  IF fx0-fx > epsf*(abs(fx)+epsf) THEN
    icsf:= 0
  ELSE
    INCR( icsf);

  IF icsf=4 THEN
  BEGIN
    bfgste:= 3;
EXIT;
  END;

  IF vecnor(difx)=0 THEN
  BEGIN
    bfgste:= 4;
EXIT;
  END;

(*********************************************
   compute update vectors z and y
*********************************************)

  thet2:= 1;
  s1:= 0; s2:= 0; s3:= 0;
  den1:= skal1(d,gradx0)/dskal;
  h:= 1/sqrt(den1);
  FOR i:= 1 TO n DO
  BEGIN
    y[i]:= gradx0[i]*h;
    dif1:= difx[i];
    dif2:= gradx[i]-gradx0[i];
    INCR( s1, SQR( dif1));
    INCR( s2, SQR( dif2));
    INCR( s3, dif1*dif2);
    z[i]:= dif2;
  END;

  IF s3 < eta*s2 THEN
  BEGIN
{**********************************************
   bfgs-updating impossible from this information
   f not uniformly convex of course
**********************************************}
    s4:= SQR(sig*dskal)*den1;
    // s(k)(transpose)*a(k)*s(k) in the usual notation
    IF s3< 0.2*s4 THEN
      thet2:= 0.8*s4/(s4-s3);
    IF thet2<>1 THEN
      INCR( imod);
    s3:= 0.2*s4;
    h:= (1-thet2)*sig*dskal;

    // powell's modification
    // h*gradx0 = a(k)*s(k)*(1-thet2)
    FOR i:= 1 TO n DO
      z[i]:= thet2*z[i]+h*gradx0[i];
  END; // if s3<eta*s2

  s3:=1/sqrt(s3);
  FOR i:= 1 TO n DO
    z[i]:= z[i]*s3;
  acc14:= 1;
  cholso(a,z,v);

  // v = b(k)*y(k)/sqrt(y's) in the usual notation
  s4:= 0;
  s5:= 0;
  FOR i:=1 TO n DO
  BEGIN
    difxin:= difx[i]*s3;
    wi:=difxin+v[i];
    // w=(sig(i)+(b*y)(i))/sqrt(y's)
    INCR( s5, z[i]*wi);
    INCR( s4, v[i]*difxin);
  END;

  // small n (direct chol) not copied here
  // Update cholesky
  FOR i:= 1 TO n DO
  BEGIN
    diaga[i]:= a[i][i];
    FOR j:= 1 TO i-1 DO
      a[i][j]:= a[j][i];
  END;

  IF NOT update_OK(a,z,y) THEN
  BEGIN
    INCR( inoup);
    acc14:= -1;
    FOR i:=1 TO n DO
    BEGIN
      a[i][i]:= diaga[i];
      FOR j:=1 TO i-1 DO
        a[j][i]:=a[i][j];
    END;
  END
  ELSE
    INCR( iup);

{****************************************************
   next step
****************************************************}
  IF acc14=1 THEN
  BEGIN
    //recursive computation of trace(a) and trace(b)
    // it is stopped if one trace becomes negative, indicating unreliability
    IF tracea>0 THEN
      INCR( tracea, SQR( vecnor(z))-SQR( vecnor(y)));
    IF traceb>0 THEN
      DECR( traceb, 2*s4+s1*SQR( s3)*s5);
  END;
  // UNTIL FALSE;

  finished:= FALSE;
END;

{*******************************************************************
   subprograms for computation of an updated cholesky-
   decomposition, method of stewart
*******************************************************************}

PROCEDURE leftel(
  CONST a: ARRAY_2D;
  CONST b, y: ARRAY_1D;
  VAR yl: DOUBLE;
  CONST n: INTEGER);
VAR
  i, j: INTEGER;
  h: DOUBLE;
//    double precision a(nx,nx),b(nx),y(nx),yl,h
{   leftel assumes that the cholesky-factor of a
     a=r(transpose)*r is stored in the upper half of a.
     b is a right hand side. leftel solves
         y(transpose)*r = b(transpose)
     yl=norm(y)**2
}
BEGIN
  yl:= 0;
  FOR i:= 1 TO n DO
  BEGIN
    h:= b[i];
    FOR j:=1 TO i-1 DO
      DECR( h, a[j][i]*y[j]);
    h:= h/a[i][i];
    y[i]:= h;
    INCR( yl, SQR( h));
  END;
END;

{**********************************************************}

FUNCTION dsq1(
      a, b: DOUBLE):
  DOUBLE; // computes sqrt(a**2+b**2) numerically safe
BEGIN
  a:= abs(a);
  b:= abs(b);
  IF a>b THEN
    dsq1:= a*sqrt(1+SQR(b/a))
  ELSE
  BEGIN
    IF b>a THEN
      dsq1:= b*sqrt(1+SQR(a/b))
    ELSE
      dsq1:= a*sqrt(2);
  END;
END;

{*******************************************************************}

// subroutine update(r,z,y,n,ifail)
FUNCTION Tspelmin_obj. update_OK(
  CONST r: ARRAY_2D;
  CONST z, y: ARRAY_1D):
BOOLEAN;

VAR
  yl, zl, wl, wn1, ai, bi, h: DOUBLE;
  i, j, i1: INTEGER;
{    integer i,j,n,i1
      double precision r(nx,nx),z(nx),y(nx)
      double precision sdiag(nx),rn1(nx),w(nx)
      double precision yl,zl,wl,wn1,ai,bi,h,dsq1
c   update computes the upper triangular cholesky-factor
c   r1 of
c             r(transpose)*r+z*z(transpose)-y*y(transpose)
c   and restores it in r. the strict lower triangle of r re-
c   mains unchanged.
c   RESULT=FALSE if the decomposition does'nt exist, RESULT=TRUE on dimension
c   error, RESULT=0 on success.
}
BEGIN
  RESULT:= TRUE;
  // save subdiagonal
  FOR i:=1 TO n-1 DO
  BEGIN
    sdiag[i]:= r[i+1][i];
    r[i+1][i]:= 0;
  END;

  //   step one: include z*z(transpose)
  zl:= 0;
  FOR i:=1 TO n DO
    INCR( zl, SQR( z[ i]));

  IF zl<>0 THEN
  BEGIN
    // solve w(transpose)*r=z(transpose)
    leftel(r,z,w,wl,n);
    wl:= sqrt(1+wl);
    // u(2)*u(3)*...*u(n)*w = ( norm(w),0,..,0)(transpose)
    // u(i) rotations
    FOR i:= n DOWNTO 2 DO
      IF w[i]<>0 THEN
      BEGIN
        i1:= i-1;
        ai:= w[i1];
        bi:= w[i];
        w[i1]:= dsq1(ai,bi);
        ai:= ai/w[i1];
        bi:= -bi/w[i1];
        r[i][i1]:= bi*r[i1][i1];
        r[i1][i1]:= ai*r[i1][i1];
        FOR j:= i TO n DO
        BEGIN
          h:= ai*r[i1][j] - bi*r[i][j];
          r[i][j]:= bi*r[i1][j] + ai*r[i][j];
          r[i1][j]:= h;
        END;
      END;

    // r=d*r, d=diag(wl,1,...,1), r now hessenberg
    FOR i:= 1 TO n DO
      r[1][i]:= r[1][i]*wl;

    // r=u(n-1)*...*u(1)*r now upper triangular,
    // u(i) givens-rotations
    FOR i:= 1 TO n-1 DO
    BEGIN
      i1:= i+1;
      ai:= r[i][i];
      bi:= -r[i1][i];
      h:= dsq1(ai,bi);
      IF h<>0 THEN
      BEGIN
        ai:= ai/h;
        bi:= bi/h;
        r[i][i]:= h;
        r[i1][i]:= 0;
        FOR j:=i+1 TO n DO
        BEGIN
          h:= ai*r[i][j] - bi*r[i1][j];
          r[i1][j]:= bi*r[i][j] + ai*r[i1][j];
          r[i][j]:= h;
        END;
      END;
    END;
  END; // if zl<> 0

  // step two : include -y*y(transpose)
  yl:= 0;
  FOR i:=1 TO n DO
    INCR( yl, SQR( y[ i]));

  IF yl<>0 THEN
  BEGIN
    leftel(r,y,w,wl,n);
    IF wl>=1 THEN
      RESULT:= FALSE
    ELSE BEGIN
      wl:= sqrt(1-wl);
      wn1:= wl;
{******************************************************
      ( r(new) ,0 )              (  r , w )
      (-----------) = u(1)*...u(n)*(-----------)
      (y(transp),1)              ((0,..,0),wl)
 ******************************************************}
      FOR i:= n DOWNTO 1 DO
      BEGIN
        ai:= wn1;
        bi:= w[i];
        wn1:= dsq1(ai,bi);
        IF wn1<>0 THEN
        BEGIN
          ai:= ai/wn1;
          bi:= bi/wn1;
          rn1[i]:= bi*r[i][i];
          r[i][i]:= ai*r[i][i];
          FOR j:=i+1 TO n DO
          BEGIN
            h:= ai*r[i][j] - bi*rn1[j];
            rn1[j]:= bi*r[i][j] + ai*rn1[j];
            r[i][j]:= h;
          END;
        END; // if wn1<> 0
      END; // for i:= n downto 1
    END; // wl<1
  END; // yl<>0

  // restore subdiagonal
  FOR i:= 1 TO n-1 DO
    r[i+1][i]:= sdiag[i];
END;

{*******************************************************************
     cholesky decomposition of a symmetric positive matrix a
     the strict lower triangle remains unaffected
     the upper triangle including the diagonal holds the cholesky-
     factor. initially the strict upper triangle may be undefined
 *******************************************************************}
//    subroutine chol(a,n,r,ifail)
PROCEDURE chol(
  CONST a: ARRAY_2D;
  CONST n: INTEGER;
  CONST r: ARRAY_2D;
  VAR ifail: INTEGER);
VAR
  i, j, k: INTEGER;
  h, s: DOUBLE;
{
c copyright = spellucci
      implicit none
      include 'dominpar.inc'
      integer i,j,k,ifail,n
      double precision a(nx,nx),r(nx,nx),h,s
c   computes the cholesky-factor r of a=r(transp)*r
c   and stores it in the upper triangle of r
c   a and r may be identical. the strict lower triangle
c   of a remains unchanged anyway.
c   ifail .ne. 0 if the decomposition does'nt exist,
c   =0 otherwise
}
BEGIN
  ifail:= 0;
  FOR i:=1 TO n DO
  BEGIN
    h:= a[i][i];
    FOR j:=1 TO i-1 DO
      DECR( h, SQR( r[j][i]));

    IF h<=0 THEN
    BEGIN
      ifail:= 1;
EXIT;
    END;

    h:= sqrt(h);
    r[i][i]:= h;
    h:= 1/h;
    FOR k:=i+1 TO n DO
    BEGIN
      s:= 0;
      FOR j:=1 TO i-1 DO
        INCR( s, r[j][i]*r[j][k]);
      s:= (a[k][i]-s)*h;
      r[i][k]:= s;
    END;
  END;
END;

{ *******************************************************************}

// subroutine cholso(a,n,b,x)
PROCEDURE Tspelmin_obj. cholso(
  CONST a: ARRAY_2D;
  CONST b, x: ARRAY_1D);
VAR
  i, j: INTEGER;
  s: DOUBLE;
{
c copyright = spellucci
  implicit none
  include 'dominpar.inc'
  integer i,j,n
  double precision a(nx,nx),b(nx),c(nx),x(nx)
  double precision s
c   solves the linear system a*x=b, a symmetric positive definite
c   it is assumed that the cholesky-factor r of
c   a = r(transpose)*r
c   is stored in the upper triangle of a by chol.
}
BEGIN
  FOR i:=1 TO n DO
  BEGIN
    s:= 0;
    FOR j:=1 TO i-1 DO
      INCR( s, a[j][i]*c[j]);
    c[i]:= (b[i]-s)/a[i][i];
  END;

  FOR i:=n DOWNTO 1 DO
  BEGIN
    s:= 0;
    FOR j:=i+1 TO n DO
      INCR( s, a[i][j]*x[j]);
    x[i]:= (c[i]-s)/a[i][i];
  END;
END;

{*******************************************************************
   initia is used for initializing the quasi newton-update
*******************************************************************}

PROCEDURE Tspelmin_obj. initia;
VAR
  i, j: INTEGER;
  gn, sqrt_gn: DOUBLE;
BEGIN
  FOR i:=1 TO n DO
  BEGIN // xst1 should be in the range of definiton of gradf
    xst1[i]:= x[i]*(1+epsx)+sign( SQR( epsx), x[i]);
    xd[i]:= x[i]-xst1[i];
  END;

  private_f( x); // MVB: force f before df
  IF @gradf<>NIL THEN
    private_gradf(x,gradxs)
  ELSE
    numgrd(x,gradxs);
  IF oor( gradxs[1]) THEN
  BEGIN
    bfgste:= -3;
EXIT;
  END;

  gn:= vecnor(gradxs);
  if niter=0 THEN
    epsg:= epsg*(gn+epsg);
  private_f( xst1); // MVB
  if @gradf<>NIL THEN
    private_gradf(xst1,gradx1)
  ELSE
    numgrd(xst1,gradx1);
  IF oor( gradx1[1]) THEN
  BEGIN
    bfgste:= -3;
EXIT;
  END;

  FOR i:= 1 TO n DO
    DECR( gradxs[i], gradx1[i]);

  gn:= vecnor(gradxs);
 gn:= ( gn/vecnor(xd) ) / n; // I think this is correct precedence

  IF gn < sqrt(epsmac) THEN
    gn:= 1;
{ gn should be an estimate of the order of magnitude of the hessian
 in case of a very small gn the computation of gn itself is expected
 to be unreliable }

  sqrt_gn:= SQRT( gn);
  zero( a[1][1], n*n);
  FOR i:= 1 TO n DO BEGIN
    a[i][i]:= sqrt_gn;
    diaga[i]:= gn;
  END;

  tracea:= n*gn;
  traceb:= n/gn;
END;

{*******************************************************************
     refres is used on resta in bfgs
     resta is done only on occasion of a too small stepsize
     sig .lt. sigsm
 *******************************************************************}

PROCEDURE Tspelmin_obj. refres(
  CONST niter1: INTEGER);
BEGIN
  INCR( ires);
  initia();
// restart with scaled unit matrix
END;

{*******************************************************************
     testx checks for sufficient accuracy
 *******************************************************************}

PROCEDURE Tspelmin_obj. testx;
VAR
  xsatis, gsatis: BOOLEAN;
  i: INTEGER;
  an, sx, sg, damin: DOUBLE;
BEGIN
  an:= 0;
  sx:= vecnor(difx);
  sg:= vecnor(gradx);
  damin:= a[1][1];
  FOR i:= 1 TO n DO
  BEGIN
    INCR( an, diaga[i]);
    damin:= min( damin,a[i][i]);
  END;

  IF (tracea>0) AND (traceb>0) THEN
    acc8:= tracea*traceb/SQR( n)
  ELSE
    acc8:= an/SQR( damin);

  xsatis:= sx <= epsx*(xnorm+epsx);
  gsatis:= sg <= max( epsg, epsmac*acc8);
  IF xsatis AND gsatis THEN
    bfgste:= 1;
END;

{*******************************************************************}

FUNCTION Tspelmin_obj. vecnor(
  CONST x: ARRAY_1D):
  DOUBLE;
VAR
  i: INTEGER;
  xm, h: DOUBLE;
BEGIN
  RESULT:= 0;
  IF n<=0 THEN
EXIT;

  xm:= abs(x[1]);
  FOR i:=2 TO n DO
    xm:= max(xm,abs(x[i]));

  IF xm=0 THEN
EXIT;

  h:= 0;
  FOR i:=1 TO n DO
    INCR( h, SQR(x[i]/xm));
  RESULT:= xm*sqrt(h);
END;

{***************************************************************}

PROCEDURE Tspelmin_obj. numgrd(
  CONST xl, gradxl: ARRAY_1D);
VAR
  fxl: ARRAY[1..6] OF DOUBLE;
  sd1, sd2, sd3, xincr, zz, d1, d2, d3: DOUBLE;
  i: INTEGER;
{****************************************************
     high precision numerical differentiation
     by sixth order extrapolation
****************************************************}
BEGIN
  FOR i:=1 TO n DO
  BEGIN
    zz:= xl[i];
    xincr:= deldif*(abs(xl[i])+1);
    xl[i]:= zz-xincr;
    fxl[1]:= private_f(xl);
    IF oor( fxl[1]) THEN
EXIT;
    xl[i]:= zz+xincr;
    fxl[2]:= private_f(xl);
    IF oor( fxl[2]) THEN
EXIT;
    xincr:= xincr+xincr;
    d1:= xincr;
    xl[i]:= zz-xincr;
    fxl[3]:= private_f(xl);
    IF oor( fxl[3]) THEN
EXIT;
    xl[i]:= zz+xincr;
    fxl[ 4]:= private_f(xl);
    IF oor( fxl[ 4]) THEN
EXIT;
    xincr:= xincr+xincr;
    d2:= xincr;
    xl[i]:= zz-xincr;
    fxl[5]:= private_f(xl);
    IF oor( fxl[5]) THEN
EXIT;
    xl[i]:= zz+xincr;
    fxl[ 6]:= private_f(xl);
    IF oor( fxl[6]) THEN
EXIT;
    xl[i]:= zz;
    d3:= xincr+xincr;
    sd1:= (fxl[2]-fxl[1])/d1;
    sd2:= (fxl[4]-fxl[3])/d2;
    sd3:= (fxl[6]-fxl[5])/d3;
    sd3:= sd2-sd3;
    sd2:= sd1-sd2;
    sd3:= sd2-sd3;
    gradxl[i]:= sd1+0.4*sd2+sd3/45;
  END;
  INCR( icgf);
END;

{***************************************************************}
{***************************************************************}

VAR
  term, tol1: DOUBLE;

INITIALIZATION
// Set epsmac & tolmac

  epsmac:= power( 2, -20);
  term:= 1+epsmac;
  WHILE term<>1 DO
  BEGIN
    epsmac:= epsmac / 2;
    term:= 1+epsmac;
  END;
  epsmac:= epsmac+epsmac;
  tolmac:= epsmac;
  WHILE tolmac<>0 DO
  BEGIN
    tol1:= tolmac;
    tolmac:= tolmac/16;
  END;

  tolmac:= tol1;

END.
{$WARNINGS ON}
{$HINTS ON}

