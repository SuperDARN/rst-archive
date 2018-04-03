/* imagename.c
   =========== 
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
#include "rxml.h"
#include "rfbuffer.h"
#include "rplot.h"
#include "fontdb.h"
#include "rplotg.h"
#include "grplot.h"
#include "block.h"

/*
 $Log: imagename.c,v $
 Revision 1.2  2004/04/26 20:59:24  barnes
 Audit - Enforced warning set to "all".

 Revision 1.1  2003/03/22 03:16:45  barnes
 Initial revision

*/

int GrPlotImageNameStart(char *name,int atnum,char **atname,char **atval,
		    char *buf,int sze,void *data) {
  int i;
  struct GrPlotBlock *blk;
  struct GrPlotImageName *ptr;
  struct GrPlotData *plt;
  struct GrPlotConvert *cnv;

  blk=(struct GrPlotBlock *) data;
  if (blk==NULL) return -1;
  ptr=(struct GrPlotImageName *) blk->data;
  if (ptr==NULL) return -1;
  plt=ptr->plt;
  if (plt==NULL) return -1;
  cnv=&plt->cnv;

  if (strcmp(name,blk->name)==0) {
    int s=0;
    unsigned int mask;
    char *xvalue=NULL;
    char *yvalue=NULL;
    char *xtype=NULL;
    char *ytype=NULL;

    char tmp[64];
    ptr->mask=0;
    ptr->name=NULL;
    ptr->matrix=NULL;
    ptr->dx=0;
    ptr->dy=0;
    ptr->x=0;
    ptr->y=0;
    for (i=0;i<atnum;i++) {
      if (strcmp(atname[i],"mask")==0) {
        strcpy(tmp,"0x");
        strcat(tmp,atval[i]);
        sscanf(tmp,"%x",&mask);
        ptr->mask=mask;
      } else if (strcmp(atname[i],"matrix")==0)
        ptr->matrix=RplotMatrixString(atval[i]);
      else if (strcmp(atname[i],"xvalue")==0) xvalue=atval[i];
      else if (strcmp(atname[i],"yvalue")==0) yvalue=atval[i];
      else if (strcmp(atname[i],"xpos")==0) xvalue=atval[i];
      else if (strcmp(atname[i],"ypos")==0) yvalue=atval[i];
      else if (strcmp(atname[i],"xtype")==0) xtype=atval[i];
      else if (strcmp(atname[i],"ytype")==0) ytype=atval[i];
      else if (strcmp(atname[i],"xoffset")==0) ptr->dx=atof(atval[i]);
      else if (strcmp(atname[i],"yoffset")==0) ptr->dy=atof(atval[i]);
    }
    if (xvalue !=NULL) {
      if (xtype==NULL) ptr->x=atof(xvalue);
      else if (cnv->user !=NULL)
        s=(cnv->user)(xtype,xvalue,&ptr->x,cnv->data);
      else ptr->x=0;
    }
    if (yvalue !=NULL) {
      if (ytype==NULL) ptr->y=atof(yvalue);
      else if (cnv->user !=NULL)
        s=(cnv->user)(xtype,yvalue,&ptr->y,cnv->data);
      else ptr->y=0;
    }
    return s;
  }

 
  if (strcmp(name,"extent")==0) {
    struct GrPlotExtent *ext;
    ext=malloc(sizeof(struct GrPlotExtent));
    ext->cnv=&plt->cnv;
    ext->inc=&plt->inc;
    ext->xmin=&ptr->xmin;
    ext->xmax=&ptr->xmax;
    ext->ymin=&ptr->ymin;
    ext->ymax=&ptr->ymax;
    ptr->state=ptr->state | 0x01;
    blk=GrPlotSave(blk->xml,"extent",ext);
    XMLSetStart(blk->xml,GrPlotExtentStart,blk);
    XMLSetEnd(blk->xml,GrPlotExtentEnd,blk);
    return XMLCallStart(blk->xml,name,atnum,atname,atval,buf,sze);
  }

  if (strcmp(name,"name")==0) {
    struct GrPlotString *str;
    str=malloc(sizeof(struct GrPlotString));
    str->txt=&ptr->name; 
    str->inc=&plt->inc;
    blk=GrPlotSave(blk->xml,"name",str);
    XMLSetStart(blk->xml,GrPlotStringStart,blk);
    XMLSetText(blk->xml,GrPlotStringText,blk);
    XMLSetEnd(blk->xml,GrPlotStringEnd,blk);
    return XMLCallStart(blk->xml,name,atnum,atname,atval,buf,sze);
  }

  if (strcmp(name,"include")==0) {
    struct GrPlotInclude *inc;
    inc=malloc(sizeof(struct GrPlotInclude));
    inc->inc=&plt->inc;
    blk=GrPlotSave(blk->xml,name,inc);
    XMLSetStart(blk->xml,GrPlotIncludeStart,blk);
    XMLSetEnd(blk->xml,GrPlotIncludeEnd,blk);
    return XMLCallStart(blk->xml,name,atnum,atname,atval,buf,sze);
  }


  return 0;
}


int GrPlotImageNameEnd(char *name,char *buf,int sze,void *data) {

  struct GrPlotBlock *blk;
  struct GrPlotImageName *ptr;
  struct GrPlotData *plt;

  blk=(struct GrPlotBlock *) data;
  if (blk==NULL) return -1;
  ptr=(struct GrPlotImageName *) blk->data;
  if (ptr==NULL) return -1;
  plt=ptr->plt;

  if (strcmp(name,blk->name)==0) {
    struct PlotData *plot;
    plot=plt->plot;
    if (plot==NULL) return -1;
    if (ptr->state !=0x01) return -1;
    if (ptr->name==NULL) return -1;
    
    if (ptr->off !=NULL) {
      ptr->x+=(ptr->off)->x;
      ptr->y+=(ptr->off)->y;
    }


    PlotImageName(plot,plt->num,ptr->matrix,ptr->name,ptr->dx,ptr->dy,
             ptr->x,ptr->y,
             ptr->xmin,ptr->xmax,ptr->ymin,ptr->ymax,
             ptr->mask);
    
    if (ptr->matrix !=NULL) free(ptr->matrix);
    free(ptr->name);
    free(ptr);
    GrPlotRestore(blk);
    return 0;
  }
  return 0;
}

