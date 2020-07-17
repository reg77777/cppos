#ifndef INCLUDE_FIFO
#define INCLUDE_FIFO

struct FIFO{
  int ptr_r=0;
  int ptr_w=0;
  unsigned char data[32];

  FIFO();
  bool have_buf();
  unsigned char pop();
  void push(unsigned char val);
};

#endif
