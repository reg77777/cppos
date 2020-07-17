#ifndef INCLUDE_VECTOR
#define INCLUDE_VECTOR

template<typename T>
class vector{
  private:
    T*array;
  public:
    int size,array_size;
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
    T*begin(){return 0;};
    T*end(){return this->array+size;};
};

#endif
