/* gtablewrite.h
   ================
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _GTABLEWRITE_H
#define _GTABLEWRITE_H

int GridTableWrite(int fp,struct GridTable *ptr,char *log,int xtd);
int GridTableFwrite(FILE *fp,struct GridTable *ptr,char *log,int xtd);

#endif
