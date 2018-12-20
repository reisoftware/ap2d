// Page_Text.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Text.h"

#include "Mgr_Control.h"
#include "Global.h"
#include "DB_View.h"
#include "Dimension.h"
#include "Dimension_Style.h"
#include "Mgr_Convert.h"
#include "Ln_Dim_Block.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Paint_Entity_Tools.h"


using namespace dlhml;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page_Text property page

IMPLEMENT_DYNCREATE(Page_Text, CPropertyPage)

Page_Text::Page_Text() : CPropertyPage(Page_Text::IDD)
{
	//{{AFX_DATA_INIT(Page_Text)
	angle_ = 0.0;
	height_ = 0.0;
	content_ = _T("");
	precision_ = 0;
	//}}AFX_DATA_INIT
	select_all_ = FALSE;
}

Page_Text::~Page_Text()
{
}

void Page_Text::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Text)
	DDX_Control(pDX, IDC_CHECK_PRECISION, check_precision_);
	DDX_Control(pDX, IDC_COMBO_FRAME_OUT, frame_out_);
	DDX_Control(pDX, IDC_CHECK_TEXT_HIGHT, check_text_height_);
	DDX_Control(pDX, IDC_CHECK_TEXT_COLOR, check_text_color_);
	DDX_Control(pDX, IDC_CHECK_TEXT_ANGLE, check_text_angle_);
	DDX_Control(pDX, IDC_CHECK_TEXT, check_text_);
	DDX_Control(pDX, IDC_CHECK_OUT_FRAME, check_out_frame_);
	DDX_Control(pDX, IDC_CHECK_FRAME_KIND, check_frame_kind_);
	DDX_Control(pDX, IDC_CHECK_FRAME_COLOR, check_frame_color_);
	DDX_Control(pDX, IDC_CHECK_ARROW_POS, check_arrow_pos_);
	DDX_Control(pDX, IDC_COMBO_TEXT_POS, text_pos_);
	DDX_Control(pDX, IDC_COMBO_FRAME_KIND, frame_kind_);
	DDX_Control(pDX, IDC_COMBO_FRAME_COLOR, frame_color_);
	DDX_Control(pDX, IDC_COMBO_COLOR, text_color_);
	DDX_Text(pDX, IDC_EDIT_ANGLE, angle_);
	DDX_Text(pDX, IDC_EDIT_HIGHT, height_);
	DDX_Text(pDX, IDC_EDIT_TEXT, content_);
	DDX_Text(pDX, IDC_EDIT_PRECISION, precision_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Text, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Text)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Text message handlers
void Page_Text::init()
{
	frame_color_.init_color();
	frame_color_.SetCurSel(0);
	text_color_.init_color();
	text_color_.SetCurSel(0);

	set_combo_frame_kind(frame_kind_);
	frame_kind_.SetCurSel(0);
	set_combo_text_pos(text_pos_);
	text_pos_.SetCurSel(0);

	

}
void Page_Text::load_info()
{
	angle_ = 	Global::instance()->cur_val().page_text_.angle_ * 180.0/3.1415926;

	set_combo_color(text_color_,Global::instance()->cur_val().page_text_.color_);

	text_color_.set_color_index(Global::instance()->cur_val().page_text_.color_-1);

	content_ = 	Global::instance()->cur_val().page_text_.content_.c_str();

	height_ = Global::instance()->cur_val().page_text_.hight_;
	precision_ = Global::instance()->cur_val().page_text_.precision_;

	set_combo_txt(text_pos_,Global::instance()->cur_val().page_text_.text_pos_.c_str());

	set_combo_color(frame_color_,Global::instance()->cur_val().page_text_.frame_color_);
	frame_color_.set_color_index(Global::instance()->cur_val().page_text_.color_-1);

	set_combo_txt(frame_kind_,Global::instance()->cur_val().page_text_.frame_kind_.c_str());
	set_combo_txt(frame_out_,Global::instance()->cur_val().page_text_.frame_out_.c_str());
	
	UpdateData(FALSE);
}

