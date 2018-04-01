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
"apply_bumpfb - Apply a bump-map to a bitmap image.\n",
"apply_bumpfp --help\n",
"apply_bumpfp [options] imgname bumpname\n",
"apply_bumpfp -ppm [options] imgname bumpname\n",
"apply_bumpfp -ppmx [options] imgname bumpname\n",
"apply_bumpfp -xml [options] imgname bumpname\n",

"--help\tprint the help message and exit.\n",
"-ppm\tproduce a Portable PixMap (PPM) image as the output.\n",
"-ppmx\tproduce an extended Portable PixMap (PPMX) image as the output.\n",
"-xml\tproduce an XML image representation as the output.\n",
"-ippm\tinput image file is a Portable PixMap (PPM).\n",
"-ippmx\tinput image file is an extended Portable PixMap (PPMX).\n",
"-ixml \tinput image file is an XML image representation.\n",
"-mask \tgenerate an alpha channel mask rather than applying the bump-map.\n",
"-level level\tthreshold the bump-map height at level.\n",
"imgname\tfilename of the bitmap image.\n",
"bumpname\tfilename of the bumpmap.\n",

NULL};