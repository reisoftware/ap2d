// Page_Dim_Texts.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Dim_Texts.h"
#include "Entity.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"
#include "DB_View.h"
#include "Mgr_Database.h"
#include "Dlg_Dim_Texts_Edit.h"
#include "Paint_Entity_Tools.h"

using namespace dlhml;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page_Dim_Texts property page

IMPLEMENT_DYNCREATE(Page_Dim_Texts, CPropertyPage)

Page_Dim_Texts::Page_Dim_Texts() : CPropertyPage(Page_Dim_Texts::IDD)
{
	//{{AFX_DATA_INIT(Page_Dim_Texts)
	check_ = FALSE;
	//}}AFX_DATA_INIT
}

Page_Dim_Texts::~Page_Dim_Texts()
{
}

void Page_Dim_Texts::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Dim_Texts)
	DDX_Control(pDX, IDC_LIST_NAMES, list_);
	DDX_Check(pDX, IDC_CHECK_NAMES, check_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Dim_Texts, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Dim_Texts)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NAMES, OnDblclkListNames)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NAMES, OnClickListNames)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Dim_Texts message handlers

BOOL Page_Dim_Texts::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	init_list();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//// << init >> //////////////////////////////////////////////////////////////////////
void Page_Dim_Texts::init_list()
{
	init_list_lead();
	init_list_text();
}

void Page_Dim_Texts::init_list_lead()
{
	list_.SetExtendedStyle(list_.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	list_.InsertColumn(0, "text1", LVCFMT_LEFT, 150);
	list_.InsertColumn(1, "text2", LVCFMT_LEFT, 150);
}

void Page_Dim_Texts::init_list_text()
{
	list_.DeleteAllItems();

	std::vector<dlhml::Entity*> ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	if(ents.size() != 1){
		return;
	}
	if(!ents[0]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
		return;
	}

	Ln_Dim_Block& blk = *static_cast<Ln_Dim_Block*>(ents[0]);
	int n=blk.size();
	int i=0;
	for(; i<n; ++i){
		CString str1 = blk[i]->dim_text().c_str();
		CString str2 = blk[i]->dim_text2().c_str();
		list_.InsertItem(i, str1);
		list_.SetItem(i, 1, LVIF_TEXT, str2, 0, 0, 0, 0);
	}
}

void Page_Dim_Texts::reset_entities()
{
	UpdateData();
//	if(!check_){
//		return;
//	}

	std::vector<dlhml::Entity*> ents;
	get_select_ents(DB_View::instance()->cur_view()->scene()->database(),ents);
	if(ents.size() != 1){
		return;
	}
	if(!ents[0]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
		return;
	}

	Ln_Dim_Block& blk = *static_cast<Ln_Dim_Block*>(ents[0]);
	int n=blk.size();
	int c=list_.GetItemCount();
	if(n!=c){
		return;
	}

	int i=0;
	for(; i<n; ++i){
		CString str1 = list_.GetItemText(i, 0);
		CString str2 = list_.GetItemText(i, 1);
		blk[i]->dim_text(str2.GetBuffer(0));
		blk[i]->dim_text2(str2.GetBuffer(0));
		blk[i]->user_content_ = true;
		Paint_Entity_Tools::dim_text_recal(*blk[i]);
	}
}

void Page_Dim_Texts::OnDblclkListNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = list_.GetSelectionMark();
	if(sel<0 || sel>=list_.GetItemCount()){
		return;
	}

	Dlg_Dim_Texts_Edit dlg;
	dlg.txt1_ = list_.GetItemText(sel, 0);
	dlg.txt2_ = list_.GetItemText(sel, 1);

	if(dlg.DoModal() != IDOK){
		return;
	}

	list_.SetItemText(sel, 0, dlg.txt1_);
	list_.SetItemText(sel, 1, dlg.txt2_);
	
	*pResult = 0;
}

void Page_Dim_Texts::OnClickListNames(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
}



void Page_Dim_Texts::OnButApply() 
{
	// TODO: Add your control notification handler code here
	reset_entities();
	DB_View::instance()->cur_view()->scene()->invalidate();
}
