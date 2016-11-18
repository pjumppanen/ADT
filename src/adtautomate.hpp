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
//    adtautomate.hpp
//
//  Purpose:
//    This file includes declarations of utility classes used to automate the
//    construction of construction, initialisation and interface code, both
//    in R and the target language.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTAUTOMATE_HPP
#define __ADTAUTOMATE_HPP


#include "adtcommon.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtExpressionAdditive;
class AdtAutoAttribute;
class AdtAutoClass;
class AdtFile;

//  ----------------------------------------------------------------------------
//  Include file base names
//  ----------------------------------------------------------------------------
extern const char* CONSTRUCTOR_ARGS;
extern const char* CONSTRUCTOR_CALL_ARGS;
extern const char* CONSTRUCTOR_LOCALS;
extern const char* CONSTRUCTOR_SCALARS_PHASE;
extern const char* CONSTRUCTOR_ARRAYS_PHASE;
extern const char* IMPL_LIB_INTERFACE_METHODS;
extern const char* IMPL_LIB_INTERFACE_GLOBALS;
extern const char* DECL_LIB_INTERFACE_METHODS;
extern const char* DECL_LIB_INTERFACE_GLOBALS;
extern const char* DECL_LIB_INTERFACE_CONSTRUCTOR;
extern const char* IMPL_LIB_INTERFACE_CONSTRUCTOR;
extern const char* IMPL_LIB_REGISTRATION;
extern const char* LIB_EXPORTS;
extern const char* ARRAY_PLANS;
extern const char* ARRAY_PLANS_INIT;
extern const char* ARRAY_PLANS_COPY;


//  ----------------------------------------------------------------------------
//  List of AdtAutoAttribute objects
//  ----------------------------------------------------------------------------
typedef std::list<AdtAutoAttribute*>                  AdtAutoAttributePtrList;
typedef std::list<AdtAutoAttribute*>::iterator        AdtAutoAttributePtrListIter;
typedef std::list<AdtAutoAttribute*>::const_iterator  AdtAutoAttributePtrListConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of AdtAutoAttribute by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtAutoAttribute*>                        AdtAutoAttributePtrStringPair;
typedef std::map<string, AdtAutoAttribute*, string_less>                  AdtAutoAttributePtrByStringMap;
typedef std::map<string, AdtAutoAttribute*, string_less>::iterator        AdtAutoAttributePtrByStringMapIter;
typedef std::map<string, AdtAutoAttribute*, string_less>::const_iterator  AdtAutoAttributePtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of AdtAutoClass by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtAutoClass*>                        AdtAutoClassPtrStringPair;
typedef std::map<string, AdtAutoClass*, string_less>                  AdtAutoClassPtrByStringMap;
typedef std::map<string, AdtAutoClass*, string_less>::iterator        AdtAutoClassPtrByStringMapIter;
typedef std::map<string, AdtAutoClass*, string_less>::const_iterator  AdtAutoClassPtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  Multi-mappings of AdtAutoAttribute by int
//  ----------------------------------------------------------------------------
typedef std::pair<const int, AdtAutoAttribute*>                 AdtAutoAttributePtrIntPair;
typedef std::multimap<int, AdtAutoAttribute*>                   AdtAutoAttributePtrByIntMultimap;
typedef std::multimap<int, AdtAutoAttribute*>::iterator         AdtAutoAttributePtrByIntMultimapIter;
typedef std::multimap<int, AdtAutoAttribute*>::const_iterator   AdtAutoAttributePtrByIntMultimapConstIter;


class AdtAutoHelper
{
private:
  static char         Buffer[2048];

public:
  AdtAutoHelper();
  AdtAutoHelper(const AdtAutoHelper& rCopy);
  virtual ~AdtAutoHelper();

  const char*         delphiType(AdtAutoType nType, int nDimensions) const;
  const char*         delphiType(AdtAutoType nType) const;
  const char*         delphiConstructorType(AdtAutoType nType) const;
  const char*         cppType(AdtAutoType nType, int nDimensions) const;
  const char*         cppType(AdtAutoType nType) const;
  const char*         R_Type(AdtAutoType nType) const;
  const char*         R_AccessType(AdtAutoType nType) const;
  const char*         R_CheckType(AdtAutoType nType, bool bIsCpp) const;

  void                DelphiR_registerInterfaceRoutine(const char* pExportRountineName,
                                                       const char* pInternalRountineName,
                                                       size_t nArgs) const;

  void                writeDelphiR_Return(AdtFile& rFile,
                                          AdtAutoType nType,
                                          const char* pReturn) const;

  void                writeDelphiR_CheckType(AdtFile& rFile,
                                             AdtAutoType nType,
                                             const char* pVar) const;

  void                writeDelphiVarCheckType(AdtFile& rFile,
                                              const char* pName,
                                              AdtAutoType nType,
                                              int nDimensions = 0,
                                              const char* pExtraArgs = 0) const;

