protected:
  /* AUTODEC */
  int           NR; // total number of random effects
  int           NP; // total number of parameters
  ARRAY_1D      plower /* NR */;
  ARRAY_1D      pupper /* NR */;
  ARRAY_1I      pnbd /* NR */;
  ARRAY_1D      ReRun /* NR */;
  ARRAY_1D      GradRun /* NR */;
  ARRAY_1D      Par /* NP */;
  ARRAY_1D      CheckPar /* NP */;
  ARRAY_1D      Dir /* NR */;
  ARRAY_1D      Dir2 /* NP */;
  ARRAY_1D      TempRow/* NR */;
  ARRAY_1D      TempRow2/* NP */;
  ARRAY_2D      Hessian/* NR,NR */;
  ARRAY_2D      Cholesky/* NR,NR */;
  ARRAY_2D      ReParXCovar/* NR,NP */;
  ARRAY_1D      var /* NR */;
  ARRAY_1D      zm /* 0 : NR * (NR + 13) / 2 */;
  bool          Dirty;

protected:
  double  dlognorm(const double x, 
                   const double mean,
                   const double sigma);

  void    choleskyDecomposition(const ARRAY_2D pA/* nSize, nSize */, 
                                ARRAY_2D pL/* nSize, nSize */, 
                                const int nSize);

  double  logDeterminantFromChol(const ARRAY_2D pL/* nSize, nSize */, 
                                 const int nSize);

  void    matrixInverseFromChol(const ARRAY_2D pL/* nSize, nSize */, 
                                ARRAY_2D pInv/* nSize, nSize */, 
                                const int nSize);

#ifndef AD
  struct SolveContext
  {
    int nFnCalls;
    int nGradCalls;
    $(classname)* pThis;
  };

  static void   inner_simfn(int* indic, int* n, double* re, double* f, double* gr, int* izs, float* rzs, double* dzs);
  static double inner_optimfn(int n, double* re, void* context);
  static void   inner_optimgr(int n, double* re, double* gr, void* context);

  virtual double  innerObjective(int n, ARRAY_1D re) = 0;
  virtual void    innerGradient(int n, ARRAY_1D re, ARRAY_1D gr) = 0;
#endif

  // < BLACKBOX ReadNotWritten:(0,1)
  // ReadThenWritten:(1,0)
  // deps:(1,1,id); >
  void          solveInner(ARRAY_1D reHat/* NR */, const ARRAY_1D par/* NP */);

  // Log determinant of Hessian with respect to random effects
  double        logDetHessianRE(const ARRAY_1D re/* NR */, const ARRAY_1D par/* NP */, const ARRAY_2D pHessian/* NR,NR */, ARRAY_2D pCholesky/* NR,NR */);
