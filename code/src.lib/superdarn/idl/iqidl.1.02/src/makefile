# Makefile for iqidl library
# ==========================
# by R.J.Barnes
#
#
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn -I${IDL_IPATH}
IGNVER=1
SRC=iqidl.c
OBJS = iqidl.o
DSTPATH=$(LIBPATH)
OUTPUT = iqidl
SLIB= -liqdata.1 -ldmap.1 -lrtime.1 -lrcnv.1
LINK="1"
ifdef IDL_IPATH
include $(MAKELIBIDL)
else
version: version.info $(SRC)
	$(BINPATH)/rcsv -t version.info
clean:
	rm -f *.o
	rm -f $(OUTPUT)
endif



