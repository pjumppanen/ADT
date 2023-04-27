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


SEXP R_CALLARG::wrapArgument(const AdtMemAllocator& rMemAllocator,
                             bool bNoTranslation)
{
  SEXP  Result(R_NilValue);

  try
  {
    if (IsScalar)
    {
      switch (VarType)
      {
        case AdtVarType_INT:
        {
          PROTECT(Result = Rf_allocVector(INTSXP, 1));
          INTEGER(Result)[0] = ((int*)Array)[0];
          UNPROTECT(1);
          break;
        }

        case AdtVarType_DOUBLE:
        {
          PROTECT(Result = Rf_allocVector(REALSXP, 1));
          REAL(Result)[0] = ((double*)Array)[0];
          UNPROTECT(1);
          break;
        }

        case AdtVarType_LONGBOOL:
        case AdtVarType_CHAR:
        case AdtVarType_UCHAR:
        case AdtVarType_BOOL:
        default:
        {
          break;
        }
      }
    }
    else
    {
      AdtArrayCoord aCoords[ADLIB_MAX_COORDS]   = {0};
      AdtArrayInfo* pInfo                       = AdtArrayPlanActor::arrayInfo(rMemAllocator, Array);
      unsigned int  nCoords                     = pInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

      switch (pInfo->VarType)
      {
        case AdtVarType_INT:
        case AdtVarType_DOUBLE:
        case AdtVarType_LONGBOOL:
        case AdtVarType_CHAR:
        case AdtVarType_UCHAR:
        case AdtVarType_BOOL:
        {
          char* pResultData = 0;

          // Full array get operation
          switch(pInfo->VarType)
          {
            case AdtVarType_INT:
            {
              Result      = R_CreateArray(nCoords, aCoords, INTSXP);
              pResultData = (char*)INTEGER(Result);
              break;
            }

            case AdtVarType_DOUBLE:
            {
              Result      = R_CreateArray(nCoords, aCoords, REALSXP);
              pResultData = (char*)REAL(Result);
              break;
            }

            case AdtVarType_LONGBOOL:
            {
              Result      = R_CreateArray(nCoords, aCoords, LGLSXP);
              pResultData = (char*)LOGICAL(Result);
              break;
            }

            case AdtVarType_CHAR:
            case AdtVarType_UCHAR:
            case AdtVarType_BOOL:
            {
              Result      = R_CreateArray(nCoords, aCoords, RAWSXP);
              pResultData = (char*)RAW(Result);
              break;
            }

            default:
            {
              break;
            }
          }

          if (pResultData != 0)
          {
            if (bNoTranslation)
            {
              ::memcpy(pResultData, pInfo->firstData(), pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::ADlib_to_R(rMemAllocator, Array, pResultData);
            }
          }
        }
      }
    }
  }
  catch (std::runtime_error &e)
  {
    Rf_error("ERROR: R_CALL::wrapArgument threw a runtime exception, %s", e.what());
  }

  return (Result);
}                             


//  ----------------------------------------------------------------------------
//  R_RETARG class method implementations
//  ----------------------------------------------------------------------------
void R_RETARG::assign(SEXP Result,
                      const AdtMemAllocator& rMemAllocator,
                      bool bNoTranslation)
{
  try
  {
    if (IsScalar)
    {
      switch (VarType)
      {
        case AdtVarType_INT:
        {
          Result = Rf_coerceVector(Result, INTSXP);

          PROTECT(Result);
          ((int*)Array)[0] = INTEGER(Result)[0];
          UNPROTECT(1);
          break;
        }

        case AdtVarType_DOUBLE:
        {
          Result = Rf_coerceVector(Result, REALSXP);

          PROTECT(Result);
          ((double*)Array)[0] = REAL(Result)[0];
          UNPROTECT(1);
          break;
        }

        case AdtVarType_LONGBOOL:
        case AdtVarType_CHAR:
        case AdtVarType_UCHAR:
        case AdtVarType_BOOL:
        default:
        {
          break;
        }
      }
    }
    else
    {
      AdtArrayCoord aCoords[ADLIB_MAX_COORDS] = {0};
      AdtArrayInfo* pInfo                     = AdtArrayPlanActor::arrayInfo(rMemAllocator, Array);
      unsigned int  nCoords                   = pInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

      switch (pInfo->VarType)
      {
        case AdtVarType_INT:
        case AdtVarType_DOUBLE:
        {
          char*       pSrcArgData     = 0;
          SEXPTYPE    nSrcArgType     = 0;
          const char* pSrcArgTypeName = "";

          switch(pInfo->VarType)
          {
            case AdtVarType_INT:
            {
              Result = Rf_coerceVector(Result, INTSXP);

              PROTECT(Result);

              pSrcArgData     = (char*)INTEGER(Result);
              nSrcArgType     = INTSXP;
              pSrcArgTypeName = "INTSXP";
              break;
            }

            case AdtVarType_DOUBLE:
            {
              Result = Rf_coerceVector(Result, REALSXP);

              PROTECT(Result);

              pSrcArgData     = (char*)REAL(Result);
              nSrcArgType     = REALSXP;
              pSrcArgTypeName = "REALSXP";
              break;
            }

            case AdtVarType_LONGBOOL:
            case AdtVarType_CHAR:
            case AdtVarType_UCHAR:
            case AdtVarType_BOOL:
            default:
            {
              break;
            }
          }

          if (pSrcArgData != 0)
          {
            if (bNoTranslation)
            {
              ::memcpy(pInfo->firstData(), pSrcArgData, pInfo->lengthOfData());
            }
            else
            {
              AdtArrayPlanActor::R_to_ADlib(rMemAllocator, pSrcArgData, Array);
            }

            UNPROTECT(1);
          }
        }

        case AdtVarType_LONGBOOL:
        case AdtVarType_CHAR:
        case AdtVarType_UCHAR:
        case AdtVarType_BOOL:
        default:
        {
          break;
        }
      }  
    }
  }
  catch (std::runtime_error &e)
  {
    Rf_error("ERROR: R_RETARG::assign threw a runtime exception, %s", e.what());
  }
}


//  ----------------------------------------------------------------------------
//  R_CALL class method implementations
//  ----------------------------------------------------------------------------
void R_CALL::callR(R_RETARG& ret, R_CALLARG* Arguments[], int nArguments)
{
  if (Valid)
  {
    int           cn;
    SEXP          Nil(R_NilValue);
    SEXP          Result(R_NilValue);
    SEXP          Call = langN(nArguments);
    PROTECT_INDEX ipx;

    // Initialise args and do call
    SEXP  tcall = Call;

    for (cn = 0 ; cn < nArguments ; cn++)
    {
      SETCADR(tcall, Arguments[cn]->wrapArgument(*MemAllocator, NoTranslation));
      tcall = CDR(tcall);
    }

    PROTECT_WITH_INDEX(Result = Rf_eval(Call, Environment), &ipx);
    REPROTECT(Result = Rf_coerceVector(Result, ret.type()), ipx);
    ret.assign(Result, *MemAllocator, NoTranslation);
    UNPROTECT(1);
  }
}

//  ----------------------------------------------------------------------------

SEXP R_CALL::langN(int nArguments) const
{
  SEXP List = Rf_cons(PROTECT(R_NilValue), R_NilValue);

  for (int cn = 0 ; cn < nArguments - 1 ; cn++)
  {
    List = Rf_cons(PROTECT(R_NilValue), List);
  }

  SEXP Call = Rf_lcons(PROTECT(Function), List); 
  UNPROTECT(1 + nArguments);

  return (Call);
}

//  ----------------------------------------------------------------------------

R_CALL::R_CALL()
 : Function(R_NilValue),
   Environment(R_NilValue),
   MemAllocator(0)
{
  NoTranslation = false;
  Valid         = false;
}

//  ----------------------------------------------------------------------------

R_CALL::R_CALL(SEXP func, SEXP env, bool bNoTranslation, const AdtMemAllocator& rAllocator)
 : Function(func),
   Environment(env),
   MemAllocator(&rAllocator)
{
  NoTranslation = false;
  Valid         = false;

  initialise(func, env, bNoTranslation, rAllocator);
}

//  ----------------------------------------------------------------------------

R_CALL::R_CALL(const R_CALL& rCopy)
 : Function(R_NilValue),
   Environment(R_NilValue),
   MemAllocator(0)
{
  NoTranslation = false;
  Valid         = false;
}

//  ----------------------------------------------------------------------------

R_CALL::~R_CALL()
{

}

//  ----------------------------------------------------------------------------

void R_CALL::initialise(SEXP func, SEXP env, bool bNoTranslation, const AdtMemAllocator& rAllocator)
{
  NoTranslation = bNoTranslation;
  Valid         = Rf_isFunction(func) && Rf_isEnvironment(env);

  if (Valid)
  {
    Function      = func;
    Environment   = env;
    MemAllocator  = &rAllocator; 
  }
}

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret)
{
  callR(ret, 0, 0);
}

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0)
{
  R_CALLARG* Arguments[1] = {&arg0};

  callR(ret, Arguments, 1);
}                          

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1)
{
  R_CALLARG* Arguments[2] = {&arg0, 
                             &arg1};

  callR(ret, Arguments, 2);
}

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2)
{
  R_CALLARG* Arguments[3] = {&arg0, 
                             &arg1, 
                             &arg2};

  callR(ret, Arguments, 3);
}

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3)
{
  R_CALLARG* Arguments[4] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3};

  callR(ret, Arguments, 4);
}                          

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4)
{
  R_CALLARG* Arguments[5] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3, 
                             &arg4};

  callR(ret, Arguments, 5);
}                          

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4, 
                          R_CALLARG arg5)
{
  R_CALLARG* Arguments[6] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3, 
                             &arg4, 
                             &arg5};

  callR(ret, Arguments, 6);
}                          

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4, 
                          R_CALLARG arg5, 
                          R_CALLARG arg6)
{
  R_CALLARG* Arguments[7] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3, 
                             &arg4, 
                             &arg5, 
                             &arg6};

  callR(ret, Arguments, 7);
}                        

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4, 
                          R_CALLARG arg5, 
                          R_CALLARG arg6, 
                          R_CALLARG arg7)
{
  R_CALLARG* Arguments[8] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3, 
                             &arg4, 
                             &arg5, 
                             &arg6, 
                             &arg7};

  callR(ret, Arguments, 8);
}                        

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4, 
                          R_CALLARG arg5, 
                          R_CALLARG arg6, 
                          R_CALLARG arg7, 
                          R_CALLARG arg8)
{
  R_CALLARG* Arguments[9] = {&arg0, 
                             &arg1, 
                             &arg2, 
                             &arg3, 
                             &arg4, 
                             &arg5, 
                             &arg6, 
                             &arg7, 
                             &arg8};

  callR(ret, Arguments, 9);
}                          

