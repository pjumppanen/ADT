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


#include "UKF.hpp"


// ----------------------------------------------------------------------------
// UnscentedKalmanFilter method implementations
// ----------------------------------------------------------------------------
#ifndef AD
void UnscentedKalmanFilter::printMatrix(const char* pLabel, const ARRAY_2D pA, const int nRow, const int nCol)
{
  int cn;
  int cm;
  char sBuffer[2048] = {0};

  Rprintf("\n%s\n", pLabel);

  for (cn = 1 ; cn <= nRow ; cn++)
  {
    sBuffer[0] = 0;

    for (cm = 1 ; cm <= nCol ; cm++)
    {
      sprintf(sBuffer + strlen(sBuffer), "%g ", pA[cn][cm]);
    }

    Rprintf("%s\n", sBuffer);
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::printVector(const char* pLabel, const ARRAY_1D pV, const int nSize)
{
  int cm;
  char sBuffer[2048] = {0};

  Rprintf("\n%s\n", pLabel);

  sBuffer[0] = 0;

  for (cm = 1 ; cm <= nSize ; cm++)
  {
    sprintf(sBuffer + strlen(sBuffer), "%g ", pV[cm]);
  }

  Rprintf("%s\n", sBuffer);
}
#endif

// ----------------------------------------------------------------------------

bool UnscentedKalmanFilter::choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, 
                                                  ARRAY_2D pU/* nSize, nSize */, 
                                                  const int nSize)
{
  //--------------------------------------------------------------------------
  // pA is symetric positive definite matrix
  // pU is the cholesky decomposition in upper triangular form
  //--------------------------------------------------------------------------
  double sum;
  int    ci, cj, ck;
  bool   bOk;

  bOk = true;

  for (ci = 1 ; ci <= nSize ; ci++)
  {
    sum = pA[ci][ci];

    for (cj = 1 ; cj <= ci - 1 ; cj++)
    {
      sum = sum - pU[cj][ci] * pU[cj][ci];
    }

#ifndef AD
    if (sum < 0.0)
    {
      bOk = false;
    }
#endif

    pU[ci][ci] = sqrt(sum);

    for (cj = ci + 1 ; cj <= nSize ; cj++)
    {
      sum = pA[ci][cj];

      for (ck = 1 ; ck <= ci - 1 ; ck++)
      {
        sum = sum - pU[ck][ci] * pU[ck][cj];
      }

      pU[ci][cj] = sum / pU[ci][ci];
    }
  }

  return (bOk);
}

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::logDeterminantFromChol(const ARRAY_2D pU/* nSize, nSize */, 
                                                     const int nSize)
{
  double dLogDet;
  int    ci;

  dLogDet = 0.0;

  for (ci = 1 ; ci <= nSize ; ci++)
  {
    dLogDet += log(pU[ci][ci]);
  }

  dLogDet *= 2.0;

  return (dLogDet);
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::matrixInverseFromChol(const ARRAY_2D pU/* nSize, nSize */, 
                                                  ARRAY_2D pInv/* nSize, nSize */, 
                                                  const int nSize)
{
  //--------------------------------------------------------------------------
  // pU is the cholesky decomposition of A in upper triangular form
  // pInv is the resulting upper triangular inverse matrix
  //--------------------------------------------------------------------------
  int     cc;
  int     cr;
  int     cq;
  double  b;
  double  dEntry;

  for (cc = nSize ; cc >= 1 ; cc--)
  {
    for (cr = cc ; cr >= 1 ; cr--)
    {
      b = 0.0;

      if (cr == cc)
      {
        b = (1.0 / pU[cr][cr]);
      }

      if (cr < nSize)
      {
        for (cq = 1 + cr ; cq <= nSize ; cq++)
        {
          if (cc <= cq)
          {
            b = b - pInv[cq][cc] * pU[cr][cq];
          }
          else
          {
            b = b - pInv[cc][cq] * pU[cr][cq];
          }
        }
      }

      dEntry = b * (1.0 / pU[cr][cr]);

      pInv[cc][cr] = dEntry;
      pInv[cr][cc] = dEntry;
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::inverseFromUpperTriangular(const ARRAY_2D pU/* nSize, nSize */, 
                                                       ARRAY_2D pInv/* nSize, nSize */, 
                                                       const int nSize)
{
  int i, j, k;
  double sum;

  // Initialize the result matrix as the identity matrix
  for (i = 1 ; i <= nSize ; i++)
  {
    for (j = 1 ; j <= nSize ; j++)
    {
      if (i == j)
      {
        pInv[i][j] = 1.0;
      }
      else
      {
        pInv[i][j] = 0.0;
      }
    }
  }

  // Perform back-substitution to find the inverse
  for (k = 1 ; k <= nSize ; k++)
  {
    for (i = nSize ; i >= 1 ; i--)
    {
      sum = 0.0;

      for (j = i + 2 ; j <= nSize ; j++)
      {
        sum += pU[i][j] * pInv[j][k];
      }

      pInv[i][k] = (pInv[i][k] - sum) / pU[i][i];
    }
  }
}


// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::copy(ARRAY_1D target_measurement /* measurement_dim */, 
                                 ARRAY_1D target_state /* state_dim */, 
                                 ARRAY_2D target_covariance /* state_dim, state_dim */)
{
  int cn;
  int cm;

  if (target_measurement != 0)
  {
    for (cn = 1 ; cn <= measurement_dim ; cn++)
    {
      target_measurement[cn] = output_measurement[cn];
    }
  }

  if (target_state != 0)
  {
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      target_state[cn] = state_mean[cn];
    }
  }

  if (target_covariance != 0)
  {
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      for (cm = 1 ; cm <= state_dim ; cm++)
      {
        target_covariance[cn][cm] = state_cov[cn][cm];
      }
    }
  }
}                                   

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::initialise(const ARRAY_2D _process_noise_cov /* state_dim,state_dim */, 
                                       const ARRAY_2D _process_noise_scale /* time_dim,state_dim */, 
                                       const ARRAY_3D _measurement_noise_cov /* time_dim,measurement_dim,measurement_dim */, 
                                       const ARRAY_1D _init_state /* state_dim */)
{
  int     cn;
  int     cm;
  int     ct;
  double  lambda;

  NA_count  = 0;
  IsNA      = false;

  // initialise state, covariance matrices and mean
  for (ct = 1 ; ct <= time_dim ; ct++)
  {
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      process_noise_scale[ct][cn] = _process_noise_scale[ct][cn];
    }

    for (cn = 1 ; cn <= measurement_dim ; cn++)
    {
      for (cm = 1 ; cm <= measurement_dim ; cm++)
      {
        measurement_noise_cov[ct][cn][cm] = _measurement_noise_cov[ct][cn][cm];
      }
    }
  }

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    state_mean[cn]               = _init_state[cn];
    posterior_state_means[0][cn] = state_mean[cn];
    apriori_state_means[0][cn]   = state_mean[cn];

    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      process_noise_cov[cn][cm]       = _process_noise_cov[cn][cm];
      state_cov[cn][cm]               = process_noise_scale[1][cn] * process_noise_cov[cn][cm] * process_noise_scale[1][cm];
      posterior_state_covs[0][cn][cm] = state_cov[cn][cm];
      apriori_state_covs[0][cn][cm]   = state_cov[cn][cm];
    }
  }

  // initialise sigma point weights
  n_sigma = 2 * state_dim + 1;
  lambda  = (alpha * alpha) * (state_dim + kappa) - state_dim;
  _gamma  = ::sqrt(state_dim + lambda);

  wm[1] = lambda / (state_dim + lambda);
  wc[1] = lambda / (state_dim + lambda) + (1 - (alpha * alpha) + beta);

  for (cn = 2 ; cn <= n_sigma ; cn++)
  {
    wm[cn] = 1.0 / (2.0 * (state_dim + lambda));
    wc[cn] = 1.0 / (2.0 * (state_dim + lambda));
  } 
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::sigmaPointsToMean(ARRAY_1D _transformed_mean /* _dim */, 
                                               const ARRAY_2D _sigma_points /* 2 * state_dim + 1,_dim */, 
                                               int _dim)
{
  int cn;
  int ck;

  // transformed mean
  for (cn = 1 ; cn <= _dim ; cn++)
  {
    _transformed_mean[cn] = 0.0;

    for (ck = 1 ; ck <= n_sigma ; ck++)
    {
      _transformed_mean[cn] += wm[ck] * _sigma_points[ck][cn];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::resetNoiseCovariance()
{
  zero(accumulated_process_noise_cov);
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::updateProcessNoiseCovariance(const int t)
{
  int cn;
  int cm;

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      accumulated_process_noise_cov[cn][cm] += process_noise_scale[t][cn] * process_noise_cov[cn][cm] * process_noise_scale[t][cm];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::sigmaPointsToCovariance(ARRAY_2D _transformed_cov /* _dim,_dim */, 
                                                    ARRAY_1D _devs /* _dim */, 
                                                    const ARRAY_2D _sigma_points /* 2 * state_dim + 1,_dim */, 
                                                    const ARRAY_2D _noise_cov /* _dim,_dim */,
                                                    const ARRAY_1D _mean /* _dim */,
                                                    int _dim)
{
  int cn;
  int cm;
  int ck;

  // transformed covariance
  for (cn = 1 ; cn <= _dim ; cn++)
  {
    for (cm = 1 ; cm <= _dim ; cm++)
    {
      _transformed_cov[cn][cm] = 0.0;
    }
  }

  for (ck = 1 ; ck <= n_sigma ; ck++)
  {
    for (cn = 1 ; cn <= _dim ; cn++)
    {
      _devs[cn] = _sigma_points[ck][cn] - _mean[cn];
    }

    for (cn = 1 ; cn <= _dim ; cn++)
    {
      for (cm = 1 ; cm <= _dim ; cm++)
      {
        _transformed_cov[cn][cm] += wc[ck] * _devs[cn] * _devs[cm];
      }
    }
  }

  for (cn = 1 ; cn <= _dim ; cn++)
  {
    for (cm = 1 ; cm <= _dim ; cm++)
    {
      _transformed_cov[cn][cm] += _noise_cov[cn][cm];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::crossCovariance(ARRAY_2D _cross_cov /* state_dim,state_dim */, 
                                            const ARRAY_2D _sigma_points /* 2 * state_dim + 1,state_dim */, 
                                            const ARRAY_1D _mean /* state_dim */,
                                            const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                            const ARRAY_1D _input_mean /* state_dim */)
{
  int cn;
  int cm;
  int ck;

  // cross covariance
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      _cross_cov[cn][cm] = 0.0;
    }
  }

  for (ck = 1 ; ck <= n_sigma ; ck++)
  {
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      state_dev[cn]  = _sigma_points[ck][cn] - _mean[cn];
      state_dev2[cn] = _input_sigma_points[ck][cn] - _input_mean[cn];
    }

    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      for (cm = 1 ; cm <= state_dim ; cm++)
      {
        _cross_cov[cn][cm] += wc[ck] * state_dev2[cn] * state_dev[cm];
      }
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::findSigmaPoints(ARRAY_2D _sigma_points /* 2 * state_dim + 1,state_dim */, 
                                            const ARRAY_2D _chol_cov /* state_dim,state_dim */,
                                            const ARRAY_1D _mean /* state_dim */, 
                                            const ARRAY_2D _cov /* state_dim,state_dim */)
{
  int   ck;
  int   ci;
  bool  bIsOk;

  // initialise cholesky decomposition target
  for (ci = 1 ; ci <= state_dim ; ci++)
  {
    for (ck = 1 ; ck <= state_dim ; ck++)
    {
      _chol_cov[ci][ck] = 0.0;
    }
  }

  // find cholesky decomposition
  bIsOk = choleskyDecomposition(_cov, _chol_cov, state_dim);

#ifndef AD
  if (!bIsOk)
  {
    Rf_error("cov has no Cholesky decomposition");
  }
#endif

  // find sigma points
  for (ck = 1 ; ck <= state_dim ; ck++)
  {
    _sigma_points[1][ck] = _mean[ck];
  }

  for (ci = 2 ; ci <= state_dim + 1 ; ci++)
  {
    for (ck = 1 ; ck <= state_dim ; ck++)
    {
      _sigma_points[ci][ck]             = _mean[ck] + (_gamma * _chol_cov[ck][ci - 1]);
      _sigma_points[state_dim + ci][ck] = _mean[ck] - (_gamma * _chol_cov[ck][ci - 1]);
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::propagateSigmaPoints(ARRAY_2D _output_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                                 const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                                 const int t)
{
  int cn;
  int cm;

  // get last state that the sigma points are based on. This is then
  // passed to the model_state() function as the previous state reference
  // point. Why this is necessary is because if the model has non-linearity
  // based upon relative change the model code will not be able to implement 
  // it without the previous state because it needs it to figure out if the 
  // change in state implied by a given sigma point exceeds the limit imposed
  // by the non-linearity. 
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    last_state[cn] = posterior_state_means[t-1][cn];  
  }

  for (cm = 1 ; cm <= n_sigma ; cm++)
  {
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      input_state[cn] = _input_sigma_points[cm][cn];
    }

    model_state(output_state, input_state, last_state, t, time);

    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      _output_sigma_points[cm][cn] = output_state[cn];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::findOutput(ARRAY_1D _output_measurement /* measurment_dim */, 
                                       const ARRAY_1D _input_state /* state_dim */, 
                                       const int t)
{
  int cn;

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    input_state[cn] = _input_state[cn];
  }

  model_output(output_measurement, input_state, t, time);

  for (cn = 1 ; cn <= measurement_dim ; cn++)
  {
    _output_measurement[cn] = output_measurement[cn];
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::predictOutput(ARRAY_2D _output_sigma_points /* 2 * state_dim + 1,measurment_dim */, 
                                          const ARRAY_2D _input_sigma_points /* 2 * state_dim + 1,state_dim */, 
                                          const int t)
{
  int ck;

  for (ck = 1 ; ck <= n_sigma ; ck++)
  {
    findOutput(_output_sigma_points[ck], _input_sigma_points[ck], t);
  }
}

// ----------------------------------------------------------------------------

// This method is needed to set the next state into a valid state. The process
// within the UKF is to use sigma points to calculate the next state through 
// a weighted mean. If the non-linearity in our model restricts the next state
// to a particular range (ie. in the sea and not on land), the weighted mean 
// will no necessarily be in the valid range. To avoid this happening we make
// sure that it is in the valid range by running limitState(). Statistically, it 
// will potentially mean that the mean state is slightly biased relative to the 
// covariance matrix representing it but there is no way to avoid this if we are
// to ensure filtered points do not lie on land.
void UnscentedKalmanFilter::limitState(ARRAY_1D _output_state, 
                                       const ARRAY_1D _input_state, 
                                       const ARRAY_1D _last_state, 
                                       const int t)
{
  int cn;

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    last_state[cn]  = _last_state[cn];  
    input_state[cn] = _input_state[cn];
  }

  model_limit_state(output_state, input_state, last_state, t, time);

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    _output_state[cn] = output_state[cn];
  }
}

// ----------------------------------------------------------------------------

bool UnscentedKalmanFilter::checkIsNA(const ARRAY_1D measurement /* measurement_dim */)
{
  int cn;

  IsNA = false;

  for (cn = 1 ; cn <= measurement_dim ; cn++)
  {
    if (ISNA(measurement[cn]) || ISNAN(measurement[cn]))
    {
      IsNA = true;
      break;
    }
  }

  return (IsNA);
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::predict(const int t)
{
  int cn;

  resetNoiseCovariance();
  updateProcessNoiseCovariance(t);

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    input_state_mean[cn] = state_mean[cn];
  }

  // generate sigma points
  findSigmaPoints(input_sigma_points, state_chol_cov, state_mean, state_cov);

#ifndef AD
#ifdef __TRACE
  Rprintf("time %d\n", t);
  printMatrix("sigma points", input_sigma_points, 2 * state_dim + 1, state_dim);
#endif
#endif

  // Propagate sigma points through the state transition model
  propagateSigmaPoints(sigma_points, input_sigma_points, t);

#ifndef AD
#ifdef __TRACE
  printMatrix("output sigma points", sigma_points, 2 * state_dim + 1, state_dim);
#endif
#endif

  // Find new mean
  sigmaPointsToMean(state_mean, 
                    sigma_points, 
                    state_dim);

#ifndef AD
#ifdef __TRACE
  printVector("state mean", _state_mean, state_dim);
#endif
#endif

  // Update mean to ensure it lies in valid space
  limitState(state_mean, state_mean, last_state, t);

#ifndef AD
#ifdef __TRACE
  printVector("limited state mean", _state_mean, state_dim);
#endif  
#endif

  // find new covariance
  sigmaPointsToCovariance(state_cov, 
                          state_dev, 
                          sigma_points, 
                          accumulated_process_noise_cov,
                          state_mean,
                          state_dim);

#ifndef AD
#ifdef __TRACE
  printMatrix("state cov", _state_cov, state_dim, state_dim);
#endif
#endif

  // find cross covariance for smoothing stage
  crossCovariance(smoothing_cross_covs[t], 
                  sigma_points, 
                  state_mean,
                  input_sigma_points, 
                  input_state_mean);

#ifndef AD
#ifdef __TRACE
  printMatrix("smoothing cross cov", smoothing_cross_covs[t], state_dim, state_dim);
#endif
#endif

  // find predicted model outputs
  predictOutput(output_sigma_points, 
                sigma_points, 
                t);

  // Need to update the measurement mean based on the average state
  findOutput(output_measurement, 
            state_mean, 
            t);

#ifndef AD
#ifdef __TRACE
  printMatrix("Pk", _state_cov, state_dim,state_dim);
#endif
#endif                
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::update(const ARRAY_1D measurement /* measurement_dim */, 
                                   const int t)
{
  int     cn;
  int     cm;
  int     cr;
  int     ck;
  double  dSum;
  double  dSumLklA;
  double  dSumLklB;
  bool    bIsOk;

  if (!isNA())
  {
    // Find new mean
    sigmaPointsToMean(predicted_measurement_mean, 
                      output_sigma_points, 
                      measurement_dim);

    // find new covariance
    sigmaPointsToCovariance(predicted_measurement_cov, 
                            measurement_dev, 
                            output_sigma_points, 
                            measurement_noise_cov[t],
                            predicted_measurement_mean,
                            measurement_dim);

    // calculate cross-covariance between state and measurement
    zero(cross_cov);

    for (ck = 1 ; ck <= n_sigma ; ck++)
    {
      // cross cov matrix input/output:
      for (cn = 1 ; cn <= state_dim ; cn++)
      {
        state_dev[cn] = sigma_points[ck][cn] - state_mean[cn];
      }

      for (cn = 1 ; cn <= measurement_dim ; cn++)
      {
        measurement_dev[cn] = output_sigma_points[ck][cn] - predicted_measurement_mean[cn];
      }

      for (cn = 1 ; cn <= state_dim ; cn++)
      {
        for (cm = 1 ; cm <= measurement_dim ; cm++)
        {
          cross_cov[cn][cm]  += wc[ck] * state_dev[cn] * measurement_dev[cm];
        }
      }
    }

    // Kalman gain
    zero(measurement_chol_cov);
    zero(measurement_inv_cov);

    bIsOk = choleskyDecomposition(predicted_measurement_cov, measurement_chol_cov, measurement_dim);

#ifndef AD
    if (!bIsOk)
    {
      Rf_error("measurement_cov in update() has no Cholesky decomposition");
    }
#endif

    matrixInverseFromChol(measurement_chol_cov, measurement_inv_cov, measurement_dim);

    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      for (cm = 1 ; cm <= measurement_dim ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= measurement_dim ; cr++)
        {
          dSum += cross_cov[cn][cr] * measurement_inv_cov[cr][cm];
        }

        KalmanGain[cn][cm] = dSum;
      }
    }

#ifndef AD
#ifdef __TRACE
    printMatrix("Pk_bar", state_cov, state_dim,state_dim);
    printMatrix("Kalman Gain", KalmanGain, state_dim,measurement_dim);
    printMatrix("Cross Cov", cross_cov, state_dim,measurement_dim);
    printVector("x_k", state_mean, state_dim);
#endif    
#endif

    // update state estimate
    for (cn = 1 ; cn <= measurement_dim ; cn++)
    {
      innovation[cn] = measurement[cn] - predicted_measurement_mean[cn];
    }

    dSumLklB = 0.0;

    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      dSum     = 0.0;
      dSumLklA = 0.0;

      for (cr = 1 ; cr <= measurement_dim ; cr++)
      {
        dSum    += KalmanGain[cn][cr] * innovation[cr];
        dSumLklA += measurement_inv_cov[cn][cr] * innovation[cr];
      }

      state_mean[cn] = state_mean[cn] + dSum;
      dSumLklB      += dSumLklA * innovation[cn];
    }

    // log likelihood
    LogLikelihood += (logDeterminantFromChol(measurement_chol_cov, measurement_dim) + dSumLklB + (measurement_dim * log(2 * M_PI)));

    // need to make next state comply with non-linear requirements of model
    limitState(state_mean, state_mean, posterior_state_means[t-1], t);

    // Update the model output
    findOutput(output_measurement, state_mean, t);

    // update state covariance
    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      for (cm = 1 ; cm <= measurement_dim ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= measurement_dim ; cr++)
        {
          dSum += KalmanGain[cn][cr] * predicted_measurement_cov[cr][cm];
        }

        temp_cross_cov[cn][cm] = dSum;
      }
    }

    for (cn = 1 ; cn <= state_dim ; cn++)
    {
      for (cm = 1 ; cm <= state_dim ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= measurement_dim ; cr++)
        {
          dSum += temp_cross_cov[cn][cr] * KalmanGain[cm][cr];
        }

        state_cov[cn][cm] = state_cov[cn][cm] - dSum;
      }
    }
#ifndef AD
#ifdef __TRACE
    printVector("x_k_bar", state_mean, state_dim);
    printVector("y_k", output_measurement, measurement_dim);
#endif
#endif  
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::smoothingUpdate(const int t)
{
  int     cn;
  int     cm;
  int     cr;
  double  dSum;
  bool    bIsOk;

  // Do smoothing using the RTS method
  zero(state_chol_cov);
  zero(state_inv_cov);

#ifndef AD
#ifdef __TRACE
  printMatrix("apriori_state_covs[t]", apriori_state_covs[t], state_dim,state_dim);
#endif
#endif

  bIsOk = choleskyDecomposition(apriori_state_covs[t], state_chol_cov, state_dim);

#ifndef AD
  if (!bIsOk)
  {
    Rf_error("apriori_state_covs[t] in smoothingUpdate() has no Cholesky decomposition");
  }
#endif

  matrixInverseFromChol(state_chol_cov, state_inv_cov, state_dim);

#ifndef AD
#ifdef __TRACE
  printMatrix("apriori_state_covs[t] inverse", state_inv_cov, state_dim,state_dim);
#endif
#endif

  // Calculate Dk, state transition matrix (conceptually from EKF)
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= state_dim ; cr++)
      {
        dSum += smoothing_cross_covs[t][cn][cr] * state_inv_cov[cr][cm];
      }

      StateTransition[cn][cm] = dSum;
    }
  }

#ifndef AD
#ifdef __TRACE
  printMatrix("Dk", StateTransition, state_dim,state_dim);
#endif
#endif

  // Calculate Ak, smoothing gain
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= state_dim ; cr++)
      {
        // t(Dk) * inv(aP[t])
        dSum += StateTransition[cr][cn] * state_inv_cov[cr][cm];
      }

      working_state_mat[cn][cm] = dSum;
    }
  }

#ifndef AD
#ifdef __TRACE
  printMatrix("working_state_mat", working_state_mat, state_dim,state_dim);
#endif
#endif

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= state_dim ; cr++)
      {
        // pP[t] * t(Dk) * inv(aP[t])
        dSum += posterior_state_covs[t-1][cm][cr] * working_state_mat[cr][cn];
      }

      SmoothingGain[cm][cn] = dSum;
    }
  }

