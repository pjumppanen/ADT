AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray";
  BLACKBOX: ArrayTest.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS R_ArrayTest(ArrayTest) SOURCE FILE: ArrayTest_Unit.pas OUTPUT FILE: R_ArrayTest_Unit.pas
  BEGIN
    FUNCTION=sum OUTVAR=sum VAR=X MODE=r;
    FUNCTION=polySumA OUTVAR=polySumA VAR=X MODE=r;
    FUNCTION=polySumB OUTVAR=polySumB VAR=X MODE=r;
    FUNCTION=polySumC OUTVAR=polySumC VAR=X MODE=r;
  END
END
