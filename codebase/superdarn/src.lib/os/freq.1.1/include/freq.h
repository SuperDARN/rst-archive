/* freq.h
   ======
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/

#ifndef _FREQ_H
#define _FREQ_H


#define DEFAULT_FREQ 13000

struct FreqTable {
  int num;
  int dfrq;
  int *start;
  int *end;
};

struct FreqTable *FreqLoadTable(FILE *fp);
int FreqTest(struct FreqTable *ptr,int freq);
   	
#endif
