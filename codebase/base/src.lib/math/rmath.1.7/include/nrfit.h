/* nrfit.h
   =====
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _NRFIT_H
#define _NRFIT_H

void nrfit(float *x,float *y,int ndata,float *sig,int mwt,
         float *a,float *b,float *siga,float *sigb,float *chi2,
	 float *q);

#endif













