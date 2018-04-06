pro badlag_calc_table,seq,mpinc,lagfr,nrang,nblnk,badl


	;set information for katscan
	if(seq eq 0) then begin
		npul = 8
		nlags = 23
		;pulse sequence
		pulse = [0,14,22,24,27,31,42,43]
		;lag table
		lagt1 = [0,42,22,24,27,22,24,14,22,14,31,31,14,0, 27,27,14,24,24,22,22,0, 0]
		lagt2 = [0,43,24,27,31,27,31,22,31,24,42,43,27,14,42,43,31,42,43,42,43,22,24]
		lag_avail = lagt2-lagt1
	endif

	;set information for normalscan
	if(seq eq 1) then begin
		npul =7
		nlags = 17
		;pulse sequence
		pulse = [0,9,12,20,22,26,27]
                ;lag table
		lagt1 = [0,26,20, 9,22,22,20,20,0,12, 9, 0, 9,12,12, 9, 9]
		lagt2 = [0,27,22,12,26,27,26,27,9,22,20,12,22,26,27,26,27]
		lag_avail = lagt2-lagt1
	endif

	;set information for tauscan
	if(seq eq 2) then begin
		npul = 13
		nlags = 17
		;pulse sequence
		pulse = [0,15,16,23,27,29,32,47,50,52,56,63,64]
    ;lag table 1
		lagt1 = [0,15,27,29,23,27,23,16,15,23,16,15,16,15, 0, 0,15]
		lagt2 = [0,16,29,32,27,32,29,23,23,32,27,27,29,29,15,16,32]
		;lag table 2
		lagt3 = [64,63,50,47,52,47,50,56,56,47,52,52,50,50,32,47,47]
		lagt4 = [64,64,52,50,56,52,56,63,64,56,63,64,63,64,47,63,64]
		lag_avail = lagt2-lagt1
	endif


  ;calculate the number of samples
	nsamp = pulse(npul-1)*mpinc+lagfr+nrang
	samples = intarr(nsamp)
	;calculate the bad samples
	for i=0,npul-1 do begin
		for j=0,nblnk-1 do begin
			samples(pulse(i)*mpinc+j) = 1
		endfor
	endfor

	for i=0,nrang-1 do begin
		if(seq ne 2) then begin
			for j=0,nlags-1 do begin
				samp1 = lagt1(j)*mpinc+lagfr+i
				samp2 = lagt2(j)*mpinc+lagfr+i
				if(samples(samp1) eq 1 OR samples(samp2) eq 1) then badl(i,j) = 1
			endfor
		endif else begin
			for j=0,nlags-1 do begin
				samp1 = lagt1(j)*mpinc+lagfr+i
				samp2 = lagt2(j)*mpinc+lagfr+i
				samp3 = lagt3(j)*mpinc+lagfr+i
				samp4 = lagt4(j)*mpinc+lagfr+i
				if((samples(samp1) eq 1 OR samples(samp2) eq 1)AND(samples(samp3) eq 1 OR samples(samp4) eq 1)) then $
					badl(i,j) = 1
			endfor
		endelse
	endfor

	
end


