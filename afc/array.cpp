#include "stdafx.h"
#include "array.h"
#include <vector>

namespace ary{
  
  class Ary
  {
  public:
    int max_;
    int size_;
    void * mem_;
  public:
    Ary():max_(0),size_(0),mem_(NULL){}
    ~Ary(){destory();}
    
  public:
    void set(void * mem, int newsize);
    void destory();
    void create(int newsize);
    
  public:
    void resize(int newsize);
    void add_size(int unitsize);
    void push_back(void * o, int unitsize);
  };
  
  void Ary::set(void * mem, int newsize)
  {
    destory();
    mem_ = mem;
    size_ = newsize;
  }
  
  void Ary::destory()
  {
    if(mem_){
      free(mem_);
      mem_ = 0;
      size_ = 0;
    }
  }
  
  void Ary::create(int newsize)
  {
    void * m = malloc(max_);
    memcpy(m, mem_, size_);
    set(m, newsize);
  }
  
  void Ary::resize(int newsize)
  {
    if(newsize <= max_){
      size_ = newsize;
      return;
    }
    max_ = newsize;
    
    create(newsize);
  }
  
  void Ary::add_size(int unitsize)
  {
    int newsize = size_ +1;
    if(max_==0){
      max_=1;
    }
    max_ *= 2;
    
    create(newsize);
  }
  
  void Ary::push_back(void * o, int unitsize)
  {
    add_size(unitsize);
    
    char * p = (char*)(mem_);
    p += (size_-1)*unitsize;
    memcpy(p, o, unitsize);
  }
  
  
  
  //////////////////////////////////////////////////////////////////////////
  class AryAry
  {
  public:
    std::vector<Ary*> dat_;
    
  public:
    int find_index(void * p); //  如果没有则返回-1
    Ary& take_ary(void * p); //  如果没有则添加一个后，返回新加入的
    Ary& getat(int index);
    
  public:
    ~AryAry(){
      int i=0;
      for(i=0; i<dat_.size(); ++i){
        if(dat_[i]){
          delete dat_[i];
          dat_[i] = NULL;
        }
      }
      dat_.clear();
    }
  };
  
  static AryAry& mgr()
  {
    static AryAry a;
    return a;
  }
  
  int AryAry::find_index(void * p)
  {
    int i=0;
    for(i=0; i<dat_.size(); ++i){
      if(getat(i).mem_ == p){
        return i;
      }
    }
    return -1;
  }
  
  Ary& AryAry::take_ary(void * p)
  {
    int id = find_index(p);
    if(id < 0){
      Ary * a = new Ary;
      dat_.push_back(a);
      id = dat_.size() -1;
    }
    return getat(id);
  }
  
  Ary& AryAry::getat(int index)
  {
    return *dat_[index];
  }
  
  
  //////////////////////////////////////////////////////////////////////////
  int size(void * p, int unitsize)
  {
    int id = mgr().find_index(p);
    if(id < 0){
      return 0;
    }
    int itsize = mgr().getat(id).size_;
    return itsize / unitsize;
  }
  
  void resize(void ** pp, int newcount, int unitsize)
  {
    Ary & a = mgr().take_ary(*pp);
    a.resize(newcount * unitsize);
    *pp = a.mem_;
  }
  
  void add_size(void ** pp, int unitsize)
  {
    Ary & a = mgr().take_ary(*pp);
    a.add_size(unitsize);
    *pp = a.mem_;
  }
  
  void push_back(void ** pp, void * o, int unitsize)
  {
    Ary & a = mgr().take_ary(*pp);
    a.push_back(o, unitsize);
    *pp = a.mem_;
  }
  
  
}//namespace
