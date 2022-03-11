MODULE COMMON

  INTEGER(4) , PARAMETER :: dim_stack
  REAL(8) :: CholeskyMatrixRE(NR,NR)
  REAL(8) :: HessianMatrixRE(NR,NR)
  REAL(8) :: reb1_re(NR)
  REAL(8) :: red2_re(NR)
  INTEGER(4) :: N
  INTEGER(4) :: NP
  INTEGER(4) :: NR
  REAL(8) :: par_logK
  REAL(8) :: par_logQ
  REAL(8) :: par_logR
  REAL(8) :: par_logr0
  REAL(8) :: par_logtheta
  REAL(8) :: par_u(N)
  REAL(8) :: y(N)
  REAL(8) :: par_ub1_re(n)
  REAL(8) :: yb1_re(n)
  REAL(8) :: par_ud2_re(n)
  REAL(8) :: yd2_re(n)
  REAL(8) :: par_ub1_red2_re(n)
  REAL(8) :: yb1_red2_re(n)
  REAL(8) :: par_logkd3_par
  REAL(8) :: par_logqd3_par
  REAL(8) :: par_logrd3_par
  REAL(8) :: par_logr0d3_par
  REAL(8) :: par_logthetad3_par
  REAL(8) :: par_ub1_red3_par(n)
  REAL(8) :: yb1_red3_par(n)
  REAL(8) :: par_ud3_par(n)
  REAL(8) :: par_logkb4_par
  REAL(8) :: par_logqb4_par
  REAL(8) :: par_logrb4_par
  REAL(8) :: par_logr0b4_par
  REAL(8) :: par_logthetab4_par
  REAL(8) :: par_ub4_par(n)
  REAL(8) :: choleskymatrixred1_re(nr,nr)
  REAL(8) :: hessianmatrixred1_re(nr,nr)
  REAL(8) :: par_ud1_re(n)
  REAL(8) :: yd1_re(n)
  REAL(8) :: par_ub1_red2_red1_re(n)
  REAL(8) :: yb1_red2_red1_re(n)
  REAL(8) :: par_ud2_red1_re(n)
  REAL(8) :: par_ub1_red1_re(n)
  
ENDMODULE 

! ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__gradientRE(re,par,pGrad)

  REAL(8) , INTENT (IN):: re(NR)
  REAL(8) , INTENT (IN):: par(NP)
  REAL(8) , INTENT (INOUT):: pGrad(NR)
  USE COMMON
  REAL(8) :: loglikelihoodb1_re
  loglikelihoodb1_re = 1.0
  CALL R_REDev__LOGLIKELIHOOD_BRE(re,pGrad,par,loglikelihoodb1_re)
  
ENDSUBROUTINE 

!  ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__hessianRE(re,par,pHessian)

  REAL(8) , INTENT (IN):: re(NR)
  REAL(8) , INTENT (IN):: par(NP)
  REAL(8) , INTENT (INOUT):: pHessian(NR,NR)
  USE COMMON
  INTEGER(4) :: cn
  REAL(8) :: loglikelihoodb1_re
  loglikelihoodb1_re = 1.0
  cn = 1
  
  DO WHILE (cn.LE.NR)
    red2_re(cn) = 0.0
    cn = cn + 1
  ENDDO 
  
  cn = 1
  
  DO WHILE (cn.LE.NR)
    red2_re(cn) = 1.0
    !  Hessian matrix is symmetric and we construct the matrix row by row by
    !  taking the tangent derivative of the adjoint derivative in each basis
    !  direction. The hessian result goes into an ARRAY_2D but we pass the
    !  n'th column to be filled by indexing the array.
    CALL R_REDev__LOGLIKELIHOOD_BRE_DRE(re,red2_re,reb1_re,pHessian(cn)&
    &,par,loglikelihoodb1_re)
    red2_re(cn) = 0.0
    cn = cn + 1
  ENDDO 
  
  
ENDSUBROUTINE 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__laplace(re,par)

  REAL(8) , INTENT (IN):: re(NR)
  REAL(8) , INTENT (IN):: par(NP)
  USE COMMON
  REAL(8) :: h
  h = ((-NR * LOG(2 * M_PI) + R_REDev__logDetHessianRE(re,par)) * 0.5) &
  &+ R_REDev__logLikelihood(re,par)
  R_REDev__laplace = (h)
  RETURN 
  
ENDFUNCTION 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__logDetHessianRE(re,par)

  REAL(8) , INTENT (IN):: re(NR)
  REAL(8) , INTENT (IN):: par(NP)
  USE COMMON
  REAL(8) :: logdet
  CALL R_REDev__hessianRE(re,par,HessianMatrixRE)
  CALL R_REDev__choleskyDecomposition(HessianMatrixRE,CholeskyMatrixRE,&
  &NR)
  logdet = R_REDev__logDeterminantFromChol(CholeskyMatrixRE,NR)
  R_REDev__logDetHessianRE = (logdet)
  RETURN 
  
ENDFUNCTION 

! ----------------------------------------------------------------------------
INTEGER(4) FUNCTION one_if(a)

  LOGICAL :: a
  
  IF (A) THEN
  
    one_if = 1
    
  ELSE 
  
    one_if = 0
    
  ENDIF 
  
  
ENDFUNCTION 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__dlognorm(x,mean,sigma)

  REAL(8) , INTENT (IN):: x
  REAL(8) , INTENT (IN):: mean
  REAL(8) , INTENT (IN):: sigma
  USE COMMON
  REAL(8) :: dValue
  dValue = -LOG(sigma) - 0.5 * LOG(2 * M_PI) - 0.5 * (((x - mean) / sig&
  &ma)**(2.0))
  R_REDev__dlognorm = (dValue)
  RETURN 
  
ENDFUNCTION 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__logDeterminantFromChol(pL,nSize)

  REAL(8) , INTENT (IN):: pL(nSize,nSize)
  INTEGER(4) , INTENT (IN):: nSize
  USE COMMON
  ! --------------------------------------------------------------------------
  !  pL is the cholesky decomposition of A in lower triangular form
  ! --------------------------------------------------------------------------
  REAL(8) :: dLogDet
  INTEGER(4) :: ci
  dLogDet = 0.0
  ci = 1
  
  DO WHILE (ci.LE.nSize)
    dLogDet = dLogDet + (LOG(pL(ci,ci)))
    ci = ci + 1
  ENDDO 
  
  dLogDet = dLogDet * (2.0)
  R_REDev__logDeterminantFromChol = (dLogDet)
  RETURN 
  
ENDFUNCTION 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__logLikelihood(re,par)

  REAL(8) , INTENT (IN):: re(NR)
  REAL(8) , INTENT (IN):: par(NP)
  USE COMMON
  !  Decode parameters     
  REAL(8) :: dLikelihood
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  !  Copy over random effects
  cm = 1
  cn = 0
  
  DO WHILE (cn.LT.NR)
    par_u(cm) = re(cm)
    cm = cm + 1
    cn = cn + 1
  ENDDO 
  
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  cm = cm + 1
  par_logK = par(cm)
  cm = cm + 1
  par_logQ = par(cm)
  cm = cm + 1
  par_logR = par(cm)
  cm = cm + 1
  !  Call likelihood function
  dLikelihood = R_REDev__thetalogLikelihood(par_u,par_logr0,par_logthet&
  &a,par_logK,par_logQ,par_logR)
  R_REDev__logLikelihood = (dLikelihood)
  RETURN 
  
ENDFUNCTION 

!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDev__thetalogLikelihood(u,logr0,logtheta,logK,logQ&
&,logR)

  REAL(8) , INTENT (IN):: u(N)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logK
  REAL(8) , INTENT (IN):: logQ
  REAL(8) , INTENT (IN):: logR
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: r0
  REAL(8) :: theta
  REAL(8) :: K
  REAL(8) :: Q
  REAL(8) :: R
  REAL(8) :: ll
  INTEGER(4) :: cn
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  K = EXP(logK)
  Q = EXP(logQ)
  R = EXP(logR)
  ll = 0.0
  cn = 2
  
  DO WHILE (cn.LE.N)
    mean = u(cn - 1) + r0 * (1.0 - ((EXP(u(cn - 1)) / K)**(theta)))
    ll = ll - (R_REDev__dlognorm(u(cn),mean,SQRT(Q)))
    cn = cn + 1
  ENDDO 
  
  cn = 1
  
  DO WHILE (cn.LE.N)
    ll = ll - (R_REDev__dlognorm(y(cn),u(cn),SQRT(R)))
    cn = cn + 1
  ENDDO 
  
  R_REDev__thetalogLikelihood = (ll)
  RETURN 
  
ENDFUNCTION 

! ----------------------------------------------------------------------------
! Including stdlib.f
! ----------------------------------------------------------------------------
! ----------------------------------------------------------------------------
! Standard definitions of needed functions
! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeInteger1(a,i)

  INTEGER(1) :: i
  INTEGER(1) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeInteger4(a,i)

  INTEGER(4) :: i
  INTEGER(4) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeInteger8(a,i)

  INTEGER(8) :: i
  INTEGER(8) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeReal4(a,i)

  INTEGER(4) :: i
  REAL(8) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeReal8(a,i)

  INTEGER(4) :: i
  REAL(8) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeReal16(a,i)

  INTEGER(4) :: i
  REAL(8) :: a(:)
  
ENDSUBROUTINE 

! ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__choleskyDecomposition(pA,pL,nSize)

  REAL(8) , INTENT (IN):: pA(nSize,nSize)
  REAL(8) , INTENT (INOUT):: pL(nSize,nSize)
  INTEGER(4) , INTENT (IN):: nSize
  USE COMMON
  ! --------------------------------------------------------------------------
  !  A is symetric positive definite matrix in lower triangular form
  !  L is the cholesky decomposition in lower triangular form
  ! --------------------------------------------------------------------------
  REAL(8) :: sum
  INTEGER(4) :: ci,cj,ck
  ci = 1
  
  DO WHILE (ci.LE.nSize)
    sum = pA(ci,ci)
    cj = 1
    
    DO WHILE (cj.LE.ci - 1)
      sum = sum - pL(ci,cj) * pL(ci,cj)
      cj = cj + 1
    ENDDO 
    
    pL(ci,ci) = SQRT(sum)
    cj = ci + 1
    
    DO WHILE (cj.LE.nSize)
      sum = pA(cj,ci)
      ck = 1
      
      DO WHILE (ck.LE.ci - 1)
        sum = sum - pL(ci,ck) * pL(cj,ck)
        ck = ck + 1
      ENDDO 
      
      pL(cj,ci) = sum / pL(ci,ci)
      cj = cj + 1
    ENDDO 
    
    ci = ci + 1
  ENDDO 
  
  
