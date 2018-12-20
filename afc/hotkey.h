#ifndef _AFC_HOTKEY_H_
#define _AFC_HOTKEY_H_

#include "export.h"
#include "hk_fptr.h"
#include "hk_fhit.h"

namespace hk{

AFCAPI void load(LPCSTR file);
AFCAPI void push_sec(LPCSTR sec);
AFCAPI void pop_dlg(HWND hparent);
AFCAPI void enable(bool b);
AFCAPI void enable(LPCSTR sec, bool b);
AFCAPI void enable(LPCSTR sec, LPCSTR cmd, bool b);

template<class T>
void push_key(LPCSTR cmd, Fptr<T>::PF ptr, 
              char hit=NOHIT, bool ctrl=false, bool shift=false)
{
  hk::push_key(cmd, hit, ctrl, shift);
  hk::fps_instance<T>().push_key(cmd, ptr);
}

template<class T>
Fptr<T>::PF find(char hit)
{
  std::string cmd = hk::fhit_instance().find(hit);
  return hk::fps_instance<T>().find(cmd.c_str());
}


}//namespace

#endif//FILE
