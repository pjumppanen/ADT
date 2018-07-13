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
//    AdtParser.cpp
//
//  Purpose:
//    This file includes implementations of base classes used in code parsers.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtparser.hpp"
#include "adtutils.hpp"
#include "adtfortran.hpp"
#include "adtblackbox.hpp"


//  ----------------------------------------------------------------------------
//  Instantiate static members
//  ----------------------------------------------------------------------------
AdtParserPtrList  AdtParser::EmptyList;
const string      AdtParser::EmptyString;


//  ----------------------------------------------------------------------------
//  AdtParserContext method implementations
//  ----------------------------------------------------------------------------
void AdtParserContext::object(AdtParser* pObject)
{
  AdtParser*  pOldObject;

  pOldObject  = Object;
  Object      = pObject;

  if (Object != 0)
  {
    Object->lock();
  }

  UtlReleaseReference(pOldObject);
}


//  ----------------------------------------------------------------------------
//  AdtParser method implementations
//  ----------------------------------------------------------------------------
bool AdtParser::findObject(const AdtParserPtrByStringMap& rMap, const char* pName, const AdtParser*& pObj) const
{
  bool bFound;

  bFound  = false;
  pObj    = 0;

  if (pName != 0)
  {
    AdtParserPtrByStringMapConstIter Iter = rMap.find(pName);

    if (Iter != rMap.end())
    {
      pObj    = (*Iter).second;
      bFound  = true;
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

bool AdtParser::findObject(const AdtParserPtrByStringMapCS& rMap, const char* pName, const AdtParser*& pObj) const
{
  bool bFound;

  bFound  = false;
  pObj    = 0;

  if (pName != 0)
  {
    AdtParserPtrByStringMapCSConstIter Iter = rMap.find(pName);

    if (Iter != rMap.end())
    {
      pObj    = (*Iter).second;
      bFound  = true;
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

void AdtParser::initList()
{
  if (ObjList == 0)
  {
    ObjList = new AdtParserPtrList;
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::copyList(const AdtParserPtrList* pList, bool bAppend)
{
  if ((pList != 0) && (pList->size() > 0))
  {
    initList();

    if (ObjList != 0)
    {
      AdtParserPtrListConstIter Iter;

      if (bAppend)
      {
        for (Iter = pList->begin() ; Iter != pList->end() ; ++Iter)
        {
          AdtParser* pObj = *Iter;

          if (pObj != 0)
          {
            AdtParser* pCopy = pObj->copy();

            if (pCopy != 0)
            {
              ObjList->push_back(pCopy);
              pCopy->parent(this);

              UtlReleaseReference(pCopy);
            }
          }
        }
      }
      else
      {
        // We traverse the list in reverse direction to preserve the order of the
        // objects inserted into the list.
        Iter = pList->end();

        do
        {
          --Iter;

          AdtParser* pObj = *Iter;

          if (pObj != 0)
          {
            AdtParser* pCopy = pObj->copy();

            if (pCopy != 0)
            {
              ObjList->push_front(pCopy);
              pCopy->parent(this);

              UtlReleaseReference(pCopy);
            }
          }
        }
        while (Iter != pList->begin());
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::flush()
{
  if (ObjList != 0)
  {
    ObjList->clear();
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::updateDepth()
{
  AdtParser*  pObject = 0;

  if (descendantObjMap().size() > 0)
  {
    AdtSizeTByStringMapConstIter Iter;

    for (Iter = descendantObjMap().begin() ; Iter != descendantObjMap().end() ; ++Iter)
    {
      AdtParser*  pDescendant = object(Iter);

      if (pDescendant != 0)
      {
        pDescendant->depth(depth() + 1, true);
      }
    }
  }

  //Continue searching
  if ((ObjList != 0) && (ObjList->size() > 0))
  {
    AdtParserPtrListIter  Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pDescendant = *Iter;

      if (pDescendant != 0)
      {
        pDescendant->depth(depth() + 1, true);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::nextIsBottom(const char*& pDescendantPath, const char* pEnd) const
{
  bool bIsBottom = false;

  switch (*pEnd)
  {
    case ',':
    {
      pDescendantPath = pEnd + 1;
      break;
    }

    case ';':
    {
      pDescendantPath = pEnd + 1;
      bIsBottom       = true;
      break;
    }

    case '\0':
    {
      pDescendantPath = pEnd;
      bIsBottom       = true;
      break;
    }

    default:
    {
      // should never happen
      FAIL();
      break;
    }
  }

  return (bIsBottom);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findDescendantHelper(const char*& pDescendantPath,
                                           AdtParserPtrList* pList,
                                           AdtParserPtrByStringMap* pMap,
                                           AdtParserPtrByStringMultiMap* pMultiMap) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  const char*     pStart  = pDescendantPath;
  const char*     pEnd    = ::strchr(pDescendantPath, ',');
  const char*     pEnd2   = ::strchr(pDescendantPath, ';');
  bool            bBottom = false;
  AdtParser*      pObject = 0;

  if (pEnd == 0)
  {
    pEnd = pEnd2;
  }
  else if ((pEnd2 != 0) && (pEnd2 < pEnd))
  {
    pEnd = pEnd2;
  }

  if (pStart != 0)
  {
    if (pEnd == 0)
    {
      pEnd = pStart + strlen(pStart);
    }

    size_t                        nLength = pEnd - pStart;
    string                        ObjectName(pStart, 0, nLength);
    AdtSizeTByStringMapConstIter  Iter    = descendantObjMap().find(ObjectName);

    if ((Iter != descendantObjMap().end()) && (object(Iter) != 0))
    {
      pObject = object(Iter);
      bBottom = nextIsBottom(pDescendantPath, pEnd);

      if (!bBottom)
      {
        //recurse to a lower level
        pObject = pObject->findDescendantHelper(pDescendantPath,
                                                pList,
                                                pMap,
                                                pMultiMap);
      }
      else
      {
        if (pList != 0)
        {
          pObject->enumerateSpecial(*pList);
        }

        if (pMap != 0)
        {
          pObject->enumerateSpecial(*pMap);
        }

        if (pMultiMap != 0)
        {
          pObject->enumerateSpecial(*pMultiMap);
        }
      }
    }
    else if (((pList != 0) || (pMap != 0) || (pMultiMap != 0)) && (ObjectName == this->listType()))
    {
      // Look through the list of objects for a match
      bBottom = nextIsBottom(pDescendantPath, pEnd);

      AdtParserPtrListConstIter Iter;

      for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
      {
        const char* pTempDescendantPath = pDescendantPath;
        AdtParser*  pObj                = *Iter;

        if (pObj != 0)
        {
          if (!bBottom)
          {
            pObj->findDescendantHelper(pTempDescendantPath,
                                       pList,
                                       pMap,
                                       pMultiMap);
          }
          else
          {
            if (pList != 0)
            {
              pObj->enumerateSpecial(*pList);
            }

            if (pMap != 0)
            {
              pObj->enumerateSpecial(*pMap);
            }

            if (pMultiMap != 0)
            {
              pObj->enumerateSpecial(*pMultiMap);
            }
          }
        }
      }
    }
    else
    {
      //We failed to find the object so move on to the next path
      bBottom = nextIsBottom(pDescendantPath, pEnd);
    }
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findAscendantWithClassLineageHelper(const char*& pAscendantClassPath, AdtParser** ppSibling) const
{
  //Typical search string. Comma seperated list of object classes to ascend
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList"
  //
  const char*     pStart  = pAscendantClassPath;
  const char*     pEnd    = ::strchr(pAscendantClassPath, ',');
  bool            bTop    = (pEnd == 0);
  AdtParser*      pObject = 0;

  if (pStart != 0)
  {
    size_t      nLength = (pEnd != 0) ? pEnd - pStart : ::strlen(pStart);
    string      ClassName(pStart, 0, nLength);
    AdtParser*  pParent = parent();

    if ((pParent != 0) && pParent->isType(ClassName))
    {
      pObject = pParent;

      if (ppSibling != 0)
      {
        *ppSibling = (AdtParser*)this;
      }

      if (!bTop)
      {
        pAscendantClassPath = pEnd + 1;

        //recurse to a higher level
        pObject = pObject->findAscendantWithClassLineageHelper(pAscendantClassPath, ppSibling);
      }
    }
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendant(AdtParserPtrList& rList, const char*& pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  findDescendantHelper(pDescendantPath, &rList, 0, 0);
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendant(AdtParserPtrByStringMap& rMap, const char*& pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  findDescendantHelper(pDescendantPath, 0, &rMap, 0);
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendant(AdtParserPtrByStringMultiMap& rMap, const char*& pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  findDescendantHelper(pDescendantPath, 0, 0, &rMap);
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateSpecial(AdtParserPtrList& rList)
{
  if (ObjList == 0)
  {
    enumerateAddObj(rList, this);
  }
  else
  {
    enumerate(rList);
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateSpecial(AdtParserPtrByStringMap& rMap)
{
  if (ObjList == 0)
  {
    enumerateAddObj(rMap, this);
  }
  else
  {
    enumerate(rMap);
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateSpecial(AdtParserPtrByStringMultiMap& rMap)
{
  if (ObjList == 0)
  {
    enumerateAddObj(rMap, this);
  }
  else
  {
    enumerate(rMap);
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerate(AdtParserPtrList& rList) const
{
  if (ObjList != 0)
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        pObj->enumerateAddObj(rList, pObj);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerate(AdtParserPtrByStringMap& rMap) const
{
  if (ObjList != 0)
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        pObj->enumerateAddObj(rMap, pObj);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerate(AdtParserPtrByStringMultiMap& rMap) const
{
  if (ObjList != 0)
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pObj = *Iter;

      if (pObj != 0)
      {
        pObj->enumerateAddObj(rMap, pObj);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::append(AdtParserPtrByStringMap& rDestMap,
                       const AdtParserPtrByStringMap& rSrcMap)
{
  AdtParserPtrByStringMapConstIter  Iter;

  for (Iter = rSrcMap.begin() ; Iter != rSrcMap.end() ; ++Iter)
  {
    rDestMap.insert(*Iter);
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddObj(AdtParserPtrList& rList, AdtParser* pObj) const
{
  if (pObj != 0)
  {
    rList.push_back(pObj);
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  enumerateAddObj(rMap, pObj, name());
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddObj(AdtParserPtrByStringMultiMap& rMap, AdtParser* pObj) const
{
  enumerateAddObj(rMap, pObj, name());
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddObj(AdtParserPtrByStringMap& rMap, AdtParser* pObj, const char* pKeyName) const
{
  if ((pObj != 0) && (pKeyName != 0))
  {
    rMap.insert(AdtParserPtrByStringMap::value_type(pKeyName, pObj));
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddObj(AdtParserPtrByStringMultiMap& rMap, AdtParser* pObj, const char* pKeyName) const
{
  if ((pObj != 0) && (pKeyName != 0))
  {
    rMap.insert(AdtParserPtrByStringMap::value_type(pKeyName, pObj));
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::isSimpleComment() const
{
  const char* pChar;
  int         cn;
  int         nNZ            = 0;
  int         Histogram[256] = {0};

  for (pChar = comment() ; *pChar != 0 ; ++pChar)
  {
    switch (*pChar)
    {
      case '\n':
      case '\r':
      case '\t':
      case ' ':
      {
        // Ignore these
        break;
      }

      default:
      {
        unsigned char nIndex = *((unsigned char*)pChar);

        Histogram[nIndex]++;
        break;
      }
    }
  }

  for (cn = 0 ; cn < 256 ; cn++)
  {
    if (Histogram[cn] != 0)
    {
      nNZ++;
    }
  }

  bool bSimple = (nNZ <= 4);

  return (bSimple);
}

//  ----------------------------------------------------------------------------

void AdtParser::translateComment(string& rResult,
                                 AdtParserCodeType nResultCodeType,
                                 bool bDropSimpleComments) const
{
  bool        bOk      = true;
  const char* pComment = comment();

  rResult = "";

  if ((pComment != 0) && (*pComment != 0) && (!bDropSimpleComments || !AdtParser::isSimpleComment()))
  {
    const char* pLinePrefix = 0;

    switch (nResultCodeType)
    {
      case AdtParserCodeCPP:
      case AdtParserCodeDelphi:
      case AdtParserCodeJava:
      {
        pLinePrefix = "// ";
        break;
      }

      case AdtParserCodeFortran:
      {
        pLinePrefix = "! ";
        break;
      }

      default:
      {
        bOk = false;
        FAIL();
        break;
      }
    }

    if ((pLinePrefix != 0) && bOk)
    {
      const char* pChar = AdtParse::nextWord(pComment);

      while ((*pChar != 0) && bOk)
      {
        string sCommentLines;

        switch (*pChar)
        {
          case '{':
          {
            // Delphi multiline comment
            pChar++;

            AdtParse::matchExtractWord(sCommentLines,
                                       "}",
                                       pChar);

            AdtParse::matchWord(pChar, "}");
            break;
          }

          case '(':
          {
            pChar++;

            // Possibly a delphi multiline comment
            if (*pChar == '*')
            {
              pChar++;

              AdtParse::matchExtractWord(sCommentLines,
                                         "*)",
                                         pChar);

              AdtParse::matchWord(pChar, "*)");
            }
            else
            {
              bOk = false;
              FAIL();
            }
            break;
          }

          case '/':
          {
            // C++, Java or Delphi single or multi-line comment
            pChar++;

            if (*pChar == '/')
            {
              pChar++;

              AdtParse::extractWord(sCommentLines,
                                    "\n",
                                    pChar,
                                    false);

              AdtParse::matchWord(pChar, "\n");
            }
            else if (*pChar == '*')
            {
              pChar++;

              AdtParse::matchExtractWord(sCommentLines,
                                         "*/",
                                         pChar);

              AdtParse::matchWord(pChar, "*/");
            }
            else
            {
              bOk = false;
              FAIL();
            }
            break;
          }

          case '!':
          {
            // Fortran comment
            pChar++;

            AdtParse::extractWord(sCommentLines,
                                  "\n",
                                  pChar,
                                  false);

            AdtParse::matchWord(pChar, "\n");
            break;
          }

          case '\r':
          case '\n':
          case '\t':
          case ' ':
          {
            pChar++;
            break;
          }

          default:
          {
            // Unknown format
            bOk = false;
            FAIL();
            break;
          }
        }

        const char* pCommentLine = sCommentLines;

        while (*pCommentLine != 0)
        {
          string sCommentLine;

          AdtParse::extractWord(sCommentLine,
                                "\n",
                                pCommentLine,
                                false);

          AdtParse::matchWord(pCommentLine, "\n");

          rResult += pLinePrefix;
          rResult += sCommentLine;
          rResult += "\n";
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtFile& AdtParser::writeExpanded(AdtFile& pOutFile,
                                  const char* pString,
                                  bool bExcludeLast)
{
  if (pOutFile.isOpen() && (pString != 0) && (pString[0] != 0))
  {
    string  sCopy(pString);
    char*   pStart    = (char*)((const char*)sCopy);
    char*   pEnd      = pStart;

    while (*pEnd != 0)
    {
      bool  bContinue = true;

      while ((*pEnd != 0) && bContinue)
      {
        switch (*pEnd)
        {
          case '\n':
          {
            *pEnd = 0;

            if (*(pEnd + 1) == '\r')
            {
              pEnd++;
              *pEnd = 0;
            }

            bContinue = false;
            break;
          }

          case '\r':
          {
            *pEnd = 0;

            if (*(pEnd + 1) == '\n')
            {
              pEnd++;
              *pEnd = 0;
            }

            bContinue = false;
            break;
          }

          default:
          {
            break;
          }
        }

        pEnd++;
      }

      pOutFile.write(pStart);

      pStart = pEnd;

      if ((!bExcludeLast || (*pEnd != 0)) && !bContinue)
      {
        pOutFile.newline();
      }
    }
  }

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtParser::write(AdtFile& pOutFile, const char* pString)
{
  pOutFile.write(pString);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtParser::write(AdtFile& pOutFile, char nChar)
{
  pOutFile.write(nChar);

  return (pOutFile);
}

//  ----------------------------------------------------------------------------

void AdtParser::bindComments(AdtCommon* pCompilerBase)
{
  if (CanBindComments && (pCompilerBase != 0))
  {
    const string* pComment = 0;

    pCompilerBase->extractComment(&pComment, FileName, LineNumber);
    this->bindComment(pComment);
  }

  AdtStringListConstIter  ObjNameIter;
  const AdtStringList&    rObjList = descendantObjNameList();

  for (ObjNameIter = rObjList.begin() ; ObjNameIter != rObjList.end() ; ++ObjNameIter)
  {
    AdtSizeTByStringMapConstIter  MapIter = descendantObjMap().find(*ObjNameIter);
    AdtParser*                    pObj    = object(MapIter);

    if (pObj != 0)
    {
      pObj->bindComments(pCompilerBase);
    }
  }

  AdtParserPtrListConstIter Iter;
  const AdtParserPtrList&   rList = objList();

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if (pObj != 0)
    {
      pObj->bindComments(pCompilerBase);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::bindComment(const string* pComment)
{
  if (pComment != 0)
  {
    Comment = pComment;
  }
}

//  ----------------------------------------------------------------------------

AdtParser::AdtParser()
{
  ObjList         = 0;
  ObjName         = 0;
  Comment         = 0;
  Parent          = 0;
  Depth           = 0;
  LineNumber      = 0;
  FileName        = 0;
  CanBindComments = false;
}

//  ----------------------------------------------------------------------------

AdtParser::AdtParser(const AdtParser& rCopy)
{
  ObjList         = 0;
  ObjName         = rCopy.ObjName;
  Comment         = rCopy.Comment;
  Parent          = 0;
  Depth           = rCopy.Depth;
  LineNumber      = rCopy.LineNumber;
  FileName        = rCopy.FileName;
  CanBindComments = rCopy.CanBindComments;

  copyList(rCopy.ObjList);
}

//  ----------------------------------------------------------------------------

AdtParser::~AdtParser()
{
  flush();

  if (ObjList != 0)
  {
    delete ObjList;
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::lineNumberAndFileName(int nLineNumber,
                                      const char* pFileName)
{
  // This is a hacky solution to get around the issue of finding the right
  // starting line number of compound solutions. As in a Pascal IMPLEMENTATION
  // section, we pass the start line number in the object constructor and set
  // LineNmber to that.
  if ((LineNumber == 0) || (LineNumber > nLineNumber))
  {
    LineNumber = nLineNumber;
  }

  FileName = pFileName;

  // If this object contains others then we need to find the minimum linenumber
  // of all contained objects. This is used for both error contexts and in
  // re-binding comments with code.
  AdtParserPtrListConstIter Iter;
  const AdtParserPtrList&   rList = objList();

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if ((pObj             != 0         ) &&
        (pObj->FileName   == FileName  ) &&
        (pObj->LineNumber <  LineNumber))
    {
      LineNumber = pObj->LineNumber;
    }
  }

  AdtSizeTByStringMapConstIter  MapIter;
  const AdtSizeTByStringMap&    rMap = descendantObjMap();

  for (MapIter = rMap.begin() ; MapIter != rMap.end() ; ++MapIter)
  {
    AdtParser* pObj = object(MapIter);

    if ((pObj             != 0         ) &&
        (pObj->FileName   == FileName  ) &&
        (pObj->LineNumber <  LineNumber))
    {
      LineNumber = pObj->LineNumber;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::name(const char* pObjName)
{
  if (pObjName != 0)
  {
    AdtCommon::allocString(pObjName, &ObjName);
  }
  else
  {
    ObjName = 0;
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::comment(const char* pComment)
{
  if (pComment != 0)
  {
    AdtCommon::allocString(pComment, &Comment);
  }
  else
  {
    Comment = 0;
  }
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::object(size_t nArg) const
{
  AdtParser* pObject = 0;

  if ((ObjList != 0) && (nArg < listSize()))
  {
    AdtParserPtrListConstIter Iter;
    size_t                    nCount = 0;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      if (nCount == nArg)
      {
        pObject = *Iter;
        break;
      }

      nCount++;
    }
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

bool AdtParser::findOutermostMatch(AdtParser* pMatchTo,
                                   AdtParser*& pThisTopmost,
                                   AdtParser*& pMatchTopmost,
                                   const char* pAcceptableClassList)
{
  bool bMatched = false;

  pThisTopmost  = 0;
  pMatchTopmost = 0;

  if (pMatchTo != 0)
  {
    AdtParser* pThisTopmostParent   = this;
    AdtParser* pMatchTopmostParent  = pMatchTo;

    while ((pThisTopmostParent              != 0                              ) &&
           (pMatchTopmostParent             != 0                              ) &&
           (pMatchTopmostParent->listSize() <= 1                              ) &&
           (pMatchTopmostParent->listSize() == pThisTopmostParent->listSize() ) &&
            pMatchTopmostParent->allowableMatch(pThisTopmostParent))
    {
      if (pAcceptableClassList != 0)
      {
        bool        bContinue = true;
        const char* pStart    = 0;
        const char* pEnd      = pAcceptableClassList - 1;

        while (bContinue)
        {
          pStart      = pEnd + 1;
          pEnd        = ::strchr(pStart, ',');

          if (pEnd == 0)
          {
            pEnd      = ::strchr(pStart, '\0');
            bContinue = false;
          }

          size_t  nLength = pEnd - pStart;
          string  ClassName(pStart, 0, nLength);

          if (ClassName == pThisTopmostParent->type())
          {
            pThisTopmost  = pThisTopmostParent;
            pMatchTopmost = pMatchTopmostParent;
            break;
          }
        }
      }
      else
      {
        pThisTopmost  = pThisTopmostParent;
        pMatchTopmost = pMatchTopmostParent;
      }

      pThisTopmostParent  = pThisTopmostParent->parent();
      pMatchTopmostParent = pMatchTopmostParent->parent();

      bMatched            = true;
    }
  }

  return (bMatched);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findDescendantMatch(AdtParser* pMatchTo, AdtParser*& pNewMatchTo)
{
  AdtParser*  pMatch      = findObject(pMatchTo->type());
  AdtParser*  pOrigin     = this;

  pNewMatchTo = pMatchTo;

  if (pMatch != 0)
  {
    AdtParser*  pTest   = pMatch;
    AdtParser*  pTestTo = pMatchTo;

    while ((pTestTo != 0) && (pTest != 0) && (pOrigin != pTest))
    {
      if (pTest->listSize() > 1)
      {
        pMatch      = pTest;
        pNewMatchTo = pTestTo;
      }

      pTest   = pTest->parent();
      pTestTo = pTestTo->parent();
    }
  }

  return (pMatch);
}

//  ----------------------------------------------------------------------------

void AdtParser::printDescendants(AdtFile& rOutFile) const
{
  if (name().length() > 0)
  {
    write(rOutFile, name());
    write(rOutFile, " : ");
  }

  write(rOutFile, type());

  rOutFile.newline();

  if (descendantObjMap().size() > 0)
  {
    AdtSizeTByStringMapConstIter  Iter;

    rOutFile.incrementIndent();
    rOutFile.homeline();

    for (Iter = descendantObjMap().begin() ; Iter != descendantObjMap().end() ; ++Iter)
    {
      const string&   rAttribute  = (*Iter).first;
      AdtParser*      pDescendant = object(Iter);

      if (pDescendant != 0)
      {
        write(rOutFile, rAttribute);
        write(rOutFile, " -> ");
        pDescendant->printDescendants(rOutFile);
      }
    }

    rOutFile.decrementIndent();
    rOutFile.homeline();
  }

  if ((ObjList != 0) && (ObjList->size() > 0))
  {
    AdtParserPtrListConstIter Iter;

    write(rOutFile, "List contents");
    rOutFile.incrementIndent();
    rOutFile.newline();

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pDescendant = *Iter;

      if (pDescendant != 0)
      {
        write(rOutFile, " -> ");
        pDescendant->printDescendants(rOutFile);
      }
    }

    rOutFile.decrementIndent();
    rOutFile.homeline();
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::hasSubString(const char* pString,
                             const char* pSubString,
                             int& nStart,
                             int& nLength,
                             bool bMatchCase)
{
  bool bFound = false;

  if ((pString != 0) && (pSubString != 0))
  {
    const char* pChar       = pString;
    const char* pMatchChar  = pSubString;
    bool        bFoundStart = false;

    nStart = 0;

    while ((*pChar != 0) && (*pMatchChar != 0))
    {
      if (bMatchCase)
      {
        if (*pChar == *pMatchChar)
        {
          bFoundStart = true;
          break;
        }
      }
      else
      {
        if (toupper(*pChar) == toupper(*pMatchChar))
        {
          bFoundStart = true;
          break;
        }
      }

      pChar++;
      nStart++;
    }

    if (bFoundStart)
    {
      pChar++;
      pMatchChar++;

      bFound  = true;
      nLength = 1;

      while ((*pChar != 0) && (*pMatchChar != 0))
      {
        if (bMatchCase)
        {
          if (*pChar != *pMatchChar)
          {
            bFound  = false;
            nLength = 0;
            break;
          }
        }
        else
        {
          if (toupper(*pChar) != toupper(*pMatchChar))
          {
            bFound  = false;
            nLength = 0;
            break;
          }
        }

        pChar++;
        pMatchChar++;
        nLength++;
      }

      if (*pMatchChar != 0)
      {
        bFound = false;
      }
    }
    else
    {
      nStart = 0;
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

void AdtParser::findObjects(AdtParserPtrList& rList,
                            const char* pClassName,
                            const char* pObjectName,
                            bool bMatchCase,
                            const char* pParentClassName,
                            bool bAllowPartialNameMatch) const
{
  //Check for a match
  if (isType(pClassName))
  {
    bool bFound = true;

    if ((pParentClassName != 0) && (Parent != 0))
    {
      bFound = bFound && Parent->isType(pParentClassName);
    }

    if (pObjectName != 0)
    {
      if (bAllowPartialNameMatch)
      {
        int nStart  = 0;
        int nLength = 0;

        bFound = bFound && hasSubString(name(),
                                        pObjectName,
                                        nStart,
                                        nLength,
                                        bMatchCase);
      }
      else
      {
        if (bMatchCase)
        {
          bFound = bFound && (::strcmp(name(), pObjectName) == 0);
        }
        else
        {
          bFound = bFound && (::caseless_string_comparison(name(), pObjectName) == 0);
        }
      }
    }

    if (bFound)
    {
      AdtParser* pThis = (AdtParser*)this;

      rList.push_back(pThis);
    }
  }

  //Continue searching
  if (descendantObjMap().size() > 0)
  {
    AdtStringListConstIter  NameIter;

    // We indirect the access to the descendant objects as we want to insure that they
    // are scanned in the order defined. This ensures that if you a looking for the
    // first occurence of something in code you will find it.
    for (NameIter = descendantObjNameList().begin() ; NameIter != descendantObjNameList().end() ; ++NameIter)
    {
      const string& rName = *NameIter;

      AdtSizeTByStringMapConstIter  ObjIter = descendantObjMap().find(rName);

      if (ObjIter != descendantObjMap().end())
      {
        AdtParser*  pDescendant = object(ObjIter);

        if (pDescendant != 0)
        {
          pDescendant->findObjects(rList,
                                   pClassName,
                                   pObjectName,
                                   bMatchCase,
                                   pParentClassName,
                                   bAllowPartialNameMatch);
        }
      }
    }
  }

  //Continue searching
  if ((ObjList != 0) && (ObjList->size() > 0))
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pDescendant = *Iter;

      if (pDescendant != 0)
      {
        pDescendant->findObjects(rList,
                                 pClassName,
                                 pObjectName,
                                 bMatchCase,
                                 pParentClassName,
                                 bAllowPartialNameMatch);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findObject(const char* pClassName,
                                 const char* pObjectName,
                                 bool bMatchCase,
                                 const char* pParentClassName,
                                 bool bAllowPartialNameMatch) const
{
  bool        bFound  = false;
  AdtParser*  pObject = 0;

  //Check for a match
  if (isType(pClassName))
  {
    bFound = true;

    if ((pParentClassName != 0) && (Parent != 0))
    {
      bFound = bFound && Parent->isType(pParentClassName);
    }

    if (pObjectName != 0)
    {
      if (bAllowPartialNameMatch)
      {
        int nStart  = 0;
        int nLength = 0;

        bFound = bFound && hasSubString(name(),
                                        pObjectName,
                                        nStart,
                                        nLength,
                                        bMatchCase);
      }
      else
      {
        if (bMatchCase)
        {
          bFound = bFound && (::strcmp(name(), pObjectName) == 0);
        }
        else
        {
          bFound = bFound && (::caseless_string_comparison(name(), pObjectName) == 0);
        }
      }
    }

    if (bFound)
    {
      pObject = (AdtParser*)this;
    }
  }

  //Continue searching
  if (!bFound && (descendantObjMap().size() > 0))
  {
    AdtStringListConstIter  NameIter;

    // We indirect the access to the descendant objects as we want to insure that they
    // are scanned in the order defined. This ensures that if you a looking for the
    // first occurence of something in code you will find it.
    for (NameIter = descendantObjNameList().begin() ; NameIter != descendantObjNameList().end() ; ++NameIter)
    {
      const string& rName = *NameIter;

      AdtSizeTByStringMapConstIter  ObjIter = descendantObjMap().find(rName);

      if (ObjIter != descendantObjMap().end())
      {
        AdtParser*  pDescendant = object(ObjIter);

        if (pDescendant != 0)
        {
          pObject = pDescendant->findObject(pClassName,
                                            pObjectName,
                                            bMatchCase,
                                            pParentClassName,
                                            bAllowPartialNameMatch);

          if (pObject != 0)
          {
            bFound = true;
            break;
          }
        }
      }
    }
  }

  //Continue searching
  if (!bFound && (ObjList != 0) && (ObjList->size() > 0))
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pDescendant = *Iter;

      if (pDescendant != 0)
      {
        pObject = pDescendant->findObject(pClassName,
                                          pObjectName,
                                          bMatchCase,
                                          pParentClassName,
                                          bAllowPartialNameMatch);

        if (pObject != 0)
        {
          bFound = true;
          break;
        }
      }
    }
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findDescendant(const char* pDescendantPath) const
{
  AdtParser* pObject = 0;

  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  if (pDescendantPath != 0)
  {
    const char* pPathContext = pDescendantPath;

    pObject = findDescendantHelper(pPathContext, 0, 0, 0);
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findAscendantWithClassLineage(const char* pAscendantClassPath, AdtParser** ppSibling) const
{
  AdtParser* pObject = 0;

  //Comma seperated list of parent object classes to ascend.
  if (pAscendantClassPath != 0)
  {
    const char* pClassPathContext = pAscendantClassPath;

    pObject = findAscendantWithClassLineageHelper(pClassPathContext, ppSibling);
  }

  return (pObject);
}

//  ----------------------------------------------------------------------------

AdtParser* AdtParser::findAscendantWithClass(const char* pAscendantClass, AdtParser** ppSibling) const
{
  AdtParser* pParent  = parent();
  AdtParser* pSibling = (AdtParser*)this;

  for ( ; pParent != 0 ; pParent = pParent->parent())
  {
    if (pParent->isType(pAscendantClass))
    {
      if (ppSibling != 0)
      {
        *ppSibling = pSibling;
      }

      //Found match so end loop.
      break;
    }

    pSibling = pParent;
  }

  return (pParent);
}

//  ----------------------------------------------------------------------------

void AdtParser::listToMap(AdtParserPtrByStringMap& rMap, const AdtParserPtrList& rList) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if (pObj != 0)
    {
      rMap.insert(AdtParserPtrByStringMap::value_type(pObj->name(), *Iter));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::listToMap(AdtParserPtrByStringMultiMap& rMap, const AdtParserPtrList& rList) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if (pObj != 0)
    {
      rMap.insert(AdtParserPtrByStringMultiMap::value_type(pObj->name(), *Iter));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::listToMap(AdtParserPtrByStringMapCS& rMap, const AdtParserPtrList& rList) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if (pObj != 0)
    {
      rMap.insert(AdtParserPtrByStringMapCS::value_type(pObj->name(), *Iter));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::listToMap(AdtParserPtrByStringMultiMapCS& rMap, const AdtParserPtrList& rList) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser*  pObj = *Iter;

    if (pObj != 0)
    {
      rMap.insert(AdtParserPtrByStringMultiMapCS::value_type(pObj->name(), *Iter));
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMap& rMap) const
{
  AdtParserPtrByStringMapConstIter  Iter;

  for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
  {
    AdtParser*  pObj = (*Iter).second;

    if (pObj != 0)
    {
      rList.push_back(pObj);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMultiMap& rMap, const char* pKeyName) const
{
  AdtParserPtrByStringMultiMapConstIter Iter;

  if (pKeyName == 0)
  {
    for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
    {
      AdtParser*  pObj = (*Iter).second;

      if (pObj != 0)
      {
        rList.push_back(pObj);
      }
    }
  }
  else
  {
    AdtParserPtrByStringMultiMapConstIter EndIter = rMap.upper_bound(pKeyName);

    for (Iter = rMap.lower_bound(pKeyName) ; Iter != EndIter ; ++Iter)
    {
      AdtParser*  pObj = (*Iter).second;

      if (pObj != 0)
      {
        rList.push_back(pObj);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMapCS& rMap) const
{
  AdtParserPtrByStringMapCSConstIter  Iter;

  for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
  {
    AdtParser*  pObj = (*Iter).second;

    if (pObj != 0)
    {
      rList.push_back(pObj);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::mapToList(AdtParserPtrList& rList, const AdtParserPtrByStringMultiMapCS& rMap, const char* pKeyName) const
{
  AdtParserPtrByStringMultiMapCSConstIter Iter;

  if (pKeyName == 0)
  {
    for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
    {
      AdtParser*  pObj = (*Iter).second;

      if (pObj != 0)
      {
        rList.push_back(pObj);
      }
    }
  }
  else
  {
    AdtParserPtrByStringMultiMapCSConstIter EndIter = rMap.upper_bound(pKeyName);

    for (Iter = rMap.lower_bound(pKeyName) ; Iter != EndIter ; ++Iter)
    {
      AdtParser*  pObj = (*Iter).second;

      if (pObj != 0)
      {
        rList.push_back(pObj);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::objListToNameList(AdtStringList& rNameList, const AdtParserPtrList& rList)
{
  AdtParserPtrListConstIter Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    AdtParser* pObj = *Iter;

    if (pObj != 0)
    {
      rNameList.push_back(pObj->name());
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::nameListToNameMap(AdtStringByStringMap& rNameMap, const AdtStringList& rNameList, const char* pPrefix)
{
  if (rNameList.size() > 0)
  {
    AdtStringListConstIter  Iter;

    for (Iter = rNameList.begin() ; Iter != rNameList.end() ; ++Iter)
    {
      string  rName(*Iter);

      if (pPrefix != 0)
      {
        rName = pPrefix + rName;
      }

      rNameMap[rName] = rName;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendantList(AdtParserPtrList& rList, const char* pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  if (pDescendantPath != 0)
  {
    const char* pPathContext = pDescendantPath;

    while (*pPathContext != 0)
    {
      enumerateDescendant(rList, pPathContext);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendantMap(AdtParserPtrByStringMap& rMap, const char* pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  if (pDescendantPath != 0)
  {
    const char* pPathContext = pDescendantPath;

    while (*pPathContext != 0)
    {
      enumerateDescendant(rMap, pPathContext);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateDescendantMap(AdtParserPtrByStringMultiMap& rMap, const char* pDescendantPath) const
{
  //Typical search string. Comma seperated list of objects to descend and semi-
  //colon seperated multiple search paths.
  //
  //  "Program,Block,DeclSection,VarSection,VarDeclList;
  //      Library,Block,DeclSection,VarSection,VarDeclList;
  //      Unit,ImplementationSection,DeclSection,VarSection,VarDeclList;"
  //
  if (pDescendantPath != 0)
  {
    const char* pPathContext = pDescendantPath;

    while (*pPathContext != 0)
    {
      enumerateDescendant(rMap, pPathContext);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::enumerateAddByObjList(AdtParserPtrByStringMap& rMap, AdtParser* pObj) const
{
  if ((pObj != 0) && (ObjList != 0))
  {
    AdtParserPtrListConstIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj != 0)
      {
        enumerateAddObj(rMap, pObj, pListObj->name());
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::add(AdtParser* pObj, bool bAppend)
{
  bool bAdded = false;

  initList();

  if ((pObj != 0) && pObj->isType(this->listType()))
  {
    if (ObjList != 0)
    {
      if (bAppend)
      {
        ObjList->push_back(pObj);
      }
      else
      {
        ObjList->push_front(pObj);
      }

      pObj->parent(this);

      bAdded = true;
    }
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtParser::addListCopy(AdtParser* pObj, bool bAppend)
{
  bool bAdded = false;

  if ((pObj != 0) && (strcmp(pObj->listType(), this->listType()) == 0))
  {
    copyList(pObj->ObjList, bAppend);

    bAdded = true;
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtParser::insertBefore(const AdtParser* pObj, AdtParser* pInsertObj)
{
  bool bInserted = false;

  if ((ObjList != 0) && (pObj != 0) && (pInsertObj != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj == pObj)
      {
        ObjList->insert(Iter, pInsertObj);
        pInsertObj->parent(this);
        bInserted = true;
        break;
      }
      else
      {
        ++Iter;
      }
    }
  }

  return (bInserted);
}

//  ----------------------------------------------------------------------------

bool AdtParser::insertAfter(const AdtParser* pObj, AdtParser* pInsertObj)
{
  bool bInserted = false;

  if ((ObjList != 0) && (pObj != 0) && (pInsertObj != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj == pObj)
      {
        Iter++;

        if (Iter == ObjList->end())
        {
          ObjList->push_back(pInsertObj);
        }
        else
        {
          ObjList->insert(Iter, pInsertObj);
        }

        pInsertObj->parent(this);
        bInserted = true;
        break;
      }
      else
      {
        ++Iter;
      }
    }
  }

  return (bInserted);
}

//  ----------------------------------------------------------------------------

bool AdtParser::insertBefore(const AdtParser* pObj, const AdtParserPtrList& rObjList)
{
  bool bInserted = false;

  if ((ObjList != 0) && (pObj != 0) && (rObjList.size() > 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj == pObj)
      {
        AdtParserPtrListConstIter ObjIter;

        for (ObjIter = rObjList.begin() ; ObjIter != rObjList.end() ; ++ObjIter)
        {
          AdtParser*  pInsertObj = (AdtParser*)(const AdtParser*)*ObjIter;

          Iter = ObjList->insert(Iter, pInsertObj);
          pInsertObj->parent(this);
        }

        bInserted = true;
        break;
      }
      else
      {
        ++Iter;
      }
    }
  }

  return (bInserted);
}

//  ----------------------------------------------------------------------------

bool AdtParser::insertAfter(const AdtParser* pObj, const AdtParserPtrList& rObjList)
{
  bool bInserted = false;

  if ((ObjList != 0) && (pObj != 0) && (rObjList.size() > 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj == pObj)
      {
        Iter++;

        if (Iter == ObjList->end())
        {
          AdtParserPtrListConstIter ObjIter;

          for (ObjIter = rObjList.begin() ; ObjIter != rObjList.end() ; ++ObjIter)
          {
            AdtParser*  pInsertObj = (AdtParser*)(const AdtParser*)*ObjIter;

            ObjList->push_back(pInsertObj);
            pInsertObj->parent(this);
          }
        }
        else
        {
          AdtParserPtrListConstIter ObjIter;

          for (ObjIter = rObjList.begin() ; ObjIter != rObjList.end() ; ++ObjIter)
          {
            AdtParser*  pInsertObj = (AdtParser*)(const AdtParser*)*ObjIter;

            Iter = ObjList->insert(Iter, pInsertObj);
            pInsertObj->parent(this);
          }
        }

        bInserted = true;
        break;
      }
      else
      {
        ++Iter;
      }
    }
  }

  return (bInserted);
}

//  ----------------------------------------------------------------------------

void AdtParser::remove(const char* pObjName)
{
  if ((ObjList != 0) && (pObjName != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if ((pListObj != 0) && (pListObj->name() == pObjName))
      {
        Iter = ObjList->erase(Iter);
      }
      else
      {
        ++Iter;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::remove(AdtParser* pObj)
{
  if ((ObjList != 0) && (pObj != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj == pObj)
      {
        Iter = ObjList->erase(Iter);
      }
      else
      {
        ++Iter;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::removeMatching(const AdtParserPtrByStringMap& rMap, AdtParserPtrList* pRemovedList)
{
  if (ObjList != 0)
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if (pListObj != 0)
      {
        AdtParserPtrByStringMapConstIter  MapIter = rMap.find(pListObj->name());

        if (MapIter != rMap.end())
        {
          if (pRemovedList != 0)
          {
            pRemovedList->push_back(pListObj);
          }

          Iter = ObjList->erase(Iter);
        }
        else
        {
          ++Iter;
        }
      }
      else
      {
        ++Iter;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::removeAllExcept(const AdtParser* pObj)
{
  if ((ObjList != 0) && (pObj != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if ((pListObj != 0) && (pListObj == pObj))
      {
        ++Iter;
      }
      else
      {
        Iter = ObjList->erase(Iter);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtParser::removeAllExcept(const char* pObjName)
{
  if ((ObjList != 0) && (pObjName != 0))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; )
    {
      AdtParser*  pListObj = *Iter;

      if ((pListObj != 0) && (pListObj->name() == pObjName))
      {
        ++Iter;
      }
      else
      {
        Iter = ObjList->erase(Iter);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::replace(AdtParser* pObj, AdtParser* pListObj)
{
  bool bAdded = false;

  if ((pObj                 != 0) &&
      (pListObj             != 0) &&
      (pListObj->ObjList    != 0) &&
      (ObjList              != 0) &&
      (pListObj->listType() == this->listType()))
  {
    AdtParserPtrListIter Iter;

    for (Iter = ObjList->begin() ; Iter != ObjList->end() ; ++Iter)
    {
      AdtParser* pLocalObj = *Iter;

      //Find pObj
      if (pLocalObj == pObj)
      {
        //Insert list objects in front of pObj
        AdtParserPtrListIter InsertIter;

        for (InsertIter = pListObj->ObjList->begin() ; InsertIter != pListObj->ObjList->end() ; ++InsertIter)
        {
          AdtParser* pInsertObj = *InsertIter;

          if (pInsertObj != 0)
          {
            ObjList->insert(Iter, pInsertObj);

            pInsertObj->parent(this);
            pInsertObj->depth(depth() + 1, true);
          }
        }

        //Remove pObj
        ObjList->erase(Iter);
        bAdded = true;
        break;
      }
    }
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtParser::replaceInParent(AdtParser* pObj)
{
  bool bReplaced = false;

  this->lock();

  if (Parent != 0)
  {
    if (Parent->ObjList != 0)
    {
      //Search and replace on the List iter first. Note that we assume that an
      //object instance can only appear in the list once.
      AdtParserPtrListIter ListIter;

      for (ListIter = Parent->ObjList->begin() ; ListIter != Parent->ObjList->end() ; ++ListIter)
      {
        AdtParserContext& rContext = *ListIter;

        //Find this in parent
        if (rContext.object() == this)
        {
          rContext.object(pObj);

          if (pObj != 0)
          {
            pObj->parent(Parent, true, true);
          }
          else
          {
            // If we are nulling the pointer in a list context we need to remove the list item
            ListIter = Parent->ObjList->erase(ListIter);
          }

          bReplaced = true;
          break;
        }
      }
    }

    //Search and replace on the map iter next. Note that we assume that an
    //object instance can only appear in the map once.
    AdtSizeTByStringMapConstIter MapIter;

    for (MapIter = Parent->descendantObjMap().begin() ; MapIter != Parent->descendantObjMap().end() ; ++MapIter)
    {
      //Find and replace this in parent
      if (Parent->replaceObject(MapIter, pObj, this))
      {
        if (pObj != 0)
        {
          pObj->parent(Parent, true, true);
        }

        bReplaced = true;
        break;
      }
    }
  }

  UtlReleaseReference(this);

  return (bReplaced);
}

//  ----------------------------------------------------------------------------

void AdtParser::depth(int nDepth, bool bUpdateChildren)
{
  Depth = nDepth;

  if (bUpdateChildren)
  {
    updateDepth();
  }
}

//  ----------------------------------------------------------------------------

bool AdtParser::replaceObject(const AdtSizeTByStringMapConstIter& rIter,
                              AdtParser* pNewObj,
                              AdtParser* pIfOnlyEqualObj)
{
  bool        bReplaced = false;
  AdtParser** ppObject  = objectAddress(rIter);

  if (pIfOnlyEqualObj != 0)
  {
    if (*ppObject == pIfOnlyEqualObj)
    {
      *ppObject = pNewObj;

      if (pNewObj != 0)
      {
        pNewObj->lock();
      }

      UtlReleaseReference(pIfOnlyEqualObj);

      bReplaced = true;
    }
  }
  else
  {
    AdtParser* pOldObject;

    pOldObject  = *ppObject;
    *ppObject   = pNewObj;

    if (pNewObj != 0)
    {
      pNewObj->lock();
    }

    UtlReleaseReference(pOldObject);

    bReplaced = true;
  }

  return (bReplaced);
}

//  ----------------------------------------------------------------------------

AdtSourceFileType adtSourceFileTypeFromFile(const string& rSourceFile)
{
  AdtSourceFileType nSourceFileType = UnknownSourceFileType;

  UtlFilePath TestPath(rSourceFile);

  if ((TestPath.extension().eq(".h")  ) ||
      (TestPath.extension().eq(".hpp")))
  {
    nSourceFileType = CppHeaderFileType;
  }
  else if ((TestPath.extension().eq(".c")) ||
           (TestPath.extension().eq(".cpp")))
  {
    nSourceFileType = CppSourceFileType;
  }
  else if (TestPath.extension().eq(".pas"))
  {
    nSourceFileType = DelphiSourceFileType;
  }
  else if ((TestPath.extension().eq(".j"))    ||
           (TestPath.extension().eq(".jav"))  ||
           (TestPath.extension().eq(".java")))
  {
    nSourceFileType = JavaSourceFileType;
  }
  else if ((TestPath.extension().eq(".f"))    ||
           (TestPath.extension().eq(".for"))  ||
           (TestPath.extension().eq(".f90"))  ||
           (TestPath.extension().eq(".f95")))
  {
    nSourceFileType = FortranSourceFileType;
  }

  return (nSourceFileType);
}


//  ----------------------------------------------------------------------------
//  AdtSourceRoot method implementations
//  ----------------------------------------------------------------------------
AdtSourceRoot::AdtSourceRoot()
 : RegardAsClassFunctionMap(),
   RegardAsClassSubroutineMap(),
   ClassPrefixStack(),
   IncludeMap(),
   IsBlackBoxMap()
{

}

//  ----------------------------------------------------------------------------

AdtSourceRoot::AdtSourceRoot(const AdtSourceRoot& rCopy)
 : RegardAsClassFunctionMap(),
   RegardAsClassSubroutineMap(),
   ClassPrefixStack(),
   IncludeMap(),
   IsBlackBoxMap()
{

}

//  ----------------------------------------------------------------------------

AdtSourceRoot::~AdtSourceRoot()
{

}

//  ----------------------------------------------------------------------------

void AdtSourceRoot::addBlackBox(const AdtBlackBoxDefinition* pBlackBox,
                                AdtStringByStringMap& rRegardAsClassFunctionMap,
                                AdtStringByStringMap& rRegardAsClassSubroutineMap)
{
  if (pBlackBox != 0)
  {
    IsBlackBoxMap[pBlackBox->nativeName()] = 1;

    if (pBlackBox->isFunction())
    {
      rRegardAsClassFunctionMap[pBlackBox->baseName()] = pBlackBox->baseName();
    }
    else
    {
      rRegardAsClassSubroutineMap[pBlackBox->baseName()] = pBlackBox->baseName();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtSourceRoot::appendIsBlackBoxMap(AdtIntByStringMap& rIsBlackBoxMap) const
{
  for (AdtIntByStringMapConstIter Iter = IsBlackBoxMap.begin() ; Iter != IsBlackBoxMap.end() ; ++Iter)
  {
    rIsBlackBoxMap[Iter->first] = 1;
  }
}


//  ----------------------------------------------------------------------------
//  AdtSliceBuilder  method implementations
//  ----------------------------------------------------------------------------
bool AdtSliceBuilder::parseArrayArg(const char*& pChar,
                                    string& rVarName,
                                    AdtStringList& rIndexList) const
{
  string  sIndex;
  bool    bContinue = true;

  AdtParse::extractWord(rVarName, "( ", pChar, true);

  pChar     = AdtParse::nextWord(pChar);
  bContinue = AdtParse::matchWord(pChar, "(");

  rIndexList.clear();

  while (bContinue)
  {
    pChar = AdtParse::nextWord(pChar);

    AdtParse::bracketedExtractWord(sIndex, "),", "(",")", pChar, true);
    rIndexList.push_back(sIndex);
    AdtParse::matchWord(pChar, ",");

    bContinue = !AdtParse::matchWord(pChar, ")");
  }

  pChar = AdtParse::nextWord(pChar);

  return (rIndexList.size() > 0);
}

//  ----------------------------------------------------------------------------

bool AdtSliceBuilder::parseCountArg(const char*& pChar,
                                    AdtStringList& rCountList,
                                    string& rErrorString) const
{
  bool bParsed = true;

  // Parse count expression properly taking into consideration
  // the implied number of indices from the index list size. Need
  // to take into account *, (, ), +, - and sqr, pwr and power.
  while (*pChar != '\0')
  {
    pChar = AdtParse::nextWord(pChar);

    if (AdtParse::matchWord(pChar, "power", false) ||
        AdtParse::matchWord(pChar, "pwr", false))
    {
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, "(", false))
      {
        string sArg1;

        pChar = AdtParse::nextWord(pChar);

        if (AdtParse::bracketedExtractWord(sArg1, ",", "(",")", pChar, true))
        {
          pChar = AdtParse::nextWord(pChar);

          if (AdtParse::matchWord(pChar, ",", false))
          {
            string sArg2;

            pChar = AdtParse::nextWord(pChar);

            if (AdtParse::bracketedExtractWord(sArg2, ")", "(",")", pChar, true))
            {
              pChar = AdtParse::nextWord(pChar);

              int nCount = ::atoi(sArg2);

              if (nCount > 0)
              {
                for (int cn = 0 ; cn < nCount ; cn++)
                {
                  rCountList.push_back(sArg1);
                }
              }
              else
              {
                // Exponent must be integer constant
                rErrorString  = "Exponent must be integer constant in %s\n";
                bParsed       = false;
                break;
              }

              AdtParse::matchWord(pChar, ")", false);
            }
            else
            {
              // Missing exponent argument
              rErrorString  = "Missing exponent argument in %s\n";
              bParsed       = false;
              break;
            }
          }
        }
        else
        {
          // Missing base argument
          rErrorString  = "Missing base argument in %s\n";
          bParsed       = false;
          break;
        }
      }
      else
      {
        // Missing parenthesis
        rErrorString  = "Missing parenthesis in %s\n";
        bParsed       = false;
        break;
      }
    }
    else if (AdtParse::matchWord(pChar, "sqr", false))
    {
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, "(", false))
      {
        pChar = AdtParse::nextWord(pChar);

        string sArg;

        if (AdtParse::bracketedExtractWord(sArg, ")", "(",")", pChar, true))
        {
          pChar = AdtParse::nextWord(pChar);

          rCountList.push_back(sArg);
          rCountList.push_back(sArg);

          AdtParse::matchWord(pChar, ")", false);
        }
        else
        {
          // Missing closing bracket
          rErrorString  = "Missing closing bracket in %s\n";
          bParsed       = false;
          break;
        }
      }
      else
      {
        // Missing parenthesis
        rErrorString  = "Missing parenthesis in %s\n";
        bParsed       = false;
        break;
      }
    }
    else
    {
      string sIndex;

      AdtParse::matchWord(pChar, "(", false);

      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::bracketedExtractWord(sIndex, "*)", "(",")", pChar, true))
      {
        pChar = AdtParse::nextWord(pChar);

        rCountList.push_back(sIndex);

        if (AdtParse::matchWord(pChar, ")", false))
        {
          pChar = AdtParse::nextWord(pChar);
          break;
        }
        else
        {
          AdtParse::matchWord(pChar, "*", false);
          pChar = AdtParse::nextWord(pChar);
        }
      }
      else
      {
        // Missing argument
        rErrorString  = "Missing argument in %s\n";
        bParsed       = false;
        break;
      }
    }
  }

  return (bParsed);
}

//  ----------------------------------------------------------------------------

void AdtSliceBuilder::buildSliceExp(string& sCode,
                                    const string& rVarName,
                                    const AdtStringList& rCountList,
                                    const AdtStringList& rIndexList) const
{
  bool                    bFirst    = true;
  AdtStringListConstIter  CountIter = rCountList.begin();
  AdtStringListConstIter  DestIter  = rIndexList.begin();
  size_t                  nArgDiff  = rIndexList.size() - rCountList.size();

  sCode += rVarName + "(";

  for (size_t cn = 0 ; cn < nArgDiff ; cn++)
  {
    if (!bFirst)
    {
      sCode += ",";
    }
    else
    {
      bFirst = false;
    }

    sCode += (*DestIter);

    DestIter++;
  }

  for ( ; CountIter != rCountList.end() ; ++CountIter, ++DestIter)
  {
    if (!bFirst)
    {
      sCode += ",";
    }
    else
    {
      bFirst = false;
    }

    sCode += (*DestIter) + ":" + (*DestIter) + "+" + (*CountIter) + "-1";
  }

  sCode += ")";
}

//  ----------------------------------------------------------------------------

AdtSliceBuilder::AdtSliceBuilder()
 : ErrorString()
{

}

//  ----------------------------------------------------------------------------

AdtSliceBuilder::~AdtSliceBuilder()
{

}

//  ----------------------------------------------------------------------------

bool AdtSliceBuilder::convertZero(const char* pExpression, string& sCode)
{
  bool bConverted = false;

  ErrorString = "";

  if (pExpression != 0)
  {
    // Need to translate the ZERO expression in sBuffer to equivalent slice operation
    const char* pChar = pExpression;

    while (*pChar != '\0')
    {
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, "ZERO", false))
      {
        pChar = AdtParse::nextWord(pChar);
      }
      else if (AdtParse::matchWord(pChar, "("))
      {
        string        rDestVarName;
        AdtStringList rDestIndexList;

        pChar = AdtParse::nextWord(pChar);

        if (parseArrayArg(pChar, rDestVarName, rDestIndexList))
        {
          pChar = AdtParse::nextWord(pChar);

          if (AdtParse::matchWord(pChar, ","))
          {
            AdtStringList rCountList;

            pChar = AdtParse::nextWord(pChar);

            if (parseCountArg(pChar, rCountList, ErrorString))
            {
              size_t nArgDiff = rDestIndexList.size() - rCountList.size();

              pChar = AdtParse::nextWord(pChar);

              if (nArgDiff >= 0)
              {
                buildSliceExp(sCode,
                              rDestVarName,
                              rCountList,
                              rDestIndexList);

                sCode += " = 0";

                bConverted = true;
              }
              else
              {
                // Destination mis-match with array count
                ErrorString = "ZERO ERROR: Too few indices in destination argument in %s\nContext line %d in file %s\n";
              }
            }
            else
            {
              ErrorString = "ZERO ERROR: " + ErrorString + "\nContext line %d in file %s\n";
            }
            break;
          }
          else
          {
            // No count argument
            ErrorString = "ZERO ERROR: No count argument in %s\nContext line %d in file %s\n";
            break;
          }
        }
        else
        {
          // Invalid dest argument
          ErrorString = "ZERO ERROR: Invalid dest argument in %s\nContext line %d in file %s\n";
          break;
        }
      }
    }
  }

  return (bConverted);
}

//  ----------------------------------------------------------------------------

bool AdtSliceBuilder::convertXCopy(const char* pExpression, string& sCode)
{
  // Need to translate the XCOPY expression in pExpression to equivalent slice operation
  bool bConverted = false;

  if (pExpression != 0)
  {
    const char* pChar = pExpression;

    ErrorString = "";

    while (*pChar != '\0')
    {
      pChar = AdtParse::nextWord(pChar);

      if (AdtParse::matchWord(pChar, "XCOPY", false))
      {
        pChar = AdtParse::nextWord(pChar);
      }
      else if (AdtParse::matchWord(pChar, "("))
      {
        string        rSrcVarName;
        AdtStringList rSrcIndexList;

        pChar = AdtParse::nextWord(pChar);

        if (parseArrayArg(pChar, rSrcVarName, rSrcIndexList))
        {
          pChar = AdtParse::nextWord(pChar);

          if (AdtParse::matchWord(pChar, ","))
          {
            string        rDestVarName;
            AdtStringList rDestIndexList;

            pChar = AdtParse::nextWord(pChar);

            if (parseArrayArg(pChar, rDestVarName, rDestIndexList))
            {
              pChar = AdtParse::nextWord(pChar);

              if (AdtParse::matchWord(pChar, ","))
              {
                AdtStringList rCountList;

                pChar = AdtParse::nextWord(pChar);

                if (parseCountArg(pChar, rCountList, ErrorString))
                {
                  size_t nArgDiff = rDestIndexList.size() - rCountList.size();

                  pChar = AdtParse::nextWord(pChar);

                  if (nArgDiff >= 0)
                  {
                    buildSliceExp(sCode,
                                  rDestVarName,
                                  rCountList,
                                  rDestIndexList);

                    sCode += " = ";

                    nArgDiff = rSrcIndexList.size() - rCountList.size();

                    if (nArgDiff >= 0)
                    {
                      buildSliceExp(sCode,
                                    rSrcVarName,
                                    rCountList,
                                    rSrcIndexList);

                      bConverted = true;
                    }
                    else
                    {
                      // Src mis-match with array count
                      ErrorString = "XCOPY ERROR: Too few indices in source argument in %s\nContext line %d in file %s\n";
                    }
                  }
                  else
                  {
                    // Destination mis-match with array count
                    ErrorString = "XCOPY ERROR: Too few indices in destination argument in %s\nContext line %d in file %s\n";
                  }
                }
                else
                {
                  ErrorString = "XCOPY ERROR: " + ErrorString + "\nContext line %d in file %s\n";
                }

                break;
              }
              else
              {
                // No count argument
                ErrorString = "XCOPY ERROR: No count argument in %s\nContext line %d in file %s\n";
                break;
              }
            }
            else
            {
              // Invalid dest argument
              ErrorString = "XCOPY ERROR: Invalid dest argument in %s\nContext line %d in file %s\n";
              break;
            }
          }
          else
          {
            // No destination arg
            ErrorString = "XCOPY ERROR: No destination arg in %s\nContext line %d in file %s\n";
            break;
          }
        }
        else
        {
          // Invalid src argument
          ErrorString = "XCOPY ERROR: Invalid src argument in %s\nContext line %d in file %s\n";
          break;
        }
      }
    }
  }

  return (bConverted);
}

//  ----------------------------------------------------------------------------

void AdtSliceBuilder::reportError(const char* pExpression,
                                  int nLineNumber,
                                  const char* pFileName) const
{
  if ((pExpression != 0) && (pFileName != 0))
  {
    ::printf(ErrorString.c_str(), pExpression, nLineNumber, pFileName);
  }

  AdtExit(-1);
}
