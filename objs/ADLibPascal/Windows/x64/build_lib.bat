cd %~dp0
IF EXIST .\lib GOTO LIBDIR
mkdir .\lib
GOTO CONT
:LIBDIR
del /Q .\lib\*.*
:CONT
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gutil.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gset.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gmap.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gvector.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gstack.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gdeque.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gqueue.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gpriorityqueue.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\garrayutils.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\ghashmap.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\ghashset.pp
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtcommon.pas
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtalloc.pas
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtalias.pas
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtarray.pas
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtR.pas
fpc -Px86_64 -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\Raccess.pas
