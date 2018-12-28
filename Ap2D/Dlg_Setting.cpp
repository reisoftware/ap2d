// Dlg_Setting.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Setting.h"
#include "Global.h"

#include "dir.h"
#include "Mgr_File.h"
#include "DB_Font_Width_Factor.h"

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
	ON_NOTIFY(NM_CLICK, IDC_LIST_WIDTH_FACTOR, OnClickListWidthFactor)
	ON_BN_CLICKED(IDC_BUT_SAVE, OnButSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setting message handlers

void Dlg_Setting::OnCheckRightMenuShow() 
{
	// TODO: Add your control notification handler code here
	Global::instance()->setting().show_right_menu_ = check_show_right_menu_.GetCheck();
}
void Dlg_Setting::set_list_prop(CListCtrl &list_ctrl) 
{
	LONG lStyle;
	lStyle = GetWindowLong(list_ctrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(list_ctrl.m_hWnd, GWL_STYLE, lStyle);//设置style 
	DWORD dwStyle = list_ctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	list_ctrl.SetExtendedStyle(dwStyle); //设置扩展风格
}

void Dlg_Setting::init_list_font_db() 
{

	set_list_prop(m_lsit_font_db);
	m_lsit_font_db.InsertColumn( 1, "Height",LVCFMT_LEFT,100);//插入列
	m_lsit_font_db.InsertColumn( 2, "Width Factor",LVCFMT_LEFT,150);//插入列


}
BOOL Dlg_Setting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	init_list_font_db();
	DB_Font_Width_Factor::instance()->show(m_lsit_font_db);

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
	UpdateData();
	CString wf = DB_Font_Width_Factor::instance()->find(m_height_);
	if(wf != "-1")
	{
		m_width_factor_ = wf;
		UpdateData(FALSE);
	}else
	{
		DB_Font_Width_Factor::instance()->add(m_height_,m_width_factor_);
		int pos = m_lsit_font_db.GetItemCount();
		m_lsit_font_db.InsertItem(pos,"");
		m_lsit_font_db.SetItemText(pos, 0,m_height_);
		m_lsit_font_db.SetItemText(pos, 1,m_width_factor_);

	}


	
}

void Dlg_Setting::OnButEdit() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	POSITION pos  = m_lsit_font_db.GetFirstSelectedItemPosition();
	int nItem = m_lsit_font_db.GetNextSelectedItem(pos);
	if ( nItem >= 0 )
	{
		DB_Font_Width_Factor::instance()->edit(m_height_,m_width_factor_);
		//修改list中的值	
		m_lsit_font_db.SetItemText(nItem, 0,m_height_);
		m_lsit_font_db.SetItemText(nItem, 1,m_width_factor_);

	}
}

void Dlg_Setting::OnButDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	POSITION pos  = m_lsit_font_db.GetFirstSelectedItemPosition();
	int nItem = m_lsit_font_db.GetNextSelectedItem(pos);
	if ( nItem >= 0 )
	{
		DB_Font_Width_Factor::instance()->del(m_height_);
		m_lsit_font_db.DeleteItem(nItem);
	}	
	
}

void Dlg_Setting::OnClickListWidthFactor(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_lsit_font_db.GetFirstSelectedItemPosition();
	if (pos == NULL){
	  // AfxMessageBox("No items were selected!\n");
		m_height_ = "0.0";
		m_width_factor_ = "0.0";
		UpdateData(FALSE);

	}
	else
	{	
		int nItem = m_lsit_font_db.GetNextSelectedItem(pos);		
		CString height = m_lsit_font_db .GetItemText(nItem,0);
		m_height_ = height;
		CString wf = m_lsit_font_db .GetItemText(nItem,1);
		m_width_factor_ = wf;
		UpdateData(FALSE);
	}	
	*pResult = 0;
}

void Dlg_Setting::OnButSave() 
{
	// TODO: Add your control notification handler code here
		DB_Font_Width_Factor::instance()->save();
}
