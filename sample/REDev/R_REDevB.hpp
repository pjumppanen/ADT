// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements the full random effects fitting process.
// ----------------------------------------------------------------------------


#ifndef __R_REDEVB_HPP__
#define __R_REDEVB_HPP__


#include "dR_REDevA.hpp"


// ----------------------------------------------------------------------------

class R_REDevB : public DR_REDevA
{
protected:
  /* AD_ALIAS Dc=DR_REDevB, DR_REDevA */
  /* AUTOINIT */
  /* AUTODEC 1 */
  ARRAY_1D      Dir /* NR */;
  ARRAY_1D      TempRow/* NR */;
#include "Dc_array_plans.hpp"

#ifndef AD
private:
  int       MultithreadedCount;

  struct ParallelForContext
  {
    R_REDevA* This;
    ARRAY_1D  Par;
    ARRAY_1D  Re;
    ARRAY_1D  Dir;
    ARRAY_2D  Result;

    ParallelForContext(R_REDevA* pThis,
                       ARRAY_1D  par/* NP */,
                       ARRAY_1D  re/* NR */,
                       ARRAY_1D  dir/* NR */,
                       ARRAY_2D  pResult)
    {
      This        = pThis;
      Par         = par;
      Re          = re;
      Dir         = dir;
      Result      = pResult;
    };
  };

  static void hessianRow(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);
  static void covarRE_ParRow(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);
#endif

public:
  R_REDevB(
#include "Dc_constructor_args.hpp"
  );

  R_REDevB(const R_REDevB& rCopy);
  virtual ~R_REDevB();

#ifndef AD
  virtual AdtArrays* createShallowCopy() const;

  void      beginMultithreaded(int nThreads = 0);
  void      endMultithreaded();

#endif //AD

// Hessian of objective with respect to random effects
  void      hessianRE(const ARRAY_1D re/* NR */, 
                      const ARRAY_1D par/* NP */, 
                      ARRAY_2D pHessian/* NR,NR */);

  // Covariance matrix of objective with respect to random effects against parameters (ie. dRE dPar)
  void      covarRE_Par(const ARRAY_1D re/* NR */, 
                        const ARRAY_1D par/* NP */, 
                        ARRAY_2D pReParXCovar/* NR,NP */);

  // Log determinant of Hessian with respect to random effects
  double    logDetHessianRE(const ARRAY_1D re/* NR */, 
                            const ARRAY_1D par/* NP */, 
                            const ARRAY_2D pHessian/* NR,NR */,
                            ARRAY_2D pCholesky/* NR,NR */);

  // Laplace approximation of Maximum Likelihood
  double    laplace(const ARRAY_1D re/* NR */, 
                    const ARRAY_1D par/* NP */,
                    ARRAY_2D pHessian/* NR,NR */,
                    ARRAY_2D pCholesky/* NR,NR */);
};


#endif  //__R_REDEVB_HPP__
