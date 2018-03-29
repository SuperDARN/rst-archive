; fitrange.pro
; ============
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
; FitACFMakeFitRange


; ---------------------------------------------------------------


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+
; NAME:
;       FitACFMakeFitRange
;
; PURPOSE:
;       Create a structure to hold range data for the FitACF algorithm.
;       
;
; CALLING SEQUENCE:
;        FitACFMakeFitRange,rng
;
;
;-----------------------------------------------------------------
;



pro FitACFMakeFitRange,rng

  rng={FitRange, $
       v:0.0D, $
       v_err:0.0D, $
       p_0:0.0D, $
       p_l:0.0D, $
       p_l_err:0.0D, $ 
       p_s:0.0D, $
       p_s_err:0.0D,$
       w_l:0.0D, $
       w_l_err:0.0D,$
       w_s:0.0D, $
       w_s_err:0.0D,$ 
       phi0:0.0D, $
       phi0_err:0.0D, $
       sdev_l:0.0D, $
       sdev_s:0.0D, $
       sdev_phi:0.0D, $
       qflg:0, $
       gsct:0, $
       nump:0 $
  }
end
 
