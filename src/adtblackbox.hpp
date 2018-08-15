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
//    adtblackbox.hpp
//
//  Purpose:
//    This file includes declarations of classes used to build black box
//    parse trees.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTBLACKBOX_HPP
#define __ADTBLACKBOX_HPP


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION const char*  adtBlackBox_AllocString(void* pContext, const char* pTokenText);
C_FUNCTION void         adtBlackBox_SetRoot(void* pObj);
C_FUNCTION void*        adtBlackBoxDerivativeList_create(void* pObj);
C_FUNCTION void*        adtBlackBoxList_add(void* pList, void* pObj);
C_FUNCTION void*        adtBlackBoxDerivative_create(const char* pIdentifier, void* pExprAdditiveObj, void* pExtendedListObj, void* pSpecListObj, int nIsExtended, int nIsNull, void* pBlackBoxDefObj);
C_FUNCTION void*        adtBlackBoxSpecList_create(void* pObj);
C_FUNCTION void*        adtBlackBoxSpec_create(void* pIdentList, int nType);
C_FUNCTION void*        adtBlackBoxIdentList_create(void* pObj);
C_FUNCTION void*        adtBlackBoxIdent_create(int nNumber);
C_FUNCTION void*        adtBlackBoxExprAdditive_create(void* pExprAdditiveObj, void* pExprMultiplicativeObj, int nIsPlus);
C_FUNCTION void*        adtBlackBoxExprMultiplicative_create(void* pExprMultiplicativeObj, void* pExprPowerObj, int nIsMultiply);
C_FUNCTION void*        adtBlackBoxExprPower_create(void* pExprPowerObj, void* pExprUnaryObj);
C_FUNCTION void*        adtBlackBoxExprUnary_create(void* pExprPostfixObj, int nHasOp, int nIsPlus);
C_FUNCTION void*        adtBlackBoxExprPostfix_create(int nType, int nValue, double dValue, const char* pIdentifier, void* pArgListObj, void* pExprAdditiveObj);
C_FUNCTION void*        adtBlackBoxArgList_create(void* pObj);
C_FUNCTION void*        adtBlackBoxStandAloneDef_create(const char* pIdentifier, void* pArgDefListObj, int nArgType, void* pDerivativeListObj);
C_FUNCTION void*        adtBlackBoxArgDef_create(const char* pIdentifier, int nArgType, int nDirType);
C_FUNCTION void*        adtBlackBoxArgDefList_create(void* pObj);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtBlackBoxDerivativeList;
class AdtBlackBoxExprAdditive;
class AdtBlackBoxExprMultiplicative;
class AdtBlackBoxExprPower;
class AdtBlackBoxExprUnary;
class AdtBlackBoxExprPostfix;
class AdtBlackBoxArgList;
class AdtBlackBoxDerivativeExtendedList;
class AdtBlackBoxSpecList;
class AdtBlackBoxIdentList;
class AdtBlackBoxStandAloneDef;
class AdtBlackBoxArgDef;
class AdtBlackBoxArgDefList;



//  ----------------------------------------------------------------------------

enum AdtBlackBoxArgType{AdtBlackBox_undefined,
                        AdtBlackBox_real,
                        AdtBlackBox_integer,
                        AdtBlackBox_complex,
                        AdtBlackBox_character,
                        AdtBlackBox_boolean};


//  ----------------------------------------------------------------------------
//  class AdtBlackBoxDefinition
//  ----------------------------------------------------------------------------
class AdtBlackBoxDefinition
{
  struct AdtBlackBoxInfo
  {
    string              Name;
    size_t              Parameter;
    AdtBlackBoxArgType  Type;
    bool                ReadNotWritten;
    bool                NotReadThenWritten;
    bool                NotReadNotWritten;
    bool                ReadThenWritten;
    bool                IsArray;

    AdtBlackBoxInfo(size_t nParameter,
                    AdtBlackBoxArgType nType,
                    const char* pName,
                    bool bReadNotWritten,
                    bool bNotReadThenWritten,
                    bool bNotReadNotWritten,
                    bool bReadThenWritten,
                    bool bIsArray);

    AdtBlackBoxInfo(const AdtBlackBoxInfo& rCopy);

    AdtBlackBoxInfo&    operator = (const AdtBlackBoxInfo& rCopy);

