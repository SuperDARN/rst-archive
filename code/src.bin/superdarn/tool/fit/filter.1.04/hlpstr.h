/* hlpstr.h
   ========
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


char *hlpstr[]={
"filter - Median filters data to produce a cfit format file from either a fit, fitacf or cfit format file.\n",
"filter --help\n",
"filter [options] fitname [inxname]\n",
"filter -new [options] fitacfname [inxname]\n",
"filter -cfit [options] cfitname\n",
"filter -new -cfit [options] cfitname\n",
"filter -c [options] fitnames...\n",
"filter -c -new [options] fitacfnames...\n",
"filter -c -cfit [options] cfitnames...\n",
"filter -c -new -cfit [options] cfitnames...\n",

"--help\tprint the help message and exit.\n",
"-vb\tverbose. Log information to the console.\n",
"-sd yyyymmdd\tstart from the date yyyymmdd.\n",
"-st hr:mn\tstart from the time hr:mn.\n",
"-ed yyyymmdd\tstop at the date yyyymmdd.\n",
"-et hr:mn\tstop at the time hr:mn.\n",
"-ex hr:mn\tuse the interval whose extent is hr:mn.\n",
"-tl tlen\tignore the scan flag and instead use a fixed length scan of  tlen seconds.\n",
"-cn channel\tprocess data from channel channel for stereo mode data.\n",
"-ebm ebeams\texclude the beams listed in ebeams, which is a comma separated list of beam numbers.\n",
"-minrng minrange\texclude data from range gates lower than minrange.\n",
"-maxrng maxrange\texclude data from range gates higher than maxrange.\n",
"-fwgt mode\tset the filter weighting mode to mode.\n",
"-pmax pmax\texclude data with a power greater than pmax.\n",
"-vmax vmax\texclude data with an absolute velocity greater than vmax.\n",
"-wmax wmax\texclude data with a spectral width greater than wmax.\n",
"-vemax vemax\texclude data with a velocity error greater than vemax.\n",
"-pmin pmin\texclude data with a power less than pmin.\n",
"-vmin vmin\texclude data with an absolute velocity less than vmin.\n",
"-wmin wmin\texclude data with a spectral width less than wmin.\n",
"-vemin vemin\texclude data with a velocity error less than vemin.\n",
"-fmax fmax\tset the maximum allowed variation in frequency to be fmax Hertz.\n",
"-nav\tdo not perform temporal averaging.\n",
"-nlm\tdo not exclude data because it exceeds the data limits.\n",
"-nb\tdo not exclude data based on the operating parameters.\n",
"-ion\texclude data marked as ground scatter.\n",
"-gs\texclude data marked as ionospheric scatter.\n",
"-both\tdo not exclude data based on the type flag.\n",
"fitname\tfilename of the fit format file.\n",
"inxname\tfilename of the index file.\n",
"-new\tthe input file is in the fitacf format.\n",
"fitacfname\tfilename of the fitacf format file.\n",
"-cfit\tthe input file is in the cfit format.\n",
"cfitfname\tfilename of the cfit format file.\n",
"-c\tconcatenate multiple input files.\n",
"fitnames\tfilenames of the fit format files.\n",
"fitacfnames\tfilenames of the fitacf format files.\n",
"cfitnames\tfilenames of the cfit format files.\n",

NULL};
