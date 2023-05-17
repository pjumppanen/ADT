// -----------------------------------------------------------------------------
// Unscented Kalman Filter Example project based on by Jaroslaw Goslinski code in:
//
// https://github.com/jaroslav87/UKF-MNGM.git
//
// Companion article:
//
// https://jgoslinski.medium.com/the-unscented-kalman-filter-simply-the-best-python-code-5cd5ebaebf5f
//
// Implements UKF Kalman smoothing based on the Jacobian Equivalent Rauch-Tung-Striebel
// smoother (abbreviated as JE-RTS method) described in:
//
//   "A computatonally efficient unscented Kalman smoother for ameliorated tracking
//    of subatomic particles in high energy physics experiments", Jahanzeb Akhtar,
//   Imran Ghous, Muhammad Jawad, Zhaoxia Duan, Ikram Ullah Khosa, Saim Ahmed, 
//   Computer Physics Communications 283 (2023) 108585.
//
//  https://doi.org/10.1016/j.cpc.2022.108585
// -----------------------------------------------------------------------------


#ifndef __UKF_HPP__
#define __UKF_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------
// class UnscentedKalmanFilter
// ----------------------------------------------------------------------------
class UnscentedKalmanFilter : public AdtArrays
{
protected:
  /* AD_LIBNAME UKF */
  /* AD_ALIAS UKF=I_UnscentedKalmanFilter */
  /* AUTOINIT */
  int       n;  // size of the state vector
  int       m;  // size of the output vector
  int       ns; // number of samples
  double    kappa;
  double    alfa;
  double    beta;
  R_CALL    model_output;
  R_CALL    model_state;
  ARRAY_2D  y /* ns, m */; // observed measurement data
  
  /* AUTODEC */
  // UKF params
  double  lambda_;
  double  gamma;
  double  W0m;
  double  W0c;
  double  W;

  // Result data
  ARRAY_2D  y_k /* 0:ns, m */;
  ARRAY_2D  x_k /* 0:ns, n */; 
  ARRAY_2D  y_k_smooth /* 0:ns, m */;
  ARRAY_2D  x_k_smooth /* 0:ns, n */; 
                 
  // all vectors used in the UKF process
  ARRAY_1D  x_P /* n */;
  ARRAY_1D  y_P /* m */;
  ARRAY_1D  ym /* m */;
  ARRAY_1D  xi /* n */;
  ARRAY_1D  xp /* n */;
  ARRAY_1D  yi /* m */;

  // covarince matrices used in the process
  ARRAY_3D  P_k /* 0:ns,n,n */;   // Kalman filter covariance
  ARRAY_3D  chol_P_k /* ns,n,n */;
  ARRAY_3D  Ps_k /* 0:ns,n,n */;  // JE-RTS smoothed covariance
  ARRAY_2D  P_aprioriP /* n,n */;

  // Arrays used in smoothing
  ARRAY_2D  inv_P_k /* n,n */;
  ARRAY_2D  inv_root_P_km1 /* n,n */;
  ARRAY_2D  Ye_k /* n,n */;
  ARRAY_2D  A_k /* n,n */;
  ARRAY_1D  x_Temp /* n */;
  
  // clear sigma points
  ARRAY_2D  y_sigma /* m, 2 * n + 1 */;
  ARRAY_2D  x_sigma /* n, 2 * n + 1 */;

  // sigma points after passing through the function f/h
  ARRAY_2D  x_sigma_f /* n, 2 * n + 1 */;

  // cross covariances
  ARRAY_2D  P_xy /* n,m */;
  ARRAY_2D  P_xyP /* n,m */;

  ARRAY_2D  P_y /* m,m */;
  ARRAY_2D  chol_P_y /* m,m */;
  ARRAY_2D  inv_P_y /* m,m */;
  ARRAY_2D  oP_y /* m,m */;
  ARRAY_2D  P_y_P /* m,m */;
  ARRAY_2D  K /* n,m */;
  ARRAY_2D  K_P_y /* n,m */;
  ARRAY_2D  K_0 /* n,m */;
  ARRAY_2D  K_UKF_T /* m,n */;

  ARRAY_2D  Q /* n,n */;
  ARRAY_2D  R /* m,m */;

  double    Rs;
  double    Qs;
  double    LogLikelihood;
  double    SmoothedLogLikelihood;

  bool      Filtered;
  bool      Smoothed;
  
#include "UKF_array_plans.hpp"

protected:
  void      choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pU/* nSize, nSize */, const int nSize);
  double    logDeterminantFromChol(const ARRAY_2D pU/* nSize, nSize */, const int nSize);
  void      matrixInverseFromChol(const ARRAY_2D pU/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize);

  void      setCovariances(double _Q, double _R);
  void      sigma_points(const ARRAY_1D vect_X /* n */, const ARRAY_2D matrix_S /* n,n */);
  void      y_UKF_calc(const int t);
  void      state(const int t);

  void      resetUKF(const double _Q, const double _R, const ARRAY_1D x_0 /* n */);

  void      timeUpdate(const int t);

  void      measurementUpdate(const int t,
                              const ARRAY_1D z/* m */);

  void      smoothingUpdate(const int t);

public:
  UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
  );

  double    filter(ARRAY_2D  x_est /* ns, n */,
                   ARRAY_2D  y_est /* ns, m */,
                   const double _Q, 
                   const double _R, 
                   const ARRAY_1D x_0 /* n */);

  double    smooth();
};

#endif  __UKF_HPP__