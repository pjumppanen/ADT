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
//    Adtutils.hpp
//
//  Purpose:
//    This file includes declarations of utility classes used with Flex/Bison
//    parsing in this project.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADTUTILS_HPP
#define __ADTUTILS_HPP


#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include "lexer.h"


#ifdef _MSC_VER

  #include <direct.h>

  #define popen           _popen
  #define pclose          _pclose
  #define adt_mkdir(Dir)  mkdir(Dir)
  #define ftello         _ftelli64
  #define fseeko         _fseeki64

  typedef __int64 f_ptr;

#else

  #include <unistd.h>

  #define adt_mkdir(Dir)  mkdir(Dir, S_IRWXO | S_IRWXG | S_IRWXU)

  typedef off_t f_ptr;

#endif


//  ----------------------------------------------------------------------------
//  C/C++ compatibility macros
//  ----------------------------------------------------------------------------
#ifdef __cplusplus
  #define C_FUNCTION      extern "C"
  #define C_BLOCK_BEGIN   extern "C" {
  #define C_BLOCK_END     }
#else
  #define C_FUNCTION
  #define C_BLOCK_BEGIN
  #define C_BLOCK_END
#endif


//  ----------------------------------------------------------------------------
//  function prototypes
//  ----------------------------------------------------------------------------
C_FUNCTION FILE*        lex_fopen(const char* pFileName, const char* pMode);

C_FUNCTION void         automate_DisableAutomation(int nDisable);
C_FUNCTION void         automate_AD_LibName(const char* pText, const char* pFileName, int nLineNumber);
C_FUNCTION void         automate_AD_Alias(const char* pText, const char* pFileName, int nLineNumber);
C_FUNCTION void         automate_VarModeAndPhase(int nMode, const char* pText, const char* pFileName, int nLineNumber);
C_FUNCTION int          automate_IgnoreInclude(const char* pFileName);
C_FUNCTION int          automate_preserveInclude(const char* pFileName);
C_FUNCTION int          automate_IgnoreDependency(const char* pFileName);
C_FUNCTION int          automate_ForceInclude(const char* pFileName);

C_FUNCTION void*        scopeManager_Create(void);
C_FUNCTION void         scopeManager_Destroy(void* pPtrScopeManager);
C_FUNCTION void         scopeManager_addUsing(void* pPtrScopeManager, const char* pUsing);
C_FUNCTION void         scopeManager_addUsingDeclaration(void* pPtrScopeManager, const char* pTypeName);
C_FUNCTION void         scopeManager_addType(void* pPtrScopeManager, const char* pTypeName);
C_FUNCTION void         scopeManager_addSymbol(void* pPtrScopeManager, const char* pSymbolName);
C_FUNCTION int          scopeManager_isType(void* pPtrScopeManager, const char* pSymbolName);
C_FUNCTION void         scopeManager_pushScope(void* pPtrScopeManager, const char* pScope, int nIsFunction);
C_FUNCTION void         scopeManager_popScope(void* pPtrScopeManager);
C_FUNCTION void         scopeManager_inheritsFrom(void* pPtrScopeManager, const char* pParentScope);

C_FUNCTION void*        symTable_Create(void);
C_FUNCTION void         symTable_Destroy(void* pSymTable);
C_FUNCTION void         symTable_Add(void* pSymTable, const char* pSymbol, const char* pValue);
C_FUNCTION void         symTable_Remove(void* pSymTable, const char* pSymbol);
C_FUNCTION int          symTable_Defined(void* pSymTable, const char* pSymbol, int* pnValue);

C_FUNCTION size_t       adtParse_wordLength(const char* pText, const char* pWordDelimiters, const char** ppEndWord);
C_FUNCTION int          adtParse_stepOverWord(char** pWord, const char* pWordDelimiters, const char** rpText);
C_FUNCTION int          adtParse_stepOverWord2(char** pWord, const char** ppWordDelimiters, const char** rpText);
C_FUNCTION int          adtParse_extractWord(char** pWord, const char* pWordDelimiters, const char** rpText);
C_FUNCTION int          adtParse_extractWord2(char** pWord, const char** ppWordDelimiters, const char** rpText);
C_FUNCTION int          adtParse_bracketedExtractWord(char** pWord, const char* pWordDelimiters, const char* pOpenBrackets, const char* pCloseBrackets, const char** rpText);
C_FUNCTION int          adtParse_bracketedExtractWord2(char** pWord, const char** ppWordDelimiters, const char** ppOpenBrackets, const char** ppCloseBrackets, const char** rpText);
C_FUNCTION int          adtParse_previousMatchWord(const char** ppChar, const char* pFirstChar, const char* pWord, int nCaseSensitive);
C_FUNCTION int          adtParse_matchWord(const char** ppChar, const char* pWord, int nCaseSensitive);
C_FUNCTION const char*  adtParse_previousWord(const char* pChar, const char* pFirstChar, size_t* pnCount);
C_FUNCTION const char*  adtParse_nextWord(const char* pChar, size_t* pnCount, int bIncludeNewline);
C_FUNCTION const char*  adtParse_nextLine(const char* pChar, size_t* pnCount);

