#ifndef INCLUDE_ASMFUNC
#define INCLUDE_ASMFUNC

extern "C"{
  void io_hlt();
  void io_cli();
  void io_sti();
  void io_stihlt();
  void io_out8(int port,int data);
  unsigned char io_in8(int port);
  void load_idtr(int limit,int addr);
  void load_gdtr(int limit,int addr);
  void asm_inthandler21();
}
//int load_eflags();
//void io_store_eflags(int eflags);

#endif
