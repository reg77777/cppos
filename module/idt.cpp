#include "include/idt.h"

void inthandler21(int*esp){
  io_out8(PIC0_OCW2,0x61);
  extern FIFO key;
  key.push((unsigned char)io_in8(PORT_KEYDAT));
}

void IDTs::set_idt(IDT*idts,int offset,int selector,int ar){
  idts->offset_low=offset&0xffff;
  idts->selector=selector;
  idts->dw_count=(ar>>8)&0xff;
  idts->access_right=ar&0xff;
  idts->offset_high=(offset>>16)&0xffff;
}

IDTs::IDTs(){
  IDT*idts=(IDT*)ADR_IDT;
  for(int i=0;i<LIMIT_IDT/8;i++)set_idt(idts+i,0,0,0);
  load_idtr(LIMIT_IDT,ADR_IDT);
  set_idt(idts+0x21,(int)asm_inthandler21,2*8,AR_INTGATE32);
  pic_init();
  //keyboard
  while(1){if(!(io_in8(PORT_KEYSTA)&KEYSTA_SEND_NOTREADY))break;}
  io_out8(PORT_KEYCMD,KEYCMD_WRITE_MODE);
  while(1){if(!(io_in8(PORT_KEYSTA)&KEYSTA_SEND_NOTREADY))break;}
  io_out8(PORT_KEYDAT,KBC_MODE);
}


void IDTs::pic_init(){
  io_out8(PIC0_IMR,0xff);
  io_out8(PIC1_IMR,0xff);

  io_out8(PIC0_ICW1,0x11);
  io_out8(PIC0_ICW2,0x20);
  io_out8(PIC0_ICW3,1<<2);
  io_out8(PIC0_ICW4,0x01);

  io_out8(PIC1_ICW1,0x11);
  io_out8(PIC1_ICW2,0x28);
  io_out8(PIC1_ICW3,2);
  io_out8(PIC1_ICW4,0x01);

  io_out8(PIC0_IMR,0xf9);
  io_out8(PIC1_IMR,0xef);
}
