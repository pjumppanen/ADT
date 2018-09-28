require(Oarray)

AT.destroy <- function(Context)
{
  return (.External('_AT.destroy', Context))
}

AT.create <- function(ix, iy, A1_I, A1_D, A2_IA, A2_IB, A2_DA, A2_LB, A2_C, A2_UC, A2_B, SingularBool, SingularLongbool)
{
  return (.External('_AT.create', as.integer(ix), as.integer(iy), as.integer(A1_I), as.double(A1_D), as.integer(A2_IA), as.integer(A2_IB), as.double(A2_DA), as.logical(A2_LB), as.raw(A2_C), as.raw(A2_UC), as.raw(A2_B), as.raw(SingularBool), as.logical(SingularLongbool)))
}

AT.get.A1_D <- function(Context, ...)
{
  return (.External('_AT.get.A1_D', Context, list(...)))
}

AT.set.A1_D <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A1_D', Context, as.double(Arg), list(...)))
}

AT.get.nt.A1_D <- function(Context, ...)
{
  return (.External('_AT.get.nt.A1_D', Context, list(...)))
}

AT.set.nt.A1_D <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A1_D', Context, as.double(Arg), list(...)))
}

AT.get.A1_I <- function(Context, ...)
{
  return (.External('_AT.get.A1_I', Context, list(...)))
}

AT.set.A1_I <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A1_I', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A1_I <- function(Context, ...)
{
  return (.External('_AT.get.nt.A1_I', Context, list(...)))
}

AT.set.nt.A1_I <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A1_I', Context, as.integer(Arg), list(...)))
}

AT.get.A2_B <- function(Context, ...)
{
  return (.External('_AT.get.A2_B', Context, list(...)))
}

AT.set.A2_B <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_B', Context, as.raw(Arg), list(...)))
}

AT.get.nt.A2_B <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_B', Context, list(...)))
}

AT.set.nt.A2_B <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_B', Context, as.raw(Arg), list(...)))
}

AT.get.A2_C <- function(Context, ...)
{
  return (.External('_AT.get.A2_C', Context, list(...)))
}

AT.set.A2_C <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_C', Context, as.raw(Arg), list(...)))
}

AT.get.nt.A2_C <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_C', Context, list(...)))
}

AT.set.nt.A2_C <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_C', Context, as.raw(Arg), list(...)))
}

AT.get.A2_DA <- function(Context, ...)
{
  return (.External('_AT.get.A2_DA', Context, list(...)))
}

AT.set.A2_DA <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_DA', Context, as.double(Arg), list(...)))
}

AT.get.nt.A2_DA <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_DA', Context, list(...)))
}

AT.set.nt.A2_DA <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_DA', Context, as.double(Arg), list(...)))
}

AT.get.A2_IA <- function(Context, ...)
{
  return (.External('_AT.get.A2_IA', Context, list(...)))
}

AT.set.A2_IA <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_IA', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A2_IA <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_IA', Context, list(...)))
}

AT.set.nt.A2_IA <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_IA', Context, as.integer(Arg), list(...)))
}

AT.get.A2_IB <- function(Context, ...)
{
  return (.External('_AT.get.A2_IB', Context, list(...)))
}

AT.set.A2_IB <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_IB', Context, as.integer(Arg), list(...)))
}

AT.get.nt.A2_IB <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_IB', Context, list(...)))
}

AT.set.nt.A2_IB <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_IB', Context, as.integer(Arg), list(...)))
}

AT.get.A2_LB <- function(Context, ...)
{
  return (.External('_AT.get.A2_LB', Context, list(...)))
}

AT.set.A2_LB <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_LB', Context, as.logical(Arg), list(...)))
}

AT.get.nt.A2_LB <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_LB', Context, list(...)))
}

AT.set.nt.A2_LB <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_LB', Context, as.logical(Arg), list(...)))
}

AT.get.A2_UC <- function(Context, ...)
{
  return (.External('_AT.get.A2_UC', Context, list(...)))
}

AT.set.A2_UC <- function(Context, Arg, ...)
{
  return (.External('_AT.set.A2_UC', Context, as.raw(Arg), list(...)))
}

AT.get.nt.A2_UC <- function(Context, ...)
{
  return (.External('_AT.get.nt.A2_UC', Context, list(...)))
}

