###############################################################################
# Test minimisation code for ADT. This mimimisation problem is the Rosenbrock
# bananna function generalised to N dimensions.
###############################################################################


# Parameter declarations. Note that we need to explicitely make N integer
# because the C++ code takes an integer parameter, not a double. We also need
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
  if (is.na(match("Rosenbrock",  attr(getLoadedDLLs(), "names"))))
  {
    if (version$arch == "i386")
    {
      dyn.load("../../objs/Win32/Debug/Rosenbrock.dll")

    } else
    {
      dyn.load("../../objs/x64/Debug/Rosenbrock.dll")
    }
  }

} else if (version$os == "cygwin")
{
  # Running in cygwin
  if (is.na(match("",  attr(getLoadedDLLs(), "names"))))
  {
    file.copy("../../objs/sample/Rosenbrock/.libs/cygRosenbrock-0.dll", "../../objs/sample/Rosenbrock/.libs/Rosenbrock.dll", overwrite=TRUE)
    dyn.load("../../objs/sample/Rosenbrock/.libs/Rosenbrock.dll")
  }

} else
{
  # Running in Linux
  if (is.na(match("libRosenbrock",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("../../objs/sample/Rosenbrock/.libs/libRosenbrock.so")
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
CaseNames<-c("All R based", "C++ objective", "C++ objective - transposing", "C++ objective and gradient", "C++ objective and gradient - transposing", "C++ objective, gradient and hessian", "C++ objective, gradient and hessian - transposing", "C++ objective and gradient minimised in C++")


# Data frame to store results in
Results<-data.frame(case=CaseNames,
                    objective=rep(0,8),
                    RMS.error=rep(0,8),
                    convergence=rep(0,8),
                    time.taken=rep(0,8),
                    iterations=rep(0,8),
                    fn.evaluations=rep(0,8),
                    grad.evaluations=rep(0,8),
                    message=rep(0,8))


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

# Do mimimisation all in c++ using BFGS minimiser vmmin()
MinRes <- rep(0,RRb.N)
maxit <- as.integer(250)
fncount <- as.integer(1)
grcount <- as.integer(1)
status <- as.integer(0)

timeTaken <- system.time(RRb.minimise(RRb.Context, StartX, MinRes, maxit, fncount, grcount, status))

Results$time.taken[8]<-timeTaken[["elapsed"]]
Results$RMS.error[8]<-(sum((Correct - MinRes)^2))^0.5
Results$convergence[8]<-status
Results$iterations[8]<-NA
Results$fn.evaluations[8]<-fncount
Results$grad.evaluations[8]<-grcount
Results$message[8]<-""

# Print the results
writeLines(c("Comparison of minimisation run times and performance for different ",
             "implementations of the Rosenbrock minimisation problem with ",
             paste(RRb.N, "parameters. Minimisation performed using nlminb except C++"),
             "case which uses the BFGS minimiser vmmin()."))
print(Results)
