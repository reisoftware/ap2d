#include "stdafx.h"
#include "resource.h"

#include "hotkey.h"
#include "hk_dlg.h"
#include "hk_edit_dlg.h"

#include "list_ctrl.h"
#include "dllmain.h"

#include <shellapi.h>
#include <cassert>

namespace hkdlg{


HWND hwnd_dlg_ = NULL; 
hk::Fhit m_hk_; //m_hk_ = hk::fhit_instance();

List_Ctrl list_sec_; 
List_Ctrl list_key_; 


////////////////////  <<<  function declared  >>>  ////////////////////
static void init_sec();
static void init_sec_column();
static void init_sec_item();

static void init_key();
static void init_key_column();
static void init_key_item(const char * sec_name);


BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam); 
static BOOL command_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
static BOOL notify_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

static void on_ok();
static void on_cancel();
static void on_advanced();
static void on_default();

static void on_list_sec_click();
static void on_list_key_dbclick();

////////////////////  <<<  function define  >>>  ////////////////////
HWND& hwnd_dlg()
{
  return hwnd_dlg_;
}

hk::Fhit& hotkey()
{
  return m_hk_;
}
// 
// bool isok()
// {
//   return isok_;
// }
// 
// std::string& ini_file()
// {
//   return file_;
// }

void show_dlg(HWND hparent)
{
  m_hk_ = hk::fhit_instance();
  DialogBox(afc::hinstance(),
    MAKEINTRESOURCE(ID_DLG_HOTKEY), 
    hparent,
    (DLGPROC)DlgProc); 
//   init_sec();
//   init_key();
  ShowWindow(hwnd_dlg_, SW_SHOW); 
}



////////////////////  <<<  proc  >>>  ////////////////////
BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  hwnd_dlg_ = hDlg;
  switch(message) 
  { 
  case WM_INITDIALOG:
    init_sec();
    init_key();
    return TRUE;
  case WM_COMMAND: 
    return command_proc(hDlg, message, wParam, lParam);
  case WM_NOTIFY:
    return notify_proc(hDlg, message, wParam, lParam);
  case WM_CLOSE:
    on_cancel();
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
    on_cancel();
    return TRUE;
  case ID_ADVANCED:
    on_advanced();
    return TRUE;
  case ID_DEFAULT:
    on_default();
    return TRUE;
  }
  
  return TRUE;
}

////////////////////  <<<  edit_dlg  >>>  ////////////////////
BOOL notify_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  NMHDR * nmhdr = (NMHDR*)lParam;
  if( wParam==ID_LIST_SEC && nmhdr->code==NM_CLICK ){
    on_list_sec_click();
    return TRUE;
  }
  if( wParam==ID_LIST_KEY && nmhdr->code==NM_DBLCLK){
    on_list_key_dbclick();
    return TRUE;
  }

  return TRUE;
}

////////////////////  <<<  sec  >>>  ////////////////////
void init_sec()
{
  HWND hdlg = hwnd_dlg();
  //HWND hlc = ::GetDlgItem(hwnd_dlg(), ID_LIST_SEC);
  //list_sec_.init(hlc);
  list_sec_.init(hwnd_dlg(), ID_LIST_SEC);
  list_sec_.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  init_sec_column();
  init_sec_item();
}

void init_sec_column()
{
  list_sec_.InsertColumn(0, 150, "TYPE");
}

void init_sec_item()
{
  int i=0;
  for(i=0; i<m_hk_.hotkey_.size(); ++i){
    list_sec_.InsertItem(m_hk_.hotkey_[i].name_.c_str());
  }
}


////////////////////  <<<  key  >>>  ////////////////////
void init_key()
{
  HWND hdlg = hwnd_dlg();
  HWND hlc = ::GetDlgItem(hwnd_dlg(), ID_LIST_KEY);
  list_key_.init(hlc);
  list_key_.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  init_key_column();
  //init_key_item();
}

void init_key_column()
{
  list_key_.InsertColumn(0, 150, "command");
  list_key_.InsertColumn(1, 150, "hotkey");
}

void init_key_item(const char * sec_name)
{
  list_key_.DeleteAllItems();
  hk::Sec * sec = m_hk_.find(sec_name);
  if(!sec){
    return;
  }
  assert(sec && "init_key_item(), find sec_name.");
  std::vector<hk::Key>& keys = sec->keys_;
  int i=0;
  for(i=0; i<keys.size(); ++i){
    std::string kval = keys[i].key_value();
    list_key_.InsertItem(keys[i].cmd_.c_str());
    list_key_.SetItemText(i, 1, kval.c_str());
  }
}

void on_ok()
{
  hk::fhit_instance() = m_hk_;
  hk::fhit_instance().save();
  EndDialog(hwnd_dlg_, IDOK);
}

void on_cancel()
{
  EndDialog(hwnd_dlg_, IDCANCEL);
}

void on_advanced()
{
  on_ok();
  ::ShellExecute(hwnd_dlg_, "open", hk::fhit_instance().file_.c_str(), "", "", SW_SHOW);
  //EndDialog(hwnd_dlg_, IDCANCEL);
}


void on_default()
{
  int selid = list_sec_.GetSelectionMark();
  m_hk_ = hk::default_fhit();
  list_key_.DeleteAllItems();
  if(selid < 0){
    return;
  }
  std::string sec = list_sec_.GetItemText(selid, 0);
  init_key_item(sec.c_str());
}

void on_list_sec_click()
{
  std::string sectxt;
  int selid = list_sec_.GetSelectionMark();
  if(selid == -1){
    return ;
  }
  sectxt = list_sec_.GetItemText(selid, 0);
  init_key_item(sectxt.c_str());
  return ;
}


void on_list_key_dbclick()
{
  std::string sectxt;
  int secid = list_sec_.GetSelectionMark();
  if(secid == -1){
    return;
  }
  sectxt = list_sec_.GetItemText(secid, 0);

  int keyid = list_key_.GetSelectionMark();
  if(keyid == -1){
    return;
  }
  edit::hparent() = hwnd_dlg_;
  edit::kcmd() = list_key_.GetItemText(keyid, 0);
  edit::kval() = list_key_.GetItemText(keyid, 1);

  edit::show_dlg();
  if(edit::isok()){
    LPCSTR kcmdstr = edit::kcmd().c_str();
    LPCSTR kvalstr = edit::kval().c_str();
    list_key_.SetItemText(keyid, 1, kvalstr);
    m_hk_.set(sectxt.c_str(), kcmdstr, kvalstr);
  }
}



}//namespace



