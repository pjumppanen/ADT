require(Oarray)

Rb.destroy <- function(Context)
{
  return (.External('_Rb.destroy', Context))
}

Rb.create <- function(N)
{
  return (.External('_Rb.create', as.integer(N)))
}

Rb.get.N <- function(Context)
{
  return (.External('_Rb.get.N', Context))
}

Rb.set.N <- function(Context, Arg)
{
  return (.External('_Rb.set.N', Context, as.integer(Arg)))
}

Rb.rosenbrock <- function(Context, X)
{
  return (.External('_Rb.rosenbrock', Context, X))
}

Rb.nt.rosenbrock <- function(Context, X)
{
  return (.External('_Rb.nt.rosenbrock', Context, X))
}

Rb.ROSENBROCK_BX <- function(Context, X, xb1_x, rosenbrockb1_x)
{
  return (.External('_Rb.ROSENBROCK_BX', Context, X, xb1_x, rosenbrockb1_x))
}

Rb.nt.ROSENBROCK_BX <- function(Context, X, xb1_x, rosenbrockb1_x)
{
  return (.External('_Rb.nt.ROSENBROCK_BX', Context, X, xb1_x, rosenbrockb1_x))
}

Rb.ROSENBROCK_BX_DX <- function(Context, X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x)
{
  return (.External('_Rb.ROSENBROCK_BX_DX', Context, X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x))
}

Rb.nt.ROSENBROCK_BX_DX <- function(Context, X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x)
{
  return (.External('_Rb.nt.ROSENBROCK_BX_DX', Context, X, xd2_x, xb1_x, xb1_xd2_x, rosenbrockb1_x))
}

