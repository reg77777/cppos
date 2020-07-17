//#include "asmfunc.h"
#include "include/idt.h"

void io_hlt(){
  asm("hlt");
}

void io_cli(){
  asm("cli");
}

void io_sti(){
  asm("sti");
}

void io_stihlt(){
  asm("sti;"
      "hlt;");
}

void io_out8(int port,int data){
  asm("mov edx,[%0];"
      "mov al,[%1];"
      "out dx,al;"
      :
      :"r"(port),"r"(data)
      :
      );
}

int io_in8(int port){
  unsigned char res;
  asm("mov edx,[%1];"
      "mov eax,0;"
      "in %0,dx;"
      :"=r"(res)
      :"r"(port)
      :
      );
  return res;
}

void load_gdtr(int limit,int addr){
  asm("mov ax,[%0];"
      "mov [%1],ax;"
      "lgdt [%1];"
      :
      :"r"(limit),"r"(addr)
      :
      );
}

void load_idtr(int limit,int addr){
  asm("mov ax,[%0];"
      "mov [%1],ax;"
      "lidt [%1];"
      :
      :"r"(limit),"r"(addr)
      :
      );
}

void asm_inthandler21(){
  asm("push es;"
      "push ds;"
      "pushad;"
      "mov eax,esp;"
      "push eax;"
      "mov ax,ss;"
      "mov ds,ax;"
      "mov es,ax;"
      "call inthandler21;"
      "pop eax;"
      "popad;"
      "pop ds;"
      "pop es;"
      "iretd;"
      );
}

int load_eflags(){
}

void io_store_eflags(int eflags){
}

void write_mem8(int addr,int data){
}

int load_cr0(){
}

void store_cr0(int cr0){
}
