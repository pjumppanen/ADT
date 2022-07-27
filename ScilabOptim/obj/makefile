R_SHARE_DIR=C:/Users/jum002/Documents/R/R-4.0.5/share
R_HOME=C:/Users/jum002/Documents/R/R-4.0.5
include $(R_HOME)/etc/x64/Makeconf
CC=C:/rtools40/mingw64/bin/gcc
CXX=C:/rtools40/mingw64/bin/g++
FC=C:/rtools40/mingw64/bin/gfortran
COMMONFLAGS=-O0\
-g\
-DDEBUG\
-D_DEBUG\
-I../include/\
-IC:/Users/jum002/Documents/R/R-4.0.5/include
CFLAGS=$(COMMONFLAGS)
CXXFLAGS=$(COMMONFLAGS)\
-Wno-ignored-attributes
FFLAGS=$(COMMONFLAGS)
LDFLAGS=-shared
LDLIBS=-L'C:/Users/jum002/Documents/R/R-4.0.5/bin/x64' -lRblas -lgfortran -lquadmath
objects=ajour.o \
bfgsd.o \
calbx.o \
calmaj.o \
ctcab.o \
ctonb.o \
dcube.o \
ddd2.o \
dgefa.o \
fajc1.o \
fcomp1.o \
fcube.o \
ffinf1.o \
fmani1.o \
fmc11a.o \
fmc11b.o \
fmc11e.o \
fmc11z.o \
fmlag1.o \
fmulb1.o \
fmuls1.o \
fprf2.o \
frdf1.o \
fremf2.o \
fuclid.o \
gcp.o \
icscof.o \
icse.o \
icse0.o \
icse1.o \
icse2.o \
icsec2.o \
icsei.o \
majour.o \
majysa.o \
majz.o \
n1fc1.o \
n1fc1a.o \
n1fc1o.o \
n1gc2.o \
n1gc2a.o \
n1gc2b.o \
n1qn1.o \
n1qn1a.o \
n1qn2.o \
n1qn2a.o \
n1qn3.o \
n1qn3a.o \
nlis0.o \
nlis2.o \
proj.o \
ql0001.o \
qnbd.o \
qpgen1sci.o \
qpgen2.o \
rdmps1.o \
rdmpsz.o \
rednor.o \
relvar.o \
rlbd.o \
satur.o \
shanph.o \
strang.o \
writebuf.o \
zgcbd.o \
zqnbd.o \
dogleg.o \
dpmpar.o \
enorm.o \
fdjac1.o \
fdjac2.o \
gcbd.o \
hybrd.o \
hybrd1.o \
hybrj.o \
hybrj1.o \
lmder.o \
lmdif.o \
lmpar.o \
qform.o \
qrfac.o \
qrsolv.o \
r1mpyq.o \
r1updt.o \
dadd.o \
dset.o \
dmmul.o \
dlamch.o \
dgesl.o \
util.o \
vfinite.o

ScilabOptim.dll : $(objects)
	$(CXX) -o ScilabOptim.dll $(LDFLAGS) $(objects) $(LDLIBS) $(LIBR)

vfinite.o : ../src/vfinite.c 
	$(CC) $(CFLAGS) -c ../src/vfinite.c

dgesl.o : ../src/dgesl.f 
	$(FC) $(FFLAGS) -c ../src/dgesl.f

util.o : ../src/util.f 
	$(FC) $(FFLAGS) -c ../src/util.f

dlamch.o : ../src/dlamch.f 
	$(FC) $(FFLAGS) -c ../src/dlamch.f

ajour.o : ../src/ajour.f 
	$(FC) $(FFLAGS) -c ../src/ajour.f

bfgsd.o : ../src/bfgsd.f 
	$(FC) $(FFLAGS) -c ../src/bfgsd.f

calbx.o : ../src/calbx.f 
	$(FC) $(FFLAGS) -c ../src/calbx.f

calmaj.o : ../src/calmaj.f 
	$(FC) $(FFLAGS) -c ../src/calmaj.f

ctcab.o : ../src/ctcab.f 
	$(FC) $(FFLAGS) -c ../src/ctcab.f

ctonb.o : ../src/ctonb.f 
	$(FC) $(FFLAGS) -c ../src/ctonb.f

dcube.o : ../src/dcube.f 
	$(FC) $(FFLAGS) -c ../src/dcube.f

ddd2.o : ../src/ddd2.f 
	$(FC) $(FFLAGS) -c ../src/ddd2.f

dgefa.o : ../src/dgefa.f 
	$(FC) $(FFLAGS) -c ../src/dgefa.f

dadd.o : ../src/dadd.f 
	$(FC) $(FFLAGS) -c ../src/dadd.f

