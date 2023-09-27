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


#include "UKF.hpp"


// ----------------------------------------------------------------------------
// UnscentedKalmanFilter method implementations
// ----------------------------------------------------------------------------
bool UnscentedKalmanFilter::choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pU/* nSize, nSize */, const int nSize)
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

double UnscentedKalmanFilter::logDeterminantFromChol(const ARRAY_2D pU/* nSize, nSize */, const int nSize)
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

void UnscentedKalmanFilter::matrixInverseFromChol(const ARRAY_2D pU/* nSize, nSize */, ARRAY_2D pInv/* nSize, nSize */, const int nSize)
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

UnscentedKalmanFilter::UnscentedKalmanFilter(
#include "UKF_constructor_args.hpp"
)
 : model_output(),
   model_state(),
   model_limit_state()
{
  #include "UKF_constructor_locals.hpp"
  #include "UKF_constructor_scalars_phase_1.hpp"
  #include "UKF_constructor_arrays_phase_1.hpp"
  #include "UKF_array_plans_init.hpp"

  // UKF params
  lambda_     = (n + kappa) * alfa * alfa - n;
  gamma       = sqrt(n + lambda_);
  W0m         = lambda_ / (n + lambda_);
  W0c         = lambda_ / (n + lambda_) + (1.0 - alfa * alfa + beta);
  W           = 1.0 / (2.0 * (n + lambda_));

  zero(y_k);
  zero(x_k);
  zero(x_k_bar);
  zero(y_k_smooth);
  zero(x_k_smooth);

  // all vectors used in the UKF process
  zero(x_P);
  zero(y_P);
  zero(ym);

  // covarince matrices used in the process
  zero(P_k);
  zero(P_k_bar);
  zero(chol_P_k);
  zero(Ps_k);

  // clear sigma points
  zero(y_sigma);
  zero(x_sigma);

  // sigma points after passing through the function f/h
  zero(x_sigma_f);

  // cross covariances
  zero(P_xy);
  zero(P_xyP);

  zero(P_y);
  zero(K);
  zero(K_0);
  zero(K_UKF_T);

  Filtered = false;
  Smoothed = false;
}

// ----------------------------------------------------------------------------
// Q - process noise covraiance,
// Qscale - process noise covraiance scaling by sample
// R - measurement noise covariance,
// x_0 - initial state
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::resetUKF(const ARRAY_2D _Q /* n,n */, 
                                     const ARRAY_2D _Qscale /* ns,n */, 
                                     const ARRAY_3D _R /* ns,m,m */, 
                                     const ARRAY_1D x_0 /* n */)
{
  int cn;
  int cm;
  int ct;

  zero(y_k);
  zero(x_k);
  zero(x_k_bar);
  zero(y_k_smooth);
  zero(x_k_smooth);

  zero(ym);
  zero(y_P);
  zero(P_y);
  zero(P_xy);
  zero(P_xyP);
  
  zero(K);
  zero(K_0);
  zero(K_UKF_T);

  zero(y_sigma);
  zero(x_sigma);
  zero(x_sigma_f);

  zero(P_k);
  zero(P_k_bar);
  zero(chol_P_k);

  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      Q[cn][cm] = _Q[cn][cm];
    }
  }

  for (ct = 1 ; ct <= ns ; ct++)
  {
    for (cn = 1 ; cn <= n ; cn++)
    {
      Qscale[ct][cn] = _Qscale[ct][cn];
    }

    for (cn = 1 ; cn <= m ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        R[ct][cn][cm] = _R[ct][cn][cm];
      }
    }
  }

  for (cn = 1 ; cn <= n ; cn++)
  {
    x_k[0][cn] = x_0[cn];

    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k[0][cn][cm] = Qscale[1][cn] * Q[cn][cm] * Qscale[1][cm];
    }
  }

  zero(x_P);

  LogLikelihood         = 0.0;
  SmoothedLogLikelihood = 0.0;
  
  Filtered = false;
  Smoothed = false;
}


