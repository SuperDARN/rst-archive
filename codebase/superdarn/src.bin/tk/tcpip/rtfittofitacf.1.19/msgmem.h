/* msgmem.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/



int writeraw(char *buf,int sze); 
void readsock(fd_set *fdset,char *tmp_buf,int tmp_sze);
int writesock();



