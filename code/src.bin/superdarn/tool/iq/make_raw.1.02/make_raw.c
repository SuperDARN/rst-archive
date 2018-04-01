/* make_raw.c
   ==========
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
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "rtypes.h"
#include "dmap.h"
#include "rconvert.h"
#include "option.h"
#include "rtime.h"
#include "limit.h"
#include "rprm.h"
#include "iqdata.h"
#include "rawdata.h"

#include "iqread.h"
#include "rawwrite.h"

#include "tsg.h"
#include "acf.h"
#include "radar.h"

#include "errstr.h"
#include "hlpstr.h"

/*
 $Log: make_raw.c,v $
 Revision 1.2  2008/03/19 00:20:51  code
 Fixed some bugs in the lag table decoding.

 Revision 1.1  2008/03/18 21:51:36  code
 Initial revision

 Revision 1.1  2008/03/18 15:45:52  code
 Initial revision

*/

#define ACF_PART 0
#define XCF_PART 1
#define REAL_BUF_OFFSET 0
#define IMAG_BUF_OFFSET 1

struct RadarNetwork *network;  
struct Radar *radar;
struct RadarSite *site;

struct OptionData opt;

float pwr0[MAX_RANGE];
float acfd[MAX_RANGE*LAG_SIZE*2];
float xcfd[MAX_RANGE*LAG_SIZE*2];

int loadlag(FILE *fp,int (*lag)[2]) {
  /* load the lag table */
  char txt[256];
  int lagnum=0,c,real,imag;
  while(fgets(txt,255,fp) !=NULL) {
    for (c=0;(txt[c] !=0) && (c<256);c++) 
      if (txt[c]=='#') break;
    if (txt[c]=='#') continue;
    if (sscanf(txt,"%d %d\n",&real,&imag) !=2) continue;
    lag[lagnum][0]=real;
    lag[lagnum][1]=imag; 
    lagnum++;
  }
  return lagnum-1;
}