// ----------------------------------------------------------------------------
// vect_X - state vector
// sigma points are drawn from P
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::sigma_points(const ARRAY_1D vect_X /* n */, const ARRAY_2D matrix_S /* n,n */)
{
  int ck;
  int cn;

  for (cn = 1 ; cn <= n ; cn++)
  {
    x_sigma[cn][1] = vect_X[cn];
  }

  for (ck = 2 ; ck <= n + 1 ; ck++)
  {
    for (cn = 1 ; cn <= n ; cn++)
    {
      x_sigma[cn][ck]     = vect_X[cn] + gamma * matrix_S[cn][ck - 1];
      x_sigma[cn][n + ck] = vect_X[cn] - gamma * matrix_S[cn][ck - 1];
    }
  }
}

// ----------------------------------------------------------------------------
// finding the y = h(x, ...)
// the input is x_sigma, which is using h(...) then we find y_sigma_UKF from which we get to the y_UKF
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::y_UKF_calc(const int t)
{
  int ck;
  int cn;

  for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
  {
    for (cn = 1 ; cn <= n ; cn++)
    {
      xi[cn] = x_sigma_f[cn][ck];
    }

    model_output(yi, xi, t);

    for (cn = 1 ; cn <= m ; cn++)
    {
      y_sigma[cn][ck] = yi[cn];
    }
  }

  // y_UKF
  for (cn = 1 ; cn <= m ; cn++)
  {
    ym[cn] = W0m * y_sigma[cn][1];
  }

  for (ck = 2 ; ck <= 2 * n + 1; ck++)
  {
    for (cn = 1 ; cn <= m ; cn++)
    {
      ym[cn] += W * y_sigma[cn][ck];
    }
  }
}

// ----------------------------------------------------------------------------
// w - input vector data
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::state(const int t)
{
  int j;
  int cn;

  // get last state that the sigma points are based on. This is then
  // passed to the model_state() function as the previous state reference
  // point. Why this is necessary is because if the model has non-linearity
  // based upon relative change the model code will not be able to implement 
  // it without the previous state because it needs it to figure out if the 
  // change in state implied by a given sigma point exceeds the limit imposed
  // by the non-linearity. 
  for (j = 1 ; j <= n ; j++)
  {
    xlast[j] = x_k[t-1][j];  
  }

  for (j = 1 ; j <= 2 * n + 1 ; j++)
  {
    for (cn = 1 ; cn <= n ; cn++)
    {
      xp[cn] = x_sigma[cn][j];
    }

    model_state(xi, xp, xlast, t);

    for (cn = 1 ; cn <= n ; cn++)
    {
      x_sigma_f[cn][j] = xi[cn];
    }
  }
}

// ----------------------------------------------------------------------------

