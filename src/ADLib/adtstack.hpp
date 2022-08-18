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
//    adtstack.hpp
//
//  Purpose:
//    This file includes declarations of classes for use in Auto-differentiation
//    code implemented in C++. In particular, it implements the stack support
//    required for the algorithmic differentiation tape.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADT_STACK__
#define __ADT_STACK__


#ifndef AD

#include <stdio.h>
#include "adtarrays.hpp"


#ifdef _MSC_VER

  #define currentThreadId   GetCurrentThreadId
  #define ThreadIdType      unsigned long

  #define fileseek          _fseeki64
  #define filetell          _ftelli64
  #define file_offset       __int64

  //  ----------------------------------------------------------------------------
  //  Disable C4996 warning message
  //  ----------------------------------------------------------------------------
  //  'foo': This function or variable may be unsafe. Consider using foo_s instead.
  //  To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
  //  ----------------------------------------------------------------------------
  #pragma warning(disable : 4996)

#else

  #include <pthread.h>

  #define currentThreadId   pthread_self
  #define ThreadIdType      pthread_t

  #define fileseek          fseeko
  #define filetell          ftello
  #define file_offset       off_t

  #include <unistd.h>

#endif


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtADStack;


//  ----------------------------------------------------------------------------
//  Wrapper macros to incorporate Allocator into Tapenade Array push/pop calls
//  ----------------------------------------------------------------------------
#define PUSHREAL4(A)            Stack.PUSHREAL4SCALAR((A))
#define POPREAL4(A)             Stack.POPREAL4SCALAR((A))
#define LOOKREAL4(A)            Stack.LOOKREAL4SCALAR((A))
#define PUSHREAL4ARRAY(A,B)     Stack.PUSHREAL4ARRAY_allocator(MemAllocator, (A), (B))
#define POPREAL4ARRAY(A,B)      Stack.POPREAL4ARRAY_allocator(MemAllocator, (A), (B))
#define PUSHREAL8(A)            Stack.PUSHREAL8SCALAR((A))
#define POPREAL8(A)             Stack.POPREAL8SCALAR((A))
#define LOOKREAL8(A)            Stack.LOOKREAL8SCALAR((A))
#define PUSHREAL8ARRAY(A,B)     Stack.PUSHREAL8ARRAY_allocator(MemAllocator, (A), (B))
#define POPREAL8ARRAY(A,B)      Stack.POPREAL8ARRAY_allocator(MemAllocator, (A), (B))
//#define PUSHREAL16(A)            Stack.PUSHREAL16SCALAR((A))
//#define POPREAL16(A)             Stack.POPREAL16SCALAR((A))
//#define LOOKREAL16(A)            Stack.LOOKREAL16SCALAR((A))
// #define PUSHREAL16ARRAY(A,B)    Stack.PUSHREAL16ARRAY_allocator(MemAllocator, (A), (B))
// #define POPREAL16ARRAY(A,B)     Stack.POPREAL16ARRAY_allocator(MemAllocator, (A), (B))
#define PUSHINTEGER1(A)         Stack.PUSHINTEGER1SCALAR((A))
#define POPINTEGER1(A)          Stack.POPINTEGER1SCALAR((A))
#define LOOKINTEGER1(A)         Stack.LOOKINTEGER1SCALAR((A))
#define PUSHINTEGER1ARRAY(A,B)  Stack.PUSHINTEGER1ARRAY_allocator(MemAllocator, (A), (B))
#define POPINTEGER1ARRAY(A,B)   Stack.POPINTEGER1ARRAY_allocator(MemAllocator, (A), (B))
#define PUSHINTEGER2(A)         Stack.PUSHINTEGER2SCALAR((A))
#define POPINTEGER2(A)          Stack.POPINTEGER2SCALAR((A))
#define LOOKINTEGER2(A)         Stack.LOOKINTEGER2SCALAR((A))
#define PUSHINTEGER2ARRAY(A,B)  Stack.PUSHINTEGER2ARRAY_allocator(MemAllocator, (A), (B))
#define POPINTEGER2ARRAY(A,B)   Stack.POPINTEGER2ARRAY_allocator(MemAllocator, (A), (B))
#define PUSHINTEGER4(A)         Stack.PUSHINTEGER4SCALAR((A))
#define POPINTEGER4(A)          Stack.POPINTEGER4SCALAR((A))
#define LOOKINTEGER4(A)         Stack.LOOKINTEGER4SCALAR((A))
#define PUSHINTEGER4ARRAY(A,B)  Stack.PUSHINTEGER4ARRAY_allocator(MemAllocator, (A), (B))
#define POPINTEGER4ARRAY(A,B)   Stack.POPINTEGER4ARRAY_allocator(MemAllocator, (A), (B))
// #define PUSHINTEGER8(A)         Stack.PUSHINTEGER8SCALAR((A))
// #define POPINTEGER8(A)          Stack.POPINTEGER8SCALAR((A))
// #define LOOKINTEGER8(A)         Stack.LOOKINTEGER8SCALAR((A))
// #define PUSHINTEGER8ARRAY(A,B)  Stack.PUSHINTEGER8ARRAY_allocator(MemAllocator, (A), (B))
// #define POPINTEGER8ARRAY(A,B)   Stack.POPINTEGER8ARRAY_allocator(MemAllocator, (A), (B))
#define PUSHCONTROL1B(A)        Stack.PUSHCONTROL1BSCALAR((A))
#define POPCONTROL1B(A)         Stack.POPCONTROL1BSCALAR((A))
#define LOOKCONTROL1B(A)        Stack.LOOKCONTROL1BSCALAR((A))
#define PUSHCONTROL2B(A)        Stack.PUSHCONTROL2BSCALAR((A))
#define POPCONTROL2B(A)         Stack.POPCONTROL2BSCALAR((A))
#define LOOKCONTROL2B(A)        Stack.LOOKCONTROL2BSCALAR((A))
#define PUSHCONTROL3B(A)        Stack.PUSHCONTROL3BSCALAR((A))
#define POPCONTROL3B(A)         Stack.POPCONTROL3BSCALAR((A))
#define LOOKCONTROL3B(A)        Stack.LOOKCONTROL3BSCALAR((A))
#define PUSHCONTROL4B(A)        Stack.PUSHCONTROL4BSCALAR((A))
#define POPCONTROL4B(A)         Stack.POPCONTROL4BSCALAR((A))
#define LOOKCONTROL4B(A)        Stack.LOOKCONTROL4BSCALAR((A))


