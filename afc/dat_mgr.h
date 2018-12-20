#ifndef _AFC_DAT_MGR_H_
#define _AFC_DAT_MGR_H_

#include <cassert>
#include <vector>
#include <algorithm>

#include "array_ptr.h"



namespace afc{
namespace dat{

////////////////////  <<<  declare  >>>  ////////////////////
#define TS(T) std::vector<T>
#define TSS(T) std::vector<std::vector<T>* >
  


template<class T>
class Mgr
{
public:
  ////函数指针（用于过滤、分组、排序、输出）
  typedef bool (*PF_ITEM_DEL)(T*);
  typedef bool (*PF_ITEM_EQU)(T*, T*);
  typedef bool (*PF_GROUP_LESS)(TS(T*)*, TS(T*)*);
  typedef bool (*PF_ITEM_LESS)(T*, T*);
  typedef void (*PF_ITEM_TRACE)(T*);
  
public:
  ////初始化数据（初始状态：全部数据只分一个组）
  void init(T * ary);
  void init(TS(T)& ary);

public:
  ////过滤
  void filter(PF_ITEM_DEL pf);
  void filter(int group_id, PF_ITEM_DEL pf);
  ////分组
  void group(PF_ITEM_EQU pf);
  ////排序（组间排序）
  void sort(PF_GROUP_LESS pf);
  ////排序（组内排序）
  void sort(int group_id, PF_ITEM_LESS pf);
  ////排序（循环每个组内排序）
  void sort(PF_ITEM_LESS pf);
  ////排序（组间排序+循环每个组内排序）
  void sort(PF_GROUP_LESS pf_group, PF_ITEM_LESS pf_item);

public:
  ////组的数量
  int group_count();
  ////组的指针
  TS(T*) * group(int group_id);
  ////组内元素的数量
  int item_count(int group_id);
  int item_count(TS(T*) * group_ptr);
  ////组内元素的指针
  T * item(int group_id, int item_id);
  T * item(TS(T*) * group_ptr, int item_id);

public:
  //void trace();
  void trace(PF_ITEM_TRACE pf = NULL);
  
private:
  TSS(T*)& dat_mgr();
  void clear_dat_mgr();
  bool is_valid(TS(T*) * ts);
  void ptr_2_dat_mgr(T * ary, int count);
  void erase_null_group();
  static bool is_null_group(const TS(T*)*& ts);

private:
  TSS(T*) dat_;

public:
  ~Mgr(){
    clear_dat_mgr();
  }
};


////////////////////  <<<  public  >>>  ////////////////////

template<class T>
void Mgr<T>::init(T * ary)
{
  clear_dat_mgr();
  if(!ary){
    return;
  }
  int count = afc::ary::size<T>(ary);
  if(count<=0){
    return;
  }
  ptr_2_dat_mgr(ary, count);
}

template<class T>
void Mgr<T>::init(TS(T)& ary)
{
  clear_dat_mgr();
  if(ary.empty()){
    return;
  }
  int count = ary.size();
  if(count<=0){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    return;
  }
  ptr_2_dat_mgr(&ary[0], count);

//   TRACE_OUT("init()\n");
//   trace_tss<T>(dat_mgr());
}

template<class T>
void Mgr<T>::filter(PF_ITEM_DEL pf)
{
  assert(pf);
  int n=group_count();
  int i=0;
  for(i=0; i<n; ++i){
    filter(i, pf);
  }
  //del null group
  erase_null_group();
}

template<class T>
void Mgr<T>::filter(int group_id, PF_ITEM_DEL pf)
{
  assert(pf);
//   assert(group_id >= 0);
//   assert(group_id < dat_mgr().size());
//   assert(dat_mgr()[group_id]);
//   TS(T*)& ts = *dat_mgr()[group_id];
  TS(T*)& ts = *group(group_id);
  TS(T*)::iterator it = std::remove_if(ts.begin(), ts.end(), pf);
  if(it != ts.end()){
    ts.erase(it, ts.end());
  }
}

template<class T>
void Mgr<T>::group(PF_ITEM_EQU pf)
{
  assert(pf);
  //TRACE_OUT("\ngrouping()\n");
  TSS(T*) temp;
  int count = dat_mgr().size();
  //TRACE_OUT("dat_mgr count = %d, \n", count);
  if(count <= 0){
    return;
  }
  //TRACE_OUT("dat_mgr[0]'s item count = %d, \n", item_count(0));
  int i=0;
  for(i=0; i<count; ++i){
    ary_2_ary2d<T>(*dat_mgr()[i], temp, pf);
  }
  copy_tss<T>(temp, dat_mgr());
}

template<class T>
void Mgr<T>::sort(PF_GROUP_LESS pf)
{
  assert(pf);
  TSS(T*) tss = dat_mgr();
  std::sort(tss.begin(), tss.end(), pf);
  dat_mgr() = tss;
}

template<class T>
void Mgr<T>::sort(int group_id, PF_ITEM_LESS pf)
{
  assert(pf);
//   assert(group_id >= 0);
//   assert(group_id < dat_mgr().size());
//   assert(dat_mgr()[group_id]);
//   TS(T*) ts = *dat_mgr()[group_id];
  TS(T*) ts = *group(group_id);
  std::sort(ts.begin(), ts.end(), pf);
  *group(group_id) = ts;
}

template<class T>
void Mgr<T>::sort(PF_ITEM_LESS pf)
{
  assert(pf);
  int n = group_count();
  int i=0;
  for(i=0; i<n; ++i){
    sort(i, pf);
  }
}

template<class T>
void Mgr<T>::sort(PF_GROUP_LESS pf_group, PF_ITEM_LESS pf_item)
{
  assert(pf_group);
  assert(pf_item);
  sort(pf_group);
  sort(pf_item);
}

template<class T>
int Mgr<T>::group_count()
{
  int n = dat_mgr().size();
  return n;
}

template<class T>
TS(T*)* Mgr<T>::group(int group_id)
{
  assert(group_id >= 0);
  assert(group_id < dat_mgr().size());
  assert(dat_mgr()[group_id]);
  TS(T*) * ts = dat_mgr()[group_id];
  assert(ts);
  return ts;
}

template<class T>
int Mgr<T>::item_count(int group_id)
{
  assert(group_id >= 0);
  assert(group_id < dat_mgr().size());
  assert(dat_mgr()[group_id]);
  int n = dat_mgr()[group_id]->size();
  return n;
}

template<class T>
int Mgr<T>::item_count(TS(T*) * group_ptr)
{
  assert(group_ptr);
//   TRACE_OUT("item_count(%d)\n", group_ptr);
  assert(is_valid(group_ptr));
  int n = group_ptr->size();
  return n;
}

template<class T>
T * Mgr<T>::item(int group_id, int item_id)
{
  assert(group_id >= 0);
  assert(group_id < dat_mgr().size());
  assert(item_id >= 0);
  assert((dat_mgr()[group_id]));
  assert(item_id < dat_mgr()[group_id]->size());
  T * t = (*(dat_mgr()[group_id]))[item_id];
  return t;
}

template<class T>
T * Mgr<T>::item(TS(T*) * group_ptr, int item_id)
{
  assert(group_ptr);
  assert(item_id >= 0);
  assert(is_valid(group_ptr));
  assert(item_id < group_ptr->size());
  T * t = (*group_ptr)[item_id];
  return t;
}

// template<class T>
// void Mgr<T>::trace()
// {
//   trace_tss<T>(dat_mgr(), NULL);
// }

template<class T>
void Mgr<T>::trace(PF_ITEM_TRACE pf)
{
  trace_tss<T>(dat_mgr(), pf);
}

////////////////////  <<<  private  >>>  ////////////////////
template<class T>
TSS(T*)& Mgr<T>::dat_mgr()
{
  return dat_;
//   static Dat_Mgr<T> mgr_;
//   TRACE_OUT("dat_mgr(), &mgr_ == %d\n", &mgr_);
//   TRACE_OUT("dat_mgr(), &mgr_.dat_ == %d\n", &mgr_.dat_);
//   return mgr_.dat_;
}

template<class T>
void Mgr<T>::clear_dat_mgr()
{
  destory_tss<T>(dat_mgr());
}

template<class T>
bool Mgr<T>::is_valid(TS(T*) * ts)
{
  TSS(T*)::iterator it = NULL;
  it = std::find(dat_mgr().begin(), dat_mgr().end(), ts);
  if(it == dat_mgr().end()){
    return false;
  }
  return true;
}

template<class T>
void Mgr<T>::ptr_2_dat_mgr(T * ary, int count)
{
  clear_dat_mgr();
  if(count<=0){
    return;
  }
  //new
  //TRACE_OUT("ptr_2_dat_mgr()\n");
  TS(T*) * new_ts = create_ts<T>();
  dat_mgr().push_back(new_ts);
  TS(T*)& ts = *dat_mgr()[0];
  int i=0;
  for(i=0; i<count; ++i){
    ts.push_back(&ary[i]);
  }
//   trace_tss<T>(dat_mgr());
}

template<class T>
bool Mgr<T>::is_null_group(const TS(T*)*& ts)
{
  if(ts->empty()){
    return true;
  }
  return false;
}

template<class T>
void Mgr<T>::erase_null_group()
{
  TSS(T*)::iterator find_it = NULL;
  find_it = std::remove_if(dat_mgr().begin(), dat_mgr().end(), is_null_group);
  if(find_it == dat_mgr().end()){
    return;
  }
  TSS(T*)::iterator it = find_it;
  for(; it!=dat_mgr().end(); ++it){
    destory_ts<T>(*it);
  }
  dat_mgr().erase(find_it, dat_mgr().end());
}

template<class T>
void ary_2_ary2d(TS(T*)& s, TSS(T*)& d, Mgr<T>::PF_ITEM_EQU pf)
{
  int count = s.size();
//   TRACE_OUT("ary_2_ary2d, ary's item count = %d, \n", count);
  int i=0;
  for(i=0; i<count; ++i){
    element_2_ary2d<T>(s[i], d, pf);
  }
}

template<class T>
void element_2_ary2d(T * s, TSS(T*)& d, Mgr<T>::PF_ITEM_EQU pf)
{
  int count = d.size();
//   TRACE_OUT("element_2_ary2d, ary2d's ary count = %d, \n", count);
  int i=0;
  for(i=0; i<count; ++i){
    if(element_2_ary<T>(s, *d[i], pf)){
      return;
    }
  }
  //new
  TS(T*) * new_ts = create_ts<T>();
  new_ts->push_back(s);
  d.push_back(new_ts);
}

template<class T>
bool element_2_ary(T * s, TS(T*)& d, Mgr<T>::PF_ITEM_EQU pf)
{
  assert(!d.empty() && "dest ary mustn't null.");
  if(pf(s, d.front())){
    d.push_back(s);
    return true;
  }else{
    return false;
  }

//   int count = d.size();
//   TRACE_OUT("element_2_ary, ary's item count = %d, \n", count);
//   int i=0;
//   for(i=0; i<count; ++i){
//     if(pf(s, d[i])){
//       d.push_back(s);
//       return true;
//     }
//   }
//   return false;
}

template<class T>
TS(T*) * create_ts()
{
  TS(T*) * ts = new TS(T*);
  assert(ts);
  return ts;
}

template<class T>
void destory_ts(TS(T*) *& ts)
{
  ts->clear();
  delete ts;
  ts = NULL;
}

template<class T>
void destory_tss(TSS(T*)& tss)
{
  int count = tss.size();
  int i=0;
  for(i=0; i<count; ++i){
    destory_ts<T>(tss[i]);
  }
  tss.clear();
}

template<class T>
void copy_tss(TSS(T*)& s, TSS(T*)& d)
{
  destory_tss<T>(d);
  d = s;
}

template<class T>
void trace_t(T* t, Mgr<T>::PF_ITEM_TRACE pf)
{
  if(pf){
    pf(t);
    return;
  }
  TRACE_OUT("T * t == %d\n", t);
}


template<class T>
void trace_ts(TS(T*)& ts, Mgr<T>::PF_ITEM_TRACE pf)
{
  int count = ts.size();
  TRACE_OUT("item's count == %d\n", count);
  int i=0;
  for(i=0; i<count; ++i){
    assert(ts[i]);
    //TRACE_OUT("item[%d]'s info\n", i);
    trace_t<T>(ts[i], pf);
  }
}

template<class T>
void trace_tss(TSS(T*)& tss, Mgr<T>::PF_ITEM_TRACE pf)
{
  int count = tss.size();
  TRACE_OUT("group's count == %d\n", count);
  int i=0;
  for(i=0; i<count; ++i){
    assert(tss[i]);
    TRACE_OUT("group[%d]'s info\n", i);
    trace_ts<T>(*tss[i], pf);
  }
}


}//namespace
}//namespace




#endif//FILE