AT.set.nt.A2_UC <- function(Context, Arg, ...)
{
  return (.External('_AT.set.nt.A2_UC', Context, as.raw(Arg), list(...)))
}

AT.boundsCheckTest <- function(Context, x)
{
  return (.External('_AT.boundsCheckTest', Context, x))
}

AT.nt.boundsCheckTest <- function(Context, x)
{
  return (.External('_AT.nt.boundsCheckTest', Context, x))
}

AT.IFTEST_BX <- function(Context, x, xb6_x, iftestb6_x)
{
  return (.External('_AT.IFTEST_BX', Context, x, xb6_x, iftestb6_x))
}

AT.nt.IFTEST_BX <- function(Context, x, xb6_x, iftestb6_x)
{
  return (.External('_AT.nt.IFTEST_BX', Context, x, xb6_x, iftestb6_x))
}

AT.isNegative <- function(Context, dValue)
{
  return (.External('_AT.isNegative', Context, dValue))
}

AT.nt.isNegative <- function(Context, dValue)
{
  return (.External('_AT.nt.isNegative', Context, dValue))
}

AT.isPositive <- function(Context, dValue)
{
  return (.External('_AT.isPositive', Context, dValue))
}

AT.nt.isPositive <- function(Context, dValue)
{
  return (.External('_AT.nt.isPositive', Context, dValue))
}

AT.get.ix <- function(Context)
{
  return (.External('_AT.get.ix', Context))
}

AT.set.ix <- function(Context, Arg)
{
  return (.External('_AT.set.ix', Context, as.integer(Arg)))
}

AT.get.iy <- function(Context)
{
  return (.External('_AT.get.iy', Context))
}

AT.set.iy <- function(Context, Arg)
{
  return (.External('_AT.set.iy', Context, as.integer(Arg)))
}

AT.polySum3D <- function(Context, X)
{
  return (.External('_AT.polySum3D', Context, X))
}

AT.nt.polySum3D <- function(Context, X)
{
  return (.External('_AT.nt.polySum3D', Context, X))
}

AT.POLYSUM3D_BX <- function(Context, x, xb1_x, polysum3db1_x)
{
  return (.External('_AT.POLYSUM3D_BX', Context, x, xb1_x, polysum3db1_x))
}

AT.nt.POLYSUM3D_BX <- function(Context, x, xb1_x, polysum3db1_x)
{
  return (.External('_AT.nt.POLYSUM3D_BX', Context, x, xb1_x, polysum3db1_x))
}

AT.polySumA <- function(Context, X)
{
  return (.External('_AT.polySumA', Context, X))
}

AT.nt.polySumA <- function(Context, X)
{
  return (.External('_AT.nt.polySumA', Context, X))
}

AT.POLYSUMA_BX <- function(Context, x, xb3_x, polysumab3_x)
{
  return (.External('_AT.POLYSUMA_BX', Context, x, xb3_x, polysumab3_x))
}

AT.nt.POLYSUMA_BX <- function(Context, x, xb3_x, polysumab3_x)
{
  return (.External('_AT.nt.POLYSUMA_BX', Context, x, xb3_x, polysumab3_x))
}

AT.polySumB <- function(Context, X)
{
  return (.External('_AT.polySumB', Context, X))
}

AT.nt.polySumB <- function(Context, X)
{
  return (.External('_AT.nt.polySumB', Context, X))
}

AT.POLYSUMB_BX <- function(Context, x, xb4_x, polysumbb4_x)
{
  return (.External('_AT.POLYSUMB_BX', Context, x, xb4_x, polysumbb4_x))
}

AT.nt.POLYSUMB_BX <- function(Context, x, xb4_x, polysumbb4_x)
{
  return (.External('_AT.nt.POLYSUMB_BX', Context, x, xb4_x, polysumbb4_x))
}

AT.polySumC <- function(Context, X)
{
  return (.External('_AT.polySumC', Context, X))
}

AT.nt.polySumC <- function(Context, X)
{
  return (.External('_AT.nt.polySumC', Context, X))
}

AT.POLYSUMC_BX <- function(Context, x, xb5_x, polysumcb5_x)
{
  return (.External('_AT.POLYSUMC_BX', Context, x, xb5_x, polysumcb5_x))
}

