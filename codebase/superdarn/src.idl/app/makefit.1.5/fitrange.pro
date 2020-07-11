; fitrange.pro
; ============
; Author: R.J.Barnes - Based on C code by K.Baker
; 
; LICENSE AND DISCLAIMER
; 
; Copyright (c) 2012 The Johns Hopkins University/Applied Physics Laboratory
; 
; This file is part of the Radar Software Toolkit (RST).
; 
; RST is free software: you can redistribute it and/or modify
; it under the terms of the GNU Lesser General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; any later version.
; 
; RST is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU Lesser General Public License for more details.
; 
; You should have received a copy of the GNU Lesser General Public License
; along with RST.  If not, see <http://www.gnu.org/licenses/>.
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
 