dset.o : ../src/dset.f 
	$(FC) $(FFLAGS) -c ../src/dset.f

dmmul.o : ../src/dmmul.f 
	$(FC) $(FFLAGS) -c ../src/dmmul.f

fajc1.o : ../src/fajc1.f 
	$(FC) $(FFLAGS) -c ../src/fajc1.f

fcomp1.o : ../src/fcomp1.f 
	$(FC) $(FFLAGS) -c ../src/fcomp1.f

fcube.o : ../src/fcube.f 
	$(FC) $(FFLAGS) -c ../src/fcube.f

ffinf1.o : ../src/ffinf1.f 
	$(FC) $(FFLAGS) -c ../src/ffinf1.f

fmani1.o : ../src/fmani1.f 
	$(FC) $(FFLAGS) -c ../src/fmani1.f

fmc11a.o : ../src/fmc11a.f 
	$(FC) $(FFLAGS) -c ../src/fmc11a.f

fmc11b.o : ../src/fmc11b.f 
	$(FC) $(FFLAGS) -c ../src/fmc11b.f

fmc11e.o : ../src/fmc11e.f 
	$(FC) $(FFLAGS) -c ../src/fmc11e.f

fmc11z.o : ../src/fmc11z.f 
	$(FC) $(FFLAGS) -c ../src/fmc11z.f

fmlag1.o : ../src/fmlag1.f 
	$(FC) $(FFLAGS) -c ../src/fmlag1.f

fmulb1.o : ../src/fmulb1.f 
	$(FC) $(FFLAGS) -c ../src/fmulb1.f

fmuls1.o : ../src/fmuls1.f 
	$(FC) $(FFLAGS) -c ../src/fmuls1.f

fprf2.o : ../src/fprf2.f 
	$(FC) $(FFLAGS) -c ../src/fprf2.f

frdf1.o : ../src/frdf1.f 
	$(FC) $(FFLAGS) -c ../src/frdf1.f

fremf2.o : ../src/fremf2.f 
	$(FC) $(FFLAGS) -c ../src/fremf2.f

fuclid.o : ../src/fuclid.f 
	$(FC) $(FFLAGS) -c ../src/fuclid.f

gcbd.o : ../src/gcbd.f 
	$(FC) $(FFLAGS) -c ../src/gcbd.f

gcp.o : ../src/gcp.f 
	$(FC) $(FFLAGS) -c ../src/gcp.f

icscof.o : ../src/icscof.f 
	$(FC) $(FFLAGS) -c ../src/icscof.f

icse.o : ../src/icse.f 
	$(FC) $(FFLAGS) -c ../src/icse.f

icse0.o : ../src/icse0.f 
	$(FC) $(FFLAGS) -c ../src/icse0.f

icse1.o : ../src/icse1.f 
	$(FC) $(FFLAGS) -c ../src/icse1.f

icse2.o : ../src/icse2.f 
	$(FC) $(FFLAGS) -c ../src/icse2.f

icsec2.o : ../src/icsec2.f 
	$(FC) $(FFLAGS) -c ../src/icsec2.f

icsei.o : ../src/icsei.f 
	$(FC) $(FFLAGS) -c ../src/icsei.f

majour.o : ../src/majour.f 
	$(FC) $(FFLAGS) -c ../src/majour.f

majysa.o : ../src/majysa.f 
	$(FC) $(FFLAGS) -c ../src/majysa.f

majz.o : ../src/majz.f 
	$(FC) $(FFLAGS) -c ../src/majz.f

n1fc1.o : ../src/n1fc1.f 
	$(FC) $(FFLAGS) -c ../src/n1fc1.f

n1fc1a.o : ../src/n1fc1a.f 
	$(FC) $(FFLAGS) -c ../src/n1fc1a.f

n1fc1o.o : ../src/n1fc1o.f 
	$(FC) $(FFLAGS) -c ../src/n1fc1o.f

n1gc2.o : ../src/n1gc2.f 
	$(FC) $(FFLAGS) -c ../src/n1gc2.f

n1gc2a.o : ../src/n1gc2a.f 
	$(FC) $(FFLAGS) -c ../src/n1gc2a.f

n1gc2b.o : ../src/n1gc2b.f 
	$(FC) $(FFLAGS) -c ../src/n1gc2b.f

n1qn1.o : ../src/n1qn1.f 
	$(FC) $(FFLAGS) -c ../src/n1qn1.f

n1qn1a.o : ../src/n1qn1a.f 
	$(FC) $(FFLAGS) -c ../src/n1qn1a.f

n1qn2.o : ../src/n1qn2.f 
	$(FC) $(FFLAGS) -c ../src/n1qn2.f

