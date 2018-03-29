# Makefile for rtmultiplex
# ========================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
 
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn -DPOSIX -D__EXTENSIONS__
OBJS = rtmultiplex.o loginfo.o fork.o socket.o msgmem.o connect.o pipe.o
SRC=hlpstr.h errstr.h connect.c connect.h loginfo.c loginfo.h fork.c fork.h pipe.c pipe.h msgmem.c msgmem.h rtmultiplex.c socket.c socket.h
OUTPUT = $(BINPATH)/rtmultiplex
LIBS=-lrtime.1 -lcnx.1 -lopt.1 -lrcnv.1 

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

