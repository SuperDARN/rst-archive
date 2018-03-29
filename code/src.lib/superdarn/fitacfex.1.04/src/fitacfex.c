
/* fitacfex.c
   ========== 
   Algorithm: R.A.Greenwald, K.Oskavik
   Implementation: R.J.Barnes
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "rtypes.h"
#include "rmath.h"
#include "nrfit.h"
#include "limit.h"
#include "rprm.h"
#include "rawdata.h"
#include "fitdata.h"
#include "fitblk.h"

/*
 $Log: fitacfex.c,v $
 Revision 1.4  2007/03/09 13:53:11  code
 Fixed velocity error name.

 Revision 1.3  2007/03/09 13:52:26  code
 Added error estimate for velocity.

 Revision 1.2  2007/02/21 22:26:25  code
 Modification to allow fitting even with a negative slope
 This allows ground scatter to be better captured.

 Revision 1.1  2007/02/20 16:21:44  code
 Initial revision

*/

void FitACFex(struct RadarParm *prm,struct RawData *raw,
              struct FitData *fit) {

  float minpwr=3.0;
  int minlag=5;
  float sderr=2.5;
  int nslopes=120;

  float a,b,siga,sigb,chi2,q;

  float *model_phi;

  float model_slope;
  float model_vel_pos;

  float *model_vels; 
  float *model_errors;
  float *lagpwr=NULL,*logpwr=NULL;

  float lag0pwr;
  float re,im;
  float assumed_width=0.0;
  
  int goodcnt=0;
  int *lag_avail=NULL,availcnt=0;
  float *good_lags=NULL;

  float delta_pos,delta_neg;

  float *data_phi_pos,*data_phi_neg;
  float data_phi;
  float pwr;
  float error_neg=0,error_pos=0;
  float model_mean,model_sd,model_min;
  int mininx=0;
    
  int i,j,R,L;

  float phi;
  int p;

  model_phi=malloc(sizeof(float)*(nslopes+1)*(prm->mplgs+1));
  model_vels=malloc(sizeof(float)*(2*nslopes+1));
  model_errors=malloc(sizeof(float)*(2*nslopes+1));
  lagpwr=malloc(sizeof(float)*prm->mplgs);
  logpwr=malloc(sizeof(float)*prm->mplgs);
  
  data_phi_pos=malloc(sizeof(float)*prm->mplgs);
  data_phi_neg=malloc(sizeof(float)*prm->mplgs);

  lag_avail=malloc(sizeof(int)*prm->mplgs);
  good_lags=malloc(sizeof(float)*prm->mplgs);
  


  for (i=0;i<=nslopes;i++) {
    model_slope=180.0*i/nslopes;
    for (j=0;j<=prm->mplgs;j++) {
      phi=j*model_slope;
      p=phi/360;
      model_phi[i*(prm->mplgs+1)+j]=phi-p*360;
      
    }
    model_vel_pos=2.9979E8/2.0*(1-1000.0*prm->tfreq/
	   (1000.0*prm->tfreq+model_slope/360.0/(prm->mpinc*1.0e-6)));

    model_vels[nslopes-i]=-model_vel_pos;
    model_vels[nslopes+i]=model_vel_pos;

  }
   
    


  for (R=0;R<prm->nrang;R++) {

    fit->rng[R].v=HUGE_VAL;
    fit->rng[R].v_err=HUGE_VAL;
    fit->rng[R].p_0=-1.0;

    fit->rng[R].w_l=-1.0;
    fit->rng[R].w_l_err=-1.0;
    fit->rng[R].p_l=-1.0;
    fit->rng[R].p_l_err=-1.0;

    fit->rng[R].w_s=-1.0;
    fit->rng[R].w_s_err=-1.0;
    fit->rng[R].p_s=-1.0;
    fit->rng[R].p_s_err=-1.0;

    fit->rng[R].sdev_l=0;
    fit->rng[R].sdev_s=-0;

    fit->rng[R].sdev_phi=-0;

    fit->rng[R].qflg=0;
    fit->rng[R].gsct=0;
    fit->rng[R].nump=0;

    availcnt=0;
    lag0pwr=10.0*log10(raw->acfd[R][0][0]/prm->noise.search);

    for (j=0;j<=2*nslopes;j++) model_errors[j]=1.0e30;

    for (L=0;L<prm->mplgs;L++) {
      re=raw->acfd[R][L][0];
      im=raw->acfd[R][L][1];
      lagpwr[L]=sqrt(re*re+im*im);

      if (lagpwr[L]>0) {
        lag_avail[availcnt]=L;
        availcnt++;
      }
    }
    if ((lag0pwr>minpwr) && (availcnt>minlag)) {
      for (i=0;i<availcnt;i++) {
        L=lag_avail[i];
        lagpwr[L]-=prm->noise.search;
        if (lagpwr[L]< (lagpwr[0]/sqrt(prm->nave))) 
          lagpwr[L]=-1;
      }
    }
    goodcnt=0;
    for (i=0;i<availcnt;i++) {
      L=lag_avail[i];
      if (lagpwr[L]>0) {
        
        logpwr[goodcnt]=log(lagpwr[L]);
        good_lags[goodcnt]=L;
        goodcnt++;
      }
    }
   

    if (goodcnt<4) continue; /* no fit possible */
    

    nrfit(good_lags,logpwr,goodcnt,NULL,0,&a,&b,&siga,&sigb,&chi2,&q);

    assumed_width=-2.9979e8*b/(prm->mpinc*1.e-6)/
                  (2*PI*1000.0*prm->tfreq);



    if (assumed_width<0) assumed_width=0;
    
    fit->rng[R].w_l=assumed_width;

   
    
    /*    if (assumed_width==0) continue; */
    
    pwr=0.0;
    for (i=0;i<goodcnt;i++) {
      L=good_lags[i];
      data_phi=atan2(raw->acfd[R][L][1],
			raw->acfd[R][L][0])*180.0/PI;
      
      data_phi_pos[i]=data_phi;
      data_phi_neg[i]=360-data_phi;

      if (data_phi<0) {
        data_phi_pos[i]+=360;
	data_phi_neg[i]=-data_phi;
      }
      pwr+=lagpwr[L];
    }
    
    for(i=0;i<=nslopes;i++) {
      
      error_neg=0;
      error_pos=0;
      for (j=0;j<goodcnt;j++) {
        L=good_lags[j];
	delta_pos=fabs(data_phi_pos[j]-model_phi[i*(prm->mplgs+1)+L]); 
	delta_neg=fabs(data_phi_neg[j]-model_phi[i*(prm->mplgs+1)+L]);

        if (delta_pos>180.0) delta_pos=360-delta_pos;
        if (delta_neg>180.0) delta_neg=360-delta_neg;
	
         
	
        error_neg+=delta_neg*delta_neg*lagpwr[L]/pwr;
        error_pos+=delta_pos*delta_pos*lagpwr[L]/pwr;
      
      }

      error_neg=sqrt(error_neg);
      error_pos=sqrt(error_pos);
      model_errors[nslopes-i]=error_neg;      
      model_errors[nslopes+i]=error_pos;

      
    }

    model_mean=0.0;
    model_sd=0.0;
    model_min=1.0e30;
    mininx=0;

    for (i=0;i<=nslopes*2;i++) {

      model_mean+=model_errors[i];
      if (model_errors[i]<model_min) {
         model_min=model_errors[i];
         mininx=i;
      }
    }

    model_mean=model_mean/(nslopes*2);

    for (i=0;i<=nslopes*2;i++) 
      model_sd+=(model_errors[i]-model_mean)*(model_errors[i]-model_mean);

    model_sd=sqrt(model_sd/(nslopes*2));

    if (model_min<(model_mean-sderr*model_sd)) {

      fit->rng[R].v=model_vels[mininx];
      fit->rng[R].v_err=model_vels[1]-model_vels[0];
      fit->rng[R].qflg=1;
      fit->rng[R].p_0=raw->pwr0[R];
      fit->rng[R].p_l=lag0pwr;
      fit->rng[R].nump=goodcnt;    
      /*      if (fit->rng[R].w_l<0) fit->rng[R].qflg=0; */
      if ((fit->rng[R].v<30) && (fit->rng[R].w_l<30)) fit->rng[R].gsct=1;

    }
  }


  free(model_phi);
  free(model_vels);
  free(model_errors);
  free(lagpwr);
  free(logpwr);
  free(data_phi_pos);
  free(data_phi_neg);


  free(lag_avail);
  free(good_lags);




}