  void                writeDelphiR_CheckInstance(AdtFile& rFile,
                                                 const char* pClassName,
                                                 const char* pAliasName) const;

  void                writeDelphiR_GetterAndSetter(AdtFile& rFile,
                                                   const char* pName,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName,
                                                   bool bScalar) const;

  void                writeDelphiR_InterfaceDeclMethods(AdtFile& rFile,
                                                        const char* pName,
                                                        const AdtAutoAttributePtrList& rArgumentList) const;

  void                writeDelphiR_InterfaceDeclGlobals(AdtFile& rFile,
                                                        const char* pName,
                                                        const AdtAutoAttributePtrList& rArgumentList,
                                                        const char* pAliasName) const;

  void                writeDelphiR_InterfaceImplMethods(AdtFile& rFile,
                                                        const char* pName,
                                                        AdtAutoType nType,
                                                        const AdtAutoAttributePtrList& rArgumentList,
                                                        const char* pClassName,
                                                        const char* pAliasName,
                                                        const char* pR_TypeName) const;

  void                writeDelphiR_InterfaceImplGlobals(AdtFile& rFile,
                                                        const char* pName,
                                                        AdtAutoType nType,
                                                        const AdtAutoAttributePtrList& rArgumentList,
                                                        const char* pClassName,
                                                        const char* pAliasName,
                                                        const char* pR_TypeName) const;

  void                CppR_registerInterfaceRoutine(const char* pExportRountineName,
                                                    const char* pInternalRountineName,
                                                    size_t nArgs) const;

  void                writeCppR_AllocReturn(AdtFile& rFile,
                                            AdtAutoType nType,
                                            const char* pReturn) const;

  void                writeCppR_Return(AdtFile& rFile,
                                       AdtAutoType nType,
                                       const char* pReturn) const;

  void                writeCppR_CheckType(AdtFile& rFile,
                                          AdtAutoType nType,
                                          const char* pVar) const;

  void                writeCppVarCheckType(AdtFile& rFile,
                                           const char* pName,
                                           AdtAutoType nType,
                                           int nDimensions = 0,
                                           const char* pExtraArgs = 0) const;

  void                writeCppR_CheckInstance(AdtFile& rFile,
                                              const char* pR_TypeName) const;

  void                writeCppR_GetterAndSetter(AdtFile& rFile,
                                                const char* pName,
                                                const char* pClassName,
                                                const char* pAliasName,
                                                const char* pR_TypeName,
                                                bool bScalar) const;

  void                writeCppR_InterfaceDeclMethods(AdtFile& rFile,
                                                     const char* pName,
                                                     const AdtAutoAttributePtrList& rArgumentList) const;

  void                writeCppR_InterfaceDeclGlobals(AdtFile& rFile,
                                                     const char* pName,
                                                     const AdtAutoAttributePtrList& rArgumentList,
                                                     const char* pAliasName) const;

  void                writeCppR_InterfaceImplMethods(AdtFile& rFile,
                                                     const char* pName,
                                                     AdtAutoType nType,
                                                     const AdtAutoAttributePtrList& rArgumentList,
                                                     const char* pClassName,
                                                     const char* pAliasName,
                                                     const char* pR_TypeName) const;

  void                writeCppR_InterfaceImplGlobals(AdtFile& rFile,
                                                     const char* pName,
                                                     AdtAutoType nType,
                                                     const AdtAutoAttributePtrList& rArgumentList,
                                                     const char* pClassName,
                                                     const char* pAliasName,
                                                     const char* pR_TypeName) const;

  void                writeR_typeCast(AdtFile& rFile,
                                      AdtAutoType nType,
                                      const char* pVar,
                                      const char* pContext) const;
};

//  ----------------------------------------------------------------------------

inline AdtAutoHelper::AdtAutoHelper()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

