include Makeconf
include $(R_HOME)/etc/$(ARCH)/Makeconf
MY_CFLAGS=$(ALL_CFLAGS) -I $(R_HOME)/include -I ./include
MY_CXXFLAGS=$(ALL_CXXFLAGS) -Wno-ignored-attributes -I $(R_HOME)/include -I ./include
MY_FFLAGS=$(ALL_FFLAGS)
MY_LDFLAGS=$(SHLIB_LDFLAGS) $(LDFLAGS)
MY_LDLIBS=$(FLIBS) $(BLAS_LIBS)
OUT = lib/$(ARCH)/ScilabOptim$(SHLIB_EXT)
OUTLIB = lib/$(ARCH)/ScilabOptim.$(STATICLIB_EXT)

ifdef DLLTOOL
	EXPORT_LIB = $(DLLTOOL) -D $(OUT) -l $(OUTLIB)
else
	EXPORT_LIB =
endif

ODIR = obj
SDIR = src
IDIR = include
objects=obj/ajour.o \
obj/bfgsd.o \
obj/calbx.o \
obj/calmaj.o \
obj/ctcab.o \
obj/ctonb.o \
obj/dcube.o \
obj/ddd2.o \
obj/dgefa.o \
obj/fajc1.o \
obj/fcomp1.o \
obj/fcube.o \
obj/ffinf1.o \
obj/fmani1.o \
obj/fmc11a.o \
obj/fmc11b.o \
obj/fmc11e.o \
obj/fmc11z.o \
obj/fmlag1.o \
obj/fmulb1.o \
obj/fmuls1.o \
obj/fprf2.o \
obj/frdf1.o \
obj/fremf2.o \
obj/fuclid.o \
obj/gcp.o \
obj/icscof.o \
obj/icse.o \
obj/icse0.o \
obj/icse1.o \
obj/icse2.o \
obj/icsec2.o \
obj/icsei.o \
obj/majour.o \
obj/majysa.o \
obj/majz.o \
obj/n1fc1.o \
obj/n1fc1a.o \
obj/n1fc1o.o \
obj/n1gc2.o \
obj/n1gc2a.o \
obj/n1gc2b.o \
obj/n1qn1.o \
obj/n1qn1a.o \
obj/n1qn2.o \
obj/n1qn2a.o \
obj/n1qn3.o \
obj/n1qn3a.o \
obj/nlis0.o \
obj/nlis2.o \
obj/proj.o \
obj/ql0001.o \
obj/qnbd.o \
obj/qpgen1sci.o \
obj/qpgen2.o \
obj/rdmps1.o \
obj/rdmpsz.o \
obj/rednor.o \
obj/relvar.o \
obj/rlbd.o \
obj/satur.o \
obj/shanph.o \
obj/strang.o \
obj/writebuf.o \
obj/zgcbd.o \
obj/zqnbd.o \
obj/dogleg.o \
obj/dpmpar.o \
obj/enorm.o \
obj/fdjac1.o \
obj/fdjac2.o \
obj/gcbd.o \
obj/hybrd.o \
obj/hybrd1.o \
obj/hybrj.o \
obj/hybrj1.o \
obj/lmder.o \
obj/lmdif.o \
obj/lmpar.o \
obj/qform.o \
obj/qrfac.o \
obj/qrsolv.o \
obj/r1mpyq.o \
obj/r1updt.o \
obj/dadd.o \
obj/dset.o \
obj/dmmul.o \
obj/dlamch.o \
obj/dgesl.o \
obj/util.o \
obj/vfinite.o

$(ODIR)/%.o: $(SDIR)/%.f 
	$(FC) -c -o $@ $< $(MY_FFLAGS) 

$(ODIR)/%.o: $(SDIR)/%.c 
	$(CC) -c -o $@ $< $(MY_CFLAGS) 

$(OUT): $(objects) 
	$(CXX) -o $(OUT) $(MY_LDFLAGS) $(objects) $(MY_LDLIBS) $(LIBR)
	$(EXPORT_LIB)

clean : 
	rm $(OUTLIB) $(OUT) $(objects)

