AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray";
  BLACKBOX: common.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D_MinRosenbrock(MinRosenbrock) SOURCE FILE: MinRosenbrock_Unit.pas OUTPUT FILE: D_MinRosenbrock_Unit.pas
  BEGIN
    FUNCTION=rosenbrock OUTVAR=rosenbrock VAR=X MODE=r;
    FUNCTION=ROSENBROCK_BX OUTVAR=xb1_x VAR=X MODE=f;
  END

  CLASS DR_MinRosenbrock(R_MinRosenbrock) SOURCE FILE: R_MinRosenbrock_Unit.pas OUTPUT FILE: DR_MinRosenbrock_Unit.pas
  BEGIN

  END
END
