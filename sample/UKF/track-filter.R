# Attempt to do argos track filtering with UKF model
# ----------------------------------------------------------------------------


# Load necessary libraries
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

# ----------------------------------------------------------------------------

# open my land filter code library 
dyn.load("../../../LandFilter/land_filter.dll")

LFContext <- .External('Initialise', "../../../LandFilter/coastline/GSHHS_f_L1.shp")

# ----------------------------------------------------------------------------

distanceStartEnd <- function(start_lon, 
                             start_lat, 
                             end_lon, 
                             end_lat)
{
  # Convert coordinates to radians
  start_lat <- start_lat * pi / 180.0
  start_lon <- start_lon * pi / 180.0
  end_lat   <- end_lat * pi / 180.0
  end_lon   <- end_lon * pi / 180.0

  # Radius of the Earth in metres
  radius <- 6371000.0
  
  # Calculate the difference in longitude
  delta_lon <- end_lon - start_lon
  delta_lat <- end_lat - start_lat

  # Calculate the distance using the Haversine formula
  a <- (sin(delta_lat / 2.0) ** 2) + cos(start_lat) * cos(end_lat) * (sin(delta_lon / 2.0) ** 2)
  c <- 2.0 * atan2(sqrt(a), sqrt(1.0 - a))
  
  # distance in m
  distance <- abs(radius * c)

  return (distance)
}

# ----------------------------------------------------------------------------

speedFromStartEndAndTime <- function(start_lon, 
                                     start_lat, 
                                     end_lon, 
                                     end_lat,
                                     dt)
{
  # Convert coordinates to radians
  start_lat <- start_lat * pi / 180.0
  start_lon <- start_lon * pi / 180.0
  end_lat   <- end_lat * pi / 180.0
  end_lon   <- end_lon * pi / 180.0

  # Radius of the Earth in metres
  radius <- 6371000.0
  
  # Calculate the difference in longitude
  delta_lon <- end_lon - start_lon
  delta_lat <- end_lat - start_lat

  # Calculate the distance using the Haversine formula
  a <- (sin(delta_lat / 2.0) ** 2) + cos(start_lat) * cos(end_lat) * (sin(delta_lon / 2.0) ** 2)
  c <- 2.0 * atan2(sqrt(a), sqrt(1.0 - a))
  
  # distance in m
  distance <- abs(radius * c)

  # speed in m/s, dt in seconds
  speed <- distance / dt

  return (speed)
}

# ----------------------------------------------------------------------------
# returns the error covariance matrices from Vincent et al (2002) data.
# TRIAL ALTERNATIVE TO PREVIOUS COMMENTED OUT CODE IN kf.fit
#
#
#
rmat <- function(zero.AB=FALSE, spFil = TRUE)
{
  # Use Speed filtering
  if (spFil)
  {
    cvList <- structure(list(
        "-2" = structure(c(570.338054652832, -65.4519963196788,
                                -65.4519963196788, 112.008917565891),
            .Dim = c(2L, 2L)),
          "-1" = structure(c(73.3220003893619, -10.8302053706227,
                            -10.8302053706227, 31.6081164580945),
            .Dim = c(2L,2L)),
          "0" = structure(c(248.384660714022, 331.576499892469,
                            331.576499892469, 749.168713906962),
            .Dim = c(2L, 2L)),
          "1" = structure(c(4.05618904257116, 0.179338351718480,
                            0.179338351718480, 0.632816121863039),
              .Dim = c(2L,2L)),
          "2" = structure(c(0.69672091533716,0.0547615102249857,
                            0.0547615102249857, 0.0949871603625376),
              .Dim = c(2L,2L)),
          "3" = structure(c(0.359940022223408,0.12725434958535,
                            0.12725434958535, 0.092235304576537),
            .Dim = c(2L,2L))),
          #"G" = structure(c(0.0,0.0,0.0,0.0), .Dim = c(2L,2L))),
            .Names = c("-2", "-1", "0", "1", "2", "3"))
   }
   # Dont Use speed filtering
   else
   {
      cvList <- structure(
          list("-2" = structure(c(608.285847032308, -60.0080321240214,
                                  -60.0080321240214, 111.483098577438),
                    .Dim = c(2L, 2L)),
                "-1" = structure(c(56.4817199579225, -8.11189879917165,
                                  -8.11189879917165, 23.2348271771370),
                    .Dim = c(2L, 2L)),
                "0" = structure(c(1937.94637018685, 1133.80579384735,
                                  1133.80579384735, 1343.79913671960),
                    .Dim = c(2L, 2L)),
                "1" = structure(c(4.46253493108096, -0.141556752001644,
                                -0.141556752001644, 0.668006886366648),
                    .Dim = c(2L, 2L)),
                "2" = structure(c(0.765081718261347, -0.0701769695088216,
                                -0.0701769695088216, 0.178488816779786),
                    .Dim = c(2L, 2L)),
                "3" = structure(c(0.345389595130328, 0.121767613767362,
                                  0.121767613767362, 0.0884682832681666),
                    .Dim = c(2L, 2L))),
                #"G" = structure(c(0,0,0,0.), .Dim = c(2L,2L))),
      .Names = c("-2", "-1", "0", "1", "2", "3"))
  }

  if (zero.AB)
  {
    cvList$"2" <- matrix(c(0.001,0,0,0.001),2,2)
    cvList$"3" <- matrix(c(0.001,0,0,0.001),2,2)
  }

  return (cvList);
}