#ifndef AD
#ifdef __TRACE
  printMatrix("Ak", SmoothingGain, state_dim,state_dim);
  printMatrix("state_cov", state_cov, state_dim,state_dim);
  printMatrix("apriori_state_covs[t]", apriori_state_covs[t], state_dim,state_dim);
#endif
#endif

  // Update Smoothed covariance
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= state_dim ; cr++)
      {
        // (aP[t] - S) * t(Ak)
        dSum += (apriori_state_covs[t][cn][cr] - state_cov[cn][cr]) * SmoothingGain[cm][cr];
      }

      working_state_mat[cn][cm] = dSum;
    }
  }

#ifndef AD
#ifdef __TRACE
  printMatrix("working_state_mat", working_state_mat, state_dim,state_dim);
#endif
#endif

  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= state_dim ; cr++)
      {
        // Ak * (aP[t] - S) * t(Ak)
        dSum += SmoothingGain[cn][cr] * working_state_mat[cr][cm];
      }

      state_cov[cn][cm] = posterior_state_covs[t-1][cn][cm] - dSum;
    }
  }

#ifndef AD
#ifdef __TRACE
  printMatrix("state_cov", state_cov, state_dim,state_dim);
#endif
#endif

  // Update Smoothed mean
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    dSum = 0.0;

    for (cr = 1 ; cr <= state_dim ; cr++)
    {
      dSum += SmoothingGain[cn][cr] * (state_mean[cr] - apriori_state_means[t][cr]);
    }

    working_state_vec[cn] = posterior_state_means[t-1][cn] + dSum;
  }

