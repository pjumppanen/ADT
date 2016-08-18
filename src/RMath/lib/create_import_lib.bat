REM create R import library to interface with R.dll
LIB /DEF:R.def /OUT:.\x32\R.lib /MACHINE:X86
LIB /DEF:R.def /OUT:.\x64\R.lib /MACHINE:X64
LIB /DEF:Rblas.def /OUT:.\x32\Rblas.lib /MACHINE:X86
LIB /DEF:Rblas.def /OUT:.\x64\Rblas.lib /MACHINE:X64
LIB /DEF:Rlapack.def /OUT:.\x32\Rlapack.lib /MACHINE:X86
LIB /DEF:Rlapack.def /OUT:.\x64\Rlapack.lib /MACHINE:X64