n1qn2a.o : ../src/n1qn2a.f 
	$(FC) $(FFLAGS) -c ../src/n1qn2a.f

n1qn3.o : ../src/n1qn3.f 
	$(FC) $(FFLAGS) -c ../src/n1qn3.f

n1qn3a.o : ../src/n1qn3a.f 
	$(FC) $(FFLAGS) -c ../src/n1qn3a.f

nlis0.o : ../src/nlis0.f 
	$(FC) $(FFLAGS) -c ../src/nlis0.f

nlis2.o : ../src/nlis2.f 
	$(FC) $(FFLAGS) -c ../src/nlis2.f

proj.o : ../src/proj.f 
	$(FC) $(FFLAGS) -c ../src/proj.f

ql0001.o : ../src/ql0001.f 
	$(FC) $(FFLAGS) -c ../src/ql0001.f

qnbd.o : ../src/qnbd.f 
	$(FC) $(FFLAGS) -c ../src/qnbd.f

qpgen1sci.o : ../src/qpgen1sci.f 
	$(FC) $(FFLAGS) -c ../src/qpgen1sci.f

qpgen2.o : ../src/qpgen2.f 
	$(FC) $(FFLAGS) -c ../src/qpgen2.f

rdmps1.o : ../src/rdmps1.f 
	$(FC) $(FFLAGS) -c ../src/rdmps1.f

rdmpsz.o : ../src/rdmpsz.f 
	$(FC) $(FFLAGS) -c ../src/rdmpsz.f

rednor.o : ../src/rednor.f 
	$(FC) $(FFLAGS) -c ../src/rednor.f

relvar.o : ../src/relvar.f 
	$(FC) $(FFLAGS) -c ../src/relvar.f

rlbd.o : ../src/rlbd.f 
	$(FC) $(FFLAGS) -c ../src/rlbd.f

satur.o : ../src/satur.f 
	$(FC) $(FFLAGS) -c ../src/satur.f

shanph.o : ../src/shanph.f 
	$(FC) $(FFLAGS) -c ../src/shanph.f

strang.o : ../src/strang.f 
	$(FC) $(FFLAGS) -c ../src/strang.f

writebuf.o : ../src/writebuf.f 
	$(FC) $(FFLAGS) -c ../src/writebuf.f

zgcbd.o : ../src/zgcbd.f 
	$(FC) $(FFLAGS) -c ../src/zgcbd.f

zqnbd.o : ../src/zqnbd.f 
	$(FC) $(FFLAGS) -c ../src/zqnbd.f

dogleg.o : ../src/dogleg.f 
	$(FC) $(FFLAGS) -c ../src/dogleg.f

dpmpar.o : ../src/dpmpar.f 
	$(FC) $(FFLAGS) -c ../src/dpmpar.f

enorm.o : ../src/enorm.f 
	$(FC) $(FFLAGS) -c ../src/enorm.f

fdjac1.o : ../src/fdjac1.f 
	$(FC) $(FFLAGS) -c ../src/fdjac1.f

fdjac2.o : ../src/fdjac2.f 
	$(FC) $(FFLAGS) -c ../src/fdjac2.f

hybrd.o : ../src/hybrd.f 
	$(FC) $(FFLAGS) -c ../src/hybrd.f

hybrd1.o : ../src/hybrd1.f 
	$(FC) $(FFLAGS) -c ../src/hybrd1.f

hybrj.o : ../src/hybrj.f 
	$(FC) $(FFLAGS) -c ../src/hybrj.f

hybrj1.o : ../src/hybrj1.f 
	$(FC) $(FFLAGS) -c ../src/hybrj1.f

lmder.o : ../src/lmder.f 
	$(FC) $(FFLAGS) -c ../src/lmder.f

lmdif.o : ../src/lmdif.f 
	$(FC) $(FFLAGS) -c ../src/lmdif.f

lmpar.o : ../src/lmpar.f 
	$(FC) $(FFLAGS) -c ../src/lmpar.f

qform.o : ../src/qform.f 
	$(FC) $(FFLAGS) -c ../src/qform.f

qrfac.o : ../src/qrfac.f 
	$(FC) $(FFLAGS) -c ../src/qrfac.f

qrsolv.o : ../src/qrsolv.f 
	$(FC) $(FFLAGS) -c ../src/qrsolv.f

r1mpyq.o : ../src/r1mpyq.f 
	$(FC) $(FFLAGS) -c ../src/r1mpyq.f

r1updt.o : ../src/r1updt.f 
	$(FC) $(FFLAGS) -c ../src/r1updt.f

clean : 
	rm ScilabOptim.dll $(objects)

