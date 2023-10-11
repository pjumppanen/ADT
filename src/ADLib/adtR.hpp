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

#define R_NO_REMAP

#include "adtarrays.hpp"
#include <R_ext/Rdynload.h>
#include <Rinternals.h>


//  ----------------------------------------------------------------------------
//  MACRO to force inclusion of R interface code in Linkage process
//  ----------------------------------------------------------------------------
#define INCLUDE_R_INTERFACE   void* GlobalR_ADLibDebug = (void*)R_ADLibDebug;


//  ----------------------------------------------------------------------------
//  R_CALLARG class
//  ----------------------------------------------------------------------------
class R_CALLARG
{
private:
  char*       Array;
  AdtVarType  VarType;
  bool        IsScalar;

public:
  R_CALLARG(const int& nValue);
  R_CALLARG(const double& dValue);

  R_CALLARG(const ARRAY_1D pArray);
  R_CALLARG(const ARRAY_2D pArray);
  R_CALLARG(const ARRAY_3D pArray);
  R_CALLARG(const ARRAY_4D pArray);
  R_CALLARG(const ARRAY_5D pArray);
  R_CALLARG(const ARRAY_6D pArray);
  R_CALLARG(const ARRAY_7D pArray);
  R_CALLARG(const ARRAY_8D pArray);
  R_CALLARG(const ARRAY_9D pArray);
  R_CALLARG(const ARRAY_10D pArray);

  R_CALLARG(const ARRAY_1I pArray);
  R_CALLARG(const ARRAY_2I pArray);
  R_CALLARG(const ARRAY_3I pArray);
  R_CALLARG(const ARRAY_4I pArray);
  R_CALLARG(const ARRAY_5I pArray);
  R_CALLARG(const ARRAY_6I pArray);
  R_CALLARG(const ARRAY_7I pArray);
  R_CALLARG(const ARRAY_8I pArray);
  R_CALLARG(const ARRAY_9I pArray);
  R_CALLARG(const ARRAY_10I pArray);

  SEXP  wrapArgument(const AdtMemAllocator& rMemAllocator,
                     bool bNoTranslation,
                     int& nProtect);
};

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const int& nValue)
{
  Array     = (char*)&nValue;
  VarType   = AdtVarType_INT;
  IsScalar  = true;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const double& dValue)
{
  Array     = (char*)&dValue;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = true;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_1D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_2D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_3D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_4D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_5D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_6D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_7D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_8D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_9D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_10D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_1I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_2I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_3I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_4I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_5I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_6I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_7I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_8I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_9I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}

//  ----------------------------------------------------------------------------

inline R_CALLARG::R_CALLARG(const ARRAY_10I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
}


//  ----------------------------------------------------------------------------
//  R_RETARG class
//  ----------------------------------------------------------------------------
class R_RETARG
{
private:
  char*       Array;
  AdtVarType  VarType;
  SEXPTYPE    RType;
  bool        IsScalar;

public:
  R_RETARG(int& nValue);
  R_RETARG(double& dValue);

  R_RETARG(ARRAY_1D pArray);
  R_RETARG(ARRAY_2D pArray);
  R_RETARG(ARRAY_3D pArray);
  R_RETARG(ARRAY_4D pArray);
  R_RETARG(ARRAY_5D pArray);
  R_RETARG(ARRAY_6D pArray);
  R_RETARG(ARRAY_7D pArray);
  R_RETARG(ARRAY_8D pArray);
  R_RETARG(ARRAY_9D pArray);
  R_RETARG(ARRAY_10D pArray);

  R_RETARG(ARRAY_1I pArray);
  R_RETARG(ARRAY_2I pArray);
  R_RETARG(ARRAY_3I pArray);
  R_RETARG(ARRAY_4I pArray);
  R_RETARG(ARRAY_5I pArray);
  R_RETARG(ARRAY_6I pArray);
  R_RETARG(ARRAY_7I pArray);
  R_RETARG(ARRAY_8I pArray);
  R_RETARG(ARRAY_9I pArray);
  R_RETARG(ARRAY_10I pArray);

