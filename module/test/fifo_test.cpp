#include <bits/stdc++.h>
#include "../fifo.cpp"

using namespace std;

int main(){
  FIFO fifo;
  for(int i=0;i<16;i++)fifo.push(i);
  for(int i=0;i<16;i++)cout<<(int)fifo.pop()<<" "<<fifo.ptr_r<<" "<<fifo.ptr_w<<endl;
  for(int i=0;i<31;i++)fifo.push(i);
  for(int i=0;i<31;i++)cout<<(int)fifo.pop()<<" "<<fifo.ptr_r<<" "<<fifo.ptr_w<<endl;
}
