unit Rloader;

interface

PROCEDURE load_R_routines(
      variables: ARRAY OF PPOINTER;
      export_names: ARRAY OF STRING);

implementation

USES
  SysUtils, {$IFDEF FPC} dynlibs {$ELSE} Windows {$ENDIF};

VAR
  Rdll_handle: INTEGER = 0;

PROCEDURE load_R_routines(
      variables: ARRAY OF PPOINTER;
      export_names: ARRAY OF STRING);
VAR
  i: INTEGER;
BEGIN
  IF HIGH( export_names) <> HIGH( variables) THEN
RAISE Exception. Create( 'Mismatched # names and # procs in "load_R_routines"');

  IF Rdll_handle=0 THEN BEGIN
    {$IFDEF FPC}
    Rdll_handle:= LoadLibrary( GetEnvironmentVariable( 'R_LATEST') + '\BIN\R.DLL'); // lets it find Rxxx.DLL
    {$ELSE}
    Rdll_handle:= LoadLibraryEx( PCHAR( GetEnvironmentVariable( 'R_LATEST') + '\BIN\R.DLL'),
        0, LOAD_WITH_ALTERED_SEARCH_PATH); // lets it find Rxxx.DLL
    {$ENDIF}
    IF Rdll_handle=0 THEN
      Rdll_handle:= LoadLibrary( 'R.DLL');
    IF Rdll_handle=0 THEN
RAISE Exception. Create( 'Can''t find R.DLL');
  END;

  FOR i:= LOW( variables) TO HIGH( variables) DO
    IF variables[i]=NIL THEN
RAISE Exception. Create( 'NIL POINTER in call to "load_R_routines"; probably want @@')
    ELSE IF variables[i]^=NIL THEN BEGIN
      variables[ i]^:= GetProcAddress( Rdll_handle, PCHAR( export_names[ i]));
      IF variables[i]^ = NIL THEN
RAISE Exception. Create( 'Can''t find "' + export_names[ i] + '" in R.dll');
    END;
END;

INITIALIZATION
FINALIZATION
  IF Rdll_handle <> 0 THEN
    FreeLibrary( Rdll_handle);
END.
