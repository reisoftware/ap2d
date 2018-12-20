#include "stdafx.h"
#include "hotkey.h"
#include "hk_fhit.h"
#include "hk_dlg.h"

namespace hk{
  

void load(LPCSTR file)
{
  fhit_instance().ini_file(file);
  default_fhit().ini_file(file);
  fhit_instance().load();
}

void push_sec(LPCSTR sec)
{
  fhit_instance().push_sec(sec);
  default_fhit().push_sec(sec);
}

void pop_dlg(HWND hparent)
{
  hkdlg::show_dlg(hparent);
}

void enable(bool b)
{
  fhit_instance().enable(b);
  default_fhit().enable(b);
}

void enable(LPCSTR sec, bool b)
{
  fhit_instance().enable(sec, b);
  default_fhit().enable(sec, b);
}
void enable(LPCSTR sec, LPCSTR cmd, bool b)
{
  fhit_instance().enable(sec, cmd, b);
  default_fhit().enable(sec, cmd, b);
}



}//namespace
