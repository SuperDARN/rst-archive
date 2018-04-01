; readriq.pro
; ===========
; Author: R.J.Barnes
; 
; Copyright 2004 The Johns Hopkins University/Applied Physics Laboratory.
; All rights reserved.
; 
; This material may be used, modified, or reproduced by or for the U.S.
; Government pursuant to the license rights granted under the clauses at DFARS
; 252.227-7013/7014.
; 
; For any other permissions, please contact the Space Department
; Program Office at JHU/APL.
; 
; This Distribution and Disclaimer Statement must be included in all copies of
; "Radar Software Toolkit - SuperDARN Toolkit" (hereinafter "the Program").
; 
; The Program was developed at The Johns Hopkins University/Applied Physics
; Laboratory (JHU/APL) which is the author thereof under the "work made for
; hire" provisions of the copyright law.  
; 
; JHU/APL assumes no obligation to provide support of any kind with regard to
; the Program.  This includes no obligation to provide assistance in using the
; Program or to provide updated versions of the Program.
; 
; THE PROGRAM AND ITS DOCUMENTATION ARE PROVIDED AS IS AND WITHOUT ANY EXPRESS
; OR IMPLIED WARRANTIES WHATSOEVER.  ALL WARRANTIES INCLUDING, BUT NOT LIMITED
; TO, PERFORMANCE, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE
; HEREBY DISCLAIMED.  YOU ASSUME THE ENTIRE RISK AND LIABILITY OF USING THE
; PROGRAM TO INCLUDE USE IN COMPLIANCE WITH ANY THIRD PARTY RIGHTS.  YOU ARE
; ADVISED TO TEST THE PROGRAM THOROUGHLY BEFORE RELYING ON IT.  IN NO EVENT
; SHALL JHU/APL BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING, WITHOUT
; LIMITATION, ANY LOST PROFITS, LOST SAVINGS OR OTHER INCIDENTAL OR
; CONSEQUENTIAL DAMAGES, ARISING OUT OF THE USE OR INABILITY TO USE THE
; PROGRAM."
; 
; 
; 
; 
; 
; 
;
; A Simply demonstration program for reading iqdat files


pro readiq

; Open the raw index file and load it into the inx structure 

;  openr,inp,'test.rawinx',/GET_LUN,/STDIO,/SWAP_IF_BIG_ENDIAN
;  s=RawLoadInx(inp,inx)
;  free_lun,inp
 
; Open the raw file for read only 
 
  inp=IQOpen('test.iqdat',/read)

;  out=IQOpen('test2.iqdat',/write) 

;  Search for a specific time in the file

;  s=IQSeek(inp,2002,12,19,0,30,10,inx,atme=atme)
 
  while IQRead(inp,prm,iq,samples) ne -1 do begin
     
 ;    s=IQWrite(out,prm,iq,samples)
     print, prm.time.hr,prm.time.mt,prm.time.sc
     s=IQExtractIQ(iq,0,0,samples,iqc)
    
     plot,real_part(iqc),linestyle=1
     oplot,imaginary(iqc),linestyle=5
  endwhile
  free_lun,inp

end


