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
#define PUSHREAL4(A)            PUSHREAL4SCALAR(Stack, (A))
#define POPREAL4(A)             POPREAL4SCALAR(Stack, (A))
#define LOOKREAL4(A)            LOOKREAL4SCALAR(Stack, (A))
#define PUSHREAL4ARRAY(A,B)     PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPREAL4ARRAY(A,B)      POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHREAL8(A)            PUSHREAL8SCALAR(Stack, (A))
#define POPREAL8(A)             POPREAL8SCALAR(Stack, (A))
#define LOOKREAL8(A)            LOOKREAL8SCALAR(Stack, (A))
#define PUSHREAL8ARRAY(A,B)     PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPREAL8ARRAY(A,B)      POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
//#define PUSHREAL16(A)            PUSHREAL16SCALAR(Stack, (A))
//#define POPREAL16(A)             POPREAL16SCALAR(Stack, (A))
//#define LOOKREAL16(A)            LOOKREAL16SCALAR(Stack, (A))
// #define PUSHREAL16ARRAY(A,B)    PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
// #define POPREAL16ARRAY(A,B)     POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHINTEGER1(A)         PUSHINTEGER1SCALAR(Stack, (A))
#define POPINTEGER1(A)          POPINTEGER1SCALAR(Stack, (A))
#define LOOKINTEGER1(A)         LOOKINTEGER1SCALAR(Stack, (A))
#define PUSHINTEGER1ARRAY(A,B)  PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPINTEGER1ARRAY(A,B)   POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHINTEGER2(A)         PUSHINTEGER2SCALAR(Stack, (A))
#define POPINTEGER2(A)          POPINTEGER2SCALAR(Stack, (A))
#define LOOKINTEGER2(A)         LOOKINTEGER2SCALAR(Stack, (A))
#define PUSHINTEGER2ARRAY(A,B)  PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPINTEGER2ARRAY(A,B)   POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHINTEGER4(A)         PUSHINTEGER4SCALAR(Stack, (A))
#define POPINTEGER4(A)          POPINTEGER4SCALAR(Stack, (A))
#define LOOKINTEGER4(A)         LOOKINTEGER4SCALAR(Stack, (A))
#define PUSHINTEGER4ARRAY(A,B)  PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPINTEGER4ARRAY(A,B)   POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
// #define PUSHINTEGER8(A)         PUSHINTEGER8SCALAR(Stack, (A))
// #define POPINTEGER8(A)          POPINTEGER8SCALAR(Stack, (A))
// #define LOOKINTEGER8(A)         LOOKINTEGER8SCALAR(Stack, (A))
// #define PUSHINTEGER8ARRAY(A,B)  PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
// #define POPINTEGER8ARRAY(A,B)   POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHCONTROL1B(A)        PUSHCONTROL1BSCALAR(Stack, (A))
#define POPCONTROL1B(A)         POPCONTROL1BSCALAR(Stack, (A))
#define LOOKCONTROL1B(A)        LOOKCONTROL1BSCALAR(Stack, (A))
#define PUSHCONTROL1BARRAY(A,B) PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPCONTROL1BARRAY(A,B)  POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHCONTROL2B(A)        PUSHCONTROL2BSCALAR(Stack, (A))
#define POPCONTROL2B(A)         POPCONTROL2BSCALAR(Stack, (A))
#define LOOKCONTROL2B(A)        LOOKCONTROL2BSCALAR(Stack, (A))
#define PUSHCONTROL2BARRAY(A,B) PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPCONTROL2BARRAY(A,B)  POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHCONTROL3B(A)        PUSHCONTROL3BSCALAR(Stack, (A))
#define POPCONTROL3B(A)         POPCONTROL3BSCALAR(Stack, (A))
#define LOOKCONTROL3B(A)        LOOKCONTROL3BSCALAR(Stack, (A))
#define PUSHCONTROL3BARRAY(A,B) PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPCONTROL3BARRAY(A,B)  POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))
#define PUSHCONTROL4B(A)        PUSHCONTROL4BSCALAR(Stack, (A))
#define POPCONTROL4B(A)         POPCONTROL4BSCALAR(Stack, (A))
#define LOOKCONTROL4B(A)        LOOKCONTROL4BSCALAR(Stack, (A))
#define PUSHCONTROL4BARRAY(A,B) PUSHARRAY_allocator(Stack, MemAllocator, ((const char*)A), (B))
#define POPCONTROL4BARRAY(A,B)  POPARRAY_allocator(Stack, MemAllocator, ((char*)A), (B))


