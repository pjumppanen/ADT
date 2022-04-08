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
//    AdtMake.cpp
//
//  Purpose:
//    This file includes implementations of classes used to implement the make
//    system for ADT.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtmake.hpp"
#include "adtcpp.hpp"
#include "adtautomate.hpp"


//  ----------------------------------------------------------------------------
//  globals
//  ----------------------------------------------------------------------------
AdtMakeSystem  MakeSystem;


//  ----------------------------------------------------------------------------
//  static members
//  ----------------------------------------------------------------------------
AdtStringList             AdtMakeSystem::StringList;
AdtStringList             AdtMakeSystem::IncludeList;
AdtMakeClass              AdtMakeSystem::CurrentClass;
AdtMakeCommand            AdtMakeSystem::CurrentCommand;
AdtMakeCommandOperation   AdtMakeSystem::CurrentCommandOperation;
AdtMakeCommandList        AdtMakeSystem::MakeCommandList;
AdtMakeSystem::AdtOpType  AdtMakeSystem::OpType = AdtMakeSystem::OtherOpType;
AdtMakeIncremental        AdtMakeSystem::BuildCheck;
string                    AdtExePath::ExePath;


//  ----------------------------------------------------------------------------
//  AdtExePath method implementations
//  ----------------------------------------------------------------------------
AdtExePath::AdtExePath(const char* pExeFileAndPath)
{
  UtlFilePath Path(pExeFileAndPath);

  Path.name("");
  Path.extension("");
  Path.join(ExePath);
}


//  ----------------------------------------------------------------------------
//  "C" callable function implementations
//  ----------------------------------------------------------------------------
void make_AddInclude(const char* pFileName)
{
  MakeSystem.addInclude(unifyFilePath(pFileName));
}

//  ----------------------------------------------------------------------------

const char* make_AllocString(const char* pTokenText)
{
  const char* pString = MakeSystem.allocString(pTokenText);

  return (pString);
}

//  ----------------------------------------------------------------------------

void  make_LogText(const char* pTokenText, int nLineNumber)
{
  MakeSystem.logText(pTokenText, nLineNumber);
}

//  ----------------------------------------------------------------------------

void make_MakeCommandOpen()
{
  MakeSystem.makeCommandOpen();
}

//  ----------------------------------------------------------------------------

void make_MakeCommandClose()
{
  MakeSystem.makeCommandClose();
}

//  ----------------------------------------------------------------------------

void make_ClassOpen(const char* pNewClassName,
                    const char* pParentClassName,
                    const char* pSourceFile,
                    const char* pSourceFile2,
                    const char* pOutputFile,
                    const char* pOutputFile2)
{
  MakeSystem.makeClassOpen(pNewClassName,
                           pParentClassName,
                           pSourceFile,
                           pSourceFile2,
                           pOutputFile,
                           pOutputFile2);
}

//  ----------------------------------------------------------------------------

void make_ClassClose()
{
  MakeSystem.makeClassClose();
}

//  ----------------------------------------------------------------------------

void make_PathsOpen()
{
  MakeSystem.pathsOpen();
}

//  ----------------------------------------------------------------------------

void make_PathsClose()
{
  MakeSystem.pathsClose();
}

//  ----------------------------------------------------------------------------

void make_SwitchesOpen()
{
  MakeSystem.switchesOpen();
}

//  ----------------------------------------------------------------------------

void make_SwitchesClose()
{
  MakeSystem.switchesClose();
}

//  ----------------------------------------------------------------------------

void make_BlackBoxOpen()
{
  MakeSystem.blackBoxOpen();
}

//  ----------------------------------------------------------------------------

void make_BlackBoxClose()
{
  MakeSystem.blackBoxClose();
}

//  ----------------------------------------------------------------------------

void make_SourceFilesOpen()
{
  MakeSystem.sourceFilesOpen();
}

//  ----------------------------------------------------------------------------

void make_SourceFilesClose()
{
  MakeSystem.sourceFilesClose();
}

//  ----------------------------------------------------------------------------

void make_WorkingDirectory(const char* pString)
{
  MakeSystem.workingDirectory(unifyFilePath(pString));
}

//  ----------------------------------------------------------------------------

void make_IncludeDirectory(const char* pString)
{
  MakeSystem.includeDirectory(unifyFilePath(pString));
}

//  ----------------------------------------------------------------------------

void make_SourceOptionsFile(const char* pString, int nType)
{
  MakeSystem.sourceOptionsFile(unifyFilePath(pString), nType);
}

//  ----------------------------------------------------------------------------

void make_FortranIncludeFilesOpen()
{
  MakeSystem.fortranIncludeFilesOpen();
}

//  ----------------------------------------------------------------------------

void make_FortranIncludeFilesClose()
{
  MakeSystem.fortranIncludeFilesClose();
}

//  ----------------------------------------------------------------------------

void make_ClassBoundsCheckOpen()
{
  MakeSystem.classBoundsCheckOpen();
}

//  ----------------------------------------------------------------------------

void make_ClassBoundsCheckClose()
{
  MakeSystem.classBoundsCheckClose();
}

//  ----------------------------------------------------------------------------

void make_CommandVarOpen()
{
  MakeSystem.commandVarOpen();
}

//  ----------------------------------------------------------------------------

void make_CommandOutVarOpen()
{
  MakeSystem.commandOutVarOpen();
}

//  ----------------------------------------------------------------------------

void make_CommandOpClose()
{
  MakeSystem.commandOpClose();
}

//  ----------------------------------------------------------------------------

void make_CommandClose()
{
  MakeSystem.commandClose();
}

//  ----------------------------------------------------------------------------

void make_CommandUser(const char* pString)
{
  MakeSystem.commandUser(pString);
}

//  ----------------------------------------------------------------------------

void make_CommandPre(const char* pString)
{
  MakeSystem.commandPre(unifyFilePath(pString));
}

//  ----------------------------------------------------------------------------

void make_CommandPost(const char* pString)
{
  MakeSystem.commandPost(unifyFilePath(pString));
}

//  ----------------------------------------------------------------------------

void make_CommandPragmas(const char* pString)
{
  MakeSystem.commandPragmas(pString);
}

//  ----------------------------------------------------------------------------

void make_CommandMode(const char* pString)
{
  MakeSystem.commandMode(pString);
}

//  ----------------------------------------------------------------------------

void make_CommandFunction(const char* pString)
{
  MakeSystem.commandFunction(pString);
}

//  ----------------------------------------------------------------------------

void make_PushString(const char* pString)
{
  MakeSystem.pushString(pString);
}


//  ----------------------------------------------------------------------------
//  AdtMakeIncremental method implementations
//  ----------------------------------------------------------------------------
bool AdtMakeIncremental::Build = false;

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::shouldBuild() const
{
  bool bShouldBuild = false;

  if (ReferenceString != 0)
  {
    if (CheckString.length() > ReferenceLength)
    {
      bShouldBuild = true;
    }
    else if (strncmp(ReferenceString, CheckString.c_str(), CheckString.length()) != 0)
    {
      bShouldBuild = true;
    }
  }
  else
  {
    bShouldBuild = true;
  }

  return (bShouldBuild);
}

//  ----------------------------------------------------------------------------

void AdtMakeIncremental::close(bool bWriteCheckString)
{
  if (ReferenceString != 0)
  {
    delete ReferenceString;

    ReferenceString = 0;
    ReferenceLength = 0;
  }

  if (bWriteCheckString             &&
      (CheckFileName.length() > 0)  &&
      (CheckString.length()   > 0))
  {
    FILE* pCheckFile = fopen(CheckFileName, "wb");

    if (pCheckFile != 0)
    {
      fwrite(CheckString.c_str(), CheckString.length(), 1, pCheckFile);
      fwrite(NewMethodsAndAttributesString.c_str(), NewMethodsAndAttributesString.length(), 1, pCheckFile);
      fclose(pCheckFile);
    }
  }
}

//  ----------------------------------------------------------------------------

AdtMakeIncremental::AdtMakeIncremental()
 : CheckString(),
   CheckFileName(),
   NewMethodsAndAttributesString()
{
  ReferenceString = 0;
  ReferenceLength = 0;
}

//  ----------------------------------------------------------------------------

AdtMakeIncremental::~AdtMakeIncremental()
{
  close(false);
}

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::open(const char* pBuildCheckFileAndPath)
{
  bool bOpened = false;

  if (pBuildCheckFileAndPath != 0)
  {
    close(false);

    CheckFileName = pBuildCheckFileAndPath;

    FILE* pCheckFile = fopen(pBuildCheckFileAndPath, "rb");

    if (pCheckFile != 0)
    {
      fseek(pCheckFile, 0, SEEK_END);

      ReferenceLength = ftell(pCheckFile);

      fseek(pCheckFile, 0, SEEK_SET);

      if (ReferenceLength > 0)
      {
        ReferenceString = new char[ReferenceLength + 1];

        memset(ReferenceString, 0, ReferenceLength + 1);

        if (ReferenceString != 0)
        {
          if (fread(ReferenceString, ReferenceLength, 1, pCheckFile) == 1)
          {
            bOpened = true;
          }
          else
          {
            bOpened = false;
            Build   = true;
          }
        }
      }

      fclose(pCheckFile);
    }
    else
    {
      // If we can't open a check file then it means it hasn't been built before
      // so we flag that it should be built
      Build = true;
    }
  }

  return (bOpened);
}

//  ----------------------------------------------------------------------------

void AdtMakeIncremental::close()
{
  close(true);
}

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::checkText(const char* pText)
{
  if (pText != 0)
  {
    CheckString += pText;
  }

  if ((Build == false) && shouldBuild())
  {
    Build = true;
  }

  return (Build);
}

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::checkList(const AdtStringList& rList)
{
  AdtStringListConstIter  Iter;

  for (Iter = rList.begin() ; Iter != rList.end() ; ++Iter)
  {
    const string& rText = *Iter;

    checkText(rText);
  }

  if ((Build == false) && shouldBuild())
  {
    Build = true;
  }

  return (Build);
}

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::checkMap(const AdtIntByStringMap& rMap)
{
  AdtIntByStringMapConstIter  Iter;

  for (Iter = rMap.begin() ; Iter != rMap.end() ; ++Iter)
  {
    const string& rText = (*Iter).first;

    checkText(rText);
  }

  if ((Build == false) && shouldBuild())
  {
    Build = true;
  }

  return (Build);
}

//  ----------------------------------------------------------------------------

bool AdtMakeIncremental::checkFile(const char* pFilenameAndPath)
{
  if (pFilenameAndPath != 0)
  {
    struct stat Status;

    CheckString += pFilenameAndPath;

    // Get the file time stamp and add it to check string
    if (stat(pFilenameAndPath, &Status) == 0)
    {
      const char* pTimeDescr = asctime(gmtime(&Status.st_mtime));

      if (pTimeDescr != 0)
      {
        char* pCR = (char*)strchr(pTimeDescr, '\n');

        while (pCR != 0)
        {
          *pCR = ' ';
          pCR  = (char*)strchr(pTimeDescr, '\n');
        }

        CheckString += pTimeDescr;
      }
    }
    else
    {
      Build = true;
    }
  }

  if ((Build == false) && shouldBuild())
  {
    Build = true;
  }

  return (Build);
}

//  ----------------------------------------------------------------------------

