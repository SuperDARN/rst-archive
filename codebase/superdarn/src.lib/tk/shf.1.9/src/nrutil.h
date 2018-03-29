/* nrutil.h
   ======== 
   Author R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#define SQR(a) (((a)==0) ? 0 : (a)*(a))
#define FMAX(a,b) ((a)>(b) ? (a) : (b))
#define SIGN(a,b) ((b)>=0.0 ? fabs(a) : -fabs(a))

#define IMIN(a,b) ((a)<(b) ? (a) : (b))