# ----------------------------------------------------------------------------

loadArgosTrackData <- function(PreFilterFile, max_speed)
{
  # Read ARGOS positions from file
  df <- read.table(PreFilterFile,
                  sep = ",",
                  col.names = c("TAG_TYPE",
                                "SMART_ID",
                                "R_LQ",
                                "R_DATE",
                                "R_TIME",
                                "LAT",
                                "LON",
                                "QI",
                                "SOL1_LAT",
                                "SOL1_LON",
                                "SOL2_LAT",
                                "SOL2_LON"),
                  as.is = c(4,5,6,7,8,9,10,11,12),
                  na.strings = c("","NA"),
                  strip.white = TRUE);

  # remove duplicates
  df <- unique(df)

  # Match the location quality values to what Toby's code expects
  levels(df$R_LQ)[which(levels(df$R_LQ) == 'A')] <- "-1"
  levels(df$R_LQ)[which(levels(df$R_LQ) == 'B')] <- "-2"
  df$LQ <- as.character(df$R_LQ)

  # Create date values from raw date and time values
  df$D_DATE <- as.POSIXct(paste(df$R_DATE, df$R_TIME))

  # make sure that data is in time order
  df <- df[order(df$D_DATE),]

  # Fix longitudes that are not normalised to range [-180, 180]
  df$LON <- df$LON - as.integer(df$LON / 180) * 360

  # remove NA LQ records
  df <- df[!is.na(df$LQ),]  

  # remove Z LQ records
  df <- df[!df$LQ=='Z',]

  # remove -9 quality records
  if (any(df$LQ == -9))
  {
    df <- df[!(df$LQ == -9),]
    cat(" -9 quality locations removed \n")
  }

  # need to unwrap longitudes (ie. take out the sign changed at the date line)
  # we do this because we are using the longitude as a markov model state
  # variable and don't want the discontinuity of the date line crossing.
  # We store LonOffsets in the data frame.
  LonOffset  <- 0.0
  LonOffsets <- 0.0 * df$LON

  for (cn in 2:length(df$LON))
  {
    SignTest <- ((df$LON[cn] * df$LON[cn - 1]) < 0.0)

    if (SignTest)
    {
      if (df$LON[cn] < 0)
      {
        LonOffset <- LonOffset + 360.0
      }
      else
      {
        LonOffset <- LonOffset - 360.0
      }
    }

    LonOffsets[cn] <- LonOffset
  }

  df$LonOffsets <- LonOffsets

  # Do speed filtering to removed bad outliers
  lons <- df$LON
  lats <- df$LAT

  speed_fwd  <- lons * 0.0
  speed_back <- lons * 0.0
  dt         <- diff(df$D_DATE)
  times      <- as.integer(df$D_DATE)
  idxs       <- which(dt != 0)
  drop_speed <- max_speed

  if (length(idxs) > 3)
  {
    drop <- c()

    bContinue <- TRUE

    while (bContinue)
    {
      bContinue <- FALSE
      next_idxs <- idxs

      # search forward
      for (cn in 3:length(idxs))
      {
        ca1     <- idxs[cn - 2]
        ca2     <- idxs[cn - 1]
        cb      <- idxs[cn]
        dt1     <- times[cb] - times[ca1]
        dt2     <- times[cb] - times[ca2]
        speed_1 <- speedFromStartEndAndTime(lons[ca1], lats[ca1], lons[cb], lats[cb], dt1)
        speed_2 <- speedFromStartEndAndTime(lons[ca2], lats[ca2], lons[cb], lats[cb], dt2)

        if ((speed_1 > drop_speed) && (speed_2 > drop_speed))
        {
          drop          <- c(drop, idxs[cn])
          next_idxs[cn] <- NA
          bContinue     <- TRUE
        }
      }

      # search remainder
      for (cn in 1:2)
      {
        cb      <- idxs[cn]
        ca1     <- idxs[cn + 1]
        ca2     <- idxs[cn + 2]
        dt1     <- times[ca1] - times[cb]
        dt2     <- times[ca2] - times[cb]
        speed_1 <- speedFromStartEndAndTime(lons[cb], lats[cb], lons[ca1], lats[ca1], dt1)
        speed_2 <- speedFromStartEndAndTime(lons[cb], lats[cb], lons[ca2], lats[ca2], dt2)

        if ((speed_1 > drop_speed) && (speed_2 > drop_speed))
        {
          drop          <- c(drop,cn)
          next_idxs[cn] <- NA
          bContinue     <- TRUE
        }
      }

      idxs <- next_idxs[which(!is.na(next_idxs))]
    }
  }

  df <- df[-c(drop),]

  # make sure that data is in time order
  df <- df[order(df$D_DATE),]

  # add a time record in units of days
  dt   <- diff(df$D_DATE) / (24 * 3600)
  df$t <- c(0.0, cumsum(as.double(dt)))

  # add R covariance matrices
  Rlist <- rmat(FALSE, FALSE)
  df$R  <- sapply(df$LQ, function(x) {if (is.na(x)) Rlist[['3']] else Rlist[[x]]}, simplify=FALSE, USE.NAMES=FALSE)

  # combine records of same time to give a single record with 
  # averaged position and summed covariance.
  ridx <- which(dt == 0)

  deletions <- c()

  for (ix in ridx)
  {
    aidx    <- which(df$t == df[ix,]$t)
    meanLat <- mean(df[aidx,]$LAT)
    meanLon <- mean(df[aidx,]$LON)
    sumR    <- df[ix,]$R[[1]] * 0

    lapply(df[aidx,]$R, function(x) {sumR <<- sumR + x})

    meanR   <- sumR / length(df[aidx,]$R)

    df[ix,]$R[[1]] <- meanR
    deletions      <- c(deletions, aidx[2:length(aidx)])
  }

  df <- df[-c(deletions),]

  # update time records post duplicate removals
  dt   <- diff(df$D_DATE) / (24 * 3600)
  df$t <- c(0.0, cumsum(as.double(dt)))

  return (df)
}

