// -----------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the
// Rosenbrock bananna function generalised to N dimensions.
// -----------------------------------------------------------------------
{$mode delphi}{$H+}
unit MinRosenbrock_Unit;

interface

uses
  adtcommon,
  adtarray,
  adtR,
  Raccess;

type
  MinRosenbrock = class(AdtArrays)
    {AD_LIBNAME RosenbrockPas}
    {AD_ALIAS Rb=D_MinRosenbrock}
    {AUTOINIT}
    N: integer;

    {MANUAL}
    No2: integer;

    {$I Rb_array_plans.pas}

    constructor create({$I Rb_constructor_args.pas});overload;
    constructor create(const rCopy : MinRosenbrock);overload;

    function rosenbrock(const X{N}: ARRAY_1D):double;
  end;

implementation

//------------------------------------------------------------------------

  constructor MinRosenbrock.create({$I Rb_constructor_args.pas});

  var
    dummy : longint;
    {$I Rb_constructor_locals.pas}

  begin
    inherited create;

    {$I Rb_constructor_scalars_phase_1.pas}
    {$I Rb_constructor_arrays_phase_1.pas}
    {$I Rb_array_plans_init.pas}

    // I need to put this here because div is not translatable to fortran in
    // any circularly consistent manner.
    No2 := arg_N div 2;
  end;

  //------------------------------------------------------------------------

  constructor MinRosenbrock.create(const rCopy : MinRosenbrock);

  begin
    inherited create;

    N   := rCopy.N;
    No2 := rCopy.N;
  end;

//------------------------------------------------------------------------

  function MinRosenbrock.rosenbrock(const X{N}: ARRAY_1D):double;

  var
    cn:           integer;
    dSum:         double;
    p1,p2,f1,f2:  double;

  begin
    dSum := 0.0;

    for cn := 1 TO No2 do
    begin
      p1 := X[2 * cn - 1];
      p2 := X[2 * cn];
      f1 := (p1 * p1 - p2);
      f1 := 100 * f1 * f1;
      f2 := (p1 - 1.0);
      f2 := f2 * f2;

      dSum := dSum + f1 + f2;
    end;

    result := dSum;
  end;

end.
