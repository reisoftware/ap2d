// Dlg_Edit_Hotkey.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Edit_Hotkey.h"

#include "../afc/hk_key_value.h"
#include "../afc/hk_sec.h"
#include "str_tools.h"
#include "Dlg_Hot_Key.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Edit_Hotkey dialog


Dlg_Edit_Hotkey::Dlg_Edit_Hotkey(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Edit_Hotkey::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Edit_Hotkey)
	cbk_ = -1;
	hit_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Edit_Hotkey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Edit_Hotkey)
	DDX_CBIndex(pDX, ID_COMBO_CBK, cbk_);
	DDX_CBString(pDX, ID_COMBO_HIT, hit_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Edit_Hotkey, CDialog)
	//{{AFX_MSG_MAP(Dlg_Edit_Hotkey)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Edit_Hotkey message handlers
void Dlg_Edit_Hotkey::set(LPCTSTR kcmd, LPCTSTR kval)
{
  kcmd_ = kcmd;
  kval_ = kval;
}

std::string Dlg_Edit_Hotkey::kcmd()const
{
  return kcmd_;
}

std::string Dlg_Edit_Hotkey::kval()const
{
  return kval_;
}




BOOL Dlg_Edit_Hotkey::OnInitDialog() 
{
	CDialog::OnInitDialog();
  //////////////////////////////////
  hk::COMBO_KEY ck;
  char hit=0;
  hk::set_value(kval_, ck, hit);
  cbk_ = (int)ck;
  hit_ = hit;

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Edit_Hotkey::OnOK() 
{
  //////////////////////////////////
  UpdateData();
  hit_ = afc::filter_string(hit_.GetBuffer(0), " \t").c_str();
  if(hit_.IsEmpty()){
    //     AfxMessageBox("Select a letter, please.");
    //     return;
    hit_ = hk::tilde();
  }
  if(hit_.GetLength() != 1){
    AfxMessageBox("Select one letter only, please.");
    return;
  }
  char hit = 0;
  hit = hit_.GetAt(0);
  hit = toupper(hit);
  if(!hk::can_use(hit)){
    AfxMessageBox("Select a letter, please.");
    return;
  }
  kval_ = hk::get_value((hk::COMBO_KEY)cbk_, hit);
  if(hkdlg::hotkey().is_conflict(kval_.c_str())){
    AfxMessageBox("Conflict, select the other hotkey, please.");
    return;
  }
//////
	CDialog::OnOK();
}
