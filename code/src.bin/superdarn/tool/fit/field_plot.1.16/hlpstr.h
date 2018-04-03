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
"field_plot - Plot fit, fitacf, cfit and csd format files.\n",
"field_plot --help\n",
"field_plot [options] fitname [inxname]\n",
"field_plot -new [options] [fitacfname] [inxname]\n",
"field_plot -cfit [options] [cfitname]\n",
"field_plot -csd [options] [csdname]\n",
"field_plot -ps [-xp xoff] [-yp yoff] [options] fitname [inxname]\n",
"field_plot -new -ps [-xp xoff] [-yp yoff] [options] [fitacfname] [inxname]\n",
"field_plot -cfit -ps [-xp xoff] [-yp yoff] [options] [cfitname]\n",
"field_plot -csd -ps [-xp xoff] [-yp yoff] [options] [csdname] [csdname]\n",
"field_plot -ppm [options] fitname [inxname]\n",
"field_plot -new -ppm [options] [fitacfname] [inxname]\n",
"field_plot -cfit -ppm [options] [cfitname]\n",
"field_plot -csd -ppm [options] [csdname] \n",
"field_plot -ppmx [options] fitname [inxname]\n",
"field_plot -new -ppmx [options] [fitacfname] [inxname]\n",
"field_plot -cfit -ppmx [options] [cfitname]\n",
"field_plot -csd -ppmx [options] [csdname]\n",
"field_plot -xml [options] fitname [inxname]\n",
"field_plot -new -xml [options] [fitacfname] [inxname]\n",
"field_plot -cfit -xml [options] [cfitname]\n",
"field_plot -csd -xml [options] [csdname]\n",
"field_plot -x [-display display] [-xoff xoff] [-yoff yoff] [-delay delay] [options] fitname [inxname]\n",
"field_plot -new -x [-display display] [-xoff xoff] [-yoff yoff] [-delay delay] [options] [fitacfname] [inxname]\n",
"field_plot -cfit -x [-display display] [-xoff xoff] [-yoff yoff] [-delay delay] [options] [cfitname]\n",
"field_plot -csd -x [-display display] [-xoff xoff] [-yoff yoff] [-delay delay] [options] [csdname]\n",

