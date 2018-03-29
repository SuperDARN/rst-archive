/* fit_noise.h
   ===========
   Author: R.J.Barnes & K.Baker
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



void fit_noise(struct complex *nacf,int *badlag,
               struct FitACFBadSample *badsmp,
	       double skynoise,struct FitPrm *prm,
	       struct FitRange *ptr);
