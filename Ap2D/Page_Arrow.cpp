// Page_Arrow.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Arrow.h"

#include "Mgr_Control.h"
#include "Global.h"
#include "Line_Arrow.h"
#include "Arc_Arrow.h"

#include "Mgr_Convert.h"
#include "DB_View.h"
#include "Ln_Dim_Block.h"
#include "Paint_Entity_Tools.h"

using namespace dlhml;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page_Arrow property page

IMPLEMENT_DYNCREATE(Page_Arrow, CPropertyPage)

Page_Arrow::Page_Arrow() : CPropertyPage(Page_Arrow::IDD)
{
	//{{AFX_DATA_INIT(Page_Arrow)
	arrow_level_ = 0.0;
	//}}AFX_DATA_INIT
}

Page_Arrow::~Page_Arrow()
{
}

void Page_Arrow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Arrow)
	DDX_Control(pDX, IDC_COMBO_ARROW_NUM, arrow_num_);
	DDX_Control(pDX, IDC_CHECK_ARROW_NUM, check_arrow_num_);
	DDX_Control(pDX, IDC_CHECK_ARROW_POS, check_arrow_pos_);
	DDX_Control(pDX, IDC_CHECK_ARROW_LEVEL, check_arrow_level_);
	DDX_Control(pDX, IDC_CHECK_ARROW_KIND, check_arrow_kind_);
	DDX_Control(pDX, IDC_COMBO_ARROW_KIND, arrow_style_);
	DDX_Control(pDX, IDC_COMBO_ARROW_POS, arrow_pos_);
	DDX_Text(pDX, IDC_EDIT_ARROW_LEVEL, arrow_level_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Arrow, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Arrow)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Arrow message handlers

void Page_Arrow::init()
{
	set_combo_arrow_pos(arrow_pos_);
	set_combo_arrow_style(arrow_style_);
	set_combo_arrow_num(arrow_num_);
	arrow_pos_.SetCurSel(0);
	arrow_style_.SetCurSel(0);
	arrow_num_.SetCurSel(0);
}
void Page_Arrow::load_info()
{
	set_combo_txt(arrow_pos_,Global::instance()->cur_val().page_arrow_.arrow_pos_.c_str());
	set_combo_txt(arrow_style_,Global::instance()->cur_val().page_arrow_.arrow_style_.c_str());
	set_combo_txt(arrow_num_,Global::instance()->cur_val().page_arrow_.arrow_num_.c_str());
	
	arrow_level_ = Global::instance()->cur_val().page_arrow_.arrow_level_;

	UpdateData(FALSE);
}
BOOL Page_Arrow::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Page_Arrow::set_current_val() 
{
	UpdateData();
	CString temp;
	arrow_pos_.GetWindowText(temp);
	if(check_arrow_pos_.GetCheck())
		Global::instance()->cur_val().page_arrow_.arrow_pos_ = temp;

	arrow_style_.GetWindowText(temp);
	if(check_arrow_kind_.GetCheck())
		Global::instance()->cur_val().page_arrow_.arrow_style_ = temp;

	if(check_arrow_level_.GetCheck()){
		Global::instance()->cur_val().page_arrow_.arrow_level_ = arrow_level_;
		Global::instance()->cur_val().page_arrow_.arrow_hight_ = arrow_level_;
		}
	arrow_num_.GetWindowText(temp);
	if(check_arrow_num_.GetCheck())
		Global::instance()->cur_val().page_arrow_.arrow_num_ = temp;
	


	Global::instance()->cur_val().page_arrow_.check_arrow_kind_ = check_arrow_kind_.GetCheck();
	Global::instance()->cur_val().page_arrow_.check_arrow_level_ = check_arrow_level_.GetCheck();
	Global::instance()->cur_val().page_arrow_.check_arrow_pos_ = check_arrow_pos_.GetCheck();
	Global::instance()->cur_val().page_arrow_.check_arrow_num_ = check_arrow_num_.GetCheck();




}
void Page_Arrow::change_properties() 
{
	dlhml::Dimension *dim = NULL;
	dlhml::Dimension_Style dim_style;
	for(int i=0;i<ents_.size();i++){
		if(ents_[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
			dlhml::Ln_Dim_Block *v = (dlhml::Ln_Dim_Block *)ents_[i];
		//	v->lead_dim();
			create_dim_style(dim_style);
			v->set_dim_style(dim_style);
			dlhml::Paint_Entity_Tools::recal_dim_block(*v);

		}else {
		dim = (dlhml::Dimension *)ents_[i];
		dim_style = dim->dim_style_val();

		dim_style.arrow_size(Global::instance()->cur_val().page_arrow_.arrow_hight_);
		dim_style.arrow_style(get_arrow_style_by_name(Global::instance()->cur_val().page_arrow_.arrow_style_.c_str()));
		dim_style.arrow_num(atoi(Global::instance()->cur_val().page_arrow_.arrow_num_.c_str()));
		dim->dim_style_val(dim_style);	
		}
	}
}
void Page_Arrow::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();
}


void Page_Arrow::set_checks(BOOL check)
{
	check_arrow_pos_.SetCheck(check);
	check_arrow_level_.SetCheck(check);
	check_arrow_kind_.SetCheck(check);
	check_arrow_num_.SetCheck(check);
}

void Page_Arrow::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
}


void Page_Arrow::Updata()
{
	load_info();
}