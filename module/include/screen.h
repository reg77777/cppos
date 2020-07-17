#ifndef INCLUDE_SCREEN
#define INCLUDE_SCREEN

class Screen{
  private:
    short sizex=*((short*)0x0ff4);
    short sizey=*((short*)0x0ff6);
    char*vram=*((char**)0x0ff8);
    char initial_color=4;
    int font_sizex=8;
    int font_sizey=16;
    int cli_cursor=0;
    const char keycord[128]={
       0 , 0 ,'1','2','3','4','5','6','7','8','9','0','-','^', 0 , 0 ,
      'Q','W','E','R','T','Y','U','I','O','P','@','[', 0 , 0 ,'A','S',
      'D','F','G','H','J','K','L',';',':', 0 , 0 ,'[','Z','X','C','V',
      'B','N','M',',','.','/', 0 ,'*', 0 ,' ', 0 , 0 , 0 , 0 , 0 , 0 ,
       0 , 0 , 0 , 0 , 0 , 0 , 0 ,'7','8','9','-','4','5','6','+','1',
       '2','3','0','.'
    };
  public:
    Screen();
    void write(int x,int y,int color);
    void fill(int x1,int y1,int x2,int y2,int color);
    void font_fill(int x,int y);
    void font_write(char c,int x,int y,int color);
    void print(char*c,int x,int y,int color);
    void print_num(unsigned int n,int x,int y,int color);
    void cursor_write(int x,int y);
    void cli_input(unsigned char c);
    void cli_backspace();
};

#endif
