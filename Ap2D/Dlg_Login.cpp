// Dlg_Login.cpp : implementation file
//

#include "stdafx.h"
#include "Ap2D.h"
#include "Dlg_Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Login dialog


Dlg_Login::Dlg_Login(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Login::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Login)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Login)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Login, CDialog)
	//{{AFX_MSG_MAP(Dlg_Login)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Login message handlers
