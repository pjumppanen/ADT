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
//    adtblackbox.cpp
//
//  Purpose:
//    This file includes implementations of classes used to build black box
//    parse trees.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtblackbox.hpp"


//  ----------------------------------------------------------------------------

const char* adtBlackBox_AllocString(void* pContext, const char* pTokenText)
{
  const char* pString = 0;

  if (pContext != 0)
  {
    AdtBlackBoxCompiler* Context = (AdtBlackBoxCompiler*)pContext;

    pString = Context->allocString(pTokenText);
  }

  return (pString);
}

//  ----------------------------------------------------------------------------

void adtBlackBox_SetRoot(void* pObj)
{
  AdtBlackBoxBase::blackBoxRootObject(Obj(pObj));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxDerivativeList_create(void* pObj)
{
  return (Hnd(new AdtBlackBoxDerivativeList(ObjAndRelease(pObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxList_add(void* pList, void* pObj)
{
  AdtParser*  pObjList = Obj(pList);

  if (pObjList != 0)
  {
    pObjList->add(ObjAndRelease(pObj));
  }

  return (Hnd(pObjList));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxDerivative_create(const char* pIdentifier, void* pExprAdditiveObj, void* pExtendedListObj, void* pSpecListObj, int nIsExtended, int nIsNull, void* pBlackBoxDefObj)
{
  return (Hnd(new AdtBlackBoxDerivative(pIdentifier, ObjAndRelease(pExprAdditiveObj), ObjAndRelease(pExtendedListObj), ObjAndRelease(pSpecListObj), nIsExtended != 0, nIsNull != 0, ObjAndRelease(pBlackBoxDefObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxSpecList_create(void* pObj)
{
  return (Hnd(new AdtBlackBoxSpecList(ObjAndRelease(pObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxSpec_create(void* pIdentList, int nType)
{
  return (Hnd(new AdtBlackBoxSpec(ObjAndRelease(pIdentList), (AdtBlackBoxSpecType)nType), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxIdentList_create(void* pObj)
{
  return (Hnd(new AdtBlackBoxIdentList(ObjAndRelease(pObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxIdent_create(int nNumber)
{
  return (Hnd(new AdtBlackBoxIdent(nNumber), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxExprAdditive_create(void* pExprAdditiveObj, void* pExprMultiplicativeObj, int nIsPlus)
{
  return (Hnd(new AdtBlackBoxExprAdditive(ObjAndRelease(pExprAdditiveObj), ObjAndRelease(pExprMultiplicativeObj), nIsPlus != 0), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxExprMultiplicative_create(void* pExprMultiplicativeObj, void* pExprPowerObj, int nIsMultiply)
{
  return (Hnd(new AdtBlackBoxExprMultiplicative(ObjAndRelease(pExprMultiplicativeObj), ObjAndRelease(pExprPowerObj), nIsMultiply != 0), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxExprPower_create(void* pExprPowerObj, void* pExprUnaryObj)
{
  return (Hnd(new AdtBlackBoxExprPower(ObjAndRelease(pExprPowerObj), ObjAndRelease(pExprUnaryObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxExprUnary_create(void* pExprPostfixObj, int nHasOp, int nIsPlus)
{
  return (Hnd(new AdtBlackBoxExprUnary(ObjAndRelease(pExprPostfixObj), nHasOp != 0, nIsPlus != 0), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxExprPostfix_create(int nType, int nValue, double dValue, const char* pIdentifier, void* pArgListObj, void* pExprAdditiveObj)
{
  return (Hnd(new AdtBlackBoxExprPostfix((AdtBlackBoxPostfixType)nType, nValue, dValue, pIdentifier, ObjAndRelease(pArgListObj), ObjAndRelease(pExprAdditiveObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxArgList_create(void* pObj)
{
  return (Hnd(new AdtBlackBoxArgList(ObjAndRelease(pObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgType decodeArgType(bool& bIsArray, int nArgType)
{
  AdtBlackBoxArgType  nType = AdtBlackBox_undefined;

  bIsArray = false;

  switch (nArgType)
  {
    case 0:
    {
      nType = AdtBlackBox_real;
      break;
    }

    case 1:
    {
      nType = AdtBlackBox_integer;
      break;
    }

    case 2:
    {
      nType = AdtBlackBox_complex;
      break;
    }

    case 3:
    {
      nType = AdtBlackBox_character;
      break;
    }

    case 4:
    {
      nType = AdtBlackBox_boolean;
      break;
    }

    case 5:
    {
      nType    = AdtBlackBox_real;
      bIsArray = true;
      break;
    }

    case 6:
    {
      nType    = AdtBlackBox_integer;
      bIsArray = true;
      break;
    }

    case 7:
    {
      nType    = AdtBlackBox_complex;
      bIsArray = true;
      break;
    }

    case 8:
    {
      nType    = AdtBlackBox_character;
      bIsArray = true;
      break;
    }

    case 9:
    {
      nType    = AdtBlackBox_boolean;
      bIsArray = true;
      break;
    }

    default:
    {
      nType = AdtBlackBox_undefined;
      break;
    }
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxStandAloneDef_create(const char* pIdentifier, void* pArgDefListObj, int nArgType, void* pDerivativeListObj)
{
  bool                bIsArray  = false;
  AdtBlackBoxArgType  nType     = decodeArgType(bIsArray, nArgType);

  return (Hnd(new AdtBlackBoxStandAloneDef(pIdentifier, ObjAndRelease(pArgDefListObj), nType, bIsArray, ObjAndRelease(pDerivativeListObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxArgDef_create(const char* pIdentifier, int nArgType, int nDirType)
{
  bool                bIsArray  = false;
  AdtBlackBoxArgType  nType     = decodeArgType(bIsArray, nArgType);

  return (Hnd(new AdtBlackBoxArgDef(pIdentifier, (AdtBlackBoxArgType)nType, bIsArray, (AdtAutoDir)nDirType), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}

//  ----------------------------------------------------------------------------

void* adtBlackBoxArgDefList_create(void* pObj)
{
  return (Hnd(new AdtBlackBoxArgDefList(ObjAndRelease(pObj)), yyBlackBox_lineNumber(), yyBlackBox_fileName()));
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxDefinition::AdtBlackBoxInfo method implementations
//  ----------------------------------------------------------------------------
void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeSeperator(AdtFile& rOutFile) const
{
  rOutFile.write(", ");
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::appendArg(string& rString, bool& bWithSeperator) const
{
  if (Parameter > 0)
  {
    if (bWithSeperator)
    {
      rString += ", ";
    }

    rString += "metavar " + Name;

    bWithSeperator = true;
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeShape(AdtFile& rOutFile, bool bWithSeperator) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  if (Parameter > 0)
  {
    char sBuffer[32] = {0};

    ::sprintf(sBuffer, "param %zd", Parameter);
    rOutFile.write(sBuffer);
  }
  else
  {
    rOutFile.write("result");
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeType(AdtFile& rOutFile, bool bWithSeperator, double dTapenadeVersion) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  if (dTapenadeVersion > 3.12)
  {
    switch (Type)
    {
      case AdtBlackBox_real:
      {
        rOutFile.write(IsArray ? "arrayType(float(), dimColons())" : "float()");
        break;
      }

      case AdtBlackBox_integer:
      {
        rOutFile.write(IsArray ? "arrayType(integer(), dimColons())" : "integer()");
        break;
      }

      case AdtBlackBox_complex:
      {
        rOutFile.write(IsArray ? "arrayType(complex(), dimColons())" : "complex()");
        break;
      }

      case AdtBlackBox_character:
      {
        rOutFile.write(IsArray ? "arrayType(character(), dimColons())" : "character()");
        break;
      }

      case AdtBlackBox_boolean:
      {
        rOutFile.write(IsArray ? "arrayType(boolean(), dimColons())" : "boolean()");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }
  else
  {
    switch (Type)
    {
      case AdtBlackBox_real:
      {
        rOutFile.write(IsArray ? "arrayType(metavar real, dimColons())" : "ident real");
        break;
      }

      case AdtBlackBox_integer:
      {
        rOutFile.write(IsArray ? "arrayType(metavar integer, dimColons())" : "ident integer");
        break;
      }

      case AdtBlackBox_complex:
      {
        rOutFile.write(IsArray ? "arrayType(metavar complex, dimColons())" : "ident complex");
        break;
      }

      case AdtBlackBox_character:
      {
        rOutFile.write(IsArray ? "arrayType(metavar character, dimColons())" : "ident character");
        break;
      }

      case AdtBlackBox_boolean:
      {
        rOutFile.write(IsArray ? "arrayType(metavar boolean, dimColons())" : "ident boolean");
        break;
      }

      default:
      {
        FAIL();
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeReadNotWritten(AdtFile& rOutFile, bool bWithSeperator) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  rOutFile.write(ReadNotWritten ? "1" : "0");
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeNotReadThenWritten(AdtFile& rOutFile, bool bWithSeperator) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  rOutFile.write(NotReadThenWritten ? "1" : "0");
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeNotReadNotWritten(AdtFile& rOutFile, bool bWithSeperator) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  rOutFile.write(NotReadNotWritten ? "1" : "0");
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::AdtBlackBoxInfo::writeReadThenWritten(AdtFile& rOutFile, bool bWithSeperator) const
{
  if (bWithSeperator)
  {
    writeSeperator(rOutFile);
  }

  rOutFile.write(ReadThenWritten ? "1" : "0");
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxDefinition method implementations
//  ----------------------------------------------------------------------------
void AdtBlackBoxDefinition::translateName(const char* pName)
{
  string      sWord;
  const char* pPrefixEnd;
  const char* pChar = pName;

  Name        = "";
  NativeName  = pName;
  pPrefixEnd  = strrchr(pName, '.');

  if (pPrefixEnd == 0)
  {
    pPrefixEnd  = strrchr(pName, ':');
  }

  if (pPrefixEnd == 0)
  {
    BaseName = pName;
  }
  else
  {
    pPrefixEnd++;

    BaseName = pPrefixEnd;
  }

  // replace scoping operator with double underscore.
  while (AdtParse::extractWord(sWord, ":.", pChar, true))
  {
    Name += sWord + "__";

    if (*pChar == ':')
    {
      pChar += 2;
    }
    else
    {
      pChar++;
    }
  }

  Name += pChar;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::AdtBlackBoxDefinition(const char* pName, bool bIsFunction, const char* pFileName, int nLineNumber)
 : Name(),
   BaseName(),
   NativeName(),
   FileName(),
   NameMap(),
   TypeList(),
   ReadNotWrittenValues(),
   NotReadThenWrittenValues(),
   NotReadNotWrittenValues(),
   ReadThenWrittenValues(),
   DepsValues(),
   DerivativeSpecification()
{
  if (pFileName != 0)
  {
    FileName = pFileName;
  }

  LineNumber = nLineNumber;
  IsFunction = bIsFunction;

  translateName(pName);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::AdtBlackBoxDefinition(const AdtBlackBoxDefinition& rCopy)
: Name(rCopy.Name),
  BaseName(rCopy.BaseName),
  NativeName(rCopy.NativeName),
  FileName(rCopy.FileName),
  NameMap(rCopy.NameMap),
  TypeList(rCopy.TypeList),
  ReadNotWrittenValues(rCopy.ReadNotWrittenValues),
  NotReadThenWrittenValues(rCopy.NotReadThenWrittenValues),
  NotReadNotWrittenValues(rCopy.NotReadNotWrittenValues),
  ReadThenWrittenValues(rCopy.ReadThenWrittenValues),
  DepsValues(rCopy.DepsValues),
  DerivativeSpecification(rCopy.DerivativeSpecification)
{
  LineNumber = rCopy.LineNumber;
  IsFunction = rCopy.IsFunction;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::~AdtBlackBoxDefinition()
{
  TypeList.clear();
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::addArgument(AdtBlackBoxArgType nType,
                                        const char* pName,
                                        bool bReadNotWritten,
                                        bool bNotReadThenWritten,
                                        bool bNotReadNotWritten,
                                        bool bReadThenWritten,
                                        bool bIsArray)
{
  size_t nParameter = TypeList.size() + 1;

  NameMap[pName] = 1;

  TypeList.push_back(AdtBlackBoxInfo(nParameter,
                                     nType,
                                     pName,
                                     bReadNotWritten,
                                     bNotReadThenWritten,
                                     bNotReadNotWritten,
                                     bReadThenWritten,
                                     bIsArray));
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::addReturn(AdtBlackBoxArgType nType,
                                      bool bIsArray)
{
  TypeList.push_back(AdtBlackBoxInfo(0,
                                     nType,
                                     0,
                                     false,
                                     true,
                                     false,
                                     false,
                                     bIsArray));
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::writeDefinition(AdtFile& rOutFile, double dTapenadeVersion) const
{
  bool                        bWithSeperator;
  AdtBlackBoxInfoConstIter    Iter;
  string                      lcName(Name);

  // Need to do this because of a bug in Tapenade that assumes all lowercase names
  lcName.toLower();

  rOutFile.write(IsFunction ? "function " : "subroutine ");
  rOutFile.write(lcName);
  rOutFile.write(":");
  rOutFile.incrementIndent();
  rOutFile.newline();
  rOutFile.write("external:");
  rOutFile.newline();

  // Write shape spec
  rOutFile.write("shape: (");

  bWithSeperator = false;

  for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
  {
    Iter->writeShape(rOutFile, bWithSeperator);
    bWithSeperator = true;
  }

  rOutFile.write(")");
  rOutFile.newline();

  // Write type spec
  rOutFile.write("type: (");

  bWithSeperator = false;

  for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
  {
    Iter->writeType(rOutFile, bWithSeperator, dTapenadeVersion);
    bWithSeperator = true;
  }

  rOutFile.write(")");
  rOutFile.newline();

  // Write ReadNotWritten spec
  rOutFile.write("ReadNotWritten: (");

  if (ReadNotWrittenValues.length() > 0)
  {
    rOutFile.write(ReadNotWrittenValues);
  }
  else
  {
    bWithSeperator = false;

    for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
    {
      Iter->writeReadNotWritten(rOutFile, bWithSeperator);
      bWithSeperator = true;
    }
  }

  rOutFile.write(")");
  rOutFile.newline();

  // Write NotReadThenWritten spec
  rOutFile.write("NotReadThenWritten: (");

  if (NotReadThenWrittenValues.length() > 0)
  {
    rOutFile.write(NotReadThenWrittenValues);
  }
  else
  {
    bWithSeperator = false;

    for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
    {
      Iter->writeNotReadThenWritten(rOutFile, bWithSeperator);
      bWithSeperator = true;
    }
  }

  rOutFile.write(")");
  rOutFile.newline();

  // Write NotReadNotWritten spec
  rOutFile.write("NotReadNotWritten: (");

  if (NotReadNotWrittenValues.length() > 0)
  {
    rOutFile.write(NotReadNotWrittenValues);
  }
  else
  {
    bWithSeperator = false;

    for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
    {
      Iter->writeNotReadNotWritten(rOutFile, bWithSeperator);
      bWithSeperator = true;
    }
  }

  rOutFile.write(")");
  rOutFile.newline();

  // Write ReadThenWritten spec
  rOutFile.write("ReadThenWritten: (");

  if (ReadThenWrittenValues.length() > 0)
  {
    rOutFile.write(ReadThenWrittenValues);
  }
  else
  {
    bWithSeperator = false;

    for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
    {
      Iter->writeReadThenWritten(rOutFile, bWithSeperator);
      bWithSeperator = true;
    }
  }

  rOutFile.write(")");
  rOutFile.newline();

  //Write deps entry if there is one
  if (DepsValues.length() > 0)
  {
    rOutFile.write("deps: (");
    rOutFile.write(DepsValues);
    rOutFile.write(")");
    rOutFile.newline();
  }

  //Write derivative entry if there is one
  if (DerivativeSpecification.length() > 0)
  {
    rOutFile.write("derivative:");
    rOutFile.incrementIndent();
    rOutFile.newline();
    rOutFile.write(DerivativeSpecification);
    rOutFile.decrementIndent();
    rOutFile.newline();
  }

  rOutFile.decrementIndent();
  rOutFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDefinition::appendCallPart(string& rDerivativeSpec, double dTapenadeVersion) const
{
  bool                        bWithSeperator;
  AdtBlackBoxInfoConstIter    Iter;
  string                      lcName(Name);

  // Need to do this because of a bug in Tapenade that assumes all lowercase names
  lcName.toLower();

  if (dTapenadeVersion > 3.12)
  {
    rDerivativeSpec += "call(none(), ident " + lcName + ", expressions(";
  }
  else
  {
    rDerivativeSpec += "call(ident " + lcName + ", expressions(";
  }

  bWithSeperator = false;

  for (Iter = TypeList.begin() ; Iter != TypeList.end() ; ++Iter)
  {
    Iter->appendArg(rDerivativeSpec, bWithSeperator);
  }

  rDerivativeSpec += "))";
}

//  ----------------------------------------------------------------------------

bool AdtBlackBoxDefinition::hasArgument(const char* pName) const
{
  bool bHasArgument = false;

  if (pName != 0)
  {
    bHasArgument = (NameMap.find(pName) != NameMap.end());
  }

  return (bHasArgument);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::AdtBlackBoxInfo::AdtBlackBoxInfo(size_t nParameter,
                                                        AdtBlackBoxArgType nType,
                                                        const char* pName,
                                                        bool bReadNotWritten,
                                                        bool bNotReadThenWritten,
                                                        bool bNotReadNotWritten,
                                                        bool bReadThenWritten,
                                                        bool bIsArray)
 : Name()
{
  if (pName != 0)
  {
    Name = pName;
  }

  Parameter           = nParameter;
  Type                = nType;
  ReadNotWritten      = bReadNotWritten;
  NotReadThenWritten  = bNotReadThenWritten;
  NotReadNotWritten   = bNotReadNotWritten;
  ReadThenWritten     = bReadThenWritten;
  IsArray             = bIsArray;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::AdtBlackBoxInfo::AdtBlackBoxInfo(const AdtBlackBoxInfo& rCopy)
 : Name(rCopy.Name)
{
  Parameter           = rCopy.Parameter;
  Type                = rCopy.Type;
  ReadNotWritten      = rCopy.ReadNotWritten;
  NotReadThenWritten  = rCopy.NotReadThenWritten;
  NotReadNotWritten   = rCopy.NotReadNotWritten;
  ReadThenWritten     = rCopy.ReadThenWritten;
  IsArray             = rCopy.IsArray;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDefinition::AdtBlackBoxInfo& AdtBlackBoxDefinition::AdtBlackBoxInfo::operator = (const AdtBlackBoxInfo& rCopy)
{
  Name                = rCopy.Name;
  Parameter           = rCopy.Parameter;
  Type                = rCopy.Type;
  ReadNotWritten      = rCopy.ReadNotWritten;
  NotReadThenWritten  = rCopy.NotReadThenWritten;
  NotReadNotWritten   = rCopy.NotReadNotWritten;
  ReadThenWritten     = rCopy.ReadThenWritten;
  IsArray             = rCopy.IsArray;

  return (*this);
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxCompiler method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxCompiler::AdtBlackBoxCompiler()
 : AdtCommon(),
   ErrorMsg(),
   ErrorContext()
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxCompiler::~AdtBlackBoxCompiler()
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivativeList* AdtBlackBoxCompiler::compileFile(const char* pBlackBoxFile)
{
  AdtBlackBoxDerivativeList* pBlackBox = 0;

  if (pBlackBoxFile != 0)
  {
    ErrorMsg      = "";
    ErrorContext  = "";
    yyBlackBoxin  = ::fopen(pBlackBoxFile, "rt");

    if (yyBlackBoxin != 0)
    {
      int nBLACKBOXDEF = 1;

      adtBlackBox_pContext  = (void*)this;
//      yyBlackBoxdebug       = 1;
      yyBlackBoxdebug       = 0;
      yyBlackBoxIsFile      = 1;

      yyBlackBox_resetLineNumber(pBlackBoxFile);
      yyBlackBoxrestart(yyBlackBoxin);
      yyBlackBox_pushState(nBLACKBOXDEF);
      yyBlackBoxparse();
      yyBlackBox_popState();
      yyBlackBox_endParse();

      adtBlackBox_pContext  = 0;
      yyBlackBoxdebug       = 0;

      if (yyBlackBox_error() == 0)
      {
        pBlackBox = AdtBlackBoxBase::blackBoxRootObject();

        if (pBlackBox != 0)
        {
          pBlackBox->lock();
        }
      }

      AdtBlackBoxBase::blackBoxRootObject(0);
      yyBlackBox_releaseBuffer();
      fclose(yyBlackBoxin);

      yyBlackBoxin = 0;
    }
  }

  return (pBlackBox);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivativeList* AdtBlackBoxCompiler::compileText(const char* pBlackBoxText)
{
  AdtBlackBoxDerivativeList* pBlackBox = 0;

  if (pBlackBoxText != 0)
  {
    string  rFileName;

    ErrorMsg      = "";
    ErrorContext  = "";

    if (beginParseString(yyBlackBoxin, rFileName, pBlackBoxText))
    {
      adtBlackBox_pContext  = (void*)this;
//      yyBlackBoxdebug       = 1;
      yyBlackBoxdebug       = 0;
      yyBlackBoxIsFile      = 0;

      yyBlackBox_resetLineNumber(0);
      yyBlackBoxrestart(yyBlackBoxin);
      yyBlackBoxparse();
      yyBlackBox_endParse();

      adtBlackBox_pContext  = 0;
      yyBlackBoxdebug       = 0;

      if (yyBlackBox_error() == 0)
      {
        pBlackBox = AdtBlackBoxBase::blackBoxRootObject();

        if (pBlackBox != 0)
        {
          pBlackBox->lock();
        }
      }
      else
      {
        ErrorMsg      = yyBlackBox_errorMsg();
        ErrorContext  = pBlackBoxText;
      }

      AdtBlackBoxBase::blackBoxRootObject(0);
      yyBlackBox_releaseBuffer();
      endParseString(yyBlackBoxin, rFileName);
    }
  }

  return (pBlackBox);
}

//  ----------------------------------------------------------------------------

bool AdtBlackBoxCompiler::isBlackBox(const char* pComments)
{
  // Does the comment line look like a black box definition?
  bool bIsBlackBox = (pComments != 0) && ((::strstr(pComments, "BLACKBOX") != 0) || (::strstr(pComments, "D/D") != 0));

  return (bIsBlackBox);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxCompiler::parseComments(AdtBlackBoxDefinition& rDefaultDef,
                                        const char* pComments,
                                        const char* pFile,
                                        int nLine,
                                        double dTapenadeVersion)
{
  if (AdtBlackBoxCompiler::isBlackBox(pComments))
  {
    AdtBlackBoxCompiler         Compiler;
    AdtBlackBoxDerivativeList*  pRoot;
    int                         nBlackBoxCount    = 0;
    int                         nDerivativeCount  = 0;

    pRoot = Compiler.compileText(pComments);

    if (pRoot != 0)
    {
      // Build Tapenade ready black box definition and check the following
      // while doing so:
      //
      // (1) We should only have one function or subroutine black box definition.
      //     If more then it is an error.
      //
      // (2) If derivatives are specified we need to check that the dependent and
      //     independent variables exist in the function definition.
      //
      // (3) If BLACKBOX is specified without a spec list then we need to determine
      //     a 'default' spec list for the function based on the formal parameters.
      //
      // (4) If BLACKBOX is specified with a spec list then we need to check that
      //     it is consistent with the functions formal parameters.
      string  sDerivativeText;

      pRoot->updateBlackBoxDef(rDefaultDef,
                               sDerivativeText,
                               nBlackBoxCount,
                               nDerivativeCount,
                               pFile,
                               nLine,
                               dTapenadeVersion);

      rDefaultDef.derivativeSpecification(sDerivativeText);
    }
    else
    {
      ::printf("ERROR: Syntax error in the black box definition on line %d in file %s.\n  %s",
               nLine,
               pFile,
               Compiler.ErrorMsg.c_str());

      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

bool AdtBlackBoxCompiler::makeBlackBoxFile(const char* pSrcDefinitionsFile,
                                           const char* pDestBlackBoxFile,
                                           AdtIntByStringMap& rIsBlackBoxMap,
                                           bool bAppend,
                                           double dTapenadeVersion)
{
  bool bMade = false;

  if ((pSrcDefinitionsFile != 0) && (pDestBlackBoxFile != 0))
  {
    AdtBlackBoxCompiler         Compiler;
    AdtBlackBoxDerivativeList*  pRoot;

    pRoot = Compiler.compileFile(pSrcDefinitionsFile);

    if (pRoot != 0)
    {
      AdtFile     BlackBoxFile;
      const char* pMode = bAppend ? "at" : "wt";

      if (BlackBoxFile.open(pDestBlackBoxFile, pMode))
      {
        // process all AdtBlackBoxStandAloneDef objects
        AdtParserPtrListConstIter Iter;

        for (Iter = pRoot->objList().begin() ; Iter != pRoot->objList().end() ; ++Iter)
        {
          AdtBlackBoxDerivative*  pObj = (AdtBlackBoxDerivative*)Iter->object();

          if ((pObj != 0) && (pObj->blackBoxDef() != 0))
          {
            AdtBlackBoxStandAloneDef* pStandAloneDef = pObj->blackBoxDef();

            pStandAloneDef->writeBlackBoxDefinition(BlackBoxFile, rIsBlackBoxMap, dTapenadeVersion);

            bMade = true;
          }
        }

        BlackBoxFile.close();

        if (!bMade)
        {
          ::unlink(pDestBlackBoxFile);
        }
      }

      UtlReleaseReference(pRoot);
    }
  }

  return (bMade);
}


AdtBlackBoxDerivativeList*  AdtBlackBoxBase::BlackBoxRootObject = 0;

//  ----------------------------------------------------------------------------
//  AdtBlackBoxBase method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxBase::AdtBlackBoxBase()
 : AdtParser()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtBlackBoxBase::AdtBlackBoxBase(const AdtBlackBoxBase& rCopy)
 : AdtParser(rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtBlackBoxBase::~AdtBlackBoxBase()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxBase::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                      string& rDerivativeText,
                                      const char* pFile,
                                      int nLine,
                                      double dTapenadeVersion) const
{
  bool                      bWithSeperator = false;
  AdtParserPtrListConstIter Iter;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    const AdtBlackBoxBase*  pObj = (AdtBlackBoxBase*)(AdtParser*)*Iter;

    if (pObj != 0)
    {
      if (bWithSeperator)
      {
        rDerivativeText += ", ";
      }

      pObj->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

      bWithSeperator = true;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxBase::updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                        string& rDerivativeText,
                                        int& nBlackBoxCount,
                                        int& nDerivativeCount,
                                        const char* pFile,
                                        int nLine,
                                        double dTapenadeVersion) const
{
  AdtParserPtrListConstIter Iter;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    const AdtBlackBoxBase*  pObj = (AdtBlackBoxBase*)(AdtParser*)*Iter;

    if (pObj != 0)
    {
      pObj->updateBlackBoxDef(rDefaultDef,
                              rDerivativeText,
                              nBlackBoxCount,
                              nDerivativeCount,
                              pFile,
                              nLine,
                              dTapenadeVersion);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxBase::blackBoxRootObject(AdtParser* pRoot)
{
  UtlReleaseReference(BlackBoxRootObject);

  BlackBoxRootObject = 0;

  if (pRoot != 0)
  {
    if (pRoot->isType("AdtBlackBoxDerivativeList"))
    {
      BlackBoxRootObject = (AdtBlackBoxDerivativeList*)pRoot;
      BlackBoxRootObject->lock();
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivativeList* AdtBlackBoxBase::blackBoxRootObject()
{
  return (BlackBoxRootObject);
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxBase, AdtParser);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxDerivative method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxDerivative::AdtBlackBoxDerivative(const char* pIdentifier,
                                             AdtParser* pExprAdditiveObj,
                                             AdtParser* pExtendedListObj,
                                             AdtParser* pSpecListObj,
                                             bool bIsExtended,
                                             bool bIsNull,
                                             AdtParser* pBlackBoxDefObj)
 : AdtBlackBoxBase(),
   Identifier()
{
  if (pIdentifier != 0)
  {
    Identifier = pIdentifier;
  }

  IsExtended  = bIsExtended;
  IsNull      = bIsNull;

  initObject(ExprAdditive,            pExprAdditiveObj, AdtBlackBoxExprAdditive,    true);
  initObject(DerivativeExtendedList,  pExtendedListObj, AdtBlackBoxDerivativeList,  true);
  initObject(SpecList,                pSpecListObj,     AdtBlackBoxSpecList,        true);
  initObject(BlackBoxDef,             pBlackBoxDefObj,  AdtBlackBoxStandAloneDef,   true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivative::AdtBlackBoxDerivative(const AdtBlackBoxDerivative& rCopy)
 : AdtBlackBoxBase(rCopy),
   Identifier(rCopy.Identifier)
{
  IsExtended  = rCopy.IsExtended;
  IsNull      = rCopy.IsNull;

  copyObject(ExprAdditive,            rCopy, AdtBlackBoxExprAdditive);
  copyObject(DerivativeExtendedList,  rCopy, AdtBlackBoxDerivativeList);
  copyObject(SpecList,                rCopy, AdtBlackBoxSpecList);
  copyObject(BlackBoxDef,             rCopy, AdtBlackBoxStandAloneDef);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivative::~AdtBlackBoxDerivative()
{
  UtlReleaseReference(ExprAdditive);
  UtlReleaseReference(DerivativeExtendedList);
  UtlReleaseReference(SpecList);
  UtlReleaseReference(BlackBoxDef);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDerivative::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                            string& rDerivativeText,
                                            const char* pFile,
                                            int nLine,
                                            double dTapenadeVersion) const
{
  if (!IsExtended)
  {
    rDerivativeText += "binary(";

    rDefaultDef.appendCallPart(rDerivativeText, dTapenadeVersion);
  }

  if (isDerivativeNull())
  {
    rDerivativeText += ", none(), expressions()";
  }
  else if (isDerivativeComplete())
  {
    string  lcIdentifier(Identifier);

    // Need to do this because of a bug in Tapenade that assumes all lowercase names
    lcIdentifier.toLower();

    if (IsExtended)
    {
      rDerivativeText += "binary(metavar " + lcIdentifier + ", none(), ";

      ExprAdditive->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

      rDerivativeText += ")";
    }
    else
    {
      rDerivativeText += ", none(), expressions(binary(metavar " + lcIdentifier + ", none(), ";

      ExprAdditive->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

      rDerivativeText += "))";
    }
  }
  else if (isDerivativeMultipart())
  {
    rDerivativeText += ", ";

    ExprAdditive->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ", expressions(";

    DerivativeExtendedList->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ")";
  }
  else
  {
    FAIL();
  }

  if (!IsExtended)
  {
    rDerivativeText += ")";
  }
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDerivative::updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                              string& rDerivativeText,
                                              int& nBlackBoxCount,
                                              int& nDerivativeCount,
                                              const char* pFile,
                                              int nLine,
                                              double dTapenadeVersion) const
{
  if (isDerivativeMultipart())
  {
    if (nDerivativeCount > 1)
    {
      ::printf("ERROR: Too many derivatives in the black box definition on line %d in file %s.\n",
               nLine,
               pFile);

      AdtExit(-1);
    }

    buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
  }
  else if (isDerivativeNull())
  {
    nDerivativeCount++;

    if (nDerivativeCount > 1)
    {
      ::printf("ERROR: Too many derivatives in the black box definition on line %d in file %s.\n",
               nLine,
               pFile);

      AdtExit(-1);
    }

    buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
  }
  else if (isDerivativeComplete())
  {
    nDerivativeCount++;

    if (IsExtended)
    {
      if (nDerivativeCount != 1)
      {
        ::printf("ERROR: Partial derivatives must appear after the common derivative term in the black box definition on line %d in file %s.\n",
                 nLine,
                 pFile);

        AdtExit(-1);
      }
    }
    else
    {
      if (nDerivativeCount > 1)
      {
        ::printf("ERROR: Too many derivatives in the black box definition on line %d in file %s.\n",
                 nLine,
                 pFile);

        AdtExit(-1);
      }

      buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
    }

    if (!rDefaultDef.hasArgument(Identifier))
    {
      ::printf("ERROR: variable %s in the black box definition not part of the function on line %d in file %s.\n",
               Identifier.c_str(),
               nLine,
               pFile);

      AdtExit(-1);
    }
  }

  if (isBlackBox())
  {
    nBlackBoxCount++;

    if (nBlackBoxCount > 1)
    {
      ::printf("ERROR: Too many black box definitions on line %d in file %s.\n",
               nLine,
               pFile);

      AdtExit(-1);
    }

    if (SpecList != 0)
    {
      SpecList->updateBlackBoxDef(rDefaultDef,
                                  rDerivativeText,
                                  nBlackBoxCount,
                                  nDerivativeCount,
                                  pFile,
                                  nLine,
                                  dTapenadeVersion);
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxDerivative, AdtBlackBoxBase);



//  ----------------------------------------------------------------------------
//  AdtBlackBoxDerivativeList method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxDerivativeList::AdtBlackBoxDerivativeList(AdtParser* pBlackBoxDerivativeObj)
 : AdtBlackBoxBase()
{
  add(pBlackBoxDerivativeObj);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivativeList::AdtBlackBoxDerivativeList(const AdtBlackBoxDerivativeList& rCopy)
 : AdtBlackBoxBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxDerivativeList::~AdtBlackBoxDerivativeList()
{

}

//  ----------------------------------------------------------------------------

void AdtBlackBoxDerivativeList::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                string& rDerivativeText,
                                                const char* pFile,
                                                int nLine,
                                                double dTapenadeVersion) const
{
  AdtParserPtrListConstIter Iter;
  bool                      bAddSeperator = false;

  for (Iter = objList().begin() ; Iter != objList().end() ; ++Iter)
  {
    const AdtBlackBoxDerivative*  pObj = (AdtBlackBoxDerivative*)(AdtParser*)*Iter;

    if ((pObj != 0) && pObj->isDerivative())
    {
      if (bAddSeperator)
      {
        rDerivativeText += ", ";
      }

      bAddSeperator = true;

      pObj->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxDerivativeList, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprAdditive method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxExprAdditive::AdtBlackBoxExprAdditive(AdtParser* pExprAdditive,
                                                 AdtParser* pExprMultiplicative,
                                                 bool bIsPlus)
 : AdtBlackBoxBase()
{
  IsPlus = bIsPlus;

  initObject(ExprAdditive,        pExprAdditive,        AdtBlackBoxExprAdditive,        true);
  initObject(ExprMultiplicative,  pExprMultiplicative,  AdtBlackBoxExprMultiplicative,  true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprAdditive::AdtBlackBoxExprAdditive(const AdtBlackBoxExprAdditive& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  IsPlus = rCopy.IsPlus;

  copyObject(ExprAdditive,        rCopy,  AdtBlackBoxExprAdditive);
  copyObject(ExprMultiplicative,  rCopy,  AdtBlackBoxExprMultiplicative);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprAdditive::~AdtBlackBoxExprAdditive()
{
  UtlReleaseReference(ExprAdditive);
  UtlReleaseReference(ExprMultiplicative);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxExprAdditive::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                              string& rDerivativeText,
                                              const char* pFile,
                                              int nLine,
                                              double dTapenadeVersion) const
{
  if ((ExprAdditive != 0) && (ExprMultiplicative != 0))
  {
    rDerivativeText += (IsPlus ? "add(" : "sub(");

    ExprAdditive->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ", ";

    ExprMultiplicative->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ")";
  }
  else if (ExprMultiplicative != 0)
  {
    ExprMultiplicative->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxExprAdditive, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprMultiplicative method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxExprMultiplicative::AdtBlackBoxExprMultiplicative(AdtParser* pExprMultiplicative,
                                                             AdtParser* pExprPower,
                                                             bool bIsMultiply)
 : AdtBlackBoxBase()
{
  IsMultiply = bIsMultiply;

  initObject(ExprMultiplicative,  pExprMultiplicative,  AdtBlackBoxExprMultiplicative,  true);
  initObject(ExprPower,           pExprPower,           AdtBlackBoxExprPower,           true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprMultiplicative::AdtBlackBoxExprMultiplicative(const AdtBlackBoxExprMultiplicative& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  IsMultiply = rCopy.IsMultiply;

  copyObject(ExprMultiplicative,  rCopy,  AdtBlackBoxExprMultiplicative);
  copyObject(ExprPower,           rCopy,  AdtBlackBoxExprPower);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprMultiplicative::~AdtBlackBoxExprMultiplicative()
{
  UtlReleaseReference(ExprMultiplicative);
  UtlReleaseReference(ExprPower);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxExprMultiplicative::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                    string& rDerivativeText,
                                                    const char* pFile,
                                                    int nLine,
                                                    double dTapenadeVersion) const
{
  if ((ExprMultiplicative != 0) && (ExprPower != 0))
  {
    rDerivativeText += (IsMultiply ? "mul(" : "div(");

    ExprMultiplicative->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ", ";

    ExprPower->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ")";
  }
  else if (ExprPower != 0)
  {
    ExprPower->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxExprMultiplicative, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprPower method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxExprPower::AdtBlackBoxExprPower(AdtParser* pExprPower,
                                           AdtParser* pExprUnary)
 : AdtBlackBoxBase()
{
  initObject(ExprPower, pExprPower, AdtBlackBoxExprPower, true);
  initObject(ExprUnary, pExprUnary, AdtBlackBoxExprUnary, true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprPower::AdtBlackBoxExprPower(const AdtBlackBoxExprPower& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  copyObject(ExprPower, rCopy,  AdtBlackBoxExprPower);
  copyObject(ExprUnary, rCopy,  AdtBlackBoxExprUnary);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprPower::~AdtBlackBoxExprPower()
{
  UtlReleaseReference(ExprPower);
  UtlReleaseReference(ExprUnary);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxExprPower::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                           string& rDerivativeText,
                                           const char* pFile,
                                           int nLine,
                                           double dTapenadeVersion) const
{
  if ((ExprPower != 0) && (ExprUnary != 0))
  {
    rDerivativeText += "power(";

    ExprPower->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ", ";

    ExprUnary->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    rDerivativeText += ")";
  }
  else if (ExprUnary != 0)
  {
    ExprUnary->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxExprPower, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprUnary method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxExprUnary::AdtBlackBoxExprUnary(AdtParser* pExprPostfix,
                                           bool bHasOp,
                                           bool bIsPlus)
 : AdtBlackBoxBase()
{
  HasOp   = bHasOp;
  IsPlus  = bIsPlus;

  initObject(ExprPostfix, pExprPostfix, AdtBlackBoxExprPostfix, true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprUnary::AdtBlackBoxExprUnary(const AdtBlackBoxExprUnary& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  HasOp   = rCopy.HasOp;
  IsPlus  = rCopy.IsPlus;

  copyObject(ExprPostfix, rCopy, AdtBlackBoxExprPostfix);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprUnary::~AdtBlackBoxExprUnary()
{
  UtlReleaseReference(ExprPostfix);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxExprUnary::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                           string& rDerivativeText,
                                           const char* pFile,
                                           int nLine,
                                           double dTapenadeVersion) const
{
  if (ExprPostfix != 0)
  {
    if (HasOp && !IsPlus)
    {
      rDerivativeText += "sub(realCst 0.0, ";
    }

    ExprPostfix->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

    if (HasOp && !IsPlus)
    {
      rDerivativeText += ")";
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxExprUnary, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprPostfix method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxExprPostfix::AdtBlackBoxExprPostfix(AdtBlackBoxPostfixType nType,
                                               int nValue,
                                               double dValue,
                                               const char* pIdentifier,
                                               AdtParser* pArgList,
                                               AdtParser* pExprAdditive)
 : AdtBlackBoxBase()
{
  Type        = nType;
  IntValue    = nValue;
  DoubleValue = dValue;

  if (pIdentifier != 0)
  {
    name(pIdentifier);
  }

  initObject(ArgList,       pArgList,       AdtBlackBoxArgList,       true);
  initObject(ExprAdditive,  pExprAdditive,  AdtBlackBoxExprAdditive,  true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprPostfix::AdtBlackBoxExprPostfix(const AdtBlackBoxExprPostfix& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  Type        = rCopy.Type;
  IntValue    = rCopy.IntValue;
  DoubleValue = rCopy.DoubleValue;

  copyObject(ArgList,       rCopy,  AdtBlackBoxArgList);
  copyObject(ExprAdditive,  rCopy,  AdtBlackBoxExprAdditive);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxExprPostfix::~AdtBlackBoxExprPostfix()
{
  UtlReleaseReference(ArgList);
  UtlReleaseReference(ExprAdditive);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxExprPostfix::buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                             string& rDerivativeText,
                                             const char* pFile,
                                             int nLine,
                                             double dTapenadeVersion) const
{
  char  sBuffer[32] = {0};

  switch (Type)
  {
    case AdtBlackBoxPostfixInteger:
    {
      ::sprintf(sBuffer, "intCst %d", IntValue);

      rDerivativeText += sBuffer;
      break;
    }

    case AdtBlackBoxPostfixReal:
    {
      ::sprintf(sBuffer, "realCst %g", DoubleValue);

      rDerivativeText += sBuffer;
      break;
    }

    case AdtBlackBoxPostfixVariable:
    {
      if (!rDefaultDef.hasArgument(name()))
      {
        ::printf("ERROR: variable %s in the black box definition not part of the function on line %d in file %s.\n",
                 name().c_str(),
                 nLine,
                 pFile);

        AdtExit(-1);
      }

      string  lcName(name());

      // Need to do this because of a bug in Tapenade that assumes all lowercase names
      lcName.toLower();

      rDerivativeText += "metavar " + lcName;
      break;
    }

    case AdtBlackBoxPostfixFunction:
    {
      string  lcName(name());

      // Need to do this because of a bug in Tapenade that assumes all lowercase names
      lcName.toLower();

      if (dTapenadeVersion > 3.12)
      {
        rDerivativeText += "call(none(), ident " + lcName + ", expressions(";
      }
      else
      {
        rDerivativeText += "call(ident " + lcName + ", expressions(";
      }

      ArgList->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);

      rDerivativeText += "))";
      break;
    }

    case AdtBlackBoxPostfixBrackets:
    {
      ExprAdditive->buildDerivative(rDefaultDef, rDerivativeText, pFile, nLine, dTapenadeVersion);
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxExprPostfix, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxSpec method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxSpec::AdtBlackBoxSpec(AdtParser* pIdentListObj, AdtBlackBoxSpecType nType)
 : AdtBlackBoxBase()
{
  Type = nType;

  initObject(IdentList, pIdentListObj, AdtBlackBoxIdentList, true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxSpec::AdtBlackBoxSpec(const AdtBlackBoxSpec& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  Type = rCopy.Type;

  copyObject(IdentList, rCopy, AdtBlackBoxIdentList);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxSpec::~AdtBlackBoxSpec()
{
  UtlReleaseReference(IdentList);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxSpec::updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                        string& rDerivativeText,
                                        int& nBlackBoxCount,
                                        int& nDerivativeCount,
                                        const char* pFile,
                                        int nLine,
                                        double dTapenadeVersion) const
{
  if (IdentList != 0)
  {
    AdtParserPtrListConstIter Iter;
    string                    sValues;
    size_t                    nNumArgs      = rDefaultDef.numberOfArguments();
    size_t                    nCount        = 0;
    bool                      bAddSeperator = false;

    for (Iter = IdentList->objList().begin() ; Iter != IdentList->objList().end() ; ++Iter)
    {
      const AdtBlackBoxIdent*  pObj = (AdtBlackBoxIdent*)(AdtParser*)*Iter;

      if (pObj != 0)
      {
        if (bAddSeperator)
        {
          sValues += ", ";
        }

        bAddSeperator = true;

        if (pObj->isIndependent())
        {
          sValues += "id";
          nCount  += nNumArgs;
        }
        else if (pObj->isTrue())
        {
          sValues += "1";
          nCount++;
        }
        else
        {
          sValues += "0";
          nCount++;
        }
      }
    }

    size_t      nRequiredArgs = nNumArgs;
    const char* pTypeName     = 0;
    bool        bError        = false;

    switch (Type)
    {
      case SpecType_READ_NOT_WRITTEN:
      {
        if (nCount == nRequiredArgs)
        {
          rDefaultDef.readNotWrittenValues(sValues);
        }
        else
        {
          pTypeName = "ReadNotWritten";
          bError    = true;
        }
        break;
      }

      case SpecType_NOT_READ_THEN_WRITTEN:
      {
        if (nCount == nRequiredArgs)
        {
          rDefaultDef.notReadThenWrittenValues(sValues);
        }
        else
        {
          pTypeName = "NotReadThenWritten";
          bError    = true;
        }
        break;
      }

      case SpecType_NOT_READ_NOT_WRITTEN:
      {
        if (nCount == nRequiredArgs)
        {
          rDefaultDef.notReadNotWrittenValues(sValues);
        }
        else
        {
          pTypeName = "NotReadNotWritten";
          bError    = true;
        }
        break;
      }

      case SpecType_READ_THEN_WRITTEN:
      {
        if (nCount == nRequiredArgs)
        {
          rDefaultDef.readThenWrittenValues(sValues);
        }
        else
        {
          pTypeName = "ReadThenWritten";
          bError    = true;
        }
        break;
      }

      case SpecType_DEPS:
      {
        nRequiredArgs = nNumArgs * nNumArgs;

        if (nCount == nRequiredArgs)
        {
          rDefaultDef.depsValues(sValues);
        }
        else
        {
          pTypeName = "deps";
          bError    = true;
        }
        break;
      }

      default:
      {
        FAIL();
      }
    }

    if (bError)
    {
      ::printf("ERROR: %s entry in black box definition requires %d values whereas %d values were given on line %d in file %s.\n",
               pTypeName,
               (int)nRequiredArgs,
               (int)nCount,
               nLine,
               pFile);

      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxSpec, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgList method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxArgList::AdtBlackBoxArgList(AdtParser* pExprAdditiveObj)
 : AdtBlackBoxBase()
{
  add(pExprAdditiveObj);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgList::AdtBlackBoxArgList(const AdtBlackBoxArgList& rCopy)
: AdtBlackBoxBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgList::~AdtBlackBoxArgList()
{

}


//  ----------------------------------------------------------------------------

implType(AdtBlackBoxArgList, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxSpecList method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxSpecList::AdtBlackBoxSpecList(AdtParser* pSpecListObj)
 : AdtBlackBoxBase()
{
  add(pSpecListObj);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxSpecList::AdtBlackBoxSpecList(const AdtBlackBoxSpecList& rCopy)
 : AdtBlackBoxBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxSpecList::~AdtBlackBoxSpecList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxSpecList, AdtBlackBoxBase);



//  ----------------------------------------------------------------------------
//  AdtBlackBoxIdent method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxIdent::AdtBlackBoxIdent(int nNumber)
 : AdtBlackBoxBase()
{
  if (nNumber < 0)
  {
    IsIndependent = true;
    IsTrue        = false;
  }
  else if (nNumber == 0)
  {
    IsIndependent = false;
    IsTrue        = false;
  }
  else
  {
    IsIndependent = false;
    IsTrue        = true;
  }
}

//  ----------------------------------------------------------------------------

AdtBlackBoxIdent::AdtBlackBoxIdent(const AdtBlackBoxIdent& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  IsIndependent = rCopy.IsIndependent;
  IsTrue        = rCopy.IsTrue;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxIdent::~AdtBlackBoxIdent()
{

}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxIdent, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxIdentList method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxIdentList::AdtBlackBoxIdentList(AdtParser* pIdentListObj)
 : AdtBlackBoxBase()
{
  add(pIdentListObj);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxIdentList::AdtBlackBoxIdentList(const AdtBlackBoxIdentList& rCopy)
 : AdtBlackBoxBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxIdentList::~AdtBlackBoxIdentList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxIdentList, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxStandAloneDef method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxStandAloneDef::AdtBlackBoxStandAloneDef(const char* pIdentifier,
                                                   AdtParser* pArgDefListObj,
                                                   AdtBlackBoxArgType nType,
                                                   bool bIsArray,
                                                   AdtParser* pDerivativeListObj)
 : AdtBlackBoxBase()
{
  if (pIdentifier != 0)
  {
    name(pIdentifier);
  }

  ReturnType    = nType;
  ReturnIsArray = bIsArray;

  initObject(ArgDefList,      pArgDefListObj,     AdtBlackBoxArgDefList,      true);
  initObject(DerivativeList,  pDerivativeListObj, AdtBlackBoxDerivativeList,  true);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxStandAloneDef::AdtBlackBoxStandAloneDef(const AdtBlackBoxStandAloneDef& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  ReturnType    = rCopy.ReturnType;
  ReturnIsArray = rCopy.ReturnIsArray;

  copyObject(ArgDefList,      rCopy,  AdtBlackBoxArgDefList);
  copyObject(DerivativeList,  rCopy,  AdtBlackBoxDerivativeList);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxStandAloneDef::~AdtBlackBoxStandAloneDef()
{
  UtlReleaseReference(ArgDefList);
  UtlReleaseReference(DerivativeList);
}

//  ----------------------------------------------------------------------------

void AdtBlackBoxStandAloneDef::writeBlackBoxDefinition(AdtFile& rOutFile,
                                                       AdtIntByStringMap& rIsBlackBoxMap,
                                                       double dTapenadeVersion)
{
  if (DerivativeList != 0)
  {
    string                    sDerivativeText;
    int                       nBlackBoxCount    = 0;
    int                       nDerivativeCount  = 0;
    bool                      bIsFunction       = (ReturnType != AdtBlackBox_undefined);
    AdtBlackBoxDefinition     BlackBox(name(), bIsFunction, fileName(), lineNumber());
    AdtParserPtrListConstIter Iter;

    for (Iter = ArgDefList->objList().begin() ; Iter != ArgDefList->objList().end() ; ++Iter)
    {
      const AdtBlackBoxArgDef*  pObj = (AdtBlackBoxArgDef*)(AdtParser*)*Iter;

      if (!bIsFunction && (caseless_string_comparison("result", pObj->name()) == 0))
      {
        BlackBox.addReturn(pObj->argType(), pObj->isArray());
      }
      else
      {
        BlackBox.addArgument(pObj->argType(),
                             pObj->name(),
                             pObj->dirType() == AdtAutoDir_IN,
                             pObj->dirType() == AdtAutoDir_OUT,
                             pObj->dirType() == AdtAutoDir_UNDEFINED,
                             pObj->dirType() == AdtAutoDir_INOUT,
                             pObj->isArray());
      }
    }

    if (bIsFunction)
    {
      BlackBox.addReturn(ReturnType, ReturnIsArray);
    }

    DerivativeList->updateBlackBoxDef(BlackBox,
                                      sDerivativeText,
                                      nBlackBoxCount,
                                      nDerivativeCount,
                                      fileName(),
                                      lineNumber(),
                                      dTapenadeVersion);

    BlackBox.derivativeSpecification(sDerivativeText);
    BlackBox.writeDefinition(rOutFile, dTapenadeVersion);

    rIsBlackBoxMap[BlackBox.nativeName()] = 1;
  }
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxStandAloneDef, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgDef method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxArgDef::AdtBlackBoxArgDef(const char* pIdentifier,
                                     AdtBlackBoxArgType nType,
                                     bool bIsArray,
                                     AdtAutoDir nDirType)
 : AdtBlackBoxBase()
{
  if (pIdentifier != 0)
  {
    name(pIdentifier);
  }

  Type    = nType;
  IsArray = bIsArray;
  DirType = nDirType;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgDef::AdtBlackBoxArgDef(const AdtBlackBoxArgDef& rCopy)
 : AdtBlackBoxBase(rCopy)
{
  Type    = rCopy.Type;
  IsArray = rCopy.IsArray;
  DirType = rCopy.DirType;
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgDef::~AdtBlackBoxArgDef()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxArgDef, AdtBlackBoxBase);


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgDefList method implementations
//  ----------------------------------------------------------------------------
AdtBlackBoxArgDefList::AdtBlackBoxArgDefList(AdtParser* pArgDefListObj)
 : AdtBlackBoxBase()
{
  add(pArgDefListObj);
}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgDefList::AdtBlackBoxArgDefList(const AdtBlackBoxArgDefList& rCopy)
 : AdtBlackBoxBase(rCopy)
{

}

//  ----------------------------------------------------------------------------

AdtBlackBoxArgDefList::~AdtBlackBoxArgDefList()
{

}

//  ----------------------------------------------------------------------------

implType(AdtBlackBoxArgDefList, AdtBlackBoxBase);
