// ----------------------------------------------------------------------------
// Test code for ADT Arrays.
// ----------------------------------------------------------------------------

{$mode objfpc}
{$modeswitch autoderef}
{$modeswitch duplicatelocals}
{$H+}
unit ArrayTest_Unit;

interface

uses
  adtcommon,
  adtarray,
  adtR,
  Raccess,
  Math;

const
  // Test global constants
  male   = 1;
  female = 2;
  n_sex  = 2;

type
  ArrayTest = class(AdtArrays)
  protected
    {AD_LIBNAME ArrayTestPas}
    {AD_ALIAS AT=R_ArrayTest}
    {AUTOINIT 1}
    ix : integer;
    iy : integer;

    // Test 1D arrays
    A1_I {1:1+ix}       : ARRAY_1I;
    A1_D {1:ix}         : ARRAY_1D;
    A2_IA{1+ix,-1:iy}   : ARRAY_2I;
    A2_IB{-1:iy,1+ix}   : ARRAY_2I;
    A2_DA{1+ix,1:n_sex} : ARRAY_2D;

    // Test longbool arrays
    A2_LB{1+ix,-1:iy} : ARRAY_2LB;

    // Test Raw array types
    A2_C {1+ix,-1:iy} : ARRAY_2C;
    A2_UC{1+ix,-1:iy} : ARRAY_2UC;
    A2_B {1+ix,-1:iy} : ARRAY_2B;

    // Bool and longbool singulars
    SingularBool      : boolean;
    SingularLongbool  : longbool;

    { AUTODEC 2 }
    A3_DA{-1:iy,1+ix,A2_IA[<2>,<1>]+A2_IB[<1>,<2>]} : ARRAY_3D;
    A3_DB{-1:iy,1+ix,A2_IA[<-1>,<-2>]}              : ARRAY_3D;
    A3_DC{-1:iy,1+ix,A1_I[<-1>]}                    : ARRAY_3D;
    A3_DD{1+ix,-1:iy,A1_I[<-2>]}                    : ARRAY_3D;

    { AUTODEC NO_INTERFACE }
    A1_B {1:ix} : ARRAY_1B;
    A1_C {1:ix} : ARRAY_1C;
    A1_L {1:ix} : ARRAY_1L;
    A1_F {1:ix} : ARRAY_1F;
    A1_UC{1:ix} : ARRAY_1UC;
    A1_UL{1:ix} : ARRAY_1UL;
    A1_US{1:ix} : ARRAY_1US;

    // Check for null sized arrays
    N1_D{1:0} : ARRAY_1D;

    {$I include/AT_array_plans.pas}

  protected
    function polyA(x : double) : double;
    function polyB(x : double) : double;

    {$IFNDEF AD}
    { This function is used to test stand-alone black box definitions so we
      don't want it to be included in any AD processing. }
    function polyC(x : double) : double;
    {$ENDIF}

    function t_one_if(bTrue : boolean) : integer;
    function ifTest(x : double) : double;

  public
    constructor create({$I include/AT_constructor_args.pas}); overload;
    constructor create(const rCopy : ArrayTest); overload;

    // Function to test the interface generation on functions with no args
    function sumA1_D() : double;

    function sum(const X{1:ix} : ARRAY_1D) : double;
    function polySumA(const X{1:ix} : ARRAY_1D) : double;
    function polySumB(const X{1:ix} : ARRAY_1D) : double;
    function polySumC(const X{1:ix} : ARRAY_1D) : double;
    function polySum3D(const X{1:1 + ix} : ARRAY_1D) : double;
    function boundsCheckTest(const X{1:ix} : ARRAY_1D) : double; virtual;
    function test_one_if(v : double) : double;
    function test_one_if_internal(v : double) : double;

    function isNegative(dValue : double) : boolean;
    function isPositive(dValue : double) : longbool;
  end;

  function global_sum(const Y{nBase:nCount} : ARRAY_1D; nBase, nCount : integer) : double;

implementation

// ----------------------------------------------------------------------------

  {< D/D(x) (4 * x) - 5; >}
  function ArrayTest.polyA(x : double) : double;

  begin
    Result := (2 * x * x) - (5 * x) + 3;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.polyB(x : double) : double;

  begin
    Result := (2 * x * x) - (5 * x) + 3;
  end;

// ----------------------------------------------------------------------------

  {$IFNDEF AD}

  function ArrayTest.polyC(x : double) : double;

  begin
    Result := (2 * x * x) - (5 * x) + 3;
  end;

  {$ENDIF}

// ----------------------------------------------------------------------------

  function ArrayTest.t_one_if(bTrue : boolean) : integer;

  begin
    if (bTrue) then
      Result := 1
    else
      Result := 0;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.ifTest(x : double) : double;

  var
    dValue : double;

  begin
    dValue := polyB(x);

    if (dValue > 0.0) then
      dValue := dValue * 2.0;

    if (true) then
    begin
      if (dValue > 1.0) then
      begin
        dValue := dValue * 1.5;
      end;
    end;

    Result := dValue;
  end;

// ----------------------------------------------------------------------------

  constructor ArrayTest.create({$I include/AT_constructor_args.pas}); overload;

  var
    dummy : longint;
    {$I include/AT_constructor_locals.pas}

  begin
    inherited create;

    {$I include/AT_constructor_scalars_phase_1.pas}
    {$I include/AT_constructor_arrays_phase_1.pas}
    {$I include/AT_constructor_scalars_phase_2.pas}
    {$I include/AT_constructor_arrays_phase_2.pas}
    {$I include/AT_array_plans_init.pas}
  end;

  // ----------------------------------------------------------------------------

  constructor ArrayTest.create(const rCopy : ArrayTest); overload;

  begin
    inherited create(@rCopy, false);
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.sumA1_D() : double;

  var
    cn   : integer;
    dSum : double;

  begin
    dSum := 0.0;

    for cn := 1 to ix do
    begin
      dSum := dSum + A1_D[cn];
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.sum(const X{1:ix} : ARRAY_1D) : double;

  begin
    Result := global_sum(X, 1, ix) + X[male] + X[female];
  end;

// ----------------------------------------------------------------------------

// Note that putting AD NOCHECKPOINT outside of a function appears to be a
// bad thing to do from a Tapenade perspective and results in no differential
// being created. I don't know if this makes any sense and whether the behaviour
// is errant but Tapenade does not throw any warnings about it. As it breaks
// my test harness I've put "bad" in front of the pragma to ensure it isn't
// used as it will break the test harness.
  { $bad AD NOCHECKPOINT }
  function ArrayTest.polySumA(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    { $AD NOCHECKPOINT }
    for cn := 1 to ix do
    begin
      dSum := dSum + polyA(X[cn]);
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.polySumB(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    for cn := 1 to ix do
    begin
      dSum := dSum + polyB(X[cn]);
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.polySumC(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    for cn := 1 to ix do
    begin
      dSum := dSum + polyC(X[cn]);
    end;

    Result := dSum;
  end;

  // ----------------------------------------------------------------------------

  function ArrayTest.polySum3D(const X{1:1 + ix} : ARRAY_1D) : double;

  var
    cx    : integer;
    cy    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    for cx := 1 to 1 + ix do
    begin
      for cy := -1 to iy do
      begin
        dSum := dSum + polyC(X[cx] * A3_DD[cx][cy][A1_I[cx]]);
      end;
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function global_sum(const Y{nBase:nCount} : ARRAY_1D; nBase, nCount : integer) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    for cn := nBase to nBase + nCount - 1 do
    begin
      dSum := dSum + Y[cn];
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.boundsCheckTest(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;
    dR    : double;

  begin
    dSum := 0.0;
    dR   := 0.9;

    // Make indexing step over the line on purpose. Bounds error!
    for cn := 1 to ix + 5 do
    begin
      dSum := dSum + power(dR, dSum * power(dR, X[cn]));
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.test_one_if(v : double) : double;

  begin
    Result := power((t_one_if(v > 0.0) - t_one_if(v > 30.0)) * v, 5);
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.test_one_if_internal(v : double) : double;

  begin
    Result := power((one_if(v > 0.0) - one_if(v > 30.0)) * v, 5);
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.isNegative(dValue : double) : boolean;

  begin
    Result := (dValue < 0.0);
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.isPositive(dValue : double) : longbool;

  begin
    if (dValue >= 0.0) then
      Result := true
    else
      Result := false;
  end;

end.
