#ifndef INCLUDE_SCREEN
#define INCLUDE_SCREEN

class Screen{
  private:
    short sizex=*((short*)0x0ff4);
    short sizey=*((short*)0x0ff6);
    char*vram=*((char**)0x0ff8);
    char initial_color=0xf;
    //unsigned char fonts[4096];
  public:
    Screen();
    void write(int val,int x,int y);
    void font_write(char c,int x,int y,int color);
};

#endif
