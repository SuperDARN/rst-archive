/* pipe.h
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/




int pipewrite(int fildes,unsigned char *buffer,unsigned int size);
int piperead(int fildes,unsigned char **buffer);
