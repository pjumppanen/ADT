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
//  AdtADStackImpl implementations
//  ----------------------------------------------------------------------------
void AdtADStackImpl::push(const char* pBuffer, size_t nSize)
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
      switch(nSize)
      {
        case 1:
        {
          *(StackBuffer + StackPtr) = *(pBuffer);
          break;
        }
        
        case 2:
        {
          *((int16_t*)(StackBuffer + StackPtr)) = *((int16_t*)pBuffer);
          break;
        }
        
        case 4:
        {
          *((int32_t*)(StackBuffer + StackPtr)) = *((int32_t*)pBuffer);
          break;
        }
        
        case 8:
        {
          *((int64_t*)(StackBuffer + StackPtr)) = *((int64_t*)pBuffer);
          break;
        }

        default:
        {
          ::memcpy(StackBuffer + StackPtr, pBuffer, nSize);
          break;
        }
      }

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

void AdtADStackImpl::pop(char* pBuffer, size_t nSize)
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
    switch(nSize)
    {
      case 1:
      {
        *(pBuffer) = *(StackBuffer + StackPtr - 1);
        break;
      }
      
      case 2:
      {
        *((int16_t*)pBuffer) = *((int16_t*)(StackBuffer + StackPtr - 2));
        break;
      }
      
      case 4:
      {
        *((int32_t*)pBuffer) = *((int32_t*)(StackBuffer + StackPtr - 4));
        break;
      }
      
      case 8:
      {
        *((int64_t*)pBuffer) = *((int64_t*)(StackBuffer + StackPtr - 8));
        break;
      }

      default:
      {
        ::memcpy(pBuffer, StackBuffer + StackPtr - nSize, nSize);
        break;
      }
    }

    StackPtr -= nSize;
  }
}

//  ----------------------------------------------------------------------------

