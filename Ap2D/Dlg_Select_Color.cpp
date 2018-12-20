// Dlg_Select_Color.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Select_Color.h"
#include "Global.h"
#include "Mgr_Control.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Color dialog


Dlg_Select_Color::Dlg_Select_Color(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Select_Color::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Select_Color)
	check_color_ = FALSE;
	include_cur_txt_ = FALSE;
	one_postfix_ = _T("");
	one_prefix_ = _T("");
	two_postfix_ = _T("");
	two_prefix_ = _T("");
	cur_txt_val_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Select_Color::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Select_Color)
	DDX_Control(pDX, IDC_COMBO_COLOR_ERROR, error_color_);
	DDX_Control(pDX, IDC_COMBO_COLOR_NO2, color_no2_);
	DDX_Control(pDX, IDC_COMBO_COLOR, color_);
	DDX_Check(pDX, IDC_CHECK_RECORD, check_color_);
	DDX_Check(pDX, IDC_CHECK_INCLUDE_CURRENT, include_cur_txt_);
	DDX_Text(pDX, IDC_EDIT_ONE_POSTFIX, one_postfix_);
	DDX_Text(pDX, IDC_EDIT_ONE_PREFIX, one_prefix_);
	DDX_Text(pDX, IDC_EDIT_TWO_POSTFIX, two_postfix_);
	DDX_Text(pDX, IDC_EDIT_TWO_PREFIX, two_prefix_);
	DDX_Text(pDX, IDC_EDIT_CURRENT_TXT_VAL, cur_txt_val_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Select_Color, CDialog)
	//{{AFX_MSG_MAP(Dlg_Select_Color)
	ON_BN_CLICKED(ID_BUT_SEL_COLOR, OnButSelColor)
	ON_BN_CLICKED(IDC_CHECK_RECORD, OnCheckRecord)
	ON_BN_CLICKED(IDC_CHECK_INCLUDE_CURRENT, OnCheckIncludeCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Select_Color message handlers
int Dlg_Select_Color::get_color()
{
	return color_.get_color_index();

}
int Dlg_Select_Color::get_error_color()
{
	return error_color_.get_color_index();

}
int Dlg_Select_Color::get_color_no2()
{
	return color_no2_.get_color_index();

}

BOOL Dlg_Select_Color::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	color_.init_color();
	color_.SetCurSel(1);

	error_color_.init_color();
	error_color_.SetCurSel(2);

	color_no2_.init_color();
	color_no2_.SetCurSel(3);

	set_combo_color(color_,Global::instance()->cur_val().sel_color_prop_.cur_color_one_);
	set_combo_color(color_no2_,Global::instance()->cur_val().sel_color_prop_.cur_color_two_);
	set_combo_color(error_color_,Global::instance()->cur_val().sel_color_prop_.cur_color_error_);
	UpdateData(FALSE);
	
	
	check_color_ = Global::instance()->cur_val().sel_color_prop_.is_rember_color_ ;

	cur_txt_val_ = Global::instance()->cur_val().sel_color_prop_.cur_txt_val_.c_str();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Select_Color::OnButSelColor() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Global::instance()->cur_val().sel_color_prop_.cur_color_one_ = color_.get_color_index();
	Global::instance()->cur_val().sel_color_prop_.cur_color_two_ = color_no2_.get_color_index();
	Global::instance()->cur_val().sel_color_prop_.cur_color_error_ = error_color_.get_color_index();

	int jj = error_color_.get_color_index();
	Global::instance()->cur_val().sel_color_prop_.one_postfix_ = one_postfix_;
	Global::instance()->cur_val().sel_color_prop_.one_prefix_ = one_prefix_;

	Global::instance()->cur_val().sel_color_prop_.two_postfix_ = two_postfix_;
	Global::instance()->cur_val().sel_color_prop_.two_prefix_ = two_prefix_;

	Global::instance()->cur_val().sel_color_prop_.cur_txt_val_ = cur_txt_val_;

	CDialog::OnOK();
}

void Dlg_Select_Color::OnCheckRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Global::instance()->cur_val().sel_color_prop_.is_rember_color_ = check_color_;
}

void Dlg_Select_Color::OnCheckIncludeCurrent() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Global::instance()->cur_val().sel_color_prop_.include_cur_txt_ = include_cur_txt_;
	
}