# ----------------------------------------------------------------------------

addInterpolationPoints <- function(df)
{
  # Interpolate the argos data at 24 hour interval
  interpolated_times <- seq(min(df$D_DATE), max(df$D_DATE), by="24 hours")
  interpolated_times <- interpolated_times[which(!interpolated_times %in% df$D_DATE)]
  NAfield <- rep(NA, times=(length(interpolated_times)))
  Zerofield <- rep(0.0, times=(length(interpolated_times)))
  Rdims <- dim(df[1,]$R[[1]])
  Rfield <- rep(list(array(NA, dim = Rdims)), times=(length(interpolated_times)))
  df.added <- data.frame(TAG_TYPE=NAfield,
                         SMART_ID=NAfield,
                         R_LQ=NAfield,
                         R_DATE=NAfield,
                         R_TIME=NAfield,
                         LAT=NAfield,
                         LON=NAfield,
                         QI=NAfield,
                         SOL1_LAT=NAfield,
                         SOL1_LON=NAfield,
                         SOL2_LAT=NAfield,
                         SOL2_LON=NAfield,
                         LQ=NAfield,
                         D_DATE=interpolated_times,
                         LonOffsets=Zerofield, 
                         t=NAfield,
                         R=NAfield)

  df.added$R <- Rfield
  df <- rbind(df, df.added)

  rownames(df) <- 1:nrow(df)

  # make sure that data is in time order
  df <- df[order(df$D_DATE),]

  # update time records post duplicate removals
  dt   <- diff(df$D_DATE) / (24 * 3600)
  df$t <- c(0.0, cumsum(as.double(dt)))

  return (df)
}

