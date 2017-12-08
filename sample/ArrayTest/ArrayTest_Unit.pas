// ----------------------------------------------------------------------------
// Test code for ADT Arrays.
// ----------------------------------------------------------------------------

{$mode delphi}{$H+}
unit ArrayTest_Unit;

interface

uses
  adtcommon,
  adtarray,
  adtR,
  Raccess,
  Math;

const
  male   = 1;
  female = 2;

type
  ArrayTest = class(AdtArrays)
  protected
    {AD_LIBNAME ArrayTestPas}
    {AD_ALIAS AT=R_ArrayTest}
    {AUTOINIT 1}
    ix : integer;
    iy : integer;

    // Test 1D arrays
    A1_I {1:1+ix}     : ARRAY_1I;
    A1_D {1:ix}       : ARRAY_1D;
    A2_IA{1+ix,-1:iy} : ARRAY_2I;
    A2_IB{-1:iy,1+ix} : ARRAY_2I;

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

    {$I AT_array_plans.pas}

  protected
    { D/D(x) (4 * x) - 5; }
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
    constructor create({$I AT_constructor_args.pas}); overload;
    constructor create(const rCopy : ArrayTest); overload;

    // Function to test the interface generation on functions with no args
    function sumA1_D() : double;

    function sum(const X{1:ix} : ARRAY_1D) : double;
    function polySumA(const X{1:ix} : ARRAY_1D) : double;
    function polySumB(const X{1:ix} : ARRAY_1D) : double;
    function polySumC(const X{1:ix} : ARRAY_1D) : double;
    function boundsCheckTest(const X{1:ix} : ARRAY_1D) : double; virtual;
    function test_one_if(v : double) : double;
    function test_one_if_internal(v : double) : double;
  end;

  function global_sum(const X{1:ix} : ARRAY_1D; nBase, nCount : integer) : double;

implementation

// ----------------------------------------------------------------------------

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

  constructor ArrayTest.create({$I AT_constructor_args.pas}); overload;

  var
    dummy : longint;
    {$I AT_constructor_locals.pas}

  begin
    inherited create;

    {$I AT_constructor_scalars_phase_1.pas}
    {$I AT_constructor_arrays_phase_1.pas}
    {$I AT_constructor_scalars_phase_2.pas}
    {$I AT_constructor_arrays_phase_2.pas}
    {$I AT_array_plans_init.pas}
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

  function ArrayTest.polySumA(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

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

  function global_sum(const X{1:ix} : ARRAY_1D; nBase, nCount : integer) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    for cn := nBase to nBase + nCount - 1 do
    begin
      dSum := dSum + X[cn];
    end;

    Result := dSum;
  end;

// ----------------------------------------------------------------------------

  function ArrayTest.boundsCheckTest(const X{1:ix} : ARRAY_1D) : double;

  var
    cn    : integer;
    dSum  : double;

  begin
    dSum := 0.0;

    // Make indexing step over the line on purpose. Bounds error!
    for cn := 1 to ix + 5 do
    begin
      dSum := dSum + X[cn];
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

end.
