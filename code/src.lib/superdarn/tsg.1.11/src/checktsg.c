/* checktsg.c
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
#include <string.h>

#include "tsg.h"

/*
 $Log: checktsg.c,v $
 Revision 1.2  2004/06/16 22:01:37  barnes
 Added missing header.

 Revision 1.1  2003/10/31 19:03:19  barnes
 Initial revision

*/

struct TSGtable *TSGMakeTable(int max) {
  struct TSGtable *ptr=NULL;
  if (max==0) return 0;
  ptr=malloc(sizeof(struct TSGtable));
  if (ptr==NULL) return NULL;
  ptr->buf=malloc(sizeof(struct TSGprm)*max);
  if (ptr->buf==NULL) {
    free(ptr);
    return NULL;
  }
  ptr->active=malloc(sizeof(int)*max);
  if (ptr->active==NULL) {
    free(ptr->buf);
    free(ptr);
    return NULL;
  }
  memset(ptr->active,0,sizeof(int)*max);

  ptr->num=0;
  ptr->max=max;
  return ptr;
}

void TSGFreeTable(struct TSGtable *ptr) {
  if (ptr->buf !=NULL) free(ptr->buf);
  free(ptr);
} 

int TSGCmp(struct TSGprm *p1, struct TSGprm *p2) {
  int i;
  if (p1->nrang !=p2->nrang) return -1;
  if (p1->frang !=p2->frang) return -1;
  if (p1->rsep !=p2->rsep) return -1;
  if (p1->mppul != p2->mppul) return -1;
  if (p1->mpinc != p2->mpinc) return -1;
  if (p1->nbaud != p2->nbaud) return -1;
  for (i=0;(i<p1->mppul) && (p1->pat[i]==p2->pat[i]);i++);
  if (i<p1->mppul) return -1;
  return 0;  
}

int TSGCheck(struct TSGprm *tsg,struct TSGtable *tsgtab) {
  int i;
  if (tsgtab->num==0) return -1;
  for (i=tsgtab->num-1;i>=0;i--) {
    if ((tsgtab->active[i]==1) && (TSGCmp(tsg,&tsgtab->buf[i])==0)) break;
  }
  return i;
}

void TSGRemove(struct TSGtable *tsgtab,int id) {
  struct TSGprm *ptr;
  if (tsgtab->num==0) return;
  if (id==tsgtab->num) tsgtab->num--;
  ptr=&tsgtab->buf[id];
  tsgtab->active[id]=0;
  if (ptr->code !=NULL) free(ptr->code);
  if (ptr->pat !=NULL) free(ptr->pat);
}

int TSGAdd(struct TSGprm *tsg,struct TSGtable *tsgtab) {
  struct TSGprm *ptr;
  int i;
  if (tsgtab->num==tsgtab->max) return -1;
  for (i=0;(tsgtab->active[i]==1) && (i<tsgtab->num);i++); 
 
  tsgtab->active[i]=1;
  ptr=&tsgtab->buf[i];
  memcpy(ptr,tsg,sizeof(struct TSGprm));
  if (ptr->mppul !=0) {
    ptr->pat=malloc(sizeof(int)*ptr->mppul);
    if (ptr->pat==NULL) return -1;
    memcpy(ptr->pat,tsg->pat,sizeof(int)*ptr->mppul);
  } 
  if (ptr->nbaud>1) {
    ptr->code=malloc(sizeof(int)*ptr->nbaud);
    if (ptr->code==NULL) {
      if (ptr->pat !=NULL) free(ptr->pat);
      return -1;
    }
    memcpy(ptr->code,tsg->code,sizeof(int)*ptr->nbaud);
  }
  if (i==tsgtab->num) tsgtab->num++; 
  return i; 
}
