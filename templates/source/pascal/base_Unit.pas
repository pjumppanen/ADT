// ----------------------------------------------------------------------------
$(title-comment)
// ----------------------------------------------------------------------------

{$mode objfpc}
{$modeswitch autoderef}
{$modeswitch duplicatelocals}
{$H+}
unit $(filename)_Unit;

interface

uses
  adtcommon,
  adtarray,
  adtR,
  Raccess,
  Math;

type
  $(classname) = class(AdtArrays)
  protected
    // Required to avoid ADT compile error when no variables have been defined
    // Delete after you've added some variables
    cdummy : longint;
    {AD_LIBNAME $(libname)}
    {AD_ALIAS $(short-classname)=D$(classname)}
    {AUTOINIT}
    {AUTODEC}

    {$I include/$(short-classname)_array_plans.pas}

  public
    constructor create({$I include/$(short-classname)_constructor_args.pas}); overload;
    constructor create(const rCopy : $(classname)); overload;
  end;

implementation

// ----------------------------------------------------------------------------

  constructor $(classname).create({$I include/$(short-classname)_constructor_args.pas}); overload;

  var
    dummy : longint;
    {$I include/$(short-classname)_constructor_locals.pas}

  begin
    inherited create;

    {$I include/$(short-classname)_constructor_scalars_phase_1.pas}
    {$I include/$(short-classname)_constructor_arrays_phase_1.pas}
    {$I include/$(short-classname)_array_plans_init.pas}
  end;

  // ----------------------------------------------------------------------------

  constructor $(classname).create(const rCopy : $(classname)); overload;

  begin
    inherited create(@rCopy, false);
  end;

end.
