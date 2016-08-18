// ----------------------------------------------------------------------------
// MSE operating model implemented with ADT and ADlib. Declaratation of
// minimiser layer.
// ----------------------------------------------------------------------------

#ifndef __MSEOMMIN_HPP__
#define __MSEOMMIN_HPP__


#include "D_Mseom.hpp"


// ----------------------------------------------------------------------------

class OperatingModelMin : public D_OperatingModelBase
{
protected:
  /* AD_LIBNAME Mseom */
  /* AD_ALIAS Om=D_OperatingModelMin, D_OperatingModelBase */

#include "Om_array_plans.hpp"

  /* AUTODEC */
  ARRAY_2D TACbyF/* nfleets, nsim */;

public:
  ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */;
  ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */;
  ARRAY_5D ssnd1_par/* nareas,nsubyears,nages,npop,nsim */;
  ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */;
  ARRAY_2D last_par/* nfleets,nsim */;

#ifndef AD
private:
  // ----------------------------------------------------------------------------
  // Declare context info structure for use with parallelFor() operations
  // ----------------------------------------------------------------------------
  struct ParallelForContext
  {
    ParallelForContext(OperatingModelMin* pThis,
                       const int nReport,
                       const ARRAY_4D pECurrent/* nfleets, nareas, nsubyears, nsim */,
                       const ARRAY_2D pQy/* nfleets, nsim */,
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
                       const ARRAY_1I pSRrel/* npop */,
                       ARRAY_5D pN/* nareas, nsubyears + 1, nages, npop, nsim */,
                       ARRAY_5D pNBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                       ARRAY_5D pSSN/* nareas, nsubyears, nages, npop, nsim */,
                       ARRAY_6D pC/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                       ARRAY_2D pSSBA/* npop, nsim */,
                       const int nntargets,
                       const ARRAY_1I ptargpop/* ntargets */,
                       const int nrun_years,
                       ARRAY_1D pMSY/* nsim */,
                       ARRAY_1D pBMSY/* nsim */,
                       ARRAY_1D pSSBMSY/* nsim */,
                       ARRAY_1D pSSBMSY_B0/* nsim */,
                       ARRAY_1D pMinPar/* nsim */,
                       int nmaxit);

    ParallelForContext(OperatingModelMin* pThis,
                       const int nReport,
                       const double dEffortCeiling,
                       const int nProjectionYear,
                       const ARRAY_2D pTACbyF /* nfleets, nsim */,
                       const ARRAY_2D pTAEbyF /* nfleets, nsim */,
                       const ARRAY_2D pTACEError /* nfleets, nsim */,
                       const ARRAY_4D pECurrent/* nfleets,nareas,nsubyears,nsim */,
                       const ARRAY_2D pQy/* nfleets, nsim */,
                       const ARRAY_2D pR0/* npop, nsim */,
                       const ARRAY_3D pM/* nages, npop, nsim */,
                       const ARRAY_3D pmat/* nages, npop, nsim */,
                       const ARRAY_4D pIdist/* nareas, nages, npop, nsim */,
                       const ARRAY_3D pLen_age/* nages, npop, nsim */,
                       const ARRAY_3D pWt_age/* nages, npop, nsim */,
                       const ARRAY_3D pWt_age_mid/* nages, npop, nsim */,
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
                       ARRAY_2D pSSBA/* npop, nsim */,
                       int maxit);

    OperatingModelMin*  This;
    const ARRAY_2D      TACbyF;
    const ARRAY_2D      TAEbyF;
    const ARRAY_2D      TACEError;
    const ARRAY_4D      ECurrent;
    const ARRAY_2D      qy;
    const ARRAY_2D      R0;
    const ARRAY_3D      M;
    const ARRAY_3D      mat;
    const ARRAY_4D      Idist;
    const ARRAY_3D      Len_age;
    const ARRAY_3D      Wt_age;
    const ARRAY_3D      Wt_age_mid;
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
    const int           ntargets;
    const ARRAY_1I      targpop;
    ARRAY_1D            MinPar;
    int                 maxit;
    const int           run_years;
    const int           ProjectionYear;
    const int           Report;
    const double        EffortCeiling;
    ARRAY_1D            MSY;
    ARRAY_1D            BMSY;
    ARRAY_1D            SSBMSY;
    ARRAY_1D            SSBMSY_B0;
    int                 nIdx;

