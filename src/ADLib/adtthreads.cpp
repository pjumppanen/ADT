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
//    adtthreads.cpp
//
//  Purpose:
//    This file includes implementations of classes to supply multi-threaded
//    support for ADLib.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtthreads.hpp"


//  ----------------------------------------------------------------------------
//  AdtWaitForThreadClosure function
//  ----------------------------------------------------------------------------
//  This function goes into a wait state until all threads have closed. You
//  typically call this function prior to destroying the main window to avoid
//  protection violations caused by incorrect destruction order.
//  ----------------------------------------------------------------------------
void AdtWaitForThreadClosure()
{
  int nWaitCount = 0;

  AdtThread::updateThreadCount();

  //Wait until all threads have terminated.
  while (AdtThread::threadCount() > 0)
  {
    msSleep(50);
    nWaitCount++;

    if (nWaitCount > 200)
    {
      //If it takes longer than 10 seconds to shut down then there is
      //probably something wrong in the way you are using threads.
      break;
    }
  }
}


#ifdef _MSC_VER


//  ----------------------------------------------------------------------------

extern "C" void msSleep(unsigned long nMilliseconds)
{
  ::Sleep(nMilliseconds);
}


//  ----------------------------------------------------------------------------
//  AdtWaitForSingleObject function
//  ----------------------------------------------------------------------------
AdtWaitStatus AdtWaitForSingleObject(HANDLE hObject, unsigned nTimeOut)
{
  AdtWaitStatus nStatus   = WaitFailed;
  bool          bContinue = true;

  while (bContinue)
  {
		DWORD   Result = ::WaitForSingleObject(hObject, (nTimeOut == INFINITE) ? 100 : nTimeOut);

		switch (Result)
		{
			case WAIT_OBJECT_0:
			case WAIT_ABANDONED:
			{
			  nStatus   = WaitSignaled;
				bContinue = false;
			  break;
			}

			case WAIT_TIMEOUT:
			{
			  nStatus   = WaitTimedout;
			  bContinue = (nTimeOut == INFINITE) ? true : false;
			  break;
			}

			case WAIT_FAILED:
			{
			  nStatus   = WaitFailed;
			  bContinue = false;
			  break;
			}

			default:
			{
			  throw(std::runtime_error(std::string("WaitForSingleObject() returned unexpected result")));
			  bContinue = false;
			  break;
			}
		}

		if (bContinue)
		{
		  msSleep(0);
		}
  }

  return (nStatus);
}


