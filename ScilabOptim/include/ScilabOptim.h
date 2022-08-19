// ----------------------------------------------------------------------------
// ScilabOptim.h
// ----------------------------------------------------------------------------
// Port of the ScilabOptim module of Scilab into a stand-alone C callable 
// dynamic library allowing the use of the optimisers in other code projects.
// 
// Ported by Paavo Jumppanen, year 2022
// ----------------------------------------------------------------------------


#include <R.h>


// begin extern "C"
#ifdef __cplusplus
extern "C" {
#endif


// ----------------------------------------------------------------------------
// Message callback function type called when ScilabOptim prints text output
// ----------------------------------------------------------------------------
typedef void (*messageCallback)(const char* pMessage);

// ----------------------------------------------------------------------------

void registerMessageCallback(messageCallback pMessageCallback);


/*
minimization of a regular function without constraints

vs. marshal, inria, 1987
Copyright INRIA

direction of descent calculated by a quasi-newton method
wolfe type linear search

simul: entry point to the simulation module (see modulopt i standards)
n1qn1 always calls simul with indic = 4; the modulus of
simulation must be presented in the subroutine form simul
(n,x, f, g, izs, rzs, dzs) and be declared as external in the
program calling n1qn1.

  n (e):        number of variables on which f depends.
  x (e-s):      n-dimensional vector; in input the initial point;
                output: end point computed by n1qn1.
  f (e-s):      scalar; in input value of f in x (initial), in output
                value of f in x (final).
  g (e-s):      n-dimensional vector: input value of the gradient in x
                (initial), output value of the gradient in x (final).
  var (e):      strictly positive vector of dimension n. amplitude of the
                desired modification at the first iteration on x(i).
                value is 10% of the difference (in absolute value) with the
                optimal x(i) coordinate
  eps (e-s):    in scalar input defines the precision of the stop test.
                the program considers that convergence is obtained when it
                is impossible to decrease f by assigning to at least one coordinate
                x(i) a variation greater than eps*var(i).
                in output, eps contains the square of the norm of the gradient in x (final).
  mode (e):     defines the initial approximation of the hessian
                 =1 n1qn1 l initializes itself
                 =2 the hessian is provided in zm in compressed form (zm
                    contains the columns of the lower part of the Hessian)
  niter (e-s):  input maximum number of iterations: output number
                of iterations actually performed.
  nsim (e-s):   input maximum number of calls to simul (i.e.
                with index = 4). output the number of such calls actually made.
  iprint (e):   checks for print messages:
                 0   nothing is printed
                 = 1 initial and final prints
                 = 2 one print per iteration (number of iterations,
                     number of calls a simul, current value of f).
                 >=3 additional research information
                     linear; very useful for detecting errors in the gradient.
  lp (e):        the number of the output channel, i.e. the impressions
                 commands by iprint are done by write(lp, format).
  zm:            working memory for n1qn1 of dimension n*(n+13)/2.
                 izs, rzs, dzs memories reserved for the simulator (see doc)
*/

typedef void (*simul_n1qn1_t)(int* n, double* x, double* f, double* g, int* izs, float* rzs, double* dzs);

void F77_NAME(n1qn1)(simul_n1qn1_t simul, 
                     int* n, 
                     double* x,
                     double* f,
                     double* g,
                     double* var,
                     double* eps,
                     int* mode,
                     int* niter,
                     int* nsim,
                     int* iprint,
                     int* lp,
                     double* zm,
                     int* izs,
                     float* rzs,
                     double* dzs);



/*
Unconstrained minimization by an algorithm of quasi-Newton with limited memory.

Origin
  Version 1.0 of n1qn2 (Modulopt, INRIA), September 1988.

Comments
  This code is in principle intended for large problems,
  large n, but also suitable for any n. The method
  used is of the quasi-Newton type (BFGS) with variable size,
  which allows maximum use of the declared memory available.
  nible. It is estimated that the more memory used, the more
  rapid will be the decrease in criterion f.

Called subroutines
  n1qn2:    routine-hat which structures the memory declared available
            nible and calls n1qn2a,
  n1qn2a:   actual optimizer,
  strang:   descent direction calculation routine,
  nlis0:    linear search routine.

On his side, the user must provide:
  1) a routine that calls the n1qn2 optimization module,
  2) a simulation routine, called simul by n1qn2, which
     calculates the value of f and its gradient at a given point,
  3) a routine, called prosca by n1qn2, which realizes the product
     scalar of two vectors, this scalar product must be
     the one used to calculate the gradient of f in simul.

Call list
  subroutine n1qn2(simul,prosca,n,x,f,g,dxmin,df1,epsg,iprint,io,
                   mode,niter,nsim,dz,ndz,izs,rzs,dzs)

  In the description of arguments that follows, (e) means that
  the argument must be initialized before calling n1qn2, (s)
  means that the argument is a variable with no meaning
  only in output and (es) = (e)+(s). Arguments of type (s) and (es)
  are in general modified by n1qn2 and therefore cannot be
  constants.

  In the description of arguments that follows, (e) means that
  the argument must be initialized before calling n1qn2, (s)
  means that the argument is a variable with no meaning
  only in output and (es) = (e)+(s). Arguments of type (s) and (es)
  are in general modified by n1qn2 and therefore cannot be
  constants.

  simul:      Call name of the simulation subroutine that
              which calculates the value of f and its gradient g
              at the current iteration. This module should look like
              follows:

                simul subroutine (indic,n,x,f,g,izs,rzs,dzs).

              The name of the subroutine must be declared external
              in the calling module n1qn2. The arguments n, x, f,
              g, izs, rzs and dzs have the same meaning as below
              below. N1qn2 calls simul either with indic=1, in
              this case the simulator will do what it wants but will not change
              will not manage the value of the arguments, or with indic=4, in
              case the simulator will calculate both f and g.

  prosca:     Call name of the subroutine performing the product
              scalar of two vectors u and v. This module must
              presented in the form:
            
                subroutine prosca (n,u,v,ps,izs,rzs,dzs).

              The name of the subroutine must be declared external
              in the calling module n1qn2. The arguments n, izs,
              rzs and dzs have the same meaning as below.
              The arguments u, v and ps are vectors of dimension
              n of the double precision type. ps give the product
              scalar of u and v.

  n(e):       Scalar of type integer. Gives the dimension n of the
              variable x.

  x(es):      n-dimensional vector of the double precision type. In
              input it is necessary to provide the value of the initial 
              point, in output, this is the end point calculated by n1qn2.

  f(es):      Double precision scalar. As input, it is the
              value of f in x (initial), value that we will obtain
              by calling the simulator simul before calling n1qn2.
              Output is the value of f at x (final).

  g(es):      n-dimensional vector of the double precision type.
              As input, it is necessary to provide the value of the gradient of f
              in x (initial), value that we will obtain by calling
              the simulator simul before calling n1qn2. Out in
              mode 1, it is the value of the gradient of f in x (final).

  dxmin(e):   Double precision scalar, strictly positive.
              This argument defines the resolution on x in norm
              l-infinity: two points whose distance in norm l-
              infini is greater than dxmin will be considered as
              not distinguishable by the linear search routine.

  df1(e):     Double precision scalar, strictly positive.
              This argument gives an estimate of the decrease
              expected for f during the first iteration.

  epsg(es):   Double precision scalar, strictly positive
              and strictly less than 1. Its input value,
              determines the stopping test which relates to the norm
              (prosca) of the gradient. The minimizer considers that the
              convergence is reached in x(k) and stops in mode 1
              if E(k) := |g(k)|/|g(1)| < epsg, where g(1) and g(k) are
              the gradients at the entry point and at iteration k,
              respectively. At output, epsg = E(k).

  iprint(e):  Scalar of type integer which controls the outputs.

               <0:  Nothing is printed and n1qn2 calls the simulator
                    with indic=1 every (-iprint) iterations.

               =0:  Nothing is printed.

               >=1: Initial and final impressions, messages
                    errors.

               >=3: One print line per iteration giving
                    the order k of the current iteration leading from x(k)
                    a x(k+1), the number of calls to the simulator before
                    this iteration, the value of the criterion f and its
                    directional derivative along d(k).

               >=4: Printing of nlis0.

               >=5: Additional impressions at the end of iteration k:
                    the stopping test E(k+1), prosca(y(k),s(k)) which
                    must be positive, the Oren-Spedicato factor
                    and the angle of the descent direction d(k) with
                    -g(k).

  io(e):      Scalar of type integer which will be taken as number
              output channel for controlled prints
              by iprint.

  mode(s):    Scalar of type integer giving the output mode of
              n1qn2.

               <0:  Unable to continue linear search
                    because the simulator responded with indic<0. Fashion
                    returns this value of indic.

               =0:  Stop requested by the simulator which responded with
                    index=0.

               =1:  Normal end with test on the gradient satisfied.

               =2:  Badly initialized input arguments. It could be
                    of n<=0, niter<=0, nsim<=0, dxmin<=0, epsg<=0,
                    epsg>1 or nrz<5n+1 (not enough memory
                    allocated).

               =3:  Linear search was blocked on tmax=10^20
                    (very unlikely mode).

               =4:  Maximum number of iterations reached.

               =5:  Maximum number of simulations reached.

               =6:  Stop on dxmin during linear search. This
                    output mode can have very different origins
                    various. If the number of step attempts during the
                    last linear search is weak, it can
                    mean that dxmin was taken too large. he can
                    also be errors or inaccuracies in the
                    gradient calculation. In this case, the management of
                    search d(k) can no longer be a direction of
                    descent of f in x(k), given that n1qn2
                    allows itself directions d(k) that can do with
                    -g(k) an angle close to 90 degrees. We will watch
                    therefore to calculate the gradient with precision.

               =7:  Either (g,d) or (y,s) are not positive (mode
                    output very unlikely).

  niter(es):  Scalar of type integer, strictly positive. In
              input is the maximum number of iterations allowed.
              The output is the number of iterations performed.

  nsim(es):   Scalar of type integer, strictly positive. In
              input is the maximum number of simulations allowed.
              The output is the number of simulations performed.

  rz(s):      Vector of dimension nrz of type double precision.
              This is the address of a work area for n1qn2.

  nrz(e):     Scalar of the integer type, strictly positive, giving
              the dimension of the working area rz. In addition to
              vectors x and g given as arguments, n1qn2 needs
              a work area made up of at least three
              n-dimensional vectors and each requested update
              requires 1 scalar and 2 n-dimensional vectors
              additional. So if m is the number of bets a
              desired day for the construction of the metric
              local, it will be necessary to take

                 nrz >= 3*n + m*(2*n+1).

              In fact, the number m is determined by n1qn2 which takes:

                  m = default integer part of ((nrz-3*n)/(2*n+1))

              This number must be >= 1. We must therefore nrz >= 5*n +1,
              otherwise n1qn2 stops in mode 2.
              
  izs, rzs, 
  dzs:        Addresses of memory zones respectively of the type
              integer, real and double precision. They are reserved
              to the user. N1qn2 does not use them and
              transmits to simul and prosca.
*/

typedef void (*simul_n1qn2_t)(int* indic, int* n, double* x, double* f, double* g, int* izs, float* rzs, double* dzs);
typedef void (*prosca_t)(int* n, double* u, double* v, double* ps, int* izs, float* rzs, double* dzs);

void F77_NAME(n1qn2)(simul_n1qn2_t simul,
                     prosca_t prosca,
                     int* n,
                     double* x,
                     double* f,
                     double* g,
                     double* dxmin,
                     double* df1,
                     double* epsg,
                     int* iprint,
                     int* io,
                     int* mode,
                     int* niter,
                     int* nsim,
                     double* dz,
                     int* ndz,
                     int* izs,
                     float* rzs,
                     double* dzs);



/*
n1qn3, version 1.0, September 1988.
Jean Charles Gilbert, Claude Lemarechal, INRIA.
Copyright INRIA
email: Jean-Charles.Gilbert@inria.fr

Uses subroutines:
  n1qn3a
  ddd2
  nlis0 + dcube (XII/88)

The n1qn3 subroutine is an interface between the program
caller and the n1qn3a subroutine, the actual minimizer.

The prosca module is supposed to realize the scalar product of two
Rn vectors; the ctonb module is supposed to make the change
bases: Euclidean basis -> orthonormal basis (for the product
scalar prosca); the ctbas module does the reverse transformation:
orthonormal basis -> Euclidean basis.

dz is the work area for n1qn3a, of dimension ndz.
It is subdivided into
  4 n-dimensional vectors: d,gg,diag,aux
  m scalars: alpha
  m n-dimensional vectors: ybar
  m n-dimensional vectors: sbar

m is then the largest integer such that
  m*(2*n+1)+4*n .le. ndz,
  let m := (ndz-4*n) / (2*n+1)
  We must have m >= 1, so ndz >= 6n+1.

At each iteration the metric is formed from a matrix
diagonal D which is updated m times by the formula of BFGS in
using the m most recent {y,s} pairs. The matrix diagonal is equal 
after the first iteration to

  (y,s)/|y|**2 * identity (Oren-Spedicato factor)

and is itself updated at each iteration using the diagonalized direct 
BFGS formula adapted to the ellipsoid of Rayleigh. If we note

  D[i]:=(De[i],e[i]), y[i]:=(y,e[i]), s[i]:=(s,e[i]),

where the e[i] form an orthonormal basis for the dot product
(.,.) that prosca realizes, the update formula of D is written:

  D[i] := 1 / ( (Dy,y)/(y,s)/D[i] + y[i]**2/(y,s)
        - (Dy,y)*(s[i]/D[i])**2/(y,s)/(D**(-1)s,s) )

Arguments:

integer n,iprint,io,mode,niter,nsim,ndz,izs(1)
real rzs(1)
double precision x(1),f,g(1),dxmin,df1,epsg,dz(1),dzs(1)
external simul,prosca,ctonb,ctcab
*/

typedef void (*ctonb_t)(int* n, double* depl, double* aux, int* izs, float* rzs, double* dzs);
typedef void (*ctcab_t)(int* n, double* aux, double* depl, int* izs, float* rzs, double* dzs);

void F77_NAME(n1qn3)(simul_n1qn2_t simul,
                     prosca_t prosca,
                     ctonb_t ctonb,
                     ctcab_t ctcab,
                     int* n,
                     double* x,
                     double* f,
                     double* g,
                     double* dxmin,
                     double* df1,
                     double* epsg,
                     int* iprint,
                     int* io,
                     int* mode,
                     int* niter,
                     int* nsim,
                     double* dz,
                     double* ndz,
                     int* izs,
                     float* rzs,
                     double* dzs);


/*
algorithm for minimizing a regular function under bound constraints

method
  bfgs method with limited memory + projection

subroutines (modulopt)
  proj rlbd majysa majz calbx gcp relvar bfgsd shanph

call list
  indgc       flag of gcbd in,
    input
      =1 standard
      =2 dh and indic initialized at the beginning of trav and itrav
         ifac,f,g initialize

    output
      if < 0 inability to calculate a better point than the initial point
      if = 0 stop requested by the user
      if > 0 we provide a better point than the starting point
      = -14 insufficient memory
      = -13 indgc not equal to zero or 1 in input
      = -12 zero,epsg or non-strict df0. positive
      = -11 n,napmax,itmax or non-strict io. positive
      < -10 inappropriate input parameters
      = -6 stop during the calculation of the direction of descent and iter=1
      = -5 stop when calculating the Hessian approximation iter=1
      = -3 simul anomaly: negative indicator at a point or
           f and g were previously calculated
      = -2 Linear search failed on first iteration
      = -1 f undefined at the initial point
      = 1 stop on epsg
      = 2 epsf
      = 3 epsx
      = 4 napmax
      = 5 itmax
      = 6 slope in opposite direction to gradient too small
      = 7 stop when calculating descent direction
      = 8 stops when calculating the Hessian approximation
      = 10 stop by failure of the linear search, cause not specified
      = 11 same with indsim < 0
      = 12 a pitch too small close to a pitch too big
           this may result from an error in the gradient
      = 13 too many calls in a linear search

  simul subroutine to calculate f and g (modulopt standard)
    n         dim of x
    x         variables to optimize (control)
    f         criterion value
    g         gradient of f
    iprint 
              if =0 no printing
                  1 impressions at the beginning and end of execution
                  2 3 rows at each iteration
                  >=3 many prints
    io        output file number
    zero      near zero machine
    napmax    maximum number of simul calls
    itmax     maximum number of iterations of gcbd
    epsf      criterion stop on f
    epsg      stop if greater than norm2(g+)/n
    epsx      vector dim n precision on x
    df0       >0 predicted decrease f
    binf,
    bsup      bounds inf,sup,de dim n
    nfac      number of variables not blocked at the optimum
    vect,
    ivect     dim work vectors nvect,nivect
    izs,
    rzs,
    dzs:      see modulopt standards

meaning of some internal variables

    {y}={g1}-{g0}  l (local)
    {s}={x1}-{x0}  l
    {z}=[b]*{s}.   [b] is an estimate of Hessian l
    ys=<y>*{s}     l
    zs=<z>*{s}     l
    diag        diagonal approximation of the hessian
                  if indgc=0 diag initializes to *******************
                  then updated by bfgs diagonal
    nt:         the number of moves taken into account l
                  index(nt) identifies the vectors y,s,z l
    wk1,
    wk2:        work vectors of dim n l
    iblock      vector dim n ; if x(i) is blocked, ibloc(i)=blocking iteration;
                               if x(i) is free, ibloc(i)=-1*(release iteration)
    irit:       irit=1, if vars release at current iter, 0 otherwise
    ired:       ired=1 restart decision, 0 otherwise
    alg(1)=param
    alg(2)=condmax
    alg(6)=eps
    alg(9)=tetaq (restart criterion)
    ialg(1)     powell correction on y if (y,s) too small
                  0: no powell correction
                  1: corrected
    ialg(2)     diag update by bfgsd
                  0: no update
                  1: update of diag by bfgsd
    ialg(3)     scaled by shanno-phua method
                  0: no scaling
                  1: scaled at all iterations
                  2: scaled at the 2nd iteration only
    ialg(4):    memorization for choice iterations
    ialg(5):    storage by variable
                  0: no memorization
                  1: with memorization
    ialg(6):    choice of release iterations
                  1: relaxation at all iterations
                  2: relaxation if decrease g norm gradient
                  10: release if decrease criterion % iter.initcycle
                  11: release if decrease criterion % cycle decrease
    ialg(7):    choice of variables to release
                  1: modified bertsekas method
    ialg(8):    choice of descent direction
                  3: sb without memory: nt last moves
                  4: restart without accumulation
                  5: restart with accumulation
    ialg(9):    restart criterion
                  2: restart if fact. or defact.
                  10: decrease criterion % decrease iter_init of the cycle
                  11: criterion decrease % total cycle decrease
                  12: decrease in znglib by a factor of alg(9)=tetaq
    eps0        is used to partition variables
    ceps0       uses in the calculation of eps0
    izag        min number of iterations during which a var remains blocked
    nap         number of fake calls
    iter        current iteration
    ind         simul indicator
    icv         memory input indgc
    np          param used for vect management. nb of current vector.
    lb          param used for vect management. 1st place free.
    nb          param used for vect management.
    nb=2        if the algorithm used is qn without memory +restart +not acc
    nb=1        otherwise
*/

void F77_NAME(gcbd)(int* indgc,
                    simul_n1qn2_t simul,
                    char nomf[6],
                    int* n,
                    double* x,
                    double* f,
                    double* g,
                    int* iprint,
                    int* io,
                    double* zero,
                    int* napmax,
                    int* itmax,
                    double* epsf,
                    double* epsg,
                    double* epsx,
                    double* df0,
                    double* binf,
                    double* bsup,
                    int* nfac,
                    double* vect,
                    int* nvect,
                    int* ivect,
                    int* nivect,
                    int* izs,
                    float* rzs,
                    double* dzs);


/*
minimization of a hemiderivable function by a sheaf method.

the direction is obtained by projection of the origin
on a polyhedron generated by a set of gradients already calculated
and the linear search gives a step of descent or a zero step.
the algorithm minimizes f at near eps0 (if convexity)
where eps0 is a tolerance given by the user.

  mode
    <=0 mode=simul indicator
    1   normal ending
    2   inconsistent call
    3   reduce x-scale
    4   max iterations
    5   max simulations
    6   impossible to go beyond dx
    7   fprf2 failed
    8   we start to loop

  iprint
    <0  indic=1 every -iprint iterations
    0   no impressions
    1   initial and final impressions
    2   impressions at each convergence
    3   one print per iteration
    4   information n1fc1 and nlis2
    >4  debugs
    5     various tolerances
    6     weights
    >6    fprf2

uses the following subroutines:

  fprf2   (direction calculation)
  fremf2,
  ffinf1  (fprf2 slaves)
  frdf1   (beam reduction)
  nlis2   (linear search)
  simul   (simulation module)
  prosca  (duality product giving the gradient)
*/

void F77_NAME(n1fc1)(simul_n1qn2_t simul,
                     prosca_t prosca,
                     int* n,
                     double* xn,
                     double* fn,
                     double* g,
                     double* dxmin,
                     double* df1,
                     double* epsf,
                     double* zero,
                     int* iprint,
                     int* io,
                     int* mode,
                     int* iter,
                     int* nsim,
                     int* memax,
                     int* iz,
                     double* rz,
                     double* dz,
                     int* izs,
                     float* rzs,
                     double* dzs);


/*
code for minimizing a regular function under constraints of terminals, to modulopt standards

method
  Principle of the algorithm: quasi-Newton + projection
  details in the inria report no. 242.1983 .
  This version allows to test several variants of the algorithm
  by modifying some internal parameters (see how in the code)
  required memory size of the order of n**2/2
  for large problems the gcbd code is better suited

subroutines called
  zqnbd     effective optimizer
  project   projection
  calmaj    hessian update
  update    update of choleski factors
  rlbd,
  satur     linear search with bounds

call list

  subroutine qnbd(indqn,simul,n,x,f,g,iprint,io,zero,
                  napmax,itmax,epsf,epsg,epsx,df0,binf,bsup,nfac,
                  trav,ntrav,itrav,nitrav,izs,rzs,dzs)

  indqn   indicator of qnbd
    input     =1 standard
              =2 dh and indic initialized at the beginning of trav and itrav
                 ifac,f,g initialize
    output
      if < 0  inability to calculate a better point than the initial point
      if = 0  stop requested by the user
      if > 0  we provide a better point than the starting point
      < -10   inappropriate input parameters
      = -6    stop during the calculation of the direction of descent and iter=1
      = -5    stop when calculating the Hessian approximation iter=1
      = -3    simul anomaly: negative indicator at a point or
              f and g were previously calculated
      = -2    Linear search failed on first iteration
      = -1    f undefined at the initial point
      = 1     stop on epsg
      = 2     epsf
      = 3     epsx
      = 4     napmax
      = 5     itmax
      = 6     slope in opposite direction to gradient too small
      = 7     stop when calculating descent direction
      = 8     stops when calculating the Hessian approximation
      = 10    stop by failure of the linear search, cause not specified
      = 11    same with indsim < 0
      = 12    a pitch too small close to a pitch too big
              this may result from an error in the gradient
      = 13    too many calls in a linear search

  simul   see modulopt standards
  n       dim of x
  binf,
  bsup    bounds inf,sup,de dim n
  x       variables to optimize (control)
  f       criterion value
  g       gradient of f
  zero    near zero machine
  napmax  maximum number of simul calls
  itmax   maximum number of descent iterations
  itrav   vect work dim nitrav=2n , breaks down into indic and izig
  nfac    number of factorized variables (e if indqn=2)
  iprint  print factor, varies from 0 (no impressions) to 3 (many impressions)
  io      result file number
  epsx    vector dim n precision on x
  epsf    criterion stop on f
  epsg    stop if greater than norm2(g+)/n
  trav    vect dim work ntrav we must ntrav > n(n+1)/2 +6n
  df0     >0 predicted decrease f (take 1. by default)
  izs,
  rzs,
  dzs:    see modulopt standards

indications on the internal variables a qnbd and zqnbd

  izig      is used to memorize constraints (active if izag>1)
            if i does not change d ens we remove 1 a izig (positive)
            otherwise we add izag factorization only if izig is zero
  dh        hessian estimate dim n(n+1)/2 row in three pieces
  indic(i)  new index of index i
  indic     vector dim n order of ranking of indices
            no need to initialize it if indqn=1

linear search parameters
  amd,amf   param. of the Wolfe test. (.7,.1)
  napm      max number of calls in the rl (=15)

*/

void F77_NAME(qnbd)(int* indqn,
                    simul_n1qn2_t simul,
                    int* n,
                    double* x,
                    double* f,
                    double* g,
                    int* iprint,
                    int* io,
                    double* zero,
                    int* napmax,
                    int* itmax,
                    double* epsf,
                    double* epsg,
                    double* epsx,
                    double* df0,
                    double* binf,
                    double* bsup,
                    int* nfac,
                    double* trav,
                    int* ntrav,
                    int* itrav,
                    int* nitrav,
                    int* izs,
                    float* rzs,
                    double* dzs);


/*
This routine uses the Goldfarb/Idnani algorithm to solve the
following minimization problem:

     minimize  -d^T x + 1/2 *  x^T D x

     where   A1^T x  = b1
             A2^T x >= b2

the matrix D is assumed to be positive definite.  Especially,
w.l.o.g. D is assumed to be symmetric.
 
Input parameter:
  dmat      nxn matrix, the matrix D from above (dp)
            *** WILL BE DESTROYED ON EXIT ***
            The user has two possibilities:
            a)  Give D (ierr=0), in this case we use routines from LINPACK
                to decompose D.
            b)  To get the algorithm started we need R^-1, where D=R^TR.
                So if it is cheaper to calculate R^-1 in another way (D may
                be a band matrix) then with the general routine, the user
                may pass R^{-1}.  Indicated by ierr not equal to zero.
  dvec      nx1 vector, the vector d from above (dp)
            *** WILL BE DESTROYED ON EXIT ***
            contains on exit the solution to the inisolve.QP.compact.ftial, i.e.,
            unconstrained problem
  fddmat    scalar, the leading dimension of the matrix dmat
  n         the dimension of dmat and dvec (int)
  amat      (nnz x 1) array of non zero entries of A (dp) stored column-wise
            *** ENTRIES CORRESPONDING TO EQUALITY CONSTRAINTS MAY HAVE CHANGED SIGNES ON EXIT ***
  colnnz    (q x 1) array (int) stores the number of non-zero entries of A for each column.
  nzrindex  (nnz x 1) array (int) stores the row index  of non-zero entries of A 
  bvec      qx1 vector, the vector of constants b in the constraints (dp)
            [ b = (b1^T b2^T)^T ]
            *** ENTRIES CORRESPONDING TO EQUALITY CONSTRAINTS MAY HAVE CHANGED SIGNES ON EXIT ***
  fdamat    the first dimension of amat as declared in the calling program. 
            fdamat >= n (and iamat must have fdamat+1 as first dimension)
  q         integer, the number of constraints.
  meq       integer, the number of equality constraints, 0 <= meq <= q.
  ierr      integer, code for the status of the matrix D:
              ierr =  0, we have to decompose D
              ierr != 0, D is already decomposed into D=R^TR and we were given R^{-1}.

Output parameter:
  sol       nx1 the final solution (x in the notation above)
  crval     scalar, the value of the criterion at the minimum      
  iact      qx1 vector, the constraints which are active in the final fit (int)
  nact      scalar, the number of constraints active in the final fit (int)
  iter      2x1 vector, first component gives the number of "main" 
            iterations, the second one says how many constraints were
            deleted after they became active
  ierr      integer, error code on exit, if
            ierr = 0, no problems
            ierr = 1, the minimization problem has no solution
            ierr = 2, problems with decomposing D, in this case sol contains garbage!!

Working space:
  work      vector with length at least 2*n+r*(r+5)/2 + 2*q +1 where r=min(n,q)

*/

void F77_NAME(qpgen1sci)(double* dmat, 
                         double* dvec, 
                         int* fddmat, 
                         int* n, 
                         double* sol,
                         double* crval, 
                         int* colnnz,
                         int* nzrindex,
                         double* amat,
                         double* bvec,
                         int* q,
                         int* meq,
                         int* iact,
                         int* nact,
                         int* iter,
                         double* work,
                         int* ierr);

/*
this routine uses the Goldfarb/Idnani algorithm to solve the
following minimization problem:

  minimize  -d^T x + 1/2 *  x^T D x
  where      A1^T x  = b1
             A2^T x >= b2

the matrix D is assumed to be positive definite.  Especially,
w.l.o.g. D is assumed to be symmetric.
 
Input parameter:
  dmat    nxn matrix, the matrix D from above (dp)
          *** WILL BE DESTROYED ON EXIT ***
          The user has two possibilities:
          a)  Give D (ierr=0), in this case we use routines from LINPACK
              to decompose D.
          b)  To get the algorithm started we need R^-1, where D=R^TR.
              So if it is cheaper to calculate R^-1 in another way (D may
              be a band matrix) then with the general routine, the user
              may pass R^{-1}.  Indicated by ierr not equal to zero.
  dvec    nx1 vector, the vector d from above (dp)
          *** WILL BE DESTROYED ON EXIT ***
          contains on exit the solution to the initial, i.e.,
          unconstrained problem
  fddmat  scalar, the leading dimension of the matrix dmat
  n       the dimension of dmat and dvec (int)
  amat    nxq matrix, the matrix A from above (dp) [ A=(A1 A2)^T ]
          *** ENTRIES CORRESPONDING TO EQUALITY CONSTRAINTS MAY HAVE CHANGED SIGNES ON EXIT ***
  bvec    qx1 vector, the vector of constants b in the constraints (dp)
          [ b = (b1^T b2^T)^T ]
          *** ENTRIES CORRESPONDING TO EQUALITY CONSTRAINTS MAY HAVE CHANGED SIGNES ON EXIT ***
  fdamat  the first dimension of amat as declared in the calling program. 
          fdamat >= n !!
  q       integer, the number of constraints.
  meq     integer, the number of equality constraints, 0 <= meq <= q.
  ierr    integer, code for the status of the matrix D:
            ierr =  0, we have to decompose D
            ierr != 0, D is already decomposed into D=R^TR and we were given R^{-1}.

Output parameter:
  sol     nx1 the final solution (x in the notation above)
  crval   scalar, the value of the criterion at the minimum      
  iact    qx1 vector, the constraints which are active in the final
          fit (int)
  nact    scalar, the number of constraints active in the final fit (int)
  iter    2x1 vector, first component gives the number of "main" 
          iterations, the second one says how many constraints were
          deleted after they became active
  ierr    integer, error code on exit, if
            ierr = 0, no problems
            ierr = 1, the minimization problem has no solution
            ierr = 2, problems with decomposing D, in this case sol contains garbage!!

Working space:
  work    vector with length at least 2*n+r*(r+5)/2 + 2*q +1 where r=min(n,q)

*/

void F77_NAME(qpgen2)(double* dmat, 
                      double* dvec, 
                      int* fddmat, 
                      int* n, 
                      double* sol, 
                      double* crval, 
                      double* amat, 
                      double* bvec, 
                      int* fdamat, 
                      int* q, 
                      int* meq, 
                      int* iact, 
                      int* nact, 
                      int* iter, 
                      double* work, 
                      int* ierr);


/*
subroutine qrfac

this subroutine uses householder transformations with column
pivoting (optional) to compute a qr factorization of the
m by n matrix a. that is, qrfac determines an orthogonal
matrix q, a permutation matrix p, and an upper trapezoidal
matrix r with diagonal elements of nonincreasing magnitude,
such that a*p = q*r. the householder transformation for
column k, k = 1,2,...,min(m,n), is of the form

                      t
      i - (1/u(k))*u*u

where u has zeros in the first k-1 positions. the form of
this transformation and the method of pivoting first
appeared in the corresponding linpack subroutine.

the subroutine statement is

  subroutine qrfac(m,n,a,lda,pivot,ipvt,lipvt,rdiag,acnorm,wa)

where

  m is a positive integer input variable set to the number
    of rows of a.

  n is a positive integer input variable set to the number
    of columns of a.

  a is an m by n array. on input a contains the matrix for
    which the qr factorization is to be computed. on output
    the strict upper trapezoidal part of a contains the strict
    upper trapezoidal part of r, and the lower trapezoidal
    part of a contains a factored form of q (the non-trivial
    elements of the u vectors described above).

  lda is a positive integer input variable not less than m
    which specifies the leading dimension of the array a.

  pivot is a logical input variable. if pivot is set true,
    then column pivoting is enforced. if pivot is set false,
    then no column pivoting is done.

  ipvt is an integer output array of length lipvt. ipvt
    defines the permutation matrix p such that a*p = q*r.
    column j of p is column ipvt(j) of the identity matrix.
    if pivot is false, ipvt is not referenced.

  lipvt is a positive integer input variable. if pivot is false,
    then lipvt may be as small as 1. if pivot is true, then
    lipvt must be at least n.

  rdiag is an output array of length n which contains the
    diagonal elements of r.

  acnorm is an output array of length n which contains the
    norms of the corresponding columns of the input matrix a.
    if this information is not needed, then acnorm can coincide
    with rdiag.

  wa is a work array of length n. if pivot is false, then wa
    can coincide with rdiag.

subprograms called

  minpack-supplied ... dlamch,enorm

  fortran-supplied ... dmax1,dsqrt,min0

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more
*/

void F77_NAME(qrfac)(int* m,
                     int* n,
                     double* a,
                     int* lda,
                     int* pivot,
                     int* ipvt,
                     int* lipvt,
                     double* rdiag,
                     double* acnorm,
                     double* wa);


/*
subroutine qrsolv

given an m by n matrix a, an n by n diagonal matrix d,
and an m-vector b, the problem is to determine an x which
solves the system

      a*x = b ,     d*x = 0 ,

in the least squares sense.

this subroutine completes the solution of the problem
if it is provided with the necessary information from the
qr factorization, with column pivoting, of a. that is, if
a*p = q*r, where p is a permutation matrix, q has orthogonal
columns, and r is an upper triangular matrix with diagonal
elements of nonincreasing magnitude, then qrsolv expects
the full upper triangle of r, the permutation matrix p,
and the first n components of (q transpose)*b. the system
a*x = b, d*x = 0, is then equivalent to

             t       t
      r*z = q *b ,  p *d*p*z = 0 ,

where x = p*z. if this system does not have full rank,
then a least squares solution is obtained. on output qrsolv
also provides an upper triangular matrix s such that

       t   t               t
      p *(a *a + d*d)*p = s *s .

s is computed within qrsolv and may be of separate interest.

the subroutine statement is

  subroutine qrsolv(n,r,ldr,ipvt,diag,qtb,x,sdiag,wa)

where

  n is a positive integer input variable set to the order of r.

  r is an n by n array. on input the full upper triangle
    must contain the full upper triangle of the matrix r.
    on output the full upper triangle is unaltered, and the
    strict lower triangle contains the strict upper triangle
    (transposed) of the upper triangular matrix s.

  ldr is a positive integer input variable not less than n
    which specifies the leading dimension of the array r.

  ipvt is an integer input array of length n which defines the
    permutation matrix p such that a*p = q*r. column j of p
    is column ipvt(j) of the identity matrix.

  diag is an input array of length n which must contain the
    diagonal elements of the matrix d.

  qtb is an input array of length n which must contain the first
    n elements of the vector (q transpose)*b.

  x is an output array of length n which contains the least
    squares solution of the system a*x = b, d*x = 0.

  sdiag is an output array of length n which contains the
    diagonal elements of the upper triangular matrix s.

  wa is a work array of length n.

subprograms called

  fortran-supplied ... dabs,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more
*/

void F77_NAME(qrsolv)(int* n,
                      double* r,
                      int* ldr,
                      int* ipvt,
                      double* diag,
                      double* qtb,
                      double* x,
                      double* sdiag,
                      double* wa);


/*
subroutine r1mpyq

given an m by n matrix a, this subroutine computes a*q where
q is the product of 2*(n - 1) transformations

      gv(n-1)*...*gv(1)*gw(1)*...*gw(n-1)

and gv(i), gw(i) are givens rotations in the (i,n) plane which
eliminate elements in the i-th and n-th planes, respectively.
q itself is not given, rather the information to recover the
gv, gw rotations is supplied.

the subroutine statement is

  subroutine r1mpyq(m,n,a,lda,v,w)

where

  m is a positive integer input variable set to the number
    of rows of a.

  n is a positive integer input variable set to the number
    of columns of a.

  a is an m by n array. on input a must contain the matrix
    to be postmultiplied by the orthogonal matrix q
    described above. on output a*q has replaced a.

  lda is a positive integer input variable not less than m
    which specifies the leading dimension of the array a.

  v is an input array of length n. v(i) must contain the
    information necessary to recover the givens rotation gv(i)
    described above.

  w is an input array of length n. w(i) must contain the
    information necessary to recover the givens rotation gw(i)
    described above.

subroutines called

  fortran-supplied ... dabs,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more
*/

void F77_NAME(r1mpyq)(int* m,
                      int* n,
                      double* a,
                      int* lda,
                      double* v,
                      double* w);


/*
subroutine r1updt

given an m by n lower trapezoidal matrix s, an m-vector u,
and an n-vector v, the problem is to determine an
orthogonal matrix q such that

              t
      (s + u*v )*q

is again lower trapezoidal.

this subroutine determines q as the product of 2*(n - 1)
transformations

      gv(n-1)*...*gv(1)*gw(1)*...*gw(n-1)

where gv(i), gw(i) are givens rotations in the (i,n) plane
which eliminate elements in the i-th and n-th planes,
respectively. q itself is not accumulated, rather the
information to recover the gv, gw rotations is returned.

the subroutine statement is

  subroutine r1updt(m,n,s,ls,u,v,w,sing)

where

  m is a positive integer input variable set to the number
    of rows of s.

  n is a positive integer input variable set to the number
    of columns of s. n must not exceed m.

  s is an array of length ls. on input s must contain the lower
    trapezoidal matrix s stored by columns. on output s contains
    the lower trapezoidal matrix produced as described above.

  ls is a positive integer input variable not less than
    (n*(2*m-n+1))/2.

  u is an input array of length m which must contain the
    vector u.

  v is an array of length n. on input v must contain the vector
    v. on output v(i) contains the information necessary to
    recover the givens rotation gv(i) described above.

  w is an output array of length m. w(i) contains information
    necessary to recover the givens rotation gw(i) described
    above.

  sing is a logical output variable. sing is set true if any
    of the diagonal elements of the output s are zero. otherwise
    sing is set false.

subprograms called

  minpack-supplied ... dlamch

  fortran-supplied ... dabs,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more,
john l. nazareth
*/

void F77_NAME(r1updt)(int* m,
                      int* n,
                      double* s,
                      int* ls,
                      double* u,
                      double* v,
                      double* w,
                      int* sing);


/*
linear search subroutine for problems with bound constraints (handled by projection)
the return criterion is an extension of wolfe's

method
  for each value of the parameter t , the criterion is calculated
  and its gradient. an extrapolation phase makes it possible to obtain a 
  framework. The interval is then reduced according to the cases by a method
  dichotomy, linear interpolation on derivatives or d cubic interpolation.

prints
  if iprint > 2 , rlbd provides the following prints:

  the first line says:
  t first value of t provided in call list
  tproj smallest t > 0 for which we stumble on a terminal
  dh/dt derivative at zero of h(t)=f(x+t*d)-f(x)
  tmax maximum value of t provided in call list

following lines:
  character string at the beginning of the line: indicates how it will be calculated
  the step of the next line;
  ic:   cubic interpolation
  s:    saturation of a variable on a terminal
  id:   linear interpolation on the derivative
  e:    extrapolation
  d:    failed cubic interpolation t is calculated by dichotomy
  b:    convergence backup active

subroutines used
  proj and satur (library modulopt)

call list
  subroutine rlbd(indrl,n,simul,proj,x,binf,bsup,f,hp,t,tmax,d,gn,tproj,
                  amd,amf,iprint,io,zero,nap,napmax,xn,izs,rzs,dzs)

  e;s;e,s: parameters initialized on input,on output,on input and output

  indrl   <0:             linear search did not find better step (s)
          =0:             stop requested by the user in simul
          >0:             better not provided with f and g
          >9:             best not provided with f and without g
          =14:            delta too small
          =13:            nap=napmax
          =8:             all variables are saturated
          =4:             delta too small
          =3:             nap=napmax
          =2:             t=tmax
          =1:             serious descent with t<tmax
          =0:             stop requested by user
          =-3:            nap=napmax
          =-4:            deltat too small
          =-1000+indic:   nap=napmax and indic<0

  n:      dimension of x                                          (e,s)
  simul:  subroutine providing the criterion and the gradient     (e)
  x:      initial value of the variable to be optimized as input;
          value a the optimum output.                             (e,s)
  binf,
  bsup:   lower and upper bounds of dimension n                   (e,s)
  f:      value of the criterion in x                             (e,s)
  hp:     derived from f(x+t*d) with respect to t at 0            (e)
  t:      not
  tmax:   maximum step value                                      (e,s)
  d:      descent direction                                       (e)
  gn:     gradient of f in xn                                     (e,s)
  tproj:  smallest step saturating a new constraint               (s)
  amf,
  amd:    wolfe test constants                                    (e)
  iprint
        <=2:      no printing                                     (e)
        >=3:      one printing per simul calculation              (e)
        io:       result file number                              (e)
        zero:     close to machine zero                           (e)
        nap:      number of calls to simul                        (e)
        napmax:   maximum number of calls to simul                (e)
        xn:       n-dimensional work array (=x+t*d)
        izs,
        rzs,
        dzs:      cf standard modulopt                            (e,s)

  algorithm parameters
    eps1:   save conv. in linear interpolation on derivative
    eps:    save conv. in saturation interpolation of a constraint.
    epst:   save conv. in cubic interpolation
    extra,
    extrp:  are used to calculate the limit on the relative variation
            of t in extrapolation and linear interpolation on the derivative
    cofder: intervenes in the choice between interpolation methods

  work variables
    fn:     value of the criterion in xn
    hpn:    derivative of f(x+t*d) with respect to t
    hpd:    value of hpn on the right
    hpg:    value of hpn on the left
    td:     not too big
    tg:     not too small
    tproj:  smallest step saturating a constraint
    tmaxp:  largest step saturating a constraint
    ftd:    value of f in x+td*d
    ftg:    value of f in x+tg*d
    hptd:   value of hpn in x+td*d
    hptg:   value of hpn in x+tg*d
    imax=1: tmax has been reached
        =0: tmax has not been reached
    icos:   index of the variable saturated by the upper bound
    icoi:   index of the variable saturated by the lower bound
    ico1:   index of the saturated variable in tmaxp
    icop:   index of the saturated variable in tproj
*/

void F77_NAME(rlbd)(int* indrl,
                    int* n,
                    simul_n1qn2_t simul,
                    double* x,
                    double* binf,
                    double* bsup,
                    double* f,
                    double* hp,
                    double* t,
                    double* tmax,
                    double* d,
                    double* gn,
                    double* tproj,
                    double* amd,
                    double* amf,
                    int* iprint,
                    int* io,
                    double* zero,
                    int* nap,
                    int* napmax,
                    double* xn,
                    int* izs,
                    float* rzs,
                    double* dzs);



/*
subroutine calculating, in a given interval, a close step
of tmi saturating a constraint

  topt:   not calculate (=0 if there is no such step                  (s)
  ttmin,
  ttsup:  bounds of the interval in which must be top
  tmi:    not in the vicinity of which we calculate topt              (e)
  iproj:  projection indicator                                        (e)
            =0: we are looking for a step saturating a constraint in
                the interval ttmin,ttsup
            =1: we seek a step in the interval tg,td and we
                brings it back to the interval ttmin,ttsup
                by projection
  icos:   index of the variable saturated by the upper bound
  icoi:   index of the variable saturated by the lower bound
  inf:    flag for initializing icoi and icos
            =0: the upper limit is reached
            =1: the upper limit is reached
            =2: the step is obtained by projection on ttmin ttsup
*/

void F77_NAME(satur)(int* n,
                     double* x,
                     double* binf,
                     double* bsup,
                     double* d,
                     double* ttmin,
                     double* ttsup,
                     double* topt,
                     double* tg,
                     double* td,
                     double* tmi,
                     int* icoi,
                     int* icos,
                     int* iproj);



/* 
Calculate the product H g or

  . H is a matrix constructed by the inverse bfgs formula
    a m memories from precon times the unit matrix in
    a Hilbert space whose scalar product is given by prosca
    (cf. J. Nocedal, math. of comp. 35/151 (1980) 773-782)

  . g is an n-dimensional vector (usually the gradient)

The precon factor therefore appears as a preconditioner scalar.

  delp = g (input), = H g (output)

The matrix H is memorized by the array vectors
ybar, sbar and the pointers jmin, jmax.

alpha(m) is a work area.

izs(1),rzs(1),dzs(1) are working areas for prosca

*/

void F77_NAME(strang)(prosca_t prosca,
                      int* n,
                      int* m,
                      double* depl,
                      int* jmin,
                      int* jmax,
                      double* precon,
                      double* alpha,
                      double* ybar,
                      double* sbar,
                      int* izs,
                      float* rzs,
                      double* dzs);


/*
dpori computes the inverse of the factor of a 
double precision symmetric positive definite matrix 
using the factors computed by dpofa.

modification of dpodi by BaT 05/11/95

on entry

    a       double precision(lda, n)
            the output  a  from dpofa

    lda     integer
            the leading dimension of the array  a .

    n       integer
            the order of the matrix  a .

on return

    a       if dpofa was used to factor  a  then
            dpodi produces the upper half of inverse(a) .
            elements of  a  below the diagonal are unchanged.

error condition

    a division by zero will occur if the input factor contains
    a zero on the diagonal and the inverse is requested.
    it will not occur if the subroutines are called correctly
    and if dpoco or dpofa has set info .eq. 0 .

linpack.  this version dated 08/14/78 .
cleve moler, university of new mexico, argonne national lab.
modified by Berwin A. Turlach 05/11/95

subroutines and functions

blas daxpy,dscal
fortran mod

internal variables

double precision t
integer j,k,kp1

compute inverse(r)

*/

void F77_NAME(dpori)(double* a,
                     int* lda,
                     int* n);



/*
dposl solves the double precision symmetric positive definite
system a * x = b
using the factors computed by dpoco or dpofa.

on entry

   a       double precision(lda, n)
           the output from dpoco or dpofa.

   lda     integer
           the leading dimension of the array  a .

   n       integer
           the order of the matrix  a .

   b       double precision(n)
           the right hand side vector.

on return

   b       the solution vector  x .

error condition

   a division by zero will occur if the input factor contains
   a zero on the diagonal.  technically this indicates
   singularity but it is usually caused by improper subroutine
   arguments.  it will not occur if the subroutines are called
   correctly and  info .eq. 0 .

to compute  inverse(a) * c  where  c  is a matrix
with  p  columns
      call dpoco(a,lda,n,rcond,z,info)
      if (rcond is too small .or. info .ne. 0) go to ...
      do 10 j = 1, p
         call dposl(a,lda,n,c(1,j))
   10 continue

linpack.  this version dated 08/14/78 .
cleve moler, university of new mexico, argonne national lab.

subroutines and functions

blas daxpy,ddot

*/

void F77_NAME(dposl)(double* a,
                     int* lda,
                     int* n,
                     double* b);


/*
this subroutine adds the vector x, of size n, to the vector y. 

(y=y+x)

in the case of two increments equal to 1, this subroutine
uses "bloomed" loops. 

in case the increments are negative this
subroutine takes the components in reverse order.

call list

  subroutine dadd(n,dx,incx,dy,incy)

  n: vector size x

  dx: double precision vector containing x

  dy: double precision vector containing y

  incx, incy: increments between vector components.

*/

void F77_NAME(dadd)(int* n,
                    double* dx,
                    int* incx,
                    double* dy,
                    int* incy);


/*
calculate the product h g or

  . h is a matrix constructed by the inverse bfgs formula
    a nm memories from the diagonal matrix diag
    in a Hilbert space whose scalar product is given by prosca
    (cf. J. Nocedal, Math. of Comp. 35/151 (1980) 773-782)

  . g is an n-dimensional vector (usually the gradient)

the matrix diag therefore appears as a diagonal preconditioner
depl = g (input), = h g (output)
the matrix h is memorized by the array vectors
ybar, sbar and jmin, jmax pointers
alpha(nm) is work area
izs(1),rzs(1),dzs(1) are working areas for prosca

    arguments
integer n,nm,jmin,jmax,izs(1)
real rzs(1)
double precision depl(n),diag(n),alpha(nm),ybar(n,nm),sbar(n,nm),
    aux(n),dzs(1)
external prosca,ctonb,ctcab
*/

void F77_NAME(ddd2)(prosca_t prosca,
                    ctonb_t ctonb,
                    ctcab_t ctcab,
                    int* n,
                    int* nm,
                    double* depl,
                    double* aux,
                    int* jmin,
                    int* jmax,
                    double* diag,
                    double* alpha,
                    double* ybar,
                    double* sbar,
                    int* izs,
                    float* rzs,
                    double* dzs);


/*
dgefa factors a double precision matrix by gaussian elimination.

dgefa is usually called by dgeco, but it can be called
directly with a saving in time if  rcond  is not needed.
(time for dgeco) = (1 + 9/n)*(time for dgefa) .

on entry

   a       double precision(lda, n)
           the matrix to be factored.

   lda     integer
           the leading dimension of the array  a .

   n       integer
           the order of the matrix  a .

on return

   a       an upper triangular matrix and the multipliers
           which were used to obtain it.
           the factorization can be written  a = l*u  where
           l  is a product of permutation and unit lower
           triangular matrices and  u  is upper triangular.

   ipvt    integer(n)
           an integer vector of pivot indices.

   info    integer
           = 0  normal value.
           = k  if  u(k,k) .eq. 0.0 .  this is not an error
                condition for this subroutine, but it does
                indicate that dgesl or dgedi will divide by zero
                if called.  use  rcond  in dgeco for a reliable
                indication of singularity.

linpack. this version dated 08/14/78 .
cleve moler, university of new mexico, argonne national lab.

subroutines and functions

blas daxpy,dscal,idamax

*/

void F77_NAME(dgefa)(double* a,
                     int* lda,
                     int* n,
                     int* ipvt,
                     int* info);


/*
dgesl solves the double precision system

  a * x = b  or  trans(a) * x = b

using the factors computed by dgeco or dgefa.

calling sequence

  subroutine dgesl(a,lda,n,ipvt,b,job)
  on entry

    a       double precision(lda, n)
            the output from dgeco or dgefa.

    lda     integer
            the leading dimension of the array  a .

    n       integer
            the order of the matrix  a .

    ipvt    integer(n)
            the pivot vector from dgeco or dgefa.

    b       double precision(n)
            the right hand side vector.

    job     integer
            = 0         to solve  a*x = b ,
            = nonzero   to solve  trans(a)*x = b  where
                        trans(a)  is the transpose.

  on return

    b       the solution vector  x .

  error condition

    a division by zero will occur if the input factor contains a
    zero on the diagonal.  technically this indicates singularity
    but it is often caused by improper arguments or improper
    setting of lda .  it will not occur if the subroutines are
    called correctly and if dgeco has set rcond .gt. 0.0
    or dgefa has set info .eq. 0 .

    to compute  inverse(a) * c  where  c  is a matrix

    with  p  columns
          call dgeco(a,lda,n,ipvt,rcond,z)
          if (rcond is too small) go to ...
          do 10 j = 1, p
             call dgesl(a,lda,n,ipvt,c(1,j),0)
       10 continue

originator
    linpack. this version dated 08/14/78 .
    cleve moler, university of new mexico, argonne national lab.

auxiliary routines

    blas daxpy,ddot

*/

void F77_NAME(dgesl)(double* a,
                     int* lda,
                     int* n,
                     int* ipvt,
                     double* b,
                     int* job);


/*
PURPOSE
   computes the matrix product C = A * B
       C   =   A   *   B
     (l,n)   (l,m) * (m,n)
  
PARAMETERS
   input 
   -----
   A : (double) array (l, m) with leading dim na
            
   B : (double) array (m, n) with leading dim nb

   na, nb, nc, l, m, n : integers

   output 
   ------
   C : (double) array (l, n) with leading dim nc

NOTE
   (original version substituted by a call to the blas dgemm)
*/

void F77_NAME(dmmul)(double* A, 
                     int* na, 
                     double* B, 
                     int* nb, 
                     double* C, 
                     int* nc, 
                     int* l, 
                     int* m, 
                     int* n);


/*
subroutine dogleg

given an m by n matrix a, an n by n nonsingular diagonal
matrix d, an m-vector b, and a positive number delta, the
problem is to determine the convex combination x of the
gauss-newton and scaled gradient directions that minimizes
(a*x - b) in the least squares sense, subject to the
restriction that the euclidean norm of d*x be at most delta.

this subroutine completes the solution of the problem
if it is provided with the necessary information from the
qr factorization of a. that is, if a = q*r, where q has
orthogonal columns and r is an upper triangular matrix,
then dogleg expects the full upper triangle of r and
the first n components of (q transpose)*b.

the subroutine statement is

  subroutine dogleg(n,r,lr,diag,qtb,delta,x,wa1,wa2)

where

  n is a positive integer input variable set to the order of r.

  r is an input array of length lr which must contain the upper
    triangular matrix r stored by rows.

  lr is a positive integer input variable not less than
    (n*(n+1))/2.

  diag is an input array of length n which must contain the
    diagonal elements of the matrix d.

  qtb is an input array of length n which must contain the first
    n elements of the vector (q transpose)*b.

  delta is a positive input variable which specifies an upper
    bound on the euclidean norm of d*x.

  x is an output array of length n which contains the desired
    convex combination of the gauss-newton direction and the
    scaled gradient direction.

  wa1 and wa2 are work arrays of length n.

subprograms called

  minpack-supplied ... dlamch,enorm

  fortran-supplied ... dabs,dmax1,dmin1,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more

*/

void F77_NAME(dogleg)(int* n,
                      double* r,
                      int* lr,
                      double* diag,
                      double* qtb,
                      double* delta,
                      double* x,
                      double* wa1,
                      double* wa2);


/*
dset assigns a scalar to all elements of a vector

call list
  subroutine dset(n,dx,dy,incy)

  double precision dx,dy(n*incy)
  integer n,incy

  n:    number of elements of the vector dy
  dx:   scalar to assign
  dy:   array containing the vector
  incy: increment between two consecutive elements of vector y
        in the dy array

*/

void F77_NAME(dset)(int* n,
                    double* dx,
                    double* dy,
                    int* incy);


/*
function enorm

given an n-vector x, this function calculates the
euclidean norm of x.

the euclidean norm is computed by accumulating the sum of
squares in three different sums. the sums of squares for the
small and large components are scaled so that no overflows
occur. non-destructive underflows are permitted. underflows
and overflows do not occur in the computation of the unscaled
sum of squares for the intermediate components.
the definitions of small, intermediate and large components
depend on two constants, rdwarf and rgiant. the main
restrictions on these constants are that rdwarf**2 not
underflow and rgiant**2 not overflow. the constants
given here are suitable for every known computer.

the function statement is

  double precision function enorm(n,x)

where

  n is a positive integer input variable.

  x is an input array of length n.

subprograms called

  fortran-supplied ... dabs,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more

**********
integer i
double precision agiant,floatn,one,rdwarf,rgiant,s1,s2,s3,xabs,
                 x1max,x3max,zero
data one,zero,rdwarf,rgiant /1.0d0,0.0d0,3.834d-20,1.304d19/
*/

double F77_NAME(enorm)(int* n, 
                      double* x);


/*
subroutine fdjac1

this subroutine computes a forward-difference approximation
to the n by n jacobian matrix associated with a specified
problem of n functions in n variables. if the jacobian has
a banded form, then function evaluations are saved by only
approximating the nonzero terms.

the subroutine statement is

  subroutine fdjac1(fcn,n,x,fvec,fjac,ldfjac,iflag,ml,mu,epsfcn,
                    wa1,wa2)

where

  fcn is the name of the user-supplied subroutine which
    calculates the functions. fcn must be declared
    in an external statement in the user calling
    program, and should be written as follows.

    subroutine fcn(n,x,fvec,iflag)
    integer n,iflag
    double precision x(n),fvec(n)
    ----------
    calculate the functions at x and
    return this vector in fvec.
    ----------
    return
    end

    the value of iflag should not be changed by fcn unless
    the user wants to terminate execution of fdjac1.
    in this case set iflag to a negative integer.

  n is a positive integer input variable set to the number
    of functions and variables.

  x is an input array of length n.

  fvec is an input array of length n which must contain the
    functions evaluated at x.

  fjac is an output n by n array which contains the
    approximation to the jacobian matrix evaluated at x.

  ldfjac is a positive integer input variable not less than n
    which specifies the leading dimension of the array fjac.

  iflag is an integer variable which can be used to terminate
    the execution of fdjac1. see description of fcn.

  ml is a nonnegative integer input variable which specifies
    the number of subdiagonals within the band of the
    jacobian matrix. if the jacobian is not banded, set
    ml to at least n - 1.

  epsfcn is an input variable used in determining a suitable
    step length for the forward-difference approximation. this
    approximation assumes that the relative errors in the
    functions are of the order of epsfcn. if epsfcn is less
    than the machine precision, it is assumed that the relative
    errors in the functions are of the order of the machine
    precision.

  mu is a nonnegative integer input variable which specifies
    the number of superdiagonals within the band of the
    jacobian matrix. if the jacobian is not banded, set
    mu to at least n - 1.

  wa1 and wa2 are work arrays of length n. if ml + mu + 1 is at
    least n, then the jacobian is considered dense, and wa2 is
    not referenced.

subprograms called

  minpack-supplied ... dlamch

  fortran-supplied ... dabs,dmax1,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more

*/

typedef void (*fcn1_t)(int* n, double* x, double* fvec, int* flag);

void F77_NAME(fdjac1)(fcn1_t fcn,
                      int* n,
                      double* x,
                      double* fvec,
                      double* fjac,
                      double* ldfjac,
                      int* iflag,
                      int* ml,
                      int* mu,
                      double* epsfcn,
                      double* wa1,
                      double* wa2);


/* 
subroutine fdjac2

this subroutine computes a forward-difference approximation
to the m by n jacobian matrix associated with a specified
problem of m functions in n variables.

the subroutine statement is

  subroutine fdjac2(fcn,m,n,x,fvec,fjac,ldfjac,iflag,epsfcn,wa)

where

  fcn is the name of the user-supplied subroutine which
    calculates the functions. fcn must be declared
    in an external statement in the user calling
    program, and should be written as follows.

    subroutine fcn(m,n,x,fvec,iflag)
    integer m,n,iflag
    double precision x(n),fvec(m)
    ----------
    calculate the functions at x and
    return this vector in fvec.
    ----------
    return
    end

    the value of iflag should not be changed by fcn unless
    the user wants to terminate execution of fdjac2.
    in this case set iflag to a negative integer.

  m is a positive integer input variable set to the number
    of functions.

  n is a positive integer input variable set to the number
    of variables. n must not exceed m.

  x is an input array of length n.

  fvec is an input array of length m which must contain the
    functions evaluated at x.

  fjac is an output m by n array which contains the
    approximation to the jacobian matrix evaluated at x.

  ldfjac is a positive integer input variable not less than m
    which specifies the leading dimension of the array fjac.

  iflag is an integer variable which can be used to terminate
    the execution of fdjac2. see description of fcn.

  epsfcn is an input variable used in determining a suitable
    step length for the forward-difference approximation. this
    approximation assumes that the relative errors in the
    functions are of the order of epsfcn. if epsfcn is less
    than the machine precision, it is assumed that the relative
    errors in the functions are of the order of the machine
    precision.

  wa is a work array of length m.

subprograms called

  user-supplied ...... fcn

  minpack-supplied ... dlamch

  fortran-supplied ... dabs,dmax1,dsqrt

argonne national laboratory. minpack project. march 1980.
burton s. garbow, kenneth e. hillstrom, jorge j. more

*/

typedef void (*fcn2_t)(int* m, int* n, double* x, double* fvec, int* flag);

void F77_NAME(fdjac2)(fcn2_t fcn,
                      int* m,
                      int* n,
                      double* x,
                      double* fvec,
                      double* fjac,
                      int* ldfjac,
                      int* iflag,
                      double* epsfcn,
                      double* wa);


/*
on entry

iflag=0-1  initialize on one subgradient (mu in)

iflag=2    "     "     "     "     "     "     "
           and strive to enter by priority the
           points of the previous corral at the
           beginning of the iterations.

iflag=3    initialize on the previous projection
           (with its corresponding corral)


****  on exit  *****

           iflag=0    normal end

                 1    old solution is already optimal

                 2    constraints non feasible

                 3    trying to enter a variable
                      that is already in the corral

                 4    starting to loop




print > 5    one prints final information


print > 6    one prints information at each iteration


print > 7    one prints also

         - at each iteration the choleski matrix
         - and the initial information such as (pi,pj) ...


*/

void F77_NAME(fprf2)(int* iflag,
                     int* ntot,
                     int* nv,
                     int* io,
                     double* zero,
                     double* s2,
                     double* eps,
                     double* al,
                     int* iprint,
                     double* u,
                     double* eta,
                     int* mm1,
                     int* jc,
                     int* ic,
                     double* r,
                     double* a,
                     double* e,
                     double* rr,
                     double* xpr,
                     double* y,
                     double* w1,
                     double* w2);


/*
this subroutine fills the data for fprf2
(scalar products and 2 linear constraints)

   from 1 to ntot +1 if iflag=0
   from nta+1 +1 to ntot +1 otherwise

   (the +1 is due to the gap, place first)

p contains the opposites of the gradients in a single file
-g(1), -g(2),..., -g(ntot) i.e. ntot*n coordinates

*/

void F77_NAME(fremf2)(prosca_t prosca,
                      int* iflag,
                      int* n,
                      int* ntot,
                      int* nta,
                      int* mm1,
                      double* p,
                      double* alfa,
                      double* e,
                      double* a,
                      double *r,
                      int* izs,
                      float* rzs,
                      double* dzs);


// End extern "C"
#ifdef __cplusplus
}
#endif


