AD
BEGIN
  WORKING DIRECTORY: "./work/";
  INCLUDE DIRECTORY: "./include/";
  SWITCHES: "rebuild";
  PASCAL OPTIONS FILE: pascal_macros.txt;
  FORTRAN INCLUDE FILES: stdlib.f;

  CLASS D$(classname)($(classname)) SOURCE FILE: $(filename)_unit.pas OUTPUT FILE: D$(filename)_unit.pas
  BEGIN

  END

  CLASS RI$(classname)(R$(classname)) SOURCE FILE: R$(filename)_unit.pas OUTPUT FILE: RI$(filename)_unit.pas
  BEGIN

  END
END