C_FUNCTION void         adtDelphi_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber);
C_FUNCTION const char*  adtDelphi_AllocString(void* pContext, const char* pTokenText, int nTranslate);
C_FUNCTION void         adtDelphi_ParseCommandBlock(void* pContext, const char* pCommandBlock);
C_FUNCTION void         adtDelphi_LogText(void* pContext, const char* pTokenText, int nLineNumber);
C_FUNCTION void         adtDelphi_LogFlush(void* pContext);

C_FUNCTION void         adtFortran_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber);
C_FUNCTION const char*  adtFortran_AllocString(void* pContext, const char* pTokenText, int nTranslate);
C_FUNCTION void         adtFortran_LogText(void* pContext, const char* pTokenText, int nLineNumber);
C_FUNCTION void         adtFortran_LogFlush(void* pContext);

C_FUNCTION void         adtCpp_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber);
C_FUNCTION const char*  adtCpp_AllocString(void* pContext, const char* pTokenText, int nTranslate);
C_FUNCTION void         adtCpp_ParseCommandBlock(void* pContext, const char* pCommandBlock);
C_FUNCTION void         adtCpp_LogText(void* pContext, const char* pTokenText, int nLineNumber);
C_FUNCTION void         adtCpp_LogFlush(void* pContext);

C_FUNCTION void         adtJava_AppendComment(void* pContext, const char* pTokenText, const char* pFileName, int nLineNumber);
C_FUNCTION const char*  adtJava_AllocString(void* pContext, const char* pTokenText, int nTranslate);
C_FUNCTION void         adtJava_ParseCommandBlock(void* pContext, const char* pCommandBlock);
C_FUNCTION void         adtJava_LogText(void* pContext, const char* pTokenText, int nLineNumber);
C_FUNCTION void         adtJava_LogFlush(void* pContext);

C_FUNCTION void         AdtExit(int nExitCode);

//  ----------------------------------------------------------------------------
//  Defines
//  ----------------------------------------------------------------------------
#define AdtDelphiCodeType_PROGRAM 0
#define AdtDelphiCodeType_UNIT    1
#define AdtDelphiCodeType_PACKAGE 2
#define AdtDelphiCodeType_LIBRARY 3

#define AdtDelphiSection_IMPLEMENTATION 0
#define AdtDelphiSection_INTERFACE      1


//  ----------------------------------------------------------------------------
//  global variable declarations
//  ----------------------------------------------------------------------------
C_BLOCK_BEGIN

extern int     adtDelphi_nSection;
extern int     adtDelphi_nCodeType;
extern int     adtDelphi_nLineNumber;
extern int     adtDelphi_nBlockDepth;
extern int     adtDelphi_nClassBlockDepth;
extern void*   adtDelphi_pDelphiContext;

extern int     adtFortran_nLineNumber;
extern int     adtFortran_nBlockDepth;
extern void*   adtFortran_pFortranContext;

extern int     adtCpp_nLineNumber;
extern int     adtCpp_nBlockDepth;
extern void*   adtCpp_pCppContext;

extern int     adtJava_nLineNumber;
extern int     adtJava_nBlockDepth;
extern void*   adtJava_pJavaContext;

C_BLOCK_END


#ifdef __cplusplus


#include "adtcommon.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtParser;
class AdtSourceRoot;
class AdtFortran;
class AdtFortranExecutableProgram;
class AdtDelphi;
class AdtDelphiGoal;
class AdtCpp;
class AdtCppTranslationUnit;
class AdtCppScope;
class AdtJava;
class AdtJavaGoal;


//  ----------------------------------------------------------------------------
//  AdtTapenadeVersion class
//  ----------------------------------------------------------------------------
class AdtTapenadeVersion
{
private:
  static double TapenadeVersion;

public:
  AdtTapenadeVersion(bool bInit = false);

  operator double() const;
};

//  ----------------------------------------------------------------------------

inline AdtTapenadeVersion::operator double() const
{
  return (TapenadeVersion);
}


//  ----------------------------------------------------------------------------
//  Mappings of AdtCppScope* by string
//  ----------------------------------------------------------------------------
typedef std::pair<const string, AdtCppScope*>                         AdtCppScopePtrStringPair;
typedef std::map<string, AdtCppScope*, string_less>                   AdtCppScopePtrByStringMap;
typedef std::map<string, AdtCppScope*, string_less>::iterator         AdtCppScopePtrByStringMapIter;
typedef std::map<string, AdtCppScope*, string_less>::const_iterator   AdtCppScopePtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtCppScope class
//  ----------------------------------------------------------------------------
//  This class is used to track defined types and the context we are in when
//  parsing cpp code.
//  ----------------------------------------------------------------------------
class AdtCppScope
{
private:
  string                      Name;
  AdtIntByStringMap           InheritsFromMap;
  AdtIntByStringMap           TypeMap;
  AdtIntByStringMap           SymbolMap;
  AdtCppScopePtrByStringMap   ScopeMap;
  AdtCppScope*                Parent;

public:
  AdtCppScope(AdtCppScope* pParent, const char* pName);
  AdtCppScope(const AdtCppScope& rCopy);
  virtual ~AdtCppScope();

  void                  reset();
  void                  name(const char* pName);
  AdtCppScope*          findScope(const char* pScopeName);
  AdtCppScope*          addScope(const char* pScopeName);
  void                  addType(const char* pTypeName);
  void                  addSymbol(const char* pTypeName);
  void                  inheritsFrom(const char* pParentScope);

