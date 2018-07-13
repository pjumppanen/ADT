# Load the library
if (version$os == "mingw32")
{
  # Running in Windows - assume we have changed dir to the sample\ArrayTest folder
  if (is.na(match("ArrayTest",  attr(getLoadedDLLs(), "names"))))
  {
    if (version$arch == "i386")
    {
      dyn.load("../../objs/Win32/Release/ArrayTest.dll")

    } else
    {
      dyn.load("../../objs/x64/Release/ArrayTest.dll")
    }
  }

} else if (version$os == "cygwin")
{
  # Running in cygwin
  if (is.na(match("ArrayTest.dll",  attr(getLoadedDLLs(), "names"))))
  {
    file.copy("../../objs/sample/ArrayTest/.libs/cygArrayTest-0.dll", "../../objs/sample/ArrayTest/.libs/ArrayTest.dll", overwrite=TRUE)
    dyn.load("../../objs/sample/ArrayTest/.libs/ArrayTest.dll")
  }

} else
{
  # Running in Linux
  if (is.na(match("libArrayTest",  attr(getLoadedDLLs(), "names"))))
  {
    dyn.load("../../objs/sample/ArrayTest/.libs/libArrayTest.so")
  }
}


require('Oarray')


AT.ix <- 5
AT.iy <- 3

# /*1:1+ix*/
AT.A1_I <- 1:(1+AT.ix)

# /*1:ix*/
AT.A1_D <- (1:AT.ix) + 10.0

# /*1+ix,-1:iy*/
AT.A2_IA <- Oarray(1:((1 + AT.ix) * (AT.iy + 2)), dim=c(1 + AT.ix, AT.iy + 2), offset=c(1, -1), drop.negative=FALSE)

# /*-1:iy,1+ix*/
AT.A2_IB <- Oarray(1:((1 + AT.ix) * (AT.iy + 2)), dim=c(AT.iy + 2, 1 + AT.ix), offset=c(-1, 1), drop.negative=FALSE)

# /*1+ix,1:n_sex*/
AT.A2_DA <- Oarray(1.0 / (1:((1 + AT.ix) * 2)), dim=c(1 + AT.ix, 2), offset=c(1, 1), drop.negative=FALSE)

# /*C++ dim 1+ix,-1:iy*/
AT.A2_LB <- (runif((1 + AT.ix) * (AT.iy + 2), min=0, max=255) > 128)
dim(AT.A2_LB) <- c((1 + AT.ix), (AT.iy + 2))

# /*1+ix,-1:iy*/
AT.A2_C <- Oarray(as.integer(runif((1 + AT.ix) * (AT.iy + 2), min=-128, max=127)), dim=c(1 + AT.ix, AT.iy + 2), offset=c(1, -1), drop.negative=FALSE)

# /*1+ix,-1:iy*/
AT.A2_UC <- Oarray(as.integer(runif((1 + AT.ix) * (AT.iy + 2), min=0, max=255)), dim=c(1 + AT.ix, AT.iy + 2), offset=c(1, -1), drop.negative=FALSE)

# /*1+ix,-1:iy*/
AT.A2_B <- (runif((1 + AT.ix) * (AT.iy + 2), min=0, max=255) > 128)
dim(AT.A2_B)<-c((1 + AT.ix), (AT.iy + 2))


source('AT_R_interface.r', print.eval=TRUE)


# Create object instance
Context <- AT.create(AT.ix, AT.iy, AT.A1_I, AT.A1_D, AT.A2_IA, AT.A2_IB, AT.A2_DA, AT.A2_LB, bitwAnd(AT.A2_C + 256, 255), AT.A2_UC, AT.A2_B, 1, TRUE)


# Test getters
if ((AT.ix - AT.get.ix(Context)) != 0) print("AT.get.ix() failed") else print("AT.get.ix() succeeded")

if ((AT.iy - AT.get.iy(Context)) != 0) print("AT.get.iy() failed") else print("AT.get.iy() succeeded")

if (sum(AT.A1_I - AT.get.A1_I(Context)) != 0) print("AT.get.A1_I() failed") else print("AT.get.A1_I() succeeded")

