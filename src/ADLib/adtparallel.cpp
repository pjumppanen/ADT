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
//    adtparallel.cpp
//
//  Purpose:
//    This file includes implementations of classes to implement parallelisation
//    of for loops for ADlib.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtparallel.hpp"
#include "adtarrays.hpp"


#ifdef _MSC_VER

#elif __APPLE__

#include <sys/sysctl.h>

#elif __MINGW32__

#include <sysinfoapi.h>

#else

#include <sys/sysinfo.h>

#endif


//  ----------------------------------------------------------------------------
//  StdOutString used when no thread pool in use
//  ----------------------------------------------------------------------------
adtstring SerialisedStdOutString;
adtstring SerialisedStdErrString;


//  ----------------------------------------------------------------------------
//  AdtThreadPool class
//  ----------------------------------------------------------------------------
class AdtThreadPool
{
  struct AdtThreadPoolInfo
  {
    AdtThreadPool*          Parent;
    AdtThread*              Thread;
    AdtSemaphore*           Semaphore;
    adtstring*              StdOutString;
    adtstring*              StdErrString;
    void*                   Context;
    AdtParallelForCallback  Callback;
    int                     ThreadIdx;
    int                     Idx;
    unsigned                ThreadId;
  };

private:
  static int                Instance;
  static int                RunCount;
  static int                ActiveThreads;
  static int                NumberOfThreads;
  static AdtThreadPoolInfo  ThreadsInfo[256];
  static AdtAtomicLock      Lock;
  static AdtMutex*          Mutex;
  static AdtSemaphore*      FreeSemaphore;
  static AdtSemaphore*      CompleteSemaphore;
  static bool               Close;
  static bool               Initialised;
  static bool               HasStdOut;
  static bool               HasStdErr;
  static adtstringList      StdOutStringList;
  static adtstringList      StdErrStringList;

protected:
  static unsigned           threadCallback(void* pInstance, unsigned nThreadId);
  void                      run(AdtThreadPoolInfo* pInfo, unsigned nThreadId);
  bool                      createPool(int nNumberOfThreads);
  void                      flushStringList(bool& bHasContent, adtstringList& rStringList, AdtParallelStdOutCallback pCallback);
  void                      flushStdOutAndStdErr();
  static bool               writeToStdString(const char* pString, bool bStdOut);

public:
  AdtThreadPool();
  virtual ~AdtThreadPool();

  bool                      initialise(int nNumberOfThreads = 0);

  void                      beginRun(int nCount);
  void                      addRun(void* pContext,
                                   AdtParallelForCallback pCallback,
                                   int nIdx);

  void                      waitForCompletion();
  static void               close();
  static int                numberOfThreads();
  static int                numberOfCores();
  static bool               writeToStdOutString(const char* pString);
  static bool               writeToStdErrString(const char* pString);
};

//  ----------------------------------------------------------------------------

int AdtThreadPool::numberOfThreads()
{
  return (NumberOfThreads);
}

//  ----------------------------------------------------------------------------

int                               AdtThreadPool::Instance           = 0;
int                               AdtThreadPool::RunCount           = 0;
int                               AdtThreadPool::ActiveThreads      = 0;
int                               AdtThreadPool::NumberOfThreads    = 0;
AdtThreadPool::AdtThreadPoolInfo  AdtThreadPool::ThreadsInfo[256]   = {0};
AdtAtomicLock                     AdtThreadPool::Lock;
AdtMutex*                         AdtThreadPool::Mutex              = 0;
AdtSemaphore*                     AdtThreadPool::FreeSemaphore      = 0;
AdtSemaphore*                     AdtThreadPool::CompleteSemaphore  = 0;
bool                              AdtThreadPool::Close              = false;
bool                              AdtThreadPool::Initialised        = false;
bool                              AdtThreadPool::HasStdOut          = false;
bool                              AdtThreadPool::HasStdErr          = false;
adtstringList                     AdtThreadPool::StdOutStringList;
adtstringList                     AdtThreadPool::StdErrStringList;

