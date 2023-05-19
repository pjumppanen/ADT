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
void UnscentedKalmanFilter::choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, ARRAY_2D pU/* nSize, nSize */, const int nSize)
{
  //--------------------------------------------------------------------------
  // pA is symetric positive definite matrix
  // pU is the cholesky decomposition in upper triangular form
  //--------------------------------------------------------------------------
  double sum;
  int    ci, cj, ck;

  for (ci = 1 ; ci <= nSize ; ci++)
  {
    sum = pA[ci][ci];

    for (cj = 1 ; cj <= ci - 1 ; cj++)
    {
      sum = sum - pU[cj][ci] * pU[cj][ci];
    }

#ifndef AD
    assert(sum > 0.0);
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
   model_state()
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
  zero(P_aprioriP);

  // clear sigma points
  zero(y_sigma);
  zero(x_sigma);

  // sigma points after passing through the function f/h
  zero(x_sigma_f);

  // cross covariances
  zero(P_xy);
  zero(P_xyP);

  zero(P_y);
  zero(oP_y);
  zero(P_y_P);
  zero(K);
  zero(K_0);
  zero(K_UKF_T);

  zero(Q);
  zero(R);

  Rs = 0.0;
  Qs = 0.0;

  Filtered = false;
  Smoothed = false;
}

// ----------------------------------------------------------------------------
// Q - filter process noise covraiance
// R - measurement noise covariance,
// P - init covariance noise
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::resetUKF(const double _Q, const double _R, const ARRAY_1D x_0 /* n */)
{
  int cn;

  zero(y_k);
  zero(x_k);
  zero(x_k_bar);
  zero(y_k_smooth);
  zero(x_k_smooth);

  zero(ym);
  zero(y_P);
  zero(P_y);
  zero(P_y_P);
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
  zero(P_aprioriP);

  for (cn = 1 ; cn <= n ; cn++)
  {
    x_k[0][cn]      = x_0[cn];
    P_k[0][cn][cn]  = _Q;
  }

  zero(x_P);

  setCovariances(_Q, _R);

  LogLikelihood = 0.0;
  
  Filtered = false;
  Smoothed = false;
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::setCovariances(double _Q, double _R)
{
  int cn;

  zero(Q);
  zero(R);

  for (cn = 1 ; cn <= n ; cn++)
  {
    Q[cn][cn] = _Q;
  }

  for (cn = 1 ; cn <= m ; cn++)
  {
    R[cn][cn] = _R;
  }
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

  for (j = 1 ; j <= 2 * n + 1 ; j++)
  {
    for (cn = 1 ; cn <= n ; cn++)
    {
      xp[cn] = x_sigma[cn][j];
    }

    model_state(xi, xp, t);

    for (cn = 1 ; cn <= n ; cn++)
    {
      x_sigma_f[cn][j] = xi[cn];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::timeUpdate(const int t)
{
  int     cn;
  int     cm;
  int     ck;
  double  dW;

  choleskyDecomposition(P_k[t-1], chol_P_k[t], n);
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
        P_aprioriP[cn][cm]  = dW * x_P[cn] * x_P[cm];
        P_k_bar[t][cn][cm] += P_aprioriP[cn][cm];
      }
    }
  }

  for (cn = 1 ; cn <= n ; cn++)
  {
    for (cm = 1 ; cm <= n ; cm++)
    {
      P_k_bar[t][cn][cm] += Q[cn][cm];
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

  zero(P_y);

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
          P_y_P[cn][cm] = dW * y_P[cn] * y_P[cm];
          P_y[cn][cm]  += P_y_P[cn][cm];
        }
      }
    }

    for (cn = 1 ; cn <= m ; cn++)
    {
      for (cm = 1 ; cm <= m ; cm++)
      {
        P_y[cn][cm]  += R[cn][cm];
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

    choleskyDecomposition(P_y, chol_P_y, m);
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
        dSum += inv_P_y[cn][cr] * ym[cr];
      }

      yt_invPy_y += dSum * ym[cn];
    }

    LogLikelihood += (logDeterminantFromChol(chol_P_y, m) + yt_invPy_y);

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

  if (naData[t])
  {
    // with NA data next smoothed state equals previous state
    for (cc = 1 ; cc <= n ; cc++)
    {
      x_k_smooth[t-1][cc] = x_k_smooth[t][cc];
      y_k_smooth[t-1][cc] = y_k_smooth[t][cc];

      for (cr = 1 ; cr <= n ; cr++)
      {
        Ps_k[t-1][cr][cc] = Ps_k[t][cr][cc];
      }
    }
  }
  else
  {
    // Implement UKF Kalman smoothing based on the Jacobian Equivalent 
    // Rauch-Tung-Striebel smoother (abbreviated as JE-RTS method).
    zero(Ye_k);

    // using A_k as temp to find Ye_k
    for (cr = 1 ; cr <= n ; cr++)
    {
      for (cc = 1 ; cc <= n ; cc++)
      {
        A_k[cr][cc] = P_k[t][cr][cc] - Q[cr][cc];
      }
    }

    choleskyDecomposition(A_k, Ye_k, n);

    zero(inv_root_P_km1);

    // using A_k as temp to find inverse of root of P_k at t-1
    choleskyDecomposition(chol_P_k[t], A_k, n);
    matrixInverseFromChol(A_k, inv_root_P_km1, n);

    zero(inv_P_k);

    // using A_k as temp to find inverse of P_k_bar at t
    choleskyDecomposition(P_k_bar[t], A_k, n);
    matrixInverseFromChol(A_k, inv_P_k, n);

    // find smoothing gain A_k
    // Ak = inv_root_P_km1 * inv_P_k
    for (cc = 1 ; cc <= n ; cc++)
    {
      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = 0.0;

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += inv_root_P_km1[cr][cn] * inv_P_k[cn][cc];
        }

        A_k[cr][cc] = dSum;
      }
    }

    // Ak = Yk * Ak
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
          dSum += Ye_k[cr][cn] * x_Temp[cn];
        }

        A_k[cr][cc] = dSum;
      }
    }

    // Ak = Pk[t-1] * Ak
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
          dSum += P_k[t-1][cr][cn] * x_Temp[cn];
        }

        A_k[cr][cc] = dSum;
      }
    }

    // find smoothed state
    for (cr = 1 ; cr <= n ; cr++)
    {
      dSum = x_k[t-1][cr];

      for (cc = 1 ; cc <= n ; cc++)
      {
        dSum += A_k[cr][cc] * (x_k_smooth[t][cc] - x_k_bar[t][cc]);
      }

      x_smooth[cr]        = x_k_smooth[t][cr];
      x_k_smooth[t-1][cr] = dSum;
      xi[cr]              = dSum;
    }

    model_output(yi, xi, t-1);

    // find smoothed covariance
    // Ps_k[t-1] = (P_k_bar[t] - Ps_k[t]) * t(A_k)
    for (cc = 1 ; cc <= n ; cc++)
    {
      y_smooth[cc]        = y_k_smooth[t][cc];
      y_k_smooth[t-1][cc] = yi[cc];

      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = 0.0;

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += (P_k_bar[t][cr][cn] - Ps_k[t][cr][cn]) * A_k[cc][cn];
        }

        Ps_k[t-1][cr][cc] = dSum;
      }
    }

    // Ps_k[t-1] = P_k[t] - A_k * Ps_k[t-1]
    for (cc = 1 ; cc <= n ; cc++)
    {
      for (cr = 1 ; cr <= n ; cr++)
      {
        x_Temp[cr] = Ps_k[t-1][cr][cc];
      }

      for (cr = 1 ; cr <= n ; cr++)
      {
        dSum = P_k[t][cr][cc];

        for (cn = 1 ; cn <= n ; cn++)
        {
          dSum += -A_k[cr][cn] * x_Temp[cn];
        }

        Ps_k[t-1][cr][cc] = dSum;
      }
    }

    if (bWithLogLikelihood)
    {
      // Find new sigma points
      zero(chol_Ps_k);

      choleskyDecomposition(Ps_k[t-1], chol_Ps_k, n);
      sigma_points(x_k_smooth[t-1], chol_Ps_k);
      y_UKF_calc(t-1);

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
            P_y_P[cn][cm] = dW * y_P[cn] * y_P[cm];
            P_y[cn][cm]  += P_y_P[cn][cm];
          }
        }
      }

      for (cn = 1 ; cn <= m ; cn++)
      {
        for (cm = 1 ; cm <= m ; cm++)
        {
          P_y[cn][cm]  += R[cn][cm];
        }
      }

      // Find loglikelihood
      zero(chol_P_y);

      choleskyDecomposition(P_y, chol_P_y, m);
      matrixInverseFromChol(chol_P_y, inv_P_y, m);

      yt_invPy_y = 0.0;

      for (cn = 1 ; cn <= m ; cn++)
      {
        dSum = 0.0;

        for (cr = 1 ; cr <= m ; cr++)
        {
          dSum += inv_P_y[cn][cr] * ym[cr];
        }

        yt_invPy_y += dSum * ym[cn];
      }

      SmoothedLogLikelihood += (logDeterminantFromChol(chol_P_y, m) + yt_invPy_y);
    }
  }
}

// ----------------------------------------------------------------------------

double UnscentedKalmanFilter::filter(ARRAY_2D  x_est /* ns, n */, 
                                     ARRAY_2D  y_est /* ns, m */, 
                                     const double _Q, 
                                     const double _R, 
                                     const ARRAY_1D x_0 /* n */)
{
  int t;
  int i;

  resetUKF(_Q, _R, x_0);

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

    for (cr = 1 ; cr <= n ; cr++)
    {
      x_k_smooth[ns][cr] = x_k[ns][cr];
      y_k_smooth[ns][cr] = y_k[ns][cr];

      for (cc = 1 ; cc <= n ; cc++)
      {
        Ps_k[ns][cr][cc] = P_k[ns][cr][cc];
      }
    }

    SmoothedLogLikelihood = 0.0;

    for (t = ns ; t > 1 ; t--)
    {
      smoothingUpdate(x_smooth[t], y_smooth[t], t, bWithLogLikelihood);
    }

    SmoothedLogLikelihood *= -0.5;

    Smoothed = true;
  }

  return (SmoothedLogLikelihood);
}

