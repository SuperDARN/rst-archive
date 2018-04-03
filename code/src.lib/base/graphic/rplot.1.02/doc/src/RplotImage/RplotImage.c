/* RplotImage.c
   ============
   Author: R.J.Barnes
*/


#include <stdio.h>
#include <stdlib.h>
#include "rfbuffer.h"
#include "rplot.h"

int stream(char *buf,int sze,void *data) {
  FILE *fp;
  fp=(FILE *) data;
  fwrite(buf,sze,1,stdout);
  return 0;
} 


int main(int argc,char *argv[]) {

  struct FrameBuffer *img;

  struct Rplot *rplot=NULL;

  float wdt=400,hgt=400;

  unsigned int bgcol=0xffffffff;
  unsigned int fgcol=0xff000000;
  int x,y;

  img=FrameBufferMake("FrameBuffer",10,10,24);
  
  FrameBufferClear(img,bgcol,0x0f);

  FrameBufferEllipse(img,NULL,5,5,5,5,0,fgcol,0x0f,0,NULL,NULL);

  rplot=RplotMake();
  RplotSetText(rplot,stream,stdout);   
  RplotMakePlot(rplot,"Rplot",wdt,hgt,24);

  RplotRectangle(rplot,NULL,0,0,wdt,hgt,
                  1,bgcol,0x0f,0,NULL);

  for (x=0;x<wdt;x+=10) {
    for (y=0;y<hgt;y+=10) {
      RplotImage(rplot,NULL,img,0x0f,x,y,1);
    }
  }

  RplotEndPlot(rplot);
  FrameBufferFree(img);

  return 0;
}

