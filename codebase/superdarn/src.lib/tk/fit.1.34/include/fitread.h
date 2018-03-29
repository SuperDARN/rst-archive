/* fitread.h
   ========= 
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _FITREAD_H
#define _FITREAD_H

int FitDecode(struct DataMap *ptr,struct FitData *);
int FitFread(FILE *fp,struct RadarParm *,struct FitData *);
int FitRead(int fid,struct RadarParm *,struct FitData *);

#endif