ENDSUBROUTINE 

!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__matrixInverseFromChol(pL,pInv,nSize)

  REAL(8) , INTENT (IN):: pL(nSize,nSize)
  REAL(8) , INTENT (INOUT):: pInv(nSize,nSize)
  INTEGER(4) , INTENT (IN):: nSize
  USE COMMON
  ! --------------------------------------------------------------------------
  !  pL is the cholesky decomposition of A in lower triangular form
  !  pInv is the resulting lower triangular inverse matrix
  ! --------------------------------------------------------------------------
  INTEGER(4) :: cc
  INTEGER(4) :: cr
  INTEGER(4) :: cq
  REAL(8) :: b
  cc = nSize
  
  DO WHILE (cc.GE.1)
    cr = cc
    
    DO WHILE (cr.GE.1)
      b = 0.0
      
      IF (cr.EQ.cc) THEN
      
        b = (1.0 / pL(cr,cr))
        
      ENDIF 
      
      
      IF (cr.LT.nSize) THEN
      
        cq = 1 + cr
        
        DO WHILE (cq.LE.nSize)
          b = b - pInv(cq,cc) * pL(cq,cr)
          cq = cq + 1
        ENDDO 
        
        
      ENDIF 
      
      pInv(cc,cr) = b * (1.0 / pL(cr,cr))
      cr = cr - 1
    ENDDO 
    
    cc = cc - 1
  ENDDO 
  
  
ENDSUBROUTINE 

!  Differentiation of redev__loglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__loglikelihood
!   with respect to varying inputs: re
!   RW status of diff variables: y:(loc) par_u:(loc) redev__loglikelihood:in-killed
!                re:out
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__LOGLIKELIHOOD_BRE(re,reb1_re,par,loglikelihoodb1_re&
&)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) :: reb1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  REAL(8) :: dlikelihoodb1_re
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  REAL(8) :: loglikelihoodb1_re
  !  Copy over random effects
  cm = 1
  cn = 0
  ad_count = 0
  
  DO WHILE (cn.LT.nr)
    par_u(cm) = re(cm)
    CALL PUSHINTEGER4(cm)
    cm = cm + 1
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  cm = cm + 1
  par_logk = par(cm)
  cm = cm + 1
  par_logq = par(cm)
  cm = cm + 1
  par_logr = par(cm)
  !  Call likelihood function
  dlikelihoodb1_re = loglikelihoodb1_re
  CALL R_REDev__THETALOGLIKELIHOOD_BRE(par_u,par_ub1_re,par_logr0,par_l&
  &ogtheta,par_logk,par_logq,par_logr,dlikelihoodb1_re)
  reb1_re = 0.0
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cm)
    reb1_re(cm) = reb1_re(cm) + par_ub1_re(cm)
    par_ub1_re(cm) = 0.0
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__LOGLIKELIHOOD_BRE

!  Differentiation of redev__thetaloglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__thetaloglikelihood
!   with respect to varying inputs: u
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE(u,ub1_re,logr0,logtheta,logk&
&,logq,logr,thetaloglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) :: ub1_re(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logk
  REAL(8) , INTENT (IN):: logq
  REAL(8) , INTENT (IN):: logr
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meanb1_re
  REAL(8) :: r0
  REAL(8) :: theta
  REAL(8) :: k
  REAL(8) :: q
  REAL(8) :: r
  REAL(8) :: llb1_re
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: arg1
  REAL(8) :: result1b1_re
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  INTEGER(4) :: ad_count0
  INTEGER(4) :: i0
  REAL(8) :: thetaloglikelihoodb1_re
  mean = 0
  arg1 = 0
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  k = EXP(logk)
  q = EXP(logq)
  r = EXP(logr)
  cn = 2
  ad_count = 0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(mean)
    mean = u(cn - 1) + r0 * (1.0 - (EXP(u(cn - 1)) / k)**theta)
    CALL PUSHREAL8(arg1)
    arg1 = SQRT(q)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  cn = 1
  ad_count0 = 0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(arg1)
    arg1 = SQRT(r)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count0 = ad_count0 + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count0)
  llb1_re = thetaloglikelihoodb1_re
  ub1_re = 0.0
  CALL POPINTEGER4(ad_count0)
  
  DO i0 = 1,ad_count0
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    yb1_re = 0.0
    CALL R_REDev__DLOGNORM_BRE(y(cn),yb1_re(cn),u(cn),ub1_re(cn),arg1,r&
    &esult1b1_re)
    CALL POPREAL8(arg1)
  ENDDO 
  
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    meanb1_re = 0.0
    CALL R_REDev__DLOGNORM_BRE(u(cn),ub1_re(cn),mean,meanb1_re,arg1,res&
    &ult1b1_re)
    CALL POPREAL8(arg1)
    CALL POPREAL8(mean)
    
    IF (EXP(u(cn - 1)) / k.LE.0.0.AND.(theta.EQ.0.0.OR.theta.NE.INT(the&
    &ta))) THEN
    
      ub1_re(cn - 1) = ub1_re(cn - 1) + meanb1_re
      
    ELSE 
    
      ub1_re(cn - 1) = ub1_re(cn - 1) + (1.0 - theta * (EXP(u(cn - 1)) &
      &/ k)**(theta - 1) * r0 * EXP(u(cn - 1)) / k) * meanb1_re
      
    ENDIF 
    
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE

!  Differentiation of redev__dlognorm in reverse (adjoint) mode:
!   gradient     of useful results: x redev__dlognorm mean
!   with respect to varying inputs: x mean
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__DLOGNORM_BRE(x,xb1_re,mean,meanb1_re,sigma,dlognorm&
&b1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) :: xb1_re
  REAL(8) , INTENT (IN):: mean
  REAL(8) :: meanb1_re
  REAL(8) , INTENT (IN):: sigma
  USE COMMON
  REAL(8) :: dvalueb1_re
  INTRINSIC LOG
  REAL(8) :: dlognormb1_re
  REAL(8) :: tempb1_re
  dvalueb1_re = dlognormb1_re
  tempb1_re = -(2.0 * (x - mean) * 0.5 * dvalueb1_re / sigma**2)
  xb1_re = xb1_re + tempb1_re
  meanb1_re = meanb1_re - tempb1_re
  
ENDSUBROUTINE R_REDev__DLOGNORM_BRE

!  Differentiation of redev__loglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: reb1_re
!   with respect to varying inputs: re
!   RW status of diff variables: par_ub1_re:(loc) y:(loc) yb1_re:(loc)
!                par_u:(loc) reb1_re:out re:in
!  Differentiation of redev__loglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__loglikelihood
!   with respect to varying inputs: re
!   RW status of diff variables: y:(loc) par_u:(loc) redev__loglikelihood:in-killed
!                re:out
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__LOGLIKELIHOOD_BRE_DRE(re,red2_re,reb1_re,reb1_red2_&
&re,par,loglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red2_re(nr)
  REAL(8) :: reb1_re(nr)
  REAL(8) :: reb1_red2_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  REAL(8) :: dlikelihoodb1_re
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  REAL(8) :: loglikelihoodb1_re
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  !  Copy over random effects
  cm = 1
  cn = 0
  ad_count = 0
  par_ud2_re = 0.0
  
  DO WHILE (cn.LT.nr)
    par_ud2_re(cm) = red2_re(cm)
    par_u(cm) = re(cm)
    CALL PUSHINTEGER4(cm)
    cm = cm + 1
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  cm = cm + 1
  par_logk = par(cm)
  cm = cm + 1
  par_logq = par(cm)
  cm = cm + 1
  par_logr = par(cm)
  !  Call likelihood function
  dlikelihoodb1_re = loglikelihoodb1_re
  CALL R_REDev__THETALOGLIKELIHOOD_BRE_DRE(par_u,par_ud2_re,par_ub1_re,&
  &par_ub1_red2_re,par_logr0,par_logtheta,par_logk,par_logq,par_logr,dl&
  &ikelihoodb1_re)
  reb1_re = 0.0
  CALL POPINTEGER4(ad_count)
  reb1_red2_re = 0.0
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cm)
    reb1_red2_re(cm) = reb1_red2_re(cm) + par_ub1_red2_re(cm)
    reb1_re(cm) = reb1_re(cm) + par_ub1_re(cm)
    par_ub1_red2_re(cm) = 0.0
    par_ub1_re(cm) = 0.0
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__LOGLIKELIHOOD_BRE_DRE

