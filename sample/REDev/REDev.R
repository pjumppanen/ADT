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
      dyn.load("../../objs/x64/Debug/ScilabOptim.dll")
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
nMaxDirs <- 10
Db.Context <- Dd.create(Y, NR, NP, nMaxDirs)

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
OuterGrad <- array(as.double(NA), dim=c(NP))


# Inner Objective function.
outerObjFn <- function(par)
{
  InnerPar <<- par
  innerRes <- nlminb(start = reHat,
                     objective = innerObjFn,
                     gradient = innerGradFn)

  reHat <<- innerRes$par

  return (Dc.nt.laplace(Db.Context, 
                        reHat, 
                        par))
}

outerObj2Fn <- function(par)
{
  print("ObjFn Start\n")
  
  Result <- Dc.nt.solveAndLaplace(Db.Context, par)
  
  print("ObjFn End\n")

  return (Result)
}

# Inner Gradient function. Note that InnerGrad should be declared with the
# correct size in global scope.
outerGradFn <- function(par)
{
  InnerPar <<- par
  innerRes <- nlminb(start = reHat,
                     objective = innerObjFn,
                     gradient = innerGradFn)

  reHat <<- innerRes$par

  Dd.nt.gradientLaplacePar(Db.Context, 
                          reHat, 
                          par, 
                          OuterGrad)

  return (OuterGrad)
}

outerGrad2Fn <- function(par)
{
  print("GradFn Start\n")
  
  Dd.nt.solveAndGradientLaplacePar(Db.Context, 
                                   par, 
                                   OuterGrad)

  print("GradFn End\n")

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
system.time(innerRes <- nlminb(start = reHat,
                   objective = innerObjFn,
                   gradient = innerGradFn,
#                   hessian = innerHessianFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18)))

system.time(innerRes <- nlminb(start = innerRes$par,
                   objective = innerObjFn,
                   gradient = innerGradFn,
                   hessian = innerHessianFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18)))

system.time(innerRes2 <- nlminb(start = reHat,
                   objective = innerObjFn,
                   gradient = innerGradFn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-18)))

system.time(innerRes2 <- nlminb(start = reHat,
                   objective = innerObjFn,
                   gradient = innerGradFn))
#RRd.endMultithreadedHessian(RRd.Context)

reHat <- innerRes$par

pars <- unlist(parameters)
system.time(OuterRes <- nlminb(start = pars,
                   objective = outerObjFn,
                   gradient = outerGradFn))

Dc.nt.setInitialRE(Db.Context, reHat)
system.time(OuterRes2 <- nlminb(start = pars,
                   objective = outerObj2Fn,
                   gradient = outerGrad2Fn))


Dc.nt.setInitialRE(Db.Context, reHat)
system.time(OuterRes2 <- nlminb(start = pars,
                   objective = outerObj2Fn,
                   gradient = outerGrad2Fn,
                   scale = 1,
                   control = list(eval.max=100000,iter.max=10000,abs.tol=1e-8)))



Dc.set.nt.ReHat(Db.Context, reHat)
Dc.nt.solveAndLaplace(Db.Context, pars)
Dc.get.nt.ReHat(Db.Context)


newton(eval(random.start),fn=f0,gr=function(x)f0(x,order=1),
      #              he=function(x)f0(x,order=2))


test <- newton(par = reHat,
               fn = innerObjFn,
               gr = innerGradFn,
               he = innerHessianFn)

  M <- new("dsTMatrix",
           i = as.integer(attr(ADHess$ptr,"i")),
           j = as.integer(attr(ADHess$ptr,"j")),
           x = ev(obj$env$par), Dim = c(n,n), uplo = "L")

nDirs <- 5           
Dirs  <- array(as.integer(c(1,2,3,4,5)), dim=c(nDirs))
Diff  <- array(as.double(NA), dim=c(NR,nDirs))

Db.nt.secondDiffMultiRE(Db.Context,
                        reHat, 
                        InnerPar,
                        Dirs,
                        Diff,
                        as.integer(nDirs))

nDirs <- 1
Dirs  <- array(as.integer(c(2)), dim=c(nDirs))
Diff  <- array(as.double(NA), dim=c(NR,nDirs))

Db.nt.secondDiffMultiRE(Db.Context,
                        reHat, 
                        InnerPar,
                        Dirs,
                        Diff,
                        as.integer(nDirs))

nDirs <- 3
Dirs  <- array(as.integer(c(1,2,3)), dim=c(nDirs))
Diff  <- array(as.double(NA), dim=c(nDirs,NR))

system.time(Db.nt.secondDiffMultiRE(Db.Context,
                        reHat, 
                        InnerPar,
                        Dirs,
                        Diff,
                        as.integer(nDirs)))

system.time(innerHessianFn(reHat))

# check
InnerHessian[1:3,1:10]
Diff[,1:10]
InnerHessian[1:3,1:10]-Diff[,1:10]


system.time(sapply(1:100, function(x){Db.nt.secondDiffMultiRE(Db.Context,
                                                              reHat, 
                                                              InnerPar,
                                                              Dirs,
                                                              Diff,
                                                              as.integer(nDirs))}))

system.time(sapply(1:100, function(x){innerHessianFn(reHat);return(0)}))

