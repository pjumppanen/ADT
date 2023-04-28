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
  ARRAY_1D  x_apriori /* n */;
  ARRAY_1D  x_aposteriori /* n */;
  ARRAY_1D  x_P /* n */;
  ARRAY_1D  y_P /* m */;
  ARRAY_1D  in_ /* m */;
  ARRAY_1D  y /* m */;
  ARRAY_1D  xi /* n */;
  ARRAY_1D  xp /* n */;
  ARRAY_1D  yi /* m */;

  // covarince matrices used in the process

  ARRAY_2D  P_apriori /* n,n */;
  ARRAY_2D  P_aprioriP /* n,n */;
  ARRAY_2D  P_aposteriori /* n,n */;

  // square root product of a given covariances s
  ARRAY_2D  sP_apriori /* n,n */;
  ARRAY_2D  sP_aposteriori /* n,n */;

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

  double Rs;
  double Qs;
  
#include "UKF_array_plans.hpp"

public:
  void    choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pL/* nSize, nSize */, const int nSize);
  void    matrixInverseFromChol(const ARRAY_2D pL/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize);

  void    setCovariances(double _Q, double _R);
  void    sigma_points(const ARRAY_1D vect_X /* n */, const ARRAY_2D matrix_S /* n,n */);
  void    y_UKF_calc();
  void    state(ARRAY_1D w/* n */);

public:
  UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
  );

  void    resetUKF(double _Q, double _R, const ARRAY_1D x_0 /* n */);
  void    timeUpdate(ARRAY_1D w/* n */);
  void    measurementUpdate(const ARRAY_1D z/* m */);
};

#endif  __UKF_HPP__
