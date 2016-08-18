###############################################################################
# Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
# bananna function generalised to N dimensions.
###############################################################################


# Parameter declarations. Note that we need to explicitely make N integer
# because the Pascal code takes an integer parameter, not a double. We also need
# to initialise X, Grad and Hessian to the correct size / shape as required
# by the problem. This initialisation needs to be done in the same scope as
# the call to nlminb().
RRb.N <- as.integer(150)
StartX <- rep(0,RRb.N)
Grad <- rep(0,RRb.N)
Hessian <- array(0,dim=c(RRb.N,RRb.N))


# The true minimum of the Rosenbrock function
Correct <- rep(1,RRb.N)


# R based objective function.
Rosenbrock<-function(Params)
{
  Sum <- 0.0

  for (ix in seq(1, RRb.N / 2))
  {
    p1 <- Params[2 * ix - 1]
    p2 <- Params[2 * ix]
    f1 <- (p1 * p1 - p2)
    f1 <- 100 * f1 * f1
    f2 <- (p1 - 1)
    f2 <- f2 * f2
    Sum <- Sum + f1 + f2
  }

  return (Sum)
}


# Load the library
if (version$os == "mingw32")
{
  # Running in Windows - assume we have changed dir to the sample\Rosenbrock folder
  if (is.na(match("RosenbrockPas",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("./RosenbrockPas.dll")
  }

} else
{
  # Running in Linux
  if (is.na(match("libRosenbrockPas",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("./libRosenbrockPas.so")
  }
}


# include auto-generated interface code
source('Rb_R_interface.r', print.eval=TRUE)
source('RRb_R_interface.r', print.eval=TRUE)


# create the object instance
RRb.Context <- RRb.create(RRb.N)


# Objective function.
objFn <- function(X)
{
  return (Rb.nt.rosenbrock(RRb.Context, X))
}
# transposing version.
objFn.tr <- function(X)
{
  return (Rb.rosenbrock(RRb.Context, X))
}


# Gradient wrapper function. Note that Grad should be declared to the correct size
# in global scope.
gradFn <- function(X)
{
  Rb.nt.ROSENBROCK_BX(RRb.Context, X, Grad, as.double(1.0))

  return (Grad)
}
# transposing version.
gradFn.tr <- function(X)
{
  Rb.ROSENBROCK_BX(RRb.Context, X, Grad, as.double(1.0))

  return (Grad)
}


# Hessian wrapper function. Note that Hessian must be declared to the correct size
# in global scope.
hessianFn <- function(X)
{
  RRb.nt.hessian(RRb.Context, X, Hessian)

  return (Hessian)
}
# transposing version.
hessianFn.tr <- function(X)
{
  RRb.hessian(RRb.Context, X, Hessian)

  return (Hessian)
}


# Descriptive name for each test case
CaseNames<-c("All R based", "Pascal objective", "Pascal objective - transposing", "Pascal objective and gradient", "Pascal objective and gradient - transposing", "Pascal objective, gradient and hessian", "Pascal objective, gradient and hessian - transposing")


# Data frame to store results in
Results<-data.frame(case=CaseNames,
                    objective=rep(0,7),
                    RMS.error=rep(0,7),
                    convergence=rep(0,7),
                    time.taken=rep(0,7),
                    iterations=rep(0,7),
                    fn.evaluations=rep(0,7),
                    grad.evaluations=rep(0,7),
                    message=rep(0,7))


# Calculate all results
objFns      <- list(Rosenbrock, objFn, objFn.tr,  objFn,  objFn.tr,     objFn,     objFn.tr)
gradientFns <- list(      NULL,  NULL,     NULL, gradFn, gradFn.tr,    gradFn,    gradFn.tr)
hessianFns  <- list(      NULL,  NULL,     NULL,   NULL,      NULL, hessianFn, hessianFn.tr)


for (cn in 1:7)
{
  print(paste("Minimising '", CaseNames[cn], "' solution.", sep = ""))
  flush.console()

  Results$time.taken[cn]<-as.double(system.time(res<-nlminb(start = StartX,
                                                            objective = objFns[[cn]],
                                                            gradient = gradientFns[[cn]],
                                                            hessian = hessianFns[[cn]],
                                                            scale=1,
                                                            control=list(eval.max=100000,iter.max=10000)))[3])

  Results$RMS.error[cn]<-(sum((Correct - res$par)^2))^0.5
  Results$convergence[cn]<-res$convergence
  Results$iterations[cn]<-res$iterations
  Results$fn.evaluations[cn]<-as.integer(res$evaluations[1])
  Results$grad.evaluations[cn]<-as.integer(res$evaluations[2])
  Results$message[cn]<-res$message
}


# Print the results
print(c("Comparison of minimisation run times and performance for different ",
        "implementations of the Rosenbrock minimisation problem with ",
        paste(RRb.N, "parameters. Minimisation performed using nlminb. ")))
print(Results)