!  Differentiation of redev__thetaloglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: ub1_re
!   with respect to varying inputs: u
!  Differentiation of redev__thetaloglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__thetaloglikelihood
!   with respect to varying inputs: u
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE_DRE(u,ud2_re,ub1_re,ub1_red2&
&_re,logr0,logtheta,logk,logq,logr,thetaloglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) , INTENT (IN):: ud2_re(n)
  REAL(8) :: ub1_re(n)
  REAL(8) :: ub1_red2_re(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logk
  REAL(8) , INTENT (IN):: logq
  REAL(8) , INTENT (IN):: logr
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meand2_re
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red2_re
  REAL(8) :: r0
  REAL(8) :: theta
  REAL(8) :: k
  REAL(8) :: q
  REAL(8) :: r
  REAL(8) :: llb1_re
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: arg1
  REAL(8) :: arg1d2_re
  REAL(8) :: result1b1_re
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  INTEGER(4) :: ad_count0
  INTEGER(4) :: i0
  REAL(8) :: thetaloglikelihoodb1_re
  EXTERNAL PUSHREAL8
  EXTERNAL PUSHREAL8_d
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  EXTERNAL POPREAL8
  EXTERNAL POPREAL8_d
  INTRINSIC INT
  REAL(8) :: pwx1
  REAL(8) :: pwx1d2_re
  REAL(8) :: pwr1
  REAL(8) :: pwr1d2_re
  REAL(8) :: pwy1
  mean = 0
  arg1 = 0
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  k = EXP(logk)
  q = EXP(logq)
  r = EXP(logr)
  cn = 2
  ad_count = 0
  meand2_re = 0.0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(mean)
    CALL PUSHREAL8(meand2_re)
    pwx1d2_re = ud2_re(cn - 1) * EXP(u(cn - 1)) / k
    pwx1 = EXP(u(cn - 1)) / k
    
    IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.theta.EQ.INT(theta))) THEN
    
      pwr1d2_re = theta * pwx1**(theta - 1) * pwx1d2_re
      
    ELSEIF (pwx1.EQ.0.0.AND.theta.EQ.1.0) THEN 
    
      pwr1d2_re = pwx1d2_re
      
    ELSE 
    
      pwr1d2_re = 0.0
      
    ENDIF 
    
    pwr1 = pwx1**theta
    meand2_re = ud2_re(cn - 1) - r0 * pwr1d2_re
    mean = u(cn - 1) + r0 * (1.0 - pwr1)
    arg1d2_re = 0.0
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d2_re)
    arg1 = SQRT(q)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  cn = 1
  ad_count0 = 0
  
  DO WHILE (cn.LE.n)
    arg1d2_re = 0.0
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d2_re)
    arg1 = SQRT(r)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count0 = ad_count0 + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count0)
  llb1_re = thetaloglikelihoodb1_re
  ub1_re = 0.0
  CALL POPINTEGER4(ad_count0)
  ub1_red2_re = 0.0
  arg1d2_re = 0.0
  
  DO i0 = 1,ad_count0
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    yb1_re = 0.0
    yb1_red2_re = 0.0
    yd2_re = 0.0
    CALL R_REDev__DLOGNORM_BRE_DRE(y(cn),yd2_re(cn),yb1_re(cn),yb1_red2&
    &_re(cn),u(cn),ud2_re(cn),ub1_re(cn),ub1_red2_re(cn),arg1,arg1d2_re&
    &,result1b1_re)
    CALL POPREAL8(arg1d2_re)
    CALL POPREAL8(arg1)
  ENDDO 
  
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    meanb1_re = 0.0
    meanb1_red2_re = 0.0
    CALL R_REDev__DLOGNORM_BRE_DRE(u(cn),ud2_re(cn),ub1_re(cn),ub1_red2&
    &_re(cn),mean,meand2_re,meanb1_re,meanb1_red2_re,arg1,arg1d2_re,res&
    &ult1b1_re)
    CALL POPREAL8(arg1d2_re)
    CALL POPREAL8(arg1)
    CALL POPREAL8(meand2_re)
    CALL POPREAL8(mean)
    
    IF (EXP(u(cn - 1)) / k.LE.0.0.AND.(theta.EQ.0.0.OR.theta.NE.INT(the&
    &ta))) THEN
    
      ub1_red2_re(cn - 1) = ub1_red2_re(cn - 1) + meanb1_red2_re
      ub1_re(cn - 1) = ub1_re(cn - 1) + meanb1_re
      
    ELSE 
    
      pwx1d2_re = ud2_re(cn - 1) * EXP(u(cn - 1)) / k
      pwx1 = EXP(u(cn - 1)) / k
      pwy1 = theta - 1
      
      IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.pwy1.EQ.INT(pwy1))) THEN
      
        pwr1d2_re = pwy1 * pwx1**(pwy1 - 1) * pwx1d2_re
        
      ELSEIF (pwx1.EQ.0.0.AND.pwy1.EQ.1.0) THEN 
      
        pwr1d2_re = pwx1d2_re
        
      ELSE 
      
        pwr1d2_re = 0.0
        
      ENDIF 
      
      pwr1 = pwx1**pwy1
      ub1_red2_re(cn - 1) = ub1_red2_re(cn - 1) + (1.0 - theta * pwr1 *&
      & r0 * EXP(u(cn - 1)) / k) * meanb1_red2_re - theta * r0 * (pwr1d&
      &2_re * EXP(u(cn - 1)) + pwr1 * ud2_re(cn - 1) * EXP(u(cn - 1))) &
      &* meanb1_re / k
      ub1_re(cn - 1) = ub1_re(cn - 1) + (1.0 - theta * pwr1 * r0 * EXP(&
      &u(cn - 1)) / k) * meanb1_re
      
    ENDIF 
    
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE_DRE

!  Differentiation of redev__dlognorm_bre in forward (tangent) mode:
!   variations   of useful results: meanb1_re xb1_re
!   with respect to varying inputs: x sigma meanb1_re xb1_re mean
!  Differentiation of redev__dlognorm in reverse (adjoint) mode:
!   gradient     of useful results: x redev__dlognorm mean
!   with respect to varying inputs: x mean
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__DLOGNORM_BRE_DRE(x,xd2_re,xb1_re,xb1_red2_re,mean,m&
&eand2_re,meanb1_re,meanb1_red2_re,sigma,sigmad2_re,dlognormb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) , INTENT (IN):: xd2_re
  REAL(8) :: xb1_re
  REAL(8) :: xb1_red2_re
  REAL(8) , INTENT (IN):: mean
  REAL(8) , INTENT (IN):: meand2_re
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red2_re
  REAL(8) , INTENT (IN):: sigma
  REAL(8) , INTENT (IN):: sigmad2_re
  USE COMMON
  REAL(8) :: dvalueb1_re
  INTRINSIC LOG
  REAL(8) :: dlognormb1_re
  REAL(8) :: tempb1_re
  REAL(8) :: tempb1_red2_re
  dvalueb1_re = dlognormb1_re
  tempb1_red2_re = -((2.0 * 0.5 * dvalueb1_re * (xd2_re - meand2_re) * &
  &sigma**2 - 2.0 * (x - mean) * 0.5 * dvalueb1_re * 2 * sigma * sigmad&
  &2_re) / (sigma**2)**2)
  tempb1_re = -(2.0 * (x - mean) * 0.5 * dvalueb1_re / sigma**2)
  xb1_red2_re = xb1_red2_re + tempb1_red2_re
  xb1_re = xb1_re + tempb1_re
  meanb1_red2_re = meanb1_red2_re - tempb1_red2_re
  meanb1_re = meanb1_re - tempb1_re
  
ENDSUBROUTINE R_REDev__DLOGNORM_BRE_DRE

!  Differentiation of redev__loglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: reb1_re
!   with respect to varying inputs: par
!   RW status of diff variables: par_ub1_re:(loc) par_logr0:(loc)
!                yb1_re:(loc) par_logk:(loc) par_logq:(loc) par_logr:(loc)
!                par_logtheta:(loc) par_u:(loc) reb1_re:out par:in
!  Differentiation of redev__loglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__loglikelihood
!   with respect to varying inputs: re
!   RW status of diff variables: y:(loc) par_u:(loc) redev__loglikelihood:in-killed
!                re:out
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__LOGLIKELIHOOD_BRE_DPAR(re,reb1_re,reb1_red3_par,par&
&,pard3_par,loglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) :: reb1_re(nr)
  REAL(8) :: reb1_red3_par(nr)
  REAL(8) , INTENT (IN):: par(np)
  REAL(8) , INTENT (IN):: pard3_par(np)
  USE COMMON
  REAL(8) :: dlikelihoodb1_re
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  REAL(8) :: loglikelihoodb1_re
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  !  Copy over random effects
  cm = 1
  cn = 0
  ad_count = 0
  
  DO WHILE (cn.LT.nr)
    par_u(cm) = re(cm)
    CALL PUSHINTEGER4(cm)
    cm = cm + 1
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  !  Copy over parameters
  cm = 1
  par_logr0d3_par = pard3_par(cm)
  par_logr0 = par(cm)
  cm = cm + 1
  par_logthetad3_par = pard3_par(cm)
  par_logtheta = par(cm)
  cm = cm + 1
  par_logkd3_par = pard3_par(cm)
  par_logk = par(cm)
  cm = cm + 1
  par_logqd3_par = pard3_par(cm)
  par_logq = par(cm)
  cm = cm + 1
  par_logrd3_par = pard3_par(cm)
  par_logr = par(cm)
  !  Call likelihood function
  dlikelihoodb1_re = loglikelihoodb1_re
  CALL R_REDev__THETALOGLIKELIHOOD_BRE_DPAR(par_u,par_ud3_par,par_ub1_r&
  &e,par_ub1_red3_par,par_logr0,par_logr0d3_par,par_logtheta,par_logthe&
  &tad3_par,par_logk,par_logkd3_par,par_logq,par_logqd3_par,par_logr,pa&
  &r_logrd3_par,dlikelihoodb1_re)
  reb1_re = 0.0
  CALL POPINTEGER4(ad_count)
  reb1_red3_par = 0.0
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cm)
    reb1_red3_par(cm) = reb1_red3_par(cm) + par_ub1_red3_par(cm)
    reb1_re(cm) = reb1_re(cm) + par_ub1_re(cm)
    par_ub1_red3_par(cm) = 0.0
    par_ub1_re(cm) = 0.0
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__LOGLIKELIHOOD_BRE_DPAR