# ----------------------------------------------------------------------------

estimateQ <- function(df)
{
  idx      <- which(!is.na(df$LON))
  na_idx   <- which(is.na(df$LON))
  full.len <- length(df$LON)
  dt.full  <- diff(df$t)

  # remove NA records
  df    <- df[idx,]
  len   <- length(df$LON)
  y     <- array(NA, c(len, 2))
  y[,1] <- df$LON + df$LonOffsets
  y[,2] <- df$LAT

  # Radius of the Earth in km
  radius <- 6371.0

  # should be able to estimate starting values for Q based on 
  # observation data (which should eliminate implausible values)
  # and these need to have a time scale component on lon and lat
  # state variable components which need to grow with time since
  # how far an animal may have moved (ie. variance) will be a 
  # function of time. 
  scaling   <- cos(y[1:(len - 1),2] * pi / 180.0)
  data.time <- df$t
  dy        <- diff(y)
  dy[,1]    <- dy[,1] * scaling
  dt        <- diff(data.time)
  dyondt    <- dy / dt
  fit.x     <- density(dyondt[,1]) 
  fit.y     <- density(dyondt[,1]) 
  Q         <- array(as.double(0.0), c(4, 4))
  Qscaling  <- array(as.double(1.0), c(full.len, 4))

  Q[1,1] <- fit.x$bw ** 2
  Q[2,2] <- fit.y$bw ** 2
  Q[3,3] <- radius * pi * (Q[1,1]) * 0.5 / 180
  Q[4,4] <- radius * pi * (Q[2,2]) * 0.5 / 180

  dt.idxs <- 1:length(dt)
  Qscaling[idx[dt.idxs],1] <- (1.0 / scaling)

  # for interpolated locations (ie. points in time we have added 
  # which we have no observations for) we need to add variance
  # scaling for the latitudinal component based on some guestimate.
  # The simplest approach is a linear interpolation from the scaling
  # before and after the block of NA values. 

  # first we find the sequential na indices
  len.na_idx <- length(na_idx)

  if (len.na_idx > 0)
  {
    check_idx  <- c(na_idx[1] - 1, na_idx)
    check      <- check_idx[1:len.na_idx] - check_idx[2:(len.na_idx + 1)] + 1
    start_ix   <- na_idx[1]
    end_ix     <- start_ix
    iy         <- 1
    ranges     <- list()

    for (ix in 2:len.na_idx)
    {
      if (check[ix] != 0)
      {
        ranges[[iy]] <- c(start_ix, end_ix)
        start_ix     <- na_idx[ix]
        iy           <- iy + 1
      }

      end_ix <- na_idx[ix]
    }

    ranges[[iy]] <- c(start_ix, end_ix)

    # now we interpolate the scaling for those ranges
    for (range in ranges)
    {
      if (range[1] == 1)
      {
        # no scaling before NA
        Qscaling[range[1]:range[2],1] <- Qscaling[range[2]+1,1]
      }
      else if (range[2] == full.len)
      {
        # no scaling after NA
        Qscaling[range[1]:range[2],1] <- Qscaling[range[1]-1,1]
      }
      else
      {
        start_ix <- range[1]
        end_ix   <- range[2]

        start_scaling <- Qscaling[start_ix - 1,1]
        end_scaling   <- Qscaling[end_ix - 1,1]

        for (ix in start_ix:end_ix)
        {
          scaling        <- start_scaling + (ix - start_ix + 1) * (end_scaling - start_scaling) / (end_ix - start_ix + 2)
          Qscaling[ix,1] <- scaling
        }
      }
    }
  }

  dt.full  <- c(dt.full, dt.full[length(dt.full)])
  Qscaling <- Qscaling * dt.full

  return (list(Q=Q, Qscaling=Qscaling))
}
QandQscaling2 <- estimateQ(df2)

# ----------------------------------------------------------------------------