//  ----------------------------------------------------------------------------

AdtParallelStdOutCallback         StdOutCallback = 0;
AdtParallelStdOutCallback         StdErrCallback = 0;

//  ----------------------------------------------------------------------------

unsigned AdtThreadPool::threadCallback(void* pInstance, unsigned nThreadId)
{
  AdtThreadPoolInfo*  pInfo = (AdtThreadPoolInfo*)pInstance;

  pInfo->Parent->run(pInfo, nThreadId);

  return (0);
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::run(AdtThreadPoolInfo* pInfo, unsigned nThreadId)
{
  while (!Close)
  {
    pInfo->ThreadId = nThreadId;

    AdtWaitOnSemaphore WaitJob(pInfo->Semaphore, 50);

    if (WaitJob)
    {
      if (pInfo->Callback != 0)
      {
        try
        {
          pInfo->Callback(pInfo->Context, pInfo->Idx, pInfo->ThreadIdx, *pInfo->StdOutString);
        }
        catch (const std::exception& e)
        {
          pInfo->StdErrString->append(e.what());
        }
        catch (const std::string& e)
        {
          pInfo->StdErrString->append(e);
        }
      }

      AdtWaitOnMutex  WaitUpdate(AdtThreadPool::Mutex);

      if (WaitUpdate)
      {
        pInfo->Context  = 0;
        pInfo->Callback = 0;

        AdtThreadPool::ActiveThreads--;
        AdtThreadPool::RunCount--;

        if (pInfo->StdOutString->length() > 0)
        {
          HasStdOut = true;

          StdOutStringList.push_front(*pInfo->StdOutString);
          pInfo->StdOutString->clear();
        }

        if (pInfo->StdErrString->length() > 0)
        {
          HasStdErr = true;

          StdErrStringList.push_front(*pInfo->StdErrString);
          pInfo->StdErrString->clear();
        }

        AdtThreadPool::FreeSemaphore->signal();

        if (AdtThreadPool::RunCount == 0)
        {
          AdtThreadPool::CompleteSemaphore->signal();
        }

      }
    }
  }

  AdtReleaseReference(pInfo->Semaphore);
}

//  ----------------------------------------------------------------------------

bool AdtThreadPool::createPool(int nNumberOfThreads)
{
  bool bInitialised = false;

  atomicLock(&Lock, true);

  if ((NumberOfThreads == 0) && (nNumberOfThreads > 0) && (nNumberOfThreads < 128))
  {
    NumberOfThreads   = nNumberOfThreads;
    Mutex             = new AdtMutex;
    FreeSemaphore     = new AdtSemaphore(0, NumberOfThreads, NumberOfThreads);
    CompleteSemaphore = new AdtSemaphore(0, 0, 1);
    Close             = false; // Must do this before creating threads or they may exit on creation

    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      for (int cn = 0 ; cn < NumberOfThreads ; cn++)
      {
        ThreadsInfo[cn].Parent        = this;
        ThreadsInfo[cn].Semaphore     = new AdtSemaphore(0, 0, 1);
        ThreadsInfo[cn].StdOutString  = new adtstring;
        ThreadsInfo[cn].StdErrString  = new adtstring;
        ThreadsInfo[cn].Context       = 0;
        ThreadsInfo[cn].Callback      = 0;
        ThreadsInfo[cn].ThreadIdx     = cn;
        ThreadsInfo[cn].Idx           = 0;
        ThreadsInfo[cn].Thread        = new AdtThread(AdtThreadPool::threadCallback, (void*)(ThreadsInfo + cn));

        AdtReleaseReference(ThreadsInfo[cn].Thread);
      }
    }

    bInitialised = true;
    Initialised  = true;
  }

  atomicUnlock(&Lock);

  return (bInitialised);
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::flushStringList(bool& bHasContent, adtstringList& rStringList, AdtParallelStdOutCallback pCallback)
{
  // Technically as HasStdOut is a shared resource it should be locked by mutex
  // but as it only ever gets written to while locked and is atomic in size
  // (ie. a bool type) it should be perfectly safe to read when not locked.
  // Doing so avoids the overhead of unecessary locking.
  if (bHasContent)
  {
    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      adtstring output;

      while (rStringList.size() > 0)
      {
        output.append(rStringList.back());
        rStringList.pop_back();
      }

      if ((pCallback != 0) && (output.length() > 0))
      {
        pCallback(output);
      }

      bHasContent = false;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::flushStdOutAndStdErr()
{
  // Technically as HasStdOut is a shared resource it should be locked by mutex
  // but as it only ever gets written to while locked and is atomic in size
  // (ie. a bool type) it should be perfectly safe to read when not locked.
  // Doing so avoids the overhead of unecessary locking.
  flushStringList(HasStdOut, StdOutStringList, StdOutCallback);
  flushStringList(HasStdErr, StdErrStringList, StdErrCallback);
}

//  ----------------------------------------------------------------------------

bool AdtThreadPool::writeToStdString(const char* pString, bool bStdOut)
{
  bool bWritten = false;

  if (pString != 0)
  {
    unsigned nId = AdtThread::threadId();

    if (nId == AdtThread::mainThreadId())
    {
      if (bStdOut)
      {
        SerialisedStdOutString.append(pString);
      }
      else
      {
        SerialisedStdErrString.append(pString);
      }

      bWritten = true;
    }
    else
    {
      AdtWaitOnMutex  Wait(Mutex);

      if (Wait)
      {
        for (int cn = 0 ; cn < NumberOfThreads ; cn++)
        {
          if (ThreadsInfo[cn].ThreadId == nId)
          {
            if (bStdOut)
            {
              ThreadsInfo[cn].StdOutString->append(pString);
            }
            else
            {
              ThreadsInfo[cn].StdErrString->append(pString);
            }

            bWritten = true;
            break;
          }
        }
      }
    }
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

AdtThreadPool::AdtThreadPool()
{
  Instance++;
}

//  ----------------------------------------------------------------------------

AdtThreadPool::~AdtThreadPool()
{
  Instance--;

  if (Instance == 0)
  {
    close();
  }
}

//  ----------------------------------------------------------------------------

bool AdtThreadPool::initialise(int nNumberOfThreads)
{
  bool bDone = false;

  if (!Initialised)
  {
    int nNumberOfCores = numberOfCores();
    
    if ((nNumberOfThreads > nNumberOfCores) || (nNumberOfThreads == 0))
    {
      nNumberOfThreads = nNumberOfCores;
    }

    bDone = createPool(nNumberOfThreads);
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::beginRun(int nCount)
{
  AdtWaitOnMutex  Wait(Mutex);

  if (Wait)
  {
    RunCount += nCount;
  }
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::addRun(void* pContext,
                           AdtParallelForCallback pCallback,
                           int nIdx)
{
  if (pCallback != 0)
  {
    AdtWaitOnSemaphore WaitFree(FreeSemaphore);

    if (WaitFree)
    {
      AdtWaitOnMutex  WaitAdd(Mutex);

      if (WaitAdd)
      {
        for (int cn = 0 ; cn < NumberOfThreads ; cn++)
        {
          if (ThreadsInfo[cn].Callback == 0)
          {
            AdtThreadPool::ActiveThreads++;

            ThreadsInfo[cn].Context   = pContext;
            ThreadsInfo[cn].Callback  = pCallback;
            ThreadsInfo[cn].Idx       = nIdx;
            ThreadsInfo[cn].Semaphore->signal();
            break;
          }
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::waitForCompletion()
{
  while (true)
  {
    AdtWaitOnSemaphore Wait(CompleteSemaphore, 50);

    flushStdOutAndStdErr();

    if (Wait)
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtThreadPool::close()
{
  if (NumberOfThreads != 0)
  {
    {
      AdtWaitOnMutex  WaitClose(Mutex);

      if (WaitClose)
      {
        Close = true;
      }
    }

    AdtWaitForThreadClosure();

    AdtWaitOnMutex  Wait(Mutex);

    if (Wait)
    {
      for (int cn = 0 ; cn < NumberOfThreads ; cn++)
      {
        delete ThreadsInfo[cn].StdOutString;

        ThreadsInfo[cn].Parent        = 0;
        ThreadsInfo[cn].Semaphore     = 0;
        ThreadsInfo[cn].StdOutString  = 0;
        ThreadsInfo[cn].StdErrString  = 0;
        ThreadsInfo[cn].Context       = 0;
        ThreadsInfo[cn].Callback      = 0;
        ThreadsInfo[cn].ThreadIdx     = 0;
        ThreadsInfo[cn].Idx           = 0;
        ThreadsInfo[cn].Thread        = 0;
      }
    }

    atomicLock(&Lock, true);

    AdtReleaseReference(Mutex);
    AdtReleaseReference(FreeSemaphore);
    AdtReleaseReference(CompleteSemaphore);

    NumberOfThreads   = 0;
    Mutex             = 0;
    FreeSemaphore     = 0;
    CompleteSemaphore = 0;

    atomicUnlock(&Lock);
  }

  Initialised = false;
}

//  ----------------------------------------------------------------------------

int AdtThreadPool::numberOfCores()
{
  int nCores = 1;

#if defined(_MSC_VER) || defined(__MINGW32__)

  SYSTEM_INFO sysinfo;

  GetSystemInfo(&sysinfo);

  nCores = sysinfo.dwNumberOfProcessors;

#elif __APPLE__

  int       nm[2];
  size_t    len = 4;
  uint32_t  count;

  nm[0] = CTL_HW;
  nm[1] = HW_AVAILCPU;

  sysctl(nm, 2, &count, &len, NULL, 0);

  if (count < 1)
  {
    nm[1] = HW_NCPU;

    sysctl(nm, 2, &count, &len, NULL, 0);

    if (count < 1)
    {
      count = 1;
    }
  }

  nCores = count;

#else

  nCores = get_nprocs_conf();

#endif

  if (nCores > 256)
  {
    throw(std::runtime_error(std::string("buffers too small to cater for number of cores - modify the source code of adtparallel.cpp")));
  }

  return (nCores);
}

//  ----------------------------------------------------------------------------

bool AdtThreadPool::writeToStdOutString(const char* pString)
{
  bool bWritten = writeToStdString(pString, true);

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtThreadPool::writeToStdErrString(const char* pString)
{
  bool bWritten = writeToStdString(pString, false);

  return (bWritten);
}


//  ----------------------------------------------------------------------------
//  some AdtThread static members
//  ----------------------------------------------------------------------------
//  Note that we need to put these static members here so that they remain in
//  scope before ThreadPoolSingleton is destroyed.
//  ----------------------------------------------------------------------------
#ifdef _MSC_VER

long                  AdtThread::ThreadCount  = 0;
HandleByHandleMap     AdtThread::HandleMap;

#else

long                  AdtThread::ThreadCount  = 0;
PthreadByUnsignedMap  AdtThread::PthreadMap;

#endif


//  ----------------------------------------------------------------------------
//  AdtThreadPool singlton
//  ----------------------------------------------------------------------------
//  We use a static singlton instance of AdtThreadPool to ensure that the pool
//  is cleaned up on exit.
//  ----------------------------------------------------------------------------
AdtThreadPool   ThreadPoolSingleton;


//  ----------------------------------------------------------------------------

void parallelFor(void* pContext, AdtParallelForCallback pCallback, int nStartIdx, int nEndIdx, bool bSerialise)
{
  if (pCallback == 0)
  {
    throw(std::runtime_error(std::string("invalid callback function")));
  }

  if (nStartIdx > nEndIdx)
  {
    throw(std::runtime_error(std::string("start index must be less than or equal to end index")));
  }

  // if nStartIdx equals nEndIdx then don't bother with thread processing
  if (bSerialise || (nStartIdx == nEndIdx))
  {
    for (int nIdx = nStartIdx ; nIdx <= nEndIdx ; nIdx++)
    {
      SerialisedStdOutString.clear();
      SerialisedStdErrString.clear();

      pCallback(pContext, nIdx, 0, SerialisedStdOutString);

      if ((SerialisedStdOutString.length() > 0) && (StdOutCallback != 0))
      {
        StdOutCallback(SerialisedStdOutString);
      }

      if ((SerialisedStdErrString.length() > 0) && (StdErrCallback != 0))
      {
        StdOutCallback(SerialisedStdErrString);
      }
    }
  }
  else
  {
    AdtThreadPool ThreadPool;

    // Create thread pool on first use. This ensures that if we don't use the
    // parallelFor() function when a thread pool isn't created.
    ThreadPool.initialise(nEndIdx - nStartIdx + 1);
    ThreadPool.beginRun(nEndIdx - nStartIdx + 1);

    for (int nIdx = nStartIdx ; nIdx <= nEndIdx ; nIdx++)
    {
      ThreadPool.addRun(pContext, pCallback, nIdx);
    }

    ThreadPool.waitForCompletion();
  }
}


//  ----------------------------------------------------------------------------
//  Mappings of int by int
//  ----------------------------------------------------------------------------
typedef std::pair<const int, int>                          IntIntPair;
typedef std::multimap<int, int>                            IntByIntMultimap;
typedef std::multimap<int, int>::iterator                  IntByIntMultimapIter;
typedef std::multimap<int, int>::const_iterator            IntByIntMultimapConstIter;

//  ----------------------------------------------------------------------------
//  The basic idea behind priorityParallelFor() is that the order of calling
//  pCallback is prioritised in groups and must be done in that group order.
//  This is to account of parallelisation of operations that have an order
//  dendency. The priority grouping is denoted by the entries in the array
//  pPriorities. For example, a call like,
//
//  priorityParallelFor(MyContext, MyCallBack, MyPriority, 1, 10, false)
//
//  with MyPriority containing,
//
//  MyPriority[1] == 1
//  MyPriority[2] == 2
//  MyPriority[3] == 2
//  MyPriority[4] == 2
//  MyPriority[5] == 3
//  MyPriority[6] == 3
//  MyPriority[7] == 4
//  MyPriority[8] == 5
//  MyPriority[9] == 6
//  MyPriority[10] == 6
//
//  Will call MyCallback with index == 1 first, then index 2,3 & 4 second in any
//  order depending on which thread operates first, then 5 & 6 third, then 7,
//  then 8, and finally 9 & 10 in any order. This mechanism therefore gives
//  some scope for parellelisation of a heirarchical process. The lowest level
//  priority always evaluates first but the values themselves are unimportant.
//  ----------------------------------------------------------------------------

void priorityParallelFor(void* pContext, AdtParallelForCallback pCallback, int* pPriorities, int nStartIdx, int nEndIdx, bool bSerialise)
{
  if (pPriorities != 0)
  {
    int                   nIdx;
    IntByIntMultimap      PriorityMap;
    IntByIntMultimapIter  Iter;

    for (nIdx = nStartIdx ; nIdx <= nEndIdx ; nIdx++)
    {
      PriorityMap.insert(IntIntPair(pPriorities[nIdx], nIdx));
    }

    Iter = PriorityMap.begin();

    while (Iter != PriorityMap.end())
    {
      int cn;
      int nKey    = Iter->first;
      int nCount  = PriorityMap.count(nKey);

      if (bSerialise || (nCount == 1))
      {
        for (cn = 0 ; cn < nCount ; cn++)
        {
          nIdx = Iter->second;

          SerialisedStdOutString.clear();
          SerialisedStdErrString.clear();

          pCallback(pContext, nIdx, 0, SerialisedStdOutString);

          if ((SerialisedStdOutString.length() > 0) && (StdOutCallback != 0))
          {
            StdOutCallback(SerialisedStdOutString);
          }

          if ((SerialisedStdErrString.length() > 0) && (StdErrCallback != 0))
          {
            StdOutCallback(SerialisedStdErrString);
          }

          Iter++;
        }
      }
      else
      {
        AdtThreadPool ThreadPool;

        // Create thread pool on first use. This ensures that if we don't use the
        // parallelFor() function when a thread pool isn't created.
        ThreadPool.initialise(nCount);
        ThreadPool.beginRun(nCount);

        for (cn = 0 ; cn < nCount ; cn++)
        {
          nIdx = Iter->second;

          ThreadPool.addRun(pContext, pCallback, nIdx);

          Iter++;
        }

        ThreadPool.waitForCompletion();
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtParallelStdOutCallback setStdOutCallback(AdtParallelStdOutCallback pCallback)
{
  AdtParallelStdOutCallback pLastCallback;

  pLastCallback   = StdOutCallback;
  StdOutCallback  = pCallback;

  return (pLastCallback);
}

//  ----------------------------------------------------------------------------

AdtParallelStdOutCallback getStdOutCallback()
{
  return (StdOutCallback);
}

//  ----------------------------------------------------------------------------

AdtParallelStdOutCallback setStdErrCallback(AdtParallelStdOutCallback pCallback)
{
  AdtParallelStdOutCallback pLastCallback;

  pLastCallback   = StdErrCallback;
  StdErrCallback  = pCallback;

  return (pLastCallback);
}

//  ----------------------------------------------------------------------------

AdtParallelStdOutCallback getStdErrCallback()
{
  return (StdErrCallback);
}

//  ----------------------------------------------------------------------------

void createThreadPool(int nNumberOfThreads)
{
  AdtThreadPool ThreadPool;

  ThreadPool.initialise(nNumberOfThreads);
}

//  ----------------------------------------------------------------------------

void closeThreadPool()
{
  AdtThreadPool::close();
}

//  ----------------------------------------------------------------------------

int numberOfThreads()
{
  return (AdtThreadPool::numberOfThreads());
}

//  ----------------------------------------------------------------------------

bool writeToStdOutString(const char* pString)
{
  return (AdtThreadPool::writeToStdOutString(pString));
}

//  ----------------------------------------------------------------------------

bool writeToStdErrString(const char* pString)
{
  return (AdtThreadPool::writeToStdErrString(pString));
}

//  ----------------------------------------------------------------------------

AdtArrays*  ShallowCopies[256] = {0};
int         ShallowCopiesCount = 0;

//  ----------------------------------------------------------------------------

void allocateShallowCopies(AdtArrays* pParent)
{
  freeShallowCopies();

  ShallowCopiesCount = AdtThreadPool::numberOfCores();

  for (int nIdx = 0 ; nIdx < ShallowCopiesCount ; nIdx++)
  {
    ShallowCopies[nIdx] = pParent->createShallowCopy();
  }
}

//  ----------------------------------------------------------------------------

void freeShallowCopies()
{
  for (int nIdx = 0 ; nIdx < ShallowCopiesCount ; nIdx++)
  {
    delete ShallowCopies[nIdx];

    ShallowCopies[nIdx] = 0;
  }

  ShallowCopiesCount = 0;
}

//  ----------------------------------------------------------------------------

AdtArrays* shallowCopy(int nIdx)
{
  return (ShallowCopies[nIdx]);
}
