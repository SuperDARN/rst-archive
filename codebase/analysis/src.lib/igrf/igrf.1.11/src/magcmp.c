/* magcmp.c
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#include <math.h>
#include <stdio.h>
#include "igrfcall.h"



int IGRFMagCmp(double date, double frho, double flat, double flon, 
           double *bx, double *by, double *bz, double *b) {
  int s;
  frho = frho - 6372.;
  s=IGRFCall(date, flat, flon, frho, bx, by, bz);
  *b = sqrt(*bx * *bx + *by * *by + *bz * *bz);
  *bx = -*bx;
  *bz = -*bz;
  return s;
} 

