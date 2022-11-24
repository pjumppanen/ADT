AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  INCLUDE DIRECTORY: "./include/";
  SWITCHES: "rebuild","Oarray";//,"ThrowException";
  BLACKBOX: ArrayTest.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS R_ArrayTest(ArrayTest) SOURCE FILE: ArrayTest.cpp OUTPUT FILES: R_ArrayTest.cpp R_ArrayTest.hpp
  BEGIN
    BOUNDS CHECK boundsCheckTest;
    FUNCTION=polySum3D OUTVAR=polySum3D VAR=X MODE=r;
    FUNCTION=sum OUTVAR=sum VAR=X MODE=r;
    FUNCTION=polySumA OUTVAR=polySumA VAR=X MODE=r;
    FUNCTION=polySumB OUTVAR=polySumB VAR=X MODE=r;
    FUNCTION=polySumC OUTVAR=polySumC VAR=X MODE=r;
    FUNCTION=ifTest OUTVAR=ifTest VAR=X MODE=r;
    FUNCTION=test_one_if OUTVAR=test_one_if VAR=v MODE=f;
    FUNCTION=test_one_if OUTVAR=test_one_if VAR=v MODE=r;
    FUNCTION=test_one_if_internal OUTVAR=test_one_if_internal VAR=v MODE=f;
    FUNCTION=test_one_if_internal OUTVAR=test_one_if_internal VAR=v MODE=r;

    DIFF=trigA OUTVAR=rOut VAR=x,y;
    DIFF=trigB OUTVAR=trigB VAR=x,y;
    MULTIDIFF=trigA OUTVAR=rOut VAR=x,y;
    MULTIDIFF=trigB OUTVAR=trigB VAR=x,y;
    GRAD=trigA OUTVAR=rOut VAR=x,y;
    GRAD=trigB OUTVAR=trigB VAR=x,y;
    MULTIGRAD=trigA OUTVAR=rOut VAR=x,y;
    MULTIGRAD=trigB OUTVAR=trigB VAR=x,y;
  END
END
