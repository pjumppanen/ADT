// ----------------------------------------------------------------------------
// Code to develop generalised RE modelling code.
// ----------------------------------------------------------------------------
// This layer implements:
//
//  gradientRE()
//  diffRE()
//
// ----------------------------------------------------------------------------


#ifndef __R_REDEVA_HPP__
#define __R_REDEVA_HPP__


#include "d_REDev.hpp"


// ----------------------------------------------------------------------------

class R_REDevA : public D_REDev
{
protected:
  /* AD_ALIAS Db=DR_REDevA, D_REDev */
  /* AUTOINIT */
  /* AUTODEC 1 */
  ARRAY_1D reb2_re /* NR */;
  ARRAY_2D red3_re /* NR,nbdirsmax */;
  ARRAY_2D reb2_red3_re /* NR,nbdirsmax */;

#include "Db_array_plans.hpp"

public:
  R_REDevA(
#include "Db_constructor_args.hpp"
  );

  R_REDevA(const R_REDevA& rCopy);
  virtual ~R_REDevA();

  // Gradient of objective with respect to random effects
  void      gradientRE(const ARRAY_1D re/* NR */, 
                       const ARRAY_1D par/* NP */, 
                       ARRAY_1D pGrad/* NR */);

  // Partial differentiation of objective with respect to random effects evaluated in the direction dir
  double    diffRE(const ARRAY_1D re/* NR */, 
                   const ARRAY_1D par/* NP */,
                   const ARRAY_1D dir/* NR */);

  // Partial differentiation of objective with respect to random effects evaluated in multiple directions
  //void      secondDiffMultiRE(const ARRAY_1D re/* NR */, 
  //                            const ARRAY_1D par/* NP */,
  //                            const ARRAY_1I dirs/* nDirs */,
  //                            ARRAY_2D pDiff/* NR, nDirs */,
  //                            int nDirs);
};


#endif  //__R_REDEVA_HPP__
