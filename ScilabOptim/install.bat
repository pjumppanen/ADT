SET bat_path=%~dp0
copy /Y %bat_path%\lib\x64\ScilabOptim.dll %bat_path%\..\objs\x64\Debug
copy /Y %bat_path%\lib\x64\ScilabOptim.dll %bat_path%\..\objs\x64\Release
