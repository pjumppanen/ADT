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
//    adtstack.cpp
//
//  Purpose:
//    This file includes implementations of classes for use in Auto-differentiation
//    code implemented in C++. In particular, it implements the stack support
//    required for the algorithmic differentiation tape.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtstack.hpp"

#ifdef _MSC_VER

  #include <windows.h>

#else

  #include <pthread.h>

#endif


//  ----------------------------------------------------------------------------

void PUSHREAL4SCALAR(AdtADStack& rStack, float fNum)
{
  rStack.push(fNum);
}

//  ----------------------------------------------------------------------------

void POPREAL4SCALAR(AdtADStack& rStack, float& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKREAL4SCALAR(AdtADStack& rStack, float& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHREAL4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPREAL4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHREAL8SCALAR(AdtADStack& rStack, double dNum)
{
  rStack.push(dNum);
}

//  ----------------------------------------------------------------------------

void POPREAL8SCALAR(AdtADStack& rStack, double& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKREAL8SCALAR(AdtADStack& rStack, double& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHREAL8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPREAL8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1SCALAR(AdtADStack& rStack, char cNum)
{
  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1SCALAR(AdtADStack& rStack, char& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER1SCALAR(AdtADStack& rStack, char& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1SCALAR(AdtADStack& rStack, unsigned char cNum)
{
  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2SCALAR(AdtADStack& rStack, short nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2SCALAR(AdtADStack& rStack, short& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER2SCALAR(AdtADStack& rStack, short& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2SCALAR(AdtADStack& rStack, unsigned short nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4SCALAR(AdtADStack& rStack, long nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4SCALAR(AdtADStack& rStack, long& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4SCALAR(AdtADStack& rStack, long& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4SCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4SCALAR(AdtADStack& rStack, int& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4SCALAR(AdtADStack& rStack, int& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned long nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL1BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL1BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL1BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL1BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL1BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL2BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL2BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL2BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL2BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL2BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL3BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL3BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL3BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL3BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL3BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL4BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL4BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL4BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL4BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL4BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  rStack.pop(rAllocator, pNum, nSize);
}


//  ----------------------------------------------------------------------------
//  AdtADStack implementations
//  ----------------------------------------------------------------------------
void AdtADStack::push(const char* pBuffer, size_t nSize)
{
  // On push if nSize is greater than half the Buffer size then we need to write
  // the unsaved buffer to disk and then write all but half a buffer size in
  // length of the data to the memory buffer, leaving the StackPtr at half the
  // buffer length.
  //
  // If the size is smaller than that then we do one of two things. If nSize is
  // less than the available size then we write the data to the memory buffer,
  // otherwise we write the buffer and the array less half a buffer size in data
  // so that the StackPtr is at half the buffer length. This will invariably
  // require some writing to disk and some memory moving operations.
  size_t  nHalfBufferSize = BufferSize / 2;

  if (nSize > nHalfBufferSize)
  {
    // Large push operation
    size_t  nBytesToWrite = nSize - nHalfBufferSize;

    // Write buffer contents
    ::fwrite(StackBuffer, StackPtr, 1, StackFile);

    // Write all but half a buffer of the source
    ::fwrite(pBuffer, nBytesToWrite, 1, StackFile);

    // Write the rest of the source to the buffer
    ::memcpy(StackBuffer, pBuffer + nBytesToWrite, nHalfBufferSize);

    StackPtr = nHalfBufferSize;
  }
  else
  {
    // Small push operation
    size_t  nAvailableSize = BufferSize - StackPtr;

    if (nSize < nAvailableSize)
    {
      // Write all data to memory buffer
      ::memcpy(StackBuffer + StackPtr, pBuffer, nSize);

      StackPtr += nSize;
    }
    else
    {
      // Write all but half a buffer size of data to disk leaving the half
      // buffer size part in memory
      size_t  nBytesToWrite = StackPtr + nSize - nHalfBufferSize;
      size_t  nBytesToMove  = StackPtr - nBytesToWrite;

      // Write buffer contents
      ::fwrite(StackBuffer, nBytesToWrite, 1, StackFile);

      // Move remainder of buffer to front
      ::memmove(StackBuffer, StackBuffer + nBytesToWrite, nBytesToMove);

      StackPtr = nBytesToMove;

      ::memcpy(StackBuffer + StackPtr, pBuffer, nSize);

      StackPtr += nSize;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(char* pBuffer, size_t nSize)
{
  if (nSize > StackPtr)
  {
    // Copy stack file data to correct location
    file_offset nCurrentFilePos;
    file_offset nReadFilePos;
    size_t      nRead           = 0;
    size_t      nBytesToRead    = nSize - StackPtr;
    size_t      nHalfBufferSize = BufferSize / 2;

    nCurrentFilePos = ::filetell(StackFile);

    if ((size_t)nCurrentFilePos < nBytesToRead)
    {
      throw(std::runtime_error(std::string("Stack push pop imbalance")));
    }

    nReadFilePos = nCurrentFilePos - nBytesToRead;

    ::fileseek(StackFile, nReadFilePos, SEEK_SET);
    nRead = ::fread(pBuffer, nBytesToRead, 1, StackFile);

    // Copy the buffer contents to correct destination location
    ::memcpy(pBuffer + nSize - StackPtr, StackBuffer, StackPtr);

    if ((size_t)nReadFilePos > nHalfBufferSize)
    {
      // Read one half a buffer size block of data into memory. This provides
      // a degree of stack hysteresis to mimimise disk accesses between push
      // and pop operations near the buffer boundaries.
      nReadFilePos -= nHalfBufferSize;

      ::fileseek(StackFile, nReadFilePos, SEEK_SET);
      nRead = ::fread(StackBuffer, nHalfBufferSize, 1, StackFile);
      ::fileseek(StackFile, nReadFilePos, SEEK_SET);

      StackPtr = nHalfBufferSize;
    }
    else
    {
      // Read the entire disk content into buffer.
      nBytesToRead = (size_t)nReadFilePos;
      nReadFilePos = 0;
      StackPtr     = nBytesToRead;

      ::fileseek(StackFile, nReadFilePos, SEEK_SET);
      nRead = ::fread(StackBuffer, nBytesToRead, 1, StackFile);
      ::fileseek(StackFile, nReadFilePos, SEEK_SET);
    }
  }
  else
  {
    // Entire data is in stack buffer so simply write stack buffer contents
    // to the destination buffer
    ::memcpy(pBuffer, StackBuffer + StackPtr - nSize, nSize);

    StackPtr -= nSize;
  }
}

//  ----------------------------------------------------------------------------

void AdtADStack::look(char* pBuffer, size_t nSize)
{
  if (nSize > StackPtr)
  {
    // Copy stack file data to correct location
    file_offset nCurrentFilePos;
    file_offset nReadFilePos;
    size_t      nRead        = 0;
    size_t      nBytesToRead = nSize - StackPtr;

    nCurrentFilePos = ::filetell(StackFile);

    if ((size_t)nCurrentFilePos < nBytesToRead)
    {
      throw(std::runtime_error(std::string("Stack push pop imbalance")));
    }

    nReadFilePos = nCurrentFilePos - nBytesToRead;

    ::fileseek(StackFile, nReadFilePos, SEEK_SET);
    nRead = ::fread(pBuffer, nBytesToRead, 1, StackFile);
    ::fileseek(StackFile, nCurrentFilePos, SEEK_SET);

    // Copy the buffer contents to correct destination location
    ::memcpy(pBuffer + nSize - StackPtr, StackBuffer, StackPtr);
  }
  else
  {
    // Entire data is in stack buffer so simply write stack buffer contents
    // to the destination buffer
    ::memcpy(pBuffer, StackBuffer + StackPtr - nSize, nSize);
  }
}

//  ----------------------------------------------------------------------------

AdtADStack::AdtADStack(size_t nBufferSize)
{
  ::memset(StackFileName, 0, sizeof(StackFileName));

  StackFile   = 0;
  BufferSize  = 0;
  StackBuffer = 0;
  StackPtr    = 0;

  if (nBufferSize > 0)
  {
    char* pTmpFileName = tempnam(0, "adttmpstack");

    strcpy(StackFileName, pTmpFileName);

    StackFile   = ::fopen(StackFileName, "wb+");
    BufferSize  = nBufferSize;
    StackBuffer = new char[nBufferSize];

    if (StackFile == 0)
    {
      throw(std::runtime_error(std::string("Stack file creation failed")));
    }

    if (StackBuffer == 0)
    {
      throw(std::runtime_error(std::string("Stack buffer creation failed")));
    }
  }
  else
  {
    throw(std::runtime_error(std::string("Stack buffer size must be greater than 0")));
  }
}

//  ----------------------------------------------------------------------------

AdtADStack::~AdtADStack()
{
  if (StackFile != 0)
  {
    fclose(StackFile);
    unlink(StackFileName);
  }

  if (StackBuffer != 0)
  {
    delete StackBuffer;
  }
}

//  ----------------------------------------------------------------------------

int AdtADStack::baseIndex(const AdtMemAllocator& rAllocator, char* pArray, int nSize) const
{
  int                   nIndex  = 0;
  const AdtArrayInfo*   pInfo   = AdtArrayPlanActor::arrayInfo(rAllocator, pArray);

  if (pInfo == 0)
  {
    throw(std::runtime_error(std::string("push/pop operation on invalid array")));
  }

  const AdtArrayCoord&  rCoord  = pInfo->Actor->coord(0);

  if (rCoord.Size != nSize)
  {
    throw(std::runtime_error(std::string("push/pop array size parameter inconsistent with actual array size")));
  }

  return (rCoord.IndexBase);
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::push(const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  push((const char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

//  ----------------------------------------------------------------------------

void AdtADStack::pop(const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize)
{
  int nIndex = baseIndex(rAllocator, (char*)pNum, nSize);

  pop((char*)&pNum[nIndex], nSize * sizeof(*pNum));
}