"--help\tprint the help message and exit.\n",
"-cf cfname\tread command line options from the file cfname.\n",
"-def\tplot using some sensible default options so that the user will see something plotted.\n",
"-r repeat\tset the number of rows and columns of panels in the plot to repeat. The default value of 2 produces a 2x2 panel plot. If this value is set to zero then the program will produce sequential plots and write them to a file.\n",
"-sd yyyymmdd\tplot starting from the date yyyymmdd.\n",
"-st hr:mn\tplot starting from the time hr:mn.\n",
"-ed yyyymmdd\tstop plotting at the date yyyymmdd.\n",
"-et hr:mn\tstop plotting at the time hr:mn.\n",
"-ex hr:mn\tplot an interval whose extent is hr:mn.\n",
"-tn\tgenerate filenames of the form <em>hrmn.sc.xxx</em> when producing sequential plots.\n",
"-dn\tgenerate filenames of the form <em>yyyymmdd.hrmn.sc.xxx</em> when producing sequential plots.\n",
"-wdt width\tset the width of the plot to width.\n",
"-hgt height\tset the height of the plot to height.\n",
"-padpad\tset the padding around the edge of the plot to  pad.\n",
"-sf scale\tset the scale factor (magnification) to scale. The default scale factor is 1.\n",
"-ortho\tuse an orthographic projection.\n",
"-lat lat\tcenter the plot on the latitude given by lat.\n",
"-lon lon\tcenter the plot on the longitude given by lon.\n",
"-latmin latmin\tadjust the scale factor so that the lowest visible latitude is  latmin. Applies when the stereographic projection is used.\n",
"-mag\tuse magnetic coordinates.\n",
"-rotate\trotate the plot so that the local noon is at the top of the plot.\n",
"-flip\tflip the direction of the X-axis.\n",
"-square\tforce the use of a square bounding box around the plot.\n",
"-coast\tplot coastlines.\n",
"-fcoast\tplot filled coastlines.\n",
"-bnd\tplot state boundaries.\n",
"-grd\tplot a grid.\n",
"-grdlat grdlat\tset the latitude spacing of the grid to grdlat degrees.\n",
"-grdlon grdlon\tset the longitude spacing of the grid to grdlon degrees.\n",
"-igrd\tplot the inverse grid, if the plot is in geographic coordinates, a geomagnetic grid is plotted, if the plot is in geomagnetic coordinates, a geographic grid is plotted.\n",
"-igrdlat igrdlat\tset the latitude spacing of the inverse grid to grdlat degrees.\n",
"-igrdlon igrdlon\tset the longitude spacing of the inverse grid to grdlon degrees.\n",
"-igrdontop\tplot the inverse grid on top.\n",
"-grdontop\tplot the grid on top.\n",
"-tmk\tplot a clock-dial grid showing the time.\n",
"-fov\tplot the radar fields of view of other SuperDARN radars.\n",
"-ffov\tplot the filled radar fields of view of other SuperDARN radars.\n",
"-fan\tplot the radar field of view.\n",
"-ffov\tplot the filled radar field of view.\n",
"-tmtick tick\tset the grid interval for the time clock-dial to tick hours.\n",
"-lst\tuse local solar time rather than local time.\n",
"-term\tplot the terminator.\n",
"-fterm\tplot a filled terminator.\n",
"-tmlbl\tLabel the time clock-dial.\n",
"-lnewdt lnewdt\tset the line width to lnewdt.\n",
"-bgcol rrggbb\tset the background color to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-txtcol rrggbb\tset the color of the text to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-grdcol rrggbb\tset the color of the grid to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-igrdcol rrggbb\tset the color of the inverse grid to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-cstcol rrggbb\tset the color of the coastline to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-bndcol rrggbb\tset the color of the state boundaries to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-lndcol rrggbb\tset the color of the land to rrggbb, specified as the  hexadecimal value for the 24-bit red,green and blue component color.\n",
"-seacol rrggbb\tset the color of the sea to rrggbb, specified as the  hexadecimal value for the 24-bit red,green and blue component color.\n",
"-tmkcol rrggbb\tset the color of the time clock-dial to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-fovcol rrggbb\tset the color of the fields of view outline of other SuperDARN radars to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-ffovcol rrggbb\tset the color of the filled fields of view of other SuperDARN radars to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-fovcol rrggbb\tset the color of the field of view of the radar being plotted (the radar fan) outline to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-ffovcol rrggbb\tset the color of the filled field of view of the radar being ploted (the radar fan) to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-trmcol rrggbb\tset the color of the terminator outline to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-ftrmcol rrggbb\tset the color of the filled terminator outline to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-gscol rrggbb\tset the color of ground scatter to rrggbb, specified as the hexadecimal value for the 24-bit red,green and blue component color.\n",
"-vkey vkeyname\tload the colorkey used to plot velocity vectors from the file vkeyname.\n",
"-key keyname\tload the colorkey from the file xkeyname.\n",
"-p\tplot power.\n",
"-v\tplot velocity.\n",
"-w\tplot spectral width.\n",
"-vec\tplot velocity vectors.\n",
"-pmin pmin\tset the minimum value of the power scale to pmin.\n",
"-pmax pmax\tset the maximum value of the power scale to pmax.\n",
"-vmin vmin\tset the minimum value of the velocity scale to vmin.\n",
"-vmax vmax\tset the maximum value of the velocity scale to vmax.\n",
"-wmin wmin\tset the minimum value of the spectral width scale to wmin.\n",
"-wmax wmax\tset the maximum value of the spectral width scale to wmax.\n",
"-gs\tcolor ground scatter.\n",
"-gm\tmask out ground scatter.\n",
"-keyp\tplot the color key.\n",
"-vkeyp\tplot the color key for velocity vectors.\n",
"-vecp\tplot the example vector.\n",
"-vsf vsf\tset the vector scale factor to vsf.\n",
"-vecr radius\tset the radius of the circle at the end of the vector to radius.\n",
"-logo\tplot the logo and credits.\n",
"-time\tplot the time of the plotted data.\n",
"-frame\tadd a frame around the borders of the plot.\n",
"-over\tthe output plot will be overlaid on another plot, do not paint the background with the bacground color.\n",
"-tl tlen\tignore the scan flag and instead use a fixed length scan of  tlen seconds.\n",
"-cn channel\tfor stereo mode data, plot channel channel, if omitted then both channels are plotted.\n",
"-cp cpid\tplot beams that contain the program identifier cpid only.\n",
"-scan scan\tplot beams that have a value for the scan flag of scan.\n",
"-ns\tignore non-scan data (data with a scan flag of -1)..\n",
"-s step\tset the number of scans  skipped between plots to step.\n",
"fitname\tfilename of the fit format file to plot.\n",
"inxname\tfilename of the index file.\n",
"-new\tfile is in the fitacf format.\n",
"fitacfname\tfilename of the fitacf format file to plot.\n",
"-cfit\tfile is in the cfit format.\n",
"cfitname\tfilename of the cfit format file to plot.\n",
"-csd\tfile is in the csd format.\n",
"csd\tfilename of the csd format file to plot.\n",
"-ps\tproduce a PostScript plot as the output.\n",
"-xp xoff\tset the X offset of the PostScript plot to xoff.\n",
"-yp xoff\tset the Y offset of the PostScript plot to yoff.\n",
"-ppm\tproduce a Portable PixMap (PPM) image as the output.\n",
"-ppmx\tproduce an extended Portable PixMap (PPMX) image as the output.\n",
"-xml\tproduce an XML image representation as the output.\n",
"-x\tplot the data on an X-terminal.\n",
"-display display\tconnect to the xterminal named display.\n",
"-xoff xoff\topen the window, xoff pixels from the left edge of the screen.\n",
"-yoff yoff\topen the window ypad pixels from the top edge of the screen.\n",
"-delay delay\tset the delay between frames to delay milliseconds, a value of 0 will pause the frame until a mouse button is pressed.\n",

NULL};
