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
//    adtautomate.cpp
//
//  Purpose:
//    This file includes implementations of utility classes used to automate
//    the construction of construction, initialisation and interface code,
//    both in R and the target language.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtautomate.hpp"
#include "adtexpression.hpp"
#include "adtutils.hpp"


//  ----------------------------------------------------------------------------

const char* CONSTRUCTOR_ARGS                = "_constructor_args";
const char* CONSTRUCTOR_CALL_ARGS           = "_constructor_call_args";
const char* CONSTRUCTOR_LOCALS              = "_constructor_locals";
const char* CONSTRUCTOR_SCALARS_PHASE       = "_constructor_scalars_phase";
const char* CONSTRUCTOR_ARRAYS_PHASE        = "_constructor_arrays_phase";
const char* IMPL_LIB_INTERFACE_METHODS      = "_impl_lib_interface_methods";
const char* IMPL_LIB_INTERFACE_GLOBALS      = "_impl_lib_interface_globals";
const char* DECL_LIB_INTERFACE_METHODS      = "_decl_lib_interface_methods";
const char* DECL_LIB_INTERFACE_GLOBALS      = "_decl_lib_interface_globals";
const char* DECL_LIB_INTERFACE_CONSTRUCTOR  = "_decl_lib_interface_constructor";
const char* IMPL_LIB_INTERFACE_CONSTRUCTOR  = "_impl_lib_interface_constructor";
const char* IMPL_LIB_REGISTRATION           = "_impl_lib_registration";
const char* LIB_EXPORTS                     = "_lib_exports";
const char* ARRAY_PLANS                     = "_array_plans";
const char* ARRAY_PLANS_INIT                = "_array_plans_init";
const char* ARRAY_PLANS_COPY                = "_array_plans_copy";


//  ----------------------------------------------------------------------------
//  AdtAutoHelper method implementations
//  ----------------------------------------------------------------------------
char AdtAutoHelper::Buffer[2048] = {0};

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::delphiType(AdtAutoType nType, int nDimensions) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      pType = "ARRAY_%dD";
      break;
    }

    case AdtAutoType_FLOAT:
    {
      pType = "ARRAY_%dS";
      break;
    }

    case AdtAutoType_SHORT:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    {
      pType = "ARRAY_%dL";
      break;
    }

    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_CHAR:
    {
      pType = "ARRAY_%dB";
      break;
    }

    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_LONG_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "ARRAY_%dB";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "ARRAY_%dLB";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  // This is not re-entrant or thread safe but it doens't need to be either.
  ::sprintf(Buffer, pType, nDimensions);

  return (Buffer);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::delphiConstructorType(AdtAutoType nType) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      pType = "pdouble";
      break;
    }

    case AdtAutoType_FLOAT:
    {
      pType = "";
      break;
    }

    case AdtAutoType_SHORT:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    {
      pType = "plongint";
      break;
    }

    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_CHAR:
    {
      pType = "pshortint";
      break;
    }

    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "pbyte";
      break;
    }

    case AdtAutoType_LONG_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "";
      FAIL();
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "pboolean";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "plongbool";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::delphiType(AdtAutoType nType) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      pType = "double";
      break;
    }

    case AdtAutoType_FLOAT:
    {
      pType = "single";
      break;
    }

    case AdtAutoType_SHORT:
    {
      pType = "smallint";
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    {
      pType = "word";
      break;
    }

    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    {
      pType = "longint";
      break;
    }

    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "longword";
      break;
    }

    case AdtAutoType_CHAR:
    {
      pType = "shortint";
      break;
    }

    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "byte";
      break;
    }

    case AdtAutoType_LONG_LONG:
    {
      pType = "int64";
      break;
    }

    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "Qword";
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "boolean";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "longbool";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::cppType(AdtAutoType nType, int nDimensions) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      pType = "ARRAY_%dD";
      break;
    }

    case AdtAutoType_FLOAT:
    {
      pType = "ARRAY_%dF";
      break;
    }

    case AdtAutoType_SHORT:
    {
      pType = "ARRAY_%dS";
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    {
      pType = "ARRAY_%dUS";
      break;
    }

    case AdtAutoType_INT:
    {
      pType = "ARRAY_%dI";
      break;
    }

    case AdtAutoType_LONG:
    {
      pType = "ARRAY_%dL";
      break;
    }

    case AdtAutoType_UNSIGNED_INT:
    {
      pType = "ARRAY_%dUI";
      break;
    }

    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "ARRAY_%dUL";
      break;
    }

    case AdtAutoType_CHAR:
    {
      pType = "ARRAY_%dC";
      break;
    }

    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "ARRAY_%dUC";
      break;
    }

    case AdtAutoType_LONG_LONG:
    {
      pType = "ARRAY_%dLL";
      break;
    }

    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "ARRAY_%dULL";
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "ARRAY_%dB";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "ARRAY_%dLB";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  // This is not re-entrant or thread safe but it doens't need to be either.
  ::sprintf(Buffer, pType, nDimensions);

  return (Buffer);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::cppType(AdtAutoType nType) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      pType = "double";
      break;
    }

    case AdtAutoType_FLOAT:
    {
      pType = "float";
      break;
    }

    case AdtAutoType_SHORT:
    {
      pType = "short";
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    {
      pType = "unsigned short";
      break;
    }

    case AdtAutoType_INT:
    {
      pType = "int";
      break;
    }

    case AdtAutoType_LONG:
    {
      pType = "long";
      break;
    }

    case AdtAutoType_UNSIGNED_INT:
    {
      pType = "unsigned int";
      break;
    }

    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "unsigned long";
      break;
    }

    case AdtAutoType_CHAR:
    {
      pType = "char";
      break;
    }

    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "unsigned char";
      break;
    }

    case AdtAutoType_LONG_LONG:
    {
      pType = "long long";
      break;
    }

    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "unsigned long long";
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "bool";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "longbool";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::R_Type(AdtAutoType nType) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    case AdtAutoType_FLOAT:
    case AdtAutoType_LONG_LONG:
    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "REALSXP";
      break;
    }

    case AdtAutoType_SHORT:
    case AdtAutoType_UNSIGNED_SHORT:
    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "INTSXP";
      break;
    }

    case AdtAutoType_CHAR:
    case AdtAutoType_UNSIGNED_CHAR:
    case AdtAutoType_BOOL:
    {
      pType = "RAWSXP";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "LGLSXP";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::R_AccessType(AdtAutoType nType) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    case AdtAutoType_FLOAT:
    case AdtAutoType_LONG_LONG:
    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = "REAL";
      break;
    }

    case AdtAutoType_UNSIGNED_SHORT:
    case AdtAutoType_UNSIGNED_CHAR:
    {
      pType = "RAW";
      break;
    }

    case AdtAutoType_SHORT:
    case AdtAutoType_CHAR:
    {
      pType = "RAWCHAR";
      break;
    }

    case AdtAutoType_BOOL:
    {
      pType = "RAWBOOL";
      break;
    }

    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "INTEGER";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = "LONGBOOL";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

