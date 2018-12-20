#include "stdafx.h"
#include "hk_edit_dlg.h"
#include "dllmain.h"
#include "resource.h"
#include "hk_key_value.h"
#include "hk_fhit.h"
#include "hk_dlg.h"

namespace edit{

std::string kcmd_;
std::string kval_;
BOOL isok_ = FALSE;

HWND hwnd_; 
HWND hparent_;

////////////////////  <<<    >>>  ////////////////////
BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL command_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

static void on_init_dlg();
static void on_ok();

////////////////////  <<<    >>>  ////////////////////
std::string& kcmd()
{
  return kcmd_;
}
std::string& kval()
{
  return kval_;
}

BOOL isok()
{
  return isok_;
}

HWND& hparent()
{
  return hparent_;
}


void show_dlg()
{
  isok_ = false;
  DialogBox(afc::hinstance(),
    MAKEINTRESOURCE(ID_DLG_HOTKEY_EDIT), 
    hparent_,
    (DLGPROC)edit::DlgProc);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  hwnd_ = hDlg;
  switch(message) 
  { 
  case WM_INITDIALOG:
    on_init_dlg();
    return TRUE;
  case WM_COMMAND: 
    return command_proc(hDlg, message, wParam, lParam);
    return TRUE;     
  case WM_CLOSE: 
    EndDialog(hDlg, IDCANCEL);
    //DestroyWindow(hDlg); 
    hwnd_ = NULL; 
    return TRUE; 
  } 
  return FALSE; 
}

BOOL command_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(LOWORD(wParam)){
  case IDOK:
    on_ok();
    return TRUE;
  case IDCANCEL:
    EndDialog(hDlg, IDCANCEL);
    return TRUE;
  }
  
  return TRUE;
}


void on_init_dlg()
{
  HWND hcbk  = ::GetDlgItem(hwnd_, ID_COMBO_CBK );
  HWND hhit  = ::GetDlgItem(hwnd_, ID_COMBO_HIT );
  
  ::SendMessage(hcbk, CB_ADDSTRING, 1, (LPARAM)hk::tilde());
  ::SendMessage(hcbk, CB_ADDSTRING, 1, (LPARAM)hk::k_ctrl());
  ::SendMessage(hcbk, CB_ADDSTRING, 1, (LPARAM)hk::k_shift());
  ::SendMessage(hcbk, CB_ADDSTRING, 1, (LPARAM)hk::k_ctrl_shift());
  
  ::SendMessage(hhit, CB_ADDSTRING, 1, (LPARAM)hk::tilde());
  char i=0;
  for(i=65; i<=90; ++i){
    std::string str;
    str = i;
    ::SendMessage(hhit, CB_ADDSTRING, 1, (LPARAM)(str.c_str()));
  }

  hk::COMBO_KEY cbk = hk::KEY_NULL;
  char hit = 0;
  hk::set_value(kval_, cbk, hit);
  
  ::SendMessage(hcbk, CB_SETCURSEL, cbk, 0);
  std::string str;
  str = hit;
  ::SetWindowText(hhit, str.c_str());
}

void on_ok()
{
  HWND hcbk  = ::GetDlgItem(hwnd_, ID_COMBO_CBK );
  HWND hhit  = ::GetDlgItem(hwnd_, ID_COMBO_HIT );

  char hit = 0;

  char buf[2];
  int cbk = (int)::SendMessage(hcbk, CB_GETCURSEL, 0, 0);
  int len = ::GetWindowText(hhit, buf, 2);
  if(len <= 0 || len >= 2){
    return;
  }
  buf[len] = 0;
  hit = buf[0];
  hit = toupper(hit);
  if(!hk::can_use(hit)){
    ::MessageBox(hwnd_, "Select a letter, please.", "HotKey", MB_OK);
    return;
  }

  std::string kvalstr = hk::get_value((hk::COMBO_KEY)cbk, hit);
  if(kval_ != kvalstr){
    if(hkdlg::hotkey().is_conflict(kvalstr.c_str())){
      ::MessageBox(hwnd_, "Conflicting, reset it please.", "HotKey", MB_OK);
      return;
    }
  }
  kval_ = kvalstr;
  isok_ = true;
  EndDialog(hwnd_, IDOK);
}

}//namespace

