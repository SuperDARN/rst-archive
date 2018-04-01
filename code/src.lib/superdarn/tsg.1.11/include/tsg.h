/* tsg.h
   =====
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

/*
 $Log: tsg.h,v $
 Revision 1.4  2007/05/24 13:39:49  code
 Fixed definition of gort.

 Revision 1.3  2007/05/24 13:36:57  code
 Added a variable to determine whether we should use the scope sync as a gate
 or a trigger. When using the GC214 card we use a gate to keep sampling during the pulse
 sequence.
 With the GC214TS card we use a trigger and flip the scope sync off after the first
 TX pulse.

 Revision 1.2  2006/11/08 16:50:19  code
 Added start delay.

 Revision 1.1  2004/07/12 22:39:30  barnes
 Initial revision

*/

#ifndef _TSG_H
#define _TSG_H

#define CLOCK_PERIOD	10		/* clock period in microseconds */

struct TSGbuf {
  unsigned char *code;
  unsigned char *rep;
  int len;
};

struct TSGprm {
  int nrang,          /* number of ranges */
      frang,          /* distance to first range */
      rsep,           /* range gate separation */
      smsep,          /* sample separation */
      lagfr,
      txpl,           /* length of pulse */
      mppul,          /* number of pulses in the sequence */
      mpinc,	      /* multi-pulse increment */
      mlag,           /* maximum lag in the sequence */
      nbaud,	      /* number of baud in the phase code */
      samples,	      /* number of samples generated by the sequence */
      smdelay,        /* sample delay */
      stdelay,        /* delay at front of sequence */
      gort;           /* gate or trigger with scope sync*/
  int rtoxmin;        /* delay between receiver off and pulse */
      int *pat,	      /* pointer to the pulse pattern */
	  *code;      /* pointer to the phase code table */
};

struct TSGtable {
  int num;
  int max;
  int *active;
  struct TSGprm *buf;
};

#define TSG_OK 0
#define TSG_INV_RSEP 1
#define TSG_NO_SMSEP 2
#define TSG_INV_MPPUL_SMSEP 3
#define TSG_INV_PAT 4
#define TSG_INV_MPINC_SMSEP 5
#define TSG_INV_LAGFR_SMSEP 6
#define TSG_INV_DUTY_CYCLE 7
#define TSG_INV_ODD_SMSEP 8
#define TSG_INV_TXPL_BAUD 9
#define TSG_INV_MEMORY 10
#define TSG_INV_PHASE_DELAY 11

#endif