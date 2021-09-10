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
//    AdtMake.hpp
//
//  Purpose:
//    This file includes declarations of classes used to implement the make
//    system for ADT.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTMAKE_HPP
#define __ADTMAKE_HPP


#include "adtdelphi.hpp"
#include "adtfortran.hpp"


#ifdef __cplusplus
  #define C_FUNCTION  extern "C"
#else
  #define C_FUNCTION
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION void         make_AddInclude(const char* pFileName);

C_FUNCTION const char*  make_AllocString(const char* pTokenText);
C_FUNCTION void         make_LogText(const char* pTokenText, int nLineNumber);

C_FUNCTION void         make_MakeCommandOpen();
C_FUNCTION void         make_MakeCommandClose();

C_FUNCTION void         make_PathsOpen();
C_FUNCTION void         make_PathsClose();
C_FUNCTION void         make_SwitchesOpen();
C_FUNCTION void         make_SwitchesClose();
C_FUNCTION void         make_BlackBoxOpen();
C_FUNCTION void         make_BlackBoxClose();
C_FUNCTION void         make_SourceFilesOpen();
C_FUNCTION void         make_SourceFilesClose();
C_FUNCTION void         make_WorkingDirectory(const char* pString);
C_FUNCTION void         make_IncludeDirectory(const char* pString);
C_FUNCTION void         make_SourceOptionsFile(const char* pString, int nType);
C_FUNCTION void         make_FortranIncludeFilesOpen();
C_FUNCTION void         make_FortranIncludeFilesClose();

C_FUNCTION void         make_ClassOpen(const char* pNewClassName,
                                       const char* pParentClassName,
                                       const char* pSourceFile,
                                       const char* pSourceFile2,
                                       const char* pOutputFile,
                                       const char* pOutputFile2);

C_FUNCTION void         make_ClassClose();

C_FUNCTION void         make_ClassBoundsCheckOpen();
C_FUNCTION void         make_ClassBoundsCheckClose();

C_FUNCTION void         make_CommandVarOpen();
C_FUNCTION void         make_CommandOutVarOpen();
C_FUNCTION void         make_CommandOpClose();
C_FUNCTION void         make_CommandClose();

C_FUNCTION void         make_CommandUser(const char* pString);
C_FUNCTION void         make_CommandPre(const char* pString);
C_FUNCTION void         make_CommandPost(const char* pString);
C_FUNCTION void         make_CommandPragmas(const char* pString);
C_FUNCTION void         make_CommandMode(const char* pString);
C_FUNCTION void         make_CommandFunction(const char* pString);
C_FUNCTION void         make_CommandBoundsCheckOpen();
C_FUNCTION void         make_CommandBoundsCheckClose();

C_FUNCTION void         make_PushString(const char* pString);


#ifdef __cplusplus


#include "adtparser.hpp"
#include "adtutils.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtMakeClass;
class AdtMakeCommand;


//  ----------------------------------------------------------------------------
//  AdtExePath class
//  ----------------------------------------------------------------------------
//  Global var class holding path to folder the ADT executable resides in
//  ----------------------------------------------------------------------------
class AdtExePath
{
private:
  static string   ExePath;

public:
  AdtExePath();
  AdtExePath(const char* pExeFileAndPath);
  virtual ~AdtExePath();

  operator const char* () const;
};

//  ----------------------------------------------------------------------------

inline AdtExePath::AdtExePath()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

inline AdtExePath::~AdtExePath()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

inline AdtExePath::operator const char* () const
{
  return (ExePath.c_str());
}


//  ----------------------------------------------------------------------------
//  AdtMakeIncremental class
//  ----------------------------------------------------------------------------
//  Utility class to help implement incremental building of ADT projects. This
//  class is a placeholder for common operations used to manage the incremental
//  build process
//  ----------------------------------------------------------------------------
class AdtMakeIncremental
{
private:
  static bool       Build;
  string            CheckFileName;
  char*             ReferenceString;
  size_t            ReferenceLength;
  string            CheckString;
  string            NewMethodsAndAttributesString;

protected:
  bool              shouldBuild() const;
  void              close(bool bWriteCheckString);

public:
  AdtMakeIncremental();
  virtual ~AdtMakeIncremental();

  bool              open(const char* pBuildCheckFileAndPath);
  void              close();

  bool              checkText(const char* pText);
  bool              checkList(const AdtStringList& rList);
  bool              checkMap(const AdtIntByStringMap& rMap);
  bool              checkFile(const char* pFilenameAndPath);

