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
//  Wrapper macros to incorporate Allocator into Tapenade Array push/pop calls
//  ----------------------------------------------------------------------------
#define PUSHREAL4ARRAY(A,B)     PUSHREAL4ARRAY_allocator(Allocator, (A), (B))
#define POPREAL4ARRAY(A,B)      POPREAL4ARRAY_allocator(Allocator, (A), (B))
#define PUSHREAL8ARRAY(A,B)     PUSHREAL8ARRAY_allocator(Allocator, (A), (B))
#define POPREAL8ARRAY(A,B)      POPREAL8ARRAY_allocator(Allocator, (A), (B))
// #define PUSHREAL16ARRAY(A,B)    PUSHREAL16ARRAY_allocator(Allocator, (A), (B))
// #define POPREAL16ARRAY(A,B)     POPREAL16ARRAY_allocator(Allocator, (A), (B))
#define PUSHINTEGER1ARRAY(A,B)  PUSHINTEGER1ARRAY_allocator(Allocator, (A), (B))
#define POPINTEGER1ARRAY(A,B)   POPINTEGER1ARRAY_allocator(Allocator, (A), (B))
#define PUSHINTEGER2ARRAY(A,B)  PUSHINTEGER2ARRAY_allocator(Allocator, (A), (B))
#define POPINTEGER2ARRAY(A,B)   POPINTEGER2ARRAY_allocator(Allocator, (A), (B))
#define PUSHINTEGER4ARRAY(A,B)  PUSHINTEGER4ARRAY_allocator(Allocator, (A), (B))
#define POPINTEGER4ARRAY(A,B)   POPINTEGER4ARRAY_allocator(Allocator, (A), (B))
// #define PUSHINTEGER8ARRAY(A,B)  PUSHINTEGER8ARRAY_allocator(Allocator, (A), (B))
// #define POPINTEGER8ARRAY(A,B)   POPINTEGER8ARRAY_allocator(Allocator, (A), (B))
#define PUSHCONTROL1BARRAY(A,B) PUSHCONTROL1BARRAY_allocator(Allocator, (A), (B))
#define POPCONTROL1BARRAY(A,B)  POPCONTROL1BARRAY_allocator(Allocator, (A), (B))
#define PUSHCONTROL2BARRAY(A,B) PUSHCONTROL2BARRAY_allocator(Allocator, (A), (B))
#define POPCONTROL2BARRAY(A,B)  POPCONTROL2BARRAY_allocator(Allocator, (A), (B))
#define PUSHCONTROL3BARRAY(A,B) PUSHCONTROL3BARRAY_allocator(Allocator, (A), (B))
#define POPCONTROL3BARRAY(A,B)  POPCONTROL3BARRAY_allocator(Allocator, (A), (B))
#define PUSHCONTROL4BARRAY(A,B) PUSHCONTROL4BARRAY_allocator(Allocator, (A), (B))
#define POPCONTROL4BARRAY(A,B)  POPCONTROL4BARRAY_allocator(Allocator, (A), (B))


//  ----------------------------------------------------------------------------
//  Tapenade stack function wrappers
//  ----------------------------------------------------------------------------
void PUSHREAL4(float fNum);
void POPREAL4(float& rNum);
void LOOKREAL4(float& rNum);
void PUSHREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1F pNum, int nSize);
void POPREAL4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1F pNum, int nSize);

void PUSHREAL8(double dNum);
void POPREAL8(double& rNum);
void LOOKREAL8(double& rNum);
void PUSHREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1D pNum, int nSize);
void POPREAL8ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1D pNum, int nSize);

// Not supported at this stage. Most C++ compilers have sizeof(double) == sizeof(long double)
// void PUSHREAL16(long double dNum);
// void POPREAL16(long double& rNum);
// void LOOKREAL16(long double& rNum);
// void PUSHREAL16ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1LD pNum, int nSize);
// void POPREAL16ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1LD pNum, int nSize);

void PUSHINTEGER1(char cNum);
void POPINTEGER1(char& rNum);
void LOOKINTEGER1(char& rNum);
void PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1C pNum, int nSize);
void POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1C pNum, int nSize);

void PUSHINTEGER1(unsigned char cNum);
void POPINTEGER1(unsigned char& rNum);
void LOOKINTEGER1(unsigned char& rNum);
void PUSHINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UC pNum, int nSize);
void POPINTEGER1ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UC pNum, int nSize);

void PUSHINTEGER2(short nNum);
void POPINTEGER2(short& rNum);
void LOOKINTEGER2(short& rNum);
void PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1S pNum, int nSize);
void POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1S pNum, int nSize);

void PUSHINTEGER2(unsigned short nNum);
void POPINTEGER2(unsigned short& rNum);
void LOOKINTEGER2(unsigned short& rNum);
void PUSHINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1US pNum, int nSize);
void POPINTEGER2ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1US pNum, int nSize);

void PUSHINTEGER4(long nNum);
void POPINTEGER4(long& rNum);
void LOOKINTEGER4(long& rNum);
void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1L pNum, int nSize);
void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1L pNum, int nSize);

void PUSHINTEGER4(int nNum);
void POPINTEGER4(int& rNum);
void LOOKINTEGER4(int& rNum);
void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHINTEGER4(unsigned long nNum);
void POPINTEGER4(unsigned long& rNum);
void LOOKINTEGER4(unsigned long& rNum);
void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UL pNum, int nSize);
void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UL pNum, int nSize);

void PUSHINTEGER4(unsigned int nNum);
void POPINTEGER4(unsigned int& rNum);
void LOOKINTEGER4(unsigned int& rNum);
void PUSHINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1UI pNum, int nSize);
void POPINTEGER4ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1UI pNum, int nSize);

// Not supported at this stage and probably not needed.
// void PUSHINTEGER8(long long nNum);
// void POPINTEGER8(long long& nNum);
// void LOOKINTEGER8(long long& nNum);
// void PUSHINTEGER8ARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1LL pNum, int nSize);
// void POPINTEGER8ARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1LL pNum, int nSize);

void PUSHCONTROL1B(int nNum);
void POPCONTROL1B(int& nNum);
void LOOKCONTROL1B(int& nNum);
void PUSHCONTROL1BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL1BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL2B(int nNum);
void POPCONTROL2B(int& nNum);
void LOOKCONTROL2B(int& nNum);
void PUSHCONTROL2BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL2BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL3B(int nNum);
void POPCONTROL3B(int& nNum);
void LOOKCONTROL3B(int& nNum);
void PUSHCONTROL3BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL3BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);

void PUSHCONTROL4B(int nNum);
void POPCONTROL4B(int& nNum);
void LOOKCONTROL4B(int& nNum);
void PUSHCONTROL4BARRAY_allocator(const AdtMemAllocator& rAllocator, const ARRAY_1I pNum, int nSize);
void POPCONTROL4BARRAY_allocator(const AdtMemAllocator& rAllocator, ARRAY_1I pNum, int nSize);


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtADStackGroup;


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