// This method is needed to set the next state into a valid state. The process
// within the UKF is to use sigma points to calculate the next state through 
// a weighted mean. If the non-linearity in our model restricts the next state
// to a particular range (ie. in the sea and not on land), the weighted mean 
// will no necessarily be in the valid range. To avoid this happening we make
// sure that it is in the valid range by 
void UnscentedKalmanFilter::limitState(ARRAY_1D xout, const ARRAY_1D xin, const ARRAY_1D xprev, const int t)
{
  int j;

  for (j = 1 ; j <= n ; j++)
  {
    xlast[j] = xprev[j];  
    xp[j]    = xin[j];
  }

  model_limit_state(xi, xp, xlast, t);

  for (j = 1 ; j <= n ; j++)
  {
    xout[j] = xi[j];
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::timeUpdate(const int t)
{
  int     cn;
  int     cm;
  int     ck;
  double  dW;
  bool    bIsOk;

  bIsOk = choleskyDecomposition(P_k[t-1], chol_P_k[t], n);
#ifndef AD
  if (!bIsOk)
  {
    Rf_error("P_k in timeUpdate() has no Cholesky decomposition");
  }
#endif

  sigma_points(x_k[t-1], chol_P_k[t]);
  state(t);

  // apriori state:
  for (cn = 1 ; cn <= n ; cn++)
  {
    x_k_bar[t][cn] = W0m * x_sigma_f[cn][1];

    for (ck = 2 ; ck <= 2 * n + 1 ; ck++)
    {
      x_k_bar[t][cn] += W * x_sigma_f[cn][ck]; 
    }
  }

  // need to make next state comply with non-linear requirements of model
  limitState(x_k_bar[t], x_k_bar[t], x_k[t-1], t);

  // apriori covariance matrix:
  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k_bar[t][cn][cm] = 0.0;
    }
  }

  for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
  {
    if (ck == 1)
    {
      dW = W0c;
    }
    else
    {
      dW = W;
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      x_P[cn] = x_sigma_f[cn][ck] - x_k_bar[t][cn];
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      for (cm = 1 ; cm <= n ; cm++)
      {
        P_k_bar[t][cn][cm] += dW * x_P[cn] * x_P[cm];
      }
    }
  }

  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k_bar[t][cn][cm] += Qscale[t][cn] * Q[cn][cm] * Qscale[t][cm];
    }
  }

  y_UKF_calc(t);
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::measurementUpdate(const int t,
                                              const ARRAY_1D z/* m */)
{
  int     ck;
  int     cn;
  int     cm;
  int     cr;
  double  dW;
  double  dSum;
  double  yt_invPy_y; 
  bool    bIsNA;
  bool    bIsOk;

  bIsNA = false;

  for (cn = 1 ; cn <= m ; cn++)
  {
    if (ISNA(z[cn]) || ISNAN(z[cn]))
    {
      bIsNA = true;
      break;
    }
  }

  naData[t] = bIsNA;

  if (bIsNA)
  {
    // with NA data next state equals previous state
    for (cn = 1 ; cn <= n ; cn++)
    {
      x_k[t][cn] = x_k_bar[t][cn];

      for (cm = 1 ; cm <= n ; cm++)
      {
        P_k[t][cn][cm]  = P_k_bar[t][cn][cm];
      }
    }
  }
  else
  {
    zero(P_y);

    // only do measurement update if we have a new measurement
    for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
    {
      if (ck == 1)
      {
        dW = W0c;
      }
      else
      {
        dW = W;
      }

      // cov matrix output/output
      for (cn = 1 ; cn <= m ; cn++)
      {
        y_P[cn] = y_sigma[cn][ck] - ym[cn];
      }

      for (cn = 1 ; cn <= m ; cn++)
      {
        for (cm = 1 ; cm <= m ; cm++)
        {
          P_y[cn][cm]  += dW * y_P[cn] * y_P[cm];
        }
      }
    }

    for (cn = 1 ; cn <= m ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        P_y[cn][cm]  += R[t][cn][cm];
      }
    }

    zero(P_xy);

    for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
    {
      if (ck == 1)
      {
        dW = W0c;
      }
      else
      {
        dW = W;
      }

      // cross cov matrix input/output:
      for (cn = 1 ; cn <= n ; cn++)
      {
        x_P[cn] = x_sigma_f[cn][ck] - x_k_bar[t][cn];
      }

      for (cn = 1 ; cn <= m ; cn++)
      {
        y_P[cn] = y_sigma[cn][ck] - ym[cn];
      }

      for (cn = 1 ; cn <= n ; cn++)
      {
        for (cm = 1 ; cm <= m ; cm++)
        {
          P_xyP[cn][cm]  = dW * x_P[cn] * y_P[cm];
          P_xy[cn][cm]  += P_xyP[cn][cm];
        }
      }
    }

    // kalman gain:
    zero(chol_P_y);

    bIsOk = choleskyDecomposition(P_y, chol_P_y, m);
#ifndef AD
    if (!bIsOk)
    {
      Rf_error("P_y in measurementUpdate() has no Cholesky decomposition");
    }
#endif

    matrixInverseFromChol(chol_P_y, inv_P_y, m);

    for (cn = 1 ; cn <= n ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= m ; cr++)
        {
          dSum += P_xy[cn][cr] * inv_P_y[cr][cm];
        }

        K[cn][cm] = dSum;
      }
    }

    // log likelihood
    yt_invPy_y = 0.0;

    for (cn = 1 ; cn <= m ; cn++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= m ; cr++)
      {
        dSum += inv_P_y[cn][cr] * (z[cr] - ym[cr]);
      }

      yt_invPy_y += dSum * (z[cn] - ym[cn]);
    }

    LogLikelihood += (logDeterminantFromChol(chol_P_y, m) + yt_invPy_y + (m * log(2 * M_PI)));

    // aposteriori state:
    for (cn = 1 ; cn <= m ; cn++)
    {
      y_P[cn] = z[cn] - ym[cn];
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= m ; cr++)
      {
        dSum += K[cn][cr] * y_P[cr];
      }

      x_k[t][cn] = x_k_bar[t][cn] + dSum;
    }

    // need to make next state comply with non-linear requirements of model
    limitState(x_k[t], x_k[t], x_k[t-1], t);

    // cov aposteriori:
    for (cn = 1 ; cn <= n ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= m ; cr++)
        {
          dSum += K[cn][cr] * P_y[cr][cm];
        }

        K_P_y[cn][cm] = dSum;
      }
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      for (cm = 1 ; cm <= n ; cm++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= m ; cr++)
        {
          dSum += K_P_y[cn][cr] * K[cm][cr];
        }

        P_k[t][cn][cm] = P_k_bar[t][cn][cm] - dSum;
      }
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::smoothingUpdate(ARRAY_1D  x_smooth /* n */, 
                                            ARRAY_1D  y_smooth /* m */, 
                                            const int t, 
                                            const bool bWithLogLikelihood)
{
  int     cr;
  int     cc;
  int     cn;
  int     cm;
  int     ck;
  double  dSum;
  double  dW;
  double  yt_invPy_y;
  bool    bIsOk;

  // find smoothing gain
  zero(A_k);

  // find chol_Ps_k
  bIsOk = choleskyDecomposition(Ps_k[t+1], chol_Ps_k, n);
#ifndef AD
  if (!bIsOk)
  {
    Rf_error("P_k_bar[t] in smoothingUpdate() has no Cholesky decomposition");
  }
#endif

  // Find new sigma points
  sigma_points(x_k[t], chol_Ps_k);
  state(t);

  // apriori state:
  for (cn = 1 ; cn <= n ; cn++)
  {
    x_k_bar[t+1][cn] = W0m * x_sigma_f[cn][1];
    xi[cn]           = W0m * x_sigma[cn][1];

    for (ck = 2 ; ck <= 2 * n + 1 ; ck++)
    {
      x_k_bar[t+1][cn] += W * x_sigma_f[cn][ck]; 
      xi[cn]           += W * x_sigma[cn][ck]; 
    }
  }

  // apriori covariance matrix:
  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k_bar[t+1][cn][cm] = 0.0;
      C_k[cn][cm]          = 0.0;
    }
  }

  for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
  {
    if (ck == 1)
    {
      dW = W0c;
    }
    else
    {
      dW = W;
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      x_P[cn]  = x_sigma_f[cn][ck] - x_k_bar[t+1][cn];
      x_Pc[cn] = x_sigma[cn][ck] - xi[cn]; // This looks like it is using the wrong x_sigma
    }

    for (cn = 1 ; cn <= n ; cn++)
    {
      for (cm = 1 ; cm <= n ; cm++)
      {
        C_k[cn][cm]          += dW * x_Pc[cn] * x_P[cm];
        P_k_bar[t+1][cn][cm] += dW * x_P[cn] * x_P[cm];
      }
    }
  }

  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k_bar[t+1][cn][cm] += Qscale[t+1][cn] * Q[cn][cm] * Qscale[t+1][cm];
    }
  }

  y_UKF_calc(t+1);

  if (naData[t])
  {
    // with NA data next smoothed state equals previous state
    for (cc = 1 ; cc <= n ; cc++)
    {
      x_smooth[cc]      = x_k_smooth[t+1][cc];
      x_k_smooth[t][cc] = x_k[t][cc];

      for (cr = 1 ; cr <= n ; cr++)
      {
        Ps_k[t][cr][cc] = Ps_k[t+1][cr][cc];
      }
    }

    for (cc = 1 ; cc <= m ; cc++)
    {
      y_smooth[cc]      = y_k_smooth[t+1][cc];
      y_k_smooth[t][cc] = yi[cc];
    }
  }
  else
  {
    zero(P_y);

    // Find P_y
    for (ck = 1 ; ck <= 2 * n + 1 ; ck++)
    {
      if (ck == 1)
      {
        dW = W0c;
      }
      else
      {
        dW = W;
      }

      // cov matrix output/output
      for (cn = 1 ; cn <= m ; cn++)
      {
        y_P[cn] = y_sigma[cn][ck] - ym[cn];
      }

      for (cn = 1 ; cn <= m ; cn++)
      {
        for (cm = 1 ; cm <= m ; cm++)
        {
          P_y[cn][cm]  += dW * y_P[cn] * y_P[cm];
        }
      }
    }

    for (cn = 1 ; cn <= m ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        P_y[cn][cm]  += R[t+1][cn][cm];
      }
    }

    // find smoothing gain
    zero(A_k);

    // Use A_k as temp to find inv_P_k_bar
    bIsOk = choleskyDecomposition(P_k_bar[t+1], A_k, n);
