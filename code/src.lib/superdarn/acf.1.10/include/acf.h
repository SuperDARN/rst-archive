/* acf.h
   =====
   Author: R.J.Barnes
*/

/* 
 Copyright 2004 The Johns Hopkins University/Applied Physics Laboratory.
 All rights reserved.
 
 This material may be used, modified, or reproduced by or for the U.S.
 Government pursuant to the license rights granted under the clauses at DFARS
 252.227-7013/7014.
 
 For any other permissions, please contact the Space Department
 Program Office at JHU/APL.
 
 This Distribution and Disclaimer Statement must be included in all copies of
 "Radar Software Toolkit - SuperDARN Toolkit" (hereinafter "the Program").
 
 The Program was developed at The Johns Hopkins University/Applied Physics
 Laboratory (JHU/APL) which is the author thereof under the "work made for
 hire" provisions of the copyright law.  
 
 JHU/APL assumes no obligation to provide support of any kind with regard to
 the Program.  This includes no obligation to provide assistance in using the
 Program or to provide updated versions of the Program.
 
 THE PROGRAM AND ITS DOCUMENTATION ARE PROVIDED AS IS AND WITHOUT ANY EXPRESS
 OR IMPLIED WARRANTIES WHATSOEVER.  ALL WARRANTIES INCLUDING, BUT NOT LIMITED
 TO, PERFORMANCE, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE
 HEREBY DISCLAIMED.  YOU ASSUME THE ENTIRE RISK AND LIABILITY OF USING THE
 PROGRAM TO INCLUDE USE IN COMPLIANCE WITH ANY THIRD PARTY RIGHTS.  YOU ARE
 ADVISED TO TEST THE PROGRAM THOROUGHLY BEFORE RELYING ON IT.  IN NO EVENT
 SHALL JHU/APL BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING, WITHOUT
 LIMITATION, ANY LOST PROFITS, LOST SAVINGS OR OTHER INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, ARISING OUT OF THE USE OR INABILITY TO USE THE
 PROGRAM."
 
 
 
 
 
 
*/

/*
 $Log: acf.h,v $
 Revision 1.8  2008/03/13 22:41:09  code
 Removed "delay" term - see comments in the C modules.

 Revision 1.7  2006/08/17 19:01:37  code
 Removed redundant wrappers.

 Revision 1.6  2006/08/17 18:59:15  code
 Added missing prototype.

 Revision 1.5  2006/08/17 18:41:35  code
 Added extended calculation functions.

 Revision 1.4  2006/02/07 19:18:06  barnes
 Further modification to the lag table.

 Revision 1.3  2006/02/07 19:06:25  barnes
 Simon Shepherd's modification of the lag table.

 Revision 1.2  2005/07/26 17:50:21  barnes
 Added code to correctly find XCFs.

 Revision 1.1  2004/07/12 22:30:36  barnes
 Initial revision

*/


#ifndef _ACF_H
#define _ACF_H


#define ACF_PART 0
#define XCF_PART 1









int ACFCalculate(struct TSGprm *prm,
 		 int16 *inbuf,int rngoff,int dflg,
		 int roffset,int ioffset,
		 int mplgs,int lagnum,int (*lagtable)[2],
  	         float *acfbuf,
	         int xcf,int xcfoff,
                 int badrange,float atten,float *dco);

int ACFAverage(float *pwr0,float *acfd,
		 float *xcfd,int *lagsum,
                 int nave,int nrang,int mplgs);

int ACFBadLagZero(struct TSGprm *prm,int mplgs,int (*lagtable)[2]);

void ACFNormalize(float *pwr0,float *acfd,float *xcfd,
                  int nrang,int mplgs,float atten);

int ACFSumPower(struct TSGprm *prm,int mplgs,
                int (*lagtable)[2],float *acfpwr0,
		int16 *inbuf,int rngoff,int dflg,
		int roffset,int ioffset,
		int badrng,float noise,float mxpwr,
		float atten,
	        int thr,int lmt,
                int *abort);

int ACFSumProduct(int16 *buffer,float *avepower,
		  int numsamples,float *mxpwr,float *dco);













#endif
