// Page_Common.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Common.h"
#include "Mgr_Control.h"

#include "Global.h"
#include "DB_View.h"
#include "Mgr_Convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page_Common property page

IMPLEMENT_DYNCREATE(Page_Common, CPropertyPage)

Page_Common::Page_Common() : CPropertyPage(Page_Common::IDD)
{
	//{{AFX_DATA_INIT(Page_Common)
	//}}AFX_DATA_INIT
}

Page_Common::~Page_Common()
{
}

void Page_Common::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Common)
	DDX_Control(pDX, IDC_CHECK_L_COLOR, check_line_color_);
	DDX_Control(pDX, IDC_CHECK_L_TYPE, check_line_type_);
	DDX_Control(pDX, IDC_COMBO_LINE_STYLE, line_type_);
	DDX_Control(pDX, IDC_COMBO_COLOR, color_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Common, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Common)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Common message handlers
void Page_Common::init()
{
	set_combo_line_type(line_type_);
	line_type_.SetCurSel(0);
	color_.init_color();
	color_.SetCurSel(0);

}
void Page_Common::load_info()
{
	set_combo_color(color_,Global::instance()->cur_val().page_common_.color_);
	color_.set_color_index(Global::instance()->cur_val().page_common_.color_-1);
	set_combo_txt(line_type_,Global::instance()->cur_val().page_common_.line_type_.c_str());

	UpdateData(FALSE);
}

BOOL Page_Common::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Page_Common::set_current_val() 
{
	UpdateData();

	int color_index = color_.get_color_index();
	if(check_line_color_.GetCheck())
		Global::instance()->cur_val().page_common_.color_ = color_index;
	CString str;
	line_type_.GetWindowText(str);
	if(check_line_type_.GetCheck())
		Global::instance()->cur_val().page_common_.line_type_ = str;

	Global::instance()->cur_val().page_common_.check_l_color_ = check_line_color_.GetCheck();
	Global::instance()->cur_val().page_common_.check_l_type_ = check_line_type_.GetCheck();
}
void Page_Common::change_properties() 
{
	int color = 0;
	for(int i=0;i<ents_.size();i++){		
		color = Global::instance()->cur_val().page_common_.color_;
		ents_[i]->color_index(color);
		ents_[i]->line_style(Global::instance()->cur_val().page_common_.line_type_.c_str());

	}
}
void Page_Common::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void Page_Common::set_checks(BOOL check)
{
	check_line_color_.SetCheck(check);
	check_line_type_.SetCheck(check);
}

void Page_Common::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
}

void Page_Common::Updata()
{
	load_info();
}