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
//    adtparallel.hpp
//
//  Purpose:
//    This file includes declarations of classes to implement parallelisation
//    of for loops for ADlib.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTPARALLEL_HPP__
#define __ADTPARALLEL_HPP__


#include "adtthreads.hpp"


#ifndef AD


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtArrays;


//  ----------------------------------------------------------------------------
//  AdtParallelStdOutCallback type definition
//  ----------------------------------------------------------------------------
typedef void (*AdtParallelStdOutCallback)(adtstring& StdOutString);


//  ----------------------------------------------------------------------------
//  AdtParallelForCallback type definition
//  ----------------------------------------------------------------------------
typedef void (*AdtParallelForCallback)(void* pContext, int nIdx, int nThreadIdx, adtstring& StdOutString);


//  ----------------------------------------------------------------------------

void                      parallelFor(void* pContext, AdtParallelForCallback pCallback, int nStartIdx, int nEndIdx, bool bSerialise = false);
void                      priorityParallelFor(void* pContext, AdtParallelForCallback pCallback, int* pPriorities, int nStartIdx, int nEndIdx, bool bSerialise = false);

AdtParallelStdOutCallback setStdOutCallback(AdtParallelStdOutCallback pCallback);
AdtParallelStdOutCallback getStdOutCallback();

AdtParallelStdOutCallback setStdErrCallback(AdtParallelStdOutCallback pCallback);
AdtParallelStdOutCallback getStdErrCallback();

void                      createThreadPool(int nNumberOfThreads);
void                      closeThreadPool();
int                       numberOfThreads();
bool                      writeToStdOutString(const char* pString);
bool                      writeToStdErrString(const char* pString);

void                      allocateShallowCopies(AdtArrays* pParent);
void                      freeShallowCopies();
AdtArrays*                shallowCopy(int nIdx);


#endif //AD


#endif //__ADTPARALLEL_HPP__
