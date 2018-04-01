# Makefile for buffer_server
# ==========================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
INCLUDE=-I$(IPATH)/base
SRC=hlpstr.h errstr.h buffer_server.c config.h
OBJS=buffer_server.o
OUTPUT = $(BINPATH)/buffer_server
LIBS=-lopt.1
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

 

 

