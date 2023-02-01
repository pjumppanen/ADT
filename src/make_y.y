%{
/*
 * make.y
 *
 *  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
 *  ORGANISATION (CSIRO), Australia.
 *  All rights reserved.
 *
 *  This file is part of ADT.  The full ADT copyright notice, including
 *  terms governing use, modification, and redistribution, is contained in
 *  the file COPYING. COPYING can be found at the root of the source code
 *  distribution tree;
 *
 * Make system grammar for Auto-differentiation utility.
 * Typical syntax:
 *
 *   AD BEGIN
 *     [SWITCHES: switch1,switch2,...,switchN;] //Optional
 *     [BLACKBOX: File1,File2,...,FileN;] // Optional
 *     PATHS: Path1,Path2,...,PathN;
 *     SOURCE FILES: File1,File2,...,FileN;
 *     WORKING DIRECTORY: Path;
 *     [INCLUDE DIRECTORY: Path;] //Optional
 *     CPP OPTIONS FILE: FileBlah2;
 *     PASCAL OPTIONS FILE: FileBlah2;
 *     FORTRAN INCLUDE FILES: File1,File2,...,FileN;
 *     CLASS NewClassNameA (ClassNameA) SOURCE FILE: File1 OUTPUT FILE: File2
 *     BEGIN
 *       [BOUNDS CHECK fn1, fn2,...,fnN;] //Optional
 *       FUNCTION=Name1 VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes' PRE='command to run before tapenade' POST='command to run after tapenade';
 *       FUNCTION=Name2 VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *   	   .
 *   	   .
 *   	   .
 *       FUNCTION=NameN VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *   	   .
 *   	   .
 *   	   .
 *       DIFF=NameN VAR=a,b,c,d OUTVAR=e,f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       GRAD=NameN VAR=a,b,c,d OUTVAR=e,f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       MULTIDIFF=NameN VAR=a,b,c,d OUTVAR=e,f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       MULTIGRAD=NameN VAR=a,b,c,d OUTVAR=e,f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       HESSIAN=NameN VAR=a OUTVAR=b USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       REML=NameN PARAMETERS=a,b,c,d RANDOM=c,d USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *     END
 *
 *     CLASS NewClassNameB (ClassNameB) SOURCE FILE: File1 OUTPUT FILE: File2
 *     BEGIN
 *       [BOUNDS CHECK fn1, fn2,...,fnN;] //Optional
 *       FUNCTION=Name1 VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *       FUNCTION=Name2 VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *   	   .
 *   	   .
 *   	   .
 *       FUNCTION=NameN VAR=a,b,c,d OUTVAR=e,f MODE=f USER='any custom tapenade command line options you wish to add enclosed in quotes';
 *     END
 *      .
 *      .
 *      .
 *   END
 *   .
 *   .
 *   .
 */

#include <stdio.h>
#include "lexer.h"
#include "adtmake.hpp"

#define YYDEBUG           1
#define YYERROR_VERBOSE   1

#ifdef stderr
  #undef stderr
#endif

#define stderr            stdout

#define YYSTYPE   makeType

%}

/* make keyword tokens */
%token M_AD M_BEGIN M_BOUNDS M_CHECK M_END M_SOURCE M_OUTPUT M_FILE M_FILES
%token M_WORKING M_DIRECTORY M_FUNCTION M_VAR M_OUTVAR M_MODE M_USER M_PRAGMAS
%token M_PATHS M_CLASS M_OPTIONS M_PASCAL M_CPP M_FORTRAN M_INCLUDE M_SWITCHES
%token M_BLACKBOX M_PRE M_POST M_DIFF M_GRAD M_MULTIDIFF M_MULTIGRAD M_HESSIAN
%token M_REML M_PARAMETERS M_RANDOM

/* make special character tokens */
%token M_COMMA M_SEMICOLON M_COLON M_EQUALS M_LBRACKET M_RBRACKET

/* make input tokens */
%token M_TEXT M_FILENAME M_IDENT

/* Other tokens */
%token M_SINGLELINE_COMMENT M_MULTILINE_COMMENT


%%
MakeCommandList : MakeCommand
                | MakeCommandList MakeCommand
;

MakeCommand : MakeCommandBegin MakeOptionsList ClassList MakeCommandEnd
;

MakeOptionsList : MakeOption
                | MakeOptionsList MakeOption
;

