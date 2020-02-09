template<typename T>
class vector{
  private:
    int size;
    T*array;
    int array_size;
  public:
    vector():size(0),array_size(1){
      array=new T[array_size];
    };
    vector(int size):size(size){
      array_size=1;
      while(array_size<size)array_size*=2;
      array=new T[array_size];
    };
    vector(T array[]){
      size=sizeof(array)/sizeof(T);
      array_size=1;
      while(array_size<size)array_size*=2;
      array=new T[array_size];
    }
    void push_back(T val){
      if(array_size==size){
        array_size*=2;
        T*new_array=new T[array_size];
        for(int i=0;i<size;i++){
          new_array[i]=array[i];
        }
        delete[]array;
        array=new_array;
      }
      array[size]=val;
      ++size;
    }
    T operator[](int i){
      return this->array[i];
    }
};

class Screen{
  private:
    char*array;
    int sizex;
    int sizey;
  public:
    Screen(char*vram,int sizex,int sizey):sizex(sizex),sizey(sizey),array(vram){};
    void refresh();
    void rectanble(int x1,int y1,int x2,int y2);
    void write(int val,int x,int y){
      array[x+y*sizex]=val;
    };
};

int main(){
  short sizex=*((short*)0x0ff4);
  short sizey=*((short*)0x0ff6);
  char*vram=*((char**)0x0ff8);
  Screen screen(vram,sizex,sizey);
  for(int i=0;i<320;i++){
    for(int j=0;j<200;j++){
      screen.write((i+j)&0xf,i,j);
    }
  }
  for(;;){
  }
}
