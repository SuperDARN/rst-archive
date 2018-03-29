/* noise_acf.h
   ===========
   Author: R.J.Barnes & K.Baker
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



double noise_acf(double mnpwr,struct FitPrm *ptr,
	         double *pwr, struct FitACFBadSample *badsmp,
		 struct complex *raw,
	         struct complex *n_acf);