MakeOption : Paths
           | SourceFiles
           | WorkingDirectory
           | IncludeDirectory
           | CppOptionsFile
           | DelphiOptionsFile
           | FortranIncludeFiles
           | Switches
           | BlackBox
;

MakeCommandBegin : M_AD M_BEGIN
{
  make_MakeCommandOpen();
}
;

MakeCommandEnd : M_END
{
  make_MakeCommandClose();
}
;

Paths : BeginPaths FileNameList M_SEMICOLON
{
  make_PathsClose();
}
;

BeginPaths : M_PATHS M_COLON
{
  make_PathsOpen();
}
;

BlackBox : BeginBlackBox FileNameList M_SEMICOLON
{
  make_BlackBoxClose();
}
;

BeginBlackBox : M_BLACKBOX M_COLON
{
  make_BlackBoxOpen();
}
;

SourceFiles : BeginSourceFiles FileNameList M_SEMICOLON
{
  make_SourceFilesClose();
}
;

BeginSourceFiles : M_SOURCE M_FILES M_COLON
{
  make_SourceFilesOpen();
}
;

FileNameList : M_FILENAME
{
  make_PushString($1.sValue);
}
             | FileNameList M_COMMA M_FILENAME
{
  make_PushString($3.sValue);
}
;

WorkingDirectory : M_WORKING M_DIRECTORY M_COLON M_FILENAME M_SEMICOLON
{
  make_WorkingDirectory($4.sValue);
}
;

IncludeDirectory : M_INCLUDE M_DIRECTORY M_COLON M_FILENAME M_SEMICOLON
{
  make_IncludeDirectory($4.sValue);
}
;

DelphiOptionsFile : M_PASCAL M_OPTIONS M_FILE M_COLON M_FILENAME M_SEMICOLON
{
  make_SourceOptionsFile($5.sValue, 0);
};


CppOptionsFile : M_CPP M_OPTIONS M_FILE M_COLON M_FILENAME M_SEMICOLON
{
  make_SourceOptionsFile($5.sValue, 1);
}
;

Switches : BeginSwitches FileNameList M_SEMICOLON
{
  make_SwitchesClose();
}
;

BeginSwitches : M_SWITCHES M_COLON
{
  make_SwitchesOpen();
}
;

FortranIncludeFiles : BeginFortranIncludeFiles FileNameList M_SEMICOLON
{
  make_FortranIncludeFilesClose();
}
;

BeginFortranIncludeFiles : M_FORTRAN M_INCLUDE M_FILES M_COLON
{
  make_FortranIncludeFilesOpen();
}
;

ClassList : ClassBlock
          | ClassList ClassBlock
;

ClassBlock : ClassBlockBegin AutoDiffCommandList ClassBlockEnd
           | ClassBlockBegin ClassBlockEnd
;

ClassBlockBegin : M_CLASS M_IDENT M_LBRACKET M_IDENT M_RBRACKET M_SOURCE M_FILE M_COLON M_FILENAME M_OUTPUT M_FILE M_COLON M_FILENAME M_BEGIN
{
  make_ClassOpen($2.sValue, $4.sValue, $9.sValue, 0, $13.sValue, 0);
}
                | M_CLASS M_IDENT M_LBRACKET M_IDENT M_RBRACKET M_SOURCE M_FILE M_COLON M_FILENAME M_OUTPUT M_FILES M_COLON M_FILENAME M_FILENAME M_BEGIN
{
  make_ClassOpen($2.sValue, $4.sValue, $9.sValue, 0, $13.sValue, $14.sValue);
}
                | M_CLASS M_IDENT M_LBRACKET M_IDENT M_RBRACKET M_SOURCE M_FILES M_COLON M_FILENAME M_FILENAME M_OUTPUT M_FILE M_COLON M_FILENAME M_BEGIN
{
  make_ClassOpen($2.sValue, $4.sValue, $9.sValue, $10.sValue, $14.sValue, 0);
}
                | M_CLASS M_IDENT M_LBRACKET M_IDENT M_RBRACKET M_SOURCE M_FILES M_COLON M_FILENAME M_FILENAME M_OUTPUT M_FILES M_COLON M_FILENAME M_FILENAME M_BEGIN
{
  make_ClassOpen($2.sValue, $4.sValue, $9.sValue, $10.sValue, $14.sValue, $15.sValue);
}
;

ClassBlockEnd : M_END
{
  make_ClassClose();
}
;