//  ----------------------------------------------------------------------------
//  class AdtADStackImpl
//  ----------------------------------------------------------------------------
//  This class implements a disk based stack that pages memory to disk to free
//  space in the buffer when space is exhausted. This approach is likely  to
//  be more efficient that growing the stack and relying on operating system
//  provided paging to take care of the rest. Should aim to minimise page faults
//  as they are costly and this should do just that.
//  ----------------------------------------------------------------------------
class AdtADStackImpl
{
private:
  FILE*       StackFile;
  char        StackFileName[1024];
  char*       StackBuffer;
  size_t      BufferSize;
  size_t      StackPtr;

protected:
  void        memoryAndLength(const AdtMemAllocator& rAllocator, char* pArray, int nSize, char*& pData, size_t& nDataSize) const;

public:
  AdtADStackImpl(size_t nBufferSize, const char* pSuffix);
  virtual ~AdtADStackImpl();

  void        push(const char* pBuffer, size_t nSize);
  void        pop(char* pBuffer, size_t nSize);
  void        look(char* pBuffer, size_t nSize) const;
  void        pushArray(const AdtMemAllocator& rAllocator, const char* pArray, int nSize);
  void        popArray(const AdtMemAllocator& rAllocator, char* pArray, int nSize);

  size_t      bufferSize() const;
};

//  ----------------------------------------------------------------------------

inline size_t AdtADStackImpl::bufferSize() const
{
  return (BufferSize);
}


//  ----------------------------------------------------------------------------
//  class AdtADBitStackImpl
//  ----------------------------------------------------------------------------
class AdtADBitStackImpl : public AdtADStackImpl
{
private:
  int           adbitbuf;
  int           adbitibuf;
  int           bitcount;
  int           callcount;

private:
  void          pushBit(bool bBit);
  bool          popBit();
  void          pushBits(int nNum, int nHowMany);
  int           popBits(int nHowMany);
  int           lookBits(int nHowMany) const;

public:
  AdtADBitStackImpl(size_t nBufferSize, const char* pSuffix);
  virtual ~AdtADBitStackImpl();

