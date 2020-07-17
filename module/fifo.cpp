#include "include/fifo.h"

FIFO::FIFO(){
  for(int i=0;i<32;i++)data[i]=0;
}

bool FIFO::have_buf(){
  return ptr_r!=ptr_w;
}

unsigned char FIFO::pop(){
  if(!have_buf())return -1;
  unsigned char res=data[ptr_r];
  ptr_r++;
  if(ptr_r>=32)ptr_r=0;
  return res;
}

void FIFO::push(unsigned char val){
  data[ptr_w]=val;
  ptr_w++;
  if(ptr_w>=32)ptr_w=0;
}
