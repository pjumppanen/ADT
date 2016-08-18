/*
 Hand modified version of optim.c source code in R project that makes the
 minimisation routines thread safe for use in ADlib based projects. The
 original code will only work single threaded.
 */
/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1999-2014  The R Core Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  https://www.R-project.org/Licenses/
 */

#include "adtmaths.hpp"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <R_ext/Arith.h>
#include <R_ext/Memory.h>
#include <R_ext/Applic.h>

#ifdef _MSC_VER

#define snprintf  _snprintf

#endif

static double * create_vect(int n)
{
    return (double *)malloc(n * sizeof(double));
}

static double ** create_matrix(int nrh, int nch)
{
    int   i;
    double **m;

    m = (double **) malloc((nrh + 1) * sizeof(double *));
    for (i = 0; i <= nrh; i++)
        m[i] = (double*) malloc((nch + 1) * sizeof(double));
    return m;
}

static void free_matrix(double** ppMatrix, int nrh)
{
  int   i;

  for (i = 0; i <= nrh; i++)
      free((void*)ppMatrix[i]);

  free((void*)ppMatrix);
}

static double ** create_Lmatrix(int n)
{
    int   i;
    double **m;

    m = (double **) malloc(n * sizeof(double *) + 1);
    for (i = 0; i < n; i++)
        m[i] = (double *) malloc((i + 1) * sizeof(double));
    return m;
}

static void free_Lmatrix(double** ppMatrix, int n)
{
  free_matrix(ppMatrix, n - 1);
}


#define stepredn        0.2
#define acctol          0.0001
#define reltest         10.0


/*  BFGS variable-metric method, based on Pascal code
in J.C. Nash, `Compact Numerical Methods for Computers', 2nd edition,
converted by p2c then re-crafted by B.D. Ripley */

void
ts_vmmin(int n0, double *b, double *Fmin, optimfn fminfn, optimgr fmingr,
         int maxit, int trace, int *mask,
         double abstol, double reltol, int nREPORT, void *ex,
         int *fncount, int *grcount, int *fail)
{
    Rboolean accpoint, enough;
    double *g, *t, *X, *c, **B;
    int   count, funcount, gradcount;
    double f, gradproj;
    int   i, j, ilast, iter = 0;
    double s, steplength;
    double D1, D2;
    int   n, *l;

    if (maxit <= 0) {
        *fail = 0;
        *Fmin = fminfn(n0, b, ex);
        *fncount = *grcount = 0;
        return;
    }

    if (nREPORT <= 0)
        ts_error("REPORT must be > 0 (method = \"BFGS\")");
    l = (int *) malloc(n0 * sizeof(int));
    n = 0;
    for (i = 0; i < n0; i++) if (mask[i]) l[n++] = i;
    g = create_vect(n0);
    t = create_vect(n);
    X = create_vect(n);
    c = create_vect(n);
    B = create_Lmatrix(n);
    f = fminfn(n0, b, ex);
    if (!R_FINITE(f))
        ts_error("initial value in 'vmmin' is not finite");
    if (trace) ts_printf("initial  value %f \n", f);
    *Fmin = f;
    funcount = gradcount = 1;
    fmingr(n0, b, g, ex);
    iter++;
    ilast = gradcount;

    do {
        if (ilast == gradcount) {
            for (i = 0; i < n; i++) {
                for (j = 0; j < i; j++) B[i][j] = 0.0;
                B[i][i] = 1.0;
            }
        }
        for (i = 0; i < n; i++) {
            X[i] = b[l[i]];
            c[i] = g[l[i]];
        }
        gradproj = 0.0;
        for (i = 0; i < n; i++) {
            s = 0.0;
            for (j = 0; j <= i; j++) s -= B[i][j] * g[l[j]];
            for (j = i + 1; j < n; j++) s -= B[j][i] * g[l[j]];
            t[i] = s;
            gradproj += s * g[l[i]];
        }

        if (gradproj < 0.0) {        /* search direction is downhill */
            steplength = 1.0;
            accpoint = FALSE;
            do {
                count = 0;
                for (i = 0; i < n; i++) {
                    b[l[i]] = X[i] + steplength * t[i];
                    if (reltest + X[i] == reltest + b[l[i]]) /* no change */
                        count++;
                }
                if (count < n) {
                    f = fminfn(n0, b, ex);
                    funcount++;
                    accpoint = (R_FINITE(f) && (f <= *Fmin + gradproj * steplength * acctol)) ? TRUE : FALSE;
                    if (!accpoint) {
                        steplength *= stepredn;
                    }
                }
            } while (!(count == n || accpoint));
            enough = ((f > abstol) && fabs(f - *Fmin) > reltol * (fabs(*Fmin) + reltol)) ? TRUE : FALSE;
            /* stop if value if small or if relative change is low */
            if (!enough) {
                count = n;
                *Fmin = f;
            }
            if (count < n) {/* making progress */
                *Fmin = f;
                fmingr(n0, b, g, ex);
                gradcount++;
                iter++;
                D1 = 0.0;
                for (i = 0; i < n; i++) {
                    t[i] = steplength * t[i];
                    c[i] = g[l[i]] - c[i];
                    D1 += t[i] * c[i];
                }
                if (D1 > 0) {
                    D2 = 0.0;
                    for (i = 0; i < n; i++) {
                        s = 0.0;
                        for (j = 0; j <= i; j++)
                            s += B[i][j] * c[j];
                        for (j = i + 1; j < n; j++)
                            s += B[j][i] * c[j];
                        X[i] = s;
                        D2 += s * c[i];
                    }
                    D2 = 1.0 + D2 / D1;
                    for (i = 0; i < n; i++) {
                        for (j = 0; j <= i; j++)
                            B[i][j] += (D2 * t[i] * t[j]
                                        - X[i] * t[j] - t[i] * X[j]) / D1;
                    }
                } else {        /* D1 < 0 */
                    ilast = gradcount;
                }
            } else {        /* no progress */
                if (ilast < gradcount) {
                    count = 0;
                    ilast = gradcount;
                }
            }
        } else {                /* uphill search */
            count = 0;
            if (ilast == gradcount) count = n;
            else ilast = gradcount;
            /* Resets unless has just been reset */
        }
        if (trace && (iter % nREPORT == 0))
            ts_printf("iter%4d value %f\n", iter, f);
        if (iter >= maxit) break;
        if (gradcount - ilast > 2 * n)
            ilast = gradcount;        /* periodic restart */
    } while (count != n || ilast != gradcount);
    if (trace) {
        ts_printf("final  value %f \n", *Fmin);
        if (iter < maxit) ts_printf("converged\n");
        else ts_printf("stopped after %i iterations\n", iter);
    }
    *fail = (iter < maxit) ? 0 : 1;
    *fncount = funcount;
    *grcount = gradcount;

    free(l);
    free(g);
    free(t);
    free(X);
    free(c);
    free_Lmatrix(B, n);
}