if ((AT.A1_I[2] - AT.get.A1_I(Context,2)) != 0) print("AT.get.A1_I(2) failed") else print("AT.get.A1_I(2) succeeded")

if (sum(AT.A1_D - AT.get.A1_D(Context)) != 0) print("AT.get.A1_D() failed") else print("AT.get.A1_D() succeeded")

if ((AT.A1_D[2] - AT.get.A1_D(Context,2)) != 0) print("AT.get.A1_D(2) failed") else print("AT.get.A1_D(2) succeeded")

if (sum(AT.A2_IA - AT.get.A2_IA(Context)) != 0) print("AT.get.A2_IA() failed") else print("AT.get.A2_IA() succeeded")

if (sum(AT.A2_IA[3,] - AT.get.A2_IA(Context,3)) != 0) print("AT.get.A2_IA(3) failed") else print("AT.get.A2_IA(3) succeeded")

if (sum(AT.A2_IA[3,1] - AT.get.A2_IA(Context,3,1)) != 0) print("AT.get.A2_IA(3,1) failed") else print("AT.get.A2_IA(3,1) succeeded")

if (sum(AT.A2_IB - AT.get.A2_IB(Context)) != 0) print("AT.get.A2_IB() failed") else print("AT.get.A2_IB() succeeded")

if (sum(AT.A2_IB[3,] - AT.get.A2_IB(Context,3)) != 0) print("AT.get.A2_IB(3) failed") else print("AT.get.A2_IB(3) succeeded")

if (sum(AT.A2_IB[3,1] - AT.get.A2_IB(Context,3,1)) != 0) print("AT.get.A2_IB(3,1) failed") else print("AT.get.A2_IB(3,1) succeeded")

if (any((AT.A2_LB == AT.get.A2_LB(Context)) == FALSE)) print("AT.get.A2_LB() failed") else print("AT.get.A2_LB() succeeded")

if (any((AT.A2_LB[3,] == AT.get.A2_LB(Context,3)) == FALSE)) print("AT.get.A2_LB(3) failed") else print("AT.get.A2_LB(3) succeeded")

if (any((AT.A2_LB[3,1] == AT.get.A2_LB(Context,3,-1)) == FALSE)) print("AT.get.A2_LB(3,-1) failed") else print("AT.get.A2_LB(3,-1) succeeded")

if (any((AT.A2_B == (AT.get.A2_B(Context) != 0)) == FALSE)) print("AT.get.A2_B() failed") else print("AT.get.A2_B() succeeded")

if (any((AT.A2_B[3,] == (AT.get.A2_B(Context,3) != 0)) == FALSE)) print("AT.get.A2_B(3) failed") else print("AT.get.A2_B(3) succeeded")

if (any((AT.A2_B[3,1] == (AT.get.A2_B(Context,3, -1) != 0)) == FALSE)) print("AT.get.A2_B(3,-1) failed") else print("AT.get.A2_B(3,-1) succeeded")

if (sum(as.integer(AT.A2_UC) - as.integer(AT.get.A2_UC(Context))) != 0) print("AT.get.A2_UC() failed") else print("AT.get.A2_UC() succeeded")

if (sum(as.integer(AT.A2_UC[3,]) - as.integer(AT.get.A2_UC(Context, 3))) != 0) print("AT.get.A2_UC(3) failed") else print("AT.get.A2_UC(3) succeeded")

if (sum(as.integer(AT.A2_UC[3,1]) - as.integer(AT.get.A2_UC(Context, 3, 1))) != 0) print("AT.get.A2_UC(3,1) failed") else print("AT.get.A2_UC(3,1) succeeded")

if (sum(bitwAnd(AT.A2_C + 256, 255) - as.integer(AT.get.A2_C(Context))) != 0) print("AT.get.A2_C() failed") else print("AT.get.A2_C() succeeded")

if (sum(bitwAnd(AT.A2_C[3,] + 256, 255) - as.integer(AT.get.A2_C(Context, 3))) != 0) print("AT.get.A2_C(3) failed") else print("AT.get.A2_C(3) succeeded")

