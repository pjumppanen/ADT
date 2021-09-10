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
//    adtarrays.hpp
//
//  Purpose:
//    This file includes declarations of classes for use in Auto-differentiation
//    code implemented in C++. This is a functional equivalent of the TUseful
//    delphi unit code for delphi applications.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#ifndef __ADT_ARRAYS__
#define __ADT_ARRAYS__


#ifndef AD

#ifdef _MSC_VER
  #define EXPORT extern "C" __declspec(dllexport)
#else
  #define EXPORT extern "C"
#endif


#include "adtmaths.hpp"


//  ----------------------------------------------------------------------------
//  Forward declarations
//  ----------------------------------------------------------------------------
class AdtADStack;
class AdtArrayPlanActor;
class AdtArrays;
class AdtMutex;

//  ----------------------------------------------------------------------------
//  null pointer required for bounds check context
//  ----------------------------------------------------------------------------
#define nil 0


//  ----------------------------------------------------------------------------
//  Bounds checking context
//  ----------------------------------------------------------------------------
typedef const AdtArrayPlanActor* CHECK_CONTEXT;


//  ----------------------------------------------------------------------------
//  Ragged Array creation context
//  ----------------------------------------------------------------------------
typedef AdtArrayPlanActor* RAGGED_CONTEXT;


//  ----------------------------------------------------------------------------
//  Bounds checking macro casting wrappers
//  ----------------------------------------------------------------------------
#define check1(Context, Array, Name, File, Line, ThrowException, ix1, n1) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 1, ThrowException, ix1, n1)

//  ----------------------------------------------------------------------------

#define check2(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 2, ThrowException, ix1, n1, ix2, n2)

//  ----------------------------------------------------------------------------

#define check3(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 3, ThrowException, ix1, n1, ix2, n2, ix3, n3)

//  ----------------------------------------------------------------------------

#define check4(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 4, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4)

//  ----------------------------------------------------------------------------

#define check5(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 5, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5)

//  ----------------------------------------------------------------------------

#define check6(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 6, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6)

//  ----------------------------------------------------------------------------

#define check7(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 7, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7)

//  ----------------------------------------------------------------------------

#define check8(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 8, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8)

//  ----------------------------------------------------------------------------

#define check9(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8, ix9, n9) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 9, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8, ix9, n9)

//  ----------------------------------------------------------------------------

#define check10(Context, Array, Name, File, Line, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8, ix9, n9, ix10, n10) \
check(Context, MemAllocator, (char*)Array, Name, File, Line, 10, ThrowException, ix1, n1, ix2, n2, ix3, n3, ix4, n4, ix5, n5, ix6, n6, ix7, n7, ix8, n8, ix9, n9, ix10, n10)


//  ----------------------------------------------------------------------------
//  R interface related macros
//  ----------------------------------------------------------------------------
#define DECL_TYPE_TAG(OBJ) \
extern const SEXP OBJ##_type_tag;

//  ----------------------------------------------------------------------------

#define IMPL_TYPE_TAG(OBJ) \
const SEXP OBJ##_type_tag = install(#OBJ"TYPE_TAG");

//  ----------------------------------------------------------------------------

