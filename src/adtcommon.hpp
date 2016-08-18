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
//    adtCommon.hpp
//
//  Purpose:
//
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTCOMMON_HPP
#define __ADTCOMMON_HPP


#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
  //  ----------------------------------------------------------------------------
  //  Disable C4996 warning message
  //  ----------------------------------------------------------------------------
  //  'foo': This function or variable may be unsafe. Consider using foo_s instead.
  //  To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
  //  ----------------------------------------------------------------------------
  #pragma warning(disable : 4996)

  //  ----------------------------------------------------------------------------
  //  Disable C4786 warning message
  //  ----------------------------------------------------------------------------
  //  WARNING
  //  'identifier' : identifier was truncated to 'number' characters in the debug
  //  information. This warning occurs a lot with the use of standard template
  //  library containers. There is no workable workaround to this issue. Therefore
  //  we switch it off so that we can see real errors rather than Microsoft
  //  limitations.
  //  ----------------------------------------------------------------------------
  #pragma warning(disable: 4786)


  //  ----------------------------------------------------------------------------
  //  Disable C4800 warning message
  //  ----------------------------------------------------------------------------
  //  WARNING
  //  'type' : forcing value to bool 'true' or 'false' (performance warning). This
  //  warning occurs a lot with the use of standard template library containers.
  //  ----------------------------------------------------------------------------
  #pragma warning(disable: 4800)
#else
  #include "../config.h"
#endif

#if (HAVE_STRICMP == 1) || defined(_MSC_VER)

#define caseless_string_comparison  _stricmp

#elif (HAVE_STRCASECMP == 1)

#define caseless_string_comparison  strcasecmp

#else

#error No case insensitive string comparison function available in standard C libraries

#endif


//  ----------------------------------------------------------------------------
//  Include STL
//  ----------------------------------------------------------------------------
#include <algorithm>
#include <deque>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
#include <string>

#ifdef NDEBUG

//  ----------------------------------------------------------------------------
//  Assertion macros
//  ----------------------------------------------------------------------------
//  No debugging case : In this scenario ASSERTs do nothing
//  ----------------------------------------------------------------------------
#define ASSERT(arg)
#define FAIL()

#else

//  ----------------------------------------------------------------------------
//  Assertion macros
//  ----------------------------------------------------------------------------
//  Debugging case : In this scenario ASSERTs force an exception
//  ----------------------------------------------------------------------------
#define ASSERT(arg) if ((arg) == 0) {int* p = 0;bool b = (p[0] != 0);};
#define FAIL()      ASSERT(0)

#endif //__NO_DEBUGGING__


//  ----------------------------------------------------------------------------
//  Local version of exit
//  ----------------------------------------------------------------------------
//  We define our own in the code base for debugging purposes so that we can
//  easily catch exits with a breakpoint set in this function
//  ----------------------------------------------------------------------------
extern "C" void AdtExit(int nExitCode);


