require(Oarray)

OmB.destroy <- function(Context)
{
  return (.External('_OmB.destroy', Context))
}

OmB.create <- function(nsim, npop, nages, nsubyears, nareas, nfleets, Recsubyr)
{
  return (.External('_OmB.create', as.integer(nsim), as.integer(npop), as.integer(nages), as.integer(nsubyears), as.integer(nareas), as.integer(nfleets), as.integer(Recsubyr)))
}

OmB.get.aR <- function(Context, ...)
{
  return (.External('_OmB.get.aR', Context, list(...)))
}

OmB.set.aR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.aR', Context, as.double(Arg), list(...)))
}

OmB.get.nt.aR <- function(Context, ...)
{
  return (.External('_OmB.get.nt.aR', Context, list(...)))
}

OmB.set.nt.aR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.aR', Context, as.double(Arg), list(...)))
}

OmB.get.B0 <- function(Context, ...)
{
  return (.External('_OmB.get.B0', Context, list(...)))
}

OmB.set.B0 <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.B0', Context, as.double(Arg), list(...)))
}

OmB.get.nt.B0 <- function(Context, ...)
{
  return (.External('_OmB.get.nt.B0', Context, list(...)))
}

OmB.set.nt.B0 <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.B0', Context, as.double(Arg), list(...)))
}

OmB.get.bR <- function(Context, ...)
{
  return (.External('_OmB.get.bR', Context, list(...)))
}

OmB.set.bR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.bR', Context, as.double(Arg), list(...)))
}

OmB.get.nt.bR <- function(Context, ...)
{
  return (.External('_OmB.get.nt.bR', Context, list(...)))
}

OmB.set.nt.bR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.bR', Context, as.double(Arg), list(...)))
}

OmB.get.EforYear <- function(Context, ...)
{
  return (.External('_OmB.get.EforYear', Context, list(...)))
}

OmB.set.EforYear <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.EforYear', Context, as.double(Arg), list(...)))
}

OmB.get.nt.EforYear <- function(Context, ...)
{
  return (.External('_OmB.get.nt.EforYear', Context, list(...)))
}

OmB.set.nt.EforYear <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.EforYear', Context, as.double(Arg), list(...)))
}

OmB.get.eforyearb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.eforyearb2_par', Context, list(...)))
}

OmB.set.eforyearb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.eforyearb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.eforyearb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.eforyearb2_par', Context, list(...)))
}

OmB.set.nt.eforyearb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.eforyearb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.eforyeard1_par <- function(Context, ...)
{
  return (.External('_OmB.get.eforyeard1_par', Context, list(...)))
}

OmB.set.eforyeard1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.eforyeard1_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.eforyeard1_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.eforyeard1_par', Context, list(...)))
}

OmB.set.nt.eforyeard1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.eforyeard1_par', Context, as.double(Arg), list(...)))
}

OmB.get.FM <- function(Context, ...)
{
  return (.External('_OmB.get.FM', Context, list(...)))
}

OmB.set.FM <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.FM', Context, as.double(Arg), list(...)))
}

OmB.get.nt.FM <- function(Context, ...)
{
  return (.External('_OmB.get.nt.FM', Context, list(...)))
}

OmB.set.nt.FM <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.FM', Context, as.double(Arg), list(...)))
}

OmB.get.fmb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.fmb2_par', Context, list(...)))
}

OmB.set.fmb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.fmb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.fmb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.fmb2_par', Context, list(...)))
}

OmB.set.nt.fmb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.fmb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.fmd1_par <- function(Context, ...)
{
  return (.External('_OmB.get.fmd1_par', Context, list(...)))
}

OmB.set.fmd1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.fmd1_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.fmd1_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.fmd1_par', Context, list(...)))
}

OmB.set.nt.fmd1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.fmd1_par', Context, as.double(Arg), list(...)))
}

OmB.initialiseParameters <- function(Context, M, R0, mat, Idist, Wt_age, h)
{
  return (.External('_OmB.initialiseParameters', Context, M, R0, mat, Idist, Wt_age, h))
}

OmB.nt.initialiseParameters <- function(Context, M, R0, mat, Idist, Wt_age, h)
{
  return (.External('_OmB.nt.initialiseParameters', Context, M, R0, mat, Idist, Wt_age, h))
}

OmB.get.MovN <- function(Context, ...)
{
  return (.External('_OmB.get.MovN', Context, list(...)))
}

OmB.set.MovN <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.MovN', Context, as.double(Arg), list(...)))
}

OmB.get.nt.MovN <- function(Context, ...)
{
  return (.External('_OmB.get.nt.MovN', Context, list(...)))
}

