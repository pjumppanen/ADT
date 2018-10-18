; ADT inno setup installer script
[Setup]
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
OutputBaseFilename=ADT-1.09.5_x64_setup
AppName=ADT
AppVersion=1.09.5
DefaultDirName={pf}\ADT
DefaultGroupName=ADT
Compression=lzma2
SolidCompression=yes
ChangesEnvironment=yes
AppPublisher=CSIRO

[Files]
Source: ".\objs\x64\Release\adt.exe"; DestDir: "{app}\bin"
Source: ".\sample\include\*"; DestDir: "{app}\bin\adt-include"
Source: ".\doc\users-manual.pdf"; DestDir: "{app}"
Source: ".\doc\Presentation\*"; DestDir: "{app}\Presentation"
Source: ".\doc\Presentation\slidy\*"; DestDir: "{app}\Presentation\slidy"
Source: ".\templates\make\autoconf\*"; DestDir: "{app}\templates\make\autoconf"
Source: ".\templates\make\VisualStudio\*"; DestDir: "{app}\templates\make\VisualStudio"
Source: ".\templates\make\Lazarus\*"; DestDir: "{app}\templates\make\Lazarus"
Source: ".\templates\make\Xcode\*"; DestDir: "{app}\templates\make\Xcode"
Source: ".\templates\source\cpp\*"; DestDir: "{app}\templates\source\cpp"
Source: ".\templates\source\pascal\*"; DestDir: "{app}\templates\source\pascal"
Source: ".\templates\R\newadt_1.04.zip"; DestDir: "{app}\templates\R"
Source: ".\src\ADLib\*"; DestDir: "{app}\src\cpp"
Source: ".\src\ADLibPascal\*"; DestDir: "{app}\src\pascal"
Source: ".\src\ADLibPascal\fcl-stl\*"; DestDir: "{app}\src\pascal\fcl-stl"
Source: ".\src\ADLib\*.hpp"; DestDir: "{app}\include"
Source: ".\src\RMath\include\*.h"; DestDir: "{app}\include\RMath"
Source: ".\src\RMath\include\R_ext\*.h"; DestDir: "{app}\include\RMath\R_ext"
Source: ".\objs\Win32\Release\ADLib.lib"; DestDir: "{app}\lib\win32\release"
Source: ".\objs\Win32\Release\ADLibErr.lib"; DestDir: "{app}\lib\win32\release"
Source: ".\objs\Win32\Release\ADLibR.lib"; DestDir: "{app}\lib\win32\release"
Source: ".\objs\Win32\Release\fdlibm-5.2.lib"; DestDir: "{app}\lib\win32\release"
Source: ".\objs\Win32\Debug\ADLib.lib"; DestDir: "{app}\lib\win32\debug"
Source: ".\objs\Win32\Debug\ADLibErr.lib"; DestDir: "{app}\lib\win32\debug"
Source: ".\objs\Win32\Debug\ADLibR.lib"; DestDir: "{app}\lib\win32\debug"
Source: ".\objs\Win32\Debug\fdlibm-5.2.lib"; DestDir: "{app}\lib\win32\debug"
Source: ".\src\RMath\lib\x32\*.lib"; DestDir: "{app}\lib\win32\R"
Source: ".\objs\x64\Release\ADLib.lib"; DestDir: "{app}\lib\x64\release"
Source: ".\objs\x64\Release\ADLibErr.lib"; DestDir: "{app}\lib\x64\release"
Source: ".\objs\x64\Release\ADLibR.lib"; DestDir: "{app}\lib\x64\release"
Source: ".\objs\x64\Release\fdlibm-5.2.lib"; DestDir: "{app}\lib\x64\release"
Source: ".\objs\x64\Debug\ADLib.lib"; DestDir: "{app}\lib\x64\debug"
Source: ".\objs\x64\Debug\ADLibErr.lib"; DestDir: "{app}\lib\x64\debug"
Source: ".\objs\x64\Debug\ADLibR.lib"; DestDir: "{app}\lib\x64\debug"
Source: ".\objs\x64\Debug\fdlibm-5.2.lib"; DestDir: "{app}\lib\x64\debug"
Source: ".\src\RMath\lib\x64\*.lib"; DestDir: "{app}\lib\x64\R"
Source: ".\objs\ADLibPascal\Windows\win32\lib\*"; DestDir: "{app}\lib\Pascal\win32"
Source: ".\objs\ADLibPascal\Windows\x64\lib\*"; DestDir: "{app}\lib\Pascal\x64"

[Icons]
Name: "{group}\ADT manual"; Filename: "{app}\users-manual.pdf";
Name: "{group}\ADT slide presentation"; Filename: "{app}\Presentation\presentation.html"
Name: "{group}\Uninstall ADT"; Filename: "{uninstallexe}"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\bin"; Check: NeedsAddPath(ExpandConstant('{app}\bin'))

[Code]
function NeedsAddPath(Param: string): boolean;

var
  OrigPath: string;

begin
  RegQueryStringValue(HKEY_LOCAL_MACHINE,
                      'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
                      'Path',
                      OrigPath);

  // look for the path with leading and trailing semicolon
  // Pos() returns 0 if not found
  Result := Pos(';' + Param + ';', ';' + OrigPath + ';') = 0;
end;