inline AdtAutoHelper::AdtAutoHelper(const AdtAutoHelper& rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

inline AdtAutoHelper::~AdtAutoHelper()
{
  // Do nothing
}


//  ----------------------------------------------------------------------------
//  enum AdtAtributeType
//  ----------------------------------------------------------------------------
enum AdtAtributeType
{
  AttributeTypeScalar,
  AttributeTypeArray,
  AttributeTypeFunction,
};


//  ----------------------------------------------------------------------------
//  class AdtAutoAttribute
//  ----------------------------------------------------------------------------
class AdtAutoAttribute : public UtlReferenceCount
{
private:
  string              ClassName;
  string              Name;
  AdtAtributeType     AttributeType;
  AdtAutoType         Type;
  AdtAutoMode         Mode;
  AdtAutoDir          Dir;
  int                 Phase;
  bool                NoInterface;
  bool                WithInitialisation;
  string              FileName;
  int                 LineNumber;

protected:
  virtual void        writeDelphiVarCheckType(AdtFile& rFile,
                                              bool bPrefix,
                                              bool bInConstructor) const = 0;

  virtual void        writeDelphiVarDeclaration(AdtFile& rFile,
                                                bool bConstructor,
                                                bool bPrependSeperator) const = 0;

  virtual void        writeDelphiVarInitialisation(AdtFile& rFile,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pClassName,
                                                   bool bWithTranslation) const = 0;

  virtual void        writeDelphiVarReturn(AdtFile& rFile,
                                           const char* pClassName) const = 0;

  virtual void        writeDelphiVarDestroy(AdtFile& rFile) const = 0;

  virtual void        writeDelphiDeclLibInterfaceMethods(AdtFile& rFile) const;

  virtual void        writeDelphiDeclLibInterfaceGlobals(AdtFile& rFile, const char* pAliasName) const;

  virtual void        writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const = 0;

  virtual void        writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const = 0;

  virtual void        writeCppVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const = 0;

  virtual void        writeCppVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const = 0;

  virtual void        writeCppVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const = 0;

  virtual void        writeCppVarReturn(AdtFile& rFile,
                                        const char* pClassName) const = 0;

  virtual void        writeCppVarDestroy(AdtFile& rFile) const = 0;

  virtual void        writeCppDeclLibInterfaceMethods(AdtFile& rFile) const;

  virtual void        writeCppDeclLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pAliasName) const;

  virtual void        writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const = 0;

  virtual void        writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const = 0;

  const char*         delphiType(int nDimensions) const;
  const char*         delphiConstructorType() const;
  const char*         delphiType() const;
  const char*         cppType(int nDimensions) const;
  const char*         cppType() const;
  const char*         R_Type() const;
  const char*         R_AccessType() const;
  const char*         R_CheckType(bool bIsCpp) const;

  void                writeDelphiR_Return(AdtFile& rFile, const char* pReturn) const;
  void                writeDelphiR_CheckType(AdtFile& rFile, const char* pVar) const;

  void                writeDelphiR_GetterAndSetter(AdtFile& rFile,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const;

  void                writeCppR_Return(AdtFile& rFile, const char* pReturn) const;
  void                writeCppR_CheckType(AdtFile& rFile, const char* pVar) const;

  void                writeCppR_GetterAndSetter(AdtFile& rFile,
                                                const char* pClassName,
                                                const char* pAliasName,
                                                const char* pR_TypeName) const;

public:
  AdtAutoAttribute(const char* pName,
                   const char* pClassName,
                   AdtAtributeType nAttributeType,
                   AdtAutoType nType,
                   AdtAutoMode nMode,
                   AdtAutoDir nDir,
                   int nPhase,
                   bool bNoInterface,
                   bool bWithInitialisation,
                   const char* pFileName,
                   int nLineNumber);

  AdtAutoAttribute(const AdtAutoAttribute& rCopy);
  virtual ~AdtAutoAttribute();

  static AdtAutoType  fortranTypeToAutoType(const char* pType);
  static bool         addMapEntry(AdtStringByStringMap& rMap, const char* pKey, const char* pEntry);

  const string&       className() const;
  const string&       name() const;
  AdtAtributeType     attributeType() const;
  AdtAutoType         type() const;
  AdtAutoMode         mode() const;
  AdtAutoDir          dir() const;
  int                 phase() const;
  bool                noInterface() const;
  bool                withInitialisation() const;
  const string&       fileName() const;
  int                 lineNumber() const;

  virtual int         dimensions() const = 0;

  virtual bool        isScalar() const = 0;
  virtual bool        isRagged() const = 0;
  virtual bool        strictlyBefore(int nPhase) const = 0;
  virtual bool        checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap = 0) const = 0;
  virtual bool        checkSize(const string& rMustMatchSize) const = 0;

  void                writeVarCheckType(AdtFile& rFile,
                                        AdtSourceFileType nDestType,
                                        bool bPrefix,
                                        bool bInConstructor) const;

  void                writeVarDeclaration(AdtFile& rFile,
                                          AdtSourceFileType nDestType,
                                          bool bConstructor,
                                          bool bPrependSeperator) const;

  void                writeVarInitialisation(AdtFile& rFile,
                                             AdtSourceFileType nDestType,
                                             AdtStringByStringMap& rLocalsMap,
                                             const char* pClassName,
                                             bool bWithTranslation) const;

  void                writeVarReturn(AdtFile& rFile,
                                     AdtSourceFileType nDestType,
                                     const char* pClassName) const;

  void                writeVarDestroy(AdtFile& rFile,
                                      AdtSourceFileType nDestType) const;

  void                writeDeclLibInterfaceMethods(AdtFile& rFile,
                                                   AdtSourceFileType nDestType) const;

  void                writeDeclLibInterfaceGlobals(AdtFile& rFile,
                                                   AdtSourceFileType nDestType,
                                                   const char* pAliasName) const;

  void                writeImplLibInterfaceMethods(AdtFile& rFile,
                                                   AdtSourceFileType nDestType,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const;

  void                writeImplLibInterfaceGlobals(AdtFile& rFile,
                                                   AdtSourceFileType nDestType,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const;

  virtual void        writeRInterface(AdtFile& rFile,
                                      const char* pClassName,
                                      const char* pAliasName) const = 0;
};

//  ----------------------------------------------------------------------------

inline const string& AdtAutoAttribute::className() const
{
  return (ClassName);
}

//  ----------------------------------------------------------------------------

inline const string& AdtAutoAttribute::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline AdtAtributeType AdtAutoAttribute::attributeType() const
{
  return (AttributeType);
}

//  ----------------------------------------------------------------------------

inline AdtAutoType AdtAutoAttribute::type() const
{
  return (Type);
}

//  ----------------------------------------------------------------------------

inline AdtAutoMode AdtAutoAttribute::mode() const
{
  return (Mode);
}

//  ----------------------------------------------------------------------------

inline AdtAutoDir AdtAutoAttribute::dir() const
{
  return (Dir);
}

//  ----------------------------------------------------------------------------

inline int AdtAutoAttribute::phase() const
{
  return (Phase);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoAttribute::noInterface() const
{
  return (NoInterface);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoAttribute::withInitialisation() const
{
  return (WithInitialisation);
}

//  ----------------------------------------------------------------------------

inline const string& AdtAutoAttribute::fileName() const
{
  return (FileName);
}

//  ----------------------------------------------------------------------------

inline int AdtAutoAttribute::lineNumber() const
{
  return (LineNumber);
}


//  ----------------------------------------------------------------------------
//  class AdtAutoScalar
//  ----------------------------------------------------------------------------
class AdtAutoScalar : public AdtAutoAttribute
{
private:

protected:
  virtual void        writeDelphiVarCheckType(AdtFile& rFile,
                                              bool bPrefix,
                                              bool bInConstructor) const;

  virtual void        writeDelphiVarDeclaration(AdtFile& rFile,
                                                bool bConstructor,
                                                bool bPrependSeperator) const;

  virtual void        writeDelphiVarInitialisation(AdtFile& rFile,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pClassName,
                                                   bool bWithTranslation) const;

  virtual void        writeDelphiVarReturn(AdtFile& rFile,
                                           const char* pClassName) const;

  virtual void        writeDelphiVarDestroy(AdtFile& rFile) const;

  virtual void        writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeCppVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const;

  virtual void        writeCppVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const;

  virtual void        writeCppVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const;

  virtual void        writeCppVarReturn(AdtFile& rFile,
                                        const char* pClassName) const;

  virtual void        writeCppVarDestroy(AdtFile& rFile) const;

  virtual void        writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

  virtual void        writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

public:
  AdtAutoScalar(const char* pName,
                const char* pClassName,
                AdtAutoType nType,
                AdtAutoMode nMode,
                AdtAutoDir nDir,
                int nPhase,
                bool bNoInterface,
                bool bWithInitialisation,
                const char* pFileName,
                int nLineNumber);

  AdtAutoScalar(const AdtAutoScalar& rCopy);
  virtual ~AdtAutoScalar();

  virtual int         dimensions() const;

  virtual bool        isScalar() const;
  virtual bool        isRagged() const;
  virtual bool        strictlyBefore(int nPhase) const;
  virtual bool        checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap = 0) const;
  virtual bool        checkSize(const string& rMustMatchSize) const;

  virtual void        writeRInterface(AdtFile& rFile,
                                      const char* pClassName,
                                      const char* pAliasName) const;
};


//  ----------------------------------------------------------------------------
//  forward declaration
//  ----------------------------------------------------------------------------
class AdtAutoArray;


//  ----------------------------------------------------------------------------
//  class AdtAutoArrayPlanInfo
//  ----------------------------------------------------------------------------
//  This class is used to manage the creation of plans by automation code
//  ----------------------------------------------------------------------------
class AdtAutoArrayPlanInfo
{
private:
  const AdtAutoArray* Array;
  string              Plan;
  string              Key;
  bool                Initialised;

public:
  AdtAutoArrayPlanInfo();

  AdtAutoArrayPlanInfo(const AdtAutoArray* pArray,
                       const char* pPlan,
                       bool bInitialised);

  AdtAutoArrayPlanInfo(const AdtAutoArrayPlanInfo& rCopy);

  virtual ~AdtAutoArrayPlanInfo();

  const AdtAutoArray* array() const;
  const string&       plan() const;
  const string&       key() const;
  bool                inClass(const char* pClassName) const;
  bool                initialised() const;

  void                initialise();

  AdtAutoArrayPlanInfo& operator = (const AdtAutoArrayPlanInfo& rCopy);
};

//  ----------------------------------------------------------------------------

inline const AdtAutoArray* AdtAutoArrayPlanInfo::array() const
{
  return (Array);
}

//  ----------------------------------------------------------------------------

inline const string& AdtAutoArrayPlanInfo::plan() const
{
  return (Plan);
}

//  ----------------------------------------------------------------------------

inline const string& AdtAutoArrayPlanInfo::key() const
{
  return (Key);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoArrayPlanInfo::initialised() const
{
  return (Initialised);
}

//  ----------------------------------------------------------------------------

inline void AdtAutoArrayPlanInfo::initialise()
{
  Initialised = true;
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtAutoArrayPlanInfo by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtAutoArrayPlanInfo>                         AdtAutoArrayPlanInfoStringPair;
typedef std::map<string, AdtAutoArrayPlanInfo, string_less>                   AdtAutoArrayPlanInfoByStringMap;
typedef std::map<string, AdtAutoArrayPlanInfo, string_less>::iterator         AdtAutoArrayPlanInfoByStringMapIter;
typedef std::map<string, AdtAutoArrayPlanInfo, string_less>::const_iterator   AdtAutoArrayPlanInfoByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  class AdtAutoArray
//  ----------------------------------------------------------------------------
class AdtAutoArray : public AdtAutoAttribute
{
private:
  int                                     Dimensions;
  mutable int                             LastScalar;
  mutable int                             SmallestIndex;
  mutable bool                            IsRagged;
  mutable bool                            RefreshSizeSpecification;
  mutable bool                            HasLocalDependencies;
  mutable string                          SizeSpecification;
  mutable AdtIntByStringMap               ArrayDependencies;
  mutable AdtIntByStringMap               ArrayDependancyLocal;
  AdtStringByIntMap                       ArrayLowerBoundByIndex;
  AdtStringByIntMap                       ArrayUpperBoundByIndex;
  static AdtAutoArrayPlanInfoByStringMap  ArrayPlanInfoMap;
  static int                              ArrayPlanCount;
  static const int                        NO_INDEX;

protected:
  bool                getPlan(bool bCreate,
                              string& rPlanName) const;

  void                updateMustMatchSize(string& rMustMatchSize,
                                          const string& rLastLowerBoundExpression,
                                          const string& rLastUpperBoundExpression) const;

  void                checkDependencies(bool& bOk,
                                        AdtStringList& rDependencyList,
                                        const AdtStringByIntMap& rLowerBoundMap,
                                        const AdtStringByIntMap& rUpperBoundMap,
                                        const AdtAutoAttributePtrByStringMap& rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap,
                                        const AdtExpressionAdditive* pRootLower,
                                        const AdtExpressionAdditive* pRootUpper,
                                        int nIndex,
                                        int& nLastScalar,
                                        int& nSmallestIndex) const;

  void                arrayBoundsArguments(string& rArguments,
                                           bool bInConstructor) const;

  void                arraySizesAndBaseIndices(string& rArraySizes,
                                               string& rBaseIndices) const;

  void                writeDelphiAllocSizeSpec(AdtFile& rFile,
                                               int nStartIndex,
                                               int nEndIndex) const;

  void                write_ZERO(AdtFile& rFile) const;

  void                writePlanBasesAndSizes(AdtFile& rFile,
                                             int nStartIndex,
                                             int nEndIndex) const;

  void                writeBuildRaggedArrayPlan(AdtFile& rFile,
                                                AdtSourceFileType nDestType,
                                                AdtStringByStringMap& rLocalsMap,
                                                int nIndex,
                                                string& sLoopIndexing,
                                                string& sLastPlan,
                                                const char* pRaggedContext = 0) const;

  virtual void        writeDelphiVarCheckType(AdtFile& rFile,
                                              bool bPrefix,
                                              bool bInConstructor) const;

  virtual void        writeDelphiVarDeclaration(AdtFile& rFile,
                                                bool bConstructor,
                                                bool bPrependSeperator) const;

  virtual void        writeDelphiVarInitialisation(AdtFile& rFile,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pClassName,
                                                   bool bWithTranslation) const;

  void                writeDelphiCreatePlan(AdtFile& rFile,
                                            AdtStringByStringMap& rLocalsMap,
                                            const char* pPlan) const;

  void                writeDelphiCopyPlan(AdtFile& rFile,
                                          const char* pPlan) const;

  virtual void        writeDelphiVarReturn(AdtFile& rFile,
                                           const char* pClassName) const;

  virtual void        writeDelphiVarDestroy(AdtFile& rFile) const;

  virtual void        writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeCppVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const;

  virtual void        writeCppVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const;

  virtual void        writeCppVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const;

  void                writeCppCreatePlan(AdtFile& rFile,
                                         AdtStringByStringMap& rLocalsMap,
                                         const char* pPlan) const;

  void                writeCppCopyPlan(AdtFile& rFile,
                                       const char* pPlan) const;

  virtual void        writeCppVarReturn(AdtFile& rFile,
                                        const char* pClassName) const;

  virtual void        writeCppVarDestroy(AdtFile& rFile) const;

  virtual void        writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

  virtual void        writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

public:
  AdtAutoArray(const char* pName,
               const char* pClassName,
               AdtAutoType nType,
               AdtAutoMode nMode,
               AdtAutoDir nDir,
               int nPhase,
               bool bNoInterface,
               bool bWithInitialisation,
               int nDimensions,
               const char* pFileName,
               int nLineNumber);

  AdtAutoArray(const AdtAutoArray& rCopy);
  virtual ~AdtAutoArray();

  static void         flushArrayPlanInfo();

  static void         writeCreatePlans(AdtFile& rFile,
                                       AdtSourceFileType nDestType,
                                       const char* pClassName,
                                       AdtStringByStringMap& rLocalsMap);

  static void         writeCopyPlans(AdtFile& rFile,
                                     AdtSourceFileType nDestType,
                                     const char* pClassName);

  void                addArrayIndex(const char* sArrayLowerBound,
                                    const char* sArrayUpperBound,
                                    int nIndex);

  const string&       sizeSpecification() const;

  virtual int         dimensions() const;

  virtual bool        isScalar() const;
  virtual bool        isRagged() const;
  virtual bool        strictlyBefore(int nPhase) const;
  virtual bool        checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap = 0) const;
  virtual bool        checkSize(const string& rMustMatchSize) const;

  virtual void        writeRInterface(AdtFile& rFile,
                                      const char* pClassName,
                                      const char* pAliasName) const;

  static void         writeArrayPlans(AdtFile& rFile,
                                      AdtSourceFileType nDestType,
                                      const char* pClassName);
};

//  ----------------------------------------------------------------------------

inline const string& AdtAutoArray::sizeSpecification() const
{
  return (SizeSpecification);
}


//  ----------------------------------------------------------------------------
//  class AdtAutoFunction
//  ----------------------------------------------------------------------------
class AdtAutoFunction : public AdtAutoAttribute
{
private:
  AdtAutoAttributePtrList         ArgumentList;
  AdtAutoAttributePtrByStringMap  ArgumentMap;

protected:
  virtual void        writeDelphiVarCheckType(AdtFile& rFile,
                                              bool bPrefix,
                                              bool bInConstructor) const;

  virtual void        writeDelphiVarDeclaration(AdtFile& rFile,
                                                bool bConstructor,
                                                bool bPrependSeperator) const;

  virtual void        writeDelphiVarInitialisation(AdtFile& rFile,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pClassName,
                                                   bool bWithTranslation) const;

  virtual void        writeDelphiVarReturn(AdtFile& rFile,
                                           const char* pClassName) const;

  virtual void        writeDelphiVarDestroy(AdtFile& rFile) const;

  virtual void        writeDelphiDeclLibInterfaceMethods(AdtFile& rFile) const;

  virtual void        writeDelphiDeclLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pAliasName) const;

  virtual void        writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const;

  virtual void        writeCppVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const;

  virtual void        writeCppVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const;

  virtual void        writeCppVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const;

  virtual void        writeCppVarReturn(AdtFile& rFile,
                                        const char* pClassName) const;

  virtual void        writeCppVarDestroy(AdtFile& rFile) const;

  virtual void        writeCppDeclLibInterfaceMethods(AdtFile& rFile) const;

  virtual void        writeCppDeclLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pAliasName) const;

  virtual void        writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

  virtual void        writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const;

public:
  AdtAutoFunction(const char* pName,
                  const char* pClassName,
                  AdtAutoType nType,
                  AdtAutoDir nDir,
                  const char* pFileName,
                  int nLineNumber);

  AdtAutoFunction(const AdtAutoFunction& rCopy);
  virtual ~AdtAutoFunction();

  virtual int         dimensions() const;

  virtual bool        isScalar() const;
  virtual bool        isRagged() const;
  virtual bool        strictlyBefore(int nPhase) const;
  virtual bool        checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap = 0) const;
  virtual bool        checkSize(const string& rMustMatchSize) const;

  virtual void        writeRInterface(AdtFile& rFile,
                                      const char* pClassName,
                                      const char* pAliasName) const;

  AdtAutoScalar*      addScalar(const char* pName,
                                AdtAutoType nType,
                                AdtAutoDir nDir,
                                const char* pFileName,
                                int nLineNumber);

  AdtAutoArray*       addArray(const char* pName,
                               AdtAutoType nType,
                               AdtAutoDir nDir,
                               int nDimensions,
                               const char* pFileName,
                               int nLineNumber);

  void                reset();
};

//  ----------------------------------------------------------------------------

inline int AdtAutoFunction::dimensions() const
{
  return (0);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoFunction::isScalar() const
{
  return (true);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoFunction::isRagged() const
{
  return (false);
}


//  ----------------------------------------------------------------------------
//  class AdtAutoClass
//  ----------------------------------------------------------------------------
class AdtAutoClass : public UtlReferenceCount
{
private:
  AdtSizeTBySizeTMap                InheritedMap;
  AdtAutoAttributePtrByStringMap    AttributeByNameMap;
  AdtAutoAttributePtrByIntMultimap  AttributeByPhaseMap;
  AdtIntByIntMap                    DefinedPhasesMap;
  AdtStringList                     ArgumentList;
  AdtAutoMode                       Mode;
  bool                              NoInterface;
  int                               Phase;
  int                               MaxPhase;
  mutable int                       MaxCounter;
  string                            ClassName;
  string                            AliasName;
  string                            ParentClassName;
  string                            R_TypeName;
  string                            ParentConstructorCallArgsFileName;

  static AdtAutoClassPtrByStringMap ClassMap;
  static AdtAutoClass*              CurrentClass;
  static bool                       AddExitHandler;
  static bool                       Enabled;
  static bool                       AttributeDefsEnabled;
  static bool                       IncludeDisabled;
  static string                     LibName;
  static string                     RegistrationCodeBuffer;
  static AdtFile                    RegistrationCodeFile;
  static string                     ExternalsCodeBuffer;
  static AdtFile                    ExternalsCodeFile;

protected:
  void                  inherit(const AdtAutoAttribute* pAttribute);
  bool                  isInherited(const AdtAutoAttribute* pAttribute) const;

  void                  createFileName(string& rFileName,
                                       const char* pFileNameBase,
                                       AdtSourceFileType nDestType) const;

  void                  appendFileToStringList(AdtStringList& rStringList,
                                               const char* pDestFolder,
                                               const char* pFileNameBase,
                                               AdtSourceFileType nDestType) const;

  void                  writeIncrementalCompileFile(const string& sBufferToWrite,
                                                    AdtSourceFileType nDestType,
                                                    const char* pDestFolder,
                                                    const char* pPrefix,
                                                    int nClassNumber) const;

  void                  readIncrementalCompileFiles(AdtStringList& rStringList,
                                                    AdtSourceFileType nDestType,
                                                    const char* pDestFolder,
                                                    const char* pPrefix,
                                                    int nClassNumber) const;

  bool                  openFile(AdtFile& rFile,
                                 const char* pDestFolder,
                                 const char* pFileName) const;

  bool                  openFile(AdtFile& rFile,
                                 const char* pDestFolder,
                                 const char* pFileNameBase,
                                 AdtSourceFileType nDestType) const;

  void                  writeConstructorDecl(AdtFile& rFile,
                                             AdtSourceFileType nDestType,
                                             const char* pConstructorClassName) const;

  void                  writeConstructorImpl(AdtFile& rFile,
                                             AdtSourceFileType nDestType,
                                             const char* pConstructorClassName) const;

  void                  writeCommonR_Code(AdtFile& rFile) const;

  bool                  writeConstructorArgsFile(AdtSourceFileType nDestType,
                                                 const char* pDestFolder,
                                                 bool bCall) const;

  bool                  writeConstructorLocalsFile(AdtSourceFileType nDestType,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pDestFolder) const;

  bool                  writeConstructorPhaseFiles(AdtSourceFileType nDestType,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pDestFolder) const;

  bool                  writeArrayPlansInitFile(AdtSourceFileType nDestType,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pDestFolder) const;

  bool                  writeArrayPlansCopyFile(AdtSourceFileType nDestType,
                                                const char* pDestFolder) const;

  bool                  writeDeclLibInterfaceMethodsFile(AdtSourceFileType nDestType,
                                                         const char* pDestFolder) const;

  bool                  writeDeclLibInterfaceGlobalsFile(AdtSourceFileType nDestType,
                                                         const char* pDestFolder) const;

  bool                  writeDeclLibInterfaceConstructorFile(AdtSourceFileType nDestType,
                                                             const char* pDestFolder,
                                                             const char* pConstructorClassName) const;

  bool                  writeImplLibInterfaceConstructorFile(AdtSourceFileType nDestType,
                                                             const char* pDestFolder,
                                                             const char* pConstructorClassName) const;

  bool                  writeImplLibInterfaceMethodsFile(AdtSourceFileType nDestType,
                                                         const char* pDestFolder) const;

  bool                  writeImplLibInterfaceGlobalsFile(AdtSourceFileType nDestType,
                                                         const char* pDestFolder) const;

  bool                  writeImplLibRegistrationFile(AdtSourceFileType nDestType,
                                                     const char* pDestFolder,
                                                     int nClassNumber) const;

  bool                  writeArrayPlansFile(AdtSourceFileType nDestType,
                                            const char* pDestFolder) const;

  bool                  writeRInterfaceFile(const char* pDestFolder) const;

  bool                  checkDependencies() const;

  void                  buildParentConstructorCallArgsFileName(string& rFileName) const;

  static void           writeIncludeStatement(AdtFile& rFile,
                                              const char* pWhich,
                                              AdtSourceFileType nDestType,
                                              const char* pClassName);

  static void           flushAutoClasses();

public:
  AdtAutoClass();
  virtual ~AdtAutoClass();

  static bool           addLibName(const char* pLibName,
                                   const char* pFileName,
                                   int nLineNumber);

  static bool           addClassNameAndAlias(const char* pClassName,
                                             const char* pAlias,
                                             const char* pParentClassName,
                                             const char* pFileName,
                                             int nLineNumber);

  static bool           setModeAndPhase(int nMode,
                                        int nPhase,
                                        bool bNoInterface,
                                        const char* pFileName,
                                        int nLineNumber);

  static void           includeDisableAutomation(bool bDisable);
  static void           enableAutomation(bool bEnable, bool bWithAttributeDefsEnabled);
  static bool           automationEnabled();
  static bool           attributeDefsEnabled();
  static void           clearRegistrationCode();
  static AdtFile&       registrationCodeFile();
  static AdtFile&       externalsCodeFile();

  static void           exportConstructorArgsFiles(AdtSourceFileType nDestType,
                                                   const char* pDestFolder);

  static void           exportAutomationFiles(AdtSourceFileType nDestType,
                                              const char* pDestFolder,
                                              const char* pConstructorClassName,
                                              int nClassNumber);

  static bool           buildClassConstructor(AdtStringList& rConstructorList,
                                              const char* pClassName,
                                              const char* pParentClassName,
                                              AdtSourceFileType nAsFileType);

  static void           writeInterfaceMethodsDeclInclude(AdtFile& rFile,
                                                         AdtSourceFileType nDestType,
                                                         const char* pClassName);

  static void           writeInterfaceMethodsImplInclude(AdtFile& rFile,
                                                         AdtSourceFileType nDestType,
                                                         const char* pClassName);

  static void           writeInterfaceGlobalsDeclInclude(AdtFile& rFile,
                                                         AdtSourceFileType nDestType,
                                                         const char* pClassName);

  static void           writeInterfaceGlobalsImplInclude(AdtFile& rFile,
                                                         AdtSourceFileType nDestType,
                                                         const char* pClassName);

  static void           writeConstructorDeclInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName);

  static void           writeConstructorImplInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName);

  static AdtAutoClass*  findClass(const char* pClassName);

  static AdtAutoClass*  currentClass();

  void                  reset();

  void                  mode(AdtAutoMode nMode,
                             const char* pFileName,
                             int nLineNumber);

  AdtAutoMode           mode() const;

  void                  phase(int nPhase,
                              const char* pFileName,
                              int nLineNumber);

  int                   phase() const;

  void                  noInterface(bool bNoInterface,
                                    const char* pFileName,
                                    int nLineNumber);

  bool                  noInterface() const;

  void                  classNameAndAlias(const char* pClassName,
                                          const char* pAlias = 0);

  AdtAutoScalar*        addScalar(const char* pName,
                                  AdtAutoType nType,
                                  AdtAutoDir nDir,
                                  const char* pFileName,
                                  int nLineNumber);

  AdtAutoArray*         addArray(const char* pName,
                                 AdtAutoType nType,
                                 AdtAutoDir nDir,
                                 int nDimensions,
                                 const char* pFileName,
                                 int nLineNumber);

  AdtAutoFunction*      addFunction(const char* pName,
                                    AdtAutoType nType,
                                    AdtAutoDir nDir,
                                    bool bIsVirtual,
                                    const char* pFileName,
                                    int nLineNumber);

  bool                  writeConstructorArgsFiles(AdtSourceFileType nDestType,
                                                  const char* pDestFolder) const;

  bool                  writeAutomationFiles(AdtSourceFileType nDestType,
                                             const char* pDestFolder,
                                             const char* pConstructorClassName,
                                             int nClassNumber) const;

  void                  inheritFrom(const AdtAutoClass* pParentClass);
};

//  ----------------------------------------------------------------------------

inline AdtAutoMode AdtAutoClass::mode() const
{
  return (Mode);
}

//  ----------------------------------------------------------------------------

inline int AdtAutoClass::phase() const
{
  return (Phase);
}

//  ----------------------------------------------------------------------------

inline bool AdtAutoClass::noInterface() const
{
  return (NoInterface);
}


#endif //__ADTAUTOMATE_HPP