!  Differentiation of redev__thetaloglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: ub1_re
!   with respect to varying inputs: logq logr logr0 logtheta logk
!  Differentiation of redev__thetaloglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__thetaloglikelihood
!   with respect to varying inputs: u
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE_DPAR(u,ud3_par,ub1_re,ub1_re&
&d3_par,logr0,logr0d3_par,logtheta,logthetad3_par,logk,logkd3_par,logq,&
&logqd3_par,logr,logrd3_par,thetaloglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) , INTENT (IN):: ud3_par(n)
  REAL(8) :: ub1_re(n)
  REAL(8) :: ub1_red3_par(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logr0d3_par
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logthetad3_par
  REAL(8) , INTENT (IN):: logk
  REAL(8) , INTENT (IN):: logkd3_par
  REAL(8) , INTENT (IN):: logq
  REAL(8) , INTENT (IN):: logqd3_par
  REAL(8) , INTENT (IN):: logr
  REAL(8) , INTENT (IN):: logrd3_par
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meand3_par
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red3_par
  REAL(8) :: r0
  REAL(8) :: r0d3_par
  REAL(8) :: theta
  REAL(8) :: thetad3_par
  REAL(8) :: k
  REAL(8) :: kd3_par
  REAL(8) :: q
  REAL(8) :: qd3_par
  REAL(8) :: r
  REAL(8) :: rd3_par
  REAL(8) :: llb1_re
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: arg1
  REAL(8) :: arg1d3_par
  REAL(8) :: result1b1_re
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  INTEGER(4) :: ad_count0
  INTEGER(4) :: i0
  REAL(8) :: thetaloglikelihoodb1_re
  EXTERNAL PUSHREAL8
  EXTERNAL PUSHREAL8_d
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  EXTERNAL POPREAL8
  EXTERNAL POPREAL8_d
  INTRINSIC INT
  REAL(8) :: pwx1
  REAL(8) :: pwx1d3_par
  REAL(8) :: pwr1
  REAL(8) :: pwr1d3_par
  REAL(8) :: pwy1
  REAL(8) :: pwy1d3_par
  mean = 0
  arg1 = 0
  r0d3_par = logr0d3_par * EXP(logr0)
  r0 = EXP(logr0)
  thetad3_par = logthetad3_par * EXP(logtheta)
  theta = EXP(logtheta)
  kd3_par = logkd3_par * EXP(logk)
  k = EXP(logk)
  qd3_par = logqd3_par * EXP(logq)
  q = EXP(logq)
  rd3_par = logrd3_par * EXP(logr)
  r = EXP(logr)
  cn = 2
  ad_count = 0
  arg1d3_par = 0.0
  meand3_par = 0.0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(mean)
    CALL PUSHREAL8(meand3_par)
    pwx1d3_par = -(EXP(u(cn - 1)) * kd3_par / k**2)
    pwx1 = EXP(u(cn - 1)) / k
    
    IF (pwx1.GT.0.0) THEN
    
      pwr1d3_par = pwx1**theta * (LOG(pwx1) * thetad3_par + theta * pwx&
      &1d3_par / pwx1)
      
    ELSEIF (pwx1.EQ.0.0) THEN 
    
      
      IF (theta.EQ.1.0) THEN
      
        pwr1d3_par = pwx1d3_par
        
      ELSE 
      
        pwr1d3_par = 0.0
        
      ENDIF 
      
      
    ELSEIF (theta.EQ.INT(theta)) THEN 
    
      pwr1d3_par = theta * pwx1**(theta - 1) * pwx1d3_par
      
    ELSE 
    
      pwr1d3_par = 0.0
      
    ENDIF 
    
    pwr1 = pwx1**theta
    meand3_par = r0d3_par * (1.0 - pwr1) - r0 * pwr1d3_par
    mean = u(cn - 1) + r0 * (1.0 - pwr1)
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d3_par)
    
    IF (q.EQ.0.0) THEN
    
      arg1d3_par = 0.0
      
    ELSE 
    
      arg1d3_par = qd3_par / (2.0 * SQRT(q))
      
    ENDIF 
    
    arg1 = SQRT(q)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  cn = 1
  ad_count0 = 0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d3_par)
    
    IF (r.EQ.0.0) THEN
    
      arg1d3_par = 0.0
      
    ELSE 
    
      arg1d3_par = rd3_par / (2.0 * SQRT(r))
      
    ENDIF 
    
    arg1 = SQRT(r)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count0 = ad_count0 + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count0)
  llb1_re = thetaloglikelihoodb1_re
  ub1_re = 0.0
  CALL POPINTEGER4(ad_count0)
  ub1_red3_par = 0.0
  
  DO i0 = 1,ad_count0
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    yb1_re = 0.0
    ud3_par = 0.0
    yb1_red3_par = 0.0
    CALL R_REDev__DLOGNORM_BRE_DPAR(y(cn),yb1_re(cn),yb1_red3_par(cn),u&
    &(cn),ud3_par(cn),ub1_re(cn),ub1_red3_par(cn),arg1,arg1d3_par,resul&
    &t1b1_re)
    CALL POPREAL8(arg1d3_par)
    CALL POPREAL8(arg1)
  ENDDO 
  
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    meanb1_re = 0.0
    meanb1_red3_par = 0.0
    CALL R_REDev__DLOGNORM_BRE_DPAR(u(cn),ub1_re(cn),ub1_red3_par(cn),m&
    &ean,meand3_par,meanb1_re,meanb1_red3_par,arg1,arg1d3_par,result1b1&
    &_re)
    CALL POPREAL8(arg1d3_par)
    CALL POPREAL8(arg1)
    CALL POPREAL8(meand3_par)
    CALL POPREAL8(mean)
    
    IF (EXP(u(cn - 1)) / k.LE.0.0.AND.(theta.EQ.0.0.OR.theta.NE.INT(the&
    &ta))) THEN
    
      ub1_red3_par(cn - 1) = ub1_red3_par(cn - 1) + meanb1_red3_par
      ub1_re(cn - 1) = ub1_re(cn - 1) + meanb1_re
      
    ELSE 
    
      pwx1d3_par = -(EXP(u(cn - 1)) * kd3_par / k**2)
      pwx1 = EXP(u(cn - 1)) / k
      pwy1d3_par = thetad3_par
      pwy1 = theta - 1
      
      IF (pwx1.GT.0.0) THEN
      
        pwr1d3_par = pwx1**pwy1 * (LOG(pwx1) * pwy1d3_par + pwy1 * pwx1&
        &d3_par / pwx1)
        
      ELSEIF (pwx1.EQ.0.0) THEN 
      
        
        IF (pwy1.EQ.1.0) THEN
        
          pwr1d3_par = pwx1d3_par
          
        ELSE 
        
          pwr1d3_par = 0.0
          
        ENDIF 
        
        
      ELSEIF (pwy1.EQ.INT(pwy1)) THEN 
      
        pwr1d3_par = pwy1 * pwx1**(pwy1 - 1) * pwx1d3_par
        
      ELSE 
      
        pwr1d3_par = 0.0
        
      ENDIF 
      
      pwr1 = pwx1**pwy1
      ub1_red3_par(cn - 1) = ub1_red3_par(cn - 1) + (1.0 - theta * pwr1&
      & * r0 * EXP(u(cn - 1)) / k) * meanb1_red3_par - (EXP(u(cn - 1)) &
      &* ((thetad3_par * pwr1 + theta * pwr1d3_par) * r0 + theta * pwr1&
      & * r0d3_par) * k - theta * pwr1 * r0 * EXP(u(cn - 1)) * kd3_par)&
      & * meanb1_re / k**2
      ub1_re(cn - 1) = ub1_re(cn - 1) + (1.0 - theta * pwr1 * r0 * EXP(&
      &u(cn - 1)) / k) * meanb1_re
      
    ENDIF 
    
  ENDDO 
  
  
ENDSUBROUTINE R_REDev__THETALOGLIKELIHOOD_BRE_DPAR

!  Differentiation of redev__dlognorm_bre in forward (tangent) mode:
!   variations   of useful results: meanb1_re xb1_re
!   with respect to varying inputs: sigma meanb1_re xb1_re mean
!  Differentiation of redev__dlognorm in reverse (adjoint) mode:
!   gradient     of useful results: x redev__dlognorm mean
!   with respect to varying inputs: x mean
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__DLOGNORM_BRE_DPAR(x,xb1_re,xb1_red3_par,mean,meand3&
&_par,meanb1_re,meanb1_red3_par,sigma,sigmad3_par,dlognormb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) :: xb1_re
  REAL(8) :: xb1_red3_par
  REAL(8) , INTENT (IN):: mean
  REAL(8) , INTENT (IN):: meand3_par
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red3_par
  REAL(8) , INTENT (IN):: sigma
  REAL(8) , INTENT (IN):: sigmad3_par
  USE COMMON
  REAL(8) :: dvalueb1_re
  INTRINSIC LOG
  REAL(8) :: dlognormb1_re
  REAL(8) :: tempb1_re
  REAL(8) :: tempb1_red3_par
  dvalueb1_re = dlognormb1_re
  tempb1_red3_par = -((-(2.0 * 0.5 * dvalueb1_re * meand3_par * sigma**&
  &2) - 2.0 * (x - mean) * 0.5 * dvalueb1_re * 2 * sigma * sigmad3_par)&
  & / (sigma**2)**2)
  tempb1_re = -(2.0 * (x - mean) * 0.5 * dvalueb1_re / sigma**2)
  xb1_red3_par = xb1_red3_par + tempb1_red3_par
  xb1_re = xb1_re + tempb1_re
  meanb1_red3_par = meanb1_red3_par - tempb1_red3_par
  meanb1_re = meanb1_re - tempb1_re
  
ENDSUBROUTINE R_REDev__DLOGNORM_BRE_DPAR