AT.nt.POLYSUMC_BX <- function(Context, x, xb5_x, polysumcb5_x)
{
  return (.External('_AT.nt.POLYSUMC_BX', Context, x, xb5_x, polysumcb5_x))
}

AT.get.SingularBool <- function(Context)
{
  return (.External('_AT.get.SingularBool', Context))
}

AT.set.SingularBool <- function(Context, Arg)
{
  return (.External('_AT.set.SingularBool', Context, as.raw(Arg)))
}

AT.get.SingularLongbool <- function(Context)
{
  return (.External('_AT.get.SingularLongbool', Context))
}

AT.set.SingularLongbool <- function(Context, Arg)
{
  return (.External('_AT.set.SingularLongbool', Context, as.logical(Arg)))
}

AT.sum <- function(Context, X)
{
  return (.External('_AT.sum', Context, X))
}

AT.nt.sum <- function(Context, X)
{
  return (.External('_AT.nt.sum', Context, X))
}

AT.SUM_BX <- function(Context, x, xb2_x, sumb2_x)
{
  return (.External('_AT.SUM_BX', Context, x, xb2_x, sumb2_x))
}

AT.nt.SUM_BX <- function(Context, x, xb2_x, sumb2_x)
{
  return (.External('_AT.nt.SUM_BX', Context, x, xb2_x, sumb2_x))
}

AT.sumA1_D <- function(Context)
{
  return (.External('_AT.sumA1_D', Context))
}

AT.nt.sumA1_D <- function(Context)
{
  return (.External('_AT.nt.sumA1_D', Context))
}

AT.test_one_if <- function(Context, v)
{
  return (.External('_AT.test_one_if', Context, v))
}

AT.nt.test_one_if <- function(Context, v)
{
  return (.External('_AT.nt.test_one_if', Context, v))
}

AT.TEST_ONE_IF_BV <- function(Context, v, vb8_v, test_one_ifb8_v)
{
  return (.External('_AT.TEST_ONE_IF_BV', Context, v, vb8_v, test_one_ifb8_v))
}

AT.nt.TEST_ONE_IF_BV <- function(Context, v, vb8_v, test_one_ifb8_v)
{
  return (.External('_AT.nt.TEST_ONE_IF_BV', Context, v, vb8_v, test_one_ifb8_v))
}

AT.TEST_ONE_IF_DV <- function(Context, v, vd7_v, test_one_if)
{
  return (.External('_AT.TEST_ONE_IF_DV', Context, v, vd7_v, test_one_if))
}

AT.nt.TEST_ONE_IF_DV <- function(Context, v, vd7_v, test_one_if)
{
  return (.External('_AT.nt.TEST_ONE_IF_DV', Context, v, vd7_v, test_one_if))
}

AT.test_one_if_internal <- function(Context, v)
{
  return (.External('_AT.test_one_if_internal', Context, v))
}

AT.nt.test_one_if_internal <- function(Context, v)
{
  return (.External('_AT.nt.test_one_if_internal', Context, v))
}

AT.TEST_ONE_IF_INTERNAL_BV <- function(Context, v, vb10_v, test_one_if_internalb10_v)
{
  return (.External('_AT.TEST_ONE_IF_INTERNAL_BV', Context, v, vb10_v, test_one_if_internalb10_v))
}

AT.nt.TEST_ONE_IF_INTERNAL_BV <- function(Context, v, vb10_v, test_one_if_internalb10_v)
{
  return (.External('_AT.nt.TEST_ONE_IF_INTERNAL_BV', Context, v, vb10_v, test_one_if_internalb10_v))
}

AT.TEST_ONE_IF_INTERNAL_DV <- function(Context, v, vd9_v, test_one_if_internal)
{
  return (.External('_AT.TEST_ONE_IF_INTERNAL_DV', Context, v, vd9_v, test_one_if_internal))
}

AT.nt.TEST_ONE_IF_INTERNAL_DV <- function(Context, v, vd9_v, test_one_if_internal)
{
  return (.External('_AT.nt.TEST_ONE_IF_INTERNAL_DV', Context, v, vd9_v, test_one_if_internal))
}

AT.get.female <- function()
{
  return (.External('_AT.get.female'))
}

AT.get.male <- function()
{
  return (.External('_AT.get.male'))
}

AT.get.n_sex <- function()
{
  return (.External('_AT.get.n_sex'))
}

