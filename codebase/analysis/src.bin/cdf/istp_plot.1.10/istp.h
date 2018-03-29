/* istp.h
   ======
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




struct imfdata {
  char sat[8];
  char ins[8];
  int cnt;
  double *time;
  float *BGSMc;
  float *BGSEc;
};

struct posdata {
  char sat[8];
  char ins[8];
  int cnt;
  double *time;
  float *PGSM;
  float *PGSE;
};

struct plasmadata {
  char sat[8];
  char ins[8];
  int cnt;
  double *time;
  float *VGSM;
  float *VGSE;
  float *vth;
  float *den;
  float *pre;
};

  
