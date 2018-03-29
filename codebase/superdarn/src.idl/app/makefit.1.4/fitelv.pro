; fitelv.pro
; ==========
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
; FitACFMakeFitElv


; ---------------------------------------------------------------




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+
; NAME:
;       FitACFMakElv
;
; PURPOSE:
;      Creates a structure to store the elevation angle data.
;       
;
; CALLING SEQUENCE:
;        
;
;      FitACFMakeFitElv,elv
;
;-----------------------------------------------------------------
;


pro FitACFMakeFitElv,elv

  elv={FitElv, $
       normal:0.0D, $
       low:0.0D, $
       high:0.0D $
      }
end

