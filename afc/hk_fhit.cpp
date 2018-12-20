#include "stdafx.h"
#include "hk_fhit.h"

#include <cassert>
 
#include "ini.h"
#include "hk_key_value.h"
#include "hotkey.h"
#include "hk_dlg.h"
#include "case_sensitive.h"

namespace hk{


Fhit& fhit_instance()
{
  static Fhit fhit;
  return fhit;
}

Fhit& default_fhit()
{
  static Fhit default_;
  return default_;
}

void Fhit::push_sec(LPCSTR sec)
{
  cur_ = find(sec);
  if(cur_){
    return;
  }
  Sec mysec;
  mysec.name_ = sec;
  hotkey_.push_back(mysec);
  cur_ = &hotkey_.back();
}

void Fhit::push_key(LPCSTR key, char hit, bool ctrl, bool shift)
{
  if(hotkey_.empty() || !cur_){
    push_sec("NO_SEC");
    return;
  }
  assert(cur_);
  if(cur_->find(key)){
    return;
  }
  Key mykey;
  mykey.cmd_ = key;
  mykey.hit_ = hit;
  mykey.ctrl_ = ctrl;
  mykey.shift_ = shift;
  cur_->keys_.push_back(mykey);
}

void push_key(LPCSTR key, char hit, bool ctrl, bool shift)
{
  fhit_instance().push_key(key, hit, ctrl, shift);
  default_fhit().push_key(key, hit, ctrl, shift);
}


std::string Fhit::find(char hit)
{
  std::string fun;
  int i=0;
  for(i=0; i<hotkey_.size(); ++i){
    fun = hotkey_[i].find(hit);
    if(!fun.empty()){
      return fun;
    }
  }
  return "";
}

hk::Sec * Fhit::find(LPCSTR sec_name)
{
  std::string sn;
  int i=0;
  for(i=0; i<hotkey_.size(); ++i){
    if(hotkey_[i].name_ == sec_name){
      return &hotkey_[i];
    }
  }
  return NULL;
}


void Fhit::load()
{
	std::string value;
	for(int i = 0; i < hotkey_.size(); i++){
		Sec &sec = hotkey_[i];
		for(int j = 0; j < sec.keys_.size(); ++j){
			Key & key = sec.keys_[j];
			value = ini::read(file_.c_str(), sec.name_.c_str(), key.cmd_.c_str());
      if(value.empty()){
        continue;	
      }
			hk::set_value(value, key.ctrl_, key.shift_, key.hit_);
		}
	}
}
void Fhit::save()
{
	std::string value;
	for(int i = 0; i < hotkey_.size(); i++){
		Sec &sec = hotkey_[i];
		for(int j = 0; j < sec.keys_.size(); j++){
			Key &key = sec.keys_[j];
			value = hk::get_value(key.ctrl_, key.shift_, key.hit_);
			ini::write(file_.c_str(), sec.name_.c_str(), key.cmd_.c_str(), value.c_str());
		}
	}
}
void Fhit::set(LPCSTR sec, LPCSTR cmd, LPCSTR kval)
{
	for(int i = 0; i < hotkey_.size(); i++){
		Sec &section = hotkey_[i];
		if(section.name_ == sec){
			for(int j = 0; j < section.keys_.size(); j++){
				Key &key = section.keys_[j];
				if(key.cmd_ == cmd){
					hk::set_value(kval, key.ctrl_, key.shift_, key.hit_);
				}
			}	
		}
	}
}
bool Fhit::is_conflict(LPCSTR kval)
{
	std::string kvalue;
	kvalue = kval;
	if (kvalue[0] == NOHIT){
		return false;
	}else{
		std::string value;
		for(int i = 0; i < hotkey_.size(); i++){
			Sec &sec = hotkey_[i];
			for(int j = 0; j < sec.keys_.size(); j++){
				Key &key = sec.keys_[j];
				value = hk::get_value(key.ctrl_, key.shift_, key.hit_);
				if (value == kval){
					return true;
				}
			}
		}
	}
	return false;
}

void Fhit::enable(bool b)
{
  int i=0;
  for(i=0; i<hotkey_.size(); ++i){
    hotkey_[i].enable(b);
  }
}

void Fhit::enable(LPCSTR sec, bool b)
{
  Sec * s = find(sec);
  if(!s){
    return;
  }
  s->enable(b);
}
void Fhit::enable(LPCSTR sec, LPCSTR cmd, bool b)
{
  Sec * s = find(sec);
  if(!s){
    return;
  }
  s->enable(cmd, b);
}



}//namespace



