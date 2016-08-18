// ----------------------------------------------------------------------------
// MSE operating model implemented with ADT and ADlib. Implementation of
// minimiser layer.
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "MseomMin.hpp"


// ----------------------------------------------------------------------------

OperatingModelMin::OperatingModelMin(
#include "Om_constructor_args.hpp"
)
 : D_OperatingModelBase(
#include "Om_constructor_call_args.hpp"
)
{
  #include "Om_constructor_locals.hpp"
  #include "Om_constructor_scalars_phase_1.hpp"
  #include "Om_constructor_arrays_phase_1.hpp"
  #include "Om_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

OperatingModelMin::~OperatingModelMin()
{
  // As these are full copies they need to be destroyed to avoid leaks
  destroy(nd1_par);
  destroy(nbefored1_par);
  destroy(ssnd1_par);
  destroy(cd1_par);

  if (!IsShallowCopy)
  {
    destroy(last_par);
  }
}

// ----------------------------------------------------------------------------

OperatingModelMin::OperatingModelMin(const OperatingModelMin& rCopy)
 : D_OperatingModelBase(rCopy)
#include "Om_array_plans_copy.hpp"
{
  TACbyF = rCopy.TACbyF;

  Plan_13.create(MemAllocator, nd1_par);

  zero(nd1_par);

  Plan_13.create(MemAllocator, nbefored1_par);

  zero(nbefored1_par);

  Plan_14.create(MemAllocator, ssnd1_par);

  zero(ssnd1_par);

  Plan_15.create(MemAllocator, cd1_par);

  zero(cd1_par);

  last_par = rCopy.last_par;
}

// ----------------------------------------------------------------------------
#ifndef AD
AdtArrays* OperatingModelMin::createShallowCopy() const
{
  return (new OperatingModelMin(*this));
}
#endif
// ----------------------------------------------------------------------------
#ifndef AD
double OperatingModelMin::msyrefs_optimfn(int n, double* par, void* context)
{
  ParallelForContext* pContext = (ParallelForContext*)context;

  return pContext->This->MSYrefs_objective(par[0],
                                           pContext->Report,
                                           pContext->ECurrent,
                                           pContext->qy,
                                           pContext->R0,
                                           pContext->M,
                                           pContext->mat,
                                           pContext->Idist,
                                           pContext->Len_age,
                                           pContext->Wt_age,
                                           pContext->sel,
                                           pContext->mov,
                                           pContext->h,
                                           pContext->Recdist,
                                           pContext->SRrel,
                                           pContext->N,
                                           pContext->NBefore,
                                           pContext->SSN,
                                           pContext->C,
                                           pContext->SSBA,
                                           pContext->ntargets,
                                           pContext->targpop,
                                           pContext->run_years,
                                           pContext->nIdx);
}

// ----------------------------------------------------------------------------

void OperatingModelMin::msyrefs_optimgr(int n, double* par, double* gr, void* context)
{
  ParallelForContext* pContext          = (ParallelForContext*)context;
  double              pard1_par         = 1.0;
  double              MSYrefs_objective = 0.0;

  gr[0] = pContext->This->MSYREFS_OBJECTIVE_DPAR(par[0],
                                                 pard1_par,
                                                 pContext->Report,
                                                 pContext->ECurrent,
                                                 pContext->qy,
                                                 pContext->R0,
                                                 pContext->M,
                                                 pContext->mat,
                                                 pContext->Idist,
                                                 pContext->Len_age,
                                                 pContext->Wt_age,
                                                 pContext->sel,
                                                 pContext->mov,
                                                 pContext->h,
                                                 pContext->Recdist,
                                                 pContext->SRrel,
                                                 pContext->N,
                                                 pContext->This->nd1_par,
                                                 pContext->NBefore,
                                                 pContext->This->nbefored1_par,
                                                 pContext->SSN,
                                                 pContext->C,
                                                 pContext->This->cd1_par,
                                                 pContext->SSBA,
                                                 pContext->ntargets,
                                                 pContext->targpop,
                                                 pContext->run_years,
                                                 pContext->nIdx,
                                                 MSYrefs_objective);
}

// ----------------------------------------------------------------------------

void OperatingModelMin::findMSYrefsTask(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* ParentContext = (ParallelForContext*)pContext;
  ParallelForContext  Context       = *ParentContext;
  char                sBuffer[64]   = {0};
  bool                bReport       = (Context.Report != 0);

  Context.This = (OperatingModelMin*)shallowCopy(nThreadIdx);

  if (bReport)
  {
    snprintf(sBuffer, 64, "\nMSYrefs simulation=%d\n---\n", nIdx);
    StdOutString.append(sBuffer);
  }

  Context.nIdx  = nIdx;

  char    msg[256]  = {0};
  int     trace     = 0; // Don't print minimsation messages
  double  x         = log(0.001); //log(c(0.0001,10.0)) range
  double  val       = 0.0;
  int     nREPORT   = 100000;
  int     mask      = 1;
  double  factr     = 1.0e+08; // The iteration will stop when
                               //
                               //   (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= factr*epsmch
                               //
                               // where epsmch is the machine precision, which is
                               // automatically generated by the code.
  double  pgtol     = 1.0e-5; // The iteration will stop when
                              //
                              //   max{|proj g_i | i = 1, ..., n} <= pgtol
                              //
                              // where pg_i is the ith component of the projected gradient.
  double  lower     = log(1.0e-18);
  double  upper     = log(1000.0);
  int     m         = 10;// m is the maximum number of variable metric corrections allowed in the limited memory matrix. What does that mean?
  int     nbd       = 2; // Bound type 0 if x(i) is unbounded,
                         //            1 if x(i) has only a lower bound,
                         //            2 if x(i) has both lower and upper bounds, and
                         //            3 if x(i) has only an upper bound.

  int     fncount = 0;
  int     grcount = 0;
  int     status  = 0;

  Context.This->popdyn_init_parameters(Context.M,
                                       Context.R0,
                                       Context.mat,
                                       Context.Idist,
                                       Context.Wt_age,
                                       Context.h,
                                       nIdx);

  ts_lbfgsb(1,
            m,
            &x,
            &lower,
            &upper,
            &nbd,
            &val,
            OperatingModelMin::msyrefs_optimfn,
            OperatingModelMin::msyrefs_optimgr,
            &status,
            (void*)&Context,
            factr,
            pgtol,
            &fncount,
            &grcount,
            Context.maxit,
            msg,
            trace,
            nREPORT);

  if (bReport)
  {
    StdOutString += msg;
    StdOutString += "\n\n";
  }

  ParentContext->MinPar[nIdx] = x; //x is an in-out parameter of ts_lbfgsb()
  Context.This->MSYrefs(x,
                        Context.ECurrent,
                        Context.qy,
                        Context.R0,
                        Context.M,
                        Context.mat,
                        Context.Idist,
                        Context.Len_age,
                        Context.Wt_age,
                        Context.sel,
                        Context.mov,
                        Context.h,
                        Context.Recdist,
                        Context.SRrel,
                        Context.N,
                        Context.NBefore,
                        Context.SSN,
                        Context.C,
                        Context.SSBA,
                        Context.ntargets,
                        Context.targpop,
                        Context.run_years,
                        Context.MSY,
                        Context.BMSY,
                        Context.SSBMSY,
                        Context.SSBMSY_B0,
                        nIdx);
}

// ----------------------------------------------------------------------------
#endif

void OperatingModelMin::findMSYrefs(const int nReport,
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
                                    int maxit)
{
#ifndef AD
  ParallelForContext Context(this,
                             nReport,
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
                             ntargets,
                             targpop,
                             run_years,
                             MSY,
                             BMSY,
                             SSBMSY,
                             SSBMSY_B0,
                             MinPar,
                             maxit);

  allocateShallowCopies(this);

  parallelFor(&Context, OperatingModelMin::findMSYrefsTask, 1, nsim);

  freeShallowCopies();
#endif
}

// ----------------------------------------------------------------------------

void OperatingModelMin::findMSYref(const int nReport,
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
                                   int nSim_Idx)
{
#ifndef AD
  ParallelForContext Context(this,
                             nReport,
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
                             ntargets,
                             targpop,
                             run_years,
                             MSY,
                             BMSY,
                             SSBMSY,
                             SSBMSY_B0,
                             MinPar,
                             maxit);

  allocateShallowCopies(this);
  parallelFor(&Context, OperatingModelMin::findMSYrefsTask, nSim_Idx, nSim_Idx);
  freeShallowCopies();
#endif
}

// ----------------------------------------------------------------------------
#ifndef AD
double OperatingModelMin::projection_optimfn(int n, double* par, void* context)
{
  ParallelForContext* pContext = (ParallelForContext*)context;

  pContext->nFnCalls++;

  return pContext->This->popdyn_projection_objective(par,
                                                     pContext->nPar,
                                                     pContext->nFixed,
                                                     pContext->TAC,
                                                     pContext->TAE,
                                                     pContext->FbyPar,
                                                     pContext->FbyFixed,
                                                     pContext->ECurrent,
                                                     pContext->qy,
                                                     pContext->R0,
                                                     pContext->M,
                                                     pContext->mat,
                                                     pContext->Idist,
                                                     pContext->Len_age,
                                                     pContext->Wt_age,
                                                     pContext->Wt_age_mid,
                                                     pContext->sel,
                                                     pContext->mov,
                                                     pContext->h,
                                                     pContext->Recdist,
                                                     pContext->Recdevs,
                                                     pContext->RecSpatialDevs,
                                                     pContext->SRrel,
                                                     pContext->N,
                                                     pContext->NBefore,
                                                     pContext->SSN,
                                                     pContext->C,
                                                     pContext->SSBA,
                                                     pContext->nIdx);
}

// ----------------------------------------------------------------------------

void OperatingModelMin::projection_optimgr(int n, double* par, double* gr, void* context)
{
  ParallelForContext* pContext                          = (ParallelForContext*)context;
  double              popdyn_projection_objectiveb2_par = 1.0;
  int                 cn;

  pContext->nGradCalls++;

  for (cn = 0 ; cn < pContext->nPar ; cn++)
  {
    gr[cn] = 0.0;
  }

  pContext->This->POPDYN_PROJECTION_OBJECTIVE_BPAR(par,
                                                   gr,
                                                   pContext->nPar,
                                                   pContext->nFixed,
                                                   pContext->TAC,
                                                   pContext->TAE,
                                                   pContext->FbyPar,
                                                   pContext->FbyFixed,
                                                   pContext->ECurrent,
                                                   pContext->qy,
                                                   pContext->R0,
                                                   pContext->M,
                                                   pContext->mat,
                                                   pContext->Idist,
                                                   pContext->Len_age,
                                                   pContext->Wt_age,
                                                   pContext->Wt_age_mid,
                                                   pContext->sel,
                                                   pContext->mov,
                                                   pContext->h,
                                                   pContext->Recdist,
                                                   pContext->Recdevs,
                                                   pContext->RecSpatialDevs,
                                                   pContext->SRrel,
                                                   pContext->N,
                                                   pContext->This->nd1_par,
                                                   pContext->NBefore,
                                                   pContext->This->nbefored1_par,
                                                   pContext->SSN,
                                                   pContext->C,
                                                   pContext->This->cd1_par,
                                                   pContext->SSBA,
                                                   pContext->nIdx,
                                                   popdyn_projection_objectiveb2_par);
}

// ----------------------------------------------------------------------------

double OperatingModelMin::findUpperLimit(double dEffortCeiling,
                                         int nFleet,
                                         const ARRAY_4D ECurrent/* nfleets, nareas, nsubyears, nsim */) const
{
  int     cf;
  int     ca;
  int     cm;
  int     cs;
  double  dLimit;
  double  dMaxE   = 0.0;
  double  dFleetE = 0.0;

  // Scale effort ceiling such that all fisheries can grow to the same
  // absolute level of effort
  for (cf = 1 ; cf <= nfleets ; cf++)
  {
    double dSumE = 0.0;

    for (ca = 1 ; ca <= nareas ; ca++)
    {
      for (cm = 1 ; cm <= nsubyears ; cm++)
      {
        for (cs = 1 ; cs <= nsim ; cs++)
        {
          dSumE += ECurrent[cf][ca][cm][cs];
        }
      }
    }

    if (dMaxE < dSumE)
    {
      dMaxE = dSumE;
    }

    if (cf == nFleet)
    {
      dFleetE = dSumE;
    }
  }

  dLimit = (dFleetE != 0.0) ? dEffortCeiling * dMaxE / dFleetE : dEffortCeiling;

  return (dLimit);
}

// ----------------------------------------------------------------------------

void OperatingModelMin::projectionTask(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString)
{
  ParallelForContext* ParentContext = (ParallelForContext*)pContext;
  ParallelForContext  Context       = *ParentContext;
  char                sBuffer[128]  = {0};
  int                 nfleets;
  int                 cn;
  ARRAY_1D            px;
  ARRAY_1D            plower;
  ARRAY_1D            pupper;
  ARRAY_1I            pnbd;
  ARRAY_1D            TAC;
  ARRAY_1D            TAE;
  ARRAY_1I            FbyPar;
  ARRAY_1I            FbyFixed;
  int                 nPar;
  int                 nFixed;
  double              dTAC;
  bool                bClosure = false;
  bool                bReport  = (Context.Report != 0);

  Context.This = (OperatingModelMin*)shallowCopy(nThreadIdx);

  if (bReport)
  {
    snprintf(sBuffer, 128, "\nProjection in year = %d simulation = %d\n", Context.ProjectionYear, nIdx);
    StdOutString.append(sBuffer);
  }

  Context.nIdx  = nIdx;
  nfleets       = Context.This->nfleets;
  dTAC          = 0.0;

  AdtArrayPlan  ArrayPlan(0, nfleets);

  ArrayPlan.create(Context.This->MemAllocator, px);
  ArrayPlan.create(Context.This->MemAllocator, plower);
  ArrayPlan.create(Context.This->MemAllocator, pupper);
  ArrayPlan.create(Context.This->MemAllocator, pnbd);
  ArrayPlan.create(Context.This->MemAllocator, TAC);
  ArrayPlan.create(Context.This->MemAllocator, TAE);
  ArrayPlan.create(Context.This->MemAllocator, FbyPar);
  ArrayPlan.create(Context.This->MemAllocator, FbyFixed);

  if ((plower   != 0) &&
      (pupper   != 0) &&
      (pnbd     != 0) &&
      (TAC      != 0) &&
      (TAE      != 0) &&
      (FbyPar   != 0) &&
      (FbyFixed != 0))
  {
    nPar   = 0;
    nFixed = 0;

    for (cn = 1 ; cn <= nfleets ; cn++)
    {
      if (Context.TACbyF[cn][nIdx] <= 0.0)
      {
        // Uncontrolled fishery
        TAE[nFixed]       = Context.TAEbyF[cn][nIdx];
        FbyFixed[nFixed]  = cn;

        nFixed++;
      }
      else
      {
        // Controlled fishery
        TAC[nPar]     = Context.TACbyF[cn][nIdx];
        px[nPar]      = Context.This->last_par[cn][nIdx];
        FbyPar[nPar]  = cn;
        plower[nPar]  = log(1.0e-18);
        pupper[nPar]  = log(Context.This->findUpperLimit(Context.EffortCeiling, cn, Context.ECurrent));
        pnbd[nPar]    = 2;// Bound type 0 if x(i) is unbounded,
                          //            1 if x(i) has only a lower bound,
                          //            2 if x(i) has both lower and upper bounds, and
                          //            3 if x(i) has only an upper bound.

        dTAC += TAC[nPar];
        nPar++;
      }
    }

    Context.nPar      = nPar;
    Context.nFixed    = nFixed;
    Context.TAC       = TAC;
    Context.TAE       = TAE;
    Context.FbyPar    = FbyPar;
    Context.FbyFixed  = FbyFixed;

    if ((nPar > 0) && (dTAC > 0.0))
    {
      char    msg[256]  = {0};
      int     trace     = 0; // Don't print minimsation messages
//      int     trace     = 6; // Don't print minimsation messages
      double  val       = 0.0;
      int     nREPORT   = 100000;
      int     mask      = 1;
      double  factr     = 1.0e+8;  // The iteration will stop when
                                   //
                                   //   (f^k - f^{k+1})/max{|f^k|,|f^{k+1}|,1} <= factr*epsmch
                                   //
                                   // where epsmch is the machine precision, which is
                                   // automatically generated by the code.
      double  pgtol     = 1.0e-5;  // The iteration will stop when
                                   //
                                   //   max{|proj g_i | i = 1, ..., n} <= pgtol
                                   //
                                   // where pg_i is the ith component of the projected gradient.
      int     m         = 10;      // m is the maximum number of variable metric corrections allowed in the limited memory matrix. What does that mean?
      int     fncount   = 0;
      int     grcount   = 0;
      int     status    = 0;
      int     nRetry    = 2;

      Context.nFnCalls   = 0;
      Context.nGradCalls = 0;

      // This retry this is probably masking a bug somewhere in my code
      // leading to low level noise in the derivative evaluations.
      while (nRetry > 0)
      {
        ts_lbfgsb(nPar,
                  m,
                  px,
                  plower,
                  pupper,
                  pnbd,
                  &val,
                  OperatingModelMin::projection_optimfn,
                  OperatingModelMin::projection_optimgr,
                  &status,
                  (void*)&Context,
                  factr,
                  pgtol,
                  &fncount,
                  &grcount,
                  Context.maxit,
                  msg,
                  trace,
                  nREPORT);

        if (status == 0)
        {
          break;
        }

        nRetry--;
      }

      if (status == 0)
      {
        for (cn = 0 ; cn < nPar ; cn++)
        {
          Context.This->last_par[FbyPar[cn]][nIdx] = px[cn];//Save the last par as it should
                                                            //be close to the value needed
        }                                                   //for successive years.
      }
      else
      {
        for (cn = 0 ; cn < nPar ; cn++)
        {
          px[cn] = log(0.001);
        }
      }

      if (bReport)
      {
        StdOutString += msg;

        snprintf(sBuffer, 128, "\nobjective = %g, function count = %d, gradient count = %d\n", val, Context.nFnCalls, Context.nGradCalls);
        StdOutString.append(sBuffer);
      }
    }

    // Apply TACEError by modifying px and TAE
    for (cn = 0 ; cn < nPar ; cn++)
    {
      px[cn] += log(Context.TACEError[FbyPar[cn]][nIdx]);
    }

    for (cn = 0 ; cn < nFixed ; cn++)
    {
      TAE[cn] *= Context.TACEError[FbyFixed[cn]][nIdx];
    }

    Context.This->runProjection(px,
                                Context.nPar,
                                Context.nFixed,
                                Context.TAC,
                                Context.TAE,
                                Context.FbyPar,
                                Context.FbyFixed,
                                Context.ECurrent,
                                Context.qy,
                                Context.R0,
                                Context.M,
                                Context.mat,
                                Context.Idist,
                                Context.Len_age,
                                Context.Wt_age,
                                Context.sel,
                                Context.mov,
                                Context.h,
                                Context.Recdist,
                                Context.Recdevs,
                                Context.RecSpatialDevs,
                                Context.SRrel,
                                Context.N,
                                Context.NBefore,
                                Context.SSN,
                                Context.C,
                                Context.SSBA,
                                nIdx);

    if (bReport)
    {
      for (cn = 0 ; cn < nPar ; cn++)
      {
        double  dVulnerableBiomass = 0.0;
        double  dCatchBiomass      = 0.0;
        int     nareas             = Context.This->nareas;
        int     nages              = Context.This->nages;
        int     npop               = Context.This->npop;
        int     nsubyears          = Context.This->nsubyears;
        int     cf                 = FbyPar[cn];
        int     cr;
        int     ca;
        int     cp;
        int     cs;

        for (cr = 1 ; cr <= nareas ; cr++)
        {
          for (ca = 1 ; ca <= nages ; ca++)
          {
            for (cp = 1 ; cp <= npop ; cp++)
            {
              for (cs = 1 ; cs <= nsubyears ; cs++)
              {
                dCatchBiomass += Context.C[cf][cr][cs][ca][cp][nIdx] * Context.Wt_age_mid[ca][cp][nIdx];
              }

              dVulnerableBiomass += Context.NBefore[cr][1][ca][cp][nIdx] * Context.sel[ca][cf][nIdx] * Context.Wt_age_mid[ca][cp][nIdx];
            }
          }
        }

        snprintf(sBuffer,
                 128,
                 "Fishery = %d, TAC = %g, Catch Biomass = %g, Vulnerable Biomass = %g, E = %g\n",
                 FbyPar[cn],
                 TAC[cn],
                 dCatchBiomass,
                 dVulnerableBiomass,
                 exp(px[cn]));

        StdOutString.append(sBuffer);
      }
    }

    if (bReport)
    {
      for (cn = 0 ; cn < nFixed ; cn++)
      {
        double  dVulnerableBiomass = 0.0;
        double  dCatchBiomass      = 0.0;
        int     nareas             = Context.This->nareas;
        int     nages              = Context.This->nages;
        int     npop               = Context.This->npop;
        int     nsubyears          = Context.This->nsubyears;
        int     cf                 = FbyFixed[cn];
        int     cr;
        int     ca;
        int     cp;
        int     cs;

        for (cr = 1 ; cr <= nareas ; cr++)
        {
          for (ca = 1 ; ca <= nages ; ca++)
          {
            for (cp = 1 ; cp <= npop ; cp++)
            {
              for (cs = 1 ; cs <= nsubyears ; cs++)
              {
                dCatchBiomass += Context.C[cf][cr][cs][ca][cp][nIdx] * Context.Wt_age_mid[ca][cp][nIdx];
              }

              dVulnerableBiomass += Context.NBefore[cr][1][ca][cp][nIdx] * Context.sel[ca][cf][nIdx] * Context.Wt_age_mid[ca][cp][nIdx];
            }
          }
        }

        snprintf(sBuffer,
                 128,
                 "Fishery = %d, TAE = %g, Catch Biomass = %g, Vulnerable Biomass = %g\n",
                 FbyFixed[cn],
                 TAE[cn],
                 dCatchBiomass,
                 dVulnerableBiomass);

        StdOutString.append(sBuffer);
      }

      StdOutString += "\n";
    }
  }

  ArrayPlan.destroy(Context.This->MemAllocator, px);
  ArrayPlan.destroy(Context.This->MemAllocator, plower);
  ArrayPlan.destroy(Context.This->MemAllocator, pupper);
  ArrayPlan.destroy(Context.This->MemAllocator, pnbd);
  ArrayPlan.destroy(Context.This->MemAllocator, TAC);
  ArrayPlan.destroy(Context.This->MemAllocator, TAE);
  ArrayPlan.destroy(Context.This->MemAllocator, FbyPar);
  ArrayPlan.destroy(Context.This->MemAllocator, FbyFixed);
}

#endif
// ----------------------------------------------------------------------------

void OperatingModelMin::beginProjection(const ARRAY_1D pPar/* nfleets */)
{
  int cf;
  int cs;

  // reset the last_par vector to initial supplied value
  for (cf = 1 ; cf <= nfleets ; cf++)
  {
    for (cs = 1 ; cs <= nsim ; cs++)
    {
      last_par[cf][cs] = pPar[cf];
    }
  }
}

// ----------------------------------------------------------------------------

void OperatingModelMin::projection(const int nProjectionYear,
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
                                   int maxit)
{
  int     cf;
  int     cr;
  int     cm;
  int     cs;
  double  dSum;
  double  dSumAll;

  // Calculate TACbyF from TAC and CMCurrent. Need to check for TAEbyF to see
  // whether to exclude it from TAC
  for (cs = 1 ; cs <= nsim ; cs++)
  {
    dSumAll = 0.0;

    for (cf = 1 ; cf <= nfleets ; cf++)
    {
      dSum = 0.0;

      if (TAEbyF[cf][cs] <= 0.0)
      {
        for (cr = 1 ; cr <= nareas ; cr++)
        {
          for (cm = 1 ; cm <= nsubyears ; cm++)
          {
          #ifndef AD
            dSum += isnan(CMCurrent[cf][cr][cm][cs]) ? 0.0 : CMCurrent[cf][cr][cm][cs];
          #endif
          }
        }
      }

      TACbyF[cf][cs] = dSum;
      dSumAll       += dSum;
    }

    for (cf = 1 ; cf <= nfleets ; cf++)
    {
      if (dSumAll == 0.0)
      {
        TACbyF[cf][cs] = 0.0;
      }
      else
      {
        TACbyF[cf][cs] *= TAC[cs] / dSumAll;
      }
    }
  }

  #ifndef AD
    ParallelForContext Context(this,
                               nReport,
                               dEffortCeiling,
                               nProjectionYear,
                               TACbyF,
                               TAEbyF,
                               TACEError,
                               ECurrent,
                               qy,
                               R0,
                               M,
                               mat,
                               Idist,
                               Len_age,
                               Wt_age,
                               Wt_age_mid,
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
                               maxit);

    allocateShallowCopies(this);
    parallelFor(&Context, OperatingModelMin::projectionTask, 1, nsim);
    freeShallowCopies();
  #endif
}

#ifndef AD

// ----------------------------------------------------------------------------
// Implement context info structure for use with parallelFor() operations
// ----------------------------------------------------------------------------
OperatingModelMin::ParallelForContext::ParallelForContext(OperatingModelMin* pThis,
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
                                                          int nmaxit)
 : This(pThis),
   Report(nReport),
   EffortCeiling(100.0),
   TACbyF(0),
   TAEbyF(0),
   TACEError(0),
   ECurrent(pECurrent),
   qy(pQy),
   R0(pR0),
   M(pM),
   mat(pmat),
   Idist(pIdist),
   Len_age(pLen_age),
   Wt_age(pWt_age),
   Wt_age_mid(0),
   sel(psel),
   mov(pmov),
   h(ph),
   Recdist(pRecdist),
   Recdevs(0),
   RecSpatialDevs(0),
   SRrel(pSRrel),
   N(pN),
   NBefore(pNBefore),
   SSN(pSSN),
   C(pC),
   SSBA(pSSBA),
   ntargets(nntargets),
   targpop(ptargpop),
   run_years(nrun_years),
   ProjectionYear(0),
   MSY(pMSY),
   BMSY(pBMSY),
   SSBMSY(pSSBMSY),
   SSBMSY_B0(pSSBMSY_B0),
   MinPar(pMinPar),
   maxit(nmaxit)
{
  TAC       = 0;
  TAE       = 0;
  FbyPar    = 0;
  FbyFixed  = 0;
  nPar      = 0;
  nFixed    = 0;

  nFnCalls    = 0;
  nGradCalls  = 0;
}

// ----------------------------------------------------------------------------

OperatingModelMin::ParallelForContext::ParallelForContext(OperatingModelMin* pThis,
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
                                                          int nmaxit)
 : This(pThis),
   Report(nReport),
   EffortCeiling(dEffortCeiling),
   TACbyF(pTACbyF),
   TAEbyF(pTAEbyF),
   TACEError(pTACEError),
   ECurrent(pECurrent),
   qy(pQy),
   R0(pR0),
   M(pM),
   mat(pmat),
   Idist(pIdist),
   Len_age(pLen_age),
   Wt_age(pWt_age),
   Wt_age_mid(pWt_age_mid),
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
   ntargets(0),
   targpop(0),
   MinPar(0),
   run_years(0),
   ProjectionYear(nProjectionYear),
   MSY(0),
   BMSY(0),
   SSBMSY(0),
   SSBMSY_B0(0),
   maxit(nmaxit)
{
  TAC       = 0;
  TAE       = 0;
  FbyPar    = 0;
  FbyFixed  = 0;
  nPar      = 0;
  nFixed    = 0;

  nFnCalls    = 0;
  nGradCalls  = 0;
}


#endif
