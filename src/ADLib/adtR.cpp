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
//    adtR.cpp
//
//  Purpose:
//    This file includes implementations of R interface related code for the
//    ADLib library.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtR.hpp"
#include <stdarg.h>


//  ----------------------------------------------------------------------------
//  R Interface helper functions used to simplify interface code
//  ----------------------------------------------------------------------------
static SEXP DropNegativeSymbol  = NULL;
static SEXP OffsetSymbol        = NULL;

//  ----------------------------------------------------------------------------

bool ReadIndices(SEXP sArgList, int* pIndices, unsigned int nArgs, unsigned int& rErrorIndex)
{
  bool bRead = true;

  // Read indices from argument list
  for (unsigned int cn = 0 ; cn < nArgs ; cn++)
  {
    SEXP Element = VECTOR_ELT(sArgList, cn);

    if (Rf_isInteger(Element))
    {
      pIndices[cn] = INTEGER(Element)[0];
    }
    else if (Rf_isReal(Element))
    {
      double dVal = REAL(Element)[0];
      int    nVal = int(dVal);

      if ((dVal - nVal) != 0)
      {
        bRead       = false;
        rErrorIndex = cn;
        break;
      }
      else
      {
        pIndices[cn] = nVal;
      }
    }
    else
    {
      bRead       = false;
      rErrorIndex = cn;
      break;
    }
  }

  return (bRead);
}

//  ----------------------------------------------------------------------------

SEXP R_ImplGetter(const AdtMemAllocator& rAllocator,
                  bool bNoTranslation,
                  char* pArray,
                  const char* pName,
                  SEXP sArgList,
                  const char* pFileName,
                  int nLineNumber)
{
  SEXP  Result = {0};

  if (Rf_isNewList(sArgList))
  {
    unsigned int  nErrorIndex;
    unsigned int  nArgs                       = Rf_length(sArgList);
    int           aIndices[ADLIB_MAX_COORDS]  = {0};
    AdtArrayCoord aCoords[ADLIB_MAX_COORDS]   = {0};
    AdtArrayInfo* pInfo                       = AdtArrayPlanActor::arrayInfo(rAllocator, pArray);
    unsigned int  nCoords                     = pInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

    if ((nArgs > nCoords) || (nArgs > ADLIB_MAX_COORDS))
    {
      Rf_error("ERROR: Too many arguments in list of arguments passed in call to getter for %s. See line %d in file %s", pName, nLineNumber, pFileName);
    }

    // Read indices from argument list
    if (!ReadIndices(sArgList, aIndices, nArgs, nErrorIndex))
    {
      Rf_error("ERROR: Indexing argument %d in the getter argument list is not an integer for %s. See line %d in file %s", pName, nErrorIndex + 1, nLineNumber, pFileName);
    }

    if ((pInfo->VarType != AdtVarType_INT) && (pInfo->VarType != AdtVarType_DOUBLE))
    {
      std::runtime_error("R_ImplGetter called on array of type not supported in R\n");
    }
    else if (nArgs == 0)
    {
      try
      {
        // Full array get operation
        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            Result  = R_CreateArray(nCoords, aCoords, INTSXP);

            if (bNoTranslation)
            {
              ::memcpy((char*)INTEGER(Result), pInfo->firstData(), pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::ADlib_to_R(rAllocator, pArray, (char*)INTEGER(Result));
            }
            break;
          }

          case AdtVarType_DOUBLE:
          {
            Result  = R_CreateArray(nCoords, aCoords, REALSXP);

            if (bNoTranslation)
            {
              ::memcpy((char*)REAL(Result), pInfo->firstData(), pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::ADlib_to_R(rAllocator, pArray, (char*)REAL(Result));
            }
            break;
          }

          default:
          {
            break;
          }
        }
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplGetter threw a runtime exception, %s", e.what());
      }
    }
    else if (nArgs == nCoords)
    {
      const AdtArrayPlanActor*  pActor = 0;

      try
      {
        // scalar element get operation
        char* pData = pInfo->Actor->indexArray(aIndices,
                                               nArgs,
                                               pArray,
                                               pInfo->SizeOf,
                                               &pActor);

        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            int* pInt;

            pInt    = (int*)pData;
            Result  = R_Scalar(*pInt);
            break;
          }

          case AdtVarType_DOUBLE:
          {
            double* pDouble;

            pDouble = (double*)pData;
            Result  = R_Scalar(*pDouble);
            break;
          }

          default:
          {
            break;
          }
        }
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplGetter threw a runtime exception, %s", e.what());
      }
    }
    else
    {
      char* pSliceArray = 0;

      try
      {
        // Slice array get operation
        pSliceArray = AdtArrayPlanActor::createSlice(rAllocator,
                                                     pArray,
                                                     aIndices,
                                                     nArgs);

        AdtArrayInfo* pSliceInfo    = AdtArrayPlanActor::arrayInfo(rAllocator, pSliceArray);
        unsigned int  nSliceCoords  = pSliceInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            Result = R_CreateArray(nSliceCoords, aCoords, INTSXP);

            if (bNoTranslation)
            {
              ::memcpy((char*)INTEGER(Result), pSliceInfo->firstData(), pSliceInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::ADlib_to_R(rAllocator, pSliceArray, (char*)INTEGER(Result));
            }
            break;
          }

          case AdtVarType_DOUBLE:
          {
            Result = R_CreateArray(nSliceCoords, aCoords, REALSXP);

            if (bNoTranslation)
            {
              ::memcpy((char*)REAL(Result), pSliceInfo->firstData(), pSliceInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::ADlib_to_R(rAllocator, pSliceArray, (char*)REAL(Result));
            }
            break;
          }

          default:
          {
            break;
          }
        }

        rAllocator.free(pSliceArray);
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplGetter threw a runtime exception, %s", e.what());

        if (pSliceArray != 0)
        {
          rAllocator.free(pSliceArray);
        }
      }
    }
  }
  else
  {
    Rf_error("ERROR: Expecting list of arguments in call to getter for %s. See line %d in file %s", pName, nLineNumber, pFileName);
  }

  return (Result);
}