if (sum(bitwAnd(AT.A2_C[3,1] + 256, 255) - as.integer(AT.get.A2_C(Context, 3, 1))) != 0) print("AT.get.A2_C(3,1) failed") else print("AT.get.A2_C(3,1) succeeded")


# Test setters
AT.ix_new <- AT.ix + 1
AT.set.ix(Context,AT.ix_new)
if ((AT.ix_new - AT.get.ix(Context)) != 0) print("AT.set.ix() failed") else print("AT.set.ix() succeeded")
AT.ix <- AT.ix_new - 1
AT.set.ix(Context,AT.ix)

AT.iy_new <- AT.iy + 1
AT.set.iy(Context,AT.iy_new)
if ((AT.iy_new - AT.get.iy(Context)) != 0) print("AT.set.iy() failed") else print("AT.set.iy() succeeded")
AT.iy <- AT.iy_new - 1
AT.set.iy(Context,AT.iy)

AT.A1_I_new <- AT.A1_I + 12
AT.set.A1_I(Context,AT.A1_I_new)
if (sum(AT.A1_I_new - AT.get.A1_I(Context)) != 0) print("AT.set.A1_I() failed") else print("AT.set.A1_I() succeeded")
AT.A1_I <- AT.A1_I_new - 12
AT.set.A1_I(Context,AT.A1_I)

AT.A1_I[1] <- AT.A1_I[1] + 12
AT.set.A1_I(Context,AT.A1_I[1], 1)
if (sum(AT.A1_I - AT.get.A1_I(Context)) != 0) print("AT.set.A1_I(1) failed") else print("AT.set.A1_I(1) succeeded")
AT.A1_I[1] <- AT.A1_I[1] - 12
AT.set.A1_I(Context,AT.A1_I[1], 1)

AT.A1_D_new <- AT.A1_D + 12
AT.set.A1_D(Context,AT.A1_D_new)
if (sum(AT.A1_D_new - AT.get.A1_D(Context)) != 0) print("AT.set.A1_D() failed") else print("AT.set.A1_D() succeeded")
AT.A1_D <- AT.A1_D_new - 12
AT.set.A1_D(Context,AT.A1_D)

AT.A1_D[1] <- AT.A1_D[1] + 12
AT.set.A1_D(Context,AT.A1_D[1], 1)
if (sum(AT.A1_D - AT.get.A1_D(Context)) != 0) print("AT.set.A1_D(1) failed") else print("AT.set.A1_D(1) succeeded")
AT.A1_D[1] <- AT.A1_D[1] - 12
AT.set.A1_D(Context,AT.A1_D[1], 1)

AT.A2_IA_new <- AT.A2_IA
AT.A2_IA_new[5,] <- AT.A2_IA_new[3,]
AT.set.A2_IA(Context,AT.get.A2_IA(Context,3), 5)
if (sum(AT.A2_IA_new - AT.get.A2_IA(Context)) != 0) print("AT.set.A2_IA(5) failed") else print("AT.set.A2_IA(5) succeeded")
AT.set.A2_IA(Context,AT.A2_IA)

AT.A2_IB_new <- AT.A2_IB
AT.A2_IB_new[0,] <- AT.A2_IB_new[3,]
AT.set.A2_IB(Context,AT.get.A2_IB(Context,3), 0)
if (sum(AT.A2_IB_new - AT.get.A2_IB(Context)) != 0) print("AT.set.A2_IB(0) failed") else print("AT.set.A2_IB(0) succeeded")
AT.set.A2_IB(Context,AT.A2_IB)

AT.A2_IA_new <- AT.A2_IA
AT.A2_IA_new[5,1] <- 99
AT.set.A2_IA(Context,99, 5,1)
if (sum(AT.A2_IA_new - AT.get.A2_IA(Context)) != 0) print("AT.set.A2_IA(5,1) failed") else print("AT.set.A2_IA(5,1) succeeded")
AT.set.A2_IA(Context,AT.A2_IA)

