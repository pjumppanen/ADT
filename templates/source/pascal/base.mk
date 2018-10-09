AD
BEGIN
  WORKING DIRECTORY: "./work/";
  INCLUDE DIRECTORY: "./include/";
  SWITCHES: "rebuild";
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D$(classname)($(classname)) SOURCE FILE: $(filename)_Unit.pas OUTPUT FILE: D$(filename)_Unit.pas
  BEGIN

  END

  CLASS RI$(classname)(R$(classname)) SOURCE FILE: R$(filename)_Unit.pas OUTPUT FILE: RI$(filename)_Unit.pas
  BEGIN

  END
END
