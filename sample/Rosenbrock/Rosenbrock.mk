AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray";
  BLACKBOX: common.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D_MinRosenbrock(MinRosenbrock) SOURCE FILE: Rosenbrock.cpp OUTPUT FILES: d_Rosenbrock.cpp d_Rosenbrock.hpp
  BEGIN
    FUNCTION=rosenbrock OUTVAR=rosenbrock VAR=X MODE=r;
    FUNCTION=ROSENBROCK_BX OUTVAR=xb1_x VAR=X MODE=f;
  END

  CLASS DR_MinRosenbrock(R_MinRosenbrock) SOURCE FILE: R_Rosenbrock.cpp OUTPUT FILES: dR_Rosenbrock.cpp dR_Rosenbrock.hpp
  BEGIN

  END
END
