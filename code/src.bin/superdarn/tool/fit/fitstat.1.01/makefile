# Makefile for test_fit
# =====================
# Author: R.J.Barnes
#
#

INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
OBJS = fitstat.o
SRC=fitstat.c hlpstr.h errstr.h
OUTPUT = $(BINPATH)/fitstat
LIBS=-loldfit.1 -lfit.1 -lrscan.1 -ldmap.1 -lopt.1 -lrtime.1 -lrcnv.1
SLIB=-lm
include $(MAKEBIN)
 

