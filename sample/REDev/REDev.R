###############################################################################
# Test minimisation code for ADT. 
###############################################################################

# Load the library
if (version$os == "mingw32")
{
  # Running in Windows - assume we have changed dir to the sample\Rosenbrock folder
  if (is.na(match("REDev",  attr(getLoadedDLLs(), "names"))))
  {
    if (version$arch == "i386")
    {
      dyn.load("../../objs/Win32/Debug/REDev.dll")

    } else
    {
      dyn.load("../../objs/x64/Debug/REDev.dll")
    }
  }

} else if (version$os == "cygwin")
{
  # Running in cygwin
  if (is.na(match("",  attr(getLoadedDLLs(), "names"))))
  {
    file.copy("../../objs/sample/REDev/.libs/cygREDev-0.dll", "../../objs/sample/REDev/.libs/REDev.dll", overwrite=TRUE)
    dyn.load("../../objs/sample/REDev/.libs/REDev.dll")
  }

} else
{
  # Running in Linux
  if (is.na(match("libREDev",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("../../objs/sample/REDev/.libs/libREDev.so")
  }
}


# include auto-generated interface code
source('Da_R_interface.r', print.eval=TRUE)
source('Db_R_interface.r', print.eval=TRUE)
source('Dc_R_interface.r', print.eval=TRUE)
source('Dd_R_interface.r', print.eval=TRUE)


Y <- scan("TMBex/thetalog/thetalog.dat", skip=3, quiet=TRUE)
X <- Y * 0

# Parameter initial guess
logr0     <- 0
logtheta  <- 0
logK      <- 6
logQ      <- 0
logR      <- 0

parameters <- list(logr0, logtheta, logK, logQ, logR)

NR <- length(Y)
NP <- length(parameters)

# create the object instance
Db.Context <- Dd.create(Y, NR, NP)

# -----------------------------------------------------------------------------
# Do determinant check
# -----------------------------------------------------------------------------
A <- matrix(c(4, 2, 2,
              2, 3, 1,
              2, 1, 3), nrow=3, byrow=TRUE)

det(A)

L <- A * 0

Da.choleskyDecomposition(Db.Context, A, L, as.integer(3))

# should be null matrix
t(L) - chol(A)

# should be null
det(A) - exp(Da.logDeterminantFromChol(Db.Context, L, as.integer(3)))

# -----------------------------------------------------------------------------
# Do Inverse check
# -----------------------------------------------------------------------------
RInv <- solve(A)
RInv[upper.tri(RInv)] <- 0.0

Inv <- A * NA

Da.matrixInverseFromChol(Db.Context, L, Inv, as.integer(3))

# should be null
RInv - Inv


# -----------------------------------------------------------------------------
# Support for Outer Minimisation
# -----------------------------------------------------------------------------
OuterGrad             <- array(as.double(NA), dim=c(NP))
Cholesky              <- array(as.double(NA), dim=c(NR,NR))
InvHessian            <- array(as.double(NA), dim=c(NR,NR))
LaplaceGradRE         <- array(as.double(NA), dim=c(NR))
LaplaceGradPar        <- array(as.double(NA), dim=c(NP))
ObjReParXCovar        <- array(as.double(NA), dim=c(NP,NR))
HessianRE_LowerLimit  <- array(as.integer(NA), dim=c(NR))
HessianRE_UpperLimit  <- array(as.integer(NA), dim=c(NR))
CoVarPar_LowerLimit   <- array(as.integer(NA), dim=c(NR))
CoVarPar_UpperLimit   <- array(as.integer(NA), dim=c(NR))


# Inner Objective function.
outerObjFn <- function(par)
{
  return (Dc.nt.laplace(Db.Context, 
                        reHat, 
                        par, 
                        InnerHessian, 
                        Cholesky))
}

# Inner Gradient function. Note that InnerGrad should be declared with the
# correct size in global scope.
outerGradFn <- function(par)
{
  Dd.nt.gradientLaplacePar(Db.Context, 
                          reHat, 
                          par, 
                          InnerHessian, 
                          Cholesky,
                          InvHessian, 
                          LaplaceGradRE, 
                          LaplaceGradPar, 
                          ObjReParXCovar,
                          OuterGrad)

  return (OuterGrad)
}


# -----------------------------------------------------------------------------
# Support for Inner Minimisation
# -----------------------------------------------------------------------------
InnerGrad     <- array(as.double(NA), dim=c(NR))
InnerHessian  <- array(as.double(NA), dim=c(NR,NR))
InnerPar      <- as.double(unlist(parameters))

# Inner Objective function.
innerObjFn <- function(re)
{
  return (Da.nt.logLikelihood(Db.Context, re, InnerPar))
}

# Inner Gradient function. Note that InnerGrad should be declared with the
# correct size in global scope.
innerGradFn <- function(re)
{
  Db.nt.gradientRE(Db.Context, re, InnerPar, InnerGrad)

  return (InnerGrad)
}

# Inner Hessian function. Note that Hessian must be declared with the
# correct size in global scope.
innerHessianFn <- function(re)
{
  Dc.nt.hessianRE(Db.Context, re, InnerPar, InnerHessian)

  return (InnerHessian)
}


reHat <- X

# -----------------------------------------------------------------------------
# Do Inner Minimisation
# -----------------------------------------------------------------------------
# Find the random effects (re) that minimize the likelihood given a fixed set
# of parameters (par).
# -----------------------------------------------------------------------------



# Multithreaded hessian calculation
#Db.beginMultithreadedHessian(Db.Context)
innerRes <- nlminb(start = reHat,
                   objective = innerObjFn,
                   gradient = innerGradFn,
                   hessian = innerHessianFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18))

#RRd.endMultithreadedHessian(RRd.Context)

reHat <- innerRes$par


reb1_re       <- reHat * 0
hessianb1_re  <- InnerHessian * 0
choleskyb1_re <- Cholesky * 0
laplaceb1_re  <- 1.0

Dc.nt.LAPLACE_BRE(Db.Context, 
                  reHat, 
                  reb1_re, 
                  InnerPar, 
                  InnerHessian, 
                  hessianb1_re, 
                  Cholesky, 
                  choleskyb1_re, 
                  laplaceb1_re)


parb2_par      <- InnerPar * 0;
hessianb2_par  <- InnerHessian * 0;
choleskyb2_par <- InnerHessian * 0;
laplaceb2_par  <- 1.0                  

Dc.nt.LAPLACE_BPAR(Db.Context, 
                   reHat, 
                   InnerPar, 
                   parb2_par, 
                   InnerHessian, 
                   hessianb2_par, 
                   Cholesky, 
                   choleskyb2_par, 
                   laplaceb2_par)

Dc.nt.covarRE_Par(Db.Context, 
                   reHat, 
                   InnerPar, 
                   ObjReParXCovar);

LaplaceGrad <- InnerPar * 0

Dd.nt.gradientLaplacePar(Db.Context, 
                         reHat, 
                         InnerPar, 
                         InnerHessian, 
                         Cholesky,
                         InvHessian, 
                         LaplaceGradRE, 
                         LaplaceGradPar, 
                         ObjReParXCovar,
                         LaplaceGrad)

outerGradFn(InnerPar)


pars <- unlist(parameters)
OuterRes <- nlminb(start = pars,
                   objective = outerObjFn,
                   gradient = outerGradFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18))

OuterRes <- nlminb(start = pars,
                   objective = outerObjFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18))

