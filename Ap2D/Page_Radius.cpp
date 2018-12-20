// Page_Radius.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Page_Radius.h"

#include "Global.h"
#include "Mgr_Control.h"
#include "DB_View.h"
#include "RArc.h"
#include "Circle.h"
#include "Arc_Arrow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dlhml;

/////////////////////////////////////////////////////////////////////////////
// Page_Radius property page

IMPLEMENT_DYNCREATE(Page_Radius, CPropertyPage)

Page_Radius::Page_Radius() : CPropertyPage(Page_Radius::IDD)
{
	//{{AFX_DATA_INIT(Page_Radius)
	radius_ = 0.0;
	//}}AFX_DATA_INIT
	select_all_ = FALSE;
}

Page_Radius::~Page_Radius()
{
}

void Page_Radius::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Page_Radius)
	DDX_Control(pDX, IDC_CHECK_L_RADIUS, check_radius_);
	DDX_Text(pDX, IDC_EDIT_RADIUS, radius_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Page_Radius, CPropertyPage)
	//{{AFX_MSG_MAP(Page_Radius)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_CHECK, OnButCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Page_Radius message handlers

void Page_Radius::init()
{

}
void Page_Radius::load_info()
{
	radius_ = Global::instance()->cur_val().page_radius_.radius_;

	UpdateData(FALSE);

}

BOOL Page_Radius::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	init();
	set_checks(TRUE);
	load_info();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Page_Radius::set_checks(BOOL check)
{
	check_radius_.SetCheck(check);
}

void Page_Radius::set_current_val() 
{
	UpdateData();
	if(check_radius_.GetCheck())
		Global::instance()->cur_val().page_radius_.radius_= radius_;

}
void Page_Radius::change_properties() 
{
	for(int i=0;i<ents_.size();i++){
		if(ents_[i]->isa(MY_RUNTIME_CLASS(RArc))){
			dlhml::RArc *v = (dlhml::RArc *)ents_[i];
			v->radius(Global::instance()->cur_val().page_radius_.radius_);
		}else if(ents_[i]->isa(MY_RUNTIME_CLASS(Circle))){
			dlhml::Circle *v = (dlhml::Circle *)ents_[i];
			v->radius(Global::instance()->cur_val().page_radius_.radius_);
		
		}else if(ents_[i]->isa(MY_RUNTIME_CLASS(Arc_Arrow))){
			dlhml::Arc_Arrow *v = (dlhml::Arc_Arrow *)ents_[i];
			v->radius(Global::instance()->cur_val().page_radius_.radius_);
		
		}
	}
}
void Page_Radius::OnButApply() 
{
	// TODO: Add your control notification handler code here
	set_current_val();
	change_properties();
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void Page_Radius::OnButCheck() 
{
	// TODO: Add your control notification handler code here
	select_all_ = !select_all_;
	set_checks(select_all_);
	
}

void Page_Radius::Updata()
{
	load_info();
}