!  Differentiation of redev__loglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__loglikelihood
!   with respect to varying inputs: par
!   RW status of diff variables: par_logr0:(loc) par_logk:(loc)
!                par_logq:(loc) par_logr:(loc) par_logtheta:(loc)
!                par_u:(loc) redev__loglikelihood:in-killed par:out
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__LOGLIKELIHOOD_BPAR(re,par,parb4_par,loglikelihoodb4&
&_par)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: par(np)
  REAL(8) :: parb4_par(np)
  USE COMMON
  REAL(8) :: dlikelihoodb4_par
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  REAL(8) :: loglikelihoodb4_par
  !  Copy over random effects
  cm = 1
  cn = 0
  
  DO WHILE (cn.LT.nr)
    par_u(cm) = re(cm)
    cm = cm + 1
    cn = cn + 1
  ENDDO 
  
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  CALL PUSHINTEGER4(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  CALL PUSHINTEGER4(cm)
  cm = cm + 1
  par_logk = par(cm)
  CALL PUSHINTEGER4(cm)
  cm = cm + 1
  par_logq = par(cm)
  CALL PUSHINTEGER4(cm)
  cm = cm + 1
  par_logr = par(cm)
  !  Call likelihood function
  dlikelihoodb4_par = loglikelihoodb4_par
  CALL R_REDev__THETALOGLIKELIHOOD_BPAR(par_u,par_ub4_par,par_logr0,par&
  &_logr0b4_par,par_logtheta,par_logthetab4_par,par_logk,par_logkb4_par&
  &,par_logq,par_logqb4_par,par_logr,par_logrb4_par,dlikelihoodb4_par)
  parb4_par = 0.0
  parb4_par(cm) = parb4_par(cm) + par_logrb4_par
  CALL POPINTEGER4(cm)
  parb4_par(cm) = parb4_par(cm) + par_logqb4_par
  CALL POPINTEGER4(cm)
  parb4_par(cm) = parb4_par(cm) + par_logkb4_par
  CALL POPINTEGER4(cm)
  parb4_par(cm) = parb4_par(cm) + par_logthetab4_par
  CALL POPINTEGER4(cm)
  parb4_par(cm) = parb4_par(cm) + par_logr0b4_par
  
ENDSUBROUTINE R_REDev__LOGLIKELIHOOD_BPAR

!  Differentiation of redev__thetaloglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__thetaloglikelihood
!   with respect to varying inputs: logq logr logr0 logtheta logk
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__THETALOGLIKELIHOOD_BPAR(u,ub4_par,logr0,logr0b4_par&
&,logtheta,logthetab4_par,logk,logkb4_par,logq,logqb4_par,logr,logrb4_p&
&ar,thetaloglikelihoodb4_par)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) :: ub4_par(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) :: logr0b4_par
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) :: logthetab4_par
  REAL(8) , INTENT (IN):: logk
  REAL(8) :: logkb4_par
  REAL(8) , INTENT (IN):: logq
  REAL(8) :: logqb4_par
  REAL(8) , INTENT (IN):: logr
  REAL(8) :: logrb4_par
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meanb4_par
  REAL(8) :: r0
  REAL(8) :: r0b4_par
  REAL(8) :: theta
  REAL(8) :: thetab4_par
  REAL(8) :: k
  REAL(8) :: kb4_par
  REAL(8) :: q
  REAL(8) :: qb4_par
  REAL(8) :: r
  REAL(8) :: rb4_par
  REAL(8) :: llb4_par
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: arg1
  REAL(8) :: arg1b4_par
  REAL(8) :: result1b4_par
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  INTEGER(4) :: ad_count0
  INTEGER(4) :: i0
  REAL(8) :: thetaloglikelihoodb4_par
  REAL(8) :: temp1
  REAL(8) :: temp0
  REAL(8) :: temp
  mean = 0
  meanb4_par = 0
  arg1 = 0
  arg1b4_par = 0
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  k = EXP(logk)
  q = EXP(logq)
  r = EXP(logr)
  cn = 2
  ad_count = 0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(mean)
    mean = u(cn - 1) + r0 * (1.0 - (EXP(u(cn - 1)) / k)**theta)
    CALL PUSHREAL8(arg1)
    arg1 = SQRT(q)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  cn = 1
  ad_count0 = 0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(arg1)
    arg1 = SQRT(r)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count0 = ad_count0 + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count0)
  llb4_par = thetaloglikelihoodb4_par
  rb4_par = 0.0
  CALL POPINTEGER4(ad_count0)
  
  DO i0 = 1,ad_count0
    CALL POPINTEGER4(cn)
    result1b4_par = -llb4_par
    CALL R_REDev__DLOGNORM_BPAR(y(cn),u(cn),ub4_par(cn),arg1,arg1b4_par&
    &,result1b4_par)
    CALL POPREAL8(arg1)
    
    IF (.NOT.(((r.EQ.0.0)))) rb4_par = rb4_par + arg1b4_par / (2.0 * SQ&
    &RT(r))
    
  ENDDO 
  
  kb4_par = 0.0
  qb4_par = 0.0
  thetab4_par = 0.0
  r0b4_par = 0.0
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cn)
    result1b4_par = -llb4_par
    CALL R_REDev__DLOGNORM_BPAR(u(cn),mean,meanb4_par,arg1,arg1b4_par,r&
    &esult1b4_par)
    CALL POPREAL8(arg1)
    
    IF (.NOT.(((q.EQ.0.0)))) qb4_par = qb4_par + arg1b4_par / (2.0 * SQ&
    &RT(q))
    
    CALL POPREAL8(mean)
    temp1 = EXP(u(cn - 1))
    temp0 = temp1 / k
    temp = temp0**theta
    r0b4_par = r0b4_par + (1.0 - temp) * meanb4_par
    
    IF (.NOT.((((temp0.LE.0.0.AND.(theta.EQ.0.0.OR.theta.NE.INT(theta))&
    &))))) kb4_par = kb4_par + theta * temp0**(theta - 1) * r0 * temp0 &
    &* meanb4_par / k
    
    
    IF (.NOT.(((temp0.LE.0.0)))) thetab4_par = thetab4_par - r0 * temp &
    &* LOG(temp0) * meanb4_par
    
  ENDDO 
  
  logrb4_par = EXP(logr) * rb4_par
  logqb4_par = EXP(logq) * qb4_par
  logkb4_par = EXP(logk) * kb4_par
  logthetab4_par = EXP(logtheta) * thetab4_par
  logr0b4_par = EXP(logr0) * r0b4_par
  
ENDSUBROUTINE R_REDev__THETALOGLIKELIHOOD_BPAR

!  Differentiation of redev__dlognorm in reverse (adjoint) mode:
!   gradient     of useful results: redev__dlognorm
!   with respect to varying inputs: sigma mean
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDev__DLOGNORM_BPAR(x,mean,meanb4_par,sigma,sigmab4_par,d&
&lognormb4_par)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) , INTENT (IN):: mean
  REAL(8) :: meanb4_par
  REAL(8) , INTENT (IN):: sigma
  REAL(8) :: sigmab4_par
  USE COMMON
  REAL(8) :: dvalueb4_par
  INTRINSIC LOG
  REAL(8) :: dlognormb4_par
  REAL(8) :: tempb4_par
  REAL(8) :: temp
  dvalueb4_par = dlognormb4_par
  temp = (x - mean) / sigma
  tempb4_par = -(2.0 * temp * 0.5 * dvalueb4_par / sigma)
  sigmab4_par = -(temp * tempb4_par) - dvalueb4_par / sigma
  meanb4_par = -tempb4_par
  
ENDSUBROUTINE R_REDev__DLOGNORM_BPAR

!  Differentiation of r_redev__laplace in forward (tangent) mode:
!   variations   of useful results: r_redev__laplace
!   with respect to varying inputs: re
!   RW status of diff variables: par_ub1_re:(loc) y:(loc) yb1_red2_re:(loc)
!                choleskymatrixre:(loc) hessianmatrixre:(loc) par_ud2_re:(loc)
!                par_ub1_red2_re:(loc) par_u:(loc) re:in r_redev__laplace:out
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__LAPLACE_DRE(re,red1_re,par,laplace)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  REAL(8) :: h
  REAL(8) :: hd1_re
  INTEGER(4) :: m_pi
  INTRINSIC LOG
  REAL(8) :: result1
  REAL(8) :: result1d1_re
  REAL(8) :: result2
  REAL(8) :: result2d1_re
  REAL(8) :: laplace
  m_pi = 0
  result1 = 0
  result2 = 0
  par_ud1_re = 0.0
  result1d1_re = R_REDEV__LOGDETHESSIANRE_DRE(re,red1_re,par,result1)
  result2d1_re = R_REDEV__LOGLIKELIHOOD_DRE(re,red1_re,par,result2)
  hd1_re = 0.5 * result1d1_re + result2d1_re
  h = (-(nr * LOG(2 * m_pi)) + result1) * 0.5 + result2
  r_redev__laplace_dre = hd1_re
  laplace = h
  RETURN 
  
ENDFUNCTION R_REDEV__LAPLACE_DRE

!  Differentiation of r_redev__logdethessianre in forward (tangent) mode:
!   variations   of useful results: par_u r_redev__logdethessianre
!   with respect to varying inputs: re
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__LOGDETHESSIANRE_DRE(re,red1_re,par,logdethess&
&ianre)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  REAL(8) :: logdet
  REAL(8) :: logdetd1_re
  REAL(8) :: logdethessianre
  logdet = 0
  CALL R_REDEV__HESSIANRE_DRE(re,red1_re,par,hessianmatrixre,hessianmat&
  &rixred1_re)
  CALL R_REDEV__CHOLESKYDECOMPOSITION_DRE(hessianmatrixre,hessianmatrix&
  &red1_re,choleskymatrixre,choleskymatrixred1_re,nr)
  logdetd1_re = R_REDEV__LOGDETERMINANTFROMCHOL_DRE(choleskymatrixre,ch&
  &oleskymatrixred1_re,nr,logdet)
  r_redev__logdethessianre_dre = logdetd1_re
  logdethessianre = logdet
  RETURN 
  
ENDFUNCTION R_REDEV__LOGDETHESSIANRE_DRE

!  Differentiation of r_redev__logdeterminantfromchol in forward (tangent) mode:
!   variations   of useful results: r_redev__logdeterminantfromchol
!   with respect to varying inputs: pl
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__LOGDETERMINANTFROMCHOL_DRE(pl,pld1_re,nsize,l&
&ogdeterminantfromchol)

  IMPLICIT NONE
  INTEGER(4) , INTENT (IN):: nsize
  REAL(8) , INTENT (IN):: pl(nsize,nsize)
  REAL(8) , INTENT (IN):: pld1_re(nsize,nsize)
  USE COMMON
  ! --------------------------------------------------------------------------
  !  pL is the cholesky decomposition of A in lower triangular form
  ! --------------------------------------------------------------------------
  REAL(8) :: dlogdet
  REAL(8) :: dlogdetd1_re
  INTEGER(4) :: ci
  INTRINSIC LOG
  REAL(8) :: logdeterminantfromchol
  dlogdet = 0.0
  ci = 1
  dlogdetd1_re = 0.0
  
  DO WHILE (ci.LE.nsize)
    dlogdetd1_re = dlogdetd1_re + pld1_re(ci,ci) / pl(ci,ci)
    dlogdet = dlogdet + LOG(pl(ci,ci))
    ci = ci + 1
  ENDDO 
  
  dlogdetd1_re = 2.0 * dlogdetd1_re
  dlogdet = dlogdet * 2.0
  r_redev__logdeterminantfromchol_dre = dlogdetd1_re
  logdeterminantfromchol = dlogdet
  RETURN 
  
ENDFUNCTION R_REDEV__LOGDETERMINANTFROMCHOL_DRE

!  Differentiation of r_redev__loglikelihood in forward (tangent) mode:
!   variations   of useful results: r_redev__loglikelihood
!   with respect to varying inputs: par_u re
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__LOGLIKELIHOOD_DRE(re,red1_re,par,loglikelihoo&
&d)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  !  Decode parameters     
  REAL(8) :: dlikelihood
  REAL(8) :: dlikelihoodd1_re
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  REAL(8) :: loglikelihood
  dlikelihood = 0
  !  Copy over random effects
  cm = 1
  cn = 0
  
  DO WHILE (cn.LT.nr)
    par_ud1_re(cm) = red1_re(cm)
    par_u(cm) = re(cm)
    cm = cm + 1
    cn = cn + 1
  ENDDO 
  
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  cm = cm + 1
  par_logk = par(cm)
  cm = cm + 1
  par_logq = par(cm)
  cm = cm + 1
  par_logr = par(cm)
  cm = cm + 1
  !  Call likelihood function
  dlikelihoodd1_re = R_REDEV__THETALOGLIKELIHOOD_DRE(par_u,par_ud1_re,p&
  &ar_logr0,par_logtheta,par_logk,par_logq,par_logr,dlikelihood)
  r_redev__loglikelihood_dre = dlikelihoodd1_re
  loglikelihood = dlikelihood
  RETURN 
  
