// Dlg_Setup.cpp : implementation file
//

#include "stdafx.h"
#include "ap2d.h"
#include "Dlg_Setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////



// Dlg_Setup dialog


Dlg_Setup::Dlg_Setup(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Setup::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Setup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_Setup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Setup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Setup, CDialog)
	//{{AFX_MSG_MAP(Dlg_Setup)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Setup message handlers
