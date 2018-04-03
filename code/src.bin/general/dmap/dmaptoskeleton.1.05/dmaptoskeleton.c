/* dmaptoskeleton.c
   ================
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
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "rtypes.h"
#include "option.h"
#include "dmap.h"
#include "hlpstr.h"
#include "errstr.h"


/*
 $Log: dmaptoskeleton.c,v $
 Revision 1.6  2005/08/08 14:48:43  barnes
 Added option to dump the command line options

 Revision 1.5  2004/07/14 17:43:22  barnes
 Added help and error message.

 Revision 1.4  2004/06/22 18:16:46  barnes
 Changed reporting of integers to int.

 Revision 1.3  2004/06/22 18:12:49  barnes
 Changed references of Long to Int.

 Revision 1.2  2004/05/04 19:11:07  barnes
  Renamed the type header to avoid confusion.

 Revision 1.1  2004/04/27 17:45:44  barnes
 Initial revision

*/

#define STRINGSIZE 256

int snum=0;
struct DataMapScalar **sptr=NULL;
char **cdfsname;


int anum=0;
struct DataMapArray **aptr=NULL;
char **cdfaname;

int32 *rptr=NULL;
int32 *roff=NULL;
int rnum=0; 


struct OptionData opt;
int arg=0;

int main(int argc,char *argv[]) {
  int status=0;
  struct DataMap *ptr;
  struct DataMapScalar *sx=NULL,*sy=NULL;
  struct DataMapArray *ax=NULL,*ay=NULL;

  char buf[1024];
  unsigned char vbflg=0;

  FILE *fp;
  int c,i;
  int x=0,n;
  int tab;

  char *cdfname=NULL;
  char *cdfdef={"dmapcdf"};
  int block=0;
  int rnum=0,znum=0;
  int nelm=0;
  unsigned char help=0;
  unsigned char option=0;


  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  OptionAdd(&opt,"vb",'x',&vbflg);

  if (argc>1) {
    arg=OptionProcess(1,argc,argv,&opt,NULL); 
    if (help==1) {
      OptionPrintInfo(stdout,hlpstr);
      exit(0);
    }
    if (option==1) {
      OptionDump(stdout,&opt);
      exit(0);
    }

    fp=fopen(argv[arg],"r");
    if (fp==NULL) {
      fprintf(stderr,"File not found.\n");
      exit(-1);
    }  
  } else {
    OptionPrintInfo(stdout,errstr);
    exit(-1);
  }


  if (cdfname==NULL) cdfname=cdfdef;

  while ((ptr=DataMapFread(fp)) !=NULL) {


    for (c=0;c<ptr->snum;c++) {
      sx=ptr->scl[c];
      for (n=0;n<snum;n++) {
	sy=sptr[n];
        if (strcmp(sx->name,sy->name) !=0) continue;
        if (sx->type !=sy->type) continue;
        break;
      }
      if (n==snum) {
	/* copy the scalar */
        if (sptr==NULL) sptr=malloc(sizeof(struct DataMapScalar *));
        else {
          struct DataMapScalar **tmp;
          tmp=realloc(sptr,(snum+1)*sizeof(struct DataMapScalar *));
          if (tmp==NULL) break;
          sptr=tmp;
	}
        sptr[snum]=DataMapMakeScalar(sx->name,sx->type,NULL);
        snum++;
      }
    }
    if (c !=ptr->snum) {      
      status=-1;
      break;
    }
    for (c=0;c<ptr->anum;c++) {
      ax=ptr->arr[c];
      for (n=0;n<anum;n++) {
        ay=aptr[n];
        if (strcmp(ax->name,ay->name) !=0) continue;
        if (ax->type != ay->type) continue;
        if (ax->dim != ay->dim) continue;
        break;
      }
      if (n !=anum) {
        /* check the ranges */
        for (i=0;i<ax->dim;i++)
          if (ax->rng[i]>rptr[roff[n]+i]) rptr[roff[n]+i]=ax->rng[i];
      }

      if (n==anum) {
	/* copy the array */
      
        if (roff==NULL) roff=malloc(sizeof(int32));
        else {
          int32 *tmp;
          tmp=realloc(roff,(anum+1)*sizeof(int32));
          if (tmp==NULL) break;
	  roff=tmp;
	}
        roff[anum]=rnum;
        if (rptr==NULL) rptr=malloc(sizeof(int32)*ax->dim);
        else {
          int32 *tmp;
          tmp=realloc(rptr,(rnum+ax->dim)*sizeof(int32));
          if (tmp==NULL) break;
	  rptr=tmp;
	}
        for (i=0;i<ax->dim;i++) rptr[rnum+i]=ax->rng[i];
        rnum+=ax->dim;
	
        if (aptr==NULL) aptr=malloc(sizeof(struct DataMapArray *));
        else {
          struct DataMapArray **tmp;
          tmp=realloc(aptr,(anum+1)*sizeof(struct DataMapArray *));
          if (tmp==NULL) break;
          aptr=tmp;
	}
        aptr[anum]=DataMapMakeArray(ax->name,ax->type,ax->dim,NULL,
				    NULL);
        anum++;
       

      }

    }
    if (c !=ptr->anum) {
       status=-1;
       break;
    }
    DataMapFree(ptr);
    block++;
  }
  fclose(fp);

  if (status==-1) {
    fprintf(stderr,"Error processing file.\n");
    exit(-1);
  }

  for (n=0;n<anum;n++) { 
     ax=aptr[n];
     ax->rng=rptr+roff[n];
     for (c=0;c<ax->dim;c++) if (ax->rng[c]==0) break; /* bad data */
     if (c !=ax->dim) ax->dim=0;
  }


  cdfsname=malloc(sizeof(char *)*snum);
  if (cdfsname==NULL) {
    fprintf(stderr,"Could not allocate scalar name table.\n");
    exit(-1);
  }

  cdfaname=malloc(sizeof(char *)*anum);
  if (cdfaname==NULL) {
    fprintf(stderr,"Could not allocate array name table.\n");
    exit(-1);
  }



  for (n=0;n<snum;n++) { 
    sx=sptr[n];
    cdfsname[n]=malloc(strlen(sx->name)+1);
    for (c=0;sx->name[c] !=0;c++) 
       if (isalnum(sx->name[c])) cdfsname[n][c]=sx->name[c];
	   else cdfsname[n][c]='_';
    cdfsname[n][c]=0;
    x=0;
    for (c=0;c<n;c++) if (strncmp(cdfsname[c],cdfsname[n],
                          strlen(cdfsname[n]))==0) x++;; 
    if (x !=0) {
      char *tmp;
      char txt[4];
      x++;
      sprintf(txt,"%.3d",x);
      tmp=realloc(cdfsname[n],strlen(cdfsname[n])+4);
      if (tmp==NULL) break;
      cdfsname[n]=tmp;
      strcat(cdfsname[n],txt);
    }
  }

  if (n !=snum) {
    fprintf(stderr,"Error generating names.\n");
    exit(-1);
  }

  for (n=0;n<anum;n++) { 
    ax=aptr[n];
    cdfaname[n]=NULL;
    if (ax->dim==0) continue;
    cdfaname[n]=malloc(strlen(ax->name)+1);
    for (c=0;ax->name[c] !=0;c++) 
       if (isalnum(ax->name[c])) cdfaname[n][c]=ax->name[c];
	   else cdfaname[n][c]='_';
    cdfaname[n][c]=0;
    for (c=0;c<n;c++) if (strncmp(cdfaname[c],cdfaname[n],
                          strlen(cdfaname[n]))==0) x++;
    if (x !=0) {
      char *tmp;
      char txt[4];
      x++;
      sprintf(txt,"%.3d",x);
      tmp=realloc(cdfaname[n],strlen(cdfaname[n])+4);
      if (tmp==NULL) break;
      cdfaname[n]=tmp;
      strcat(cdfaname[n],txt);
    }

  }

  if (n !=anum) {
    fprintf(stderr,"Error generating names.\n");
    exit(-1);
  }

  rnum=snum;
  znum=anum;

  fp=fopen(argv[2],"w");
  fprintf(fp,"#header\n");
  fprintf(fp,"                            CDF NAME: %s\n",cdfname);
  fprintf(fp,"                       DATA ENCODING: NETWORK\n");
  fprintf(fp,"                            MAJORITY: ROW\n");
  fprintf(fp,"                              FORMAT: SINGLE\n\n");
  fprintf(fp,
     "! Variables  G.Attributes  V.Attributes  Records  Dims  Sizes\n");
  fprintf(fp,
     "! ---------  ------------  ------------  -------  ----  -----\n");
  fprintf(fp,
     "  %d/%d           0             0         %d/z    0\n",
     rnum,znum,block);

  fprintf(fp,"\n#GLOBALattributes\n");
  fprintf(fp,"\n#VARIABLEattributes\n");
 
  fprintf(fp,"\n#variables\n\n");
  for (n=0;n<snum;n++) {
    sx=sptr[n];
    fprintf(fp,"! Variable          Data      Number    Record   Dimension\n");
    fprintf(fp,"! Name              Type     Elements  Variance  Variances\n");
    fprintf(fp,"! --------          ----     --------  --------  ---------\n");
    fprintf(fp,"\n");
    sprintf(buf,"  %c%s%c",'"',cdfsname[n],'"');
    fprintf(fp,buf);
    tab=18-strlen(buf);
    if (tab>0) for (c=0;c<tab;c++) fprintf(fp," ");
    else fprintf(fp," ");
    switch (sx->type) {
    case DATACHAR:
      fprintf(fp,"CDF_CHAR  ");
      break;
    case DATASHORT:
      fprintf(fp,"CDF_INT2  ");
      break;
    case DATAINT:
      fprintf(fp,"CDF_INT4  ");
      break;
    case DATAFLOAT:
      fprintf(fp,"CDF_FLOAT ");
      break;
    case DATADOUBLE:
      fprintf(fp,"CDF_DOUBLE");
      break;
    case DATASTRING:
      fprintf(fp,"CDF_CHAR  ");
      break;

    }
    nelm=1;
    if (sx->type==DATASTRING) nelm=STRINGSIZE;
    fprintf(fp,"    %d         T          ",nelm);
    fprintf(fp,"\n\n");
    fprintf(fp,"! Attribute         Data     Value\n");
    fprintf(fp,"! Name              Type\n");
    fprintf(fp,"! --------          ----     --------\n");
    fprintf(fp,"\n.\n\n");


  }  
  fprintf(fp,"\n#zVariables\n\n");


  for (n=0;n<anum;n++) {
    ax=aptr[n];

    fprintf(fp,"! Variable          Data      Number");
    fprintf(fp,"                 Record   Dimension\n");
    fprintf(fp,"! Name              Type     Elements  Dims");
    fprintf(fp,"  Sizes  Variance  Variances\n");
    fprintf(fp, "! --------          ----     --------  ----");
    fprintf(fp,"  -----  --------  ---------\n");
    fprintf(fp,"\n");
    sprintf(buf,"  %c%s%c",'"',cdfaname[n],'"');
    fprintf(fp,buf);
    tab=18-strlen(buf);
    if (tab>0) for (c=0;c<tab;c++) fprintf(fp," ");
    else fprintf(fp," ");
    switch (ax->type) {
    case DATACHAR:
      fprintf(fp,"CDF_CHAR  ");
      break;
    case DATASHORT:
      fprintf(fp,"CDF_INT2  ");
      break;
    case DATAINT:
      fprintf(fp,"CDF_INT4  ");
      break;
    case DATAFLOAT:
      fprintf(fp,"CDF_FLOAT ");
      break;
    case DATADOUBLE:
      fprintf(fp,"CDF_DOUBLE");
      break;
    case DATASTRING:
      fprintf(fp,"CDF_CHAR  ");
      break;

    }

    nelm=1;
    if (ax->type==DATASTRING) nelm=STRINGSIZE;
    fprintf(fp,"    %d         %d     ",nelm,ax->dim);
    for (c=0;c<ax->dim;c++) fprintf(fp,"%d ",ax->rng[c]);
    fprintf(fp,"    T     ");
    for (c=0;c<ax->dim;c++) fprintf(fp,"T ");
    fprintf(fp,"\n\n");
    fprintf(fp,"! Attribute         Data     Value\n");
    fprintf(fp,"! Name              Type\n");
    fprintf(fp,"! --------          ----     --------\n");
    fprintf(fp,"\n.\n\n");

  }

  fprintf(fp,"#end\n\n");

  fp=fopen(argv[3],"w");
  for (n=0;n<snum;n++) {
   fprintf(fp,"\t");
     sx=sptr[n];
     switch(sx->type) {
     case DATACHAR:
        fprintf(fp,"char 0");
        break;
     case DATASHORT:
        fprintf(fp,"short 0");
        break;
     case DATAINT:
        fprintf(fp,"int 0");
        break;
     case DATAFLOAT:
        fprintf(fp,"float 0");
        break;
     case DATADOUBLE:
        fprintf(fp,"double 0");
        break;
     case DATASTRING:
        fprintf(fp,"string 0"); 
    }
    fprintf(fp," %c%s%c=%s;\n",'"',sx->name,'"',cdfsname[n]);
  }

  for (n=0;n<anum;n++) {
   fprintf(fp,"\t");
     ax=aptr[n];
     if (ax->dim==0) continue;
     switch(ax->type) {
     case DATACHAR:
        fprintf(fp,"char");
        break;
     case DATASHORT:
        fprintf(fp,"short");
        break;
     case DATAINT:
        fprintf(fp,"int");
        break;
     case DATAFLOAT:
        fprintf(fp,"float");
        break;
     case DATADOUBLE:
        fprintf(fp,"double");
        break;
     case DATASTRING:
        fprintf(fp,"string"); 
    }
    fprintf(fp," %d",ax->dim); 
    fprintf(fp," %c%s%c=%s;\n",'"',ax->name,'"',cdfaname[n]);
  }
  fclose(fp);
  return 0;
}