OmB.set.nt.MovN <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.MovN', Context, as.double(Arg), list(...)))
}

OmB.get.movnb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.movnb2_par', Context, list(...)))
}

OmB.set.movnb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.movnb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.movnb2_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.movnb2_par', Context, list(...)))
}

OmB.set.nt.movnb2_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.movnb2_par', Context, as.double(Arg), list(...)))
}

OmB.get.movnd1_par <- function(Context, ...)
{
  return (.External('_OmB.get.movnd1_par', Context, list(...)))
}

OmB.set.movnd1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.movnd1_par', Context, as.double(Arg), list(...)))
}

OmB.get.nt.movnd1_par <- function(Context, ...)
{
  return (.External('_OmB.get.nt.movnd1_par', Context, list(...)))
}

OmB.set.nt.movnd1_par <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.movnd1_par', Context, as.double(Arg), list(...)))
}

OmB.get.MSY_Recdevs <- function(Context, ...)
{
  return (.External('_OmB.get.MSY_Recdevs', Context, list(...)))
}

OmB.set.MSY_Recdevs <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.MSY_Recdevs', Context, as.double(Arg), list(...)))
}

OmB.get.nt.MSY_Recdevs <- function(Context, ...)
{
  return (.External('_OmB.get.nt.MSY_Recdevs', Context, list(...)))
}

OmB.set.nt.MSY_Recdevs <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.MSY_Recdevs', Context, as.double(Arg), list(...)))
}

OmB.get.MSY_RecSpatialDevs <- function(Context, ...)
{
  return (.External('_OmB.get.MSY_RecSpatialDevs', Context, list(...)))
}

OmB.set.MSY_RecSpatialDevs <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.MSY_RecSpatialDevs', Context, as.double(Arg), list(...)))
}

OmB.get.nt.MSY_RecSpatialDevs <- function(Context, ...)
{
  return (.External('_OmB.get.nt.MSY_RecSpatialDevs', Context, list(...)))
}

OmB.set.nt.MSY_RecSpatialDevs <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.MSY_RecSpatialDevs', Context, as.double(Arg), list(...)))
}

OmB.MSYrefs <- function(Context, par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx)
{
  return (.External('_OmB.MSYrefs', Context, par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx))
}

OmB.nt.MSYrefs <- function(Context, par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx)
{
  return (.External('_OmB.nt.MSYrefs', Context, par, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, MSY, BMSY, SSBMSY, SSBMSY_B0, sim_idx))
}

OmB.MSYrefs_objective <- function(Context, par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx)
{
  return (.External('_OmB.MSYrefs_objective', Context, par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx))
}

OmB.nt.MSYrefs_objective <- function(Context, par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx)
{
  return (.External('_OmB.nt.MSYrefs_objective', Context, par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, NBefore, SSN, C, SSBA, ntargets, targpop, run_years, sim_idx))
}

OmB.MSYREFS_OBJECTIVE_DPAR <- function(Context, par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective)
{
  return (.External('_OmB.MSYREFS_OBJECTIVE_DPAR', Context, par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective))
}

OmB.nt.MSYREFS_OBJECTIVE_DPAR <- function(Context, par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective)
{
  return (.External('_OmB.nt.MSYREFS_OBJECTIVE_DPAR', Context, par, pard1_par, nReport, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, SRrel, N, nd1_par, NBefore, nbefored1_par, SSN, C, cd1_par, SSBA, ntargets, targpop, run_years, sim_idx, MSYrefs_objective))
}

OmB.get.nages <- function(Context)
{
  return (.External('_OmB.get.nages', Context))
}

OmB.set.nages <- function(Context, Arg)
{
  return (.External('_OmB.set.nages', Context, as.integer(Arg)))
}

OmB.get.nareas <- function(Context)
{
  return (.External('_OmB.get.nareas', Context))
}

OmB.set.nareas <- function(Context, Arg)
{
  return (.External('_OmB.set.nareas', Context, as.integer(Arg)))
}

OmB.nextYear <- function(Context, N, NBefore)
{
  return (.External('_OmB.nextYear', Context, N, NBefore))
}

OmB.nt.nextYear <- function(Context, N, NBefore)
{
  return (.External('_OmB.nt.nextYear', Context, N, NBefore))
}

OmB.get.nfleets <- function(Context)
{
  return (.External('_OmB.get.nfleets', Context))
}

OmB.set.nfleets <- function(Context, Arg)
{
  return (.External('_OmB.set.nfleets', Context, as.integer(Arg)))
}

OmB.get.npop <- function(Context)
{
  return (.External('_OmB.get.npop', Context))
}

