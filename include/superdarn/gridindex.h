/* gridindex.h
   =========== 
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#ifndef _GRIDINDEX_H
#define _GRIDINDEX_H


struct GridIndex {
  int num;
  double *tme;
  int *inx;
};

void GridIndexFree(struct GridIndex *inx);
struct GridIndex *GridIndexLoad(int fid);
struct GridIndex *GridIndexFload(FILE *fp);
 


#endif