//  ----------------------------------------------------------------------------

void R_CALL::operator () (R_RETARG ret, 
                          R_CALLARG arg0, 
                          R_CALLARG arg1, 
                          R_CALLARG arg2, 
                          R_CALLARG arg3, 
                          R_CALLARG arg4, 
                          R_CALLARG arg5, 
                          R_CALLARG arg6, 
                          R_CALLARG arg7, 
                          R_CALLARG arg8, 
                          R_CALLARG arg9)
{
  R_CALLARG* Arguments[10] = {&arg0, 
                              &arg1, 
                              &arg2, 
                              &arg3, 
                              &arg4, 
                              &arg5, 
                              &arg6, 
                              &arg7, 
                              &arg8, 
                              &arg9};

  callR(ret, Arguments, 10);
}


//  ----------------------------------------------------------------------------
//  R Interface helper functions used to simplify interface code
//  ----------------------------------------------------------------------------
static SEXP             DropNegativeSymbol  = NULL;
static SEXP             OffsetSymbol        = NULL;
static R_UseArrayClass  ArrayClass          = ArrayClass_offarray;

//  ----------------------------------------------------------------------------

void R_SetArrayClass(R_UseArrayClass nClass)
{
  ArrayClass = nClass;
}

//  ----------------------------------------------------------------------------