  void              updateNewMethodsAndAttributes(const char* pParentClassName,
                                                  AdtStringByStringMap& NewMethodMap,
                                                  AdtStringList& NewMethodList,
                                                  AdtStringByStringMap& NewAttributesMap,
                                                  AdtStringList& NewAttributesList);

  void              forceRebuild();

  static bool       build();
  static void       build(bool bMarkForBuild);
};

//  ----------------------------------------------------------------------------

inline bool AdtMakeIncremental::build()
{
  return (Build);
}

//  ----------------------------------------------------------------------------

inline void AdtMakeIncremental::build(bool bMarkForBuild)
{
  Build = bMarkForBuild;
}


//  ----------------------------------------------------------------------------
//  AdtMakeCommandOperation class
//  ----------------------------------------------------------------------------
class AdtMakeCommandOperation
{
private:
  string          FunctionName;
  string          UserOptions;
  string          PreCommand;
  string          PostCommand;
  string          Pragmas;
  string          Mode;
  mutable string  VarSuffix;
  mutable string  SubSuffix;
  mutable string  ModuleSuffix;
  mutable string  BaseSubSuffix;
  mutable string  CopySubSuffix;
  AdtStringList   Vars;
  AdtStringList   OutVars;

protected:
  void            executeCommandLine(const AdtMakeCommand& rParent,
                                     const string& rCommandline,
                                     const char* pSourceFile,
                                     const char* pTypeMsg) const;

public:
  AdtMakeCommandOperation();
  AdtMakeCommandOperation(const AdtMakeCommandOperation& rCopy);
  virtual ~AdtMakeCommandOperation();

  void            reset();

  bool            isNull() const;
  bool            shouldBuild(AdtMakeIncremental& rBuildCheck) const;

  void            functionName(const char* pFunctionName);
  void            userOptions(const char* pUserOptions);
  void            preCommand(const char* pCommandText);
  void            postCommand(const char* pCommandText);
  void            pragmas(const char* pPragmas);
  void            mode(const char* pMode);
  void            vars(const AdtStringList& rVars);
  void            outVars(const AdtStringList& rOutVars);

  bool            execute(const AdtMakeCommand& rParent,
                          AdtFortranExecutableProgram* pWorkingRoot,
                          AdtStringList& rNewFunctionsList,
                          AdtStringList& rTranslateFunctionsFromList,
                          AdtStringList& rTranslateFunctionsToList,
                          string& rOutputFileName,
                          const char* pSourceFile,
                          const char* pBlackBoxFile,
                          const char* pClassName,
                          int nIteration) const;

  const string&   qualifiedFunctionName(string& rFunctionName,
                                        const char* pClassName) const;

