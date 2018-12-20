// Dlg_Jishou_add.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Jishou_add.h"
#include "DB_Jishou.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Jishou_add dialog


Dlg_Jishou_add::Dlg_Jishou_add(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Jishou_add::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Jishou_add)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Jishou_add::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Jishou_add)
	DDX_Control(pDX, IDC_COMBO_RIGHT_JOINT, combo_joint_right_);
	DDX_Control(pDX, IDC_COMBO_LEFT_JOINT, combo_joint_left_);
	DDX_Control(pDX, IDC_COMBO_ASSEMBLEY_NO, combo_ass_no_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Jishou_add, CDialog)
	//{{AFX_MSG_MAP(Dlg_Jishou_add)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Jishou_add message handlers

void Dlg_Jishou_add::init_dlg_data()
{
	Ji1Shou cur_jishou =DB_Jishou::instance()->get_sel_data();
	if ( DB_Jishou::instance()->re_status() ) {
		combo_ass_no_.SetWindowText(cur_jishou.ass_no_);
		combo_joint_left_.SetWindowText(cur_jishou.l_joint_);
		combo_joint_right_.SetWindowText(cur_jishou.r_joint_);
	}
		
}

BOOL Dlg_Jishou_add::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init_dlg_data();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dlg_Jishou_add::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}



void Dlg_Jishou_add::OnOK() 
{
	// TODO: Add extra validation here
	//ass_no_
	Ji1Shou cur_jishou; //获得当前对话框中的数据
	combo_ass_no_.GetWindowText(cur_jishou.ass_no_);
	combo_joint_left_.GetWindowText(cur_jishou.l_joint_);
	combo_joint_right_.GetWindowText(cur_jishou.r_joint_);

	JS jishous =  DB_Jishou::instance()->return_js_db(); //获得jishous db数据
	if ( !(DB_Jishou::instance()->re_status()) ) {  //判断 是否是编辑弹出的对话框 用来确定添加数据还是编辑数据 true是编辑 false 添加
		int cur_status = 0 ; //记录状态。是否已经存在该部件号。
		for (int i =0 ;i < jishous.size() ;i++ ){
			if ( cur_jishou.ass_no_.Compare(jishous[i].ass_no_) ==0 ){
				cur_status = 1;
				break;
			}		
		}
		if ( cur_status != 1 ){
			if ( cur_jishou.ass_no_.Compare("") == 0 )
				AfxMessageBox("Assembley NO can not be empty !");
			else {
				DB_Jishou::instance()->add_data_to_db(cur_jishou);//向db数据中添加一项
				CDialog::OnOK();
			}
			
		}
		else
			AfxMessageBox("It has been existed ! Please reset or turn off dialog to edit it !");
	}
	else{
		Ji1Shou cur_ji =DB_Jishou::instance()->get_sel_data();
		int cur_status = 0;
		int save_i = 0;
		for (int i = 0 ; i < jishous.size() ; i++ ){
			if ( jishous[i].ass_no_.Compare(cur_ji.ass_no_) == 0 ){
				save_i = i;
			}
			else if ( jishous[i].ass_no_.Compare(cur_jishou.ass_no_) == 0  ){
				cur_status = 1;
			}
		}
		if ( cur_status != 1 ){
			if ( cur_jishou.ass_no_.Compare("") == 0 )
				AfxMessageBox("Assembley NO can not be empty !");
			else{
				jishous[save_i].ass_no_ = cur_jishou.ass_no_;
				jishous[save_i].l_joint_ = cur_jishou.l_joint_;
				jishous[save_i].r_joint_ = cur_jishou.r_joint_;
				DB_Jishou::instance()->init_jishou_db(jishous);
				CDialog::OnOK();
			}
				
		}
		else
			AfxMessageBox("It has been existed ! Please reset or turn off dialog to edit it !");
	}

	
}
