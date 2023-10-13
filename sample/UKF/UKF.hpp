// -----------------------------------------------------------------------------
// Unscented Kalman Filter
// -----------------------------------------------------------------------------
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
  int       state_dim;
  int       measurement_dim;
  int       time_dim;
  double    kappa;
  double    alpha;
  double    beta;
  R_CALL    model_output;
  R_CALL    model_state;
  R_CALL    model_limit_state;

  // observed measurement data
  ARRAY_2D  y /* time_dim, measurement_dim */;

  // time of obsevered measurement data
  ARRAY_1D  time /* time_dim */;

  /* AUTODEC */
  // process noise covariance matrix
  ARRAY_2D  process_noise_cov /* state_dim,state_dim */;

  // process noise scaling to cater for non-uniform sample time
  ARRAY_2D  process_noise_scale /* time_dim,state_dim */;

  // observation noise covariance by sample
  ARRAY_3D  measurement_noise_cov /* time_dim,measurement_dim,measurement_dim */;

  // current state
  ARRAY_2D  accumulated_process_noise_cov /* state_dim,state_dim */;
  ARRAY_2D  state_cov /* state_dim,state_dim */;
  ARRAY_1D  state_mean /* state_dim */;
  ARRAY_1D  input_state_mean /* state_dim */;
  
  ARRAY_1D  state_dev /* state_dim */;
  ARRAY_1D  state_dev2 /* state_dim */;
  ARRAY_1D  measurement_dev /* measurement_dim */;

  // cholesky decomposition temporary
  ARRAY_2D  state_chol_cov /* state_dim,state_dim */;
  ARRAY_2D  state_inv_cov /* state_dim,state_dim */;
  ARRAY_2D  measurement_chol_cov /* state_dim,state_dim */;
  ARRAY_2D  measurement_inv_cov /* state_dim,state_dim */;

  // sigma points temporary
  ARRAY_2D sigma_points /* 2 * state_dim + 1,state_dim */;
  ARRAY_2D input_sigma_points /* 2 * state_dim + 1,state_dim */;
  ARRAY_2D output_sigma_points /* 2 * state_dim + 1,measurement_dim */;

  ARRAY_3D  apriori_state_covs /* 0:time_dim,state_dim,state_dim */;
  ARRAY_2D  apriori_state_means /* 0:time_dim,state_dim */;
  
  ARRAY_3D  posterior_state_covs /* 0:time_dim,state_dim,state_dim */;
  ARRAY_2D  posterior_state_means /* 0:time_dim,state_dim */;
  ARRAY_2D  posterior_measurement_means /* time_dim,measurement_dim */;

  ARRAY_3D  smoothing_cross_covs /* 0:time_dim,state_dim,state_dim */;

  ARRAY_1D  input_state /* state_dim */;
  ARRAY_1D  output_state /* state_dim */;
  ARRAY_1D  output_measurement /* measurement_dim */;
  ARRAY_1D  last_state /* state_dim */;

  ARRAY_1D  predicted_measurement_mean /* measurement_dim */;
  ARRAY_2D  predicted_measurement_cov /* measurement_dim,measurement_dim */;
  ARRAY_2D  cross_cov /* state_dim,measurement_dim */;

  ARRAY_2D  KalmanGain /* state_dim,measurement_dim */;
  ARRAY_2D  temp_cross_cov /* state_dim,measurement_dim */;
  ARRAY_1D  innovation /* measurement_dim */;

  ARRAY_2D  SmoothingGain /* state_dim,state_dim */;
  ARRAY_2D  StateTransition /* state_dim,state_dim */;
  ARRAY_2D  working_state_mat /* state_dim,state_dim */;
  ARRAY_1D  working_state_vec /* state_dim */;

  // sigma point weights
  ARRAY_1D  wm /* 2 * state_dim + 1 */;
  ARRAY_1D  wc /* 2 * state_dim + 1 */;
  double    LogLikelihood;
  double    _gamma;
  int       n_sigma;

  ARRAY_1I  StartNA /* time_dim */;
  ARRAY_1I  EndNA /* time_dim */;
  int       NA_count;
  bool      IsNA;

#include "UKF_array_plans.hpp"

protected:
#ifndef AD
  void      printMatrix(const char* pLabel, const ARRAY_2D pA, const int nRow, const int nCol);
  void      printVector(const char* pLabel, const ARRAY_1D pV, const int nSize);