BOOL Page_Text::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Page_Text::set_current_val() 
{
	UpdateData();
	CString str;
	if(check_text_angle_.GetCheck())
		Global::instance()->cur_val().page_text_.angle_= angle_;
	
	int color_index = text_color_.get_color_index();
	if(check_text_color_.GetCheck())
		Global::instance()->cur_val().page_text_.color_= color_index;
	if(check_text_.GetCheck())
		Global::instance()->cur_val().page_text_.content_= content_;

	if(check_text_height_.GetCheck())
		Global::instance()->cur_val().page_text_.hight_= height_;

	text_pos_.GetWindowText(str);
	if(check_out_frame_.GetCheck())
		Global::instance()->cur_val().page_text_.text_pos_= str;
	
	color_index = frame_color_.get_color_index();
	if(check_frame_color_.GetCheck()){
		Global::instance()->cur_val().page_text_.frame_color_= color_index;
	}

	frame_out_.GetWindowText(str);
	if(check_out_frame_.GetCheck())
		Global::instance()->cur_val().page_text_.frame_out_= str;


	frame_kind_.GetWindowText(str);
	if(check_frame_kind_.GetCheck())
		Global::instance()->cur_val().page_text_.frame_kind_= str;

	if(check_precision_.GetCheck())
		Global::instance()->cur_val().page_text_.precision_= precision_;

	
	Global::instance()->cur_val().page_text_.check_angle_ = check_text_angle_.GetCheck();
	Global::instance()->cur_val().page_text_.check_color_ = check_text_color_.GetCheck();
	Global::instance()->cur_val().page_text_.check_content_ = check_text_.GetCheck();
	Global::instance()->cur_val().page_text_.check_frame_color_ = check_frame_color_.GetCheck();
	Global::instance()->cur_val().page_text_.check_frame_kind_ = check_frame_kind_.GetCheck();
	Global::instance()->cur_val().page_text_.check_frame_out_ = check_out_frame_.GetCheck();
	Global::instance()->cur_val().page_text_.check_hight_ = check_text_height_.GetCheck();
	Global::instance()->cur_val().page_text_.check_precision_ = check_precision_.GetCheck();

}
void Page_Text::change_properties() 
{
	dlhml::Dimension *dim = NULL;
	dlhml::Dimension_Style dim_style;
	for(int i=0;i<ents_.size();i++){

		if(ents_[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))){
			dlhml::Ln_Dim_Block *v = (dlhml::Ln_Dim_Block *)ents_[i];
			create_dim_style(dim_style);
			v->set_dim_style(dim_style);
			dlhml::Paint_Entity_Tools::recal_dim_block(*v);

		}else{
			dim = (dlhml::Dimension *)ents_[i];
			dim->dim_text(Global::instance()->cur_val().page_text_.content_.c_str());
			dim_style = dim->dim_style_val();

			dim_style.text_height(Global::instance()->cur_val().page_text_.hight_);
			dim_style.text_color(Global::instance()->cur_val().page_text_.color_);

			dim->text_rotation(Global::instance()->cur_val().page_text_.angle_*3.1415926/180);
			dim_style.text_precision(Global::instance()->cur_val().page_text_.precision_);

			dim_style.txt_frame(get_txt_frame(Global::instance()->cur_val().page_text_.frame_kind_.c_str()));
			if(check_frame_color_.GetCheck()){
				dim_style.line_color(Global::instance()->cur_val().page_text_.frame_color_);
				dim_style.text_frame_color(Global::instance()->cur_val().page_text_.frame_color_);
			}
			dim->dim_style_val(dim_style);
		}
		
	}
	
	
}
void Page_Text::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void Page_Text::set_checks(BOOL check)
{
	check_text_height_.SetCheck(check);
	check_text_color_.SetCheck(check);
	check_text_angle_.SetCheck(check);
	check_text_.SetCheck(check);
	check_out_frame_.SetCheck(check);
	check_frame_kind_.SetCheck(check);
	check_frame_color_.SetCheck(check);
	check_arrow_pos_.SetCheck(check);
	check_precision_.SetCheck(check);
}

void Page_Text::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
}


void Page_Text::Updata()
{
	load_info();
}

