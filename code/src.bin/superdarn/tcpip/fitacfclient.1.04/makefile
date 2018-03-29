# Makefile for fitacfclient
# =========================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
OBJS = fitacfclient.o
SRC=hlpstr.h errstr.h fitacfclient.c
OUTPUT = $(BINPATH)/fitacfclient
LIBS=-lfitcnx.1 -lfit.1 -lrscan.1 -lcnx.1 -ldmap.1 -lopt.1 -lrtime.1 -lrcnv.1

ifdef TCPIPLIBS
  SLIB=$(TCPIPLIBS)
  include $(MAKEBIN)
else
version: version.info $(SRC)
	$(BINPATH)/rcsv -t version.info
clean:
	rm -f *.o
	rm -f $(OUTPUT)
endif

