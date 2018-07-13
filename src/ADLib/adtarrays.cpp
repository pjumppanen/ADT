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
//    adtarrays.cpp
//
//  Purpose:
//    This file includes implementations of classes for use in Auto-differentiation
//    code implemented in C++. This is a functional equivalent of the TUseful
//    delphi unit code for delphi applications.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtarrays.hpp"
#include "adtthreads.hpp"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>


#ifdef _MSC_VER
  #define snprintf _snprintf
#endif


//  ----------------------------------------------------------------------------

size_t elementSizeFromVarType(AdtVarType nVarType)
{
  size_t nSizeOf = 0;

  switch(nVarType)
  {
    case AdtVarType_UNDEFINED:
    default:
    {
      throw(std::runtime_error(std::string("Uninitialised var type")));
      break;
    }

    case AdtVarType_BOOL:
    {
      nSizeOf = sizeof(bool);
      break;
    }

    case AdtVarType_LONGBOOL:
    {
      nSizeOf = sizeof(longbool);
      break;
    }

    case AdtVarType_CHAR:
    {
      nSizeOf = sizeof(char);
      break;
    }

    case AdtVarType_UCHAR:
    {
      nSizeOf = sizeof(unsigned char);
      break;
    }

    case AdtVarType_INT:
    {
      nSizeOf = sizeof(int);
      break;
    }

    case AdtVarType_UINT:
    {
      nSizeOf = sizeof(unsigned int);
      break;
    }

    case AdtVarType_LONG:
    {
      nSizeOf = sizeof(long);
      break;
    }

    case AdtVarType_ULONG:
    {
      nSizeOf = sizeof(unsigned long);
      break;
    }

    case AdtVarType_SHORT:
    {
      nSizeOf = sizeof(short);
      break;
    }

    case AdtVarType_USHORT:
    {
      nSizeOf = sizeof(unsigned short);
      break;
    }

    case AdtVarType_FLOAT:
    {
      nSizeOf = sizeof(float);
      break;
    }

    case AdtVarType_DOUBLE:
    {
      nSizeOf = sizeof(double);
      break;
    }
  }

  return (nSizeOf);
}

//  ----------------------------------------------------------------------------

const char* varTypeName(AdtVarType nVarType)
{
  const char* pTypeName;

  switch (nVarType)
  {
    default:
    case AdtVarType_UNDEFINED:
    {
      pTypeName = "AdtVarType_UNDEFINED";
      break;
    }

    case AdtVarType_BOOL:
    {
      pTypeName = "AdtVarType_BOOL";
      break;
    }

    case AdtVarType_LONGBOOL:
    {
      pTypeName = "AdtVarType_LONGBOOL";
      break;
    }

    case AdtVarType_CHAR:
    {
      pTypeName = "AdtVarType_CHAR";
      break;
    }

    case AdtVarType_UCHAR:
    {
      pTypeName = "AdtVarType_UCHAR";
      break;
    }

    case AdtVarType_INT:
    {
      pTypeName = "AdtVarType_INT";
      break;
    }

    case AdtVarType_UINT:
    {
      pTypeName = "AdtVarType_UINT";
      break;
    }

    case AdtVarType_LONG:
    {
      pTypeName = "AdtVarType_LONG";
      break;
    }

    case AdtVarType_ULONG:
    {
      pTypeName = "AdtVarType_ULONG";
      break;
    }

    case AdtVarType_SHORT:
    {
      pTypeName = "AdtVarType_SHORT";
      break;
    }

    case AdtVarType_USHORT:
    {
      pTypeName = "AdtVarType_USHORT";
      break;
    }

    case AdtVarType_FLOAT:
    {
      pTypeName = "AdtVarType_FLOAT";
      break;
    }

    case AdtVarType_DOUBLE:
    {
      pTypeName = "AdtVarType_DOUBLE";
      break;
    }
  }

  return (pTypeName);
}


//  ----------------------------------------------------------------------------
//  AdtArrayCoord method implementations
//  ----------------------------------------------------------------------------
void AdtArrayCoord::appendKey(adtstring& rKey, bool bWithPrefix) const
{
  char sBuffer[48] = {0};

  ::sprintf(sBuffer, bWithPrefix ? ",%d:%d" : "%d:%d", IndexBase, Size);
  rKey.append(sBuffer);
}


//  ----------------------------------------------------------------------------
//  AdtArrayInfo method implementations
//  ----------------------------------------------------------------------------
void AdtArrayInfo::xcopy(const AdtArrayInfo* pSrcArrayInfo)
{
  if ((*Actor == *(pSrcArrayInfo->Actor)) &&
      (SizeOf == pSrcArrayInfo->SizeOf))
  {
    ::memcpy((void*)(BlockPtr + LookupSize),
             (void*)(pSrcArrayInfo->BlockSize + pSrcArrayInfo->LookupSize),
             (BlockSize - LookupSize) * sizeof(char));
  }
  else
  {
    throw(std::runtime_error(std::string("Incompatible array x_copy")));
  }
}


//  ----------------------------------------------------------------------------
//  AdtMemAllocator method implementations
//  ----------------------------------------------------------------------------
char* AdtMemAllocator::debugAlloc(size_t nSize) const
{
  char  GuardByte = (char)0xFD;
  char* pMemory   = new char[nSize + sizeof(size_t) + 2 * 4];

  for (int cn = 0 ; cn < 4 ; cn++)
  {
    *pMemory++ = GuardByte;
  }

  *((size_t*)pMemory) = nSize;

  pMemory += sizeof(size_t);

  char* pEndGuard = pMemory + nSize;

  for (int cn = 0 ; cn < 4 ; cn++)
  {
    *pEndGuard++ = GuardByte;
  }

  return (pMemory);
}

//  ----------------------------------------------------------------------------

void AdtMemAllocator::debugFree(char* pBlock) const
{
  char  GuardByte = (char)0xFD;
  char* pMemory   = pBlock - sizeof(size_t) - 4;
  char* pToFree   = pMemory;

  // Check for underwrite
  for (int cn = 0 ; cn < 4 ; cn++)
  {
    assert(*pMemory++ == GuardByte);
  }

  size_t nSize = *((size_t*)pMemory);

  pMemory += sizeof(size_t);

  char* pEndGuard = pMemory + nSize;

  // Check for overwrite
  for (int cn = 0 ; cn < 4 ; cn++)
  {
    assert(*pEndGuard++ == GuardByte);
  }

  delete [] pToFree;
}

//  ----------------------------------------------------------------------------

bool AdtMemAllocator::free(AdtAllocRecord& rAllocRecord) const
{
  bool bFreed = false;

  AdtWaitOnMutex  Wait(Mutex);

  if (Wait)
  {
    rAllocRecord.LockCount--;

    if (rAllocRecord.LockCount == 0)
    {
      if ((rAllocRecord.IsOurBlock) && (rAllocRecord.BlockPtr != 0))
      {
#ifdef __TRACE_ALLOC__
        printf("Delete Block %x\n", (unsigned int)rAllocRecord.BlockPtr);
#endif
        debugFree(rAllocRecord.BlockPtr);
        rAllocRecord.BlockPtr = 0;
      }

      if (rAllocRecord.UserPtr != 0)
      {
        if (rAllocRecord.Callback != 0)
        {
          (rAllocRecord.Callback)(rAllocRecord.UserPtr);
        }

#ifdef __TRACE_ALLOC__
        printf("Delete User %x\n", (unsigned int)rAllocRecord.UserPtr);
#endif
        debugFree(rAllocRecord.UserPtr);
        rAllocRecord.UserPtr = 0;
      }

      bFreed = true;
    }
  }

  return (bFreed);
}

//  ----------------------------------------------------------------------------

AdtMemAllocator::AdtMemAllocator()
 : AllocMap()
{
  Mutex = new AdtMutex;
}

//  ----------------------------------------------------------------------------

AdtMemAllocator::~AdtMemAllocator()
{
  free();

  AdtReleaseReference(Mutex);
}

//  ----------------------------------------------------------------------------