//  ----------------------------------------------------------------------------
//  AdtMutex method implementations
//  ----------------------------------------------------------------------------
AdtMutex::AdtMutex(const AdtMutex& rCopy)
 : AdtReferenceCount(rCopy)
{
  throw(std::runtime_error(std::string("AdtMutex() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtMutex::AdtMutex(const char* pName)
 : AdtReferenceCount(),
   Name()
{
  if (pName != 0)
  {
    Name = pName;
  }

  HandleMutex = ::CreateMutexA(0, false, pName);
}

//  ----------------------------------------------------------------------------

AdtMutex::~AdtMutex()
{
  if (HandleMutex != 0)
  {
    ::CloseHandle(HandleMutex);
  }
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex method implementations
//  ----------------------------------------------------------------------------
AdtWaitOnMutex::AdtWaitOnMutex(const AdtWaitOnMutex&)
{
  throw(std::runtime_error(std::string("AdtWaitOnMutex() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtWaitOnMutex::AdtWaitOnMutex(const AdtMutex* pMutex, unsigned nTimeOut)
{
  if ((pMutex != 0) && pMutex->isValid())
  {
    HandleMutex = pMutex->handle();
    Status      = AdtWaitForSingleObject(HandleMutex, nTimeOut);
  }
  else
  {
    HandleMutex = 0;
    Status      = WaitFailed;
  }
}


//  ----------------------------------------------------------------------------
//  AdtSemaphore method implementations
//  ----------------------------------------------------------------------------
AdtSemaphore::AdtSemaphore(const AdtSemaphore& rCopy)
 : AdtReferenceCount(rCopy),
   Name(rCopy.Name)
{
  throw(std::runtime_error(std::string("AdtSemaphore() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtSemaphore::AdtSemaphore(const char* pName, int nCount, int nMaxCount)
 : AdtReferenceCount(),
   Name()
{
  if (pName != 0)
  {
    Name = pName;
  }

  HandleSemaphore = ::CreateSemaphoreA(0, nCount, nMaxCount, pName);
}

//  ----------------------------------------------------------------------------

AdtSemaphore::~AdtSemaphore()
{
  if (HandleSemaphore != 0)
  {
    ::CloseHandle(HandleSemaphore);
  }
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore method implementations
//  ----------------------------------------------------------------------------
AdtWaitOnSemaphore::AdtWaitOnSemaphore(const AdtWaitOnSemaphore&)
{
  throw(std::runtime_error(std::string("AdtWaitOnSemaphore() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtWaitOnSemaphore::AdtWaitOnSemaphore(AdtSemaphore* pSemaphore, unsigned nTimeOut)
{
  if ((pSemaphore != 0) && pSemaphore->isValid())
  {
    HandleSemaphore = pSemaphore->handle();
    Status          = AdtWaitForSingleObject(HandleSemaphore, nTimeOut);
  }
  else
  {
    HandleSemaphore = 0;
    Status          = WaitFailed;
  }
}


//  ----------------------------------------------------------------------------
//  AdtThread method implementations
//  ----------------------------------------------------------------------------
unsigned          AdtThread::MainId       = ::GetCurrentThreadId();

//  ----------------------------------------------------------------------------

unsigned AdtThread::threadMain(AdtThread* pThis)
{
  unsigned    nExitCode;

  //Register for COM use
  ::CoInitialize(0);

  HandleMap[pThis->HandleThread]  = pThis->HandleThread;
  nExitCode                       = pThis->Callback(pThis->Instance, pThis->Id);
  pThis->ExitCode                 = nExitCode;

  if (pThis->unlock())
  {
    delete pThis;
  }

  //Un-register COM use
  ::CoUninitialize();

  ::_endthreadex(nExitCode);

  pThis->closeThreadHandle();

  return (nExitCode);
}

//  ----------------------------------------------------------------------------

unsigned __stdcall AdtThread::localThreadCallback(void* pInstance)
{
  unsigned    nExitCode;
  AdtThread*  pThis;

  pThis     = (AdtThread*)pInstance;
  nExitCode = threadMain(pThis);

  return (nExitCode);
}

//  ----------------------------------------------------------------------------

void AdtThread::closeThreadHandle()
{
  if (HandleThread != 0)
  {
    ::CloseHandle(HandleThread);

    HandleMap.erase(HandleThread);
    HandleThread = 0;
  }

  IsOpen = true;
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread(const AdtThread& rCopy)
 : AdtReferenceCount(rCopy)
{
  throw(std::runtime_error(std::string("AdtThread() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread()
 : AdtReferenceCount()
{
  Instance     = 0;
  Callback     = 0;
  ExitCode     = 0;
  IsOpen       = false;
  Id           = 0;
  HandleThread = 0;

  ThreadCount++;
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize)
 : AdtReferenceCount()
{
  Instance     = 0;
  Callback     = 0;
  ExitCode     = 0;
  IsOpen       = false;
  Id           = 0;
  HandleThread = 0;

  open(pCallback, pInstance, nStackSize);

  ThreadCount++;
}

//  ----------------------------------------------------------------------------

AdtThread::~AdtThread()
{
  closeThreadHandle();

  ThreadCount--;
}

//  ----------------------------------------------------------------------------

void AdtThread::updateThreadCount()
{
  HandleByHandleMapIter Iter;

  // The purpose of this function is to check for threads closed by the OS
  // which aren't known to be closed by the AdtThread code. This typically
  // happens if the code resides in a dynamic library that is unloaded. Not
  // accounting for this will result in calls to AdtWaitForThreadClosure()
  // stalling for the timeout period as it waits for already closed threads
  // to close.
  for (Iter = HandleMap.begin() ; Iter != HandleMap.end() ; )
  {
    HANDLE        hHandleThread = (*Iter).second;
    unsigned long nExitCode     = STILL_ACTIVE;

    if ((::GetExitCodeThread(hHandleThread, &nExitCode) == 0) || (nExitCode != STILL_ACTIVE))
    {
      HandleByHandleMapIter DelIter = Iter;

      ++Iter;

      // Thread has been terminated by OS so update thread count and thread map.
      HandleMap.erase(DelIter);

      ThreadCount--;
    }
    else
    {
      ++Iter;
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtThread::open(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize)
{
  bool bOpened = false;

  if ((pCallback != 0) && (pInstance != 0))
  {
    closeThreadHandle();

    Instance      = pInstance;
    Callback      = pCallback;
    ExitCode      = 0;

    lock();

    IsOpen        = true;
    HandleThread  = (HANDLE)_beginthreadex(0, nStackSize, localThreadCallback, (void*)this, 0, &Id);
    bOpened       = (HandleThread != 0);
    IsOpen        = bOpened;

    if (!bOpened)
    {
      unlock();
    }
  }

  return (bOpened);
}

//  ----------------------------------------------------------------------------

void AdtThread::waitForThreadClosure()
{
  if (IsOpen)
  {
    AdtWaitForSingleObject(HandleThread, INFINITE);
    closeThreadHandle();
  }
}

//  ----------------------------------------------------------------------------

void AdtThread::exit(unsigned long nExitCode)
{
  if (::GetCurrentThreadId() == Id)
  {
    if (HandleThread != 0)
    {
      ::_endthreadex(nExitCode);

      closeThreadHandle();

      if (unlock())
      {
        delete this;
      }
    }
  }
  else
  {
    throw(std::runtime_error(std::string("AdtThread::exit() called from wrong thread")));
  }
}

//  ----------------------------------------------------------------------------

unsigned AdtThread::threadId()
{
  return (::GetCurrentThreadId());
}

//  ----------------------------------------------------------------------------

unsigned AdtThread::mainThreadId()
{
  return (MainId);
}

//  ----------------------------------------------------------------------------

bool AdtThread::isMainThread()
{
  bool bIsMain = (::GetCurrentThreadId() == MainId);

  return (bIsMain);
}

#else //!WIN32


//  ----------------------------------------------------------------------------

extern "C" void msSleep(unsigned long nMilliseconds)
{
  ::usleep(nMilliseconds * 1000);
}

#ifdef __APPLE__

//  ----------------------------------------------------------------------------
//  We define this shit because Apple doesn't bloody implement it!!! Stupid!!!
//  ----------------------------------------------------------------------------
int clock_gettime(int, struct timespec* tp)
{
  timeval tod;

  ::gettimeofday(&tod, 0);

  tp->tv_sec  = tod.tv_sec;
  tp->tv_nsec = tod.tv_usec * 1000;
}

#endif //__APPLE__

//  ----------------------------------------------------------------------------
//  AdtSemaphore method implementations
//  ----------------------------------------------------------------------------
void AdtSemaphore::threadExitCleanup(void* pContext)
{
  AdtSemaphore* pThis = (AdtSemaphore*)pContext;

  ::pthread_mutex_unlock(&pThis->Mutex);
}

//  ----------------------------------------------------------------------------

AdtWaitStatus AdtSemaphore::waitOnSemaphore(unsigned nTimeOut)
{
  AdtWaitStatus Status = WaitSignaled;
  bool          bAgain = true;

  while (bAgain)
  {
    if (nTimeOut == INFINITE)
    {
      if (::pthread_mutex_lock(&Mutex) == EDEADLK)
      {
        throw(std::runtime_error(std::string("Recursive semaphores not allowed")));
      }
      else
      {
        pthread_cleanup_push(AdtSemaphore::threadExitCleanup, this);

        if (Count > 0)
        {
          bAgain = false;

          Count--;

          ::pthread_mutex_unlock(&Mutex);
        }
        else
        {
          switch (::pthread_cond_wait(&ConditionVariable, &Mutex))
          {
            case 0:
            {
              if (Count > 0)
              {
                bAgain = false;

                Count--;
              }
              break;
            }

            default:
            {
              Status = WaitFailed;
              bAgain = false;
              break;
            }
          }
        }

        pthread_cleanup_pop(1);
      }
    }
    else
    {
      timespec  tm;

      ::clock_gettime(CLOCK_REALTIME, &tm);

      tm.tv_sec   += nTimeOut / 1000;
      tm.tv_nsec  += (nTimeOut % 1000) * 1000000;

      if (::pthread_mutex_lock(&Mutex) == EDEADLK)
      {
        throw(std::runtime_error(std::string("Recursive semaphores not allowed")));
      }
      else
      {
        pthread_cleanup_push(AdtSemaphore::threadExitCleanup, this);

        if (Count > 0)
        {
          bAgain = false;

          Count--;

          ::pthread_mutex_unlock(&Mutex);
        }
        else
        {
          switch (::pthread_cond_timedwait(&ConditionVariable, &Mutex, &tm))
          {
            case 0:
            {
              if (Count > 0)
              {
                bAgain = false;

                Count--;
              }
              break;
            }

            case ETIMEDOUT:
            {
              Status = WaitTimedout;
              bAgain = false;
              break;
            }

            default:
            {
              Status = WaitFailed;
              bAgain = false;
              break;
            }
          }
        }

        pthread_cleanup_pop(1);
      }
    }
  }

  return (Status);
}

//  ----------------------------------------------------------------------------

AdtSemaphore::AdtSemaphore(const AdtSemaphore& rCopy)
 : AdtReferenceCount(rCopy),
   ConditionVariable(),
   Mutex(),
   MutexAttr(),
   Name(rCopy.Name)
{
  IsValidCondVar    = false;
  IsValidMutexAttr  = false;
  IsValidMutex      = false;

  throw(std::runtime_error(std::string("AdtSemaphore() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtSemaphore::AdtSemaphore(const char* pName, int nCount, int nMaxCount)
 : AdtReferenceCount(),
   ConditionVariable(),
   Mutex(),
   MutexAttr(),
   Name()
{
  if (pName != 0)
  {
    Name = pName;
  }

  if (nCount <= nMaxCount)
  {
    Count             = 0;
    MaxCount          = nMaxCount;
    IsValidCondVar    = (::pthread_cond_init(&ConditionVariable, 0) == 0);
    IsValidMutexAttr  = (::pthread_mutexattr_init(&MutexAttr) == 0);

    ::pthread_mutexattr_settype(&MutexAttr, PTHREAD_MUTEX_ERRORCHECK);

    IsValidMutex      = (::pthread_mutex_init(&Mutex, &MutexAttr) == 0);

    signal(nCount);
  }
  else
  {
    Count             = 0;
    MaxCount          = 0;
    IsValidCondVar    = false;
    IsValidMutexAttr  = false;
    IsValidMutex      = false;
  }
}

//  ----------------------------------------------------------------------------

AdtSemaphore::~AdtSemaphore()
{
  if (IsValidCondVar)
  {
    ::pthread_cond_destroy(&ConditionVariable);
  }

  if (IsValidMutex)
  {
    ::pthread_mutex_destroy(&Mutex);
  }

  if (IsValidMutexAttr)
  {
    ::pthread_mutexattr_destroy(&MutexAttr);
  }
}

//  ----------------------------------------------------------------------------

bool AdtSemaphore::signal(long nCount) const
{
  bool bSignalled = false;

  if (isValid() && (nCount > 0))
  {
    if (::pthread_mutex_lock(&Mutex) == EDEADLK)
    {
      throw(std::runtime_error(std::string("Recursive semaphores not allowed")));
    }
    else
    {
      bool  bSignal;
      int   nMaxSignals;

      pthread_cleanup_push(AdtSemaphore::threadExitCleanup, (void*)this);

      nMaxSignals = (MaxCount - Count);

      if (nCount > nMaxSignals)
      {
        nCount = nMaxSignals;
      }

      bSignal = ((nCount > 0) && (Count == 0));
      Count  += nCount;

      if (bSignal)
      {
        ::pthread_cond_signal(&ConditionVariable);
      }
      else
      {
        ::pthread_mutex_unlock(&Mutex);
      }

      pthread_cleanup_pop(1);

      bSignalled = true;
    }
  }

  return (bSignalled);
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnSemaphore method implementations
//  ----------------------------------------------------------------------------
AdtWaitOnSemaphore::AdtWaitOnSemaphore(const AdtWaitOnSemaphore&)
{
  throw(std::runtime_error(std::string("AdtWaitOnSemaphore() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtWaitOnSemaphore::AdtWaitOnSemaphore(AdtSemaphore* pSemaphore, unsigned nTimeOut)
{
  if ((pSemaphore != 0) && pSemaphore->isValid())
  {
    Status = pSemaphore->waitOnSemaphore(nTimeOut);
  }
  else
  {
    Status = WaitFailed;
  }
}


//  ----------------------------------------------------------------------------
//  AdtMutex method implementations
//  ----------------------------------------------------------------------------
pthread_t AdtMutex::InvalidThread;

//  ----------------------------------------------------------------------------

AdtMutex::AdtMutex(const AdtMutex& rCopy)
 : AdtReferenceCount(rCopy),
   Name(),
   MutexLock()
{
  throw(std::runtime_error(std::string("AdtMutex() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtMutex::AdtMutex(const char* pName)
 : AdtReferenceCount(),
   Name(),
   MutexLock()
{
  if (pName != 0)
  {
    Name = pName;
  }

  MutexLock.LockCount = 0;

  Semaphore = new AdtSemaphore(pName, 1, 1);
}

//  ----------------------------------------------------------------------------

AdtMutex::~AdtMutex()
{
  AdtReleaseReference(Semaphore);
}

//  ----------------------------------------------------------------------------

AdtWaitStatus AdtMutex::wait(unsigned nTimeOut) const
{
  AdtWaitStatus nStatus = WaitFailed;

  if (Semaphore != 0)
  {
    bool bIsOurs = (pthread_equal(pthread_self(), MutexLock.Owner) != 0);

    if (bIsOurs)
    {
      nStatus = WaitSignaled;
      MutexLock.LockCount++;
    }
    else
    {
      AdtWaitOnSemaphore  Wait(Semaphore, nTimeOut);

      nStatus = Wait.status();

      if (nStatus == WaitSignaled)
      {
        MutexLock.Owner     = pthread_self();
        MutexLock.LockCount = 1;
      }
    }
  }

  return (nStatus);
}

//  ----------------------------------------------------------------------------

void AdtMutex::release() const
{
  bool bSignal = true;
  bool bIsOurs = (pthread_equal(pthread_self(), MutexLock.Owner) != 0);

  if (bIsOurs)
  {
    MutexLock.LockCount--;

    bSignal = MutexLock.LockCount == 0;

    if (MutexLock.LockCount < 0)
    {
      throw(std::runtime_error(std::string("AdtMutex() unbalanced wait and release calls")));
    }
  }

  if (bSignal && (Semaphore != 0))
  {
    MutexLock.Owner = InvalidThread;

    Semaphore->signal();
  }
}


//  ----------------------------------------------------------------------------
//  AdtWaitOnMutex method implementations
//  ----------------------------------------------------------------------------
AdtWaitOnMutex::AdtWaitOnMutex(const AdtWaitOnMutex&)
{
  throw(std::runtime_error(std::string("AdtWaitOnMutex() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtWaitOnMutex::AdtWaitOnMutex(const AdtMutex* pMutex, unsigned nTimeOut)
{
  Mutex   = 0;
  Status  = WaitFailed;

  if ((pMutex != 0) && pMutex->isValid())
  {
    Status = pMutex->wait(nTimeOut);

    if (Status == WaitSignaled)
    {
      Mutex = pMutex;
    }
  }
}


//  ----------------------------------------------------------------------------
//  AdtThread method implementations
//  ----------------------------------------------------------------------------
unsigned              AdtThread::NextId       = AdtThread::initNextId();
pthread_key_t         AdtThread::KeyId;
pthread_once_t        AdtThread::KeyIdOnce    = PTHREAD_ONCE_INIT;
pthread_t             AdtThread::MainThread   = ::pthread_self();

//  ----------------------------------------------------------------------------

unsigned AdtThread::initNextId()
{
  AdtThreadId Id;

  pthread_once(&AdtThread::KeyIdOnce, AdtThread::makeKeyId);
  pthread_setspecific(AdtThread::KeyId, Id.pId);

  return (Id.nId);
}

//  ----------------------------------------------------------------------------

void AdtThread::makeKeyId()
{
  pthread_key_create(&AdtThread::KeyId, 0);
}

//  ----------------------------------------------------------------------------

unsigned AdtThread::threadMain(AdtThread* pThis)
{
  unsigned    nExitCode;
  unsigned    nId = ++NextId;
  AdtThreadId Id;

  Id.nId = nId;

  pthread_once(&AdtThread::KeyIdOnce, AdtThread::makeKeyId);
  pthread_setspecific(AdtThread::KeyId, Id.pId);

  PthreadMap[nId] = pThis->Thread;
  pThis->Id       = nId;
  nExitCode       = pThis->Callback(pThis->Instance, pThis->Id);
  pThis->ExitCode = nExitCode;

  if (pThis->unlock())
  {
    delete pThis;
  }

  pThis->closeThreadHandle();

  return (nExitCode);
}

//  ----------------------------------------------------------------------------

void* AdtThread::localThreadCallback(void* pInstance)
{
  AdtThread*  pThis = (AdtThread*)pInstance;

  threadMain(pThis);

  return 0;
}

//  ----------------------------------------------------------------------------

void AdtThread::closeThreadHandle()
{
  Thread = 0;
  IsOpen = false;

  PthreadMap.erase(Id);
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread(const AdtThread& rCopy)
 : AdtReferenceCount(rCopy)
{
  throw(std::runtime_error(std::string("AdtThread() can't be copied")));
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread()
 : AdtReferenceCount(),
   Attr(),
   Thread()
{
  Instance  = 0;
  Callback  = 0;
  ExitCode  = 0;
  Id        = 0;
  IsOpen    = false;

  pthread_attr_init(&Attr);
  pthread_attr_setdetachstate(&Attr, PTHREAD_CREATE_JOINABLE);

  ThreadCount++;
}

//  ----------------------------------------------------------------------------

AdtThread::AdtThread(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize)
 : AdtReferenceCount(),
   Attr(),
   Thread()
{
  Instance  = 0;
  Callback  = 0;
  ExitCode  = 0;
  Id        = 0;
  IsOpen    = false;

  pthread_attr_init(&Attr);

  open(pCallback, pInstance, nStackSize);

  ThreadCount++;
}

//  ----------------------------------------------------------------------------

AdtThread::~AdtThread()
{
  closeThreadHandle();
  pthread_attr_destroy(&Attr);

  ThreadCount--;
}

//  ----------------------------------------------------------------------------

void AdtThread::updateThreadCount()
{
  PthreadByUnsignedMapIter Iter;

  // The purpose of this function is to check for threads closed by the OS
  // which aren't known to be closed by the AdtThread code. This typically
  // happens if the code resides in a dynamic library that is unloaded. Not
  // accounting for this will result in calls to AdtWaitForThreadClosure()
  // stalling for the timeout period as it waits for already closed threads
  // to close.
  for (Iter = PthreadMap.begin() ; Iter != PthreadMap.end() ; )
  {
    pthread_t           rThread         = (*Iter).second;
    int                 nPolicy         = 0;
    struct sched_param  ScheduleParams  = {0};

    if (::pthread_getschedparam(rThread, &nPolicy, &ScheduleParams) == ESRCH)
    {
      PthreadByUnsignedMapIter DelIter = Iter;

      ++Iter;

      // Thread has been terminated by OS so update thread count and thread map.
      PthreadMap.erase(DelIter);

      ThreadCount--;
    }
    else
    {
      ++Iter;
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtThread::open(AdtThreadCallback pCallback, void* pInstance, unsigned nStackSize)
{
  bool bOpened = false;

  if (!IsOpen && (pCallback != 0) && (pInstance != 0))
  {
    closeThreadHandle();

    Instance = pInstance;
    Callback = pCallback;
    Id       = 0;
    ExitCode = 0;

    lock();

    if (nStackSize > 0)
    {
      pthread_attr_setstacksize(&Attr, nStackSize);
    }

    IsOpen = (pthread_create(&Thread, &Attr, localThreadCallback, (void*)this) == 0);

    if (!IsOpen)
    {
      unlock();
    }
  }

  return (IsOpen);
}

//  ----------------------------------------------------------------------------

void AdtThread::waitForThreadClosure()
{
  if (IsOpen)
  {
    pthread_join(Thread, 0);
    closeThreadHandle();
  }
}

//  ----------------------------------------------------------------------------

void AdtThread::exit(unsigned long nExitCode)
{
  if (IsOpen)
  {
    if (pthread_equal(pthread_self(), Thread))
    {
      ExitCode = nExitCode;

      pthread_exit(0);
      closeThreadHandle();

      if (unlock())
      {
        delete this;
      }
    }
    else
    {
      throw(std::runtime_error(std::string("AdtThread::exit() called from wrong thread")));
    }
  }
}

//  ----------------------------------------------------------------------------

unsigned AdtThread::threadId()
{
  AdtThreadId Id;

  Id.pId = pthread_getspecific(AdtThread::KeyId);

  return (Id.nId);
}

//  ----------------------------------------------------------------------------

unsigned AdtThread::mainThreadId()
{
  return (0);
}

//  ----------------------------------------------------------------------------

bool AdtThread::isMainThread()
{
  bool bIsMain = (pthread_equal(pthread_self(), MainThread) != 0);

  return (bIsMain);
}


#endif