initR <- function(df)
{
  size_n  <- length(df$R)
  R       <- array(as.double(0.0), c(size_n, 2, 2))
  ix      <-1

  # Radius of the Earth in km
  radius <- 6371.0

  for (Ri in df$R)
  {
    scaleY      <- 180.0 / (pi * radius)
    scaleX      <- scaleY / cos(df$LAT[ix] * pi / 180.0)
    scale       <- Ri * 0.0
    scale[1,1]  <- scaleX * scaleX
    scale[1,2]  <- scaleX * scaleY
    scale[2,1]  <- scale[1,2]
    scale[2,2]  <- scaleY * scaleY
    R[ix,,]     <- Ri * scale
    ix          <- ix + 1
  }

  return (R)
}

# ----------------------------------------------------------------------------

max_speed <- 7.2 # 2 ms^{-1}

sigma0 <- c(0.4408, 0.2794)

df           <- loadArgosTrackData("smart414_pre-filter", max_speed)
QandQscaling <- estimateQ(df)
data.time    <- df$t

# ----------------------------------------------------------------------------

n     <- 4
m     <- 2
kappa <- 0.0
alfa  <- 1.0
#alfa  <- 0.001
beta  <- 2.0

# Create model test data
# initial x value
x_0    <- array(NA, n)
y_0    <- array(NA, m)

# generate model data
size_n <- length(df$LON)

y <- array(NA, c(size_n, m))

y[,1] <- df$LON + df$LonOffsets
y[,2] <- df$LAT

x_0[1] <- y[1,1]
x_0[2] <- y[1,2]
x_0[3] <- 0.0
x_0[4] <- 0.0
y_0[1] <- y[1,1]
y_0[2] <- y[1,1]

# ----------------------------------------------------------------------------

model_output <- function(x, t)
{
  y <- x[1:2]

  return (y)
}

# ----------------------------------------------------------------------------

model_state <- function(xp, xlast, t)
{
  seconds_in_days <- 3600 * 24 

  x      <- xp * 0
  xi     <- .External('LandLimit', LFContext, xlast[1], xlast[2], xp[1], xp[2])
  dt     <- as.double(if (t==1) 0.0 else (data.time[t] - data.time[t-1]))
  x[1:4] <- .External('SpeedAndLandLimit', LFContext, xi[1], xi[2], xp[3], xp[4], dt * seconds_in_days, max_speed)
  
  if (.External('PointOnLand', LFContext, xlast[1], xlast[2]))
  {
    browser()
  }

  if (.External('PointOnLand', LFContext, xi[1], xi[2]))
  {
    browser()
  }

  if (.External('PointOnLand', LFContext, x[1], x[2]))
  {
    browser()
  }
 
  if (any(is.na(x)))
  {
    browser()
  }

  return (x)
}

# ----------------------------------------------------------------------------

model_limit_state <- function(xp, xlast, t)
{
  x <- xp

  if (.External('PointOnLand', LFContext, xlast[1], xlast[2]))
  {
    browser()
  }

  x[1:2]  <- .External('LandLimit', LFContext, xlast[1], xlast[2], xp[1], xp[2])

  if (any(is.na(x)))
  {
    browser()
  }

  if (.External('PointOnLand', LFContext, x[1], x[2]))
  {
    browser()
  }

  return (x)
}

# ----------------------------------------------------------------------------

# create the object instance
UKF.Context <- UKF.create(n,
                          m,
                          size_n,
                          kappa,
                          alfa,
                          beta,
                          model_output, 
                          environment(), 
                          F, 
                          model_state, 
                          environment(), 
                          F, 
                          model_limit_state,
                          environment(), 
                          F, 
                          y)

est_state  <- array(as.double(NA), c(size_n, n))
est_output <- array(as.double(NA), c(size_n, m))
smt_state  <- array(as.double(NA), c(size_n, n))
smt_output <- array(as.double(NA), c(size_n, m))

R         <- initR(df)
Q         <- QandQscaling$Q
Qscaling  <- QandQscaling$Qscaling
Qscaling  <- Qscaling / 10

# run filtering
UKF.filter(UKF.Context,
          est_state,
          est_output,
          Q, 
          Qscaling, 
          R, 
          x_0)

est_output[,1] <- est_output[,1] - df$LonOffsets

# ----------------------------------------------------------------------------

xlim <- c(min(df$LON, na.rm=T),max(df$LON, na.rm=T))
ylim <- c(min(df$LAT, na.rm=T),max(df$LAT, na.rm=T))