//  ----------------------------------------------------------------------------
//  Extension to the basic_string template in STL
//  ----------------------------------------------------------------------------
template <class T> class string_ext : public std::basic_string<T>
{
protected:
  bool match(const T* pStart, const T* pWord, const T*& pNext, bool bCaseSensitive) const;

  // We need this method because the basic_string implementation uses lazy
  // copying with shared pointers for copy construction. When I create a string
  // copy I want it to be a copy and not an alias. Using aliasing can result in
  // subtle and hard to find and fix bugs.
  void forceCopy(const T* p, size_t pos, size_t n)
  {
    if (p != 0)
    {
      if (n == (size_t)-1)
      {
        n = ::strlen(p + pos);
      }

      std::basic_string<T>::assign(n, (T)0);
      ::memcpy((void*)std::basic_string<T>::c_str(), p + pos, sizeof(T) * n);
    }
  };

public:
  friend inline string_ext operator+(const string_ext& s1, const string_ext& s2)
  {
    string_ext  res(s1);

    res += s2;

    return (res);
  };

  friend inline string_ext operator+(const string_ext& s,  const T* p)
  {
    string_ext  res(s);

    res += p;

    return (res);
  };

  friend inline string_ext operator+(const T* p,   const string_ext& s)
  {
    string_ext  res(p);

    res += s;

    return (res);
  };

  string_ext()
   : std::basic_string<T>()
  {

  };

  string_ext(const string_ext& rhs)
   : std::basic_string<T>()
  {
    forceCopy(rhs.c_str(), 0, rhs.length());
  };

  string_ext(const string_ext& rhs, size_t pos, size_t n)
   : std::basic_string<T>()
  {
    forceCopy(rhs.c_str(), pos, n);
  };

  string_ext(const T* s, size_t n)
   : std::basic_string<T>()
  {
    forceCopy(s, 0, n);
  };

  string_ext(const T* s)
   : std::basic_string<T>()
  {
    forceCopy(s, 0, (size_t)-1);
  };

  string_ext(size_t n, T c)
   : std::basic_string<T>(n, c)
  {

  };

  string_ext& operator=(const string_ext& rhs)
  {
    forceCopy(rhs.c_str(), 0, rhs.length());

    return *this;
  };

  string_ext& operator=(const T* s)
  {
    forceCopy(s, 0, (size_t)-1);

    return *this;
  };

  string_ext& operator=(T c)
  {
    assign(c);
    return *this;
  };

  string_ext& trimLeft(const T* s)
  {
    size_t pos = string_ext::find_first_not_of(s);

    if (pos != string_ext::npos)
    {
      string_ext::assign(string_ext::substr(pos, string_ext::length() - pos));
    }

    return *this;
  };

  string_ext& trimRight(const T* s)
  {
    size_t pos = string_ext::find_last_not_of(s);

    if (pos != string_ext::npos)
    {
      string_ext::assign(string_ext::substr(0, pos + 1));
    }

    return *this;
  };

  string_ext& trim(const T* s)
  {
    trimLeft(s);
    return trimRight(s);
  };

  string_ext& right(size_t nLen)
  {
    if (string_ext::length() >= nLen)
    {
      string_ext::assign(string_ext::substr(string_ext::length() - nLen, nLen));
    }

    return *this;
  };

  string_ext& left(size_t nLen)
  {
    string_ext::assign(string_ext::substr(0, nLen));
    return *this;
  };

  string_ext& mid(size_t nPos, size_t nLen)
  {
    string_ext::assign(string_ext::substr(nPos, nLen));
    return *this;
  };

  string_ext& toUpper()
  {
    for (size_t cx = 0 ; cx < string_ext::length() ; cx++)
    {
      string_ext::at(cx) = ::toupper(string_ext::at(cx));
    }

    return *this;
  };

  string_ext& toLower()
  {
    for (size_t cx = 0 ; cx < string_ext::length() ; cx++)
    {
      string_ext::at(cx) = ::tolower(string_ext::at(cx));
    }

    return *this;
  };

  const T* findMatch(const T* pWord, const T*& pNext, bool bForward = true, bool bCaseSensitive = true) const;

  bool eq(const string_ext& s) const
  {
    return (caseless_string_comparison(*this, s) == 0);
  };

  bool eq(const T* s) const
  {
    return (caseless_string_comparison(*this, s) == 0);
  };

  bool ne(const string_ext& s) const
  {
    return (caseless_string_comparison(*this, s) != 0);
  };

  bool ne(const T* s) const
  {
    return (caseless_string_comparison(*this, s) != 0);
  };

  int icompare(const string_ext& s) const
  {
    return (caseless_string_comparison(*this, s));
  };

  int icompare(const T* s) const
  {
    return (caseless_string_comparison(*this, s));
  };

  operator const T*() const
  {
    return string_ext::c_str();
  };
};

//  ----------------------------------------------------------------------------

