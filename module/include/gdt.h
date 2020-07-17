#ifndef INCLUDE_GDT
#define INCLUDE_GDT

struct GDT{
  short limit_low,base_low;
  char base_mid,access_right;
  char limit_high,base_high;
};

class GDTs{
  public:
    GDTs();
    void set_gdt(GDT*gdts,unsigned int limit,int base,int ar);
    void load();
};

#endif