#define CHECK_TYPE_TAG(s, OBJ) \
((TYPEOF(s) == EXTPTRSXP) && (R_ExternalPtrTag(s) == OBJ##_type_tag))

//  ----------------------------------------------------------------------------

#define ASSERT_TYPE_TAG(s, OBJ) \
if (!((TYPEOF(s) == EXTPTRSXP) && (R_ExternalPtrTag(s) == OBJ##_type_tag)))\
{\
  Rf_error("ERROR: rInstance must be a "#OBJ"TYPE_TAG");\
}

//  ----------------------------------------------------------------------------

#define TYPE_TAG_STRING(OBJ) #OBJ"TYPE_TAG"

//  ----------------------------------------------------------------------------

#define TYPE_TAG_OBJ(OBJ) OBJ##_type_tag

//  ----------------------------------------------------------------------------

#define MAKE_R_EXTERNAL_PTR(Result, pCONTEXT, DESTROY_FN, OBJ) \
PROTECT(Result = R_MakeExternalPtr((void*)pCONTEXT, OBJ##_type_tag, Rf_mkChar("AdtArraysClass")));\
R_RegisterCFinalizer(Result, DESTROY_FN);\
UNPROTECT(1)\


//  ----------------------------------------------------------------------------
//  struct longbool
//  ----------------------------------------------------------------------------
//  need to define a longbool struct to act as longbool type. Cannot use typedef
//  because that is only an alias and will conflict with int in the overloading
//  of methods in the AdtArrays class.
//  ----------------------------------------------------------------------------
union longbool
{
  int Val;

  longbool& operator =(longbool a_longbool);
  longbool& operator =(bool a_bool);
  longbool& operator =(int a_int);

  operator bool() const;
  operator int() const;

  friend longbool operator !(longbool a_longbool);
  friend longbool operator &&(longbool a_longbool_A, longbool a_longbool_B);
  friend longbool operator ||(longbool a_longbool_A, longbool a_longbool_B);
};

//  ----------------------------------------------------------------------------

inline longbool& longbool::operator =(longbool a_longbool)
{
  Val = a_longbool.Val;

  return (*this);
}

//  ----------------------------------------------------------------------------

inline longbool& longbool::operator =(bool a_bool)
{
  Val = a_bool ? 1 : 0;

  return (*this);
}

//  ----------------------------------------------------------------------------

inline longbool& longbool::operator =(int a_int)
{
  Val = (a_int != 0) ? 1 : 0;

  return (*this);
}

//  ----------------------------------------------------------------------------

inline longbool::operator bool() const
{
  return (Val != 0);
}

//  ----------------------------------------------------------------------------

inline longbool::operator int() const
{
  return (Val);
}

//  ----------------------------------------------------------------------------

inline longbool operator !(longbool a_longbool)
{
  longbool Result;

  Result.Val = (a_longbool.Val == 0) ? 1 : 0;

  return (Result);
}

//  ----------------------------------------------------------------------------

inline longbool operator &&(longbool a_longbool_A, longbool a_longbool_B)
{
  longbool Result;

  Result.Val = ((a_longbool_A.Val != 0) && (a_longbool_B.Val != 0)) ? 1 : 0;

  return (Result);
}

//  ----------------------------------------------------------------------------

inline longbool operator ||(longbool a_longbool_A, longbool a_longbool_B)
{
  longbool Result;

  Result.Val = ((a_longbool_A.Val != 0) || (a_longbool_B.Val != 0)) ? 1 : 0;

  return (Result);
}


//  ----------------------------------------------------------------------------
//  The maximum number of array co-ordinates supported in this library. If you
//  add more then please update this.
//  ----------------------------------------------------------------------------
#define ADLIB_MAX_COORDS  10


//  ----------------------------------------------------------------------------
//  Array typedefs
//  ----------------------------------------------------------------------------
typedef bool*                       ARRAY_1B;
typedef bool**                      ARRAY_2B;
typedef bool***                     ARRAY_3B;
typedef bool****                    ARRAY_4B;
typedef bool*****                   ARRAY_5B;
typedef bool******                  ARRAY_6B;
typedef bool*******                 ARRAY_7B;
typedef bool********                ARRAY_8B;
typedef bool*********               ARRAY_9B;
typedef bool**********              ARRAY_10B;

//  ----------------------------------------------------------------------------

typedef longbool*                   ARRAY_1LB;
typedef longbool**                  ARRAY_2LB;
typedef longbool***                 ARRAY_3LB;
typedef longbool****                ARRAY_4LB;
typedef longbool*****               ARRAY_5LB;
typedef longbool******              ARRAY_6LB;
typedef longbool*******             ARRAY_7LB;
typedef longbool********            ARRAY_8LB;
typedef longbool*********           ARRAY_9LB;
typedef longbool**********          ARRAY_10LB;

//  ----------------------------------------------------------------------------

typedef char*                       ARRAY_1C;
typedef char**                      ARRAY_2C;
typedef char***                     ARRAY_3C;
typedef char****                    ARRAY_4C;
typedef char*****                   ARRAY_5C;
typedef char******                  ARRAY_6C;
typedef char*******                 ARRAY_7C;
typedef char********                ARRAY_8C;
typedef char*********               ARRAY_9C;
typedef char**********              ARRAY_10C;

//  ----------------------------------------------------------------------------

typedef unsigned char*              ARRAY_1UC;
typedef unsigned char**             ARRAY_2UC;
typedef unsigned char***            ARRAY_3UC;
typedef unsigned char****           ARRAY_4UC;
typedef unsigned char*****          ARRAY_5UC;
typedef unsigned char******         ARRAY_6UC;
typedef unsigned char*******        ARRAY_7UC;
typedef unsigned char********       ARRAY_8UC;
typedef unsigned char*********      ARRAY_9UC;
typedef unsigned char**********     ARRAY_10UC;

//  ----------------------------------------------------------------------------

typedef int*                        ARRAY_1I;
typedef int**                       ARRAY_2I;
typedef int***                      ARRAY_3I;
typedef int****                     ARRAY_4I;
typedef int*****                    ARRAY_5I;
typedef int******                   ARRAY_6I;
typedef int*******                  ARRAY_7I;
typedef int********                 ARRAY_8I;
typedef int*********                ARRAY_9I;
typedef int**********               ARRAY_10I;

//  ----------------------------------------------------------------------------

typedef unsigned int*               ARRAY_1UI;
typedef unsigned int**              ARRAY_2UI;
typedef unsigned int***             ARRAY_3UI;
typedef unsigned int****            ARRAY_4UI;
typedef unsigned int*****           ARRAY_5UI;
typedef unsigned int******          ARRAY_6UI;
typedef unsigned int*******         ARRAY_7UI;
typedef unsigned int********        ARRAY_8UI;
typedef unsigned int*********       ARRAY_9UI;
typedef unsigned int**********      ARRAY_10UI;

//  ----------------------------------------------------------------------------

typedef short*                      ARRAY_1S;
typedef short**                     ARRAY_2S;
typedef short***                    ARRAY_3S;
typedef short****                   ARRAY_4S;
typedef short*****                  ARRAY_5S;
typedef short******                 ARRAY_6S;
typedef short*******                ARRAY_7S;
typedef short********               ARRAY_8S;
typedef short*********              ARRAY_9S;
typedef short**********             ARRAY_10S;

//  ----------------------------------------------------------------------------

typedef unsigned short*             ARRAY_1US;
typedef unsigned short**            ARRAY_2US;
typedef unsigned short***           ARRAY_3US;
typedef unsigned short****          ARRAY_4US;
typedef unsigned short*****         ARRAY_5US;
typedef unsigned short******        ARRAY_6US;
typedef unsigned short*******       ARRAY_7US;
typedef unsigned short********      ARRAY_8US;
typedef unsigned short*********     ARRAY_9US;
typedef unsigned short**********    ARRAY_10US;

//  ----------------------------------------------------------------------------

typedef long*                       ARRAY_1L;
typedef long**                      ARRAY_2L;
typedef long***                     ARRAY_3L;
typedef long****                    ARRAY_4L;
typedef long*****                   ARRAY_5L;
typedef long******                  ARRAY_6L;
typedef long*******                 ARRAY_7L;
typedef long********                ARRAY_8L;
typedef long*********               ARRAY_9L;
typedef long**********              ARRAY_10L;

//  ----------------------------------------------------------------------------

typedef unsigned long*              ARRAY_1UL;
typedef unsigned long**             ARRAY_2UL;
typedef unsigned long***            ARRAY_3UL;
typedef unsigned long****           ARRAY_4UL;
typedef unsigned long*****          ARRAY_5UL;
typedef unsigned long******         ARRAY_6UL;
typedef unsigned long*******        ARRAY_7UL;
typedef unsigned long********       ARRAY_8UL;
typedef unsigned long*********      ARRAY_9UL;
typedef unsigned long**********     ARRAY_10UL;

//  ----------------------------------------------------------------------------

typedef float*                      ARRAY_1F;
typedef float**                     ARRAY_2F;
typedef float***                    ARRAY_3F;
typedef float****                   ARRAY_4F;
typedef float*****                  ARRAY_5F;
typedef float******                 ARRAY_6F;
typedef float*******                ARRAY_7F;
typedef float********               ARRAY_8F;
typedef float*********              ARRAY_9F;
typedef float**********             ARRAY_10F;

//  ----------------------------------------------------------------------------

typedef double*                     ARRAY_1D;
typedef double**                    ARRAY_2D;
typedef double***                   ARRAY_3D;
typedef double****                  ARRAY_4D;
typedef double*****                 ARRAY_5D;
typedef double******                ARRAY_6D;
typedef double*******               ARRAY_7D;
typedef double********              ARRAY_8D;
typedef double*********             ARRAY_9D;
typedef double**********            ARRAY_10D;


//  ----------------------------------------------------------------------------
//  enum AdtVarType
//  ----------------------------------------------------------------------------
enum AdtVarType
{
  AdtVarType_UNDEFINED,
  AdtVarType_BOOL,
  AdtVarType_LONGBOOL,
  AdtVarType_CHAR,
  AdtVarType_UCHAR,
  AdtVarType_INT,
  AdtVarType_UINT,
  AdtVarType_LONG,
  AdtVarType_ULONG,
  AdtVarType_SHORT,
  AdtVarType_USHORT,
  AdtVarType_FLOAT,
  AdtVarType_DOUBLE
};

size_t      elementSizeFromVarType(AdtVarType nVarType);
const char* varTypeName(AdtVarType nVarType);


//  ----------------------------------------------------------------------------
//  function to convert array to varType. We need this for template
//  function implementations to eliminate template parameters.
//  ----------------------------------------------------------------------------
inline AdtVarType varType(ARRAY_1B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_2B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_3B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_4B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_5B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_6B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_7B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_8B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_9B Array){ return (AdtVarType_BOOL); };
inline AdtVarType varType(ARRAY_10B Array){ return (AdtVarType_BOOL); };

inline AdtVarType varType(ARRAY_1LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_2LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_3LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_4LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_5LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_6LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_7LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_8LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_9LB Array){ return (AdtVarType_LONGBOOL); };
inline AdtVarType varType(ARRAY_10LB Array){ return (AdtVarType_LONGBOOL); };

inline AdtVarType varType(ARRAY_1C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_2C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_3C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_4C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_5C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_6C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_7C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_8C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_9C Array){ return (AdtVarType_CHAR); };
inline AdtVarType varType(ARRAY_10C Array){ return (AdtVarType_CHAR); };

inline AdtVarType varType(ARRAY_1UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_2UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_3UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_4UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_5UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_6UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_7UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_8UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_9UC Array){ return (AdtVarType_UCHAR); };
inline AdtVarType varType(ARRAY_10UC Array){ return (AdtVarType_UCHAR); };

inline AdtVarType varType(ARRAY_1I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_2I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_3I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_4I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_5I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_6I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_7I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_8I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_9I Array){ return (AdtVarType_INT); };
inline AdtVarType varType(ARRAY_10I Array){ return (AdtVarType_INT); };

inline AdtVarType varType(ARRAY_1UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_2UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_3UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_4UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_5UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_6UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_7UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_8UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_9UI Array){ return (AdtVarType_UINT); };
inline AdtVarType varType(ARRAY_10UI Array){ return (AdtVarType_UINT); };

inline AdtVarType varType(ARRAY_1S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_2S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_3S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_4S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_5S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_6S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_7S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_8S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_9S Array){ return (AdtVarType_SHORT); };
inline AdtVarType varType(ARRAY_10S Array){ return (AdtVarType_SHORT); };

inline AdtVarType varType(ARRAY_1US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_2US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_3US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_4US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_5US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_6US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_7US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_8US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_9US Array){ return (AdtVarType_USHORT); };
inline AdtVarType varType(ARRAY_10US Array){ return (AdtVarType_USHORT); };

inline AdtVarType varType(ARRAY_1L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_2L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_3L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_4L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_5L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_6L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_7L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_8L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_9L Array){ return (AdtVarType_LONG); };
inline AdtVarType varType(ARRAY_10L Array){ return (AdtVarType_LONG); };

inline AdtVarType varType(ARRAY_1UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_2UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_3UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_4UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_5UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_6UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_7UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_8UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_9UL Array){ return (AdtVarType_ULONG); };
inline AdtVarType varType(ARRAY_10UL Array){ return (AdtVarType_ULONG); };

inline AdtVarType varType(ARRAY_1F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_2F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_3F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_4F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_5F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_6F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_7F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_8F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_9F Array){ return (AdtVarType_FLOAT); };
inline AdtVarType varType(ARRAY_10F Array){ return (AdtVarType_FLOAT); };

inline AdtVarType varType(ARRAY_1D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_2D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_3D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_4D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_5D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_6D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_7D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_8D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_9D Array){ return (AdtVarType_DOUBLE); };
inline AdtVarType varType(ARRAY_10D Array){ return (AdtVarType_DOUBLE); };


//  ----------------------------------------------------------------------------
//  one_if() logical array indice selection
//  ----------------------------------------------------------------------------
inline int one_if(bool bTrue)
{
  return (bTrue ? 1 : 0);
}


//  ----------------------------------------------------------------------------
//  struct AdtArrayCoord
//  ----------------------------------------------------------------------------
//  This structure describes the ordinate properties of an array index
//  ----------------------------------------------------------------------------
struct AdtArrayCoord
{
  int IndexBase;
  int Size;

  void appendKey(adtstring& rKey, bool bWithPrefix) const;
};


//  ----------------------------------------------------------------------------
//  struct AdtArrayInfo
//  ----------------------------------------------------------------------------
//  This structure contains information describing the allocated array.
//  ----------------------------------------------------------------------------
struct AdtArrayInfo
{
  size_t                    LookupSize;
  size_t                    BlockSize;
  size_t                    SizeOf;
  char*                     BlockPtr;
  char*                     Existing;
  AdtVarType                VarType;
  const AdtArrayPlanActor*  Actor;

public:
  void                      zero();
  void                      xcopy(const AdtArrayInfo* pArrayInfo);

  char*                     firstData();
  size_t                    lengthOfData() const;
};

//  ----------------------------------------------------------------------------

inline void AdtArrayInfo::zero()
{
  ::memset((void*)(BlockPtr + LookupSize), 0, (BlockSize - LookupSize) * sizeof(char));
}

//  ----------------------------------------------------------------------------

inline char* AdtArrayInfo::firstData()
{
  return (BlockPtr + LookupSize);
}

//  ----------------------------------------------------------------------------

inline size_t AdtArrayInfo::lengthOfData() const
{
  return (BlockSize - LookupSize);
}


//  ----------------------------------------------------------------------------
//  AdtUserDestroyCallback type definition
//  ----------------------------------------------------------------------------
typedef void (*AdtUserDestroyCallback)(char* pData);


//  ----------------------------------------------------------------------------
//  enum AdtAllocType
//  ----------------------------------------------------------------------------
enum AdtAllocType
{
  AdtAllocType_ARRAY,
  AdtAllocType_UNSPECIFIED
};


//  ----------------------------------------------------------------------------
//  class AdtMemAllocator
//  ----------------------------------------------------------------------------
//  This class is used to manage allocate memory so it can be automatically
//  freed without user intervention when used in an AdtDiff class context.
//  ----------------------------------------------------------------------------
class AdtMemAllocator
{
  //  ----------------------------------------------------------------------------
  //  struct AdtAllocRecord
  //  ----------------------------------------------------------------------------
  struct AdtAllocRecord
  {
    AdtUserDestroyCallback  Callback;
    AdtAllocType            AllocType;
    bool                    IsOurBlock;
    int                     BlockOffset;
    char*                   BlockPtr;
    size_t                  BlockSize;
    char*                   UserPtr;
    size_t                  UserSize;
    int                     LockCount;
  };

  //  ----------------------------------------------------------------------------
  //  Mappings of AdtAllocRecord by char*
  //  ----------------------------------------------------------------------------
  typedef std::pair<const char*, AdtAllocRecord>           AdtCharPtrAllocRecordPair;
  typedef std::map<char*, AdtAllocRecord>                  AdtAllocRecordByCharPtrMap;
  typedef std::map<char*, AdtAllocRecord>::iterator        AdtAllocRecordByCharPtrMapIter;
  typedef std::map<char*, AdtAllocRecord>::const_iterator  AdtAllocRecordByCharPtrMapConstIter;

private:
  mutable AdtAllocRecordByCharPtrMap  AllocMap;
  AdtMutex*                           Mutex;

private:
  char*                   debugAlloc(size_t nSize) const;
  void                    debugFree(char* pBlock) const;

protected:
  bool                    free(AdtAllocRecord& rAllocRecord) const;

public:
  AdtMemAllocator();
  virtual ~AdtMemAllocator();

  char*                   alloc(size_t nSize,
                                AdtAllocType nAllocType,
                                int nBlockOffset = 0,
                                AdtUserDestroyCallback pCallback = 0,
                                char** ppUserPtr = 0,
                                size_t nUserSize = 0,
                                char* pExisting = 0) const;

  char*                   blockPtr(char* pOffsetBlock, size_t* pBlockSize = 0, AdtAllocType* pAllocType = 0) const;
  char*                   userPtr(char* pOffsetBlock, size_t* pUserSize = 0) const;
  bool                    lock(char* pOffsetBlock) const;
  bool                    free(char* pOffsetBlock) const;
  void                    free();
};


//  ----------------------------------------------------------------------------
//  class AdtArrayPlanActor
//  ----------------------------------------------------------------------------
//  This class describes the ordinate properties of the indices making up an
//  entire array and can use this information to create such an array. The array
//  plan can cope with ragged arrays. It can also create array aliases in the
//  case of having a multi-dimensional array in a contiguous memory block which
//  we would like to access using normal array indexing syntax.
//
//  Calling the create method with pExisting defined as the memory block and the
//  AdtArrayPlanActor initialised according to the actual array layout will
//  generate a lookup for that array and return a pointer to that lookup.
//
//  AdtArrayPlanActor is not mean't to be used directly but is delegated to by
//  instances of AdtArrayPlan. We have an inner AdtArrayPlanActor class so that
//  the created array can maintain a reference counted instance of the actor
//  class in it's memory for future reference in case, for example, the user
//  would like to know about some property of the array, or copy it entirely.
//  ----------------------------------------------------------------------------
class AdtArrayPlanActor
{
  //  ----------------------------------------------------------------------------
  //  struct AdtAliasArray
  //  ----------------------------------------------------------------------------
  struct AdtAliasArray
  {
    AdtVarType    VarType;
    int           Dims;
    char*         Array;
  };

  //  ----------------------------------------------------------------------------
  //  Mappings of AdtAliasArray by char*
  //  ----------------------------------------------------------------------------
  typedef std::pair<const void*, AdtAliasArray>           AdtVoidPtrAliasArrayPair;
  typedef std::map<void*, AdtAliasArray>                  AdtAliasArrayByVoidPtrMap;
  typedef std::map<void*, AdtAliasArray>::iterator        AdtAliasArrayByVoidPtrMapIter;
  typedef std::map<void*, AdtAliasArray>::const_iterator  AdtAliasArrayByVoidPtrMapConstIter;

  //  ----------------------------------------------------------------------------
  //  Mappings of AdtArrayPlanActor* by const adtstring
  //  ----------------------------------------------------------------------------
  typedef std::pair<const adtstring, AdtArrayPlanActor*>           AdtStringAllocRecordPair;
  typedef std::map<adtstring, AdtArrayPlanActor*>                  AdtArrayPlanActorPtrByStringMap;
  typedef std::map<adtstring, AdtArrayPlanActor*>::iterator        AdtArrayPlanActorPtrByStringMapIter;
  typedef std::map<adtstring, AdtArrayPlanActor*>::const_iterator  AdtArrayPlanActorPtrByStringMapConstIter;

private:
  mutable AdtAliasArrayByVoidPtrMap       AliasMap;
  static AdtArrayPlanActorPtrByStringMap  CacheMap;
  static bool                             CacheUsed;

protected:
  AdtArrayPlanActor**               NextRagged;
  AdtArrayPlanActor*                Next;
  AdtArrayCoord                     Coord;
  int                               NumberOfCoOrdinates;
  bool                              IsCached;
  mutable size_t                    LookupSize;
  mutable size_t                    ArrayCount;
  mutable int                       LockCount;

protected:
  size_t                            findLookupSize() const;
  size_t                            arraySize(size_t nSizeOf) const;

  bool                              initialiseLookupInner(char**& pLookup,
                                                          char*& pData,
                                                          size_t nSizeOf,
                                                          const char* pStartAddress,
                                                          const char* pEndAddress,
                                                          const char* pDataStartAddress,
                                                          const char* pDataEndAddress) const;

  void                              initialiseLookup(char* pArray,
                                                     size_t nSizeOf,
                                                     size_t nLookupSize,
                                                     size_t nDataSize,
                                                     void* pExisting = 0) const;

  void                              destroyNext();
  void                              destroyNextRagged();
  void                              copyNext(const AdtArrayPlanActor* pNext);
  void                              copyNextRagged(AdtArrayPlanActor* const* ppNextRagged);

  void                              notifyDestroy(AdtArrayInfo* pArrayInfo) const;

  static void                       destroyArrayInfo(char* pData);

public:
  friend void check(const AdtArrayPlanActor*& pContext,
                    const AdtMemAllocator& rAllocator,
                    char* pArray,
                    const char* pArrayName,
                    const char* pFileName,
                    int nFileLine,
                    int nIndices,
                    bool bThrowException,
                    ...);

  AdtArrayPlanActor();
  AdtArrayPlanActor(const AdtArrayCoord* pCoords,
                    int nCoords,
                    bool bTranspose = false,
                    bool bSupressUpdate = false);

  AdtArrayPlanActor(const AdtArrayPlanActor& rCopy);

  virtual ~AdtArrayPlanActor();

  bool                              initialise(const AdtArrayCoord* pCoords,
                                               int nCoords,
                                               bool bTranspose = false,
                                               bool bSupressUpdate = false);

  bool                              beginRagged(const AdtArrayCoord& rCoord);
  bool                              beginRagged(AdtArrayPlanActor*& pContext, const AdtArrayCoord& rCoord);
  bool                              addArrayPlanActor(AdtArrayPlanActor* pActor, int nIndex);
  void                              updateCoOrdinates(AdtArrayPlanActor* pContext);
  void                              endRagged();

  bool                              isCached() const;

  char*                             create(const AdtMemAllocator& rAllocator,
                                           AdtVarType nVarType,
                                           void* pExisting = 0) const;

  char*                             createTransposed(const AdtMemAllocator& rAllocator,
                                                     AdtVarType nVarType,
                                                     void* pExisting = 0) const;

  char*                             existing(AdtVarType nVarType,
                                             void* pExisting) const;

  static AdtArrayInfo*              arrayInfo(const AdtMemAllocator& rAllocator,
                                              char* pArray);

  static char*                      createSlice(const AdtMemAllocator& rAllocator,
                                                char* pArray,
                                                const int* pIndices,
                                                int nIndices);

  static char*                      createSameShape(const AdtMemAllocator& rAllocator,
                                                    char* pRefArray);

  static void                       destroy(const AdtMemAllocator& rAllocator, char* pArray);

  static void                       R_to_ADlib(const AdtMemAllocator& rAllocator,
                                               char* pArraySrc,
                                               char* pArrayDest);

  static void                       ADlib_to_R(const AdtMemAllocator& rAllocator,
                                               char* pArraySrc,
                                               char* pArrayDest);

  AdtArrayPlanActor&                operator = (const AdtArrayPlanActor& rCopy);
  bool                              operator == (const AdtArrayPlanActor& rCopy) const;

  bool                              isRegular() const;
  bool                              isRagged() const;

  int                               numberOfCoOrdinates() const;

  char*                             indexArray(const int* pIndices,
                                               int nIndices,
                                               char* pArray,
                                               size_t nSizeOf,
                                               const AdtArrayPlanActor** ppActor = 0) const;

  int                               getCoords(AdtArrayCoord* pCoords, int nCoords, bool bReversed = false) const;

  const AdtArrayCoord&              coord(int nCoord) const;
  const AdtArrayCoord&              coord(const int* pIndices,
                                          int nIndices,
                                          const AdtArrayPlanActor** ppActor = 0) const;

  size_t                            lookupSize() const;
  size_t                            arrayCount() const;

  void                              lock() const;
  bool                              unlock() const;

  static AdtArrayPlanActor*         createArrayPlanActor(const AdtArrayCoord* pCoords,
                                                         int nCoords);

  static AdtArrayPlanActor*         cachedArrayPlanActor(const AdtArrayCoord* pCoords,
                                                         int nCoords,
                                                         bool bLock,
                                                         bool bTranspose = false);

  static void                       flush(void);
};

//  ----------------------------------------------------------------------------

inline bool AdtArrayPlanActor::isCached() const
{
  return (IsCached);
}

//  ----------------------------------------------------------------------------

inline AdtArrayInfo* AdtArrayPlanActor::arrayInfo(const AdtMemAllocator& rAllocator,
                                                  char* pArray)
{
  AdtArrayInfo* pArrayInfo = (AdtArrayInfo*)rAllocator.userPtr(pArray);

  if (pArrayInfo == 0)
  {
    throw(std::runtime_error(std::string("Unrecognised array")));
  }

  return (pArrayInfo);
}

//  ----------------------------------------------------------------------------

inline bool AdtArrayPlanActor::isRagged() const
{
  return (!isRegular());
}

//  ----------------------------------------------------------------------------

inline int AdtArrayPlanActor::numberOfCoOrdinates() const
{
  return (NumberOfCoOrdinates);
}

//  ----------------------------------------------------------------------------

inline const AdtArrayCoord& AdtArrayPlanActor::coord(int nCoord) const
{
  return (AdtArrayPlanActor::coord(0, nCoord));
}

//  ----------------------------------------------------------------------------

inline void AdtArrayPlanActor::lock() const
{
  LockCount++;
}


//  ----------------------------------------------------------------------------

class AdtArrayPlan
{
protected:
  AdtArrayPlanActor*  Actor;

public:
  AdtArrayPlan();
  AdtArrayPlan(int nBaseIndex, int nSize);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5,
               int nBaseIndex6, int nSize6);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5,
               int nBaseIndex6, int nSize6,
               int nBaseIndex7, int nSize7);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5,
               int nBaseIndex6, int nSize6,
               int nBaseIndex7, int nSize7,
               int nBaseIndex8, int nSize8);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5,
               int nBaseIndex6, int nSize6,
               int nBaseIndex7, int nSize7,
               int nBaseIndex8, int nSize8,
               int nBaseIndex9, int nSize9);

  AdtArrayPlan(int nBaseIndex1, int nSize1,
               int nBaseIndex2, int nSize2,
               int nBaseIndex3, int nSize3,
               int nBaseIndex4, int nSize4,
               int nBaseIndex5, int nSize5,
               int nBaseIndex6, int nSize6,
               int nBaseIndex7, int nSize7,
               int nBaseIndex8, int nSize8,
               int nBaseIndex9, int nSize9,
               int nBaseIndex10, int nSize10);

  AdtArrayPlan(const AdtArrayPlan& rCopy);
  virtual ~AdtArrayPlan();

  void            initialise(int nBaseIndex, int nSize);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5,
                             int nBaseIndex6, int nSize6);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5,
                             int nBaseIndex6, int nSize6,
                             int nBaseIndex7, int nSize7);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5,
                             int nBaseIndex6, int nSize6,
                             int nBaseIndex7, int nSize7,
                             int nBaseIndex8, int nSize8);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5,
                             int nBaseIndex6, int nSize6,
                             int nBaseIndex7, int nSize7,
                             int nBaseIndex8, int nSize8,
                             int nBaseIndex9, int nSize9);

  void            initialise(int nBaseIndex1, int nSize1,
                             int nBaseIndex2, int nSize2,
                             int nBaseIndex3, int nSize3,
                             int nBaseIndex4, int nSize4,
                             int nBaseIndex5, int nSize5,
                             int nBaseIndex6, int nSize6,
                             int nBaseIndex7, int nSize7,
                             int nBaseIndex8, int nSize8,
                             int nBaseIndex9, int nSize9,
                             int nBaseIndex10, int nSize10);

  bool            beginRagged(AdtArrayPlanActor*& pContext, int nBaseIndex, int nSize);
  bool            addArrayPlan(AdtArrayPlanActor* pContext, AdtArrayPlan& rArrayPlan, int nIndex);
  void            endRagged(AdtArrayPlanActor* pContext);

  bool            beginRagged(int nBaseIndex, int nSize);
  bool            addArrayPlan(AdtArrayPlan& rArrayPlan, int nIndex);
  void            endRagged();

  AdtArrayPlan&   operator = (const AdtArrayPlan& rCopy);
  bool            operator == (const AdtArrayPlan& rCopy) const;

  int             numberOfCoOrdinates() const;
  size_t          lookupSize() const;

  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  template<class T>
  bool            existing(T& pArray, void* pExisting) const
  {
    pArray = (T)((Actor != 0) ? Actor->existing(varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // New array creation method
  template<class T>
  bool            create(const AdtMemAllocator& rAllocator, T& pArray, void* pExisting = 0) const
  {
    pArray = (T)((Actor != 0) ? Actor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // Simplified array creation methods
  // 1D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex, int nSize,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[1] = {{nBaseIndex, nSize}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 1, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 2D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[2] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 2, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 3D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[3] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 3, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 4D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[4] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 4, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 5D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[5] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 5, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 6D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         int nBaseIndex6, int nSize6,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[6] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5},
                                      {nBaseIndex6, nSize6}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 6, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 7D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         int nBaseIndex6, int nSize6,
                         int nBaseIndex7, int nSize7,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[7] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5},
                                      {nBaseIndex6, nSize6},
                                      {nBaseIndex7, nSize7}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 7, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 8D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         int nBaseIndex6, int nSize6,
                         int nBaseIndex7, int nSize7,
                         int nBaseIndex8, int nSize8,
                         void* pExisting = 0)
  {
    AdtArrayCoord       rCoords[8] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5},
                                      {nBaseIndex6, nSize6},
                                      {nBaseIndex7, nSize7},
                                      {nBaseIndex8, nSize8}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 8, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 9D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         int nBaseIndex6, int nSize6,
                         int nBaseIndex7, int nSize7,
                         int nBaseIndex8, int nSize8,
                         int nBaseIndex9, int nSize9,
                         void* pExisting)
  {
    AdtArrayCoord       rCoords[9] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5},
                                      {nBaseIndex6, nSize6},
                                      {nBaseIndex7, nSize7},
                                      {nBaseIndex8, nSize8},
                                      {nBaseIndex9, nSize9}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 9, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // 10D
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator,
                         T& pArray,
                         int nBaseIndex1, int nSize1,
                         int nBaseIndex2, int nSize2,
                         int nBaseIndex3, int nSize3,
                         int nBaseIndex4, int nSize4,
                         int nBaseIndex5, int nSize5,
                         int nBaseIndex6, int nSize6,
                         int nBaseIndex7, int nSize7,
                         int nBaseIndex8, int nSize8,
                         int nBaseIndex9, int nSize9,
                         int nBaseIndex10, int nSize10,
                         void* pExisting)
  {
    AdtArrayCoord       rCoords[10] = {{nBaseIndex1, nSize1},
                                      {nBaseIndex2, nSize2},
                                      {nBaseIndex3, nSize3},
                                      {nBaseIndex4, nSize4},
                                      {nBaseIndex5, nSize5},
                                      {nBaseIndex6, nSize6},
                                      {nBaseIndex7, nSize7},
                                      {nBaseIndex8, nSize8},
                                      {nBaseIndex9, nSize9},
                                      {nBaseIndex10, nSize10}};
    AdtArrayPlanActor*  pActor     = AdtArrayPlanActor::cachedArrayPlanActor(rCoords, 10, false);

    pArray = (T)((pActor != 0) ? pActor->create(rAllocator, varType(pArray), pExisting) : 0);

    return (pArray != 0);
  }

  // Same shape array creation method
  template<class T>
  static bool     create(const AdtMemAllocator& rAllocator, T& pArray, const T pRefArray)
  {
    pArray = (T)(AdtArrayPlanActor::createSameShape(rAllocator, (char*)pRefArray));

    return (pArray != 0);
  }

  // array destruction method
  template<class T>
  static void     destroy(const AdtMemAllocator& rAllocator, T& pArray)
  {
    AdtArrayPlanActor::destroy(rAllocator, (char*)pArray);
  }
};


//  ----------------------------------------------------------------------------
//  class AdtArrays
//  ----------------------------------------------------------------------------
//  This class is a base class for auto-differentiation classes. It has an
//  instance of AdtMemAllocator to be used to allocate arrays used in the AD
//  work. Any allocated arrays will thus be freed automatically when the
//  instance of AdtArrays is freed.
//  ----------------------------------------------------------------------------
class AdtArrays
{
private:
protected:
  bool                    IsShallowCopy;
  AdtMemAllocator&        MemAllocator;
  AdtADStack&             Stack;

public:
  static const size_t     DefaultStackSize;

  AdtArrays();
  AdtArrays(const AdtArrays& rCopy, bool bShallow = true);
  virtual ~AdtArrays();

  const AdtMemAllocator&  memAllocator() const;
  AdtADStack&             stack() const;

  virtual AdtArrays*      createShallowCopy() const;

  template<class T>
  static void             zero(T& rArrayOriginValue, int nCount)
  {
    ::memset((void*)&rArrayOriginValue, 0, nCount * sizeof(T));
  }

  template<class T>
  static void             xcopy(const T& rSrcArrayOriginValue, T& rDestArrayOriginValue, int nCount)
  {
    ::memcpy((void*)&rDestArrayOriginValue, (void*)&rSrcArrayOriginValue, nCount * sizeof(T));
  }

  // zero methods
  template<class T>
  void                    zero(T pArray)
  {
    AdtArrayInfo* pArrayInfo = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);

    pArrayInfo->zero();
  }

  // xcopy methods
  template<class T>
  void                    xcopy(T pArraySrc, T pArrayDest)
  {
    AdtArrayInfo* pArrayInfoSrc   = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArraySrc);
    AdtArrayInfo* pArrayInfoDest  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArrayDest);

    pArrayInfoDest->xcopy(pArrayInfoSrc);
  }

  // set_all methods
  template<class T>
  void                    set_all(T* pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T*** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T**** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T***** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T****** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T******* pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T******** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T********* pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  template<class T>
  void                    set_all(T********** pArray, T to)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] = to;
    }
  }

  // inc methods
  template<class T>
  void                    inc(T* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    int           cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T*** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T**** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T***** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T****** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T******* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T******** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T********* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  template<class T>
  void                    inc(T********** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += 1;
    }
  }

  // dec methods
  template<class T>
  void                    dec(T* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T*** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T**** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T***** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T****** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T******* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T******** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T********* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  template<class T>
  void                    dec(T********** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= 1;
    }
  }

  // incby methods
  template<class T>
  void                    incby(T* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T*** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T**** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T***** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T****** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T******* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T******** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T********* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  template<class T>
  void                    incby(T********** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] += by;
    }
  }

  // decby methods
  template<class T>
  void                    decby(T* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T*** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T**** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T***** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T****** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T******* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T******** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T********* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  template<class T>
  void                    decby(T********** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] -= by;
    }
  }

  // mulby methods
  template<class T>
  void                    mulby(T* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T*** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T**** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T***** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T****** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T******* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T******** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T********* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  template<class T>
  void                    mulby(T********** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] *= by;
    }
  }

  // divby methods
  template<class T>
  void                    divby(T* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T*** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T**** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T***** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T****** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T******* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T******** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T********* pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  template<class T>
  void                    divby(T********** pArray, T by)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);
    size_t        cn;

    for (cn = 0 ; cn < nCount ; cn++)
    {
      pData[cn] /= by;
    }
  }

  // flatten methods
  template<class T>
  T*                      createFlattened(T* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T*** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T**** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T***** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T****** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T******* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T******** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T********* pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createFlattened(T********** pArray)
  {
    AdtArrayInfo* pArrayInfo  = AdtArrayPlanActor::arrayInfo(MemAllocator, (char*)pArray);
    T*            pFlattened  = 0;
    T*            pData       = (T*)pArrayInfo->firstData();
    size_t        nCount      = pArrayInfo->lengthOfData() / sizeof(T);

    AdtArrayPlan::create(MemAllocator, pFlattened, 1, nCount, pData);

    return (pFlattened);
  }

  template<class T>
  T*                      createSlice(T** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 1);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T*** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  1);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T*** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 2);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T**** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   1);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T**** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  2);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T**** pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 3);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T***** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    1);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T***** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   2);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T***** pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  3);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T***** pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 4);

    return (pSliceArray);
  };

  template<class T>
  T*****                  createSlice(T****** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T*****      pSliceArray = (T*****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                     (char*)pArray,
                                                                     aIndices,
                                                                     1);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T****** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    2);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T****** pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   3);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T****** pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  4);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T****** pArray, int i1, int i2, int i3, int i4, int i5)
  {
    int         aIndices[5] = {i1, i2, i3, i4, i5};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 5);

    return (pSliceArray);
  };

  template<class T>
  T******                 createSlice(T******* pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T******     pSliceArray = (T******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                      (char*)pArray,
                                                                      aIndices,
                                                                      1);

    return (pSliceArray);
  };

  template<class T>
  T*****                  createSlice(T******* pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T*****      pSliceArray = (T*****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                     (char*)pArray,
                                                                     aIndices,
                                                                     2);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T******* pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    3);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T******* pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   4);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T******* pArray, int i1, int i2, int i3, int i4, int i5)
  {
    int         aIndices[5] = {i1, i2, i3, i4, i5};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  5);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T******* pArray, int i1, int i2, int i3, int i4, int i5, int i6)
  {
    int         aIndices[6] = {i1, i2, i3, i4, i5, i6};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 6);

    return (pSliceArray);
  };

  template<class T>
  T*******                createSlice(T******** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T*******    pSliceArray = (T*******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                       (char*)pArray,
                                                                       aIndices,
                                                                       1);

    return (pSliceArray);
  };

  template<class T>
  T******                 createSlice(T******** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T******     pSliceArray = (T******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                      (char*)pArray,
                                                                      aIndices,
                                                                      2);

    return (pSliceArray);
  };

  template<class T>
  T*****                  createSlice(T******** pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T*****      pSliceArray = (T*****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                     (char*)pArray,
                                                                     aIndices,
                                                                     3);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T******** pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    4);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T******** pArray, int i1, int i2, int i3, int i4, int i5)
  {
    int         aIndices[5] = {i1, i2, i3, i4, i5};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   5);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T******** pArray, int i1, int i2, int i3, int i4, int i5, int i6)
  {
    int         aIndices[6] = {i1, i2, i3, i4, i5, i6};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  6);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T******** pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7)
  {
    int         aIndices[7] = {i1, i2, i3, i4, i5, i6, i7};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 7);

    return (pSliceArray);
  };

  template<class T>
  T********               createSlice(T********* pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T********   pSliceArray = (T********)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                        (char*)pArray,
                                                                        aIndices,
                                                                        1);

    return (pSliceArray);
  };

  template<class T>
  T*******                createSlice(T********* pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T*******    pSliceArray = (T*******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                       (char*)pArray,
                                                                       aIndices,
                                                                       2);

    return (pSliceArray);
  };

  template<class T>
  T******                 createSlice(T********* pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T******     pSliceArray = (T******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                      (char*)pArray,
                                                                      aIndices,
                                                                      3);

    return (pSliceArray);
  };

  template<class T>
  T*****                  createSlice(T********* pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T*****      pSliceArray = (T*****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                     (char*)pArray,
                                                                     aIndices,
                                                                     4);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T********* pArray, int i1, int i2, int i3, int i4, int i5)
  {
    int         aIndices[5] = {i1, i2, i3, i4, i5};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    5);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T********* pArray, int i1, int i2, int i3, int i4, int i5, int i6)
  {
    int         aIndices[6] = {i1, i2, i3, i4, i5, i6};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   6);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T********* pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7)
  {
    int         aIndices[7] = {i1, i2, i3, i4, i5, i6, i7};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  7);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T********* pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
  {
    int         aIndices[8] = {i1, i2, i3, i4, i5, i6, i7, i8};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 8);

    return (pSliceArray);
  };

  template<class T>
  T*********              createSlice(T********** pArray, int i1)
  {
    int         aIndices[1] = {i1};
    T*********  pSliceArray = (T*********)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                         (char*)pArray,
                                                                         aIndices,
                                                                         1);

    return (pSliceArray);
  };

  template<class T>
  T********               createSlice(T********** pArray, int i1, int i2)
  {
    int         aIndices[2] = {i1, i2};
    T********   pSliceArray = (T********)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                        (char*)pArray,
                                                                        aIndices,
                                                                        2);

    return (pSliceArray);
  };

  template<class T>
  T*******                createSlice(T********** pArray, int i1, int i2, int i3)
  {
    int         aIndices[3] = {i1, i2, i3};
    T*******    pSliceArray = (T*******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                       (char*)pArray,
                                                                       aIndices,
                                                                       3);

    return (pSliceArray);
  };

  template<class T>
  T******                 createSlice(T********** pArray, int i1, int i2, int i3, int i4)
  {
    int         aIndices[4] = {i1, i2, i3, i4};
    T******     pSliceArray = (T******)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                      (char*)pArray,
                                                                      aIndices,
                                                                      4);

    return (pSliceArray);
  };

  template<class T>
  T*****                  createSlice(T********** pArray, int i1, int i2, int i3, int i4, int i5)
  {
    int         aIndices[5] = {i1, i2, i3, i4, i5};
    T*****      pSliceArray = (T*****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                     (char*)pArray,
                                                                     aIndices,
                                                                     5);

    return (pSliceArray);
  };

  template<class T>
  T****                   createSlice(T********** pArray, int i1, int i2, int i3, int i4, int i5, int i6)
  {
    int         aIndices[6] = {i1, i2, i3, i4, i5, i6};
    T****       pSliceArray = (T****)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                    (char*)pArray,
                                                                    aIndices,
                                                                    6);

    return (pSliceArray);
  };

  template<class T>
  T***                    createSlice(T********** pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7)
  {
    int         aIndices[7] = {i1, i2, i3, i4, i5, i6, i7};
    T***        pSliceArray = (T***)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                   (char*)pArray,
                                                                   aIndices,
                                                                   7);

    return (pSliceArray);
  };

  template<class T>
  T**                     createSlice(T********** pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
  {
    int         aIndices[8] = {i1, i2, i3, i4, i5, i6, i7, i8};
    T**         pSliceArray = (T**)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                  (char*)pArray,
                                                                  aIndices,
                                                                  8);

    return (pSliceArray);
  };

  template<class T>
  T*                      createSlice(T********** pArray, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
  {
    int         aIndices[9] = {i1, i2, i3, i4, i5, i6, i7, i8, i9};
    T*          pSliceArray = (T*)AdtArrayPlanActor::createSlice(MemAllocator,
                                                                 (char*)pArray,
                                                                 aIndices,
                                                                 9);

    return (pSliceArray);
  };

  // Simplified array creation methods
  // 1D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex, int nSize,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex, nSize,
                                pExisting);
  }

  // 2D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                pExisting);
  }

  // 3D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                pExisting);
  }

  // 4D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                pExisting);
  }

  // 5D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                pExisting);
  }

  // 6D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 int nBaseIndex6, int nSize6,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                pExisting);
  }

  // 7D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 int nBaseIndex6, int nSize6,
                                 int nBaseIndex7, int nSize7,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                pExisting);
  }

  // 8D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 int nBaseIndex6, int nSize6,
                                 int nBaseIndex7, int nSize7,
                                 int nBaseIndex8, int nSize8,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                pExisting);
  }

  // 9D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 int nBaseIndex6, int nSize6,
                                 int nBaseIndex7, int nSize7,
                                 int nBaseIndex8, int nSize8,
                                 int nBaseIndex9, int nSize9,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                nBaseIndex9, nSize9,
                                pExisting);
  }

  // 10D
  template<class T>
  bool                    create(T& pArray,
                                 int nBaseIndex1, int nSize1,
                                 int nBaseIndex2, int nSize2,
                                 int nBaseIndex3, int nSize3,
                                 int nBaseIndex4, int nSize4,
                                 int nBaseIndex5, int nSize5,
                                 int nBaseIndex6, int nSize6,
                                 int nBaseIndex7, int nSize7,
                                 int nBaseIndex8, int nSize8,
                                 int nBaseIndex9, int nSize9,
                                 int nBaseIndex10, int nSize10,
                                 void* pExisting = 0) const
  {
    return AdtArrayPlan::create(MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                nBaseIndex9, nSize9,
                                nBaseIndex10, nSize10,
                                pExisting);
  }

  // Same shape array creation method - copying shape from existing array
  template<class T>
  bool                    create(T& pArray, const T& pRefArray) const
  {
    return (AdtArrayPlan::create(MemAllocator, pArray, pRefArray));
  }

  // array destruction method
  template<class T>
  void                    destroy(T& pArray) const
  {
    AdtArrayPlan::destroy(MemAllocator, pArray);
  }
};

//  ----------------------------------------------------------------------------

inline const AdtMemAllocator& AdtArrays::memAllocator() const
{
  return (MemAllocator);
}

//  ----------------------------------------------------------------------------

inline AdtADStack& AdtArrays::stack() const
{
  return (Stack);
}


#endif //AD

#endif //__ADT_ARRAYS__
