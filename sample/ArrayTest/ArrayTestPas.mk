AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray"; //,"ThrowException";
  BLACKBOX: ArrayTest.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS R_ArrayTest(ArrayTest) SOURCE FILE: ArrayTest_Unit.pas OUTPUT FILE: R_ArrayTest_Unit.pas
  BEGIN
    BOUNDS CHECK boundsCheckTest;
    FUNCTION=sum OUTVAR=sum VAR=X MODE=r;
    FUNCTION=polySumA OUTVAR=polySumA VAR=X MODE=r;
    FUNCTION=polySumB OUTVAR=polySumB VAR=X MODE=r;
    FUNCTION=polySumC OUTVAR=polySumC VAR=X MODE=r;
    FUNCTION=ifTest OUTVAR=ifTest VAR=X MODE=r;
    FUNCTION=test_one_if OUTVAR=test_one_if VAR=v MODE=f;
    FUNCTION=test_one_if OUTVAR=test_one_if VAR=v MODE=r;
    FUNCTION=test_one_if_internal OUTVAR=test_one_if_internal VAR=v MODE=f;
    FUNCTION=test_one_if_internal OUTVAR=test_one_if_internal VAR=v MODE=r;
  END
END