#define big             1.0e+35   /*a very large number*/


/* Nelder-Mead, based on Pascal code
   in J.C. Nash, `Compact Numerical Methods for Computers', 2nd edition,
   converted by p2c then re-crafted by B.D. Ripley */
void ts_nmmin(int n, double *Bvec, double *X, double *Fmin, optimfn fminfn,
              int *fail, double abstol, double intol, void *ex,
              double alpha, double bet, double gamm, int trace,
              int *fncount, int maxit)
{
    char action[50];
    int C;
    Rboolean calcvert;
    double convtol, f;
    int funcount=0, H, i, j, L=0;
    int n1=0;
    double oldsize;
    double **P;
    double size, step, temp, trystep;
    char tstr[9]; // allow for 10^8 iters ...
    double VH, VL, VR;

    if (maxit <= 0) {
        *Fmin = fminfn(n, Bvec, ex);
        *fncount = 0;
        *fail = 0;
        return;
    }
    if (trace)
        ts_printf("  Nelder-Mead direct search function minimizer\n");
    P = create_matrix(n, n+1);
    *fail = FALSE;
    f = fminfn(n, Bvec, ex);
    if (!R_FINITE(f)) {
        ts_error("function cannot be evaluated at initial parameters");
        *fail = TRUE;
    } else {
        if (trace) ts_printf("function value for initial parameters = %f\n", f);
        funcount = 1;
        convtol = intol * (fabs(f) + intol);
        if (trace) ts_printf("  Scaled convergence tolerance is %g\n", convtol);
        n1 = n + 1;
        C = n + 2;
        P[n1 - 1][0] = f;
        for (i = 0; i < n; i++)
            P[i][0] = Bvec[i];

        L = 1;
        size = 0.0;

        step = 0.0;
        for (i = 0; i < n; i++) {
            if (0.1 * fabs(Bvec[i]) > step)
                step = 0.1 * fabs(Bvec[i]);
        }
        if (step == 0.0) step = 0.1;
        if (trace) ts_printf("Stepsize computed as %f\n", step);
        for (j = 2; j <= n1; j++) {
            strcpy(action, "BUILD          ");
            for (i = 0; i < n; i++)
                P[i][j - 1] = Bvec[i];

            trystep = step;
            while (P[j - 2][j - 1] == Bvec[j - 2]) {
                P[j - 2][j - 1] = Bvec[j - 2] + trystep;
                trystep *= 10;
            }
            size += trystep;
        }
        oldsize = size;
        calcvert = TRUE;
        do {
            if (calcvert) {
                for (j = 0; j < n1; j++) {
                    if (j + 1 != L) {
                        for (i = 0; i < n; i++)
                            Bvec[i] = P[i][j];
                        f = fminfn(n, Bvec, ex);
                        if (!R_FINITE(f)) f = big;
                        funcount++;
                        P[n1 - 1][j] = f;
                    }
                }
                calcvert = FALSE;
            }

            VL = P[n1 - 1][L - 1];
            VH = VL;
            H = L;

            for (j = 1; j <= n1; j++) {
                if (j != L) {
                    f = P[n1 - 1][j - 1];
                    if (f < VL) {
                        L = j;
                        VL = f;
                    }
                    if (f > VH) {
                        H = j;
                        VH = f;
                    }
                }
            }

            if (VH <= VL + convtol || VL <= abstol) break;

            // avoid buffer overflow at 100001 iters. (PR#15240)
            if (trace) {
                snprintf(tstr, 9, "%5d", funcount);
                ts_printf("%s%s %f %f\n", action, tstr, VH, VL);
            }

            for (i = 0; i < n; i++) {
                temp = -P[i][H - 1];
                for (j = 0; j < n1; j++)
                    temp += P[i][j];
                P[i][C - 1] = temp / n;
            }
            for (i = 0; i < n; i++)
                Bvec[i] = (1.0 + alpha) * P[i][C - 1] - alpha * P[i][H - 1];
            f = fminfn(n, Bvec, ex);
            if (!R_FINITE(f)) f = big;
            funcount++;
            strcpy(action, "REFLECTION     ");
            VR = f;
            if (VR < VL) {
                P[n1 - 1][C - 1] = f;
                for (i = 0; i < n; i++) {
                    f = gamm * Bvec[i] + (1 - gamm) * P[i][C - 1];
                    P[i][C - 1] = Bvec[i];
                    Bvec[i] = f;
                }
                f = fminfn(n, Bvec, ex);
                if (!R_FINITE(f)) f = big;
                funcount++;
                if (f < VR) {
                    for (i = 0; i < n; i++)
                        P[i][H - 1] = Bvec[i];
                    P[n1 - 1][H - 1] = f;
                    strcpy(action, "EXTENSION      ");
                } else {
                    for (i = 0; i < n; i++)
                        P[i][H - 1] = P[i][C - 1];
                    P[n1 - 1][H - 1] = VR;
                }
            } else {
                strcpy(action, "HI-REDUCTION   ");
                if (VR < VH) {
                    for (i = 0; i < n; i++)
                        P[i][H - 1] = Bvec[i];
                    P[n1 - 1][H - 1] = VR;
                    strcpy(action, "LO-REDUCTION   ");
                }

                for (i = 0; i < n; i++)
                    Bvec[i] = (1 - bet) * P[i][H - 1] + bet * P[i][C - 1];
                f = fminfn(n, Bvec, ex);
                if (!R_FINITE(f)) f = big;
                funcount++;

                if (f < P[n1 - 1][H - 1]) {
                    for (i = 0; i < n; i++)
                        P[i][H - 1] = Bvec[i];
                    P[n1 - 1][H - 1] = f;
                } else {
                    if (VR >= VH) {
                        strcpy(action, "SHRINK         ");
                        calcvert = TRUE;
                        size = 0.0;
                        for (j = 0; j < n1; j++) {
                            if (j + 1 != L) {
                                for (i = 0; i < n; i++) {
                                    P[i][j] = bet * (P[i][j] - P[i][L - 1])
                                        + P[i][L - 1];
                                    size += fabs(P[i][j] - P[i][L - 1]);
                                }
                            }
                        }
                        if (size < oldsize) {
                            oldsize = size;
                        } else {
                            if (trace)
                                ts_printf("Polytope size measure not decreased in shrink\n");
                            *fail = 10;
                            break;
                        }
                    }
                }
            }

        } while (funcount <= maxit);

    }

    if (trace) {
        ts_printf("Exiting from Nelder Mead minimizer\n");
        ts_printf("    %d function evaluations used\n", funcount);
    }
    *Fmin = P[n1 - 1][L - 1];
    for (i = 0; i < n; i++) X[i] = P[i][L - 1];
    if (funcount > maxit) *fail = 1;
    *fncount = funcount;
    free_matrix(P, n);
}

