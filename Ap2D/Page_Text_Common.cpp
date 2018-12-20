// Page_Text_Common.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Page_Text_Common.h"

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dlhml;
/////////////////////////////////////////////////////////////////////////////
// Page_Text_Common property page

IMPLEMENT_DYNCREATE(Page_Text_Common, CPropertyPage)

Page_Text_Common::Page_Text_Common() : CPropertyPage(Page_Text_Common::IDD)
{
	//{{AFX_DATA_INIT(Page_Text_Common)
	content_ = _T("");
	precision_ = 0.0;
	height_ = 0.0;
	angle_ = 0.0;
	width_factor_ = 0.0;
	//}}AFX_DATA_INIT
}

Page_Text_Common::~Page_Text_Common()
{
}

void Page_Text_Common::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Text_Common)
	DDX_Control(pDX, IDC_CHECK_WIDTH_FACTOR, check_width_factor_);
	DDX_Control(pDX, IDC_CHECK_TEXT_HIGHT, check_text_hight_);
	DDX_Control(pDX, IDC_CHECK_TEXT_COLOR, check_text_color_);
	DDX_Control(pDX, IDC_CHECK_TEXT_ANGLE, check_text_angle_);
	DDX_Control(pDX, IDC_CHECK_TEXT, check_text_);
	DDX_Control(pDX, IDC_CHECK_PRECISION, check_precision_);
	DDX_Control(pDX, IDC_CHECK_FONT_STYLE, check_font_style_);
	DDX_Control(pDX, IDC_CHECK_ARROW_POS, check_arrow_pos_);
	DDX_Control(pDX, IDC_COMBO_FONT_STYLE, font_style_);
	DDX_Control(pDX, IDC_COMBO_TEXT_POS, text_pos_);
	DDX_Control(pDX, IDC_COMBO_COLOR, text_color_);
	DDX_Text(pDX, IDC_EDIT_TEXT, content_);
	DDX_Text(pDX, IDC_EDIT_PRECISION, precision_);
	DDX_Text(pDX, IDC_EDIT_HIGHT, height_);
	DDX_Text(pDX, IDC_EDIT_ANGLE, angle_);
	DDX_Text(pDX, IDC_EDIT_WIDTH_FACTOR, width_factor_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Text_Common, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Text_Common)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Text_Common message handlers
void Page_Text_Common::set_checks(BOOL check)
{
	check_text_hight_.SetCheck(check);
	check_text_color_.SetCheck(check);
	check_text_angle_.SetCheck(check);
	check_text_.SetCheck(check);
	check_arrow_pos_.SetCheck(check);
	check_precision_.SetCheck(check);

	check_font_style_.SetCheck(check);
	check_width_factor_.SetCheck(check);

}


INT CALLBACK NEnumFontNameProc(LOGFONT *plf, TEXTMETRIC* /*ptm*/, INT /*nFontType*/, LPARAM lParam)
{
 CComboBox* comboBox = (CComboBox*) lParam;
 
 comboBox->AddString(plf->lfFaceName);
 
 return TRUE;
}

void Page_Text_Common::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();	
}
void Page_Text_Common::init()
{
	text_color_.init_color();
	text_color_.SetCurSel(0);

	set_combo_text_pos(text_pos_);
	text_pos_.SetCurSel(0);

	font_style_.AddString("Standard");
	font_style_.AddString("Arial");
	font_style_.AddString("dim.shx");

	 ::EnumFontFamilies(GetDC()->m_hDC, (LPTSTR) NULL, (FONTENUMPROC)NEnumFontNameProc, (LPARAM)&(font_style_));
    int nCount = font_style_.GetCount();
    if (nCount > 0)
        font_style_.SetCurSel(nCount-5);
    else
        font_style_.SetCurSel(0);





	

}
void Page_Text_Common::load_info()
{
	angle_ = 	Global::instance()->cur_val().page_text_common_.angle_ * 180.0/3.1415926;

	set_combo_color(text_color_,Global::instance()->cur_val().page_text_common_.color_);

	text_color_.set_color_index(Global::instance()->cur_val().page_text_common_.color_-1);

	content_ = 	Global::instance()->cur_val().page_text_common_.content_.c_str();

	height_ = Global::instance()->cur_val().page_text_common_.hight_;
	precision_ = Global::instance()->cur_val().page_text_common_.precision_;

	set_combo_txt(text_pos_,Global::instance()->cur_val().page_text_common_.text_pos_.c_str());


	font_style_.SetWindowText(Global::instance()->cur_val().page_text_common_.font_style_.c_str());
//	set_combo_txt(font_style_,Global::instance()->cur_val().page_text_common_.font_style_.c_str());
	width_factor_ = Global::instance()->cur_val().page_text_common_.width_factor_;

	
	UpdateData(FALSE);
}

BOOL Page_Text_Common::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Page_Text_Common::set_current_val() 
{
	UpdateData();
	CString str;
	if(check_text_.GetCheck())
		Global::instance()->cur_val().page_text_common_.content_= content_;

	if(check_text_angle_.GetCheck())
		Global::instance()->cur_val().page_text_common_.angle_= angle_;
	
	int color_index = text_color_.get_color_index();
	if(check_text_color_.GetCheck())
		Global::instance()->cur_val().page_text_common_.color_= color_index;
	if(check_text_.GetCheck())
		Global::instance()->cur_val().page_text_common_.content_= content_;

	if(check_text_hight_.GetCheck())
		Global::instance()->cur_val().page_text_common_.hight_= height_;


	if(check_precision_.GetCheck())
		Global::instance()->cur_val().page_text_common_.precision_= precision_;

	if(check_width_factor_.GetCheck())
		Global::instance()->cur_val().page_text_common_.width_factor_= width_factor_;
	
	font_style_.GetWindowText(str);
	if(check_font_style_.GetCheck())
		Global::instance()->cur_val().page_text_common_.font_style_= str;
	
	Global::instance()->cur_val().page_text_common_.check_angle_ = check_text_angle_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_color_ = check_text_color_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_content_ = check_text_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_hight_ = check_text_hight_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_precision_ = check_precision_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_font_style_ = check_font_style_.GetCheck();
	Global::instance()->cur_val().page_text_common_.check_width_factor_ = check_width_factor_.GetCheck();

}
void Page_Text_Common::change_properties() 
{
	dlhml::Dimension *dim = NULL;
	dlhml::Dimension_Style dim_style;
	for(int i=0;i<ents_.size();i++){

		if(ents_[i]->isa(MY_RUNTIME_CLASS(Text))){
			Text *txt = (Text *)ents_[i];
			if(check_text_.GetCheck())
				txt->text(Global::instance()->cur_val().page_text_common_.content_);
			if(check_text_angle_.GetCheck())
				txt->rotation(Global::instance()->cur_val().page_text_common_.angle_);
			
			int color_index = text_color_.get_color_index();
			if(check_text_color_.GetCheck())
				txt->color_index(color_index);

			if(check_text_hight_.GetCheck())
				txt->dxf_height(Global::instance()->cur_val().page_text_common_.hight_);
			

		//	if(check_precision_.GetCheck())
		//		txt->(Global::instance()->cur_val().page_text_common_.precision_);

			if(check_width_factor_.GetCheck())
				txt->width_factor(Global::instance()->cur_val().page_text_common_.width_factor_);

			CString str;
			font_style_.GetWindowText(str);
			if(check_font_style_.GetCheck())
				txt->font(Global::instance()->cur_val().page_text_common_.font_style_);
		}
		
	}
	
	
}

void Page_Text_Common::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
	
}
