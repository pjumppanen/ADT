//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    adtR.hpp
//
//  Purpose:
//    This file includes declarations of R interface related code for the
//    ADLib library.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTR_HPP__
#define __ADTR_HPP__


#ifndef AD


#include "adtarrays.hpp"
#include <R_ext/Rdynload.h>
#include <Rinternals.h>


//  ----------------------------------------------------------------------------
//  MACRO to force inclusion of R interface code in Linkage process
//  ----------------------------------------------------------------------------
#define INCLUDE_R_INTERFACE   void* GlobalR_ADLibDebug = (void*)R_ADLibDebug;


//  ----------------------------------------------------------------------------
//  Template functions to determine R type from array type
//  ----------------------------------------------------------------------------
template<class T> inline SEXPTYPE RType(T Array){ return (NILSXP); };

template<> inline SEXPTYPE RType<ARRAY_1I>(ARRAY_1I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_2I>(ARRAY_2I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_3I>(ARRAY_3I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_4I>(ARRAY_4I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_5I>(ARRAY_5I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_6I>(ARRAY_6I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_7I>(ARRAY_7I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_8I>(ARRAY_8I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_9I>(ARRAY_9I Array){ return (INTSXP); };
template<> inline SEXPTYPE RType<ARRAY_10I>(ARRAY_10I Array){ return (INTSXP); };

template<> inline SEXPTYPE RType<ARRAY_1D>(ARRAY_1D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_2D>(ARRAY_2D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_3D>(ARRAY_3D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_4D>(ARRAY_4D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_5D>(ARRAY_5D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_6D>(ARRAY_6D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_7D>(ARRAY_7D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_8D>(ARRAY_8D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_9D>(ARRAY_9D Array){ return (REALSXP); };
template<> inline SEXPTYPE RType<ARRAY_10D>(ARRAY_10D Array){ return (REALSXP); };

//  ----------------------------------------------------------------------------

template<class T> inline const char* RTypeName(T Array){ return ("NILSXP"); };

template<> inline const char* RTypeName<ARRAY_1I>(ARRAY_1I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_2I>(ARRAY_2I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_3I>(ARRAY_3I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_4I>(ARRAY_4I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_5I>(ARRAY_5I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_6I>(ARRAY_6I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_7I>(ARRAY_7I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_8I>(ARRAY_8I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_9I>(ARRAY_9I Array){ return ("INTSXP"); };
template<> inline const char* RTypeName<ARRAY_10I>(ARRAY_10I Array){ return ("INTSXP"); };

template<> inline const char* RTypeName<ARRAY_1D>(ARRAY_1D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_2D>(ARRAY_2D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_3D>(ARRAY_3D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_4D>(ARRAY_4D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_5D>(ARRAY_5D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_6D>(ARRAY_6D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_7D>(ARRAY_7D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_8D>(ARRAY_8D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_9D>(ARRAY_9D Array){ return ("REALSXP"); };
template<> inline const char* RTypeName<ARRAY_10D>(ARRAY_10D Array){ return ("REALSXP"); };


//  ----------------------------------------------------------------------------
//  R Interface helper functions used to simplify interface code
//  ----------------------------------------------------------------------------
SEXP R_ImplGetter(const AdtMemAllocator& rAllocator,
                  bool bNoTranslation,
                  char* pArray,
                  const char* pName,
                  SEXP sArgList,
                  const char* pFileName,
                  int nLineNumber);

SEXP R_ImplSetter(const AdtMemAllocator& rAllocator,
                  bool bNoTranslation,
                  char* pArray,
                  const char* pName,
                  SEXP sSrcArg,
                  SEXP sArgList,
                  const char* pFileName,
                  int nLineNumber);

void R_CheckArgument(const char* pName,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber,
                     int nDims,
                     AdtArrayCoord* pCoords,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType);

void R_CheckArgument(const char* pName,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber,
                     int nDims,
                     ...);

void R_CheckArgument(const char* pName,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber);

SEXP R_CreateArray(int nDims, AdtArrayCoord* pCoords, SEXPTYPE nType);

SEXP R_CreateArray(int nDims, SEXPTYPE nType, ...);

SEXP R_Scalar(const int& nResult);

SEXP R_Scalar(const double& dResult);

SEXP R_Empty();


#include <R_ext/Applic.h>


// Minimisers borrowed from R and made thread safe
void ts_vmmin(int n0, double *b, double *Fmin, optimfn fminfn, optimgr fmingr,
              int maxit, int trace, int *mask,
              double abstol, double reltol, int nREPORT, void *ex,
              int *fncount, int *grcount, int *fail);

void ts_nmmin(int n, double *Bvec, double *X, double *Fmin, optimfn fminfn,
              int *fail, double abstol, double intol, void *ex,
              double alpha, double bet, double gamm, int trace,
              int *fncount, int maxit);

void ts_cgmin(int n, double *Bvec, double *X, double *Fmin,
              optimfn fminfn, optimgr fmingr, int *fail,
              double abstol, double intol, void *ex, int type, int trace,
              int *fncount, int *grcount, int maxit);

void ts_lbfgsb(int n, int m, double *x, double *l, double *u, int *nbd,
               double *Fmin, optimfn fminfn, optimgr fmingr, int *fail,
               void *ex, double factr, double pgtol,
               int *fncount, int *grcount, int maxit, char *msg,
               int trace, int nREPORT);


#endif //AD

#endif //__ADTR_HPP__
