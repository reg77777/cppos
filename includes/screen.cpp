#include "screen.h"
#include "easy_fonts.cpp"

Screen::Screen(){
  for(int i=0;i<sizex;i++){
    for(int j=0;j<sizey;j++){
      write(initial_color,i,j);
    }
  }
}

void Screen::write(int val,int x,int y){
  vram[x+y*sizex]=val;
}

void Screen::font_write(char c,int x,int y,int color){
  for(int i=0;i<16;i++){
    char font=easy_fonts[c*16+i];
    if(font&0x80)write(color,x+0,y+i);
    if(font&0x40)write(color,x+1,y+i);
    if(font&0x20)write(color,x+2,y+i);
    if(font&0x10)write(color,x+3,y+i);
    if(font&0x08)write(color,x+4,y+i);
    if(font&0x04)write(color,x+5,y+i);
    if(font&0x02)write(color,x+6,y+i);
    if(font&0x01)write(color,x+7,y+i);
  }
  /*
  for(int i=0;i<16;i++){
    for(int j=0;j<8;j++){
      if(easy_fonts[c*108+i*8]>>j)write(color,x+j,y+i);
       char*p,d;
    }
  }
  */
}