    ARRAY_1D            TAC;
    ARRAY_1D            TAE;
    ARRAY_1I            FbyPar;
    ARRAY_1I            FbyFixed;
    int                 nPar;
    int                 nFixed;

    int                 nFnCalls;
    int                 nGradCalls;
  };

  static void   findMSYrefsTask(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);
  static double msyrefs_optimfn(int n, double* par, void* context);
  static void   msyrefs_optimgr(int n, double* par, double* gr, void* context);

  static void   projectionTask(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);
  static double projection_optimfn(int n, double* par, void* context);
  static void   projection_optimgr(int n, double* par, double* gr, void* context);

  double        findUpperLimit(double dEffortCeiling,
                               int nFleet,
                               const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */) const;

#endif

public:
  OperatingModelMin(
#include "Om_constructor_args.hpp"
  );

  OperatingModelMin(const OperatingModelMin& rCopy);

  virtual ~OperatingModelMin();

#ifndef AD
  virtual AdtArrays* createShallowCopy() const;
#endif //AD

  void   findMSYrefs(const int nReport,
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
                     const ARRAY_3D Recdist/* nareas, npop, nsim */,
                     const ARRAY_1I SRrel/* npop */,
                     ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                     ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                     ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                     ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                     ARRAY_2D SSBA/* npop, nsim */,
                     const int ntargets,
                     const ARRAY_1I targpop/* ntargets */,
                     const int run_years,
                     ARRAY_1D MinPar/* nsim */,
                     ARRAY_1D MSY/* nsim */,
                     ARRAY_1D BMSY/* nsim */,
                     ARRAY_1D SSBMSY/* nsim */,
                     ARRAY_1D SSBMSY_B0/* nsim */,
                     int maxit);

  void   findMSYref(const int nReport,
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
                    const ARRAY_3D Recdist/* nareas, npop, nsim */,
                    const ARRAY_1I SRrel/* npop */,
                    ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                    ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                    ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                    ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                    ARRAY_2D SSBA/* npop, nsim */,
                    const int ntargets,
                    const ARRAY_1I targpop/* ntargets */,
                    const int run_years,
                    ARRAY_1D MinPar/* nsim */,
                    ARRAY_1D MSY/* nsim */,
                    ARRAY_1D BMSY/* nsim */,
                    ARRAY_1D SSBMSY/* nsim */,
                    ARRAY_1D SSBMSY_B0/* nsim */,
                    int maxit,
                    int nSim_Idx);

  void   beginProjection(const ARRAY_1D pPar/* nfleets */);

  void   projection(const int nProjectionYear,
                    const int nReport,
                    const double dEffortCeiling,
                    const ARRAY_1D TAC /* nsim */,
                    const ARRAY_2D TAEbyF /* nfleets, nsim */,
                    const ARRAY_2D TACEError /* nfleets, nsim */,
                    const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */,
                    const ARRAY_4D CMCurrent/* nfleets,nareas,nsubyears,nsim */,
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
                    const ARRAY_3D Recdist/* nareas, npop, nsim */,
                    const ARRAY_3D Recdevs/* SpawnPerYr, npop, nsim */,
                    const ARRAY_3D RecSpatialDevs/* nareas, npop, nsim */,
                    const ARRAY_1I SRrel/* npop */,
                    ARRAY_5D N/* nareas, nsubyears + 1, nages, npop, nsim */,
                    ARRAY_5D NBefore/* nareas, nsubyears + 1, nages, npop, nsim */,
                    ARRAY_5D SSN/* nareas, nsubyears, nages, npop, nsim */,
                    ARRAY_6D C/* nfleets, nareas, nsubyears, nages, npop, nsim */,
                    ARRAY_2D SSBA/* npop, nsim */,
                    int maxit);
};


#endif  //__MSEOM_HPP__