//  ----------------------------------------------------------------------------
//  class AdtADStack
//  ----------------------------------------------------------------------------
//  This class implements a disk based stack that pages memory to disk to free
//  space in the buffer when space is exhausted. This approach is likely to be
//  more efficient that growing the stack and relying on operating system
//  provided paging to take care of the rest. Should aim to minimise page faults
//  as they are costly and this should do just that.
//  ----------------------------------------------------------------------------
class AdtADStack
{
private:
  FILE*       StackFile;
  char        StackFileName[1024];
  char*       StackBuffer;
  size_t      BufferSize;
  size_t      StackPtr;

protected:
  void        push(const char* pBuffer, size_t nSize);
  void        pop(char* pBuffer, size_t nSize);
  void        look(char* pBuffer, size_t nSize);

  void        memoryAndLength(const AdtMemAllocator& rAllocator, char* pArray, int nSize, char*& pData, size_t& nDataSize) const;

public:
  AdtADStack(size_t nBufferSize);
  virtual ~AdtADStack();

  void        push(float fNum);
  void        push(double dNum);
  void        push(char nNum);
  void        push(unsigned char nNum);
  void        push(short nNum);
  void        push(unsigned short nNum);
  void        push(long nNum);
  void        push(unsigned long nNum);
  void        push(int nNum);
  void        push(unsigned int nNum);

  void        pop(float& rNum);
  void        pop(double& rNum);
  void        pop(char& rNum);
  void        pop(unsigned char& rNum);
  void        pop(short& rNum);
  void        pop(unsigned short& rNum);
  void        pop(long& rNum);
  void        pop(unsigned long& rNum);
  void        pop(int& rNum);
  void        pop(unsigned int& rNum);

  void        look(float& rNum);
  void        look(double& rNum);
  void        look(char& rNum);
  void        look(unsigned char& rNum);
  void        look(short& rNum);
  void        look(unsigned short& rNum);
  void        look(long& rNum);
  void        look(unsigned long& rNum);
  void        look(int& rNum);
  void        look(unsigned int& rNum);

  void        pushArray(const AdtMemAllocator& rAllocator, const char* pArray, int nSize);

  void        popArray(const AdtMemAllocator& rAllocator, char* pArray, int nSize);

