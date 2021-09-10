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
class AdtADStackGroup;


//  ----------------------------------------------------------------------------
//  Wrapper macros to incorporate Allocator into Tapenade Array push/pop calls
//  ----------------------------------------------------------------------------
#define PUSHREAL4(A)            PUSHREAL4SCALAR(Stack, (A))
#define POPREAL4(A)             POPREAL4SCALAR(Stack, (A))
#define LOOKREAL4(A)            LOOKREAL4SCALAR(Stack, (A))
#define PUSHREAL4ARRAY(A,B)     PUSHREAL4ARRAY_allocator(Stack, Allocator, (A), (B))
#define POPREAL4ARRAY(A,B)      POPREAL4ARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHREAL8(A)            PUSHREAL8SCALAR(Stack, (A))
#define POPREAL8(A)             POPREAL8SCALAR(Stack, (A))
#define LOOKREAL8(A)            LOOKREAL8SCALAR(Stack, (A))
#define PUSHREAL8ARRAY(A,B)     PUSHREAL8ARRAY_allocator(Stack, Allocator, (A), (B))
#define POPREAL8ARRAY(A,B)      POPREAL8ARRAY_allocator(Stack, Allocator, (A), (B))
//#define PUSHREAL16(A)            PUSHREAL16SCALAR(Stack, (A))
//#define POPREAL16(A)             POPREAL16SCALAR(Stack, (A))
//#define LOOKREAL16(A)            LOOKREAL16SCALAR(Stack, (A))
// #define PUSHREAL16ARRAY(A,B)    PUSHREAL16ARRAY_allocator(Stack, Allocator, (A), (B))
// #define POPREAL16ARRAY(A,B)     POPREAL16ARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHINTEGER1(A)         PUSHINTEGER1SCALAR(Stack, (A))
#define POPINTEGER1(A)          POPINTEGER1SCALAR(Stack, (A))
#define LOOKINTEGER1(A)         LOOKINTEGER1SCALAR(Stack, (A))
#define PUSHINTEGER1ARRAY(A,B)  PUSHINTEGER1ARRAY_allocator(Stack, Allocator, (A), (B))
#define POPINTEGER1ARRAY(A,B)   POPINTEGER1ARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHINTEGER2(A)         PUSHINTEGER2SCALAR(Stack, (A))
#define POPINTEGER2(A)          POPINTEGER2SCALAR(Stack, (A))
#define LOOKINTEGER2(A)         LOOKINTEGER2SCALAR(Stack, (A))
#define PUSHINTEGER2ARRAY(A,B)  PUSHINTEGER2ARRAY_allocator(Stack, Allocator, (A), (B))
#define POPINTEGER2ARRAY(A,B)   POPINTEGER2ARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHINTEGER4(A)         PUSHINTEGER4SCALAR(Stack, (A))
#define POPINTEGER4(A)          POPINTEGER4SCALAR(Stack, (A))
#define LOOKINTEGER4(A)         LOOKINTEGER4SCALAR(Stack, (A))
#define PUSHINTEGER4ARRAY(A,B)  PUSHINTEGER4ARRAY_allocator(Stack, Allocator, (A), (B))
#define POPINTEGER4ARRAY(A,B)   POPINTEGER4ARRAY_allocator(Stack, Allocator, (A), (B))
// #define PUSHINTEGER8(A)         PUSHINTEGER8SCALAR(Stack, (A))
// #define POPINTEGER8(A)          POPINTEGER8SCALAR(Stack, (A))
// #define LOOKINTEGER8(A)         LOOKINTEGER8SCALAR(Stack, (A))
// #define PUSHINTEGER8ARRAY(A,B)  PUSHINTEGER8ARRAY_allocator(Stack, Allocator, (A), (B))
// #define POPINTEGER8ARRAY(A,B)   POPINTEGER8ARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHCONTROL1B(A)        PUSHCONTROL1BSCALAR(Stack, (A))
#define POPCONTROL1B(A)         POPCONTROL1BSCALAR(Stack, (A))
#define LOOKCONTROL1B(A)        LOOKCONTROL1BSCALAR(Stack, (A))
#define PUSHCONTROL1BARRAY(A,B) PUSHCONTROL1BARRAY_allocator(Stack, Allocator, (A), (B))
#define POPCONTROL1BARRAY(A,B)  POPCONTROL1BARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHCONTROL2B(A)        PUSHCONTROL2BSCALAR(Stack, (A))
#define POPCONTROL2B(A)         POPCONTROL2BSCALAR(Stack, (A))
#define LOOKCONTROL2B(A)        LOOKCONTROL2BSCALAR(Stack, (A))
#define PUSHCONTROL2BARRAY(A,B) PUSHCONTROL2BARRAY_allocator(Stack, Allocator, (A), (B))
#define POPCONTROL2BARRAY(A,B)  POPCONTROL2BARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHCONTROL3B(A)        PUSHCONTROL3BSCALAR(Stack, (A))
#define POPCONTROL3B(A)         POPCONTROL3BSCALAR(Stack, (A))
#define LOOKCONTROL3B(A)        LOOKCONTROL3BSCALAR(Stack, (A))
#define PUSHCONTROL3BARRAY(A,B) PUSHCONTROL3BARRAY_allocator(Stack, Allocator, (A), (B))
#define POPCONTROL3BARRAY(A,B)  POPCONTROL3BARRAY_allocator(Stack, Allocator, (A), (B))
#define PUSHCONTROL4B(A)        PUSHCONTROL4BSCALAR(Stack, (A))
#define POPCONTROL4B(A)         POPCONTROL4BSCALAR(Stack, (A))
#define LOOKCONTROL4B(A)        LOOKCONTROL4BSCALAR(Stack, (A))
#define PUSHCONTROL4BARRAY(A,B) PUSHCONTROL4BARRAY_allocator(Stack, Allocator, (A), (B))
#define POPCONTROL4BARRAY(A,B)  POPCONTROL4BARRAY_allocator(Stack, Allocator, (A), (B))


