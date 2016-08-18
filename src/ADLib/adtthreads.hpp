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
//    adtthreads.hpp
//
//  Purpose:
//    This file includes declarations of classes to supply multi-threaded
//    support for ADLib.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTTHREADS_HPP__
#define __ADTTHREADS_HPP__


#include "adtmaths.hpp"


#ifndef AD


//  ----------------------------------------------------------------------------
//  AdtReferenceCount Class
//  ----------------------------------------------------------------------------
//  This class provides base level support for object instance reference
//  counting in situations where objects are shared between multiple owners.
//  ----------------------------------------------------------------------------
class AdtReferenceCount
{
private:
  mutable long  LockCount;

public:
  AdtReferenceCount();
  AdtReferenceCount(const AdtReferenceCount& aCopy);
  virtual ~AdtReferenceCount();

  void          lock() const;
  bool          unlock() const;
  int           lockCount() const;
};

//  ----------------------------------------------------------------------------

inline AdtReferenceCount::AdtReferenceCount()
{
  LockCount = 1;
}

//  ----------------------------------------------------------------------------

inline AdtReferenceCount::AdtReferenceCount(const AdtReferenceCount&)
{
  LockCount = 1;
}

//  ----------------------------------------------------------------------------

inline AdtReferenceCount::~AdtReferenceCount()
{
  assert(LockCount == 0);
}


//  ----------------------------------------------------------------------------

inline void AdtReferenceCount::lock() const
{
  LockCount++;
}

//  ----------------------------------------------------------------------------

inline bool AdtReferenceCount::unlock() const
{
  LockCount--;

  if (LockCount < 0)
  {
    throw(std::runtime_error(std::string("AdtReferenceCount::unlock() called too many times")));
  }

  return (LockCount == 0);
}

//  ----------------------------------------------------------------------------

inline int AdtReferenceCount::lockCount() const
{
  return (LockCount);
}


//  ----------------------------------------------------------------------------
//  AdtReleaseReference macro
//  ----------------------------------------------------------------------------
//  This is a convenience macro used for releasing object references.
//  ----------------------------------------------------------------------------
#define AdtReleaseReference(pObject)\
{\
  const AdtReferenceCount* pReferenceCount = (pObject);\
\
  if ((pReferenceCount != 0) && pReferenceCount->unlock())\
  {\
    delete pReferenceCount;\
  }\
}


//  ----------------------------------------------------------------------------
//  Sleep function
//  ----------------------------------------------------------------------------
extern "C" void msSleep(unsigned long nMilliseconds);


//  ----------------------------------------------------------------------------
//  Wait for thread closure function
//  ----------------------------------------------------------------------------
void AdtWaitForThreadClosure();


//  ----------------------------------------------------------------------------
//  AdtThreadCallback type definition
//  ----------------------------------------------------------------------------
typedef unsigned (*AdtThreadCallback)(void* pInstance, unsigned nThreadId);


#if defined(_MSC_VER)

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>
#include <objbase.h>
#include <process.h>


//  ----------------------------------------------------------------------------
//  Enumerated types
//  ----------------------------------------------------------------------------
enum AdtWaitStatus{WaitSignaled   = WAIT_OBJECT_0,
                   WaitTimedout   = WAIT_TIMEOUT,
                   WaitAbandoned  = WAIT_ABANDONED,
                   WaitFailed     = WAIT_FAILED};

//  ----------------------------------------------------------------------------
//  Wait for single obejct function
//  ----------------------------------------------------------------------------
AdtWaitStatus AdtWaitForSingleObject(HANDLE hObject, unsigned nTimeOut);


