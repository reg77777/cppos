#include "includes/screen.h"
#include "includes/asmfunc.h"

int main(){
  Screen screen;
  screen.font_write('A',0,0,0);
  while(true)hlt();
}
