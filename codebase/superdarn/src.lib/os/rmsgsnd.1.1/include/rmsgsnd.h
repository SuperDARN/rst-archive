/* rmsgsnd.h
   =========
   Author: R.J.Barnes
*/


/*
 (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
 
 
 
*/


#ifndef _RMSGSND_H
#define _RMSGSND_H

int RMsgSndOpen(int sock,size_t buflen,unsigned char *bufadr);

int RMsgSndClose(int sock);

int RMsgSndQuit(int sock);

int RMsgSndReset(int sock);

int RMsgSndSend(int sock,struct RMsgBlock *ptr);

int RMsgSndAdd(struct RMsgBlock *ptr, 
	       size_t buflen,unsigned char *buf,int type,int tag);

#endif
