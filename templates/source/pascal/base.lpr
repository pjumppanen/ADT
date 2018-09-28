library $(filename);

{$mode objfpc}{$H+}

uses
  Classes, $(filename)_unit, D$(filename)_unit, R$(filename)_unit, RI$(filename)_unit, adtarray, adtR, Raccess;

// ----------------------------------------------------------------------------

{$I include/R$(short-classname)_impl_lib_registration.pas}

exports
  {$I include/R$(short-classname)_lib_exports.pas};

begin

end.
