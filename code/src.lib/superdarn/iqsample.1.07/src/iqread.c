/* iqread.c
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
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "rtypes.h"
#include "dmap.h"
#include "limit.h"
#include "rprm.h"
#include "iqdata.h"

/*
 $Log: iqread.c,v $
 Revision 1.6  2008/03/25 15:32:45  code
 Fixed problem with reading files with empty records.

 Revision 1.5  2008/03/18 16:26:48  code
 Fixed bugs in reading in the file.

 Revision 1.4  2008/03/14 18:03:13  code
 Added missing header.

 Revision 1.3  2008/03/14 16:15:37  code
 Added a variable that indicates number of samples to skip before performin calculations.

 Revision 1.2  2008/03/13 19:22:18  code
 Changed format to include receiver channel.

 Revision 1.1  2008/03/13 17:32:30  code
 Initial revision

*/



int IQDecode(struct DataMap *ptr,struct RadarParm *prm,
              struct IQData *iqdata,int16 **samples) {



  int c,x;

  struct DataMapScalar *s;
  struct DataMapArray *a;

  memset(prm,0,sizeof(struct RadarParm));
  memset(iqdata,0,sizeof(struct IQData));
  for (c=0;c<ptr->snum;c++) {
    s=ptr->scl[c];
   
    if ((strcmp(s->name,"radar.revision.major")==0) && (s->type==DATACHAR))
      prm->revision.major=*(s->data.cptr);
    if ((strcmp(s->name,"radar.revision.minor")==0) && (s->type==DATACHAR))
      prm->revision.minor=*(s->data.cptr);

    if ((strcmp(s->name,"origin.code")==0) && (s->type==DATACHAR))
      prm->origin.code=*(s->data.cptr);

    if ((strcmp(s->name,"origin.time")==0) && (s->type==DATASTRING))
      strncpy(prm->origin.time,*((char **) s->data.vptr),ORIGIN_TIME_SIZE);

    if ((strcmp(s->name,"origin.command")==0) && (s->type==DATASTRING))
      strncpy(prm->origin.command,*((char **) s->data.vptr),ORIGIN_COMMAND_SIZE);


    if ((strcmp(s->name,"cp")==0) && (s->type==DATASHORT))
      prm->cp=*(s->data.sptr);
    if ((strcmp(s->name,"stid")==0) && (s->type==DATASHORT))
      prm->stid=*(s->data.sptr);
    if ((strcmp(s->name,"time.yr")==0) && (s->type==DATASHORT))
      prm->time.yr=*(s->data.sptr);
    if ((strcmp(s->name,"time.mo")==0) && (s->type==DATASHORT))
      prm->time.mo=*(s->data.sptr);
    if ((strcmp(s->name,"time.dy")==0) && (s->type==DATASHORT))
      prm->time.dy=*(s->data.sptr);
    if ((strcmp(s->name,"time.hr")==0) && (s->type==DATASHORT))
      prm->time.hr=*(s->data.sptr);
    if ((strcmp(s->name,"time.mt")==0) && (s->type==DATASHORT))
      prm->time.mt=*(s->data.sptr);
    if ((strcmp(s->name,"time.sc")==0) && (s->type==DATASHORT))
      prm->time.sc=*(s->data.sptr);
    if ((strcmp(s->name,"time.us")==0) && (s->type==DATAINT))
      prm->time.us=*(s->data.lptr);
    if ((strcmp(s->name,"txpow")==0) && (s->type==DATASHORT))
      prm->txpow=*(s->data.sptr);
    if ((strcmp(s->name,"nave")==0) && (s->type==DATASHORT))
      prm->nave=*(s->data.sptr);
    if ((strcmp(s->name,"atten")==0) && (s->type==DATASHORT))
      prm->atten=*(s->data.sptr);
    if ((strcmp(s->name,"lagfr")==0) && (s->type==DATASHORT))
      prm->lagfr=*(s->data.sptr);
    if ((strcmp(s->name,"smsep")==0) && (s->type==DATASHORT))
      prm->smsep=*(s->data.sptr);
    if ((strcmp(s->name,"ercod")==0) && (s->type==DATASHORT))
      prm->ercod=*(s->data.sptr);
    if ((strcmp(s->name,"stat.agc")==0) && (s->type==DATASHORT))
      prm->stat.agc=*(s->data.sptr);
    if ((strcmp(s->name,"stat.lopwr")==0) && (s->type==DATASHORT))
      prm->stat.lopwr=*(s->data.sptr);
    if ((strcmp(s->name,"noise.search")==0) && (s->type==DATAFLOAT))
      prm->noise.search=*(s->data.fptr);
    if ((strcmp(s->name,"noise.mean")==0) && (s->type==DATAFLOAT))
      prm->noise.mean=*(s->data.fptr);
    if ((strcmp(s->name,"channel")==0) && (s->type==DATASHORT))
      prm->channel=*(s->data.sptr);
    if ((strcmp(s->name,"bmnum")==0) && (s->type==DATASHORT))
      prm->bmnum=*(s->data.sptr);
    if ((strcmp(s->name,"bmazm")==0) && (s->type==DATAFLOAT))
      prm->bmazm=*(s->data.fptr);
    if ((strcmp(s->name,"scan")==0) && (s->type==DATASHORT))
      prm->scan=*(s->data.sptr);
    if ((strcmp(s->name,"offset")==0) && (s->type==DATASHORT))
      prm->offset=*(s->data.sptr);
    if ((strcmp(s->name,"rxrise")==0) && (s->type==DATASHORT))
      prm->rxrise=*(s->data.sptr);
    if ((strcmp(s->name,"intt.sc")==0) && (s->type==DATASHORT))
      prm->intt.sc=*(s->data.sptr);
    if ((strcmp(s->name,"intt.us")==0) && (s->type==DATAINT))
      prm->intt.us=*(s->data.lptr);
    if ((strcmp(s->name,"txpl")==0) && (s->type==DATASHORT))
      prm->txpl=*(s->data.sptr);
    if ((strcmp(s->name,"mpinc")==0) && (s->type==DATASHORT))
      prm->mpinc=*(s->data.sptr);
    if ((strcmp(s->name,"mppul")==0) && (s->type==DATASHORT))
      prm->mppul=*(s->data.sptr);
    if ((strcmp(s->name,"mplgs")==0) && (s->type==DATASHORT))
      prm->mplgs=*(s->data.sptr);
    if ((strcmp(s->name,"nrang")==0) && (s->type==DATASHORT))
      prm->nrang=*(s->data.sptr);
    if ((strcmp(s->name,"frang")==0) && (s->type==DATASHORT))
      prm->frang=*(s->data.sptr);
    if ((strcmp(s->name,"rsep")==0) && (s->type==DATASHORT))
      prm->rsep=*(s->data.sptr);
    if ((strcmp(s->name,"xcf")==0) && (s->type==DATASHORT))
      prm->xcf=*(s->data.sptr);
    if ((strcmp(s->name,"tfreq")==0) && (s->type==DATASHORT))
      prm->tfreq=*(s->data.sptr);

    if ((strcmp(s->name,"mxpwr")==0) && (s->type==DATAINT))
      prm->mxpwr=*(s->data.lptr);
    if ((strcmp(s->name,"lvmax")==0) && (s->type==DATAINT))
      prm->lvmax=*(s->data.sptr);

    if ((strcmp(s->name,"iqdata.revision.major")==0) && (s->type==DATAINT))
      iqdata->revision.major=*(s->data.lptr);
    if ((strcmp(s->name,"iqdata.revision.minor")==0) && (s->type==DATAINT))
      iqdata->revision.minor=*(s->data.sptr);

    if ((strcmp(s->name,"combf")==0) && (s->type==DATASTRING))
      strncpy(prm->combf,*((char **) s->data.vptr),COMBF_SIZE-1);


    if ((strcmp(s->name,"seqnum")==0) && (s->type==DATAINT))
      iqdata->seqnum=*(s->data.lptr);
    if ((strcmp(s->name,"chnnum")==0) && (s->type==DATAINT))
      iqdata->chnnum=*(s->data.lptr);
    if ((strcmp(s->name,"smpnum")==0) && (s->type==DATAINT))
      iqdata->smpnum=*(s->data.lptr);
    if ((strcmp(s->name,"skpnum")==0) && (s->type==DATAINT))
      iqdata->skpnum=*(s->data.lptr);



  }
 
  for (c=0;c<ptr->anum;c++) {
   a=ptr->arr[c];
   if ((strcmp(a->name,"ptab")==0) && (a->type==DATASHORT) &&
        (a->dim==1)) {
      for (x=0;x<a->rng[0];x++) prm->pulse[x]=a->data.sptr[x];
    }

    if ((strcmp(a->name,"ltab")==0) && (a->type==DATASHORT) &&
        (a->dim==2)) {
      for (x=0;x<a->rng[1];x++) {
        prm->lag[x][0]=a->data.sptr[2*x];
        prm->lag[x][1]=a->data.sptr[2*x+1];
      }
    }

    if ((strcmp(a->name,"tsc")==0) && (a->type==DATAINT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->tval[x].tv_sec=a->data.lptr[x];
    }
    if ((strcmp(a->name,"tus")==0) && (a->type==DATAINT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->tval[x].tv_nsec=a->data.lptr[x]*1000;
    }

    if ((strcmp(a->name,"tatten")==0) && (a->type==DATASHORT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->atten[x]=a->data.sptr[x];
    }

    if ((strcmp(a->name,"tnoise")==0) && (a->type==DATAFLOAT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->noise[x]=a->data.fptr[x];
    }

    if ((strcmp(a->name,"toff")==0) && (a->type==DATAINT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->offset[x]=a->data.lptr[x];
    }

    if ((strcmp(a->name,"tsze")==0) && (a->type==DATAINT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      for (x=0;x<a->rng[0];x++) iqdata->size[x]=a->data.lptr[x];
    }

    if ((strcmp(a->name,"data")==0) && (a->type==DATASHORT) &&
        (a->dim==1) && (a->rng[0]>0)) {
      int16 *buf=NULL;
      if (*samples==NULL) buf=malloc(a->rng[0]*sizeof(int16));
      else buf=realloc(*samples,a->rng[0]*sizeof(int16));
      if (buf==NULL) break;
      *samples=buf;
      for (x=0;x<a->rng[0];x++) buf[x]=a->data.sptr[x];
    }
  }
      
  return 0;

}



int IQRead(int fid,struct RadarParm *prm,
              struct IQData *iqdata,int16 **samples) {
  int s;
  struct DataMap *ptr;

  ptr=DataMapRead(fid);
  if (ptr==NULL) return -1;
  s=IQDecode(ptr,prm,iqdata,samples);
  DataMapFree(ptr);
  return s;
}

int IQFread(FILE *fp,struct RadarParm *prm,
              struct IQData *iqdata,int16 **samples) {
  return IQRead(fileno(fp),prm,iqdata,samples);
}

