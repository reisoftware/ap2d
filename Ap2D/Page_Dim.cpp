// Page_Dim.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Dim.h"

#include "Mgr_Control.h"
#include "Global.h"
#include "DB_View.h"
#include "Dimension.h"
#include "Dimension_Style.h"
#include "Mgr_Convert.h"
#include "Ln_Dim_Block.h"
#include "Paint_Entity_Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dlhml;
/////////////////////////////////////////////////////////////////////////////
// Page_Dim property page

IMPLEMENT_DYNCREATE(Page_Dim, CPropertyPage)

Page_Dim::Page_Dim() : CPropertyPage(Page_Dim::IDD)
{
	//{{AFX_DATA_INIT(Page_Dim)
	end_dim_len_ = 0.0;
	end_offset_ = 0.0;
	start_dim_len_ = 0.0;
	start_offset_ = 0.0;
	//}}AFX_DATA_INIT
}

Page_Dim::~Page_Dim()
{
}

void Page_Dim::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Dim)
	DDX_Control(pDX, IDC_CHECK_START_OFFSET, check_start_offset_);
	DDX_Control(pDX, IDC_CHECK_START_DIM_LENGTH, check_start_dim_len_);
	DDX_Control(pDX, IDC_CHECK_END_OFFSET, check_end_offset_);
	DDX_Control(pDX, IDC_CHECK_END_DIM_LENGTH, check_end_dim_len_);
	DDX_Control(pDX, IDC_CHECK_DIM_KIND, check_dim_kind_);
	DDX_Control(pDX, IDC_COMBO_DIM_KIND, dim_kind_);
	DDX_Text(pDX, IDC_EDIT_END_DIM_LEN, end_dim_len_);
	DDX_Text(pDX, IDC_EDIT_END_OFFSET, end_offset_);
	DDX_Text(pDX, IDC_EDIT_START_DIM_LEN, start_dim_len_);
	DDX_Text(pDX, IDC_EDIT_START_OFFSET, start_offset_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Dim, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Dim)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Dim message handlers
void Page_Dim::init()
{
	set_combo_dim_kind(dim_kind_);
	dim_kind_.SetCurSel(0);

}

BOOL Page_Dim::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Page_Dim::set_checks(BOOL check)
{
	check_start_offset_.SetCheck(check);
	check_start_dim_len_.SetCheck(check);
	check_end_offset_.SetCheck(check);
	check_end_dim_len_.SetCheck(check);
	check_dim_kind_.SetCheck(check);
}


void Page_Dim::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
}
void Page_Dim::load_info()
{
	std::string s = Global::instance()->cur_val().page_dim_.dim_kind_;

	set_combo_txt(dim_kind_,Global::instance()->cur_val().page_dim_.dim_kind_.c_str());


	start_offset_ = Global::instance()->cur_val().page_dim_.start_offset_;
	end_offset_ = Global::instance()->cur_val().page_dim_.end_offset_;
	start_dim_len_ = Global::instance()->cur_val().page_dim_.start_dim_len_;
	end_dim_len_ = Global::instance()->cur_val().page_dim_.end_dim_len_;

	UpdateData(FALSE);
}

void Page_Dim::set_current_val() 
{
	UpdateData();
	CString str;
	dim_kind_.GetWindowText(str);
	if(check_dim_kind_.GetCheck())
		Global::instance()->cur_val().page_dim_.dim_kind_= str;
	if(check_start_offset_.GetCheck())
		Global::instance()->cur_val().page_dim_.start_offset_= start_offset_;
	if(check_end_offset_.GetCheck())
		Global::instance()->cur_val().page_dim_.end_offset_= end_offset_;
	if(check_start_dim_len_.GetCheck())
		Global::instance()->cur_val().page_dim_.start_dim_len_= start_dim_len_;
	if(check_end_dim_len_.GetCheck())
		Global::instance()->cur_val().page_dim_.end_dim_len_= end_dim_len_;


	Global::instance()->cur_val().page_dim_.check_dim_kind_ = check_dim_kind_.GetCheck();
	Global::instance()->cur_val().page_dim_.check_start_offset_ = check_start_offset_.GetCheck();
	Global::instance()->cur_val().page_dim_.check_end_offset_ = check_end_offset_.GetCheck();
	Global::instance()->cur_val().page_dim_.check_start_dim_len_ = check_start_dim_len_.GetCheck();
	Global::instance()->cur_val().page_dim_.check_end_dim_len_ = check_end_dim_len_.GetCheck();
	
}


void Page_Dim::change_properties() 
{
	dlhml::Dimension *dim = NULL;
	dlhml::Dimension_Style dim_style;
	for(int i=0;i<ents_.size();i++){

		if(ents_[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
			dlhml::Ln_Dim_Block *v = (dlhml::Ln_Dim_Block *)ents_[i];
			CString dim_kind = Global::instance()->cur_val().page_dim_.dim_kind_.c_str();
			if(dim_kind == "Base Line Dim")
				v->mode(dlhml::PILEUP_DIM);	
			else if(dim_kind == "Continue Line Dim")
				v->mode(dlhml::CLOSED_DIM);	
			else
				v->mode(dlhml::PILEUP_DIM);	

			create_dim_style(dim_style);
			v->set_dim_style(dim_style);
			dlhml::Paint_Entity_Tools::recal_dim_block(*v);
		}else{
			dim = (dlhml::Dimension *)ents_[i];
			dim_style = dim->dim_style_val();
			dim_style.start_dim_length(Global::instance()->cur_val().page_dim_.start_dim_len_);
			dim_style.end_dim_length(Global::instance()->cur_val().page_dim_.end_dim_len_);
			dim_style.extend_end_off(Global::instance()->cur_val().page_dim_.end_offset_);
			dim_style.extend_start_off(Global::instance()->cur_val().page_dim_.start_offset_);

			dim->dim_style_val(dim_style);
		}
		
	}
	
}
void Page_Dim::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();
}


void Page_Dim::Updata()
{
	load_info();
}