  void          PUSHCONTROL1BSCALAR(int nNum);
  void          POPCONTROL1BSCALAR(int& nNum);
  void          LOOKCONTROL1BSCALAR(int& nNum) const;

  // Push, Pop, Look 2 bits
  void          PUSHCONTROL2BSCALAR(int nNum);
  void          POPCONTROL2BSCALAR(int& nNum);
  void          LOOKCONTROL2BSCALAR(int& nNum) const;

  // Push, Pop, Look 3 bits
  void          PUSHCONTROL3BSCALAR(int nNum);
  void          POPCONTROL3BSCALAR(int& nNum);
  void          LOOKCONTROL3BSCALAR(int& nNum) const;

  // Push, Pop, Look 4 bits
  void          PUSHCONTROL4BSCALAR(int nNum);
  void          POPCONTROL4BSCALAR(int& nNum);
  void          LOOKCONTROL4BSCALAR(int& nNum) const;
};


//  ----------------------------------------------------------------------------
//  class AdtADStack
//  ----------------------------------------------------------------------------
class AdtADStack
{
private:
  AdtADStackImpl    FloatStack;
  AdtADStackImpl    DoubleStack;
  AdtADStackImpl    CharStack;
  AdtADStackImpl    UCharStack;
  AdtADStackImpl    ShortStack;
  AdtADStackImpl    UShortStack;
  AdtADStackImpl    LongStack;
  AdtADStackImpl    ULongStack;
  AdtADStackImpl    IntStack;
  AdtADStackImpl    UIntStack;
  AdtADBitStackImpl BoolStack;

public:
  AdtADStack(size_t nBufferSize);
  virtual ~AdtADStack();

  void            PUSHREAL4SCALAR(float fNum);
  void            POPREAL4SCALAR(float& rNum);
  void            LOOKREAL4SCALAR(float& rNum);

  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9F pArray, int nSize);
  void            PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10F pArray, int nSize);
  void            POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10F pArray, int nSize);

  void            PUSHREAL8SCALAR(double dNum);
  void            POPREAL8SCALAR(double& rNum);
  void            LOOKREAL8SCALAR(double& rNum);

  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9D pArray, int nSize);
  void            PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10D pArray, int nSize);
  void            POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10D pArray, int nSize);

// Not supported at this stage. Most C++ compilers have sizeof(double) == sizeof(long double)
// ----------------------------------------------------
//  void            PUSHREAL16SCALAR(long double dNum);
//  void            POPREAL16SCALAR(long double& rNum);
//  void            LOOKREAL16SCALAR(long double& rNum);

  void            PUSHINTEGER1SCALAR(char cNum);
  void            POPINTEGER1SCALAR(char& rNum);
  void            LOOKINTEGER1SCALAR(char& rNum);

  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9C pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10C pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10C pArray, int nSize);

  void            PUSHINTEGER1SCALAR(unsigned char cNum);
  void            POPINTEGER1SCALAR(unsigned char& rNum);
  void            LOOKINTEGER1SCALAR(unsigned char& rNum);

  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UC pArray, int nSize);
  void            PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UC pArray, int nSize);
  void            POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UC pArray, int nSize);

  void            PUSHINTEGER2SCALAR(short nNum);
  void            POPINTEGER2SCALAR(short& rNum);
  void            LOOKINTEGER2SCALAR(short& rNum);

  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9S pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10S pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10S pArray, int nSize);

  void            PUSHINTEGER2SCALAR(unsigned short nNum);
  void            POPINTEGER2SCALAR(unsigned short& rNum);
  void            LOOKINTEGER2SCALAR(unsigned short& rNum);

  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9US pArray, int nSize);
  void            PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10US pArray, int nSize);
  void            POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10US pArray, int nSize);

  void            PUSHINTEGER4SCALAR(long nNum);
  void            POPINTEGER4SCALAR(long& rNum);
  void            LOOKINTEGER4SCALAR(long& rNum);

  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9L pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10L pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10L pArray, int nSize);

  void            PUSHINTEGER4SCALAR(int nNum);
  void            POPINTEGER4SCALAR(int& rNum);
  void            LOOKINTEGER4SCALAR(int& rNum);

  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9I pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10I pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10I pArray, int nSize);

  void            PUSHINTEGER4SCALAR(unsigned long nNum);
  void            POPINTEGER4SCALAR(unsigned long& rNum);
  void            LOOKINTEGER4SCALAR(unsigned long& rNum);

  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UL pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UL pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UL pArray, int nSize);

  void            PUSHINTEGER4SCALAR(unsigned int nNum);
  void            POPINTEGER4SCALAR(unsigned int& rNum);
  void            LOOKINTEGER4SCALAR(unsigned int& rNum);

  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UI pArray, int nSize);
  void            PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UI pArray, int nSize);
  void            POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UI pArray, int nSize);

