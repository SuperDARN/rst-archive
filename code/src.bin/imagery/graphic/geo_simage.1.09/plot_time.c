/* plot_time.c
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
#include <math.h>
#include <ctype.h>

#include "rfbuffer.h"
#include "rplot.h"
#include "rtime.h"
#include "text_box.h"

/*
 $Log: plot_time.c,v $
 Revision 1.4  2005/11/02 20:46:19  barnes
 Modifications to handle GUVI L1C data.

 Revision 1.3  2004/06/21 22:16:21  barnes
 Added missing header.

 Revision 1.2  2004/04/27 20:25:21  barnes
 Audit - Enforced warning set to "all".

 Revision 1.1  2004/03/09 19:50:34  barnes
 Initial revision

*/

void plot_time(struct Rplot *rplot,
               float xoff,float yoff,float wdt,float hgt,
               double stime,double etime,
               unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {
  int i;
  char txt[256];
  float txbox[3];
  char *month[]={"Jan","Feb","Mar","Apr","May","Jun",
               "Jul","Aug","Sep","Oct","Nov","Dec",0};
  char *tmeA="00:00:00 UT";
  char *tmeB="0000-00-00 00:00:00 UT";
  char *tmeC="0";
  char *start="Start:";
  char *end="End:";
  float cwdt;
  float x,y;
  int syr,smo,sdy,shr,smt,ssc,eyr,emo,edy,ehr,emt,esc;
  double sec;

  TimeEpochToYMDHMS(etime,&eyr,&emo,&edy,&ehr,&emt,&sec);
  esc=sec;
  TimeEpochToYMDHMS(stime,&syr,&smo,&sdy,&shr,&smt,&sec);
  ssc=sec;


  if (stime==etime) {
    txtbox(fontname,fontsize,strlen(tmeC),tmeC,txbox,txtdata);
    cwdt=txbox[0];

    sprintf(txt,"%.2d %s %d",sdy,month[smo-1],syr);
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

    sprintf(txt,"%.2d:%.2d:%.2d UT",shr,smt,ssc);
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
  } else {
    txtbox(fontname,fontsize,strlen(tmeC),tmeC,txbox,txtdata);
    cwdt=txbox[0];
    sprintf(txt,"%.4d-%.2d-%.2d %.2d:%.2d:%.2dUT",
                  syr,smo,sdy,shr,smt,ssc);
    txtbox(fontname,fontsize,strlen(tmeB),tmeB,txbox,txtdata);
    x=xoff+wdt-txbox[0];
    y=yoff+txbox[2];
    txtbox(fontname,fontsize,strlen(start),start,txbox,txtdata);
    RplotText(rplot,NULL,fontname,fontsize,x-txbox[0],
                y,strlen(start),start,color,mask,1);

    for (i=0;txt[i] !=0;i++) {
      txtbox(fontname,fontsize,1,txt+i,txbox,txtdata);
      RplotText(rplot,NULL,fontname,fontsize,x,
                y,1,txt+i,color,mask,1);
      if (isdigit(txt[i])) x+=cwdt;
      else x+=txbox[0];
    }
    
    sprintf(txt,"%.4d-%.2d-%.2d %.2d:%.2d:%.2dUT",
                  eyr,emo,edy,ehr,emt,esc);
    txtbox(fontname,fontsize,strlen(tmeB),tmeB,txbox,txtdata);
    x=xoff+wdt-txbox[0];
    y+=txbox[2]-txbox[1]+6;

    txtbox(fontname,fontsize,strlen(end),end,txbox,txtdata);
    RplotText(rplot,NULL,fontname,fontsize,x-txbox[0],
                y,strlen(end),end,color,mask,1);

    for (i=0;txt[i] !=0;i++) {
      txtbox(fontname,fontsize,1,txt+i,txbox,txtdata);
      RplotText(rplot,NULL,fontname,fontsize,x,
                y,1,txt+i,color,mask,1);
      if (isdigit(txt[i])) x+=cwdt;
      else x+=txbox[0];
    }
  }
}
  
