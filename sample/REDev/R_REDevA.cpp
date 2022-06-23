// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements:
//
//  gradientRE()
//  hessianRE()
//  logDetHessianRE()
//  laplace()
//
// ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "R_REDevA.hpp"
#include <R_ext/Applic.h>


// ----------------------------------------------------------------------------
// R_MinRosenbrock method implementations
// ----------------------------------------------------------------------------
R_REDevA::R_REDevA(
#include "Db_constructor_args.hpp"
)
 : D_REDev(
#include "Da_constructor_call_args.hpp"
   )
{
  #include "Db_constructor_locals.hpp"
  #include "Db_constructor_scalars_phase_1.hpp"
  #include "Db_constructor_arrays_phase_1.hpp"
  #include "Db_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

R_REDevA::R_REDevA(const R_REDevA& rCopy)
 : D_REDev(rCopy)
#include "Db_array_plans_copy.hpp"
{

}

// ----------------------------------------------------------------------------

R_REDevA::~R_REDevA()
{

}

// ----------------------------------------------------------------------------

void R_REDevA::gradientRE(const ARRAY_1D re/* NR */, 
                          const ARRAY_1D par/* NP */, 
                          ARRAY_1D pGrad/* NR */)
{
  double  loglikelihoodb1_re;

  loglikelihoodb1_re = 1.0;

  LOGLIKELIHOOD_BRE(re, pGrad, par, loglikelihoodb1_re);
}

// ----------------------------------------------------------------------------

double R_REDevA::diffRE(const ARRAY_1D re/* NR */, 
                        const ARRAY_1D par/* NP */,
                        const ARRAY_1D dir/* NR */)
{
  double  dDiff;
  double  dLoglikelihood;

  dLoglikelihood = 0.0;

  dDiff = LOGLIKELIHOOD_DRE(re, dir, par, dLoglikelihood);
  
  return (dDiff);
}

// ----------------------------------------------------------------------------

//void R_REDevA::secondDiffMultiRE(const ARRAY_1D re/* NR */, 
//                                 const ARRAY_1D par/* NP */,
//                                 const ARRAY_1I dirs/* nDirs */,
//                                 ARRAY_2D pDiff/* NR, nDirs */,
//                                 int nDirs)
//{
//  int     cn;
//  int     cm;
//  double  loglikelihoodb2_re;
//
//  loglikelihoodb2_re = 1.0;
//
//  for (cm = 1 ; cm <= NR ; cm++)
//  {
//    reb2_re[cm] = 1.0;
//
//    for (cn = 1 ; cn <= nDirs ; cn++)
//    {
//      if (dirs[cn] == cm)
//      {
//        red3_re[cm][cn] = 1.0;
//      }
//      else
//      {
//        red3_re[cm][cn] = 0.0;
//      }
//      reb2_red3_re[cm][cn] = 0.0;
//    }
//  }
//
//  LOGLIKELIHOOD_BRE_DREV(re, 
//                         red3_re, 
//                         reb2_re, 
//                         pDiff, 
//                         par, 
//                         loglikelihoodb2_re, 
//                         nDirs);
//}                           
