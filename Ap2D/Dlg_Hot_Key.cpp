// Dlg_Hot_Key.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Hot_Key.h"


#include <cassert>
#include "../afc/hotkey.h"

#include "Dlg_Edit_Hotkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static hk::Fhit g_hk_; //g_hk_ = hk::fhit_instance();

/////////////////////////////////////////////////////////////////////////////
// Dlg_Hot_Key dialog
namespace hkdlg{
hk::Fhit& hotkey()
{
  return g_hk_;
}
}//namespace


Dlg_Hot_Key::Dlg_Hot_Key(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Hot_Key::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Hot_Key)
	//}}AFX_DATA_INIT
}


void Dlg_Hot_Key::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Hot_Key)
	DDX_Control(pDX, IDC_LIST_SEC, list_sec_);
	DDX_Control(pDX, IDC_LIST_KEY, list_key_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Hot_Key, CDialog)
	//{{AFX_MSG_MAP(Dlg_Hot_Key)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SEC, OnClickListSec)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_KEY, OnDblclkListKey)
	ON_BN_CLICKED(IDC_BN_DEFAULT, OnBnDefault)
	ON_BN_CLICKED(IDC_BN_ADVANCED, OnBnAdvanced)
	ON_BN_CLICKED(IDC_BN_OK, OnBnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Hot_Key message handlers
BOOL Dlg_Hot_Key::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  g_hk_ = hk::fhit_instance();
  init_sec();
  init_key();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Hot_Key::init_sec()
{
  list_sec_.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  init_sec_column();
  init_sec_item();
}

void Dlg_Hot_Key::init_sec_column()
{
  list_sec_.InsertColumn(0, "TYPE", LVCFMT_LEFT, 150);
}

void Dlg_Hot_Key::init_sec_item()
{
  int i=0;
  for(i=0; i<g_hk_.hotkey_.size(); ++i){
    list_sec_.InsertItem(i, g_hk_.hotkey_[i].name_.c_str());
  }
}

void Dlg_Hot_Key::init_key()
{
  list_key_.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  init_key_column();
}

void Dlg_Hot_Key::init_key_column()
{
  list_key_.InsertColumn(0, "command", LVCFMT_LEFT, 150);
  list_key_.InsertColumn(1, "hotkey", LVCFMT_LEFT, 150);
}

void Dlg_Hot_Key::init_key_item(LPCTSTR sec_name)
{
  list_key_.DeleteAllItems();
  hk::Sec * sec = g_hk_.find(sec_name);
  if(!sec){
    return;
  }
  assert(sec && "init_key_item(), find sec_name.");
  std::vector<hk::Key>& keys = sec->keys_;
  int i=0;
  for(i=0; i<keys.size(); ++i){
    std::string kval = keys[i].key_value();
    list_key_.InsertItem(i, keys[i].cmd_.c_str());
    list_key_.SetItemText(i, 1, kval.c_str());
  }
}

void Dlg_Hot_Key::init_key_item()
{
  int selid = list_sec_.GetSelectionMark();
  list_key_.DeleteAllItems();
  if(selid < 0){
    return;
  }
  std::string sec = list_sec_.GetItemText(selid, 0);
  init_key_item(sec.c_str());
}


void Dlg_Hot_Key::OnClickListSec(NMHDR* pNMHDR, LRESULT* pResult) 
{
  std::string sectxt;
  int selid = list_sec_.GetSelectionMark();
  if(selid == -1){
    return ;
  }
  sectxt = list_sec_.GetItemText(selid, 0);
  init_key_item(sectxt.c_str());
	
  /////////////
	*pResult = 0;
}

void Dlg_Hot_Key::OnDblclkListKey(NMHDR* pNMHDR, LRESULT* pResult) 
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


  ///////////////////
  Dlg_Edit_Hotkey dlg;
  dlg.set(list_key_.GetItemText(keyid, 0), list_key_.GetItemText(keyid, 1));
  if(dlg.DoModal() == IDOK){
    LPCSTR kcmdstr = dlg.kcmd().c_str();
    LPCSTR kvalstr = dlg.kval().c_str();
    list_key_.SetItemText(keyid, 1, kvalstr);
    g_hk_.set(sectxt.c_str(), kcmdstr, kvalstr);
  }
  //*****************
  //   edit::hparent() = hwnd_dlg_;
  //   edit::kcmd() = list_key_.GetItemText(keyid, 0);
  //   edit::kval() = list_key_.GetItemText(keyid, 1);
  //   
  //   edit::show_dlg();
  //   if(edit::isok()){
  //     LPCSTR kcmdstr = edit::kcmd().c_str();
  //     LPCSTR kvalstr = edit::kval().c_str();
  //     list_key_.SetItemText(keyid, 1, kvalstr);
  //     g_hk_.set(sectxt.c_str(), kcmdstr, kvalstr);
  //   }
  ///////////////////
	
  /////////////
	*pResult = 0;
}

void Dlg_Hot_Key::on_ok()
{
  hk::fhit_instance() = g_hk_;
  hk::fhit_instance().save();
  OnOK();
}

void Dlg_Hot_Key::OnBnDefault() 
{
  ///////////////////
  g_hk_ = hk::default_fhit();
  init_key_item();
  //*****************
  //   g_hk_ = hk::default_fhit();
  //   int selid = list_sec_.GetSelectionMark();
  //   list_key_.DeleteAllItems();
  //   if(selid < 0){
  //     return;
  //   }
  //   std::string sec = list_sec_.GetItemText(selid, 0);
  //   init_key_item(sec.c_str());
  ///////////////////
}

void Dlg_Hot_Key::OnBnAdvanced() 
{
  on_ok();
  ::ShellExecute(NULL, "open", hk::fhit_instance().file_.c_str(), "", "", SW_SHOW);
}

void Dlg_Hot_Key::OnBnOk() 
{
	// TODO: Add your control notification handler code here
	on_ok();
}
