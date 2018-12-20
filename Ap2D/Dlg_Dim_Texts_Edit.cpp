// Dlg_Dim_Texts_Edit.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Dim_Texts_Edit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Texts_Edit dialog


Dlg_Dim_Texts_Edit::Dlg_Dim_Texts_Edit(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Dim_Texts_Edit::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Dim_Texts_Edit)
	txt1_ = _T("");
	txt2_ = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Dim_Texts_Edit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Dim_Texts_Edit)
	DDX_Text(pDX, IDC_EDIT_TXT1, txt1_);
	DDX_Text(pDX, IDC_EDIT_TXT2, txt2_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Dim_Texts_Edit, CDialog)
	//{{AFX_MSG_MAP(Dlg_Dim_Texts_Edit)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Dim_Texts_Edit message handlers