/* Conjugate gradients, based on Pascal code
   in J.C. Nash, `Compact Numerical Methods for Computers', 2nd edition,
   converted by p2c then re-crafted by B.D. Ripley */
void ts_cgmin(int n, double *Bvec, double *X, double *Fmin,
              optimfn fminfn, optimgr fmingr, int *fail,
              double abstol, double intol, void *ex, int type, int trace,
              int *fncount, int *grcount, int maxit)
{
    Rboolean accpoint;
    double *c, *g, *t;
    int count, cycle, cyclimit;
    double f;
    double G1, G2, G3, gradproj;
    int funcount=0, gradcount=0, i;
    double newstep, oldstep, setstep, steplength=1.0;
    double tol;

    if (maxit <= 0) {
        *Fmin = fminfn(n, Bvec, ex);
        *fncount = *grcount = 0;
        *fail = FALSE;
        return;
    }
    if (trace) {
        ts_printf("  Conjugate gradients function minimizer\n");
        switch (type) {
        case 1:            ts_printf("Method: Fletcher Reeves\n");        break;
        case 2:            ts_printf("Method: Polak Ribiere\n");                break;
        case 3:            ts_printf("Method: Beale Sorenson\n");        break;
        default:
            ts_error("unknown 'type' in \"CG\" method of 'optim'");
        }
    }
    c = create_vect(n); g = create_vect(n); t = create_vect(n);

    setstep = 1.7;
    *fail = 0;
    cyclimit = n;
    tol = intol * n * sqrt(intol);

    if (trace) ts_printf("tolerance used in gradient test=%g\n", tol);
    f = fminfn(n, Bvec, ex);
    if (!R_FINITE(f)) {
        ts_error("Function cannot be evaluated at initial parameters");
    } else {
        *Fmin = f;
        funcount = 1;
        gradcount = 0;
        do {
            for (i = 0; i < n; i++) {
                t[i] = 0.0;
                c[i] = 0.0;
            }
            cycle = 0;
            oldstep = 1.0;
            count = 0;
            do {
                cycle++;
                if (trace) {
                    ts_printf("%d %d %f\n", gradcount, funcount, *Fmin);
                    ts_printf("parameters ");
                    for (i = 1; i <= n; i++) {
                        ts_printf("%10.5f ", Bvec[i - 1]);
                        if (i / 7 * 7 == i && i < n)
                            ts_printf("\n");
                    }
                    ts_printf("\n");
                }
                gradcount++;
                if (gradcount > maxit) {
                    *fncount = funcount;
                    *grcount = gradcount;
                    *fail = 1;
                    return;
                }
                fmingr(n, Bvec, g, ex);
                G1 = 0.0;
                G2 = 0.0;
                for (i = 0; i < n; i++) {
                    X[i] = Bvec[i];
                    switch (type) {

                    case 1: /* Fletcher-Reeves */
                        G1 += g[i] * g[i];
                        G2 += c[i] * c[i];
                        break;

                    case 2: /* Polak-Ribiere */
                        G1 += g[i] * (g[i] - c[i]);
                        G2 += c[i] * c[i];
                        break;

                    case 3: /* Beale-Sorenson */
                        G1 += g[i] * (g[i] - c[i]);
                        G2 += t[i] * (g[i] - c[i]);
                        break;

                    default:
                        ts_error("unknown type in \"CG\" method of 'optim'");
                    }
                    c[i] = g[i];
                }
                if (G1 > tol) {
                    if (G2 > 0.0)
                        G3 = G1 / G2;
                    else
                        G3 = 1.0;
                    gradproj = 0.0;
                    for (i = 0; i < n; i++) {
                        t[i] = t[i] * G3 - g[i];
                        gradproj += t[i] * g[i];
                    }
                    steplength = oldstep;

                    accpoint = FALSE;
                    do {
                        count = 0;
                        for (i = 0; i < n; i++) {
                            Bvec[i] = X[i] + steplength * t[i];
                            if (reltest + X[i] == reltest + Bvec[i])
                                count++;
                        }
                        if (count < n) { /* point is different */
                            f = fminfn(n, Bvec, ex);
                            funcount++;
                            accpoint = (R_FINITE(f) && (f <= *Fmin + gradproj * steplength * acctol)) ? TRUE : FALSE;

                            if (!accpoint) {
                                steplength *= stepredn;
                                if (trace) ts_printf("*");
                            } else *Fmin = f; /* we improved, so update value */
                        }
                    } while (!(count == n || accpoint));
                    if (count < n) {
                        newstep = 2 * (f - *Fmin - gradproj * steplength);
                        if (newstep > 0) {
                            newstep = -(gradproj * steplength * steplength / newstep);
                            for (i = 0; i < n; i++)
                                Bvec[i] = X[i] + newstep * t[i];
                            *Fmin = f;
                            f = fminfn(n, Bvec, ex);
                            funcount++;
                            if (f < *Fmin) {
                                *Fmin = f;
                                if (trace) ts_printf(" i< ");
                            } else { /* reset Bvec to match lowest point */
                                if (trace) ts_printf(" i> ");
                                for (i = 0; i < n; i++)
                                    Bvec[i] = X[i] + steplength * t[i];
                            }
                        }
                    }
                }
                oldstep = setstep * steplength;
                if (oldstep > 1.0)
                    oldstep = 1.0;
            } while ((count != n) && (G1 > tol) && (cycle != cyclimit));

        } while ((cycle != 1) ||
                 ((count != n) && (G1 > tol) && *Fmin > abstol));

    }
    if (trace) {
        ts_printf("Exiting from conjugate gradients minimizer\n");
        ts_printf("    %d function evaluations used\n", funcount);
        ts_printf("    %d gradient evaluations used\n", gradcount);
    }
    *fncount = funcount;
    *grcount = gradcount;

    free(c);
    free(g);
    free(t);
}