void AdtMakeIncremental::updateNewMethodsAndAttributes(const char* pParentClassName,
                                                       AdtStringByStringMap& NewMethodMap,
                                                       AdtStringList& NewMethodList,
                                                       AdtStringByStringMap& NewAttributesMap,
                                                       AdtStringList& NewAttributesList)
{
  if (pParentClassName != 0)
  {
    AdtStringByStringMap  UpdatedNewMethodMap;
    AdtStringList         UpdatedNewMethodList;
    AdtStringByStringMap  UpdatedNewAttributesMap;
    AdtStringList         UpdatedNewAttributesList;

    if (ReferenceString != 0)
    {
      // Need to merge cached methods and attributes. The cached new methods and attributes
      // are stored in the check file at the end of the check text using newline
      // characters as separators. The form is:
      //  \nclassname_1
      //  \nnew_method_1,new_method_2,...new_method_n
      //  \nnew_attribute_1,new_attribute_2,...new_atrribute_n
      //  \nclassname_2
      //  \nnew_method_1,new_method_2,...new_method_n
      //  \nnew_attribute_1,new_attribute_2,...new_atrribute_n
      //    .
      //    .
      //    .
      //
      //
      const char* pInfo = strchr(ReferenceString, '\n');

      if (pInfo != 0)
      {
        while (AdtParse::matchWord(pInfo, "\n"))
        {
          string sClass;
          string sMethods;
          string sAttributes;

          AdtParse::extractWord(sClass, "\n", pInfo);
          AdtParse::matchWord(pInfo, "\n");
          AdtParse::extractWord(sMethods, "\n", pInfo);
          AdtParse::matchWord(pInfo, "\n");
          AdtParse::extractWord(sAttributes, "\n", pInfo);

          if (sClass.eq(pParentClassName))
          {
            const char* pMethods    = sMethods;
            const char* pAttributes = sAttributes;
            string      sMethod;
            string      sAttribute;

            while (AdtParse::extractWord(sMethod, ",", pMethods))
            {
              UpdatedNewMethodList.push_back(sMethod);
              UpdatedNewMethodMap[sMethod] = sMethod;

              AdtParse::matchWord(pMethods, ",");
            }

            while (AdtParse::extractWord(sAttribute, ",", pAttributes))
            {
              UpdatedNewAttributesList.push_back(sAttribute);
              UpdatedNewAttributesMap[sAttribute] = sAttribute;

              AdtParse::matchWord(pAttributes, ",");
            }
            break;
          }
        }
      }
    }

    // Merge old with new
    AdtStringListConstIter Iter;

    for (Iter = NewMethodList.begin() ; Iter != NewMethodList.end() ; ++Iter)
    {
      const string& sMethod = *Iter;

      if (UpdatedNewMethodMap.find(sMethod) == UpdatedNewMethodMap.end())
      {
        UpdatedNewMethodList.push_back(sMethod);
        UpdatedNewMethodMap[sMethod] = sMethod;
      }
    }

    for (Iter = NewAttributesList.begin() ; Iter != NewAttributesList.end() ; ++Iter)
    {
      const string& sAttribute = *Iter;

      if (UpdatedNewAttributesMap.find(sAttribute) == UpdatedNewAttributesMap.end())
      {
        UpdatedNewAttributesList.push_back(sAttribute);
        UpdatedNewAttributesMap[sAttribute] = sAttribute;
      }
    }

    // replace with merged lists and maps
    NewMethodList.assign(UpdatedNewMethodList.begin(), UpdatedNewMethodList.end());
    NewAttributesList.assign(UpdatedNewAttributesList.begin(), UpdatedNewAttributesList.end());

    NewMethodMap      = UpdatedNewMethodMap;
    NewAttributesMap  = UpdatedNewAttributesMap;

    // Update the NewMethodsAndAttributesString to include the new methods
    // and attributes for this build
    NewMethodsAndAttributesString += "\n";
    NewMethodsAndAttributesString += pParentClassName;
    NewMethodsAndAttributesString += "\n";

    bool bFirst = true;

    for (Iter = NewMethodList.begin() ; Iter != NewMethodList.end() ; ++Iter)
    {
      const string& sMethod = *Iter;

      if (bFirst)
      {
        bFirst = false;
      }
      else
      {
        NewMethodsAndAttributesString += ",";
      }

      NewMethodsAndAttributesString += sMethod;
    }

    NewMethodsAndAttributesString += "\n";

    bFirst = true;

    for (Iter = NewAttributesList.begin() ; Iter != NewAttributesList.end() ; ++Iter)
    {
      const string& sAttribute = *Iter;

      if (bFirst)
      {
        bFirst = false;
      }
      else
      {
        NewMethodsAndAttributesString += ",";
      }

      NewMethodsAndAttributesString += sAttribute;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeIncremental::forceRebuild()
{
  AdtMakeIncremental::build(true);

  // Need to remove reference string or else we may end up with spurious compile errors
  if (ReferenceString != 0)
  {
    delete ReferenceString;

    ReferenceString = 0;
    ReferenceLength = 0;
  }
}


//  ----------------------------------------------------------------------------
//  AdtMakeCommandOperation method implementations
//  ----------------------------------------------------------------------------
void AdtMakeCommandOperation::executeCommandLine(const AdtMakeCommand& rParent,
                                                 const string& rCommandline,
                                                 const char* pSourceFile,
                                                 const char* pTypeMsg) const
{
  const char* pChar = rCommandline;
  string      sCommandLine;

  // Build command line. Substitute %work% and %file% with working directory
  // and pSourceFile respectively.
  while (*pChar != 0)
  {
    string      sBuffer;
    const char* pRootChar;
    size_t      nCount = 0;

    if (AdtParse::matchWord(pChar, "%work%", false))
    {
      sCommandLine += rParent.workingDirectory();

      pRootChar = pChar;
      pChar     = AdtParse::nextWord(pChar, &nCount);
    }
    else if (AdtParse::matchWord(pChar, "%file%", false))
    {
      sCommandLine += pSourceFile;

      pRootChar = pChar;
      pChar     = AdtParse::nextWord(pChar, &nCount);
    }
    else
    {
      string  sWord;

      AdtParse::extractWord(sWord, " \n\t", pChar);

      sCommandLine += sWord;

      pRootChar = pChar;
      pChar     = AdtParse::nextWord(pChar, &nCount);
    }

    if (nCount > 0)
    {
      sCommandLine.append(pRootChar, nCount);

      nCount = 0;
    }
  }

  ::printf("\nrunning %s with:\n%s\n", pTypeMsg, sCommandLine.c_str());

  //Run step through a pipe so we can capture stdout and redirect it here
  FILE* pPipe = popen(sCommandLine, "r");

  if (pPipe != 0)
  {
    char  pBuffer[128] = {0};

    ::printf("\n");

    while(!feof(pPipe))
    {
      if (::fgets(pBuffer, 128, pPipe) != 0)
      {
        ::printf("  %s", pBuffer);
      }
    }

    int nExitCode = pclose(pPipe);

    ::printf("\nexit code: %d\n\n", nExitCode);

    if (nExitCode != 0)
    {
      ::printf("command exited with exit code %d. Please fix issues\n\n", nExitCode);
    }
  }
}

//  ----------------------------------------------------------------------------

AdtMakeCommandOperation::AdtMakeCommandOperation()
 : FunctionName(),
   UserOptions(),
   PreCommand(),
   PostCommand(),
   Pragmas(),
   Mode(),
   VarSuffix(),
   SubSuffix(),
   ModuleSuffix(),
   BaseSubSuffix(),
   CopySubSuffix(),
   Vars(),
   OutVars()
{

}

//  ----------------------------------------------------------------------------

AdtMakeCommandOperation::AdtMakeCommandOperation(const AdtMakeCommandOperation& rCopy)
 : FunctionName(rCopy.FunctionName),
   UserOptions(rCopy.UserOptions),
   PreCommand(rCopy.PreCommand),
   PostCommand(rCopy.PostCommand),
   Pragmas(rCopy.Pragmas),
   Mode(rCopy.Mode),
   VarSuffix(rCopy.VarSuffix),
   SubSuffix(rCopy.SubSuffix),
   ModuleSuffix(rCopy.ModuleSuffix),
   BaseSubSuffix(rCopy.BaseSubSuffix),
   CopySubSuffix(rCopy.CopySubSuffix),
   Vars(rCopy.Vars),
   OutVars(rCopy.OutVars)
{

}

//  ----------------------------------------------------------------------------

AdtMakeCommandOperation::~AdtMakeCommandOperation()
{

}

//  ----------------------------------------------------------------------------

bool AdtMakeCommandOperation::shouldBuild(AdtMakeIncremental& rBuildCheck) const
{
  rBuildCheck.checkText(FunctionName);
  rBuildCheck.checkText(UserOptions);
  rBuildCheck.checkText(PreCommand);
  rBuildCheck.checkText(PostCommand);
  rBuildCheck.checkText(Pragmas);
  rBuildCheck.checkText(Mode);
  rBuildCheck.checkList(Vars);
  rBuildCheck.checkList(OutVars);

  return (rBuildCheck.build());
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommandOperation::execute(const AdtMakeCommand& rParent,
                                      AdtFortranExecutableProgram* pWorkingRoot,
                                      AdtStringList& rNewFunctionsList,
                                      AdtStringByStringMap& rPublicMethodsMap,
                                      AdtStringList& rTranslateFunctionsFromList,
                                      AdtStringList& rTranslateFunctionsToList,
                                      string& rOutputFileName,
                                      const char* pSourceFile,
                                      const char* pBlackBoxFile,
                                      const char* pClassName,
                                      int nIteration) const
{
  AdtTapenadeVersion TapenadeVersion;

  bool bDone = false;

  if (pSourceFile != 0)
  {
    AdtStringListConstIter  Iter;
    AdtStringList           FunctionAndSubroutineList;
    string                  Arguments("tapenade -inputlanguage fortran95 -outputlanguage fortran95 ");
    string                  WrtSuffix;
    string                  sNewFunctionName;
    string                  sFunctionName;
    string                  sOutputFileName;
    string                  sDeleteFileName;
    string                  sTestOutputFileName;

    VarSuffix     = "";
    SubSuffix     = "";
    ModuleSuffix  = "";
    BaseSubSuffix = "";
    CopySubSuffix = "";

    if (FunctionName.length() > 0)
    {
      qualifiedFunctionName(sFunctionName, pClassName);

      //-head, -root <proc>     set the differentiation root procedure
      Arguments         += "-head \"" + sFunctionName;
      sNewFunctionName  += sFunctionName;
    }

    if (OutVars.size() > 0)
    {
      // set outvars with -head directive.
      // Syntax:
      //  -head "{function name}({outvars list})/({w.r.t. vars list})"
      AdtParserPtrByStringMap FunctionMap;

      Arguments += "(";

      if (pWorkingRoot != 0)
      {
        AdtParserPtrList      FunctionList;
        AdtParserPtrListIter  ObjIter;

        // Build a map of all the functions in the code to be differentiated.
        // We use this to determine if the outvar is a function or var name.
        pWorkingRoot->findObjects(FunctionList,
                                  "AdtFortranFunctionSubprogram",
                                  0,
                                  false,
                                  "AdtFortranProgramUnit");

        pWorkingRoot->listToMap(FunctionMap, FunctionList);

        // Need to enumerate the subroutines for building the FunctionAndSubroutineList
        pWorkingRoot->findObjects(FunctionList,
                                  "AdtFortranSubroutineSubprogram",
                                  0,
                                  false,
                                  "AdtFortranProgramUnit");

        AdtParser::objListToNameList(FunctionAndSubroutineList, FunctionList);
      }

      for (Iter = OutVars.begin() ; Iter != OutVars.end() ; ++Iter)
      {
        const string& rOutVar = *Iter;
        string        sFunctionName;
        bool          bIsFunctionName;

        if (pClassName != 0)
        {
          sFunctionName += pClassName;
          sFunctionName += "__";
        }

        sFunctionName += rOutVar;

        bIsFunctionName = (FunctionMap.find(sFunctionName) != FunctionMap.end());

        if (Iter != OutVars.begin())
        {
           Arguments += " ";
        }

        Arguments += bIsFunctionName ? sFunctionName : rOutVar;
      }

      Arguments += ")";
    }

    if (Vars.size() > 0)
    {
      Arguments += "/(";

      // set with respect to vars with -head directive.
      // Syntax:
      //  -head "{function name}({outvars list})/({w.r.t. vars list})"
      for (Iter = Vars.begin() ; Iter != Vars.end() ; ++Iter)
      {
        const string& rVar = *Iter;

        if (Iter != Vars.begin())
        {
           Arguments += " ";
        }

        Arguments += rVar;
        WrtSuffix += rVar;
      }

      Arguments += ")";
    }

    Arguments += "\" ";

    bool bAddV = false;

    string DiffVarNameOption("-tgtvarname");
    string DiffFuncNameOption("-tgtfuncname");

    if (Mode.length() > 0)
    {
      char  sVarSuffix[32] = {0};

      //f => -tangent, -d            differentiate in the tangent mode
      //r => -reverse, -b            differentiate in the reverse mode
      if (Mode == "f")
      {
        ::sprintf(sVarSuffix, "d%d_", nIteration);

        Arguments    += "-d ";
        SubSuffix     = "_d";
        ModuleSuffix  = "_d";
        BaseSubSuffix = "_d";
      }
      else if (Mode == "m")
      {
        ::sprintf(sVarSuffix, "d%d_", nIteration);

        Arguments    += "-d -multi ";
        SubSuffix     = "_d";
        ModuleSuffix  = "_d";
        BaseSubSuffix = "_d";
        bAddV         = true;
      }
      else if (Mode == "r")
      {
        ::sprintf(sVarSuffix, "b%d_", nIteration);

        Arguments    += "-b ";
        SubSuffix     = "_b";
        ModuleSuffix  = "_b";
        BaseSubSuffix = "_b";

        DiffVarNameOption  = "-adjvarname";
        DiffFuncNameOption = "-adjfuncname";
      }
      else
      {
        ::sprintf(sVarSuffix, "d%d_", nIteration);

        Arguments    += "-d ";
        SubSuffix     = "_d";
        ModuleSuffix  = "_d";
        BaseSubSuffix = "_d";
      }

      CopySubSuffix = string("_c") + sVarSuffix;
      VarSuffix     = sVarSuffix;
    }

    VarSuffix     += WrtSuffix;
    SubSuffix     += WrtSuffix;
    CopySubSuffix += WrtSuffix;

    CopySubSuffix.toUpper();

    if (TapenadeVersion > 3.12)
    {
      Arguments += "-tgtmodulename _d -adjmodulename _b -copyname _c ";
    }

    //Special option to force more error message reporting
    Arguments += "-debug 1 ";

    //If -diffvarname is specified in user options then don't add defaults to argument list
    if (strstr(UserOptions, DiffVarNameOption.c_str()) == 0)
    {
      // -diffvarname <str>      set differentiation suffix for variables (default d and b)
      Arguments += DiffVarNameOption + " " + VarSuffix + " ";
    }

    //If -difffuncname is specified in user options then don't add defaults to argument list
    const char* pDiffFuncName = strstr(UserOptions, DiffFuncNameOption.c_str());

    if (pDiffFuncName == 0)
    {
      // -difffuncname <str>     set differentiation suffix for procedures (default _D and _B)
      Arguments += DiffFuncNameOption + " " + SubSuffix + " ";
    }
    else
    {
      // Need to extract the SubSuffix as it is used to determine the output file name
      const char* pParseText = pDiffFuncName;

      //This extract word extracts '-difffuncname'
      AdtParse::extractWord(SubSuffix, " \t\n\r", pParseText);

      //This extract word extracts <str>
      pParseText = AdtParse::nextWord(pParseText);
      AdtParse::extractWord(SubSuffix, " \t\n\r", pParseText);
    }

    if (sFunctionName.length() > 0)
    {
      sOutputFileName += sFunctionName;
    }
    else
    {
      sOutputFileName += pClassName;
    }

    // -output, -o <file>      put all generated procedures into a single <file>
    Arguments += "-o " + sOutputFileName + " ";

    if (rParent.workingDirectory().length() > 0)
    {
      // -outputdirectory, -O <directory>  put all generated files in <directory> (default .)
      Arguments += "-O " + rParent.workingDirectory() + " ";
    }

    // -ext <file>   Add any black box routine definition files to command line
    if ((pBlackBoxFile != 0) && (pBlackBoxFile[0] != 0))
    {
      Arguments += "-ext " + string(pBlackBoxFile) + " ";
    }

    if (UserOptions.length() > 0)
    {
      Arguments += " " + UserOptions + " ";
    }

    if (pSourceFile != 0)
    {
      Arguments += pSourceFile;
    }

    if (bAddV)
    {
      SubSuffix     += "v";
      ModuleSuffix  += "v";
      BaseSubSuffix += "v";
    }

    sNewFunctionName  += SubSuffix;
    sOutputFileName   += SubSuffix;

    rNewFunctionsList.push_back(sNewFunctionName);

    // Should only add to rPublicMethodsMap if parent is public.
    if (rPublicMethodsMap.find(sFunctionName) != rPublicMethodsMap.end())
    {
      rPublicMethodsMap[sNewFunctionName] = sNewFunctionName;
    }

    string  sMessageFile(sOutputFileName);
    bool    bWriteMessageFile = true;

    sMessageFile    += ".msg";

    if (PreCommand.length() > 0)
    {
      executeCommandLine(rParent, PreCommand, pSourceFile, "pre-step");
    }

    // delete previous output files so we can be sure we know when Tapenade
    // has run correctly. As it doesn't return a non-zero exit code we won't
    // know when it has failed otherwise.
    rParent.prefixWorkingDirectory(sDeleteFileName,
                                   sOutputFileName + ".f95",
                                   false);

    unlink(sDeleteFileName);

    rParent.prefixWorkingDirectory(sDeleteFileName,
                                   sOutputFileName + ".f90",
                                   false);

    unlink(sDeleteFileName);

    ::printf("\nrunning TAPENADE with:\n%s\n", Arguments.c_str());

    //Run tapenade through a pipe so we can capture stdout and redirect it here
    FILE* pPipe = popen(Arguments, "r");

    if (pPipe != 0)
    {
      char  pBuffer[128]    = {0};
      bool  bErrorMessages  = false;

      ::printf("\n");

      while(!feof(pPipe))
      {
        if (::fgets(pBuffer, 128, pPipe) != 0)
        {
          ::printf("  %s", pBuffer);

          if ((::strstr(pBuffer, "Command:") != 0) ||
              (::strstr(pBuffer, "(DD"     ) != 0) ||
              (::strstr(pBuffer, "(TC"     ) != 0) ||
              (::strstr(pBuffer, "(CF"     ) != 0) ||
              (::strstr(pBuffer, "(DF"     ) != 0) ||
              (::strstr(pBuffer, "(AD"     ) != 0))
          {
            bErrorMessages = true;
          }
        }
      }

      int nExitCode = pclose(pPipe);

      ::printf("\nexit code: %d\n\n", nExitCode);

      // Test for output file existence. If non-exstent there is a problem.
      sTestOutputFileName = sOutputFileName + ".f95";

      rParent.prefixWorkingDirectory(rOutputFileName,
                                     sTestOutputFileName,
                                     false);

      struct stat finfo = {0};

      if (::stat(rOutputFileName, &finfo) != 0)
      {
        sTestOutputFileName = sOutputFileName + ".f90";

        rParent.prefixWorkingDirectory(rOutputFileName,
                                       sTestOutputFileName,
                                       false);

        ::printf("WARNING: Expected .f95 output not found. Trying .f90 extension.\n");

        if (::stat(rOutputFileName, &finfo) != 0)
        {
          ::printf("ERROR: Tapenade output file %s (.f95 / .f90) not found.\n", sOutputFileName.c_str());

          bErrorMessages = true;
        }
      }

      if ((nExitCode != 0) || bErrorMessages)
      {
        ::printf("TAPENADE failed to compile cleanly. Please fix issues\n");

        AdtExit(-1);
      }

      if (bWriteMessageFile)
      {
        //Write the message file to standard io.
        FILE* pMsgFile = fopen(sMessageFile, "r");

        if (pMsgFile != 0)
        {
          while(!feof(pMsgFile))
          {
            if (::fgets(pBuffer, 128, pMsgFile) != 0)
            {
              ::printf("  %s", pBuffer);
            }
          }

          fclose(pMsgFile);

          ::printf("\n");
        }
      }

      // Seems current versions of Tapenade no longer create copies of code
      // that needs elimination so this is not longer required.
      if (false)
      {
        // Build translation lists. New versions of Tapenade create literal copies
        // of old code in AD'ed code with the suffix CopySubSuffix. This causes
        // massive code bloating in ADT so we swap them back using the compiler
        // translation feature.
        rTranslateFunctionsFromList.clear();
        rTranslateFunctionsToList.clear();

        for (Iter = FunctionAndSubroutineList.begin() ; Iter != FunctionAndSubroutineList.end() ; ++Iter)
        {
          const string& rToName = *Iter;
          string        sFromName(rToName);

          sFromName += CopySubSuffix;

          rTranslateFunctionsFromList.push_back(sFromName);
          rTranslateFunctionsToList.push_back(rToName);
        }
      }

      bDone = true;
    }

    sOutputFileName = sTestOutputFileName;

    if (PostCommand.length() > 0)
    {
      executeCommandLine(rParent, PostCommand, sOutputFileName, "post-step");
    }
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommandOperation::reset()
{
  FunctionName  = "";
  UserOptions   = "";
  PreCommand    = "";
  PostCommand   = "";
  Pragmas       = "";
  Mode          = "";
  VarSuffix     = "";
  SubSuffix     = "";
  BaseSubSuffix = "";
  CopySubSuffix = "";

  Vars.clear();
  OutVars.clear();
}

//  ----------------------------------------------------------------------------

const string& AdtMakeCommandOperation::qualifiedFunctionName(string& rFunctionName,
                                                             const char* pClassName) const
{
  if (pClassName != 0)
  {
    rFunctionName += pClassName;
    rFunctionName += "__";
  }

  rFunctionName += FunctionName;

  return (rFunctionName);
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommandOperation::pragma(const char* pPragmas) const
{
  bool bSet = false;

  if (pPragmas != 0)
  {
    string      sPragmas(Pragmas);
    const char* pChar = sPragmas;

    do
    {
      pChar = AdtParse::nextWord(pChar);

      if (caseless_string_comparison(pPragmas, pChar) == 0)
      {
        bSet = true;
        break;
      }

      pChar += AdtParse::wordLength(pChar, " \t\r\n", 0);
    }
    while ((pChar != 0) && (*pChar != 0));
  }

  return (bSet);
}


//  ----------------------------------------------------------------------------
//  AdtMakeClass method implementations
//  ----------------------------------------------------------------------------
void AdtMakeClass::reset()
{
  ClassName         = "";
  ParentClassName   = "";
  SourceFile        = "";
  SourceHeaderFile  = "";
  OutputFile        = "";
  OutputHeaderFile  = "";
  WorkingFile       = "";
  BlackBoxFile      = "";
  SourceFileType    = DelphiSourceFileType;
  DestFileType      = DelphiSourceFileType;
  LastModifiedTime  = 0;

  IsBlackBoxMap.clear();
  OperationsList.clear();
  BoundsCheckList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeClass::makeResult(const char* pFilenameTemp,
                              const char* pFilename,
                              const char* pCommandBlock,
                              const char* pCommandBlockName,
                              const char* pPreText,
                              const char* pPostText,
                              const AdtStringList* pSearchPaths,
                              const AdtStringList& rNewMethodList,
                              const AdtStringByStringMap& rNewMethodMap)
{
  if ((pFilenameTemp != 0) && (pFilename != 0))
  {
    AdtSourceRoot*  pGoal;
    AdtFile         FileOut;
    AdtCompiler     ParserContext(pFilename);

    AdtCppScopeManager::mapNames(true);

    //Final step: we need to compile the output and do a reverse mode macro
    //replacement operation on the code to convert Fortran intrinsics to
    //intrinsics and to also convert the stack_check calls to the appropriate
    //code. Then tis all done.
    ::printf("Expanding macros in %s\n", pFilenameTemp);

    ParserContext.parse(pFilenameTemp,
                        pCommandBlock,
                        pCommandBlockName,
                        pSearchPaths,
                        false);

    pGoal = ParserContext.sourceRoot();

    AdtCppScopeManager::mapNames(false);

    if (pGoal != 0)
    {
      if (FileOut.open(pFilename, "wt"))
      {
        pGoal->optimise(rNewMethodList,
                        rNewMethodMap);

        pGoal->expandMacros();

        if (pPreText != 0)
        {
          FileOut.write(pPreText);
        }

        pGoal->writeNative(FileOut);

        if (pPostText != 0)
        {
          FileOut.write(pPostText);
        }

        FileOut.close();
      }

      // Delete the temporary
      ::unlink(pFilenameTemp);
    }
    else
    {
      ::printf("MAKE ERROR : Failed to compile file %s\n", pFilenameTemp);

      AdtExit(-1);
    }

    ParserContext.releaseRoot();
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeClass::initFiles(string& rFile,
                             string& rHeaderFile,
                             AdtSourceFileType& rFileType,
                             const char* pFile,
                             const char* pFile2)
{
  if (pFile != 0)
  {
    UtlFilePath WorkingPath(pFile);

    if (pFile2 != 0)
    {
      UtlFilePath TestPath(pFile2);

      if ((TestPath.extension() == ".h") || (TestPath.extension() == ".hpp"))
      {
        if (WorkingPath.extension() != ".cpp")
        {
          ::printf("MAKE ERROR : Expecting '.cpp' file extension for file %s\nIs this a C++ file?\n", pFile);
          AdtExit(-1);
        }
        else
        {
          rHeaderFile = pFile2;
          rFile       = pFile;
          rFileType   = CppSourceFileType;
        }
      }
      else if (TestPath.extension() != ".cpp")
      {
        ::printf("MAKE ERROR : Expecting '.cpp' file extension for file %s\nIs this a C++ file?\n", pFile2);
        AdtExit(-1);
      }
      else
      {
        if ((WorkingPath.extension() == ".h") || (WorkingPath.extension() == ".hpp"))
        {
          WorkingPath.split(pFile2);

          rHeaderFile = pFile;
          rFile       = pFile2;
          rFileType   = CppSourceFileType;
        }
        else
        {
          ::printf("MAKE ERROR : Expecting '.h' or '.hpp' file extension for file %s\nIs this a C++ header file?\n", pFile);
          AdtExit(-1);
        }
      }
    }
    else
    {
      if (WorkingPath.extension() == ".cpp")
      {
        WorkingPath.extension(".hpp");
        WorkingPath.join(rHeaderFile);

        rFile     = pFile;
        rFileType = CppSourceFileType;
      }
      else
      {
        rFile     = pFile;
        rFileType = AdtMakeCommand::sourceFileType(rFile);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtMakeClass::AdtMakeClass()
 : ClassName(),
   ParentClassName(),
   SourceFile(),
   SourceHeaderFile(),
   OutputFile(),
   OutputHeaderFile(),
   WorkingFile(),
   BlackBoxFile(),
   IsBlackBoxMap(),
   OperationsList(),
   BoundsCheckList()
{
  SourceFileType    = DelphiSourceFileType;
  DestFileType      = DelphiSourceFileType;
  LastModifiedTime  = 0;
}

//  ----------------------------------------------------------------------------

AdtMakeClass::AdtMakeClass(const AdtMakeClass& rCopy)
 : ClassName(rCopy.ClassName),
   ParentClassName(rCopy.ParentClassName),
   SourceFile(rCopy.SourceFile),
   SourceHeaderFile(rCopy.SourceHeaderFile),
   OutputFile(rCopy.OutputFile),
   OutputHeaderFile(rCopy.OutputHeaderFile),
   WorkingFile(rCopy.WorkingFile),
   BlackBoxFile(rCopy.BlackBoxFile),
   IsBlackBoxMap(rCopy.IsBlackBoxMap),
   OperationsList(rCopy.OperationsList),
   BoundsCheckList(rCopy.BoundsCheckList)
{
  SourceFileType    = rCopy.SourceFileType;
  DestFileType      = rCopy.DestFileType;
  LastModifiedTime  = rCopy.LastModifiedTime;
}

//  ----------------------------------------------------------------------------

AdtMakeClass::~AdtMakeClass()
{

}

//  ----------------------------------------------------------------------------

string AdtMakeClass::constructIncludeDirectory(const AdtMakeCommand& rMakeCommand,
                                               const string& rRootPath) const
{
  string      sIncludeFolder;
  const char* pChar = AdtParse::nextWord(rMakeCommand.includeDirectory());

  AdtParse::matchWord(pChar, "./") || AdtParse::matchWord(pChar, ".\\");

  if (strlen(pChar) > 0)
  {
    if (rRootPath.length() > 0)
    {
      sIncludeFolder += rRootPath + "/";
    }

    sIncludeFolder += pChar;
  }

  return (unixifyFilePath(sIncludeFolder));
}

//  ----------------------------------------------------------------------------

int AdtMakeClass::make(AdtMakeCommand& rParent,
                       AdtParserPtrList& rCodeList,
                       AdtMakeClassPtrByStringMap& rWorkingMakeByClass,
                       AdtFortranExecutableProgram* pCallExpandRoot,
                       const char** pOptionsFileTexts,
                       const char** pOptionsFileNames,
                       const char* pFortranInclude,
                       AdtMakeIncremental& rBuildCheck,
                       int nClassNumber)
{
  int                 nReturnCode    = 0;
  AdtSourceRoot*      pGoal          = 0;
  string              rFileAndPath;
  AdtTapenadeVersion  TapenadeVersion;

  //Parse source
  if (rParent.findFile(SourceFile, rFileAndPath))
  {
    AdtCompiler ParserContext(rFileAndPath);

    rBuildCheck.checkFile(rFileAndPath);
    rBuildCheck.checkList(BoundsCheckList);

    if (ParserContext.isValid())
    {
      UtlFilePath SourcePath(rFileAndPath);
      string      SourceFolder;

      SourcePath.name("");
      SourcePath.extension("");
      SourcePath.join(SourceFolder);

      string sIncludeFolder(constructIncludeDirectory(rParent, SourceFolder));

      AdtAutoClass::enableAutomation(true, true);
      AdtCppScopeManager::globalScopeManager()->pushScope("Preprocess", false);

      ::printf("Preprocess %s\n", SourceFile.c_str());

      ParserContext.parse(rFileAndPath,
                          pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                          pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                          &rParent.paths(),
                          true);

      ParserContext.releaseRoot();

      // Fix the chicken and egg problem of needing the constructor args files
      // to compile the makefile correctly but not being in a position to export
      // all files yet because we need to do all the AD operations first.
      AdtAutoClass::exportConstructorArgsFiles(SourceFileType, sIncludeFolder);
      AdtAutoClass::enableAutomation(false, false);
      AdtCppScopeManager::globalScopeManager()->popScope();

      ::printf("Compiling %s\n", SourceFile.c_str());

      AdtMakeSystem::clearIncludeList();

      ParserContext.parse(rFileAndPath,
                          pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                          pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                          &rParent.paths(),
                          true);

      AdtMakeSystem::checkIncludes(rBuildCheck, rParent);

      pGoal = ParserContext.sourceRoot();

      if (pGoal != 0)
      {
        nReturnCode = 0;

        if (0)
        {
          //Test write parsed code.
          AdtFile Test;
          string  TestFile(rFileAndPath);

          TestFile += ".rec";

          if (Test.open(TestFile, "wt"))
          {
            pGoal->writeNative(Test);

            Test.close();
          }
        }

        string rParentsParentClassName;

        if (pGoal->hasClass(ParentClassName, rParentsParentClassName))
        {
          AdtStringList GlobalBoundsCheckList;

          if (rParent.switchDefined("BoundsCheck"))
          {
            // Find all the methods defined in this class and create a name list
            // of them. We need this in the event that someone requests a global
            // bounds check.
            pGoal->enumerateMethodNames(GlobalBoundsCheckList);
          }

          // Check to see if the parent class of pClassType is in the map of currently
          // AD'ed working fortran files. If it is we use the corresponding working
          // file to merge with, otherwise we build the fortran file by merging
          // sources and translating to fortran.
          AdtFortran                    FortranContext;
          AdtMakeClass*                 pWorkingMake      = 0;
          AdtFortranExecutableProgram*  pSavedWorkingRoot = 0;

          if (rParentsParentClassName.length() > 0)
          {
            AdtMakeClassPtrByStringMapIter  Iter = rWorkingMakeByClass.find(rParentsParentClassName);

            ::printf("\nIs parent class %s in Fortran form? ", rParentsParentClassName.c_str());

            if (Iter != rWorkingMakeByClass.end())
            {
              pWorkingMake = (*Iter).second;
              ::printf("yes\n");
            }
            else
            {
              ::printf("no\n");
            }
          }

          ::printf("\nFlattening class %s\n", ParentClassName.c_str());

          // Merge source and translate to fortran working file
          AdtStringByStringMap  rRegardAsClassFunctionsMap;
          AdtStringByStringMap  rRegardAsClassSubroutineMap;
          AdtStringByStringMap  rPublicMethodsMap;
          AdtStringList         ConstructorList;
          AdtParserPtrList      IdentList;
          AdtParserPtrListIter  Iter;
          string                UsesList;
          string                rLastWorkingFile;
          string                rLastClassName;
          bool                  bHasBlackBoxFile = false;
          bool                  bHaveSavedWorkingRoot;

          //Merge all sources by flattening the class
          if (pWorkingMake != 0)
          {
            AdtParserPtrList rEmptyCodeList;

            pWorkingMake->lastWorkingFile(rLastWorkingFile);

            FortranContext.parse(rLastWorkingFile, 0, 0, &rParent.paths());

            pSavedWorkingRoot = AdtFortranBase::fortranRootObject();

            if (pSavedWorkingRoot != 0)
            {
              // Build a map of function names that should be regarded as class
              // methods in the translation to fortran
              string sClassPrefix(pWorkingMake->parentClassName());

              rLastClassName = sClassPrefix;
              sClassPrefix  += "__";

              pSavedWorkingRoot->enumerateFunctionNames(rRegardAsClassFunctionsMap, sClassPrefix);
              pSavedWorkingRoot->enumerateSubroutineNames(rRegardAsClassSubroutineMap, sClassPrefix);
              pSavedWorkingRoot->lock();

              adtFortran_releaseRoot();
            }
            else
            {
              ::printf("MAKE ERROR : Failed to compile file %s\n", rLastWorkingFile.c_str());
              AdtExit(-1);
            }

            pGoal->flattenClass(ParentClassName, rEmptyCodeList, UsesList, rPublicMethodsMap);

            // Must do this after flatten class as the above imports code from
            // rCodeList which may contain black box definitions
            pGoal->buildBlackBoxFile(0,
                                     rRegardAsClassFunctionsMap,
                                     rRegardAsClassSubroutineMap,
                                     TapenadeVersion);

            struct stat StatBuf;

            bHasBlackBoxFile      = (::stat(BlackBoxFile, &StatBuf) == 0);
            bHaveSavedWorkingRoot = true;
          }
          else
          {
            pGoal->flattenClass(ParentClassName, rCodeList, UsesList, rPublicMethodsMap);

            // Must do this after flatten class as the above imports code from
            // rCodeList which may contain black box definitions
            bHasBlackBoxFile      = pGoal->buildBlackBoxFile(BlackBoxFile,
                                                             rRegardAsClassFunctionsMap,
                                                             rRegardAsClassSubroutineMap,
                                                             TapenadeVersion);

            bHaveSavedWorkingRoot = false;
          }

          pGoal->appendIsBlackBoxMap(IsBlackBoxMap);
          pGoal->expandMacros();
          pGoal->extractClassConstructors(ConstructorList, ClassName, ParentClassName, sIncludeFolder, destFileType());

          //Write merged and flattened source
          string  OutputFileTemp(OutputFile);
          AdtFile FileOut;

          OutputFileTemp += ".tmp";

          if (FileOut.open(OutputFileTemp, "wt"))
          {
            AdtCppDeclaration::writeFlatFile(true);

            pGoal->writeNative(FileOut);

            AdtCppDeclaration::writeFlatFile(false);

            FileOut.close();
          }

          if (0)
          {
            //Test write flattened code.
            AdtFile Test;
            string  TestFile(rFileAndPath);

            TestFile += ".flat";

            if (Test.open(TestFile, "wt"))
            {
              pGoal->writeNative(Test);

              Test.close();
            }
          }

          ParserContext.releaseRoot();

          //Now translate the entire module to fortran
          AdtFile FortranOut(true);
          string  rWorkingFile;
          string  rCachedWorkingFile;
          int     nIteration = 0;
          bool    bHasCachedWorkingFile = false;

          bHasCachedWorkingFile = workingFile(rWorkingFile, nIteration);
          rCachedWorkingFile    = rWorkingFile + ".tmp";

          if (bHasCachedWorkingFile)
          {
            // Save the working file so we can restore it if we need to
            AdtFileCopy Copy(rWorkingFile, rCachedWorkingFile);
          }

          if (FortranOut.open(rWorkingFile, "wt"))
          {
            AdtFortranExecutableProgram*  pWorkingRoot = 0;

            //Re-compile the flattened source to obtain a valid parse tree. The macro
            //replacement process uses tricks to build the macro replaced code which
            //results in an invalid parse tree that must be re-built before translation
            //into fortran.
            ::printf("Re-compiling code\n");

            ParserContext.parse(OutputFileTemp,
                                pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                                pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(SourceFileType)],
                                &rParent.paths(),
                                true);

            pGoal = ParserContext.sourceRoot();

            if (pGoal != 0)
            {
              if ((pWorkingMake == 0) && (pFortranInclude != 0))
              {
                // Add fortran includes
                FortranOut.write(pFortranInclude);
              }

              // translate the entire module to fortran
              pGoal->isBlackBoxMap(IsBlackBoxMap);
              pGoal->regardAsClassFunctions(rRegardAsClassFunctionsMap);
              pGoal->regardAsClassSubroutines(rRegardAsClassSubroutineMap);
              pGoal->writeClassMethodsAsFortran(FortranOut,
                                                pSavedWorkingRoot,
                                                ParentClassName,
                                                rLastClassName,
                                                false);

              UtlReleaseReference(pSavedWorkingRoot);

              pSavedWorkingRoot = 0;

              FortranOut.close();
              ParserContext.releaseRoot();

              //Now compile the Fortran code to obtain a parse tree for it. We shall use
              //this parse tree for maintaining the Fortran source as we proceed through
              //the various make operations that produce extra Fortran code as a result.
              ::printf("\nCompiling working file %s\n", rWorkingFile.c_str());

              FortranContext.parse(rWorkingFile, 0, 0, &rParent.paths());

              pWorkingRoot = AdtFortranBase::fortranRootObject();

              if (pWorkingRoot != 0)
              {
                AdtStringList                   NewMethodList;
                AdtStringByStringMap            NewMethodMap;
                AdtStringList                   NewAttributeList;
                AdtStringByStringMap            NewAttributeMap;
                AdtMakeCommandOperationListIter Iter;
                bool                            bRebuildWorkingRoot = false;

                pWorkingRoot->lock();
                pWorkingRoot->initialise();
                adtFortran_releaseRoot();

                if (rBuildCheck.build())
                {
                  if (bHaveSavedWorkingRoot)
                  {
                    AdtStringList                 IgnoreNewMethodList;
                    AdtStringByStringMap          IgnoreNewMethodMap;
                    AdtStringList                 IgnoreNewAttributeList;
                    AdtStringByStringMap          IgnoreNewAttributeMap;
                    int                           nIteration = 0;

                    // Merge fortran translation with working file
                    ::printf("Merging working file %s into working file %s\n", rLastWorkingFile.c_str(), rWorkingFile.c_str());

                    FortranContext.parse(rLastWorkingFile, 0, 0, &rParent.paths());

                    pSavedWorkingRoot = AdtFortranBase::fortranRootObject();

                    pSavedWorkingRoot->initialise();
                    pWorkingRoot->mergeWith(pSavedWorkingRoot,
                                            pCallExpandRoot,
                                            0,
                                            nIteration,
                                            IgnoreNewMethodList,
                                            IgnoreNewMethodMap,
                                            IgnoreNewAttributeList,
                                            IgnoreNewAttributeMap,
                                            pWorkingMake->parentClassName(),
                                            0,
                                            &NewAttributeList,
                                            &NewAttributeMap);

                    adtFortran_releaseRoot();

                    pSavedWorkingRoot     = 0;
                    bHaveSavedWorkingRoot = false;

                    //Write the merged file output
                    if (FortranOut.open(rWorkingFile, "wt"))
                    {
                      AdtFortranName::setClearPrefix(0);
                      AdtFortranBase::setChangePrefix(pWorkingMake->parentClassName(), parentClassName());

                      pWorkingRoot->writeFortran(FortranOut);
                      FortranOut.close();

                      UtlReleaseReference(pWorkingRoot);

                      AdtFortranName::setClearPrefix(0);
                      AdtFortranBase::setChangePrefix(0, 0);

                      //Re-compile file to obtain consistent parse tree
                      FortranContext.parse(rWorkingFile, 0, 0, &rParent.paths());

                      pWorkingRoot = AdtFortranBase::fortranRootObject();

                      if (pWorkingRoot != 0)
                      {
                        pWorkingRoot->lock();
                        pWorkingRoot->initialise();
                        adtFortran_releaseRoot();
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Failed to compile file %s\n", rWorkingFile.c_str());

                        AdtExit(-1);
                      }
                    }
                  }
                }
                else
                {
                  if (bHasCachedWorkingFile)
                  {
                    // Restore the working file
                    AdtFileCopy Copy(rCachedWorkingFile, rWorkingFile);

                    ::unlink(rCachedWorkingFile);
                  }

                  bRebuildWorkingRoot = true;
                }

                //Now do the auto-differentiation operations
                int           nIteration          = 0;
                AdtStringList rVarSuffixList;

                for (Iter = OperationsList.begin() ; Iter != OperationsList.end() ; ++Iter)
                {
                  string                          sOutputFile;
                  string                          rPrevWorkingFile(rWorkingFile);
                  const AdtMakeCommandOperation&  rOperation = *Iter;
                  AdtStringList                   rNewFunctionsList;
                  AdtStringList                   rTranslateFunctionsFromList;
                  AdtStringList                   rTranslateFunctionsToList;
                  bool                            bWorkingFileExists;

                  nIteration++;

                  bWorkingFileExists = workingFile(rWorkingFile, nIteration);

                  // Here we should do a check on the operation to see if we have
                  // an exisiting solution we can use or whether we need to re-
                  // calculate it.
                  if (!bWorkingFileExists || rOperation.shouldBuild(rBuildCheck))
                  {
                    AdtFileCopy Copy(rPrevWorkingFile, rWorkingFile);

                    if (bRebuildWorkingRoot)
                    {
                      UtlReleaseReference(pWorkingRoot);

                      AdtFortranName::setClearPrefix(0);
                      AdtFortranBase::setChangePrefix(0, 0);

                      //Re-compile working root
                      ::printf("Re-compiling working file %s\n", rWorkingFile.c_str());
                      FortranContext.parse(rWorkingFile, 0, 0, &rParent.paths());

                      pWorkingRoot = AdtFortranBase::fortranRootObject();

                      if (pWorkingRoot != 0)
                      {
                        pWorkingRoot->lock();
                        pWorkingRoot->initialise();
                        adtFortran_releaseRoot();
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Failed to compile file %s\n", rWorkingFile.c_str());

                        AdtExit(-1);
                      }

                      bRebuildWorkingRoot = false;
                    }

                    if (rOperation.execute(rParent,
                                           pWorkingRoot,
                                           rNewFunctionsList,
                                           rPublicMethodsMap,
                                           rTranslateFunctionsFromList,
                                           rTranslateFunctionsToList,
                                           sOutputFile,
                                           rWorkingFile,
                                           bHasBlackBoxFile ? BlackBoxFile.c_str() : 0,
                                           ParentClassName,
                                           nIteration))
                    {
                      AdtFortranExecutableProgram*  pAutodiffRoot = 0;

                      rVarSuffixList.push_back(rOperation.varSuffix());

                      AdtFortranBase::PushPopDisable = rOperation.pragma("PushPopDisable");

                      //Now compile the tapenade generated source from sOutputFile.
                      ::printf("Compiling result file %s\n", sOutputFile.c_str());

                      FortranContext.setPushPopSubstitution(rOperation.subSuffix(), rOperation.baseSubSuffix());
                      FortranContext.addTranslation(rTranslateFunctionsFromList, rTranslateFunctionsToList);

                      FortranContext.parse(sOutputFile, 0, 0, &rParent.paths());

                      FortranContext.removeTranslation(rTranslateFunctionsFromList);
                      FortranContext.clearPushPopSubstitution(rOperation.subSuffix());

                      pAutodiffRoot = AdtFortranBase::fortranRootObject();

                      if (pAutodiffRoot != 0)
                      {
                        string  sFunctionName;

                        pAutodiffRoot->initialise();

                        if (0)
                        {
                          char  sBuffer[16];

                          //Test code to see if fortran compilation working
                          AdtFile TestFortranOut(true);
                          string  TestFile(rWorkingFile);

                          ::sprintf(sBuffer, ".pre.%d", nIteration);

                          TestFile += sBuffer;

                          if (TestFortranOut.open(TestFile, "wt"))
                          {
                            pAutodiffRoot->writeFortran(TestFortranOut);
                            TestFortranOut.close();
                          }
                        }

                        // With the parse tree we need to figure out what functions / subroutines are new
                        // (ie. not in the original source) and add it to that source. Similarly,
                        // for the new modules that tapenade creates we need to merge those
                        // variables contained within into the original module, then carry out the
                        // next operation.
                        ::printf("Merging result file %s into working file %s\n", sOutputFile.c_str(), rWorkingFile.c_str());
                        pWorkingRoot->mergeWith(pAutodiffRoot,
                                                pCallExpandRoot,
                                                &rNewFunctionsList,
                                                nIteration,
                                                NewMethodList,
                                                NewMethodMap,
                                                NewAttributeList,
                                                NewAttributeMap,
                                                ParentClassName,
                                                rOperation.moduleSuffix());

                        //Write the merged file output
                        if (FortranOut.open(rWorkingFile, "wt"))
                        {
                          pWorkingRoot->writeFortran(FortranOut);
                          FortranOut.close();
                        }
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Failed to compile file %s\n", sOutputFile.c_str());

                        AdtExit(-1);
                      }

                      adtFortran_releaseRoot();
                    }

                    string  sClassPrefix(parentClassName());

                    sClassPrefix += "__";

                    AdtParser::nameListToNameMap(rPublicMethodsMap, BoundsCheckList, sClassPrefix);
                  }
                  else
                  {
                    ::printf("Using cached working file %s\n", rWorkingFile.c_str());

                    bRebuildWorkingRoot = true;
                  }
                }

                UtlReleaseReference(pWorkingRoot);

                // Log the working make in our map of working makes by class
                rWorkingMakeByClass[ClassName] = this;

                if (rBuildCheck.build())
                {
                  // Re-compile the fortran code. We do this to obtain a symantically
                  // consistent parse tree which isn't the case without this step.
                  ::printf("Re-compiling working file %s\n", rWorkingFile.c_str());

                  FortranContext.parse(rWorkingFile, 0, 0, &rParent.paths());

                  pWorkingRoot = AdtFortranBase::fortranRootObject();

                  if (pWorkingRoot != 0)
                  {
                    AdtFile* pVariablesDebugFile  = 0;
                    bool     bVariablesDebug      = false;
                    bool     bThrowException      = rParent.switchDefined("ThrowException");

                    if (bVariablesDebug)
                    {
                      string  TestFile(rWorkingFile);

                      TestFile += ".vars";

                      pVariablesDebugFile = new AdtFile;

                      pVariablesDebugFile->open(TestFile, "wt");

                      ::printf("Writing known variables to %s\n", TestFile.c_str());
                    }

                    // Put in stack size checking for stack read / write operations
                    ::printf("Adding stack fixups\n");
                    pWorkingRoot->addStackFixups(NewMethodMap);

                    //Call initialise to obtain variable info on functions prior to
                    //doing slice fixups. We need that info to do slice fixups and we
                    //must do this after stack fixups as that can add variables.
                    pWorkingRoot->initialise();

                    string  sClassPrefix(parentClassName());

                    sClassPrefix += "__";

                    rBuildCheck.updateNewMethodsAndAttributes(parentClassName(),
                                                              NewMethodMap,
                                                              NewMethodList,
                                                              NewAttributeMap,
                                                              NewAttributeList);

                    // Put in slice operation function calls and optional bounds checking
                    if ((BoundsCheckList.size() > 0) || (GlobalBoundsCheckList.size() > 0))
                    {
                      ::printf("Adding slice fixups and bounds checks\n");
                    }
                    else
                    {
                      ::printf("Adding slice fixups\n");
                    }

                    pWorkingRoot->addSliceFixups(NewMethodMap,
                                                 NewMethodList,
                                                 BoundsCheckList,
                                                 GlobalBoundsCheckList,
                                                 sClassPrefix,
                                                 pVariablesDebugFile,
                                                 bThrowException);

                    if (bVariablesDebug)
                    {
                      pVariablesDebugFile->close();

                      delete pVariablesDebugFile;
                      pVariablesDebugFile = 0;
                    }

                    //adding slice fixups can add new stack variables so we need to re-initialise.
                    pWorkingRoot->initialise();

                    if (0)
                    {
                      //Test code to see if fortran compilation working
                      AdtFile TestFortranOut(true);
                      string  TestFile(rWorkingFile);

                      TestFile += ".post_fixups";

                      if (TestFortranOut.open(TestFile, "wt"))
                      {
                        pWorkingRoot->writeFortran(TestFortranOut);
                        TestFortranOut.close();
                      }
                    }

                    // Now back translate to source format, building the new required class
                    // definition on the way. To do this we need to make a derived class
                    // from the parent class that includes only additional functions and
                    // data created by tapenade.
                    if (destFileType() == CppSourceFileType)
                    {
                      string  HeaderFileTemp(OutputHeaderFile);
                      AdtFile CppHeader;

                      HeaderFileTemp += ".tmp";

                      if (CppHeader.open(HeaderFileTemp, "wt"))
                      {
                        string  sPreText;
                        string  sPostText;

                        pWorkingRoot->writeCPP_ClassHeader(CppHeader,
                                                           SourceHeaderFile,
                                                           rPublicMethodsMap,
                                                           NewMethodList,
                                                           NewAttributeList,
                                                           ClassName,
                                                           ParentClassName,
                                                           sIncludeFolder,
                                                           ConstructorList,
                                                           sPreText,
                                                           sPostText);

                        CppHeader.close();

                        // Note the false entry for the bWithAttributeDefsEnabled
                        // parameter. We disable it because we are compiling auto-generated
                        // code and we do not want it treating added attributes as
                        // new array types with needed interfaces as this will result
                        // in processing errors. We do however need added functions
                        // to have interfaces so these aren't affected by this switch.
                        AdtAutoClass::enableAutomation(true, false);

                        makeResult(HeaderFileTemp,
                                   OutputHeaderFile,
                                   pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   sPreText,
                                   sPostText,
                                   &rParent.paths(),
                                   NewMethodList,
                                   NewMethodMap);

                        AdtAutoClass::exportAutomationFiles(SourceFileType, SourceFolder, sIncludeFolder, ClassName, nClassNumber);
                        AdtAutoClass::enableAutomation(false, false);
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Can't open file %s for writing\n", HeaderFileTemp.c_str());

                        AdtExit(-1);
                      }

                      AdtFile CppSource;

                      if (CppSource.open(OutputFileTemp, "wt"))
                      {
                        string  sPreText;
                        string  sPostText;

                        pWorkingRoot->writeCPP_ClassImplementation(CppSource,
                                                                   OutputHeaderFile,
                                                                   NewMethodList,
                                                                   NewAttributeList,
                                                                   ClassName,
                                                                   ParentClassName,
                                                                   sIncludeFolder,
                                                                   ConstructorList,
                                                                   &rVarSuffixList,
                                                                   sPreText,
                                                                   sPostText);

                        CppSource.close();

                        makeResult(OutputFileTemp,
                                   OutputFile,
                                   pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   sPreText,
                                   sPostText,
                                   &rParent.paths(),
                                   NewMethodList,
                                   NewMethodMap);
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Can't open file %s for writing\n", OutputFileTemp.c_str());

                        AdtExit(-1);
                      }
                    }
                    else
                    {
                      if (FileOut.open(OutputFileTemp, "wt"))
                      {
                        ::printf("Building output file %s\n", OutputFileTemp.c_str());

                        pWorkingRoot->writeDelphiClass(FileOut,
                                                       rPublicMethodsMap,
                                                       NewMethodList,
                                                       NewAttributeList,
                                                       ClassName,
                                                       ParentClassName,
                                                       sIncludeFolder,
                                                       ConstructorList,
                                                       UsesList,
                                                       &rVarSuffixList);

                        FileOut.close();

                        // Add translation of C / C++ __FILE__ and __LINE__
                        // macros into delphi equivalents
                        AdtCommon::addTranslation("__FILE__", "{$I %FILE%}");
                        AdtCommon::addTranslation("__LINE__", "{$I %LINE%}");

                        // Note the false entry for the bWithAttributeDefsEnabled
                        // parameter. We disable it because we are compiling auto-generated
                        // code and we do not want it treating added attributes as
                        // new array types with needed interfaces as this will result
                        // in processing errors. We do however need added functions
                        // to have interfaces so these aren't affected by this switch.
                        AdtAutoClass::enableAutomation(true, false);

                        makeResult(OutputFileTemp,
                                   OutputFile,
                                   pOptionsFileTexts[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   pOptionsFileNames[AdtMakeCommand::fileTypeToIndex(DestFileType)],
                                   0,
                                   0,
                                   &rParent.paths(),
                                   NewMethodList,
                                   NewMethodMap);

                        AdtAutoClass::exportAutomationFiles(SourceFileType, SourceFolder, sIncludeFolder, ClassName, nClassNumber);
                        AdtAutoClass::enableAutomation(false, false);

                        AdtCommon::removeTranslation("__FILE__");
                        AdtCommon::removeTranslation("__LINE__");
                      }
                      else
                      {
                        ::printf("MAKE ERROR : Can't open file %s for writing\n", OutputFileTemp.c_str());

                        AdtExit(-1);
                      }
                    }

                    adtFortran_releaseRoot();
                  }
                  else
                  {
                    ::printf("MAKE ERROR : Failed to compile file %s\n", rWorkingFile.c_str());

                    AdtExit(-1);
                  }
                }
              }
              else
              {
                ::printf("MAKE ERROR : Failed to compile file %s\n", rWorkingFile.c_str());

                AdtExit(-1);
              }
            }
            else
            {
              ::printf("MAKE ERROR : Failed to compile file %s\n", OutputFileTemp.c_str());

              AdtExit(-1);
            }
          }
          else
          {
            ::printf("MAKE ERROR : Cannot open working file %s\nMake sure the working folder exists\n\n",
                     rWorkingFile.c_str());

            AdtExit(-1);
          }
        }
        else
        {
          // class not defined
          ::printf("MAKE ERROR : Class %s not defined in file %s\n",
                   ParentClassName.c_str(),
                   SourceFile.c_str());

          AdtExit(-1);
        }
      }
      else
      {
        ::printf("MAKE ERROR : Compile failed\n");

        AdtExit(-1);
      }

      ParserContext.releaseRoot();
    }
    else
    {
      ::printf("MAKE ERROR : No parser available for %s\n",
               SourceFile.c_str());

      AdtExit(-1);
    }
  }
  else
  {
    //Can't find file
    ::printf("MAKE ERROR : Can't find file %s\n", SourceFile.c_str());

    AdtExit(-1);
  }

  return (nReturnCode);
}

//  ----------------------------------------------------------------------------

void AdtMakeClass::newMakeClass(const AdtMakeCommand& rMakeCommand,
                                const char* pNewClassName,
                                const char* pParentClassName,
                                const char* pSourceFile,
                                const char* pSourceFile2,
                                const char* pOutputFile,
                                const char* pOutputFile2)
{
  reset();

  AdtTapenadeVersion  TapenadeVersion(true);

  if (pNewClassName != 0)
  {
    ClassName = pNewClassName;
  }

  if (pParentClassName != 0)
  {
    ParentClassName = pParentClassName;
  }

  initFiles(SourceFile,
            SourceHeaderFile,
            SourceFileType,
            pSourceFile,
            pSourceFile2);

  initFiles(OutputFile,
            OutputHeaderFile,
            DestFileType,
            pOutputFile,
            pOutputFile2);

  string      sWorkingFile;
  string      sBlackBoxFile;
  UtlFilePath WorkingPath(OutputFile);

  WorkingPath.drive("");
  WorkingPath.directory("");
  WorkingPath.extension(".f95");
  WorkingPath.join(sWorkingFile);

  rMakeCommand.prefixWorkingDirectory(WorkingFile,
                                      sWorkingFile,
                                      false);

  WorkingPath.extension("_bb.txt");
  WorkingPath.join(sBlackBoxFile);

  rMakeCommand.prefixWorkingDirectory(BlackBoxFile,
                                      sBlackBoxFile,
                                      false);

  // Delete black box file and for all stand-alone black box files append
  // black box definitions to this file.
  ::unlink(BlackBoxFile);

  const AdtStringList&    rBlackBoxList = rMakeCommand.blackBoxList();
  AdtStringListConstIter  Iter;

  for (Iter = rBlackBoxList.begin() ; Iter != rBlackBoxList.end() ; ++Iter)
  {
    const string& rFileAndPath = *Iter;

    // Compile definition file into Tapenade compatible format and append it
    // to the output file.
    AdtBlackBoxCompiler::makeBlackBoxFile(rFileAndPath, BlackBoxFile, IsBlackBoxMap, true, TapenadeVersion);
  }

  string sExtFileAndPath;

  // Append black box include file
  if (rMakeCommand.findFile("my_extlib.txt", sExtFileAndPath))
  {
    AdtFileCopy Append(sExtFileAndPath, BlackBoxFile, true);
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeClass::addOperation(const AdtMakeCommandOperation& rOperation)
{
  OperationsList.push_back(rOperation);
}

//  ----------------------------------------------------------------------------

void AdtMakeClass::boundsCheck(const AdtStringList& rBoundsCheckList)
{
  BoundsCheckList.assign(rBoundsCheckList.begin(), rBoundsCheckList.end());
}

//  ----------------------------------------------------------------------------

bool AdtMakeClass::workingFile(string& rWorkingFile, size_t nIteration) const
{
  struct stat Status;
  char        sBuffer[16] = {0};
  bool        bExists;

  UtlFilePath WorkingPath(WorkingFile);

  ::sprintf(sBuffer, ".%zd", nIteration);
  WorkingPath.name(WorkingPath.name() + sBuffer);
  WorkingPath.join(rWorkingFile);

  bExists = (stat(rWorkingFile, &Status) == 0);

  return (bExists);
}

//  ----------------------------------------------------------------------------

bool AdtMakeClass::lastWorkingFile(string& rWorkingFile) const
{
  return (workingFile(rWorkingFile, OperationsList.size()));
}


//  ----------------------------------------------------------------------------
//  AdtMakeCommand method implementations
//  ----------------------------------------------------------------------------
void AdtMakeCommand::reset()
{
  WorkingDirectory  = "";
  IncludeDirectory  = "";
  SourceFileType    = UnknownSourceFileType;

  Switches.clear();
  Paths.clear();
  BlackBoxList.clear();
  SourceFiles.clear();
  ClassList.clear();
  addDefaultPaths();
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::addDefaultPaths()
{
  // Add default paths to ADT includes plus ADLib includes. On linux like
  // environments these are:
  //
  // /usr/local/share/adt/include
  // /usr/local/include
  // /usr/local/share/adt/templates/source/cpp
  // /usr/local/share/adt/templates/source/pascal
  //
  // On Windows these are:
  //
  // {adt exe path}/adt-include
  // {adt exe path}/include
  // {adt exe path}/../templates/source/cpp
  // {adt exe path}/../templates/source/pascal
  string sADT_include;
  string sADTSrc_include;
  string sADLib_include;
  string sADLibPas_include;

  #if defined(_MSC_VER)

  AdtExePath  sPath;
  string      sExePath(sPath);
  string      sExePathLessSlash(sExePath);
  string      sRootPath;

  sExePathLessSlash.left(sExePathLessSlash.length() - 1);

  UtlFilePath rPath(sExePathLessSlash);

  rPath.name("");
  rPath.extension("");
  rPath.join(sRootPath);

  sADT_include      = sExePath + "adt-include\\";
  sADTSrc_include   = sRootPath + "include\\";
  sADLib_include    = sRootPath + "templates\\source\\cpp\\";
  sADLibPas_include = sRootPath + "templates\\source\\pascal\\";

  #else

  sADT_include      = "/usr/local/share/adt/include/";
  sADTSrc_include   = "/usr/local/include/";
  sADLib_include    = "/usr/local/share/adt/templates/source/cpp/";
  sADLibPas_include = "/usr/local/share/adt/templates/source/pascal/";

  #endif

  Paths.push_back(sADT_include);
  Paths.push_back(sADTSrc_include);
  Paths.push_back(sADLib_include);
  Paths.push_back(sADLibPas_include);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::fixDirectory(string& rDirectory,
                                  const char* pDirectory,
                                  const char* pTypeName,
                                  bool bNoSubDirectories)
{
  // Make sure the directory path ends in a slash
  if (pDirectory != 0)
  {
    int   nOffset;
    char  nLastChar;

    rDirectory = pDirectory;

    switch (pDirectory[0])
    {
      case '\"':
      case '\'':
      {
        rDirectory.trim("\"\'");
        nOffset = 2;
        break;
      }

      default:
      {
        nOffset = 1;
        break;
      }
    }

    if (bNoSubDirectories)
    {
      bool        bOk;
      string      sWord;
      const char* pDirectory  = rDirectory.c_str();
      const char* pChar       = AdtParse::nextWord(pDirectory);

    #if defined(_MSC_VER)
      AdtParse::matchWord(pChar, "./") || AdtParse::matchWord(pChar, ".\\");
      AdtParse::extractWord(sWord, "/\\", pChar, false);

      pChar = AdtParse::nextWord(pChar);

      AdtParse::matchWord(pChar, "/") || AdtParse::matchWord(pChar, "\\");
    #else
      AdtParse::matchWord(pChar, "./");
      AdtParse::extractWord(sWord, "/", pChar, false);

      pChar = AdtParse::nextWord(pChar);

      AdtParse::matchWord(pChar, "/");
    #endif

      bOk   = (*pChar == 0) && (sWord.length() > 0);

      if (!bOk)
      {
        // Working has sub-directories
         ::printf("MAKE ERROR : %s folder %s must be only one level deep and relative to the project folder\n\n",
                 pTypeName,
                 rDirectory.c_str());

        AdtExit(-1);
      }
    }

    nLastChar = pDirectory[::strlen(pDirectory) - nOffset];

    switch (nLastChar)
    {
      case '\\':
      case '/':
      {
        break;
      }

      default:
      {
        rDirectory += "/";
        break;
      }
    }

    // Make sure the working directory exists and if not create it.
    struct stat status = {0};
    string      TestDir(rDirectory);

    TestDir.trimRight("/\\");

    if (stat(TestDir, &status) == 0)
    {
      if ((status.st_mode & S_IFDIR) != S_IFDIR)
      {
        // Working directory exists but it isn't a directory.
        ::printf("MAKE ERROR : %s folder %s is a file\nchange the name of the %s folder\n\n",
                 pTypeName,
                 TestDir.c_str(),
                 pTypeName);

        AdtExit(-1);
      }
    }
    else
    {
      if (adt_mkdir(TestDir) != 0)
      {
        // mkdir failed
        ::printf("MAKE ERROR : Cannot create %s folder %s\nCheck folder permissions\nerror number %d\n\n",
                 pTypeName,
                 TestDir.c_str(), errno);

        AdtExit(-1);
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::prefixDirectory(const string& rDirectory,
                                     string& rResultFileName,
                                     const char* pFileName,
                                     bool bQuote) const
{
  if ((pFileName != 0) && (pFileName[0] != 0))
  {
    string StrippedFileName(pFileName);

    StrippedFileName.trim("\"\'");

    if (rDirectory.length() > 0)
    {
      string StrippedDirectory(rDirectory);

      StrippedDirectory.trim("\"\'");

      if (bQuote)
      {
        rResultFileName = "\"" + StrippedDirectory + StrippedFileName + "\"";
      }
      else
      {
        rResultFileName = StrippedDirectory + StrippedFileName;
      }
    }
    else
    {
      if (bQuote)
      {
        rResultFileName = "\"" + StrippedFileName + "\"";
      }
      else
      {
        rResultFileName = StrippedFileName;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

AdtMakeCommand::AdtMakeCommand()
 : WorkingDirectory(),
   IncludeDirectory(),
   Switches(),
   Paths(),
   BlackBoxList(),
   SourceFiles(),
   FortranIncludeFiles(),
   ClassList()
{
  SourceFileType = UnknownSourceFileType;
}

//  ----------------------------------------------------------------------------

AdtMakeCommand::AdtMakeCommand(const AdtMakeCommand& rCopy)
 : WorkingDirectory(rCopy.WorkingDirectory),
   IncludeDirectory(rCopy.IncludeDirectory),
   Switches(rCopy.Switches),
   Paths(rCopy.Paths),
   BlackBoxList(rCopy.BlackBoxList),
   SourceFiles(rCopy.SourceFiles),
   FortranIncludeFiles(rCopy.FortranIncludeFiles),
   ClassList(rCopy.ClassList)
{
  SourceFileType = rCopy.SourceFileType;

  for (int cn = 0 ; cn < NUM_SOURCE_TYPES ; cn++)
  {
    SourceOptionsFile[cn] = rCopy.SourceOptionsFile[cn];
  }
}

//  ----------------------------------------------------------------------------

AdtMakeCommand::~AdtMakeCommand()
{

}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::workingDirectory(const char* pWorkingDirectory)
{
  fixDirectory(WorkingDirectory, pWorkingDirectory, "Working", true);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::includeDirectory(const char* pIncludeDirectory)
{
  fixDirectory(IncludeDirectory, pIncludeDirectory, "Include", true);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::prefixWorkingDirectory(string& rResultFileName,
                                            const char* pFileName,
                                            bool bQuote) const
{
  prefixDirectory(WorkingDirectory,
                  rResultFileName,
                  pFileName,
                  bQuote);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::prefixIncludeDirectory(string& rResultFileName,
                                            const char* pFileName,
                                            bool bQuote) const
{
  prefixDirectory(IncludeDirectory,
                  rResultFileName,
                  pFileName,
                  bQuote);
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommand::switchDefined(const char* pSwitch) const
{
  bool bDefined = (Switches.find(pSwitch) != Switches.end());

  return (bDefined);
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommand::withStackSubstitution(const AdtMakeCommandOperation* pOperation) const
{
  bool bWithStackSubstitution = false;

  if (switchDefined("WithoutStackSubstitution"))
  {
    bWithStackSubstitution = false;
  }

  if (switchDefined("WithStackSubstitution"))
  {
    bWithStackSubstitution = true;
  }

  if (pOperation != 0)
  {
    // Pragma takes precedence over switches
    if (bWithStackSubstitution && pOperation->pragma("WithoutStackSubstitution"))
    {
      bWithStackSubstitution = false;
    }
    else if (!bWithStackSubstitution && pOperation->pragma("WithStackSubstitution"))
    {
      bWithStackSubstitution = true;
    }
  }

  return (bWithStackSubstitution);
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommand::isFile(const char* pFileName) const
{
  bool        bIsFile = false;
  struct stat status;

  if (stat(pFileName, &status) == 0)
  {
    bIsFile = (((status.st_mode & S_IFDIR) != S_IFDIR) && ((status.st_mode & S_IFREG) == S_IFREG));
  }

  return (bIsFile);
}

//  ----------------------------------------------------------------------------

bool AdtMakeCommand::findFile(const string& rSourceFileName, string& rFileAndPath) const
{
  bool bFound = false;

  //Try file as is
  if (isFile(rSourceFileName))
  {
    rFileAndPath  = rSourceFileName;
    bFound        = true;
  }
  else
  {
    //Try adding path
    for (AdtStringListConstIter PathsIter = Paths.begin() ; PathsIter != Paths.end() ; ++PathsIter)
    {
      const string& rPossiblePath = *PathsIter;

      //Add path without slash
      rFileAndPath  = rPossiblePath;
      rFileAndPath += rSourceFileName;

      if (isFile(rFileAndPath))
      {
        bFound = true;
        break;
      }

      //Add path with slash
      rFileAndPath  = rPossiblePath;
      rFileAndPath += "/";
      rFileAndPath += rSourceFileName;

      if (isFile(rFileAndPath))
      {
        bFound = true;
        break;
      }
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

int AdtMakeCommand::make(AdtMakeIncremental& rBuildCheck)
{
  int nReturnCode = 0;

  //We need to look through the operation list for function names to be operated
  //on. Those that we can identify in the given class should be converted to
  //fortran prior to differentiation. Those that can't are assumed to be generated
  //by tapenade. We need to do one output fortran file per function to be
  //differentiated and keep track of the file names.
  //
  //Then run through the tapenade operations one by one, collating the output
  //files and parsing each to determine which functions and variables are defined
  //in each. This needs to be mapped so that future operations will know which
  //files to act on. Each tapenade output file that contains pushes and pops need
  //to have them removed and replaced by array indexing instead.
  //
  //When all operations are done the resulting fortran outputs need to be merged
  //into one. This is should be easy enough to achieve by merging the parse trees
  //into one and then doing the translation back to source format.
  AdtParserPtrList  CodeList;
  string            rRootSourceFileName;
  string            rFileAndPath;
  const char*       pOptionsFileTexts[NUM_SOURCE_TYPES] = {0};
  const char*       pOptionsFileNames[NUM_SOURCE_TYPES] = {0};
  bool              bHasSourceFiles = false;
  int               cn;

  AdtCppScopeManager::resetGlobalScopeManager();
  AdtCppScopeManager::mapNames(false);

  //Open and read options file
  for (cn = 0 ; cn < NUM_SOURCE_TYPES ; cn++)
  {
    if (findFile(SourceOptionsFile[cn], rFileAndPath))
    {
      FILE* pFile = ::fopen(rFileAndPath, "rb");

      if (pFile != 0)
      {
        long nLength = 0;

        rBuildCheck.checkFile(rFileAndPath);

        ::fseek(pFile, 0, SEEK_END);

        nLength = ::ftell(pFile);

        ::fseek(pFile, 0, SEEK_SET);

        if (nLength > 0)
        {
          char* pOptionsFileText = new char[nLength + 1];

          if (pOptionsFileText != 0)
          {
            pOptionsFileText[nLength] = 0;

            if (::fread(pOptionsFileText, nLength, 1, pFile) == 0)
            {
              pOptionsFileText[0] = 0;
            }
          }

          pOptionsFileTexts[cn] = pOptionsFileText;
          pOptionsFileNames[cn] = SourceOptionsFile[cn];
        }

        ::fclose(pFile);
      }
    }
  }

  //Parse all sources
  for (AdtStringListIter SrcIter = SourceFiles.begin() ; SrcIter != SourceFiles.end() ; ++SrcIter)
  {
    string& rSourceFileName = *SrcIter;

    if (findFile(rSourceFileName, rFileAndPath))
    {
      AdtParser*      pParseRoot  = 0;
      AdtSourceRoot*  pGoal       = 0;
      AdtCompiler     ParserContext(rFileAndPath);

      if (ParserContext.isValid())
      {
        bHasSourceFiles = true;

        rBuildCheck.checkFile(rFileAndPath);

        ::printf("Compiling %s\n", rSourceFileName.c_str());

        AdtMakeSystem::clearIncludeList();

        ParserContext.parse(rFileAndPath,
                            pOptionsFileTexts[fileTypeToIndex(SourceFileType)],
                            pOptionsFileNames[fileTypeToIndex(SourceFileType)],
                            &Paths,
                            true);

        AdtMakeSystem::checkIncludes(rBuildCheck, *this);

        pGoal       = ParserContext.sourceRoot();
        pParseRoot  = ParserContext.parseRoot();

        if ((pGoal != 0) && (pParseRoot != 0))
        {
          CodeList.push_back(pParseRoot);

          if (0)
          {
            //Test write parsed code.
            AdtFile Test;
            string  TestFile(rFileAndPath);

            TestFile += ".rec";

            if (Test.open(TestFile, "wt"))
            {
              pGoal->writeNative(Test);

              Test.close();
            }
          }
        }
        else
        {
          ::printf("MAKE ERROR : Failed to compile file %s\n", rFileAndPath.c_str());

          AdtExit(-1);
        }

        ParserContext.releaseRoot();
      }
      else
      {
        ::printf("MAKE ERROR : No parser available for %s\n",
                 rFileAndPath.c_str());

        AdtExit(-1);
      }
    }
    else
    {
      //Can't find file
      ::printf("MAKE ERROR : Can't find file %s\n", rSourceFileName.c_str());
    }
  }

  //Now build fortran includes
  AdtFile FortranOut(true);
  string  FortranInclude;

  if (FortranOut.open(FortranInclude))
  {
    AdtFortran                    FortranContext;
    AdtFortranExecutableProgram*  pWorkingRoot    = 0;
    AdtFortranExecutableProgram*  pCallExpandRoot = 0;
    AdtStringByStringMap          IncludeFunctionsMap;

    if (FortranIncludeFiles.size() > 0)
    {
      AdtStringListConstIter  IncludeIter;

      ::printf("\n");

      //Compile any include files and write the source to the head of the
      //working fortran file.
      for (IncludeIter = FortranIncludeFiles.begin() ; IncludeIter != FortranIncludeFiles.end() ; ++IncludeIter)
      {
        const string& rIncludeFileName = *IncludeIter;

        if (findFile(rIncludeFileName, rFileAndPath))
        {
          AdtFortranExecutableProgram*  pIncludeRoot = 0;

          rBuildCheck.checkFile(rFileAndPath);

          ::printf("Compiling fortran include file %s\n", rIncludeFileName.c_str());

          FortranContext.parse(rFileAndPath, 0, 0, &Paths);

          pIncludeRoot = AdtFortranBase::fortranRootObject();

          if (pIncludeRoot != 0)
          {
            //Verify that we don't have any module definitions (not allowed)
            //and create a map of include functions so we know to remove them
            //from the class we create.
            AdtParserPtrList  ModuleList;

            pIncludeRoot->findObjects(ModuleList, "AdtFortranModule");

            if (ModuleList.size() > 0)
            {
              //Include file defines modules
              ::printf("MAKE ERROR : Modules definitions not allowed in file %s\n", rIncludeFileName.c_str());
            }
            else
            {
              string            sMessage;
              AdtParserPtrList  FunctionList;

              pIncludeRoot->findObjects(FunctionList,
                                        "AdtFortranFunctionSubprogram",
                                        0,
                                        false,
                                        "AdtFortranProgramUnit");

              pIncludeRoot->findObjects(FunctionList,
                                        "AdtFortranSubroutineSubprogram",
                                        0,
                                        false,
                                        "AdtFortranProgramUnit");

              AdtParserPtrListConstIter Iter;

              for (Iter = FunctionList.begin() ; Iter != FunctionList.end() ; ++Iter)
              {
                AdtParser*  pObj = *Iter;

                if (pObj != 0)
                {
                  IncludeFunctionsMap.insert(AdtStringByStringMap::value_type(pObj->name(), pObj->name()));
                }
              }

              FortranOut.write("! ----------------------------------------------------------------------------");
              FortranOut.newline();
              FortranOut.write("MODULE DIFFSIZES");
              FortranOut.incrementIndent();
              FortranOut.newline();
              FortranOut.write("INTEGER(4) , parameter :: nbdirsmax = 25");
              FortranOut.decrementIndent();
              FortranOut.newline();
              FortranOut.write("ENDMODULE");
              FortranOut.newline();

              FortranOut.write("! ----------------------------------------------------------------------------");
              FortranOut.newline();

              sMessage  = "! Including ";
              sMessage += rIncludeFileName;

              FortranOut.write(sMessage);
              FortranOut.newline();
              FortranOut.write("! ----------------------------------------------------------------------------");
              FortranOut.newline();

              pIncludeRoot->writeFortran(FortranOut);

              FortranOut.newline();
              FortranOut.write("! ----------------------------------------------------------------------------");
              FortranOut.newline();
            }
          }
          else
          {
            ::printf("MAKE ERROR : Failed to compile file %s\n", rFileAndPath.c_str());

            AdtExit(-1);
          }

          adtFortran_releaseRoot();
        }
        else
        {
          //Can't find file
          ::printf("MAKE ERROR : Can't find file %s\n", rIncludeFileName.c_str());

          AdtExit(-1);
        }
      }
    }

    FortranOut.close();

    // Need a switch / option to control this, maybe in the makefile
    AdtFortranBase::WithStackSubstitution = withStackSubstitution();

    //Parse the CallExpansion macros.
    if (!FortranContext.parseCallExpandMacros(pCallExpandRoot))
    {
      ::printf("MAKE ERROR : Failed to compile file CallExpand macros\n");

      AdtExit(-1);
    }

    if (0)
    {
      //Debugging stuff to print the parse tree of the fortran call expansion definitions
      AdtFile MacrosFile;

      MacrosFile.open("FortranMacros.txt", "wt");
      pCallExpandRoot->printDescendants(MacrosFile);
    }

    // Check build switches
    rBuildCheck.checkMap(Switches);

    //Now make the classes
    AdtMakeClassListIter        Iter;
    AdtMakeClassPtrByStringMap  WorkingMakeByClass;
    int                         cn = 1;

    for (Iter = ClassList.begin() ; Iter != ClassList.end() ; ++Iter)
    {
      AdtMakeClass& rMakeClass = *Iter;

      if (!bHasSourceFiles)
      {
        // If we don't have source files then we need to do a null compile so
        // that the command file is parsed prior to parsing our source code.
        // If we don't then the automation processing will not work because
        // the array data types will not be defined.
        AdtCompiler ParserContext(rMakeClass.sourceFile());

        if (ParserContext.isValid())
        {
          ParserContext.parse(0,
                              pOptionsFileTexts[fileTypeToIndex(rMakeClass.sourceFileType())],
                              pOptionsFileNames[fileTypeToIndex(rMakeClass.sourceFileType())],
                              &Paths,
                              true);
        }
      }

      rMakeClass.make(*this,
                      CodeList,
                      WorkingMakeByClass,
                      pCallExpandRoot,
                      pOptionsFileTexts,
                      pOptionsFileNames,
                      FortranInclude,
                      rBuildCheck,
                      cn);

      cn++;
    }

    UtlReleaseReference(pCallExpandRoot);
    WorkingMakeByClass.clear();
  }

  //Empty the CodeList
  CodeList.clear();

  for (cn = 0 ; cn < NUM_SOURCE_TYPES ; cn++)
  {
    if (pOptionsFileTexts[cn] != 0)
    {
      delete pOptionsFileTexts[cn];
    }
  }

  return (nReturnCode);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::addClass(const AdtMakeClass& rClass)
{
  ClassList.push_back(rClass);
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::switches(const AdtStringList& rSwitches)
{
  for (AdtStringListConstIter Iter = rSwitches.begin() ; Iter != rSwitches.end() ; ++Iter)
  {
    const string& rSwitch         = *Iter;
    const char*   pBoundsCheckKey = "BoundsCheck-";

    if (strstr(rSwitch.c_str(), pBoundsCheckKey) == rSwitch.c_str())
    {
      // This is a functional bounds check request so add the function to the
      // list of bounds checked functions
      const char* pBoundsCheckFunctionName = rSwitch.c_str() + strlen(pBoundsCheckKey);
    }
    else
    {
      Switches[rSwitch] = 1;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::blackBox(const AdtStringList& rBlackBoxFiles)
{
  BlackBoxList.clear();

  //qualify all black box definition files
  for (AdtStringListConstIter Iter = rBlackBoxFiles.begin() ; Iter != rBlackBoxFiles.end() ; ++Iter)
  {
    string        sFileAndPath;
    const string& rBlackBoxFileName = *Iter;

    if (findFile(rBlackBoxFileName, sFileAndPath))
    {
      BlackBoxList.push_back(sFileAndPath);
    }
    else
    {
      ::printf("MAKE ERROR : Cannot find black box file %s\n", rBlackBoxFileName.c_str());

      AdtExit(-1);
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeCommand::sourceFiles(const AdtStringList& rSourceFiles)
{
  SourceFileType = UnknownSourceFileType;

  //Parse all sources
  for (AdtStringListConstIter SrcIter = rSourceFiles.begin() ; SrcIter != rSourceFiles.end() ; ++SrcIter)
  {
    const string& rSourceFileName = *SrcIter;

    switch (sourceFileType(rSourceFileName))
    {
      default:
      case UnknownSourceFileType:
      {
        ::printf("ERROR: Source file %s has unknown file type.\n", rSourceFileName.c_str());

        AdtExit(-1);
        break;
      }

      case DelphiSourceFileType:
      {
        switch (SourceFileType)
        {
          default:
          case UnknownSourceFileType:
          case DelphiSourceFileType:
          {
            SourceFileType = DelphiSourceFileType;
            break;
          }

          case CppSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was object pascal but this one is C++.\n");

            AdtExit(-1);
            break;
          }

          case JavaSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was object pascal but this one is java.\n");

            AdtExit(-1);
            break;
          }
        }

        break;
      }

      case CppSourceFileType:
      {
        switch (SourceFileType)
        {
          default:
          case UnknownSourceFileType:
          case CppSourceFileType:
          {
            SourceFileType = CppSourceFileType;
            break;
          }

          case DelphiSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was C++ but this one is object pascal.\n");

            AdtExit(-1);
            break;
          }

          case JavaSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was C++ but this one is java.\n");

            AdtExit(-1);
            break;
          }
        }

        break;
      }

      case CppHeaderFileType:
      {
        // ERROR - headers not allowed as source files. Need a cpp file
        ::printf("ERROR: header files not allowed as source files\n");

        AdtExit(-1);
        break;
      }

      case JavaSourceFileType:
      {
        switch (SourceFileType)
        {
          default:
          case UnknownSourceFileType:
          case JavaSourceFileType:
          {
            SourceFileType = JavaSourceFileType;
            break;
          }

          case CppSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was java but this one is C++.\n");

            AdtExit(-1);
            break;
          }

          case DelphiSourceFileType:
          {
            ::printf("ERROR: Mixing source types not allowed. First type was java but this one is object pascal.\n");

            AdtExit(-1);
            break;
          }
        }

        break;
      }
    }
  }

  SourceFiles = rSourceFiles;
}

//  ----------------------------------------------------------------------------

int AdtMakeCommand::fileTypeToIndex(AdtSourceFileType nType)
{
  int nIndex = 0;

  switch (nType)
  {
    default:
    case UnknownSourceFileType:
    case JavaSourceFileType:
    case FortranSourceFileType:
    case DelphiSourceFileType:
    {
      nIndex = 0;
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      nIndex = 1;
      break;
    }
  }

  return (nIndex);
}

//  ----------------------------------------------------------------------------

AdtSourceFileType AdtMakeCommand::sourceFileType(const string& rSourceFile)
{
  AdtSourceFileType nSourceFileType = adtSourceFileTypeFromFile(rSourceFile);

  return (nSourceFileType);
}


//  ----------------------------------------------------------------------------
//  AdtMakeSystem method implementations
//  ----------------------------------------------------------------------------
void AdtMakeSystem::updateOptions(AdtOpType nNextOpType)
{
  switch (OpType)
  {
    case VarOpType:
    {
      CurrentCommandOperation.vars(StringList);
      break;
    }

    case OutVarOpType:
    {
      CurrentCommandOperation.outVars(StringList);
      break;
    }

    case OtherOpType:
    default:
    {
      //Do nothing
    }
  }

  StringList.clear();

  OpType = nNextOpType;
}

//  ----------------------------------------------------------------------------

AdtMakeSystem::AdtMakeSystem()
{
  //Set string comparison mode to case insensitive.
//  string::SetCaseSensitivity(0);
}

//  ----------------------------------------------------------------------------

AdtMakeSystem::~AdtMakeSystem()
{

}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::parse(const char* pFilename,
                          FILE*& yyMakein,
                          int& yyMakedebug,
                          parse_fn yyMakeparse)
{
  if ((yyMakeparse  != 0) &&
      (pFilename    != 0))
  {
    yyMakein    = 0;
    yyMakedebug = 1;
    yyMakedebug = 0;
    yyMakein    = ::fopen(pFilename, "rt");

    if (yyMakein != 0)
    {
      yyMake_resetLineNumber(allocString(pFilename));
      yyMakeparse();
      yyMake_endParse();

      ::fclose(yyMakein);

      yyMakein = 0;
    }

    yyMakedebug = 0;

    yyMake_releaseBuffer();
  }
}

//  ----------------------------------------------------------------------------

int AdtMakeSystem::make(const char* pFilename)
{
  int nReturnCode = 0;

  UtlFilePath MakePath(pFilename);
  string      BuildCheckFileName;

  ::printf("Making %s\n", pFilename);

  MakePath.extension(".dch");
  MakePath.join(BuildCheckFileName);
  BuildCheck.open(BuildCheckFileName);

  parse(pFilename,
        yyMakein,
        yyMakedebug,
        yyMakeparse);

  for (AdtMakeCommandListIter Iter = MakeCommandList.begin() ; Iter != MakeCommandList.end() ; ++Iter)
  {
    AdtMakeCommand& rMakeCommand = *Iter;

    if (rMakeCommand.switchDefined("Rebuild"))
    {
      BuildCheck.forceRebuild();
    }

    useArrayClass(ArrayClass_offarray);

    if (rMakeCommand.switchDefined("Oarray"))
    {
      useArrayClass(ArrayClass_Oarray);
    }

    nReturnCode = rMakeCommand.make(BuildCheck);

    if (nReturnCode != 0)
    {
      break;
    }
  }

  BuildCheck.close();

  return (nReturnCode);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::makeCommandOpen()
{
  CurrentCommand.newMakeCommand();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::makeCommandClose()
{
  MakeCommandList.push_back(CurrentCommand);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::makeClassOpen(const char* pNewClassName,
                                  const char* pParentClassName,
                                  const char* pSourceFile,
                                  const char* pSourceFile2,
                                  const char* pOutputFile,
                                  const char* pOutputFile2)
{
  CurrentClass.newMakeClass(CurrentCommand,
                            pNewClassName,
                            pParentClassName,
                            pSourceFile,
                            pSourceFile2,
                            pOutputFile,
                            pOutputFile2);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::makeClassClose()
{
  CurrentCommand.addClass(CurrentClass);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::pathsOpen()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::pathsClose()
{
  CurrentCommand.paths(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::switchesOpen()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::switchesClose()
{
  CurrentCommand.switches(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::blackBoxOpen()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::blackBoxClose()
{
  CurrentCommand.blackBox(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::sourceFilesOpen()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::sourceFilesClose()
{
  CurrentCommand.sourceFiles(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::workingDirectory(const char* pString)
{
  CurrentCommand.workingDirectory(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::includeDirectory(const char* pString)
{
  CurrentCommand.includeDirectory(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::sourceOptionsFile(const char* pString, int nType)
{
  AdtSourceFileType nTypeSpec;

  switch (nType)
  {
    case 0:
    {
      nTypeSpec = DelphiSourceFileType;
      break;
    }

    case 1:
    {
      nTypeSpec = CppSourceFileType;
      break;
    }

    default:
    {
      nTypeSpec = DelphiSourceFileType;
      FAIL();
      break;
    }
  }

  CurrentCommand.sourceOptionsFile(pString, nTypeSpec);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::fortranIncludeFilesOpen()
{
  //Do nothing
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::fortranIncludeFilesClose()
{
  CurrentCommand.fortranIncludeFiles(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::classBoundsCheckOpen()
{
  updateOptions();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::classBoundsCheckClose()
{
  CurrentClass.boundsCheck(StringList);
  StringList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandVarOpen()
{
  updateOptions(VarOpType);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandOutVarOpen()
{
  updateOptions(OutVarOpType);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandOpClose()
{
  updateOptions();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandClose()
{
  if (!CurrentCommandOperation.isNull())
  {
    CurrentClass.addOperation(CurrentCommandOperation);
    CurrentCommandOperation.reset();
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandUser(const char* pString)
{
  CurrentCommandOperation.userOptions(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandPre(const char* pString)
{
  CurrentCommandOperation.preCommand(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandPost(const char* pString)
{
  CurrentCommandOperation.postCommand(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandPragmas(const char* pString)
{
  CurrentCommandOperation.pragmas(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandMode(const char* pString)
{
  CurrentCommandOperation.mode(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::commandFunction(const char* pString)
{
  CurrentCommandOperation.functionName(pString);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::pushString(const char* pString)
{
  // Need to filter out quotes as we need to allow quoted strings to support
  // file names with spaces. If a string has a leading quote then remove it
  // and the corresponding trailing quote.
  if ((*pString == '\'') || (*pString == '\"'))
  {
    string rString(pString);

    rString.mid(1, rString.length() - 2);

    StringList.push_back(rString);
  }
  else
  {
    StringList.push_back(pString);
  }
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::addInclude(const char* pFileName)
{
  IncludeList.push_back(pFileName);
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::clearIncludeList()
{
  IncludeList.clear();
}

//  ----------------------------------------------------------------------------

void AdtMakeSystem::checkIncludes(AdtMakeIncremental& rBuildCheck,
                                  const AdtMakeCommand& rMakeCommand)
{
  AdtStringListConstIter  Iter;

  for (Iter = IncludeList.begin() ; Iter != IncludeList.end() ; ++Iter)
  {
    string  rFileAndPath;

    if (rMakeCommand.findFile(*Iter, rFileAndPath))
    {
      rBuildCheck.checkFile(rFileAndPath);
    }
  }

  IncludeList.clear();
}