//  ----------------------------------------------------------------------------

SEXP R_ImplSetter(const AdtMemAllocator& rAllocator,
                  bool bNoTranslation,
                  char* pArray,
                  const char* pName,
                  SEXP sSrcArg,
                  SEXP sArgList,
                  const char* pFileName,
                  int nLineNumber)
{
  if (Rf_isNewList(sArgList))
  {
    unsigned int  nErrorIndex;
    unsigned int  nArgs                       = Rf_length(sArgList);
    int           aIndices[ADLIB_MAX_COORDS]  = {0};
    AdtArrayCoord aCoords[ADLIB_MAX_COORDS]   = {0};
    AdtArrayInfo* pInfo                       = AdtArrayPlanActor::arrayInfo(rAllocator, pArray);
    unsigned int  nCoords                     = pInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

    if ((nArgs > nCoords) || (nArgs > ADLIB_MAX_COORDS))
    {
      Rf_error("ERROR: Too many arguments in list of arguments passed in call to setter for %s. See line %d in file %s", pName, nLineNumber, pFileName);
    }

    // Read indices from argument list
    if (!ReadIndices(sArgList, aIndices, nArgs, nErrorIndex))
    {
      Rf_error("ERROR: Indexing argument %d in the setter argument list is not an integer for %s. See line %d in file %s", pName, nErrorIndex + 1, nLineNumber, pFileName);
    }

    if ((pInfo->VarType != AdtVarType_INT) && (pInfo->VarType != AdtVarType_DOUBLE))
    {
      std::runtime_error("R_ImplSetter called on array of type not supported in R\n");
    }
    else if (nArgs == 0)
    {
      try
      {
        // Full array set operation
        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            nCoords,
                            aCoords,
                            "INTSXP",
                            INTSXP);

            if (bNoTranslation)
            {
              ::memcpy(pInfo->firstData(), (char*)INTEGER(sSrcArg), pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::R_to_ADlib(rAllocator, (char*)INTEGER(sSrcArg), pArray);
            }
            break;
          }

          case AdtVarType_DOUBLE:
          {
            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            nCoords,
                            aCoords,
                            "REALSXP",
                            REALSXP);

            if (bNoTranslation)
            {
              ::memcpy(pInfo->firstData(), (char*)REAL(sSrcArg), pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::R_to_ADlib(rAllocator, (char*)REAL(sSrcArg), pArray);
            }
            break;
          }

          default:
          {
            break;
          }
        }
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplSetter threw a runtime exception, %s", e.what());
      }
    }
    else if (nArgs == nCoords)
    {
      const AdtArrayPlanActor*  pActor = 0;

      try
      {
        // scalar element set operation
        char* pData = pInfo->Actor->indexArray(aIndices,
                                               nArgs,
                                               pArray,
                                               pInfo->SizeOf,
                                               &pActor);

        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            int* pInt;

            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            0,
                            aCoords,
                            "INTSXP",
                            INTSXP);

            pInt    = (int*)pData;
            pInt[0] = INTEGER(sSrcArg)[0];
            break;
          }

          case AdtVarType_DOUBLE:
          {
            double* pDouble;

            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            0,
                            aCoords,
                            "REALSXP",
                            REALSXP);

            pDouble     = (double*)pData;
            pDouble[0]  = REAL(sSrcArg)[0];
            break;
          }

          default:
          {
            break;
          }
        }
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplSetter threw a runtime exception, %s", e.what());
      }
    }
    else
    {
      char* pSliceArray = 0;

      try
      {
        // Slice array get operation
        pSliceArray = AdtArrayPlanActor::createSlice(rAllocator,
                                                     pArray,
                                                     aIndices,
                                                     nArgs);

        AdtArrayInfo* pSliceInfo    = AdtArrayPlanActor::arrayInfo(rAllocator, pSliceArray);
        unsigned int  nSliceCoords  = pSliceInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

        switch(pInfo->VarType)
        {
          case AdtVarType_INT:
          {
            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            nSliceCoords,
                            aCoords,
                            "INTSXP",
                            INTSXP);

            if (bNoTranslation)
            {
              ::memcpy(pSliceInfo->firstData(), (char*)INTEGER(sSrcArg), pSliceInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::R_to_ADlib(rAllocator, (char*)INTEGER(sSrcArg), pSliceArray);
            }
            break;
          }

          case AdtVarType_DOUBLE:
          {
            R_CheckArgument(pName,
                            sSrcArg,
                            pFileName,
                            nLineNumber,
                            nSliceCoords,
                            aCoords,
                            "REALSXP",
                            REALSXP);

            if (bNoTranslation)
            {
              ::memcpy(pSliceInfo->firstData(), (char*)REAL(sSrcArg), pSliceInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::R_to_ADlib(rAllocator, (char*)REAL(sSrcArg), pSliceArray);
            }
            break;
          }

          default:
          {
            break;
          }
        }

        rAllocator.free(pSliceArray);
      }
      catch (std::runtime_error &e)
      {
        Rf_error("ERROR: R_ImplSetter threw a runtime exception, %s", e.what());

        if (pSliceArray != 0)
        {
          rAllocator.free(pSliceArray);
        }
      }
    }
  }
  else
  {
    Rf_error("ERROR: Expecting list of arguments in call to setter for %s. See line %d in file %s", pName, nLineNumber, pFileName);
  }

  return (R_Empty());
}