pro badlag_find,filename,hr,mn,beam

  set_plot,'PS',/copy
  device,/landscape,/COLOR,BITS_PER_PIXEL=8,filename='/rst/output_plots/badlag.ps'

	loadct,0
	
	inp=RawOpen(filename,/read)
	print,filename

	print,RawRead(inp,prm,raw)

	cnt = 0
	maxc = 20
	while RawRead(inp,prm,raw) ne -1 do begin
		if((prm.time.hr ge hr AND prm.time.mt ge mn AND prm.bmnum eq beam) OR (cnt gt 0)) then begin
			print,prm.time.mt,prm.bmnum
			if(cnt eq 0) then begin
				badl_mult = intarr(prm.nrang,prm.mplgs)
				lagnums = intarr(prm.mplgs)
			endif
			cnt = cnt+1
			for i=0,prm.nrang-1 do begin
				sigma = sqrt(raw.acfd(i,0,0)^2+raw.acfd(i,0,1)^2)/sqrt(prm.nave)
				for j=0,prm.mplgs-1 do begin
					pwr = sqrt(raw.acfd(i,j,0)^2+raw.acfd(i,j,1)^2)
					if(pwr lt sigma*2.) then badl_mult(i,j) = badl_mult(i,j)+ 1
					lagnums(j) = abs(prm.lag(j,1) - prm.lag(j,0))
				endfor
			endfor
			if(cnt eq maxc) then break
		endif
  endwhile
  free_lun,inp

	badl = intarr(prm.nrang,prm.mplgs)
	for i=0,prm.nrang-1 do $
		for j=0,prm.mplgs-1 do $
			if(badl_mult(i,j) ge maxc*.75) then badl(i,j) =  1

	seq = 0
	if(abs(prm.cp) eq 150 OR abs(prm.cp) eq 151) then seq = 0
	if(abs(prm.cp) eq 3310 OR abs(prm.cp) eq 503) then seq = 2

	badl_calc = intarr(prm.nrang,prm.mplgs)
	badlag_calc_table,seq,prm.mpinc/prm.smsep,prm.lagfr/prm.smsep,prm.nrang,2,badl_calc
	print,(badl(17,*) AND badl_calc(17,*))


  nrow = 25.
	ncol = (prm.nrang/nrow)
	if(fix(ncol) ne (prm.nrang/nrow)) then ncol = fix(ncol)+1
	ncol = ncol*2


  radar_info,prm.stid,glat,glon,mlat,mlon,oneletter,threeletter,name,fix(prm.stid)
  
  if(prm.time.mo lt 10) then mostr = '0'+strtrim(round(prm.time.mo),2) $
  else mostr = strtrim(round(prm.time.mo),2)

  if(prm.time.dy lt 10) then dystr = '0'+strtrim(round(prm.time.dy),2) $
  else dystr = strtrim(round(prm.time.dy),2)

  if(prm.time.hr lt 10) then hrstr = '0'+strtrim(round(prm.time.hr),2) $
  else hrstr = strtrim(round(prm.time.hr),2)

  if(prm.time.mt lt 10) then mtstr = '0'+strtrim(round(prm.time.mt),2) $
  else mtstr = strtrim(round(prm.time.mt),2)

  if(prm.time.sc lt 10) then scstr = '0'+strtrim(round(prm.time.sc),2) $
  else scstr = strtrim(round(prm.time.sc),2)

  title = name+' '+strtrim(fix(prm.time.yr),2)+'/'+mostr+'/'+dystr+','
	title = title+' cpid='+strtrim(prm.cp,2)+' mpinc='+strtrim(prm.mpinc,2)
	title = title+' lagfr='+strtrim(prm.lagfr,2)+' nrang='+strtrim(prm.nrang,2)

  plot,findgen(1),findgen(1),xrange=[0,ncol],yrange=[0,nrow],xstyle=1,ystyle=1,$
			/nodata,/noerase,pos=[.05,.05,.95,.95],title='Low power lags by range gate, '+title,$
			xticks=1,yticks=1,charthick=3.,xthick=3.,ythick=3.,xtickname=replicate(' ',2),$
			ytickname=replicate(' ',2),charsize=.75
; 	xyouts,.95,.02,mis_str,charsize=.6,alignment=1.,charthick=3.,/normal

	for i=0,prm.nrang-1 do begin
		loadct,0
		row = 24 - (i MOD 25)
		col = fix(i/nrow)
		xyouts,col*2+.05,row+.3,strtrim(i,2),/data,charthick=3,charsize=.6
		plots,[col*2,col*2],[0,nrow],thick=3.
		plots,[col*2+.4,col*2+.4],[0,nrow],thick=3. 
		plots,[0,ncol],[row,row],thick=3.

		bad_str1 = ''
		bad_str2 = ''
		cnt = 0
		for j=0,prm.mplgs-1 do begin
			if(badl(i,j)) then cnt = cnt + 1
		endfor
		pcnt = 0
		print,cnt
		bad_str1 = ''
		bad_str2 = ''

		;iterate through the lags
		for j=0,prm.mplgs-1 do begin
			mycol = 0
			;if we have low power badlag
			if(badl(i,j)) then begin
				mycol = 0
				loadct,0
				;if we calculated a bad lag
				if(badl_calc(i,j)) then begin
					mycol = 125
					loadct,34
				endif

				;if we are printing on the 1st line
				if(pcnt lt 11) then begin
					;keep track for length of string
					len = strlen(bad_str1)
					;if we need only 1 line
					if(cnt le 11) then begin
						xyouts,col*2+.45+len*.05,row+.3,strtrim(lagnums(j),2)+' ',/data,charthick=3,charsize=.6,color=mycol
					;if we need 2 lines
					endif else begin
						xyouts,col*2+.45+len*.05,row+.6,strtrim(lagnums(j),2)+' ',/data,charthick=3,charsize=.6,color=mycol
					endelse
					bad_str1 = bad_str1+strtrim(lagnums(j),2)+' '
				;if we are printing on the 2nd line
				endif else begin
					len = strlen(bad_str2)
					xyouts,col*2+.45+len*.05,row+.21,strtrim(lagnums(j),2)+' ',/data,charthick=3,charsize=.6,color=mycol
					bad_str2 = bad_str2+strtrim(lagnums(j),2)+' '
				endelse

				pcnt = pcnt+1

			endif
		endfor

	endfor

	erase

	;close the postscript file
  device,/close

end