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

# ----------------------------------------------------------------------------

model_output <- function(x, t)
{
  y    <- array(data=NA, dim=2)
  y[1] <- (x[1] * 2) / 9.0 + (x[2] * 2) / 7.0;
  y[2] <- (x[1] * 2) / 6.0 + (x[2] * 2) / 2.0;

  return (y)
}

# ----------------------------------------------------------------------------

model_state <- function(xp, t)
{
  x    <- xp * 0
  x[1] <- 0.5 * xp[1] - 0.1 * xp[2] + 0.7 * (xp[1] / (1.0 + xp[1] * xp[1])) + 2.2 * cos(1.2 * (t - 1));
  x[2] <- 0.8 * xp[2] - 0.2 * xp[1] + 0.9 * (xp[2] / (1.0 + xp[2] * xp[2])) + 2.4 * cos(2.2 * (t - 1));

  return (x)
}

# ----------------------------------------------------------------------------

# create the object instance
UKF.Context <- UKF.create(n,m,kappa,alfa,beta, model_output, environment(), F, model_state, environment(), F)

# initial x value
x_0    <- array(NA, n)
y_0    <- array(NA, m)
x_0[1] <- 0.1
x_0[2] <- 0.1
y_0[1] <- 0.0
y_0[2] <- 0.0

# generate model data
size_n <- 500

x <- array(NA, c(size_n, 2))
y <- array(NA, c(size_n, 2))
u <- array(rnorm(2 * size_n, 0., 1.0), c(size_n, 2))
v <- array(rnorm(2 * size_n, 0., 1.0), c(size_n, 2))

x[1,] <- x_0
y[1,] <- y_0

for (i in 2:size_n)
{
  w       <- c(i,i)
  x[i,] <- model_state(x[i-1,], i) + u[i,]
  y[i,] <- model_output(x[i-1,], i) + v[i,]
}

# reset and run the UKF
UKF.resetUKF(UKF.Context, 0.1,  0.1, x_0)

err_total               <- 0.0
est_state               <- array(0.0, c(size_n, n))
est_output              <- array(0.0, c(size_n, n))

# estimation loop
for (i in 1:size_n)
{
  # recursively go through time update and measurement correction
  UKF.timeUpdate(UKF.Context, i)
  UKF.measurementUpdate(UKF.Context, y[i, ])

  err <- 0.0

  for (j in 1:n)
  {
    err <- err + (UKF.get.x_aposteriori(UKF.Context)[j] - x[i, j]) ** 2
  }

  est_state[i, 1]  <- UKF.get.x_aposteriori(UKF.Context)[1]
  est_state[i, 2]  <- UKF.get.x_aposteriori(UKF.Context)[2]
  est_output[i, 1] <- UKF.get.yi(UKF.Context)[1]
  est_output[i, 2] <- UKF.get.yi(UKF.Context)[2]

  err_total <- err_total + err
}

print(paste("total error:", err_total))

# plot results
require(ggplot2)

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
