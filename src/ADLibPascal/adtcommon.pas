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
//    adtcommon.pas
//
//  Purpose:
//    This file declares the array types supported.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
Unit adtcommon;

interface

uses
  Classes,
  SysUtils,
  gutil;

type
  pchar             = ^char;
  ppchar            = ^pchar;
  pppchar           = ^ppchar;
  ppppchar          = ^pppchar;
  pppppchar         = ^ppppchar;
  ppppppchar        = ^pppppchar;
  pppppppchar       = ^ppppppchar;
  ppppppppchar      = ^pppppppchar;
  pppppppppchar     = ^ppppppppchar;
  ppppppppppchar    = ^pppppppppchar;
  plongint          = ^longint;
  pdouble           = ^double;
  plongbool         = ^longbool;


  //  -------------------------------------------------------------------------
  //  ARRAY_B?
  //  -------------------------------------------------------------------------
  boolean_array_1   = array[0..99] of boolean;
  ARRAY_1B          = ^boolean_array_1;
  boolean_array_2   = array[0..99] of ARRAY_1B;
  ARRAY_2B          = ^boolean_array_2;
  boolean_array_3   = array[0..99] of ARRAY_2B;
  ARRAY_3B          = ^boolean_array_3;
  boolean_array_4   = array[0..99] of ARRAY_3B;
  ARRAY_4B          = ^boolean_array_4;
  boolean_array_5   = array[0..99] of ARRAY_4B;
  ARRAY_5B          = ^boolean_array_5;
  boolean_array_6   = array[0..99] of ARRAY_5B;
  ARRAY_6B          = ^boolean_array_6;
  boolean_array_7   = array[0..99] of ARRAY_6B;
  ARRAY_7B          = ^boolean_array_7;
  boolean_array_8   = array[0..99] of ARRAY_7B;
  ARRAY_8B          = ^boolean_array_8;
  boolean_array_9   = array[0..99] of ARRAY_8B;
  ARRAY_9B          = ^boolean_array_9;
  boolean_array_10  = array[0..99] of ARRAY_9B;
  ARRAY_10B         = ^boolean_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_LB?
  //  -------------------------------------------------------------------------
  longbool_array_1   = array[0..99] of longbool;
  ARRAY_1LB          = ^longbool_array_1;
  longbool_array_2   = array[0..99] of ARRAY_1LB;
  ARRAY_2LB          = ^longbool_array_2;
  longbool_array_3   = array[0..99] of ARRAY_2LB;
  ARRAY_3LB          = ^longbool_array_3;
  longbool_array_4   = array[0..99] of ARRAY_3LB;
  ARRAY_4LB          = ^longbool_array_4;
  longbool_array_5   = array[0..99] of ARRAY_4LB;
  ARRAY_5LB          = ^longbool_array_5;
  longbool_array_6   = array[0..99] of ARRAY_5LB;
  ARRAY_6LB          = ^longbool_array_6;
  longbool_array_7   = array[0..99] of ARRAY_6LB;
  ARRAY_7LB          = ^longbool_array_7;
  longbool_array_8   = array[0..99] of ARRAY_7LB;
  ARRAY_8LB          = ^longbool_array_8;
  longbool_array_9   = array[0..99] of ARRAY_8LB;
  ARRAY_9LB          = ^longbool_array_9;
  longbool_array_10  = array[0..99] of ARRAY_9LB;
  ARRAY_10LB         = ^longbool_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_C?
  //  -------------------------------------------------------------------------
  shortint_array_1  = array[0..99] of shortint;
  ARRAY_1C          = ^shortint_array_1;
  shortint_array_2  = array[0..99] of ARRAY_1C;
  ARRAY_2C          = ^shortint_array_2;
  shortint_array_3  = array[0..99] of ARRAY_2C;
  ARRAY_3C          = ^shortint_array_3;
  shortint_array_4  = array[0..99] of ARRAY_3C;
  ARRAY_4C          = ^shortint_array_4;
  shortint_array_5  = array[0..99] of ARRAY_4C;
  ARRAY_5C          = ^shortint_array_5;
  shortint_array_6  = array[0..99] of ARRAY_5C;
  ARRAY_6C          = ^shortint_array_6;
  shortint_array_7  = array[0..99] of ARRAY_6C;
  ARRAY_7C          = ^shortint_array_7;
  shortint_array_8  = array[0..99] of ARRAY_7C;
  ARRAY_8C          = ^shortint_array_8;
  shortint_array_9  = array[0..99] of ARRAY_8C;
  ARRAY_9C          = ^shortint_array_9;
  shortint_array_10 = array[0..99] of ARRAY_9C;
  ARRAY_10C         = ^shortint_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_UC?
  //  -------------------------------------------------------------------------
  byte_array_1      = array[0..99] of byte;
  ARRAY_1UC         = ^byte_array_1;
  byte_array_2      = array[0..99] of ARRAY_1UC;
  ARRAY_2UC         = ^byte_array_2;
  byte_array_3      = array[0..99] of ARRAY_2UC;
  ARRAY_3UC         = ^byte_array_3;
  byte_array_4      = array[0..99] of ARRAY_3UC;
  ARRAY_4UC         = ^byte_array_4;
  byte_array_5      = array[0..99] of ARRAY_4UC;
  ARRAY_5UC         = ^byte_array_5;
  byte_array_6      = array[0..99] of ARRAY_5UC;
  ARRAY_6UC         = ^byte_array_6;
  byte_array_7      = array[0..99] of ARRAY_6UC;
  ARRAY_7UC         = ^byte_array_7;
  byte_array_8      = array[0..99] of ARRAY_7UC;
  ARRAY_8UC         = ^byte_array_8;
  byte_array_9      = array[0..99] of ARRAY_8UC;
  ARRAY_9UC         = ^byte_array_9;
  byte_array_10     = array[0..99] of ARRAY_9UC;
  ARRAY_10UC        = ^byte_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_S?
  //  -------------------------------------------------------------------------
  smallint_array_1  = array[0..99] of smallint;
  ARRAY_1S          = ^smallint_array_1;
  smallint_array_2  = array[0..99] of ARRAY_1S;
  ARRAY_2S          = ^smallint_array_2;
  smallint_array_3  = array[0..99] of ARRAY_2S;
  ARRAY_3S          = ^smallint_array_3;
  smallint_array_4  = array[0..99] of ARRAY_3S;
  ARRAY_4S          = ^smallint_array_4;
  smallint_array_5  = array[0..99] of ARRAY_4S;
  ARRAY_5S          = ^smallint_array_5;
  smallint_array_6  = array[0..99] of ARRAY_5S;
  ARRAY_6S          = ^smallint_array_6;
  smallint_array_7  = array[0..99] of ARRAY_6S;
  ARRAY_7S          = ^smallint_array_7;
  smallint_array_8  = array[0..99] of ARRAY_7S;
  ARRAY_8S          = ^smallint_array_8;
  smallint_array_9  = array[0..99] of ARRAY_8S;
  ARRAY_9S          = ^smallint_array_9;
  smallint_array_10 = array[0..99] of ARRAY_9S;
  ARRAY_10S         = ^smallint_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_US?
  //  -------------------------------------------------------------------------
  word_array_1      = array[0..99] of word;
  ARRAY_1US         = ^word_array_1;
  word_array_2      = array[0..99] of ARRAY_1US;
  ARRAY_2US         = ^word_array_2;
  word_array_3      = array[0..99] of ARRAY_2US;
  ARRAY_3US         = ^word_array_3;
  word_array_4      = array[0..99] of ARRAY_3US;
  ARRAY_4US         = ^word_array_4;
  word_array_5      = array[0..99] of ARRAY_4US;
  ARRAY_5US         = ^word_array_5;
  word_array_6      = array[0..99] of ARRAY_5US;
  ARRAY_6US         = ^word_array_6;
  word_array_7      = array[0..99] of ARRAY_6US;
  ARRAY_7US         = ^word_array_7;
  word_array_8      = array[0..99] of ARRAY_7US;
  ARRAY_8US         = ^word_array_8;
  word_array_9      = array[0..99] of ARRAY_8US;
  ARRAY_9US         = ^word_array_9;
  word_array_10     = array[0..99] of ARRAY_9US;
  ARRAY_10US        = ^word_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_L?
  //  -------------------------------------------------------------------------
  longint_array_1   = array[0..99] of longint;
  ARRAY_1L          = ^longint_array_1;
  longint_array_2   = array[0..99] of ARRAY_1L;
  ARRAY_2L          = ^longint_array_2;
  longint_array_3   = array[0..99] of ARRAY_2L;
  ARRAY_3L          = ^longint_array_3;
  longint_array_4   = array[0..99] of ARRAY_3L;
  ARRAY_4L          = ^longint_array_4;
  longint_array_5   = array[0..99] of ARRAY_4L;
  ARRAY_5L          = ^longint_array_5;
  longint_array_6   = array[0..99] of ARRAY_5L;
  ARRAY_6L          = ^longint_array_6;
  longint_array_7   = array[0..99] of ARRAY_6L;
  ARRAY_7L          = ^longint_array_7;
  longint_array_8   = array[0..99] of ARRAY_7L;
  ARRAY_8L          = ^longint_array_8;
  longint_array_9   = array[0..99] of ARRAY_8L;
  ARRAY_9L          = ^longint_array_9;
  longint_array_10  = array[0..99] of ARRAY_9L;
  ARRAY_10L         = ^longint_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_UL?
  //  -------------------------------------------------------------------------
  longword_array_1  = array[0..99] of longword;
  ARRAY_1UL         = ^longword_array_1;
  longword_array_2  = array[0..99] of ARRAY_1UL;
  ARRAY_2UL         = ^longword_array_2;
  longword_array_3  = array[0..99] of ARRAY_2UL;
  ARRAY_3UL         = ^longword_array_3;
  longword_array_4  = array[0..99] of ARRAY_3UL;
  ARRAY_4UL         = ^longword_array_4;
  longword_array_5  = array[0..99] of ARRAY_4UL;
  ARRAY_5UL         = ^longword_array_5;
  longword_array_6  = array[0..99] of ARRAY_5UL;
  ARRAY_6UL         = ^longword_array_6;
  longword_array_7  = array[0..99] of ARRAY_6UL;
  ARRAY_7UL         = ^longword_array_7;
  longword_array_8  = array[0..99] of ARRAY_7UL;
  ARRAY_8UL         = ^longword_array_8;
  longword_array_9  = array[0..99] of ARRAY_8UL;
  ARRAY_9UL         = ^longword_array_9;
  longword_array_10 = array[0..99] of ARRAY_9UL;
  ARRAY_10UL        = ^longword_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_I?
  //  -------------------------------------------------------------------------
  integer_array_1   = array[0..99] of integer;
  ARRAY_1I          = ^integer_array_1;
  integer_array_2   = array[0..99] of ARRAY_1I;
  ARRAY_2I          = ^integer_array_2;
  integer_array_3   = array[0..99] of ARRAY_2I;
  ARRAY_3I          = ^integer_array_3;
  integer_array_4   = array[0..99] of ARRAY_3I;
  ARRAY_4I          = ^integer_array_4;
  integer_array_5   = array[0..99] of ARRAY_4I;
  ARRAY_5I          = ^integer_array_5;
  integer_array_6   = array[0..99] of ARRAY_5I;
  ARRAY_6I          = ^integer_array_6;
  integer_array_7   = array[0..99] of ARRAY_6I;
  ARRAY_7I          = ^integer_array_7;
  integer_array_8   = array[0..99] of ARRAY_7I;
  ARRAY_8I          = ^integer_array_8;
  integer_array_9   = array[0..99] of ARRAY_8I;
  ARRAY_9I          = ^integer_array_9;
  integer_array_10  = array[0..99] of ARRAY_9I;
  ARRAY_10I         = ^integer_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_F?
  //  -------------------------------------------------------------------------
  single_array_1    = array[0..99] of single;
  ARRAY_1F          = ^single_array_1;
  single_array_2    = array[0..99] of ARRAY_1F;
  ARRAY_2F          = ^single_array_2;
  single_array_3    = array[0..99] of ARRAY_2F;
  ARRAY_3F          = ^single_array_3;
  single_array_4    = array[0..99] of ARRAY_3F;
  ARRAY_4F          = ^single_array_4;
  single_array_5    = array[0..99] of ARRAY_4F;
  ARRAY_5F          = ^single_array_5;
  single_array_6    = array[0..99] of ARRAY_5F;
  ARRAY_6F          = ^single_array_6;
  single_array_7    = array[0..99] of ARRAY_6F;
  ARRAY_7F          = ^single_array_7;
  single_array_8    = array[0..99] of ARRAY_7F;
  ARRAY_8F          = ^single_array_8;
  single_array_9    = array[0..99] of ARRAY_8F;
  ARRAY_9F          = ^single_array_9;
  single_array_10   = array[0..99] of ARRAY_9F;
  ARRAY_10F         = ^single_array_10;

  //  -------------------------------------------------------------------------
  //  ARRAY_D?
  //  -------------------------------------------------------------------------
  double_array_1    = array[0..99] of double;
  ARRAY_1D          = ^double_array_1;
  double_array_2    = array[0..99] of ARRAY_1D;
  ARRAY_2D          = ^double_array_2;
  double_array_3    = array[0..99] of ARRAY_2D;
  ARRAY_3D          = ^double_array_3;
  double_array_4    = array[0..99] of ARRAY_3D;
  ARRAY_4D          = ^double_array_4;
  double_array_5    = array[0..99] of ARRAY_4D;
  ARRAY_5D          = ^double_array_5;
  double_array_6    = array[0..99] of ARRAY_5D;
  ARRAY_6D          = ^double_array_6;
  double_array_7    = array[0..99] of ARRAY_6D;
  ARRAY_7D          = ^double_array_7;
  double_array_8    = array[0..99] of ARRAY_7D;
  ARRAY_8D          = ^double_array_8;
  double_array_9    = array[0..99] of ARRAY_8D;
  ARRAY_9D          = ^double_array_9;
  double_array_10   = array[0..99] of ARRAY_9D;
  ARRAY_10D         = ^double_array_10;


  //  -------------------------------------------------------------------------
  //  TLess pchar specialisation
  //  -------------------------------------------------------------------------
  AdtLessPChar = specialize TLess<pchar>;


  //  -------------------------------------------------------------------------
  //  TLess AnsiString specialisation
  //  -------------------------------------------------------------------------
  AdtLessAnsiString = specialize TLess<AnsiString>;


  //  -------------------------------------------------------------------------
  //  enum AdtVarType
  //  -------------------------------------------------------------------------
  AdtVarType = (AdtVarType_UNDEFINED,
                AdtVarType_BOOL,
                AdtVarType_LONGBOOL,
                AdtVarType_CHAR,
                AdtVarType_UCHAR,
                AdtVarType_INT,
                AdtVarType_LONG,
                AdtVarType_ULONG,
                AdtVarType_SHORT,
                AdtVarType_USHORT,
                AdtVarType_FLOAT,
                AdtVarType_DOUBLE);

