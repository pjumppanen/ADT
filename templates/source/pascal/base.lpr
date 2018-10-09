library $(filename);

{$mode objfpc}{$H+}

uses
  Classes, $(filename)_Unit, D$(filename)_Unit, R$(filename)_Unit, RI$(filename)_Unit, adtarray, adtR, Raccess;

// ----------------------------------------------------------------------------

{$I include/R$(short-classname)_impl_lib_registration.pas}

exports
  {$I include/R$(short-classname)_lib_exports.pas};

begin

end.
