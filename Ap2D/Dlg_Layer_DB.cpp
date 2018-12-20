// Dlg_Layer_DB.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Layer_DB.h"
#include "Mgr_Dxfs.h"

#include "Global.h"
#include "Mgr_Detail.h"
#include "DB_View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Layer_DB dialog


Dlg_Layer_DB::Dlg_Layer_DB(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Layer_DB::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Layer_DB)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Layer_DB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Layer_DB)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Layer_DB, CDialog)
	//{{AFX_MSG_MAP(Dlg_Layer_DB)
	ON_BN_CLICKED(ID_BUT_DOWN_LOAD, OnButDownLoad)
	ON_BN_CLICKED(ID_BUT_SETUP, OnButSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Layer_DB message handlers
void Dlg_Layer_DB::get_select_layers(strings &layers)
{
	layers.clear();
	if(IsDlgButtonChecked(IDC_CHECK_PART_SER))
		layers.push_back(LAYER_PART);
	if(IsDlgButtonChecked(IDC_CHECK_SHEET_SER))
		layers.push_back(LAYER_SHEET);
	if(IsDlgButtonChecked(IDC_CHECK_CUT_SER))
		layers.push_back(LAYER_CUT);
	if(IsDlgButtonChecked(IDC_CHECK_VIEW_SER))
		layers.push_back(LAYER_VIEW);
	if(IsDlgButtonChecked(IDC_CHECK_MARK_SER))
		layers.push_back(LAYER_MARK);
	if(IsDlgButtonChecked(IDC_CHECK_DIM_SER))
		layers.push_back(LAYER_DIM);
	if(IsDlgButtonChecked(IDC_CHECK_APDIM_SER))
		layers.push_back(LAYER_AP_DIM);

}
void Dlg_Layer_DB::OnButDownLoad() 
{
	// TODO: Add your control notification handler code here
	strings layers;
	get_select_layers(layers);
	if(strcmp(Global::instance()->get_cur_detail_name().c_str(), "")==0){
		AfxMessageBox("Please select the detail name.");
		return ;
	}
	std::string key_detail;
	for(int i=0;i<layers.size();i++){
		key_detail = Global::instance()->get_detail_key(Global::instance()->get_cur_detail_name(),layers[i]);
		detail::download(key_detail);
	}
	int d = DB_View::instance()->cur_view()->scene()->database()->entity_size();
	
}

void Dlg_Layer_DB::OnButSetup() 
{
	// TODO: Add your control notification handler code here
	//当前文件层上设置
	if(IsDlgButtonChecked(IDC_CHECK_PART))
		Global::instance()->layer_info().cur_part_ = true;
	else
		Global::instance()->layer_info().cur_part_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_SHEET))
		Global::instance()->layer_info().cur_sheet_ = true;
	else
		Global::instance()->layer_info().cur_sheet_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_CUT))
		Global::instance()->layer_info().cur_cut_ = true;
	else
		Global::instance()->layer_info().cur_cut_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_VIEW))
		Global::instance()->layer_info().cur_view_ = true;
	else
		Global::instance()->layer_info().cur_view_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_MARK))
		Global::instance()->layer_info().cur_mark_ = true;
	else
		Global::instance()->layer_info().cur_mark_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_DIM))
		Global::instance()->layer_info().cur_dim_ = true;
	else
		Global::instance()->layer_info().cur_dim_ = false;
		
	//服务器上设置
	if(IsDlgButtonChecked(IDC_CHECK_PART_SER))
		Global::instance()->layer_info().ser_part_ = true;
	else
		Global::instance()->layer_info().ser_part_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_SHEET_SER))
		Global::instance()->layer_info().ser_sheet_ = true;
	else
		Global::instance()->layer_info().ser_sheet_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_CUT_SER))
		Global::instance()->layer_info().ser_cut_ = true;
	else
		Global::instance()->layer_info().ser_cut_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_VIEW_SER))
		Global::instance()->layer_info().ser_view_ = true;
	else
		Global::instance()->layer_info().ser_view_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_MARK_SER))
		Global::instance()->layer_info().ser_mark_ = true;
	else
		Global::instance()->layer_info().ser_mark_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_DIM_SER))
		Global::instance()->layer_info().ser_dim_ = true;
	else
		Global::instance()->layer_info().ser_dim_ = false;
	if(IsDlgButtonChecked(IDC_CHECK_APDIM_SER))
		Global::instance()->layer_info().ser_ap_dim_ = true;
	else
		Global::instance()->layer_info().ser_ap_dim_ = false;
}
void Dlg_Layer_DB::init_select()
{
	CheckDlgButton(IDC_CHECK_PART, Global::instance()->layer_info().cur_part_);   
	CheckDlgButton(IDC_CHECK_SHEET, Global::instance()->layer_info().cur_sheet_);   
	CheckDlgButton(IDC_CHECK_CUT, Global::instance()->layer_info().cur_cut_);   
	CheckDlgButton(IDC_CHECK_VIEW, Global::instance()->layer_info().cur_view_);
	CheckDlgButton(IDC_CHECK_MARK, Global::instance()->layer_info().cur_mark_);   
	CheckDlgButton(IDC_CHECK_DIM, Global::instance()->layer_info().cur_dim_);
	
	CheckDlgButton(IDC_CHECK_MARK_SER, Global::instance()->layer_info().ser_part_);
	CheckDlgButton(IDC_CHECK_DIM_SER, Global::instance()->layer_info().ser_sheet_);
	CheckDlgButton(IDC_CHECK_APDIM_SER, Global::instance()->layer_info().ser_cut_);
	CheckDlgButton(IDC_CHECK_MARK_SER, Global::instance()->layer_info().ser_view_);
	CheckDlgButton(IDC_CHECK_MARK_SER, Global::instance()->layer_info().ser_mark_);
	CheckDlgButton(IDC_CHECK_DIM_SER, Global::instance()->layer_info().ser_dim_);
	CheckDlgButton(IDC_CHECK_APDIM_SER, Global::instance()->layer_info().ser_ap_dim_);
//	CheckDlgButton()


}
BOOL Dlg_Layer_DB::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	init_select();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
