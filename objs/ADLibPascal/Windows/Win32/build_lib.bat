cd %~dp0
IF EXIST .\lib GOTO LIBDIR
mkdir .\lib
GOTO CONT
:LIBDIR
del /Q .\lib\*.*
:CONT
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gutil.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gset.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gmap.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gvector.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gstack.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gdeque.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gqueue.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\gpriorityqueue.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\garrayutils.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\ghashmap.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\fcl-stl\ghashset.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtcommon.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtalloc.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtalias.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtarray.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\adtR.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi.\lib -Fi..\..\..\..\sample\common -Fu. -FU.\lib ..\..\..\..\src\ADLibPascal\Raccess.pas