//  ----------------------------------------------------------------------------
//  Tapenade stack function wrappers
//  ----------------------------------------------------------------------------
void PUSHREAL4SCALAR(AdtADStack& rStack, float fNum);
void POPREAL4SCALAR(AdtADStack& rStack, float& rNum);
void LOOKREAL4SCALAR(AdtADStack& rStack, float& rNum);
void PUSHREAL4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize);
void POPREAL4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize);

void PUSHREAL8SCALAR(AdtADStack& rStack, double dNum);
void POPREAL8SCALAR(AdtADStack& rStack, double& rNum);
void LOOKREAL8SCALAR(AdtADStack& rStack, double& rNum);
void PUSHREAL8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize);
void POPREAL8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize);

// Not supported at this stage. Most C++ compilers have sizeof(double) == sizeof(long double)
// void PUSHREAL16SCALAR(AdtADStack& rStack, long double dNum);
// void POPREAL16SCALAR(AdtADStack& rStack, long double& rNum);
// void LOOKREAL16SCALAR(AdtADStack& rStack, long double& rNum);
// void PUSHREAL16ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1LD pNum, int nSize);
// void POPREAL16ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1LD pNum, int nSize);

void PUSHINTEGER1SCALAR(AdtADStack& rStack, char cNum);
void POPINTEGER1SCALAR(AdtADStack& rStack, char& rNum);
void LOOKINTEGER1SCALAR(AdtADStack& rStack, char& rNum);
void PUSHINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize);
void POPINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize);

void PUSHINTEGER1SCALAR(AdtADStack& rStack, unsigned char cNum);
void POPINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum);
void LOOKINTEGER1SCALAR(AdtADStack& rStack, unsigned char& rNum);
void PUSHINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize);
void POPINTEGER1ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize);

void PUSHINTEGER2SCALAR(AdtADStack& rStack, short nNum);
void POPINTEGER2SCALAR(AdtADStack& rStack, short& rNum);
void LOOKINTEGER2SCALAR(AdtADStack& rStack, short& rNum);
void PUSHINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize);
void POPINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize);

void PUSHINTEGER2SCALAR(AdtADStack& rStack, unsigned short nNum);
void POPINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum);
void LOOKINTEGER2SCALAR(AdtADStack& rStack, unsigned short& rNum);
void PUSHINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize);
void POPINTEGER2ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize);

void PUSHINTEGER4SCALAR(AdtADStack& rStack, long nNum);
void POPINTEGER4SCALAR(AdtADStack& rStack, long& rNum);
void LOOKINTEGER4SCALAR(AdtADStack& rStack, long& rNum);
void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize);
void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize);

void PUSHINTEGER4SCALAR(AdtADStack& rStack, int nNum);
void POPINTEGER4SCALAR(AdtADStack& rStack, int& rNum);
void LOOKINTEGER4SCALAR(AdtADStack& rStack, int& rNum);
void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned long nNum);
void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum);
void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned long& rNum);
void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize);
void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize);

void PUSHINTEGER4SCALAR(AdtADStack& rStack, unsigned int nNum);
void POPINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum);
void LOOKINTEGER4SCALAR(AdtADStack& rStack, unsigned int& rNum);
void PUSHINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize);
void POPINTEGER4ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize);

// Not supported at this stage and probably not needed.
// void PUSHINTEGER8SCALAR(AdtADStack& rStack, long long nNum);
// void POPINTEGER8SCALAR(AdtADStack& rStack, long long& nNum);
// void LOOKINTEGER8SCALAR(AdtADStack& rStack, long long& nNum);
// void PUSHINTEGER8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1LL pNum, int nSize);
// void POPINTEGER8ARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1LL pNum, int nSize);

