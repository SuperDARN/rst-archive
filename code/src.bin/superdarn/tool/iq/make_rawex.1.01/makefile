# Makefile for make_rawex
# =======================
# Author: R.J.Barnes
# by R.J.Barnes
#
#

INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
OBJS = make_rawex.o
IGNVER=1
SRC=hlpstr.h errstr.h make_rawex.c
OUTPUT = $(BINPATH)/make_rawex
LIBS=-lacfex.1 -lacf.1 -lraw.1 -lradar.1 -liqdata.1 -lopt.1 -ldmap.1 -lrcnv.1 -lrtime.1
SLIB=-lm
include $(MAKEBIN)
 

