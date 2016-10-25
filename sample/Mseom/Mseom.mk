AD BEGIN
  PATHS: "../common", "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  BLACKBOX: Mseom.bbdef;
  SWITCHES: "rebuild","Oarray";
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D_OperatingModelBase(OperatingModelBase) SOURCE FILE: Mseom.cpp OUTPUT FILES: D_Mseom.cpp D_Mseom.hpp
  BEGIN
    FUNCTION=MSYrefs_objective OUTVAR=MSYrefs_objective VAR=par MODE=f;
    FUNCTION=popdyn_projection_objective OUTVAR=popdyn_projection_objective VAR=par MODE=r PRAGMAS='PushPopDisable';
  END

  CLASS D_OperatingModelMin(OperatingModelMin) SOURCE FILE: MseomMin.cpp OUTPUT FILES: D_MseomMin.cpp D_MseomMin.hpp
  BEGIN

  END
END