#ifndef AD
    if (!bIsOk)
    {
      Rf_error("P_k_bar[t] in smoothingUpdate() has no Cholesky decomposition");
    }
#endif

    zero(inv_P_k_bar);

    matrixInverseFromChol(A_k, inv_P_k_bar, n);

    // A_k = C_k * inv_P_k_bar
    for (cc = 1 ; cc <= n ; cc++)
    {
      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = 0.0;

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += C_k[cr][cn] * inv_P_k_bar[cn][cc];
        }

        A_k[cr][cc] = dSum;
      }
    }

    // A_k = Ps_k[t] * A_k 
    for (cc = 1 ; cc <= n ; cc++)
    {
      for (cr = 1 ; cr <= n ; cr++)
      {
        x_Temp[cr] = A_k[cr][cc];
      }

      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = 0.0;

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += Ps_k[t][cr][cn] * x_Temp[cn];
        }

        A_k[cr][cc] = dSum;
      }
    }

    // find smoothed state
    for (cr = 1 ; cr <= n ; cr++)
    {
      dSum = x_k[t][cr];

      for (cc = 1 ; cc <= n ; cc++)
      {
        dSum += A_k[cr][cc] * (x_k_smooth[t+1][cc] - x_k_bar[t+1][cc]);
      }

      x_k_smooth[t][cr] = dSum;
      x_smooth[cr]      = dSum;
    }

    // need to make next state comply with non-linear requirements of model
    limitState(x_k_smooth[t], x_k_smooth[t], x_k_smooth[t], t+1);

    for (cr = 1 ; cr <= n ; cr++)
    {
      xi[cr] = x_k_smooth[t][cr];
    }

    model_output(yi, xi, t+1);

    for (cc = 1 ; cc <= m ; cc++)
    {
      y_k_smooth[t][cc] = yi[cc];
      y_smooth[cc]      = yi[cc];
    }

    // find smoothed covariance
    // Ps_k[t] = (P_k_bar[t+1] - Ps_k[t+1]) * t(A_k)
    for (cr = 1 ; cr <= n ; cr++)
    {
      for (cc = 1 ; cc <= n ; cc++)
      {
        dSum = 0.0;

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += (P_k_bar[t+1][cr][cn] - Ps_k[t+1][cr][cn]) * A_k[cc][cn];
        }

        Ps_k[t][cr][cc] = dSum;
      }
    }

    // Ps_k[t] = P_k[t] - A_k * Ps_k[t]
    for (cc = 1 ; cc <= n ; cc++)
    {
      for (cr = 1 ; cr <= n ; cr++)
      {
        x_Temp[cr] = Ps_k[t][cr][cc];
      }

      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = P_k[t][cr][cc];

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += -A_k[cr][cn] * x_Temp[cn];
        }

        Ps_k[t][cr][cc] = dSum;
      }
    }

    // Find loglikelihood
    zero(chol_P_y);

    bIsOk = choleskyDecomposition(P_y, chol_P_y, m);
