AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
//  SWITCHES: "rebuild","Oarray";
  SWITCHES: "rebuild","Oarray","WithStackSubstitution";
  BLACKBOX: common.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D_REDev(REDev) SOURCE FILE: REDev.cpp OUTPUT FILES: d_REDev.cpp d_REDev.hpp
  BEGIN
    FUNCTION=logLikelihood OUTVAR=logLikelihood VAR=re MODE=f PRAGMAS="PushPopDisable";  // f'u(u,theta)       - forward mode
    FUNCTION=logLikelihood OUTVAR=logLikelihood VAR=re MODE=r PRAGMAS="PushPopDisable";  // f'u(u,theta)       - reverse mode
  END

  CLASS DR_REDevA(R_REDevA) SOURCE FILE: R_REDevA.cpp OUTPUT FILES: dR_REDevA.cpp dR_REDevA.hpp
  BEGIN
    FUNCTION=diffRE OUTVAR=diffRE VAR=re MODE=r PRAGMAS="PushPopDisable";     // f''uu(u,theta)                       - reverse mode
    FUNCTION=diffRE OUTVAR=diffRE VAR=re,par MODE=r PRAGMAS="PushPopDisable"; // f''uu(u,theta) & f''utheta(u,theta)  - reverse mode
  END

  CLASS DR_REDevB(R_REDevB) SOURCE FILE: R_REDevB.cpp OUTPUT FILES: dR_REDevB.cpp dR_REDevB.hpp
  BEGIN
    FUNCTION=laplace OUTVAR=laplace VAR=re,par MODE=r PRAGMAS="PushPopDisable";
  END

  CLASS DR_REDevC(R_REDevC) SOURCE FILE: R_REDevC.cpp OUTPUT FILES: dR_REDevC.cpp dR_REDevC.hpp
  BEGIN

  END
END
