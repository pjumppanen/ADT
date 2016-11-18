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
//    AdtParser.hpp
//
//  Purpose:
//    This file includes declarations of base classes used in code parsers.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTPARSER_HPP
#define __ADTPARSER_HPP


#ifdef __cplusplus


#include "adtcommon.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtFile;
class AdtParser;
class AdtFortranExecutableProgram;
class AdtBlackBoxDefinition;


//  ----------------------------------------------------------------------------
//  Conversion class from object pointer to Hnd for "C" interface
//  ----------------------------------------------------------------------------
class Hnd
{
private:
  void* Handle;

public:
  Hnd(AdtParser* pObj);
  Hnd(AdtParser* pObj, int nLineNumber, const char* pFileName);
  ~Hnd();

  operator void*() const;
};

//  ----------------------------------------------------------------------------

inline Hnd::Hnd(AdtParser* pObj)
{
  Handle = (void*)pObj;
}

//  ----------------------------------------------------------------------------

inline Hnd::~Hnd()
{

}

//  ----------------------------------------------------------------------------

inline Hnd::operator void*() const
{
  return (Handle);
}


//  ----------------------------------------------------------------------------
//  Conversion class from Hnd to object pointer for "C" interface
//  ----------------------------------------------------------------------------
class Obj
{
private:
  AdtParser*  Object;
  bool        Release;

public:
  Obj(void* pHnd, bool bRelease = false);
  ~Obj();

  operator AdtParser*() const;
};

//  ----------------------------------------------------------------------------

inline Obj::Obj(void* pHnd, bool bRelease)
{
  Object  = (AdtParser*)pHnd;
  Release = bRelease;
}

//  ----------------------------------------------------------------------------

inline Obj::operator AdtParser*() const
{
  return (Object);
}

//  ----------------------------------------------------------------------------

#define ObjAndRelease(pHnd) Obj(pHnd, true)


//  ----------------------------------------------------------------------------
//  Macro for declaring class identity methods
//  ----------------------------------------------------------------------------
#define declType\
  virtual bool                        isType(const char* pType) const;\
  virtual const char*                 type() const;\
  virtual AdtParser*                  copy() const;\
  \
  virtual const AdtStringList&        descendantObjNameList() const;\
  virtual const AdtSizeTByStringMap&  descendantObjMap() const;\
  void                                addDescendantObjName(AdtParser** ppObj, const char* pName);\
  \
  static AdtStringList                DescendantObjNameList;\
  static AdtSizeTByStringMap          DescendantObjNameMap;\