  bool                  isTypeOrSymbol(string* pKeySymbolName, const char* pSymbolName, bool bCheckType, bool bRecurse = false) const;
  bool                  isType(const char* pSymbolName, bool bRecurse = false) const;
  bool                  isSymbol(const char* pSymbolName, bool bRecurse = false) const;
  void                  qualifiedName(string& rName, bool bWithGlobal = false, bool bAsScope = false) const;
  const string&         name() const;
};

//  ----------------------------------------------------------------------------

inline bool AdtCppScope::isType(const char* pSymbolName, bool bRecurse) const
{
  return (isTypeOrSymbol(0, pSymbolName, true, bRecurse));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppScope::isSymbol(const char* pSymbolName, bool bRecurse) const
{
  return (isTypeOrSymbol(0, pSymbolName, false, bRecurse));
}

//  ----------------------------------------------------------------------------

inline void AdtCppScope::name(const char* pName)
{
  if (pName != 0)
  {
    Name = pName;
  }
}

//  ----------------------------------------------------------------------------

inline const string& AdtCppScope::name() const
{
  return (Name);
}


//  ----------------------------------------------------------------------------
//  AdtCppScopeManager class
//  ----------------------------------------------------------------------------
class AdtCppScopeManager
{
private:
  static AdtCppScopeManager   GlobalScopeManager;
  static bool                 MapNames;
  AdtIntByStringMap           UsingMap;
  AdtStringList               ScopeStack;
  mutable AdtCppScope         GlobalScope;
  AdtCppScope*                CurrentScope;

protected:
  AdtCppScope*                findScope(AdtCppScope* pCurrentScope,
                                        const char*& pScopeName,
                                        bool bCreate) const;

  void                        setScope(const char* pScopeName);

public:
  AdtCppScopeManager();
  AdtCppScopeManager(const AdtCppScopeManager& rCopy);
  virtual ~AdtCppScopeManager();

  static AdtCppScopeManager*  globalScopeManager();
  static void                 resetGlobalScopeManager();
  static void                 addUserDefinedType(const char* pTypeName);

  // MapNames static member is used to control the mapping of names. When we
  // translate C++ to Fortran for processing by Tapenade, Tapenade will alter
  // the case of the symbols because it can and Fortran is a case insensitive
  // language. Therefore when translating back to C++ we must translate the
  // symbol case back to the for C++ expects, otherwise we will have linkage
  // errors.
  //
  // When MapNames is false C++ parser will collect the symbol names as it
  // appears in the source (through calls to addSymbol()). When MapNames is
  // true then calls to addSymbol() do nothing but the parser converts symbol
  // names with the same letters but possibly different case to the case as is
  // in the symbol table. This happens through calls to mapSymbolCase().
  //
  // To process the C++ source we set MapNames to false during the forward step
  // processing (compiling sources to generate fortran code) but then set it to
  // true for the final C++ source code compilation stage that generates the
  // final Auto-differentiated C++ source.
  static void                 mapNames(bool bEnable);
  static bool                 mapNames();

  void                        reset();

  static bool                 nestedNameSpecifier(string& sScopeName, const char*& pTypeName);
  static bool                 splitScope(const char* pScope, string& rScope, string& rSymbol);

  void                        inheritsFrom(const char* pParentScope);
  void                        addUsing(const char* pUsing);
  void                        addUsingDeclaration(const char* pTypeName);
  void                        addType(const char* pTypeName);
  void                        addSymbol(const char* pTypeName);
  bool                        isTypeOrSymbol(string* pKeySymbolName, const char* pSymbolName, bool bCheckType, string* pDestBaseName = 0) const;
  bool                        isType(const char* pSymbolName, string* pDestBaseName = 0) const;
  bool                        isSymbol(const char* pSymbolName, string* pDestBaseName = 0) const;
  void                        mapSymbolCase(string& rMappedSymbolName, const char* pSymbolName) const;

  void                        pushScope(const char* pScope, bool bIsFunction);
  void                        popScope();

  void                        currentScopeName(string& rName);
  void                        qualifyName(string& rName);
};

//  ----------------------------------------------------------------------------

inline bool AdtCppScopeManager::isType(const char* pSymbolName, string* pDestBaseName) const
{
  return (isTypeOrSymbol(0, pSymbolName, true, pDestBaseName));
}

//  ----------------------------------------------------------------------------

inline bool AdtCppScopeManager::isSymbol(const char* pSymbolName, string* pDestBaseName) const
{
  return (isTypeOrSymbol(0, pSymbolName, false, pDestBaseName));
}


//  ----------------------------------------------------------------------------
//  AdtCppSplitNameAndComment class
//  ----------------------------------------------------------------------------
//  This utility class is used to seperate comments from symbols. The C/C++
//  parser has been built so that inline and end of line comments are bound to
//  the LITERAL and IDENTIFIER tokens. This is so that array size describing
//  comments will be along side the symbol name. This class breaks them up into
//  there components.
//  ----------------------------------------------------------------------------
class AdtCppSplitNameAndComment
{
private:
  string          Name;
  string          Comment;

public:
  AdtCppSplitNameAndComment(const char* pNameAndPossibleComment);
  AdtCppSplitNameAndComment(const AdtCppSplitNameAndComment& rCopy);
  virtual ~AdtCppSplitNameAndComment();

  void            split(const char* pNameAndPossibleComment);
  const string&   name() const;
  const string&   comment() const;
                  operator const char*() const;
};

//  ----------------------------------------------------------------------------

inline const string& AdtCppSplitNameAndComment::name() const
{
  return (Name);
}

//  ----------------------------------------------------------------------------

inline const string& AdtCppSplitNameAndComment::comment() const
{
  return (Comment);
}

//  ----------------------------------------------------------------------------

inline AdtCppSplitNameAndComment::operator const char*() const
{
  return (Name.c_str());
}


//  ----------------------------------------------------------------------------
//  AdtStringCache class
//  ----------------------------------------------------------------------------
//  This class is used to cache copies of strings representing the tokens in the
//  parsing process for later processing. This allows use to save pointers to
//  tokens and not worry about allocation of storage to persist the tokens
//  whilst parisng continues.
//  ----------------------------------------------------------------------------
class AdtStringCache
{
private:
  AdtIntByStringMapCS   StringMap;

public:
  AdtStringCache();
  virtual ~AdtStringCache();

  void                  flush();
  const char*           add(const char* pString, const string** ppCachedString = 0);
};


//  ----------------------------------------------------------------------------
//  AdtFileCopy class
//  ----------------------------------------------------------------------------
//  This operator class copies files
//  ----------------------------------------------------------------------------
class AdtFileCopy
{
public:
  AdtFileCopy(const char* pSrcFile, const char* pDestFile);
  virtual ~AdtFileCopy();
};


//  ----------------------------------------------------------------------------
//  AdtFile class
//  ----------------------------------------------------------------------------
class AdtFile
{
private:
  FILE*           Handle;
  string*         OutputBuffer;
  string          FileName;
  int             TabSize;
  int             Indent;
  bool            IsFortranFile;
  mutable bool    IsEnabled;
  mutable bool    IsComment;
  mutable size_t  LineCharCount;
  mutable f_ptr   LastNewlinePos;
  mutable size_t  DelayedNewlineCount;

protected:
  void          addDelayedNewlines() const;
  void          writeChar(char nChar) const;
  void          writeString(const char* pString, size_t nStringLength = (size_t)-1) const;

public:
  AdtFile(bool bIsFortranFile = false);
  virtual ~AdtFile();

  bool          open(const char* sFileName, const char* sMode);
  bool          open(string& rBuffer);
  void          close();

  const string& fileName() const;

  void          newline() const;
  void          homeline() const;
  void          delayedNewlines(int nCount) const;
  void          write(const string& rString) const;
  void          write(const char* pString) const;
  void          write(char nChar) const;
  void          readLines(AdtStringList& rStringList);

  void          tabSize(int nTabSize);
  void          incrementIndent();
  void          decrementIndent();
  void          indent(int nIndent);

  bool          isFortranFile() const;
  bool          isOpen() const;
  int           tabSize() const;
  int           indent() const;

  bool          isEnabled() const;
  void          enable() const;
  void          disable() const;
};

//  ----------------------------------------------------------------------------

inline const string& AdtFile::fileName() const
{
  return (FileName);
}

//  ----------------------------------------------------------------------------

inline void AdtFile::write(const string& rString) const
{
  if (IsEnabled)
  {
    write(rString.c_str());
  }
}

//  ----------------------------------------------------------------------------

inline void AdtFile::tabSize(int nTabSize)
{
  if (IsEnabled)
  {
    TabSize = nTabSize;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtFile::incrementIndent()
{
  if (IsEnabled)
  {
    Indent++;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtFile::decrementIndent()
{
  if (IsEnabled)
  {
    Indent--;
  }
}

//  ----------------------------------------------------------------------------

inline void AdtFile::indent(int nIndent)
{
  if (IsEnabled)
  {
    Indent = nIndent;
  }
}

//  ----------------------------------------------------------------------------

inline bool AdtFile::isFortranFile() const
{
  return (IsFortranFile);
}

//  ----------------------------------------------------------------------------

inline bool AdtFile::isOpen() const
{
  return ((Handle != 0) || (OutputBuffer != 0));
}

//  ----------------------------------------------------------------------------

inline int AdtFile::tabSize() const
{
  return (TabSize);
}

//  ----------------------------------------------------------------------------

inline int AdtFile::indent() const
{
  return (Indent);
}

//  ----------------------------------------------------------------------------

inline bool AdtFile::isEnabled() const
{
  return (IsEnabled);
}

//  ----------------------------------------------------------------------------

inline void AdtFile::enable() const
{
  IsEnabled = true;
}

//  ----------------------------------------------------------------------------

inline void AdtFile::disable() const
{
  IsEnabled = false;
}


//  ----------------------------------------------------------------------------
//  AdtParse namespace
//  ----------------------------------------------------------------------------
namespace AdtParse
{
  size_t        wordLength(const char* pText,
                           const char* pWordDelimiters,
                           const char** ppEndWord,
                           bool bMustBeDelimited = false);

  size_t        wordLength(const char* pText,
                           const char** ppWordDelimiters,
                           const char** ppEndWord,
                           bool bMustBeDelimited);

  size_t        bracketedWordLength(const char* pText,
                                    const char* pWordDelimiters,
                                    const char* pOpenBrackets,
                                    const char* pCloseBrackets,
                                    const char** ppEndWord,
                                    bool bMustBeDelimited = false);

  size_t        bracketedWordLength(const char* pText,
                                    const char** ppWordDelimiters,
                                    const char** ppOpenBrackets,
                                    const char** ppCloseBrackets,
                                    const char** ppEndWord,
                                    bool bMustBeDelimited = false);

  bool          stepOverWord(const char* pWordDelimiters,
                             const char*& rpText,
                             bool bMustBeDelimited = false);

  bool          stepOverWord(const char** ppWordDelimiters,
                             const char*& rpText,
                             bool bMustBeDelimited = false);

  bool          extractWord(string& sWord,
                            const char* pWordDelimiters,
                            const char*& rpText,
                            bool bMustBeDelimited = false);

  bool          extractWord(string& sWord,
                            const char** ppWordDelimiters,
                            const char*& rpText,
                            bool bMustBeDelimited = false);

  bool          matchExtractWord(string& sWord,
                                 const char* pDelimitingWord,
                                 const char*& rpText);

  bool          bracketedExtractWord(string& sWord,
                                     const char* pWordDelimiters,
                                     const char* pOpenBrackets,
                                     const char* pCloseBrackets,
                                     const char*& rpText,
                                     bool bMustBeDelimited = false);

  bool          bracketedExtractWord(string& sWord,
                                     const char** ppWordDelimiters,
                                     const char** ppOpenBrackets,
                                     const char** ppCloseBrackets,
                                     const char*& rpText,
                                     bool bMustBeDelimited = false);

  bool          previousMatchWord(const char*& rpChar,
                                  const char* pFirstChar,
                                  const char* pWord,
                                  bool bCaseSensitive = true);

  bool          matchWord(const char*& pChar,
                          const char* pWord,
                          bool bCaseSensitive = true);

  int           matchWhichWord(const char*& pChar,
                               const char** ppWords,
                               int nWords,
                               bool bCaseSensitive = true);

  const char*   previousWord(const char* pChar,
                             const char* pFirstChar,
                             size_t* pnCount = 0);

  const char*   nextWord(const char* pChar, size_t* pnCount = 0, bool bIncludeNewline = true);
  const char*   nextLine(const char* pChar, size_t* pnCount = 0);
}


//  ----------------------------------------------------------------------------
//  AdtGenericAbstractCommand class
//  ----------------------------------------------------------------------------
//  This is an abstract base class for commands issued against the parsed delphi
//  or CPP code.
//  ----------------------------------------------------------------------------
class AdtGenericAbstractCommand
{
private:

public:
  AdtGenericAbstractCommand();
  AdtGenericAbstractCommand(const AdtGenericAbstractCommand& rCopy);
  virtual ~AdtGenericAbstractCommand();

  virtual bool          execute(AdtDelphi& rParent,
                                FILE*& yyDelphiin,
                                int& yyDelphidebug,
                                parse_fn yyDelphiparse) = 0;

  virtual bool          execute(AdtCpp& rParent,
                                FILE*& yyCppin,
                                int& yyCppdebug,
                                parse_fn yyCppparse) = 0;

  virtual bool          execute(AdtJava& rParent,
                                FILE*& yyJavain,
                                int& yyJavadebug,
                                parse_fn yyJavaparse) = 0;

  virtual bool          isType(const char* pType) const;
  virtual const char*   type() const;
};


//  ----------------------------------------------------------------------------
//  List of AdtGenericAbstractCommand*
//  ----------------------------------------------------------------------------
typedef std::list<AdtGenericAbstractCommand*>                  AdtGenericAbstractCommandPtrList;
typedef std::list<AdtGenericAbstractCommand*>::iterator        AdtGenericAbstractCommandPtrListIter;
typedef std::list<AdtGenericAbstractCommand*>::const_iterator  AdtGenericAbstractCommandPtrListConstIter;


//  ----------------------------------------------------------------------------
//  AdtGenericDefineCommand class
//  ----------------------------------------------------------------------------
//  This class implements the macro define command.
//  ----------------------------------------------------------------------------
class AdtGenericDefineCommand : public AdtGenericAbstractCommand
{
private:
  string                CompressedMacro;
  string                ExpandedMacro;
  string                VariableDefinitions;
  string                CommandBlockName;

public:
  AdtGenericDefineCommand(const char* pCompressedMacro,
                          const char* pExpandedMacro,
                          const char* pVariableDefinitions,
                          const char* pCommandBlockName);

  AdtGenericDefineCommand(const AdtGenericDefineCommand& rCopy);
  virtual ~AdtGenericDefineCommand();

  virtual bool          execute(AdtDelphi& rParent,
                                FILE*& yyDelphiin,
                                int& yyDelphidebug,
                                parse_fn yyDelphiparse);

  virtual bool          execute(AdtCpp& rParent,
                                FILE*& yyCppin,
                                int& yyCppdebug,
                                parse_fn yyCppparse);

  virtual bool          execute(AdtJava& rParent,
                                FILE*& yyJavain,
                                int& yyJavadebug,
                                parse_fn yyJavaparse);

  virtual bool          isType(const char* pType) const;
  virtual const char*   type() const;
};


//  ----------------------------------------------------------------------------
//  AdtGenericTypeMapCommand class
//  ----------------------------------------------------------------------------
//  This class implements the type map command.
//  ----------------------------------------------------------------------------
class AdtGenericTypeMapCommand : public AdtGenericAbstractCommand
{
private:
  string                GenericType;
  string                FortranType;
  string                FortranSize;

public:
  AdtGenericTypeMapCommand(const char* pGenericType,
                           const char* pFortranType,
                           const char* pFortranSize);

  AdtGenericTypeMapCommand(const AdtGenericTypeMapCommand& rCopy);
  virtual ~AdtGenericTypeMapCommand();

  virtual bool          execute(AdtDelphi& rParent,
                                FILE*& yyDelphiin,
                                int& yyDelphidebug,
                                parse_fn yyDelphiparse);

  virtual bool          execute(AdtCpp& rParent,
                                FILE*& yyCppin,
                                int& yyCppdebug,
                                parse_fn yyCppparse);

  virtual bool          execute(AdtJava& rParent,
                                FILE*& yyJavain,
                                int& yyJavadebug,
                                parse_fn yyJavaparse);

  virtual bool          isType(const char* pType) const;
  virtual const char*   type() const;
};


//  ----------------------------------------------------------------------------
//  AdtGenericCommandBlock class
//  ----------------------------------------------------------------------------
//  The command block class is a container for various commands that ADT will
//  follow in performing auto-differentiation. This includes things like macro
//  substitution definitions and which function to differentiate with respect
//  to what and in which mode.
//  ----------------------------------------------------------------------------
class AdtGenericCommandBlock
{
protected:
  AdtGenericAbstractCommandPtrList   DefineCommandList;
  AdtGenericAbstractCommandPtrList   TypeMapCommandList;
  bool                               IsForwardMode;

protected:
  void                              flush(AdtGenericAbstractCommandPtrList& rList);
  void                              add(AdtGenericAbstractCommandPtrList& rList, AdtGenericAbstractCommand* pCommand);

  bool                              execute(AdtGenericAbstractCommandPtrList& rList,
                                            AdtDelphi& rParent,
                                            FILE*& yyDelphiin,
                                            int& yyDelphidebug,
                                            parse_fn yyDelphiparse);

  bool                              execute(AdtGenericAbstractCommandPtrList& rList,
                                            AdtCpp& rParent,
                                            FILE*& yyCppin,
                                            int& yyCppdebug,
                                            parse_fn yyCppparse);

  bool                              execute(AdtGenericAbstractCommandPtrList& rList,
                                            AdtJava& rParent,
                                            FILE*& yyCppin,
                                            int& yyCppdebug,
                                            parse_fn yyCppparse);

  const char*                       parseDefine(const char* pChar, int nMode, const char* pCommandBlockName);
  const char*                       parseInclude(const char* pChar);
  const char*                       parseTypeMap(const char* pChar);
  const char*                       parseDefType(const char* pChar);

public:
  AdtGenericCommandBlock();
  AdtGenericCommandBlock(const AdtGenericCommandBlock& rCopy);
  virtual ~AdtGenericCommandBlock();

  bool                              reset();
  bool                              isForwardMode() const;
  void                              isForwardMode(bool bForward);

  bool                              parseAppend(const char* pCommandBlock, const char* pCommandBlockName);

  bool                              execute(AdtDelphi& rParent,
                                            FILE*& yyDelphiin,
                                            int& yyDelphidebug,
                                            parse_fn yyDelphiparse);

  bool                              execute(AdtCpp& rParent,
                                            FILE*& yyCppin,
                                            int& yyCppdebug,
                                            parse_fn yyCppparse);

  bool                              execute(AdtJava& rParent,
                                            FILE*& yyJavain,
                                            int& yyJavadebug,
                                            parse_fn yyJavaparse);
};

//  ----------------------------------------------------------------------------

inline bool AdtGenericCommandBlock::isForwardMode() const
{
  return (IsForwardMode);
}

//  ----------------------------------------------------------------------------

inline void AdtGenericCommandBlock::isForwardMode(bool bForward)
{
  IsForwardMode = bForward;
}


//  ----------------------------------------------------------------------------
//  AdtCommon class
//  ----------------------------------------------------------------------------
class AdtCommentCollection
{
private:
  string              FileName;
  AdtStringByIntMap   CommentMap;

public:
  AdtCommentCollection(const char* pFileName);
  virtual ~AdtCommentCollection();

  void                addComment(const char* pComment, int nLineNumber);
  bool                extractComment(string& rComment, int nUpToLineNumber);
  void                flush();

  const string&       fileName() const;
};

//  ----------------------------------------------------------------------------

inline void AdtCommentCollection::flush()
{
  CommentMap.clear();
}

//  ----------------------------------------------------------------------------

inline const string& AdtCommentCollection::fileName() const
{
  return (FileName);
}

//  ----------------------------------------------------------------------------

typedef std::pair<const string, AdtCommentCollection*>                        AdtCommentCollectionPtrStringPair;
typedef std::map<string, AdtCommentCollection*, string_less>                  AdtCommentCollectionPtrByStringMap;
typedef std::map<string, AdtCommentCollection*, string_less>::iterator        AdtCommentCollectionPtrByStringMapIter;
typedef std::map<string, AdtCommentCollection*, string_less>::const_iterator  AdtCommentCollectionPtrByStringMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtCommon class
//  ----------------------------------------------------------------------------
class AdtCommon
{
private:
  FILE*                               Log;
  const char*                         Comment;
  static AdtStringCache               StringCache;
  static AdtStringByStringMap         TranslationMap;
  AdtCommentCollectionPtrByStringMap  CommentCollectionMap;

protected:
  bool                    beginParseString(FILE*& rFile, string& sFileName, const char* pString);
  bool                    endParseString(FILE*& rFile, string& sFileName);
  void                    flush();

public:
  AdtCommon();
  virtual ~AdtCommon();

  bool                    openLog(const char* pFileAndPath, const char* pMode);
  bool                    closeLog();
  void                    logText(const char* pTokenText, int nLineNumber);
  void                    logFlush();
  void                    appendComment(const char* pCommentText, const char* pFileName, int nLineNumber);
  bool                    extractComment(const string** ppComment, const char* pFileName, int nUpToLineNumber);

  static void             addTranslation(const char* pOriginalText, const char* pTranslatedText);
  static void             addTranslation(const AdtStringList& rOriginalTextList, const AdtStringList& rTranslatedTextList);
  static void             removeTranslation(const char* pOriginalText);
  static void             removeTranslation(const AdtStringList& rOriginalTextList);
  static const char*      allocString(const char* pTokenText,
                                      const string** ppCachedString = 0,
                                      bool bTranslate = false);
};


//  ----------------------------------------------------------------------------
//  AdtCompilerBase class
//  ----------------------------------------------------------------------------
class AdtCompilerBase : public AdtCommon
{
protected:
  AdtGenericCommandBlock  CommandBlock;

protected:
  void                    stripComments(string& sStrippedCommandBlock,
                                        const char* pCommandBlock,
                                        const char** ppLeadingBraces,
                                        const char** ppTrailingBraces,
                                        int nBraceTypes) const;

  void                    parseCommandBlock(const char* pCommandBlock);

public:
  AdtCompilerBase();
  virtual ~AdtCompilerBase();

  virtual void            parseCommandBlock(const char* pCommandBlock, bool bEmbedded) = 0;

  virtual bool            parse(const char* pFilename,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                const AdtStringList* pSearchPaths = 0,
                                bool bForwardMode = true) = 0;

  virtual bool            parseString(AdtParser*& pRoot,
                                      const char* pString) = 0;

  virtual void            releaseRoot() = 0;
  virtual AdtParser*      parseRoot() const = 0;
  virtual AdtSourceRoot*  sourceRoot() const = 0;
};


//  ----------------------------------------------------------------------------
//  AdtCompiler class
//  ----------------------------------------------------------------------------
class AdtCompiler
{
private:
  AdtCompilerBase*  ParserContext;

private:
  AdtCompilerBase*  createCompilerForFile(const string& rSourceFile) const;

  AdtCompiler(const AdtCompiler& rCopy);

public:
  AdtCompiler(const string& rSourceFile);
  virtual ~AdtCompiler();

  void              parseCommandBlock(const char* pCommandBlock, bool bEmbedded);

  bool              parse(const char* pFilename,
                          const char* pCommandBlock = 0,
                          const char* pCommandBlockName = 0,
                          const AdtStringList* pSearchPaths = 0,
                          bool bForwardMode = true);

  bool              parseString(AdtParser*& pRoot,
                                const char* pString);

  void              releaseRoot();
  AdtParser*        parseRoot() const;
  AdtSourceRoot*    sourceRoot() const;
  bool              isValid() const;
};

//  ----------------------------------------------------------------------------

inline void AdtCompiler::parseCommandBlock(const char* pCommandBlock, bool bEmbedded)
{
  if (ParserContext != 0)
  {
    ParserContext->parseCommandBlock(pCommandBlock, bEmbedded);
  }
}

//  ----------------------------------------------------------------------------

inline bool AdtCompiler::parse(const char* pFilename,
                               const char* pCommandBlock,
                               const char* pCommandBlockName,
                               const AdtStringList* pSearchPaths,
                               bool bForwardMode)
{
  return (ParserContext != 0 ? ParserContext->parse(pFilename,
                                                    pCommandBlock,
                                                    pCommandBlockName,
                                                    pSearchPaths,
                                                    bForwardMode)
                             : false);
}

//  ----------------------------------------------------------------------------

inline bool AdtCompiler::parseString(AdtParser*& pRoot,
                                   const char* pString)
{
  return (ParserContext != 0 ? ParserContext->parseString(pRoot,
                                                          pString)
                             : false);
}

//  ----------------------------------------------------------------------------

inline void AdtCompiler::releaseRoot()
{
  if (ParserContext != 0)
  {
    ParserContext->releaseRoot();
  }
}

//  ----------------------------------------------------------------------------

inline AdtParser* AdtCompiler::parseRoot() const
{
  return (ParserContext != 0 ? ParserContext->parseRoot()
                             : 0);
}

//  ----------------------------------------------------------------------------

inline AdtSourceRoot* AdtCompiler::sourceRoot() const
{
  return (ParserContext != 0 ? ParserContext->sourceRoot()
                             : 0);
}

//  ----------------------------------------------------------------------------

inline bool AdtCompiler::isValid() const
{
  return (ParserContext != 0);
}


//  ----------------------------------------------------------------------------
//  AdtFortran class
//  ----------------------------------------------------------------------------
class AdtFortran : public AdtCompilerBase
{
protected:
  static const char*      PushPopFunctions[55];
  static const char*      CallExpandMacrosWithStackSubstitution;
  static const char*      CallExpandMacrosWithoutStackSubstitution;

protected:
  bool                    parse(void*& pFortranContext,
                                const char* pFilename,
                                FILE*& yyFortranin,
                                int& yyFortrandebug,
                                parse_fn yyFortranparse);

  bool                    parseString(void*& pFortranContext,
                                      AdtFortranExecutableProgram*& pRoot,
                                      const char* pString,
                                      FILE*& yyFortranin,
                                      int& yyFortrandebug,
                                      parse_fn yyFortranparse);

public:
  AdtFortran();
  virtual ~AdtFortran();

  virtual void            parseCommandBlock(const char* pCommandBlock, bool bEmbedded);

  virtual bool            parse(const char* pFilename,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                const AdtStringList* pSearchPaths = 0,
                                bool bForwardMode = true);

  virtual bool            parseString(AdtParser*& pRoot,
                                      const char* pString);

  virtual void            releaseRoot();
  virtual AdtParser*      parseRoot() const;
  virtual AdtSourceRoot*  sourceRoot() const;

  bool                    parseCallExpandMacros(AdtFortranExecutableProgram*& pRoot);

  void                    setPushPopSubstitution(const char* pFullSuffix, const char* pBaseSuffix);
  void                    clearPushPopSubstitution(const char* pFullSuffix);
};


//  ----------------------------------------------------------------------------
//  AdtDelphi class
//  ----------------------------------------------------------------------------
class AdtDelphi : public AdtCompilerBase
{
protected:
  bool                    parse(void*& pDelphiContext,
                                const char* pFilename,
                                FILE*& yyDelphiin,
                                int& yyDelphidebug,
                                parse_fn yyDelphiparse,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                bool bForwardMode = true);

  bool                    parseString(void*& pDelphiContext,
                                      AdtDelphiGoal*& pRoot,
                                      const char* pString,
                                      FILE*& yyDelphiin,
                                      int& yyDelphidebug,
                                      parse_fn yyDelphiparse);

public:
  AdtDelphi();
  virtual ~AdtDelphi();

  virtual void            parseCommandBlock(const char* pCommandBlock, bool bEmbedded);

  virtual bool            parse(const char* pFilename,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                const AdtStringList* pSearchPaths = 0,
                                bool bForwardMode = true);

  virtual bool            parseString(AdtParser*& pRoot,
                                      const char* pString);

  virtual void            releaseRoot();
  virtual AdtParser*      parseRoot() const;
  virtual AdtSourceRoot*  sourceRoot() const;
};


//  ----------------------------------------------------------------------------
//  AdtCpp class
//  ----------------------------------------------------------------------------
class AdtCpp : public AdtCompilerBase
{
protected:
  bool                    parse(void*& pCppContext,
                                const char* pFilename,
                                FILE*& yyCppin,
                                int& yyCppdebug,
                                parse_fn yyCppparse,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                bool bForwardMode = true);

  bool                    parseString(void*& pCppContext,
                                      AdtCppTranslationUnit*& pRoot,
                                      const char* pString,
                                      FILE*& yyCppin,
                                      int& yyCppdebug,
                                      parse_fn yyCppparse);

public:
  AdtCpp();
  virtual ~AdtCpp();

  virtual void            parseCommandBlock(const char* pCommandBlock, bool bEmbedded);

  virtual bool            parse(const char* pFilename,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                const AdtStringList* pSearchPaths = 0,
                                bool bForwardMode = true);

  virtual bool            parseString(AdtParser*& pRoot,
                                      const char* pString);

  virtual void            releaseRoot();
  virtual AdtParser*      parseRoot() const;
  virtual AdtSourceRoot*  sourceRoot() const;
};


//  ----------------------------------------------------------------------------
//  AdtJava class
//  ----------------------------------------------------------------------------
class AdtJava : public AdtCompilerBase
{
protected:
  bool                    parse(void*& pJavaContext,
                                const char* pFilename,
                                FILE*& yyJavain,
                                int& yyJavadebug,
                                parse_fn yyJavaparse,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                bool bForwardMode = true);

  bool                    parseString(void*& pJavaContext,
                                      AdtJavaGoal*& pRoot,
                                      const char* pString,
                                      FILE*& yyJavain,
                                      int& yyJavadebug,
                                      parse_fn yyJavaparse);

public:
  AdtJava();
  virtual ~AdtJava();

  virtual void            parseCommandBlock(const char* pCommandBlock, bool bEmbedded);

  virtual bool            parse(const char* pFilename,
                                const char* pCommandBlock = 0,
                                const char* pCommandBlockName = 0,
                                const AdtStringList* pSearchPaths = 0,
                                bool bForwardMode = true);

  virtual bool            parseString(AdtParser*& pRoot,
                                      const char* pString);

  virtual void            releaseRoot();
  virtual AdtParser*      parseRoot() const;
  virtual AdtSourceRoot*  sourceRoot() const;
};


#endif //__cplusplus

#endif //__ADTUTILS_HPP