//  ----------------------------------------------------------------------------

void R_CheckArgument(const char* pName,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber,
                     int nDims,
                     AdtArrayCoord* pCoords,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType)
{
  if (Argument != 0)
  {
    int nArgLength = Rf_length(Argument);

    if (TYPEOF(Argument) != nRequiredType)
    {
      Rf_error("ERROR: %s must be of type %s. See line %d in file %s",
               pName,
               pRequiredTypeName,
               nLineNumber,
               pFileName);
    }

    if (nDims < 1)
    {
      // Expect scalar
      if (nArgLength > 1)
      {
        Rf_warning("WARNING: Scalar expected but %s is a vector or array. See line %d in file %s",
                   pName,
                   nLineNumber,
                   pFileName);
      }
    }
    else
    {
      // Expect array or Oarray
      int       cn;
      int       nSize = 0;
      bool      bNegativeOrZero;
      bool      bOarray;

      bNegativeOrZero = false;
      bOarray         = false;

      for (cn = 0 ; cn < nDims ; cn++)
      {
        int nLowerBound = pCoords[cn].IndexBase;
        int nUpperBound = pCoords[cn].IndexBase + pCoords[cn].Size - 1;

        bNegativeOrZero = bNegativeOrZero || (nLowerBound <= 0);
        bOarray         = bOarray || (nLowerBound != 1);

        if (nUpperBound < nLowerBound)
        {
          std::runtime_error("R_CheckArgument called with index upper bound less than lower bound\n");
        }

        if (cn == 0)
        {
          nSize = (nUpperBound - nLowerBound + 1);
        }
        else
        {
          nSize *= (nUpperBound - nLowerBound + 1);
        }
      }

      if (nArgLength < nSize)
      {
        Rf_error("ERROR: %s is a vector or array with length less than expected. A length of %d elements is required. See line %d in file %s",
                 pName,
                 nSize,
                 nLineNumber,
                 pFileName);
      }
      else if (nArgLength > nSize)
      {
        Rf_warning("WARNING: %s is a vector or array with length greater than expected. See line %d in file %s",
                   pName,
                   nLineNumber,
                   pFileName);
      }
    }
  }
  else
  {
    Rf_error("ERROR: Argument %s is null. See line %d in file %s",
             pName,
             nLineNumber,
             pFileName);
  }
}

