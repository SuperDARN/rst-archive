/* magcmp.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _MAGCMP_H
#define _MAGCMP_H

int IGRFMagCmp(double date, double frho, double flat, double flon, 
                double *bx, double *by, double *bz, double *b);

#endif
