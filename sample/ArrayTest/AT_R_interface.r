require(Oarray)

AT.destroy <- function(Context)
{
  return (.Call('_AT.destroy', Context))
}

AT.create <- function(ix, iy, A1_I, A1_D, A2_IA, A2_IB)
{
  return (.Call('_AT.create', as.integer(ix), as.integer(iy), as.integer(A1_I), as.double(A1_D), as.integer(A2_IA), as.integer(A2_IB)))
}

AT.get.A1_D <- function(Context, ...)
{
  return (.Call('_AT.get.A1_D', Context, list(...)))
}

AT.set.A1_D <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.A1_D', Context, as.double(Arg), list(...)))
}

AT.get.nt.A1_D <- function(Context, ...)
{
  return (.Call('_AT.get.nt.A1_D', Context, list(...)))
}

AT.set.nt.A1_D <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.nt.A1_D', Context, as.double(Arg), list(...)))
}

AT.get.A1_I <- function(Context, ...)
{
  return (.Call('_AT.get.A1_I', Context, list(...)))
}

AT.set.A1_I <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.A1_I', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A1_I <- function(Context, ...)
{
  return (.Call('_AT.get.nt.A1_I', Context, list(...)))
}

AT.set.nt.A1_I <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.nt.A1_I', Context, as.integer(Arg), list(...)))
}

AT.get.A2_IA <- function(Context, ...)
{
  return (.Call('_AT.get.A2_IA', Context, list(...)))
}

AT.set.A2_IA <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.A2_IA', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A2_IA <- function(Context, ...)
{
  return (.Call('_AT.get.nt.A2_IA', Context, list(...)))
}

AT.set.nt.A2_IA <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.nt.A2_IA', Context, as.integer(Arg), list(...)))
}

AT.get.A2_IB <- function(Context, ...)
{
  return (.Call('_AT.get.A2_IB', Context, list(...)))
}

AT.set.A2_IB <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.A2_IB', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A2_IB <- function(Context, ...)
{
  return (.Call('_AT.get.nt.A2_IB', Context, list(...)))
}

AT.set.nt.A2_IB <- function(Context, Arg, ...)
{
  return (.Call('_AT.set.nt.A2_IB', Context, as.integer(Arg), list(...)))
}

AT.boundsCheckTest <- function(Context, X)
{
  return (.Call('_AT.boundsCheckTest', Context, X))
}

AT.nt.boundsCheckTest <- function(Context, X)
{
  return (.Call('_AT.nt.boundsCheckTest', Context, X))
}

AT.GLOBAL_SUM_BX <- function(Context, X, xb1_x, nBase, nCount, global_sumb1_x)
{
  return (.Call('_AT.GLOBAL_SUM_BX', Context, X, xb1_x, nBase, nCount, global_sumb1_x))
}

AT.nt.GLOBAL_SUM_BX <- function(Context, X, xb1_x, nBase, nCount, global_sumb1_x)
{
  return (.Call('_AT.nt.GLOBAL_SUM_BX', Context, X, xb1_x, nBase, nCount, global_sumb1_x))
}

AT.IFTEST_BX <- function(Context, X, xb5_x, iftestb5_x)
{
  return (.Call('_AT.IFTEST_BX', Context, X, xb5_x, iftestb5_x))
}

AT.nt.IFTEST_BX <- function(Context, X, xb5_x, iftestb5_x)
{
  return (.Call('_AT.nt.IFTEST_BX', Context, X, xb5_x, iftestb5_x))
}

AT.get.ix <- function(Context)
{
  return (.Call('_AT.get.ix', Context))
}

AT.set.ix <- function(Context, Arg)
{
  return (.Call('_AT.set.ix', Context, as.integer(Arg)))
}

AT.get.iy <- function(Context)
{
  return (.Call('_AT.get.iy', Context))
}

AT.set.iy <- function(Context, Arg)
{
  return (.Call('_AT.set.iy', Context, as.integer(Arg)))
}

AT.POLYB_BX <- function(Context, X, xb3_x, polybb3_x)
{
  return (.Call('_AT.POLYB_BX', Context, X, xb3_x, polybb3_x))
}

AT.nt.POLYB_BX <- function(Context, X, xb3_x, polybb3_x)
{
  return (.Call('_AT.nt.POLYB_BX', Context, X, xb3_x, polybb3_x))
}

AT.POLYB_BX0 <- function(Context, X, xb5_x, polybb5_x)
{
  return (.Call('_AT.POLYB_BX0', Context, X, xb5_x, polybb5_x))
}

AT.nt.POLYB_BX0 <- function(Context, X, xb5_x, polybb5_x)
{
  return (.Call('_AT.nt.POLYB_BX0', Context, X, xb5_x, polybb5_x))
}

AT.polySumA <- function(Context, X)
{
  return (.Call('_AT.polySumA', Context, X))
}

AT.nt.polySumA <- function(Context, X)
{
  return (.Call('_AT.nt.polySumA', Context, X))
}

