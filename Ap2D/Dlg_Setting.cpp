// Dlg_Setting.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Setting.h"
#include "Global.h"

#include "dir.h"
#include "Mgr_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setting dialog


Dlg_Setting::Dlg_Setting(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Setting::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Setting)
	reduce_scale_ = 0.0;
	reduce_scale_export_ = 0.0;
	m_height_ = _T("");
	m_width_factor_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Setting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Setting)
	DDX_Control(pDX, IDC_LIST_WIDTH_FACTOR, m_lsit_font_db);
	DDX_Control(pDX, IDC_CHECK_RIGHT_MENU_SHOW, check_show_right_menu_);
	DDX_Text(pDX, IDC_EDIT_TEXT_SCALE, reduce_scale_);
	DDX_Text(pDX, IDC_EDIT_TEXT_SCALE_EXPORT, reduce_scale_export_);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height_);
	DDX_Text(pDX, IDC_EDIT_WIDTH_FACTOR, m_width_factor_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Setting, CDialog)
	//{{AFX_MSG_MAP(Dlg_Setting)
	ON_BN_CLICKED(IDC_CHECK_RIGHT_MENU_SHOW, OnCheckRightMenuShow)
	ON_BN_CLICKED(IDC_BUT_ADD, OnButAdd)
	ON_BN_CLICKED(IDC_BUT_EDIT, OnButEdit)
	ON_BN_CLICKED(IDC_BUT_DEL, OnButDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setting message handlers

void Dlg_Setting::OnCheckRightMenuShow() 
{
	// TODO: Add your control notification handler code here
	Global::instance()->setting().show_right_menu_ = check_show_right_menu_.GetCheck();
}

BOOL Dlg_Setting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	check_show_right_menu_.SetCheck(Global::instance()->setting().show_right_menu_);
	reduce_scale_ = Global::instance()->setting().reduce_scale_;
	reduce_scale_export_ = Global::instance()->setting().reduce_scale_export_;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Setting::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	std::string ini_file = exe_path()+"setting.ini";
	CString str;
	
	int check = check_show_right_menu_.GetCheck();
	Global::instance()->setting().show_right_menu_ = check;
	str.Format("%i",check);
	write(ini_file.c_str(), "show_right_menu","show_right_menu", str);
	str.Format("%f",reduce_scale_);
	Global::instance()->setting().reduce_scale_ = reduce_scale_;
	write(ini_file.c_str(), "reduce_scale","reduce_scale", str.GetBuffer(0));
	str.Format("%f",reduce_scale_export_);
	Global::instance()->setting().reduce_scale_export_ = reduce_scale_export_;
	write(ini_file.c_str(), "reduce_scale_export","reduce_scale_export", str.GetBuffer(0));

	
	CDialog::OnOK();
}

void Dlg_Setting::OnButAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void Dlg_Setting::OnButEdit() 
{
	// TODO: Add your control notification handler code here
	
}

void Dlg_Setting::OnButDel() 
{
	// TODO: Add your control notification handler code here
	
}
