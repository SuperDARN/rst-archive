/* gridwrite.h
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



#ifndef _GRIDWRITE_H
#define _GRIDWRITE_H

int GridWrite(int fd,struct GridData *ptr);
int GridFwrite(FILE *fp,struct GridData *ptr);

#endif