ENDFUNCTION R_REDEV__LOGLIKELIHOOD_DRE

!  Differentiation of r_redev__thetaloglikelihood in forward (tangent) mode:
!   variations   of useful results: r_redev__thetaloglikelihood
!   with respect to varying inputs: u
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__THETALOGLIKELIHOOD_DRE(u,ud1_re,logr0,logthet&
&a,logk,logq,logr,thetaloglikelihood)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) , INTENT (IN):: ud1_re(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logk
  REAL(8) , INTENT (IN):: logq
  REAL(8) , INTENT (IN):: logr
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meand1_re
  REAL(8) :: r0
  REAL(8) :: theta
  REAL(8) :: k
  REAL(8) :: q
  REAL(8) :: r
  REAL(8) :: ll
  REAL(8) :: lld1_re
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: pwx1
  REAL(8) :: pwx1d1_re
  REAL(8) :: pwr1
  REAL(8) :: pwr1d1_re
  REAL(8) :: result1
  REAL(8) :: result2
  REAL(8) :: result2d1_re
  REAL(8) :: thetaloglikelihood
  result2 = 0
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  k = EXP(logk)
  q = EXP(logq)
  r = EXP(logr)
  ll = 0.0
  cn = 2
  lld1_re = 0.0
  
  DO WHILE (cn.LE.n)
    pwx1d1_re = ud1_re(cn - 1) * EXP(u(cn - 1)) / k
    pwx1 = EXP(u(cn - 1)) / k
    
    IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.theta.EQ.INT(theta))) THEN
    
      pwr1d1_re = theta * pwx1**(theta - 1) * pwx1d1_re
      
    ELSEIF (pwx1.EQ.0.0.AND.theta.EQ.1.0) THEN 
    
      pwr1d1_re = pwx1d1_re
      
    ELSE 
    
      pwr1d1_re = 0.0
      
    ENDIF 
    
    pwr1 = pwx1**theta
    meand1_re = ud1_re(cn - 1) - r0 * pwr1d1_re
    mean = u(cn - 1) + r0 * (1.0 - pwr1)
    result1 = SQRT(q)
    result2d1_re = R_REDEV__DLOGNORM_DRE(u(cn),ud1_re(cn),mean,meand1_r&
    &e,result1,result2)
    lld1_re = lld1_re - result2d1_re
    ll = ll - result2
    cn = cn + 1
  ENDDO 
  
  cn = 1
  
  DO WHILE (cn.LE.n)
    result1 = SQRT(r)
    yd1_re = 0.0
    result2d1_re = R_REDEV__DLOGNORM_DRE(y(cn),yd1_re(cn),u(cn),ud1_re(&
    &cn),result1,result2)
    lld1_re = lld1_re - result2d1_re
    ll = ll - result2
    cn = cn + 1
  ENDDO 
  
  r_redev__thetaloglikelihood_dre = lld1_re
  thetaloglikelihood = ll
  RETURN 
  
ENDFUNCTION R_REDEV__THETALOGLIKELIHOOD_DRE

!  Differentiation of r_redev__dlognorm in forward (tangent) mode:
!   variations   of useful results: r_redev__dlognorm
!   with respect to varying inputs: x mean
!  ----------------------------------------------------------------------------
REAL(8) FUNCTION R_REDEV__DLOGNORM_DRE(x,xd1_re,mean,meand1_re,sigma,dl&
&ognorm)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) , INTENT (IN):: xd1_re
  REAL(8) , INTENT (IN):: mean
  REAL(8) , INTENT (IN):: meand1_re
  REAL(8) , INTENT (IN):: sigma
  USE COMMON
  REAL(8) :: dvalue
  REAL(8) :: dvalued1_re
  INTRINSIC LOG
  INTEGER(4) :: m_pi
  REAL(8) :: dlognorm
  m_pi = 0
  dvalued1_re = -(0.5 * 2.0 * (x - mean) * (xd1_re - meand1_re) / sigma&
  &**2)
  dvalue = -LOG(sigma) - 0.5 * LOG(2 * m_pi) - 0.5 * ((x - mean) / sigm&
  &a)**2.0
  r_redev__dlognorm_dre = dvalued1_re
  dlognorm = dvalue
  RETURN 
  
ENDFUNCTION R_REDEV__DLOGNORM_DRE

!  Differentiation of r_redev__hessianre in forward (tangent) mode:
!   variations   of useful results: par_u phessian
!   with respect to varying inputs: re
!  ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDEV__HESSIANRE_DRE(re,red1_re,par,phessian,phessiand1_re&
&)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  REAL(8) , INTENT (INOUT):: phessian(nr,nr)
  REAL(8) , INTENT (INOUT):: phessiand1_re(nr,nr)
  USE COMMON
  INTEGER(4) :: cn
  REAL(8) :: loglikelihoodb1_re
  loglikelihoodb1_re = 1.0
  cn = 1
  
  DO WHILE (cn.LE.nr)
    red2_re(cn) = 0.0
    cn = cn + 1
  ENDDO 
  
  cn = 1
  par_ud1_re = 0.0
  phessiand1_re = 0.0
  
  DO WHILE (cn.LE.nr)
    red2_re(cn) = 1.0
    !  Hessian matrix is symmetric and we construct the matrix row by row by
    !  taking the tangent derivative of the adjoint derivative in each basis
    !  direction. The hessian result goes into an ARRAY_2D but we pass the
    !  n'th column to be filled by indexing the array.
    CALL R_REDEV__LOGLIKELIHOOD_BRE_DRE_DRE(re,red1_re,red2_re,reb1_re,&
    &phessian(cn),phessiand1_re(cn),par,loglikelihoodb1_re)
    red2_re(cn) = 0.0
    cn = cn + 1
  ENDDO 
  
  
ENDSUBROUTINE R_REDEV__HESSIANRE_DRE

!  Differentiation of r_redev__choleskydecomposition in forward (tangent) mode:
!   variations   of useful results: pl
!   with respect to varying inputs: pa
! ----------------------------------------------------------------------------
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDEV__CHOLESKYDECOMPOSITION_DRE(pa,pad1_re,pl,pld1_re,nsi&
&ze)

  IMPLICIT NONE
  INTEGER(4) , INTENT (IN):: nsize
  REAL(8) , INTENT (IN):: pa(nsize,nsize)
  REAL(8) , INTENT (IN):: pad1_re(nsize,nsize)
  REAL(8) , INTENT (INOUT):: pl(nsize,nsize)
  REAL(8) , INTENT (INOUT):: pld1_re(nsize,nsize)
  USE COMMON
  ! --------------------------------------------------------------------------
  !  A is symetric positive definite matrix in lower triangular form
  !  L is the cholesky decomposition in lower triangular form
  ! --------------------------------------------------------------------------
  REAL(8) :: sum
  REAL(8) :: sumd1_re
  INTEGER(4) :: ci,cj,ck
  INTRINSIC SQRT
  ci = 1
  pld1_re = 0.0
  
  DO WHILE (ci.LE.nsize)
    sumd1_re = pad1_re(ci,ci)
    sum = pa(ci,ci)
    cj = 1
    
    DO WHILE (cj.LE.ci - 1)
      sumd1_re = sumd1_re - pld1_re(ci,cj) * pl(ci,cj) - pl(ci,cj) * pl&
      &d1_re(ci,cj)
      sum = sum - pl(ci,cj) * pl(ci,cj)
      cj = cj + 1
    ENDDO 
    
    
    IF (sum.EQ.0.0) THEN
    
      pld1_re(ci,ci) = 0.0
      
    ELSE 
    
      pld1_re(ci,ci) = sumd1_re / (2.0 * SQRT(sum))
      
    ENDIF 
    
    pl(ci,ci) = SQRT(sum)
    cj = ci + 1
    
    DO WHILE (cj.LE.nsize)
      sumd1_re = pad1_re(cj,ci)
      sum = pa(cj,ci)
      ck = 1
      
      DO WHILE (ck.LE.ci - 1)
        sumd1_re = sumd1_re - pld1_re(ci,ck) * pl(cj,ck) - pl(ci,ck) * &
        &pld1_re(cj,ck)
        sum = sum - pl(ci,ck) * pl(cj,ck)
        ck = ck + 1
      ENDDO 
      
      pld1_re(cj,ci) = (sumd1_re * pl(ci,ci) - sum * pld1_re(ci,ci)) / &
      &pl(ci,ci)**2
      pl(cj,ci) = sum / pl(ci,ci)
      cj = cj + 1
    ENDDO 
    
    ci = ci + 1
  ENDDO 
  
  
ENDSUBROUTINE R_REDEV__CHOLESKYDECOMPOSITION_DRE

