// Dlg_Input.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Input dialog


Dlg_Input::Dlg_Input(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Input::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Input)
	str_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Input::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Input)
	DDX_Text(pDX, IDC_EDIT1, str_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Input, CDialog)
	//{{AFX_MSG_MAP(Dlg_Input)
	ON_BN_CLICKED(ID_BUT_SET, OnButSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Input message handlers

void Dlg_Input::OnButSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	val_ = str_.GetBuffer(0);

	CDialog::OnOK();
}
	