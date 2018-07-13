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
//    adtR.pas
//
//  Purpose:
//    This file implements R interface related code for the ADLib library.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
unit adtR;

interface

uses
  Classes,
  SysUtils,
  Raccess,
  adtcommon,
  adtalloc,
  adtarray;

type
  R_UseArrayClass = (ArrayClass_offarray, ArrayClass_Oarray);

  function R_LONGBOOL(x : SEXP) : plongbool; inline;
  function R_RAWBOOL(x : SEXP) : pboolean; inline;
  function R_RAWCHAR(x : SEXP) : pshortint; inline;

  //  ----------------------------------------------------------------------------
  //  functions to determine R type from array type
  //  ----------------------------------------------------------------------------
  function RType(rArray : ARRAY_1I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_2I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_3I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_4I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_5I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_6I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_7I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_8I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_9I) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_10I) : SEXPTYPE ; overload ; inline;

  //  ----------------------------------------------------------------------------

  function RType(rArray : ARRAY_1D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_2D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_3D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_4D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_5D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_6D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_7D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_8D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_9D) : SEXPTYPE ; overload ; inline;
  function RType(rArray : ARRAY_10D) : SEXPTYPE ; overload ; inline;

  //  ----------------------------------------------------------------------------

  function RTypeName(rArray : ARRAY_1I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_2I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_3I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_4I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_5I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_6I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_7I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_8I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_9I) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_10I) : AnsiString ; overload ; inline;

  //  ----------------------------------------------------------------------------

  function RTypeName(rArray : ARRAY_1D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_2D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_3D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_4D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_5D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_6D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_7D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_8D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_9D) : AnsiString ; overload ; inline;
  function RTypeName(rArray : ARRAY_10D) : AnsiString ; overload ; inline;


  //  ----------------------------------------------------------------------------
  //  R Interface helper functions used to simplify interface code
  //  ----------------------------------------------------------------------------
  function R_ImplGetter(rAllocator : AdtMemAllocator;
                        bNoTranslation : boolean;
                        pArray : pchar;
                        pName : AnsiString;
                        sArgList : SEXP;
                        pFileName : AnsiString;
                        pLineNumber : AnsiString) : SEXP;

  function R_ImplSetter(rAllocator : AdtMemAllocator;
                        bNoTranslation : boolean;
                        pArray : pchar;
                        pName : AnsiString;
                        sSrcArg : SEXP;
                        sArgList : SEXP;
                        pFileName : AnsiString;
                        pLineNumber : AnsiString) : SEXP;

  procedure R_CheckArgument(pName : AnsiString;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString;
                            nDims : longint;
                            pCoords : PAdtArrayCoord;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE);overload;

  procedure R_CheckArgument(pName : AnsiString;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString;
                            nDims: longint;
                            Args: Array of const);overload;

  procedure R_CheckArgument(pName : AnsiString;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString);overload;

  function R_CreateArray(nDims : longint; pCoords : PAdtArrayCoord; nType : SEXPTYPE) : SEXP;overload;

  function R_CreateArray(nDims : longint; nType : SEXPTYPE; Args: Array of const) : SEXP;overload;

  function R_Scalar(nResult : longint) : SEXP;overload;

  function R_Scalar(dResult : double) : SEXP;overload;

  function R_Scalar(bResult : longbool) : SEXP;overload;

  function R_Scalar(cResult : char) : SEXP;overload;

  function R_Empty() : SEXP;

  procedure R_SetArrayClass(nClass : R_UseArrayClass);


