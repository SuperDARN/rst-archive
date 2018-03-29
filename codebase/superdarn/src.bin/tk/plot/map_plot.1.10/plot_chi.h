/* plot_chi.h
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



void plot_chi(struct Plot *plot,
              float xoff,float yoff,
              struct CnvMapData *ptr,
	      int degfree,int degfree_dat,
              unsigned int color,unsigned char mask,
              char *txtfontname,char *symfontname,float fontsize,
	      void *txtdata);

 