const char* AdtAutoHelper::R_CheckType(AdtAutoType nType, bool bIsCpp) const
{
  const char* pType = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    case AdtAutoType_FLOAT:
    case AdtAutoType_LONG_LONG:
    case AdtAutoType_UNSIGNED_LONG_LONG:
    {
      pType = bIsCpp ? "isReal" : "Rf_isReal";
      break;
    }

    case AdtAutoType_SHORT:
    case AdtAutoType_UNSIGNED_SHORT:
    case AdtAutoType_INT:
    case AdtAutoType_LONG:
    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      pType = "Rf_isIntegerOrFactor";
      break;
    }

    case AdtAutoType_CHAR:
    case AdtAutoType_UNSIGNED_CHAR:
    case AdtAutoType_BOOL:
    {
      pType = bIsCpp ? "isRaw" : "Rf_isRaw";
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      pType = bIsCpp ? "isLogical" : "Rf_isLogical";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }

  return (pType);
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::DelphiR_registerInterfaceRoutine(const char* pExportRountineName,
                                                     const char* pInternalRountineName,
                                                     size_t nArgs) const
{
  char sBuffer[32] = {0};

  AdtAutoClass::registrationCodeFile().write("(cmdName : '");
  AdtAutoClass::registrationCodeFile().write(pExportRountineName);
  AdtAutoClass::registrationCodeFile().write("'; cmdFunc : @");
  AdtAutoClass::registrationCodeFile().write(pInternalRountineName);
  AdtAutoClass::registrationCodeFile().write("; cmdNumArgs : ");

  ::sprintf(sBuffer, "%zd", nArgs);

  AdtAutoClass::registrationCodeFile().write(sBuffer);
  AdtAutoClass::registrationCodeFile().write("),");
  AdtAutoClass::registrationCodeFile().newline();

  AdtAutoClass::externalsCodeFile().write(pInternalRountineName);
  AdtAutoClass::externalsCodeFile().write(",");
  AdtAutoClass::externalsCodeFile().newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_Return(AdtFile& rFile,
                                        AdtAutoType nType,
                                        const char* pReturn) const
{
  if (pReturn != 0)
  {
    rFile.write("Result := Rf_allocVector(");
    rFile.write(R_Type(nType));
    rFile.write(", 1);");
    rFile.newline();
    rFile.newline();
    rFile.write("Rf_protect(Result);");
    rFile.newline();
    rFile.write("R_");
    rFile.write(R_AccessType(nType));
    rFile.write("(Result)^ := ");
    rFile.write(pReturn);
    rFile.write(";");
    rFile.newline();
    rFile.write("Rf_unprotect(1);");
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_CheckType(AdtFile& rFile,
                                           AdtAutoType nType,
                                           const char* pVar) const
{
  if (pVar != 0)
  {
    rFile.write("if (");
    rFile.write(R_CheckType(nType, false));
    rFile.write("(");
    rFile.write(pVar);
    rFile.write(") = false) then");
    rFile.newline();
    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("Rf_error('ERROR: ");
    rFile.write(pVar);
    rFile.write(" must be of type ");
    rFile.write(R_Type(nType));
    rFile.write(". See line' + {$INCLUDE %LINE%} + ' in file ' + {$INCLUDE %FILE%});");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiVarCheckType(AdtFile& rFile,
                                            const char* pName,
                                            AdtAutoType nType,
                                            int nDimensions,
                                            const char* pExtraArgs) const
{
  rFile.write("R_CheckArgument('");
  rFile.write(pName);
  rFile.write("', '");
  rFile.write(R_Type(nType));
  rFile.write("', ");
  rFile.write(R_Type(nType));
  rFile.write(", ");
  rFile.write(pName);
  rFile.write(", {$I %FILE%}, {$I %LINE%}");

  if (nDimensions != 0)
  {
    char  sBuffer[32] = {0};

    ::sprintf(sBuffer, ", %d", nDimensions);

    rFile.write(sBuffer);

    if (pExtraArgs != 0)
    {
      rFile.write(", [");
      rFile.write(pExtraArgs);
      rFile.write("]");
    }
  }

  rFile.write(");");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_CheckInstance(AdtFile& rFile,
                                               const char* pClassName,
                                               const char* pAliasName) const
{
  rFile.write("R_CHECK_POINTER(rInstance);");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_GetterAndSetter(AdtFile& rFile,
                                                 const char* pName,
                                                 const char* pClassName,
                                                 const char* pAliasName,
                                                 const char* pR_TypeName,
                                                 bool bScalar) const
{
  const char* sTypeC[2] = {"", "nt_"};
  const char* sTypeR[2] = {"", "nt."};

  for (int cn = 0 ; cn < (bScalar ? 1 : 2) ; cn++)
  {
    string  FunctionName;
    string  ExportName;

    // implement getter function
    FunctionName  = pAliasName;
    FunctionName += "_get_";
    FunctionName += sTypeC[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".get.";
    ExportName += sTypeR[cn];
    ExportName += pName;

    DelphiR_registerInterfaceRoutine(ExportName,
                                     FunctionName,
                                     bScalar ? 1 : 2);

    rFile.newline();
    rFile.write("function ");
    rFile.write(FunctionName);
    rFile.write("(args : SEXP) : SEXP; cdecl;");
    rFile.newline();
    rFile.newline();
    rFile.write("var");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("rInstance : SEXP;");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("sArgList: SEXP;");
      rFile.newline();
    }

    rFile.decrementIndent();
    rFile.newline();

    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("args := R_CDR(args); rInstance := R_CAR(args);");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("args := R_CDR(args); sArgList := R_CAR(args);");
      rFile.newline();
    }

    rFile.newline();

    writeDelphiR_CheckInstance(rFile, pClassName, pAliasName);
    rFile.newline();
    rFile.write("Result := ");
    rFile.write(pClassName);
    rFile.write("(R_ExternalPtrAddr(rInstance))._get_");
    rFile.write(sTypeC[cn]);
    rFile.write(pName);
    rFile.write(bScalar ? "();" : "(sArgList);" );
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
    rFile.newline();
    rFile.newline();

    // implement setter function
    FunctionName  = pAliasName;
    FunctionName += "_set_";
    FunctionName += sTypeC[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".set.";
    ExportName += sTypeR[cn];
    ExportName += pName;

    DelphiR_registerInterfaceRoutine(ExportName,
                                     FunctionName,
                                     bScalar ? 2 : 3);

    rFile.write("function ");
    rFile.write(FunctionName);
    rFile.write("(args : SEXP) : SEXP; cdecl;");
    rFile.newline();
    rFile.newline();
    rFile.write("var");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("rInstance : SEXP;");
    rFile.newline();
    rFile.write("arg_");
    rFile.write(pName);
    rFile.write(" : SEXP;");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("sArgList : SEXP;");
      rFile.newline();
    }

    rFile.decrementIndent();
    rFile.newline();

    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("args := R_CDR(args); rInstance := R_CAR(args);");
    rFile.newline();
    rFile.write("args := R_CDR(args); arg_");
    rFile.write(pName);
    rFile.write(" := R_CAR(args);");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("args := R_CDR(args); sArgList := R_CAR(args);");
      rFile.newline();
    }

    rFile.newline();
    writeDelphiR_CheckInstance(rFile, pClassName, pAliasName);
    rFile.newline();
    rFile.write("Result := ");
    rFile.write(pClassName);
    rFile.write("(R_ExternalPtrAddr(rInstance))._set_");
    rFile.write(sTypeC[cn]);
    rFile.write(pName);
    rFile.write("(arg_");
    rFile.write(pName);
    rFile.write(bScalar ? ");" : ", sArgList);");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
    rFile.newline();
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_GlobalGetter(AdtFile& rFile,
                                              const char* pName,
                                              const char* pAliasName,
                                              AdtAutoType nType) const
{
  string  FunctionName;
  string  ExportName;

  // implement getter function
  FunctionName  = pAliasName;
  FunctionName += "_get_";
  FunctionName += pName;

  ExportName  = "_";
  ExportName += pAliasName;
  ExportName += ".get.";
  ExportName += pName;

  DelphiR_registerInterfaceRoutine(ExportName,
                                   FunctionName,
                                   0);

  rFile.newline();
  rFile.write("function ");
  rFile.write(FunctionName);
  rFile.write("() : SEXP; cdecl;");
  rFile.newline();
  rFile.newline();
  rFile.write("begin");
  rFile.incrementIndent();
  rFile.newline();

  writeDelphiR_Return(rFile, nType, pName);

  rFile.decrementIndent();
  rFile.newline();
  rFile.write("end;");
  rFile.newline();
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_InterfaceDeclMethods(AdtFile& rFile,
                                                      const char* pName,
                                                      const AdtAutoAttributePtrList& rArgumentList) const
{
  int         cn;
  const char* pTranslateTxt = (rArgumentList.size() > 0) ? "; bTranslate : boolean" : "bTranslate : boolean";
  const char* sPrefix[3]    = {"internal_", "", "nt_"};
  const char* sArgs[3]      = {pTranslateTxt, "", ""};

  for (cn = 0 ; cn < 3 ; cn++)
  {
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    // declare interface method
    rFile.write("function R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    // declare function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write("; ");
        }
        else
        {
          bFirst = false;
        }

        rFile.write(pAttribute->name().c_str());
        rFile.write(" : SEXP");
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(sArgs[cn]);
    rFile.write(") : SEXP;");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_InterfaceDeclGlobals(AdtFile& rFile,
                                                      const char* pName,
                                                      const AdtAutoAttributePtrList& rArgumentList,
                                                      const char* pAliasName) const
{
  int         cn;
  const char* sPrefix[2] = {"", "nt_"};

  for (cn = 0 ; cn < 2 ; cn++)
  {
    // declare interface wrapper function
    rFile.write("function ");
    rFile.write(pAliasName);
    rFile.write("_R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(args : SEXP) : SEXP; cdecl;");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_InterfaceImplMethods(AdtFile& rFile,
                                                      const char* pName,
                                                      AdtAutoType nType,
                                                      const AdtAutoAttributePtrList& rArgumentList,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  AdtAutoAttributePtrListConstIter  Iter;
  bool                              bFirst            = true;
  bool                              bHasOutParameters = false;
  AdtStringByStringMap              LocalsMap;

  // implement internal class interface function
  rFile.newline();
  rFile.write("function ");
  rFile.write(pClassName);
  rFile.write(".R_internal_");
  rFile.write(pName);
  rFile.write("(");

  // declare function arguments
  for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
  {
    const AdtAutoAttribute* pAttribute = *Iter;

    if (pAttribute != 0)
    {
      if (!bFirst)
      {
        rFile.write("; ");
      }
      else
      {
        bFirst = false;
      }

      rFile.write(pAttribute->name().c_str());
      rFile.write(" : SEXP");
    }
    else
    {
      // Should never happen
      FAIL();
    }
  }

  rFile.write((rArgumentList.size() > 0) ? "; bTranslate : boolean) : SEXP;" : "bTranslate : boolean) : SEXP;");
  rFile.newline();

  for (int nPass = 0 ; nPass < 2 ; nPass++)
  {
    switch (nPass)
    {
      case 0:
      {
        rFile.disable();
        break;
      }

      default:
      case 1:
      {
        AdtStringByStringMapIter  StrIter;
        bool                      bVarDeclared = false;

        rFile.enable();

        if (rArgumentList.size() > 0)
        {
          rFile.newline();
          rFile.write("var");
          rFile.incrementIndent();
          rFile.newline();

          bVarDeclared = true;

          // declare arguments to pass to class method
          for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
          {
            const AdtAutoAttribute* pAttribute = *Iter;

            if (pAttribute != 0)
            {
              pAttribute->writeVarDeclaration(rFile, DelphiSourceFileType, false, false);
              rFile.write(";");
              rFile.newline();
            }
            else
            {
              // Should never happen
              FAIL();
            }
          }
        }

        if (LocalsMap.size() > 0)
        {
          if (!bVarDeclared)
          {
            rFile.newline();
            rFile.write("var");
            rFile.incrementIndent();
            rFile.newline();
          }

          for (StrIter = LocalsMap.begin() ; StrIter != LocalsMap.end() ; ++StrIter)
          {
            rFile.write(StrIter->second);
            rFile.write(";");
            rFile.newline();
          }

          LocalsMap.clear();
        }

        if (bVarDeclared)
        {
          rFile.decrementIndent();
          rFile.newline();
        }
        break;
      }
    }

    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();

    // Check argument types
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarCheckType(rFile, DelphiSourceFileType, false, false);

        rFile.newline();
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write("if bTranslate then");
    rFile.newline();
    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();

    // initialise arguments to pass to class method with translation
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        switch (pAttribute->dir())
        {
          case AdtAutoDir_INOUT:
          case AdtAutoDir_OUT:
          {
            bHasOutParameters = true;
            break;
          }

          case AdtAutoDir_IN:
          case AdtAutoDir_UNDEFINED:
          default:
          {
            // Do nothing
            break;
          }
        }

        pAttribute->writeVarInitialisation(rFile, DelphiSourceFileType, LocalsMap, pClassName, true);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.decrementIndent();
    rFile.homeline();
    rFile.write("end");
    rFile.newline();
    rFile.write("else");
    rFile.newline();
    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();

    // initialise arguments to pass to class method without translation
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarInitialisation(rFile, DelphiSourceFileType, LocalsMap, pClassName, false);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.decrementIndent();
    rFile.homeline();
    rFile.write("end;");
    rFile.newline();
    rFile.newline();

    if (nType != AdtAutoType_UNDEFINED)
    {
      rFile.write("Result := Rf_allocVector(");
      rFile.write(R_Type(nType));
      rFile.write(", 1);");
      rFile.newline();
      rFile.newline();
      rFile.write("Rf_protect(Result);");
      rFile.newline();
      rFile.write("R_");
      rFile.write(R_AccessType(nType));
      rFile.write("(Result)^ := ");
    }
    else
    {
      rFile.write("Result := Rf_allocVector(REALSXP, 1);");
      rFile.newline();
      rFile.newline();
      rFile.write("Rf_protect(Result);");
      rFile.newline();
      rFile.write("R_REAL(Result)^ := 0.0;");
      rFile.newline();
    }

    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write("arg_");
        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(");");
    rFile.newline();

    if (bHasOutParameters)
    {
      // translate results back to source arguments
      rFile.newline();
      rFile.write("if bTranslate then");
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();

      // initialise arguments to pass to class method with translation
      for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
      {
        const AdtAutoAttribute* pAttribute = *Iter;

        if (pAttribute != 0)
        {
          switch (pAttribute->dir())
          {
            case AdtAutoDir_INOUT:
            case AdtAutoDir_OUT:
            {
              pAttribute->writeVarReturn(rFile, DelphiSourceFileType, pClassName);
              break;
            }

            case AdtAutoDir_IN:
            case AdtAutoDir_UNDEFINED:
            default:
            {
              // Do nothing
              break;
            }
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.decrementIndent();
      rFile.homeline();
      rFile.write("end");
      rFile.newline();
      rFile.write("else");
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();

      // initialise arguments to pass to class method with translation
      for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
      {
        const AdtAutoAttribute* pAttribute = *Iter;

        if (pAttribute != 0)
        {
          if (pAttribute->isScalar())
          {
            switch (pAttribute->dir())
            {
              case AdtAutoDir_INOUT:
              case AdtAutoDir_OUT:
              {
                pAttribute->writeVarReturn(rFile, DelphiSourceFileType, pClassName);
                break;
              }

              case AdtAutoDir_IN:
              case AdtAutoDir_UNDEFINED:
              default:
              {
                // Do nothing
                break;
              }
            }
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.decrementIndent();
      rFile.homeline();
      rFile.write("end;");
    }

    rFile.newline();

    // free temporary arrays
    if (rArgumentList.size() > 0)
    {
      rFile.newline();
    }

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarDestroy(rFile, DelphiSourceFileType);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write("Rf_unprotect(1);");

    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
    rFile.newline();
  }

  // implement translated and not translated class interface functions
  const char* sPrefix[2]    = {"", "nt_"};
  const char* sTranslate[2] = {"true", "false"};
  int         cn            = 0;

  for (cn = 0 ; cn < 2 ; cn++)
  {
    bFirst = true;

    rFile.newline();
    rFile.write("function ");
    rFile.write(pClassName);
    rFile.write(".R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    // declare function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write("; ");
        }
        else
        {
          bFirst = false;
        }

        rFile.write(pAttribute->name().c_str());
        rFile.write(" : SEXP");
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(") : SEXP;");
    rFile.newline();
    rFile.newline();
    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("Result := R_internal_");
    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    if (rArgumentList.size() > 0)
    {
      rFile.write(", ");
    }

    rFile.write(sTranslate[cn]);
    rFile.write(");");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeDelphiR_InterfaceImplGlobals(AdtFile& rFile,
                                                      const char* pName,
                                                      AdtAutoType nType,
                                                      const AdtAutoAttributePtrList& rArgumentList,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  const char* sPrefix[2]  = {"", "nt_"};
  const char* sPrefixR[2] = {"", "nt."};
  int         cn          = 0;

  for (cn = 0 ; cn < 2 ; cn++)
  {
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    string  FunctionName;
    string  ExportName;

    // implement getter function
    FunctionName  = pAliasName;
    FunctionName += "_R_";
    FunctionName += sPrefix[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".";
    ExportName += sPrefixR[cn];
    ExportName += pName;

    DelphiR_registerInterfaceRoutine(ExportName,
                                     FunctionName,
                                     rArgumentList.size() + 1);

    // implement interface wrapper function
    rFile.write("function ");
    rFile.write(FunctionName);
    rFile.write("(args : SEXP) : SEXP; cdecl;");

    // declare locals for arguments
    rFile.newline();
    rFile.newline();
    rFile.write("var");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("rInstance : SEXP;");
    rFile.newline();

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (Iter != rArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write(pAttribute->name().c_str());
        rFile.write(" : SEXP;");
      }
    }

    rFile.decrementIndent();
    rFile.newline();
    rFile.newline();
    rFile.write("begin");
    rFile.incrementIndent();
    rFile.newline();

    // Read .External args
    rFile.write("args := R_CDR(args); rInstance := R_CAR(args);");
    rFile.newline();

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (Iter != rArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("args := R_CDR(args); ");
        rFile.write(pAttribute->name().c_str());
        rFile.write(" := R_CAR(args);");
      }
    }

    rFile.newline();
    rFile.newline();
    writeDelphiR_CheckInstance(rFile, pClassName, pAliasName);
    rFile.newline();

    rFile.write("Result := ");
    rFile.write(pClassName);
    rFile.write("(R_ExternalPtrAddr(rInstance)).R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(");");

    rFile.decrementIndent();
    rFile.newline();
    rFile.write("end;");
    rFile.newline();
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::CppR_registerInterfaceRoutine(const char* pExportRountineName,
                                                  const char* pInternalRountineName,
                                                  size_t nArgs) const
{
  char sBuffer[32] = {0};

  AdtAutoClass::registrationCodeFile().write("{\"");
  AdtAutoClass::registrationCodeFile().write(pExportRountineName);
  AdtAutoClass::registrationCodeFile().write("\", (DL_FUNC)&");
  AdtAutoClass::registrationCodeFile().write(pInternalRountineName);
  AdtAutoClass::registrationCodeFile().write(", ");

  ::sprintf(sBuffer, "%zd", nArgs);

  AdtAutoClass::registrationCodeFile().write(sBuffer);
  AdtAutoClass::registrationCodeFile().write("},");
  AdtAutoClass::registrationCodeFile().newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_AllocReturn(AdtFile& rFile,
                                          AdtAutoType nType,
                                          const char* pReturn) const
{
  if (pReturn != 0)
  {
    rFile.write("SEXP Result = allocVector(");
    rFile.write(R_Type(nType));
    rFile.write(", 1);");
    rFile.newline();
    rFile.newline();
    rFile.write("PROTECT(Result);");
    rFile.newline();
    rFile.write(R_AccessType(nType));
    rFile.write("(Result)[0] = ");
    rFile.write(pReturn);
    rFile.write(";");
    rFile.newline();
    rFile.write("UNPROTECT(1);");
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_Return(AdtFile& rFile,
                                     AdtAutoType nType,
                                     const char* pReturn) const
{
  if (pReturn != 0)
  {
    writeCppR_AllocReturn(rFile, nType, pReturn);

    rFile.newline();
    rFile.newline();
    rFile.write("return(Result);");
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_CheckType(AdtFile& rFile,
                                        AdtAutoType nType,
                                        const char* pVar) const
{
  if (pVar != 0)
  {
    rFile.write("if (");
    rFile.write(R_CheckType(nType, true));
    rFile.write("(");
    rFile.write(pVar);
    rFile.write(") == 0)");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("Rf_error(\"ERROR: ");
    rFile.write(pVar);
    rFile.write(" must be of type ");
    rFile.write(R_Type(nType));
    rFile.write(". See line %d in file %s\", __LINE__, __FILE__);");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppVarCheckType(AdtFile& rFile,
                                         const char* pName,
                                         AdtAutoType nType,
                                         int nDimensions,
                                         const char* pExtraArgs) const
{
  rFile.write("R_CheckArgument(\"");
  rFile.write(pName);
  rFile.write("\", \"");
  rFile.write(R_Type(nType));
  rFile.write("\", ");
  rFile.write(R_Type(nType));
  rFile.write(", ");
  rFile.write(pName);
  rFile.write(", __FILE__, __LINE__");

  if (nDimensions != 0)
  {
    char  sBuffer[32] = {0};

    ::sprintf(sBuffer, ", %d", nDimensions);

    rFile.write(sBuffer);

    if (pExtraArgs != 0)
    {
      rFile.write(", ");
      rFile.write(pExtraArgs);
    }
  }

  rFile.write(");");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_CheckInstance(AdtFile& rFile,
                                            const char* pR_TypeName) const
{
  rFile.write("ASSERT_TYPE_TAG(rInstance, ");
  rFile.write(pR_TypeName);
  rFile.write(");");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_GetterAndSetter(AdtFile& rFile,
                                              const char* pName,
                                              const char* pClassName,
                                              const char* pAliasName,
                                              const char* pR_TypeName,
                                              bool bScalar) const
{
  const char* sTypeC[2] = {"", "nt_"};
  const char* sTypeR[2] = {"", "nt."};

  for (int cn = 0 ; cn < (bScalar ? 1 : 2) ; cn++)
  {
    string  FunctionName;
    string  ExportName;

    // implement getter function
    FunctionName  = pAliasName;
    FunctionName += "_get_";
    FunctionName += sTypeC[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".get.";
    ExportName += sTypeR[cn];
    ExportName += pName;

    CppR_registerInterfaceRoutine(ExportName,
                                  FunctionName,
                                  bScalar ? 1 : 2);

    rFile.newline();
    rFile.write("EXPORT SEXP ");
    rFile.write(FunctionName);
    rFile.write("(SEXP args)");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("SEXP rInstance;");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("SEXP sArgList;");
      rFile.newline();
    }

    rFile.write("args = CDR(args); rInstance = CAR(args);");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("args = CDR(args); sArgList = CAR(args);");
      rFile.newline();
    }

    rFile.newline();

    writeCppR_CheckInstance(rFile, pR_TypeName);
    rFile.newline();
    rFile.write(pClassName);
    rFile.write("* pContext = (");
    rFile.write(pClassName);
    rFile.write("*)R_ExternalPtrAddr(rInstance);");
    rFile.newline();
    rFile.newline();
    rFile.write("return (pContext->_get_");
    rFile.write(sTypeC[cn]);
    rFile.write(pName);
    rFile.write(bScalar ? "());" : "(sArgList));" );
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
    rFile.newline();
    rFile.newline();

    // implement setter function
    FunctionName  = pAliasName;
    FunctionName += "_set_";
    FunctionName += sTypeC[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".set.";
    ExportName += sTypeR[cn];
    ExportName += pName;

    CppR_registerInterfaceRoutine(ExportName,
                                  FunctionName,
                                  bScalar ? 2 : 3);

    rFile.write("EXPORT SEXP ");
    rFile.write(FunctionName);
    rFile.write("(SEXP args)");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("SEXP rInstance;");
    rFile.newline();
    rFile.write("SEXP arg_");
    rFile.write(pName);
    rFile.write(";");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("SEXP sArgList;");
      rFile.newline();
    }

    rFile.newline();
    rFile.newline();
    rFile.write("args = CDR(args); rInstance = CAR(args);");
    rFile.newline();
    rFile.write("args = CDR(args); arg_");
    rFile.write(pName);
    rFile.write(" = CAR(args);");
    rFile.newline();

    if (!bScalar)
    {
      rFile.write("args = CDR(args); sArgList = CAR(args);");
      rFile.newline();
    }

    rFile.newline();
    writeCppR_CheckInstance(rFile, pR_TypeName);
    rFile.newline();
    rFile.write(pClassName);
    rFile.write("* pContext = (");
    rFile.write(pClassName);
    rFile.write("*)R_ExternalPtrAddr(rInstance);");
    rFile.newline();
    rFile.newline();
    rFile.write("return (pContext->_set_");
    rFile.write(sTypeC[cn]);
    rFile.write(pName);
    rFile.write("(arg_");
    rFile.write(pName);
    rFile.write(bScalar ? "));" : ", sArgList));");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
    rFile.newline();
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_GlobalGetter(AdtFile& rFile,
                                           const char* pName,
                                           const char* pAliasName,
                                           AdtAutoType nType) const
{
  string  FunctionName;
  string  ExportName;

  // implement getter function
  FunctionName  = pAliasName;
  FunctionName += "_get_";
  FunctionName += pName;

  ExportName  = "_";
  ExportName += pAliasName;
  ExportName += ".get.";
  ExportName += pName;

  CppR_registerInterfaceRoutine(ExportName,
                                FunctionName,
                                0);

  rFile.newline();
  rFile.write("EXPORT SEXP ");
  rFile.write(FunctionName);
  rFile.write("()");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();

  writeCppR_Return(rFile, nType, pName);

  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_InterfaceDeclMethods(AdtFile& rFile,
                                                   const char* pName,
                                                   const AdtAutoAttributePtrList& rArgumentList) const
{
  int         cn;
  const char* pTranslateTxt = (rArgumentList.size() > 0) ? ", bool bTranslate" : "bool bTranslate";
  const char* sPrefix[3]    = {"internal_", "", "nt_"};
  const char* sArgs[3]      = {pTranslateTxt, "", ""};

  for (cn = 0 ; cn < 3 ; cn++)
  {
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    // declare interface method
    rFile.write("SEXP R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    // declare function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }
        else
        {
          bFirst = false;
        }

        rFile.write("SEXP ");
        rFile.write(pAttribute->name().c_str());
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(sArgs[cn]);
    rFile.write(");");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_InterfaceDeclGlobals(AdtFile& rFile,
                                                   const char* pName,
                                                   const AdtAutoAttributePtrList& rArgumentList,
                                                   const char* pAliasName) const
{
  int         cn;
  const char* sPrefix[2] = {"", "nt_"};

  for (cn = 0 ; cn < 2 ; cn++)
  {
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    // declare interface wrapper function
    rFile.write("EXPORT SEXP ");
    rFile.write(pAliasName);
    rFile.write("_R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(SEXP args);");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_InterfaceImplMethods(AdtFile& rFile,
                                                   const char* pName,
                                                   AdtAutoType nType,
                                                   const AdtAutoAttributePtrList& rArgumentList,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const
{
  AdtAutoAttributePtrListConstIter  Iter;
  bool                              bFirst            = true;
  bool                              bHasOutParameters = false;
  AdtStringByStringMap              LocalsMap;

  // implement internal class interface function
  rFile.newline();
  rFile.write("SEXP ");
  rFile.write(pClassName);
  rFile.write("::R_internal_");
  rFile.write(pName);
  rFile.write("(");

  // declare function arguments
  for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
  {
    const AdtAutoAttribute* pAttribute = *Iter;

    if (pAttribute != 0)
    {
      if (!bFirst)
      {
        rFile.write(", ");
      }
      else
      {
        bFirst = false;
      }

      rFile.write("SEXP ");
      rFile.write(pAttribute->name().c_str());
    }
    else
    {
      // Should never happen
      FAIL();
    }
  }

  const char* pTranslateTxt = (rArgumentList.size() > 0) ? ", bool bTranslate)" : "bool bTranslate)";

  rFile.write(pTranslateTxt);
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();

  for (int nPass = 0 ; nPass < 2 ; nPass++)
  {
    switch (nPass)
    {
      case 0:
      {
        rFile.disable();
        break;
      }

      default:
      case 1:
      {
        AdtStringByStringMapIter  Iter;

        rFile.enable();

        for (Iter = LocalsMap.begin() ; Iter != LocalsMap.end() ; ++Iter)
        {
          rFile.write(Iter->second);
          rFile.write(";");
          rFile.newline();
        }

        LocalsMap.clear();
        break;
      }
    }

    if (rArgumentList.size() > 0)
    {
      // declare arguments to pass to class method
      for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
      {
        const AdtAutoAttribute* pAttribute = *Iter;

        if (pAttribute != 0)
        {
          pAttribute->writeVarDeclaration(rFile, CppSourceFileType, false, false);
          rFile.write(";");
          rFile.newline();
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.newline();
    }

    // Check argument types
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarCheckType(rFile, CppSourceFileType, false, false);

        rFile.newline();
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write("if (bTranslate)");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();

    // initialise arguments to pass to class method with translation
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        switch (pAttribute->dir())
        {
          case AdtAutoDir_INOUT:
          case AdtAutoDir_OUT:
          {
            bHasOutParameters = true;
            break;
          }

          case AdtAutoDir_IN:
          case AdtAutoDir_UNDEFINED:
          default:
          {
            // Do nothing
            break;
          }
        }

        pAttribute->writeVarInitialisation(rFile, CppSourceFileType, LocalsMap, pClassName, true);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.decrementIndent();
    rFile.homeline();
    rFile.write("}");
    rFile.newline();
    rFile.write("else");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();

    // initialise arguments to pass to class method without translation
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarInitialisation(rFile, CppSourceFileType, LocalsMap, pClassName, false);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.decrementIndent();
    rFile.homeline();
    rFile.write("}");
    rFile.newline();
    rFile.newline();

    if (nType != AdtAutoType_UNDEFINED)
    {
      rFile.write("SEXP Result = Rf_allocVector(");
      rFile.write(R_Type(nType));
      rFile.write(", 1);");
      rFile.newline();
      rFile.newline();
      rFile.write("PROTECT(Result);");
      rFile.newline();
      rFile.write(R_AccessType(nType));
      rFile.write("(Result)[0] = ");
    }
    else
    {
      rFile.write("SEXP Result = Rf_allocVector(REALSXP, 1);");
      rFile.newline();
      rFile.newline();
      rFile.write("PROTECT(Result);");
      rFile.newline();
      rFile.write("REAL(Result)[0] = 0.0;");
      rFile.newline();
    }

    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write("arg_");
        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(");");
    rFile.newline();

    if (bHasOutParameters)
    {
      // translate results back to source arguments
      rFile.newline();
      rFile.write("if (bTranslate)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();

      // initialise arguments to pass to class method with translation
      for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
      {
        const AdtAutoAttribute* pAttribute = *Iter;

        if (pAttribute != 0)
        {
          switch (pAttribute->dir())
          {
            case AdtAutoDir_INOUT:
            case AdtAutoDir_OUT:
            {
              pAttribute->writeVarReturn(rFile, CppSourceFileType, pClassName);
              break;
            }

            case AdtAutoDir_IN:
            case AdtAutoDir_UNDEFINED:
            default:
            {
              // Do nothing
              break;
            }
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.decrementIndent();
      rFile.homeline();
      rFile.write("}");
      rFile.newline();
      rFile.write("else");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();

      // initialise arguments to pass to class method with translation
      for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
      {
        const AdtAutoAttribute* pAttribute = *Iter;

        if (pAttribute != 0)
        {
          if (pAttribute->isScalar())
          {
            switch (pAttribute->dir())
            {
              case AdtAutoDir_INOUT:
              case AdtAutoDir_OUT:
              {
                pAttribute->writeVarReturn(rFile, CppSourceFileType, pClassName);
                break;
              }

              case AdtAutoDir_IN:
              case AdtAutoDir_UNDEFINED:
              default:
              {
                // Do nothing
                break;
              }
            }
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.decrementIndent();
      rFile.homeline();
      rFile.write("}");
    }

    rFile.newline();

    // free temporary arrays
    if (rArgumentList.size() > 0)
    {
      rFile.newline();
    }

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        pAttribute->writeVarDestroy(rFile, CppSourceFileType);
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write("UNPROTECT(1);");
    rFile.newline();
    rFile.newline();
    rFile.write("return (Result);");
  }

  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();

  // implement translated and not translated class interface functions
  const char* sPrefix[2]    = {"", "nt_"};
  const char* sTranslate[2] = {"true", "false"};
  int         cn            = 0;

  for (cn = 0 ; cn < 2 ; cn++)
  {
    bFirst = true;

    rFile.newline();
    rFile.write("SEXP ");
    rFile.write(pClassName);
    rFile.write("::R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    // declare function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }
        else
        {
          bFirst = false;
        }

        rFile.write("SEXP ");
        rFile.write(pAttribute->name().c_str());
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(")");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("return (R_internal_");
    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    if (rArgumentList.size() > 0)
    {
      rFile.write(", ");
    }

    rFile.write(sTranslate[cn]);
    rFile.write("));");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeCppR_InterfaceImplGlobals(AdtFile& rFile,
                                                   const char* pName,
                                                   AdtAutoType nType,
                                                   const AdtAutoAttributePtrList& rArgumentList,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const
{
  const char* sPrefix[2]  = {"", "nt_"};
  const char* sPrefixR[2] = {"", "nt."};
  int         cn          = 0;

  for (cn = 0 ; cn < 2 ; cn++)
  {
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    string  FunctionName;
    string  ExportName;

    // implement global function
    FunctionName  = pAliasName;
    FunctionName += "_R_";
    FunctionName += sPrefix[cn];
    FunctionName += pName;

    ExportName  = "_";
    ExportName += pAliasName;
    ExportName += ".";
    ExportName += sPrefixR[cn];
    ExportName += pName;

    CppR_registerInterfaceRoutine(ExportName,
                                  FunctionName,
                                  rArgumentList.size() + 1);

    // implement interface wrapper function
    rFile.newline();
    rFile.write("EXPORT SEXP ");
    rFile.write(FunctionName);
    rFile.write("(SEXP args)");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("SEXP rInstance;");
    rFile.newline();

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (Iter != rArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("SEXP ");
        rFile.write(pAttribute->name().c_str());
        rFile.write(";");
      }
    }

    rFile.newline();
    rFile.newline();

    // Read .External args
    rFile.write("args = CDR(args); rInstance = CAR(args);");
    rFile.newline();

    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (Iter != rArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("args = CDR(args); ");
        rFile.write(pAttribute->name().c_str());
        rFile.write(" = CAR(args);");
      }
    }

    rFile.newline();
    rFile.newline();
    writeCppR_CheckInstance(rFile, pR_TypeName);
    rFile.newline();

    rFile.write(pClassName);
    rFile.write("* pContext = (");
    rFile.write(pClassName);
    rFile.write("*)R_ExternalPtrAddr(rInstance);");
    rFile.newline();
    rFile.newline();

    rFile.write("SEXP Result = pContext->R_");
    rFile.write(sPrefix[cn]);
    rFile.write(pName);
    rFile.write("(");

    bFirst = true;

    // Pass function arguments
    for (Iter = rArgumentList.begin() ; Iter != rArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (pAttribute != 0)
      {
        if (!bFirst)
        {
          rFile.write(", ");
        }

        rFile.write(pAttribute->name().c_str());

        bFirst = false;
      }
      else
      {
        // Should never happen
        FAIL();
      }
    }

    rFile.write(");");
    rFile.newline();
    rFile.newline();
    rFile.write("return (Result);");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoHelper::writeR_typeCast(AdtFile& rFile,
                                    AdtAutoType nType,
                                    const char* pVar,
                                    const char* pContext) const
{
  const char* pCast = 0;

  switch(nType)
  {
    case AdtAutoType_DOUBLE:
    {
      rFile.write("as.double(");
      rFile.write(pVar);
      rFile.write(")");
      break;
    }

    // Strictly speaking, AdtAutoType_LONG should not be used for interfaces
    // bacause it is not portable between 64 and 32 bit variants of R on Linux.
    // It will work for Windows platforms because they use a different programming
    // model. I leave this in for backward compatibility with Mark Bravingtons
    // code but he should switch from using LONG to INT.
    case AdtAutoType_LONG:
    {
      ::printf("WARNING: Variable %s is a long / LONG and used as an interface "
               "type to R but this type is not portable between 64 and 32 bit "
               "platforms. Use INT/int instead.\n", pContext);
    }

    case AdtAutoType_INT:
    {
      rFile.write("as.integer(");
      rFile.write(pVar);
      rFile.write(")");
      break;
    }

    // It's essential to have something for 1-byte data. Not entirely sure it's
    // just OK to do this with BOOLs too. TRUE/FALSE are OK but NA is coerced
    // to FALSE in R
    case AdtAutoType_CHAR:
    case AdtAutoType_UNSIGNED_CHAR:
    case AdtAutoType_BOOL:
    {
      rFile.write("as.raw(");
      rFile.write(pVar);
      rFile.write(")");
      break;
    }

    case AdtAutoType_LONGBOOL:
    {
      rFile.write("as.logical(");
      rFile.write(pVar);
      rFile.write(")");
      break;
    }

    case AdtAutoType_FLOAT:
    case AdtAutoType_LONG_LONG:
    case AdtAutoType_UNSIGNED_LONG_LONG:
    case AdtAutoType_SHORT:
    case AdtAutoType_UNSIGNED_SHORT:
    case AdtAutoType_UNSIGNED_INT:
    case AdtAutoType_UNSIGNED_LONG:
    {
      ::printf("ERROR: Variable %s is type %s / %s which is not supported as interface type to R\n",
               pContext,
               cppType(nType),
               delphiType(nType));
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
//  AdtAutoAttribute method implementations
//  ----------------------------------------------------------------------------
AdtAutoType AdtAutoAttribute::fortranTypeToAutoType(const char* pType)
{
  AdtAutoType nType = AdtAutoType_UNDEFINED;

  if (caseless_string_comparison("REAL", pType) == 0)
  {
    nType = AdtAutoType_DOUBLE;
  }
  else if (caseless_string_comparison("REAL(8)", pType) == 0)
  {
    nType = AdtAutoType_DOUBLE;
  }
  else if (caseless_string_comparison("REAL(4)", pType) == 0)
  {
    nType = AdtAutoType_FLOAT;
  }
  else if (caseless_string_comparison("INTEGER(2)", pType) == 0)
  {
    nType = AdtAutoType_SHORT;
  }
  else if (caseless_string_comparison("UNSIGNED(2)", pType) == 0)
  {
    nType = AdtAutoType_UNSIGNED_SHORT;
  }
  else if (caseless_string_comparison("INTEGER", pType) == 0)
  {
    nType = AdtAutoType_INT;
  }
  else if (caseless_string_comparison("UNSIGNED", pType) == 0)
  {
    nType = AdtAutoType_UNSIGNED_INT;
  }
  else if (caseless_string_comparison("INTEGER(1)", pType) == 0)
  {
    nType = AdtAutoType_CHAR;
  }
  else if (caseless_string_comparison("UNSIGNED(1)", pType) == 0)
  {
    nType = AdtAutoType_UNSIGNED_CHAR;
  }
  else if (caseless_string_comparison("INTEGER(4)", pType) == 0)
  {
    nType = AdtAutoType_LONG;
  }
  else if (caseless_string_comparison("UNSIGNED(4)", pType) == 0)
  {
    nType = AdtAutoType_UNSIGNED_LONG;
  }
  else if (caseless_string_comparison("INTEGER(8)", pType) == 0)
  {
    nType = AdtAutoType_LONG_LONG;
  }
  else if (caseless_string_comparison("UNSIGNED(8)", pType) == 0)
  {
    nType = AdtAutoType_UNSIGNED_LONG_LONG;
  }
  else if (caseless_string_comparison("LOGICAL", pType) == 0)
  {
    nType = AdtAutoType_BOOL;
  }
  else if (caseless_string_comparison("LOGICAL(4)", pType) == 0)
  {
    nType = AdtAutoType_LONGBOOL;
  }

  return (nType);
}

//  ----------------------------------------------------------------------------

bool AdtAutoAttribute::addMapEntry(AdtStringByStringMap& rMap, const char* pKey, const char* pEntry)
{
  bool bAdded = false;

  if ((pKey != 0) && (pEntry != 0))
  {
    AdtStringByStringMapIter  Iter = rMap.find(pKey);

    if (Iter == rMap.end())
    {
      rMap[pKey]  = pEntry;
      bAdded      = true;
    }
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDelphiDeclLibInterfaceMethods(AdtFile& rFile) const
{
  if (!this->isRagged())
  {
    const char* sTypeC[2] = {"", "nt_"};

    for (int cn = 0 ; cn < (this->isScalar() ? 1 : 2) ; cn++)
    {
      // Declare get and set class methods
      rFile.write("function _get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write(this->isScalar() ? "() : SEXP;" : "(sArgList : SEXP) : SEXP;");
      rFile.newline();
      rFile.write("function _set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(arg_");
      rFile.write(name());
      rFile.write(this->isScalar() ? " : SEXP) : SEXP;" : " : SEXP; sArgList : SEXP) : SEXP;");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDelphiDeclLibInterfaceGlobals(AdtFile& rFile,
                                                          const char* pAliasName) const
{
  if (!this->isRagged())
  {
    const char* sTypeC[2] = {"", "nt_"};

    for (int cn = 0 ; cn < (this->isScalar() ? 1 : 2) ; cn++)
    {
      // Declare get and set class methods
      rFile.write("function ");
      rFile.write(pAliasName);
      rFile.write("_get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(args : SEXP) : SEXP; cdecl;");
      rFile.newline();
      rFile.write("function ");
      rFile.write(pAliasName);
      rFile.write("_set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(args : SEXP) : SEXP; cdecl;");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeCppDeclLibInterfaceMethods(AdtFile& rFile) const
{
  if (!this->isRagged())
  {
    const char* sTypeC[2] = {"", "nt_"};

    for (int cn = 0 ; cn < (this->isScalar() ? 1 : 2) ; cn++)
    {
      // Declare get and set class methods
      rFile.write("SEXP _get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write(this->isScalar() ? "() const;" : "(SEXP sArgList) const;");
      rFile.newline();
      rFile.write("SEXP _set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(SEXP arg_");
      rFile.write(name());
      rFile.write(this->isScalar() ? ");" : ", SEXP sArgList);");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeCppDeclLibInterfaceGlobals(AdtFile& rFile,
                                                       const char* pAliasName) const
{
  if (!this->isRagged())
  {
    const char* sTypeC[2] = {"", "nt_"};

    for (int cn = 0 ; cn < (this->isScalar() ? 1 : 2) ; cn++)
    {
      // Declare get and set class methods
      rFile.write("EXPORT SEXP ");
      rFile.write(pAliasName);
      rFile.write("_get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(SEXP args);");
      rFile.newline();
      rFile.write("EXPORT SEXP ");
      rFile.write(pAliasName);
      rFile.write("_set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(SEXP args);");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::delphiType(int nDimensions) const
{
  AdtAutoHelper Helper;

  return (Helper.delphiType(type(), nDimensions));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::delphiType() const
{
  AdtAutoHelper Helper;

  return (Helper.delphiType(type()));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::delphiConstructorType() const
{
  AdtAutoHelper Helper;

  return (Helper.delphiConstructorType(type()));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::cppType(int nDimensions) const
{
  AdtAutoHelper Helper;

  return (Helper.cppType(type(), nDimensions));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::cppType() const
{
  AdtAutoHelper Helper;

  return (Helper.cppType(type()));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::R_Type() const
{
  AdtAutoHelper Helper;

  return (Helper.R_Type(type()));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::R_AccessType() const
{
  AdtAutoHelper Helper;

  return (Helper.R_AccessType(type()));
}

//  ----------------------------------------------------------------------------

const char* AdtAutoAttribute::R_CheckType(bool bIsCpp) const
{
  AdtAutoHelper Helper;

  return (Helper.R_CheckType(type(), bIsCpp));
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDelphiR_Return(AdtFile& rFile, const char* pReturn) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_Return(rFile, type(), pReturn);
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDelphiR_CheckType(AdtFile& rFile, const char* pVar) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_CheckType(rFile, type(), pVar);
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDelphiR_GetterAndSetter(AdtFile& rFile,
                                                    const char* pClassName,
                                                    const char* pAliasName,
                                                    const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_GetterAndSetter(rFile, name().c_str(), pClassName, pAliasName, pR_TypeName, this->isScalar());
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeCppR_Return(AdtFile& rFile, const char* pReturn) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_Return(rFile, type(), pReturn);
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeCppR_CheckType(AdtFile& rFile, const char* pVar) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_CheckType(rFile, type(), pVar);
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeCppR_GetterAndSetter(AdtFile& rFile,
                                                 const char* pClassName,
                                                 const char* pAliasName,
                                                 const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_GetterAndSetter(rFile, name().c_str(), pClassName, pAliasName, pR_TypeName, this->isScalar());
}

//  ----------------------------------------------------------------------------

AdtAutoAttribute::AdtAutoAttribute(const char* pName,
                                   const char* pClassName,
                                   AdtAtributeType nAttributeType,
                                   AdtAutoType nType,
                                   AdtAutoMode nMode,
                                   AdtAutoDir nDir,
                                   int nPhase,
                                   bool bNoInterface,
                                   bool bWithInitialisation,
                                   const char* pFileName,
                                   int nLineNumber)
 : UtlReferenceCount(),
   Name(pName),
   ClassName(pClassName),
   FileName(pFileName)
{
  AttributeType       = nAttributeType;
  Type                = nType;
  Mode                = nMode;
  Dir                 = nDir;
  Phase               = nPhase;
  NoInterface         = bNoInterface;
  WithInitialisation  = bWithInitialisation;
  LineNumber          = nLineNumber;
}

//  ----------------------------------------------------------------------------

AdtAutoAttribute::AdtAutoAttribute(const AdtAutoAttribute& rCopy)
 : UtlReferenceCount(),
   Name(rCopy.Name),
   ClassName(rCopy.ClassName),
   FileName(rCopy.FileName)
{
  AttributeType       = rCopy.AttributeType;
  Type                = rCopy.Type;
  Mode                = rCopy.Mode;
  Dir                 = rCopy.Dir;
  Phase               = rCopy.Phase;
  NoInterface         = rCopy.NoInterface;
  WithInitialisation  = rCopy.WithInitialisation;
  LineNumber          = rCopy.LineNumber;
}

//  ----------------------------------------------------------------------------

AdtAutoAttribute::~AdtAutoAttribute()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeVarCheckType(AdtFile& rFile,
                                         AdtSourceFileType nDestType,
                                         bool bPrefix,
                                         bool bInConstructor) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiVarCheckType(rFile, bPrefix, bInConstructor);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppVarCheckType(rFile, bPrefix, bInConstructor);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeVarDeclaration(AdtFile& rFile,
                                           AdtSourceFileType nDestType,
                                           bool bConstructor,
                                           bool bPrependSeperator) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiVarDeclaration(rFile, bConstructor, bPrependSeperator);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppVarDeclaration(rFile, bConstructor, bPrependSeperator);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeVarInitialisation(AdtFile& rFile,
                                              AdtSourceFileType nDestType,
                                              AdtStringByStringMap& rLocalsMap,
                                              const char* pClassName,
                                              bool bWithTranslation) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiVarInitialisation(rFile, rLocalsMap, pClassName, bWithTranslation);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppVarInitialisation(rFile, rLocalsMap, pClassName, bWithTranslation);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeVarReturn(AdtFile& rFile,
                                      AdtSourceFileType nDestType,
                                      const char* pClassName) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiVarReturn(rFile, pClassName);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppVarReturn(rFile, pClassName);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeVarDestroy(AdtFile& rFile,
                                       AdtSourceFileType nDestType) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiVarDestroy(rFile);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppVarDestroy(rFile);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDeclLibInterfaceMethods(AdtFile& rFile,
                                                    AdtSourceFileType nDestType) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiDeclLibInterfaceMethods(rFile);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppDeclLibInterfaceMethods(rFile);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeDeclLibInterfaceGlobals(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pAliasName) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiDeclLibInterfaceGlobals(rFile, pAliasName);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppDeclLibInterfaceGlobals(rFile, pAliasName);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeImplLibInterfaceMethods(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pAliasName,
                                                    const char* pR_TypeName) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiImplLibInterfaceMethods(rFile, pClassName, pAliasName, pR_TypeName);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppImplLibInterfaceMethods(rFile, pClassName, pAliasName, pR_TypeName);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoAttribute::writeImplLibInterfaceGlobals(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pAliasName,
                                                    const char* pR_TypeName) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      this->writeDelphiImplLibInterfaceGlobals(rFile, pClassName, pAliasName, pR_TypeName);
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      this->writeCppImplLibInterfaceGlobals(rFile, pClassName, pAliasName, pR_TypeName);
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}


//  ----------------------------------------------------------------------------
//  AdtAutoGlobalScalar method implementations
//  ----------------------------------------------------------------------------
void AdtAutoGlobalScalar::writeDelphiVarCheckType(AdtFile& rFile,
                                                  bool bPrefix,
                                                  bool bInConstructor) const
{
  // do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiVarDeclaration(AdtFile& rFile,
                                                    bool bConstructor,
                                                    bool bPrependSeperator) const
{
  // do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiVarInitialisation(AdtFile& rFile,
                                                       AdtStringByStringMap& rLocalsMap,
                                                       const char* pClassName,
                                                       bool bWithTranslation) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiVarReturn(AdtFile& rFile,
                                               const char* pClassName) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiVarDestroy(AdtFile& rFile) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                             const char* pClassName,
                                                             const char* pAliasName,
                                                             const char* pR_TypeName) const
{

}

//  ----------------------------------------------------------------------------

void  AdtAutoGlobalScalar::writeDelphiDeclLibInterfaceGlobals(AdtFile& rFile,
                                                              const char* pAliasName) const
{
  // Declare get global functions
  rFile.write("function ");
  rFile.write(pAliasName);
  rFile.write("_get_");
  rFile.write(name());
  rFile.write("() : SEXP; cdecl;");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                             const char* pClassName,
                                                             const char* pAliasName,
                                                             const char* pR_TypeName) const
{
  // implement get routine using .External interface
  AdtAutoHelper Helper;

  Helper.writeDelphiR_GlobalGetter(rFile, name().c_str(), pAliasName, this->type());
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppVarCheckType(AdtFile& rFile,
                                               bool bPrefix,
                                               bool bInConstructor) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppVarDeclaration(AdtFile& rFile,
                                                 bool bConstructor,
                                                 bool bPrependSeperator) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppVarInitialisation(AdtFile& rFile,
                                                    AdtStringByStringMap& rLocalsMap,
                                                    const char* pClassName,
                                                    bool bWithTranslation) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppVarReturn(AdtFile& rFile,
                                            const char* pClassName) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppVarDestroy(AdtFile& rFile) const
{

}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                          const char* pClassName,
                                                          const char* pAliasName,
                                                          const char* pR_TypeName) const
{

}

//  ----------------------------------------------------------------------------

void  AdtAutoGlobalScalar::writeCppDeclLibInterfaceGlobals(AdtFile& rFile,
                                                           const char* pAliasName) const
{
  // Declare get global functions
  rFile.write("EXPORT SEXP ");
  rFile.write(pAliasName);
  rFile.write("_get_");
  rFile.write(name());
  rFile.write("();");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                          const char* pClassName,
                                                          const char* pAliasName,
                                                          const char* pR_TypeName) const
{
  // implement get routine using .External interface
  AdtAutoHelper Helper;

  Helper.writeCppR_GlobalGetter(rFile, name().c_str(), pAliasName, this->type());
}

//  ----------------------------------------------------------------------------

AdtAutoGlobalScalar::AdtAutoGlobalScalar(const char* pName,
                                         AdtAutoType nType,
                                         const char* pFileName,
                                         int nLineNumber)
 : AdtAutoAttribute(pName,
                    "",
                    AttributeTypeGlobalScalar,
                    nType,
                    AdtAutoMode_GLOBAL,
                    AdtAutoDir_OUT,
                    0,
                    false,
                    false,
                    pFileName,
                    nLineNumber)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtAutoGlobalScalar::AdtAutoGlobalScalar(const AdtAutoGlobalScalar& rCopy)
 : AdtAutoAttribute(rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtAutoGlobalScalar::~AdtAutoGlobalScalar()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

int AdtAutoGlobalScalar::dimensions() const
{
  return (0);
}

//  ----------------------------------------------------------------------------

bool AdtAutoGlobalScalar::isScalar() const
{
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoGlobalScalar::isRagged() const
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtAutoGlobalScalar::strictlyBefore(int nPhase) const
{
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoGlobalScalar::checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                            const AdtAutoAttributePtrByStringMap* pSecondaryMap) const
{
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoGlobalScalar::checkSize(const string& rMustMatchSize) const
{
  return (true);
}

//  ----------------------------------------------------------------------------

void AdtAutoGlobalScalar::writeRInterface(AdtFile& rFile,
                                          const char* pClassName,
                                          const char* pAliasName) const
{
  AdtAutoHelper Helper;

  // Write get function
  rFile.write(pAliasName);
  rFile.write(".get.");
  rFile.write(name());
  rFile.write(" <- function()");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();
  rFile.write("return (.External('_");
  rFile.write(pAliasName);
  rFile.write(".get.");
  rFile.write(name());
  rFile.write("'))");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();
}


//  ----------------------------------------------------------------------------
//  AdtAutoScalar method implementations
//  ----------------------------------------------------------------------------
void AdtAutoScalar::writeDelphiVarCheckType(AdtFile& rFile,
                                            bool bPrefix,
                                            bool bInConstructor) const
{
  AdtAutoHelper Helper;
  string        Prefixed(name());

  if (bPrefix)
  {
    Prefixed = "arg_" + name();
  }

  Helper.writeDelphiVarCheckType(rFile,
                                 Prefixed.c_str(),
                                 type(),
                                 0,
                                 0);
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeDelphiVarDeclaration(AdtFile& rFile,
                                              bool bConstructor,
                                              bool bPrependSeperator) const
{
  const char* pType = delphiType();

  if (bPrependSeperator)
  {
    rFile.write(";");
    rFile.newline();
  }

  ASSERT(mode() == AdtAutoMode_AUTOINIT || mode() == AdtAutoMode_FN_ARGUMENT);

  // Prepend an underscore as this is an argument being passed into the
  // constructor.
  rFile.write("arg_");
  rFile.write(name());
  rFile.write(" : ");
  rFile.write(pType);
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeDelphiVarInitialisation(AdtFile& rFile,
                                                 AdtStringByStringMap& rLocalsMap,
                                                 const char* pClassName,
                                                 bool bWithTranslation) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    {
      const char* pInitialiser = 0;

      rFile.write(name());
      rFile.write(" := ");

      switch(type())
      {
        case AdtAutoType_DOUBLE:
        case AdtAutoType_FLOAT:
        {
          pInitialiser = "QNaN;";
          break;
        }

        case AdtAutoType_INT:
        case AdtAutoType_SHORT:
        case AdtAutoType_UNSIGNED_INT:
        case AdtAutoType_UNSIGNED_SHORT:
        {
          pInitialiser = "$FEFE;";
          break;
        }

        case AdtAutoType_LONG:
        case AdtAutoType_UNSIGNED_LONG:
        {
          pInitialiser = "$FEFEFEFE;";
          break;
        }

        case AdtAutoType_CHAR:
        case AdtAutoType_UNSIGNED_CHAR:
        {
          pInitialiser = "$FE;";
          break;
        }

        case AdtAutoType_LONG_LONG:
        case AdtAutoType_UNSIGNED_LONG_LONG:
        {
          pInitialiser = "$FEFEFEFEFEFEFEFE;";
          break;
        }

        case AdtAutoType_BOOL:
        {
          pInitialiser = "false;";
          break;
        }

        case AdtAutoType_LONGBOOL:
        {
          pInitialiser = "false;";
          break;
        }

        default:
        {
          FAIL();
          break;
        }
      }

      rFile.write(pInitialiser);
      rFile.newline();
      break;
    }

    case AdtAutoMode_AUTOINIT:
    {
      rFile.write(name());
      rFile.write(" := arg_");
      rFile.write(name());
      rFile.write(";");
      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write("arg_");
      rFile.write(name());
      rFile.write(" := R_");
      rFile.write(R_AccessType());
      rFile.write("(");
      rFile.write(name());
      rFile.write(")^;");
      rFile.newline();
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

void AdtAutoScalar::writeDelphiVarReturn(AdtFile& rFile,
                                         const char* pClassName) const
{
  switch(mode())
  {
    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write("R_");
      rFile.write(R_AccessType());
      rFile.write("(");
      rFile.write(name());
      rFile.write(")^ := arg_");
      rFile.write(name());
      rFile.write(";");
      rFile.newline();
      break;
    }

    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeDelphiVarDestroy(AdtFile& rFile) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    case AdtAutoMode_FN_ARGUMENT:
    {
      // Do nothing for scalars
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

void AdtAutoScalar::writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                       const char* pClassName,
                                                       const char* pAliasName,
                                                       const char* pR_TypeName) const
{
  string sSourceName("arg_");

  sSourceName += name();

  // implement get and set class methods
  rFile.newline();
  rFile.write("function ");
  rFile.write(pClassName);
  rFile.write("._get_");
  rFile.write(name());
  rFile.write("() : SEXP;");
  rFile.newline();
  rFile.newline();
  rFile.write("begin");
  rFile.incrementIndent();
  rFile.newline();
  rFile.write("Result := R_Scalar(");
  rFile.write(name());
  rFile.write(");");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("end;");
  rFile.newline();
  rFile.newline();
  rFile.write("function ");
  rFile.write(pClassName);
  rFile.write("._set_");
  rFile.write(name());
  rFile.write("(arg_");
  rFile.write(name());
  rFile.write(" : SEXP) : SEXP;");
  rFile.newline();
  rFile.newline();
  rFile.write("begin");
  rFile.incrementIndent();
  rFile.newline();
  this->writeVarCheckType(rFile, DelphiSourceFileType, true, false);
  rFile.newline();
  rFile.write(name());
  rFile.write(" := R_");
  rFile.write(R_AccessType());
  rFile.write("(");
  rFile.write(sSourceName);
  rFile.write(")^;");
  rFile.newline();
  rFile.write("Result := R_Empty();");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("end;");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                       const char* pClassName,
                                                       const char* pAliasName,
                                                       const char* pR_TypeName) const
{
  // implement get and set export routines using .External interface
  writeDelphiR_GetterAndSetter(rFile, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeCppVarCheckType(AdtFile& rFile,
                                         bool bPrefix,
                                         bool bInConstructor) const
{
  AdtAutoHelper Helper;
  string        Prefixed(name());

  if (bPrefix)
  {
    Prefixed = "arg_" + name();
  }

  Helper.writeCppVarCheckType(rFile,
                              Prefixed.c_str(),
                              type(),
                              0,
                              0);
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeCppVarDeclaration(AdtFile& rFile,
                                           bool bConstructor,
                                           bool bPrependSeperator) const
{
  const char* pType = cppType();

  if (bPrependSeperator)
  {
    rFile.write(",");
    rFile.newline();
  }

  rFile.write(pType);

  ASSERT(mode() == AdtAutoMode_AUTOINIT || mode() == AdtAutoMode_FN_ARGUMENT);

  // Prepend an underscore as this is an argument being passed into the
  // constructor.
  rFile.write(" arg_");
  rFile.write(name());
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeCppVarInitialisation(AdtFile& rFile,
                                              AdtStringByStringMap& rLocalsMap,
                                              const char* pClassName,
                                              bool bWithTranslation) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    {
      const char* pInitialiser = 0;

      rFile.write(name());
      rFile.write(" = ");

      switch(type())
      {
        case AdtAutoType_DOUBLE:
        case AdtAutoType_FLOAT:
        {
          pInitialiser = "QNaN;";
          break;
        }

        case AdtAutoType_SHORT:
        case AdtAutoType_UNSIGNED_SHORT:
        {
          pInitialiser = "0xFEFE;";
          break;
        }

        case AdtAutoType_INT:
        case AdtAutoType_LONG:
        case AdtAutoType_UNSIGNED_INT:
        case AdtAutoType_UNSIGNED_LONG:
        {
          pInitialiser = "0xFEFEFEFE;";
          break;
        }

        case AdtAutoType_CHAR:
        case AdtAutoType_UNSIGNED_CHAR:
        {
          pInitialiser = "0xFE;";
          break;
        }

        case AdtAutoType_LONG_LONG:
        case AdtAutoType_UNSIGNED_LONG_LONG:
        {
          pInitialiser = "0xFEFEFEFEFEFEFEFE;";
          break;
        }

        case AdtAutoType_BOOL:
        {
          pInitialiser = "false;";
          break;
        }

        case AdtAutoType_LONGBOOL:
        {
          pInitialiser = "false;";
          break;
        }

        default:
        {
          FAIL();
          break;
        }
      }

      rFile.write(pInitialiser);
      rFile.newline();
      break;
    }

    case AdtAutoMode_AUTOINIT:
    {
      rFile.write(name());
      rFile.write(" = arg_");
      rFile.write(name());
      rFile.write(";");
      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write("arg_");
      rFile.write(name());
      rFile.write(" = ");
      rFile.write(R_AccessType());
      rFile.write("(");
      rFile.write(name());
      rFile.write(")[0];");
      rFile.newline();
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

void AdtAutoScalar::writeCppVarReturn(AdtFile& rFile,
                                      const char* pClassName) const
{
  switch(mode())
  {
    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write(R_AccessType());
      rFile.write("(");
      rFile.write(name());
      rFile.write(")[0] = arg_");
      rFile.write(name());
      rFile.write(";");
      rFile.newline();
      break;
    }

    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeCppVarDestroy(AdtFile& rFile) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    case AdtAutoMode_FN_ARGUMENT:
    {
      // Do nothing for scalars
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

void AdtAutoScalar::writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                    const char* pClassName,
                                                    const char* pAliasName,
                                                    const char* pR_TypeName) const
{
  string sSourceName("arg_");

  sSourceName += name();

  // implement get and set class methods
  rFile.newline();
  rFile.write("SEXP ");
  rFile.write(pClassName);
  rFile.write("::_get_");
  rFile.write(name());
  rFile.write("() const");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();
  rFile.write("return (R_Scalar(");
  rFile.write(name());
  rFile.write("));");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();
  rFile.write("SEXP ");
  rFile.write(pClassName);
  rFile.write("::_set_");
  rFile.write(name());
  rFile.write("(SEXP arg_");
  rFile.write(name());
  rFile.write(")");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();
  this->writeVarCheckType(rFile, CppSourceFileType, true, false);
  rFile.newline();
  rFile.write(name());
  rFile.write(" = ");
  rFile.write(R_AccessType());
  rFile.write("(");
  rFile.write(sSourceName);
  rFile.write(")[0];");
  rFile.newline();
  rFile.newline();
  rFile.write("return (R_Empty());");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                    const char* pClassName,
                                                    const char* pAliasName,
                                                    const char* pR_TypeName) const
{
  // implement get and set export routines using .External interface
  writeCppR_GetterAndSetter(rFile, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

AdtAutoScalar::AdtAutoScalar(const char* pName,
                             const char* pClassName,
                             AdtAutoType nType,
                             AdtAutoMode nMode,
                             AdtAutoDir nDir,
                             int nPhase,
                             bool bNoInterface,
                             bool bWithInitialisation,
                             const char* pFileName,
                             int nLineNumber)
 : AdtAutoAttribute(pName,
                    pClassName,
                    AttributeTypeScalar,
                    nType,
                    nMode,
                    nDir,
                    nPhase,
                    bNoInterface,
                    bWithInitialisation,
                    pFileName,
                    nLineNumber)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtAutoScalar::AdtAutoScalar(const AdtAutoScalar& rCopy)
 : AdtAutoAttribute(rCopy)
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

AdtAutoScalar::~AdtAutoScalar()
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

int AdtAutoScalar::dimensions() const
{
  return (0);
}

//  ----------------------------------------------------------------------------

bool AdtAutoScalar::isScalar() const
{
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoScalar::isRagged() const
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtAutoScalar::strictlyBefore(int nPhase) const
{
  // Scalars are initialised strictly before arrays so the phase can be less
  // than or equal to nPhase.
  bool bBefore = (phase() <= nPhase);

  return (bBefore);
}

//  ----------------------------------------------------------------------------

bool AdtAutoScalar::checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                      const AdtAutoAttributePtrByStringMap* pSecondaryMap) const
{
  // Scalars don't have order initialisation dependencies
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoScalar::checkSize(const string& rMustMatchSize) const
{
  // Scalars don't come into size checks
  return (true);
}

//  ----------------------------------------------------------------------------

void AdtAutoScalar::writeRInterface(AdtFile& rFile,
                                    const char* pClassName,
                                    const char* pAliasName) const
{
  AdtAutoHelper Helper;

  // Write get function
  rFile.write(pAliasName);
  rFile.write(".get.");
  rFile.write(name());
  rFile.write(" <- function(Context)");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();
  rFile.write("return (.External('_");
  rFile.write(pAliasName);
  rFile.write(".get.");
  rFile.write(name());
  rFile.write("', Context))");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();

  // Write set function
  rFile.write(pAliasName);
  rFile.write(".set.");
  rFile.write(name());
  rFile.write(" <- function(Context, Arg)");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();
  rFile.write("return (.External('_");
  rFile.write(pAliasName);
  rFile.write(".set.");
  rFile.write(name());
  rFile.write("', Context, ");
  Helper.writeR_typeCast(rFile, type(), "Arg", name());
  rFile.write("))");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();
}


//  ----------------------------------------------------------------------------
//  AdtAutoArrayPlanInfo method implementations
//  ----------------------------------------------------------------------------
AdtAutoArrayPlanInfo::AdtAutoArrayPlanInfo()
 : Plan(),
   Key()
{
  Array       = 0;
  Initialised = false;
}

//  ----------------------------------------------------------------------------

AdtAutoArrayPlanInfo::AdtAutoArrayPlanInfo(const AdtAutoArray* pArray,
                                           const char* pPlan,
                                           bool bInitialised)
 : Plan(pPlan),
   Key()
{
  Array       = pArray;
  Initialised = bInitialised;

  if (Array != 0)
  {
    Array->lock();
    Key = Array->sizeSpecification();
  }
}

//  ----------------------------------------------------------------------------

AdtAutoArrayPlanInfo::AdtAutoArrayPlanInfo(const AdtAutoArrayPlanInfo& rCopy)
: Plan(rCopy.Plan),
  Key(rCopy.Key)
{
  Array       = rCopy.Array;
  Initialised = rCopy.Initialised;

  if (Array != 0)
  {
    Array->lock();
  }
}

//  ----------------------------------------------------------------------------

AdtAutoArrayPlanInfo::~AdtAutoArrayPlanInfo()
{
  UtlReleaseReference(Array);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArrayPlanInfo::inClass(const char* pClassName) const
{
  bool bInClass = true;

  if (Array != 0)
  {
    bInClass = Array->className() == pClassName;
  }

  return (bInClass);
}

//  ----------------------------------------------------------------------------

AdtAutoArrayPlanInfo& AdtAutoArrayPlanInfo::operator = (const AdtAutoArrayPlanInfo& rCopy)
{
  Plan        = rCopy.Plan;
  Key         = rCopy.Key;
  Array       = rCopy.Array;
  Initialised = rCopy.Initialised;

  if (Array != 0)
  {
    Array->lock();
  }

  return (*this);
}


//  ----------------------------------------------------------------------------
//  AdtAutoArray method implementations
//  ----------------------------------------------------------------------------
AdtAutoArrayPlanInfoByStringMap AdtAutoArray::ArrayPlanInfoMap;
int                             AdtAutoArray::ArrayPlanCount = 1;
const int                       AdtAutoArray::NO_INDEX       = 0xFFFF;

//  ----------------------------------------------------------------------------

bool AdtAutoArray::getPlan(bool bCreate,
                           string& rPlanName) const
{

  bool bFound = false;

  // Variables with local dependencies (function arguments with dimension vars
  // in the argument list) cannot be created via class defined plans as the
  // dimension variable is not supplied in the constructor.
  if (!HasLocalDependencies)
  {
    string                              sKey(SizeSpecification);
    AdtAutoArrayPlanInfoByStringMapIter Iter;

    Iter = ArrayPlanInfoMap.find(sKey);

    if (Iter == ArrayPlanInfoMap.end())
    {
      char  sBuffer[16] = {0};

      ::sprintf(sBuffer, "Plan_%d", ArrayPlanCount);

      rPlanName = sBuffer;

      AdtAutoArrayPlanInfo  Info(this, rPlanName, bCreate);

      ArrayPlanInfoMap[sKey] = Info;

      ArrayPlanCount++;
    }
    else
    {
      rPlanName = Iter->second.plan();
      bFound    = true;
    }
  }

  return (bFound);
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::updateMustMatchSize(string& rMustMatchSize,
                                       const string& rLastLowerBoundExpression,
                                       const string& rLastUpperBoundExpression) const
{
  if (rMustMatchSize.length() != 0)
  {
    rMustMatchSize += ",";
  }

  if (rLastLowerBoundExpression.length() != 0)
  {
    rMustMatchSize += rLastLowerBoundExpression + ":";
  }

  rMustMatchSize += rLastUpperBoundExpression;
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::checkDependencies(bool& bOk,
                                     AdtStringList& rDependencyList,
                                     const AdtStringByIntMap& rLowerBoundMap,
                                     const AdtStringByIntMap& rUpperBoundMap,
                                     const AdtAutoAttributePtrByStringMap& rMap,
                                     const AdtAutoAttributePtrByStringMap* pSecondaryMap,
                                     const AdtExpressionAdditive* pRootLower,
                                     const AdtExpressionAdditive* pRootUpper,
                                     int nIndex,
                                     int& nLastScalar,
                                     int& nSmallestIndex) const
{
  string  rDummyMatchSize;

  // Do a dummy check size to ensure that the size spec string is initialise for
  // all arrays. We do this because we use the size spec string to manage the
  // creation and initialisation of AdtArrayPlans in automation code.
  checkSize(rDummyMatchSize);

  AdtStringListIter Iter;

  for (Iter = rDependencyList.begin() ; Iter != rDependencyList.end() ; ++Iter)
  {
    const string& rDependency                     = *Iter;
    bool                                  bAgain  = false;
    const AdtAutoAttributePtrByStringMap* pMap    = &rMap;

    do
    {
      AdtAutoAttributePtrByStringMapConstIter FindIter = pMap->find(rDependency);

      if (FindIter != pMap->end())
      {
        const AdtAutoAttribute* pObj  = (*FindIter).second;

        if (pObj->dimensions() > 0)
        {
          string  sDimension;

          if (nIndex == 0)
          {
            // Error : dependency not a scalar expression
            ::printf("ERROR:Dependency %s of array %s is a vector but the first array dimension can only have scalar dependencies.\n See line %d in file %s\n See line %d in file %s\n",
                     rDependency.c_str(),
                     name().c_str(),
                     lineNumber(),
                     fileName().c_str(),
                     pObj->lineNumber(),
                     pObj->fileName().c_str());

            bOk = false;
          }

          if (nLastScalar < 0)
          {
            nLastScalar = nIndex - 1;
          }

          if (pRootLower->buildArrayDimension(rDependency,
                                              rLowerBoundMap,
                                              rUpperBoundMap,
                                              nIndex,
                                              nSmallestIndex,
                                              sDimension) && !pObj->checkSize(sDimension))
          {
            // Error : dependency size is incorrect
            ::printf("ERROR:Dependency %s of array %s should have a size specification of {%s}.\n See line %d in file %s\n See line %d in file %s\n",
                     rDependency.c_str(),
                     name().c_str(),
                     sDimension.c_str(),
                     lineNumber(),
                     fileName().c_str(),
                     pObj->lineNumber(),
                     pObj->fileName().c_str());

            bOk = false;
          }

          if (pRootUpper->buildArrayDimension(rDependency,
                                              rLowerBoundMap,
                                              rUpperBoundMap,
                                              nIndex,
                                              nSmallestIndex,
                                              sDimension) && !pObj->checkSize(sDimension))
          {
            // Error : dependency size is incorrect
            ::printf("ERROR:Dependency %s of array %s should have a size specification of {%s}.\n See line %d in file %s\n See line %d in file %s\n",
                     rDependency.c_str(),
                     name().c_str(),
                     sDimension.c_str(),
                     lineNumber(),
                     fileName().c_str(),
                     pObj->lineNumber(),
                     pObj->fileName().c_str());

            bOk = false;
          }

          ArrayDependencies[pObj->name()] = pObj->dimensions();
        }

        // Only do this part if using primary map. The secondary map means we are
        // using dimensions specified in the call which corresponds to arrays not
        // necessarily instantiated by our code so the strictlyBefore() check is
        // irrelevent in this case.
        if (!bAgain && !pObj->strictlyBefore(phase()))
        {
          // Error : dependency not initialised before this
          ::printf("ERROR:Dependency %s of array %s is not initialised before array %s.\n See line %d in file %s\n See line %d in file %s\n",
                   rDependency.c_str(),
                   name().c_str(),
                   name().c_str(),
                   lineNumber(),
                   fileName().c_str(),
                   pObj->lineNumber(),
                   pObj->fileName().c_str());

          bOk = false;
        }

        if (bAgain)
        {
          // Add dependency to local dependency map. We use the integer value
          // stored under the key of the dependency name to signify if it is
          // a global constant or not. If 0 then it is a argument list local
          // and if 1 it is a global. When 1 we do not want to assume it is
          // an SEXP.
          int nType = (pObj->attributeType() == AttributeTypeGlobalScalar) ? 1 : 0;

          ArrayDependancyLocal[rDependency] = nType;
          HasLocalDependencies              = HasLocalDependencies  || (nType == 0);
          HasGlobalDependencies             = HasGlobalDependencies || (nType == 1);
        }

        bAgain = false;
      }
      else
      {
        if (!bAgain && (pSecondaryMap != 0))
        {
          pMap    = pSecondaryMap;
          bAgain  = true;
        }
        else
        {
          // Error : dependency not defined
          ::printf("ERROR:Dependency %s of array %s is undefined.\n See line %d in file %s\n",
                   rDependency.c_str(),
                   name().c_str(),
                   lineNumber(),
                   fileName().c_str());

          bOk     = false;
          bAgain  = false;
        }
      }
    } while (bAgain);
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::arrayBoundsArguments(string& rArguments,
                                        bool bInConstructor,
                                        bool bR_Prefix) const
{
  for (int cn = 0 ; cn < dimensions() ; cn++)
  {
    AdtStringByIntMapConstIter  Iter;

    if (cn != 0)
    {
      rArguments += ", ";
    }

    Iter = ArrayLowerBoundByIndex.find(cn);

    if (Iter != ArrayLowerBoundByIndex.end())
    {
      string                sIndexExpression = (*Iter).second;
      AdtExpressionCompiler Compiler;

      Compiler.reconstructWithPossibleSEXPArgs(sIndexExpression,
                                               sIndexExpression,
                                               ArrayDependancyLocal,
                                               bInConstructor,
                                               bR_Prefix);

      rArguments += sIndexExpression + ", ";
    }
    else
    {
      rArguments += "1, ";
    }

    Iter = ArrayUpperBoundByIndex.find(cn);

    if (Iter != ArrayUpperBoundByIndex.end())
    {
      string                sIndexExpression = (*Iter).second;
      AdtExpressionCompiler Compiler;

      Compiler.reconstructWithPossibleSEXPArgs(sIndexExpression,
                                               sIndexExpression,
                                               ArrayDependancyLocal,
                                               bInConstructor,
                                               bR_Prefix);

      rArguments += sIndexExpression;
    }
    else
    {
      FAIL();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::arraySizesAndBaseIndices(string& rArraySizes,
                                            string& rBaseIndices) const
{
  rArraySizes   = "";
  rBaseIndices  = "";

  for (int cn = 0 ; cn < dimensions() ; cn++)
  {
    AdtStringByIntMapConstIter  Iter;
    string                      sLastLowerBoundExpression;
    string                      sLastUpperBoundExpression;

    if (cn != 0)
    {
      rArraySizes   += ",";
      rBaseIndices  += ",";
    }

    Iter = ArrayUpperBoundByIndex.find(cn);

    if (Iter != ArrayUpperBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      rArraySizes   += rIndexExpression + "+1-";
    }
    else
    {
      FAIL();
    }

    Iter = ArrayLowerBoundByIndex.find(cn);

    if (Iter != ArrayLowerBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      rArraySizes   += "(" + rIndexExpression + ")";
      rBaseIndices  += rIndexExpression;
    }
    else
    {
      rBaseIndices  += "1";
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiAllocSizeSpec(AdtFile& rFile,
                                            int nStartIndex,
                                            int nEndIndex) const
{
  string  sSizes;
  string  sBases;

  for (int cn = nStartIndex ; cn < nEndIndex ; cn++)
  {
    AdtStringByIntMapConstIter  Iter;
    string                      sLastLowerBoundExpression;
    string                      sLastUpperBoundExpression;

    if (cn != nStartIndex)
    {
      sSizes += ",";
      sBases += ",";
    }

    Iter = ArrayUpperBoundByIndex.find(cn);

    if (Iter != ArrayUpperBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      sSizes += rIndexExpression + "+1";
    }
    else
    {
      FAIL();
    }

    Iter = ArrayLowerBoundByIndex.find(cn);

    if (Iter != ArrayLowerBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      sBases += rIndexExpression;
      sSizes += "-(" + rIndexExpression + ")";
    }
    else
    {
      sBases += "1";
      sSizes += "-1";
    }
  }

  rFile.write("[");
  rFile.write(sSizes);
  rFile.write("],[");
  rFile.write(sBases);
  rFile.write("]");
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::write_ZERO(AdtFile& rFile) const
{
  rFile.write("zero(");
  rFile.write(name());
  rFile.write(");");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writePlanBasesAndSizes(AdtFile& rFile,
                                          int nStartIndex,
                                          int nEndIndex) const
{
  for (int cn = nStartIndex ; cn < nEndIndex ; cn++)
  {
    AdtStringByIntMapConstIter  Iter;
    string                      sSize;
    string                      sBase;

    Iter = ArrayUpperBoundByIndex.find(cn);

    if (Iter != ArrayUpperBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      sSize += rIndexExpression + "+1";
    }
    else
    {
      FAIL();
    }

    Iter = ArrayLowerBoundByIndex.find(cn);

    if (Iter != ArrayLowerBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      sBase += rIndexExpression;
      sSize += "-(" + rIndexExpression + ")";
    }
    else
    {
      sBase += "1";
      sSize += "-1";
    }

    if (cn != nStartIndex)
    {
      rFile.write(",");
    }

    rFile.write(sBase);
    rFile.write(",");
    rFile.write(sSize);
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeBuildRaggedArrayPlan(AdtFile& rFile,
                                             AdtSourceFileType nDestType,
                                             AdtStringByStringMap& rLocalsMap,
                                             int nIndex,
                                             string& sLoopIndexing,
                                             string& sLastPlan,
                                             const char* pRaggedContext) const
{
  if (nIndex + 1 < dimensions())
  {
    AdtStringByIntMapConstIter  Iter;
    AdtExpressionCompiler       Compiler;
    string                      sLowerBoundExpression[2];
    string                      sUpperBoundExpression[2];
    string                      sLoopIndex;
    string                      sLastLoopIndexing(sLoopIndexing);
    char                        sBuffer[256]    = {0};
    const char*                 sCounterBase    = "__c";
    int                         nCounterIndex   = nIndex - SmallestIndex;

    ::sprintf(sBuffer, "__c%d", nCounterIndex);

    sLoopIndex     = sBuffer;
    sLoopIndexing += "[" + sLoopIndex + "]";

    string  sLoopIndexDecl;

    switch(nDestType)
    {
      case DelphiSourceFileType:
      {
        sLoopIndexDecl += sLoopIndex + " : longint;";
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        sLoopIndexDecl += "int " + sLoopIndex + ";";
        break;
      }

      case UnknownSourceFileType:
      case JavaSourceFileType:
      case FortranSourceFileType:
      default:
      {
        FAIL();
        break;
      }
    }

    bool bNewIndex = AdtAutoAttribute::addMapEntry(rLocalsMap, sLoopIndex, sLoopIndexDecl);

    for (int cn = 0 ; cn < 2 ; cn++)
    {
      const string& rLoopIndexing = (cn == 0) ? sLastLoopIndexing : sLoopIndexing;

      Iter = ArrayUpperBoundByIndex.find(nIndex + cn);

      if (Iter != ArrayUpperBoundByIndex.end())
      {
        const string& rIndexExpression = (*Iter).second;

        Compiler.reconstructWithIndexing(rIndexExpression,
                                         sCounterBase,
                                         nCounterIndex + LastScalar,
                                         sUpperBoundExpression[cn]);
      }
      else
      {
        FAIL();
      }

      Iter = ArrayLowerBoundByIndex.find(nIndex + cn);

      if (Iter != ArrayLowerBoundByIndex.end())
      {
        const string& rIndexExpression = (*Iter).second;

        Compiler.reconstructWithIndexing(rIndexExpression,
                                         sCounterBase,
                                         nCounterIndex + LastScalar,
                                         sLowerBoundExpression[cn]);
      }
      else
      {
        sLowerBoundExpression[cn] = "1";
      }
    }

    switch(nDestType)
    {
      case DelphiSourceFileType:
      {
        ::sprintf(sBuffer,
                  "for __c%d := %s to %s do",
                  nCounterIndex,
                  sLowerBoundExpression[0].c_str(),
                  sUpperBoundExpression[0].c_str());

        rFile.newline();
        rFile.write(sBuffer);
        rFile.newline();
        rFile.write("begin");
        rFile.incrementIndent();
        rFile.newline();

        ::sprintf(sBuffer,
                  "Plan_c%d",
                  nCounterIndex);

        string  sPlan(sBuffer);
        string  sContext(sBuffer);

        sContext += "_context";

        string  sContextDecl(sContext);

        sContextDecl += " : RAGGED_CONTEXT;";

        AdtAutoAttribute::addMapEntry(rLocalsMap, sContext, sContextDecl);

        string  sPlanDecl(sPlan);

        sPlanDecl += " : AdtArrayPlan;";

        AdtAutoAttribute::addMapEntry(rLocalsMap, sPlan, sPlanDecl);

        rFile.write(sPlan);

        if (nIndex + 2 == dimensions())
        {
          rFile.write(" := AdtArrayPlan.create(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write(",");
          rFile.write(sUpperBoundExpression[1]);
          rFile.write(" + 1 -(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write("));");
          rFile.newline();
        }
        else
        {
          rFile.write(" := AdtArrayPlan.create();");
          rFile.newline();
          rFile.write(sContext);
          rFile.write(" := nil;");
          rFile.newline();
          rFile.newline();

          rFile.write(sPlan);
          rFile.write(".beginRagged(");
          rFile.write(sContext);
          rFile.write(",");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write(",");
          rFile.write(sUpperBoundExpression[1]);
          rFile.write(" + 1 -(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write("));");
          rFile.newline();

          writeBuildRaggedArrayPlan(rFile,
                                    nDestType,
                                    rLocalsMap,
                                    nIndex + 1,
                                    sLoopIndexing,
                                    sPlan);

          rFile.newline();
          rFile.write(sBuffer);
          rFile.write(".endRagged();");
        }

        if (sLastPlan.length() > 0)
        {
          ::sprintf(sBuffer,
                    ", __c%d);",
                    nCounterIndex);

          rFile.newline();
          rFile.write(sLastPlan);
          rFile.write(".addArrayPlan(");

          if (pRaggedContext != 0)
          {
            rFile.write(pRaggedContext);
            rFile.write(", ");
          }

          rFile.write(sPlan);
          rFile.write(sBuffer);
        }

        rFile.newline();
        rFile.newline();
        rFile.write(sPlan);
        rFile.write(".destroy();");
        rFile.decrementIndent();
        rFile.newline();
        rFile.write("end;");
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        ::sprintf(sBuffer,
                  bNewIndex ? "for (int __c%d = %s ; __c%d <= %s ; __c%d++)"
                            : "for (__c%d = %s ; __c%d <= %s ; __c%d++)",
                  nCounterIndex,
                  sLowerBoundExpression[0].c_str(),
                  nCounterIndex,
                  sUpperBoundExpression[0].c_str(),
                  nCounterIndex);

        rFile.newline();
        rFile.write(sBuffer);
        rFile.newline();
        rFile.write("{");
        rFile.incrementIndent();
        rFile.newline();

        ::sprintf(sBuffer,
                  "Plan_c%d",
                  nCounterIndex);

        string  sPlan(sBuffer);
        string  sContext(sBuffer);

        sContext += "_context";

        rFile.write("AdtArrayPlan ");
        rFile.write(sPlan);

        if (nIndex + 2 == dimensions())
        {
          rFile.write("(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write(",");
          rFile.write(sUpperBoundExpression[1]);
          rFile.write(" + 1 -(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write("));");
          rFile.newline();
        }
        else
        {
          rFile.write(";");
          rFile.newline();
          rFile.newline();
          rFile.write("RAGGED_CONTEXT ");
          rFile.write(sContext);
          rFile.write(" = 0;");
          rFile.newline();
          rFile.newline();

          rFile.write(sPlan);
          rFile.write(".beginRagged(");
          rFile.write(sContext);
          rFile.write(",");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write(",");
          rFile.write(sUpperBoundExpression[1]);
          rFile.write(" + 1 -(");
          rFile.write(sLowerBoundExpression[1]);
          rFile.write("));");
          rFile.newline();

          writeBuildRaggedArrayPlan(rFile,
                                    nDestType,
                                    rLocalsMap,
                                    nIndex + 1,
                                    sLoopIndexing,
                                    sPlan);

          rFile.newline();
          rFile.write(sBuffer);
          rFile.write(".endRagged();");
        }

        if (sLastPlan.length() > 0)
        {
          ::sprintf(sBuffer,
                    ", __c%d);",
                    nCounterIndex);

          rFile.newline();
          rFile.write(sLastPlan.c_str());
          rFile.write(".addArrayPlan(");

          if (pRaggedContext != 0)
          {
            rFile.write(pRaggedContext);
            rFile.write(", ");
          }

          rFile.write(sPlan.c_str());
          rFile.write(sBuffer);
        }

        rFile.decrementIndent();
        rFile.newline();
        rFile.write("}");
        break;
      }

      case UnknownSourceFileType:
      case JavaSourceFileType:
      case FortranSourceFileType:
      default:
      {
        FAIL();
        break;
      }
    }
  }

  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const
{
  AdtAutoHelper Helper;
  string        sArguments;
  string        Prefixed(name());

  if (bPrefix)
  {
    Prefixed = "arg_" + name();
  }

  arrayBoundsArguments(sArguments, bInConstructor, true);

  Helper.writeDelphiVarCheckType(rFile,
                                 Prefixed.c_str(),
                                 type(),
                                 dimensions(),
                                 sArguments.c_str());
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const
{
  // Note that for constructors the arguments are always passed in as 1D arrays
  const char* pType = bConstructor ? delphiConstructorType()
                                   : delphiType(dimensions());

  if (bPrependSeperator)
  {
    rFile.write(";");
    rFile.newline();
  }

  ASSERT(mode() == AdtAutoMode_AUTOINIT || mode() == AdtAutoMode_FN_ARGUMENT);

  // Prepend an underscore as this is an argument being passed into the
  // constructor.
  if (bConstructor)
  {
    rFile.write("const ");
  }

  rFile.write("arg_");
  rFile.write(name());
  rFile.write(" : ");
  rFile.write(pType);
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    {
      rFile.write(name());
      rFile.write(" := nil;");
      rFile.newline();
      break;
    }

    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      string  sPlan;
      bool    bFound = getPlan(true, sPlan);

      if (!bFound)
      {
        writeDelphiCreatePlan(rFile, rLocalsMap, sPlan);
      }

      // Non trivial. We need to query the lower and upper bound expressions
      // for this array and use them to create and initialise the array. However,
      // to complicate issues, the array bounds can be specified using 1d integer
      // arrays specifying dimensions. These need to be created as ragged arrays
      // and require some trickery to determine the element count for use in
      // calls to zero.
      if (IsRagged)
      {
        string  sLoopIndexing;
        string  sContext(name());

        sContext += "_context";

        string  sContextDecl(sContext);

        sContextDecl += " : RAGGED_CONTEXT;";

        AdtAutoAttribute::addMapEntry(rLocalsMap, sContext, sContextDecl);

        rFile.write(sPlan);
        rFile.write(".create(_MemAllocator, ");
        rFile.write(name());
        rFile.write(");");
        rFile.newline();

        // Ragged array initialisation. As R does not support ragged arrays in
        // any form we cannot easily support automatic initialisation using
        // the AUTOINIT mode (ie. can't simply use XCOPY) so we may well not
        // support this automatically. We could support automatic initialisation
        // from a flat structure of the same size but this would mean that R
        // users need to handle the mapping from flat to ragged array structure.
        // That could be complicated and error prone.
        rFile.newline();
        write_ZERO(rFile);
      }
      else
      {
        rFile.write(sPlan);
        rFile.write(".create(_MemAllocator, ");
        rFile.write(name());
        rFile.write(");");
        rFile.newline();
        rFile.newline();

        if (mode() == AdtAutoMode_AUTOINIT)
        {
          rFile.write("AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(arg_");
          rFile.write(name());
          rFile.write("), pchar(");
          rFile.write(name());
          rFile.write("));");
          rFile.newline();
        }
        else
        {
          // ZERO array
          write_ZERO(rFile);
        }
      }

      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      string  sPlan;
      bool    bFound = getPlan(false, sPlan);

      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else
      {
        rFile.write("arg_");
        rFile.write(name());
        rFile.write(" := nil;");
        rFile.newline();
        rFile.newline();

        if (HasLocalDependencies || HasGlobalDependencies)
        {
          string  sArrayBounds;

          arrayBoundsArguments(sArrayBounds, false, true);

          rFile.write("AdtArrayPlan_create(MemAllocator, ");
          rFile.write("arg_");
          rFile.write(name());
          rFile.write(", ");
          rFile.write(sArrayBounds);
        }
        else
        {
          rFile.write(sPlan);
          rFile.write(".create(_MemAllocator, ");
          rFile.write("arg_");
          rFile.write(name());
        }

        if (bWithTranslation)
        {
          rFile.write(");");
          rFile.newline();
          rFile.newline();
          rFile.write("AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(R_");
          rFile.write(R_AccessType());
          rFile.write("(");
          rFile.write(name());
          rFile.write(")), pchar(arg_");
          rFile.write(name());
          rFile.write("));");
        }
        else
        {
          rFile.write(", pointer(R_");
          rFile.write(R_AccessType());
          rFile.write("(");
          rFile.write(name());
          rFile.write(")));");
        }

        rFile.newline();
        rFile.newline();
      }
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

void AdtAutoArray::writeDelphiCreatePlan(AdtFile& rFile,
                                         AdtStringByStringMap& rLocalsMap,
                                         const char* pPlan) const
{
  string  sPlan(pPlan);

  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    {
      break;
    }

    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      // Non trivial. We need to query the lower and upper bound expressions
      // for this array and use them to create and initialise the array. However,
      // to complicate issues, the array bounds can be specified using 1d integer
      // arrays specifying dimensions. These need to be created as ragged arrays
      // and require some trickery to determine the element count for use in
      // calls to zero.
      if (IsRagged)
      {
        string  sLoopIndexing;
        string  sContext(name());

        rFile.write(sPlan);
        rFile.write(" := AdtArrayPlan.create();");
        rFile.newline();

        sContext += "_context";

        string  sContextDecl(sContext);

        sContextDecl += " : RAGGED_CONTEXT;";

        AdtAutoAttribute::addMapEntry(rLocalsMap, sContext, sContextDecl);

        ASSERT(SmallestIndex != NO_INDEX);

        if (SmallestIndex - 1 >= 0)
        {
          rFile.write(sPlan);
          rFile.write(".initialise(");
          writePlanBasesAndSizes(rFile, SmallestIndex - 1, SmallestIndex);
          rFile.write(");");
          rFile.newline();
        }

        rFile.newline();
        rFile.write(sContext);
        rFile.write(" := nil;");
        rFile.newline();
        rFile.newline();
        rFile.write(sPlan);
        rFile.write(".beginRagged(");
        rFile.write(sContext);
        rFile.write(", ");
        writePlanBasesAndSizes(rFile, SmallestIndex, SmallestIndex + 1);
        rFile.write(");");
        rFile.newline();

        writeBuildRaggedArrayPlan(rFile,
                                  DelphiSourceFileType,
                                  rLocalsMap,
                                  SmallestIndex,
                                  sLoopIndexing,
                                  sPlan,
                                  sContext.c_str());

        rFile.newline();
        rFile.write(sPlan);
        rFile.write(".endRagged(");
        rFile.write(sContext);
        rFile.write(");");
        rFile.newline();
      }
      else
      {
        rFile.write(sPlan);
        rFile.write(" := AdtArrayPlan.create(");
        writePlanBasesAndSizes(rFile, 0, Dimensions);
        rFile.write(");");
        rFile.newline();
      }

      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else if (!(HasLocalDependencies || HasGlobalDependencies))
      {
        rFile.write(sPlan);
        rFile.write(" := AdtArrayPlan.create(");
        writePlanBasesAndSizes(rFile, 0, Dimensions);
        rFile.write(");");
        rFile.newline();
      }
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

void AdtAutoArray::writeDelphiCopyPlan(AdtFile& rFile,
                                       const char* pPlan) const
{
  string  sPlan(pPlan);

  rFile.write(sPlan);
  rFile.write(" := AdtArrayPlan.create(rCopy.");
  rFile.write(sPlan);
  rFile.write(");");
  rFile.newline();
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiVarReturn(AdtFile& rFile,
                                        const char* pClassName) const
{
  switch(mode())
  {
    case AdtAutoMode_FN_ARGUMENT:
    {
      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else
      {
        rFile.write("AdtArrayPlanActor_ADlib_to_R(_MemAllocator, pchar(arg_");
        rFile.write(name());
        rFile.write("), pchar(R_");
        rFile.write(R_AccessType());
        rFile.write("(");
        rFile.write(name());
        rFile.write(")));");
        rFile.newline();
      }
      break;
    }

    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiVarDestroy(AdtFile& rFile) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write("AdtArrayPlan_destroy(_MemAllocator, arg_");
      rFile.write(name());
      rFile.write(");");
      rFile.newline();
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

void AdtAutoArray::writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  if (!IsRagged)
  {
    string sSourceName("arg_");

    sSourceName += name();

    const char* sTypeC[2] = {"", "nt_"};
    const char* sBool[2]  = {"false", "true"};

    for (int cn = 0 ; cn < 2 ; cn++)
    {
      // Implement getter method
      rFile.newline();
      rFile.write("function ");
      rFile.write(pClassName);
      rFile.write("._get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(sArgList : SEXP) : SEXP;");
      rFile.newline();
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("Result := R_ImplGetter(_MemAllocator, ");
      rFile.write(sBool[cn]);
      rFile.write(", pchar(");
      rFile.write(name());
      rFile.write("), '");
      rFile.write(name());
      rFile.write("', sArgList, {$I %FILE%}, {$I %LINE%});");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();
      rFile.newline();

      // Implement setter method
      rFile.write("function ");
      rFile.write(pClassName);
      rFile.write("._set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(arg_");
      rFile.write(name());
      rFile.write(" : SEXP; sArgList : SEXP) : SEXP;");
      rFile.newline();
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("Result := R_ImplSetter(_MemAllocator, ");
      rFile.write(sBool[cn]);
      rFile.write(", pchar(");
      rFile.write(name());
      rFile.write("), '");
      rFile.write(name());
      rFile.write("', arg_");
      rFile.write(name());
      rFile.write(", sArgList, {$I %FILE%}, {$I %LINE%});");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  if (!IsRagged)
  {
    // implement get and set export routines using .External interface
    writeDelphiR_GetterAndSetter(rFile, pClassName, pAliasName, pR_TypeName);
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppVarCheckType(AdtFile& rFile,
                                        bool bPrefix,
                                        bool bInConstructor) const
{
  AdtAutoHelper Helper;
  string        sArguments;
  string        Prefixed(name());

  if (bPrefix)
  {
    Prefixed = "arg_" + name();
  }

  arrayBoundsArguments(sArguments, bInConstructor, false);

  Helper.writeCppVarCheckType(rFile,
                              Prefixed.c_str(),
                              type(),
                              dimensions(),
                              sArguments.c_str());
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppVarDeclaration(AdtFile& rFile,
                                          bool bConstructor,
                                          bool bPrependSeperator) const
{
  // Note that for constructors the arguments are always passed in as 1D arrays
  const char* pType = cppType(bConstructor ? 1 : dimensions());

  if (bPrependSeperator)
  {
    rFile.write(",");
    rFile.newline();
  }

  if (bConstructor)
  {
    rFile.write("const ");
  }

  rFile.write(pType);

  ASSERT(mode() == AdtAutoMode_AUTOINIT || mode() == AdtAutoMode_FN_ARGUMENT);

  // Prepend an underscore as this is an argument being passed into the
  // constructor.
  rFile.write(" arg_");
  rFile.write(name());
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppVarInitialisation(AdtFile& rFile,
                                             AdtStringByStringMap& rLocalsMap,
                                             const char* pClassName,
                                             bool bWithTranslation) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    {
      rFile.write(name());
      rFile.write(" = 0;");
      rFile.newline();
      break;
    }

    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      string  sPlan;
      bool    bFound = getPlan(true, sPlan);

      if (!bFound)
      {
        writeCppCreatePlan(rFile, rLocalsMap, sPlan);
      }

      // Non trivial. We need to query the lower and upper bound expressions
      // for this array and use them to create and initialise the array. However,
      // to complicate issues, the array bounds can be specified using 1d integer
      // arrays specifying dimensions. These need to be created as ragged arrays
      // and require some trickery to determine the element count for use in
      // calls to zero.
      if (IsRagged)
      {
        string  sLoopIndexing;
        string  sContext(name());

        sContext += "_context";

        rFile.write(sPlan);
        rFile.write(".create(MemAllocator, ");
        rFile.write(name());
        rFile.write(");");
        rFile.newline();

        // Ragged array initialisation. As R does not support ragged arrays in
        // any form we cannot easily support automatic initialisation using
        // the AUTOINIT mode (ie. can't simply use XCOPY) so we may well not
        // support this automatically. We could support automatic initialisation
        // from a flat structure of the same size but this would mean that R
        // users need to handle the mapping from flat to ragged array structure.
        // That could be complicated and error prone.
        rFile.newline();
        write_ZERO(rFile);
      }
      else
      {
        rFile.write(sPlan);
        rFile.write(".create(MemAllocator, ");
        rFile.write(name());
        rFile.write(");");
        rFile.newline();
        rFile.newline();

        if (mode() == AdtAutoMode_AUTOINIT)
        {
          rFile.write("AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)arg_");
          rFile.write(name());
          rFile.write(", (char*)");
          rFile.write(name());
          rFile.write(");");
          rFile.newline();
        }
        else
        {
          // ZERO array
          write_ZERO(rFile);
        }
      }

      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      string  sPlan;
      bool    bFound = getPlan(false, sPlan);

      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else
      {
        rFile.write("arg_");
        rFile.write(name());
        rFile.write(" = 0;");
        rFile.newline();
        rFile.newline();

        if (HasLocalDependencies || HasGlobalDependencies)
        {
          string  sArrayBounds;

          arrayBoundsArguments(sArrayBounds, false, false);

          rFile.write("AdtArrayPlan::create(MemAllocator, ");
          rFile.write("arg_");
          rFile.write(name());
          rFile.write(", ");
          rFile.write(sArrayBounds);
        }
        else
        {
          rFile.write(sPlan);
          rFile.write(".create(MemAllocator, ");
          rFile.write("arg_");
          rFile.write(name());
        }

        if (bWithTranslation)
        {
          rFile.write(");");
          rFile.newline();
          rFile.newline();
          rFile.write("AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)");
          rFile.write(R_AccessType());
          rFile.write("(");
          rFile.write(name());
          rFile.write("), (char*)arg_");
          rFile.write(name());
          rFile.write(");");
        }
        else
        {
          rFile.write(", (void*)");
          rFile.write(R_AccessType());
          rFile.write("(");
          rFile.write(name());
          rFile.write("));");
        }

        rFile.newline();
        rFile.newline();
      }
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

void AdtAutoArray::writeCppCreatePlan(AdtFile& rFile,
                                      AdtStringByStringMap& rLocalsMap,
                                      const char* pPlan) const
{
  string sPlan(pPlan);

  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    {
      break;
    }

    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      // Non trivial. We need to query the lower and upper bound expressions
      // for this array and use them to create and initialise the array. However,
      // to complicate issues, the array bounds can be specified using 1d integer
      // arrays specifying dimensions. These need to be created as ragged arrays
      // and require some trickery to determine the element count for use in
      // calls to zero.
      if (IsRagged)
      {
        string  sLoopIndexing;
        string  sContext(name());

        sContext += "_context";

        ASSERT(SmallestIndex != NO_INDEX);

        if (SmallestIndex - 1 >= 0)
        {
          rFile.write(sPlan);
          rFile.write(".initialise(");
          writePlanBasesAndSizes(rFile, SmallestIndex - 1, SmallestIndex);
          rFile.write(");");
          rFile.newline();
        }

        rFile.newline();
        rFile.write("RAGGED_CONTEXT ");
        rFile.write(sContext);
        rFile.write(" = 0;");
        rFile.newline();
        rFile.newline();
        rFile.write(sPlan);
        rFile.write(".beginRagged(");
        rFile.write(sContext);
        rFile.write(", ");
        writePlanBasesAndSizes(rFile, SmallestIndex, SmallestIndex + 1);
        rFile.write(");");
        rFile.newline();

        writeBuildRaggedArrayPlan(rFile,
                                  CppSourceFileType,
                                  rLocalsMap,
                                  SmallestIndex,
                                  sLoopIndexing,
                                  sPlan,
                                  sContext.c_str());

        rFile.newline();
        rFile.write(sPlan);
        rFile.write(".endRagged(");
        rFile.write(sContext);
        rFile.write(");");
        rFile.newline();
      }
      else
      {
        rFile.write(sPlan);
        rFile.write(".initialise(");
        writePlanBasesAndSizes(rFile, 0, Dimensions);
        rFile.write(");");
        rFile.newline();
      }

      rFile.newline();
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else if (!(HasLocalDependencies || HasGlobalDependencies))
      {
        rFile.write(sPlan);
        rFile.write(".initialise(");
        writePlanBasesAndSizes(rFile, 0, Dimensions);
        rFile.write(");");
        rFile.newline();
      }
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

void AdtAutoArray::writeCppCopyPlan(AdtFile& rFile,
                                    const char* pPlan) const
{
  string  sPlan(pPlan);

  rFile.write(",");
  rFile.newline();
  rFile.write(sPlan);
  rFile.write("(rCopy.");
  rFile.write(sPlan);
  rFile.write(")");
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppVarReturn(AdtFile& rFile,
                                     const char* pClassName) const
{
  switch(mode())
  {
    case AdtAutoMode_FN_ARGUMENT:
    {
      if (IsRagged)
      {
        ::printf("ERROR: R inteface code creation not supported for ragged arrays : context file %s line %d\n",
                 fileName().c_str(),
                 lineNumber());
      }
      else
      {
        rFile.write("AdtArrayPlanActor::ADlib_to_R(MemAllocator, (char*)arg_");
        rFile.write(name());
        rFile.write(", (char*)");
        rFile.write(R_AccessType());
        rFile.write("(");
        rFile.write(name());
        rFile.write("));");
        rFile.newline();
      }
      break;
    }

    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppVarDestroy(AdtFile& rFile) const
{
  switch(mode())
  {
    case AdtAutoMode_MANUAL:
    case AdtAutoMode_AUTODEC:
    case AdtAutoMode_AUTOINIT:
    {
      // Do nothing
      break;
    }

    case AdtAutoMode_FN_ARGUMENT:
    {
      rFile.write("AdtArrayPlan::destroy(MemAllocator, arg_");
      rFile.write(name());
      rFile.write(");");
      rFile.newline();
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

void AdtAutoArray::writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const
{
  if (!IsRagged)
  {
    string sSourceName("arg_");

    sSourceName += name();

    const char* sTypeC[2] = {"", "nt_"};
    const char* sBool[2]  = {"false", "true"};

    for (int cn = 0 ; cn < 2 ; cn++)
    {
      // Implement getter method
      rFile.newline();
      rFile.write("SEXP ");
      rFile.write(pClassName);
      rFile.write("::_get_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(SEXP sArgList) const");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("SEXP Result = R_ImplGetter(MemAllocator, ");
      rFile.write(sBool[cn]);
      rFile.write(", (char*)");
      rFile.write(name());
      rFile.write(", \"");
      rFile.write(name());
      rFile.write("\", sArgList, __FILE__, __LINE__);");
      rFile.newline();
      rFile.newline();
      rFile.write("return (Result);");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.newline();

      // Implement setter method
      rFile.write("SEXP ");
      rFile.write(pClassName);
      rFile.write("::_set_");
      rFile.write(sTypeC[cn]);
      rFile.write(name());
      rFile.write("(SEXP arg_");
      rFile.write(name());
      rFile.write(", SEXP sArgList");
      rFile.write(")");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("SEXP Result = R_ImplSetter(MemAllocator, ");
      rFile.write(sBool[cn]);
      rFile.write(", (char*)");
      rFile.write(name());
      rFile.write(", \"");
      rFile.write(name());
      rFile.write("\", arg_");
      rFile.write(name());
      rFile.write(", sArgList, __FILE__, __LINE__);");
      rFile.newline();
      rFile.newline();
      rFile.write("return (Result);");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                   const char* pClassName,
                                                   const char* pAliasName,
                                                   const char* pR_TypeName) const
{
  if (!IsRagged)
  {
    // implement get and set export routines using .External interface
    writeCppR_GetterAndSetter(rFile, pClassName, pAliasName, pR_TypeName);
  }
}

//  ----------------------------------------------------------------------------

AdtAutoArray::AdtAutoArray(const char* pName,
                           const char* pClassName,
                           AdtAutoType nType,
                           AdtAutoMode nMode,
                           AdtAutoDir nDir,
                           int nPhase,
                           bool bNoInterface,
                           bool bWithInitialisation,
                           int nDimensions,
                           const char* pFileName,
                           int nLineNumber)
 : AdtAutoAttribute(pName,
                    pClassName,
                    AttributeTypeArray,
                    nType,
                    nMode,
                    nDir,
                    nPhase,
                    bNoInterface,
                    bWithInitialisation,
                    pFileName,
                    nLineNumber),
   ArrayDependencies(),
   ArrayDependancyLocal(),
   ArrayLowerBoundByIndex(),
   ArrayUpperBoundByIndex(),
   SizeSpecification()
{
  Dimensions                = nDimensions;
  IsRagged                  = false;
  LastScalar                = -1;
  RefreshSizeSpecification  = true;
  HasLocalDependencies      = false;
  HasGlobalDependencies     = false;
}

//  ----------------------------------------------------------------------------

AdtAutoArray::AdtAutoArray(const AdtAutoArray& rCopy)
 : AdtAutoAttribute(rCopy),
   ArrayDependencies(rCopy.ArrayDependencies),
   ArrayDependancyLocal(rCopy.ArrayDependancyLocal),
   ArrayLowerBoundByIndex(rCopy.ArrayLowerBoundByIndex),
   ArrayUpperBoundByIndex(rCopy.ArrayUpperBoundByIndex),
   SizeSpecification(rCopy.SizeSpecification)
{
  Dimensions                = rCopy.Dimensions;
  IsRagged                  = rCopy.IsRagged;
  LastScalar                = rCopy.LastScalar;
  RefreshSizeSpecification  = true;
  HasLocalDependencies      = false;
  HasGlobalDependencies     = false;
}

//  ----------------------------------------------------------------------------

AdtAutoArray::~AdtAutoArray()
{
  ArrayDependencies.clear();
  ArrayDependancyLocal.clear();
  ArrayLowerBoundByIndex.clear();
  ArrayUpperBoundByIndex.clear();
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::flushArrayPlanInfo()
{
  ArrayPlanInfoMap.clear();
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCreatePlans(AdtFile& rFile,
                                    AdtSourceFileType nDestType,
                                    const char* pClassName,
                                    AdtStringByStringMap& rLocalsMap)
{
  AdtAutoArrayPlanInfoByStringMapIter Iter;

  for (Iter = ArrayPlanInfoMap.begin() ; Iter != ArrayPlanInfoMap.end() ; ++Iter)
  {
    AdtAutoArrayPlanInfo& rPlanInfo = Iter->second;

    if (!rPlanInfo.initialised() && rPlanInfo.inClass(pClassName))
    {
      const AdtAutoArray*   pArray = rPlanInfo.array();

      switch (nDestType)
      {
        case DelphiSourceFileType:
        {
          pArray->writeDelphiCreatePlan(rFile, rLocalsMap, rPlanInfo.plan());
          break;
        }

        case CppSourceFileType:
        case CppHeaderFileType:
        {
          pArray->writeCppCreatePlan(rFile, rLocalsMap, rPlanInfo.plan());
          break;
        }

        case JavaSourceFileType:
        case FortranSourceFileType:
        case UnknownSourceFileType:
        default:
        {
          FAIL();
          break;
        }
      }

      rPlanInfo.initialise();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeCopyPlans(AdtFile& rFile,
                                  AdtSourceFileType nDestType,
                                  const char* pClassName)
{
  AdtAutoArrayPlanInfoByStringMapIter Iter;

  for (Iter = ArrayPlanInfoMap.begin() ; Iter != ArrayPlanInfoMap.end() ; ++Iter)
  {
    AdtAutoArrayPlanInfo& rPlanInfo = Iter->second;

    if (rPlanInfo.inClass(pClassName))
    {
      const AdtAutoArray*   pArray = rPlanInfo.array();

      switch (nDestType)
      {
        case DelphiSourceFileType:
        {
          pArray->writeDelphiCopyPlan(rFile, rPlanInfo.plan());
          break;
        }

        case CppSourceFileType:
        case CppHeaderFileType:
        {
          pArray->writeCppCopyPlan(rFile, rPlanInfo.plan());
          break;
        }

        case JavaSourceFileType:
        case FortranSourceFileType:
        case UnknownSourceFileType:
        default:
        {
          FAIL();
          break;
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::addArrayIndex(const char* sArrayLowerBound,
                                 const char* sArrayUpperBound,
                                 int nIndex)
{
  if (nIndex < Dimensions)
  {
    if (sArrayLowerBound != 0)
    {
      ArrayLowerBoundByIndex[nIndex] = sArrayLowerBound;
    }

    if (sArrayUpperBound != 0)
    {
      ArrayUpperBoundByIndex[nIndex] = sArrayUpperBound;
    }

    LastScalar               = -1;
    RefreshSizeSpecification = true;
  }
  else
  {
    // Error
  }
}

//  ----------------------------------------------------------------------------

int AdtAutoArray::dimensions() const
{
  return (Dimensions);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArray::isScalar() const
{
  return (false);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArray::isRagged() const
{
  return (IsRagged);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArray::strictlyBefore(int nPhase) const
{
  // Dependent arrays must be initialised striclty before.
  bool bBefore = (phase() < nPhase);

  return (bBefore);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArray::checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                     const AdtAutoAttributePtrByStringMap* pSecondaryMap) const
{
  bool                        bOk = true;
  AdtExpressionCompiler       Compiler;
  AdtStringByIntMapConstIter  Iter;
  AdtStringList               DependencyList;
  AdtStringByIntMap           LowerBoundMap;
  AdtStringByIntMap           UpperBoundMap;

  LastScalar            = -1; // This must be initialised negative
  SmallestIndex         = NO_INDEX;
  IsRagged              = false;
  HasLocalDependencies  = false;
  HasGlobalDependencies = false;

  ArrayDependencies.clear();
  ArrayDependancyLocal.clear();

  for (int cn = 0 ; cn < Dimensions ; cn++)
  {
    string                  sLowerBoundExpression;
    string                  sUpperBoundExpression;
    AdtExpressionAdditive*  pRootLower = 0;
    AdtExpressionAdditive*  pRootUpper = 0;

    DependencyList.clear();

    Iter = ArrayLowerBoundByIndex.find(cn);

    if (Iter != ArrayLowerBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      Compiler.findDependencies(rIndexExpression,
                                DependencyList,
                                &sLowerBoundExpression,
                                &pRootLower);
    }

    Iter = ArrayUpperBoundByIndex.find(cn);

    if (Iter != ArrayUpperBoundByIndex.end())
    {
      const string& rIndexExpression = (*Iter).second;

      Compiler.findDependencies(rIndexExpression,
                                DependencyList,
                                &sUpperBoundExpression,
                                &pRootUpper);
    }

    LowerBoundMap[cn] = sLowerBoundExpression;
    UpperBoundMap[cn] = sUpperBoundExpression;

    // This is doing my head in...
    // The last scalar bounds specification needs to match the next vector
    // dependencies. Then the bounds specification for next index needs to
    // match the two previous. For example,
    //
    // A{1+y:n+x} : ARRAY_1L
    // C{1+y:n+x} : ARRAY_1L
    // B{1+y:n+x, 1:A[<1>]+C[<1>]+1} : ARRAY_2L;
    // E{1+y:n+x, 1:A[<1>]+C[<1>]+1} : ARRAY_2L;
    // D{1+y:n+x, 1:A[<1>]+C[<1>]+1, 1:B[<1>,<2>]-2*E[<1>,<2>]-1} : ARRAY_3L;
    //
    // So doing the dependency check 1,y,n,x are all scalars, checking B,
    // nLastScalar == 0 and 1+y:n+x becomes the index that must match the
    // dimensions of A and C, likewise in E. checking D, nLastScalar == 0
    // and 1+y:n+x becomes the index that must match the dimensions of index
    // nLastScalar + 1 and 1+y:n+x,1:A+C+1 becomes the index that must match
    // the dimensions of index nLastScalar + 2 for dependencies B and E.
    checkDependencies(bOk,
                      DependencyList,
                      LowerBoundMap,
                      UpperBoundMap,
                      rMap,
                      pSecondaryMap,
                      pRootLower,
                      pRootUpper,
                      cn,
                      LastScalar,
                      SmallestIndex);

    UtlReleaseReference(pRootLower);
    UtlReleaseReference(pRootUpper);
  }

  if (LastScalar >= 0)
  {
    IsRagged = true;

    if (mode() == AdtAutoMode_AUTOINIT || mode() == AdtAutoMode_FN_ARGUMENT)
    {
      ::printf("ERROR: %s is a ragged array. Ragged arrays cannot be declared with mode AUTOINIT\n",
               name().c_str());
    }
  }

  return (bOk);
}

//  ----------------------------------------------------------------------------

bool AdtAutoArray::checkSize(const string& rMustMatchSize) const
{
  bool bOk = false;

  // This method builds the size specification string for the Array and match
  // it with rMustMatchSize. If it matches then return true otherwise false.
  // Need to loop through dimensions and compile all expressions to give the
  // dimensions as a unified string. This isn't perfect as it will pull up
  // {1:n+1} as being different from {1:1+n}, when in fact, they are the same.
  // To sort out that comparison requires much more work.
  if (RefreshSizeSpecification)
  {
    AdtExpressionCompiler       Compiler;
    AdtStringByIntMapConstIter  Iter;

    //Rebuild SizeSpecification
    SizeSpecification = "";

    for (int cn = 0 ; cn < Dimensions ; cn++)
    {
      string  sLowerBoundExpression;
      string  sUpperBoundExpression;

      Iter = ArrayLowerBoundByIndex.find(cn);

      if (Iter != ArrayLowerBoundByIndex.end())
      {
        const string& rIndexExpression = (*Iter).second;

        Compiler.reconstruct(rIndexExpression, sLowerBoundExpression);
      }

      Iter = ArrayUpperBoundByIndex.find(cn);

      if (Iter != ArrayUpperBoundByIndex.end())
      {
        const string& rIndexExpression = (*Iter).second;

        Compiler.reconstruct(rIndexExpression, sUpperBoundExpression);
      }

      if (SizeSpecification.length() != 0)
      {
        SizeSpecification += ",";
      }

      if (sLowerBoundExpression.length() != 0)
      {
        SizeSpecification += sLowerBoundExpression + ":";
      }

      SizeSpecification += sUpperBoundExpression;
    }

    RefreshSizeSpecification = false;
  }

  // Check if the sizes match
  bOk = (rMustMatchSize == SizeSpecification);

  return (bOk);
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeRInterface(AdtFile& rFile,
                                   const char* pClassName,
                                   const char* pAliasName) const
{
  if (!isRagged())
  {
    AdtAutoHelper Helper;
    string        sBaseIndices;
    string        sArraySizes;

    arraySizesAndBaseIndices(sArraySizes, sBaseIndices);

    const char* sTypeR[2] = {"", "nt."};

    for (int cn = 0 ; cn < 2 ; cn++)
    {
      // Write get function
      rFile.write(pAliasName);
      rFile.write(".get.");
      rFile.write(sTypeR[cn]);
      rFile.write(name());
      rFile.write(" <- function(Context, ...)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("return (.External('_");
      rFile.write(pAliasName);
      rFile.write(".get.");
      rFile.write(sTypeR[cn]);
      rFile.write(name());
      rFile.write("', Context, list(...)))");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.newline();

      // Write set function
      rFile.write(pAliasName);
      rFile.write(".set.");
      rFile.write(sTypeR[cn]);
      rFile.write(name());
      rFile.write(" <- function(Context, Arg, ...)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("return (.External('_");
      rFile.write(pAliasName);
      rFile.write(".set.");
      rFile.write(sTypeR[cn]);
      rFile.write(name());
      rFile.write("', Context, ");
      Helper.writeR_typeCast(rFile, type(), "Arg", name());
      rFile.write(", list(...)))");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.newline();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoArray::writeArrayPlans(AdtFile& rFile,
                                   AdtSourceFileType nDestType,
                                   const char* pClassName)
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      AdtAutoArrayPlanInfoByStringMapIter Iter;

      for (Iter = ArrayPlanInfoMap.begin() ; Iter != ArrayPlanInfoMap.end() ; ++Iter)
      {
        AdtAutoArrayPlanInfo& rPlanInfo = Iter->second;

        if (rPlanInfo.inClass(pClassName))
        {
          rFile.write(rPlanInfo.plan());
          rFile.write(" : AdtArrayPlan;");
          rFile.newline();
        }
      }
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      AdtAutoArrayPlanInfoByStringMapIter Iter;

      for (Iter = ArrayPlanInfoMap.begin() ; Iter != ArrayPlanInfoMap.end() ; ++Iter)
      {
        AdtAutoArrayPlanInfo& rPlanInfo = Iter->second;

        if (rPlanInfo.inClass(pClassName))
        {
          rFile.write("AdtArrayPlan ");
          rFile.write(rPlanInfo.plan());
          rFile.write(";");
          rFile.newline();
        }
      }
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      FAIL();
      break;
    }
  }
}


//  ----------------------------------------------------------------------------
//  AdtAutoFunction method implementations
//  ----------------------------------------------------------------------------
void AdtAutoFunction::writeDelphiVarCheckType(AdtFile& rFile,
                                              bool bPrefix,
                                              bool bInConstructor) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiVarDeclaration(AdtFile& rFile,
                                                bool bConstructor,
                                                bool bPrependSeperator) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiVarInitialisation(AdtFile& rFile,
                                                   AdtStringByStringMap& rLocalsMap,
                                                   const char* pClassName,
                                                   bool bWithTranslation) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiVarReturn(AdtFile& rFile,
                                           const char* pClassName) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiVarDestroy(AdtFile& rFile) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiDeclLibInterfaceMethods(AdtFile& rFile) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_InterfaceDeclMethods(rFile, name().c_str(), ArgumentList);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiDeclLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pAliasName) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_InterfaceDeclGlobals(rFile, name().c_str(), ArgumentList, pAliasName);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiImplLibInterfaceMethods(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_InterfaceImplMethods(rFile, name().c_str(), type(), ArgumentList, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeDelphiImplLibInterfaceGlobals(AdtFile& rFile,
                                                         const char* pClassName,
                                                         const char* pAliasName,
                                                         const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeDelphiR_InterfaceImplGlobals(rFile, name().c_str(), type(), ArgumentList, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppVarCheckType(AdtFile& rFile,
                                           bool bPrefix,
                                           bool bInConstructor) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppVarDeclaration(AdtFile& rFile,
                                             bool bConstructor,
                                             bool bPrependSeperator) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppVarInitialisation(AdtFile& rFile,
                                                AdtStringByStringMap& rLocalsMap,
                                                const char* pClassName,
                                                bool bWithTranslation) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppVarReturn(AdtFile& rFile,
                                        const char* pClassName) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppVarDestroy(AdtFile& rFile) const
{
  // Do nothing
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppDeclLibInterfaceMethods(AdtFile& rFile) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_InterfaceDeclMethods(rFile, name().c_str(), ArgumentList);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppDeclLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pAliasName) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_InterfaceDeclGlobals(rFile, name().c_str(), ArgumentList, pAliasName);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppImplLibInterfaceMethods(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_InterfaceImplMethods(rFile, name().c_str(), type(), ArgumentList, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeCppImplLibInterfaceGlobals(AdtFile& rFile,
                                                      const char* pClassName,
                                                      const char* pAliasName,
                                                      const char* pR_TypeName) const
{
  AdtAutoHelper Helper;

  Helper.writeCppR_InterfaceImplGlobals(rFile, name().c_str(), type(), ArgumentList, pClassName, pAliasName, pR_TypeName);
}

//  ----------------------------------------------------------------------------

AdtAutoFunction::AdtAutoFunction(const char* pName,
                                 const char* pClassName,
                                 AdtAutoType nType,
                                 AdtAutoDir nDir,
                                 const char* pFileName,
                                 int nLineNumber)
 : AdtAutoAttribute(pName,
                    pClassName,
                    AttributeTypeFunction,
                    nType,
                    AdtAutoMode_MANUAL,
                    nDir,
                    0,
                    false,
                    true,
                    pFileName,
                    nLineNumber),
   ArgumentList(),
   ArgumentMap()
{

}

//  ----------------------------------------------------------------------------

AdtAutoFunction::AdtAutoFunction(const AdtAutoFunction& rCopy)
 : AdtAutoAttribute(rCopy),
   ArgumentList(),
   ArgumentMap()
{

}

//  ----------------------------------------------------------------------------

AdtAutoFunction::~AdtAutoFunction()
{
  reset();
}


//  ----------------------------------------------------------------------------

void AdtAutoFunction::reset()
{
  AdtAutoAttributePtrListIter         Iter;
  AdtAutoAttributePtrByStringMapIter  MapIter;

  for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
  {
    AdtAutoAttribute* pAttribute = (*Iter);

    UtlReleaseReference(pAttribute);
  }

  ArgumentList.clear();

  for (MapIter = ArgumentMap.begin() ; MapIter != ArgumentMap.end() ; ++MapIter)
  {
    AdtAutoAttribute* pAttribute = (*MapIter).second;

    UtlReleaseReference(pAttribute);
  }

  ArgumentMap.clear();
}

//  ----------------------------------------------------------------------------

bool AdtAutoFunction::strictlyBefore(int nPhase) const
{
  return (true);
}

//  ----------------------------------------------------------------------------

bool AdtAutoFunction::checkDependencies(const AdtAutoAttributePtrByStringMap rMap,
                                        const AdtAutoAttributePtrByStringMap* pSecondaryMap) const
{
  bool                                  bOk = true;
  AdtAutoAttributePtrListConstIter      Iter;
  AdtAutoAttributePtrByStringMap        ExtraMap(ArgumentMap);

  if (pSecondaryMap != 0)
  {
    AdtAutoAttributePtrByStringMapConstIter AddIter;

    for (AddIter = pSecondaryMap->begin() ; AddIter != pSecondaryMap->end() ; ++AddIter)
    {
      AdtAutoAttribute* pObj = (AdtAutoAttribute*)AddIter->second;

      ExtraMap[pObj->name()] = pObj;
    }
  }

  for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
  {
    const AdtAutoAttribute* pAttribute = *Iter;

    if (pAttribute != 0)
    {
      if (!pAttribute->checkDependencies(rMap, &ExtraMap))
      {
        bOk = false;
        break;
      }
    }
  }

  return (bOk);
}

//  ----------------------------------------------------------------------------

bool AdtAutoFunction::checkSize(const string& rMustMatchSize) const
{
  return (true);
}

//  ----------------------------------------------------------------------------

void AdtAutoFunction::writeRInterface(AdtFile& rFile,
                                      const char* pClassName,
                                      const char* pAliasName) const
{
  int         cn;
  const char* sPrefix[2] = {"", "nt."};
  const bool  bCast[2]   = {false, false};

  for (cn = 0 ; cn < 2 ; cn++)
  {
    AdtAutoHelper Helper;

    // Write R wrapper function
    rFile.write(pAliasName);
    rFile.write(".");
    rFile.write(sPrefix[cn]);
    rFile.write(name());
    rFile.write(" <- function(Context");

    if (ArgumentList.size() > 0)
    {
      rFile.write(", ");
    }

    // Write argument list
    AdtAutoAttributePtrListConstIter  Iter;
    bool                              bFirst = true;

    // declare function arguments
    for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (!bFirst)
      {
        rFile.write(", ");
      }

      if (pAttribute != 0)
      {
        rFile.write(pAttribute->name().c_str());
      }
      else
      {
        // Should never happen
        FAIL();
      }

      bFirst = false;
    }

    rFile.write(")");
    rFile.newline();
    rFile.write("{");
    rFile.incrementIndent();
    rFile.newline();
    rFile.write("return (.External('_");
    rFile.write(pAliasName);
    rFile.write(".");
    rFile.write(sPrefix[cn]);
    rFile.write(name());
    rFile.write("', Context");

    if (ArgumentList.size() > 0)
    {
      rFile.write(", ");
    }

    bFirst = true;

    // Write call arguments
    for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = *Iter;

      if (!bFirst)
      {
        rFile.write(", ");
      }

      if (pAttribute != 0)
      {
        if (bCast[cn])
        {
          Helper.writeR_typeCast(rFile,
                                 pAttribute->type(),
                                 pAttribute->name().c_str(),
                                 pAttribute->name().c_str());
        }
        else
        {
          rFile.write(pAttribute->name());
        }
      }
      else
      {
        // Should never happen
        FAIL();
      }

      bFirst = false;
    }

    rFile.write("))");
    rFile.decrementIndent();
    rFile.newline();
    rFile.write("}");
    rFile.newline();
    rFile.newline();
  }
}

//  ----------------------------------------------------------------------------

AdtAutoScalar* AdtAutoFunction::addScalar(const char* pName,
                                          AdtAutoType nType,
                                          AdtAutoDir nDir,
                                          const char* pFileName,
                                          int nLineNumber)
{
  // Note that function parameter arguments shouldn't have any initialisation
  // order dependency issues so to stop the standard checking from flagging
  // errors we pass a suitably large number for the nPhase parameter. In this
  // case we use 10000.
  AdtAutoScalar* pScalar = new AdtAutoScalar(pName,
                                             className(),
                                             nType,
                                             AdtAutoMode_FN_ARGUMENT,
                                             nDir,
                                             10000,
                                             false,
                                             false,
                                             pFileName,
                                             nLineNumber);

  if (pScalar != 0)
  {
    ArgumentList.push_back(pScalar);
    ArgumentMap.insert(AdtAutoAttributePtrStringPair(pName, pScalar));
    pScalar->lock();
  }

  return (pScalar);
}

//  ----------------------------------------------------------------------------

AdtAutoArray* AdtAutoFunction::addArray(const char* pName,
                                        AdtAutoType nType,
                                        AdtAutoDir nDir,
                                        int nDimensions,
                                        const char* pFileName,
                                        int nLineNumber)
{
  // Note that function parameter arguments shouldn't have any initialisation
  // order dependency issues so to stop the standard checking from flagging
  // errors we pass a suitably large number for the nPhase parameter. In this
  // case we use 10000.
  AdtAutoArray* pArray = new AdtAutoArray(pName,
                                          className(),
                                          nType,
                                          AdtAutoMode_FN_ARGUMENT,
                                          nDir,
                                          10000,
                                          false,
                                          false,
                                          nDimensions,
                                          pFileName,
                                          nLineNumber);

  if (pArray != 0)
  {
    ArgumentList.push_back(pArray);
    ArgumentMap.insert(AdtAutoAttributePtrStringPair(pName, pArray));
    pArray->lock();
  }

  return (pArray);
}


//  ----------------------------------------------------------------------------
//  AdtAutoClass method implementations
//  ----------------------------------------------------------------------------
AdtAutoAttributePtrByStringMap  AdtAutoClass::GlobalsMap;
AdtAutoClassPtrByStringMap      AdtAutoClass::ClassMap;
AdtAutoClass*                   AdtAutoClass::CurrentClass         = 0;
bool                            AdtAutoClass::AddExitHandler       = true;
bool                            AdtAutoClass::Enabled              = false;
bool                            AdtAutoClass::AttributeDefsEnabled = false;
bool                            AdtAutoClass::IncludeDisabled      = false;
string                          AdtAutoClass::LibName;
string                          AdtAutoClass::RegistrationCodeBuffer;
AdtFile                         AdtAutoClass::RegistrationCodeFile;
string                          AdtAutoClass::ExternalsCodeBuffer;
AdtFile                         AdtAutoClass::ExternalsCodeFile;


//  ----------------------------------------------------------------------------

void AdtAutoClass::flushAutoClasses()
{
  AdtAutoArray::flushArrayPlanInfo();

  AdtAutoClassPtrByStringMapIter  Iter;

  for (Iter = ClassMap.begin() ; Iter != ClassMap.end() ; ++Iter)
  {
    AdtAutoClass* pClass = (*Iter).second;

    UtlReleaseReference(pClass);
  }

  ClassMap.clear();

  AdtAutoAttributePtrByStringMapIter  GlobalsIter;

  for (GlobalsIter = GlobalsMap.begin() ; GlobalsIter != GlobalsMap.end() ; ++GlobalsIter)
  {
    AdtAutoAttribute* pAttribute = (*GlobalsIter).second;

    UtlReleaseReference(pAttribute);
  }

  GlobalsMap.clear();
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::addGlobalScalar(const char* pName,
                                   AdtAutoType nType,
                                   const char* pFileName,
                                   int nLineNumber)
{
  bool bAdded = false;

  if (automationEnabled()       &&
      (pName              != 0) &&
      (strlen(pName)       > 0))
  {
    AdtAutoAttributePtrByStringMapIter  Iter = GlobalsMap.find(pName);

    if (Iter != GlobalsMap.end())
    {
      ::printf("WARNING: Global variable %s is being redefined in file %s on line %d\n", pName, pFileName, nLineNumber);
    }
    else
    {
      AdtAutoAttribute* pGlobal = new AdtAutoGlobalScalar(pName,
                                                          nType,
                                                          pFileName,
                                                          nLineNumber);

      GlobalsMap[pName] = pGlobal;
    }

    bAdded  = true;
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::addLibName(const char* pLibName,
                              const char* pFileName,
                              int nLineNumber)
{
  bool bAdded = false;

  if (automationEnabled()     &&
      (pLibName         != 0) &&
      (strlen(pLibName)  > 0))
  {
    if ((LibName.length() > 0) && (LibName != pLibName))
    {
      ::printf("WARNING: Library name is being redefined with AD_LIBNAME in file %s on line %d\n", pFileName, nLineNumber);
    }

    LibName = pLibName;
    bAdded  = true;
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::addClassNameAndAlias(const char* pClassName,
                                        const char* pAlias,
                                        const char* pParentClassName,
                                        const char* pFileName,
                                        int nLineNumber)
{
  bool bAdded = false;

  if (automationEnabled())
  {
    if (pClassName != 0)
    {
      AdtAutoClass* pClass = findClass(pClassName);

      if (pClass != 0)
      {
        CurrentClass = pClass;

        ::printf("WARNING: Class %s multiply defined with AD_ALIAS in file %s on line %d\n", pClassName, pFileName, nLineNumber);
      }
      else
      {
        CurrentClass = new AdtAutoClass();

        if (CurrentClass != 0)
        {
          CurrentClass->classNameAndAlias(pClassName, pAlias);

          ClassMap[pClassName]  = CurrentClass;
          bAdded                = true;

          if (pParentClassName != 0)
          {
            AdtAutoClassPtrByStringMapConstIter Iter = ClassMap.find(pParentClassName);

            if (Iter != ClassMap.end())
            {
              CurrentClass->inheritFrom((*Iter).second);
            }
          }
        }
      }

      if (AddExitHandler)
      {
        ::atexit(AdtAutoClass::flushAutoClasses);

        AddExitHandler = false;
      }
    }
  }

  return (bAdded);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::setModeAndPhase(int nMode,
                                   int nPhase,
                                   bool bNoInterface,
                                   const char* pFileName,
                                   int nLineNumber)
{
  bool bSet = false;

  if (automationEnabled())
  {
    if (CurrentClass != 0)
    {
      CurrentClass->mode((AdtAutoMode)nMode, pFileName, nLineNumber);
      CurrentClass->phase(nPhase, pFileName, nLineNumber);
      CurrentClass->noInterface(bNoInterface, pFileName, nLineNumber);

      bSet = true;
    }
    else
    {
      ::printf("ERROR: AD_ALIAS macro missing. AD_ALIAS must be define before macro in file %s on line %d\n", pFileName, nLineNumber);
      ::AdtExit(-1);
    }
  }

  return (bSet);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::includeDisableAutomation(bool bDisable)
{
  AdtAutoClass::IncludeDisabled = bDisable;
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::enableAutomation(bool bEnable, bool bWithAttributeDefsEnabled)
{
  AdtAutoClass::Enabled               = bEnable;
  AdtAutoClass::AttributeDefsEnabled  = bEnable & bWithAttributeDefsEnabled;
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::automationEnabled()
{
  return (AdtAutoClass::Enabled && !AdtAutoClass::IncludeDisabled);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::attributeDefsEnabled()
{
  return (AttributeDefsEnabled);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::clearRegistrationCode()
{
  RegistrationCodeFile.close();
  RegistrationCodeBuffer.clear();
  RegistrationCodeFile.open(RegistrationCodeBuffer);

  ExternalsCodeFile.close();
  ExternalsCodeBuffer.clear();
  ExternalsCodeFile.open(ExternalsCodeBuffer);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtAutoClass::registrationCodeFile()
{
  return (RegistrationCodeFile);
}

//  ----------------------------------------------------------------------------

AdtFile& AdtAutoClass::externalsCodeFile()
{
  return (ExternalsCodeFile);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::exportConstructorArgsFiles(AdtSourceFileType nDestType,
                                              const char* pDestFolder)
{
  if (CurrentClass != 0)
  {
    CurrentClass->writeConstructorArgsFiles(nDestType, pDestFolder);
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::exportAutomationFiles(AdtSourceFileType nDestType,
                                         const char* pDestFolder,
                                         const char* pDestIncludeFolder,
                                         const char* pConstructorClassName,
                                         int nClassNumber)
{
  if (CurrentClass != 0)
  {
    CurrentClass->writeAutomationFiles(nDestType, pDestFolder, pDestIncludeFolder, pConstructorClassName, nClassNumber);
  }
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::buildClassConstructor(AdtStringList& rConstructorList,
                                         const char* pClassName,
                                         const char* pParentClassName,
                                         const char* pPathPrefix,
                                         AdtSourceFileType nAsFileType)
{
  bool          bDone   = false;
  AdtAutoClass* pClass  = findClass(pClassName);

  if (pClass != 0)
  {
    string  rConstructorDeclaration;
    string  rConstructorCall;
    string  rCopyConstructorDeclaration;
    string  rCopyConstructorCall;

    switch (nAsFileType)
    {
      case DelphiSourceFileType:
      {
        rConstructorDeclaration  = "create({$I ";
        rConstructorDeclaration += pPathPrefix;
        rConstructorDeclaration += pClass->AliasName;
        rConstructorDeclaration += CONSTRUCTOR_ARGS;
        rConstructorDeclaration += ".pas});";

        rConstructorCall = "create(";

        if (pClass->ParentConstructorCallArgsFileName.length() > 0)
        {
          rConstructorCall += "{$I ";
          rConstructorCall += pPathPrefix;
          rConstructorCall += pClass->ParentConstructorCallArgsFileName;
          rConstructorCall += ".pas}";
        }
        else
        {
          rConstructorCall += "{$I ";
          rConstructorCall += pPathPrefix;
          rConstructorCall += pClass->AliasName + CONSTRUCTOR_CALL_ARGS;
          rConstructorCall += ".pas}";
        }

        rConstructorCall += ");";

        rCopyConstructorDeclaration  = "create(const rCopy : ";
        rCopyConstructorDeclaration += pClass->ClassName;
        rCopyConstructorDeclaration += ");";

        rCopyConstructorCall = "create(rCopy);";
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        rConstructorDeclaration  = "(\n#include \"";
        rConstructorDeclaration += pPathPrefix;
        rConstructorDeclaration += pClass->AliasName;
        rConstructorDeclaration += CONSTRUCTOR_ARGS;
        rConstructorDeclaration += ".hpp\"\n)";

        rConstructorCall  = pParentClassName;
        rConstructorCall += "(";

        if (pClass->ParentConstructorCallArgsFileName.length() > 0)
        {
          rConstructorCall += "\n#include \"";
          rConstructorCall += pPathPrefix;
          rConstructorCall += pClass->ParentConstructorCallArgsFileName;
          rConstructorCall += ".hpp\"\n";
        }
        else
        {
          rConstructorCall += "\n#include \"";
          rConstructorCall += pPathPrefix;
          rConstructorCall += pClass->AliasName + CONSTRUCTOR_CALL_ARGS;
          rConstructorCall += ".hpp\"\n";
        }

        rConstructorCall += ")";

        rCopyConstructorDeclaration  = "(const ";
        rCopyConstructorDeclaration += pClass->ClassName;
        rCopyConstructorDeclaration += "& rCopy)";

        rCopyConstructorCall  = pParentClassName;
        rCopyConstructorCall += "(rCopy)";
        break;
      }

      case JavaSourceFileType:
      case FortranSourceFileType:
      case UnknownSourceFileType:
      default:
      {
        break;
      }
    }

    rConstructorList.push_back(rConstructorDeclaration);
    rConstructorList.push_back(rConstructorCall);
    rConstructorList.push_back(rCopyConstructorDeclaration);
    rConstructorList.push_back(rCopyConstructorCall);

    bDone = true;
  }

  return (bDone);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeIncludeStatement(AdtFile& rFile,
                                         const char* pWhich,
                                         const char* pPathPrefix,
                                         AdtSourceFileType nDestType,
                                         const char* pClassName)
{
  if (pWhich != 0)
  {
    AdtAutoClass* pClass = findClass(pClassName);

    if (pClass != 0)
    {
      switch (nDestType)
      {
        case DelphiSourceFileType:
        {
          rFile.write("{$I ");
          rFile.write(pPathPrefix);
          rFile.write(pClass->AliasName);
          rFile.write(pWhich);
          rFile.write(".pas}");
          rFile.newline();
          break;
        }

        case CppSourceFileType:
        case CppHeaderFileType:
        {
          rFile.write("#include \"");
          rFile.write(pPathPrefix);
          rFile.write(pClass->AliasName);
          rFile.write(pWhich);
          rFile.write(".hpp\"");
          rFile.newline();
          break;
        }

        case JavaSourceFileType:
        case FortranSourceFileType:
        case UnknownSourceFileType:
        default:
        {
          break;
        }
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeInterfaceMethodsDeclInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        DECL_LIB_INTERFACE_METHODS,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeInterfaceMethodsImplInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        IMPL_LIB_INTERFACE_METHODS,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeInterfaceGlobalsDeclInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        DECL_LIB_INTERFACE_GLOBALS,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeInterfaceGlobalsImplInclude(AdtFile& rFile,
                                                    AdtSourceFileType nDestType,
                                                    const char* pClassName,
                                                    const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        IMPL_LIB_INTERFACE_GLOBALS,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeConstructorDeclInclude(AdtFile& rFile,
                                               AdtSourceFileType nDestType,
                                               const char* pClassName,
                                               const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        DECL_LIB_INTERFACE_CONSTRUCTOR,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeConstructorImplInclude(AdtFile& rFile,
                                               AdtSourceFileType nDestType,
                                               const char* pClassName,
                                               const char* pPathPrefix)
{
  writeIncludeStatement(rFile,
                        IMPL_LIB_INTERFACE_CONSTRUCTOR,
                        pPathPrefix,
                        nDestType,
                        pClassName);
}

//  ----------------------------------------------------------------------------

AdtAutoClass* AdtAutoClass::findClass(const char* pClassName)
{
  AdtAutoClass*                   pClass  = 0;
  AdtAutoClassPtrByStringMapIter  Iter    = ClassMap.find(pClassName);

  if (Iter != ClassMap.end())
  {
    pClass = (*Iter).second;
  }

  return (pClass);
}

//  ----------------------------------------------------------------------------

AdtAutoClass* AdtAutoClass::currentClass()
{
  return (CurrentClass);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::inherit(const AdtAutoAttribute* pAttribute)
{
  if (pAttribute != 0)
  {
    size_t  nAttributeID;

    nAttributeID                = (size_t)pAttribute;
    InheritedMap[nAttributeID]  = nAttributeID;
  }
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::isInherited(const AdtAutoAttribute* pAttribute) const
{
  size_t  nAttributeID = (size_t)pAttribute;
  bool    bInherited   = (InheritedMap.find(nAttributeID) != InheritedMap.end());

  return (bInherited);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::createFileName(string& rFileName,
                                  const char* pFileNameBase,
                                  AdtSourceFileType nDestType) const
{
  if (pFileNameBase != 0)
  {
    rFileName = pFileNameBase;

    switch (nDestType)
    {
      case DelphiSourceFileType:
      {
        rFileName += ".pas";
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        rFileName += ".hpp";
        break;
      }

      case JavaSourceFileType:
      {
        rFileName += ".java";
        break;
      }

      case FortranSourceFileType:
      {
        rFileName += ".for";
        break;
      }

      case UnknownSourceFileType:
      default:
      {
        break;
      }
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::appendFileToStringList(AdtStringList& rStringList,
                                          const char* pDestFolder,
                                          const char* pFileNameBase,
                                          AdtSourceFileType nDestType) const
{
  AdtFile rFile;

  if (openFile(rFile, pDestFolder, pFileNameBase, nDestType, false))
  {
    rFile.readLines(rStringList);
    rFile.close();
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeIncrementalCompileFile(const string& sBufferToWrite,
                                               AdtSourceFileType nDestType,
                                               const char* pDestFolder,
                                               const char* pPrefix,
                                               int nClassNumber) const
{
  if (sBufferToWrite.length() > 0)
  {
    AdtFile rRegFile;
    string  sRegFileName(LibName);
    char    sBuffer[32] = {0};

    ::sprintf(sBuffer, "%d", nClassNumber);

    if (pPrefix != 0)
    {
      sRegFileName += pPrefix;
    }

    sRegFileName += sBuffer;

    if (openFile(rRegFile, pDestFolder, sRegFileName, nDestType, true))
    {
      rRegFile.write(sBufferToWrite);
      rRegFile.close();
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::readIncrementalCompileFiles(AdtStringList& rStringList,
                                               AdtSourceFileType nDestType,
                                               const char* pDestFolder,
                                               const char* pPrefix,
                                               int nClassNumber) const
{
  // Combine all the registration code files together and count
  // the number of entries
  for (int cn = 1 ; cn <= nClassNumber ; cn++)
  {
    string  sRegFileName(LibName);
    char    sBuffer[32] = {0};

    ::sprintf(sBuffer, "%d", cn);

    if (pPrefix != 0)
    {
      sRegFileName += pPrefix;
    }

    sRegFileName += sBuffer;

    appendFileToStringList(rStringList,
                           pDestFolder,
                           sRegFileName,
                           nDestType);
  }
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::openFile(AdtFile& rFile,
                            const char* pDestFolder,
                            const char* pFileName,
                            bool bWrite) const
{
  bool bOpened = false;

  if ((pDestFolder != 0) && (pFileName != 0))
  {
    string FileName(pDestFolder);

    FileName += pFileName;

    bOpened = bWrite ? rFile.open(FileName, "wt") : rFile.open(FileName, "rt");
  }

  return (bOpened);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::openFile(AdtFile& rFile,
                            const char* pDestFolder,
                            const char* pFileNameBase,
                            AdtSourceFileType nDestType,
                            bool bWrite) const
{
  bool    bOpened = false;
  string  FileName;

  createFileName(FileName, pFileNameBase, nDestType);

  bOpened = openFile(rFile, pDestFolder, FileName, bWrite);

  return (bOpened);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeConstructorDecl(AdtFile& rFile,
                                        AdtSourceFileType nDestType,
                                        const char* pConstructorClassName) const
{
  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      AdtStringListConstIter  Iter;
      AdtAutoHelper           Helper;

      // Write destructor interface code
      rFile.write("function ");
      rFile.write(AliasName);
      rFile.write("_destroy");
      rFile.write("(args : SEXP) : SEXP; cdecl;");
      rFile.newline();

      // Write constructor interface code
      rFile.write("function ");
      rFile.write(AliasName);
      rFile.write("_create(args : SEXP) : SEXP; cdecl;");
      rFile.newline();
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      AdtStringListConstIter  Iter;
      AdtAutoHelper           Helper;

      // Write destructor interface code
      rFile.write("EXPORT SEXP ");
      rFile.write(AliasName);
      rFile.write("_destroy");
      rFile.write("(SEXP args);");
      rFile.newline();

      // Write constructor interface code
      rFile.write("EXPORT SEXP ");
      rFile.write(AliasName);
      rFile.write("_create(SEXP args);");
      rFile.newline();
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeConstructorImpl(AdtFile& rFile,
                                        AdtSourceFileType nDestType,
                                        const char* pConstructorClassName) const
{
  string  FunctionName;
  string  ExportName;

  switch (nDestType)
  {
    case DelphiSourceFileType:
    {
      size_t                  nCount;
      AdtStringListConstIter  Iter;
      AdtAutoHelper           Helper;

      // Write destructor interface code
      rFile.newline();
      rFile.write("Procedure ");
      rFile.write(AliasName);
      rFile.write("_destroy_handler(rInstance : SEXP); cdecl;");
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();
      Helper.writeDelphiR_CheckInstance(rFile, ClassName, AliasName);
      rFile.newline();
      rFile.write("if (R_ExternalPtrAddr(rInstance) <> nil) then");
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write(pConstructorClassName);
      rFile.write("(R_ExternalPtrAddr(rInstance)).Destroy;");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();
      rFile.newline();
      rFile.write("R_ClearExternalPtr(rInstance);");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();

      FunctionName  = AliasName;
      FunctionName += "_destroy";

      ExportName  = "_";
      ExportName += AliasName;
      ExportName += ".destroy";

      rFile.newline();
      rFile.write("Function ");
      rFile.write(FunctionName);
      rFile.write("(args : SEXP) : SEXP; cdecl;");
      rFile.newline();
      rFile.newline();
      rFile.write("var");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("rInstance : SEXP;");
      rFile.newline();
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("args := R_CDR(args); rInstance := R_CAR(args);");
      rFile.newline();
      rFile.write(AliasName);
      rFile.write("_destroy_handler(rInstance);");
      rFile.newline();
      rFile.newline();

      Helper.writeDelphiR_Return(rFile, AdtAutoType_INT, "0");

      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();

      Helper.DelphiR_registerInterfaceRoutine(ExportName,
                                              FunctionName,
                                              1);

      // Write constructor interface code
      FunctionName  = AliasName;
      FunctionName += "_create";

      ExportName  = "_";
      ExportName += AliasName;
      ExportName += ".create";

      rFile.newline();
      rFile.write("function ");
      rFile.write(FunctionName);
      rFile.write("(args : SEXP) : SEXP; cdecl;");

      nCount = ArgumentList.size();

      Helper.DelphiR_registerInterfaceRoutine(ExportName,
                                              FunctionName,
                                              nCount);

      rFile.newline();
      rFile.newline();
      rFile.write("var");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("Context : ");
      rFile.write(pConstructorClassName);
      rFile.write(";");
      rFile.newline();

      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("arg_");
        rFile.write(rArg);
        rFile.write(" : SEXP;");
      }

      rFile.decrementIndent();
      rFile.newline();
      rFile.newline();
      rFile.write("begin");
      rFile.incrementIndent();
      rFile.newline();

      // Read .External args
      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("args := R_CDR(args); arg_");
        rFile.write(rArg);
        rFile.write(" := R_CAR(args);");
      }

      rFile.newline();
      rFile.newline();

      // Check argument types
      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        AdtAutoAttributePtrByStringMapConstIter AttrIter;

        const string& rArg = *Iter;
        string        sVar("arg_");

        sVar += rArg;

        AttrIter = AttributeByNameMap.find(rArg);

        if (AttrIter != AttributeByNameMap.end())
        {
          const AdtAutoAttribute* pAttribute = (*AttrIter).second;

          pAttribute->writeVarCheckType(rFile, DelphiSourceFileType, true, true);
          rFile.newline();
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      // Construct the object and return the instance
      rFile.write("Context := ");
      rFile.write(pConstructorClassName);
      rFile.write(".create(");
      rFile.incrementIndent();
      rFile.incrementIndent();
      rFile.newline();

      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        AdtAutoAttributePtrByStringMapConstIter AttrIter;

        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.write(", ");
          rFile.newline();
        }

        AttrIter = AttributeByNameMap.find(rArg);

        if (AttrIter != AttributeByNameMap.end())
        {
          const AdtAutoAttribute* pAttribute = (*AttrIter).second;
          bool                    bIsArray   = (pAttribute->dimensions() != 0);

          rFile.write("R_");
          rFile.write(Helper.R_AccessType(pAttribute->type()));
          rFile.write("(arg_");
          rFile.write(rArg);
          rFile.write(")");

          if (!bIsArray)
          {
            rFile.write("^");
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.write(");");
      rFile.decrementIndent();
      rFile.decrementIndent();
      rFile.newline();
      rFile.newline();

      rFile.write("R_INIT_TYPE();");
      rFile.newline();
      rFile.newline();
      rFile.write("Result := R_MakeExternalPtr(Pointer(Context), type_adt_tag, Rf_mkChar('TUsefulClass'));");
      rFile.newline();
      rFile.newline();
      rFile.write("Rf_protect(Result);");
      rFile.newline();
      rFile.write("R_RegisterCFinalizer(Result, @");
      rFile.write(AliasName);
      rFile.write("_destroy_handler);");
      rFile.newline();
      rFile.write("Rf_unprotect(1);");

      rFile.decrementIndent();
      rFile.newline();
      rFile.write("end;");
      rFile.newline();
      break;
    }

    case CppSourceFileType:
    case CppHeaderFileType:
    {
      size_t                  nCount;
      AdtStringListConstIter  Iter;
      AdtAutoHelper           Helper;

      // Write destructor interface code
      rFile.newline();
      rFile.write("EXPORT void ");
      rFile.write(AliasName);
      rFile.write("_destroy_handler(SEXP rInstance)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      Helper.writeCppR_CheckInstance(rFile, R_TypeName);
      rFile.newline();
      rFile.write(pConstructorClassName);
      rFile.write("* pContext = (");
      rFile.write(pConstructorClassName);
      rFile.write("*)R_ExternalPtrAddr(rInstance);");
      rFile.newline();
      rFile.newline();
      rFile.write("if (pContext != 0)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("delete pContext;");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.newline();
      rFile.write("R_ClearExternalPtr(rInstance);");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();

      FunctionName  = AliasName;
      FunctionName += "_destroy";

      ExportName  = "_";
      ExportName += AliasName;
      ExportName += ".destroy";

      rFile.newline();
      rFile.write("EXPORT SEXP ");
      rFile.write(FunctionName);
      rFile.write("(SEXP args)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("SEXP rInstance;");
      rFile.newline();
      rFile.write("args = CDR(args); rInstance = CAR(args);");
      rFile.newline();
      rFile.write(AliasName);
      rFile.write("_destroy_handler(rInstance);");
      rFile.newline();
      rFile.newline();

      Helper.writeCppR_Return(rFile, AdtAutoType_INT, "0");

      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();

      Helper.CppR_registerInterfaceRoutine(ExportName,
                                           FunctionName,
                                           1);

      // Write constructor interface code
      FunctionName  = AliasName;
      FunctionName += "_create";

      ExportName  = "_";
      ExportName += AliasName;
      ExportName += ".create";

      rFile.newline();
      rFile.write("EXPORT SEXP ");
      rFile.write(FunctionName);
      rFile.write("(SEXP args)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();

      nCount = ArgumentList.size();

      Helper.CppR_registerInterfaceRoutine(ExportName,
                                           FunctionName,
                                           nCount);

      rFile.write("SEXP Result = {0};");
      rFile.newline();
      rFile.write(pConstructorClassName);
      rFile.write("* pContext = 0;");
      rFile.newline();
      rFile.newline();

      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("SEXP arg_");
        rFile.write(rArg);
        rFile.write(";");
      }

      rFile.newline();
      rFile.newline();

      // Read .External args
      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.newline();
        }

        rFile.write("args = CDR(args); arg_");
        rFile.write(rArg);
        rFile.write(" = CAR(args);");
      }

      rFile.newline();
      rFile.newline();

      // Check argument types
      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        AdtAutoAttributePtrByStringMapConstIter AttrIter;

        const string& rArg = *Iter;
        string        sVar("arg_");

        sVar += rArg;

        AttrIter = AttributeByNameMap.find(rArg);

        if (AttrIter != AttributeByNameMap.end())
        {
          const AdtAutoAttribute* pAttribute = (*AttrIter).second;

          pAttribute->writeVarCheckType(rFile, CppSourceFileType, true, true);
          rFile.newline();
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.write("pContext = new ");
      rFile.write(pConstructorClassName);
      rFile.write("(");
      rFile.incrementIndent();
      rFile.incrementIndent();
      rFile.newline();

      for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
      {
        AdtAutoAttributePtrByStringMapConstIter AttrIter;

        const string& rArg = *Iter;

        if (Iter != ArgumentList.begin())
        {
          rFile.write(", ");
          rFile.newline();
        }

        AttrIter = AttributeByNameMap.find(rArg);

        if (AttrIter != AttributeByNameMap.end())
        {
          const AdtAutoAttribute* pAttribute = (*AttrIter).second;

          rFile.write(Helper.R_AccessType(pAttribute->type()));
          rFile.write("(arg_");
          rFile.write(rArg);
          rFile.write(")");

          if (pAttribute->dimensions() == 0)
          {
            rFile.write("[0]");
          }
        }
        else
        {
          // Should never happen
          FAIL();
        }
      }

      rFile.write(");");
      rFile.decrementIndent();
      rFile.decrementIndent();
      rFile.newline();
      rFile.newline();

      rFile.write("if (pContext != 0)");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("MAKE_R_EXTERNAL_PTR(Result, pContext, ");
      rFile.write(AliasName);
      rFile.write("_destroy_handler, ");
      rFile.write(R_TypeName);
      rFile.write(");");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.write("else");
      rFile.newline();
      rFile.write("{");
      rFile.incrementIndent();
      rFile.newline();
      rFile.write("Rf_error(\"ERROR: ");
      rFile.write(AliasName);
      rFile.write("_create() failed\");");
      rFile.newline();
      rFile.newline();
      Helper.writeCppR_AllocReturn(rFile, AdtAutoType_INT, "0");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      rFile.newline();
      rFile.write("return Result;");
      rFile.decrementIndent();
      rFile.newline();
      rFile.write("}");
      rFile.newline();
      break;
    }

    case JavaSourceFileType:
    case FortranSourceFileType:
    case UnknownSourceFileType:
    default:
    {
      break;
    }
  }
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::writeCommonR_Code(AdtFile& rFile) const
{
  size_t                  nCount;
  AdtStringListConstIter  Iter;
  AdtAutoHelper           Helper;
  string                  rUseArrayClassName;

  getUseArrayClassName(rUseArrayClassName);

  // requirements
  rFile.write("require(");
  rFile.write(rUseArrayClassName);
  rFile.write(")");
  rFile.newline();
  rFile.newline();

  // Destroy the object
  rFile.write(AliasName);
  rFile.write(".destroy <- function(Context)");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();

  rFile.write("return (.External('_");
  rFile.write(AliasName);
  rFile.write(".destroy', Context))");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();

  // Construct the object
  rFile.write(AliasName);
  rFile.write(".create <- function(");

  nCount = ArgumentList.size();

  // Write constructor arguments
  for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
  {
    AdtAutoAttributePtrByStringMapConstIter AttrIter;

    const string& rArg = *Iter;

    AttrIter = AttributeByNameMap.find(rArg);

    if (AttrIter != AttributeByNameMap.end())
    {
      rFile.write(rArg);

      if (nCount != 1)
      {
        rFile.write(", ");
      }
    }
    else
    {
      // Should never happen
      FAIL();
    }

    nCount--;
  }

  rFile.write(")");
  rFile.newline();
  rFile.write("{");
  rFile.incrementIndent();
  rFile.newline();

  // Construct the object
  rFile.write("return (.External('_");
  rFile.write(AliasName);
  rFile.write(".create', ");

  nCount = ArgumentList.size();

  // Write constructor arguments
  for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
  {
    AdtAutoAttributePtrByStringMapConstIter AttrIter;

    const string& rArg = *Iter;

    AttrIter = AttributeByNameMap.find(rArg);

    if (AttrIter != AttributeByNameMap.end())
    {
      const AdtAutoAttribute* pAttribute = (*AttrIter).second;

      Helper.writeR_typeCast(rFile, pAttribute->type(), rArg, rArg);

      if (nCount != 1)
      {
        rFile.write(", ");
      }
    }
    else
    {
      // Should never happen
      FAIL();
    }

    nCount--;
  }

  rFile.write("))");
  rFile.decrementIndent();
  rFile.newline();
  rFile.write("}");
  rFile.newline();
  rFile.newline();
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeConstructorArgsFile(AdtSourceFileType nDestType,
                                            const char* pDestFolder,
                                            bool bCall) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  if (bCall)
  {
    sFileName += CONSTRUCTOR_CALL_ARGS;
  }
  else
  {
    sFileName += CONSTRUCTOR_ARGS;
  }

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtStringListConstIter  Iter;
    bool                    bPrependSeperator = false;

    for (Iter = ArgumentList.begin() ; Iter != ArgumentList.end() ; ++Iter)
    {
      AdtAutoAttributePtrByStringMapConstIter AttrIter;

      const string& rArgName = *Iter;

      AttrIter = AttributeByNameMap.find(rArgName);

      if (AttrIter != AttributeByNameMap.end())
      {
        const AdtAutoAttribute* pAttribute = (*AttrIter).second;

        if (pAttribute != 0)
        {
          if (bCall)
          {
            if (bPrependSeperator)
            {
              rFile.write(", ");
              rFile.newline();
            }

            rFile.write("arg_");
            rFile.write(pAttribute->name());
          }
          else
          {
            pAttribute->writeVarDeclaration(rFile,
                                            nDestType,
                                            true,
                                            bPrependSeperator);
          }

          bPrependSeperator = true;
        }
      }
    }

    rFile.newline();
    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeConstructorLocalsFile(AdtSourceFileType nDestType,
                                              AdtStringByStringMap& rLocalsMap,
                                              const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += CONSTRUCTOR_LOCALS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    char                      sBuffer[256] = {0};
    AdtStringByStringMapIter  Iter;

    for (Iter = rLocalsMap.begin() ; Iter != rLocalsMap.end() ; ++Iter)
    {
      rFile.write(Iter->second);
      rFile.newline();
    }

    rFile.newline();
    rFile.close();
    rLocalsMap.clear();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeConstructorPhaseFiles(AdtSourceFileType nDestType,
                                              AdtStringByStringMap& rLocalsMap,
                                              const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;

  for (int cn = 1 ; cn <= MaxPhase ; cn++)
  {
    const char* ppFileTypes[2]  = {CONSTRUCTOR_SCALARS_PHASE, CONSTRUCTOR_ARRAYS_PHASE};
    bool        rIsScalar[2]    = {true, false};

    for (int cm = 0 ; cm < 2 ; cm++)
    {
      char    sBuffer[256] = {0};
      string  sFileName(AliasName);

      ::sprintf(sBuffer, "%s_%d", ppFileTypes[cm], cn);

      sFileName += sBuffer;

      if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
      {
        AdtAutoAttributePtrByIntMultimapConstIter Iter;
        AdtAutoAttributePtrByIntMultimapConstIter UpperBound = AttributeByPhaseMap.upper_bound(cn);

        for (Iter = AttributeByPhaseMap.lower_bound(cn) ; Iter != UpperBound ; ++Iter)
        {
          const AdtAutoAttribute* pAttribute = (*Iter).second;

          if ((pAttribute              != 0            ) &&
              pAttribute->withInitialisation()           &&
              (pAttribute->className() == ClassName    ) &&
              (pAttribute->isScalar()  == rIsScalar[cm]))
          {
            switch (pAttribute->mode())
            {
              case AdtAutoMode_MANUAL:
              case AdtAutoMode_AUTOINIT:
              {
                // Do nothing
                break;
              }

              default:
              case AdtAutoMode_AUTODEC:
              case AdtAutoMode_FN_ARGUMENT:
              {
                pAttribute->writeVarInitialisation(rFile, nDestType, rLocalsMap, ClassName, false);
                break;
              }
            }
          }
        }

        for (Iter = AttributeByPhaseMap.lower_bound(cn) ; Iter != UpperBound ; ++Iter)
        {
          const AdtAutoAttribute* pAttribute = (*Iter).second;

          if ((pAttribute              != 0                   ) &&
              pAttribute->withInitialisation()                  &&
              (pAttribute->className() == ClassName           ) &&
              (pAttribute->isScalar()  == rIsScalar[cm]       ) &&
              (pAttribute->mode()      == AdtAutoMode_AUTOINIT))
          {
            pAttribute->writeVarInitialisation(rFile, nDestType, rLocalsMap, ClassName, !rIsScalar[cm]);
          }
        }

        rFile.close();
      }
    }

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeArrayPlansInitFile(AdtSourceFileType nDestType,
                                           AdtStringByStringMap& rLocalsMap,
                                           const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += ARRAY_PLANS_INIT;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtAutoArray::writeCreatePlans(rFile, nDestType, ClassName, rLocalsMap);

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeArrayPlansCopyFile(AdtSourceFileType nDestType,
                                           const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += ARRAY_PLANS_COPY;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtAutoArray::writeCopyPlans(rFile, nDestType, ClassName);

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeDeclLibInterfaceMethodsFile(AdtSourceFileType nDestType,
                                                    const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += DECL_LIB_INTERFACE_METHODS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtAutoAttributePtrByStringMapConstIter Iter;

    for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeDeclLibInterfaceMethods(rFile, nDestType);
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeDeclLibInterfaceGlobalsFile(AdtSourceFileType nDestType,
                                                    const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += DECL_LIB_INTERFACE_GLOBALS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    switch (nDestType)
    {
      case DelphiSourceFileType:
      {
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        rFile.write("DECL_TYPE_TAG(");
        rFile.write(R_TypeName);
        rFile.write(")");
        rFile.newline();
        rFile.newline();
        break;
      }

      case JavaSourceFileType:
      case FortranSourceFileType:
      case UnknownSourceFileType:
      default:
      {
        FAIL();
        break;
      }
    }

    AdtAutoAttributePtrByStringMapConstIter Iter;

    for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeDeclLibInterfaceGlobals(rFile, nDestType, AliasName);
      }
    }

    for (Iter = GlobalsMap.begin() ; Iter != GlobalsMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeDeclLibInterfaceGlobals(rFile, nDestType, AliasName);
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeDeclLibInterfaceConstructorFile(AdtSourceFileType nDestType,
                                                        const char* pDestFolder,
                                                        const char* pConstructorClassName) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += DECL_LIB_INTERFACE_CONSTRUCTOR;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    writeConstructorDecl(rFile, nDestType, pConstructorClassName);

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeImplLibInterfaceConstructorFile(AdtSourceFileType nDestType,
                                                        const char* pDestFolder,
                                                        const char* pConstructorClassName) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += IMPL_LIB_INTERFACE_CONSTRUCTOR;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    writeConstructorImpl(rFile, nDestType, pConstructorClassName);

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeImplLibInterfaceMethodsFile(AdtSourceFileType nDestType,
                                                    const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += IMPL_LIB_INTERFACE_METHODS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtAutoAttributePtrByStringMapConstIter Iter;

    for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeImplLibInterfaceMethods(rFile, nDestType, ClassName, AliasName, R_TypeName);
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeImplLibInterfaceGlobalsFile(AdtSourceFileType nDestType,
                                                    const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += IMPL_LIB_INTERFACE_GLOBALS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    switch (nDestType)
    {
      case DelphiSourceFileType:
      {
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        rFile.write("IMPL_TYPE_TAG(");
        rFile.write(ClassName);
        rFile.write(")");
        rFile.newline();
        rFile.newline();
        break;
      }

      case JavaSourceFileType:
      case FortranSourceFileType:
      case UnknownSourceFileType:
      default:
      {
        FAIL();
        break;
      }
    }

    AdtAutoAttributePtrByStringMapConstIter Iter;

    for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeImplLibInterfaceGlobals(rFile, nDestType, ClassName, AliasName, R_TypeName);
      }
    }

    for (Iter = GlobalsMap.begin() ; Iter != GlobalsMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeImplLibInterfaceGlobals(rFile, nDestType, ClassName, AliasName, R_TypeName);
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeImplLibRegistrationFile(AdtSourceFileType nDestType,
                                                const char* pDestFolder,
                                                int nClassNumber) const
{
  AdtFile           rFile;
  bool              bWritten = false;
  string            sFileName(AliasName);
  AdtStringList     RegistrationCodeList;
  AdtStringListIter Iter;

  sFileName += IMPL_LIB_REGISTRATION;

  RegistrationCodeFile.close();
  ExternalsCodeFile.close();

  // Compile the registration code entries
  writeIncrementalCompileFile(RegistrationCodeBuffer,
                              nDestType,
                              pDestFolder,
                              "_reg_",
                              nClassNumber);

  readIncrementalCompileFiles(RegistrationCodeList,
                              nDestType,
                              pDestFolder,
                              "_reg_",
                              nClassNumber);


  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    const char* LibPrefix[] = {"", "lib"};

    switch (nDestType)
    {
      case DelphiSourceFileType:
      {
        AdtStringList ExternalsCodeList;
        string        sExportsFileName(AliasName);
        AdtFile       rExportsFile;

        sExportsFileName += LIB_EXPORTS;

        if (openFile(rExportsFile, pDestFolder, sExportsFileName, nDestType, true))
        {
          // Compile the externals definitions
          writeIncrementalCompileFile(ExternalsCodeBuffer,
                                      nDestType,
                                      pDestFolder,
                                      "_ext_",
                                      nClassNumber);

          readIncrementalCompileFiles(ExternalsCodeList,
                                      nDestType,
                                      pDestFolder,
                                      "_ext_",
                                      nClassNumber);

          // Write exports file
          for (Iter = ExternalsCodeList.begin() ; Iter != ExternalsCodeList.end() ; ++Iter)
          {
            const string& rExternalsCode = *Iter;

            rExportsFile.write(rExternalsCode);
            rExportsFile.newline();
          }

          rExportsFile.write("R_init_");
          rExportsFile.write(LibPrefix[0]);
          rExportsFile.write(LibName);
          rExportsFile.write(",");
          rExportsFile.newline();
          rExportsFile.write("R_init_");
          rExportsFile.write(LibPrefix[1]);
          rExportsFile.write(LibName);
          rExportsFile.newline();
          rExportsFile.close();
        }

        for (int cn = 0 ; cn < 2 ; cn++)
        {
          char    sBuffer[32] = {0};
          string  rUseArrayClassName;

          getUseArrayClassName(rUseArrayClassName);

          ::sprintf(sBuffer, "%zd", RegistrationCodeList.size());

          rFile.write("procedure R_init_");
          rFile.write(LibPrefix[cn]);
          rFile.write(LibName);
          rFile.write("(VAR pInfo : Pointer); cdecl;");
          rFile.newline();
          rFile.newline();
          rFile.write("const extMethods : array[0..");
          rFile.write(sBuffer);
          rFile.write("] of CallMethodDef = ");
          rFile.newline();
          rFile.write("(");
          rFile.incrementIndent();
          rFile.newline();

          for (Iter = RegistrationCodeList.begin() ; Iter != RegistrationCodeList.end() ; ++Iter)
          {
            const string& rRegistrationCode = *Iter;

            rFile.write(rRegistrationCode);
            rFile.newline();
          }

          rFile.write("(cmdName : nil; cmdFunc : nil; cmdNumArgs : 0;)");
          rFile.decrementIndent();
          rFile.newline();
          rFile.write(");");
          rFile.newline();
          rFile.newline();
          rFile.write("begin");
          rFile.incrementIndent();
          rFile.newline();
          rFile.write("R_SetArrayClass(ArrayClass_");
          rFile.write(rUseArrayClassName);
          rFile.write(");");
          rFile.newline();
          rFile.write("R_registerRoutines(pInfo, nil, nil, nil, @extMethods);");
          rFile.decrementIndent();
          rFile.newline();
          rFile.write("end;");
          rFile.newline();
          rFile.newline();
          rFile.newline();
        }
        break;
      }

      case CppSourceFileType:
      case CppHeaderFileType:
      {
        rFile.write("static const R_CallMethodDef extMethods[] = ");
        rFile.newline();
        rFile.write("{");
        rFile.incrementIndent();
        rFile.newline();

        for (Iter = RegistrationCodeList.begin() ; Iter != RegistrationCodeList.end() ; ++Iter)
        {
          const string& rRegistrationCode = *Iter;

          rFile.write(rRegistrationCode);
          rFile.newline();
        }

        rFile.write("0");
        rFile.decrementIndent();
        rFile.newline();
        rFile.write("};");
        rFile.newline();
        rFile.newline();
        rFile.newline();

        for (int cn = 0 ; cn < 2 ; cn++)
        {
          string  rUseArrayClassName;

          getUseArrayClassName(rUseArrayClassName);

          rFile.write("EXPORT void R_init_");
          rFile.write(LibPrefix[cn]);
          rFile.write(LibName);
          rFile.write("(DllInfo* pInfo)");
          rFile.newline();
          rFile.write("{");
          rFile.incrementIndent();
          rFile.newline();
          rFile.write("R_SetArrayClass(ArrayClass_");
          rFile.write(rUseArrayClassName);
          rFile.write(");");
          rFile.newline();
          rFile.write("R_registerRoutines(pInfo, 0, 0, 0, extMethods);");
          rFile.decrementIndent();
          rFile.newline();
          rFile.write("}");
          rFile.newline();
          rFile.newline();
          rFile.newline();
        }
        break;
      }

      case JavaSourceFileType:
      case FortranSourceFileType:
      case UnknownSourceFileType:
      default:
      {
        FAIL();
        break;
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeArrayPlansFile(AdtSourceFileType nDestType,
                                       const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += ARRAY_PLANS;

  if (openFile(rFile, pDestFolder, sFileName, nDestType, true))
  {
    AdtAutoArray::writeArrayPlans(rFile, nDestType, ClassName);
    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeRInterfaceFile(const char* pDestFolder) const
{
  AdtFile rFile;
  bool    bWritten = false;
  string  sFileName(AliasName);

  sFileName += "_R_interface.r";

  if (openFile(rFile, pDestFolder, sFileName, true))
  {
    writeCommonR_Code(rFile);

    AdtAutoAttributePtrByStringMapConstIter Iter;

    for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeRInterface(rFile, ClassName, AliasName);
      }
    }

    for (Iter = GlobalsMap.begin() ; Iter != GlobalsMap.end() ; ++Iter)
    {
      const AdtAutoAttribute* pAttribute = (*Iter).second;

      if ((pAttribute != 0) && !pAttribute->noInterface() && !isInherited(pAttribute))
      {
        pAttribute->writeRInterface(rFile, ClassName, AliasName);
      }
    }

    rFile.close();

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::checkDependencies() const
{
  bool                                    bOk = true;
  AdtAutoAttributePtrByStringMapConstIter Iter;

  for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
  {
    AdtAutoAttribute* pAttribute = (*Iter).second;

    if (!pAttribute->checkDependencies(AttributeByNameMap, &GlobalsMap))
    {
      bOk = false;
    }

    if (pAttribute->isRagged() && (pAttribute->dimensions() > MaxCounter))
    {
      MaxCounter = pAttribute->dimensions();
    }
  }

  return (bOk);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::buildParentConstructorCallArgsFileName(string& rFileName) const
{
  rFileName = AliasName + CONSTRUCTOR_CALL_ARGS;
}

//  ----------------------------------------------------------------------------

AdtAutoClass::AdtAutoClass()
 : UtlReferenceCount(),
   InheritedMap(),
   AttributeByNameMap(),
   AttributeByPhaseMap(),
   DefinedPhasesMap(),
   ArgumentList(),
   ClassName(),
   AliasName(),
   ParentClassName(),
   R_TypeName(),
   ParentConstructorCallArgsFileName()
{
  NoInterface = false;
  Phase       = 1;
  MaxPhase    = 1;
  MaxCounter  = -1;
  Mode        = AdtAutoMode_MANUAL;
}

//  ----------------------------------------------------------------------------

AdtAutoClass::~AdtAutoClass()
{
  reset();
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::reset()
{
  AdtAutoAttributePtrByStringMapIter Iter;

  for (Iter = AttributeByNameMap.begin() ; Iter != AttributeByNameMap.end() ; ++Iter)
  {
    AdtAutoAttribute* pAttribute = (*Iter).second;

    UtlReleaseReference(pAttribute);
  }

  InheritedMap.clear();
  AttributeByNameMap.clear();
  AttributeByPhaseMap.clear();
  DefinedPhasesMap.clear();
  ArgumentList.clear();
  LibName.clear();

  NoInterface                       = false;
  Phase                             = 1;
  MaxPhase                          = 1;
  MaxCounter                        = -1;
  Mode                              = AdtAutoMode_MANUAL;
  ClassName                         = "";
  AliasName                         = "";
  ParentClassName                   = "";
  R_TypeName                        = "";
  ParentConstructorCallArgsFileName = "";
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::mode(AdtAutoMode nMode,
                        const char* pFileName,
                        int nLineNumber)
{
  Mode = nMode;
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::phase(int nPhase,
                         const char* pFileName,
                         int nLineNumber)
{
  if (DefinedPhasesMap.find(nPhase) == DefinedPhasesMap.end())
  {
    if (nPhase < 1)
    {
      ::printf("WARNING:Phase %d in file %s on line %d must be greater than or equal to 1\n",
               nPhase,
               pFileName,
               nLineNumber);
    }
    else if (nPhase > MaxPhase)
    {
      if (nPhase > MaxPhase + 1)
      {
        // WARNING message
        ::printf("WARNING:Phase %d skips %d undefined phases in file %s on line %d\n",
                 nPhase,
                 nPhase - MaxPhase,
                 pFileName,
                 nLineNumber);
      }

      MaxPhase = nPhase;
    }

    DefinedPhasesMap[nPhase] = nPhase;
  }

  Phase = nPhase;
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::noInterface(bool bNoInterface,
                               const char* pFileName,
                               int nLineNumber)
{
  NoInterface = bNoInterface;
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::classNameAndAlias(const char* pClassName,
                                     const char* pAlias)
{
  if (pClassName != 0)
  {
    ClassName   = pClassName;
    R_TypeName  = pClassName;

    if (pAlias != 0)
    {
      AliasName = pAlias;
    }
    else
    {
      AliasName = ClassName;
    }
  }
}

//  ----------------------------------------------------------------------------

AdtAutoScalar* AdtAutoClass::addScalar(const char* pName,
                                       AdtAutoType nType,
                                       AdtAutoDir nDir,
                                       const char* pFileName,
                                       int nLineNumber)
{
  AdtAutoScalar* pAttribute = 0;

  if (AttributeByNameMap.find(pName) == AttributeByNameMap.end())
  {
    pAttribute = new AdtAutoScalar(pName,
                                   ClassName,
                                   nType,
                                   Mode,
                                   nDir,
                                   Phase,
                                   NoInterface,
                                   AttributeDefsEnabled,
                                   pFileName,
                                   nLineNumber);

    if (pAttribute != 0)
    {
      AttributeByNameMap[pAttribute->name()] = pAttribute;
      AttributeByPhaseMap.insert(AdtAutoAttributePtrIntPair(Phase, pAttribute));
    }

    if (Mode == AdtAutoMode_AUTOINIT)
    {
      ArgumentList.push_back(pName);
    }
  }
  else
  {
    ::printf("ERROR:Duplicate definition of %s in file %s on line %d\n", pName, pFileName, nLineNumber);
  }

  return (pAttribute);
}

//  ----------------------------------------------------------------------------

AdtAutoArray* AdtAutoClass::addArray(const char* pName,
                                     AdtAutoType nType,
                                     AdtAutoDir nDir,
                                     int nDimensions,
                                     const char* pFileName,
                                     int nLineNumber)
{
  AdtAutoArray* pAttribute = 0;

  if (AttributeByNameMap.find(pName) == AttributeByNameMap.end())
  {
    pAttribute = new AdtAutoArray(pName,
                                  ClassName,
                                  nType,
                                  Mode,
                                  nDir,
                                  Phase,
                                  NoInterface,
                                  AttributeDefsEnabled,
                                  nDimensions,
                                  pFileName,
                                  nLineNumber);

    if (pAttribute != 0)
    {
      AttributeByNameMap[pAttribute->name()] = pAttribute;
      AttributeByPhaseMap.insert(AdtAutoAttributePtrIntPair(Phase, pAttribute));
    }

    if (Mode == AdtAutoMode_AUTOINIT)
    {
      ArgumentList.push_back(pName);
    }
  }
  else
  {
    ::printf("ERROR:Duplicate definition of %s in file %s on line %d\n",
             pName,
             pFileName,
             nLineNumber);
  }

  return (pAttribute);
}

//  ----------------------------------------------------------------------------

AdtAutoFunction* AdtAutoClass::addFunction(const char* pName,
                                           AdtAutoType nType,
                                           AdtAutoDir nDir,
                                           bool bIsVirtual,
                                           const char* pFileName,
                                           int nLineNumber)
{
  AdtAutoFunction*                    pAttribute = 0;
  AdtAutoAttributePtrByStringMapIter  Iter       = AttributeByNameMap.find(pName);

  if (Iter == AttributeByNameMap.end())
  {
    pAttribute = new AdtAutoFunction(pName,
                                     ClassName,
                                     nType,
                                     nDir,
                                     pFileName,
                                     nLineNumber);

    if (pAttribute != 0)
    {
      AttributeByNameMap[pAttribute->name()] = pAttribute;
      AttributeByPhaseMap.insert(AdtAutoAttributePtrIntPair(0, pAttribute));
    }
  }
  else
  {
    if (bIsVirtual)
    {
      AdtAutoAttribute*  pAttr = Iter->second;

      if (pAttr->attributeType() == AttributeTypeFunction)
      {
        pAttribute = (AdtAutoFunction*)pAttr;
        pAttribute->reset();
      }
      else
      {
        ::printf("ERROR:Function definition of %s in file %s on line %d masked by another object\n",
                 pName,
                 pFileName,
                 nLineNumber);
      }
    }
    else
    {
      ::printf("ERROR:Duplicate definition of %s in file %s on line %d\nIf using BoundsCheck make sure methods are virtual\n",
               pName,
               pFileName,
               nLineNumber);
    }
  }

  return (pAttribute);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeConstructorArgsFiles(AdtSourceFileType nDestType,
                                             const char* pDestFolder) const
{
  bool bWritten = false;

  if (pDestFolder != 0)
  {
    writeConstructorArgsFile(nDestType, pDestFolder, false);
    writeConstructorArgsFile(nDestType, pDestFolder, true);

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

bool AdtAutoClass::writeAutomationFiles(AdtSourceFileType nDestType,
                                        const char* pDestFolder,
                                        const char* pDestIncludeFolder,
                                        const char* pConstructorClassName,
                                        int nClassNumber) const
{
  bool bWritten = false;

  if (pDestFolder != 0)
  {
    AdtStringByStringMap  LocalsMap;

    clearRegistrationCode();
    checkDependencies();

    writeConstructorArgsFile(nDestType, pDestIncludeFolder, false);
    writeConstructorArgsFile(nDestType, pDestIncludeFolder, true);
    writeConstructorPhaseFiles(nDestType, LocalsMap, pDestIncludeFolder);
    writeDeclLibInterfaceMethodsFile(nDestType, pDestIncludeFolder);
    writeDeclLibInterfaceConstructorFile(nDestType, pDestIncludeFolder, pConstructorClassName);
    writeImplLibInterfaceConstructorFile(nDestType, pDestIncludeFolder, pConstructorClassName);
    writeImplLibInterfaceMethodsFile(nDestType, pDestIncludeFolder);
    writeImplLibInterfaceGlobalsFile(nDestType, pDestIncludeFolder);
    writeImplLibRegistrationFile(nDestType, pDestIncludeFolder, nClassNumber);
    writeArrayPlansInitFile(nDestType, LocalsMap, pDestIncludeFolder);
    writeArrayPlansCopyFile(nDestType, pDestIncludeFolder);
    writeConstructorLocalsFile(nDestType, LocalsMap, pDestIncludeFolder);
    writeDeclLibInterfaceGlobalsFile(nDestType, pDestIncludeFolder);
    writeArrayPlansFile(nDestType, pDestIncludeFolder);
    writeRInterfaceFile(pDestFolder);

    bWritten = true;
  }

  return (bWritten);
}

//  ----------------------------------------------------------------------------

void AdtAutoClass::inheritFrom(const AdtAutoClass* pParentClass)
{
  if (pParentClass != 0)
  {
    // Copy AttributeByNameMap
    AdtAutoAttributePtrByStringMapConstIter   AttrByNameIter;

    for (AttrByNameIter = pParentClass->AttributeByNameMap.begin() ;
         AttrByNameIter != pParentClass->AttributeByNameMap.end() ;
         ++AttrByNameIter)
    {
      const AdtAutoAttribute* pAttr = AttrByNameIter->second;

      if (pAttr != 0)
      {
        pAttr->lock();
        inherit(pAttr);
      }

      AttributeByNameMap.insert(*AttrByNameIter);
    }

    // Copy AttributeByPhaseMap
    AdtAutoAttributePtrByIntMultimapConstIter AttrByPhaseIter;

    for (AttrByPhaseIter = pParentClass->AttributeByPhaseMap.begin() ;
         AttrByPhaseIter != pParentClass->AttributeByPhaseMap.end() ;
         ++AttrByPhaseIter)
    {
      const AdtAutoAttribute* pAttr = AttrByPhaseIter->second;

      if (pAttr != 0)
      {
        pAttr->lock();
        inherit(pAttr);
      }

      AttributeByPhaseMap.insert(*AttrByPhaseIter);
    }

    // Copy DefinedPhasesMap
    DefinedPhasesMap.insert(pParentClass->DefinedPhasesMap.begin(),
                            pParentClass->DefinedPhasesMap.end());

    // Copy ArgList
    ArgumentList.insert(ArgumentList.begin(),
                        pParentClass->ArgumentList.begin(),
                        pParentClass->ArgumentList.end());

    // Init parent contructor call args file name
    pParentClass->buildParentConstructorCallArgsFileName(ParentConstructorCallArgsFileName);

    ParentClassName = pParentClass->ClassName;
    R_TypeName      = pParentClass->R_TypeName;
  }
}