implementation

  var
    DropNegativeSymbol  : SEXP            = nil;
    OffsetSymbol        : SEXP            = nil;
    ArrayClass          : R_UseArrayClass = ArrayClass_offarray;

  //  ----------------------------------------------------------------------------

  procedure _log_error(sMsg : AnsiString); public name 'log_error';

  begin
    Rf_error(pchar(sMsg));
  end;

  //  ----------------------------------------------------------------------------

  procedure _log_warning(sMsg : AnsiString); public name 'log_warning';

  begin
    Rf_warning(pchar(sMsg));
  end;

  //  ----------------------------------------------------------------------------

  function R_LONGBOOL(x : SEXP) : plongbool; inline;

  begin
    R_LONGBOOL := plongbool(R_LOGICAL(x));
  end;

  //  ----------------------------------------------------------------------------

  function R_RAWBOOL(x : SEXP) : pboolean; inline;

  begin
    R_RAWBOOL := pboolean(R_RAW(x));
  end;

  //  ----------------------------------------------------------------------------

  function R_RAWCHAR(x : SEXP) : pshortint; inline;

  begin
    R_RAWCHAR := pshortint(R_RAW(x));
  end;

  //  ----------------------------------------------------------------------------

  function RType(rArray : ARRAY_1I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_2I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_3I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_4I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_5I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_6I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_7I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_8I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_9I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  function RType(rArray : ARRAY_10I) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := INTSXP;
  end;

  //  ----------------------------------------------------------------------------

  function RType(rArray : ARRAY_1D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_2D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_3D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_4D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_5D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_6D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_7D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_8D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_9D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  function RType(rArray : ARRAY_10D) : SEXPTYPE ; overload ; inline;

  begin
    rArray  := rArray;
    RType   := REALSXP;
  end;

  //  ----------------------------------------------------------------------------

  function RTypeName(rArray : ARRAY_1I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_2I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_3I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_4I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_5I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_6I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_7I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_8I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_9I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  function RTypeName(rArray : ARRAY_10I) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'INTSXP';
  end;

  //  ----------------------------------------------------------------------------

  function RTypeName(rArray : ARRAY_1D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_2D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_3D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_4D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_5D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_6D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_7D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_8D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_9D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  function RTypeName(rArray : ARRAY_10D) : AnsiString ; overload ; inline;

  begin
    rArray    := rArray;
    RTypeName := 'REALSXP';
  end;

  //  ----------------------------------------------------------------------------

  function ReadIndices(sArgList : SEXP; pIndices : plongint; nArgs : longint; var rErrorIndex : longint) : boolean;

  var
    bRead   : boolean;
    cn      : longint;
    Element : SEXP;
    dVal    : double;
    nVal    : longint;

  begin
    bRead := true;

    // Read indices from argument list
    for cn := 0 to nArgs - 1 do
    begin
      Element := R_VECTOR_ELT(sArgList, cn);

      if (Rf_isIntegerOrFactor(Element)) then
      begin
        pIndices[cn] := R_INTEGER(Element)[0];
      end
      else if (Rf_isReal(Element)) then
      begin
        dVal := R_REAL(Element)[0];
        nVal := trunc(dVal);

        if ((dVal - nVal) <> 0) then
        begin
          bRead       := false;
          rErrorIndex := cn;
          break;
        end
        else
        begin
          pIndices[cn] := nVal;
        end;
      end
      else
      begin
        bRead       := false;
        rErrorIndex := cn;
        break;
      end;
    end;

    ReadIndices := bRead;
  end;

  //  ----------------------------------------------------------------------------
  //  R Interface helper functions used to simplify interface code
  //  ----------------------------------------------------------------------------
  function R_ImplGetter(rAllocator : AdtMemAllocator;
                        bNoTranslation : boolean;
                        pArray : pchar;
                        pName : AnsiString;
                        sArgList : SEXP;
                        pFileName : AnsiString;
                        pLineNumber : AnsiString) : SEXP;

  var
    pResult       : SEXP;
    nErrorIndex   : longint;
    nArgs         : longint;
    aIndices      : array[0..ADLIB_MAX_COORDS - 1] of longint;
    aCoords       : array[0..ADLIB_MAX_COORDS - 1] of AdtArrayCoord;
    pInfo         : PAdtArrayInfo;
    nCoords       : longint;
    pActor        : PAdtArrayPlanActor;
    pData         : pchar;
    pResultData   : pchar;
    pLB           : plongbool;
    pCh           : pchar;
    pInt          : plongint;
    pReal         : pdouble;
    pSliceArray   : pchar;
    Emessage      : AnsiString;
    pSliceInfo    : PAdtArrayInfo;
    nSliceCoords  : longint;

  begin
    pResult := nil;

    if (Rf_isNewList(sArgList)) then
    begin
      nArgs       := Rf_length(sArgList);
      pInfo       := AdtArrayPlanActor_arrayInfo(rAllocator, pArray);
      nCoords     := pInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);
      nErrorIndex := 0;

      if ((nArgs > nCoords) or (nArgs > ADLIB_MAX_COORDS)) then
      begin
        Rf_error('ERROR: Too many arguments in list of arguments passed in call to getter for %s. See line %s in file %s', pchar(pName), pchar(pLineNumber), pchar(pFileName));
      end;

      // Read indices from argument list
      if (not ReadIndices(sArgList, aIndices, nArgs, nErrorIndex)) then
      begin
        Rf_error('ERROR: Indexing argument %d in the getter argument list is not an integer for %s. See line %s in file %s', nErrorIndex + 2, pchar(pName), pchar(pLineNumber), pchar(pFileName));
      end;

      case pInfo^.VarType of
        AdtVarType_INT,
        AdtVarType_DOUBLE,
        AdtVarType_LONGBOOL,
        AdtVarType_CHAR,
        AdtVarType_UCHAR,
        AdtVarType_BOOL:
        begin
          if (nArgs = 0) then
          begin
            try
              begin
                pResultData := nil;

                // Full array get operation
                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    pResult     := R_CreateArray(nCoords, aCoords, INTSXP);
                    pResultData := pchar(R_INTEGER(pResult));
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    pResult     := R_CreateArray(nCoords, aCoords, REALSXP);
                    pResultData := pchar(R_REAL(pResult));
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    pResult     := R_CreateArray(nCoords, aCoords, LGLSXP);
                    pResultData := pchar(R_LOGICAL(pResult));
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    pResult     := R_CreateArray(nCoords, aCoords, RAWSXP);
                    pResultData := pchar(R_RAW(pResult));
                  end;
                else
                  // Do nothing
                end;

                if (pResultData <> nil) then
                begin
                  if (bNoTranslation) then
                  begin
                    Move(firstData(pInfo^)[0], pResultData[0], lengthOfData(pInfo^) * SizeOf(char));
                  end
                  else
                  begin
                    AdtArrayPlanActor_ADlib_to_R(rAllocator, pArray, pResultData);
                  end;
                end;
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplGetter threw a runtime exception, %s', pchar(Emessage));
              end;
            end;
          end
          else if (nArgs = nCoords) then
          begin
            pActor := nil;

            try
              begin
                // scalar element get operation
                pData := pInfo^.Actor.indexArray(aIndices,
                                                 nArgs,
                                                 pArray,
                                                 pInfo^.SizeOf,
                                                 pActor);

                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    pInt    := plongint(pData);
                    pResult := R_Scalar(pInt^);
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    pReal   := pdouble(pData);
                    pResult := R_Scalar(pReal^);
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    pLB     := plongbool(pData);
                    pResult := R_Scalar(pLB^);
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    pCh     := pchar(pData);
                    pResult := R_Scalar(pCh^);
                  end;
                else
                  // Do nothing
                end;
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplGetter threw a runtime exception, %s', pchar(Emessage));
              end;
            end;
          end
          else
          begin
            pSliceArray := nil;

            try
              begin
                // Slice array get operation
                pSliceArray := AdtArrayPlanActor_createSlice(rAllocator,
                                                             pArray,
                                                             aIndices,
                                                             nArgs);

                pSliceInfo    := AdtArrayPlanActor_arrayInfo(rAllocator, pSliceArray);
                nSliceCoords  := pSliceInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);
                pResultData   := nil;

                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    pResult     := R_CreateArray(nSliceCoords, aCoords, INTSXP);
                    pResultData := pchar(R_INTEGER(pResult));
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    pResult     := R_CreateArray(nSliceCoords, aCoords, REALSXP);
                    pResultData := pchar(R_REAL(pResult));
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    pResult     := R_CreateArray(nSliceCoords, aCoords, LGLSXP);
                    pResultData := pchar(R_LOGICAL(pResult));
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    pResult     := R_CreateArray(nSliceCoords, aCoords, RAWSXP);
                    pResultData := pchar(R_RAW(pResult));
                  end;
                else
                  // Do nothing
                end;

                if (pResultData <> nil) then
                begin
                  if (bNoTranslation) then
                  begin
                    Move(firstData(pSliceInfo^)[0], pResultData[0], lengthOfData(pSliceInfo^) * SizeOf(char));
                  end
                  else
                  begin
                    AdtArrayPlanActor_ADlib_to_R(rAllocator, pSliceArray, pResultData);
                  end;
                end;

                rAllocator.free(pSliceArray);
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplGetter threw a runtime exception, %s', pchar(Emessage));

                if (pSliceArray <> nil) then
                begin
                  rAllocator.free(pSliceArray);
                end;
              end;
            end;
          end;
        end;
      else
        Rf_error('ERROR: R_ImplGetter called on array of type %s not supported in R\n', varTypeName(pInfo^.VarType));
      end;
    end
    else
    begin
      Rf_error('ERROR: Expecting list of arguments in call to getter for %s. See line %s in file %s', pchar(pName), pchar(pLineNumber), pchar(pFileName));
    end;

    R_ImplGetter := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_ImplSetter(rAllocator : AdtMemAllocator;
                        bNoTranslation : boolean;
                        pArray : pchar;
                        pName : AnsiString;
                        sSrcArg : SEXP;
                        sArgList : SEXP;
                        pFileName : AnsiString;
                        pLineNumber : AnsiString) : SEXP;

  var
    nErrorIndex     : longint;
    nArgs           : longint;
    aIndices        : array[0..ADLIB_MAX_COORDS] of longint;
    aCoords         : array[0..ADLIB_MAX_COORDS] of AdtArrayCoord;
    pInfo           : PAdtArrayInfo;
    nCoords         : longint;
    Emessage        : AnsiString;
    pActor          : PAdtArrayPlanActor;
    pSliceArray     : pchar;
    pData           : pchar;
    pInt            : plongint;
    pReal           : pdouble;
    pLB             : plongbool;
    pRaw            : pbyte;
    pSrcArgData     : pchar;
    nSrcArgType     : SEXPTYPE;
    pSrcArgTypeName : pchar;

    pSliceInfo      : PAdtArrayInfo;
    nSliceCoords    : longint;

  begin
    if (Rf_isNewList(sArgList)) then
    begin
      nErrorIndex := 0;
      nArgs       := Rf_length(sArgList);
      pInfo       := AdtArrayPlanActor_arrayInfo(rAllocator, pArray);
      nCoords     := pInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);

      if ((nArgs > nCoords) or (nArgs > ADLIB_MAX_COORDS)) then
      begin
        Rf_error('ERROR: Too many arguments in list of arguments passed in call to setter for %s. See line %s in file %s', pchar(pName), pchar(pLineNumber), pchar(pFileName));
      end;

      // Read indices from argument list
      if (not ReadIndices(sArgList, aIndices, nArgs, nErrorIndex)) then
      begin
        Rf_error('ERROR: Indexing argument %d in the setter argument list is not an integer for %s. See line %s in file %s', nErrorIndex + 1, pchar(pName), pchar(pLineNumber), pchar(pFileName));
      end;

      case pInfo^.VarType of
        AdtVarType_INT,
        AdtVarType_DOUBLE,
        AdtVarType_LONGBOOL,
        AdtVarType_CHAR,
        AdtVarType_UCHAR,
        AdtVarType_BOOL:
        begin
          if (nArgs = 0) then
          begin
            try
              begin
                pSrcArgData     := nil;
                nSrcArgType     := NILSXP;
                pSrcArgTypeName := '';

                // Full array set operation
                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    pSrcArgData     := pchar(R_INTEGER(sSrcArg));
                    nSrcArgType     := INTSXP;
                    pSrcArgTypeName := 'INTSXP';
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    pSrcArgData     := pchar(R_REAL(sSrcArg));
                    nSrcArgType     := REALSXP;
                    pSrcArgTypeName := 'REALSXP';
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    pSrcArgData     := pchar(R_LOGICAL(sSrcArg));
                    nSrcArgType     := LGLSXP;
                    pSrcArgTypeName := 'LGLSXP';
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    pSrcArgData     := pchar(R_RAW(sSrcArg));
                    nSrcArgType     := RAWSXP;
                    pSrcArgTypeName := 'RAWSXP';
                  end;
                else
                  // Do nothing
                end;

                if (pSrcArgData <> nil) then
                begin
                  R_CheckArgument(pName,
                                  sSrcArg,
                                  pFileName,
                                  pLineNumber,
                                  nCoords,
                                  aCoords,
                                  pSrcArgTypeName,
                                  nSrcArgType);

                  if (bNoTranslation) then
                  begin
                    Move(pSrcArgData[0], firstData(pInfo^)[0], lengthOfData(pInfo^) * SizeOf(char));
                  end
                  else
                  begin
                    AdtArrayPlanActor_R_to_ADlib(rAllocator, pSrcArgData, pArray);
                  end;
                end;
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplSetter threw a runtime exception, %s', pchar(Emessage));
              end;
            end;
          end
          else if (nArgs = nCoords) then
          begin
            pActor := nil;

            try
              begin
                // scalar element set operation
                pData := pInfo^.Actor.indexArray(aIndices,
                                                 nArgs,
                                                 pArray,
                                                 pInfo^.SizeOf,
                                                 pActor);

                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    R_CheckArgument(pName,
                                    sSrcArg,
                                    pFileName,
                                    pLineNumber,
                                    0,
                                    aCoords,
                                    'INTSXP',
                                    INTSXP);

                    pInt    := plongint(pData);
                    pInt[0] := R_INTEGER(sSrcArg)[0];
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    R_CheckArgument(pName,
                                    sSrcArg,
                                    pFileName,
                                    pLineNumber,
                                    0,
                                    aCoords,
                                    'REALSXP',
                                    REALSXP);

                    pReal     := pdouble(pData);
                    pReal[0]  := R_REAL(sSrcArg)[0];
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    R_CheckArgument(pName,
                                    sSrcArg,
                                    pFileName,
                                    pLineNumber,
                                    0,
                                    aCoords,
                                    'LGLSXP',
                                    LGLSXP);

                    pLB     := plongbool(pData);
                    pLB[0]  := R_LOGICAL(sSrcArg)[0];
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    R_CheckArgument(pName,
                                    sSrcArg,
                                    pFileName,
                                    pLineNumber,
                                    0,
                                    aCoords,
                                    'RAWSXP',
                                    RAWSXP);

                    pRaw    := pbyte(pData);
                    pRaw[0] := R_RAW(sSrcArg)[0];
                  end;
                else
                  // Do nothing
                end;
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplSetter threw a runtime exception, %s', pchar(Emessage));
              end;
            end;
          end
          else
          begin
            pSliceArray := nil;

            try
              begin
                // Slice array get operation
                pSliceArray     := AdtArrayPlanActor_createSlice(rAllocator,
                                                                 pArray,
                                                                 aIndices,
                                                                 nArgs);

                pSliceInfo      := AdtArrayPlanActor_arrayInfo(rAllocator, pSliceArray);
                nSliceCoords    := pSliceInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS, bNoTranslation);
                pSrcArgData     := nil;
                nSrcArgType     := NILSXP;
                pSrcArgTypeName := '';

                case (pInfo^.VarType) of
                  AdtVarType_INT:
                  begin
                    pSrcArgData     := pchar(R_INTEGER(sSrcArg));
                    nSrcArgType     := INTSXP;
                    pSrcArgTypeName := 'INTSXP';
                  end;

                  AdtVarType_DOUBLE:
                  begin
                    pSrcArgData     := pchar(R_REAL(sSrcArg));
                    nSrcArgType     := REALSXP;
                    pSrcArgTypeName := 'REALSXP';
                  end;

                  AdtVarType_LONGBOOL:
                  begin
                    pSrcArgData     := pchar(R_LOGICAL(sSrcArg));
                    nSrcArgType     := LGLSXP;
                    pSrcArgTypeName := 'LGLSXP';
                  end;

                  AdtVarType_CHAR,
                  AdtVarType_UCHAR,
                  AdtVarType_BOOL:
                  begin
                    pSrcArgData     := pchar(R_RAW(sSrcArg));
                    nSrcArgType     := RAWSXP;
                    pSrcArgTypeName := 'RAWSXP';
                  end;
                else
                  // Do nothing
                end;

                if (pSrcArgData <> nil) then
                begin
                  R_CheckArgument(pName,
                                  sSrcArg,
                                  pFileName,
                                  pLineNumber,
                                  nSliceCoords,
                                  aCoords,
                                  pSrcArgTypeName,
                                  nSrcArgType);

                  if (bNoTranslation) then
                  begin
                    Move(pSrcArgData[0], firstData(pSliceInfo^)[0], lengthOfData(pSliceInfo^) * SizeOf(char));
                  end
                  else
                  begin
                    AdtArrayPlanActor_R_to_ADlib(rAllocator, pSrcArgData, pSliceArray);
                  end;
                end;

                rAllocator.free(pSliceArray);
              end;
            except
              on E: Exception do
              begin
                Emessage := E.message;

                Rf_error('ERROR: R_ImplSetter threw a runtime exception, %s', pchar(Emessage));
              end;
            end;
          end;
        end;
      else
        Rf_error('ERROR: R_ImplSetter called on array of type %s not supported in R\n', varTypeName(pInfo^.VarType));
      end;
    end
    else
    begin
      Rf_error('ERROR: Expecting list of arguments in call to setter for %s. See line %s in file %s', pchar(pName), pchar(pLineNumber), pchar(pFileName));
    end;

    R_ImplSetter := R_Empty();
  end;

  //  ----------------------------------------------------------------------------

  procedure R_CheckArgument(pName : AnsiString;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString;
                            nDims : longint;
                            pCoords : PAdtArrayCoord;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE);overload;

  var
    nArgLength      : longint;
    cn              : longint;
    nSize           : longint;
    bNegativeOrZero : boolean;
    bOarray         : boolean;
    nLowerBound     : longint;
    nUpperBound     : longint;

  begin
    nArgLength := Rf_length(Argument);

    if (R_TYPEOF(Argument) <> nRequiredType) then
    begin
      Rf_error('ERROR: %s must be of type %s. See line %s in file %s',
               pchar(pName),
               pchar(pRequiredTypeName),
               pchar(pLineNumber),
               pchar(pFileName));
    end;

    if (nDims < 1) then
    begin
      // Expect scalar
      if (nArgLength > 1) then
      begin
        Rf_warning('WARNING: Scalar expected but %s is a vector or array. See line %s in file %s',
                   pchar(pName),
                   pchar(pLineNumber),
                   pchar(pFileName));
      end;
    end
    else
    begin
      // Expect array or Oarray
      nSize           := 0;
      bNegativeOrZero := false;
      bOarray         := false;

      for cn := 0 to nDims - 1 do
      begin
        nLowerBound := pCoords[cn].IndexBase;
        nUpperBound := pCoords[cn].IndexBase + pCoords[cn].Size - 1;

        bNegativeOrZero := bNegativeOrZero or (nLowerBound <= 0);
        bOarray         := bOarray or (nLowerBound <> 1);

        if (nUpperBound < nLowerBound) then
        begin
          raise Exception.Create('R_CheckArgument called with index upper bound less than lower bound\n');
        end;

        if (cn = 0) then
        begin
          nSize := (nUpperBound - nLowerBound + 1);
        end
        else
        begin
          nSize := nSize * (nUpperBound - nLowerBound + 1);
        end;
      end;

      if (nArgLength < nSize) then
      begin
        Rf_error('ERROR: %s is a vector or array with length less than expected. A length of %d elements is required. See line %s in file %s',
                 pchar(pName),
                 nSize,
                 pchar(pLineNumber),
                 pchar(pFileName));
      end
      else if (nArgLength > nSize) then
      begin
        Rf_warning('WARNING: %s is a vector or array with length greater than expected. See line %s in file %s',
                   pchar(pName),
                   pchar(pLineNumber),
                   pchar(pFileName));
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure R_CheckArgument(pName : AnsiString;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString;
                            nDims: longint;
                            Args: Array of const);overload;

  var
    cn            : longint;
    aCoords       : array[0..ADLIB_MAX_COORDS] of AdtArrayCoord;
    nLowerBound   : longint;
    nUpperBound   : longint;

  begin
    if (nDims > ADLIB_MAX_COORDS) then
    begin
      raise Exception.Create('R_CheckArgument called with too many arguments\n');
    end;

    assert(High(Args) + 1 = 2 * nDims);

    for cn := 0 to nDims - 1 do
    begin
      assert((Args[2 * cn].vtype = vtInteger) and (Args[2 * cn + 1].vtype = vtInteger));

      nLowerBound := Args[2 * cn].VInteger;
      nUpperBound := Args[2 * cn + 1].VInteger;

      aCoords[cn].IndexBase := nLowerBound;
      aCoords[cn].Size      := nUpperBound - nLowerBound + 1;

      if (nUpperBound < nLowerBound) then
      begin
        raise Exception.Create('R_CheckArgument called with index upper bound less than lower bound\n');
      end;
    end;

    R_CheckArgument(pName,
                    Argument,
                    pFileName,
                    pLineNumber,
                    nDims,
                    aCoords,
                    pRequiredTypeName,
                    nRequiredType);
  end;

  //  ----------------------------------------------------------------------------

  procedure R_CheckArgument(pName : AnsiString;
                            pRequiredTypeName : AnsiString;
                            nRequiredType : SEXPTYPE;
                            Argument : SEXP;
                            pFileName : AnsiString;
                            pLineNumber : AnsiString);overload;

  begin
    R_CheckArgument(pName,
                    Argument,
                    pFileName,
                    pLineNumber,
                    0,
                    nil,
                    pRequiredTypeName,
                    nRequiredType);
  end;

  //  ----------------------------------------------------------------------------

  function R_CreateArray(nDims : longint; pCoords : PAdtArrayCoord; nType : SEXPTYPE) : SEXP;overload;

  var
    cn              : longint;
    nSize           : longint;
    pResult         : SEXP;
    bNegativeOrZero : boolean;
    bOarray         : boolean;
    nLowerBound     : longint;
    sClass          : SEXP;
    sDropNegative   : SEXP;
    sDim            : SEXP;
    sOffset         : SEXP;

  begin
    nSize           := 0;
    bNegativeOrZero := false;
    bOarray         := false;

    for cn := 0 to nDims - 1 do
    begin
      nLowerBound     := pCoords[cn].IndexBase;
      bNegativeOrZero := bNegativeOrZero or (nLowerBound <= 0);
      bOarray         := bOarray or (nLowerBound <> 1);

      if (cn = 0) then
      begin
        nSize := pCoords[cn].Size;
      end
      else
      begin
        nSize := nSize * pCoords[cn].Size;
      end;
    end;

    if (nSize > 0) then
    begin
      pResult := Rf_PROTECT(Rf_allocVector(nType, nSize));

      if (bOarray) then
      begin
        case ArrayClass of
          ArrayClass_offarray:
          begin
            // Add Oarray class attribute
            sClass := Rf_PROTECT(Rf_allocVector(STRSXP, 1));

            R_SET_STRING_ELT(sClass, 0, Rf_mkChar('offarray'));

            Rf_classgets(pResult, sClass);
            Rf_UNPROTECT(1);

            // Add attribute names for offset and drop.negative
            if (OffsetSymbol = nil) then
            begin
              OffsetSymbol := Rf_install('offset');
            end;

            // Add dim and offset attributes
            sDim    := Rf_PROTECT(Rf_allocVector(INTSXP, nDims));
            sOffset := Rf_PROTECT(Rf_allocVector(INTSXP, nDims));

            for cn := 0 to nDims - 1 do
            begin
              R_INTEGER(sDim)[cn]    := pCoords[cn].Size;
              R_INTEGER(sOffset)[cn] := pCoords[cn].IndexBase;
            end;

            Rf_dimgets(pResult, sDim);
            Rf_setAttrib(pResult, OffsetSymbol, sOffset);
            Rf_UNPROTECT(2);
          end;

          ArrayClass_Oarray:
          begin
            // Add Oarray class attribute
            sClass := Rf_PROTECT(Rf_allocVector(STRSXP, 1));

            R_SET_STRING_ELT(sClass, 0, Rf_mkChar('Oarray'));

            Rf_classgets(pResult, sClass);
            Rf_UNPROTECT(1);

            // Add attribute names for offset and drop.negative
            if (OffsetSymbol = nil) then
            begin
              OffsetSymbol := Rf_install('offset');
            end;

            if (DropNegativeSymbol = nil) then
            begin
              DropNegativeSymbol := Rf_install('drop.negative');
            end;

            // Add drop negative attribute
            if (bNegativeOrZero) then
              sDropNegative := Rf_PROTECT(Rf_ScalarLogical(0))
            else
              sDropNegative := Rf_PROTECT(Rf_ScalarLogical(1));

            Rf_setAttrib(pResult, DropNegativeSymbol, sDropNegative);
            Rf_UNPROTECT(1);

            // Add dim and offset attributes
            sDim    := Rf_PROTECT(Rf_allocVector(INTSXP, nDims));
            sOffset := Rf_PROTECT(Rf_allocVector(INTSXP, nDims));

            for cn := 0 to nDims - 1 do
            begin
              R_INTEGER(sDim)[cn]    := pCoords[cn].Size;
              R_INTEGER(sOffset)[cn] := pCoords[cn].IndexBase;
            end;

            Rf_dimgets(pResult, sDim);
            Rf_setAttrib(pResult, OffsetSymbol, sOffset);
            Rf_UNPROTECT(2);
          end;
        else
          raise Exception.Create('R_CreateArray called with invalid R ArrayClass\n');
        end;
      end
      else
      begin
        // Add dim attribute
        sDim := Rf_PROTECT(Rf_allocVector(INTSXP, nDims));

        for cn := 0 to nDims - 1 do
        begin
          R_INTEGER(sDim)[cn] := pCoords[cn].Size;
        end;

        Rf_dimgets(pResult, sDim);
        Rf_UNPROTECT(1);
      end;

      Rf_UNPROTECT(1);
    end
    else
    begin
      raise Exception.Create('R_CreateArray called with zero dims\n');
    end;

    R_CreateArray := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_CreateArray(nDims : longint; nType : SEXPTYPE; Args: Array of const) : SEXP;overload;

  var
    cn            : longint;
    aCoords       : array[0..ADLIB_MAX_COORDS] of AdtArrayCoord;
    nLowerBound   : longint;
    nUpperBound   : longint;

  begin
    if (nDims > ADLIB_MAX_COORDS) then
    begin
      raise Exception.Create('R_CreateArray called with too many arguments\n');
    end;

    assert(High(Args) + 1 = 2 * nDims);

    for cn := 0 to nDims - 1 do
    begin
      assert((Args[2 * cn].vtype = vtInteger) and (Args[2 * cn + 1].vtype = vtInteger));

      nLowerBound := Args[2 * cn].VInteger;
      nUpperBound := Args[2 * cn + 1].VInteger;

      aCoords[cn].IndexBase := nLowerBound;
      aCoords[cn].Size      := nUpperBound - nLowerBound + 1;

      if (nUpperBound < nLowerBound) then
      begin
        raise Exception.Create('R_CreateArray called with index upper bound less than lower bound\n');
      end;
    end;

    R_CreateArray := R_CreateArray(nDims, aCoords, nType);
  end;

  //  ----------------------------------------------------------------------------

  function R_Scalar(nResult : longint) : SEXP;overload;

  var
    pResult : SEXP;

  begin
    pResult := Rf_allocVector(INTSXP, 1);

    Rf_PROTECT(pResult);
    R_INTEGER(pResult)[0] := nResult;
    Rf_UNPROTECT(1);

    R_Scalar := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_Scalar(dResult : double) : SEXP;overload;

  var
    pResult : SEXP;

  begin
    pResult := Rf_allocVector(REALSXP, 1);

    Rf_PROTECT(pResult);
    R_REAL(pResult)[0] := dResult;
    Rf_UNPROTECT(1);

    R_Scalar := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_Scalar(bResult : longbool) : SEXP;overload;

  var
    pResult : SEXP;

  begin
    pResult := Rf_allocVector(LGLSXP, 1);

    Rf_PROTECT(pResult);
    R_LOGICAL(pResult)[0] := bResult;
    Rf_UNPROTECT(1);

    R_Scalar := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_Scalar(cResult : char) : SEXP;overload;
  var
    pResult : SEXP;

  begin
    pResult := Rf_allocVector(RAWSXP, 1);

    Rf_PROTECT(pResult);

    R_RAW(pResult)[0] := byte(cResult);
    Rf_UNPROTECT(1);

    R_Scalar := pResult;
  end;

  //  ----------------------------------------------------------------------------

  function R_Empty() : SEXP;

  var
    nEmpty : longint;

  begin
    nEmpty  := 0;
    R_Empty := R_Scalar(nEmpty);
  end;

  //  ----------------------------------------------------------------------------

  procedure R_SetArrayClass(nClass : R_UseArrayClass);

  begin
    ArrayClass := nClass;
  end;

end.