  const string&   functionName() const;
  const string&   userOptions() const;
  const string&   preCommand() const;
  const string&   postCommand() const;
  const string&   pragmas() const;
  bool            pragma(const char* pPragmas) const;
  const string&   mode() const;
  const string&   varSuffix() const;
  const string&   subSuffix() const;
  const string&   moduleSuffix() const;
  const string&   baseSubSuffix() const;
  const string&   copySubSuffix() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtMakeCommandOperation::isNull() const
{
  return (FunctionName.length() == 0);
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::functionName(const char* pFunctionName)
{
  if (pFunctionName != 0)
  {
    FunctionName = pFunctionName;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::userOptions(const char* pUserOptions)
{
  if (pUserOptions != 0)
  {
    UserOptions = pUserOptions;
    UserOptions.trim("\"");
    UserOptions.trim("\'");
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::preCommand(const char* pCommandText)
{
  if (pCommandText != 0)
  {
    PreCommand = pCommandText;
    PreCommand.trim("\"");
    PreCommand.trim("\'");
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::postCommand(const char* pCommandText)
{
  if (pCommandText != 0)
  {
    PostCommand = pCommandText;
    PostCommand.trim("\"");
    PostCommand.trim("\'");
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::pragmas(const char* pPragmas)
{
  if (pPragmas != 0)
  {
    Pragmas = pPragmas;
    Pragmas.trim("\"");
    Pragmas.trim("\'");
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::mode(const char* pMode)
{
  if (pMode != 0)
  {
    Mode = pMode;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::vars(const AdtStringList& rVars)
{
  Vars = rVars;
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommandOperation::outVars(const AdtStringList& rOutVars)
{
  OutVars = rOutVars;
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::functionName() const
{
  return (FunctionName);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::userOptions() const
{
  return (UserOptions);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::preCommand() const
{
  return (PreCommand);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::postCommand() const
{
  return (PostCommand);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::pragmas() const
{
  return (Pragmas);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::mode() const
{
  return (Mode);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::varSuffix() const
{
  return (VarSuffix);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::subSuffix() const
{
  return (SubSuffix);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::moduleSuffix() const
{
  return (ModuleSuffix);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::baseSubSuffix() const
{
  return (BaseSubSuffix);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommandOperation::copySubSuffix() const
{
  return (CopySubSuffix);
}


//  ----------------------------------------------------------------------------
//  List of AdtMakeCommandOperation objects
//  ----------------------------------------------------------------------------
typedef std::list<AdtMakeCommandOperation>                  AdtMakeCommandOperationList;
typedef std::list<AdtMakeCommandOperation>::iterator        AdtMakeCommandOperationListIter;
typedef std::list<AdtMakeCommandOperation>::const_iterator  AdtMakeCommandOperationListConstIter;


//  ----------------------------------------------------------------------------
//  Mappings of AdtMakeClass by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtMakeClass*>                        AdtMakeClassPtrStringPair;
typedef std::map<string, AdtMakeClass*, string_less>                  AdtMakeClassPtrByStringMap;
typedef std::map<string, AdtMakeClass*, string_less>::iterator        AdtMakeClassPtrByStringMapIter;
typedef std::map<string, AdtMakeClass*, string_less>::const_iterator  AdtMakeClassPtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtMakeClass class
//  ----------------------------------------------------------------------------
class AdtMakeClass
{
private:
  time_t                      LastModifiedTime;
  string                      ClassName;
  string                      ParentClassName;
  string                      SourceFile;
  string                      SourceHeaderFile;
  string                      OutputFile;
  string                      OutputHeaderFile;
  string                      WorkingFile;
  string                      BlackBoxFile;
  AdtIntByStringMap           IsBlackBoxMap;
  AdtSourceFileType           SourceFileType;
  AdtSourceFileType           DestFileType;
  AdtMakeCommandOperationList OperationsList;
  AdtStringList               BoundsCheckList;

protected:
  void                  reset();

  void                  makeResult(const char* pFilenameTemp,
                                   const char* pFilename,
                                   const char* pCommandBlock,
                                   const char* pCommandBlockName,
                                   const char* pPreText,
                                   const char* pPostText,
                                   const AdtStringList* pSearchPaths,
                                   const AdtStringList& rNewMethodList,
                                   const AdtStringByStringMap& rNewMethodMap);

  void                  initFiles(string& rFile,
                                  string& rHeaderFile,
                                  AdtSourceFileType& rFileType,
                                  const char* pFile,
                                  const char* pFile2);

  string                constructIncludeDirectory(const AdtMakeCommand& rMakeCommand,
                                                  const string& rRootPath) const;

public:
  AdtMakeClass();
  AdtMakeClass(const AdtMakeClass& rCopy);
  virtual ~AdtMakeClass();

  int                   make(AdtMakeCommand& rParent,
                             AdtParserPtrList& rDelphiCodeList,
                             AdtMakeClassPtrByStringMap& rWorkingMakeByClass,
                             AdtFortranExecutableProgram* pCallExpandRoot,
                             const char** pOptionsFileTexts,
                             const char** pOptionsFileNames,
                             const char* pFortranInclude,
                             AdtMakeIncremental& rBuildCheck,
                             int nClassNumber);

  void                  newMakeClass(const AdtMakeCommand& rMakeCommand,
                                     const char* pNewClassName,
                                     const char* pParentClassName,
                                     const char* pSourceFile,
                                     const char* pSourceFile2,
                                     const char* pOutputFile,
                                     const char* pOutputFile2);

  void                  addOperation(const AdtMakeCommandOperation& rOperation);

  void                  boundsCheck(const AdtStringList& rBoundsCheckList);
  const AdtStringList&  boundsCheck() const;

  void                  sourceFile(const char* pSourceFile);
  void                  sourceHeaderFile(const char* pSourceHeaderFile);
  void                  outputFile(const char* pOutputFile);
  void                  outputHeaderFile(const char* pOutputHeaderFile);

  time_t                lastModifiedTime() const;

  const string&         className() const;
  const string&         parentClassName() const;

  const string&         sourceFile() const;
  const string&         sourceHeaderFile() const;
  const string&         outputFile() const;
  const string&         outputHeaderFile() const;
  const string&         workingFile() const;
  AdtSourceFileType     sourceFileType() const;
  AdtSourceFileType     destFileType() const;

  bool                  workingFile(string& rWorkingFile, size_t nIteration) const;
  bool                  lastWorkingFile(string& rWorkingFile) const;
};

//  ----------------------------------------------------------------------------

inline void AdtMakeClass::sourceFile(const char* pSourceFile)
{
  if (pSourceFile != 0)
  {
    SourceFile = pSourceFile;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeClass::sourceHeaderFile(const char* pSourceHeaderFile)
{
  if (pSourceHeaderFile != 0)
  {
    SourceHeaderFile = pSourceHeaderFile;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeClass::outputFile(const char* pOutputFile)
{
  if (pOutputFile != 0)
  {
    OutputFile = pOutputFile;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtMakeClass::outputHeaderFile(const char* pOutputHeaderFile)
{
  if (pOutputHeaderFile != 0)
  {
    OutputHeaderFile = pOutputHeaderFile;
  }
}

//  ----------------------------------------------------------------------------

inline const AdtStringList& AdtMakeClass::boundsCheck() const
{
  return (BoundsCheckList);
}

//  ----------------------------------------------------------------------------

inline time_t AdtMakeClass::lastModifiedTime() const
{
  return (LastModifiedTime);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::className() const
{
  return (ClassName);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::parentClassName() const
{
  return (ParentClassName);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::sourceFile() const
{
  return (SourceFile);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::sourceHeaderFile() const
{
  return (SourceHeaderFile);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::outputFile() const
{
  return (OutputFile);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::outputHeaderFile() const
{
  return (OutputHeaderFile);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeClass::workingFile() const
{
  return (WorkingFile);
}

//  ----------------------------------------------------------------------------

inline AdtSourceFileType AdtMakeClass::sourceFileType() const
{
  return (SourceFileType);
}

//  ----------------------------------------------------------------------------

inline AdtSourceFileType AdtMakeClass::destFileType() const
{
  return (DestFileType);
}


//  ----------------------------------------------------------------------------
//  List of AdtMakeClass objects
//  ----------------------------------------------------------------------------
typedef std::list<AdtMakeClass>                   AdtMakeClassList;
typedef std::list<AdtMakeClass>::iterator         AdtMakeClassListIter;
typedef std::list<AdtMakeClass>::const_iterator   AdtMakeClassListConstIter;


#define NUM_SOURCE_TYPES 2


//  ----------------------------------------------------------------------------
//  AdtMakeCommand class
//  ----------------------------------------------------------------------------
class AdtMakeCommand
{
private:
  string                    WorkingDirectory;
  string                    IncludeDirectory;
  string                    SourceOptionsFile[NUM_SOURCE_TYPES];
  AdtIntByStringMap         Switches;
  AdtStringList             Paths;
  AdtStringList             BlackBoxList;
  AdtStringList             SourceFiles;
  AdtStringList             FortranIncludeFiles;
  AdtMakeClassList          ClassList;
  AdtSourceFileType         SourceFileType;

protected:
  void                      reset();
  void                      addDefaultPaths();
  void                      fixDirectory(string& rDirectory,
                                         const char* pDirectory,
                                         const char* pTypeName,
                                         bool bNoSubDirectories);

  void                      prefixDirectory(const string& rDirectory,
                                            string& rResultFileName,
                                            const char* pFileName,
                                            bool bQuote) const;

public:
  AdtMakeCommand();
  AdtMakeCommand(const AdtMakeCommand& rCopy);
  virtual ~AdtMakeCommand();

  bool                      switchDefined(const char* pSwitch) const;
  bool                      isFile(const char* pFileName) const;
  bool                      findFile(const string& rSourceFileName, string& rFileAndPath) const;

  int                       make(AdtMakeIncremental& rBuildCheck);

  void                      newMakeCommand();
  void                      addClass(const AdtMakeClass& rClass);
  void                      workingDirectory(const char* pWorkingDirectory);
  void                      includeDirectory(const char* pIncludeDirectory);
  void                      sourceOptionsFile(const char* pOptionsFile, AdtSourceFileType nType);
  void                      paths(const AdtStringList& rPaths);
  void                      switches(const AdtStringList& rSwitches);
  void                      blackBox(const AdtStringList& rBlackBoxFiles);
  void                      sourceFiles(const AdtStringList& rSourceFiles);
  void                      fortranIncludeFiles(const AdtStringList& rSourceFiles);

  void                      prefixWorkingDirectory(string& rResultFileName,
                                                   const char* pFileName,
                                                   bool bQuote) const;

  void                      prefixIncludeDirectory(string& rResultFileName,
                                                   const char* pFileName,
                                                   bool bQuote) const;

  const string&             workingDirectory() const;
  const string&             includeDirectory() const;
  const string&             sourceOptionsFile(AdtSourceFileType nType) const;
  const AdtStringList&      paths() const;
  const AdtStringList&      blackBoxList() const;

  static int                fileTypeToIndex(AdtSourceFileType nType);
  static AdtSourceFileType  sourceFileType(const string& rSourceFile);
};

//  ----------------------------------------------------------------------------

inline void AdtMakeCommand::newMakeCommand()
{
  reset();
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommand::sourceOptionsFile(const char* pOptionsFile, AdtSourceFileType nType)
{
  SourceOptionsFile[fileTypeToIndex(nType)] = pOptionsFile;
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommand::paths(const AdtStringList& rPaths)
{
  Paths = rPaths;

  addDefaultPaths();
}

//  ----------------------------------------------------------------------------

inline void AdtMakeCommand::fortranIncludeFiles(const AdtStringList& rSourceFiles)
{
  FortranIncludeFiles = rSourceFiles;
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommand::workingDirectory() const
{
  return (WorkingDirectory);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommand::includeDirectory() const
{
  return (IncludeDirectory);
}

//  ----------------------------------------------------------------------------

inline const string& AdtMakeCommand::sourceOptionsFile(AdtSourceFileType nType) const
{
  return (SourceOptionsFile[fileTypeToIndex(nType)]);
}

//  ----------------------------------------------------------------------------

inline const AdtStringList& AdtMakeCommand::paths() const
{
  return (Paths);
}

//  ----------------------------------------------------------------------------

inline const AdtStringList& AdtMakeCommand::blackBoxList() const
{
  return (BlackBoxList);
}


//  ----------------------------------------------------------------------------
//  List of AdtMakeCommand objects
//  ----------------------------------------------------------------------------
typedef std::list<AdtMakeCommand>                   AdtMakeCommandList;
typedef std::list<AdtMakeCommand>::iterator         AdtMakeCommandListIter;
typedef std::list<AdtMakeCommand>::const_iterator   AdtMakeCommandListConstIter;


//  ----------------------------------------------------------------------------
//  AdtMakeSystem class
//  ----------------------------------------------------------------------------
//  This class implements the make system for the ADT utility.
//  ----------------------------------------------------------------------------
class AdtMakeSystem : public AdtCommon
{
enum AdtOpType{VarOpType, OutVarOpType, OtherOpType};

private:
  static AdtStringList            StringList;
  static AdtStringList            IncludeList;
  static AdtMakeClass             CurrentClass;
  static AdtMakeCommand           CurrentCommand;
  static AdtMakeCommandOperation  CurrentCommandOperation;
  static AdtMakeCommandList       MakeCommandList;
  static AdtOpType                OpType;
  static AdtMakeIncremental       BuildCheck;

protected:
  static void                   updateOptions(AdtOpType nNextOpType = OtherOpType);

public:
  AdtMakeSystem();
  virtual ~AdtMakeSystem();

  static void                   parse(const char* pFilename,
                                      FILE*& yyMakein,
                                      int& yyMakedebug,
                                      parse_fn yyMakeparse);

  static int                    make(const char* pFilename);

  static void                   makeCommandOpen();
  static void                   makeCommandClose();

  static void                   makeClassOpen(const char* pNewClassName,
                                              const char* pParentClassName,
                                              const char* pSourceFile,
                                              const char* pSourceFile2,
                                              const char* pOutputFile,
                                              const char* pOutputFile2);

  static void                   makeClassClose();

  static void                   pathsOpen();
  static void                   pathsClose();

  static void                   switchesOpen();
  static void                   switchesClose();

  static void                   blackBoxOpen();
  static void                   blackBoxClose();

  static void                   sourceFilesOpen();
  static void                   sourceFilesClose();

  static void                   workingDirectory(const char* pString);
  static void                   includeDirectory(const char* pString);
  static void                   sourceOptionsFile(const char* pString, int nType);

  static void                   fortranIncludeFilesOpen();
  static void                   fortranIncludeFilesClose();

  static void                   classBoundsCheckOpen();
  static void                   classBoundsCheckClose();

  static void                   commandVarOpen();
  static void                   commandOutVarOpen();
  static void                   commandOpClose();
  static void                   commandClose();

  static void                   commandUser(const char* pString);
  static void                   commandPre(const char* pString);
  static void                   commandPost(const char* pString);
  static void                   commandPragmas(const char* pString);
  static void                   commandMode(const char* pString);
  static void                   commandFunction(const char* pString);

  static void                   pushString(const char* pString);

  static void                   addInclude(const char* pFileName);
  static void                   clearIncludeList();
  static void                   checkIncludes(AdtMakeIncremental& rBuildCheck,
                                              const AdtMakeCommand& rMakeCommand);
};


#endif //__cplusplus
#endif //__ADTMAKE_HPP
