/* imp.h
   =====
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




int imppla_pos(CDFid id,struct posdata *ptr,double stime,double etime);
int imppla_plasma(CDFid id,struct plasmadata *ptr,double stime,double etime);
int impmag_pos(CDFid id,struct posdata *ptr,double stime,double etime);
int impmag_imf(CDFid id,struct imfdata *ptr,double stime,double etime);
  