require(ozmaps)
ozmap(xlim=xlim, ylim=ylim)
points(df$LON,df$LAT, col='green')
points(est_output, col='red')
lines(est_output, col='red')

# Whats wrong with smoothing
UKF.smooth(UKF.Context,
           smt_state,
           smt_output,
           as.raw(T))

points(smt_output, col='blue')
lines(smt_output, col='blue')


#closer view 
xlim <- c(146, 149)
ylim <- c(-44, -42)

ozmap(xlim=xlim, ylim=ylim)
points(df$LON,df$LAT, col='green')
points(est_output, col='red')
lines(est_output, col='red')
points(smt_output, col='blue')
lines(smt_output, col='blue')


# ----------------------------------------------------------------------------

df2           <- addInterpolationPoints(df)
QandQscaling2 <- estimateQ(df2)
data.time2    <- df2$t

# ----------------------------------------------------------------------------

model_output2 <- function(x, t)
{
  y <- x[1:2]

  return (y)
}

# ----------------------------------------------------------------------------

model_state2 <- function(xp, xlast, t)
{
  seconds_in_days <- 3600 * 24 

  x      <- xp * 0
  xi     <- .External('LandLimit', LFContext, xlast[1], xlast[2], xp[1], xp[2])
  dt     <- as.double(if (t==1) 0.0 else (data.time2[t] - data.time2[t-1]))
  x[1:4] <- .External('SpeedAndLandLimit', LFContext, xi[1], xi[2], xp[3], xp[4], dt * seconds_in_days, max_speed)

  return (x)
}

# ----------------------------------------------------------------------------

model_limit_state2 <- function(xp, xlast, t)
{
  x      <- xp
  x[1:2] <- .External('LandLimit', LFContext, xlast[1], xlast[2], xp[1], xp[2])

  return (x)
}

# ----------------------------------------------------------------------------

x2_0    <- array(NA, n)
y2_0    <- array(NA, m)

# generate model data
size_n2 <- length(df2$LON)

y2 <- array(NA, c(size_n2, m))

y2[,1] <- df2$LON + df2$LonOffsets
y2[,2] <- df2$LAT

x2_0[1] <- y[1,1]
x2_0[2] <- y[1,2]
x2_0[3] <- 0.0
x2_0[4] <- 0.0
y2_0[1] <- y[1,1]
y2_0[2] <- y[1,1]

UKF.Context2 <- UKF.create(n,
                           m,
                           size_n2,
                           kappa,
                           alfa,
                           beta,
                           model_output2, 
                           environment(), 
                           F, 
                           model_state2, 
                           environment(), 
                           F, 
                           model_limit_state2,
                           environment(), 
                           F, 
                           y2)

est_state2  <- array(as.double(NA), c(size_n2, n))
est_output2 <- array(as.double(NA), c(size_n2, m))
smt_state2  <- array(as.double(NA), c(size_n2, n))
smt_output2 <- array(as.double(NA), c(size_n2, m))

R2         <- initR(df2)
Q2         <- QandQscaling2$Q
Qscaling2  <- QandQscaling2$Qscaling
Qscaling2  <- Qscaling2 / 100
Qscaling2  <- Qscaling2 / 10

# run filtering
UKF.filter(UKF.Context2,
          est_state2,
          est_output2,
          Q2, 
          Qscaling2, 
          R2, 
          x2_0)

est_output2[,1] <- est_output2[,1] - df2$LonOffsets

# ----------------------------------------------------------------------------

xlim <- c(min(df2$LON, na.rm=T),max(df2$LON, na.rm=T))
ylim <- c(min(df2$LAT, na.rm=T),max(df2$LAT, na.rm=T))

require(ozmaps)
ozmap(xlim=xlim, ylim=ylim)
points(df2$LON,df2$LAT, col='green')
points(est_output2, col='red')
lines(est_output2, col='red')

# Whats wrong with smoothing
UKF.smooth(UKF.Context2,
           smt_state2,
           smt_output2,
           as.raw(T))

points(smt_output2, col='blue')
lines(smt_output2, col='blue')


#closer view 
xlim <- c(146, 149)
ylim <- c(-44, -42)

ozmap(xlim=xlim, ylim=ylim)
points(df2$LON,df2$LAT, col='green')
points(est_output2, col='red')
lines(est_output2, col='red')
points(smt_output2, col='blue')
lines(smt_output2, col='blue')