AT.POLYSUMA_BX <- function(Context, X, xb2_x, polysumab2_x)
{
  return (.Call('_AT.POLYSUMA_BX', Context, X, xb2_x, polysumab2_x))
}

AT.nt.POLYSUMA_BX <- function(Context, X, xb2_x, polysumab2_x)
{
  return (.Call('_AT.nt.POLYSUMA_BX', Context, X, xb2_x, polysumab2_x))
}

AT.polySumB <- function(Context, X)
{
  return (.Call('_AT.polySumB', Context, X))
}

AT.nt.polySumB <- function(Context, X)
{
  return (.Call('_AT.nt.polySumB', Context, X))
}

AT.POLYSUMB_BX <- function(Context, X, xb3_x, polysumbb3_x)
{
  return (.Call('_AT.POLYSUMB_BX', Context, X, xb3_x, polysumbb3_x))
}

AT.nt.POLYSUMB_BX <- function(Context, X, xb3_x, polysumbb3_x)
{
  return (.Call('_AT.nt.POLYSUMB_BX', Context, X, xb3_x, polysumbb3_x))
}

AT.polySumC <- function(Context, X)
{
  return (.Call('_AT.polySumC', Context, X))
}

AT.nt.polySumC <- function(Context, X)
{
  return (.Call('_AT.nt.polySumC', Context, X))
}

AT.POLYSUMC_BX <- function(Context, X, xb4_x, polysumcb4_x)
{
  return (.Call('_AT.POLYSUMC_BX', Context, X, xb4_x, polysumcb4_x))
}

AT.nt.POLYSUMC_BX <- function(Context, X, xb4_x, polysumcb4_x)
{
  return (.Call('_AT.nt.POLYSUMC_BX', Context, X, xb4_x, polysumcb4_x))
}

AT.sum <- function(Context, X)
{
  return (.Call('_AT.sum', Context, X))
}

AT.nt.sum <- function(Context, X)
{
  return (.Call('_AT.nt.sum', Context, X))
}

AT.SUM_BX <- function(Context, X, xb1_x, sumb1_x)
{
  return (.Call('_AT.SUM_BX', Context, X, xb1_x, sumb1_x))
}

AT.nt.SUM_BX <- function(Context, X, xb1_x, sumb1_x)
{
  return (.Call('_AT.nt.SUM_BX', Context, X, xb1_x, sumb1_x))
}

AT.sumA1_D <- function(Context)
{
  return (.Call('_AT.sumA1_D', Context))
}

AT.nt.sumA1_D <- function(Context)
{
  return (.Call('_AT.nt.sumA1_D', Context))
}

AT.test_one_if <- function(Context, v)
{
  return (.Call('_AT.test_one_if', Context, v))
}

AT.nt.test_one_if <- function(Context, v)
{
  return (.Call('_AT.nt.test_one_if', Context, v))
}

AT.TEST_ONE_IF_BV <- function(Context, v, vb7_v, test_one_ifb7_v)
{
  return (.Call('_AT.TEST_ONE_IF_BV', Context, v, vb7_v, test_one_ifb7_v))
}

AT.nt.TEST_ONE_IF_BV <- function(Context, v, vb7_v, test_one_ifb7_v)
{
  return (.Call('_AT.nt.TEST_ONE_IF_BV', Context, v, vb7_v, test_one_ifb7_v))
}

AT.TEST_ONE_IF_DV <- function(Context, v, vd6_v, test_one_if)
{
  return (.Call('_AT.TEST_ONE_IF_DV', Context, v, vd6_v, test_one_if))
}

AT.nt.TEST_ONE_IF_DV <- function(Context, v, vd6_v, test_one_if)
{
  return (.Call('_AT.nt.TEST_ONE_IF_DV', Context, v, vd6_v, test_one_if))
}

AT.test_one_if_internal <- function(Context, v)
{
  return (.Call('_AT.test_one_if_internal', Context, v))
}

AT.nt.test_one_if_internal <- function(Context, v)
{
  return (.Call('_AT.nt.test_one_if_internal', Context, v))
}

AT.TEST_ONE_IF_INTERNAL_BV <- function(Context, v, vb9_v, test_one_if_internalb9_v)
{
  return (.Call('_AT.TEST_ONE_IF_INTERNAL_BV', Context, v, vb9_v, test_one_if_internalb9_v))
}

AT.nt.TEST_ONE_IF_INTERNAL_BV <- function(Context, v, vb9_v, test_one_if_internalb9_v)
{
  return (.Call('_AT.nt.TEST_ONE_IF_INTERNAL_BV', Context, v, vb9_v, test_one_if_internalb9_v))
}

AT.TEST_ONE_IF_INTERNAL_DV <- function(Context, v, vd8_v, test_one_if_internal)
{
  return (.Call('_AT.TEST_ONE_IF_INTERNAL_DV', Context, v, vd8_v, test_one_if_internal))
}

AT.nt.TEST_ONE_IF_INTERNAL_DV <- function(Context, v, vd8_v, test_one_if_internal)
{
  return (.Call('_AT.nt.TEST_ONE_IF_INTERNAL_DV', Context, v, vd8_v, test_one_if_internal))
}