char* AdtMemAllocator::alloc(size_t nSize,
                             AdtAllocType nAllocType,
                             int nBlockOffset,
                             AdtUserDestroyCallback pCallback,
                             char** ppUserPtr,
                             size_t nUserSize,
                             char* pExisting) const
{
  char*           pOffsetBlock = 0;
  AdtWaitOnMutex  Wait(Mutex);

  if (Wait)
  {
    AdtAllocRecord  AllocRecord;

    AllocRecord.AllocType   = nAllocType;
    AllocRecord.Callback    = pCallback;
    AllocRecord.BlockOffset = nBlockOffset;
    AllocRecord.BlockSize   = 0;
    AllocRecord.UserSize    = 0;
    AllocRecord.LockCount   = 1;

    if (nSize == 0)
    {
      AllocRecord.IsOurBlock = false;
      AllocRecord.BlockPtr   = pExisting;
    }
    else
    {
      AllocRecord.IsOurBlock = true;

      if (nSize != 0)
      {
        AllocRecord.BlockPtr  = debugAlloc(nSize);
        AllocRecord.BlockSize = nSize;
#ifdef __TRACE_ALLOC__
        printf("New Block %x\n", (unsigned int)AllocRecord.BlockPtr);
#endif
      }
      else
      {
        AllocRecord.BlockPtr  = 0;
      }
    }

    if (nUserSize != 0)
    {
      AllocRecord.UserPtr   = debugAlloc(nUserSize);
      AllocRecord.UserSize  = nUserSize;
#ifdef __TRACE_ALLOC__
      printf("New User %x\n", (unsigned int)AllocRecord.UserPtr);
#endif
    }
    else
    {
      AllocRecord.UserPtr = 0;
    }

    if (AllocRecord.BlockPtr != 0)
    {
      // The nIndexingOffset parameter is required for being able to track the
      // existence of arrays with non-zero bases because the pointer the user
      // code will have access to and pass to the free() method will be offset.
      // Hence we calculate what the offset pointer would be and use that as
      // the index into the map of the allocated pointer so we can later free it.
      pOffsetBlock = AllocRecord.BlockPtr + nBlockOffset;

      if (AllocMap.find(pOffsetBlock) == AllocMap.end())
      {
        AllocMap[pOffsetBlock] = AllocRecord;
      }
      else
      {
        throw(std::runtime_error(std::string("Existing memory block already referrenced by a different allocation record.")));
      }
    }

    if (ppUserPtr != 0)
    {
      *ppUserPtr = AllocRecord.UserPtr;
    }
  }

  return (pOffsetBlock);
}

//  ----------------------------------------------------------------------------

char* AdtMemAllocator::blockPtr(char* pOffsetBlock, size_t* pBlockSize, AdtAllocType* pAllocType) const
{
  char* pBlockPtr = 0;

  if (pOffsetBlock != 0)
  {
    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      AdtAllocRecordByCharPtrMapIter  Iter = AllocMap.find(pOffsetBlock);

      if (Iter != AllocMap.end())
      {
        AdtAllocRecord& rAllocRecord = (*Iter).second;

        pBlockPtr = rAllocRecord.BlockPtr;

        if (pBlockSize != 0)
        {
          *pBlockSize = rAllocRecord.BlockSize;
        }

        if (pAllocType != 0)
        {
          *pAllocType = rAllocRecord.AllocType;
        }
      }
    }
  }

  return (pBlockPtr);
}

//  ----------------------------------------------------------------------------

char* AdtMemAllocator::userPtr(char* pOffsetBlock, size_t* pUserSize) const
{
  char* pUserPtr = 0;

  if (pOffsetBlock != 0)
  {
    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      AdtAllocRecordByCharPtrMapIter  Iter = AllocMap.find(pOffsetBlock);

      if (Iter != AllocMap.end())
      {
        AdtAllocRecord& rAllocRecord = (*Iter).second;

        pUserPtr = rAllocRecord.UserPtr;

        if (pUserSize != 0)
        {
          *pUserSize = rAllocRecord.UserSize;
        }
      }
    }
  }

  return (pUserPtr);
}

//  ----------------------------------------------------------------------------

bool AdtMemAllocator::lock(char* pOffsetBlock) const
{
  bool bLocked = false;

  if (pOffsetBlock != 0)
  {
    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      AdtAllocRecordByCharPtrMapIter  Iter = AllocMap.find(pOffsetBlock);

      if (Iter != AllocMap.end())
      {
        AdtAllocRecord& rAllocRecord = (*Iter).second;

        rAllocRecord.LockCount++;

        bLocked = true;
      }
    }
  }

  return (bLocked);
}

//  ----------------------------------------------------------------------------

bool AdtMemAllocator::free(char* pOffsetBlock) const
{
  bool bFreed = false;

  if (pOffsetBlock != 0)
  {
    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      AdtAllocRecordByCharPtrMapIter  Iter = AllocMap.find(pOffsetBlock);

      if (Iter != AllocMap.end())
      {
        AdtAllocRecord& rAllocRecord = (*Iter).second;

        if (free(rAllocRecord))
        {
          AllocMap.erase(pOffsetBlock);
        }
      }
    }
  }

  return (bFreed);
}

//  ----------------------------------------------------------------------------

void AdtMemAllocator::free()
{
  AdtWaitOnMutex  Wait(Mutex);

  if (Wait)
  {
    AdtAllocRecordByCharPtrMapIter  Iter;

    for (Iter = AllocMap.begin() ; Iter != AllocMap.end() ; ++Iter)
    {
      AdtAllocRecord& rAllocRecord = (*Iter).second;

      free(rAllocRecord);
    }

    AllocMap.clear();
  }
}


//  ----------------------------------------------------------------------------
//  AdtArrayPlanActor method implementations
//  ----------------------------------------------------------------------------
AdtArrayPlanActor::AdtArrayPlanActorPtrByStringMap  AdtArrayPlanActor::CacheMap;
bool                                                AdtArrayPlanActor::CacheUsed = false;

//  ----------------------------------------------------------------------------

size_t AdtArrayPlanActor::findLookupSize() const
{
  // Here we figure out the size of the lookup table needed to index the
  // multi-dimensional array as a contiguous block.
  LookupSize = 0;
  ArrayCount = 0;

  if (NumberOfCoOrdinates > 1)
  {
    LookupSize = Coord.Size * sizeof(char*);

    if (Next != 0)
    {
      LookupSize += Coord.Size * Next->findLookupSize();
      ArrayCount  = Coord.Size * Next->ArrayCount;
    }
    else if (NextRagged != 0)
    {
      int cn;

      for (cn = 0 ; cn < Coord.Size ; cn++)
      {
        LookupSize += NextRagged[cn]->findLookupSize();
        ArrayCount += NextRagged[cn]->ArrayCount;
      }
    }
  }
  else
  {
    ArrayCount = Coord.Size;
  }

  return (LookupSize);
}

//  ----------------------------------------------------------------------------

