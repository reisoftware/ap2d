// Dlg_Compare_Dxf.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Compare_Dxf.h"

#include "Dxf_Read.h"
#include "DB_View.h"
#include "Mgr_Database.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Compare_Dxf dialog


Dlg_Compare_Dxf::Dlg_Compare_Dxf(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Compare_Dxf::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Compare_Dxf)
	file_0_ = _T("");
	file_1_ = _T("");
	//}}AFX_DATA_INIT
	change_color_ = FALSE;
	ent_count_ = 0;
}


void Dlg_Compare_Dxf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Compare_Dxf)
	DDX_Control(pDX, IDC_CHECK_FILE_1_COLOR, check_file_1_color_);
	DDX_Control(pDX, IDC_CHECK_FILE_0_COLOR, check_file_0_color_);
	DDX_Control(pDX, IDC_COMBO_COLOR_FILE_1, color_file_1_);
	DDX_Control(pDX, IDC_COMBO_COLOR_FILE_0, color_file_0_);
	DDX_Control(pDX, IDC_COMBO_COLOR, color_);
	DDX_Text(pDX, IDC_EDIT_FILE_0, file_0_);
	DDX_Text(pDX, IDC_EDIT_FILE_1, file_1_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Compare_Dxf, CDialog)
	//{{AFX_MSG_MAP(Dlg_Compare_Dxf)
	ON_BN_CLICKED(IDC_RADIO_CHANGE_COLOR, OnRadioChangeColor)
	ON_BN_CLICKED(IDC_RADIO_NO_CHANGE, OnRadioNoChange)
	ON_BN_CLICKED(IDC_BUT_FILE_0, OnButFile0)
	ON_BN_CLICKED(IDC_BUT_FILE_1, OnButFile1)
	ON_BN_CLICKED(ID_BUT_OPEN, OnButOpen)
	ON_BN_CLICKED(IDC_CHECK_FILE_0_COLOR, OnCheckFile0Color)
	ON_BN_CLICKED(IDC_CHECK_FILE_1_COLOR, OnCheckFile1Color)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Compare_Dxf message handlers

void Dlg_Compare_Dxf::OnRadioChangeColor() 
{
	// TODO: Add your control notification handler code here
	change_color_ = TRUE;
	color_.EnableWindow(TRUE);
}

BOOL Dlg_Compare_Dxf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	color_.init_color();
	color_.SetCurSel(0);

	color_.EnableWindow(FALSE);

	color_file_0_.init_color();
	color_file_0_.SetCurSel(0);
	color_file_0_.set_color_index(0);

	color_file_1_.init_color();
	color_file_1_.SetCurSel(2);
	color_file_1_.set_color_index(2);

	check_file_0_color_.SetCheck(TRUE);
	check_file_1_color_.SetCheck(TRUE);

//	GetDlgItem(IDC_RADIO_NO_CHANGE)->
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Compare_Dxf::OnRadioNoChange() 
{
	// TODO: Add your control notification handler code here
	color_.EnableWindow(FALSE);
}

void Dlg_Compare_Dxf::OnOK() 
{
	// TODO: Add extra validation here
	CString strFile,strName;
	static char szFilter[] = "DXF file format(*.dxf) |*.dxf|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open DXF File";
	if(dlg.DoModal()== IDOK){
		strFile=dlg.GetPathName();
		CString path;
		Dxf_Read dxf_read;
		dxf_read.read(strFile.GetBuffer(0),DB_View::instance()->cur_view()->scene());
		CString group;
		group.Format("file_%d",Global::instance()->cur_val().sel_color_prop_.cur_file_num_++);
		change_group_name(dxf_read.ents_ ,group.GetBuffer(0));
		Global::instance()->get_old_ents() = dxf_read.ents_ ;

		if(change_color_){
			change_color(dxf_read.ents_,color_.get_color_index());
		}
		DB_View::instance()->cur_view()->scene()->invalidate();
		DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));

		ent_count_  = DB_View::instance()->cur_view()->scene()->database()->entity_size();
	}
	CDialog::OnOK();
}

void Dlg_Compare_Dxf::OnButFile0() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strName;
	static char szFilter[] = "DXF file format(*.dxf) |*.dxf|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open DXF File";
	if(dlg.DoModal()== IDOK){
		file_0_=dlg.GetPathName();
	}

	UpdateData(FALSE);
	
}

void Dlg_Compare_Dxf::OnButFile1() 
{
	// TODO: Add your control notification handler code here
	CString strFile,strName;
	static char szFilter[] = "DXF file format(*.dxf) |*.dxf|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER|OFN_NOCHANGEDIR, szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open DXF File";
	if(dlg.DoModal()== IDOK){
		file_1_=dlg.GetPathName();
	}
	UpdateData(FALSE);
	
}

void Dlg_Compare_Dxf::OnButOpen() 
{
	// TODO: Add your control notification handler code here

	SetCursor(LoadCursor(NULL,IDC_WAIT));

	UpdateData();
	color_0_ = color_file_0_.get_color_index();
	color_1_ = color_file_1_.get_color_index();
	//第一个文件
	CString group;
	if(file_0_ != ""){
		Dxf_Read dxf_read;
		dxf_read.read(file_0_.GetBuffer(0),DB_View::instance()->cur_view()->scene());
		group.Format("file_%d",Global::instance()->cur_val().sel_color_prop_.cur_file_num_++);
		change_group_name(dxf_read.ents_ ,group.GetBuffer(0));
		Global::instance()->get_old_ents() = dxf_read.ents_ ;

		if(check_file_0_color_.GetCheck()){
			change_color(dxf_read.ents_,color_0_);
		}

	}
	if(file_1_ != ""){
		Dxf_Read dxf_read2;
		dxf_read2.ents_.clear();
		dxf_read2.read(file_1_.GetBuffer(0),DB_View::instance()->cur_view()->scene());
		group.Format("file_%d",Global::instance()->cur_val().sel_color_prop_.cur_file_num_++);
		change_group_name(dxf_read2.ents_ ,group.GetBuffer(0));
		Global::instance()->get_old_ents() = dxf_read2.ents_ ;

		if(check_file_1_color_.GetCheck()){
			change_color(dxf_read2.ents_,color_1_);
		}
	}



	//第二个文件
//	if(file_1_ == "")
//		return;
	DB_View::instance()->cur_view()->scene()->invalidate();
	DB_View::instance()->cur_view()->scene()->middle_button_dblclk(MK_MBUTTON,dlhml::Point(100,100));

	SetCursor(LoadCursor(NULL,IDC_CROSS));

	CDialog::OnOK();
}


void Dlg_Compare_Dxf::OnCheckFile0Color() 
{
	// TODO: Add your control notification handler code here
	color_file_0_.EnableWindow(check_file_0_color_.GetCheck());
	
}

void Dlg_Compare_Dxf::OnCheckFile1Color() 
{
	// TODO: Add your control notification handler code here
	color_file_1_.EnableWindow(check_file_1_color_.GetCheck());
}
