#include "include/screen.h"
#include "include/easy_fonts.h"

Screen::Screen(){
  for(int y=0;y<sizey;y++){
    for(int x=0;x<sizex;x++){
      write(x,y,initial_color);
    }
  }
}

void Screen::write(int x,int y,int color){
  vram[x+y*sizex]=color;
}

void Screen::fill(int x1,int y1,int x2,int y2,int color){
  for(int y=y1;y<y2;y++){
    for(int x=x1;x<x2;x++){
      write(x,y,color);
    }
  }
}

void Screen::font_fill(int x,int y){
  fill(x,y,x+font_sizex,y+font_sizey,initial_color);
}

void Screen::font_write(char c,int x,int y,int color){
  font_fill(x,y);
  for(int dy=0;dy<font_sizey;dy++){
    char font=easy_fonts[c*font_sizey+dy];
    int Y=y+dy;
    if(font&0x80)write(x+0,Y,color);
    if(font&0x40)write(x+1,Y,color);
    if(font&0x20)write(x+2,Y,color);
    if(font&0x10)write(x+3,Y,color);
    if(font&0x08)write(x+4,Y,color);
    if(font&0x04)write(x+5,Y,color);
    if(font&0x02)write(x+6,Y,color);
    if(font&0x01)write(x+7,Y,color);
  }
}

void Screen::print(char*c,int x,int y,int color){
  int i=0;
  while(c[i]!='\0'){
    font_write(c[i],x+8*i,y,color);
    i++;
  }
}

void Screen::print_num(unsigned int n,int x,int y,int color){
  int buf[256];
  int size=0;
  while(n!=0){
    buf[size]=n%10;
    n/=10;
    size++;
  }
  if(size==0)buf[0]=0,size=1;
  for(int i=0;i<size;i++){
    font_write(buf[i]+0x30,x+8*(size-1-i),y,color);
  }
}

void Screen::cursor_write(int x,int y){
	static char cursor[16][17]={
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	
	for(int dy=0;dy<16;dy++){
		for(int dx=0;dx<16;dx++){
			if(cursor[dy][dx]=='*')write(x+dx,y+dy,0xf);
			if(cursor[dy][dx]=='O')write(x+dx,y+dy,0);
			if(cursor[dy][dx]=='.')write(x+dx,y+dy,initial_color);
		}
	}
	return;
}

void Screen::cli_input(unsigned char c){
  //backspace
  if(c==14)cli_backspace();
  else if(c<128)font_write(keycord[c],cli_cursor*font_sizex,((cli_cursor*font_sizex)/sizex)*font_sizey,0),cli_cursor++;
}

void Screen::cli_backspace(){
  font_fill((cli_cursor-1)*font_sizex,(((cli_cursor-1)*font_sizex)/sizex)*font_sizey);
  if(cli_cursor!=0)cli_cursor--;
}