!  Differentiation of r_redev__loglikelihood_bre_dre in forward (tangent) mode:
!   variations   of useful results: par_u reb1_red2_re /adstack_r8/[0,inf[
!   with respect to varying inputs: par_u re /adstack_r8/[0,inf[
!  Differentiation of redev__loglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: reb1_re
!   with respect to varying inputs: re
!   RW status of diff variables: par_ub1_re:(loc) y:(loc) yb1_re:(loc)
!                par_u:(loc) reb1_re:out re:in
!  Differentiation of redev__loglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__loglikelihood
!   with respect to varying inputs: re
!   RW status of diff variables: y:(loc) par_u:(loc) redev__loglikelihood:in-killed
!                re:out
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDEV__LOGLIKELIHOOD_BRE_DRE_DRE(re,red1_re,red2_re,reb1_r&
&e,reb1_red2_re,reb1_red2_red1_re,par,loglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: re(nr)
  REAL(8) , INTENT (IN):: red1_re(nr)
  REAL(8) , INTENT (IN):: red2_re(nr)
  REAL(8) :: reb1_re(nr)
  REAL(8) :: reb1_red2_re(nr)
  REAL(8) :: reb1_red2_red1_re(nr)
  REAL(8) , INTENT (IN):: par(np)
  USE COMMON
  REAL(8) :: dlikelihoodb1_re
  INTEGER(4) :: cn
  INTEGER(4) :: cm
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  REAL(8) :: loglikelihoodb1_re
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  !  Copy over random effects
  cm = 1
  cn = 0
  ad_count = 0
  par_ud2_re = 0.0
  
  DO WHILE (cn.LT.nr)
    par_ud2_re(cm) = red2_re(cm)
    par_ud1_re(cm) = red1_re(cm)
    par_u(cm) = re(cm)
    CALL PUSHINTEGER4(cm)
    cm = cm + 1
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  !  Copy over parameters
  cm = 1
  par_logr0 = par(cm)
  cm = cm + 1
  par_logtheta = par(cm)
  cm = cm + 1
  par_logk = par(cm)
  cm = cm + 1
  par_logq = par(cm)
  cm = cm + 1
  par_logr = par(cm)
  !  Call likelihood function
  dlikelihoodb1_re = loglikelihoodb1_re
  CALL R_REDEV__THETALOGLIKELIHOOD_BRE_DRE_DRE(par_u,par_ud1_re,par_ud2&
  &_re,par_ud2_red1_re,par_ub1_re,par_ub1_red1_re,par_ub1_red2_re,par_u&
  &b1_red2_red1_re,par_logr0,par_logtheta,par_logk,par_logq,par_logr,dl&
  &ikelihoodb1_re)
  reb1_re = 0.0
  CALL POPINTEGER4(ad_count)
  reb1_red2_re = 0.0
  reb1_red2_red1_re = 0.0
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cm)
    reb1_red2_red1_re(cm) = reb1_red2_red1_re(cm) + par_ub1_red2_red1_r&
    &e(cm)
    reb1_red2_re(cm) = reb1_red2_re(cm) + par_ub1_red2_re(cm)
    reb1_re(cm) = reb1_re(cm) + par_ub1_re(cm)
    par_ub1_red2_red1_re(cm) = 0.0
    par_ub1_red2_re(cm) = 0.0
    par_ub1_re(cm) = 0.0
  ENDDO 
  
  
ENDSUBROUTINE R_REDEV__LOGLIKELIHOOD_BRE_DRE_DRE

!  Differentiation of r_redev__thetaloglikelihood_bre_dre in forward (tangent) mode:
!   variations   of useful results: ub1_red2_re /adstack_r8/[0,inf[
!   with respect to varying inputs: u /adstack_r8/[0,inf[
!  Differentiation of redev__thetaloglikelihood_bre in forward (tangent) mode:
!   variations   of useful results: ub1_re
!   with respect to varying inputs: u
!  Differentiation of redev__thetaloglikelihood in reverse (adjoint) mode:
!   gradient     of useful results: redev__thetaloglikelihood
!   with respect to varying inputs: u
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDEV__THETALOGLIKELIHOOD_BRE_DRE_DRE(u,ud1_re,ud2_re,ud2_&
&red1_re,ub1_re,ub1_red1_re,ub1_red2_re,ub1_red2_red1_re,logr0,logtheta&
&,logk,logq,logr,thetaloglikelihoodb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: u(n)
  REAL(8) , INTENT (IN):: ud1_re(n)
  REAL(8) , INTENT (IN):: ud2_re(n)
  REAL(8) , INTENT (IN):: ud2_red1_re(n)
  REAL(8) :: ub1_re(n)
  REAL(8) :: ub1_red1_re(n)
  REAL(8) :: ub1_red2_re(n)
  REAL(8) :: ub1_red2_red1_re(n)
  REAL(8) , INTENT (IN):: logr0
  REAL(8) , INTENT (IN):: logtheta
  REAL(8) , INTENT (IN):: logk
  REAL(8) , INTENT (IN):: logq
  REAL(8) , INTENT (IN):: logr
  USE COMMON
  REAL(8) :: mean
  REAL(8) :: meand1_re
  REAL(8) :: meand2_re
  REAL(8) :: meand2_red1_re
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red1_re
  REAL(8) :: meanb1_red2_re
  REAL(8) :: meanb1_red2_red1_re
  REAL(8) :: r0
  REAL(8) :: theta
  REAL(8) :: k
  REAL(8) :: q
  REAL(8) :: r
  REAL(8) :: llb1_re
  INTEGER(4) :: cn
  INTRINSIC EXP
  INTRINSIC SQRT
  REAL(8) :: arg1
  REAL(8) :: arg1d1_re
  REAL(8) :: arg1d2_re
  REAL(8) :: arg1d2_red1_re
  REAL(8) :: result1b1_re
  INTEGER(4) :: ad_count
  INTEGER(4) :: i
  INTEGER(4) :: ad_count0
  INTEGER(4) :: i0
  REAL(8) :: thetaloglikelihoodb1_re
  EXTERNAL PUSHREAL8
  EXTERNAL PUSHREAL8_d
  EXTERNAL PUSHREAL8_D
  EXTERNAL PUSHINTEGER4
  EXTERNAL POPINTEGER4
  EXTERNAL POPREAL8
  EXTERNAL POPREAL8_d
  EXTERNAL POPREAL8_D
  INTRINSIC INT
  REAL(8) :: pwx1
  REAL(8) :: pwx1d1_re
  REAL(8) :: pwx1d2_re
  REAL(8) :: pwx1d2_red1_re
  REAL(8) :: pwr1
  REAL(8) :: pwr1d1_re
  REAL(8) :: pwr1d2_re
  REAL(8) :: pwr1d2_red1_re
  REAL(8) :: pwy1
  REAL(8) :: pwy10
  REAL(8) :: pwr10
  REAL(8) :: pwr10d1_re
  meanb1_red1_re = 0
  mean = 0
  arg1 = 0
  r0 = EXP(logr0)
  theta = EXP(logtheta)
  k = EXP(logk)
  q = EXP(logq)
  r = EXP(logr)
  cn = 2
  ad_count = 0
  meand2_re = 0.0
  meand2_red1_re = 0.0
  meand1_re = 0.0
  
  DO WHILE (cn.LE.n)
    CALL PUSHREAL8(mean)
    CALL PUSHREAL8(meand1_re)
    CALL PUSHREAL8(meand2_re)
    CALL PUSHREAL8(meand2_red1_re)
    pwx1d2_red1_re = ud2_re(cn - 1) * ud1_re(cn - 1) * EXP(u(cn - 1)) /&
    & k
    pwx1d2_re = ud2_re(cn - 1) * EXP(u(cn - 1)) / k
    pwx1d1_re = ud1_re(cn - 1) * EXP(u(cn - 1)) / k
    pwx1 = EXP(u(cn - 1)) / k
    
    IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.theta.EQ.INT(theta))) THEN
    
      pwy10 = theta - 1
      
      IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.pwy10.EQ.INT(pwy10))) THEN
      
        pwr10d1_re = pwy10 * pwx1**(pwy10 - 1) * pwx1d1_re
        
      ELSEIF (pwx1.EQ.0.0.AND.pwy10.EQ.1.0) THEN 
      
        pwr10d1_re = pwx1d1_re
        
      ELSE 
      
        pwr10d1_re = 0.0
        
      ENDIF 
      
      pwr10 = pwx1**pwy10
      pwr1d2_red1_re = theta * (pwr10d1_re * pwx1d2_re + pwr10 * pwx1d2&
      &_red1_re)
      pwr1d2_re = theta * pwr10 * pwx1d2_re
      
    ELSEIF (pwx1.EQ.0.0.AND.theta.EQ.1.0) THEN 
    
      pwr1d2_red1_re = pwx1d2_red1_re
      pwr1d2_re = pwx1d2_re
      
    ELSE 
    
      pwr1d2_re = 0.0
      pwr1d2_red1_re = 0.0
      
    ENDIF 
    
    
    IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.theta.EQ.INT(theta))) THEN
    
      pwr1d1_re = theta * pwx1**(theta - 1) * pwx1d1_re
      
    ELSEIF (pwx1.EQ.0.0.AND.theta.EQ.1.0) THEN 
    
      pwr1d1_re = pwx1d1_re
      
    ELSE 
    
      pwr1d1_re = 0.0
      
    ENDIF 
    
    pwr1 = pwx1**theta
    meand2_red1_re = -(r0 * pwr1d2_red1_re)
    meand2_re = ud2_re(cn - 1) - r0 * pwr1d2_re
    meand1_re = ud1_re(cn - 1) - r0 * pwr1d1_re
    mean = u(cn - 1) + r0 * (1.0 - pwr1)
    arg1d2_re = 0.0
    arg1d1_re = 0.0
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d1_re)
    arg1d2_red1_re = 0.0
    CALL PUSHREAL8(arg1d2_re)
    CALL PUSHREAL8(arg1d2_red1_re)
    arg1 = SQRT(q)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count = ad_count + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count)
  cn = 1
  ad_count0 = 0
  
  DO WHILE (cn.LE.n)
    arg1d2_re = 0.0
    arg1d1_re = 0.0
    CALL PUSHREAL8(arg1)
    CALL PUSHREAL8(arg1d1_re)
    arg1d2_red1_re = 0.0
    CALL PUSHREAL8(arg1d2_re)
    CALL PUSHREAL8(arg1d2_red1_re)
    arg1 = SQRT(r)
    CALL PUSHINTEGER4(cn)
    cn = cn + 1
    ad_count0 = ad_count0 + 1
  ENDDO 
  
  CALL PUSHINTEGER4(ad_count0)
  llb1_re = thetaloglikelihoodb1_re
  ub1_re = 0.0
  CALL POPINTEGER4(ad_count0)
  ub1_red2_re = 0.0
  arg1d2_re = 0.0
  ub1_red2_red1_re = 0.0
  arg1d2_red1_re = 0.0
  arg1d1_re = 0.0
  
  DO i0 = 1,ad_count0
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    yb1_re = 0.0
    yb1_red2_re = 0.0
    yd2_re = 0.0
    ud2_red1_re = 0.0
    yb1_red2_red1_re = 0.0
    yd1_re = 0.0
    CALL R_REDEV__DLOGNORM_BRE_DRE_DRE(y(cn),yd1_re(cn),yd2_re(cn),yb1_&
    &re(cn),yb1_red2_re(cn),yb1_red2_red1_re(cn),u(cn),ud1_re(cn),ud2_r&
    &e(cn),ud2_red1_re(cn),ub1_re(cn),ub1_red1_re(cn),ub1_red2_re(cn),u&
    &b1_red2_red1_re(cn),arg1,arg1d1_re,arg1d2_re,arg1d2_red1_re,result&
    &1b1_re)
    CALL POPREAL8(arg1d2_red1_re)
    CALL POPREAL8(arg1d2_re)
    CALL POPREAL8(arg1d1_re)
    CALL POPREAL8(arg1)
  ENDDO 
  
  CALL POPINTEGER4(ad_count)
  
  DO i = 1,ad_count
    CALL POPINTEGER4(cn)
    result1b1_re = -llb1_re
    meanb1_re = 0.0
    meanb1_red2_re = 0.0
    meanb1_red2_red1_re = 0.0
    CALL R_REDEV__DLOGNORM_BRE_DRE_DRE(u(cn),ud1_re(cn),ud2_re(cn),ub1_&
    &re(cn),ub1_red2_re(cn),ub1_red2_red1_re(cn),mean,meand1_re,meand2_&
    &re,meand2_red1_re,meanb1_re,meanb1_red1_re,meanb1_red2_re,meanb1_r&
    &ed2_red1_re,arg1,arg1d1_re,arg1d2_re,arg1d2_red1_re,result1b1_re)
    CALL POPREAL8(arg1d2_red1_re)
    CALL POPREAL8(arg1d2_re)
    CALL POPREAL8(arg1d1_re)
    CALL POPREAL8(arg1)
    CALL POPREAL8(meand2_red1_re)
    CALL POPREAL8(meand2_re)
    CALL POPREAL8(meand1_re)
    CALL POPREAL8(mean)
    
    IF (EXP(u(cn - 1)) / k.LE.0.0.AND.(theta.EQ.0.0.OR.theta.NE.INT(the&
    &ta))) THEN
    
      ub1_red2_red1_re(cn - 1) = ub1_red2_red1_re(cn - 1) + meanb1_red2&
      &_red1_re
      ub1_red2_re(cn - 1) = ub1_red2_re(cn - 1) + meanb1_red2_re
      ub1_re(cn - 1) = ub1_re(cn - 1) + meanb1_re
      
    ELSE 
    
      pwx1d2_red1_re = ud2_re(cn - 1) * ud1_re(cn - 1) * EXP(u(cn - 1))&
      & / k
      pwx1d2_re = ud2_re(cn - 1) * EXP(u(cn - 1)) / k
      pwx1d1_re = ud1_re(cn - 1) * EXP(u(cn - 1)) / k
      pwx1 = EXP(u(cn - 1)) / k
      pwy1 = theta - 1
      
      IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.pwy1.EQ.INT(pwy1))) THEN
      
        pwy10 = pwy1 - 1
        
        IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.pwy10.EQ.INT(pwy10))) THEN
        
          pwr10d1_re = pwy10 * pwx1**(pwy10 - 1) * pwx1d1_re
          
        ELSEIF (pwx1.EQ.0.0.AND.pwy10.EQ.1.0) THEN 
        
          pwr10d1_re = pwx1d1_re
          
        ELSE 
        
          pwr10d1_re = 0.0
          
        ENDIF 
        
        pwr10 = pwx1**pwy10
        pwr1d2_red1_re = pwy1 * (pwr10d1_re * pwx1d2_re + pwr10 * pwx1d&
        &2_red1_re)
        pwr1d2_re = pwy1 * pwr10 * pwx1d2_re
        
      ELSEIF (pwx1.EQ.0.0.AND.pwy1.EQ.1.0) THEN 
      
        pwr1d2_red1_re = pwx1d2_red1_re
        pwr1d2_re = pwx1d2_re
        
      ELSE 
      
        pwr1d2_re = 0.0
        pwr1d2_red1_re = 0.0
        
      ENDIF 
      
      
      IF (pwx1.GT.0.0.OR.(pwx1.LT.0.0.AND.pwy1.EQ.INT(pwy1))) THEN
      
        pwr1d1_re = pwy1 * pwx1**(pwy1 - 1) * pwx1d1_re
        
      ELSEIF (pwx1.EQ.0.0.AND.pwy1.EQ.1.0) THEN 
      
        pwr1d1_re = pwx1d1_re
        
      ELSE 
      
        pwr1d1_re = 0.0
        
      ENDIF 
      
      pwr1 = pwx1**pwy1
      ub1_red2_red1_re(cn - 1) = ub1_red2_red1_re(cn - 1) + (1.0 - thet&
      &a * pwr1 * r0 * EXP(u(cn - 1)) / k) * meanb1_red2_red1_re - thet&
      &a * r0 * (pwr1d1_re * EXP(u(cn - 1)) + pwr1 * ud1_re(cn - 1) * E&
      &XP(u(cn - 1))) * meanb1_red2_re / k - theta * r0 * ((pwr1d2_red1&
      &_re * EXP(u(cn - 1)) + pwr1d2_re * ud1_re(cn - 1) * EXP(u(cn - 1&
      &)) + ud2_re(cn - 1) * (pwr1d1_re * EXP(u(cn - 1)) + pwr1 * ud1_r&
      &e(cn - 1) * EXP(u(cn - 1)))) * meanb1_re + (pwr1d2_re * EXP(u(cn&
      & - 1)) + pwr1 * ud2_re(cn - 1) * EXP(u(cn - 1))) * meanb1_red1_r&
      &e) / k
      ub1_red2_re(cn - 1) = ub1_red2_re(cn - 1) + (1.0 - theta * pwr1 *&
      & r0 * EXP(u(cn - 1)) / k) * meanb1_red2_re - theta * r0 * (pwr1d&
      &2_re * EXP(u(cn - 1)) + pwr1 * ud2_re(cn - 1) * EXP(u(cn - 1))) &
      &* meanb1_re / k
      ub1_re(cn - 1) = ub1_re(cn - 1) + (1.0 - theta * pwr1 * r0 * EXP(&
      &u(cn - 1)) / k) * meanb1_re
      
    ENDIF 
    
  ENDDO 
  
  
