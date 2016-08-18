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
//    adterror.pas
//
//  Purpose:
//    This file implements error and warning reporting functions needed when
//    not linking against the R shared library (ie. using the R standalone
//    library).
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
Unit adterror;

interface

implementation

//  ----------------------------------------------------------------------------

procedure _log_error(sMsg : AnsiString); public name 'log_error';

begin
  writeln(sMsg);
end;

//  ----------------------------------------------------------------------------

procedure _log_warning(sMsg : AnsiString); public name 'log_warning';

begin
  writeln(sMsg);
end;

end.
