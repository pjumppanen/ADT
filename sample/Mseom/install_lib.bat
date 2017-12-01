REM This batch file installs the dll into the run location for the code
SET bat_path=%~dp0
copy %bat_path%\*.r %bat_path%\MSE-IO-BET-YFT\lib
copy %bat_path%\..\..\objs\x64\Release\Mseom.dll %bat_path%\MSE-IO-BET-YFT\lib
