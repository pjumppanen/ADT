// ----------------------------------------------------------------------------
// MSE operating model implemented with ADT and ADlib
// ----------------------------------------------------------------------------

#ifndef __MSEOM_HPP__
#define __MSEOM_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------

class OperatingModelBase : public AdtArrays
{
protected:
  /* AD_LIBNAME Mseom */
  /* AD_ALIAS OmB=D_OperatingModelBase */
  /* AUTOINIT */
  int       nsim;
  int       npop;
  int       nages;
  int       nsubyears;
  int       nareas;
  int       nfleets;

  ARRAY_1I  Recsubyr/* nsubyears */;

  /* AUTODEC */
  int       SpawnPerYr;

  ARRAY_4D  EforYear/* nfleets, nareas, nsubyears, nsim */;
  ARRAY_3D  surv/* nages, npop, nsim */;
  ARRAY_2D  B0/* npop, nsim */;
  ARRAY_2D  SSB0/* npop, nsim */;
  ARRAY_2D  SSBpR/* npop, nsim */;
  ARRAY_2D  aR/* npop, nsim */;
  ARRAY_2D  bR/* npop, nsim */;
  ARRAY_2D  FM/* nfleets, nsim */;
  ARRAY_2D  MovN/* nareas, nsim */;

  ARRAY_3D  MSY_RecSpatialDevs/* nareas, npop, nsim */;

  // Note that MSY_Recdevs is initialised in phase 2 because its dimension
  // depends on the contents of Recsubyr and is calculated during construction
  /* AUTODEC 2 */
  ARRAY_3D  MSY_Recdevs/* SpawnPerYr, npop, nsim */;

#include "OmB_array_plans.hpp"

#ifndef AD
private:
  // ----------------------------------------------------------------------------
  // Declare context info structure for use with parallelFor() operations
  // ----------------------------------------------------------------------------
  struct ParallelForContext
  {
    ParallelForContext(OperatingModelBase* pThis,
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
                       ARRAY_2D pSSBA/* npop, nsim */);

    OperatingModelBase* This;
    const ARRAY_2D      qy;
    const ARRAY_4D      ECurrent;
    const ARRAY_2D      R0;
    const ARRAY_3D      M;
    const ARRAY_3D      mat;
    const ARRAY_4D      Idist;
    const ARRAY_3D      Len_age;
    const ARRAY_3D      Wt_age;
    const ARRAY_3D      sel;
    const ARRAY_6D      mov;
    const ARRAY_2D      h;
    const ARRAY_3D      Recdist;
    const ARRAY_3D      Recdevs;
    const ARRAY_3D      RecSpatialDevs;
    const ARRAY_1I      SRrel;
    ARRAY_5D            N;
    ARRAY_5D            NBefore;
    ARRAY_5D            SSN;
    ARRAY_6D            C;
    ARRAY_2D            SSBA;
    double              totF;
  };
#endif

protected:
  void    popdyn_init_parameters(const ARRAY_3D M/* nages, npop, nsim */,
                                 const ARRAY_2D R0/* npop, nsim */,
                                 const ARRAY_3D mat/* nages, npop, nsim */,
                                 const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                                 const ARRAY_3D Wt_age/* nages, npop, nsim */,
                                 const ARRAY_2D h/* npop, nsim */,
                                 const int sim_idx);

  void    popdyn_next_year(ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                           ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                           const int sim_idx);

  void    popdyn_init(const ARRAY_2D R0/* npop, nsim */,
                      const ARRAY_3D mat/* nages, npop, nsim */,
                      const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                      ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                      ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                      ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                      const int sim_idx);

  void    popdyn_year(const ARRAY_2D qy/* nfleets, nsim */,
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
                      const int sim_idx);

  void    popdyn(double dtotF,
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
                 const int sim_idx);

  void    popdyn_projection_par(const ARRAY_1D par/* 0:npar-1 */,
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
                                const int sim_idx);

  void    popdyn_MSY_par(const double par,
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
                         const int sim_idx);

public:
  OperatingModelBase(
#include "OmB_constructor_args.hpp"
  );

  OperatingModelBase(const OperatingModelBase& rCopy);
  virtual ~OperatingModelBase();

  void    initialiseParameters(const ARRAY_3D M/* nages, npop, nsim */,
                               const ARRAY_2D R0/* npop, nsim */,
                               const ARRAY_3D mat/* nages, npop, nsim */,
                               const ARRAY_4D Idist/* nareas, nages, npop, nsim */,
                               const ARRAY_3D Wt_age/* nages, npop, nsim */,
                               const ARRAY_2D h/* npop, nsim */);

  void    nextYear(ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                   ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */);

  double  popdyn_projection_objective(const ARRAY_1D par/* 0:npar-1 */,
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
                                      const int sim_idx);

  void    runProjection(const ARRAY_1D par/* 0:npar-1 */,
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
                        const int sim_idx);

  // method MSY reference point calculation
  double  MSYrefs_objective(const double par,
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
                            const int sim_idx);

  void    MSYrefs(const double par,
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
                  const int sim_idx);

#ifndef AD
  static void runHistoric(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);
#endif

  void    runHistoric(double totF,
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
                      ARRAY_2D SSBA/* npop, nsim */);
};


#endif  //__MSEOM_HPP__
