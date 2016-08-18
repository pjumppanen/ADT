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
//    adtalias.pas
//
//  Purpose:
//    This file implements a map of AdtArrayAlias records. This
//    code would have normally resided in adtarrays.pas but because of a
//    bug in the implementation of generics it cannot. Because of that bug
//    you can only specialize TMap within a program unit.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
Unit adtalias;

interface

uses
  Classes,
  SysUtils,
  gset,
  gmap,
  adtcommon;

type
  //  ----------------------------------------------------------------------------
  //  AdtAliasArray record
  //  ----------------------------------------------------------------------------
  AdtAliasArray = record
    VarType : AdtVarType;
    Dims    : longint;
    Alias   : pchar;
  end;


  //  ----------------------------------------------------------------------------
  //  Mappings of AdtAliasArray by pchar
  //  ----------------------------------------------------------------------------
  AdtAliasArrayByCharPtrMap = specialize TMap<pchar, AdtAliasArray, AdtLessPChar>;


implementation

end.
