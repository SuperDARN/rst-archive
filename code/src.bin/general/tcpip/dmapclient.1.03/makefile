# Makefile for dmapclient
# =======================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general
OBJS = dmapclient.o
OUTPUT = $(BINPATH)/dmapclient
SRC=hlpstr.h errstr.h dmapclient.c
OUTPUT = $(BINPATH)/dmapclient
LIBS=-lcnx.1 -ldmap.1 -lopt.1 -lrcnv.1


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

 