#ifndef AD
    if (!bIsOk)
    {
      Rf_error("P_y in smoothingUpdate() has no Cholesky decomposition");
    }
#endif

    matrixInverseFromChol(chol_P_y, inv_P_y, m);

    yt_invPy_y = 0.0;

    for (cn = 1 ; cn <= m ; cn++)
    {
      dSum = 0.0;

      for (cr = 1 ; cr <= m ; cr++)
      {
        dSum += inv_P_y[cn][cr] * (y[t][cr] - ym[cr]);
      }

      yt_invPy_y += dSum * (y[t][cn] - ym[cn]);
    }

    SmoothedLogLikelihood += (logDeterminantFromChol(chol_P_y, m) + yt_invPy_y + (m * log(2 * M_PI)));
  }
}

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::filter(ARRAY_2D  x_est /* ns, n */, 
                                     ARRAY_2D  y_est /* ns, m */, 
                                     const ARRAY_2D _Q /* n,n */, 
                                     const ARRAY_2D _Qscale /* ns,n */, 
                                     const ARRAY_3D _R /* ns,m,m */, 
                                     const ARRAY_1D x_0 /* n */)
{
  int t;
  int i;

  resetUKF(_Q, _Qscale, _R, x_0);

  for (t = 1 ; t <= ns ; t++)
  {
    timeUpdate(t);
    measurementUpdate(t, y[t]);

    for (i = 1 ; i <= n ; i++)
    {
      xi[i]       = x_k[t][i];
      x_est[t][i] = xi[i];
    }

    model_output(yi, xi, t);

    for (i = 1 ; i <= m ; i++)
    {
      y_k[t][i]   = yi[i];
      y_est[t][i] = yi[i];
    }
  }

  LogLikelihood *= -0.5;

  Filtered = true;
  Smoothed = false;

  return (LogLikelihood);
}                                   

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::smooth(ARRAY_2D  x_smooth /* ns, n */, 
                                     ARRAY_2D  y_smooth /* ns, m */, 
                                     const bool bWithLogLikelihood)
{
  int t;
  int cr;
  int cc;

  if (Filtered && !Smoothed)
  {
    zero(y_k_smooth);
    zero(x_k_smooth);
    zero(Ps_k);

    for (cr = 1 ; cr <= m ; cr++)
    {
      y_k_smooth[ns][cr] = y_k[ns][cr];
      y_smooth[ns][cr]   = y_k[ns][cr];
    }

    for (cr = 1 ; cr <= n ; cr++)
    {
      x_k_smooth[ns][cr] = x_k[ns][cr];
      x_smooth[ns][cr]   = x_k[ns][cr];

      for (cc = 1 ; cc <= n ; cc++)
      {
        Ps_k[ns][cr][cc] = P_k[ns][cr][cc];
      }
    }

    SmoothedLogLikelihood = 0.0;

    for (t = ns-1 ; t > 1 ; t--)
    {
      smoothingUpdate(x_smooth[t], y_smooth[t], t, bWithLogLikelihood);
    }

    SmoothedLogLikelihood *= -0.5;

    Smoothed = true;
  }

  return (SmoothedLogLikelihood);
}