  size_t      bufferSize() const;
};

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(float fNum)
{
  push((const char*)&fNum, sizeof(fNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(double dNum)
{
  push((const char*)&dNum, sizeof(dNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(char nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(unsigned char nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(short nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(unsigned short nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(long nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(unsigned long nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(int nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::push(unsigned int nNum)
{
  push((const char*)&nNum, sizeof(nNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(float& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(double& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(char& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(unsigned char& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(short& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(unsigned short& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(long& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(unsigned long& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(int& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::pop(unsigned int& rNum)
{
  pop((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(float& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(double& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(char& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(unsigned char& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(short& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(unsigned short& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(long& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(unsigned long& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(int& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline void AdtADStack::look(unsigned int& rNum)
{
  look((char*)&rNum, sizeof(rNum));
}

//  ----------------------------------------------------------------------------

inline size_t AdtADStack::bufferSize() const
{
  return (BufferSize);
}


//  ----------------------------------------------------------------------------
//  Tapenade stack function wrappers
//  ----------------------------------------------------------------------------
inline void PUSHREAL4SCALAR(AdtADStack& rStack, float fNum)
{
  rStack.push(fNum);
}

//  ----------------------------------------------------------------------------

inline void POPREAL4SCALAR(AdtADStack& rStack, float& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKREAL4SCALAR(AdtADStack& rStack, float& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHREAL8SCALAR(AdtADStack& rStack, double dNum)
{
  rStack.push(dNum);
}

//  ----------------------------------------------------------------------------

inline void POPREAL8SCALAR(AdtADStack& rStack, double& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKREAL8SCALAR(AdtADStack& rStack, double& rNum)
{
  rStack.look(rNum);
}

// Not supported at this stage. Most C++ compilers have sizeof(double) == sizeof(long double)
//  //  ----------------------------------------------------------------------------
//
//  inline void PUSHREAL16SCALAR(AdtADStack& rStack, long double dNum)
//  {
//    rStack.push(dNum);
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void POPREAL16SCALAR(AdtADStack& rStack, long double& rNum)
//  {
//    rStack.pop(rNum);
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void LOOKREAL16SCALAR(AdtADStack& rStack, long double& rNum)
//  {
//    rStack.look(rNum);
//  }
//  
//  //  ----------------------------------------------------------------------------

inline void PUSHINTEGER1SCALAR(AdtADStack& rStack, char cNum)
{
  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER1SCALAR(AdtADStack& rStack, char& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER1SCALAR(AdtADStack& rStack, char& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER1SCALAR(AdtADStack& rStack, unsigned char cNum)
{
  rStack.push(cNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER2SCALAR(AdtADStack& rStack, short nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER2SCALAR(AdtADStack& rStack, short& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER2SCALAR(AdtADStack& rStack, short& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER2SCALAR(AdtADStack& rStack, unsigned short nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER4SCALAR(AdtADStack& rStack, long nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER4SCALAR(AdtADStack& rStack, long& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER4SCALAR(AdtADStack& rStack, long& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER4SCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER4SCALAR(AdtADStack& rStack, int& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER4SCALAR(AdtADStack& rStack, int& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned long nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum)
{
  rStack.look(rNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum)
{
  rStack.pop(rNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum)
{
  rStack.look(rNum);
}

// Not supported at this stage and probably not needed.
//  //  ----------------------------------------------------------------------------
//  
//  inline void PUSHINTEGER8SCALAR(AdtADStack& rStack, long long nNum)
//  {
//    rStack.push(nNum);
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void POPINTEGER8SCALAR(AdtADStack& rStack, long long& rNum)
//  {
//    rStack.pop(rNum);
//  }
//  
//  //  ----------------------------------------------------------------------------
//  
//  inline void LOOKINTEGER8SCALAR(AdtADStack& rStack, long long& rNum)
//  {
//    rStack.look(rNum);
//  }
//  
//  //  ----------------------------------------------------------------------------

inline void PUSHCONTROL1BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPCONTROL1BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKCONTROL1BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHCONTROL2BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPCONTROL2BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKCONTROL2BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHCONTROL3BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPCONTROL3BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKCONTROL3BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHCONTROL4BSCALAR(AdtADStack& rStack, int nNum)
{
  rStack.push(nNum);
}

//  ----------------------------------------------------------------------------

inline void POPCONTROL4BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.pop(nNum);
}

//  ----------------------------------------------------------------------------

inline void LOOKCONTROL4BSCALAR(AdtADStack& rStack, int& nNum)
{
  rStack.look(nNum);
}

//  ----------------------------------------------------------------------------

inline void PUSHARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const char* pArray, int nSize)
{
  rStack.pushArray(rAllocator, pArray, nSize);
}

//  ----------------------------------------------------------------------------

inline void POPARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, char* pArray, int nSize)
{
  rStack.popArray(rAllocator, pArray, nSize);
}


#endif //AD

#endif //__ADT_STACK__
