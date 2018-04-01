/* iqplot.c
   ======== 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#ifdef _XLIB_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#endif

#include "rtypes.h"
#include "rtime.h"
#include "dmap.h"
#include "rxml.h"
#include "option.h"

#include "rfbuffer.h"
#include "rps.h"
#include "fontdb.h"
#include "rplot.h"


#include "rplotin.h"
#include "imagedb.h"
#include "fbrplot.h"
#include "psrplot.h"

#include "xwin.h"

#include "rplotg.h"

#include "limit.h"
#include "rprm.h"
#include "iqdata.h"
#include "iqread.h"


/*
 $Log: iqplot.c,v $
 Revision 1.1  2008/03/18 17:51:42  code
 Initial revision

 */

#define WIDTH (720)
#define HEIGHT (500)

struct OptionData opt;
struct OptionFile *optf=NULL;


struct RadarParm prm;
struct IQData iq;
int16 *samples;
int16 *ptr;



int xmldecode(char *buf,int sze,void *data) {
  struct XMLdata *xmldata;
  xmldata=(struct XMLdata *) data;
  return XMLDecode(xmldata,buf,sze);
} 

char *mktext(double value,double min,double max,void *data) {
  char *txt=NULL;
  txt=malloc(32);
  sprintf(txt,"%g",value);
  return txt;
}

int txtbox(char *fntname,float sze,int num,char *txt,float *box,void *data) {
  struct FrameBufferFontDB *fontdb;
  struct FrameBufferFont *fnt;
  int tbox[3];

  fontdb=(struct FrameBufferFontDB *)data;
  if (fontdb==NULL) return -1;
  fnt=FrameBufferFontDBFind(fontdb,fntname,sze);
  
  FrameBufferTextBox(fnt,num,txt,tbox);
  
  box[0]=tbox[0];
  box[1]=tbox[1];
  box[2]=tbox[2];
 
  return 0;
}