#ifndef AD
#ifdef __TRACE
  printVector("state_mean", state_mean, state_dim);
  printVector("smoothed state_mean", working_state_vec, state_dim);
#endif
#endif

  // need to make next state comply with non-linear requirements of model
  limitState(state_mean, working_state_vec, state_mean, t-1);

  // Update the model output
  findOutput(output_measurement, state_mean, t-1);
}

// ----------------------------------------------------------------------------

UnscentedKalmanFilter::UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
)
 : model_output(),
   model_state(),
   model_limit_state()
{
  double lambda;

  #include "UKF_constructor_locals.hpp"
  #include "UKF_constructor_scalars_phase_1.hpp"
  
  n_sigma = 2 * state_dim + 1;
  lambda  = (alpha * alpha) * (state_dim + kappa) - state_dim;
  _gamma  = ::sqrt(state_dim + lambda);

  #include "UKF_constructor_arrays_phase_1.hpp"
  #include "UKF_array_plans_init.hpp"
}

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::filter(ARRAY_2D states /* time_dim, state_dim */, 
                                     ARRAY_2D measurements /* time_dim, measurement_dim */, 
                                     ARRAY_3D covariances /* time_dim, state_dim, state_dim */,                                     
                                     const ARRAY_2D _process_noise_cov /* state_dim,state_dim */, 
                                     const ARRAY_2D _process_noise_scale /* time_dim,state_dim */, 
                                     const ARRAY_3D _measurement_noise_cov /* time_dim,measurement_dim,measurement_dim */, 
                                     const ARRAY_1D _init_state /* state_dim */)
{
  int   t;
  int   cn;
  bool  bIsNA;
  bool  bLastIsNA;
  
  initialise(_process_noise_cov, 
             _process_noise_scale, 
             _measurement_noise_cov, 
             _init_state);

  LogLikelihood = 0.0;             

  for (t = 1 ; t <= time_dim ; t++)
  {
    bLastIsNA = isNA();
    bIsNA     = checkIsNA(y[t]);

    if (bLastIsNA != bIsNA)
    {
      // track NA segments
      if (bIsNA)
      {
        NA_count++;

        StartNA[NA_count] = t;
      }
      else
      {
        EndNA[NA_count] = t;
      }
    }

    predict(t);
    copy(0, apriori_state_means[t], apriori_state_covs[t]);

    update(y[t], t);
    copy(posterior_measurement_means[t], posterior_state_means[t], posterior_state_covs[t]);

    // Save the smoothed state estimate and covariance
    copy(measurements[t], states[t], covariances[t]);
  }

  LogLikelihood *= -0.5;

  return (LogLikelihood);
}                                     

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::smooth(ARRAY_2D states /* time_dim, state_dim */, 
                                     ARRAY_2D measurements /* time_dim, measurement_dim */, 
                                     ARRAY_3D covariances /* time_dim, state_dim, state_dim */)
{
  int t;
  int cn;
  int cm;

  // intitialise the starting smoothed state
  for (cn = 1 ; cn <= state_dim ; cn++)
  {
    state_mean[cn]       = posterior_state_means[time_dim][cn];
    states[time_dim][cn] = posterior_state_means[time_dim][cn];

    for (cm = 1 ; cm <= state_dim ; cm++)
    {
      state_cov[cn][cm]             = posterior_state_covs[time_dim][cn][cm];
      covariances[time_dim][cn][cm] = posterior_state_covs[time_dim][cn][cm];
    }
  }

  for (cn = 1 ; cn <= measurement_dim ; cn++)
  {
    measurements[time_dim][cn] = posterior_measurement_means[time_dim][cn];
  }

  for (t = time_dim ; t >= 2 ; t--)
  {
    smoothingUpdate(t);

    // Save the smoothed state estimate and covariance
    copy(measurements[t-1], states[t-1], covariances[t-1]);
  }

  return (0);
}
