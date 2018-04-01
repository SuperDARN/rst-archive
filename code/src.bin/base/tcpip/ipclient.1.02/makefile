# Makefile for ipclient
# =====================
# Author: R.J.Barnes
#
INCLUDE=-I$(IPATH)/base
OBJS = ipclient.o
SRC=ipclient.c
OUTPUT = $(BINPATH)/ipclient
SRC=hlpstr.h errstr.h ipclient.c
OUTPUT = $(BINPATH)/ipclient
LIBS=-lcnx.1 -lopt.1


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


 