    void                writeSeperator(AdtFile& rOutFile) const;
    void                appendArg(string& rString, bool& bWithSeperator) const;
    void                writeShape(AdtFile& rOutFile, bool bWithSeperator) const;
    void                writeType(AdtFile& rOutFile, bool bWithSeperator, double dTapenadeVersion) const;
    void                writeReadNotWritten(AdtFile& rOutFile, bool bWithSeperator) const;
    void                writeNotReadThenWritten(AdtFile& rOutFile, bool bWithSeperator) const;
    void                writeNotReadNotWritten(AdtFile& rOutFile, bool bWithSeperator) const;
    void                writeReadThenWritten(AdtFile& rOutFile, bool bWithSeperator) const;

    const string&       name() const;
  };

  //  ----------------------------------------------------------------------------
  //  List of AdtBlackBoxInfo objects
  //  ----------------------------------------------------------------------------
  typedef std::list<AdtBlackBoxInfo>                  AdtBlackBoxInfoList;
  typedef std::list<AdtBlackBoxInfo>::iterator        AdtBlackBoxInfoListIter;
  typedef std::list<AdtBlackBoxInfo>::const_iterator  AdtBlackBoxInfoConstIter;

private:
  string                Name;
  string                BaseName;
  string                NativeName;
  string                FileName;
  int                   LineNumber;
  bool                  IsFunction;
  AdtIntByStringMap     NameMap;
  AdtBlackBoxInfoList   TypeList;
  string                ReadNotWrittenValues;
  string                NotReadThenWrittenValues;
  string                NotReadNotWrittenValues;
  string                ReadThenWrittenValues;
  string                DepsValues;
  string                DerivativeSpecification;

protected:
  void                  translateName(const char* pName);

public:
  AdtBlackBoxDefinition(const char* pName, bool bIsFunction, const char* pFileName, int nLineNumber);
  AdtBlackBoxDefinition(const AdtBlackBoxDefinition& rCopy);
  virtual ~AdtBlackBoxDefinition();

  const string&         name() const;
  const string&         baseName() const;
  const string&         nativeName() const;

  void                  addArgument(AdtBlackBoxArgType nType,
                                    const char* pName,
                                    bool bReadNotWritten,
                                    bool bNotReadThenWritten,
                                    bool bNotReadNotWritten,
                                    bool bReadThenWritten,
                                    bool bIsArray);

  void                  addReturn(AdtBlackBoxArgType nType,
                                  bool bIsArray);

  void                  writeDefinition(AdtFile& rOutFile, double dTapenadeVersion) const;

  void                  readNotWrittenValues(const char* pValues);
  void                  notReadThenWrittenValues(const char* pValues);
  void                  notReadNotWrittenValues(const char* pValues);
  void                  readThenWrittenValues(const char* pValues);
  void                  depsValues(const char* pValues);
  void                  derivativeSpecification(const char* pDerivativeSpec);

  void                  appendCallPart(string& rDerivativeSpec, double dTapenadeVersion) const;

  bool                  hasArgument(const char* pName) const;

  size_t                numberOfArguments() const;

  const char*           fileName() const;
  int                   lineNumber() const;
  bool                  isFunction() const;
};

//  ----------------------------------------------------------------------------

inline const string& AdtBlackBoxDefinition::AdtBlackBoxInfo::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline const string& AdtBlackBoxDefinition::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline const string& AdtBlackBoxDefinition::baseName() const
{
  return (BaseName);
}

//  ----------------------------------------------------------------------------

