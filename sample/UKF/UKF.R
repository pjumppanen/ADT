# -----------------------------------------------------------------------------
# Unscented Kalman Filter Example project based on by Jaroslaw Goslinski code in:
#
# https://github.com/jaroslav87/UKF-MNGM.git
#
# Companion article:
#
# https://jgoslinski.medium.com/the-unscented-kalman-filter-simply-the-best-python-code-5cd5ebaebf5f
# 
# -----------------------------------------------------------------------------
# Load the library
if (version$os == "mingw32")
{
  # Running in Windows - assume we have changed dir to the sample\Rosenbrock folder
  if (is.na(match("UKF",  attr(getLoadedDLLs(), "names"))))
  {
    if (version$arch == "i386")
    {
      dyn.load("../../objs/Win32/Debug/UKF.dll")

    } else
    {
      dyn.load("../../objs/x64/Debug/UKF.dll")
    }
  }

} else if (version$os == "cygwin")
{
  # Running in cygwin
  if (is.na(match("",  attr(getLoadedDLLs(), "names"))))
  {
    file.copy("../../objs/sample/UKF/.libs/cygUKF-0.dll", "../../objs/sample/UKF/.libs/UKF.dll", overwrite=TRUE)
    dyn.load("../../objs/sample/UKF/.libs/UKF.dll")
  }

} else
{
  # Running in Linux
  if (is.na(match("libUKF",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("../../objs/sample/UKF/.libs/libUKF.so")
  }
}


# include auto-generated interface code
source('UKF_R_interface.r', print.eval=TRUE)


n     <- 2
m     <- 2
kappa <- 0.0
alfa  <- 0.001
beta  <- 2.0

# create the object instance
UKF.Context <- UKF.create(n,m,kappa,alfa,beta)

A <- matrix(c(4, 2, 2,
              2, 3, 1,
              2, 1, 3), nrow=3, byrow=TRUE)

det(A)

L <- A * 0

UKF.choleskyDecomposition(UKF.Context, A, L, as.integer(3))

InvA <- A * 0

UKF.matrixInverseFromChol(UKF.Context, L, InvA, as.integer(3))

# initial x value
x_0    <- array(NA, n)
x_0[1] <- 0.1
x_0[2] <- 0.1

# generate model data
size_n <- 500

x <- array(NA, c(size_n, 2))
y <- array(NA, c(size_n, 2))
u <- array(rnorm(2 * size_n, 0., 1.0), c(size_n, 2))
v <- array(rnorm(2 * size_n, 0., 1.0), c(size_n, 2))

x[1,] <- x_0

for (i in 1:(size_n - 1))
{
  x[i+1,1] <- 0.5 * x[i,1] - 0.1 * x[i,2] + 0.7 * (x[i,1] / (1 + x[i,1] ** 2)) + 2.2 * cos(1.2 * (i - 1)) + u[i+1,1]
  x[i+1,2] <- 0.8 * x[i,2] - 0.2 * x[i,1] + 0.9 * (x[i,2] / (1 + x[i,2] ** 2)) + 2.4 * cos(2.2 * (i - 1)) + u[i+1,2]
  y[i+1,1] <- (x[i,1] * 2) / 9.0 + (x[i,2] * 2) / 7.0 + v[i+1,1]
  y[i+1,2] <- (x[i,1] * 2) / 6.0 + (x[i,2] * 2) / 2.0 + v[i+1,2]
}

UKF.resetUKF(UKF.Context, 0.1,  0.1, x_0)

timeUpdateInput         <- rep(0.0, n)
measurementUpdateInput  <- rep(0.0, m)
err_total               <- 0.0
est_state               <- array(0.0, c(size_n, n))
est_output              <- array(0.0, c(size_n, n))


# estimation loop
for (i in 1:size_n)
{
  timeUpdateInput[]      <- i - 1
  measurementUpdateInput <- x[i, ]

  # recursively go through time update and measurement correction
  UKF.timeUpdate(UKF.Context, timeUpdateInput)
  UKF.measurementUpdate(UKF.Context, measurementUpdateInput)

  err <- 0.0

  for (j in 1:n)
  {
    err <- err + (UKF.get.x_aposteriori(UKF.Context)[j-1] - x[i, j]) ** 2
  }

  est_state[i, 1]  <- UKF.get.x_aposteriori(UKF.Context)[0]
  est_state[i, 2]  <- UKF.get.x_aposteriori(UKF.Context)[1]
  est_output[i, 1] <- UKF.get.yi(UKF.Context)[0]
  est_output[i, 2] <- UKF.get.yi(UKF.Context)[1]

  err_total <- err_total + err
}

print(paste("total error:", err_total))

df <- data.frame(sample=c(1:size_n, 1:size_n, 1:size_n, 1:size_n), 
                 value=c(x[,1], est_state[,1], x[,2], est_state[,2]),
                 groups=c(rep("x1.original", size_n), rep("x1.estimate", size_n), rep("x2.original", size_n), rep("x2.estimate", size_n)))

print(ggplot(data=df, aes(x=sample, y=value, group=groups, color=groups)) +
             geom_line() +
             xlab('') + 
             ylab('') + 
             theme_bw() + 
             theme(legend.title=element_blank()))

print(ggplot(data=df, aes(x=sample, y=value, group=groups, color=groups)) +
             geom_line() +
             xlab('') + 
             ylab('') + 
             scale_x_continuous(limits=c(0, 100), expand=c(0, 0)) +
             theme_bw() + 
             theme(legend.title=element_blank()))