template <class T> bool string_ext<T>::match(const T* pStart, const T* pWord, const T*& pNext, bool bCaseSensitive) const
{
  const T* pParseText  = pStart;
  const T* pMatchWord  = pWord;
  bool     bMatched    = true;

  while ((*pMatchWord != 0) && (*pParseText != 0) && bMatched)
  {
    bMatched = bCaseSensitive ? *pMatchWord             == *pParseText
                              : ::tolower(*pMatchWord)  == ::tolower(*pParseText);

    pMatchWord++;
    pParseText++;
  }

  if (*pMatchWord != 0)
  {
    bMatched = false;
  }

  if (bMatched)
  {
    pNext = pParseText;
  }
  else
  {
    pNext = 0;
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

template <class T> const T* string_ext<T>::findMatch(const T* pWord, const T*& pNext, bool bForward, bool bCaseSensitive) const
{
  const T* pResult = 0;

  if (bForward)
  {
    for (const T* pStart = string_ext::c_str() ; pStart != string_ext::c_str() + string_ext::length() - 1 ; ++pStart)
    {
      if (match(pStart, pWord, pNext, bCaseSensitive))
      {
        pResult = pStart;
        break;
      }
    }
  }
  else
  {
    for (const T* pStart = string_ext::c_str() + string_ext::length() - 1 ; pStart - string_ext::c_str() >= 0 ; --pStart)
    {
      if (match(pStart, pWord, pNext, bCaseSensitive))
      {
        pResult = pStart;
        break;
      }
    }
  }

  return (pResult);
}


//  ----------------------------------------------------------------------------
//  declare string type
//  ----------------------------------------------------------------------------
typedef string_ext<char>  string;


//  ----------------------------------------------------------------------------
//  non-case sensitive string comparison
//  ----------------------------------------------------------------------------
struct string_less : public std::binary_function<string, string, bool>
{
  bool operator()(const string& rX, const string& rY) const
  {
    return (rX.icompare(rY) < 0);
  }
};


//  ----------------------------------------------------------------------------
//  List of string objects
//  ----------------------------------------------------------------------------
typedef std::list<string>                                     AdtStringList;
typedef std::list<string>::iterator                           AdtStringListIter;
typedef std::list<string>::const_iterator                     AdtStringListConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of int by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, int>                          AdtIntStringPair;
typedef std::map<string, int, string_less>                    AdtIntByStringMap;
typedef std::map<string, int, string_less>::iterator          AdtIntByStringMapIter;
typedef std::map<string, int, string_less>::const_iterator    AdtIntByStringMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::map<string, int>                                 AdtIntByStringMapCS;
typedef std::map<string, int>::iterator                       AdtIntByStringMapCSIter;
typedef std::map<string, int>::const_iterator                 AdtIntByStringMapCSConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of size_t by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, size_t>                          AdtSizeTStringPair;
typedef std::map<string, size_t, string_less>                    AdtSizeTByStringMap;
typedef std::map<string, size_t, string_less>::iterator          AdtSizeTByStringMapIter;
typedef std::map<string, size_t, string_less>::const_iterator    AdtSizeTByStringMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::map<string, size_t>                                 AdtSizeTByStringMapCS;
typedef std::map<string, size_t>::iterator                       AdtSizeTByStringMapCSIter;
typedef std::map<string, size_t>::const_iterator                 AdtSizeTByStringMapCSConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of size_t by size_t
//  ----------------------------------------------------------------------------
typedef std::pair<const size_t, size_t>                        AdtSizeTSizeTPair;
typedef std::map<size_t, size_t>                               AdtSizeTBySizeTMap;
typedef std::map<size_t, size_t>::iterator                     AdtSizeTBySizeTMapIter;
typedef std::map<size_t, size_t>::const_iterator               AdtSizeTBySizeTMapConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of string by int
//  ----------------------------------------------------------------------------
typedef std::pair<const int, string>                          AdtStringIntPair;
typedef std::map<int, string>                                 AdtStringByIntMap;
typedef std::map<int, string>::iterator                       AdtStringByIntMapIter;
typedef std::map<int, string>::const_iterator                 AdtStringByIntMapConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of int by int
//  ----------------------------------------------------------------------------
typedef std::pair<const int, int>                          AdtIntIntPair;
typedef std::map<int, int>                                 AdtIntByIntMap;
typedef std::map<int, int>::iterator                       AdtIntByIntMapIter;
typedef std::map<int, int>::const_iterator                 AdtIntByIntMapConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of string by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, string>                       AdtStringStringPair;
typedef std::map<string, string, string_less>                 AdtStringByStringMap;
typedef std::map<string, string, string_less>::iterator       AdtStringByStringMapIter;
typedef std::map<string, string, string_less>::const_iterator AdtStringByStringMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::multimap<string, string, string_less>                 AdtStringByStringMultiMap;
typedef std::multimap<string, string, string_less>::iterator       AdtStringByStringMultiMapIter;
typedef std::multimap<string, string, string_less>::const_iterator AdtStringByStringMultiMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::map<string, string>                              AdtStringByStringMapCS;
typedef std::map<string, string>::iterator                    AdtStringByStringMapCSIter;
typedef std::map<string, string>::const_iterator              AdtStringByStringMapCSConstIter;


//  ----------------------------------------------------------------------------
//  UtlReferenceCount Class
//  ----------------------------------------------------------------------------
//  This class provides base level support for object instance reference
//  counting in situations where objects are shared between multiple owners.
//  ----------------------------------------------------------------------------
class UtlReferenceCount
{
private:
  mutable long  LockCount;

public:
  UtlReferenceCount();
  UtlReferenceCount(const UtlReferenceCount& aCopy);
  virtual ~UtlReferenceCount();

  void          lock() const;
  bool          unlock() const;
  int           lockCount() const;
};

//  ----------------------------------------------------------------------------

inline UtlReferenceCount::UtlReferenceCount()
{
  LockCount = 1;
}

//  ----------------------------------------------------------------------------

inline UtlReferenceCount::UtlReferenceCount(const UtlReferenceCount&)
{
  LockCount = 1;
}

//  ----------------------------------------------------------------------------

inline UtlReferenceCount::~UtlReferenceCount()
{
  ASSERT(LockCount == 0);
}


//  ----------------------------------------------------------------------------

inline void UtlReferenceCount::lock() const
{
  LockCount++;
}

//  ----------------------------------------------------------------------------

inline bool UtlReferenceCount::unlock() const
{
  LockCount--;

  ASSERT(LockCount >= 0);

  return (LockCount == 0);
}

//  ----------------------------------------------------------------------------

inline int UtlReferenceCount::lockCount() const
{
  return (LockCount);
}


//  ----------------------------------------------------------------------------
//  UtlReleaseReference macro
//  ----------------------------------------------------------------------------
//  This is a convenience macro used for releasing object references.
//  ----------------------------------------------------------------------------
#define UtlReleaseReference(pObject)\
{\
  const UtlReferenceCount* pReferenceCount = (pObject);\
\
  if ((pReferenceCount != 0) && pReferenceCount->unlock())\
  {\
    delete pReferenceCount;\
  }\
}


//  ----------------------------------------------------------------------------
//  This function maps file path into unified representation
//  ----------------------------------------------------------------------------
string unifyFilePath(const char* pFilePath);


//  ----------------------------------------------------------------------------
//  UtlFilePath class
//  ----------------------------------------------------------------------------
//  This class is used to split a path into it's principle components.
//  ----------------------------------------------------------------------------
class UtlFilePath
{
private:
  string                Drive;
  string                Directory;
  string                Name;
  string                Extension;

public:
  UtlFilePath();
  UtlFilePath(const char* pFileAndPath);
  UtlFilePath(const UtlFilePath& rCopy);
  virtual ~UtlFilePath();

  void                  split(const char* pFileAndPath);
  void                  join(string& rJoinedPath, bool bQuoted = false) const;

  void                  drive(const char* pDrive);
  void                  directory(const char* pDirectory);
  void                  name(const char* pName);
  void                  extension(const char* pExtension);

  const string&         drive() const;
  const string&         directory() const;
  const string&         name() const;
  const string&         extension() const;

  bool                  hasDrive() const;
  bool                  hasDirectory() const;
  bool                  hasName() const;
  bool                  hasExtension() const;
};

//  ----------------------------------------------------------------------------

inline void UtlFilePath::drive(const char* pDrive)
{
  Drive = pDrive;
}

//  ----------------------------------------------------------------------------

inline void UtlFilePath::directory(const char* pDirectory)
{
  Directory = pDirectory;
}

//  ----------------------------------------------------------------------------

inline void UtlFilePath::name(const char* pName)
{
  Name = pName;
}

//  ----------------------------------------------------------------------------

inline void UtlFilePath::extension(const char* pExtension)
{
  Extension = pExtension;
}

//  ----------------------------------------------------------------------------

inline const string& UtlFilePath::drive() const
{
  return (Drive);
}

//  ----------------------------------------------------------------------------

inline const string& UtlFilePath::directory() const
{
  return (Directory);
}

//  ----------------------------------------------------------------------------

inline const string& UtlFilePath::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline const string& UtlFilePath::extension() const
{
  return (Extension);
}

//  ----------------------------------------------------------------------------

inline bool UtlFilePath::hasDrive() const
{
  return (Drive.length() > 0);
}

//  ----------------------------------------------------------------------------

inline bool UtlFilePath::hasDirectory() const
{
  return (Directory.length() > 0);
}

//  ----------------------------------------------------------------------------

inline bool UtlFilePath::hasName() const
{
  return (Name.length() > 0);
}

//  ----------------------------------------------------------------------------

inline bool UtlFilePath::hasExtension() const
{
  return (Extension.length() > 0);
}


//  ----------------------------------------------------------------------------
//  AdtSourceFileType enumeration
//  ----------------------------------------------------------------------------
//  This is used to specify source and target files types in the make system
//  ----------------------------------------------------------------------------
enum AdtSourceFileType
{
  UnknownSourceFileType,
  DelphiSourceFileType,
  CppSourceFileType,
  CppHeaderFileType,
  JavaSourceFileType,
  FortranSourceFileType
};


//  ----------------------------------------------------------------------------
//  enum AdtAutoType
//  ----------------------------------------------------------------------------
enum AdtAutoType
{
  AdtAutoType_DOUBLE,
  AdtAutoType_FLOAT,
  AdtAutoType_INT,
  AdtAutoType_UNSIGNED_INT,
  AdtAutoType_SHORT,
  AdtAutoType_UNSIGNED_SHORT,
  AdtAutoType_LONG,
  AdtAutoType_UNSIGNED_LONG,
  AdtAutoType_CHAR,
  AdtAutoType_UNSIGNED_CHAR,
  AdtAutoType_LONG_LONG,
  AdtAutoType_UNSIGNED_LONG_LONG,
  AdtAutoType_BOOL,
  AdtAutoType_UNDEFINED,
};


//  ----------------------------------------------------------------------------
//  enum AdtAutoMode
//  ----------------------------------------------------------------------------
enum AdtAutoMode
{
  AdtAutoMode_MANUAL      = 0,
  AdtAutoMode_AUTODEC     = 1,
  AdtAutoMode_AUTOINIT    = 2,
  AdtAutoMode_FN_ARGUMENT = 3,
};


//  ----------------------------------------------------------------------------
//  enum AdtAutoDir
//  ----------------------------------------------------------------------------
enum AdtAutoDir
{
  AdtAutoDir_INOUT      = 0,
  AdtAutoDir_IN         = 1,
  AdtAutoDir_OUT        = 2,
  AdtAutoDir_UNDEFINED  = 3,
};


#endif  //__ADTCOMMON_HPP
