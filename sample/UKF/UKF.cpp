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


#include "UKF.hpp"


void UnscentedKalmanFilter::choleskyDecomposition(const ARRAY_2D pA/* 0:nSize-1, 0:nSize-1 */, ARRAY_2D pL/* 0:nSize-1, 0:nSize-1 */, const int nSize)
{
  //--------------------------------------------------------------------------
  // A is symetric positive definite matrix in lower triangular form
  // L is the cholesky decomposition in upper triangular form
  //--------------------------------------------------------------------------
  double sum;
  int    ci, cj, ck;

  for (ci = 0 ; ci < nSize ; ci++)
  {
    sum = pA[ci][ci];

    for (cj = 0 ; cj < ci ; cj++)
    {
      sum = sum - pL[cj][ci] * pL[cj][ci];
    }

#ifndef AD
    assert(sum > 0.0);
#endif    
    pL[ci][ci] = sqrt(sum);

    for (cj = ci + 1 ; cj < nSize ; cj++)
    {
      sum = pA[ci][cj];
      
      for (ck = 0 ; ck < ci ; ck++)
      {
        sum = sum - pL[ck][ci] * pL[ck][cj];
      }

      pL[ci][cj] = sum / pL[ci][ci];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::matrixInverseFromChol(const ARRAY_2D pL/* 0:nSize-1, 0:nSize-1 */, ARRAY_2D pInv/* 0:nSize-1, 0:nSize-1 */, const int nSize)
{
  //--------------------------------------------------------------------------
  // pL is the cholesky decomposition of A in lower triangular form
  // pInv is the resulting upper triangular inverse matrix
  //--------------------------------------------------------------------------
  int     cc;
  int     cr;
  int     cq;
  double  b;
  double  dEntry;

  for (cc = nSize - 1 ; cc >= 0 ; cc--)
  {
    for (cr = cc ; cr >= 0 ; cr--)
    {
      b = 0.0;

      if (cr == cc)
      {
        b = (1.0 / pL[cr][cr]);
      }

      if (cr < nSize - 1)
      {
        for (cq = 1 + cr ; cq < nSize ; cq++)
        {
          if (cc <= cq)
          {
            b = b - pInv[cq][cc] * pL[cr][cq];
          }
          else
          {
            b = b - pInv[cc][cq] * pL[cr][cq];
          }
        }
      }

      dEntry    = b * (1.0 / pL[cr][cr]);

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

  // all vectors used in the UKF process
  zero(x_apriori);
  zero(x_aposteriori);
  zero(x_P);
  zero(y_P);
  zero(in_);
  zero(y);

  // covarince matrices used in the process
  zero(P_apriori);
  zero(P_aprioriP);
  zero(P_aposteriori);

  // square root product of a given covariances s
  zero(sP_apriori);
  zero(sP_aposteriori);

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
}

// ----------------------------------------------------------------------------
// Q - filter process noise covraiance
// R - measurement noise covariance,
// P - init covariance noise
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::resetUKF(double _Q, double _R, const ARRAY_1D x_0 /* 0:n-1 */)
{
  int cn;

  // init of all vectors and matrices where the first dim := n
  zero(y);
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

  zero(P_apriori);
  zero(P_aprioriP);
  zero(P_aposteriori);

  for (cn = 0 ; cn < n ; cn++)
  {
    x_apriori[cn]         = x_0[cn];
    x_aposteriori[cn]     = x_0[cn];
    P_apriori[cn][cn]     = _Q;
    P_aposteriori[cn][cn] = _Q;
  }

  zero(x_P);

  setCovariances(_Q, _R);
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::setCovariances(double _Q, double _R)
{
  int cn;

  zero(Q);
  zero(R);

  for (cn = 0 ; cn < n ; cn++)
  {
    Q[cn][cn] = _Q;
  }

  for (cn = 0 ; cn < m ; cn++)
  {
    R[cn][cn] = _R;
  }
}

// ----------------------------------------------------------------------------
// vect_X - state vector
// sigma points are drawn from P
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::sigma_points(const ARRAY_1D vect_X /* 0:n-1 */, const ARRAY_2D matrix_S /* 0:n-1,0:n-1 */)
{
  int ck;
  int cn;

  for (cn = 0 ; cn < n ; cn++)
  {
    x_sigma[cn][0] = vect_X[cn];
  }

  for (ck = 1 ; ck < n + 1 ; ck++)
  {
    for (cn = 0 ; cn < n ; cn++)
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
void UnscentedKalmanFilter::y_UKF_calc()
{
  int ck;
  int cn;

  for (ck = 0 ; ck < 2 * n + 1; ck++)
  {
    for (cn = 0 ; cn < n ; cn++)
    {
      xi[cn] = x_sigma_f[cn][ck];
    }

    model_output(yi, xi);

    for (cn = 0 ; cn < m ; cn++)
    {
      y_sigma[cn][ck] = yi[cn];
    }
  }

  // y_UKF
  for (cn = 0 ; cn < m ; cn++)
  {
    y[cn] = W0m * y_sigma[cn][0];
  }

  for (ck = 1 ; ck < 2 * n + 1; ck++)
  {
    for (cn = 0 ; cn < m ; cn++)
    {
      y[cn] += W * y_sigma[cn][ck];
    }
  }
}

// ----------------------------------------------------------------------------
// w - input vector data
// ----------------------------------------------------------------------------
void UnscentedKalmanFilter::state(ARRAY_1D w/* 0:n-1 */)
{
  int j;
  int cn;

  for (j = 0 ; j < 2 * n + 1 ; j++)
  {
    for (cn = 0 ; cn < n ; cn++)
    {
      xp[cn] = x_sigma[cn][j];
    }

    model_state(xi, w, xp);

    for (cn = 0 ; cn < n ; cn++)
    {
      x_sigma_f[cn][j] = xi[cn];
    }
  }
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::timeUpdate(ARRAY_1D w/* 0:n-1 */)
{
  int     cn;
  int     cm;
  int     ck;
  double  dW;

  zero(sP_aposteriori);

  choleskyDecomposition(P_aposteriori, sP_aposteriori, n);
  sigma_points(x_aposteriori, sP_aposteriori);
  state(w);

  // apriori state:
  for (cn = 0 ; cn < n ; cn++)
  {
    x_apriori[cn] = W0m * x_sigma_f[cn][0];

    for (ck = 1 ; ck < 2 * n + 1 ; ck++)
    {
      x_apriori[cn] += W * x_sigma_f[cn][ck]; 
    }
  }

  // apriori covariance matrix:
  zero(P_apriori);

  for (ck = 0 ; ck < 2 * n + 1 ; ck++)
  {
    if (ck == 0)
    {
      dW = W0c;
    }
    else
    {
      dW = W;
    }

    for (cn = 0 ; cn < n ; cn++)
    {
      x_P[cn] = x_sigma_f[cn][ck] - x_apriori[cn];
    }

    for (cn = 0 ; cn < n ; cn++)
    {
      for (cm = 0 ; cm < n ; cm++)
      {
        P_aprioriP[cn][cm] = dW * x_P[cn] * x_P[cm];
        P_apriori[cn][cm] += P_aprioriP[cn][cm];
      }
    }
  }

  for (cn = 0 ; cn < n ; cn++)
  {
    for (cm = 0 ; cm < n ; cm++)
    {
      P_apriori[cn][cm] += Q[cn][cm];
    }
  }

  y_UKF_calc();
}

// ----------------------------------------------------------------------------

void UnscentedKalmanFilter::measurementUpdate(const ARRAY_1D z/* 0:m-1 */)
{
  int     ck;
  int     cn;
  int     cm;
  int     cr;
  double  dW;
  double  dSum;

  zero(P_y);

  for (ck = 0 ; ck < 2 * n + 1 ; ck++)
  {
    if (ck == 0)
    {
      dW = W0c;
    }
    else
    {
      dW = W;
    }

    // cov matrix oytpu/output
    for (cn = 0 ; cn < m ; cn++)
    {
      y_P[cn] = y_sigma[cn][ck] - y[cn];
    }

    for (cn = 0 ; cn < m ; cn++)
    {
      for (cm = 0 ; cm < m ; cm++)
      {
        P_y_P[cn][cm] = dW * y_P[cn] * y_P[cm];
        P_y[cn][cm]  += P_y_P[cn][cm];
      }
    }
  }

  for (cn = 0 ; cn < m ; cn++)
  {
    for (cm = 0 ; cm < m ; cm++)
    {
      P_y[cn][cm]  += R[cn][cm];
    }
  }

  zero(P_xy);

  for (ck = 0 ; ck < 2 * n + 1 ; ck++)
  {
    if (ck == 0)
    {
      dW = W0c;
    }
    else
    {
      dW = W;
    }

    // cross cov matrix input/output:
    for (cn = 0 ; cn < n ; cn++)
    {
      x_P[cn] = x_sigma_f[cn][ck] - x_apriori[cn];
    }

    for (cn = 0 ; cn < m ; cn++)
    {
      y_P[cn] = y_sigma[cn][ck] - y[cn];
    }

    for (cn = 0 ; cn < n ; cn++)
    {
      for (cm = 0 ; cm < m ; cm++)
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

  for (cn = 0 ; cn < n ; cn++)
  {
    for (cm = 0 ; cm < m ; cm++)
    {
      dSum = 0.0;

      for (cr = 0 ; cr < m ; cr++)
      {
        dSum += P_xy[cn][cr] * inv_P_y[cr][cm];
      }

      K[cn][cm] = dSum;
    }
  }

  // aposteriori state:
  for (cn = 0 ; cn < m ; cn++)
  {
    y_P[cn] = z[cn] - y[cn];
  }

  for (cn = 0 ; cn < n ; cn++)
  {
    dSum = 0.0;

    for (cr = 0 ; cr < m ; cr++)
    {
      dSum += K[cn][cr] * y_P[cr];
    }

    x_aposteriori[cn] = x_apriori[cn] + dSum;
  }

  // cov aposteriori:
  for (cn = 0 ; cn < n ; cn++)
  {
    for (cm = 0 ; cm < m ; cm++)
    {
      dSum = 0.0;

      for (cr = 0 ; cr < m ; cr++)
      {
        dSum += K[cn][cr] * P_y[cr][cm];
      }

      K_P_y[cn][cm] = dSum;
    }
  }

  for (cn = 0 ; cn < n ; cn++)
  {
    for (cm = 0 ; cm < n ; cm++)
    {
      dSum = 0.0;

      for (cr = 0 ; cr < m ; cr++)
      {
        dSum += K_P_y[cn][cr] * K[cm][cr];
      }

      P_aposteriori[cn][cm] = P_apriori[cn][cm] - dSum;
    }
  }
}