//  ----------------------------------------------------------------------------

void R_CheckArgument(const char* pName,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber,
                     int nDims, ...)
{
  int           cn;
  va_list       arglist;
  AdtArrayCoord aCoords[ADLIB_MAX_COORDS] = {0};

  if (nDims > ADLIB_MAX_COORDS)
  {
    std::runtime_error("R_CheckArgument called with too many arguments\n");
  }

  va_start(arglist, nDims);

  for (cn = 0 ; cn < nDims ; cn++)
  {
    int nLowerBound = va_arg(arglist, int);
    int nUpperBound = va_arg(arglist, int);

    aCoords[cn].IndexBase = nLowerBound;
    aCoords[cn].Size      = nUpperBound - nLowerBound + 1;

    if (nUpperBound < nLowerBound)
    {
      std::runtime_error("R_CheckArgument called with index upper bound less than lower bound\n");
    }
  }

  R_CheckArgument(pName,
                  Argument,
                  pFileName,
                  nLineNumber,
                  nDims,
                  aCoords,
                  pRequiredTypeName,
                  nRequiredType);
}

//  ----------------------------------------------------------------------------

void R_CheckArgument(const char* pName,
                     const char* pRequiredTypeName,
                     SEXPTYPE nRequiredType,
                     SEXP Argument,
                     const char* pFileName,
                     int nLineNumber)
{
  R_CheckArgument(pName,
                  Argument,
                  pFileName,
                  nLineNumber,
                  0,
                  0,
                  pRequiredTypeName,
                  nRequiredType);
}

//  ----------------------------------------------------------------------------

