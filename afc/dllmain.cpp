#include "stdafx.h"
#include "hk_dlg.h"

namespace afc{
HINSTANCE hinstance_ = NULL; 

HINSTANCE& hinstance()
{
  return hinstance_;
}

}//namespace

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch(ul_reason_for_call) 
  { 
  case DLL_PROCESS_ATTACH: 
    afc::hinstance() = (HINSTANCE)hModule; 
  case DLL_PROCESS_DETACH: 
    break; 
  } 
  return TRUE; 
}