ENDSUBROUTINE R_REDEV__THETALOGLIKELIHOOD_BRE_DRE_DRE

!  Differentiation of r_redev__dlognorm_bre_dre in forward (tangent) mode:
!   variations   of useful results: meanb1_red2_re meanb1_re xb1_red2_re
!   with respect to varying inputs: x sigma meanb1_red2_re sigmad2_re
!                meand2_re xb1_red2_re mean
!  Differentiation of redev__dlognorm_bre in forward (tangent) mode:
!   variations   of useful results: meanb1_re xb1_re
!   with respect to varying inputs: x sigma meanb1_re xb1_re mean
!  Differentiation of redev__dlognorm in reverse (adjoint) mode:
!   gradient     of useful results: x redev__dlognorm mean
!   with respect to varying inputs: x mean
!  ----------------------------------------------------------------------------
SUBROUTINE R_REDEV__DLOGNORM_BRE_DRE_DRE(x,xd1_re,xd2_re,xb1_re,xb1_red&
&2_re,xb1_red2_red1_re,mean,meand1_re,meand2_re,meand2_red1_re,meanb1_r&
&e,meanb1_red1_re,meanb1_red2_re,meanb1_red2_red1_re,sigma,sigmad1_re,s&
&igmad2_re,sigmad2_red1_re,dlognormb1_re)

  IMPLICIT NONE
  REAL(8) , INTENT (IN):: x
  REAL(8) , INTENT (IN):: xd1_re
  REAL(8) , INTENT (IN):: xd2_re
  REAL(8) :: xb1_re
  REAL(8) :: xb1_red2_re
  REAL(8) :: xb1_red2_red1_re
  REAL(8) , INTENT (IN):: mean
  REAL(8) , INTENT (IN):: meand1_re
  REAL(8) , INTENT (IN):: meand2_re
  REAL(8) , INTENT (IN):: meand2_red1_re
  REAL(8) :: meanb1_re
  REAL(8) :: meanb1_red1_re
  REAL(8) :: meanb1_red2_re
  REAL(8) :: meanb1_red2_red1_re
  REAL(8) , INTENT (IN):: sigma
  REAL(8) , INTENT (IN):: sigmad1_re
  REAL(8) , INTENT (IN):: sigmad2_re
  REAL(8) , INTENT (IN):: sigmad2_red1_re
  USE COMMON
  REAL(8) :: dvalueb1_re
  INTRINSIC LOG
  REAL(8) :: dlognormb1_re
  REAL(8) :: tempb1_re
  REAL(8) :: tempb1_red1_re
  REAL(8) :: tempb1_red2_re
  REAL(8) :: tempb1_red2_red1_re
  dvalueb1_re = dlognormb1_re
  tempb1_red2_red1_re = -(((2.0 * 0.5 * dvalueb1_re * ((xd2_re - meand2&
  &_re) * 2 * sigma * sigmad1_re - meand2_red1_re * sigma**2) - 2.0 * 0&
  &.5 * dvalueb1_re * 2 * ((xd1_re - meand1_re) * sigma * sigmad2_re + &
  &(x - mean) * (sigmad1_re * sigmad2_re + sigma * sigmad2_red1_re))) *&
  & sigma**4 - (2.0 * 0.5 * dvalueb1_re * (xd2_re - meand2_re) * sigma*&
  &*2 - 2.0 * (x - mean) * 0.5 * dvalueb1_re * 2 * sigma * sigmad2_re) &
  &* 2**2 * sigma**3 * sigmad1_re) / ((sigma**2)**2)**2)
  tempb1_red2_re = -((2.0 * 0.5 * dvalueb1_re * (xd2_re - meand2_re) * &
  &sigma**2 - 2.0 * (x - mean) * 0.5 * dvalueb1_re * 2 * sigma * sigmad&
  &2_re) / (sigma**2)**2)
  tempb1_red1_re = -((2.0 * 0.5 * dvalueb1_re * (xd1_re - meand1_re) * &
  &sigma**2 - 2.0 * (x - mean) * 0.5 * dvalueb1_re * 2 * sigma * sigmad&
  &1_re) / (sigma**2)**2)
  tempb1_re = -(2.0 * (x - mean) * 0.5 * dvalueb1_re / sigma**2)
  xb1_red2_red1_re = xb1_red2_red1_re + tempb1_red2_red1_re
  xb1_red2_re = xb1_red2_re + tempb1_red2_re
  xb1_re = xb1_re + tempb1_re
  meanb1_red2_red1_re = meanb1_red2_red1_re - tempb1_red2_red1_re
  meanb1_red2_re = meanb1_red2_re - tempb1_red2_re
  meanb1_red1_re = -tempb1_red1_re
  meanb1_re = meanb1_re - tempb1_re
  
ENDSUBROUTINE R_REDEV__DLOGNORM_BRE_DRE_DRE

