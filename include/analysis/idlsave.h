/* idlsave.h
   =========
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




#ifndef _IDLSAVE_H
#define _IDLSAVE_H

struct IDLFile {
  unsigned char zflg;
  union {
    FILE *p;
    gzFile z;
  } fp;
};

struct IDLFile *IDLOpen(char *fname,char zflg);
struct IDLFile *IDLFdopen(int fd,char zflg);
void IDLClose(struct IDLFile *fp);

struct DataMap *IDLReadSave(struct IDLFile *fp);

#endif

