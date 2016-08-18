//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    adtdiff.hpp
//
//  Purpose:
//    This file includes declarations of classes for use in Auto-differentiation
//    code implemented in C++. This is a functional equivalent of the TUseful
//    delphi unit code for delphi applications.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADT_DIFF__
#define __ADT_DIFF__


#include "adtarrays.hpp"
#include "adtstack.hpp"


class AdtDiff : public AdtArrays
{
protected:
  // Stuff for lgamma & gammln
  static const int      n_laugamp;
  static const int      n_gamlanc;

#ifndef AD

  static const double   gamlanc_cof[];

  ARRAY_1L              ismall/*257*/;
  ARRAY_1L              ibig/*257*/;
  ARRAY_1L              exp_shift/*256*/;
  ARRAY_1D              compli/*256*/;
  ARRAY_1D              acc_cval/*256*/;

#else

  ARRAY_1D              gamlanc_cof/*0:n_gamlanc + 1*/;

#endif // AD

  int                   ncheb;
  double                incheb; // inverse
  double                sqrt_two_pi;
  ARRAY_1D              cheb_x/*ncheb*/;
  ARRAY_1D              cheb_wt/*ncheb*/;

  AdtDiff();
  AdtDiff(const AdtDiff& rCopy);
  virtual ~AdtDiff();

  double                sum_log1m(const ARRAY_1D xpos /*count*/,
                                  const int first,
                                  const int count);

  double                dsum_log1m(const ARRAY_1D xpos /*count*/,
                                   const ARRAY_1D xposdir1/*count*/,
                                   const int first,
                                   const int count,
                                   double& sum_log1m_result);

  double                ddsum_log1m(const ARRAY_1D xpos/*count*/,
                                    const ARRAY_1D xposdir1/*count*/,
                                    const ARRAY_1D xposdir2/*count*/,
                                    const int first,
                                    const int count,
                                    double& sum_log1m_result,
                                    double& dsum_log1m_result);

  double                dddsum_log1m(const ARRAY_1D xpos/*count*/,
                                     const ARRAY_1D xposdir1/*count*/,
                                     const ARRAY_1D xposdir2/*count*/,
                                     const ARRAY_1D xposdir3/*count*/,
                                     const int first,
                                     const int count,
                                     double& sum_log1m_result,
                                     double& dsum_log1m_result,
                                     double& ddsum_log1m_result);

  double                logdet_and_chol(const ARRAY_2D ain/*nchol,nchol*/,
                                        const ARRAY_2D rchol/*nchol,nchol*/,
                                        const int nchol);

  double                logdet_and_chol_neg(const ARRAY_2D neg_ain/*nchol,nchol*/,
                                            const ARRAY_2D rchol/*nchol,nchol*/,
                                            const int nchol);

  void                  backsolve_chol(const ARRAY_2D rchol/*nchol,nchol*/,
                                       const ARRAY_1D target/*nchol*/,
                                       ARRAY_1D sol/*nchol*/,
                                       const int nchol);

  double                quadform(const ARRAY_1D xqf/*nqf*/,
                                 const ARRAY_2D hqf/*nqf,nqf*/,
                                 const int nqf);

  void                  to_binc(const ARRAY_2D pars/*d1,d2*/,
                                const int d1,
                                const int d2);

  void                  from_binc(const ARRAY_2D pars/*d1,d2*/,
                                  const int d1,
                                  const int d2);

  void                  to_binc_x11(const ARRAY_1D pars/*d1*/,
                                    const int start,
                                    const int d1,
                                    const int d2);

  //ADSPLIT to_binc_x11_2
  void                  to_binc_x11_2(const ARRAY_2D pars/*nnnn, d1*/,
                                      const int nnnn,
                                      const int iiii,
                                      const int start,
                                      const int d1,
                                      const int d2);

  void                  from_binc_x11(const ARRAY_1D pars/*d1*/,
                                      const int start,
                                      const int d1,
                                      const int d2);

  void                  to_binc1(const ARRAY_1D pars/*d1*/,
                                 const int start,
                                 const int d1,
                                 const int d2);

  void                  to_binc12(const ARRAY_2D pars/*nnnn, d1*/,
                                  const int nnnn,
                                  const int iiii,
                                  const int start,
                                  const int d1,
                                  const int d2);

  void                  from_binc1(const ARRAY_1D pars/*d1*/,
                                   const int start,
                                   const int d1,
                                   const int d2);

  void                  quadform_b(const ARRAY_1D xqf/*nqf*/,
                                   ARRAY_1D xqf_b/*nqf*/,
                                   const ARRAY_2D hqf/*nqf,nqf*/,
                                   const int nqf,
                                   double& xqf_wt);

  double                quadform_d(const ARRAY_1D xqf/*nqf*/,
                                   const ARRAY_1D xqf_dir/*nqf*/,
                                   const ARRAY_2D hqf/*nqf,nqf*/,
                                   const int nqf,
                                   double& hxh);

  void                  quadform_b_d(const ARRAY_1D xqf/*nqf*/,
                                     const ARRAY_1D xqf_dir/*nqf*/,
                                     ARRAY_1D xqf_b/*nqf*/,
                                     ARRAY_1D xqf_bd/*nqf*/,
                                     const ARRAY_2D hqf/*nqf,nqf*/,
                                     const int nqf,
                                     double& xqf_wt);

  double                asymp(const double _x,
                              const double _thresh);

  double                lgamma2(const double _x);

  double                nearlymin(const double _a,
                                  const double _b);

  double                nearlymax(const double _a,
                                  const double _b);

  double                laugamp(const double _y,
                                const double _p,
                                const double _lgamma_p,
                                const bool _calc_lgamma_p);

#ifndef AD
  void                  prepare_for_chint(const int _ncheb);
#endif // AD
};


#endif //__ADT_DIFF__
