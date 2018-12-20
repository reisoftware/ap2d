// Dlg_ApNet.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_ApNet.h"

#include "Global.h"
#include "ApNet_Check.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_ApNet dialog


Dlg_ApNet::Dlg_ApNet(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ApNet::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ApNet)
	user_ = _T("");
	password_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_ApNet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_ApNet)
	DDX_Text(pDX, IDC_EDIT_USER, user_);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, password_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_ApNet, CDialog)
	//{{AFX_MSG_MAP(Dlg_ApNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ApNet message handlers

void Dlg_ApNet::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();	
	ApNet_Check check;
	BOOL res = check.check(user_,password_);
	Global::instance()->cur_val().user_ = user_;
	Global::instance()->cur_val().password_ = password_;
	//BOOL res = check.check_data(user_,password_);
	if(res == TRUE){
		check.save(user_,password_);
		CDialog::OnOK();
	}else{
		CDialog::OnCancel();
	}
}

BOOL Dlg_ApNet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ApNet_Check check;
	check.open(user_,password_);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
