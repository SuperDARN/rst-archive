/* cfitindex.h
   =========== 
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/

#ifndef _CFITINDEX_H
#define _CFITINDEX_H



struct CFitIndex {
  int num;
  double *tme;
  int *inx;
};

void CFitIndexFree(struct CFitIndex *inx);
struct CFitIndex *CFitIndexLoad(int fid);
struct CFitIndex *CFitIndexFload(FILE *fp);

#endif