//  ----------------------------------------------------------------------------
//  Macro for declaring and implementing the list type method
//  ----------------------------------------------------------------------------
#define declListType(TYPE)\
  virtual const char* listType() const {return (#TYPE);};\


//  ----------------------------------------------------------------------------
//  Macro for implementing class identity methods
//  ----------------------------------------------------------------------------
#define implType(CLASSNAME, PARENTCLASSNAME)\
\
bool CLASSNAME::isType(const char* pType) const\
{\
  bool bIsType = PARENTCLASSNAME::isType(pType);\
  \
  if (!bIsType)\
  {\
    bIsType = (::strcmp(#CLASSNAME, pType) == 0);\
  }\
  \
  return (bIsType);\
}\
\
const char* CLASSNAME::type() const\
{\
  return (#CLASSNAME);\
}\
\
AdtParser* CLASSNAME::copy() const\
{\
  return (new CLASSNAME(*this));\
}\
\
AdtStringList       CLASSNAME::DescendantObjNameList;\
AdtSizeTByStringMap CLASSNAME::DescendantObjNameMap;\
\
const AdtStringList& CLASSNAME::descendantObjNameList() const\
{\
  return (CLASSNAME::DescendantObjNameList);\
}\
\
const AdtSizeTByStringMap& CLASSNAME::descendantObjMap() const\
{\
  return (CLASSNAME::DescendantObjNameMap);\
}\
\
void CLASSNAME::addDescendantObjName(AdtParser** ppObj, const char* pName)\
{\
  if ((pName != 0) && (ppObj != 0))\
  {\
    AdtSizeTByStringMapConstIter Iter = CLASSNAME::DescendantObjNameMap.find(pName);\
\
    if (Iter == CLASSNAME::DescendantObjNameMap.end())\
    {\
      size_t nPtrIndex = ((char*)ppObj - (char*)this) / sizeof(*ppObj);\
\
      CLASSNAME::DescendantObjNameMap[pName] = nPtrIndex;\
      CLASSNAME::DescendantObjNameList.push_back(pName);\
    }\
  }\
}\


//  ----------------------------------------------------------------------------
//  Macro for implementing class identity methods
//  ----------------------------------------------------------------------------
#define implTypeWithoutCopy(CLASSNAME, PARENTCLASSNAME)\
\
bool CLASSNAME::isType(const char* pType) const\
{\
  bool bIsType = PARENTCLASSNAME::isType(pType);\
  \
  if (!bIsType)\
  {\
    bIsType = (::strcmp(#CLASSNAME, pType) == 0);\
  }\
  \
  return (bIsType);\
}\
\
const char* CLASSNAME::type() const\
{\
  return (#CLASSNAME);\
}\


//  ----------------------------------------------------------------------------
//  Macro for implementing object initialisation
//  ----------------------------------------------------------------------------
#define initObject(OBJECT, SOURCE, OBJECTCLASSNAME, bMustMatch)\
\
OBJECT = 0;\
\
addDescendantObjName((AdtParser**)&OBJECT, #OBJECT);\
\
if (SOURCE != 0)\
{\
  SOURCE->lock();\
\
  if (SOURCE->isType(#OBJECTCLASSNAME))\
  {\
    OBJECT = (OBJECTCLASSNAME*)SOURCE;\
    \
    OBJECT->parent(this);\
  }\
  else\
  {\
    UtlReleaseReference(SOURCE);\
    \
    if (bMustMatch)\
    {\
      FAIL();\
    }\
  }\
}\


//  ----------------------------------------------------------------------------
//  Macro for implementing object initialisation
//  ----------------------------------------------------------------------------
#define initObjectOn(OBJECT, SOURCE, OBJECTCLASSNAME, bMustMatch, ON)\
\
ON->OBJECT = 0;\
\
ON->addDescendantObjName((AdtParser**)&ON->OBJECT, #OBJECT);\
\
if (SOURCE != 0)\
{\
  SOURCE->lock();\
\
  if (SOURCE->isType(#OBJECTCLASSNAME))\
  {\
    ON->OBJECT = (OBJECTCLASSNAME*)SOURCE;\
    \
    ON->OBJECT->parent(ON);\
  }\
  else\
  {\
    UtlReleaseReference(SOURCE);\
    \
    if (bMustMatch)\
    {\
      FAIL();\
    }\
  }\
}\


//  ----------------------------------------------------------------------------
//  Macro for implementing object copying
//  ----------------------------------------------------------------------------
#define copyObject(OBJECT, PARENT, OBJECTCLASSNAME)\
OBJECT = 0;\
\
addDescendantObjName((AdtParser**)&OBJECT, #OBJECT);\
\
if (PARENT.OBJECT != 0)\
{\
  OBJECT = new OBJECTCLASSNAME(*(PARENT.OBJECT));\
  \
  if (OBJECT != 0)\
  {\
    OBJECT->parent(this);\
  }\
}\


//  ----------------------------------------------------------------------------
//  Macro for implementing object copying
//  ----------------------------------------------------------------------------
#define copyObjectExplicit(DEST, OBJECT, PARENT, OBJECTCLASSNAME)\
(DEST)->OBJECT = 0;\
\
addDescendantObjName((AdtParser**)&((DEST)->OBJECT), #OBJECT);\
\
if ((PARENT).OBJECT != 0)\
{\
  (DEST)->OBJECT = new OBJECTCLASSNAME(*((PARENT).OBJECT));\
  \
  if ((DEST)->OBJECT != 0)\
  {\
    (DEST)->OBJECT->parent(DEST);\
  }\
}\


//  ----------------------------------------------------------------------------
//  AdtParserContext class
//  ----------------------------------------------------------------------------
//  this class is a object pointer container for use with map and list container
//  classes. We use a simple wrapper like this for two reasons. Firstly to
//  provide a mechanism to replace the pointer without modifying the list or
//  map container containing it and to also allow for object comparison which
//  allows us to sort lists. The former is important because in macro
//  substitution we need to replace part of the parse three with another and by
//  having this wrapper the process is much simplified.
//  ----------------------------------------------------------------------------
class AdtParserContext
{
private:
  AdtParser*          Object;

public:
  AdtParserContext(AdtParser* pObject = 0);
  AdtParserContext(const AdtParserContext& rCopy);
  virtual ~AdtParserContext();

  void                object(AdtParser* pObject);
  AdtParser*          object() const;
  bool                isValid() const;

                      operator AdtParser*() const;
                      operator AdtParser&() const;

  AdtParserContext&   operator =(const AdtParserContext& rA);

  bool                operator ==(const AdtParserContext& rA) const;
  bool                operator !=(const AdtParserContext& rA) const;
  bool                operator > (const AdtParserContext& rA) const;
  bool                operator >=(const AdtParserContext& rA) const;
  bool                operator < (const AdtParserContext& rA) const;
  bool                operator <=(const AdtParserContext& rA) const;
};


//  ----------------------------------------------------------------------------
//  List of AdtParser objects
//  ----------------------------------------------------------------------------
typedef std::list<AdtParserContext>                  AdtParserPtrList;
typedef std::list<AdtParserContext>::iterator        AdtParserPtrListIter;
typedef std::list<AdtParserContext>::const_iterator  AdtParserPtrListConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of AdtParser by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtParserContext>                             AdtParserPtrStringPair;
typedef std::map<string, AdtParserContext, string_less>                       AdtParserPtrByStringMap;
typedef std::map<string, AdtParserContext, string_less>::iterator             AdtParserPtrByStringMapIter;
typedef std::map<string, AdtParserContext, string_less>::const_iterator       AdtParserPtrByStringMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::map<string, AdtParserContext>                                    AdtParserPtrByStringMapCS;
typedef std::map<string, AdtParserContext>::iterator                          AdtParserPtrByStringMapCSIter;
typedef std::map<string, AdtParserContext>::const_iterator                    AdtParserPtrByStringMapCSConstIter;

//  ----------------------------------------------------------------------------

typedef std::multimap<string, AdtParserContext, string_less>                  AdtParserPtrByStringMultiMap;
typedef std::multimap<string, AdtParserContext, string_less>::iterator        AdtParserPtrByStringMultiMapIter;
typedef std::multimap<string, AdtParserContext, string_less>::const_iterator  AdtParserPtrByStringMultiMapConstIter;

//  ----------------------------------------------------------------------------

typedef std::multimap<string, AdtParserContext>                               AdtParserPtrByStringMultiMapCS;
typedef std::multimap<string, AdtParserContext>::iterator                     AdtParserPtrByStringMultiMapCSIter;
typedef std::multimap<string, AdtParserContext>::const_iterator               AdtParserPtrByStringMultiMapCSConstIter;


//  ----------------------------------------------------------------------------
//  AdtParserCodeType enum
//  ----------------------------------------------------------------------------
enum AdtParserCodeType
{
  AdtParserCodeCPP,
  AdtParserCodeDelphi,
  AdtParserCodeFortran,
  AdtParserCodeJava
};


//  ----------------------------------------------------------------------------
//  These class definitions map 1:1 to the grammar rules for the parser
//  ----------------------------------------------------------------------------
class AdtParser : public UtlReferenceCount
{
private:
  mutable const string*               ObjName;
  AdtParserPtrList*                   ObjList;
  const string*                       Comment;
  static AdtParserPtrList             EmptyList;

protected:
  static const string                 EmptyString;
  AdtParser*                          Parent;
  int                                 Depth;
  int                                 LineNumber;
  const char*                         FileName;

protected:
  bool                                findObject(const AdtParserPtrByStringMap& rMap,
                                                 const char* pName,
                                                 const AdtParser*& pObj) const;

  bool                                findObject(const AdtParserPtrByStringMapCS& rMap,
                                                 const char* pName,
                                                 const AdtParser*& pObj) const;

  void                                initList();
  void                                copyList(const AdtParserPtrList* pList, bool bAppend = true);
  void                                flush();

  void                                updateDepth();

  bool                                nextIsBottom(const char*& pDescendantPath, const char* pEnd) const;

  AdtParser*                          findDescendantHelper(const char*& pDescendantPath,
                                                           AdtParserPtrList* pList,
                                                           AdtParserPtrByStringMap* pMap,
                                                           AdtParserPtrByStringMultiMap* pMultiMap) const;

  AdtParser*                          findAscendantWithClassLineageHelper(const char*& pAscendantClassPath, AdtParser** ppSibling = 0) const;

  void                                enumerateDescendant(AdtParserPtrList& rList, const char*& pDescendantPath) const;
  void                                enumerateDescendant(AdtParserPtrByStringMap& rMap, const char*& pDescendantPath) const;
  void                                enumerateDescendant(AdtParserPtrByStringMultiMap& rMap, const char*& pDescendantPath) const;

  void                                enumerateSpecial(AdtParserPtrList& rList);
  void                                enumerateSpecial(AdtParserPtrByStringMap& rMap);
  void                                enumerateSpecial(AdtParserPtrByStringMultiMap& rMap);

  static AdtFile&                     writeExpanded(AdtFile& pOutFile, const char* pString);
  static AdtFile&                     write(AdtFile& pOutFile, const string& rString);
  static AdtFile&                     write(AdtFile& pOutFile, const char* pString);
  static AdtFile&                     write(AdtFile& pOutFile, char nChar);

public:
  AdtParser();
  AdtParser(const AdtParser& rCopy);
  virtual ~AdtParser();

  const AdtParserPtrList&             objList() const;

  void                                enumerate(AdtParserPtrList& rList) const;
  void                                enumerate(AdtParserPtrByStringMap& rMap) const;
  void                                enumerate(AdtParserPtrByStringMultiMap& rMap) const;

  static void                         append(AdtParserPtrByStringMap& rDestMap,
                                             const AdtParserPtrByStringMap& rSrcMap);

  void                                parent(AdtParser* pParent, bool bUpdateDepth = false, bool bUpdateChildDepth = false);
  AdtParser*                          parent() const;

  bool                                add(AdtParser* pObj, bool bAppend = true);
  bool                                addListCopy(AdtParser* pObj, bool bAppend = true);

  bool                                insertBefore(const AdtParser* pObj, AdtParser* pInsertObj);
  bool                                insertAfter(const AdtParser* pObj, AdtParser* pInsertObj);

  bool                                insertBefore(const AdtParser* pObj, const AdtParserPtrList& rObjList);
  bool                                insertAfter(const AdtParser* pObj, const AdtParserPtrList& rObjList);

  void                                remove(AdtParser* pObj);
  void                                remove(const char* pObjName);
  virtual void                        removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList = 0);
  void                                removeAllExcept(const AdtParser* pObj);
  void                                removeAllExcept(const char* pObjName);
  bool                                replace(AdtParser* pObj, AdtParser* pListObj);
  bool                                replaceInParent(AdtParser* pObj);

  AdtParser*                          object(size_t nArg) const;

  bool                                findOutermostMatch(AdtParser* pMatchTo,
                                                         AdtParser*& pThisTopmost,
                                                         AdtParser*& pMatchTopmost,
                                                         const char* pAcceptableClassList = 0);

  AdtParser*                          findDescendantMatch(AdtParser* pMatchTo, AdtParser*& pNewMatchTo);

  static bool                         hasSubString(const char* pString,
                                                   const char* pSubString,
                                                   int& nStart,
                                                   int& nLength,
                                                   bool bMatchCase = false);

  void                                findObjects(AdtParserPtrList& rList,
                                                  const char* pClassName,
                                                  const char* pObjectName = 0,
                                                  bool bMatchCase = false,
                                                  const char* pParentClassName = 0,
                                                  bool bAllowPartialNameMatch = false) const;

  AdtParser*                          findObject(const char* pClassName,
                                                 const char* pObjectName = 0,
                                                 bool bMatchCase = false,
                                                 const char* pParentClassName = 0,
                                                 bool bAllowPartialNameMatch = false) const;

  AdtParser*                          findDescendant(const char* pDescendantPath) const;
  AdtParser*                          findAscendantWithClassLineage(const char* pAscendantClassPath, AdtParser** ppSibling = 0) const;
  AdtParser*                          findAscendantWithClass(const char* pAscendantClass, AdtParser** ppSibling = 0) const;
  void                                printDescendants(AdtFile& pOutFile) const;

  void                                listToMap(AdtParserPtrByStringMap& rMap, const AdtParserPtrList& rList) const;
  void                                listToMap(AdtParserPtrByStringMultiMap& rMap, const AdtParserPtrList& rList) const;
  void                                listToMap(AdtParserPtrByStringMapCS& rMap, const AdtParserPtrList& rList) const;
  void                                listToMap(AdtParserPtrByStringMultiMapCS& rMap, const AdtParserPtrList& rList) const;

  void                                mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMap& rMap) const;
  void                                mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMultiMap& rMap, const char* pKeyName) const;
  void                                mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMapCS& rMap) const;
  void                                mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMultiMapCS& rMap, const char* pKeyName) const;

  static void                         objListToNameList(AdtStringList& rNameList, const AdtParserPtrList& rList);
  static void                         nameListToNameMap(AdtStringByStringMap& rNameMap, const AdtStringList& rNameList, const char* pPrefix = 0);

  void                                enumerateDescendantList(AdtParserPtrList& rList, const char* pDescendantPath) const;
  void                                enumerateDescendantMap(AdtParserPtrByStringMap& rMap, const char* pDescendantPath) const;
  void                                enumerateDescendantMap(AdtParserPtrByStringMultiMap& rMap, const char* pDescendantPath) const;
  void                                enumerateAddByObjList(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;

  virtual void                        enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const;
  virtual void                        enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const;
  virtual void                        enumerateAddObj(AdtParserPtrByStringMultiMap& rMap, AdtParser* pObj) const;
  void                                enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj, const char* pKeyName) const;
  void                                enumerateAddObj(AdtParserPtrByStringMultiMap& rMap, AdtParser* pObj, const char* pKeyName) const;

  void                                name(const char* pObjName);
  const string&                       name() const;

  void                                comment(const char* pComment);
  const string&                       comment() const;

  bool                                isSimpleComment() const;

  void                                translateComment(string& rResult,
                                                       AdtParserCodeType nResultCodeType,
                                                       bool bDropSimpleComments) const;

  virtual bool                        allowableMatch(const AdtParser* pObj) const;
  virtual bool                        isType(const char* pType) const;
  virtual bool                        hasType(const char* pType) const;
  virtual const char*                 type() const;
  virtual const char*                 listType() const;
  virtual AdtParser*                  copy() const = 0;
  size_t                              listSize() const;

  void                                depth(int nDepth, bool bUpdateChildren = false);
  int                                 depth() const;

  void                                lineNumberAndFileName(int nLineNumber,
                                                            const char* pFileName);

  int                                 lineNumber() const;
  const char*                         fileName() const;

  virtual const AdtStringList&        descendantObjNameList() const = 0;
  virtual const AdtSizeTByStringMap&  descendantObjMap() const = 0;
  AdtParser**                         objectAddress(const AdtSizeTByStringMapConstIter& rIter) const;
  AdtParser*                          object(const AdtSizeTByStringMapConstIter& rIter) const;

  bool                                replaceObject(const AdtSizeTByStringMapConstIter& rIter,
                                                    AdtParser* pNewObj,
                                                    AdtParser* pIfOnlyEqualObj = 0);
};

//  ----------------------------------------------------------------------------

inline AdtFile& AdtParser::write(AdtFile& pOutFile, const string& rString)
{
  return (AdtParser::write(pOutFile, rString.c_str()));
}

//  ----------------------------------------------------------------------------

inline const AdtParserPtrList& AdtParser::objList() const
{
  return ((ObjList != 0) ? *ObjList : EmptyList);
}

//  ----------------------------------------------------------------------------

inline void AdtParser::parent(AdtParser* pParent, bool bUpdateDepth, bool bUpdateChildDepth)
{
  Parent = pParent;

  if ((Parent != 0) && bUpdateDepth)
  {
    depth(Parent->depth() + 1, bUpdateChildDepth);
  }
}

//  ----------------------------------------------------------------------------

inline AdtParser* AdtParser::parent() const
{
  return (Parent);
}

//  ----------------------------------------------------------------------------

inline const string& AdtParser::comment() const
{
  return (Comment != 0 ? *Comment : EmptyString);
}

//  ----------------------------------------------------------------------------

inline const string& AdtParser::name() const
{
  return (ObjName != 0 ? *ObjName : EmptyString);
}

//  ----------------------------------------------------------------------------

inline bool AdtParser::allowableMatch(const AdtParser* pObj) const
{
  bool bAllowable = (this->type() == pObj->type());

  return (bAllowable);
}

//  ----------------------------------------------------------------------------

inline bool AdtParser::isType(const char* pType) const
{
  return (::strcmp("AdtParser", pType) == 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtParser::hasType(const char* pType) const
{
  return (false);
}

//  ----------------------------------------------------------------------------

inline const char* AdtParser::type() const
{
  return ("AdtParser");
}

//  ----------------------------------------------------------------------------

inline const char* AdtParser::listType() const
{
  return ("undefined");
}

//  ----------------------------------------------------------------------------

inline size_t AdtParser::listSize() const
{
  return ((ObjList != 0) ? ObjList->size() : 0);
}

//  ----------------------------------------------------------------------------

inline int AdtParser::depth() const
{
  return (Depth);
}

//  ----------------------------------------------------------------------------

inline void AdtParser::lineNumberAndFileName(int nLineNumber,
                                             const char* pFileName)
{
  LineNumber  = nLineNumber;
  FileName    = pFileName;
}

//  ----------------------------------------------------------------------------

inline int AdtParser::lineNumber() const
{
  return (LineNumber);
}

//  ----------------------------------------------------------------------------

inline const char* AdtParser::fileName() const
{
  return (FileName);
}

//  ----------------------------------------------------------------------------

inline AdtParser** AdtParser::objectAddress(const AdtSizeTByStringMapConstIter& rIter) const
{
  size_t      nIndex  = (*rIter).second;
  AdtParser** ppObj   = ((AdtParser**)this) + nIndex;

  return (ppObj);
}

//  ----------------------------------------------------------------------------

inline AdtParser* AdtParser::object(const AdtSizeTByStringMapConstIter& rIter) const
{
  return (*objectAddress(rIter));
}

//  ----------------------------------------------------------------------------

inline Obj::~Obj()
{
  if (Release && (Object != 0))
  {
    UtlReleaseReference(Object);
  }
}

//  ----------------------------------------------------------------------------

inline Hnd::Hnd(AdtParser* pObj, int nLineNumber, const char* pFileName)
{
  if (pObj != 0)
  {
    pObj->lineNumberAndFileName(nLineNumber, pFileName);
  }

  Handle = (void*)pObj;
}


//  ----------------------------------------------------------------------------
//  AdtParserContext method implementations
//  ----------------------------------------------------------------------------
inline AdtParserContext::AdtParserContext(AdtParser* pObject)
{
  Object = 0;

  object(pObject);
}

//  ----------------------------------------------------------------------------

inline AdtParserContext::AdtParserContext(const AdtParserContext& rCopy)
{
  Object = 0;

  object(rCopy.Object);
}

//  ----------------------------------------------------------------------------

inline AdtParserContext::~AdtParserContext()
{
  UtlReleaseReference(Object);
}

//  ----------------------------------------------------------------------------

inline AdtParser* AdtParserContext::object() const
{
  return (Object);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::isValid() const
{
  return (Object != 0);
}

//  ----------------------------------------------------------------------------

inline AdtParserContext::operator AdtParser*() const
{
  return (Object);
}

//  ----------------------------------------------------------------------------

inline AdtParserContext::operator AdtParser&() const
{
  return (*Object);
}

//  ----------------------------------------------------------------------------

inline AdtParserContext& AdtParserContext::operator =(const AdtParserContext& rA)
{
  object(rA.Object);

  return (*this);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator ==(const AdtParserContext& rA) const
{
  bool bIsEqual = ((Object         != 0                ) &&
                   (rA.Object      != 0                ) &&
                   (Object->type() == rA.Object->type()) &&
                   (Object->name() == rA.Object->name()));

  return (bIsEqual);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator !=(const AdtParserContext& rA) const
{
  return (!(operator ==(rA)));
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator > (const AdtParserContext& rA) const
{
  bool bGreaterThan = ((Object          != 0               ) &&
                       (rA.Object       != 0               ) &&
                       (Object->depth() > rA.Object->depth()));

  return (bGreaterThan);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator >=(const AdtParserContext& rA) const
{
  bool bGreaterThanOrEqual = ((Object          != 0                 ) &&
                              (rA.Object       != 0                 ) &&
                              (Object->depth() >= rA.Object->depth()));

  return (bGreaterThanOrEqual);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator < (const AdtParserContext& rA) const
{
  bool bLessThan = ((Object         != 0                 ) &&
                    (rA.Object      != 0                 ) &&
                    (Object->depth() < rA.Object->depth()));

  return (bLessThan);
}

//  ----------------------------------------------------------------------------

inline bool AdtParserContext::operator <=(const AdtParserContext& rA) const
{
  bool bLessThanOrEqual = ((Object          != 0                 ) &&
                           (rA.Object       != 0                 ) &&
                           (Object->depth() <= rA.Object->depth()));

  return (bLessThanOrEqual);
}

//  ----------------------------------------------------------------------------

AdtSourceFileType adtSourceFileTypeFromFile(const string& rSourceFile);


//  ----------------------------------------------------------------------------
//  AdtSourceRoot
//  ----------------------------------------------------------------------------
//  This is an abstract base class to unify support for multiple source
//  languages in the make system. All root objects for source languages should
//  multiply inherit from this plus the language specific base class and
//  implement the pure virtual methods.
//  ----------------------------------------------------------------------------
class AdtSourceRoot
{
private:
  mutable AdtIntByStringMap     IncludeMap;
  mutable AdtIntByStringMap     IsBlackBoxMap;
  mutable AdtStringByStringMap  RegardAsClassFunctionMap;
  mutable AdtStringByStringMap  RegardAsClassSubroutineMap;
  AdtStringList                 ClassPrefixStack;

public:
  AdtSourceRoot();
  AdtSourceRoot(const AdtSourceRoot& rCopy);
  virtual ~AdtSourceRoot();

  void                          clearSourceRoot();

  void                          addBlackBox(const AdtBlackBoxDefinition* pBlackBox,
                                            AdtStringByStringMap& rRegardAsClassFunctionMap,
                                            AdtStringByStringMap& rRegardAsClassSubroutineMap);

  bool                          isBlackBox(const char* pFunctionName) const;

  bool                          isIncludeFunction(const char* pFunctionName) const;
  bool                          isIncludeSubroutine(const char* pSubroutineName) const;

  const char*                   classContext() const;
  void                          pushClassContext(const char* pClassContext);
  void                          popClassContext();

  void                          regardAsClassFunctions(const AdtStringByStringMap& rRegardAsClassFunctionMap) const;
  void                          regardAsClassSubroutines(const AdtStringByStringMap& rRegardAsClassSubroutineMap) const;

  virtual void                  enumerateMethodNames(AdtStringList& rMethodList) const = 0;

  virtual bool                  hasClass(const char* pClassName,
                                         string& rParentClassName) const = 0;

  virtual bool                  buildBlackBoxFile(const char* pBlackBoxFileName,
                                                  AdtStringByStringMap& rRegardAsClassFunctionMap,
                                                  AdtStringByStringMap& rRegardAsClassSubroutineMap) = 0;

  virtual bool                  flattenClass(const char* pClassName,
                                             const AdtParserPtrList& rRootList,
                                             string& rUsesList) = 0;

  virtual bool                  optimise(const AdtStringList& rNewMethodList,
                                         const AdtStringByStringMap& rNewMethodMap) = 0;

  virtual bool                  expandMacros() = 0;

  virtual bool                  extractClassConstructors(AdtStringList& rConstructorList,
                                                         const char* pClassName,
                                                         const char* pParentClassName,
                                                         AdtSourceFileType nAsFileType) const = 0;

  virtual AdtFile&              writeClassMethodsAsFortran(AdtFile& rOutFile,
                                                           const AdtFortranExecutableProgram* pSavedRoot,
                                                           const char* pClassName,
                                                           const char* pLastClassName,
                                                           bool bExpandMacros) const = 0;

  virtual AdtFile&              writeNative(AdtFile& rOutFile) const = 0;

  virtual AdtSourceFileType     sourceFileType() const = 0;
};

//  ----------------------------------------------------------------------------

inline void AdtSourceRoot::clearSourceRoot()
{
  RegardAsClassSubroutineMap.clear();
  RegardAsClassFunctionMap.clear();
  ClassPrefixStack.clear();
  IncludeMap.clear();
  IsBlackBoxMap.clear();
}

//  ----------------------------------------------------------------------------

inline const char* AdtSourceRoot::classContext() const
{
  return (ClassPrefixStack.front().c_str());
}

//  ----------------------------------------------------------------------------

inline void AdtSourceRoot::pushClassContext(const char* pClassContext)
{
  ClassPrefixStack.push_front(pClassContext);
}

//  ----------------------------------------------------------------------------

inline void AdtSourceRoot::popClassContext()
{
  if (!ClassPrefixStack.empty())
  {
    ClassPrefixStack.pop_front();
  }
  else
  {
    FAIL();
  }
}

//  ----------------------------------------------------------------------------

inline bool AdtSourceRoot::isBlackBox(const char* pFunctionName) const
{
  bool bIsBlackBox = ((pFunctionName != 0) && (IsBlackBoxMap.find(pFunctionName) != IsBlackBoxMap.end()));

  return (bIsBlackBox);
}

//  ----------------------------------------------------------------------------

inline bool AdtSourceRoot::isIncludeFunction(const char* pFunctionName) const
{
  bool bIsInclude = false;

  if ((RegardAsClassFunctionMap.find(pFunctionName) != RegardAsClassFunctionMap.end()))
  {
    IncludeMap[pFunctionName] = 1;
    bIsInclude                = true;
  }

  return (bIsInclude);
}

//  ----------------------------------------------------------------------------

inline bool AdtSourceRoot::isIncludeSubroutine(const char* pSubroutineName) const
{
  bool bIsInclude = false;

  if ((RegardAsClassSubroutineMap.find(pSubroutineName) != RegardAsClassSubroutineMap.end()))
  {
    IncludeMap[pSubroutineName] = 1;
    bIsInclude                  = true;
  }

  return (bIsInclude);
}

//  ----------------------------------------------------------------------------

inline void AdtSourceRoot::regardAsClassFunctions(const AdtStringByStringMap& rRegardAsClassFunctionMap) const
{
  RegardAsClassFunctionMap = rRegardAsClassFunctionMap;
}

//  ----------------------------------------------------------------------------

inline void AdtSourceRoot::regardAsClassSubroutines(const AdtStringByStringMap& rRegardAsClassSubroutineMap) const
{
  RegardAsClassSubroutineMap = rRegardAsClassSubroutineMap;
}


//  ----------------------------------------------------------------------------
//  class AdtSliceBuilder
//  ----------------------------------------------------------------------------
//  This class is used to convert xcopy and zero calls into equivalent fortran
//  slices.
//  ----------------------------------------------------------------------------
class AdtSliceBuilder
{
private:
  string  ErrorString;

protected:
  bool    parseArrayArg(const char*& pChar,
                        string& rVarName,
                        AdtStringList& rIndexList) const;

  bool    parseCountArg(const char*& pChar,
                        AdtStringList& rCountList,
                        string& rErrorString) const;

  void    buildSliceExp(string& sCode,
                        const string& rVarName,
                        const AdtStringList& rCountList,
                        const AdtStringList& rIndexList) const;

public:
  AdtSliceBuilder();
  virtual ~AdtSliceBuilder();

  bool    convertZero(const char* pExpression, string& sCode);
  bool    convertXCopy(const char* pExpression, string& sCode);

  void    reportError(const char* pExpression,
                      int nLineNumber,
                      const char* pFileName) const;
};


#endif //__cplusplus
#endif //__ADTPARSER_HPP
