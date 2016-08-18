// ----------------------------------------------------------------------------
// MSE operating model implemented with ADT and ADlib
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "Mseom.hpp"
#include <R.h>


// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_init_parameters(const ARRAY_3D M/* nages, npop, nsim */,
                                                const ARRAY_2D R0/* npop, nsim */,
                                                const ARRAY_3D mat/* nages, npop, nsim */,
                                                const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                                const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                                const ARRAY_2D h/* npop, nsim */,
                                                const int sim_idx)
{
  int    ca;
  int    cp;
  int    cr;
  double dN;
  double dB;
  double dSSB;

  // Work out survivorship
  // surv=t(exp(-cumsum(c(0,M[,1:(nages-1),1])/nsubyears)))
  for (cp = 1 ; cp <= npop ; cp++)
  {
    surv[1][cp][sim_idx] = 0.0;

    for (ca = 2 ; ca <= nages ; ca++)
    {
      surv[ca][cp][sim_idx] = surv[ca - 1][cp][sim_idx] + M[ca - 1][cp][sim_idx];
    }
  }

  for (cp = 1 ; cp <= npop ; cp++)
  {
    for (ca = 1 ; ca < nages ; ca++)
    {
      surv[ca][cp][sim_idx] = exp(-surv[ca][cp][sim_idx] / nsubyears);
    }

    // infinite sum for plus group
    // surv[,nages] <- surv[,nages-1]*exp(-Madvanced[,nages]/nsubyears)/(1-exp(-Madvanced[,nages]/nsubyears))
    surv[nages][cp][sim_idx] = surv[nages - 1][cp][sim_idx] * exp(-M[nages][cp][sim_idx] / nsubyears) / (1.0 - exp(-M[nages][cp][sim_idx] / nsubyears));
  }

  // Work out SSB0, B0, SSBpR, aR, bR
  for (cp = 1 ; cp <= npop ; cp++)
  {
    SSB0[cp][sim_idx] = 0.0;
    B0[cp][sim_idx]   = 0.0;

    for (ca = 1 ; ca <= nages ; ca++)
    {
      for (cr = 1 ; cr <= nareas ; cr++)
      {
        dN    = surv[ca][cp][sim_idx] * R0[cp][sim_idx] * Idist[cr][ca][cp][sim_idx];
        dB    = dN * Wt_age[ca][cp][sim_idx];
        dSSB  = dB * mat[ca][cp][sim_idx];

        B0[cp][sim_idx]   += dB;
        SSB0[cp][sim_idx] += dSSB;
      }
    }

    SSBpR[cp][sim_idx] = SSB0[cp][sim_idx] / R0[cp][sim_idx];
    bR[cp][sim_idx]    = log(5.0 * h[cp][sim_idx]) / (0.8 * SSB0[cp][sim_idx]);
    aR[cp][sim_idx]    = exp(bR[cp][sim_idx] * SSB0[cp][sim_idx]) / SSBpR[cp][sim_idx];
  }
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_next_year(ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                          ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                          const int sim_idx)
{
  int cr;
  int ca;
  int cp;

  for (cr = 1 ; cr <= nareas ; cr++)
  {
    for (ca = 1 ; ca <= nages ; ca++)
    {
      for (cp = 1 ; cp <= npop ; cp++)
      {
        N[cr][1][ca][cp][sim_idx]       = N[cr][nsubyears + 1][ca][cp][sim_idx];
        NBefore[cr][1][ca][cp][sim_idx] = NBefore[cr][nsubyears + 1][ca][cp][sim_idx];
      }
    }
  }
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_init(const ARRAY_2D R0/* npop, nsim */,
                                     const ARRAY_3D mat/* nages, npop, nsim */,
                                     const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                     ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                     const int sim_idx)
{
  int    ca;
  int    cp;
  int    cr;
  int    mm;
  double dN;
  double dNBefore;
  double dSSN;

  mm = 1;

  // N[PAYMR]<-surv[PA]*R0[P]*Idist[PAR]                         # Calculate virgin Numbers
  // SSN[PAYMR] <- N[PAYMR] * mat[PAY]
  // SSB[PAYMR]<-SSN[PAYMR]*Wt_age[PAY]                          # Calculate spawning stock biomass
  for (cp = 1 ; cp <= npop ; cp++)
  {
    for (ca = 1 ; ca <= nages ; ca++)
    {
      for (cr = 1 ; cr <= nareas ; cr++)
      {
        dN        = surv[ca][cp][sim_idx] * R0[cp][sim_idx] * Idist[cr][ca][cp][sim_idx] * 0.3;
        dNBefore  = dN;
        dSSN      = dN * mat[ca][cp][sim_idx];

        N[cr][mm][ca][cp][sim_idx]        = dN;
        NBefore[cr][mm][ca][cp][sim_idx]  = dNBefore;
        SSN[cr][mm][ca][cp][sim_idx]      = dSSN;
      }
    }
  }
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_year(const ARRAY_2D qy/* nfleets, nsim */,
                                     const ARRAY_2D R0/* npop, nsim */,
                                     const ARRAY_3D M/* nages, npop, nsim */,
                                     const ARRAY_3D mat/* nages, npop, nsim */,
                                     const ARRAY_3D Len_age/* nages, npop, nsim */,
                                     const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                     const ARRAY_3D sel/* nages, nfleets, nsim */,
                                     const ARRAY_4D Eannual/* nfleets, nareas, nsubyears, nsim */,
                                     const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                     const ARRAY_2D h/* npop, nsim */,
                                     const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                     const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                     const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                     const ARRAY_1I SRrel/* npop */,
                                     ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                     ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                     ARRAY_2D SSBA/* npop, nsim */,
                                     int bIgnoreLast,
                                     const int sim_idx)
{
  int    ca;
  int    cp;
  int    cf;
  int    cr;
  int    cs;
  int    cr2;
  double dSSN;
  double dSSB;
  double dSSB_area;
  double dFtot;
  double dFM;
  double dZ;
  double dRecruitment;
  double dN;
  double dPlusGroup;
  int    nRecdevIdx;

  nRecdevIdx  = 1;

  for (cs = 1 ; cs <= nsubyears ; cs++)
  {
    for (cp = 1 ; cp <= npop ; cp++)
    {
      // Update SSB and SSN and do recruitment.
      dSSB = 0.0;

      for (cr = 1 ; cr <= nareas ; cr++)
      {
        dSSB_area = 0.0;

        for (ca = 1 ; ca <= nages ; ca++)
        {
          dSSN                         = NBefore[cr][cs][ca][cp][sim_idx] * mat[ca][cp][sim_idx];
          SSN[cr][cs][ca][cp][sim_idx] = dSSN;
          dSSB_area                   += dSSN * Wt_age[ca][cp][sim_idx];
        }

        dSSB += dSSB_area;
      }

      SSBA[cp][sim_idx] = dSSB;

      // Run recruitment
      if (Recsubyr[cs] != 0)
      {
        //rec<-OM@Recdevs[,pp,RecdevInd]*((0.8*OM@R0[,pp]*OM@h[,pp]*SSBA[,pp,y])/(0.2*SSBpR[,pp]*OM@R0[,pp]*(1-OM@h[,pp])+(OM@h[,pp]-0.2)*SSBA[,pp,y]))
        if (SRrel[cp] == 1)
        {
          // Beverton Holt stock recruitment relationship
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * ((0.8 * R0[cp][sim_idx] * h[cp][sim_idx] * dSSB) / (0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (1.0 - h[cp][sim_idx]) + (h[cp][sim_idx] - 0.2) * dSSB));
        }
        else
        {
          // Most transparent form of the Ricker uses alpha and beta params
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * aR[cp][sim_idx] * dSSB * exp(-bR[cp][sim_idx] * dSSB);
        }

        for (cr = 1 ; cr <= nareas ; cr++)
        {
          NBefore[cr][cs][1][cp][sim_idx] = dRecruitment * RecSpatialDevs[cr][cp][sim_idx] * Recdist[cr][cp][sim_idx];
          N[cr][cs][1][cp][sim_idx]       = NBefore[cr][cs][1][cp][sim_idx];
        }
      }

      // Move Fish
      for (ca = 1 ; ca <= nages ; ca++)
      {
        for (cr = 1 ; cr <= nareas ; cr++)
        {
          // N[,,y,m,]<-domov2(N[,,y,m,],mov[,,m,,])
          dN = 0.0;

          for (cr2 = 1 ; cr2 <= nareas ; cr2++)
          {
            dN += N[cr2][cs][ca][cp][sim_idx] * mov[cr][cr2][cs][ca][cp][sim_idx];
          }

          MovN[cr][sim_idx] = dN;
        }

        for (cr = 1 ; cr <= nareas ; cr++)
        {
          N[cr][cs][ca][cp][sim_idx] = MovN[cr][sim_idx];
        }
      }

      // Fishing and natural mortality
      for (ca = 1 ; ca <= nages ; ca++)
      {
        for (cr = 1 ; cr <= nareas ; cr++)
        {
          dFtot = 0.0;

          for (cf = 1 ; cf <= nfleets ; cf++)
          {
            //FM[PAYMRF2] <- totF*ECurrent[MRF2]*sel[FA2]
            dFM = Eannual[cf][cr][cs][sim_idx] * sel[ca][cf][sim_idx] * qy[cf][sim_idx];

            FM[cf][sim_idx] = dFM;
            dFtot          += dFM;
          }

          //Ftot <- apply(FM[,,y,m,,,drop=F],c(1,2,5),sum)
          //Z[PAYMR] <- Ftot[PAR]+M[PAY]/nsubyears
          dZ = dFtot + (M[ca][cp][sim_idx] / nsubyears);

          for (cf = 1 ; cf <= nfleets ; cf++)
          {
            //C[PAYMRF2] <- N[PAYMR2]*(1-exp(-Z[PAYMR2]))*(FM[PAYMRF2]/Z[PAYMR2])
            C[cf][cr][cs][ca][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx] * (1 - exp(-dZ)) * (FM[cf][sim_idx] / dZ);
          }

          //N[,,y,m,]<-N[,,y,m,]*exp(-Z[,,y,m,])
          N[cr][cs][ca][cp][sim_idx] *= exp(-dZ);
        }
      }

      if ((cs != nsubyears) || (bIgnoreLast == 0))
      {
        // Age fish.
        //N[,pp,nages-1,y,mm,]          <- N[,pp,nages-1,y,mm,] + N[,pp,nages,y,mm,]
        //NBefore[,pp,2:nages,y,mm+1,]  <- N[,pp,1:(nages-1),y,mm,]
        //NBefore[,pp,1,y,mm+1,]        <- rec*recSpatialDevs[,pp,]
        //N[,pp,,y,mm+1,]               <- NBefore[,pp,,y,mm+1,]
        for (cr = 1 ; cr <= nareas ; cr++)
        {
          dPlusGroup                          = N[cr][cs][nages][cp][sim_idx];
          NBefore[cr][cs + 1][1][cp][sim_idx] = 0.0;
          N[cr][cs + 1][1][cp][sim_idx]       = 0.0;

          for (ca = nages - 1 ; ca >= 1 ; ca--)
          {
            NBefore[cr][cs + 1][ca + 1][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx];
            N[cr][cs + 1][ca + 1][cp][sim_idx]       = NBefore[cr][cs + 1][ca + 1][cp][sim_idx];
          }

          NBefore[cr][cs + 1][nages][cp][sim_idx] += dPlusGroup;
          N[cr][cs + 1][nages][cp][sim_idx]       += dPlusGroup;
        }
      }
    }

    if (Recsubyr[cs] != 0)
    {
      nRecdevIdx++;
    }
  } // end nsubyears
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn(double totF,
                                const ARRAY_2D qy/* nfleets, nsim */,
                                const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */,
                                const ARRAY_2D R0/* npop, nsim */,
                                const ARRAY_3D M/* nages, npop, nsim */,
                                const ARRAY_3D mat/* nages, npop, nsim */,
                                const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                const ARRAY_3D Len_age/* nages, npop, nsim */,
                                const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                const ARRAY_3D sel/* nages, nfleets, nsim */,
                                const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                const ARRAY_2D h/* npop, nsim */,
                                const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                const ARRAY_1I SRrel/* npop */,
                                ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                ARRAY_2D SSBA/* npop, nsim */,
                                const int sim_idx)
{
  int cf;
  int cr;
  int cs;

  for (cf = 1 ; cf <= nfleets ; cf++)
  {
    for (cr = 1 ; cr <= nareas ; cr++)
    {
      for (cs = 1 ; cs <= nsubyears ; cs++)
      {
        EforYear[cf][cr][cs][sim_idx] = totF * ECurrent[cf][cr][cs][sim_idx];
      }
    }
  }

  popdyn_year(qy,
              R0,
              M,
              mat,
              Len_age,
              Wt_age,
              sel,
              EforYear,
              mov,
              h,
              Recdist,
              Recdevs,
              RecSpatialDevs,
              SRrel,
              N,
              NBefore,
              SSN,
              C,
              SSBA,
              0,
              sim_idx);
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_projection_par(const ARRAY_1D par/* 0:npar-1 */,
                                               const int npar,
                                               const int nfixed,
                                               const ARRAY_1D TAE/* 0:nfixed-1 */,
                                               const ARRAY_1I FbyPar/* 0:npar-1 */,
                                               const ARRAY_1I FbyFixed/* 0:nfixed-1 */,
                                               const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */,
                                               const ARRAY_2D qy/* nfleets, nsim */,
                                               const ARRAY_2D R0/* npop, nsim */,
                                               const ARRAY_3D M/* nages, npop, nsim */,
                                               const ARRAY_3D mat/* nages, npop, nsim */,
                                               const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                               const ARRAY_3D Len_age/* nages, npop, nsim */,
                                               const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                               const ARRAY_3D sel/* nages, nfleets, nsim */,
                                               const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                               const ARRAY_2D h/* npop, nsim */,
                                               const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                               const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                               const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                               const ARRAY_1I SRrel/* npop */,
                                               ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                               ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                               ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                               ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                               ARRAY_2D SSBA/* npop, nsim */,
                                               int bIgnoreLast,
                                               const int sim_idx)
{
  int     cr;
  int     cf;
  int     cs;
  int     cx;

  for (cr = 1 ; cr <= nareas ; cr++)
  {
    // Set effort series for year
    for (cx = 0 ; cx < npar ; cx++)
    {
      cf = FbyPar[cx];

      for (cs = 1 ; cs <= nsubyears ; cs++)
      {
        EforYear[cf][cr][cs][sim_idx] = exp(par[cx]) * ECurrent[cf][cr][cs][sim_idx];
      }
    }

    for (cx = 0 ; cx < nfixed ; cx++)
    {
      cf = FbyFixed[cx];

      for (cs = 1 ; cs <= nsubyears ; cs++)
      {
        EforYear[cf][cr][cs][sim_idx] = TAE[cx] * ECurrent[cf][cr][cs][sim_idx];
      }
    }
  }

  // Initialise N and SSN
  popdyn_next_year(N,
                   NBefore,
                   sim_idx);

  popdyn_year(qy,
              R0,
              M,
              mat,
              Len_age,
              Wt_age,
              sel,
              EforYear,
              mov,
              h,
              Recdist,
              Recdevs,
              RecSpatialDevs,
              SRrel,
              N,
              NBefore,
              SSN,
              C,
              SSBA,
              bIgnoreLast,
              sim_idx);
}

// ----------------------------------------------------------------------------

void OperatingModelBase::popdyn_MSY_par(const double par,
                                        const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */,
                                        const ARRAY_2D qy/* nfleets, nsim */,
                                        const ARRAY_2D R0/* npop, nsim */,
                                        const ARRAY_3D M/* nages, npop, nsim */,
                                        const ARRAY_3D mat/* nages, npop, nsim */,
                                        const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                        const ARRAY_3D Len_age/* nages, npop, nsim */,
                                        const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                        const ARRAY_3D sel/* nages, nfleets, nsim */,
                                        const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                        const ARRAY_2D h/* npop, nsim */,
                                        const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                        const ARRAY_1I SRrel/* npop */,
                                        ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                        ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                        ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                        ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                        ARRAY_2D SSBA/* npop, nsim */,
                                        const int run_years,
                                        const int sim_idx)
{
  int     cy;
  int     cf;
  int     cr;
  int     cs;
  double  totF;

  totF  = exp(par);

  popdyn_init(R0,
              mat,
              Idist,
              N,
              NBefore,
              SSN,
              sim_idx);

  for (cf = 1 ; cf <= nfleets ; cf++)
  {
    for (cr = 1 ; cr <= nareas ; cr++)
    {
      for (cs = 1 ; cs <= nsubyears ; cs++)
      {
        EforYear[cf][cr][cs][sim_idx] = totF * ECurrent[cf][cr][cs][sim_idx];
      }
    }
  }

  for (cy = 1 ; cy < run_years ; cy++)
  {
    popdyn_year(qy,
                R0,
                M,
                mat,
                Len_age,
                Wt_age,
                sel,
                EforYear,
                mov,
                h,
                Recdist,
                MSY_Recdevs,
                MSY_RecSpatialDevs,
                SRrel,
                N,
                NBefore,
                SSN,
                C,
                SSBA,
                0,
                sim_idx);

    popdyn_next_year(N,
                     NBefore,
                     sim_idx);
  }

  popdyn_year(qy,
              R0,
              M,
              mat,
              Len_age,
              Wt_age,
              sel,
              EforYear,
              mov,
              h,
              Recdist,
              MSY_Recdevs,
              MSY_RecSpatialDevs,
              SRrel,
              N,
              NBefore,
              SSN,
              C,
              SSBA,
              0,
              sim_idx);
}

// ----------------------------------------------------------------------------

OperatingModelBase::OperatingModelBase(
#include "OmB_constructor_args.hpp"
)
 : AdtArrays()
{
  int cn;

  #include "OmB_constructor_locals.hpp"
  #include "OmB_constructor_scalars_phase_1.hpp"
  #include "OmB_constructor_arrays_phase_1.hpp"

  // Initialise SpawnPerYr based on number of spawning events in Recsubyr
  SpawnPerYr = 0;

  for (cn = 1 ; cn <= nsubyears ; cn++)
  {
    if (Recsubyr[cn] != 0)
    {
      SpawnPerYr++;
    }
  }

  #include "OmB_constructor_scalars_phase_2.hpp"
  #include "OmB_constructor_arrays_phase_2.hpp"
  #include "OmB_array_plans_init.hpp"

  set_all(MSY_Recdevs, 1.0);
  set_all(MSY_RecSpatialDevs, 1.0);
}

// ----------------------------------------------------------------------------

OperatingModelBase::OperatingModelBase(const OperatingModelBase& rCopy)
 : AdtArrays(rCopy)
#include "OmB_array_plans_copy.hpp"
{
  // Do a shallow object copy
  nsim                = rCopy.nsim;
  npop                = rCopy.npop;
  nages               = rCopy.nages;
  nsubyears           = rCopy.nsubyears;
  nareas              = rCopy.nareas;
  nfleets             = rCopy.nfleets;
  surv                = rCopy.surv;

  Recsubyr            = rCopy.Recsubyr;

  SpawnPerYr          = rCopy.SpawnPerYr;

  EforYear            = rCopy.EforYear;
  B0                  = rCopy.B0;
  SSB0                = rCopy.SSB0;
  SSBpR               = rCopy.SSBpR;
  aR                  = rCopy.aR;
  bR                  = rCopy.bR;
  FM                  = rCopy.FM;
  MovN                = rCopy.MovN;

  MSY_Recdevs         = rCopy.MSY_Recdevs;
  MSY_RecSpatialDevs  = rCopy.MSY_RecSpatialDevs;
}

// ----------------------------------------------------------------------------

OperatingModelBase::~OperatingModelBase()
{

}

// ----------------------------------------------------------------------------

void OperatingModelBase::initialiseParameters(const ARRAY_3D M/* nages, npop, nsim */,
                                              const ARRAY_2D R0/* npop, nsim */,
                                              const ARRAY_3D mat/* nages, npop, nsim */,
                                              const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                              const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                              const ARRAY_2D h/* npop, nsim */)
{
  int sim_idx;

  for (sim_idx = 1 ; sim_idx <= nsim ; sim_idx++)
  {
    popdyn_init_parameters(M,
                           R0,
                           mat,
                           Idist,
                           Wt_age,
                           h,
                           sim_idx);
  }
}

// ----------------------------------------------------------------------------

void OperatingModelBase::nextYear(ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                  ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */)
{
  int sim_idx;

  for (sim_idx = 1 ; sim_idx <= nsim ; sim_idx++)
  {
    popdyn_next_year(N,
                     NBefore,
                     sim_idx);
  }
}

// ----------------------------------------------------------------------------

double OperatingModelBase::popdyn_projection_objective(const ARRAY_1D par/* 0:npar-1 */,
                                                       const int npar,
                                                       const int nfixed,
                                                       const ARRAY_1D TAC/* 0:npar-1 */,
                                                       const ARRAY_1D TAE/* 0:nfixed-1 */,
                                                       const ARRAY_1I FbyPar/* 0:npar-1 */,
                                                       const ARRAY_1I FbyFixed/* 0:nfixed-1 */,
                                                       const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */,
                                                       const ARRAY_2D qy/* nfleets, nsim */,
                                                       const ARRAY_2D R0/* npop, nsim */,
                                                       const ARRAY_3D M/* nages, npop, nsim */,
                                                       const ARRAY_3D mat/* nages, npop, nsim */,
                                                       const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                                       const ARRAY_3D Len_age/* nages, npop, nsim */,
                                                       const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                                       const ARRAY_3D Wt_age_mid/* nages, npop, nsim */,
                                                       const ARRAY_3D sel/* nages, nfleets, nsim */,
                                                       const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                                       const ARRAY_2D h/* npop, nsim */,
                                                       const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                                       const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                                       const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                                       const ARRAY_1I SRrel/* npop */,
                                                       ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                                       ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                                       ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                                       ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                                       ARRAY_2D SSBA/* npop, nsim */,
                                                       const int sim_idx)
{
  int     cs;
  int     cf;
  int     cr;
  int     ca;
  int     cp;
  int     cx;
  double  dTACError;
  double  dObjective;
  double  dBiomass;
  double  dCatchBiomass;

  popdyn_projection_par(par,
                        npar,
                        nfixed,
                        TAE,
                        FbyPar,
                        FbyFixed,
                        ECurrent,
                        qy,
                        R0,
                        M,
                        mat,
                        Idist,
                        Len_age,
                        Wt_age,
                        sel,
                        mov,
                        h,
                        Recdist,
                        Recdevs,
                        RecSpatialDevs,
                        SRrel,
                        N,
                        NBefore,
                        SSN,
                        C,
                        SSBA,
                        1,
                        sim_idx);

  dObjective = 0.0;

  for (cx = 0 ; cx < npar ; cx++)
  {
    dBiomass      = 0.0;
    dCatchBiomass = 1.0e-6;
    cf            = FbyPar[cx];

    for (cr = 1 ; cr <= nareas ; cr++)
    {
      for (ca = 1 ; ca <= nages ; ca++)
      {
        for (cp = 1 ; cp <= npop ; cp++)
        {
          for (cs = 1 ; cs <= nsubyears ; cs++)
          {
            dCatchBiomass += C[cf][cr][cs][ca][cp][sim_idx] * Wt_age_mid[ca][cp][sim_idx];
          }
        }
      }
    }

    dTACError     = log(TAC[cx] / dCatchBiomass);
    dObjective   += (dTACError * dTACError);
  }

  return (dObjective);
}

// ----------------------------------------------------------------------------

void OperatingModelBase::runProjection(const ARRAY_1D par/* 0:npar-1 */,
                                       const int npar,
                                       const int nfixed,
                                       const ARRAY_1D TAC/* 0:npar-1 */,
                                       const ARRAY_1D TAE/* 0:nfixed-1 */,
                                       const ARRAY_1I FbyPar/* 0:npar-1 */,
                                       const ARRAY_1I FbyFixed/* 0:nfixed-1 */,
                                       const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */,
                                       const ARRAY_2D qy/* nfleets, nsim */,
                                       const ARRAY_2D R0/* npop, nsim */,
                                       const ARRAY_3D M/* nages, npop, nsim */,
                                       const ARRAY_3D mat/* nages, npop, nsim */,
                                       const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                       const ARRAY_3D Len_age/* nages, npop, nsim */,
                                       const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                       const ARRAY_3D sel/* nages, nfleets, nsim */,
                                       const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                       const ARRAY_2D h/* npop, nsim */,
                                       const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                       const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                       const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                       const ARRAY_1I SRrel/* npop */,
                                       ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                       ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                       ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                       ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                       ARRAY_2D SSBA/* npop, nsim */,
                                       const int sim_idx)
{
  popdyn_projection_par(par,
                        npar,
                        nfixed,
                        TAE,
                        FbyPar,
                        FbyFixed,
                        ECurrent,
                        qy,
                        R0,
                        M,
                        mat,
                        Idist,
                        Len_age,
                        Wt_age,
                        sel,
                        mov,
                        h,
                        Recdist,
                        Recdevs,
                        RecSpatialDevs,
                        SRrel,
                        N,
                        NBefore,
                        SSN,
                        C,
                        SSBA,
                        0,
                        sim_idx);
}

// ----------------------------------------------------------------------------

double OperatingModelBase::MSYrefs_objective(const double par,
                                             const int nReport,
                                             const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */,
                                             const ARRAY_2D qy/* nfleets, nsim */,
                                             const ARRAY_2D R0/* npop, nsim */,
                                             const ARRAY_3D M/* nages, npop, nsim */,
                                             const ARRAY_3D mat/* nages, npop, nsim */,
                                             const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                             const ARRAY_3D Len_age/* nages, npop, nsim */,
                                             const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                             const ARRAY_3D sel/* nages, nfleets, nsim */,
                                             const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                             const ARRAY_2D h/* npop, nsim */,
                                             const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                             const ARRAY_1I SRrel/* npop */,
                                             ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                             ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                             ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                             ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                             ARRAY_2D SSBA/* npop, nsim */,
                                             const int ntargets,
                                             const ARRAY_1I targpop/* ntargets */,
                                             const int run_years,
                                             const int sim_idx)
{
  int     p;
  int     cr;
  int     cf;
  int     cm;
  int     ca;
  int     cp;
  double  dCatch;
  double  dObjective;

  popdyn_MSY_par(par,
                 ECurrent,
                 qy,
                 R0,
                 M,
                 mat,
                 Idist,
                 Len_age,
                 Wt_age,
                 sel,
                 mov,
                 h,
                 Recdist,
                 SRrel,
                 N,
                 NBefore,
                 SSN,
                 C,
                 SSBA,
                 run_years,
                 sim_idx);

  // return(-log(sum(
  // array(C[targpop,,nyears,,,],c(length(targpop),nages,nsubyears,nareas,nfleets))*
  // array(Wt_age[targpop,,nyears],c(length(targpop),nages,nsubyears,nareas,nfleets)))))
  // Use a small number to stop the function returning +inf for objective
  dCatch = 1.0e-6;

  for (cp = 1 ; cp <= ntargets ; cp++)
  {
    p = targpop[cp];

    for (cr = 1 ; cr <= nareas ; cr++)
    {
      for (ca = 1 ; ca <= nages ; ca++)
      {
        for (cf = 1 ; cf <= nfleets ; cf++)
        {
          for (cm = 1 ; cm <= nsubyears ; cm++)
          {
            dCatch += C[cf][cr][cm][ca][p][sim_idx] * Wt_age[ca][p][sim_idx];
          }
        }
      }
    }
  }

  dObjective = -log(dCatch);

  #ifndef AD
  if (nReport != 0)
  {
    char sBuffer[128] = {0};

    snprintf(sBuffer, 128, "par=%g, C=%g, objective=%g\n", par, dCatch, dObjective);
    writeToStdOutString(sBuffer);
  }
  #endif

  return (dObjective);
}

// ----------------------------------------------------------------------------

void OperatingModelBase::MSYrefs(const double par,
                                 const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */,
                                 const ARRAY_2D qy/* nfleets, nsim */,
                                 const ARRAY_2D R0/* npop, nsim */,
                                 const ARRAY_3D M/* nages, npop, nsim */,
                                 const ARRAY_3D mat/* nages, npop, nsim */,
                                 const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                 const ARRAY_3D Len_age/* nages, npop, nsim */,
                                 const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                 const ARRAY_3D sel/* nages, nfleets, nsim */,
                                 const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                 const ARRAY_2D h/* npop, nsim */,
                                 const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                 const ARRAY_1I SRrel/* npop */,
                                 ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                 ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                 ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                 ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                 ARRAY_2D SSBA/* npop, nsim */,
                                 const int ntargets,
                                 const ARRAY_1I targpop/* ntargets */,
                                 const int run_years,
                                 ARRAY_1D MSY/* nsim */,
                                 ARRAY_1D BMSY/* nsim */,
                                 ARRAY_1D SSBMSY/* nsim */,
                                 ARRAY_1D SSBMSY_B0/* nsim */,
                                 const int sim_idx)
{
  int     p;
  int     cr;
  int     cf;
  int     cm;
  int     ca;
  int     cp;
  double  dMSY;
  double  dBMSY;
  double  dSSBMSY;
  double  dSSB0;
  double  dBiomass;

  popdyn_MSY_par(par,
                 ECurrent,
                 qy,
                 R0,
                 M,
                 mat,
                 Idist,
                 Len_age,
                 Wt_age,
                 sel,
                 mov,
                 h,
                 Recdist,
                 SRrel,
                 N,
                 NBefore,
                 SSN,
                 C,
                 SSBA,
                 run_years,
                 sim_idx);

  // MSY<-sum(array(C[targpop,,nyears,,,],c(length(targpop),nages,nsubyears,nareas,nfleets))*
  //          array(Wt_age[targpop,,nyears],c(length(targpop),nages,nsubyears,nareas,nfleets)))
  // BMSY<-sum(
  //   array((SSN[targpop,,nyears,1,]+NSN[targpop,,nyears,1,]),c(length(targpop),nages,nareas))*
  //   array(Wt_age[targpop,,nyears],c(length(targpop),nages,nareas)))
  //
  // sof<-apply(E[,MSYyear]*sel*qs*4,2,sum)
  // FMSYa<-max(sof)
  // sof<-sof/max(sof)
  // VBMSY<-sum(array(rep(sof,each=length(targpop)),c(length(targpop),nages,nareas))*
  //   array((SSN[targpop,,nyears,1,]+NSN[targpop,,nyears,1,]),c(length(targpop),nages,nareas))*
  //     array(Wt_age[targpop,,nyears],c(length(targpop),nages,nareas)))
  //
  // SSBMSY<-sum(array(SSN[targpop,,nyears,1,],c(length(targpop),nages,nareas))*array(Wt_age[targpop,,nyears],c(length(targpop),nages,nareas)))
  // UMSY<-MSY/VBMSY
  // SSBMSY_B0<-SSBMSY/sum(SSB0[targpop])
  // return(c(MSY,BMSY,VBMSY,SSBMSY,UMSY,FMSYa,SSBMSY_B0))
  dMSY        = 0.0;
  dBMSY       = 0.0;
  dSSBMSY     = 0.0;
  dSSB0       = 0.0;

  for (cp = 1 ; cp <= ntargets ; cp++)
  {
    p = targpop[cp];

    for (cr = 1 ; cr <= nareas ; cr++)
    {
      for (ca = 1 ; ca <= nages ; ca++)
      {
        for (cf = 1 ; cf <= nfleets ; cf++)
        {
          for (cm = 1 ; cm <= nsubyears ; cm++)
          {
            dMSY += C[cf][cr][cm][ca][p][sim_idx] * Wt_age[ca][p][sim_idx];
          }
        }

        dBiomass = N[cr][1][ca][p][sim_idx] * Wt_age[ca][p][sim_idx];

        dBMSY   += dBiomass;
        dSSBMSY += SSN[cr][1][ca][p][sim_idx] * Wt_age[ca][p][sim_idx];
      }
    }

    dSSB0 += SSB0[p][sim_idx];
  }

  MSY[sim_idx]       = dMSY;
  BMSY[sim_idx]      = dBMSY;
  SSBMSY[sim_idx]    = dSSBMSY;
  SSBMSY_B0[sim_idx] = dSSBMSY / dSSB0;
}

// ----------------------------------------------------------------------------

#ifndef AD

void OperatingModelBase::runHistoric(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* Context = (ParallelForContext*)pContext;

  Context->This->popdyn(Context->totF,
                        Context->qy,
                        Context->ECurrent,
                        Context->R0,
                        Context->M,
                        Context->mat,
                        Context->Idist,
                        Context->Len_age,
                        Context->Wt_age,
                        Context->sel,
                        Context->mov,
                        Context->h,
                        Context->Recdist,
                        Context->Recdevs,
                        Context->RecSpatialDevs,
                        Context->SRrel,
                        Context->N,
                        Context->NBefore,
                        Context->SSN,
                        Context->C,
                        Context->SSBA,
                        nIdx);
}

#endif

// ----------------------------------------------------------------------------

void OperatingModelBase::runHistoric(double totF,
                                     const ARRAY_2D qy/* nfleets, nsim */,
                                     const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */,
                                     const ARRAY_2D R0/* npop, nsim */,
                                     const ARRAY_3D M/* nages, npop, nsim */,
                                     const ARRAY_3D mat/* nages, npop, nsim */,
                                     const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                     const ARRAY_3D Len_age/* nages, npop, nsim */,
                                     const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                     const ARRAY_3D sel/* nages, nfleets, nsim */,
                                     const ARRAY_6D mov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                     const ARRAY_2D h/* npop, nsim */,
                                     const ARRAY_3D Recdist/*nareas, npop, nsim */,
                                     const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                                     const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                                     const ARRAY_1I SRrel/* npop */,
                                     ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                     ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                                     ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                     ARRAY_2D SSBA/* npop, nsim */)
{
#ifndef AD
  ParallelForContext Context(this,
                             totF,
                             qy,
                             ECurrent,
                             R0,
                             M,
                             mat,
                             Idist,
                             Len_age,
                             Wt_age,
                             sel,
                             mov,
                             h,
                             Recdist,
                             Recdevs,
                             RecSpatialDevs,
                             SRrel,
                             N,
                             NBefore,
                             SSN,
                             C,
                             SSBA);

  parallelFor(&Context, OperatingModelBase::runHistoric, 1, nsim);
#endif
}

#ifndef AD

// ----------------------------------------------------------------------------
// Implement context info structure for use with parallelFor() operations
// ----------------------------------------------------------------------------
OperatingModelBase::ParallelForContext::ParallelForContext(OperatingModelBase* pThis,
                                                           double dtotF,
                                                           const ARRAY_2D pqy/* nfleets, nsim */,
                                                           const ARRAY_4D pECurrent/* nfleets, nareas, nsubyears, nsim */,
                                                           const ARRAY_2D pR0/* npop, nsim */,
                                                           const ARRAY_3D pM/* nages, npop, nsim */,
                                                           const ARRAY_3D pmat/* nages, npop, nsim */,
                                                           const ARRAY_4D pIdist/* nareas, nages, npop, nsim */,
                                                           const ARRAY_3D pLen_age/* nages, npop, nsim */,
                                                           const ARRAY_3D pWt_age/* nages, npop, nsim */,
                                                           const ARRAY_3D psel/* nages, nfleets, nsim */,
                                                           const ARRAY_6D pmov/* nareas, nareas, nsubyears, nages, npop, nsim */,
                                                           const ARRAY_2D ph/* npop, nsim */,
                                                           const ARRAY_3D pRecdist/*nareas, npop, nsim */,
                                                           const ARRAY_3D pRecdevs/* SpawnPerYr, npop, nsim */,
                                                           const ARRAY_3D pRecSpatialDevs/* nareas, npop, nsim */,
                                                           const ARRAY_1I pSRrel/* npop */,
                                                           ARRAY_5D pN/* nareas, nsubyears + 1, nages, npop, nsim */,
                                                           ARRAY_5D pNBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                                                           ARRAY_5D pSSN/* nareas, nsubyears, nages, npop, nsim */,
                                                           ARRAY_6D pC/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                                                           ARRAY_2D pSSBA/* npop, nsim */)
 : qy(pqy),
   ECurrent(pECurrent),
   R0(pR0),
   M(pM),
   mat(pmat),
   Idist(pIdist),
   Len_age(pLen_age),
   Wt_age(pWt_age),
   sel(psel),
   mov(pmov),
   h(ph),
   Recdist(pRecdist),
   Recdevs(pRecdevs),
   RecSpatialDevs(pRecSpatialDevs),
   SRrel(pSRrel),
   N(pN),
   NBefore(pNBefore),
   SSN(pSSN),
   C(pC),
   SSBA(pSSBA),
   totF(dtotF),
   This(pThis)
{

}


// ----------------------------------------------------------------------------
// Register handler to send text output to R
// ----------------------------------------------------------------------------
void stdOutHandler(adtstring& StdOutString)
{
  Rprintf("%s", StdOutString.c_str());
  R_FlushConsole();
}

// ----------------------------------------------------------------------------

AdtParallelStdOutCallback LastHandler = setStdOutCallback(stdOutHandler);

// ----------------------------------------------------------------------------

void stdErrHandler(adtstring& StdErrString)
{
  Rf_error("%s", StdErrString.c_str());
}

// ----------------------------------------------------------------------------

AdtParallelStdOutCallback LastOutHandler = setStdOutCallback(stdOutHandler);
AdtParallelStdOutCallback LastErrHandler = setStdErrCallback(stdErrHandler);


// ----------------------------------------------------------------------------
// These library unload handlers are here to close the thread pool used by
// parallelFor() before the library closes.
// ----------------------------------------------------------------------------
EXPORT void R_unload_Mseom(DllInfo* pInfo)
{
  closeThreadPool();
}

// ----------------------------------------------------------------------------

EXPORT void R_unload_libMseom(DllInfo* pInfo)
{
  closeThreadPool();
}


#endif
