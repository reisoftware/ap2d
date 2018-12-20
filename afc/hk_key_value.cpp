#include "stdafx.h"
#include "hk_key_value.h"

#include "case_sensitive.h"
#include "hk_key.h"
#include "str_tools.h"

#include <algorithm>
#include <vector>


namespace hk{

LPCSTR k_ctrl()
{
	return "Ctrl";
}
LPCSTR k_shift()
{
	return "Shift";
}
LPCSTR k_ctrl_shift()
{
	return "Ctrl+Shift";
}
LPCSTR tilde()
{
	return "~";
}
void set_value(std::string value, bool& ctrl, bool& shift, char& hit)
{
  std::vector<std::string> vec;
	value = afc::lower(value);
  afc::split_string(vec, value, "+-_ ");
	std::string key_ctrl = afc::lower(k_ctrl());
  std::vector<std::string>::iterator it_ctrl = std::find(vec.begin(), vec.end(), key_ctrl);
  if (it_ctrl != vec.end()){
    ctrl = true;
    vec.erase(it_ctrl);
  }else{
    ctrl = false;
  }
	std::string key_shift = afc::lower(k_shift());
  std::vector<std::string>::iterator it_shf = std::find(vec.begin(), vec.end(), key_shift);
  if (it_shf != vec.end()){
    shift = true;
    vec.erase(it_shf);
  }else{
    shift = false;
  }
  
  if (vec.size() == 0){
    ctrl = false;
    shift = false;
    hit = NOHIT;	
    return;
  }
  std::string temp = afc::upper(vec.front());
  hit = temp[0];
}
void set_value(std::string value, COMBO_KEY & combo, char& hit)
{
  bool ctrl;
  bool shift;
  hk::set_value(value, ctrl, shift, hit);
  if (hit == NOHIT){
    combo = KEY_NULL;
  }else{
    if(ctrl && shift){
      combo = KEY_CTRLSHIFT;
    }else if (ctrl && !shift){
      combo = KEY_CTRL;
    }else if (shift && !ctrl){
      combo = KEY_SHIFT;
    }
  }
}
std::string get_value(bool ctrl, bool shift, char hit)
{
  std::string s_ctrl = k_ctrl();
  std::string s_shift = k_shift();
  std::string add = "+";
  std::string value;
  if (hit == NOHIT){
    value = tilde();
  }else{
    if(ctrl && shift){
      value = s_ctrl + add + s_shift + add + hit;
    }else if (ctrl && !shift){
      value = s_ctrl + add + hit;
    }else if (shift && !ctrl){
      value = s_shift + add + hit;
    }else{
      value = hit;
    }
  }
  return value;
}
std::string get_value(COMBO_KEY combo, char hit)
{
  bool ctrl;
  bool shift;
  switch(combo){
  case KEY_NULL: 
    ctrl = false;
    shift = false;
    break;
  case KEY_CTRL:
    ctrl = true;
    shift = false;
    break;
  case KEY_SHIFT:
    ctrl = false;
    shift = true;
    break;
  case KEY_CTRLSHIFT:
    ctrl = true;
    shift = true;
    break;
  }
  return get_value(ctrl, shift, hit);
}



}//namespace
