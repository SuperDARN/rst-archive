# Makefile for fitclient
# ======================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
OBJS = fitclient.o


SRC=hlpstr.h errstr.h fitclient.c

OUTPUT = $(BINPATH)/fitclient
LIBS=-loldfitcnx.1 -lcnx.1 -lopt.1 -lrcnv.1

ifdef TCPIPLIBS
  SLIB=-lm $(TCPIPLIBS)
  include $(MAKEBIN)
else
version: version.info $(SRC)
	$(BINPATH)/rcsv -t version.info
clean:
	rm -f *.o
	rm -f $(OUTPUT)
endif

 

