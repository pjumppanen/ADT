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
//    adterror.cpp
//
//  Purpose:
//    This file includes implementations of error and warning reporting
//    functions needed when not linking against the R shared library (ie.
//    using the R standalone library).
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtmaths.hpp"
#include <stdio.h>
#include <stdarg.h>


//  ----------------------------------------------------------------------------
//  Error fallback functions when not linking to R shared lib
//  ----------------------------------------------------------------------------
void Rf_error(const char* pFormat, ...)
{
  va_list argList;

  va_start(argList, pFormat);
  ::vprintf(pFormat, argList);
  va_end(argList);
}

//  ----------------------------------------------------------------------------

void Rf_warning(const char* pFormat, ...)
{
  va_list argList;

  va_start(argList, pFormat);
  ::vprintf(pFormat, argList);
  va_end(argList);
}