OmB.set.npop <- function(Context, Arg)
{
  return (.External('_OmB.set.npop', Context, as.integer(Arg)))
}

OmB.get.nsim <- function(Context)
{
  return (.External('_OmB.get.nsim', Context))
}

OmB.set.nsim <- function(Context, Arg)
{
  return (.External('_OmB.set.nsim', Context, as.integer(Arg)))
}

OmB.get.nsubyears <- function(Context)
{
  return (.External('_OmB.get.nsubyears', Context))
}

OmB.set.nsubyears <- function(Context, Arg)
{
  return (.External('_OmB.set.nsubyears', Context, as.integer(Arg)))
}

OmB.popdyn_projection_objective <- function(Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx)
{
  return (.External('_OmB.popdyn_projection_objective', Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx))
}

OmB.nt.popdyn_projection_objective <- function(Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx)
{
  return (.External('_OmB.nt.popdyn_projection_objective', Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx))
}

OmB.POPDYN_PROJECTION_OBJECTIVE_BPAR <- function(Context, par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par)
{
  return (.External('_OmB.POPDYN_PROJECTION_OBJECTIVE_BPAR', Context, par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par))
}

OmB.nt.POPDYN_PROJECTION_OBJECTIVE_BPAR <- function(Context, par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par)
{
  return (.External('_OmB.nt.POPDYN_PROJECTION_OBJECTIVE_BPAR', Context, par, parb2_par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, Wt_age_mid, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, nb2_par, NBefore, nbeforeb2_par, SSN, C, cb2_par, SSBA, sim_idx, popdyn_projection_objectiveb2_par))
}

OmB.get.Recsubyr <- function(Context, ...)
{
  return (.External('_OmB.get.Recsubyr', Context, list(...)))
}

OmB.set.Recsubyr <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.Recsubyr', Context, as.integer(Arg), list(...)))
}

OmB.get.nt.Recsubyr <- function(Context, ...)
{
  return (.External('_OmB.get.nt.Recsubyr', Context, list(...)))
}

OmB.set.nt.Recsubyr <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.Recsubyr', Context, as.integer(Arg), list(...)))
}

OmB.runHistoric <- function(Context, totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA)
{
  return (.External('_OmB.runHistoric', Context, totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA))
}

OmB.nt.runHistoric <- function(Context, totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA)
{
  return (.External('_OmB.nt.runHistoric', Context, totF, qy, ECurrent, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA))
}

OmB.runProjection <- function(Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx)
{
  return (.External('_OmB.runProjection', Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx))
}

OmB.nt.runProjection <- function(Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx)
{
  return (.External('_OmB.nt.runProjection', Context, par, npar, nfixed, TAC, TAE, FbyPar, FbyFixed, ECurrent, qy, R0, M, mat, Idist, Len_age, Wt_age, sel, mov, h, Recdist, Recdevs, RecSpatialDevs, SRrel, N, NBefore, SSN, C, SSBA, sim_idx))
}

OmB.get.SpawnPerYr <- function(Context)
{
  return (.External('_OmB.get.SpawnPerYr', Context))
}

OmB.set.SpawnPerYr <- function(Context, Arg)
{
  return (.External('_OmB.set.SpawnPerYr', Context, as.integer(Arg)))
}

OmB.get.SSB0 <- function(Context, ...)
{
  return (.External('_OmB.get.SSB0', Context, list(...)))
}

OmB.set.SSB0 <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.SSB0', Context, as.double(Arg), list(...)))
}

OmB.get.nt.SSB0 <- function(Context, ...)
{
  return (.External('_OmB.get.nt.SSB0', Context, list(...)))
}

OmB.set.nt.SSB0 <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.SSB0', Context, as.double(Arg), list(...)))
}

OmB.get.SSBpR <- function(Context, ...)
{
  return (.External('_OmB.get.SSBpR', Context, list(...)))
}

OmB.set.SSBpR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.SSBpR', Context, as.double(Arg), list(...)))
}

OmB.get.nt.SSBpR <- function(Context, ...)
{
  return (.External('_OmB.get.nt.SSBpR', Context, list(...)))
}

OmB.set.nt.SSBpR <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.SSBpR', Context, as.double(Arg), list(...)))
}

OmB.get.surv <- function(Context, ...)
{
  return (.External('_OmB.get.surv', Context, list(...)))
}

OmB.set.surv <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.surv', Context, as.double(Arg), list(...)))
}

OmB.get.nt.surv <- function(Context, ...)
{
  return (.External('_OmB.get.nt.surv', Context, list(...)))
}

OmB.set.nt.surv <- function(Context, Arg, ...)
{
  return (.External('_OmB.set.nt.surv', Context, as.double(Arg), list(...)))
}