const
  //  ----------------------------------------------------------------------------
  //  The maximum number of array co-ordinates supported in this library. If you
  //  add more then please update this.
  //  ----------------------------------------------------------------------------
  ADLIB_MAX_COORDS = 10;

  function one_if(bTrue : boolean) : integer;inline;
  function add_to(var i : integer; v : integer) : integer;inline;
  function add_one_to(var i : integer) : integer;inline;
  function sub_one_from(var i : integer) : integer;inline;

  procedure log_error(sMsg : AnsiString) ; external name 'log_error';
  procedure log_warning(sMsg : AnsiString) ; external name 'log_warning';

  function elementSizeFromVarType(nVarType : AdtVarType) : longint;
  function varTypeName(nVarType : AdtVarType) : pchar;

  function varType(rArray : ARRAY_1B) : AdtVarType;overload;
  function varType(rArray : ARRAY_2B) : AdtVarType;overload;
  function varType(rArray : ARRAY_3B) : AdtVarType;overload;
  function varType(rArray : ARRAY_4B) : AdtVarType;overload;
  function varType(rArray : ARRAY_5B) : AdtVarType;overload;
  function varType(rArray : ARRAY_6B) : AdtVarType;overload;
  function varType(rArray : ARRAY_7B) : AdtVarType;overload;
  function varType(rArray : ARRAY_8B) : AdtVarType;overload;
  function varType(rArray : ARRAY_9B) : AdtVarType;overload;
  function varType(rArray : ARRAY_10B) : AdtVarType;overload;

  function varType(rArray : ARRAY_1LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_2LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_3LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_4LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_5LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_6LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_7LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_8LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_9LB) : AdtVarType;overload;
  function varType(rArray : ARRAY_10LB) : AdtVarType;overload;

  function varType(rArray : ARRAY_1C) : AdtVarType;overload;
  function varType(rArray : ARRAY_2C) : AdtVarType;overload;
  function varType(rArray : ARRAY_3C) : AdtVarType;overload;
  function varType(rArray : ARRAY_4C) : AdtVarType;overload;
  function varType(rArray : ARRAY_5C) : AdtVarType;overload;
  function varType(rArray : ARRAY_6C) : AdtVarType;overload;
  function varType(rArray : ARRAY_7C) : AdtVarType;overload;
  function varType(rArray : ARRAY_8C) : AdtVarType;overload;
  function varType(rArray : ARRAY_9C) : AdtVarType;overload;
  function varType(rArray : ARRAY_10C) : AdtVarType;overload;

  function varType(rArray : ARRAY_1UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_2UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_3UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_4UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_5UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_6UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_7UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_8UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_9UC) : AdtVarType;overload;
  function varType(rArray : ARRAY_10UC) : AdtVarType;overload;

  function varType(rArray : ARRAY_1I) : AdtVarType;overload;
  function varType(rArray : ARRAY_2I) : AdtVarType;overload;
  function varType(rArray : ARRAY_3I) : AdtVarType;overload;
  function varType(rArray : ARRAY_4I) : AdtVarType;overload;
  function varType(rArray : ARRAY_5I) : AdtVarType;overload;
  function varType(rArray : ARRAY_6I) : AdtVarType;overload;
  function varType(rArray : ARRAY_7I) : AdtVarType;overload;
  function varType(rArray : ARRAY_8I) : AdtVarType;overload;
  function varType(rArray : ARRAY_9I) : AdtVarType;overload;
  function varType(rArray : ARRAY_10I) : AdtVarType;overload;

  function varType(rArray : ARRAY_1S) : AdtVarType;overload;
  function varType(rArray : ARRAY_2S) : AdtVarType;overload;
  function varType(rArray : ARRAY_3S) : AdtVarType;overload;
  function varType(rArray : ARRAY_4S) : AdtVarType;overload;
  function varType(rArray : ARRAY_5S) : AdtVarType;overload;
  function varType(rArray : ARRAY_6S) : AdtVarType;overload;
  function varType(rArray : ARRAY_7S) : AdtVarType;overload;
  function varType(rArray : ARRAY_8S) : AdtVarType;overload;
  function varType(rArray : ARRAY_9S) : AdtVarType;overload;
  function varType(rArray : ARRAY_10S) : AdtVarType;overload;

  function varType(rArray : ARRAY_1US) : AdtVarType;overload;
  function varType(rArray : ARRAY_2US) : AdtVarType;overload;
  function varType(rArray : ARRAY_3US) : AdtVarType;overload;
  function varType(rArray : ARRAY_4US) : AdtVarType;overload;
  function varType(rArray : ARRAY_5US) : AdtVarType;overload;
  function varType(rArray : ARRAY_6US) : AdtVarType;overload;
  function varType(rArray : ARRAY_7US) : AdtVarType;overload;
  function varType(rArray : ARRAY_8US) : AdtVarType;overload;
  function varType(rArray : ARRAY_9US) : AdtVarType;overload;
  function varType(rArray : ARRAY_10US) : AdtVarType;overload;

  function varType(rArray : ARRAY_1L) : AdtVarType;overload;
  function varType(rArray : ARRAY_2L) : AdtVarType;overload;
  function varType(rArray : ARRAY_3L) : AdtVarType;overload;
  function varType(rArray : ARRAY_4L) : AdtVarType;overload;
  function varType(rArray : ARRAY_5L) : AdtVarType;overload;
  function varType(rArray : ARRAY_6L) : AdtVarType;overload;
  function varType(rArray : ARRAY_7L) : AdtVarType;overload;
  function varType(rArray : ARRAY_8L) : AdtVarType;overload;
  function varType(rArray : ARRAY_9L) : AdtVarType;overload;
  function varType(rArray : ARRAY_10L) : AdtVarType;overload;

  function varType(rArray : ARRAY_1UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_2UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_3UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_4UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_5UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_6UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_7UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_8UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_9UL) : AdtVarType;overload;
  function varType(rArray : ARRAY_10UL) : AdtVarType;overload;

  function varType(rArray : ARRAY_1F) : AdtVarType;overload;
  function varType(rArray : ARRAY_2F) : AdtVarType;overload;
  function varType(rArray : ARRAY_3F) : AdtVarType;overload;
  function varType(rArray : ARRAY_4F) : AdtVarType;overload;
  function varType(rArray : ARRAY_5F) : AdtVarType;overload;
  function varType(rArray : ARRAY_6F) : AdtVarType;overload;
  function varType(rArray : ARRAY_7F) : AdtVarType;overload;
  function varType(rArray : ARRAY_8F) : AdtVarType;overload;
  function varType(rArray : ARRAY_9F) : AdtVarType;overload;
  function varType(rArray : ARRAY_10F) : AdtVarType;overload;

  function varType(rArray : ARRAY_1D) : AdtVarType;overload;
  function varType(rArray : ARRAY_2D) : AdtVarType;overload;
  function varType(rArray : ARRAY_3D) : AdtVarType;overload;
  function varType(rArray : ARRAY_4D) : AdtVarType;overload;
  function varType(rArray : ARRAY_5D) : AdtVarType;overload;
  function varType(rArray : ARRAY_6D) : AdtVarType;overload;
  function varType(rArray : ARRAY_7D) : AdtVarType;overload;
  function varType(rArray : ARRAY_8D) : AdtVarType;overload;
  function varType(rArray : ARRAY_9D) : AdtVarType;overload;
  function varType(rArray : ARRAY_10D) : AdtVarType;overload;

