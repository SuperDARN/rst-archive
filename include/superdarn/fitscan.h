/* fitscan.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#ifndef _FITSCAN_H
#define _FITSCAN_H

int FitReadRadarScan(int fid,int *state,
                 struct RadarScan *ptr,struct RadarParm *prm,
		 struct FitData *fit,int tlen,
                 int lock,int chn);

int FitFreadRadarScan(FILE *fp,int *state,
                 struct RadarScan *ptr,struct RadarParm *prm,
		 struct FitData *fit,int tlen,
                 int lock,int chn);



int FitToRadarScan(struct RadarScan *ptr,struct RadarParm *prm,
		   struct FitData *fit);


#endif


