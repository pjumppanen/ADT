xcopy %~dp0\..\adt %1\adt-build-environment /s /exclude:%~dp0\exclude.txt
copy %~dp0\objs\adt-build-environment.sln %1\adt-build-environment\objs\
mkdir %1\adt-build-environment\objs\release\
mkdir %1\adt-build-environment\objs\debug\
copy %~dp0\objs\release\adt.exe %1\adt-build-environment\objs\release\
copy %~dp0\objs\release\adt.exe %1\adt-build-environment\objs\debug\
del /Q %1\adt-build-environment\src\*.*