implementation

  function one_if(bTrue : boolean) : integer;inline;

  begin
    If (bTrue) then
      Result := 1
    else
      Result := 0;
  end;

  function add_to(var i : integer ; v : integer) : integer;inline;

  begin
    i      := i + v;
    Result := i;
  end;

  function add_one_to(var i : integer) : integer;inline;

  begin
    inc(i);

    Result := i;
  end;

  function sub_one_from(var i : integer) : integer;inline;

  begin
    dec(i);

    Result := i;
  end;

  function elementSizeFromVarType(nVarType : AdtVarType) : longint;

  var
    nSizeOf : longint;

  begin
    nSizeOf := 0;

    case (nVarType) of
      AdtVarType_BOOL:      nSizeOf := sizeof(boolean);
      AdtVarType_LONGBOOL:  nSizeOf := sizeof(longbool);
      AdtVarType_CHAR:      nSizeOf := sizeof(shortint);
      AdtVarType_UCHAR:     nSizeOf := sizeof(byte);
      AdtVarType_INT:       nSizeOf := sizeof(integer);
      AdtVarType_LONG:      nSizeOf := sizeof(longint);
      AdtVarType_ULONG:     nSizeOf := sizeof(longword);
      AdtVarType_SHORT:     nSizeOf := sizeof(smallint);
      AdtVarType_USHORT:    nSizeOf := sizeof(word);
      AdtVarType_FLOAT:     nSizeOf := sizeof(single);
      AdtVarType_DOUBLE:    nSizeOf := sizeof(double);
      else
      begin
        raise Exception.Create('Uninitialised var type');
      end;
    end;

    elementSizeFromVarType := nSizeOf;
  end;

  function varTypeName(nVarType : AdtVarType): pchar;

  var
    sTypeName : pchar;

  begin
    case nVarType of
      AdtVarType_UNDEFINED:  sTypeName := 'AdtVarType_UNDEFINED';
      AdtVarType_BOOL:       sTypeName := 'AdtVarType_BOOL';
      AdtVarType_LONGBOOL:   sTypeName := 'AdtVarType_LONGBOOL';
      AdtVarType_CHAR:       sTypeName := 'AdtVarType_CHAR';
      AdtVarType_UCHAR:      sTypeName := 'AdtVarType_UCHAR';
      AdtVarType_INT:        sTypeName := 'AdtVarType_INT';
      AdtVarType_LONG:       sTypeName := 'AdtVarType_LONG';
      AdtVarType_ULONG:      sTypeName := 'AdtVarType_ULONG';
      AdtVarType_SHORT:      sTypeName := 'AdtVarType_SHORT';
      AdtVarType_USHORT:     sTypeName := 'AdtVarType_USHORT';
      AdtVarType_FLOAT:      sTypeName := 'AdtVarType_FLOAT';
      AdtVarType_DOUBLE:     sTypeName := 'AdtVarType_DOUBLE';
      else                   sTypeName := 'AdtVarType_UNDEFINED';
    end;

    result := sTypeName;
  end;

  function varType(rArray : ARRAY_1B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_2B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_3B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_4B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_5B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_6B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_7B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_8B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_9B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;
  function varType(rArray : ARRAY_10B) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_BOOL; end;

  function varType(rArray : ARRAY_1LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_2LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_3LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_4LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_5LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_6LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_7LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_8LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_9LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;
  function varType(rArray : ARRAY_10LB) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONGBOOL; end;

  function varType(rArray : ARRAY_1C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_2C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_3C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_4C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_5C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_6C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_7C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_8C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_9C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;
  function varType(rArray : ARRAY_10C) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_CHAR; end;

  function varType(rArray : ARRAY_1UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_2UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_3UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_4UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_5UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_6UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_7UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_8UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_9UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;
  function varType(rArray : ARRAY_10UC) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_UCHAR; end;

  function varType(rArray : ARRAY_1I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_2I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_3I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_4I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_5I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_6I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_7I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_8I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_9I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;
  function varType(rArray : ARRAY_10I) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_INT; end;

  function varType(rArray : ARRAY_1S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_2S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_3S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_4S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_5S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_6S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_7S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_8S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_9S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;
  function varType(rArray : ARRAY_10S) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_SHORT; end;

  function varType(rArray : ARRAY_1US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_2US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_3US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_4US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_5US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_6US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_7US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_8US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_9US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;
  function varType(rArray : ARRAY_10US) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_USHORT; end;

  function varType(rArray : ARRAY_1L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_2L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_3L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_4L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_5L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_6L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_7L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_8L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_9L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;
  function varType(rArray : ARRAY_10L) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_LONG; end;

  function varType(rArray : ARRAY_1UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_2UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_3UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_4UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_5UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_6UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_7UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_8UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_9UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;
  function varType(rArray : ARRAY_10UL) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_ULONG; end;

  function varType(rArray : ARRAY_1F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_2F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_3F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_4F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_5F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_6F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_7F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_8F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_9F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;
  function varType(rArray : ARRAY_10F) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_FLOAT; end;

  function varType(rArray : ARRAY_1D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_2D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_3D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_4D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_5D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_6D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_7D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_8D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_9D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;
  function varType(rArray : ARRAY_10D) : AdtVarType;overload; begin rArray := rArray; varType := AdtVarType_DOUBLE; end;

end.
