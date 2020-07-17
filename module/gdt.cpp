#include "include/gdt.h"
#include "include/asmfunc.h"

#define ADR_GDT         0x00270000
#define LIMIT_GDT       0x0000ffff
#define ADR_BOTPAK      0x00280000
#define LIMIT_BOTPAK    0x0007ffff 
#define AR_DATA32_RW    0x4092
#define AR_CODE32_ER    0x409a

void GDTs::set_gdt(GDT*gdts,unsigned int limit,int base,int ar){
  if(limit>0xfffff){
    ar|=0x8000;
    limit/=0x1000;
  }
  gdts->limit_low=limit&0xffff;
  gdts->base_low=base&0xffff;
  gdts->base_mid=(base>>16)&0xff;
  gdts->access_right=ar&0xff;
  gdts->limit_high=(((limit>>16)&0x0f)|((ar>>8)&0xf0));
  gdts->base_high=(base>>24)&0xff;
}


GDTs::GDTs(){
  GDT*gdts=(GDT*)ADR_GDT;
  for(int i=0;i<8192;i++)set_gdt(gdts+i,0,0,0);
  set_gdt(gdts+1,0xffffffff,0x00000000,AR_DATA32_RW);
  set_gdt(gdts+2,LIMIT_BOTPAK,ADR_BOTPAK,AR_CODE32_ER);
  load_gdtr(LIMIT_GDT,ADR_GDT);
}