// Not supported at this stage and probably not needed.
// ----------------------------------------------------
//  void            PUSHINTEGER8SCALAR(long long nNum);
//  void            POPINTEGER8SCALAR(long long& rNum);
//  void            LOOKINTEGER8SCALAR(long long& rNum);

  // Push, Pop, Look 1 bit
  void            PUSHCONTROL1BSCALAR(int nNum);
  void            POPCONTROL1BSCALAR(int& nNum);
  void            LOOKCONTROL1BSCALAR(int& nNum);

  // Push, Pop, Look 2 bits
  void            PUSHCONTROL2BSCALAR(int nNum);
  void            POPCONTROL2BSCALAR(int& nNum);
  void            LOOKCONTROL2BSCALAR(int& nNum);

  // Push, Pop, Look 3 bits
  void            PUSHCONTROL3BSCALAR(int nNum);
  void            POPCONTROL3BSCALAR(int& nNum);
  void            LOOKCONTROL3BSCALAR(int& nNum);

  // Push, Pop, Look 4 bits
  void            PUSHCONTROL4BSCALAR(int nNum);
  void            POPCONTROL4BSCALAR(int& nNum);
  void            LOOKCONTROL4BSCALAR(int& nNum);

  size_t          bufferSize() const;
};

//  ----------------------------------------------------------------------------

inline size_t AdtADStack::bufferSize() const
{
  return (FloatStack.bufferSize());
}


