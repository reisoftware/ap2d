#ifndef _AFC_FPTR_H_
#define _AFC_FPTR_H_

#include <string>
#include <vector>

namespace hk{


template<class T>
class Fptr
{
public:
  typedef void (T::*PF)();
public:
  std::string cmd_;
  PF ptr_;
};


template<class T>
class Fps
{
public:
  std::vector<Fptr<T> >  fps_;

public:
  void push_key(LPCSTR cmd, Fptr<T>::PF ptr)
  {
    Fptr<T> fp;
    fp.cmd_ = cmd;
    fp.ptr_ = ptr;
    fps_.push_back(fp);
  }

public:
  Fptr<T>::PF find(LPCSTR cmd)const
  {
    int i=0;
    for(i=0; i<fps_.size(); ++i){
      if(fps_[i].cmd_ == cmd){
        return fps_[i].ptr_;
      }
    }
    return NULL;
  }
};


template<class T>
Fps<T>& fps_instance()
{
  static Fps<T> o;
  return o;
}


}//namespace

#endif//FILE
