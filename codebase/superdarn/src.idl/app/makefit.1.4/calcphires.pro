; calcphires.pro
; ==============
; Author: R.J.Barnes - Based on C code by K.Baker
; 
; (c) 2012 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.3-6-g9146b14.txt for more information.
; 
; 
; 
;
;
; PublicFunctions
; ---------------
;
; FitACFCalcPhiRes


; ---------------------------------------------------------------



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+
; NAME:
;       FitACFCalcPhiRes
;
; PURPOSE:
;       Unknown.
;       
;
; CALLING SEQUENCE:
;        s=FitACFCalcPhiRes(acf,badlag,phires,mplgs)
;
;
;-----------------------------------------------------------------
;




function FitACFCalcPhiRes, acf,badlag,phires,mplgs
 
  LAG_SIZE=48

  if (n_elements(phires) eq 0) then phires=dblarr(LAG_SIZE)

  q=where(badlag[0:mplgs-1] eq 0,c)

  if (c ne 0) then phires[q]=atan(imaginary(acf[q]),double(acf[q]))
  
  q=where(phires ne 0,nzc)
 
  if (nzc gt 0) then return, 0
  return, -1
end
