#include "stdafx.h"
#include "hk_key.h"
#include "cbk.h"
#include "hk_key_value.h"

namespace hk{

bool can_hit(char c)
{
  if(c >= 'A' || c <= 'Z'){
    return true;
  }
  return false;
}

bool can_use(char c)
{
  if(c == NOHIT){
    return true;
  }
  if(isalpha(c)){
    return true;
  }
  return false;
}

bool Key::is_hit(char hit)
{
  if(!able_){
    return false;
  }
  hit = toupper(hit);
  if(!hk::can_hit(hit)){
    return false;
  }
  bool isctrl = afc::with_ctrl();
  bool isshift = afc::with_shift();
  return (hit_==hit) && (ctrl_==isctrl) && (shift_==isshift);
}

std::string Key::key_value()const
{
  return hk::get_value(ctrl_, shift_, hit_);
}



}//namespace
