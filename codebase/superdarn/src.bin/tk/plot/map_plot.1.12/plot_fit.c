/* plot_fit.c
   ========== 
   Author: R.J.Barnes
*/


/*
 LICENSE AND DISCLAIMER
 
 Copyright (c) 2012 The Johns Hopkins University/Applied Physics Laboratory
 
 This file is part of the Radar Software Toolkit (RST).
 
 RST is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 RST is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with RST.  If not, see <http://www.gnu.org/licenses/>.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "aacgm.h"
#include "rfbuffer.h"
#include "iplot.h"
#include "calcvector.h"
#include "cnvgrid.h"


#define VEL_MAX 25000

void plot_fit(struct Plot *plot,
              struct CnvGrid *ptr,float latmin,int magflg,
              float xoff,float yoff,float wdt,float hgt,float sf,float rad,
              int (*trnf)(int,void *,int,void *,void *data),void *data,
              unsigned int(*cfn)(double,void *),void *cdata,
              float width) {

  int i,s;
  double olon,olat,lon,lat,vazm;
  float map[2],pnt[2];
  unsigned int color=0;
  float ax,ay,bx,by;

  for (i=0;i<ptr->num;i++) {

    if (! isfinite(ptr->mag[i])) continue;
    if (fabs(ptr->mag[i])>VEL_MAX) continue;

    
    olon=ptr->lon[i];
    olat=ptr->lat[i];
    vazm=ptr->azm[i];

    lat=olat;
    lon=olon;
    if (!magflg) {
      double mlat,mlon,glat,glon,r;
      int s;
      mlat=lat;
      mlon=lon;
      s=AACGMConvert(mlat,mlon,150,&glat,&glon,&r,1);
      lat=glat;
      lon=glon;
    }

    if (fabs(lat)<fabs(latmin)) continue;
    if (cfn !=NULL) color=(*cfn)(ptr->mag[i],cdata);
    
    map[0]=lat;
    map[1]=lon;
   
    s=(*trnf)(2*sizeof(float),map,2*sizeof(float),pnt,data);
  
    if (s==-1) continue;
    ax=xoff+pnt[0]*wdt;
    ay=yoff+pnt[1]*hgt;    
    
    RPosCalcVector(olat,olon,ptr->mag[i]*sf,vazm,&lat,&lon);

    if (!magflg) {
      double mlat,mlon,glat,glon,r;
      int s;
      mlat=lat;
      mlon=lon;
      s=AACGMConvert(mlat,mlon,150,&glat,&glon,&r,1);
      lat=glat;
      lon=glon;
    }

    map[0]=lat;
    map[1]=lon;
    s=(*trnf)(2*sizeof(float),map,2*sizeof(float),pnt,data);
    if (s==-1) continue;
    bx=xoff+pnt[0]*wdt;
    by=yoff+pnt[1]*hgt;    
    
    if (rad>0) PlotEllipse(plot,NULL,ax,ay,
                 rad,rad,1,color,0x0f,0,NULL);
    
    PlotLine(plot,ax,ay,bx,by,color,0x0f,width,NULL);    
    
  } 
}
