// Array_Cad_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Array_Cad_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Array_Cad_Dlg dialog


Array_Cad_Dlg::Array_Cad_Dlg(CWnd* pParent /*=NULL*/)
:CDialog(Array_Cad_Dlg::IDD, pParent)
MCT_INIT2("Array_Cad_Dlg")
{
	//{{AFX_DATA_INIT(Array_Cad_Dlg)
	degree_ = 0.0;
	col_dis_ = 1.0;
	col_num_ = 1;
	row_dis_ = 1.0;
	row_num_ = 1;
	//}}AFX_DATA_INIT
}


void Array_Cad_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Array_Cad_Dlg)
	DDX_Text(pDX, IDC_EDIT_ANGLE, degree_);
	DDX_Text(pDX, IDC_EDIT_COL_DIS, col_dis_);
	DDX_Text(pDX, IDC_EDIT_COL_NUM, col_num_);
	DDV_MinMaxInt(pDX, col_num_, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_ROW_DIS, row_dis_);
	DDX_Text(pDX, IDC_EDIT_ROW_NUM, row_num_);
	DDV_MinMaxInt(pDX, row_num_, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Array_Cad_Dlg, CDialog)
	//{{AFX_MSG_MAP(Array_Cad_Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Array_Cad_Dlg message handlers

BOOL Array_Cad_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Array_Cad_Dlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	ary.row_num = row_num_;
	ary.col_num = col_num_;
	ary.row_dis = row_dis_;
	ary.col_dis = col_dis_;
	ary.degree  = degree_ ;
	
	CDialog::OnOK();
}