size_t AdtArrayPlanActor::arraySize(size_t nSizeOf) const
{
  size_t nArraySize = nSizeOf * ArrayCount;

  return (nArraySize);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::initialiseLookupInner(char**& pLookup,
                                              char*& pData,
                                              size_t nSizeOf,
                                              const char* pStartAddress,
                                              const char* pEndAddress,
                                              const char* pDataStartAddress,
                                              const char* pDataEndAddress) const
{
  // If we are at the bottom of the indexing hierachy (ie at the data level)
  // set bIsLookupLevel to false, otherwise true.
  bool bIsLookupLevel = false;

  if (NumberOfCoOrdinates > 1)
  {
    int     cn;
    char**  pLastLookup;
    char**  pThisLookup = pLookup;

    // Reserve space for this level of lookup
    pLookup += Coord.Size;

    if (Next != 0)
    {
      for (cn = 0 ; cn < Coord.Size ; cn++)
      {
        // Save the root location for the lookup being pointed to by this entry
        pLastLookup = pLookup;

        if (Next->initialiseLookupInner(pLookup,
                                        pData,
                                        nSizeOf,
                                        pStartAddress,
                                        pEndAddress,
                                        pDataStartAddress,
                                        pDataEndAddress))
        {
          // Point this entry to the next level of lookup. Alow for Index base
          // other than zero
          *pThisLookup = ((char*)pLastLookup) - (Next->Coord.IndexBase * sizeof(char*));

          assert((((char*)pThisLookup) >= pStartAddress) && (((char*)pThisLookup) <= pEndAddress));
          assert((((char*)pLastLookup) >= pStartAddress) && (((char*)pLastLookup) <= pEndAddress));
        }
        else
        {
          // Point this entry to the next level of data. Alow for Index base
          // other than zero
          *pThisLookup = pData - (Next->Coord.IndexBase * nSizeOf);

          assert(((((char*)pThisLookup) >= pStartAddress) && (((char*)pThisLookup) <= pEndAddress)) ||
                 ((((char*)pThisLookup) >= pDataStartAddress) && (((char*)pThisLookup) <= pDataEndAddress)));
          assert((pData >= pDataStartAddress) && (pData <= pDataEndAddress));

          pData       += (Next->Coord.Size * nSizeOf);
        }

        pThisLookup++;
      }
    }
    else if (NextRagged != 0)
    {
      for (cn = 0 ; cn < Coord.Size ; cn++)
      {
        pLastLookup = pLookup;

        if (NextRagged[cn]->initialiseLookupInner(pLookup,
                                                  pData,
                                                  nSizeOf,
                                                  pStartAddress,
                                                  pEndAddress,
                                                  pDataStartAddress,
                                                  pDataEndAddress))
        {
          // Point this entry to the next level of lookup. Alow for Index base
          // other than zero
          *pThisLookup = ((char*)pLastLookup) - (NextRagged[cn]->Coord.IndexBase * sizeof(char*));

          assert((((char*)pThisLookup) >= pStartAddress) && (((char*)pThisLookup) <= pEndAddress));
          assert((((char*)pLastLookup) >= pStartAddress) && (((char*)pLastLookup) <= pEndAddress));
        }
        else
        {
          // Point this entry to the next level of data. Alow for Index base
          // other than zero
          *pThisLookup = pData - (NextRagged[cn]->Coord.IndexBase * nSizeOf);

          assert(((((char*)pThisLookup) >= pStartAddress) && (((char*)pThisLookup) <= pEndAddress)) ||
                 ((((char*)pThisLookup) >= pDataStartAddress) && (((char*)pThisLookup) <= pDataEndAddress)));
          assert((pData >= pDataStartAddress) && (pData <= pDataEndAddress));

          pData       += (NextRagged[cn]->Coord.Size * nSizeOf);
        }

        pThisLookup++;
      }
    }

    bIsLookupLevel = true;
  }

  return (bIsLookupLevel);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::initialiseLookup(char* pArray,
                                         size_t nSizeOf,
                                         size_t nLookupSize,
                                         size_t nDataSize,
                                         void* pExisting) const
{
  // Here we initialise the lookup to point to the correct locations in the
  // multi-dimensional array as a contiguous block. If the data is stored
  // externally in a seperate block of memory, that block will be pointed to
  // by pExisting and we index into that block instead.
  if (NumberOfCoOrdinates > 1)
  {
    char**  pLookup = (char**)pArray;
    char*   pData   = (pExisting != 0) ? (char*)pExisting
                                       : pArray + nLookupSize;

    initialiseLookupInner(pLookup,
                          pData,
                          nSizeOf,
                          pArray,
                          pArray + nLookupSize - sizeof(char*),
                          pData,
                          pData + nDataSize - nSizeOf);
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::destroyNext()
{
  LookupSize = 0;
  ArrayCount = 0;

  if (Next != 0)
  {
    Next->unlock();

    Next = 0;
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::destroyNextRagged()
{
  LookupSize = 0;
  ArrayCount = 0;

  if (NextRagged != 0)
  {
    int cn;

    for (cn = 0 ; cn < Coord.Size ; cn++)
    {
      if (NextRagged[cn] != 0)
      {
        NextRagged[cn]->unlock();

        NextRagged[cn] = 0;
      }
    }

    delete [] NextRagged;

    NextRagged = 0;
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::copyNext(const AdtArrayPlanActor* pNext)
{
  destroyNext();

  if (pNext != 0)
  {
    Next = new AdtArrayPlanActor(*pNext);
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::copyNextRagged(AdtArrayPlanActor* const* ppNextRagged)
{
  destroyNextRagged();

  if ((ppNextRagged != 0) && (Coord.Size > 0))
  {
    NextRagged = new AdtArrayPlanActor*[Coord.Size];

    if (NextRagged != 0)
    {
      int cn;

      for (cn = 0 ; cn < Coord.Size ; cn++)
      {
        NextRagged[cn] = new AdtArrayPlanActor(*ppNextRagged[cn]);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::notifyDestroy(AdtArrayInfo* pArrayInfo) const
{
  if ((pArrayInfo != 0) && (pArrayInfo->Existing != 0))
  {
    // Remove mapping of array from the plan actors map of existing arrays
    AliasMap.erase(pArrayInfo->Existing);
  }

  unlock();
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::destroyArrayInfo(char* pData)
{
  AdtArrayInfo* pArrayInfo = (AdtArrayInfo*)pData;

  if ((pArrayInfo != 0) && (pArrayInfo->Actor != 0))
  {
    pArrayInfo->Actor->notifyDestroy(pArrayInfo);
  }
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor::AdtArrayPlanActor()
 : Coord(),
   AliasMap()
{
  LockCount           = 1;
  Next                = 0;
  NextRagged          = 0;
  NumberOfCoOrdinates = 0;
  LookupSize          = 0;
  ArrayCount          = 0;
  IsCached            = false;
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor::AdtArrayPlanActor(const AdtArrayCoord* pCoords,
                                     int nCoords,
                                     bool bTranspose,
                                     bool bSupressUpdate)
 : Coord(),
   AliasMap()
{
  LockCount           = 1;
  Next                = 0;
  NextRagged          = 0;
  NumberOfCoOrdinates = 0;
  LookupSize          = 0;
  ArrayCount          = 0;
  IsCached            = false;

  initialise(pCoords, nCoords, bTranspose, bSupressUpdate);
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor::AdtArrayPlanActor(const AdtArrayPlanActor& rCopy)
 : Coord(rCopy.Coord)
{
  LockCount           = 1;
  Next                = 0;
  NextRagged          = 0;
  NumberOfCoOrdinates = rCopy.NumberOfCoOrdinates;

  copyNext(rCopy.Next);
  copyNextRagged(rCopy.NextRagged);

  LookupSize          = rCopy.LookupSize;
  ArrayCount          = rCopy.ArrayCount;
  IsCached            = false;
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor::~AdtArrayPlanActor()
{
  destroyNext();
  destroyNextRagged();
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::initialise(const AdtArrayCoord* pCoords,
                                   int nCoords,
                                   bool bTranspose,
                                   bool bSupressUpdate)
{
  bool bInitialised = false;

  destroyNext();
  destroyNextRagged();

  NumberOfCoOrdinates = 0;

  if ((pCoords != 0) && (nCoords >= 1))
  {
    Coord               = *pCoords;
    NumberOfCoOrdinates = nCoords;

    if (bTranspose)
    {
      const AdtArrayCoord* pNextCoords = pCoords + nCoords - 1;

      Coord = *pNextCoords;

      if (nCoords > 1)
      {
        nCoords--;

        Next = new AdtArrayPlanActor(pCoords, nCoords, bTranspose, true);
      }
    }
    else
    {
      Coord = *pCoords;

      if (nCoords > 1)
      {
        pCoords++;
        nCoords--;

        Next = new AdtArrayPlanActor(pCoords, nCoords, bTranspose, true);
      }
    }

    if (!bSupressUpdate)
    {
      findLookupSize();
    }

    bInitialised = true;
  }

  return (bInitialised);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::beginRagged(const AdtArrayCoord& rCoord)
{
  bool bBegun = false;

  destroyNext();
  destroyNextRagged();

  Coord               = rCoord;
  NumberOfCoOrdinates = 1;

  if (Coord.Size > 0)
  {
    NextRagged = new AdtArrayPlanActor*[Coord.Size];

    if (NextRagged != 0)
    {
      int cn;

      for (cn = 0 ; cn < Coord.Size ; cn++)
      {
        NextRagged[cn] = 0;
      }

      bBegun = true;
    }
    else
    {
      // Memory allocation failure
      throw(std::runtime_error(std::string("Memory allocation failure")));
    }
  }

  return (bBegun);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::beginRagged(AdtArrayPlanActor*& pContext, const AdtArrayCoord& rCoord)
{
  bool bBegun = false;

  pContext = 0;

  if (NumberOfCoOrdinates == 0)
  {
    // Uninitialised plan case. Ragged from first co-ordinate
    pContext = this;
  }
  else
  {
    // Initialised plan case. Ragged from NumberOfCoOrdinates + 1 co-ordinate
    // Find last co-ordinate plan and add a new plan to it, set this plan to
    // the context and call beingRagged() on it.
    AdtArrayPlanActor*  pLastPlan = this;

    while (pLastPlan->Next != 0)
    {
      if (pLastPlan->NextRagged != 0)
      {
        throw(std::logic_error(std::string("calling beginRagged() on a Plan that is already ragged")));
      }

      pLastPlan = pLastPlan->Next;
    }

    if (pLastPlan != 0)
    {
      pLastPlan->Next = new AdtArrayPlanActor;
      pContext        = pLastPlan->Next;
    }
  }

  if (pContext != 0)
  {
    bBegun = pContext->beginRagged(rCoord);
  }

  return (bBegun);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::addArrayPlanActor(AdtArrayPlanActor* pActor, int nIndex)
{
  bool bAdded = false;

  if ((NextRagged != 0) && (Next == 0))
  {
    if ((nIndex >= Coord.IndexBase) && (nIndex < Coord.IndexBase + Coord.Size))
    {
      NextRagged[nIndex - Coord.IndexBase] = pActor;

      if (pActor != 0)
      {
        pActor->lock();
      }
    }
    else
    {
      // Index range error
      char  sMessage[128] = {0};

      sprintf(sMessage, "Index value %d is out of range [%d,%d)", nIndex, Coord.IndexBase, Coord.IndexBase + Coord.Size);

      throw(std::range_error(std::string(sMessage)));
    }
  }
  else
  {
    // not in a beginRagged() endRagged() code sandwitch
    throw(std::logic_error(std::string("addArrayPlan() must be called in a beginRagged() - endRagged() code sandwitch")));
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::updateCoOrdinates(AdtArrayPlanActor* pContext)
{
  AdtArrayPlanActor*  pLastPlan             = this;
  int                 nNumberOfCoOrdinates  = pContext->NumberOfCoOrdinates;

  while (pLastPlan->Next != 0)
  {
    pLastPlan->NumberOfCoOrdinates += nNumberOfCoOrdinates;
    pLastPlan                       = pLastPlan->Next;
  }

  findLookupSize();

  if (pLastPlan != pContext)
  {
    throw(std::logic_error(std::string("endRagged() called with context not connected with this plan.")));
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::endRagged()
{
  // Here we need to finalise instantiation of the ragged array by updating
  // the NumberOfCoOrdinates attribute and verifying that all entries in
  // NextRagged[] have been initialised
  if ((NextRagged != 0) && (Next == 0))
  {
    int   cn;
    bool  bFirst = true;
    int   nNumberOfCoOrdinates;

    for (cn = 0 ; cn < Coord.Size ; cn++)
    {
      if (NextRagged[cn] == 0)
      {
        char  sMessage[128] = {0};

        sprintf(sMessage, "ArrayPlan not initialised for index %d", cn + Coord.IndexBase);

        throw(std::logic_error(std::string(sMessage)));
      }
      else
      {
        if (bFirst)
        {
          nNumberOfCoOrdinates  = NextRagged[cn]->NumberOfCoOrdinates;
          bFirst                = false;
        }
        else
        {
          if (nNumberOfCoOrdinates != NextRagged[cn]->NumberOfCoOrdinates)
          {
            throw(std::logic_error(std::string("Inconsistent ArrayPlan co-ordinate sizes. They must be the same.")));
          }
        }
      }
    }

    NumberOfCoOrdinates = nNumberOfCoOrdinates + 1;

    findLookupSize();
  }
  else
  {
    // beginRagged() not called
    throw(std::logic_error(std::string("beginRagged() must be called before endRagged()")));
  }
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::create(const AdtMemAllocator& rAllocator,
                                AdtVarType nVarType,
                                void* pExisting) const
{
  int     nIndexOffset;
  char*   pArray        = 0;
  size_t  nSizeOf       = elementSizeFromVarType(nVarType);
  char*   pUserData     = 0;
  bool    bForceCreate  = false;
  size_t  nExtraSize    = 0;
  size_t  nDataSize     = arraySize(nSizeOf);
  size_t  nMemBlockSize = (pExisting == 0) ? LookupSize + nDataSize
                                           : LookupSize;

  if (NumberOfCoOrdinates == 1)
  {
    nIndexOffset = (int)(-Coord.IndexBase * nSizeOf);
    bForceCreate = (pExisting != 0);
  }
  else
  {
    nIndexOffset = -Coord.IndexBase * sizeof(char*);
  }

  if ((nMemBlockSize == 0) && !bForceCreate)
  {
    // To allow zero sized arrays to be allocated at some extra space to
    // the MemBlock.
    nExtraSize = sizeof(double);
  }

  if ((nMemBlockSize >= 0) || bForceCreate)
  {
    pArray = rAllocator.alloc(nMemBlockSize + nExtraSize,
                              AdtAllocType_ARRAY,
                              nIndexOffset,
                              AdtArrayPlanActor::destroyArrayInfo,
                              &pUserData,
                              sizeof(AdtArrayInfo),
                              (char*)pExisting);

    if (pUserData != 0)
    {
      AdtArrayInfo* pArrayInfo = (AdtArrayInfo*)pUserData;

      pArrayInfo->LookupSize  = LookupSize;
      pArrayInfo->BlockSize   = nMemBlockSize;
      pArrayInfo->SizeOf      = nSizeOf;
      pArrayInfo->BlockPtr    = pArray - nIndexOffset;
      pArrayInfo->Existing    = (char*)pExisting;
      pArrayInfo->VarType     = nVarType;
      pArrayInfo->Actor       = this;

      this->lock();
    }
  }
  else
  {
    throw(std::runtime_error(std::string("Array allocation failure")));
  }

  if ((LookupSize > 0) && (pArray != 0))
  {
    initialiseLookup(pArray - nIndexOffset,
                     nSizeOf,
                     LookupSize,
                     nDataSize,
                     pExisting);
  }

  if ((pArray != 0) && (pExisting != 0))
  {
    AdtAliasArray Alias;

    Alias.VarType   = nVarType;
    Alias.Dims      = numberOfCoOrdinates();
    Alias.Array     = pArray;

    AliasMap[pExisting] = Alias;
  }

  return (pArray);
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::createTransposed(const AdtMemAllocator& rAllocator,
                                          AdtVarType nVarType,
                                          void* pExisting) const
{
  char*               pArray;
  AdtArrayCoord       Coords[ADLIB_MAX_COORDS]  = {0};
  int                 nCoords;
  AdtArrayPlanActor*  pActor;

  nCoords = getCoords(Coords, ADLIB_MAX_COORDS);
  pActor  = cachedArrayPlanActor(Coords, nCoords, false, true);
  pArray  = pActor->AdtArrayPlanActor::create(rAllocator,
                                              nVarType,
                                              pExisting);

  return (pArray);
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::existing(AdtVarType nVarType,
                                  void* pExisting) const
{
  char*                               pArray  = 0;
  AdtAliasArrayByVoidPtrMapConstIter  Iter    = AliasMap.find(pExisting);

  if (Iter != AliasMap.end())
  {
    const AdtAliasArray& Alias = (*Iter).second;

    if (nVarType == Alias.VarType)
    {
      pArray = Alias.Array;
    }
    else
    {
      throw(std::runtime_error(std::string("Trying to create mapped array from an existing one but the AdtVarTypes don't match")));
    }
  }

  return (pArray);
}

//  ----------------------------------------------------------------------------

void check(const AdtArrayPlanActor*& pContext,
           const AdtMemAllocator& rAllocator,
           char* pArray,
           const char* pArrayName,
           const char* pFileName,
           int nFileLine,
           int nIndices,
           bool bThrowException,
           ...)
{
  if (pContext == 0)
  {
    const AdtArrayInfo* pInfo = AdtArrayPlanActor::arrayInfo(rAllocator, pArray);

    if (pInfo != 0)
    {
      pContext = pInfo->Actor;
    }
  }

  if (pContext != 0)
  {
    va_list                   arglist;
    const AdtArrayPlanActor*  pActor = pContext;
    const AdtArrayCoord*      pCoord = &(pActor->Coord);
    int*                      pNull  = 0;

    va_start(arglist, bThrowException);

    for (int cn = 0 ; cn < nIndices ; cn++)
    {
      int         nIndex      = va_arg(arglist, int);
      const char* pIndexName  = va_arg(arglist, const char*);

      if (nIndex < pCoord->IndexBase)
      {
        static char sBuffer[256] = {0};

        // Index too small
        snprintf(sBuffer,
                 255,
                 "Error in file %s on line %d : Array '%s' index %d indexed with '%s' = %d is too small. It must be greater than %d.",
                 pFileName,
                 nFileLine,
                 pArrayName,
                 nIndex + 1,
                 pIndexName,
                 nIndex,
                 pCoord->IndexBase - 1);

        if (bThrowException)
        {
          ts_warning(sBuffer);

          // Force an exception by assigning to a null pointer. We do this instead
          // of using throw() because VC debugger loses the code context through
          // the macro wrapping check for some mysterious reason. Doing it this
          // way and it finds the right context and drops the debugger into a
          // frame whereby you can see the origin of the exception in stack trace.
          pNull[0] = 0;
        }
        else
        {
          ts_error(sBuffer);
        }
        break;
      }
      else if (nIndex - pCoord->IndexBase >= pCoord->Size)
      {
        static char sBuffer[256] = {0};

        // Index too large
        snprintf(sBuffer,
                 255,
                 "Error in file %s on line %d : Array '%s' index %d indexed with '%s' = %d is too large. It must be less than %d.",
                 pFileName,
                 nFileLine,
                 pArrayName,
                 nIndex + 1,
                 pIndexName,
                 nIndex,
                 pCoord->IndexBase + pCoord->Size);

        if (bThrowException)
        {
          ts_warning(sBuffer);

          // Force an exception by assigning to a null pointer. We do this instead
          // of using throw() because VC debugger loses the code context through
          // the macro wrapping check for some mysterious reason. Doing it this
          // way and it finds the right context and drops the debugger into a
          // frame whereby you can see the origin of the exception in stack trace.
          pNull[0] = 0;
        }
        else
        {
          ts_error(sBuffer);
        }
        break;
      }

      // Go into next level of indexing
      if (pActor->Next != 0)
      {
        pActor = pActor->Next;
      }
      else if (pActor->NextRagged != 0)
      {
        pActor = pActor->NextRagged[nIndex - pCoord->IndexBase];
      }

      pCoord = &(pActor->Coord);
    }
  }
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::createSlice(const AdtMemAllocator& rAllocator,
                                     char* pArray,
                                     const int* pIndices,
                                     int nIndices)
{
  char*                     pSliceArray = 0;
  const AdtArrayPlanActor*  pRootActor  = 0;
  const AdtArrayInfo*       pInfo       = arrayInfo(rAllocator, pArray);

  // To create a slice we index the array to find the level of the LUT we need
  // along with the corresponding Actor and create a new one based array for
  // that level of indexing as per requirement for a slice operation. Then we
  // allocate the new slice array using rAllocator.alloc() so that its
  // attributes can be tracked by the normal means. Note that it is a shallow
  // allocation (requires only a small amount of resources) because most of
  // the array heirarchy is recycled and shares common memory with the parent.
  // The array slice should be freed when no longer needed though.
  if (pInfo != 0)
  {
    char* pData = pInfo->Actor->indexArray(pIndices,
                                           nIndices,
                                           pArray,
                                           pInfo->SizeOf,
                                           &pRootActor);

    if ((pData      != 0) &&
        (pRootActor != 0))
    {
      char*               pUserData     = 0;
      int                 nIndexOffset  = 0;
      AdtArrayPlanActor*  pNewActor     = 0;

      pNewActor = new AdtArrayPlanActor;

      pNewActor->NumberOfCoOrdinates = pRootActor->NumberOfCoOrdinates;
      pNewActor->LookupSize          = pRootActor->LookupSize;
      pNewActor->ArrayCount          = pRootActor->ArrayCount;
      pNewActor->Coord.IndexBase     = 1;
      pNewActor->Coord.Size          = pRootActor->Coord.Size;

      if (pRootActor->Next != 0)
      {
        pNewActor->Next = pRootActor->Next;

        pNewActor->Next->lock();
      }

      if ((pRootActor->NextRagged != 0) && (pRootActor->Coord.Size > 0))
      {
        pNewActor->NextRagged = new AdtArrayPlanActor*[pRootActor->Coord.Size];

        if (pNewActor->NextRagged != 0)
        {
          int cn;

          for (cn = 0 ; cn < pRootActor->Coord.Size ; cn++)
          {
            pNewActor->NextRagged[cn] = pRootActor->NextRagged[cn];

            pNewActor->NextRagged[cn]->lock();
          }
        }
      }

      if (pNewActor->NumberOfCoOrdinates == 1)
      {
        pData        = pData + pRootActor->Coord.IndexBase * pInfo->SizeOf;
        nIndexOffset = (int)(-pNewActor->Coord.IndexBase * pInfo->SizeOf);
      }
      else
      {
        pData        = pData + pRootActor->Coord.IndexBase * sizeof(char*);
        nIndexOffset = -pNewActor->Coord.IndexBase * sizeof(char*);
      }

      pSliceArray = rAllocator.alloc(0,
                                     AdtAllocType_ARRAY,
                                     nIndexOffset,
                                     AdtArrayPlanActor::destroyArrayInfo,
                                     &pUserData,
                                     sizeof(AdtArrayInfo),
                                     pData);

      if (pUserData != 0)
      {
        AdtArrayInfo* pArrayInfo = (AdtArrayInfo*)pUserData;

        pArrayInfo->LookupSize  = pRootActor->lookupSize();
        pArrayInfo->BlockSize   = pRootActor->arraySize(pInfo->SizeOf);
        pArrayInfo->SizeOf      = pInfo->SizeOf;
        pArrayInfo->BlockPtr    = pSliceArray - nIndexOffset;
        pArrayInfo->Existing    = pData;
        pArrayInfo->VarType     = pInfo->VarType;
        pArrayInfo->Actor       = pNewActor;
      }
    }
  }

  return (pSliceArray);
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::createSameShape(const AdtMemAllocator& rAllocator,
                                         char* pRefArray)
{
  char*               pArray      = 0;
  const AdtArrayInfo* pArrayInfo  = arrayInfo(rAllocator, pRefArray);

  if ((pArrayInfo != 0) && (pArrayInfo->Actor != 0))
  {
    pArray = pArrayInfo->Actor->create(rAllocator,
                                       pArrayInfo->VarType);
  }

  return (pArray);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::destroy(const AdtMemAllocator& rAllocator, char* pArray)
{
  rAllocator.free(pArray);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::R_to_ADlib(const AdtMemAllocator& rAllocator,
                                   char* pArraySrc,
                                   char* pArrayDest)
{
  AdtArrayCoord Coords[ADLIB_MAX_COORDS] = {0};
  AdtArrayInfo* pInfo   = AdtArrayPlanActor::arrayInfo(rAllocator, pArrayDest);
  int           nCoords = pInfo->Actor->getCoords(Coords, ADLIB_MAX_COORDS);

  switch(nCoords)
  {
    case 1:
    {
      ::memcpy((void*)(pInfo->BlockPtr + pInfo->LookupSize),
               (void*)pArraySrc,
               (pInfo->BlockSize - pInfo->LookupSize) * sizeof(char));
      break;
    }

    case 2:
    {
      char**        pArrayMappedSrc   = (char**)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char**        pArrayMappedDest  = (char**)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (size_t cs = 0 ; cs < nSizeOf ; cs++)
          {
            pArrayMappedDest[c0][c1 * nSizeOf + cs] = pArrayMappedSrc[c1][c0 * nSizeOf + cs];
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 3:
    {
      char***       pArrayMappedSrc   = (char***)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char***       pArrayMappedDest  = (char***)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (size_t cs = 0 ; cs < nSizeOf ; cs++)
            {
              pArrayMappedDest[c0][c1][c2 * nSizeOf + cs] = pArrayMappedSrc[c2][c1][c0 * nSizeOf + cs];
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 4:
    {
      char****      pArrayMappedSrc   = (char****)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char****      pArrayMappedDest  = (char****)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (size_t cs = 0 ; cs < nSizeOf ; cs++)
              {
                pArrayMappedDest[c0][c1][c2][c3 * nSizeOf + cs] = pArrayMappedSrc[c3][c2][c1][c0 * nSizeOf + cs];
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 5:
    {
      char*****     pArrayMappedSrc   = (char*****)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char*****     pArrayMappedDest  = (char*****)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                {
                  pArrayMappedDest[c0][c1][c2][c3][c4 * nSizeOf + cs] = pArrayMappedSrc[c4][c3][c2][c1][c0 * nSizeOf + cs];
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 6:
    {
      char******    pArrayMappedSrc   = (char******)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char******    pArrayMappedDest  = (char******)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                  {
                    pArrayMappedDest[c0][c1][c2][c3][c4][c5 * nSizeOf + cs] = pArrayMappedSrc[c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 7:
    {
      char*******   pArrayMappedSrc   = (char*******)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char*******   pArrayMappedDest  = (char*******)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                    {
                      pArrayMappedDest[c0][c1][c2][c3][c4][c5][c6 * nSizeOf + cs] = pArrayMappedSrc[c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 8:
    {
      char********  pArrayMappedSrc   = (char********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char********  pArrayMappedDest  = (char********)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                      {
                        pArrayMappedDest[c0][c1][c2][c3][c4][c5][c6][c7 * nSizeOf + cs] = pArrayMappedSrc[c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 9:
    {
      char********* pArrayMappedSrc   = (char*********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char********* pArrayMappedDest  = (char*********)pArrayDest;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (int c8 = Coords[8].IndexBase ; c8 < Coords[8].IndexBase + Coords[8].Size ; c8++)
                      {
                        for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                        {
                          pArrayMappedDest[c0][c1][c2][c3][c4][c5][c6][c7][c8 * nSizeOf + cs] = pArrayMappedSrc[c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    case 10:
    {
      char********** pArrayMappedSrc   = (char**********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArraySrc);
      char********** pArrayMappedDest  = (char**********)pArrayDest;
      size_t         nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (int c8 = Coords[8].IndexBase ; c8 < Coords[8].IndexBase + Coords[8].Size ; c8++)
                      {
                        for (int c9 = Coords[9].IndexBase ; c9 < Coords[9].IndexBase + Coords[9].Size ; c9++)
                        {
                          for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                          {
                            pArrayMappedDest[c0][c1][c2][c3][c4][c5][c6][c7][c8][c9 * nSizeOf + cs] = pArrayMappedSrc[c9][c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedSrc);
      break;
    }

    default:
    {
      throw(std::runtime_error(std::string("Invalid var type")));
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::ADlib_to_R(const AdtMemAllocator& rAllocator,
                                   char* pArraySrc,
                                   char* pArrayDest)
{
  AdtArrayCoord Coords[ADLIB_MAX_COORDS] = {0};
  AdtArrayInfo* pInfo   = AdtArrayPlanActor::arrayInfo(rAllocator, pArraySrc);
  int           nCoords = pInfo->Actor->getCoords(Coords, ADLIB_MAX_COORDS);

  switch(nCoords)
  {
    case 1:
    {
      ::memcpy((void*)pArrayDest,
               (void*)(pInfo->BlockPtr + pInfo->LookupSize),
               (pInfo->BlockSize - pInfo->LookupSize) * sizeof(char));
      break;
    }

    case 2:
    {
      char**        pArrayMappedDest  = (char**)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char**        pArrayMappedSrc   = (char**)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (size_t cs = 0 ; cs < nSizeOf ; cs++)
          {
            pArrayMappedDest[c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1 * nSizeOf + cs];
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 3:
    {
      char***       pArrayMappedDest  = (char***)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char***       pArrayMappedSrc   = (char***)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (size_t cs = 0 ; cs < nSizeOf ; cs++)
            {
              pArrayMappedDest[c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2 * nSizeOf + cs];
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 4:
    {
      char****      pArrayMappedDest  = (char****)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char****      pArrayMappedSrc   = (char****)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (size_t cs = 0 ; cs < nSizeOf ; cs++)
              {
                pArrayMappedDest[c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3 * nSizeOf + cs];
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 5:
    {
      char*****     pArrayMappedDest  = (char*****)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char*****     pArrayMappedSrc   = (char*****)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                {
                  pArrayMappedDest[c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4 * nSizeOf + cs];
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 6:
    {
      char******    pArrayMappedDest  = (char******)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char******    pArrayMappedSrc   = (char******)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                  {
                    pArrayMappedDest[c5][c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4][c5 * nSizeOf + cs];
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 7:
    {
      char*******   pArrayMappedDest  = (char*******)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char*******   pArrayMappedSrc   = (char*******)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                    {
                      pArrayMappedDest[c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4][c5][c6 * nSizeOf + cs];
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 8:
    {
      char********  pArrayMappedDest  = (char********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char********  pArrayMappedSrc   = (char********)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                      {
                        pArrayMappedDest[c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4][c5][c6][c7 * nSizeOf + cs];
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 9:
    {
      char********* pArrayMappedDest  = (char*********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char********* pArrayMappedSrc   = (char*********)pArraySrc;
      size_t        nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (int c8 = Coords[8].IndexBase ; c8 < Coords[8].IndexBase + Coords[8].Size ; c8++)
                      {
                        for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                        {
                          pArrayMappedDest[c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4][c5][c6][c7][c8 * nSizeOf + cs];
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    case 10:
    {
      char********** pArrayMappedDest  = (char**********)pInfo->Actor->createTransposed(rAllocator, pInfo->VarType, (void*)pArrayDest);
      char********** pArrayMappedSrc   = (char**********)pArraySrc;
      size_t         nSizeOf           = pInfo->SizeOf;

      for (int c0 = Coords[0].IndexBase ; c0 < Coords[0].IndexBase + Coords[0].Size ; c0++)
      {
        for (int c1 = Coords[1].IndexBase ; c1 < Coords[1].IndexBase + Coords[1].Size ; c1++)
        {
          for (int c2 = Coords[2].IndexBase ; c2 < Coords[2].IndexBase + Coords[2].Size ; c2++)
          {
            for (int c3 = Coords[3].IndexBase ; c3 < Coords[3].IndexBase + Coords[3].Size ; c3++)
            {
              for (int c4 = Coords[4].IndexBase ; c4 < Coords[4].IndexBase + Coords[4].Size ; c4++)
              {
                for (int c5 = Coords[5].IndexBase ; c5 < Coords[5].IndexBase + Coords[5].Size ; c5++)
                {
                  for (int c6 = Coords[6].IndexBase ; c6 < Coords[6].IndexBase + Coords[6].Size ; c6++)
                  {
                    for (int c7 = Coords[7].IndexBase ; c7 < Coords[7].IndexBase + Coords[7].Size ; c7++)
                    {
                      for (int c8 = Coords[8].IndexBase ; c8 < Coords[8].IndexBase + Coords[8].Size ; c8++)
                      {
                        for (int c9 = Coords[9].IndexBase ; c9 < Coords[9].IndexBase + Coords[9].Size ; c9++)
                        {
                          for (size_t cs = 0 ; cs < nSizeOf ; cs++)
                          {
                            pArrayMappedDest[c9][c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] = pArrayMappedSrc[c0][c1][c2][c3][c4][c5][c6][c7][c8][c9 * nSizeOf + cs];
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      rAllocator.free((char*)pArrayMappedDest);
      break;
    }

    default:
    {
      throw(std::runtime_error(std::string("Invalid var type")));
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor& AdtArrayPlanActor::operator = (const AdtArrayPlanActor& rCopy)
{
  Coord = rCopy.Coord;

  copyNext(rCopy.Next);
  copyNextRagged(rCopy.NextRagged);

  NumberOfCoOrdinates = rCopy.NumberOfCoOrdinates;

  return (*this);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::operator == (const AdtArrayPlanActor& rCopy) const
{
  bool bEqual = false;

  if ((Coord.IndexBase  == rCopy.Coord.IndexBase) &&
      (Coord.Size       == rCopy.Coord.Size     ))
  {
    if (rCopy.Next != 0)
    {
      if ((Next   != 0) &&
          (*Next  == *(rCopy.Next)))
      {
        bEqual = true;
      }
    }
    else if (Next == 0)
    {
      bEqual = true;
    }
  }

  return (bEqual);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::isRegular() const
{
  bool                      bIsRegular  = true;
  const AdtArrayPlanActor*  pActor      = this;

  for (int cn = 0 ; cn < NumberOfCoOrdinates ; cn++)
  {
    if (pActor->Next != 0)
    {
      pActor = pActor->Next;
    }
    else if (NextRagged != 0)
    {
      bIsRegular = false;
      break;
    }
  }

  return (bIsRegular);
}

//  ----------------------------------------------------------------------------

char* AdtArrayPlanActor::indexArray(const int* pIndices,
                                    int nIndices,
                                    char* pArray,
                                    size_t nSizeOf,
                                    const AdtArrayPlanActor** ppActor) const
{
  char* pData = 0;

  if ((pIndices != 0) && (pArray != 0))
  {
    pData = pArray;

    if ((nIndices < 0) || (nIndices > NumberOfCoOrdinates))
    {
      throw(std::runtime_error(std::string("too many indices")));
    }

    const AdtArrayCoord*      pCoord = &Coord;
    const AdtArrayPlanActor*  pActor = this;
    int                       cn;

    for (cn = 0 ; cn < nIndices ; cn++)
    {
      int nIndex = pIndices[cn] - pActor->Coord.IndexBase;

      if ((nIndex < 0) || (nIndex >= pActor->Coord.Size))
      {
        throw(std::runtime_error(std::string("co-ordinate out of range")));
      }

      if ((cn + 1) == NumberOfCoOrdinates)
      {
        pData   = pData + (pIndices[cn] * nSizeOf);
        pActor  = 0;
      }
      else
      {
        pData   = ((char**)pData)[pIndices[cn]];

        if (pActor->Next != 0)
        {
          pActor = pActor->Next;
        }
        else if (NextRagged != 0)
        {
          pActor = pActor->NextRagged[nIndex];
        }
        else
        {
          throw(std::runtime_error(std::string("invalid AdtArrayPlanActor")));
        }

        pCoord = &(pActor->Coord);
      }
    }

    if (ppActor != 0)
    {
      *ppActor = pActor;
    }
  }

  return (pData);
}

//  ----------------------------------------------------------------------------

int AdtArrayPlanActor::getCoords(AdtArrayCoord* pCoords, int nCoords, bool bReversed) const
{
  if (nCoords < NumberOfCoOrdinates)
  {
    throw(std::runtime_error(std::string("buffer too small to hold co-ordinate data")));
  }

  const AdtArrayPlanActor*  pActor = this;

  for (int cn = 0 ; cn < NumberOfCoOrdinates ; cn++)
  {
    if (bReversed)
    {
      pCoords[NumberOfCoOrdinates - 1 - cn] = pActor->Coord;
    }
    else
    {
      pCoords[cn] = pActor->Coord;
    }

    if (pActor->Next != 0)
    {
      pActor = pActor->Next;
    }
    else if (pActor->NextRagged != 0)
    {
      throw(std::runtime_error(std::string("cannot retrieve ragged array co-ordinate data")));
    }
  }

  return (NumberOfCoOrdinates);
}

//  ----------------------------------------------------------------------------

const AdtArrayCoord& AdtArrayPlanActor::coord(const int* pIndices,
                                              int nIndices,
                                              const AdtArrayPlanActor** ppActor) const
{
  if ((nIndices < 0) || (nIndices >= NumberOfCoOrdinates))
  {
    throw(std::runtime_error(std::string("co-ordinate out of range")));
  }

  const AdtArrayCoord*      pCoord = &Coord;
  const AdtArrayPlanActor*  pActor = this;

  for (int cn = 0 ; cn < nIndices ; cn++)
  {
    if (pActor->Next != 0)
    {
      pActor = pActor->Next;
    }
    else if (pActor->NextRagged != 0)
    {
      if (pIndices != 0)
      {
        int nIndex = pIndices[cn] - pActor->Coord.IndexBase;

        if ((nIndex < 0) || (nIndex >= pActor->Coord.Size))
        {
          throw(std::runtime_error(std::string("co-ordinate out of range")));
        }

        pActor = pActor->NextRagged[nIndex];
      }
      else
      {
        pActor = pActor->NextRagged[0];
      }
    }

    if (pActor != 0)
    {
      pCoord = &(pActor->Coord);
    }
  }

  if (ppActor != 0)
  {
    *ppActor = pActor;
  }

  return (*pCoord);
}

//  ----------------------------------------------------------------------------

size_t AdtArrayPlanActor::lookupSize() const
{
  return (LookupSize);
}

//  ----------------------------------------------------------------------------

size_t AdtArrayPlanActor::arrayCount() const
{
  return (ArrayCount);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlanActor::unlock() const
{
  bool bDestroyed = false;

  LockCount--;

  assert(LockCount >= 0);

  if (LockCount == 0)
  {
    delete this;
    bDestroyed = true;
  }

  return (bDestroyed);
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor* AdtArrayPlanActor::createArrayPlanActor(const AdtArrayCoord* pCoords,
                                                           int nCoords)
{
  AdtArrayPlanActor*  pActor = new AdtArrayPlanActor(pCoords, nCoords);

  return (pActor);
}

//  ----------------------------------------------------------------------------

AdtArrayPlanActor* AdtArrayPlanActor::cachedArrayPlanActor(const AdtArrayCoord* pCoords,
                                                           int nCoords,
                                                           bool bLock,
                                                           bool bTranspose)
{
  int                 cn;
  adtstring           sKey;
  AdtArrayPlanActor*  pActor = 0;

  if (bTranspose)
  {
    for (cn = nCoords ; cn > 0 ; cn--)
    {
      pCoords[cn - 1].appendKey(sKey, (cn != nCoords));
    }
  }
  else
  {
    for (cn = 0 ; cn < nCoords ; cn++)
    {
      pCoords[cn].appendKey(sKey, (cn != 0));
    }
  }

  AdtArrayPlanActorPtrByStringMapIter Iter = CacheMap.find(sKey);

  if (Iter != CacheMap.end())
  {
    pActor = (*Iter).second;
  }
  else
  {
    pActor          = new AdtArrayPlanActor(pCoords, nCoords, bTranspose);
    CacheMap[sKey]  = pActor;

    if (!CacheUsed)
    {
      CacheUsed = true;

      atexit(AdtArrayPlanActor::flush);
    }

    if (pActor != 0)
    {
      pActor->IsCached = true;
    }
  }

  if (bLock && (pActor != 0))
  {
    pActor->lock();
  }

  return (pActor);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlanActor::flush(void)
{
  AdtArrayPlanActorPtrByStringMapIter Iter;

  for (Iter = CacheMap.begin() ; Iter != CacheMap.end() ; ++Iter)
  {
    AdtArrayPlanActor* pActor = (*Iter).second;

    if (pActor != 0)
    {
      pActor->unlock();
    }
  }

  CacheMap.clear();
}


//  ----------------------------------------------------------------------------
//  AdtArrayPlan method implementations
//  ----------------------------------------------------------------------------
AdtArrayPlan::AdtArrayPlan()
{
  Actor = new AdtArrayPlanActor;
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex, int nSize)
{
  Actor = 0;

  initialise(nBaseIndex, nSize);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5,
                           int nBaseIndex6, int nSize6)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5,
             nBaseIndex6, nSize6);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5,
                           int nBaseIndex6, int nSize6,
                           int nBaseIndex7, int nSize7)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5,
             nBaseIndex6, nSize6,
             nBaseIndex7, nSize7);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5,
                           int nBaseIndex6, int nSize6,
                           int nBaseIndex7, int nSize7,
                           int nBaseIndex8, int nSize8)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5,
             nBaseIndex6, nSize6,
             nBaseIndex7, nSize7,
             nBaseIndex8, nSize8);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5,
                           int nBaseIndex6, int nSize6,
                           int nBaseIndex7, int nSize7,
                           int nBaseIndex8, int nSize8,
                           int nBaseIndex9, int nSize9)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5,
             nBaseIndex6, nSize6,
             nBaseIndex7, nSize7,
             nBaseIndex8, nSize8,
             nBaseIndex9, nSize9);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(int nBaseIndex1, int nSize1,
                           int nBaseIndex2, int nSize2,
                           int nBaseIndex3, int nSize3,
                           int nBaseIndex4, int nSize4,
                           int nBaseIndex5, int nSize5,
                           int nBaseIndex6, int nSize6,
                           int nBaseIndex7, int nSize7,
                           int nBaseIndex8, int nSize8,
                           int nBaseIndex9, int nSize9,
                           int nBaseIndex10, int nSize10)
{
  Actor = 0;

  initialise(nBaseIndex1, nSize1,
             nBaseIndex2, nSize2,
             nBaseIndex3, nSize3,
             nBaseIndex4, nSize4,
             nBaseIndex5, nSize5,
             nBaseIndex6, nSize6,
             nBaseIndex7, nSize7,
             nBaseIndex8, nSize8,
             nBaseIndex9, nSize9,
             nBaseIndex10, nSize10);
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::AdtArrayPlan(const AdtArrayPlan& rCopy)
{
  Actor = rCopy.Actor;

  if (Actor != 0)
  {
    Actor->lock();
  }
}

//  ----------------------------------------------------------------------------

AdtArrayPlan::~AdtArrayPlan()
{
  if (Actor != 0)
  {
    Actor->unlock();

    Actor = 0;
  }
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex, int nSize)
{
  AdtArrayCoord rCoords[1] = {{nBaseIndex, nSize}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 1);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2)
{
  AdtArrayCoord rCoords[2] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 2);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3)
{
  AdtArrayCoord rCoords[3] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 3);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4)
{
  AdtArrayCoord rCoords[4] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 4);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5)
{
  AdtArrayCoord rCoords[5] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4},
                              {nBaseIndex5, nSize5}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 5);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5,
                              int nBaseIndex6, int nSize6)
{
  AdtArrayCoord rCoords[6] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4},
                              {nBaseIndex5, nSize5},
                              {nBaseIndex6, nSize6}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 6);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5,
                              int nBaseIndex6, int nSize6,
                              int nBaseIndex7, int nSize7)
{
  AdtArrayCoord rCoords[7] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4},
                              {nBaseIndex5, nSize5},
                              {nBaseIndex6, nSize6},
                              {nBaseIndex7, nSize7}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 7);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5,
                              int nBaseIndex6, int nSize6,
                              int nBaseIndex7, int nSize7,
                              int nBaseIndex8, int nSize8)
{
  AdtArrayCoord rCoords[8] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4},
                              {nBaseIndex5, nSize5},
                              {nBaseIndex6, nSize6},
                              {nBaseIndex7, nSize7},
                              {nBaseIndex8, nSize8}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 8);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5,
                              int nBaseIndex6, int nSize6,
                              int nBaseIndex7, int nSize7,
                              int nBaseIndex8, int nSize8,
                              int nBaseIndex9, int nSize9)
{
  AdtArrayCoord rCoords[9] = {{nBaseIndex1, nSize1},
                              {nBaseIndex2, nSize2},
                              {nBaseIndex3, nSize3},
                              {nBaseIndex4, nSize4},
                              {nBaseIndex5, nSize5},
                              {nBaseIndex6, nSize6},
                              {nBaseIndex7, nSize7},
                              {nBaseIndex8, nSize8},
                              {nBaseIndex9, nSize9}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 9);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::initialise(int nBaseIndex1, int nSize1,
                              int nBaseIndex2, int nSize2,
                              int nBaseIndex3, int nSize3,
                              int nBaseIndex4, int nSize4,
                              int nBaseIndex5, int nSize5,
                              int nBaseIndex6, int nSize6,
                              int nBaseIndex7, int nSize7,
                              int nBaseIndex8, int nSize8,
                              int nBaseIndex9, int nSize9,
                              int nBaseIndex10, int nSize10)
{
  AdtArrayCoord rCoords[10] = {{nBaseIndex1, nSize1},
                               {nBaseIndex2, nSize2},
                               {nBaseIndex3, nSize3},
                               {nBaseIndex4, nSize4},
                               {nBaseIndex5, nSize5},
                               {nBaseIndex6, nSize6},
                               {nBaseIndex7, nSize7},
                               {nBaseIndex8, nSize8},
                               {nBaseIndex9, nSize9},
                               {nBaseIndex10, nSize10}};

  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = AdtArrayPlanActor::createArrayPlanActor(rCoords, 10);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlan::beginRagged(AdtArrayPlanActor*& pContext, int nBaseIndex, int nSize)
{
  bool bBegun = false;

  pContext = 0;

  if (Actor != 0)
  {
    if (Actor->isCached())
    {
      AdtArrayPlanActor*  pCached = Actor;

      // We can't use a cached actor for a ragged array plan as we are modifying
      // the plan which will invalidate it's linkage to whatever arrays it has
      // already created. Therefore we create a copy that isn't cached.
      Actor = new AdtArrayPlanActor(*pCached);
      pCached->unlock();
    }

    AdtArrayCoord rCoord = {nBaseIndex, nSize};

    bBegun = Actor->beginRagged(pContext, rCoord);
  }

  return (bBegun);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlan::addArrayPlan(AdtArrayPlanActor* pContext, AdtArrayPlan& rArrayPlan, int nIndex)
{
  bool bAdded = false;

  if ((Actor != 0) && (pContext != 0))
  {
    bAdded = pContext->addArrayPlanActor(rArrayPlan.Actor, nIndex);
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::endRagged(AdtArrayPlanActor* pContext)
{
  if ((Actor != 0) && (pContext != 0))
  {
    pContext->endRagged();

    if (Actor != pContext)
    {
      // update NumberOfCoOrdinates to include dimensions added by this context
      Actor->updateCoOrdinates(pContext);
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlan::beginRagged(int nBaseIndex, int nSize)
{
  bool bBegun = false;

  if (Actor != 0)
  {
    AdtArrayCoord rCoord = {nBaseIndex, nSize};

    bBegun = Actor->beginRagged(rCoord);
  }

  return (bBegun);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlan::addArrayPlan(AdtArrayPlan& rArrayPlan, int nIndex)
{
  bool bAdded = false;

  if (Actor != 0)
  {
    bAdded = Actor->addArrayPlanActor(rArrayPlan.Actor, nIndex);
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

void AdtArrayPlan::endRagged()
{
  if (Actor != 0)
  {
    Actor->endRagged();
  }
}

//  ----------------------------------------------------------------------------

AdtArrayPlan& AdtArrayPlan::operator = (const AdtArrayPlan& rCopy)
{
  if (Actor != 0)
  {
    Actor->unlock();
  }

  Actor = rCopy.Actor;

  if (Actor != 0)
  {
    Actor->lock();
  }

  return (*this);
}

//  ----------------------------------------------------------------------------

bool AdtArrayPlan::operator == (const AdtArrayPlan& rCopy) const
{
  bool bEqual = false;

  if ((Actor == rCopy.Actor) ||
      ((Actor != 0) && (rCopy.Actor != 0) && (*Actor == *(rCopy.Actor))))
  {
    bEqual = true;
  }

  return (bEqual);
}

//  ----------------------------------------------------------------------------

int AdtArrayPlan::numberOfCoOrdinates() const
{
  return ((Actor != 0) ? Actor->numberOfCoOrdinates() : 0);
}

//  ----------------------------------------------------------------------------

size_t AdtArrayPlan::lookupSize() const
{
  return ((Actor != 0) ? Actor->lookupSize() : 0);
}


//  ----------------------------------------------------------------------------
//  AdtArrays method implementations
//  ----------------------------------------------------------------------------
const size_t AdtArrays::DefaultStackSize = 1024;

//  ----------------------------------------------------------------------------

AdtArrays::AdtArrays()
 : MemAllocator(*(new AdtMemAllocator))
{
  IsShallowCopy = false;
}

//  ----------------------------------------------------------------------------

AdtArrays::AdtArrays(const AdtArrays& rCopy, bool bShallow)
 : MemAllocator(bShallow ? rCopy.MemAllocator : *(new AdtMemAllocator))
{
  IsShallowCopy = bShallow;
}

//  ----------------------------------------------------------------------------

AdtArrays::~AdtArrays()
{
  if (!IsShallowCopy)
  {
    delete &MemAllocator;
  }
}

//  ----------------------------------------------------------------------------

AdtArrays* AdtArrays::createShallowCopy() const
{
  return (new AdtArrays(*this, true));
}

//  ----------------------------------------------------------------------------

bool AdtArrays::createStack(char** ppArray,
                            size_t nInitialSize,
                            AdtVarType nVarType) const
{
  bool        bCreated  = false;
  size_t      nSizeOf   = elementSizeFromVarType(nVarType);

  // Tricky issue. We want to alloc stacks in such a manner that createSameShape
  // will work but we also want to allocated it such that the block has header
  // Info that stores the current stack size so we can check that value quickly
  // (ie. without the need of using the infoMap). Maybe not supporting
  // createSameShape for stacks makes more sense!!! I'm not at all sure about
  // this, other than I believe allocSameShape isn't supported for stacks in
  // Mark's code
  int           nBlockOffset  = sizeof(AdtStackInfo);
  size_t        nBlockSize    = (nSizeOf * (nInitialSize + 1)) + nBlockOffset; // Add 1 to account for possible 1 based array usage
  char*         pOffsetBlock  = MemAllocator.alloc(nBlockSize, AdtAllocType_STACK, nBlockOffset);

  if (pOffsetBlock != 0)
  {
    AdtStackInfo* pStackInfo  = stackInfo(pOffsetBlock);

    pStackInfo->StackSize = nInitialSize;
    pStackInfo->SizeOf    = nSizeOf;
    pStackInfo->VarType   = nVarType;
    bCreated              = true;
  }

  *ppArray = pOffsetBlock;

  return (bCreated);
}

//  ----------------------------------------------------------------------------

void AdtArrays::copyAndGrowStack(char** ppArray,
                                 AdtStackInfo* pCurrentStackInfo,
                                 size_t nMinSizeNeeded) const
{
  // Note that we double the minimum required stack size so that we don't
  // get a re-size immediately after the current one. It should take some
  // time for the new to be exhausted.
  AdtVarType    nVarType          = pCurrentStackInfo->VarType;
  size_t        nSizeOf           = pCurrentStackInfo->SizeOf;
  size_t        nOldStackSize     = pCurrentStackInfo->StackSize;
  size_t        nNewStackSize     = nOldStackSize;
  size_t        nNewMinStackSize  = 2 * nMinSizeNeeded;
  char*         pNewStack         = 0;

  while (nNewStackSize < nNewMinStackSize)
  {
    nNewStackSize *= 2;
  }

  if (createStack(&pNewStack, nNewStackSize, nVarType))
  {
    ::memcpy(pNewStack, *ppArray, (nOldStackSize + 1) * nSizeOf); // Add 1 to account for possible 1 based array usage

    MemAllocator.free(*ppArray);

    *ppArray = pNewStack;
  }
}