longbool* LONGBOOL(SEXP x)
{
  longbool* pLB = (longbool*)LOGICAL(x);

  return (pLB);
}

//  ----------------------------------------------------------------------------

bool* RAWBOOL(SEXP x)
{
  bool* pB = (bool*)RAW(x);

  return (pB);
}

//  ----------------------------------------------------------------------------

char* RAWCHAR(SEXP x)
{
  char* pC = (char*)RAW(x);

  return (pC);
}

//  ----------------------------------------------------------------------------

bool ReadIndices(SEXP sArgList, int* pIndices, unsigned int nArgs, unsigned int& rErrorIndex)
{
  bool bRead = true;

  // Read indices from argument list
  for (unsigned int cn = 0 ; cn < nArgs ; cn++)
  {
    SEXP Element = VECTOR_ELT(sArgList, cn);

    if (Rf_isIntegerOrFactor(Element))
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
      Rf_error("ERROR: Indexing argument %d in the getter argument list is not an integer for %s. See line %d in file %s", pName, nErrorIndex + 2, nLineNumber, pFileName);
    }

    switch (pInfo->VarType)
    {
      case AdtVarType_INT:
      case AdtVarType_DOUBLE:
      case AdtVarType_LONGBOOL:
      case AdtVarType_CHAR:
      case AdtVarType_UCHAR:
      case AdtVarType_BOOL:
      {
        if (nArgs == 0)
        {
          try
          {
            char* pResultData = 0;

            // Full array get operation
            switch(pInfo->VarType)
            {
              case AdtVarType_INT:
              {
                Result      = R_CreateArray(nCoords, aCoords, INTSXP);
                pResultData = (char*)INTEGER(Result);
                break;
              }

              case AdtVarType_DOUBLE:
              {
                Result      = R_CreateArray(nCoords, aCoords, REALSXP);
                pResultData = (char*)REAL(Result);
                break;
              }

              case AdtVarType_LONGBOOL:
              {
                Result      = R_CreateArray(nCoords, aCoords, LGLSXP);
                pResultData = (char*)LOGICAL(Result);
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                Result      = R_CreateArray(nCoords, aCoords, RAWSXP);
                pResultData = (char*)RAW(Result);
                break;
              }

              default:
              {
                break;
              }
            }

            if (pResultData != 0)
            {
              if (bNoTranslation)
              {
                ::memcpy(pResultData, pInfo->firstData(), pInfo->lengthOfData());
              }
              else
              {
                AdtArrayPlanActor::ADlib_to_R(rAllocator, pArray, pResultData);
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

              case AdtVarType_LONGBOOL:
              {
                longbool* pLongBool;

                pLongBool = (longbool*)pData;
                Result    = R_Scalar(*pLongBool);
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                char* pChar;

                pChar   = (char*)pData;
                Result  = R_Scalar(*pChar);
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
            char*         pResultData   = 0;

            switch(pInfo->VarType)
            {
              case AdtVarType_INT:
              {
                Result      = R_CreateArray(nSliceCoords, aCoords, INTSXP);
                pResultData = (char*)INTEGER(Result);
                break;
              }

              case AdtVarType_DOUBLE:
              {
                Result      = R_CreateArray(nSliceCoords, aCoords, REALSXP);
                pResultData = (char*)REAL(Result);
                break;
              }

              case AdtVarType_LONGBOOL:
              {
                Result      = R_CreateArray(nSliceCoords, aCoords, LGLSXP);
                pResultData = (char*)LOGICAL(Result);
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                Result      = R_CreateArray(nSliceCoords, aCoords, RAWSXP);
                pResultData = (char*)RAW(Result);
                break;
              }

              default:
              {
                break;
              }
            }

            if (pResultData != 0)
            {
              if (bNoTranslation)
              {
                ::memcpy(pResultData, pSliceInfo->firstData(), pSliceInfo->lengthOfData());
              }
              else
              {
                AdtArrayPlanActor::ADlib_to_R(rAllocator, pSliceArray, pResultData);
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
        break;
      }

      default:
      {
        Rf_error("ERROR: R_ImplGetter called on array of type %s not supported in R\n", varTypeName(pInfo->VarType));
        break;
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
      Rf_error("ERROR: Indexing argument %d in the setter argument list is not an integer for %s. See line %d in file %s", nErrorIndex + 3, pName, nLineNumber, pFileName);
    }

    switch (pInfo->VarType)
    {
      case AdtVarType_INT:
      case AdtVarType_DOUBLE:
      case AdtVarType_LONGBOOL:
      case AdtVarType_CHAR:
      case AdtVarType_UCHAR:
      case AdtVarType_BOOL:
      {
        if (nArgs == 0)
        {
          try
          {
            // Full array set operation
            char*       pSrcArgData     = 0;
            SEXPTYPE    nSrcArgType     = 0;
            const char* pSrcArgTypeName = "";

            switch(pInfo->VarType)
            {
              case AdtVarType_INT:
              {
                pSrcArgData     = (char*)INTEGER(sSrcArg);
                nSrcArgType     = INTSXP;
                pSrcArgTypeName = "INTSXP";
                break;
              }

              case AdtVarType_DOUBLE:
              {
                pSrcArgData     = (char*)REAL(sSrcArg);
                nSrcArgType     = REALSXP;
                pSrcArgTypeName = "REALSXP";
                break;
              }

              case AdtVarType_LONGBOOL:
              {
                pSrcArgData     = (char*)LOGICAL(sSrcArg);
                nSrcArgType     = LGLSXP;
                pSrcArgTypeName = "LGLSXP";
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                pSrcArgData     = (char*)RAW(sSrcArg);
                nSrcArgType     = RAWSXP;
                pSrcArgTypeName = "RAWSXP";
                break;
              }

              default:
              {
                break;
              }
            }

            if (pSrcArgData != 0)
            {
              R_CheckArgument(pName,
                              sSrcArg,
                              pFileName,
                              nLineNumber,
                              nCoords,
                              aCoords,
                              pSrcArgTypeName,
                              nSrcArgType);

              if (bNoTranslation)
              {
                ::memcpy(pInfo->firstData(), pSrcArgData, pInfo->lengthOfData());
              }
              else
              {
                AdtArrayPlanActor::R_to_ADlib(rAllocator, pSrcArgData, pArray);
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

              case AdtVarType_LONGBOOL:
              {
                longbool* pLongBool;

                R_CheckArgument(pName,
                                sSrcArg,
                                pFileName,
                                nLineNumber,
                                0,
                                aCoords,
                                "LGLSXP",
                                LGLSXP);

                pLongBool     = (longbool*)pData;
                pLongBool[0]  = LOGICAL(sSrcArg)[0];
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                unsigned char* pUChar;

                R_CheckArgument(pName,
                                sSrcArg,
                                pFileName,
                                nLineNumber,
                                0,
                                aCoords,
                                "RAWSXP",
                                RAWSXP);

                pUChar    = (unsigned char*)pData;
                pUChar[0] = RAW(sSrcArg)[0];
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

            AdtArrayInfo* pSliceInfo      = AdtArrayPlanActor::arrayInfo(rAllocator, pSliceArray);
            unsigned int  nSliceCoords    = pSliceInfo->Actor->getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);
            char*         pSrcArgData     = 0;
            SEXPTYPE      nSrcArgType     = 0;
            const char*   pSrcArgTypeName = "";

            // Full array get operation
            switch(pInfo->VarType)
            {
              case AdtVarType_INT:
              {
                pSrcArgData     = (char*)INTEGER(sSrcArg);
                nSrcArgType     = INTSXP;
                pSrcArgTypeName = "INTSXP";
                break;
              }

              case AdtVarType_DOUBLE:
              {
                pSrcArgData     = (char*)REAL(sSrcArg);
                nSrcArgType     = REALSXP;
                pSrcArgTypeName = "REALSXP";
                break;
              }

              case AdtVarType_LONGBOOL:
              {
                pSrcArgData     = (char*)LOGICAL(sSrcArg);
                nSrcArgType     = LGLSXP;
                pSrcArgTypeName = "LGLSXP";
                break;
              }

              case AdtVarType_CHAR:
              case AdtVarType_UCHAR:
              case AdtVarType_BOOL:
              {
                pSrcArgData     = (char*)RAW(sSrcArg);
                nSrcArgType     = RAWSXP;
                pSrcArgTypeName = "RAWSXP";
                break;
              }

              default:
              {
                break;
              }
            }

            if (pSrcArgData != 0)
            {
              R_CheckArgument(pName,
                              sSrcArg,
                              pFileName,
                              nLineNumber,
                              nSliceCoords,
                              aCoords,
                              pSrcArgTypeName,
                              nSrcArgType);

              if (bNoTranslation)
              {
                ::memcpy(pInfo->firstData(), pSrcArgData, pInfo->lengthOfData());
              }
              else
              {
                AdtArrayPlanActor::R_to_ADlib(rAllocator, pSrcArgData, pSliceArray);
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
        break;
      }

      default:
      {
        Rf_error("ERROR: R_ImplSetter called on array of type %s not supported in R\n", varTypeName(pInfo->VarType));
        break;
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
      switch (TYPEOF(Argument))
      {
        case CLOSXP:
        case ENVSXP:
        {
          break;
        }

        default:
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
      switch (ArrayClass)
      {
        case ArrayClass_Oarray:
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
          break;
        }

        case ArrayClass_offarray:
        {
          SEXP Class;
          SEXP Dim;
          SEXP Offset;

          // Add offarray class attribute
          Class = PROTECT(Rf_allocVector(STRSXP, 1));
          SET_STRING_ELT(Class, 0, Rf_mkChar("offarray"));
          Rf_classgets(Result, Class);
          UNPROTECT(1);

          // Add attribute name for offset
          if (OffsetSymbol == NULL)
          {
            OffsetSymbol = Rf_install("offset");
          }

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
          break;
        }

        default:
        {
          std::runtime_error("R_CreateArray called with invalid R ArrayClass\n");
          break;
        }
      }
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
  SEXP Result = Rf_allocVector(INTSXP, 1);

  PROTECT(Result);
  INTEGER(Result)[0] = nResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Scalar(const double& dResult)
{
  SEXP Result = Rf_allocVector(REALSXP, 1);

  PROTECT(Result);
  REAL(Result)[0] = dResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Scalar(const longbool& lbResult)
{
  SEXP Result = Rf_allocVector(LGLSXP, 1);

  PROTECT(Result);
  LOGICAL(Result)[0] = lbResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Scalar(const char& cResult)
{
  SEXP Result = Rf_allocVector(RAWSXP, 1);

  PROTECT(Result);
  RAW(Result)[0] = (unsigned char)cResult;
  UNPROTECT(1);

  return(Result);
}

//  ----------------------------------------------------------------------------

SEXP R_Empty()
{
  int nEmpty = 0;

  return (R_Scalar(nEmpty));
}
