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
  R_CALL    model_limit_state;
  ARRAY_2D  y /* ns, m */;  // observed measurement data
  ARRAY_1D  time /* ns */;  // observed time data
  
  /* AUTODEC */
  // UKF params
  double  lambda_;
  double  gamma;
  double  W0m;
  double  W0c;
  double  W;
  double  SavedLogLikelihood;
  int     t_start;
  bool    InNA;

  // measurement data plus interpolations for NA points
  ARRAY_2D  y_working /* ns, m */;

  // Result data
  ARRAY_2D  y_k /* 0:ns, m */;
  ARRAY_2D  x_k /* 0:ns, n */; 
  ARRAY_2D  x_k_bar /* ns, n */; 
  ARRAY_2D  y_k_smooth /* 0:ns, m */;
  ARRAY_2D  x_k_smooth /* 0:ns, n */;
  ARRAY_1B  naData /* 1:ns */;
                 
  // all vectors used in the UKF process
  ARRAY_1D  x_P /* n */;
  ARRAY_1D  x_Pc /* n */;
  ARRAY_1D  y_P /* m */;
  ARRAY_1D  ym /* m */;
  ARRAY_1D  xi /* n */;
  ARRAY_1D  xp /* n */;
  ARRAY_1D  xlast /* n */;
  ARRAY_1D  yi /* m */;

  // covarince matrices used in the process
  ARRAY_3D  P_k /* 0:ns,n,n */;   // Kalman filter covariance
  ARRAY_3D  P_k_bar /* ns,n,n */;   // Kalman filter covariance
  ARRAY_3D  chol_P_k /* ns,n,n */;
  ARRAY_3D  Ps_k /* 0:ns,n,n */;  // URTS smoothed covariance
  
  // Arrays used in smoothing
  ARRAY_2D  inv_P_k_bar /* n,n */;
  ARRAY_2D  A_k /* n,n */;
  ARRAY_1D  x_Temp /* n */;
  ARRAY_2D  chol_Ps_k /* n,n */;
  ARRAY_2D  C_k /* n,n */;

  // sigma points
  ARRAY_2D  x_sigma /* n, 2 * n + 1 */;

  // sigma points after passing through the function f/h
  ARRAY_2D  x_sigma_f /* n, 2 * n + 1 */;

  // sigma output points (ie. after passing through the function f/h)
  ARRAY_2D  y_sigma /* m, 2 * n + 1 */;
  
  // cross covariance
  ARRAY_2D  P_xy /* n,m */;
  ARRAY_2D  P_xyP /* n,m */;

  ARRAY_2D  P_y /* m,m */;
  ARRAY_2D  chol_P_y /* m,m */;
  ARRAY_2D  inv_P_y /* m,m */;
  ARRAY_2D  K /* n,m */;
  ARRAY_2D  K_P_y /* n,m */;
  ARRAY_2D  K_0 /* n,m */;
  ARRAY_2D  K_UKF_T /* m,n */;

  ARRAY_2D  Q /* n,n */; // Process noise covariance matrix
  ARRAY_2D  Qscale /* ns,n */; // vector of Q scaling to cater for non-uniform sample time
  ARRAY_3D  R /* ns,m,m */; // Observation noise covariance by sample

  double    LogLikelihood;
  double    SmoothedLogLikelihood;

  bool      Filtered;
  bool      Smoothed;
  
#include "UKF_array_plans.hpp"

protected:
  bool      choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pU/* nSize, nSize */, const int nSize);
  double    logDeterminantFromChol(const ARRAY_2D pU/* nSize, nSize */, const int nSize);
  void      matrixInverseFromChol(const ARRAY_2D pU/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize);

  void      setCovariances(double _Q, double _R);
  void      sigma_points(const ARRAY_1D vect_X /* n */, const ARRAY_2D matrix_S /* n,n */);
  void      y_UKF_calc(const int t);
  void      state(const int t);
  void      limitState(ARRAY_1D xout, const ARRAY_1D xin, const ARRAY_1D xprev, const int t);

  void      resetUKF(const ARRAY_2D _Q /* n,n */, 
                     const ARRAY_2D _Qscale /* ns,n */, 
                     const ARRAY_3D _R /* ns,m,m */, 
                     const ARRAY_1D x_0 /* n */);

  void      timeUpdate(const int t);

  void      measurementUpdate(int& t,
                              const ARRAY_1D z/* m */,
                              ARRAY_2D  x_est /* ns, n */,
                              ARRAY_2D  y_est /* ns, m */);

  void      smoothingUpdate(ARRAY_1D  x_smooth /* n */, 
                            ARRAY_1D  y_smooth /* m */, 
                            const int t, 
                            const bool bWithLogLikelihood);

public:
  UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
  );

  double    filter(ARRAY_2D  x_est /* ns, n */,
                   ARRAY_2D  y_est /* ns, m */,
                   const ARRAY_2D _Q /* n,n */, 
                   const ARRAY_2D _Qscale /* ns,n */, 
                   const ARRAY_3D _R /* ns,m,m */, 
                   const ARRAY_1D x_0 /* n */);

  double    smooth(ARRAY_2D  x_smooth /* ns, n */, 
                   ARRAY_2D  y_smooth /* ns, m */, 
                   const bool bWithLogLikelihood);
};

#endif  __UKF_HPP__
