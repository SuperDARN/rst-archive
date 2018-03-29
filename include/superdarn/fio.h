/* fio.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/

#ifndef _FIO_H
#define _FIO_H

char *FIOMakeFile(char *pathenv,int yr,int mo,int dy,int hr,int mt,int sc,
		  char *code,char *extra,char *ext,int mode,int flag);

#endif 