void PUSHCONTROL1BSCALAR(AdtADStack& rStack, int nNum);
void POPCONTROL1BSCALAR(AdtADStack& rStack, int& nNum);
void LOOKCONTROL1BSCALAR(AdtADStack& rStack, int& nNum);
void PUSHCONTROL1BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL1BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL2BSCALAR(AdtADStack& rStack, int nNum);
void POPCONTROL2BSCALAR(AdtADStack& rStack, int& nNum);
void LOOKCONTROL2BSCALAR(AdtADStack& rStack, int& nNum);
void PUSHCONTROL2BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL2BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL3BSCALAR(AdtADStack& rStack, int nNum);
void POPCONTROL3BSCALAR(AdtADStack& rStack, int& nNum);
void LOOKCONTROL3BSCALAR(AdtADStack& rStack, int& nNum);
void PUSHCONTROL3BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL3BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL4BSCALAR(AdtADStack& rStack, int nNum);
void POPCONTROL4BSCALAR(AdtADStack& rStack, int& nNum);
void LOOKCONTROL4BSCALAR(AdtADStack& rStack, int& nNum);
void PUSHCONTROL4BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL4BARRAY_allocator(AdtADStack& rStack, const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);


//  ----------------------------------------------------------------------------
//  Mappings of AdtADStackGroup* by ThreadIdType
//  ----------------------------------------------------------------------------
typedef std::pair<ThreadIdType, AdtADStackGroup*>                 ThreadIdTypeAdtADStackGroupPtrPair;
typedef std::map<ThreadIdType, AdtADStackGroup*>                  AdtADStackGroupPtrByThreadIdTypeMap;
typedef std::map<ThreadIdType, AdtADStackGroup*>::iterator        AdtADStackGroupPtrByThreadIdTypeMapIter;
typedef std::map<ThreadIdType, AdtADStackGroup*>::const_iterator  AdtADStackGroupPtrByThreadIdTypeMapConstIter;


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

  int         baseIndex(const AdtMemAllocator& rAllocator, char* pArray, int nSize) const;

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

  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
  void        push(const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize);

  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);
  void        pop(const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize);

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
//  class AdtADStackGroup
//  ----------------------------------------------------------------------------
//  Container for all stacks required by tapenade algorithmic differentiation.
//  Tapenade assumes that each data size type has it's own stack. We need to
//  honour this here or else the AD code may not work correctly. Also note that
//  we dynamically allocate each stack on demand to reduce possible memory
//  foot print.
//  ----------------------------------------------------------------------------
class AdtADStackGroup
{
private:
  size_t        BufferSize;
  AdtADStack*   Stack_R4;
  AdtADStack*   Stack_R8;
  AdtADStack*   Stack_I1;
  AdtADStack*   Stack_I2;
  AdtADStack*   Stack_I4;
  AdtADStack*   Stack_B;

public:
  AdtADStackGroup(size_t nBufferSize);
  virtual ~AdtADStackGroup();

  AdtADStack&   stack_R4();
  AdtADStack&   stack_R8();
  AdtADStack&   stack_I1();
  AdtADStack&   stack_I2();
  AdtADStack&   stack_I4();
  AdtADStack&   stack_B();
};

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_R4()
{
  if (Stack_R4 == 0)
  {
    Stack_R4 = new AdtADStack(BufferSize);
  }

  return (*Stack_R4);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_R8()
{
  if (Stack_R8 == 0)
  {
    Stack_R8 = new AdtADStack(BufferSize);
  }

  return (*Stack_R8);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_I1()
{
  if (Stack_I1 == 0)
  {
    Stack_I1 = new AdtADStack(BufferSize);
  }

  return (*Stack_I1);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_I2()
{
  if (Stack_I2 == 0)
  {
    Stack_I2 = new AdtADStack(BufferSize);
  }

  return (*Stack_I2);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_I4()
{
  if (Stack_I4 == 0)
  {
    Stack_I4 = new AdtADStack(BufferSize);
  }

  return (*Stack_I4);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroup::stack_B()
{
  if (Stack_B == 0)
  {
    Stack_B = new AdtADStack(BufferSize);
  }

  return (*Stack_B);
}


//  ----------------------------------------------------------------------------
//  class AdtADStackGroupSingleton
//  ----------------------------------------------------------------------------
//  This class is used to create and destroy all AdtADStackGroup instances.
//  The class constructor is to be called only in one place in the startup
//  code. Users of this lbrary should never call it.
//  ----------------------------------------------------------------------------
class AdtADStackGroupSingleton
{
private:
  static AdtADStackGroupPtrByThreadIdTypeMap  Map;
  static long                                 Lock;

private:
  static void                                 onExit();
  static void                                 beginMutex();
  static void                                 endMutex();

public:
  AdtADStackGroupSingleton();
  virtual ~AdtADStackGroupSingleton();

  static AdtADStackGroup&                     stackGroup();
  static AdtADStack&                          stack_R4();
  static AdtADStack&                          stack_R8();
  static AdtADStack&                          stack_I1();
  static AdtADStack&                          stack_I2();
  static AdtADStack&                          stack_I4();
  static AdtADStack&                          stack_B();
  static size_t                               BufferSize;
};

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_R4()
{
  return (stackGroup().stack_R4());
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_R8()
{
  return (stackGroup().stack_R8());
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_I1()
{
  return (stackGroup().stack_I1());
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_I2()
{
  return (stackGroup().stack_I2());
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_I4()
{
  return (stackGroup().stack_I4());
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtADStackGroupSingleton::stack_B()
{
  return (stackGroup().stack_B());
}

#endif //AD

#endif //__ADT_STACK__