//  ----------------------------------------------------------------------------
//  Tapenade stack function wrappers
//  ----------------------------------------------------------------------------
inline void AdtADStack::PUSHREAL4SCALAR(float rNum)
{
  FloatStack.push((const char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4SCALAR(float& rNum)
{
  FloatStack.pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKREAL4SCALAR(float& rNum)
{
  FloatStack.look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8SCALAR(double rNum)
{
  DoubleStack.push((const char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8SCALAR(double& rNum)
{
  DoubleStack.pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKREAL8SCALAR(double& rNum)
{
  DoubleStack.look((char*)&rNum, sizeof(rNum));
}

// Not supported at this stage. Most C++ compilers have sizeof(double) == sizeof(long double)
//  //  ----------------------------------------------------------------------------
//
//  inline void AdtADStack::PUSHREAL16SCALAR(long double rNum)
//  {
//    LongDoubleStack.push((const char*)&rNum, sizeof(rNum));
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void AdtADStack::POPREAL16SCALAR(long double& rNum)
//  {
//    LongDoubleStack.pop((char*)&rNum, sizeof(rNum));
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void AdtADStack::LOOKREAL16SCALAR(long double& rNum)
//  {
//    LongDoubleStack.look((char*)&rNum, sizeof(rNum));
//  }
//  
//  //  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1SCALAR(char nNum)
{
  CharStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1SCALAR(char& nNum)
{
  CharStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER1SCALAR(char& nNum)
{
  CharStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1SCALAR(unsigned char nNum)
{
  UCharStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1SCALAR(unsigned char& nNum)
{
  UCharStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER1SCALAR(unsigned char& nNum)
{
  UCharStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2SCALAR(short nNum)
{
  ShortStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2SCALAR(short& nNum)
{
  ShortStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER2SCALAR(short& nNum)
{
  ShortStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2SCALAR(unsigned short nNum)
{
  UShortStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2SCALAR(unsigned short& nNum)
{
  UShortStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER2SCALAR(unsigned short& nNum)
{
  UShortStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4SCALAR(long nNum)
{
  LongStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4SCALAR(long& nNum)
{
  LongStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER4SCALAR(long& nNum)
{
  LongStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4SCALAR(int nNum)
{
  IntStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4SCALAR(int& nNum)
{
  IntStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER4SCALAR(int& nNum)
{
  IntStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4SCALAR(unsigned long nNum)
{
  ULongStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4SCALAR(unsigned long& nNum)
{
  ULongStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER4SCALAR(unsigned long& nNum)
{
  ULongStack.look((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4SCALAR(unsigned int nNum)
{
  UIntStack.push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4SCALAR(unsigned int& nNum)
{
  UIntStack.pop((char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKINTEGER4SCALAR(unsigned int& nNum)
{
  UIntStack.look((char*)&nNum, sizeof(nNum));
}

// Not supported at this stage and probably not needed.
//  //  ----------------------------------------------------------------------------
//  
//  inline void AdtADStack::PUSHINTEGER8SCALAR(long long nNum)
//  {
//    LongLongStack.push((const char*)&nNum, sizeof(nNum));
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void AdtADStack::POPINTEGER8SCALAR(long long& nNum)
//  {
//    LongLongStack.pop((char*)&nNum, sizeof(nNum));
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void LOOKINTEGER8SCALAR(long long& nNum)
//  {
//    LongLongStack.look((char*)&nNum, sizeof(nNum));
//  }
//  
//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHCONTROL1BSCALAR(int nNum)
{
  BoolStack.PUSHCONTROL1BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPCONTROL1BSCALAR(int& nNum)
{
  BoolStack.POPCONTROL1BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKCONTROL1BSCALAR(int& nNum)
{
  BoolStack.LOOKCONTROL1BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHCONTROL2BSCALAR(int nNum)
{
  BoolStack.PUSHCONTROL2BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPCONTROL2BSCALAR(int& nNum)
{
  BoolStack.POPCONTROL2BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKCONTROL2BSCALAR(int& nNum)
{
  BoolStack.LOOKCONTROL2BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHCONTROL3BSCALAR(int nNum)
{
  BoolStack.PUSHCONTROL3BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPCONTROL3BSCALAR(int& nNum)
{
  BoolStack.POPCONTROL3BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKCONTROL3BSCALAR(int& nNum)
{
  BoolStack.LOOKCONTROL3BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHCONTROL4BSCALAR(int nNum)
{
  BoolStack.PUSHCONTROL4BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPCONTROL4BSCALAR(int& nNum)
{
  BoolStack.POPCONTROL4BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::LOOKCONTROL4BSCALAR(int& nNum)
{
  BoolStack.LOOKCONTROL4BSCALAR(nNum);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10F pArray, int nSize)
{
  FloatStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10F pArray, int nSize)
{
  FloatStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10D pArray, int nSize)
{
  DoubleStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10D pArray, int nSize)
{
  DoubleStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10C pArray, int nSize)
{
  CharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10C pArray, int nSize)
{
  CharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UC pArray, int nSize)
{
  UCharStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UC pArray, int nSize)
{
  UCharStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10S pArray, int nSize)
{
  ShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10S pArray, int nSize)
{
  ShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10US pArray, int nSize)
{
  UShortStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10US pArray, int nSize)
{
  UShortStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10L pArray, int nSize)
{
  LongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10L pArray, int nSize)
{
  LongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10I pArray, int nSize)
{
  IntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10I pArray, int nSize)
{
  IntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UL pArray, int nSize)
{
  ULongStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UL pArray, int nSize)
{
  ULongStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_1UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_2UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_2UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_3UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_3UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_4UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_4UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_5UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_5UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_6UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_6UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_7UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_7UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_8UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_8UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_9UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_9UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_10UI pArray, int nSize)
{
  UIntStack.pushArray(rAllocator, (const char*)pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator,  ARRAY_10UI pArray, int nSize)
{
  UIntStack.popArray(rAllocator, (char*)pArray, nSize);
}


#endif //AD

#endif //__ADT_STACK__
