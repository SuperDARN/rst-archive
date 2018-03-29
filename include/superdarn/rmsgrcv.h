/* rmsgrcv.h
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/


#ifndef _RMSGRCV_H
#define _RMSGRCV_H

char RMsgRcvDecodeData(int sock,struct RMsgBlock *blk,
		      unsigned char **store);
char RMsgRcvDecodeOpen(int sock,size_t *size,unsigned char **store);

#endif 
