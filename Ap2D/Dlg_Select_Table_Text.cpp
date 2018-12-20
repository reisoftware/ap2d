// Dlg_Select_Table_Text.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Select_Table_Text.h"
#include "Mgr_Database.h"
#include "Database.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Table_Text dialog


Dlg_Select_Table_Text::Dlg_Select_Table_Text(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Select_Table_Text::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Select_Table_Text)
	//}}AFX_DATA_INIT
}


void Dlg_Select_Table_Text::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Select_Table_Text)
	DDX_Control(pDX, IDC_LIST_NUMBERS, LIST_NUMBERS_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Select_Table_Text, CDialog)
	//{{AFX_MSG_MAP(Dlg_Select_Table_Text)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NUMBERS, OnDblclkListNumbers)
	ON_BN_CLICKED(ID_BUTTON_RECOVERY, OnButtonRecovery)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void Dlg_Select_Table_Text::set_sel_ifo(std::vector<dlhml::Entity*> sel_ents,std::vector<dlhml::Entity*> ents,Dlg_Select_Table_Text* dlg)
{
	cur_sel_ = sel_ents;
	all_ents_ = ents;
	dlg_tab_txt_ = dlg;
}

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Table_Text message handlers
void Dlg_Select_Table_Text::init_matrix_type()
{
	DWORD dwStyle = LIST_NUMBERS_.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	LIST_NUMBERS_.SetExtendedStyle(dwStyle); //设置扩展风格

	CRect rc;
  CWnd *pWnd = GetDlgItem(IDC_LIST_NUMBERS);//参数为控件ID
  pWnd->GetClientRect(&rc);//rc为控件的大小。
	int nWid = rc.Width();//获得控件宽度
	LIST_NUMBERS_.InsertColumn(0,"ID",LVCFMT_LEFT,50);
	LIST_NUMBERS_.InsertColumn(1,"Name",LVCFMT_LEFT,(float)(nWid-50)/2);
	LIST_NUMBERS_.InsertColumn(2,"Numbers",LVCFMT_LEFT,(float)(nWid-50)/2);
//	LIST_NUMBERS_.InsertItem(0,"");
//	LIST_NUMBERS_.SetItemText(0,0,"1");
//	LIST_NUMBERS_.SetItemText(0,1,"1");
//	LIST_NUMBERS_.SetItemText(0,2,"1");
}

void Dlg_Select_Table_Text::init_matrix_ifo()
{
	LIST_NUMBERS_.DeleteAllItems();
	mgr_db_init_dlg_sel_tab_text_data(cur_sel_,all_ents_,LIST_NUMBERS_);
	
}

BOOL Dlg_Select_Table_Text::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init_matrix_type();
	init_matrix_ifo();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void Dlg_Select_Table_Text::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void Dlg_Select_Table_Text::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}



void Dlg_Select_Table_Text::OnDblclkListNumbers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = LIST_NUMBERS_.GetFirstSelectedItemPosition();
	int ntem = LIST_NUMBERS_.GetNextSelectedItem(pos);
	CString sel_str = LIST_NUMBERS_.GetItemText(ntem,1);
	show_sel_tab_txt(sel_str,all_ents_);
	*pResult = 0;
}

void Dlg_Select_Table_Text::OnButtonRecovery() 
{
	// TODO: Add your control notification handler code here
	show_tab_txt_dlg_all_ents(all_ents_);
}

void Dlg_Select_Table_Text::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
	
	if(::IsWindow(dlg_tab_txt_->GetSafeHwnd())){
		dlg_tab_txt_->DestroyWindow();
		dlg_tab_txt_ = NULL;
	}
}
