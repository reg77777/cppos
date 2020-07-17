#ifndef INCLUDE_IDT
#define INCLUDE_IDT

#include "asmfunc.h"
#include "fifo.h"
#include <stdint.h>

#define PIC0_ICW1			0x0020
#define PIC0_OCW2			0x0020
#define PIC0_IMR			0x0021
#define PIC0_ICW2			0x0021
#define PIC0_ICW3			0x0021
#define PIC0_ICW4			0x0021
#define PIC1_ICW1			0x00a0
#define PIC1_OCW2			0x00a0
#define PIC1_IMR			0x00a1
#define PIC1_ICW2			0x00a1
#define PIC1_ICW3			0x00a1
#define PIC1_ICW4			0x00a1

#define ADR_IDT         0x0026f800
#define LIMIT_IDT       0x000007ff
#define AR_INTGATE32    0x008e

#define PORT_KEYDAT     0x0060
#define PORT_KEYSTA     0x0064
#define PORT_KEYCMD     0x0064
#define KEYSTA_SEND_NOTREADY  0x02
#define KEYCMD_WRITE_MODE     0x60
#define KBC_MODE              0x47
#define KEYCMD_SENDTO_MOUSE   0xd4
#define MOUSECMD_ENABLE     0xf4

struct IDT{
  short offset_low,selector;
  char dw_count,access_right;
  short offset_high;
};

class IDTs{
  public:
    IDTs();
    void load();
    void pic_init();
    void set_idt(IDT*idts,int offset,int selector,int ar);
    void set_key(FIFO*key);
};

extern "C" void inthandler21(int*esp);

#endif