SEXP R_CreateArray(int nDims, AdtArrayCoord* pCoords, SEXPTYPE nType)
{
  int       cn;
  int       nSize = 0;
  SEXP      Result;
  bool      bNegativeOrZero;
  bool      bOarray;

  bNegativeOrZero = false;
  bOarray         = false;

  for (cn = 0 ; cn < nDims ; cn++)
  {
    int nLowerBound = pCoords[cn].IndexBase;

    bNegativeOrZero = bNegativeOrZero || (nLowerBound <= 0);
    bOarray         = bOarray || (nLowerBound != 1);

    if (cn == 0)
    {
      nSize = pCoords[cn].Size;
    }
    else
    {
      nSize *= pCoords[cn].Size;
    }
  }

  if (nSize > 0)
  {
    Result = PROTECT(Rf_allocVector(nType, nSize));

    if (bOarray)
    {
      SEXP Class;
      SEXP DropNegative;
      SEXP Dim;
      SEXP Offset;

      // Add Oarray class attribute
      Class = PROTECT(Rf_allocVector(STRSXP, 1));
      SET_STRING_ELT(Class, 0, Rf_mkChar("Oarray"));
      Rf_classgets(Result, Class);
      UNPROTECT(1);

      // Add attribute names for offset and drop.negative
      if (OffsetSymbol == NULL)
      {
        OffsetSymbol = Rf_install("offset");
      }

      if (DropNegativeSymbol == NULL)
      {
        DropNegativeSymbol = Rf_install("drop.negative");
      }

      // Add drop negative attribute
      DropNegative = PROTECT(Rf_ScalarLogical(bNegativeOrZero ? 0 : 1));

      Rf_setAttrib(Result, DropNegativeSymbol, DropNegative);
      UNPROTECT(1);

      // Add dim and offset attributes
      Dim     = PROTECT(Rf_allocVector(INTSXP, nDims));
      Offset  = PROTECT(Rf_allocVector(INTSXP, nDims));

      for (cn = 0 ; cn < nDims ; cn++)
      {
        int nLowerBound = pCoords[cn].IndexBase;
        int nSize       = pCoords[cn].Size;

        INTEGER(Dim)[cn]    = nSize;
        INTEGER(Offset)[cn] = nLowerBound;
      }

      Rf_dimgets(Result, Dim);
      Rf_setAttrib(Result, OffsetSymbol, Offset);
      UNPROTECT(2);
    }
    else
    {
      // Add dim attribute
      SEXP Dim;

      Dim = PROTECT(Rf_allocVector(INTSXP, nDims));

      for (cn = 0 ; cn < nDims ; cn++)
      {
        int nSize = pCoords[cn].Size;

        INTEGER(Dim)[cn] = nSize;
      }

      Rf_dimgets(Result, Dim);
      UNPROTECT(1);
    }

    UNPROTECT(1);
  }
  else
  {
    std::runtime_error("R_CreateArray called with zero dims\n");
  }

  return (Result);
}

//  ----------------------------------------------------------------------------

SEXP R_CreateArray(int nDims, SEXPTYPE nType, ...)
{
  int           cn;
  SEXP          Result;
  va_list       arglist;
  AdtArrayCoord aCoords[ADLIB_MAX_COORDS] = {0};

  if (nDims > ADLIB_MAX_COORDS)
  {
    std::runtime_error("R_CreateArray called with too many arguments\n");
  }

  va_start(arglist, nType);

  for (cn = 0 ; cn < nDims ; cn++)
  {
    int nLowerBound = va_arg(arglist, int);
    int nUpperBound = va_arg(arglist, int);

    aCoords[cn].IndexBase = nLowerBound;
    aCoords[cn].Size      = nUpperBound - nLowerBound + 1;

    if (nUpperBound < nLowerBound)
    {
      std::runtime_error("R_CreateArray called with index upper bound less than lower bound\n");
    }
  }

  Result = R_CreateArray(nDims, aCoords, nType);

  return (Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Scalar(const int& nResult)
{
  SEXP Result = allocVector(INTSXP, 1);

  PROTECT(Result);
  INTEGER(Result)[0] = nResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Scalar(const double& dResult)
{
  SEXP Result = allocVector(REALSXP, 1);

  PROTECT(Result);
  REAL(Result)[0] = dResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Empty()
{
  int nEmpty = 0;

  return (R_Scalar(nEmpty));
}
