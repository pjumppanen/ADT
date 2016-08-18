#!/bin/bash
# create Delphi / Pascal shared library

cd $(dirname $(readlink -f ${BASH_SOURCE[0]}))
if [ -d ./lib ]; then
  rm -f ./lib/*.*
else
  mkdir ./lib
fi
rm -f ./Rosenbrock.so
rm -f ./D_MinRosenbrock_Unit.pas
rm -f ./RosenbrockPas.dch
../../objs/adt RosenbrockPas.mk
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gutil.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gset.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gmap.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gvector.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gstack.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gdeque.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gqueue.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/gpriorityqueue.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/garrayutils.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/ghashmap.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/fcl-stl/ghashset.pp
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/adtcommon.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/adtalloc.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/adtalias.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/adtarray.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/adtR.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib ../../src/ADLibPascal/Raccess.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib MinRosenbrock_Unit.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib D_MinRosenbrock_Unit.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib R_MinRosenbrock_Unit.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib DR_MinRosenbrock_Unit.pas
fpc -Mobjfpc -Scghi -O3 -gl -vewnhi -l -Fi./lib -Fi../common -Fu. -FU./lib RosenbrockPas.lpr
