AD BEGIN
  WORKING DIRECTORY: "./work/";
  SWITCHES: "rebuild";
  CPP OPTIONS FILE: cpp_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D$(classname)($(classname)) SOURCE FILE: $(filename).cpp OUTPUT FILES: D$(filename).cpp D$(filename).hpp
  BEGIN

  END

  CLASS RI$(classname)(R$(classname)) SOURCE FILE: R$(filename).cpp OUTPUT FILES: RI$(filename).cpp RI$(filename).hpp
  BEGIN

  END
END
