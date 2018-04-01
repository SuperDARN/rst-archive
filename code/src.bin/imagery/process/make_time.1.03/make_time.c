/* make_time.c
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
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "rtime.h"
#include "option.h"

#include "errstr.h"
#include "hlpstr.h"

/*
 $Log: make_time.c,v $
 Revision 1.5  2007/07/20 20:29:58  code
 Added the ability to set the format on the command line.

 Revision 1.4  2005/08/09 15:51:01  barnes
 Added option to dump the command line options.

 Revision 1.3  2004/05/04 20:09:42  barnes
 Removed redundant header.

 Revision 1.2  2004/04/27 20:16:32  barnes
 Audit - Enforced warning set to "all".

 Revision 1.1  2003/03/13 00:24:15  barnes
 Initial revision

*/

struct OptionData opt;

int output(FILE *fp,char *format,int yr,int mo,int dy,int hr,
           int mt,double sc) {  
  int n=0;

  while(format[n] !=0) {
    switch (format[n]) {
    case '%':
      n++;
      if (format[n]==0) break;
      switch (format[n]) {
      case 'y':
        fprintf(fp,"%.4d",yr);
        break;
      case 'M':
        fprintf(fp,"%.2d",mo);
        break;
      case 'd':
        fprintf(fp,"%.2d",dy);
        break;
      case 'h':
        fprintf(fp,"%.2d",hr);
        break;
      case 'm':
        fprintf(fp,"%.2d",mt);
        break;
      case 's':
        fprintf(fp,"%f",sc);
        break;
      }
      n++;
      break;
    case '\\':
      n++;
      switch (format[n]) {
      case 'n':
	fputc('\n',fp);
        break;
      }
      n++;
      break;
    default :
      fputc(format[n],fp);
      n++;
    }
  }
  return 0;
}


double strdate(char *text) {
  double tme;
  int val;
  int yr,mo,dy;
  val=atoi(text);
  dy=val % 100;
  mo=(val / 100) % 100;
  yr=(val / 10000);
  if (yr<1970) yr+=1900;  
  tme=TimeYMDHMSToEpoch(yr,mo,dy,0,0,0);

  return tme;
}




double strtime(char *text) {
  int hr,mn;
  double sc;
  int i,j;
  for (i=0;(text[i] !=':') && (text[i] !=0);i++);
  if (text[i]==0) return atoi(text)*3600L;
  text[i]=0;
  hr=atoi(text);
  for (j=i+1;(text[j] !=':') && (text[j] !=0);j++);
  if (text[j]==0) { 
    mn=atoi(text+i+1);
    return (double) hr*3600L+mn*60L;
  }
  text[j]=0;
  mn=atoi(text+i+1);
  sc=atof(text+j+1);
  return (double) hr*3600L+mn*60L+sc;
}   

int main (int argc,char *argv[]) {
  int arg;
 
  int yr,mo,dy,hr,mt;
  double sc;

  char *stmestr=NULL;
  char *etmestr=NULL;
  char *sdtestr=NULL;
  char *edtestr=NULL;
  char *exstr=NULL;
  int frames=100;
  double atime;
  double tstp=600;
  double stime=-1;
  double etime=-1;
  double extime=0;
 
  double sdate=-1;
  double edate=-1;

  unsigned char help=0;
  unsigned char option=0;

  
  char format[1024]={"-d %y%M%d -t %h:%m:%s\n"};
  char *uformat=NULL;

  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  OptionAdd(&opt,"st",'t',&stmestr);
  OptionAdd(&opt,"et",'t',&etmestr);
  OptionAdd(&opt,"sd",'t',&sdtestr);
  OptionAdd(&opt,"ed",'t',&edtestr);
  OptionAdd(&opt,"ex",'t',&exstr);
  OptionAdd(&opt,"f",'i',&frames);
  OptionAdd(&opt,"s",'d',&tstp);
  OptionAdd(&opt,"fmt",'t',&uformat);


  arg=OptionProcess(1,argc,argv,&opt,NULL);

  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }
  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }


  if (exstr !=NULL) extime=strtime(exstr);
  if (stmestr !=NULL) stime=strtime(stmestr);
  if (etmestr !=NULL) etime=strtime(etmestr);
  if (sdtestr !=NULL) sdate=strdate(sdtestr);
  if (edtestr !=NULL) edate=strdate(edtestr);

  if (uformat !=NULL) strcpy(format,uformat);

  stime+=sdate;

  if (etime !=-1) {
    if (edate==-1) etime+=stime - ( (int) stime % (24*3600));
    else etime+=edate;
  }
  if (extime !=0) etime=stime+extime;

  if (etime !=-1) tstp=(etime-stime)/frames;
  else etime=stime+tstp*frames;


  atime=stime;
  do {
    TimeEpochToYMDHMS(atime,&yr,&mo,&dy,&hr,&mt,&sc);
    output(stdout,format,yr,mo,dy,hr,mt,sc);
    atime+=tstp;
  } while (atime<etime);
  return 0; 
} 






