AT.A2_IB_new <- AT.A2_IB
AT.A2_IB_new[0,3] <- 99
AT.set.A2_IB(Context,99, 0, 3)
if (sum(AT.A2_IB_new - AT.get.A2_IB(Context)) != 0) print("AT.set.A2_IB(0,3) failed") else print("AT.set.A2_IB(0,3) succeeded")
AT.set.A2_IB(Context,AT.A2_IB)

AT.A2_LB_new <- AT.A2_LB
AT.A2_LB_new[3,] <- !AT.A2_LB_new[3,]
AT.set.A2_LB(Context, AT.A2_LB_new[3,], 3)
if (sum(ifelse(as.vector(AT.A2_LB_new) == as.vector(AT.get.A2_LB(Context)), 0, 1)) != 0) print("AT.set.A2_LB(3) failed") else print("AT.set.A2_LB(3) succeeded")
AT.set.A2_LB(Context,AT.A2_LB)

AT.A2_B_new <- AT.A2_B
AT.A2_B_new[3,] <- !AT.A2_B_new[3,]
AT.set.A2_B(Context, AT.A2_B_new[3,], 3)
if (sum(ifelse(as.vector(AT.A2_B_new) == as.vector(AT.get.A2_B(Context)), 0, 1)) != 0) print("AT.set.A2_B(3) failed") else print("AT.set.A2_B(3) succeeded")
AT.set.A2_B(Context,AT.A2_B)

AT.A2_UC_new <- AT.A2_UC
AT.A2_UC_new[5,1] <- 99
AT.set.A2_UC(Context,99, 5,1)
if (sum(as.integer(AT.A2_UC_new) - as.integer(AT.get.A2_UC(Context))) != 0) print("AT.set.A2_UC(5,1) failed") else print("AT.set.A2_UC(5,1) succeeded")
AT.set.A2_UC(Context,AT.A2_UC)

AT.A2_C_new <- AT.A2_C
AT.A2_C_new[5,1] <- 99
AT.set.A2_C(Context,99,5,1)
if (sum(bitwAnd(AT.A2_C_new + 256, 255) - as.integer(AT.get.A2_C(Context))) != 0) print("AT.set.A2_C(5,1) failed") else print("AT.set.A2_C(5,1) succeeded")

if (AT.sum(Context,AT.get.A1_D(Context)) - sum(AT.get.A1_D(Context)) - AT.get.A1_D(Context)[1] - AT.get.A1_D(Context)[2] != 0) print("AT.sum() failed") else print("AT.sum() succeeded")

if ((AT.polySumA(Context, AT.A1_D) - AT.polySumB(Context, AT.A1_D)) != 0) print("AT.polySumA() produces different result to AT.polySumB() : failed") else print("AT.polySumA() produces same result to AT.polySumB() : succeeded")

# make vectors to hold reverse mode differentiation results
AT.A1_DDA <- as.double(rep(0, length(AT.A1_D)))
AT.A1_DDB <- as.double(rep(0, length(AT.A1_D)))
AT.A1_DDC <- as.double(rep(0, length(AT.A1_D)))

# do reverse mode differentiation
#AT.POLYSUMA_BX(Context, AT.A1_D, AT.A1_DDA, 1.0)
AT.POLYSUMB_BX(Context, AT.A1_D, AT.A1_DDB, 1.0)
AT.POLYSUMC_BX(Context, AT.A1_D, AT.A1_DDC, 1.0)

# check they are the same
if (sum(AT.A1_DDA - AT.A1_DDB) != 0) print("AT.POLYSUMA_BX() produces different result to AT.POLYSUMB_BX() : failed") else print("AT.POLYSUMA_BX() produces same result to AT.POLYSUMB_BX() : succeeded")
if (sum(AT.A1_DDC - AT.A1_DDB) != 0) print("AT.POLYSUMC_BX() produces different result to AT.POLYSUMB_BX() : failed") else print("AT.POLYSUMC_BX() produces same result to AT.POLYSUMB_BX() : succeeded")

# check querying constants
print(paste("female =", AT.get.female()))
print(paste("male =", AT.get.male()))
print(paste("sex =", AT.get.n_sex()))

# bounds check test - should throw error in R
AT.boundsCheckTest(Context, AT.A1_D)
