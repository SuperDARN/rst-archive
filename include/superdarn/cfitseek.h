/* cfitseek.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _CFITSEEK_H
#define _CFITSEEK_H

int CFitSeek(struct CFitfp *fptr,int yr,int mo,int dy,int hr,int mt,int sc,
	     double *atme,struct CFitIndex *inx);

#endif






