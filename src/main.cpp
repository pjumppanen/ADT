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
//    main.cpp
//
//  Purpose:
//    This file defines the main entry point for the program.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include <stdio.h>
#include "adtver.hpp"
#include "adtutils.hpp"
#include "adtmake.hpp"
#include "adtdelphi.hpp"
#include "adtfortran.hpp"

const char* pHelpText =

"Invocation:\n"
"adt <makefile1>[ <makefile2> ...]\n\n"
"The makefile adheres to the format detailed below. Required user data is\n"
"enclosed in <>. Optional data is enclosed in [].\n\n"
"Filenames and paths only need to be quoted when whitespace occurs in the name.\n"
"Any extra arguments passed to tapenade using the USER parameter must be quoted \n"
"in a single string. Single line comments begin with // and free formating of \n"
"the makefile is allowed provided the syntax is preserved.\n\n"
"The source code classes whose methods are being differentiated must be \n"
"derrived from the tuseful class and can only use the array types provided by \n"
"that class. Any other non-scalar types are not allowed in differentiated code.\n\n"
"AD BEGIN\n"
"  [SWITCHES: <switch1,switch2,…,switchN>;] //Optional\n"
"  [BLACKBOX: <File1,File2,…,FileN>;] // Optional\n"
"  PATHS: <path 1[,path 2, ... ,path n]>;\n"
"  SOURCE FILES: <include file 1[, include file 2, ... ,include file n]>;\n"
"  WORKING DIRECTORY: <path to working directory>;\n"
"\n"
"  // language dependent file defining source code macro substitutions and array types - Required.\n"
"  PASCAL OPTIONS FILE: pascal_macros.txt; \n"
"\n"
"  // language dependent file defining source code macro substitutions and array types - Required.\n"
"  CPP OPTIONS FILE: cpp_macros.txt; \n"
"\n"
"  // file defining fortran functions needed to do the dfferentiation - Required.\n"
"  FORTRAN INCLUDE FILES: stdlib.f; \n"
"\n"
"  CLASS <DifferentiatedClass_1> (<ClassBeingDifferentiated_1>) \n"
"    [BOUNDS CHECK fn1, fn2,…,fnN;] //Optional \n"
"    SOURCE FILE: <class source file> \n"
"    OUTPUT FILE: <differentiated class destination file>\n"
"  BEGIN\n"
"    FUNCTION=<function_1_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'> \n"
"      [PRE=<'command to run before tapenade'>] \n"
"      [POST=<'command to run after tapenade'>];\n"
"    .\n"
"    .\n"
"    .\n"
"    FUNCTION=<function_n_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'>;\n"
"      [PRE=<'command to run before tapenade'>] \n"
"      [POST=<'command to run after tapenade'>];\n"
"  END\n"
"\n"
"  .\n"
"  .\n"
"  .\n"
"\n"
"  CLASS <DifferentiatedClass_n> (<ClassBeingDifferentiated_n>) \n"
"    SOURCE FILE: <class source file> \n"
"    OUTPUT FILE: <differentiated class destination file>\n"
"  BEGIN\n"
"    FUNCTION=<function_1_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'>;\n"
"    .\n"
"    .\n"
"    .\n"
"    FUNCTION=<function_n_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'>;\n"
"  END\n\n"
"Note that in the case of C++ code generation the OUTPUT FILE entry is \n"
"replaced by OUTPUT FILES and both the destination header and source file \n"
"names must be specified. That is \n\n"
"  CLASS <DifferentiatedClass_n> (<ClassBeingDifferentiated_n>) \n"
"    SOURCE FILE: <class source file> \n"
"    OUTPUT FILES: <differentiated class destination header file> \n"
"                  <differentiated class destination source file>\n"
"  BEGIN\n"
"    FUNCTION=<function_1_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'>;\n"
"    .\n"
"    .\n"
"    .\n"
"    FUNCTION=<function_n_to_differentiate> \n"
"      OUTVAR=<ovar_1[,ovar_2,...,ovar_n]> \n"
"      VAR=<diff_wrt_var> \n"
"      MODE=<Tapenade differentiation mode> \n"
"      USER=<'extra tapenade command line args'>;\n"
"  END\n\n"
"END \n";


//  ----------------------------------------------------------------------------

int main(int argc, char** argv)
{
  int nReturnCode = 1;

  ::printf("ADT - Automatic Differentiation via Tapenade\n"
           "Version %s\n"
           "Written by Paavo Jumppanen\n"
           "Copyright (C) 2006-%s, CSIRO\n\n" , ADT_VERSION_STRING, ADT_YEAR_STRING);

  ++argv;
  --argc;

  //Main code
  if (argc > 0)
  {
    AdtExePath  Path(argv[-1]);

    for (int cn = 0 ; cn < argc ; cn++)
    {
      nReturnCode = AdtMakeSystem::make(argv[cn]);
    }
  }
  else
  {
    // Print help
    ::printf("%s", pHelpText);
  }

  return nReturnCode;
}
