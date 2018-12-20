#ifndef _AFC_ARRAR_PTR_H_
#define _AFC_ARRAR_PTR_H_

#include "export.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include "../include/getrace.h"

namespace afc{
namespace ary{

////////////////////  <<<  declare  >>>  ////////////////////

template<class T>int size(T * p);
template<class T>void push_back(T *& p, const T & o);
template<class T>void resize(T *& p, int newsize);
template<class T>void copy(T * s, T *& d);
inline void clear();




////////////////////  <<<  public  >>>  ////////////////////

template<class T>
int size(T * p)
{
  if(!p){
    return 0;
  }
  std::vector<T> * cur = find_vector(p);
  if(!cur){
    return 0;
  }
  //std::vector<T> * cur = get_cur_ptr(p);
  return cur->size();
}


template<class T>
void push_back(T *& p, const T & o)
{
  std::vector<T> * cur = get_cur_ptr(p);

  cur->push_back(o);
  p = &(cur->front());
//   return cur->size();
}


template<class T>
void resize(T *& p, int newsize)
{
  std::vector<T> * cur = NULL;
  cur = get_cur_ptr(p);
  cur->resize(newsize);
  int n = cur->size();
  if(n <= 0){
    tmgr<T>().erase(cur);
    p = NULL;
  }else{
    p = &(cur->front());
  }
//   return n;
}

template<class T>
void copy(T * s, T *& d)
{
  d = NULL;
  int count = size<T>(s);
  int i=0;
  for(i=0; i<count; ++i){
    push_back<T>(d, s[i]);
  }
}


////////////////////  <<<  private  >>>  ////////////////////
template<class T>
void add_size(T *& p)
{
  T t;
  init_t<T>(&t);
  push_back<T>(p, t);
//   int n =push_back<T>(p, t);
//   return n;
}

class Mgr 
{
public:
  virtual void clear()=0;
};
inline std::vector<Mgr*>& mgrs();
inline void clear()
{
  int i=0;
  for(i=0; i<mgrs().size(); ++i){
    assert(mgrs()[i]);
    mgrs()[i]->clear();
  }
}


inline std::vector<Mgr*>& mgrs()
{
  static std::vector<Mgr*> ms;
  return ms;
}


template<class T>
class TMgr : public Mgr
{
public:
  std::vector<std::vector<T>* > ps_;
public:
  void erase(std::vector<T>*& p){
    std::vector<std::vector<T>* >::iterator it = NULL;
    it = std::find(ps_.begin(), ps_.end(), p);
    if(it == ps_.end()){
      return;
    }
    destory(p);
    ps_.erase(it);
  }
  void clear(){
    destory<T>(ps_);
  }
  TMgr(){
    mgrs().push_back(this);
  }
  ~TMgr(){
    clear();
  }
};

template<class T>
TMgr<T>& tmgr()
{
  static afc::ary::TMgr<T> tm;
  return tm;
}

template<class T>
std::vector<std::vector<T>* >& tps()
{
  return tmgr<T>().ps_;
}

template<class T> 
void init_t(T * t)
{
  ::ZeroMemory(t, sizeof(T));
}

template<class T>
void destory(std::vector<T>*& ary)
{
  if(!ary){
    return;
  }
  ary->clear();
  delete ary;
  ary = NULL;
}


template<class T>
void destory(std::vector<std::vector<T>* >& ps)
{
  int i=0;
  for(i=0; i<ps.size(); ++i){
    destory(ps[i]);
  }
  ps.clear();
}

template<class T>
std::vector<T>* find_vector(T * p)
{
  int i=0;
  for(i=0; i<tps<T>().size(); ++i){
    T * cur = &(tps<T>()[i]->front());
    if(cur == p){
      return (tps<T>()[i]);
    }
  }
  return NULL;
}

template<class T>
std::vector<T> * get_cur_ptr(T * p)
{
  if(p == NULL){
    return add_ts<T>();
  }
  std::vector<T> * cur = NULL;
  cur = find_vector(p);
  if(cur == NULL){
    return add_ts<T>();
  }
  return cur;
}

template<class T>
std::vector<T> * add_ts()
{
  std::vector<T> * ts = new std::vector<T>;
  tps<T>().push_back(ts);

  return ts;
}

////////////////////  <<<  inner  >>>  ////////////////////
}//namespace
}//namespace




#endif//FILE
