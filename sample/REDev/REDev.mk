AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray";
  BLACKBOX: common.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D_REDev(REDev) SOURCE FILE: REDev.cpp OUTPUT FILES: d_REDev.cpp d_REDev.hpp
  BEGIN
    FUNCTION=logLikelihood OUTVAR=logLikelihood VAR=X MODE=r;
    FUNCTION=LOGLIKELIHOOD_BX OUTVAR=xb1_x VAR=X MODE=f;
  END

  CLASS DR_REDev(R_REDev) SOURCE FILE: R_REDev.cpp OUTPUT FILES: dR_REDev.cpp dR_REDev.hpp
  BEGIN

  END
END