/* include setulb() */
#include "ts_lbfgsb.cpp"

void ts_lbfgsb(int n, int m, double *x, double *l, double *u, int *nbd,
               double *Fmin, optimfn fminfn, optimgr fmingr, int *fail,
               void *ex, double factr, double pgtol,
               int *fncount, int *grcount, int maxit, char *msg,
               int trace, int nREPORT)
{
    char task[60];
    double f, *g,  *wa;
    int tr = -1, iter = 0, *iwa, isave[21];
    struct ts_setulb_state setulb_state = {0};
    struct ts_mainlb_state mainlb_state = {0};
    struct ts_dcsrch_state dcsrch_state = {0};
    isave[12] = 0; // -Wall

    if(n == 0) { /* not handled in setulb */
        *fncount = 1;
        *grcount = 0;
        *Fmin = fminfn(n, u, ex);
        strcpy(msg, "NOTHING TO DO");
        *fail = 0;
        return;
    }
    if (nREPORT <= 0)
        ts_error("REPORT must be > 0 (method = \"L-BFGS-B\")");
    switch(trace) {
    case 2: tr = 0; break;
    case 3: tr = nREPORT; break;
    case 4: tr = 99; break;
    case 5: tr = 100; break;
    case 6: tr = 101; break;
    default: tr = -1; break;
    }

    *fail = 0;
    g = create_vect(n);
    /* this needs to be zeroed for snd in mainlb to be zeroed */
    wa = (double *) malloc((2*m*n+4*n+11*m*m+8*m) * sizeof(double));
    iwa = (int *) malloc(3 * n * sizeof(int));
    strcpy(task, "START");
    while(1) {
        ts_setulb(n, m, x, l, u, nbd, &f, g, factr, &pgtol, wa, iwa, task,
                  tr, isave, &setulb_state, &mainlb_state, &dcsrch_state);
/*        ts_printf("in lbfgsb - %s\n", task);*/
        if (strncmp(task, "FG", 2) == 0) {
            f = fminfn(n, x, ex);
            if (!R_FINITE(f))
                ts_error("L-BFGS-B needs finite values of 'fn'");
            fmingr(n, x, g, ex);
        } else if (strncmp(task, "NEW_X", 5) == 0) {
            iter++;
            if(trace == 1 && (iter % nREPORT == 0)) {
                ts_printf("iter %4d value %f\n", iter, f);
            }
            if (iter > maxit) {
                *fail = 1;
                break;
            }
        } else if (strncmp(task, "WARN", 4) == 0) {
            *fail = 51;
            break;
        } else if (strncmp(task, "CONV", 4) == 0) {
            break;
        } else if (strncmp(task, "ERROR", 5) == 0) {
            *fail = 52;
            break;
        } else { /* some other condition that is not supposed to happen */
            *fail = 52;
            break;
        }
    }
    *Fmin = f;
    *fncount = *grcount = isave[12];
    if (trace) {
        ts_printf("final  value %f \n", *Fmin);
        if (iter < maxit && *fail == 0) ts_printf("converged\n");
        else ts_printf("stopped after %i iterations\n", iter);
    }
    strcpy(msg, task);
    free(wa);
    free(iwa);
    free(g);
}
