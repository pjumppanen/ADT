// -----------------------------------------------------------------------
// Test minimisation code for ADT. This mimimisation problem is the
// Rosenbrock bananna function generalised to N dimensions. This is an
// R interface on top of the D_MinRosenbrock class
// -----------------------------------------------------------------------
{$mode delphi}{$H+}
unit R_MinRosenbrock_Unit;

interface

uses
  adtcommon,
  adtarray,
  adtR,
  Raccess,
  MinRosenbrock_Unit,
  D_MinRosenbrock_Unit;

type
  R_MinRosenbrock = class(D_MinRosenbrock)
    {AD_ALIAS RRb=DR_MinRosenbrock, D_MinRosenbrock}
    {AUTODEC 1}
    lxb1_x{1:N} : ARRAY_1D;
    lxd2_x{1:N} : ARRAY_1D;
    {$I RRb_array_plans.pas}

    constructor create({$I RRb_constructor_args.pas});

    procedure hessian(pX{1:N} : ARRAY_1D; var pHessian{1:N,1:N} : ARRAY_2D);
  end;

implementation

// ----------------------------------------------------------------------------

constructor R_MinRosenbrock.create({$I RRb_constructor_args.pas});

var
  dummy : longint;
  {$I RRb_constructor_locals.pas}

begin
  inherited create({$I RRb_constructor_call_args.pas});

  {$I RRb_constructor_scalars_phase_1.pas}
  {$I RRb_constructor_arrays_phase_1.pas}
  {$I RRb_array_plans_init.pas}
end;

// -----------------------------------------------------------------------

procedure R_MinRosenbrock.hessian(pX{1:N} : ARRAY_1D; var pHessian{1:N,1:N} : ARRAY_2D);

var
  rosenbrockb1_x  : double;
  cn              : LongInt;

begin
  rosenbrockb1_x := 1.0;

  for cn := 1 to N do
  begin
    lxd2_x[cn] := 0.0;
  end;

  for cn := 1 to N do
  begin
    lxd2_x[cn] := 1.0;

    // Hessian matrix is symmetric and we construct the matrix row by row by
    // taking the tangent mode derivative of the gradient in each basis
    // direction. The hessian result goes into an ARRAY_2D but we pass the
    // n'th column to be filled by indexing the array.
    ROSENBROCK_BX_DX(pX, lxd2_x, lxb1_x, pHessian[cn], rosenbrockb1_x);

    lxd2_x[cn] := 0.0;
  end;
end;

// ----------------------------------------------------------------------------

end.
