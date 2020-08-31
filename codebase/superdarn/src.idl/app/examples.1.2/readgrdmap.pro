; readgrdmap.pro
; ==============
; Author: R.J.Barnes
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
; A Simply demonstration program for reading grdmap files


pro readgrdmap

; Open the raw index file and load it into the inx structure 

  openr,inp,'data/grdmap/test.grdinx',/GET_LUN,/STDIO,/SWAP_IF_BIG_ENDIAN
  s=GridLoadInx(inp,inx)
  free_lun,inp
 
; Open the grdmap file for read only 
 
  inp=GridOpen('data/grdmap/test.grdmap',/read)
 

;  Search for a specific time in the file

;  s=GridSeek(inp,2002,12,19,0,30,10,inx,atme=atme)
 
  while GridRead(inp,prm,stvec,gvec) ne -1 do begin
     print, prm.stme.hr,prm.stme.mt,prm.stme.sc
     stop
  endwhile
  free_lun,inp

end


