/* gridread.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _GRIDREAD_H
#define _GRIDREAD_H

int GridRead(int fid,struct GridData *gp);
int GridFread(FILE *fp,struct GridData *gp);

#endif



