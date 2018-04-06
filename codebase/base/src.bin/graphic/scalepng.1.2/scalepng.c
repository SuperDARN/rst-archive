/* scalepng.c
   =========== */

/*
 LICENSE AND DISCLAIMER
 
 Copyright (c) 2012 The Johns Hopkins University/Applied Physics Laboratory
 
 This file is part of the Radar Software Toolkit (RST).
 
 RST is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 RST is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with RST.  If not, see <http://www.gnu.org/licenses/>.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include "option.h"
#include "rxml.h"
#include "rfbuffer.h"

#include "hlpstr.h"





struct OptionData opt;

int main(int argc,char *argv[]) {
  
  
  int arg=0;
  FILE *fp;
  
  struct FrameBuffer *src=NULL;
  struct FrameBuffer *dst=NULL;
  struct FrameBufferMatrix m;
 
  unsigned char sflg=0;
  float wdt=-1;
  float hgt=-1;
  float sf=1.0;


  unsigned char help=0;
  unsigned char option=0;


 
  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  OptionAdd(&opt,"smooth",'x',&sflg);
  OptionAdd(&opt,"wdt",'f',&wdt);
  OptionAdd(&opt,"hgt",'f',&hgt);
   OptionAdd(&opt,"sf",'f',&sf);
  
  arg=OptionProcess(1,argc,argv,&opt,NULL);   

  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }

  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }


  if (arg<argc) {
    fp=fopen(argv[arg],"r");
    if (fp==NULL) {
      fprintf(stderr,"Error opening file.\n");
      exit(-1);
    }
  } else fp=stdin;

  while ((src=FrameBufferLoadPNG(fp,"image")) !=NULL) {

    if (dst==NULL) {
      if ((wdt==-1) && (hgt==-1)) {
         wdt=src->wdt*sf;
         hgt=src->hgt*sf;
      } else if (wdt==-1) {
         wdt=src->wdt*hgt/src->hgt;
      } else if (hgt==-1) {
         hgt=src->hgt*wdt/src->wdt;
      }
      if ((wdt==0) || (hgt==0)) {
        fprintf(stderr,"Invalid image size.\n");
        exit(-1);
      }
      dst=FrameBufferMake(NULL,wdt,hgt,src->depth);
    }

    if ((wdt==src->wdt) && (hgt==src->hgt))
      FrameBufferImage(dst,NULL,src,0xf0,0,0,0,NULL);  
    else {
      float xsc=wdt/src->wdt;
      float ysc=hgt/src->hgt;
      m.a=xsc;
      m.b=0;
      m.c=0;
      m.d=ysc;
      FrameBufferImage(dst,&m,src,0xf0,0,0,sflg,NULL); 
    }
 
    FrameBufferSavePNG(dst,stdout); 

    FrameBufferFree(src);
    src=NULL;
  }

  if (arg<argc) fclose(fp);



  return 0;
}




