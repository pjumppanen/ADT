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

void PUSHREAL4(float fNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R4();

  rStack.push(fNum);
}

//  ----------------------------------------------------------------------------

void POPREAL4(float& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R4();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKREAL4(float& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R4();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R4();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R4();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHREAL8(double dNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R8();

  rStack.push(dNum);
}

//  ----------------------------------------------------------------------------

void POPREAL8(double& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R8();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKREAL8(double& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R8();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R8();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_R8();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1(char cNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1(char& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER1(char& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1(unsigned char cNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1(unsigned char& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER1(unsigned char& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I1();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2(short nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2(short& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER2(short& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2(unsigned short nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2(unsigned short& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER2(unsigned short& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I2();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4(long nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4(long& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4(long& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4(int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4(int& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4(int& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4(unsigned long nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4(unsigned long& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4(unsigned long& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4(unsigned int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4(unsigned int& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

void LOOKINTEGER4(unsigned int& rNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_I4();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL1B(int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL1B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL1B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL1BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL1BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL2B(int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL2B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL2B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL2BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL2BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL3B(int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL3B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL3B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL3BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL3BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL4B(int nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

void POPCONTROL4B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

void LOOKCONTROL4B(int& nNum)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

void PUSHCONTROL4BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

  rStack.push(rAllocator, pNum, nSize);
}

//  ----------------------------------------------------------------------------

void POPCONTROL4BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize)
{
  AdtADStack& rStack = AdtADStackGroupSingleton::stack_B();

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


//  ----------------------------------------------------------------------------
//  AdtADStackGroup implementations
//  ----------------------------------------------------------------------------
AdtADStackGroup::AdtADStackGroup(size_t nBufferSize)
{
  BufferSize  = nBufferSize;
  Stack_R4    = 0;
  Stack_R8    = 0;
  Stack_I1    = 0;
  Stack_I2    = 0;
  Stack_I4    = 0;
  Stack_B     = 0;
}

//  ----------------------------------------------------------------------------

AdtADStackGroup::~AdtADStackGroup()
{
  if (Stack_R4 != 0)
  {
    delete Stack_R4;
  }

  if (Stack_R8 != 0)
  {
    delete Stack_R8;
  }

  if (Stack_I1 != 0)
  {
    delete Stack_I1;
  }

  if (Stack_I2 != 0)
  {
    delete Stack_I2;
  }

  if (Stack_I4 != 0)
  {
    delete Stack_I4;
  }

  if (Stack_B != 0)
  {
    delete Stack_B;
  }
}


//  ----------------------------------------------------------------------------
//  AdtADStackGroupSingleton implementations
//  ----------------------------------------------------------------------------
AdtADStackGroupPtrByThreadIdTypeMap   AdtADStackGroupSingleton::Map;
long                                  AdtADStackGroupSingleton::Lock        = 0;
size_t                                AdtADStackGroupSingleton::BufferSize  = 256 * 1024; //256 kB buffer size
AdtADStackGroupSingleton              ADStackGroupSingleton;

//  ----------------------------------------------------------------------------

void AdtADStackGroupSingleton::onExit()
{
  // Destroy all AdtADStackGroup instances.
  AdtADStackGroupPtrByThreadIdTypeMapIter Iter;

  for (Iter = Map.begin() ; Iter != Map.end() ; ++Iter)
  {
    AdtADStackGroup*  pStackGroup = (*Iter).second;

    if (pStackGroup != 0)
    {
      delete pStackGroup;
    }
  }

  Map.clear();
}

//  ----------------------------------------------------------------------------
#ifdef _MSC_VER
void AdtADStackGroupSingleton::beginMutex()
{
  long nLock = ::InterlockedIncrement(&Lock);

  while (nLock != 1)
  {
    ::InterlockedDecrement(&Lock);
    ::Sleep(0);

    nLock = ::InterlockedIncrement(&Lock);
  }
}

//  ----------------------------------------------------------------------------

void AdtADStackGroupSingleton::endMutex()
{
  ::InterlockedDecrement(&Lock);
}
#else
//  ----------------------------------------------------------------------------

void AdtADStackGroupSingleton::beginMutex()
{
  long nLock = __sync_add_and_fetch(&Lock, 1);

  while (nLock != 1)
  {
    __sync_sub_and_fetch(&Lock, 1);
    sleep(0);

    nLock = __sync_add_and_fetch(&Lock, 1);
  }
}

//  ----------------------------------------------------------------------------

void AdtADStackGroupSingleton::endMutex()
{
  __sync_sub_and_fetch(&Lock, 1);
}
#endif
//  ----------------------------------------------------------------------------

AdtADStackGroupSingleton::AdtADStackGroupSingleton()
{
  // Register callback to cleanup on exit
  atexit(AdtADStackGroupSingleton::onExit);
}

//  ----------------------------------------------------------------------------

AdtADStackGroupSingleton::~AdtADStackGroupSingleton()
{
  // do nothing
}

//  ----------------------------------------------------------------------------

AdtADStackGroup& AdtADStackGroupSingleton::stackGroup()
{
  AdtADStackGroup*  pGroup    = 0;
  ThreadIdType      nThreadId = currentThreadId();

  beginMutex();

  // If the buffer doesn't exist yet then create it.
  AdtADStackGroupPtrByThreadIdTypeMapIter Iter = Map.find(nThreadId);

  if (Iter != Map.end())
  {
    pGroup          = (*Iter).second;
  }
  else
  {
    pGroup          = new AdtADStackGroup(BufferSize);
    Map[nThreadId]  = pGroup;
  }

  endMutex();

  if (pGroup == 0)
  {
    throw(std::runtime_error(std::string("AdtADStackGroup instance creation failed")));
  }

  return (*pGroup);
}