void plot_time(struct Rplot *rplot,
               float xoff,float yoff,float wdt,float hgt,
               double stime,
               unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {
  int i;
  char txt[256];
  float txbox[3];
  char *month[]={"Jan","Feb","Mar","Apr","May","Jun",
               "Jul","Aug","Sep","Oct","Nov","Dec",0};
  char *tmeA="00:00:00.0000 UT";
 
  char *tmeC="0";
  float cwdt;
  float x,y;
  int yr,mo,dy,shr,smt,ssc,fsec;
  double sec;

  txtbox(fontname,fontsize,strlen(tmeC),tmeC,txbox,txtdata);
  cwdt=txbox[0];

  TimeEpochToYMDHMS(stime,&yr,&mo,&dy,&shr,&smt,&sec);
  ssc=sec;

  fsec=10000.0*(sec-ssc);

  sprintf(txt,"%.2d %s %d",dy,month[mo-1],yr);
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
  x=xoff;
  y=yoff+txbox[2];
  for (i=0;txt[i] !=0;i++) {
    txtbox(fontname,fontsize,1,txt+i,txbox,txtdata);
    RplotText(rplot,NULL,fontname,fontsize,x,
              y,1,txt+i,color,mask,1);
    if (isdigit(txt[i])) x+=cwdt;
    else x+=txbox[0];
  }
 
  sprintf(txt,"%.2d:%.2d:%.2d.%.4d UT",shr,smt,ssc,fsec);
  
  txtbox(fontname,fontsize,strlen(tmeA),tmeA,txbox,txtdata);
  
  x=xoff+wdt-txbox[0];
  y=yoff+txbox[2];
  for (i=0;txt[i] !=0;i++) {
    txtbox(fontname,fontsize,1,txt+i,txbox,txtdata);
    RplotText(rplot,NULL,fontname,fontsize,x,
              y,1,txt+i,color,mask,1);
    if (isdigit(txt[i])) x+=cwdt;
    else x+=txbox[0];
  }
}
  


void plot_ephem(struct Rplot *rplot,
               float xoff,float yoff,float wdt,float hgt,
	       int bmnum,int channel,int tfreq,float noise,int nave,int ave,
               unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {
  int i;
  char txt[256];
  float txbox[3];

  char *dig="0";

  float cwdt;
  float x,y;


  txtbox(fontname,fontsize,strlen(dig),dig,txbox,txtdata);
  cwdt=txbox[0];

  sprintf(txt,"bmnum=%.2d channel=%.1d tfreq=%.5d noise=%4.2f smp=%.3d/%.3d",
          bmnum,channel,
          tfreq,noise,ave,nave);
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
  x=xoff;
  y=yoff+txbox[2];
  for (i=0;txt[i] !=0;i++) {
    txtbox(fontname,fontsize,1,txt+i,txbox,txtdata);
    RplotText(rplot,NULL,fontname,fontsize,x,
              y,1,txt+i,color,mask,1);
    if (isdigit(txt[i])) x+=cwdt;
    else x+=txbox[0];
  }
}


int main(int argc,char *argv[]) {


  char *fntdbfname;
  struct FrameBufferFontDB *fontdb=NULL;
  float lne=0.5;

  struct timeval tmout;
  float delay=0;

  int xdf=0;
  struct XwinDisplay *dp;
  struct XwinWindow *win;
  char *display_name=NULL;
  char *wname="iqplot";
  int xdoff=-1;
  int ydoff=-1;

  int xpnum=1,ypnum=1;
  float lpad=40,rpad=40,tpad=40,bpad=40;
  float xoff=0,yoff=0;

  struct Rplot *rplot=NULL;
  struct PlotData *plt;

  unsigned char pflg=0;

  unsigned char rflg=0;
  unsigned char iflg=0;


  int wdt=WIDTH,hgt=HEIGHT;
  int ymin=-200,ymax=200;
  int xnum=300;
  int xmin=0,xmax=0;
  int x;
 
  int pxmin,pxmax;

  int xmajor=0;
  int xminor=0;
  int ymajor=0;
  int yminor=0;

  int arg;

  float ax,ay,bx,by;
  int n;
  FILE *fp=NULL;
  double tval;

  struct FrameBuffer *img=NULL;
  struct FrameBufferRplot *fbplot=NULL;
  struct XMLdata *xmldata=NULL;
  struct RplotInPlot *rplotin=NULL; 
  

  unsigned bgcol=0xff000000;
  unsigned fgcol=0xffffffff;
  unsigned gcol=0xff606060;
  unsigned dgcol=0xff404040;
  unsigned rcol=0xff00ffff;
  unsigned icol=0xffff0000;
 

  fntdbfname=getenv("FONTDB");
  fp=fopen(fntdbfname,"r");
  if (fp !=NULL) {
    fontdb=FrameBufferFontDBLoad(fp);
    fclose(fp);
  }
 
  if (fontdb==NULL) {
    fprintf(stderr,"Could not load fonts.\n");
    exit(-1);
  }

  OptionAdd(&opt,"display",'t',&display_name);
  OptionAdd(&opt,"xoff",'i',&xdoff);
  OptionAdd(&opt,"yoff",'i',&ydoff);
  OptionAdd(&opt,"m",'i',&ymax);
  OptionAdd(&opt,"s",'i',&xmin);
  OptionAdd(&opt,"n",'i',&xnum);
  OptionAdd(&opt,"r",'x',&rflg);
  OptionAdd(&opt,"i",'x',&iflg);
  OptionAdd(&opt,"p",'x',&pflg);

  OptionAdd(&opt,"xmaj",'i',&xmajor);
  OptionAdd(&opt,"xmin",'i',&xminor);
  OptionAdd(&opt,"ymaj",'i',&ymajor);
  OptionAdd(&opt,"ymin",'i',&yminor);

 
  arg=OptionProcess(1,argc,argv,&opt,NULL);  

  if (arg<argc) fp=fopen(argv[arg],"r");
  else fp=stdin;

 
  if ((rflg==0) && (iflg==0) && (pflg==0)) {
    rflg=1;
    iflg=1;
  }

  xmldata=XMLMake();
  rplotin=RplotInMake(xmldata);  
     
  fbplot=FrameBufferRplotMake(fontdb,NULL);
  FrameBufferRplotSetAll(rplotin,fbplot);  
  XMLSetStart(xmldata,RplotInStart,rplotin);
  XMLSetEnd(xmldata,RplotInEnd,rplotin);

  rplot=RplotMake();
  RplotSetText(rplot,xmldecode,xmldata);
  
  dp=XwinOpenDisplay(display_name,&xdf);
 
  if (dp==NULL) {
    fprintf(stderr,"Could not open display.\n");
    exit(-1);
  }

  if (xdoff==-1) xdoff=(dp->wdt-wdt)/2;
  if (ydoff==-1) ydoff=(dp->hgt-hgt)/2;


  win=XwinMakeWindow(xdoff,ydoff,wdt,hgt,0,
                     dp,wname,
                     wname,argv[0],wname,argc,argv,&xdf);
  if (win==NULL) {
    fprintf(stderr,"Could not create window.\n");
    exit(-1);
  }
  XwinShowWindow(win);

  plt=PlotMake(wdt,hgt,xpnum,ypnum,lpad,rpad,bpad,tpad,xoff,yoff);
  PlotSetRplot(plt,rplot);
  PlotSetTextBox(plt,txtbox,fontdb);  

  plt->major_hgt=8;
  plt->minor_hgt=5;
  plt->ttl_hgt=20;
  plt->lbl_hgt=10;

  plt->ttl_wdt=20;
  plt->lbl_wdt=10;

  ymin=-ymax;
  if (pflg) {
    ymin=0;
    ymax=10;
    rflg=0;
    iflg=0;
  }

  xmax=xmin+xnum;

  if (xmajor==0) xmajor=(xmax-xmin)/6;
  if (xminor==0) xminor=(xmax-xmin)/30;

  if (ymajor==0) ymajor=ymax/4;
  if (yminor==0) yminor=ymax/20;

  while(IQFread(fp,&prm,&iq,&samples)==0) {

   
   
    for (n=0;n<iq.seqnum;n++) {
      tval=iq.tval[n].tv_sec+(1.0*iq.tval[n].tv_nsec)/1.0e9;
      
      RplotMakePlot(rplot,"image",wdt,hgt,24);
      RplotRectangle(rplot,NULL,0,0,wdt,hgt,1,bgcol,0x0f,0,NULL);
      pxmin=xmin;
      pxmax=xmax;
      if (pxmax>=iq.smpnum) pxmax=iq.smpnum;
      if (pxmin>=iq.smpnum) pxmin=iq.smpnum;
      ptr=samples+iq.offset[n];

      PlotXaxis(plt,0,xmin,xmax,xmajor,xminor,0x08,dgcol,0x0f,lne);
      PlotYaxis(plt,0,ymin,ymax,ymajor,yminor,0x08,dgcol,0x0f,lne);
      PlotXaxis(plt,0,xmin,xmax,xmajor,xminor,0x04,gcol,0x0f,lne);
      PlotYaxis(plt,0,ymin,ymax,ymajor,yminor,0x04,gcol,0x0f,lne);

      if (pflg) {
        for (x=pxmin+1;x<pxmax;x++) {
          ax=x-1;
        
          ay=ptr[2*(x-1)+1]*ptr[2*(x-1)+1]+ptr[2*(x-1)]*ptr[2*(x-1)];
          if (ay !=0) ay=log10(ay);
          bx=x;
          by=ptr[2*x+1]*ptr[2*x+1]+ptr[2*x]*ptr[2*x];
          if (by !=0) by=log10(by);
          PlotLine(plt,0,ax,ay,bx,by,xmin,xmax,ymin,ymax,fgcol,0x0f,lne,NULL);
        }
      }

      
       
      if (iflg) {
        for (x=pxmin+1;x<pxmax;x++) {
          ax=x-1;
          ay=ptr[2*(x-1)+1];
          bx=x;
          by=ptr[2*x+1];
          PlotLine(plt,0,ax,ay,bx,by,xmin,xmax,ymin,ymax,icol,0x0f,lne,NULL);
        }
      }
      if (rflg) {
        for (x=pxmin+1;x<pxmax;x++) {
          ax=x-1;
          ay=ptr[2*(x-1)];
          bx=x;
          by=ptr[2*x];
          PlotLine(plt,0,ax,ay,bx,by,xmin,xmax,ymin,ymax,rcol,0x0f,lne,NULL);
        }
      }

      PlotPanel(plt,0,fgcol,0x0f,lne);

      PlotXaxis(plt,0,xmin,xmax,xmajor,xminor,0x03,fgcol,0x0f,lne);
      PlotYaxis(plt,0,ymin,ymax,ymajor,yminor,0x03,fgcol,0x0f,lne);
      PlotXaxisLabel(plt,0,xmin,xmax,xmajor,0x03,mktext,NULL,
                     "Helvetica",10.0,fgcol,0x0f);

      PlotYaxisLabel(plt,0,ymin,ymax,ymajor,0x03,mktext,NULL,
                     "Helvetica",10.0,fgcol,0x0f);

      plot_time(rplot,2,2,wdt-4,hgt-4,tval,fgcol,0x0f,"Helvetica",12.0,fontdb);
     
      plot_ephem(rplot,100+2,2,wdt-4,hgt-4,prm.bmnum,prm.channel,prm.tfreq,
                 prm.noise.search,
                 prm.nave,n,fgcol,0x0f,"Helvetica",12.0,fontdb);
     

      RplotEndPlot(rplot);  
      img=fbplot->img;
      if (img==NULL) continue;
   
      XwinFrameBufferWindow(img,win);
      tmout.tv_sec=(int) delay;
      tmout.tv_usec=(delay-(int) delay)*1e6;
      if (delay !=0) XwinDisplayEvent(dp,1,&win,1,&tmout);
      else XwinDisplayEvent(dp,1,&win,1,&tmout);
     
      FrameBufferFree(fbplot->img);
      fbplot->img=NULL;
    }

  } 
  
  XwinFreeWindow(win);
  XwinCloseDisplay(dp);
  return 0;

}