inline const string& AdtBlackBoxDefinition::nativeName() const
{
  return (NativeName);
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::readNotWrittenValues(const char* pValues)
{
  ReadNotWrittenValues = (pValues != 0) ? pValues : "";
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::notReadThenWrittenValues(const char* pValues)
{
  NotReadThenWrittenValues = (pValues != 0) ? pValues : "";
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::notReadNotWrittenValues(const char* pValues)
{
  NotReadNotWrittenValues = (pValues != 0) ? pValues : "";
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::readThenWrittenValues(const char* pValues)
{
  ReadThenWrittenValues = (pValues != 0) ? pValues : "";
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::depsValues(const char* pValues)
{
  DepsValues = (pValues != 0) ? pValues : "";
}

//  ----------------------------------------------------------------------------

inline void AdtBlackBoxDefinition::derivativeSpecification(const char* pDerivativeSpec)
{
  DerivativeSpecification = (pDerivativeSpec != 0) ? pDerivativeSpec : "";
}

//  ----------------------------------------------------------------------------

inline size_t AdtBlackBoxDefinition::numberOfArguments() const
{
  return (TypeList.size());
}

//  ----------------------------------------------------------------------------

inline const char* AdtBlackBoxDefinition::fileName() const
{
  return (FileName);
}

//  ----------------------------------------------------------------------------

inline int AdtBlackBoxDefinition::lineNumber() const
{
  return (LineNumber);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDefinition::isFunction() const
{
  return (IsFunction);
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtBlackBoxDefinition pointer by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtBlackBoxDefinition*>                         AdtBlackBoxDefinitionPtrStringPair;
typedef std::map<string, AdtBlackBoxDefinition*, string_less>                   AdtBlackBoxDefinitionPtrByStringMap;
typedef std::map<string, AdtBlackBoxDefinition*, string_less>::iterator         AdtBlackBoxDefinitionPtrByStringMapIter;
typedef std::map<string, AdtBlackBoxDefinition*, string_less>::const_iterator   AdtBlackBoxDefinitionPtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  class AdtBlackBoxCompiler
//  ----------------------------------------------------------------------------
class AdtBlackBoxCompiler : public AdtCommon
{
private:
  string                          ErrorMsg;
  string                          ErrorContext;

protected:
  AdtBlackBoxDerivativeList*      compileFile(const char* pBlackBoxFile);
  AdtBlackBoxDerivativeList*      compileText(const char* pBlackBoxText);

public:
  AdtBlackBoxCompiler();
  virtual ~AdtBlackBoxCompiler();

  static bool                     isBlackBox(const char* pComments);

  static void                     parseComments(AdtBlackBoxDefinition& rDefaultDef,
                                                const char* pComments,
                                                const char* pFile,
                                                int nLine,
                                                double dTapenadeVersion);

  static bool                     makeBlackBoxFile(const char* pSrcDefinitionsFile,
                                                   const char* pDestBlackBoxFile,
                                                   AdtIntByStringMap& rIsBlackBoxMap,
                                                   bool bAppend,
                                                   double dTapenadeVersion);
};


//  ----------------------------------------------------------------------------
//  class AdtBlackBoxBase
//  ----------------------------------------------------------------------------
class AdtBlackBoxBase : public AdtParser
{
private:
  static AdtBlackBoxDerivativeList*   BlackBoxRootObject;

public:
  AdtBlackBoxBase();
  AdtBlackBoxBase(const AdtBlackBoxBase& rCopy);
  virtual ~AdtBlackBoxBase();

  virtual void                        buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                      string& rDerivativeText,
                                                      const char* pFile,
                                                      int nLine,
                                                      double dTapenadeVersion) const;

  virtual void                        updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                                        string& rDerivativeText,
                                                        int& nBlackBoxCount,
                                                        int& nDerivativeCount,
                                                        const char* pFile,
                                                        int nLine,
                                                        double dTapenadeVersion) const;

  static void                         blackBoxRootObject(AdtParser* pRoot);
  static AdtBlackBoxDerivativeList*   blackBoxRootObject();

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxDerivative class
//  ----------------------------------------------------------------------------
class AdtBlackBoxDerivative : public AdtBlackBoxBase
{
private:
  string                      Identifier;
  AdtBlackBoxExprAdditive*    ExprAdditive;
  AdtBlackBoxDerivativeList*  DerivativeExtendedList;
  AdtBlackBoxSpecList*        SpecList;
  bool                        IsExtended;
  bool                        IsNull;
  AdtBlackBoxStandAloneDef*   BlackBoxDef;

public:
  AdtBlackBoxDerivative(const char* pIdentifier,
                        AdtParser* pExprAdditiveObj,
                        AdtParser* pExtendedListObj,
                        AdtParser* pSpecListObj,
                        bool bIsExtended,
                        bool bIsNull,
                        AdtParser* pBlackBoxDefObj);

  AdtBlackBoxDerivative(const AdtBlackBoxDerivative& rCopy);
  virtual ~AdtBlackBoxDerivative();

  virtual void                buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                              string& rDerivativeText,
                                              const char* pFile,
                                              int nLine,
                                              double dTapenadeVersion) const;

  virtual void                updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                                string& rDerivativeText,
                                                int& nBlackBoxCount,
                                                int& nDerivativeCount,
                                                const char* pFile,
                                                int nLine,
                                                double dTapenadeVersion) const;

  AdtBlackBoxStandAloneDef*   blackBoxDef();

  bool                        isDerivativeNull() const;
  bool                        isDerivativeComplete() const;
  bool                        isDerivativeMultipart() const;
  bool                        isDerivative() const;

  bool                        isBlackBoxComplete() const;
  bool                        isBlackBoxDefault() const;
  bool                        isBlackBox() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtBlackBoxStandAloneDef* AdtBlackBoxDerivative::blackBoxDef()
{
  return (BlackBoxDef);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isDerivativeNull() const
{
  return (IsNull);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isDerivativeComplete() const
{
  bool bComplete = (SpecList == 0) && (ExprAdditive != 0) && (DerivativeExtendedList == 0) && (Identifier.length() > 0);

  return (bComplete);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isDerivativeMultipart() const
{
  bool bMultipart = (SpecList == 0) && (ExprAdditive != 0) && (DerivativeExtendedList != 0) && (Identifier.length() == 0);

  return (bMultipart);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isDerivative() const
{
  return (isDerivativeNull() || isDerivativeComplete() || isDerivativeMultipart());
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isBlackBoxComplete() const
{
  bool bComplete = (SpecList != 0) && (ExprAdditive == 0) && (DerivativeExtendedList == 0) && (Identifier.length() == 0);

  return (bComplete);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isBlackBoxDefault() const
{
  bool bDefault = (SpecList == 0) && (ExprAdditive == 0) && (DerivativeExtendedList == 0) && (Identifier.length() == 0);

  return (bDefault);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxDerivative::isBlackBox() const
{
  return (isBlackBoxComplete() || isBlackBoxDefault());
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxDerivativeList class
//  ----------------------------------------------------------------------------
class AdtBlackBoxDerivativeList : public AdtBlackBoxBase
{
private:

public:
  AdtBlackBoxDerivativeList(AdtParser* pBlackBoxDerivativeObj);
  AdtBlackBoxDerivativeList(const AdtBlackBoxDerivativeList& rCopy);
  virtual ~AdtBlackBoxDerivativeList();

  virtual void                        buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                      string& rDerivativeText,
                                                      const char* pFile,
                                                      int nLine,
                                                      double dTapenadeVersion) const;

  declListType(AdtBlackBoxDerivative);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprAdditive class
//  ----------------------------------------------------------------------------
class AdtBlackBoxExprAdditive : public AdtBlackBoxBase
{
private:
  bool                            IsPlus;
  AdtBlackBoxExprAdditive*        ExprAdditive;
  AdtBlackBoxExprMultiplicative*  ExprMultiplicative;

public:
  AdtBlackBoxExprAdditive(AdtParser* pExprAdditive,
                          AdtParser* pExprMultiplicative,
                          bool bIsPlus);

  AdtBlackBoxExprAdditive(const AdtBlackBoxExprAdditive& rCopy);
  virtual ~AdtBlackBoxExprAdditive();

  virtual void                    buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                  string& rDerivativeText,
                                                  const char* pFile,
                                                  int nLine,
                                                  double dTapenadeVersion) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprMultiplicative class
//  ----------------------------------------------------------------------------
class AdtBlackBoxExprMultiplicative : public AdtBlackBoxBase
{
private:
  bool                            IsMultiply;
  AdtBlackBoxExprMultiplicative*  ExprMultiplicative;
  AdtBlackBoxExprPower*           ExprPower;

public:
  AdtBlackBoxExprMultiplicative(AdtParser* pExprMultiplicative,
                                AdtParser* pExprPower,
                                bool bIsMultiply);

  AdtBlackBoxExprMultiplicative(const AdtBlackBoxExprMultiplicative& rCopy);
  virtual ~AdtBlackBoxExprMultiplicative();

  virtual void                    buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                  string& rDerivativeText,
                                                  const char* pFile,
                                                  int nLine,
                                                  double dTapenadeVersion) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprPower class
//  ----------------------------------------------------------------------------
class AdtBlackBoxExprPower : public AdtBlackBoxBase
{
private:
  bool                            IsMultiply;
  AdtBlackBoxExprPower*           ExprPower;
  AdtBlackBoxExprUnary*           ExprUnary;

public:
  AdtBlackBoxExprPower(AdtParser* pExprPower,
                       AdtParser* pExprUnary);

  AdtBlackBoxExprPower(const AdtBlackBoxExprPower& rCopy);
  virtual ~AdtBlackBoxExprPower();

  virtual void                    buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                                  string& rDerivativeText,
                                                  const char* pFile,
                                                  int nLine,
                                                  double dTapenadeVersion) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprUnary class
//  ----------------------------------------------------------------------------
class AdtBlackBoxExprUnary : public AdtBlackBoxBase
{
private:
  bool                    HasOp;
  bool                    IsPlus;
  AdtBlackBoxExprPostfix* ExprPostfix;

public:
  AdtBlackBoxExprUnary(AdtParser* pExprPostfix,
                       bool bHasOp,
                       bool bIsPlus);

  AdtBlackBoxExprUnary(const AdtBlackBoxExprUnary& rCopy);
  virtual ~AdtBlackBoxExprUnary();

  virtual void            buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                          string& rDerivativeText,
                                          const char* pFile,
                                          int nLine,
                                          double dTapenadeVersion) const;

  declType;
};


enum AdtBlackBoxPostfixType{AdtBlackBoxPostfixInteger  = 0,
                            AdtBlackBoxPostfixReal     = 1,
                            AdtBlackBoxPostfixVariable = 2,
                            AdtBlackBoxPostfixFunction = 3,
                            AdtBlackBoxPostfixBrackets = 4};

//  ----------------------------------------------------------------------------
//  AdtBlackBoxExprPostfix class
//  ----------------------------------------------------------------------------
class AdtBlackBoxExprPostfix : public AdtBlackBoxBase
{
private:
  int                       IntValue;
  double                    DoubleValue;
  AdtBlackBoxArgList*       ArgList;
  AdtBlackBoxExprAdditive*  ExprAdditive;
  AdtBlackBoxPostfixType    Type;

public:
  AdtBlackBoxExprPostfix(AdtBlackBoxPostfixType nType,
                         int nValue,
                         double dValue,
                         const char* pIdentifier,
                         AdtParser* pArgList,
                         AdtParser* pExprAdditive);

  AdtBlackBoxExprPostfix(const AdtBlackBoxExprPostfix& rCopy);
  virtual ~AdtBlackBoxExprPostfix();

  virtual void              buildDerivative(const AdtBlackBoxDefinition& rDefaultDef,
                                            string& rDerivativeText,
                                            const char* pFile,
                                            int nLine,
                                            double dTapenadeVersion) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgList class
//  ----------------------------------------------------------------------------
class AdtBlackBoxArgList : public AdtBlackBoxBase
{
private:

public:
  AdtBlackBoxArgList(AdtParser* pExprAdditiveObj);
  AdtBlackBoxArgList(const AdtBlackBoxArgList& rCopy);
  virtual ~AdtBlackBoxArgList();

  declListType(AdtBlackBoxExprAdditive);
  declType;
};


//  ----------------------------------------------------------------------------

enum AdtBlackBoxSpecType
{
  SpecType_READ_NOT_WRITTEN       = 0,
  SpecType_NOT_READ_THEN_WRITTEN  = 1,
  SpecType_NOT_READ_NOT_WRITTEN   = 2,
  SpecType_READ_THEN_WRITTEN      = 3,
  SpecType_DEPS                   = 4
};

//  ----------------------------------------------------------------------------
//  AdtBlackBoxSpec class
//  ----------------------------------------------------------------------------
class AdtBlackBoxSpec : public AdtBlackBoxBase
{
private:
  AdtBlackBoxSpecType         Type;
  AdtBlackBoxIdentList*       IdentList;

public:
  AdtBlackBoxSpec(AdtParser* pIdentListObj, AdtBlackBoxSpecType nType);
  AdtBlackBoxSpec(const AdtBlackBoxSpec& rCopy);
  virtual ~AdtBlackBoxSpec();

  virtual void                updateBlackBoxDef(AdtBlackBoxDefinition& rDefaultDef,
                                                string& rDerivativeText,
                                                int& nBlackBoxCount,
                                                int& nDerivativeCount,
                                                const char* pFile,
                                                int nLine,
                                                double dTapenadeVersion) const;

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxSpecList class
//  ----------------------------------------------------------------------------
class AdtBlackBoxSpecList : public AdtBlackBoxBase
{
private:

public:
  AdtBlackBoxSpecList(AdtParser* pSpecListObj);
  AdtBlackBoxSpecList(const AdtBlackBoxSpecList& rCopy);
  virtual ~AdtBlackBoxSpecList();

  declListType(AdtBlackBoxSpec);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxIdent class
//  ----------------------------------------------------------------------------
class AdtBlackBoxIdent : public AdtBlackBoxBase
{
private:
  bool  IsIndependent;
  bool  IsTrue;

public:
  AdtBlackBoxIdent(int nNumber);
  AdtBlackBoxIdent(const AdtBlackBoxIdent& rCopy);
  virtual ~AdtBlackBoxIdent();

  bool  isIndependent() const;
  bool  isTrue() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxIdent::isIndependent() const
{
  return (IsIndependent);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxIdent::isTrue() const
{
  return (IsTrue);
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxIdentList class
//  ----------------------------------------------------------------------------
class AdtBlackBoxIdentList : public AdtBlackBoxBase
{
private:

public:
  AdtBlackBoxIdentList(AdtParser* pIdentListObj);
  AdtBlackBoxIdentList(const AdtBlackBoxIdentList& rCopy);
  virtual ~AdtBlackBoxIdentList();

  declListType(AdtBlackBoxIdent);
  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxStandAloneDef class
//  ----------------------------------------------------------------------------
class AdtBlackBoxStandAloneDef : public AdtBlackBoxBase
{
private:
  AdtBlackBoxArgDefList*      ArgDefList;
  AdtBlackBoxArgType          ReturnType;
  bool                        ReturnIsArray;
  AdtBlackBoxDerivativeList*  DerivativeList;

public:
  AdtBlackBoxStandAloneDef(const char* pIdentifier,
                           AdtParser* pArgDefListObj,
                           AdtBlackBoxArgType nType,
                           bool bIsArray,
                           AdtParser* pDerivativeListObj);

  AdtBlackBoxStandAloneDef(const AdtBlackBoxStandAloneDef& rCopy);

  virtual ~AdtBlackBoxStandAloneDef();

  void                        writeBlackBoxDefinition(AdtFile& rOutFile,
                                                      AdtIntByStringMap& rIsBlackBoxMap,
                                                      double dTapenadeVersion);

  declType;
};


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgDef class
//  ----------------------------------------------------------------------------
class AdtBlackBoxArgDef : public AdtBlackBoxBase
{
private:
  AdtBlackBoxArgType  Type;
  bool                IsArray;
  AdtAutoDir          DirType;

public:
  AdtBlackBoxArgDef(const char* pIdentifier,
                    AdtBlackBoxArgType nType,
                    bool bIsArray,
                    AdtAutoDir nDirType);

  AdtBlackBoxArgDef(const AdtBlackBoxArgDef& rCopy);
  virtual ~AdtBlackBoxArgDef();

  AdtBlackBoxArgType  argType() const;
  AdtAutoDir          dirType() const;
  bool                isArray() const;

  declType;
};

//  ----------------------------------------------------------------------------

inline AdtBlackBoxArgType AdtBlackBoxArgDef::argType() const
{
  return (Type);
}

//  ----------------------------------------------------------------------------

inline AdtAutoDir AdtBlackBoxArgDef::dirType() const
{
  return (DirType);
}

//  ----------------------------------------------------------------------------

inline bool AdtBlackBoxArgDef::isArray() const
{
  return (IsArray);
}


//  ----------------------------------------------------------------------------
//  AdtBlackBoxArgDefList class
//  ----------------------------------------------------------------------------
class AdtBlackBoxArgDefList : public AdtBlackBoxBase
{
private:

public:
  AdtBlackBoxArgDefList(AdtParser* pArgDefListObj);
  AdtBlackBoxArgDefList(const AdtBlackBoxArgDefList& rCopy);
  virtual ~AdtBlackBoxArgDefList();

  declListType(AdtBlackBoxArgDef);
  declType;
};


#endif //__cplusplus
#endif //__ADTBLACKBOX_HPP