//  ----------------------------------------------------------------------------
//  AdtMutex class
//  ----------------------------------------------------------------------------
//  AdtMutex encapsulates mutex synchronisation objects. This class is used in
//  conjunction with AdtWaitOnMutex to aid in program flow control in multi-
//  threaded environments. A mutex is a mutual exclusion. A thread can request a
//  mutex using the AdtWaitOnMutex class. The mutex, if granted, will live for
//  the duration of the instance of AdtWaitOnMutex.
//  ----------------------------------------------------------------------------
class AdtMutex : public AdtReferenceCount
{
protected:
  HANDLE            HandleMutex;
  adtstring         Name;

protected:
  AdtMutex(const AdtMutex& rCopy);

public:
  AdtMutex(const char* pName = 0);
  virtual ~AdtMutex();

  bool              isValid() const;
  const adtstring&  name() const;
  HANDLE            handle() const;
  AdtWaitStatus     wait(unsigned nTimeOut = INFINITE) const;
  void              release() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtMutex::isValid() const
{
  return (HandleMutex != 0);
}

//  ----------------------------------------------------------------------------

inline const adtstring& AdtMutex::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline HANDLE AdtMutex::handle() const
{
  return (HandleMutex);
}

//  ----------------------------------------------------------------------------

inline AdtWaitStatus AdtMutex::wait(unsigned nTimeOut) const
{
  return (::AdtWaitForSingleObject(HandleMutex, nTimeOut));
}

//  ----------------------------------------------------------------------------

inline void AdtMutex::release() const
{
  if (HandleMutex != 0)
  {
    ::ReleaseMutex(HandleMutex);
  }
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex class
//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex is a blocking class used to control the flow of a program
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtWaitOnMutex
{
  AdtWaitStatus     Status;
  HANDLE            HandleMutex;

protected:
  AdtWaitOnMutex(const AdtWaitOnMutex& rCopy);

public:
  AdtWaitOnMutex(const AdtMutex* pMutex, unsigned nTimeOut = INFINITE);
  ~AdtWaitOnMutex();

  void              release();
  AdtWaitStatus     status() const;
                    operator bool() const;
};

//  ----------------------------------------------------------------------------

inline AdtWaitOnMutex::~AdtWaitOnMutex()
{
  if (HandleMutex != 0)
  {
    ::ReleaseMutex(HandleMutex);
  }
}

//  ----------------------------------------------------------------------------

inline void AdtWaitOnMutex::release()
{
  if (HandleMutex != 0)
  {
    ::ReleaseMutex(HandleMutex);
    HandleMutex = 0;
  }
}

//  ----------------------------------------------------------------------------

inline AdtWaitStatus AdtWaitOnMutex::status() const
{
  return (Status);
}

//  ----------------------------------------------------------------------------

inline AdtWaitOnMutex::operator bool() const
{
  return (Status == WaitSignaled);
}


//  ----------------------------------------------------------------------------
//  AdtSemaphore class
//  ----------------------------------------------------------------------------
//  AdtSemaphore encapsulates semaphore synchronisation objects. This class is
//  used in conjunction with AdtWaitOnSemaphore to aid in program flow control
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtSemaphore : public AdtReferenceCount
{
protected:
  HANDLE            HandleSemaphore;
  adtstring         Name;

protected:
  AdtSemaphore(const AdtSemaphore& rCopy);

public:
  AdtSemaphore(const char* pName, int nCount, int nMaxCount);
  virtual ~AdtSemaphore();

  bool              isValid() const;
  bool              signal(long nCount = 1) const;
  const adtstring&  name() const;
  HANDLE            handle() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtSemaphore::isValid() const
{
  return (HandleSemaphore != 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtSemaphore::signal(long nCount) const
{
  return (::ReleaseSemaphore(HandleSemaphore, nCount, 0) != 0);
}

//  ----------------------------------------------------------------------------

inline const adtstring& AdtSemaphore::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline HANDLE AdtSemaphore::handle() const
{
  return (HandleSemaphore);
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore class
//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore is a blocking class used to control the flow of a program
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtWaitOnSemaphore
{
  AdtWaitStatus     Status;
  HANDLE            HandleSemaphore;

protected:
  AdtWaitOnSemaphore(const AdtWaitOnSemaphore& rCopy);

public:
  AdtWaitOnSemaphore(AdtSemaphore* pSemaphore, unsigned nTimeOut = INFINITE);
  ~AdtWaitOnSemaphore();

  AdtWaitStatus     status() const;
                    operator bool() const;
};

//  ----------------------------------------------------------------------------

inline AdtWaitOnSemaphore::~AdtWaitOnSemaphore()
{

}

//  ----------------------------------------------------------------------------

inline AdtWaitStatus AdtWaitOnSemaphore::status() const
{
  return (Status);
}

//  ----------------------------------------------------------------------------

inline AdtWaitOnSemaphore::operator bool() const
{
  return (Status == WaitSignaled);
}


//  ----------------------------------------------------------------------------
//  Mappings of HANDLE by HANDLE
//  ----------------------------------------------------------------------------
typedef std::pair<const HANDLE, HANDLE>                          HandleHandlePair;
typedef std::map<HANDLE, HANDLE>                                 HandleByHandleMap;
typedef std::map<HANDLE, HANDLE>::iterator                       HandleByHandleMapIter;
typedef std::map<HANDLE, HANDLE>::const_iterator                 HandleByHandleMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtThread class
//  ----------------------------------------------------------------------------
//  AdtThread encapsulates a thread context and thread of execution. Creating an
//  instance of this class creates a new thread of execution. The class instance
//  can be used to control the behaviour of that thread of execution.
//  ----------------------------------------------------------------------------
class AdtThread : public AdtReferenceCount
{
protected:
  static long               ThreadCount;
  static HandleByHandleMap  HandleMap;
  HANDLE                    HandleThread;
  unsigned long             ExitCode;
  bool                      IsOpen;
  static unsigned           MainId;
  unsigned                  Id;
  void*                     Instance;
  AdtThreadCallback         Callback;

private:
  static unsigned           threadMain(AdtThread* pThis);
  static unsigned __stdcall localThreadCallback(void* pInstance);
  void                      closeThreadHandle();

  AdtThread(const AdtThread& rCopy);

public:
  AdtThread();
  AdtThread(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize = 0);
  virtual ~AdtThread();

  static void               updateThreadCount();
  static long               threadCount();

  bool                      open(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize = 0);
  void                      waitForThreadClosure();
  void                      exit(unsigned long nExitCode);
  unsigned long             exitCode() const;
  bool                      isOpen() const;
  void*                     instance() const;
  AdtThreadCallback         callback() const;

  static unsigned           threadId();
  static unsigned           mainThreadId();
  static bool               isMainThread();
};

//  ----------------------------------------------------------------------------

inline long AdtThread::threadCount()
{
  return (ThreadCount);
}

//  ----------------------------------------------------------------------------

inline unsigned long AdtThread::exitCode() const
{
  return (ExitCode);
}

//  ----------------------------------------------------------------------------

inline bool AdtThread::isOpen() const
{
  return (IsOpen);
}

//  ----------------------------------------------------------------------------

inline void* AdtThread::instance() const
{
  return (Instance);
}

//  ----------------------------------------------------------------------------

inline AdtThreadCallback AdtThread::callback() const
{
  return (Callback);
}


#else


#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#ifdef __APPLE__

  #include <sys/param.h>
  #include <sys/sysctl.h>
  #include <sys/time.h>

  // We define this shit because Apple doesn't bloody implement it!!! Stupid!!!
  #define CLOCK_REALTIME  0

  int clock_gettime(int, struct timespec *tp);

#else

  #include <time.h>

#endif //__APPLE__


#define INFINITE        0xFFFFFFFF


enum AdtWaitStatus{WaitSignaled,
                   WaitTimedout,
                   WaitAbandoned,
                   WaitFailed};


//  ----------------------------------------------------------------------------
//  AdtSemaphore class
//  ----------------------------------------------------------------------------
//  AdtSemaphore encapsulates semaphore synchronisation objects. This class is
//  used in conjunction with AdtWaitOnSemaphore to aid in program flow control
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtSemaphore : public AdtReferenceCount
{
friend class AdtWaitOnSemaphore;

protected:
  mutable pthread_mutex_t     Mutex;
  mutable pthread_mutexattr_t MutexAttr;
  mutable pthread_cond_t      ConditionVariable;
  bool                        IsValidCondVar;
  bool                        IsValidMutexAttr;
  bool                        IsValidMutex;
  mutable int                 Count;
  int                         MaxCount;
  adtstring                   Name;

protected:
  static void             threadExitCleanup(void* pContext);
  AdtWaitStatus           waitOnSemaphore(unsigned nTimeOut);

  AdtSemaphore(const AdtSemaphore& rCopy);

public:
  AdtSemaphore(const char* pName, int nCount, int nMaxCount);
  virtual ~AdtSemaphore();

  bool                    isValid() const;
  bool                    signal(long nCount = 1) const;
  const adtstring&        name() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtSemaphore::isValid() const
{
  return (IsValidCondVar && IsValidMutexAttr && IsValidMutex);
}

//  ----------------------------------------------------------------------------

inline const adtstring& AdtSemaphore::name() const
{
  return (Name);
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore class
//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore is a blocking class used to control the flow of a program
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtWaitOnSemaphore
{
  AdtWaitStatus     Status;

protected:
  AdtWaitOnSemaphore(const AdtWaitOnSemaphore& rCopy);

public:
  AdtWaitOnSemaphore(AdtSemaphore* pSemaphore, unsigned nTimeOut = INFINITE);
  ~AdtWaitOnSemaphore();

  AdtWaitStatus     status() const;
                    operator bool() const;
};

//  ----------------------------------------------------------------------------

inline AdtWaitOnSemaphore::~AdtWaitOnSemaphore()
{

}

//  ----------------------------------------------------------------------------

inline AdtWaitStatus AdtWaitOnSemaphore::status() const
{
  return (Status);
}

//  ----------------------------------------------------------------------------

inline AdtWaitOnSemaphore::operator bool() const
{
  return (Status == WaitSignaled);
}


//  ----------------------------------------------------------------------------
//  AdtMutex class
//  ----------------------------------------------------------------------------
//  AdtMutex encapsulates mutex synchronisation objects. This class is used in
//  conjunction with AdtWaitOnMutex to aid in program flow control in multi-
//  threaded environments. A mutex is a mutual exclusion. A thread can request a
//  mutex using the AdtWaitOnMutex class. The mutex, if granted, will live for
//  the duration of the instance of AdtWaitOnMutex.
//  ----------------------------------------------------------------------------
class AdtMutex : public AdtReferenceCount
{
friend class AdtWaitOnMutex;

  struct AdtMutexLock
  {
    pthread_t Owner;
    int       LockCount;
  };

protected:
  static pthread_t        InvalidThread;
  mutable AdtSemaphore*   Semaphore;
  mutable AdtMutexLock    MutexLock;
  adtstring               Name;

protected:
  AdtMutex(const AdtMutex& rCopy);

public:
  AdtMutex(const char* pName = 0);
  virtual ~AdtMutex();

  bool                    isValid() const;
  const adtstring&        name() const;
  AdtWaitStatus           wait(unsigned nTimeOut = INFINITE) const;
  void                    release() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtMutex::isValid() const
{
  return ((Semaphore != 0) && Semaphore->isValid());
}

//  ----------------------------------------------------------------------------

inline const adtstring& AdtMutex::name() const
{
  return (Name);
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex class
//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex is a blocking class used to control the flow of a program
//  in multi-threaded environments.
//  ----------------------------------------------------------------------------
class AdtWaitOnMutex
{
  AdtWaitStatus     Status;
  const AdtMutex*   Mutex;

protected:
  AdtWaitOnMutex(const AdtWaitOnMutex& rCopy);

public:
  AdtWaitOnMutex(const AdtMutex* pMutex, unsigned nTimeOut = INFINITE);
  ~AdtWaitOnMutex();

  void              release();
  AdtWaitStatus     status() const;
                    operator bool() const;
};

//  ----------------------------------------------------------------------------

inline AdtWaitOnMutex::~AdtWaitOnMutex()
{
  if (Mutex != 0)
  {
    Mutex->release();
  }
}

//  ----------------------------------------------------------------------------

inline void AdtWaitOnMutex::release()
{
  if (Mutex != 0)
  {
    Mutex->release();

    Mutex = 0;
  }
}

//  ----------------------------------------------------------------------------

inline AdtWaitStatus AdtWaitOnMutex::status() const
{
  return (Status);
}

//  ----------------------------------------------------------------------------

inline AdtWaitOnMutex::operator bool() const
{
  return (Status == WaitSignaled);
}


//  ----------------------------------------------------------------------------
//  Mappings of pthread_t by unsigned
//  ----------------------------------------------------------------------------
typedef std::pair<const unsigned, pthread_t>            unsignedPthreadPair;
typedef std::map<unsigned, pthread_t>                   PthreadByUnsignedMap;
typedef std::map<unsigned, pthread_t>::iterator         PthreadByUnsignedMapIter;
typedef std::map<unsigned, pthread_t>::const_iterator   PthreadByUnsignedMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtThread class
//  ----------------------------------------------------------------------------
//  AdtThread encapsulates a thread context and thread of execution. Creating an
//  instance of this class creates a new thread of execution. The class instance
//  can be used to control the behaviour of that thread of execution.
//  ----------------------------------------------------------------------------
class AdtThread : public AdtReferenceCount
{
protected:
  static unsigned             NextId;
  static pthread_key_t        KeyId;
  static pthread_once_t       KeyIdOnce;
  static long                 ThreadCount;
  static PthreadByUnsignedMap PthreadMap;
  pthread_attr_t              Attr;
  pthread_t                   Thread;
  static pthread_t            MainThread;
  unsigned                    Id;
  unsigned long               ExitCode;
  bool                        IsOpen;
  void*                       Instance;
  AdtThreadCallback           Callback;

private:
  static unsigned           initNextId();
  static void               makeKeyId();
  static unsigned           threadMain(AdtThread* pThis);
  static void*              localThreadCallback(void* pInstance);
  void                      closeThreadHandle();

  AdtThread(const AdtThread& rCopy);

public:
  AdtThread();
  AdtThread(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize = 0);
  virtual ~AdtThread();

  static void               updateThreadCount();
  static long               threadCount();

  bool                      open(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize = 0);
  void                      waitForThreadClosure();
  void                      exit(unsigned long nExitCode);
  unsigned long             exitCode() const;
  bool                      isOpen() const;
  void*                     instance() const;
  AdtThreadCallback         callback() const;

  static unsigned           threadId();
  static unsigned           mainThreadId();
  static bool               isMainThread();
};

//  ----------------------------------------------------------------------------

inline long AdtThread::threadCount()
{
  return (ThreadCount);
}

//  ----------------------------------------------------------------------------

inline unsigned long AdtThread::exitCode() const
{
  return (ExitCode);
}

//  ----------------------------------------------------------------------------

inline bool AdtThread::isOpen() const
{
  return (IsOpen);
}

//  ----------------------------------------------------------------------------

inline void* AdtThread::instance() const
{
  return (Instance);
}

//  ----------------------------------------------------------------------------

inline AdtThreadCallback AdtThread::callback() const
{
  return (Callback);
}


#endif


#endif //AD


#endif //__ADTTHREADS_HPP__
