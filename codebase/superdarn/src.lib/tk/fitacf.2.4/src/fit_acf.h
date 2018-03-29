/* fit_acf.h
   =========
   Author: R.J.Barnes & K.Baker
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




int fit_acf (struct complex *acf,int range,int *badlag,
	     struct FitACFBadSample *badsmp,int lag_lim,
	     struct FitPrm *prm,
	     double noise_lev_in,char xflag,double xomega,
             struct FitRange *ptr);