void AdtADStackImpl::look(char* pBuffer, size_t nSize) const
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
    switch(nSize)
    {
      case 1:
      {
        *(pBuffer) = *(StackBuffer + StackPtr - 1);
        break;
      }
      
      case 2:
      {
        *((int16_t*)pBuffer) = *((int16_t*)(StackBuffer + StackPtr - 2));
        break;
      }
      
      case 4:
      {
        *((int32_t*)pBuffer) = *((int32_t*)(StackBuffer + StackPtr - 4));
        break;
      }
      
      case 8:
      {
        *((int64_t*)pBuffer) = *((int64_t*)(StackBuffer + StackPtr - 8));
        break;
      }

      default:
      {
        ::memcpy(pBuffer, StackBuffer + StackPtr - nSize, nSize);
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtADStackImpl::AdtADStackImpl(size_t nBufferSize, const char* pSuffix)
{
  ::memset(StackFileName, 0, sizeof(StackFileName));

  StackFile   = 0;
  BufferSize  = 0;
  StackBuffer = 0;
  StackPtr    = 0;

  if ((nBufferSize > 0) && (pSuffix != 0))
  {
    strcat(StackFileName, "adttmpstack");
    strcat(StackFileName, pSuffix);

    char* pTmpFileName = tempnam(0, StackFileName);

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

AdtADStackImpl::~AdtADStackImpl()
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

void AdtADStackImpl::memoryAndLength(const AdtMemAllocator& rAllocator, char* pArray, int nSize, char*& pData, size_t& nDataSize) const
{
  int           nIndex  = 0;
  AdtArrayInfo* pInfo   = AdtArrayPlanActor::arrayInfo(rAllocator, pArray);

  if (pInfo == 0)
  {
    throw(std::runtime_error(std::string("push/pop operation on invalid array")));
  }

  pData     = pInfo->firstData();
  nDataSize = pInfo->lengthOfData();
}

//  ----------------------------------------------------------------------------

void AdtADStackImpl::pushArray(const AdtMemAllocator& rAllocator, const char* pArray, int nSize)
{
  char*   pData     = 0;
  size_t  nDataSize = 0;

  memoryAndLength(rAllocator, (char*)pArray, nSize, pData, nDataSize);

  push(pData, nDataSize);
}

//  ----------------------------------------------------------------------------

void AdtADStackImpl::popArray(const AdtMemAllocator& rAllocator, char* pArray, int nSize)
{
  char*   pData     = 0;
  size_t  nDataSize = 0;

  memoryAndLength(rAllocator, pArray, nSize, pData, nDataSize);

  pop(pData, nDataSize);
}


//  ----------------------------------------------------------------------------
//  AdtADBitStackImpl method implementations
//  ----------------------------------------------------------------------------
void AdtADBitStackImpl::pushBit(bool bBit)
{
  int nMask = 1 << adbitibuf;

  if (bBit)
  {
    adbitbuf = adbitbuf | nMask;
  }
  else
  {
    adbitbuf = adbitbuf & (~nMask);
  }
  
  if (adbitibuf >= 31)
  {
    push((char*)&adbitbuf, sizeof(adbitbuf));
    
    adbitbuf  = 0;
    adbitibuf = 0;
  }
  else
  {
    adbitibuf = adbitibuf + 1;
  }
}

//  ----------------------------------------------------------------------------

bool AdtADBitStackImpl::popBit()
{
  bool bBit;

  if (adbitibuf <= 0)
  {
    pop((char*)&adbitbuf, sizeof(adbitbuf));

    adbitibuf = 31;
  }
  else
  {
    adbitibuf = adbitibuf - 1;
  }

  int nMask = 1 << adbitibuf;

  bBit = ((adbitbuf & nMask) != 0);

  return (bBit);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::pushBits(int nNum, int nHowMany)
{
  unsigned int nMask = 1;

  for (int cn = 0 ; cn < nHowMany ; cn++)
  {
    bool bBit = ((((unsigned int)nNum) & nMask) != 0);

    pushBit(bBit);

    nMask <<= 1;
  }
}

//  ----------------------------------------------------------------------------

int AdtADBitStackImpl::popBits(int nHowMany)
{
  unsigned int nMask = 1 << (nHowMany - 1);
  unsigned int nNum  = 0;

  for (int cn = 0 ; cn < nHowMany ; cn++)
  {
    bool bBit = popBit();
    
    if (bBit)
    {
      nNum = nNum | nMask;
    }

    nMask >>= 1;
  }

  return ((int)nNum);
}

//  ----------------------------------------------------------------------------

int AdtADBitStackImpl::lookBits(int nHowMany) const
{
  unsigned int nMask  = 1 << (nHowMany - 1);
  unsigned int nNum   = 0;
  int nBit            = adbitibuf;
  int nBitField       = adbitbuf;

  for (int cn = 0 ; cn < nHowMany ; cn++)
  {
    if (nBit <= 0)
    {
      look((char*)&nBitField, sizeof(nBitField));

      nBit = 31;
    }
    else
    {
      nBit = nBit - 1;
    }

    int   nPopMask = 1 << nBit;
    bool  bBit     = ((nBitField & nPopMask) != 0);
    
    if (bBit)
    {
      nNum = nNum | nMask;
    }

    nMask >>= 1;
  }

  return ((int)nNum);
}

//  ----------------------------------------------------------------------------

AdtADBitStackImpl::AdtADBitStackImpl(size_t nBufferSize, const char* pSuffix)
 : AdtADStackImpl(nBufferSize, pSuffix)
{
  adbitbuf  = 0;
  adbitibuf = 0;
  bitcount  = 0;
  callcount = 0;
}

//  ----------------------------------------------------------------------------

AdtADBitStackImpl::~AdtADBitStackImpl()
{

}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::PUSHCONTROL1BSCALAR(int nNum)
{
  bitcount++;
  callcount++;
  push((char*)&nNum, sizeof(nNum));
//  pushBits(nNum, 1);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::POPCONTROL1BSCALAR(int& nNum)
{
  bitcount--;
  callcount--;
//  pop((char*)&nNum, sizeof(nNum));
  nNum = popBits(1);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::LOOKCONTROL1BSCALAR(int& nNum) const
{
//  look((char*)&nNum, sizeof(nNum));
  nNum = lookBits(1);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::PUSHCONTROL2BSCALAR(int nNum)
{
  bitcount += 2;
  callcount++;
//  push((char*)&nNum, sizeof(nNum));
  pushBits(nNum, 2);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::POPCONTROL2BSCALAR(int& nNum)
{
  bitcount -= 2;
  callcount--;
//  pop((char*)&nNum, sizeof(nNum));
  nNum = popBits(2);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::LOOKCONTROL2BSCALAR(int& nNum) const
{
//  look((char*)&nNum, sizeof(nNum));
  nNum = lookBits(2);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::PUSHCONTROL3BSCALAR(int nNum)
{
  bitcount += 3;
  callcount++;
  pushBits(nNum, 3);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::POPCONTROL3BSCALAR(int& nNum)
{
  bitcount -= 3;
  callcount--;
  nNum = popBits(3);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::LOOKCONTROL3BSCALAR(int& nNum) const
{
  nNum = lookBits(3);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::PUSHCONTROL4BSCALAR(int nNum)
{
  bitcount += 4;
  callcount++;
  pushBits(nNum, 4);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::POPCONTROL4BSCALAR(int& nNum)
{
  bitcount -= 4;
  callcount--;
  nNum = popBits(4);
}

//  ----------------------------------------------------------------------------

void AdtADBitStackImpl::LOOKCONTROL4BSCALAR(int& nNum) const
{
  nNum = lookBits(4);
}


//  ----------------------------------------------------------------------------
//  AdtADStack method implementations
//  ----------------------------------------------------------------------------
AdtADStack::AdtADStack(size_t nBufferSize)
 : FloatStack(nBufferSize, "_float"),
   DoubleStack(nBufferSize, "_double"),
   CharStack(nBufferSize, "_char"),
   UCharStack(nBufferSize, "_uchar"),
   ShortStack(nBufferSize, "_short"),
   UShortStack(nBufferSize, "_ushort"),
   LongStack(nBufferSize, "_long"),
   ULongStack(nBufferSize, "_ulong"),
   IntStack(nBufferSize, "_int"),
   UIntStack(nBufferSize, "_uint"),
   BoolStack(nBufferSize, "_bool")
{

}

//  ----------------------------------------------------------------------------

AdtADStack::~AdtADStack()
{

}

//  ----------------------------------------------------------------------------