AutoDiffCommandList : AutoDiffCommand
                    | AutoDiffCommandList AutoDiffCommand
;

AutoDiffCommand : AutoDiffCommandOpList M_SEMICOLON
{
  make_CommandClose();
}
;

AutoDiffCommandOpList : AutoDiffCommandOp
{
  make_CommandOpClose();
}
                      | AutoDiffCommandOpList AutoDiffCommandOp
{
  make_CommandOpClose();
}
;

AutoDiffCommandOp : AutoDiffCommandFunctionOp
                  | AutoDiffCommandHessianOp
                  | AutoDiffCommandDiffOp
                  | AutoDiffCommandGradOp
                  | AutoDiffCommandMultiDiffOp
                  | AutoDiffCommandMultiGradOp
                  | AutoDiffCommandRemlOp
                  | AutoDiffCommandVarOp
                  | AutoDiffCommandOutVarOp
                  | AutoDiffCommandParametersOp
                  | AutoDiffCommandRandomOp
                  | AutoDiffCommandModeOp
                  | AutoDiffCommandUserOp
                  | AutoDiffCommandPreOp
                  | AutoDiffCommandPostOp
                  | AutoDiffCommandPragmasOp
                  | AutoDiffCommandBoundsCheckOp

AutoDiffCommandFunctionOp : M_FUNCTION M_EQUALS M_IDENT
{
  make_CommandFunction($3.sValue);
}
;

AutoDiffCommandHessianOp : M_HESSIAN M_EQUALS M_IDENT
{
  make_CommandHessian($3.sValue);
}
;

AutoDiffCommandDiffOp : M_DIFF M_EQUALS M_IDENT
{
  make_CommandDiff($3.sValue);
}
;

AutoDiffCommandGradOp : M_GRAD M_EQUALS M_IDENT
{
  make_CommandGrad($3.sValue);
}
;

AutoDiffCommandMultiDiffOp : M_MULTIDIFF M_EQUALS M_IDENT
{
  make_CommandMultiDiff($3.sValue);
}
;

AutoDiffCommandMultiGradOp : M_MULTIGRAD M_EQUALS M_IDENT
{
  make_CommandMultiGrad($3.sValue);
}
;

AutoDiffCommandRemlOp : M_REML M_EQUALS M_IDENT
{
  make_CommandReml($3.sValue);
}
;

AutoDiffCommandVarOp : BeginAutoDiffCommandVarOp NameList
;

BeginAutoDiffCommandVarOp : M_VAR M_EQUALS
{
  make_CommandVarOpen();
}
;

AutoDiffCommandOutVarOp : BeginAutoDiffCommandOutVarOp NameList
;

BeginAutoDiffCommandOutVarOp : M_OUTVAR M_EQUALS
{
  make_CommandOutVarOpen();
}
;

AutoDiffCommandParametersOp : BeginAutoDiffCommandParametersOp NameList
;

BeginAutoDiffCommandParametersOp : M_PARAMETERS M_EQUALS
{
  make_CommandOutVarOpen();
}
;

AutoDiffCommandRandomOp : BeginAutoDiffCommandRandomOp NameList
;

BeginAutoDiffCommandRandomOp : M_RANDOM M_EQUALS
{
  make_CommandVarOpen();
}
;

AutoDiffCommandModeOp : M_MODE M_EQUALS M_IDENT
{
  make_CommandMode($3.sValue);
}
;

AutoDiffCommandUserOp : M_USER M_EQUALS M_TEXT
{
  make_CommandUser($3.sValue);
}
;

AutoDiffCommandPreOp : M_PRE M_EQUALS M_TEXT
{
  make_CommandPre($3.sValue);
}
;

AutoDiffCommandPostOp : M_POST M_EQUALS M_TEXT
{
  make_CommandPost($3.sValue);
}
;

AutoDiffCommandPragmasOp : M_PRAGMAS M_EQUALS M_TEXT
{
  make_CommandPragmas($3.sValue);
}
;

AutoDiffCommandBoundsCheckOp : BeginAutoDiffCommandBoundsCheckOp NameList
{
  make_ClassBoundsCheckClose();
}
;

BeginAutoDiffCommandBoundsCheckOp : M_BOUNDS M_CHECK
{
  make_ClassBoundsCheckOpen();
}
;

NameList : M_IDENT
{
  make_PushString($1.sValue);
}
         | NameList M_COMMA M_IDENT
{
  make_PushString($3.sValue);
}
;