int main (int argc,char *argv[]) {

  int arg;
  char *envstr;
  unsigned char help=0;
  unsigned char option=0;
  unsigned char vb=0;

  FILE *fp;
  char *lagfname=NULL;
  struct RadarParm prm;
  struct IQData iq;
  struct RawData raw;
  int16 *samples=NULL;  
  int16 *ptr;

  int i,j,n;
  int badrng=0;
  int aflg,abflg;
  int thr=0,lmt=0;
  int atstp=0;

  struct TSGprm tprm;
  int lag[LAG_SIZE][2];
  int pulse[PULSE_SIZE];
  int lagsum[LAG_SIZE];

  int lagnum=0,mplgs=0;

  int roff=REAL_BUF_OFFSET;
  int ioff=IMAG_BUF_OFFSET;
  
  float thrsh=0;
  int qiflg=0;
  int skpval=0;

  envstr=getenv("SD_RADAR");
  if (envstr==NULL) {
    fprintf(stderr,"Environment variable 'SD_RADAR' must be defined.\n");
    exit(-1);
  }

  fp=fopen(envstr,"r");

  if (fp==NULL) {
    fprintf(stderr,"Could not locate radar information file.\n");
    exit(-1);
  }

  network=RadarLoad(fp);
  fclose(fp); 
  if (network==NULL) {
    fprintf(stderr,"Failed to read radar information.\n");
    exit(-1);
  }

  envstr=getenv("SD_HDWPATH");
  if (envstr==NULL) {
    fprintf(stderr,"Environment variable 'SD_HDWPATH' must be defined.\n");
    exit(-1);
  }

  RadarLoadHardware(envstr,network);

  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);
  OptionAdd(&opt,"vb",'x',&vb);
  OptionAdd(&opt,"t",'f',&thrsh);
  OptionAdd(&opt,"qi",'x',&qiflg);
  OptionAdd(&opt,"skip",'i',&skpval);


  OptionAdd(&opt,"lagtable",'t',&lagfname);

  arg=OptionProcess(1,argc,argv,&opt,NULL);

  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }

  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }

  if (qiflg) {
    roff=IMAG_BUF_OFFSET;
    ioff=REAL_BUF_OFFSET;
  }


  if (lagfname !=NULL) {
    fp=fopen(lagfname,"r");
    if (fp==NULL) {
      fprintf(stderr,"Could not open lag table\n");
      exit(1);
    }
    lagnum=loadlag(fp,lag);
    fclose(fp);
  }

  if (arg==argc) fp=stdin;
  else fp=fopen(argv[arg],"r");

  if (fp==NULL) {
    fprintf(stderr,"File not found.\n");
    exit(-1);
  }



  while (IQFread(fp,&prm,&iq,&samples) !=-1) {
    if (vb) 
      fprintf(stderr,"%d-%d-%d %d:%d:%d beam=%d\n",prm.time.yr,prm.time.mo,
	     prm.time.dy,prm.time.hr,prm.time.mt,prm.time.sc,prm.bmnum);

    
    /* get the hardware info */

     radar=RadarGetRadar(network,prm.stid);
     if (radar==NULL) {
      fprintf(stderr,"Failed to get radar information.\n");
      break;
    }

    site=RadarYMDHMSGetSite(radar,prm.time.yr,prm.time.mo,
	  	          prm.time.dy,prm.time.hr,prm.time.mt,
                          prm.time.sc);

    if (site==NULL) {
      fprintf(stderr,"Failed to get site information.\n");
      break;
    }

    atstp=site->atten;

    /* zero our arrays */

    for (i=0;i<MAX_RANGE;i++) {
      pwr0[i]=0;
      for (j=0;j<LAG_SIZE*2;j++) {
        acfd[i*LAG_SIZE*2+j]=0;
        xcfd[i*LAG_SIZE*2+j]=0;
      }
    }

     if (lagnum==0) {
       for (i=0;i<2;i++) {
         for (j=0;j<=prm.mplgs;j++) lag[j][i]=prm.lag[j][i];
       }
       mplgs=prm.mplgs;
     } 

     if (skpval==0) skpval=iq.skpnum;   

    tprm.nrang=prm.nrang;
    tprm.lagfr=prm.lagfr;
    tprm.smsep=prm.smsep;
    tprm.mpinc=prm.mpinc;
    tprm.txpl=prm.txpl;
    tprm.mppul=prm.mppul;
    tprm.smdelay=skpval;
    tprm.pat=pulse;




    for (i=0;i<prm.mppul;i++) pulse[i]=prm.pulse[i];
 
    badrng=ACFBadLagZero(&tprm,prm.mplgs,lag);

    for (j=0;j<LAG_SIZE;j++) lagsum[j]=0;


    if (lagnum !=0) {
      int mplgs=0;      
      for (j=0;j<lagnum;j++) {
        i=abs(lag[j][0]-lag[j][1]);
        lagsum[i]++;
        if (i>mplgs) mplgs=i;
      }
    } 

    
    for (n=0;n<iq.seqnum;n++) {

      ptr=samples+iq.offset[n];

      aflg=ACFSumPower(&tprm,mplgs,lag,pwr0,
		       ptr,2*iq.chnnum,skpval !=0,
                       roff,ioff,badrng,
                       iq.noise[n],prm.mxpwr,prm.atten*atstp,
                       thr,lmt,&abflg);
       

      ACFCalculate(&tprm,ptr,2*iq.chnnum,skpval !=0,
                       roff,ioff,mplgs,lagnum,
	  	       lag,acfd,ACF_PART,2,badrng,iq.atten[n]*atstp,NULL);

      if (prm.xcf==1) ACFCalculate(&tprm,ptr,
				     2*iq.chnnum,skpval !=0,
                                     roff,ioff,prm.mplgs,
	  	                     lagnum,lag,xcfd,XCF_PART,2,badrng,
				     iq.atten[n]*atstp,NULL);

      if ((n>0) && (iq.atten[n] !=iq.atten[n-1]))
              ACFNormalize(pwr0,acfd,xcfd,prm.nrang,prm.mplgs,atstp); 
             

    }    
    if (lagnum==0) 
      ACFAverage(pwr0,acfd,xcfd,NULL,prm.nave,prm.nrang,prm.mplgs);
    else 
      ACFAverage(pwr0,acfd,xcfd,lagsum,prm.nave,prm.nrang,prm.mplgs);

    for (i=0;i<prm.nrang;i++) raw.pwr0[i]=pwr0[i];
    for (i=0;i<prm.nrang;i++) {
      for (j=0;j<prm.mplgs;j++) {
        raw.acfd[i][j][0]=acfd[(i*prm.mplgs*2)+(2*j)];
        raw.acfd[i][j][1]=acfd[(i*prm.mplgs*2)+(2*j)+1];
        raw.xcfd[i][j][0]=xcfd[(i*prm.mplgs*2)+(2*j)];
        raw.xcfd[i][j][1]=xcfd[(i*prm.mplgs*2)+(2*j)+1];
      }
    }
    raw.thr=thrsh;
    RawFwrite(stdout,&prm,&raw);
     

  }
  if (fp !=stdin) fclose(fp);
  return 0;
} 






















