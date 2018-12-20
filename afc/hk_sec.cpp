#include "stdafx.h"
#include "hk_sec.h"

namespace hk{

std::string Sec::find(char hit)
{
  int i=0;
  for(i=0; i<keys_.size(); ++i){
    if(keys_[i].is_hit(hit)){
      return keys_[i].cmd_;
    }
  }
  return "";
}

Key * Sec::find(LPCSTR cmd)
{
  int i=0;
  for(i=0; i<keys_.size(); ++i){
    if(keys_[i].cmd_ == cmd){
      return &keys_[i];
    }
  }
  return NULL;
}

void Sec::enable(bool b)
{
  int i=0;
  for(i=0; i<keys_.size(); ++i){
    keys_[i].enable(b);
  }
}
void Sec::enable(LPCSTR cmd, bool b)
{
  Key * k = find(cmd);
  if(k){
    k->enable(b);
  }
}



}//namespace

