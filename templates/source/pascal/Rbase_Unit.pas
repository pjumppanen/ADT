// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------

{$mode objfpc}
{$modeswitch autoderef}
{$modeswitch duplicatelocals}
{$H+}
unit R$(filename)_Unit;

interface

uses
  D$(filename)_Unit,
  adtcommon,
  adtarray,
  adtR,
  Raccess,
  Math;

type
  R$(classname) = class(D$(classname))
  protected
    // Required to avoid ADT compile error when no variables have been defined
    // Delete after you've added some variables
    crdummy : longint;
    {AD_LIBNAME $(libname)}
    {AD_ALIAS R$(short-classname)=RI$(classname), D$(classname)}
    {AUTOINIT}
    {AUTODEC}

    {$I include/R$(short-classname)_array_plans.pas}

  public
    constructor create({$I include/R$(short-classname)_constructor_args.pas}); overload;
    constructor create(const rCopy : R$(classname)); overload;
  end;

implementation

// ----------------------------------------------------------------------------

  constructor R$(classname).create({$I include/R$(short-classname)_constructor_args.pas}); overload;

  var
    dummy : longint;
    {$I include/R$(short-classname)_constructor_locals.pas}

  begin
    inherited create;

    {$I include/R$(short-classname)_constructor_scalars_phase_1.pas}
    {$I include/R$(short-classname)_constructor_arrays_phase_1.pas}
    {$I include/R$(short-classname)_array_plans_init.pas}
  end;

  // ----------------------------------------------------------------------------

  constructor R$(classname).create(const rCopy : R$(classname)); overload;

  begin
    inherited create(@rCopy, false);
  end;

end.
