#include "module/include/screen.h"
#include "module/include/asmfunc.h"
#include "module/include/gdt.h"
#include "module/include/idt.h"
#include "module/include/fifo.h"
#include <stdint.h>

FIFO key;

extern "C" int main(){
  GDTs gdts;
  IDTs idts;

  io_sti();
  Screen screen;

  for(;;){
    io_cli();
    if(key.have_buf())screen.cli_input(key.pop());
    else io_stihlt();
  }

  return 0;
}