  void        assign(SEXP Result,
                     const AdtMemAllocator& rMemAllocator,
                     bool bNoTranslation,
                     int& nProtect);

  SEXPTYPE    type() const;
};

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(int& nValue)
{
  Array     = (char*)&nValue;
  VarType   = AdtVarType_INT;
  IsScalar  = true;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(double& dValue)
{
  Array     = (char*)&dValue;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = true;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_1D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_2D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_3D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_4D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_5D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_6D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_7D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_8D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_9D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_10D pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_DOUBLE;
  IsScalar  = false;
  RType     = REALSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_1I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_2I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_3I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_4I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_5I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_6I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_7I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_8I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_9I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline R_RETARG::R_RETARG(ARRAY_10I pArray)
{
  Array     = (char*)pArray;
  VarType   = AdtVarType_INT;
  IsScalar  = false;
  RType     = INTSXP;
}

//  ----------------------------------------------------------------------------

inline SEXPTYPE R_RETARG::type() const
{
  return (RType);
}


//  ----------------------------------------------------------------------------
//  R_CALL class
//  ----------------------------------------------------------------------------
class R_CALL
{
private:
  bool                    Valid;
  SEXP                    Function;
  SEXP                    Environment;
  bool                    NoTranslation;
  const AdtMemAllocator*  MemAllocator;
  
protected:
  void                    callR(R_RETARG& ret, R_CALLARG* Arguments[], int nArguments);
  SEXP                    langN(int nArguments) const;

public:
  R_CALL();
  R_CALL(SEXP func, SEXP env, bool bNoTranslation, const AdtMemAllocator& rAllocator);
  R_CALL(const R_CALL& rCopy);
  ~R_CALL();

  void                    initialise(SEXP func, SEXP env, bool bNoTranslation, const AdtMemAllocator& rAllocator);

  void                    operator () (R_RETARG ret);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4, 
                                       R_CALLARG arg5);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4, 
                                       R_CALLARG arg5, 
                                       R_CALLARG arg6);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4, 
                                       R_CALLARG arg5, 
                                       R_CALLARG arg6, 
                                       R_CALLARG arg7);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4, 
                                       R_CALLARG arg5, 
                                       R_CALLARG arg6, 
                                       R_CALLARG arg7, 
                                       R_CALLARG arg8);

  void                    operator () (R_RETARG ret, 
                                       R_CALLARG arg0, 
                                       R_CALLARG arg1, 
                                       R_CALLARG arg2, 
                                       R_CALLARG arg3, 
                                       R_CALLARG arg4, 
                                       R_CALLARG arg5, 
                                       R_CALLARG arg6, 
                                       R_CALLARG arg7, 
                                       R_CALLARG arg8, 
                                       R_CALLARG arg9);
};


//  ----------------------------------------------------------------------------
//  Cast of R LOGICAL to LONGBOOL. Dodgy but LOGICAL's are of type int and
//  longbool is a union of int. Therefore the memory layout of longbool and int
//  should, in theory at least, be exactly the same. Hence we should be able to
//  cast an int* to a longbool*. Put it in a function so we can debug it if
//  something goes wrong.
//  ----------------------------------------------------------------------------
longbool* LONGBOOL(SEXP x);


//  ----------------------------------------------------------------------------
//  Cast of R RAW to bool
//  ----------------------------------------------------------------------------
bool* RAWBOOL(SEXP x);


//  ----------------------------------------------------------------------------
//  Cast of R RAW to char
//  ----------------------------------------------------------------------------
char* RAWCHAR(SEXP x);


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

SEXP R_Scalar(const longbool& lbResult);

SEXP R_Scalar(const char& cResult);

SEXP R_Empty();


enum R_UseArrayClass
{
  ArrayClass_offarray = 0,
  ArrayClass_Oarray   = 1,
};


void R_SetArrayClass(R_UseArrayClass nClass);

inline Rboolean Rf_isIntegerOrFactor(SEXP sIntExp)
{
  return ((Rboolean)(Rf_isInteger(sIntExp) | Rf_isFactor(sIntExp)));
}


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
