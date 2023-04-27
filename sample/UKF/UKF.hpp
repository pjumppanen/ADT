// -----------------------------------------------------------------------------
// Unscented Kalman Filter Example project based on by Jaroslaw Goslinski code in:
//
// https://github.com/jaroslav87/UKF-MNGM.git
//
// Companion article:
//
// https://jgoslinski.medium.com/the-unscented-kalman-filter-simply-the-best-python-code-5cd5ebaebf5f
// 
// -----------------------------------------------------------------------------

#ifndef __UKF_HPP__
#define __UKF_HPP__


#include <adtarrays.hpp>
#include "adtR.hpp"


// ----------------------------------------------------------------------------
// log likelihood of kalman filter is,
// 
// -0.5 * Sum(log det(SigmaYYi) + t(Yi) * inverse(SigmaYYi) * Yi) + c
//
// where SigmaYYi is the output covariance matrix for time i 
// and Yi is the predicted model output for time i
//
// Should be able to update this on the fly through a model run.
//
// Also in state update if we have missing data the variance updates should
// not occur and should inherit the previous time steps estimates.
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------

class UnscentedKalmanFilter : public AdtArrays
{
protected:
  /* AD_LIBNAME UKF */
  /* AD_ALIAS UKF=I_UnscentedKalmanFilter */
  /* AUTOINIT */
  int     n;  // size of the state vector
  int     m;  // size of the output vector
  double  kappa;
  double  alfa;
  double  beta;
  R_CALL  model_output;
  R_CALL  model_state;
  
  /* AUTODEC */
  // UKF params
  double  lambda_;
  double  gamma;
  double  W0m;
  double  W0c;
  double  W;

  // all vectors used in the UKF process
  ARRAY_1D  x_apriori /* 0:n-1 */;
  ARRAY_1D  x_aposteriori /* 0:n-1 */;
  ARRAY_1D  x_P /* 0:n-1 */;
  ARRAY_1D  y_P /* 0:m-1 */;
  ARRAY_1D  in_ /* 0:m-1 */;
  ARRAY_1D  y /* 0:m-1 */;
  ARRAY_1D  xi /* 0:n-1 */;
  ARRAY_1D  xp /* 0:n-1 */;
  ARRAY_1D  yi /* 0:m-1 */;

  // covarince matrices used in the process

  ARRAY_2D  P_apriori /* 0:n-1,0:n-1 */;
  ARRAY_2D  P_aprioriP /* 0:n-1,0:n-1 */;
  ARRAY_2D  P_aposteriori /* 0:n-1,0:n-1 */;

  // square root product of a given covariances s
  ARRAY_2D  sP_apriori /* 0:n-1,0:n-1 */;
  ARRAY_2D  sP_aposteriori /* 0:n-1,0:n-1 */;

  // clear sigma points
  ARRAY_2D  y_sigma /* 0:m-1, 0:2*n */;
  ARRAY_2D  x_sigma /* 0:n-1, 0:2*n */;

  // sigma points after passing through the function f/h
  ARRAY_2D  x_sigma_f /* 0:n-1, 0:2*n */;

  // cross covariances
  ARRAY_2D  P_xy /* 0:n-1,0:m-1 */;
  ARRAY_2D  P_xyP /* 0:n-1,0:m-1 */;

  ARRAY_2D  P_y /* 0:m-1,0:m-1 */;
  ARRAY_2D  chol_P_y /* 0:m-1,0:m-1 */;
  ARRAY_2D  inv_P_y /* 0:m-1,0:m-1 */;
  ARRAY_2D  oP_y /* 0:m-1,0:m-1 */;
  ARRAY_2D  P_y_P /* 0:m-1,0:m-1 */;
  ARRAY_2D  K /* 0:n-1,0:m-1 */;
  ARRAY_2D  K_P_y /* 0:n-1,0:m-1 */;
  ARRAY_2D  K_0 /* 0:n-1,0:m-1 */;
  ARRAY_2D  K_UKF_T /* 0:m-1,0:n-1  */;

  ARRAY_2D  Q /* 0:n-1,0:n-1 */;
  ARRAY_2D  R /* 0:m-1,0:m-1 */;

  double Rs;
  double Qs;
  
#include "UKF_array_plans.hpp"

public:
  void    choleskyDecomposition(const ARRAY_2D pA/* 0:nSize-1, 0:nSize-1 */, ARRAY_2D pL/* 0:nSize-1, 0:nSize-1 */, const int nSize);
  void    matrixInverseFromChol(const ARRAY_2D pL/* 0:nSize-1, 0:nSize-1 */, ARRAY_2D pInv/* 0:nSize-1, 0:nSize-1 */, const int nSize);

  void    setCovariances(double _Q, double _R);
  void    sigma_points(const ARRAY_1D vect_X /* 0:n-1 */, const ARRAY_2D matrix_S /* 0:n-1,0:n-1 */);
  void    y_UKF_calc();
  void    state(ARRAY_1D w/* 0:n-1 */);

public:
  UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
  );

  void    resetUKF(double _Q, double _R, const ARRAY_1D x_0 /* 0:n-1 */);
  void    timeUpdate(ARRAY_1D w/* 0:n-1 */);
  void    measurementUpdate(const ARRAY_1D z/* 0:m-1 */);
};

#endif  __UKF_HPP__
