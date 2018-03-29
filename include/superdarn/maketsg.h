/* maketsg.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#ifndef _MAKETSG_H
#define _MAKETSG_H

void TSGFree(struct TSGbuf *ptr);
struct TSGbuf *TSGMake(struct TSGprm *tsg,int *flg);


#endif
