require(Oarray)

RRb.destroy <- function(Context)
{
  return (.Call('_RRb.destroy', Context))
}

RRb.create <- function(N)
{
  return (.Call('_RRb.create', as.integer(N)))
}

RRb.hessian <- function(Context, pX, pHessian)
{
  return (.Call('_RRb.hessian', Context, pX, pHessian))
}

RRb.nt.hessian <- function(Context, pX, pHessian)
{
  return (.Call('_RRb.nt.hessian', Context, pX, pHessian))
}

RRb.get.lxb1_x <- function(Context, ...)
{
  return (.Call('_RRb.get.lxb1_x', Context, list(...)))
}

RRb.set.lxb1_x <- function(Context, Arg, ...)
{
  return (.Call('_RRb.set.lxb1_x', Context, as.double(Arg), list(...)))
}

RRb.get.nt.lxb1_x <- function(Context, ...)
{
  return (.Call('_RRb.get.nt.lxb1_x', Context, list(...)))
}

RRb.set.nt.lxb1_x <- function(Context, Arg, ...)
{
  return (.Call('_RRb.set.nt.lxb1_x', Context, as.double(Arg), list(...)))
}

RRb.get.lxd2_x <- function(Context, ...)
{
  return (.Call('_RRb.get.lxd2_x', Context, list(...)))
}

RRb.set.lxd2_x <- function(Context, Arg, ...)
{
  return (.Call('_RRb.set.lxd2_x', Context, as.double(Arg), list(...)))
}

RRb.get.nt.lxd2_x <- function(Context, ...)
{
  return (.Call('_RRb.get.nt.lxd2_x', Context, list(...)))
}

RRb.set.nt.lxd2_x <- function(Context, Arg, ...)
{
  return (.Call('_RRb.set.nt.lxd2_x', Context, as.double(Arg), list(...)))
}

RRb.minimise <- function(Context, pS, pR, maxit, fncount, grcount, status)
{
  return (.Call('_RRb.minimise', Context, pS, pR, maxit, fncount, grcount, status))
}

RRb.nt.minimise <- function(Context, pS, pR, maxit, fncount, grcount, status)
{
  return (.Call('_RRb.nt.minimise', Context, pS, pR, maxit, fncount, grcount, status))
}