#endif

  bool            choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, 
                                        ARRAY_2D pU/* nSize, nSize */, 
                                        const int nSize);

  double          logDeterminantFromChol(const ARRAY_2D pU/* nSize, nSize */, 
                                         const int nSize);

  void            matrixInverseFromChol(const ARRAY_2D pU/* nSize, nSize */, 
                                        ARRAY_2D pInv/* nSize, nSize */, 
                                        const int nSize);

  void            inverseFromUpperTriangular(const ARRAY_2D pU/* nSize, nSize */, 
                                             ARRAY_2D pInv/* nSize, nSize */, 
                                             const int nSize);
                                             
  void            copy(ARRAY_1D target_measurement /* measurement_dim */, 
                       ARRAY_1D target_state /* state_dim */, 
                       ARRAY_2D target_covariance /* state_dim, state_dim */);

  void            initialise(const ARRAY_2D _process_noise_cov /* state_dim,state_dim */, 
                             const ARRAY_2D _process_noise_scale /* time_dim,state_dim */, 
                             const ARRAY_3D _measurement_noise_cov /* time_dim,measurement_dim,measurement_dim */, 
                             const ARRAY_1D _init_state /* state_dim */);

  void            sigmaPointsToMean(ARRAY_1D _transformed_mean /* _dim */, 
                                    const ARRAY_2D _sigma_points /* 2 * state_dim + 1,_dim */, 
                                    int _dim);

  void            resetNoiseCovariance();

  void            updateProcessNoiseCovariance(const int t);

  void            sigmaPointsToCovariance(ARRAY_2D _transformed_cov /* _dim,_dim */, 
                                          ARRAY_1D _devs /* _dim */, 
                                          const ARRAY_2D _sigma_points /* 2 * state_dim + 1,_dim */, 
                                          const ARRAY_2D _noise_cov /* _dim,_dim */,
                                          const ARRAY_1D _mean /* _dim */,
                                          int _dim);

  void            crossCovariance(ARRAY_2D _cross_cov /* state_dim,state_dim */, 
                                  const ARRAY_2D _sigma_points /* 2 * state_dim + 1,state_dim */, 
                                  const ARRAY_1D _mean /* state_dim */,
                                  const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                  const ARRAY_1D _input_mean /* state_dim */);

  void            findSigmaPoints(ARRAY_2D _sigma_points /* 2 * state_dim + 1,state_dim */, 
                                  const ARRAY_2D _chol_cov /* state_dim,state_dim */,
                                  const ARRAY_1D _mean /* state_dim */, 
                                  const ARRAY_2D _cov /* state_dim,state_dim */);

  void            propagateSigmaPoints(ARRAY_2D _output_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                       const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                       const int t);

  void            findOutput(ARRAY_1D _output_measurement /* measurment_dim */, 
                             const ARRAY_1D _input_state /* state_dim */, 
                             const int t);

  void            predictOutput(ARRAY_2D _output_sigma_points /* 2 * state_dim + 1,measurment_dim */, 
                                const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                const int t);

  void            limitState(ARRAY_1D _output_state /* state_dim */, 
                             const ARRAY_1D _input_state /* state_dim */, 
                             const ARRAY_1D _last_state /* state_dim */, 
                             const int t);

  bool            checkIsNA(const ARRAY_1D measurement /* measurement_dim */);                             
  void            clearIsNA();
  bool            isNA() const;

  void            predict(const int t);

  void            update(const ARRAY_1D measurement /* measurement_dim */, 
                         const int t);

  void            smoothingUpdate(const int t);

public:
  UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
  );

  double          filter(ARRAY_2D states /* time_dim, state_dim */, 
                         ARRAY_2D measurements /* time_dim, measurement_dim */, 
                         ARRAY_3D covariances /* time_dim, state_dim, state_dim */,                                     
                         const ARRAY_2D _process_noise_cov /* state_dim,state_dim */, 
                         const ARRAY_2D _process_noise_scale /* time_dim,state_dim */, 
                         const ARRAY_3D _measurement_noise_cov /* time_dim,measurement_dim,measurement_dim */, 
                         const ARRAY_1D _init_state /* state_dim */);

  double          smooth(ARRAY_2D states /* time_dim, state_dim */, 
                         ARRAY_2D measurements /* time_dim, measurement_dim */, 
                         ARRAY_3D covariances /* time_dim, state_dim, state_dim */);
};

// ----------------------------------------------------------------------------

inline void UnscentedKalmanFilter::clearIsNA()
{
  IsNA = false;
}

// ----------------------------------------------------------------------------

inline bool UnscentedKalmanFilter::isNA() const
{
  return (IsNA);
}

#endif  __UKF_HPP__
