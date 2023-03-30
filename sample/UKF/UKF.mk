AD BEGIN
  PATHS: "../include", "../../src/ADLib";
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild","Oarray";
  BLACKBOX: common.bbdef;
  CPP OPTIONS FILE: cpp_macros.txt;
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS I_UnscentedKalmanFilter(UnscentedKalmanFilter) SOURCE FILE: UKF.cpp OUTPUT FILES: I_UKF.cpp I_UKF.hpp
  BEGIN

  END
END
