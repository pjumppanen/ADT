REM create R import library to interface with R.dll
REM setup VS environment
SET bat_path=%~dp0
for /f "usebackq delims=#" %%a in (`"%programfiles(x86)%\Microsoft Visual Studio\Installer\vswhere" -latest -property installationPath`) do set VsDevCmd_Path=%%a\Common7\Tools\VsDevCmd.bat
IF "%FrameworkVersion%"=="" "%VsDevCmd_Path%"

REM create VS import libs
LIB /DEF:ScilabOptim.def /OUT:%bat_path%..\..\objs\win32\debug\ScilabOptim.lib /MACHINE:X86
LIB /DEF:ScilabOptim.def /OUT:%bat_path%..\..\objs\win32\release\ScilabOptim.lib /MACHINE:X86
LIB /DEF:ScilabOptim.def /OUT:%bat_path%..\..\objs\x64\debug\ScilabOptim.lib /MACHINE:X64
LIB /DEF:ScilabOptim.def /OUT:%bat_path%..\..\objs\x64\release\ScilabOptim.lib /MACHINE:X64
