###############################################################################
# Test minimisation code for ADT. 
###############################################################################
# Parameter declarations. Note that we need to explicitely make N integer
# because the C++ code takes an integer parameter, not a double. We also need
# to initialise X, Grad and Hessian to the correct size / shape as required
# by the problem. This initialisation needs to be done in the same scope as
# the call to nlminb().
N       <- as.integer(500)
StartX  <- rep(0,N)
Grad    <- rep(0,N)
Hessian <- array(0,dim=c(N,N))


# The true minimum
Correct <- rep(1,N)


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
source('Rd_R_interface.r', print.eval=TRUE)
source('RRd_R_interface.r', print.eval=TRUE)


# create the object instance
RRd.Context <- RRd.create(N)


# Objective function.
objFn <- function(X)
{
  return (Rd.nt.logLikelihood(RRd.Context, X))
}


# Gradient wrapper function. Note that Grad should be declared to the correct size
# in global scope.
gradFn <- function(X)
{
  RRd.nt.gradient(RRd.Context, X, Grad)

  return (Grad)
}


# Hessian wrapper function. Note that Hessian must be declared to the correct size
# in global scope.
hessianFn <- function(X)
{
  RRd.hessian(RRd.Context, X, Hessian)

  return (Hessian)
}

# Multithreaded hessian calculation
RRd.beginMultithreadedHessian(RRd.Context)

system.time(res<-nlminb(start = StartX,
                        objective = objFn,
                        gradient = gradFn,
                        hessian = hessianFn,
                        scale=1,
                        control=list(eval.max=100000,iter.max=10000,abs.tol=1e-18)))

RRd.endMultithreadedHessian(RRd.Context)
